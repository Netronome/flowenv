/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_nbi_pre_setup.c
 * @brief       Set up NBI Preclassifier
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

#define NBI0                              0
#define NBI1                              1

#define NBI0_ISLAND                       0x8
#define NBI1_ISLAND                       0x9

/* NBI Preclassifier address defines */

/* PicoEngines */
#define NBIPREPICOENGINECONFIG(nbi)             (0x00280000 + ((nbi) << 24))
#define NBIPREPICOENGINESETUP(nbi)              (0x00280004 + ((nbi) << 24))
#define NBIPREPICOENGINERUNCONTROL(nbi)         (0x00280008 + ((nbi) << 24))

/* Characterizer */
#define NBIPRECHARACTERIZEBUFFERSTATUS(nbi)     (0x00290000 + ((nbi) << 24))


static int running = 0;

static void event_handler(struct nfp_device *nfp,
                          uint32_t ev_type,
                          void *ev_data,
                          uint32_t ev_data_len)
{
    if (ev_type == SIMEVENT_RUN_STOP)
        running = 0;
}

void step_sim(struct nfp_device *dev, int steps)
{
    printf("stepping %d cycles\n", steps);
    running = 1;
    nfp_sal_clock_step(dev, steps, 0);
    while (running) {
        usleep(1000);
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

int nbipreclass_configure(struct nfp_cpp *nfp_cpp,uint32_t nbi)
{
    uint32_t nbi_island;

    if (nbi == NBI0) {
        nbi_island = NBI0_ISLAND;
    } else if (nbi == NBI1) {
        nbi_island = NBI1_ISLAND;
    } else {
        return -1;
    }

    printf("NBI %d Preclassifier setup\n", nbi);
    /* From RV's nbi_island_cfg */
    xpb_writel(nfp_cpp,
               NBIPRECHARACTERIZEBUFFERSTATUS(nbi_island),
               (50 << 24) | (0xff << 16));

    xpb_writel(nfp_cpp,
               NBIPREPICOENGINESETUP(nbi_island),
               (0x3 <<  6)); /* PicoengineSetup.SequenceReplace */

    xpb_writel(nfp_cpp,
               NBIPREPICOENGINERUNCONTROL(nbi_island),
               (    3 << 28) | /* PicoengineRunControl.SMem */
               (0xfff << 16) | /* PicoengineRunControl.GroupMem */
               (0xfff <<  4) | /* PicoengineRunControl.GroupClock */
               (    0 <<  2) | /* PicoengineRunControl.IgnoreResult */
               (    1 <<  0)); /* PicoengineRunControl.Alloc */
    return 0;
}

/* cpp define for picoengine */
#define CPP_NBI_PRECLASSIFIER_OFFSET         (0x300000)
#define CPP_NBI_PRECLASSIFIER_LMEM_OFFSET(x) ((x) == 0 ? 0x30000 : (x)*0x4000)
#define CPP_NBI_PRECLASSIFIER_LMEM_COUNT 12
#define CPP_NBI_PRECLASSIFIER_LMEM_LEN 0x4000

#define CPP_NBI_PRECLASSIFIER_SMEM_OFFSET(x) ((x) == 0 ? 0x90000 : 0xb0000)
#define CPP_NBI_PRECLASSIFIER_SMEM_COUNT 2
#define CPP_NBI_PRECLASSIFIER_SMEM_LEN 0x10000
#define CPP_TGT_NBI 1
#define ISL_NBI0 8

/* basic pico-engine pass through config */
static uint8_t pico_lmem[] = {0x21, 0x22, 0x80, 0x22, 0x80, 0x74, 0x88, 0x2a,
                              0xc0, 0x2a, 0xc2, 0x7f, 0x5b, 0x5b, 0x5b, 0x5b,};

#define XPB_NBI_TABLE(n) (0x08280100 + (n) * 0x1000000)
#define XPB_NBI_TABLE_CNT (32)

/* cpp define for picoengine */
#define CPP_NBI_PRECLASSIFIER_OFFSET         (0x300000)
#define CPP_NBI_PRECLASSIFIER_LMEM_OFFSET(x) ((x) == 0 ? 0x30000 : (x)*0x4000)
#define CPP_NBI_PRECLASSIFIER_LMEM_COUNT 12
#define CPP_NBI_PRECLASSIFIER_LMEM_LEN 0x4000

#define CPP_NBI_PRECLASSIFIER_SMEM_OFFSET(x) ((x) == 0 ? 0x90000 : 0xb0000)
#define CPP_NBI_PRECLASSIFIER_SMEM_COUNT 2
#define CPP_NBI_PRECLASSIFIER_SMEM_LEN 0x10000
#define CPP_TGT_NBI 1
#define ISL_NBI0 8

#define SMEM_LEN 0x10000
#define LMEM_LEN 0x4000

int cpp_nbi_write(struct nfp_cpp *nfp_cpp,
                        int nbi, void * buffer, uint64_t len, uint64_t addr)
{
    uint32_t id = NFP_CPP_ISLD_ID(CPP_TGT_NBI,
                                  NFP_CPP_ACTION_RW,
                                  0,
                                  ISL_NBI0 + nbi);
    return nfp_cpp_write(nfp_cpp, id, addr, buffer, len);
}

int cpp_nbi_read(struct nfp_cpp *nfp_cpp,
                        int nbi, void * buffer, uint64_t len, uint64_t addr)
{
    uint32_t id = NFP_CPP_ISLD_ID(CPP_TGT_NBI,
                                  NFP_CPP_ACTION_RW,
                                  0,
                                  ISL_NBI0 + nbi);
    return nfp_cpp_read(nfp_cpp, id, addr, buffer, len);
}
int pico_config(struct nfp_cpp *nfp_cpp, uint32_t nbi)
{
    uint8_t zeros[SMEM_LEN];
    uint64_t addr;
    int i;

    memset(zeros, '\0', sizeof(zeros));

    /* zero out all the table offsets */
    for (i = 0; i < XPB_NBI_TABLE_CNT; i++)
        xpb_writel(nfp_cpp, XPB_NBI_TABLE(nbi) + i * 4, 0);

    /* zero out shared mems */
    for (i = 0; i < 2; i++) {
        addr = CPP_NBI_PRECLASSIFIER_OFFSET +
                CPP_NBI_PRECLASSIFIER_SMEM_OFFSET(i);
        cpp_nbi_write(nfp_cpp, nbi, zeros, SMEM_LEN, addr);
    }

    /* copy in the pico routine */
    memcpy(zeros, pico_lmem, sizeof(pico_lmem));

    /* load up lmem */
    for (i = 0; i < 12; i++) {
        addr = CPP_NBI_PRECLASSIFIER_OFFSET +
                CPP_NBI_PRECLASSIFIER_LMEM_OFFSET(i);
        cpp_nbi_write(nfp_cpp, nbi, zeros, LMEM_LEN, addr);
    }

    return 0;
}

/*
 * Argument Parsing
 */
#define ARG_DEFAULT_DEVICE  0
#define ARG_DEFAULT_NBI     0

struct arg_data {
    int device;
    int nbi;
};

static void usage(char *progname)
{
    fprintf(stderr,
            "usage: %s [options]\n"
            "\nWhere options are:\n"
            "        -d <device>            -- select NFP device, default 0\n"
            "        -n <nbi>               -- select NBI, default 0\n"
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

    nfp_sal_subs_simevent_all(nfp, &event_handler);

    printf("opening nfp_cpp\n");
    nfp_cpp = nfp_cpp_from_device_id(args.device);
    if (!nfp_cpp) {
        fprintf(stderr, "error: nfp_cpp_from_device_id failed\n");
        return -1;
    }

    retval = nbipreclass_configure(nfp_cpp, args.nbi);

    if (!retval)
        retval = pico_config(nfp_cpp, args.nbi);

    nfp_device_close(nfp);
    nfp_cpp_free(nfp_cpp);

    printf("done\n");

    return retval;
}
