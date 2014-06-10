/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_pcap_record.c
 * @brief       Record packets egressing the SIM ports to pcap files.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>

#include <pcap/pcap.h>

#include <nfp.h>
#include <nfp_sal.h>
#include <nfp_resid.h>

#define MAXFN 256

struct port {
    int nbi;
    int chan;
    char filename[MAXFN];
    pcap_t *pcap;
    pcap_dumper_t *pdump;
    int seq[256];
};


struct port Ports[256];
int Nports = 0;
int Max_packets = 1;
int Check_seq = 0;
int Rc = 0;
int Verbosity = 0;
int Running = 1;


void err(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    exit(-1);
}


void Usage(const char *progname)
{
    fprintf(stderr,
            "usage: %s [-m MAX] [-c] NBI:PORT:FILE [NBI:PORT:FILE ...]\n",
            progname);
    exit(-1);
}


void Configure_port(const char *pstr)
{
    struct port *pt;

    if (Nports == sizeof(Ports)/sizeof(Ports[0]))
        err("too many ports");

    pt = &Ports[Nports++];

    if (sscanf(pstr, "%d:%d:%255s", &pt->nbi, &pt->chan, pt->filename) < 3)
        err("invalid port specification");
}


void Parse_args(int argc, char *argv[])
{
    int i;
    int o;

    while ((o = getopt(argc, argv, "m:cvh")) != -1) {
        switch (o) {
        case 'c':
            Check_seq = 1;
            break;
        case 'h':
            Usage(argv[0]);
            break;
        case 'm':
            Max_packets = atoi(optarg);
            break;
        case 'v':
            Verbosity++;
            break;
        default:
            Usage(argv[0]);
        }
    }

    if (optind == argc) {
        fprintf(stderr, "No ports to listen on\n");
        Usage(argv[0]);
    }

    for (i = optind; i < argc; i++)
        Configure_port(argv[i]);

    if (Nports == 0)
        err("no ports specified");
}


void sig_handler(int sig)
{
    fprintf(stderr, "Signal received ... exiting\n");
    Running = 0;
    Rc = 1;
}


void Open_pcap_dumpers(void)
{
    int i;
    struct port *pt;

    for (i = 0; i < Nports; i++) {

        pt = &Ports[i];
        pt->pcap = pcap_open_dead(DLT_EN10MB, 65535);
        if (pt->pcap == NULL)
            err("unable to create pcap");

        pt->pdump = pcap_dump_open(pt->pcap, pt->filename);
        if (pt->pdump == NULL)
            err("unable to open %s for writing\n", pt->filename);

        pcap_dump_flush(pt->pdump);
    }
}


void Verify(struct port *pt, int pnum, unsigned char *pkt, long len)
{
    int nbi;
    int chan;
    int ctx;
    int seq;

    if (!Check_seq)
        return;

    if (len < 6) {
        fprintf(stderr, "Received runt packet\n");
        Rc = 1;
        return;
    }

    nbi = pkt[1];
    chan = pkt[2];
    ctx = pkt[3];
    seq = ntohs(*(const uint16_t *)&pkt[4]);

    if (nbi != pt->nbi) {
        fprintf(stderr, "Packet %d came out nbi %d instead of %d\n", pnum,
                pt->nbi, nbi);
        Rc = 1;
    }

    if (chan != pt->chan) {
        fprintf(stderr, "Packet %d came out channel %d instead of %d\n", pnum,
                pt->chan, chan);
        Rc = 1;
    }

    if (seq < pt->seq[ctx]) {
        fprintf(stderr, "Packet %d out of sequence.  Has seq %d but expected "
                        "at least %d\n", pnum, seq, pt->seq[ctx]);
        Rc = 1;
    }
}


void Record_packets(void)
{
    struct nfp_device *dev;
    int p;
    int nready;
    int npkts = 0;
    int nptick;
    char data[65536];
    long len;
    uint64_t etime;
    struct pcap_pkthdr ph;
    struct port *pt;

    dev = nfp_device_open(0);
    if (dev == NULL)
        err("Could not open simulator handle");

    while (Running) {

        for (nptick = 0, p = 0; p < Nports; p++) {

            pt = &Ports[p];

            nready = nfp_sal_packet_egress_status(dev, pt->nbi, pt->chan);
            while (nready > 0 && npkts < Max_packets) {

                len = nfp_sal_packet_egress(dev, pt->nbi, pt->chan, data,
                                            sizeof(data), &etime);

                if (len <= 0) {
                    fprintf(stderr, "Invalid packet length: %ld\n", len);
                    exit(-1);
                }

                if (Verbosity > 0)
                    fprintf(stderr, "Received a packet on %d:%d of %d bytes\n",
                            pt->nbi, pt->chan, (int)len);

                memset(&ph, 0, sizeof(ph));
                ph.ts.tv_sec = 0;
                ph.ts.tv_usec = 0;
                ph.caplen = len;
                ph.len = len;

                Verify(pt, npkts, data, len);

                pcap_dump((u_char *)pt->pdump, &ph, data);
                pcap_dump_flush(pt->pdump);

                npkts++;
                nptick++;
                nready--;
            }

            if (npkts == Max_packets)
                goto out;
        }

        if (nptick == 0)
            usleep(10000);

    }

out:
    nfp_device_close(dev);
}


void Close_pcap_dumpers(void)
{
    int i;
    for (i = 0; i < Nports; i++) {
        pcap_dump_close(Ports[i].pdump);
        pcap_close(Ports[i].pcap);
    }
}


int main(int argc, char *argv[])
{
    Parse_args(argc, argv);
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);
    Open_pcap_dumpers();
    Record_packets();
    Close_pcap_dumpers();
    return Rc;
}
