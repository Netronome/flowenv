/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_step.c
 * @brief       Step an NFP simulator
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
#include <sys/time.h>

#include "ns_log.h"

#include "nfp.h"
#include "nfp_cpp.h"
#include "nfp_sal.h"

void step_sim(struct nfp_device *dev, int steps)
{
    printf("stepping %d cycles\n", steps);
    nfp_sal_clock_step(dev, steps, 1);
}


/*
 * Argument Parsing
 */
#define ARG_DEFAULT_DEVICE  0

struct arg_data {
    int device;
};

static void usage(char *progname)
{
    fprintf(stderr,
            "usage: %s [options] <binfile>\n"
            "\nWhere options are:\n"
            "        -d <device>   -- select NFP device, default 0\n"
            "and arguments are:\n"
            "        <value>       -- number of ME steps to take\n",
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

static void parse_options(struct arg_data* args, int argc, char *argv[])
{
    int o;
    uint64_t val;

    args->device = ARG_DEFAULT_DEVICE;

    while ((o = getopt(argc, argv, "d:h")) != -1) {
        switch(o) {
        case 'h':
            usage(argv[0]);
            exit(0);
            break;
        case 'd':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            args->device = val;
            break;
        default:
            usage(argv[0]);
            exit(1);
            break;
        }
    }

    if (argc - optind < 1) {
        fprintf(stdout, "if no step size provided default to 100\n");
    }

}


int main(int argc, char **argv)
{
    struct nfp_device *nfp;

    int n = 100;
    long int tusec;
    float sec;
    struct arg_data args;

    NS_LOG_SET_LEVEL(NS_LOG_LVL_INFO);

    parse_options(&args, argc, argv);

    printf("opening nfp_device\n");
    nfp = nfp_device_open(args.device);
    if (!nfp) {
        fprintf(stderr, "error: nfp_device_open failed\n");
        return -1;
    }

    if (argc > optind)
        n = atoi(argv[optind]);
    {
        struct timeval tv0, tv1;
        gettimeofday(&tv0, NULL);
        step_sim(nfp, n);
        gettimeofday(&tv1, NULL);
        tusec = (tv1.tv_sec * 1000000 + tv1.tv_usec) - (tv0.tv_sec * 1000000 + tv0.tv_usec);
        sec = ((float)tusec) / (1000*1000);
        printf("%d cycles took %f us (%f cycles/per second)\n", n, sec, ((float) n) / sec);

    }

    nfp_device_close(nfp);

    return 0;
}
