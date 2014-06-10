/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_pcap_play.c
 * @brief       Inject packets from a PCAP file into the NFP simulator
 */
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <pcap/pcap.h>

#include "nfp.h"
#include "nfp_sal.h"

#define ARG_DEFAULT_DEVICE   0
#define ARG_DEFAULT_NBI      0
#define ARG_DEFAULT_PORT     0
#define ARG_DEFAULT_LOOPS    1
#define ARG_DEFAULT_USETIME  0
#define ARG_DEFAULT_WAITTIME  0
#define ARG_DEFAULT_USASNS  0

struct pcap_play_data {
    int arg_device; /* which nfp_device to use */
    int arg_nbi;
    int arg_port;
    int arg_loops;
    int arg_usetime;
    int arg_usasns;
    uint64_t arg_waittime;

    struct nfp_device *nfp;

    char *pcap_filename;
};

static void usage(char *progname)
{
    fprintf(stderr,
            "usage: %s [options] <pcapfile>\n"
            "\nWhere options are:\n"
            "        -t          -- use pcap time for sending\n"
            "        -d <device> -- select NFP device\n"
            "        -n <nbi>    -- select NBI\n"
            "        -p <port>   -- select NBI port\n"
            "        -w <time>   -- sim time in picoseconds to wait before\n"
            "                       first packet is sent\n"
            "        -u          -- interpret microsecond as nanoseconds\n"
            "                       for the pcap file\n"
            "and arguments are:\n"
            "        <pcapfile>  -- the pcap file to play\n",
            progname);
}

static int uintarg(const char *s, uint64_t *val)
{
    char *cp;
    uint64_t r;
    r = strtoull(s, &cp, 0);
    if (cp == s) {
        fprintf(stderr, "Invalid integer value: %s\n", s);
        return -1;
    }
    *val = r;
    return 0;
}

static void parse_options(struct pcap_play_data* pp_data,
                          int argc,
                          char *argv[])
{
    int o;
    uint64_t val;

    pp_data->arg_device = ARG_DEFAULT_DEVICE;
    pp_data->arg_nbi = ARG_DEFAULT_NBI;
    pp_data->arg_port = ARG_DEFAULT_PORT;
    pp_data->arg_loops = ARG_DEFAULT_LOOPS;
    pp_data->arg_usetime = ARG_DEFAULT_USETIME;
    pp_data->arg_waittime = ARG_DEFAULT_WAITTIME;
    pp_data->arg_usasns = ARG_DEFAULT_USASNS;

    while ((o = getopt(argc, argv, "w:d:n:p:l:htu")) != -1) {
        switch(o) {
        case 'h':
            usage(argv[0]);
            exit(0);
            break;
        case 't':
            pp_data->arg_usetime = 1;
            break;
        case 'u':
            pp_data->arg_usasns = 1;
            break;
        case 'w':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            pp_data->arg_waittime = val;
            break;
        case 'd':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            pp_data->arg_device = val;
            break;
        case 'n':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            pp_data->arg_nbi = val;
            break;
        case 'p':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            pp_data->arg_port = val;
            break;
        case 'l':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            pp_data->arg_loops = val;
            break;
        default:
            usage(argv[0]);
            exit(1);
            break;
        }
    }

    if (argc  - optind != 1) {
        fprintf(stderr, "must specify a pcap file\n");
        usage(argv[0]);
        exit(1);
    }

    pp_data->pcap_filename = argv[optind];
}

#define PACKET_MAX 16000
static int play_pcap(struct pcap_play_data *pp_data)
{
    pcap_t *pcap = NULL;
    struct pcap_pkthdr ph;
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    const unsigned char *pktdata;
    int ret;
    int n = 0;
    int first = 1;
    uint64_t simstart_ps = 0;
    uint64_t timein_ps;
    uint64_t timeoffset_ps;
    uint64_t timetosend_ps;

    /* get the current sim time */
    simstart_ps = nfp_sal_packet_get_time(pp_data->nfp);
    /* XXX: would it be better to get the last queued packet time rather? */

    pcap = pcap_open_offline(pp_data->pcap_filename, pcap_errbuf);
    if (!pcap) {
        fprintf(stderr, "pcap_open_offline() failed for file %s: %s\n",
                                        pp_data->pcap_filename, pcap_errbuf);
        exit(1);
    }

    while (1) {
        pktdata = pcap_next(pcap, &ph);
        if (!pktdata)
            break;

        /* calculate time to send */
        if (pp_data->arg_usasns) { /* interpret us as ns */
            timein_ps = ph.ts.tv_sec * 1000 * 1000 * 1000 * 1000 +
                        ph.ts.tv_usec * 1000;
        } else {
            timein_ps = ph.ts.tv_sec * 1000 * 1000 * 1000 * 1000 +
                        ph.ts.tv_usec * 1000 * 1000;
        }
        /* for the first packet set a zero reference */
        if (first)
            timeoffset_ps = timein_ps;

        timein_ps -= timeoffset_ps;

        if (pp_data->arg_usetime)
            timetosend_ps = pp_data->arg_waittime + timein_ps + simstart_ps;
        else
            timetosend_ps = 0; /* send immediately */

        ret = nfp_sal_packet_ingress(pp_data->nfp,
                                     pp_data->arg_nbi,
                                     pp_data->arg_port,
                                     pktdata,
                                     ph.caplen,
                                     timetosend_ps);
        if (ret < 0) {
            fprintf(stderr, "nfp_sal_packet_ingress() failed: %s\n",
                                                    strerror(errno));
            exit(1);
        }

        first = 0;
        n++;
    }

    return n;
}

int main(int argc, char **argv)
{
    struct pcap_play_data pp_data;
    int i;
    int n = 0;

    parse_options(&pp_data, argc, argv);

    pp_data.nfp = nfp_device_open(pp_data.arg_device);

    if (!pp_data.nfp) {
        fprintf(stderr, "failed to open nfp device: %s\n", strerror(errno));
        exit(1);
    }

    for (i = 0; i < pp_data.arg_loops; i++) {
        n += play_pcap(&pp_data);
    }

    nfp_device_close(pp_data.nfp);

    printf("sent %d packets\n", n);

    return 0;
}
