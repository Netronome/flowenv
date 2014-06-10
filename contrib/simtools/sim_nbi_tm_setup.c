/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_nbi_tm_setup.c
 * @brief       Initialize an NFP simulation NBI traffic manager.
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

#include "ns_log.h"

#include "nfp.h"
#include "nfp_cpp.h"
#include "nfp_sal.h"

/* address defines */
#define NBI0                              0
#define NBI1                              1

#define NBI0_ISLAND                       0x8
#define NBI1_ISLAND                       0x9

#define NBI_TMCONFIG(nbi)                       (0x00140000 + ((nbi) << 24))
#define NBI_TM_MINIPKTCREDITCONFIG(nbi)         (0x00140300 + ((nbi) << 24))
#define NBI_TMQSTATUS(nbi,x)                    (0x00150000 + ((nbi) << 24))
#define NBI_TMQCONFIG(nbi,x)                    ((0x00151000 + ((nbi) << 24)) + (x)*4)
#define NBI_TMEGRESSRATE(nbi)                   (0x00140074 + ((nbi) << 24))
#define CPP_TGT_NBI 1
#define CPP_NBI_TMHDTL(x) (0x68000 + (x) * 8 + 0x200000)

void cpp_write64(struct nfp_cpp *h, uint32_t id, uint64_t a, uint64_t d)
{
    int ret;
    ret = nfp_cpp_write(h, id, a, (const void *)&d, 8);
    if (ret < 0) {
        fprintf(stderr, "error with cpp read to address %lx : %s\n",
                            a, strerror(errno));
    }
}

void xpb_writel(struct nfp_cpp *h, uint32_t a, uint32_t d)
{
    int ret;
    ret = nfp_xpb_writel(h, a, d);
    if (ret < 0) {
        fprintf(stderr, "error with xpb write to address %x : %s\n",
                            a, strerror(errno));
    }
}

int nbitm_configure(struct nfp_device *nfp, struct nfp_cpp *nfp_cpp,
                    uint32_t nbi, uint32_t nseqr)
{
    uint32_t nbi_island;
    uint32_t id;
    int i;

    if (nbi == NBI0) {
        nbi_island = NBI0_ISLAND;
    } else if (nbi == NBI1) {
        nbi_island = NBI1_ISLAND;
    } else {
        return -1;
    }
    id = NFP_CPP_ISLD_ID(CPP_TGT_NBI,
                         NFP_CPP_ACTION_RW,
                         0,
                         nbi_island);


    /* compute the encoded seqr # */
    /* 1 seqr: 1, 2 seqr: 2, 4 seqr: 3, 8 seqr: 4... */
    if (nseqr < 1 || nseqr > 32 || ((nseqr & (nseqr - 1)) != 0)) {
        fprintf(stderr, "Invalid number of sequencers: %d\n", nseqr);
        return -1;
    }
    for (i = 1; (nseqr & (1 << (i-1))) == 0; ++i)
            ;
    nseqr = i;

    printf("Minimal NBI%d TM Configuration - single queue, no shaping\n", nbi);
    xpb_writel(nfp_cpp,
               NBI_TMCONFIG(nbi_island),
               (nseqr << 1) | /* TrafficManagerConfig.NumSequencers = 1 */
               (1 << 6) | /* TrafficManagerConfig.MiniPacketFCEnable = 1 */
               (0 << 7) | /* TrafficManagerConfig.ShaperEnable = 0 */
               (1 << 8) | /* TrafficManagerConfig.SchedulerEnable = 1 */
               (1 << 10)| /* TrafficManagerConfig.Sequencer0Enable = 1 */
               (1 << 11)| /* TrafficManagerConfig.DescQueuesEnable = 1 */
               (1 << 12)  /* TrafficManagerConfig.LevelCheckEnable = 1 */
               );

    // nfp_sal_cpp_mode(nfp_cpp, NFP_SAL_CPP_MODE_FRONTONLY);

#define QUEUE_SZ 16
#define QUEUE_NUM 1024 // (enable all tx queues)
    /*TMQueueReg.QueueConfig[i]*/
    for (i = 0; i < QUEUE_NUM; i++) {
        xpb_writel(nfp_cpp, NBI_TMQCONFIG(nbi_island, i),
                0x4 << 7 | /* TMQueueReg.QueueConfig[i].QueueSize = 0x4 (16 desc) */
                1 << 0 /* TMQueueReg.QueueConfig[i].QueueEnable = 0x1 */
        );
    }

    /*TMHeadTailSram.TMHeadTailEntry*/
    for (i = 0; i < QUEUE_NUM; i++) {
        uint64_t val;
        val = (((i * QUEUE_SZ) & 0x3FFF) << 14) | ((i * QUEUE_SZ) & 0x3FFF);

        // printf("%x = %lx TMHeadTailSram.TMHeadTailEntry[%d]\n", CPP_NBI_TMHDTL(i), val,i);

        cpp_write64(nfp_cpp, id, CPP_NBI_TMHDTL(i), val);


    }

    // SON adding check of backdoor access
#if 0
    for (i=0; i<QUEUE_NUM; i++)
    {
        uint64_t rd;
        nfp_cpp_read(nfp_cpp, id, CPP_NBI_TMHDTL(i), (void *)&rd, 8);
        printf("nbi%d check: ht_reg %d = %lx, tail = %lx, head = %lx\n", nbi, i, rd, (rd & 0x3fff), ((rd >> 14) & 0x3fff));
    }
#endif

    // nfp_sal_cpp_mode(nfp_cpp, NFP_SAL_CPP_MODE_BACKONLY);


    xpb_writel(nfp_cpp,
            NBI_TM_MINIPKTCREDITCONFIG(nbi_island),
               (0x200 << 12) | /* free pool of 512 credits */
               (8 << 0) /* setting to 8 as max value for 128 channels */
               );


    return 0;
    }


/*
 * Argument Parsing
 */
#define ARG_DEFAULT_DEVICE  0
#define ARG_DEFAULT_NBI     0
#define ARG_DEFAULT_NSEQR   1

struct arg_data {
    int device;
    int nbi;
    int nseqr;
};

static void usage(char *progname)
{
    fprintf(stderr,
            "usage: %s [options]\n"
            "\nWhere options are:\n"
            "        -d <device>            -- select NFP device, default 0\n"
            "        -n <nbi>               -- select NBI, default 0\n"
            "        -s <nseqr>             -- select number of sequencers, default 1\n"
            "        -h                     -- print help\n",
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
    args->nbi = ARG_DEFAULT_NBI;
    args->nseqr = ARG_DEFAULT_NSEQR;

    while ((o = getopt(argc, argv, "d:n:h")) != -1) {
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
        case 'n':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            args->nbi = val;
            break;
        case 's':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            args->nseqr = val;
            break;
        default:
            usage(argv[0]);
            exit(1);
            break;
        }
    }


}


int main(int argc, char **argv)
{
    struct nfp_device *nfp;
    struct nfp_cpp *nfp_cpp;
    uint32_t retval;
    struct arg_data args;

    NS_LOG_SET_LEVEL(NS_LOG_LVL_INFO);

    parse_options(&args, argc, argv);

    printf("opening nfp_device\n");
    nfp = nfp_device_open(args.device);
    if (!nfp) {
        fprintf(stderr, "error: nfp_device_open failed\n");
        return -1;
    }

    printf("opening nfp_cpp\n");
    nfp_cpp = nfp_cpp_from_device_id(args.device);
    if (!nfp_cpp) {
        fprintf(stderr, "error: nfp_cpp_from_device_id failed\n");
        return -1;
    }

    retval = nbitm_configure(nfp, nfp_cpp, args.nbi, args.nseqr);

    nfp_device_close(nfp);
    nfp_cpp_free(nfp_cpp);

    printf("done\n");

    return retval;
}
