/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_nbi_dma_setup.c
 * @brief       Initialize an NFP simulator NBI DMA engine
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

#define CPP_TGT_NBI 1
#define CPP_NBI_DMABLQMEM 0
#define CPP_NBI_DMABLQCTL(x) (0x8000 + (x) * 8)

/* NBIDMA address defines */

#define NBI0                              0
#define NBI1                              1

#define NBI0_ISLAND                       0x8
#define NBI1_ISLAND                       0x9

#define ME_ISLAND0                        32
#define ME_ISLAND1                        33
#define ME_ISLAND2                        34
#define ME_ISLAND3                        35
#define ME_ISLAND4                        36
#define ME_ISLAND5                        37
#define ME_ISLAND6                        38

#define ME_ISLANDS                        7

#define NBI_DMACFG(nbi)                         (0x00100000 + ((nbi) << 24))
#define NBI_DMASPARE(nbi)                       (0x00100004 + ((nbi) << 24))
#define NBI_DMABLQEVENT(nbi)                    (0x0010000c + ((nbi) << 24))
#define NBI_DMARATE(nbi)                        (0x00100010 + ((nbi) << 24))
#define NBI_DMACREDIT(nbi)                      (0x00100014 + ((nbi) << 24))
#define NBI_DMABPECHAINEND(nbi)                 (0x00100018 + ((nbi) << 24))
#define NBI_DMABPCFG(nbi,x)             (0x00100020 + ((nbi) << 24) + (x)*4)
#define NBI_DMABPECFG(nbi,x)            (0x00100040 + ((nbi) << 24) + (x)*4)
#define NBI_DMAPKTCNTLO(nbi)                    (0x001000c0 + ((nbi) << 24))
#define NBI_DMAPKTCNTHI(nbi)                    (0x001000c4 + ((nbi) << 24))
#define NBI_DMABYTECNTLO(nbi)                   (0x001000c8 + ((nbi) << 24))
#define NBI_DMABYTECNTHI(nbi)                   (0x001000cc + ((nbi) << 24))
#define NBI_DMADROPPKTCNTLO(nbi)                (0x001000d0 + ((nbi) << 24))
#define NBI_DMADROPPKTCNTHI(nbi)                (0x001000d4 + ((nbi) << 24))
#define NBI_DMADROPBYTECNTLO(nbi)               (0x001000d8 + ((nbi) << 24))
#define NBI_DMADROPBYTECNTHI(nbi)               (0x001000dc + ((nbi) << 24))
#define NBI_DMABUFFALLOCCREDITLIMIT0(nbi)       (0x001000e0 + ((nbi) << 24))
#define NBI_DMABUFFALLOCCREDITLIMIT1(nbi)       (0x001000e4 + ((nbi) << 24))
#define NBI_DMACPPMSTRCREDITLIMIT(nbi)          (0x001000e8 + ((nbi) << 24))
#define NBI_DMAARBITERCREDITLIMIT0(nbi)         (0x001000ec + ((nbi) << 24))
#define NBI_DMAARBITERCREDITLIMIT1(nbi)         (0x001000f0 + ((nbi) << 24))
#define NBI_DMACTRLCREDITLIMIT0(nbi)            (0x001000f4 + ((nbi) << 24))
#define NBI_DMACTRLCREDITLIMIT1(nbi)            (0x001000f8 + ((nbi) << 24))
#define NBI_DMAPUSHBUSCREDITLIMIT(nbi)          (0x001000fc + ((nbi) << 24))
#define NBI_DMARDCTRLCREDITLIMIT0(nbi)          (0x00100100 + ((nbi) << 24))
#define NBI_DMARDCTRLCREDITLIMIT1(nbi)          (0x00100104 + ((nbi) << 24))
#define NBI_DMARDCTRLCREDITLIMIT2(nbi)          (0x00100108 + ((nbi) << 24))
#define NBI_DMAMCRARBITERCREDITLIMIT(nbi)       (0x0010010c + ((nbi) << 24))
#define NBI_DMACREDITTHROTTLECFG(nbi,x) ((0x00100110 + ((nbi) << 24) + (x)*4)
#define NBI_DMAASSERTIONSCFG(nbi)               (0x00100130 + ((nbi) << 24))
#define NBI_DMAPERFCTRL(nbi)                    (0x00100134 + ((nbi) << 24))


static int running = 0;

/*
 * Argument Parsing
 */
#define ARG_DEFAULT_DEVICE  0
#define ARG_DEFAULT_NBI     0
#define ARG_DEFAULT_NUM_ISLANDS     1

struct arg_data {
    uint32_t device;
    uint32_t nbi;
    uint32_t nislands;
};

struct nbi_dma_bp_cfg
{
    int DropEn;
    int CtmOffset;
    int PriBlist;
    int SecBlist;
    int SplitLength;
    int BpeHead;
};

struct nbi_dma_bpe_cfg
{
    int BpeNum;
    int Ctm;
    int PktCredit;
    int BufCredit;
    int ChainEnd;
};

static void event_handler(struct nfp_device *nfp, uint32_t ev_type,
                          void *ev_data, uint32_t ev_data_len)
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

void cpp_write64(struct nfp_cpp *h, uint32_t id, uint64_t a, uint64_t d)
{
    int ret;
    ret = nfp_cpp_write(h, id, a, (const void *) &d, 8);
    if (ret < 0) {
        fprintf(stderr, "error with cpp read to address %lx : %s\n", a,
                strerror(errno));
        exit(1);
    }
}

void cpp_read64(struct nfp_cpp *h, uint32_t id, uint64_t a, uint64_t *d)
{
    int ret;
    ret = nfp_cpp_read(h, id, a, (void *) d, 8);
    if (ret < 0) {
        fprintf(stderr, "error with cpp read to address %lx : %s\n", a,
                strerror(errno));
        exit(1);
    }
}

void xpb_readl(struct nfp_cpp *h, uint32_t a, uint32_t* d)
{
    int ret;
    ret = nfp_xpb_readl(h, a, d);
    if (ret < 0) {
        fprintf(stderr, "error with xpb read from address %x : %s\n", a,
                strerror(errno));
        exit(1);
    }
}

void xpb_writel(struct nfp_cpp *h, uint32_t a, uint32_t d)
{
    int ret;
    ret = nfp_xpb_writel(h, a, d);
    if (ret < 0) {
        fprintf(stderr, "error with xpb write to address %x : %s\n", a,
                strerror(errno));
        exit(1);
    }
}

int nbi_dma_config(struct nfp_cpp *nfp_cpp, int nbi_island)
{
    xpb_writel(nfp_cpp,
               NBI_DMACFG(nbi_island), (0 << 10) | /*DisRxBlqWrInErr = 0*/
               (((nbi_island - NBI0_ISLAND) + 1) << 7) | /* NbiNum + 1 */
               (1 << 6) | /* CtmPollEna = 1 */
               (3 << 4) | /*CtmPollIntvl = 512us */
               (0 << 1) | /* RateLimitEnable = 0*/
               (1 << 0) /*CTM Poll search is enabled**/);

    xpb_writel(nfp_cpp, NBI_DMABLQEVENT(nbi_island), 0x0000ff);

    xpb_writel(nfp_cpp,
               NBI_DMARATE(nbi_island), (0 << 6) | /* CreditRate3 = 0 */
               (0 << 4) | /* CreditRate2 = 0 */
               (0 << 2) | /* CreditRate1 = 0*/
               (0 << 0) /* CreditRate0 = 0*/);

    xpb_writel(nfp_cpp,
               NBI_DMACREDIT(nbi_island), (3 << 14) | /* Threshold3 = 3 */
               (3 << 12) | /* Threshold2 = 3 */
               (3 << 10) | /* Threshold1 = 3*/
               (3 << 8) | /* Threshold0 = 3*/
               (3 << 6) | /* CreditRate3 = 3 */
               (3 << 4) | /* CreditRate2 = 3 */
               (3 << 2) | /* CreditRate1 = 3*/
               (3 << 0) /* CreditRate0 = 3*/);

    return 0;
}

int nbi_dma_mu_config(struct nfp_cpp *nfp_cpp, int nbi_island, int buf_cnt,
                      int buf_size, int mu_i)
{
    uint32_t id = NFP_CPP_ISLD_ID(CPP_TGT_NBI, NFP_CPP_ACTION_RW, 0,
                                  nbi_island);
    int count;
    uint64_t mu_addr;
    uint64_t buf;
    int retval;
    int muiid = mu_i;

    /* XXX Only handles IMU */
    /* MU Address base */
    if ((mu_i == 28) || (mu_i == 29)) {
        /* IMU IIDs:28,29 (IMU is always direct access) */
        mu_addr = (0x8000000000 | ((uint64_t) muiid << 32));
    } else {
        fprintf(stderr, "invalid MU Island: %d\n", mu_i);
        exit(1);
    }

    /* Fill BDSram with MU ptrs */
    count = 0;
    while (count < buf_cnt) {
        buf = ((mu_addr + (buf_size * count)) >> 11);
        /* printf("count: %d %lx\n", count, buf); */
        retval = nfp_cpp_write(nfp_cpp, id, CPP_NBI_DMABLQMEM + (count * 8),
                (const void *) &buf, 8);
        if (retval < 0) {
            fprintf(stderr, "BDSram: Unable to write to %lx=%lx\n",
                    (uint64_t)(count * 8), buf);
        }
        count += 1;
    }
    return 0;
}

int nbi_dma_bl_config(struct nfp_cpp *nfp_cpp, int island_id, int blq, int head,
                      int tail, int size)
{
    int retval = 0;
    uint32_t id = NFP_CPP_ISLD_ID(CPP_TGT_NBI, NFP_CPP_ACTION_RW, 0, island_id);
    uint64_t val;

    val = ((uint64_t)(tail - 1)) & 0xfff;
    val |= ((uint64_t) head) << 12;
    val |= ((uint64_t) size) << 36;
    cpp_write64(nfp_cpp, id, CPP_NBI_DMABLQCTL(blq), val);

    return retval;
}

int nbi_dma_bp_config(struct nfp_cpp *nfp_cpp, int island_id, int Bp,
                      struct nbi_dma_bp_cfg* bp_cfg)
{

    int retval;

    uint32_t val;

    val = (bp_cfg->DropEn << 13) | (bp_cfg->CtmOffset << 12)
            | (bp_cfg->PriBlist << 10) | (bp_cfg->SecBlist << 8)
            | (bp_cfg->SplitLength << 5) | (bp_cfg->BpeHead);

    retval = nfp_xpb_writel(nfp_cpp, NBI_DMABPCFG(island_id, Bp), val);

    return retval;
}

int nbi_dma_bpe_config(struct nfp_cpp *nfp_cpp, int island_id,
                       struct nbi_dma_bpe_cfg * bpe_cfg)
{
    uint32_t val;
    int retval;

    val = (bpe_cfg->BpeNum << 27) | (bpe_cfg->Ctm << 21)
            | (bpe_cfg->PktCredit << 10) | (bpe_cfg->BufCredit);

    retval = nfp_xpb_writel(nfp_cpp, NBI_DMABPECFG(island_id, bpe_cfg->BpeNum),
                            val);

    if (retval < 0)
        return retval;

#if DEBUG
    xpb_readl(nfp_cpp, NBI_DMABPECFG(island_id, bpe_cfg->BpeNum), &rval);
    if (rval != val) {
        fprintf(stderr, "Write of buffer pool entry %d did not work\n",
                bpe_cfg->BpeNum);
        fprintf(stderr, "Wrote %08x but read back %08x\n", val, rval);
        return -1;
    }
#endif


    if (bpe_cfg->ChainEnd == 1) {
        retval = nfp_xpb_readl(nfp_cpp, NBI_DMABPECHAINEND(island_id), &val);
        if (retval < 0)
            return retval;
        val = val | (1 << bpe_cfg->BpeNum);

        retval = nfp_xpb_writel(nfp_cpp, NBI_DMABPECHAINEND(island_id), val);

#if DEBUG
        xpb_readl(nfp_cpp, NBI_DMABPECHAINEND(island_id), &rval);
        if (rval != val) {
            fprintf(stderr, "Write of BPE chain end %d did not work\n",
                    bpe_cfg->BpeNum);
            fprintf(stderr, "Wrote %08x but read back %08x\n", val, rval);
            return -1;
        }
#endif
    }

    return (retval);
}

int nbidma_configure(struct nfp_cpp *nfp_cpp, uint32_t nbi, uint32_t nislands)
{
    int i;
    uint32_t nbi_island;
    uint32_t me_island[ME_ISLANDS];
    struct nbi_dma_bp_cfg bp_cfg;
    struct nbi_dma_bpe_cfg bpe_cfg;
    int pkt_count;
    int pkt_buf_size = 2048;
    int mu_i = 28;
    int retval;
    /*
     * This implementation is non generic. It is given only as an example.
     */

    if (nbi == NBI0) {
        nbi_island = NBI0_ISLAND;
        for (i = 0; i < nislands; ++i)
            me_island[i] = ME_ISLAND0 + i;
    } else if (nbi == NBI1) {
        mu_i += 1;
        nbi_island = NBI1_ISLAND;
        for (i = 0; i < nislands; ++i) {
            /*ME island 6 (island id 38) is the closest to NBI 1*/
            me_island[i] = ME_ISLAND6 - i;
        }
    } else {
        return -1;
    }

    /* 1.5 MB per NBI */
    pkt_count = 0x180000 / pkt_buf_size;

    printf("MU Config\n");
    retval = nbi_dma_mu_config(nfp_cpp, nbi_island, pkt_count, pkt_buf_size,
                               mu_i);
    if (retval < 0) {
        fprintf(stderr, "Error configuring MU for NBI%d\n", nbi);
        return retval;
    }

    printf("BL Config\n");
    retval = nbi_dma_bl_config(nfp_cpp, nbi_island, 0, /* Blq */
                                    (pkt_count - 1), /* head */
                                     0, /* tail */
                                     3); /* size */

    printf("DMA Config\n");
    retval = nbi_dma_config(nfp_cpp, nbi_island);
    if (retval < 0) {
        fprintf(stderr, "Error configuring DMA for NBI%d\n", nbi);
        return retval;
    }

    printf("BP Config\n");
    bp_cfg.DropEn = 0;
    bp_cfg.CtmOffset = 1;/* CtmOffset = 1 */
    bp_cfg.PriBlist = 0;/* PriBList = 0 */
    bp_cfg.SecBlist = 0;/* SecBList = 0 */
    bp_cfg.SplitLength = 3; /* SplitLength = 2K */
    bp_cfg.BpeHead = 0;
    retval = nbi_dma_bp_config(nfp_cpp, nbi_island, 0, &bp_cfg);
    if (retval < 0) {
        fprintf(stderr, "Error configuring BP for NBI%d\n", nbi);
        return retval;
    }

    printf("BPE Config\n");
    bpe_cfg.PktCredit = 512;
    bpe_cfg.BufCredit = (256 * 1024) / 2048;
    bpe_cfg.ChainEnd = 0;
    for (i = 0; i < nislands; i++) {
        bpe_cfg.Ctm = me_island[i];
        bpe_cfg.BpeNum = i;
        if (i == nislands-1)
            bpe_cfg.ChainEnd = 1;
        printf("\tAdding buffer pool entry for island %d\n", bpe_cfg.Ctm);
        retval = nbi_dma_bpe_config(nfp_cpp, nbi_island, &bpe_cfg);
        if (retval < 0) {
            fprintf(stderr, "error setting BPE%d for NBI%d\n", i, nbi);
            return retval;
        }
    }

    printf("Configure NBI%d DMA - done\n", nbi);

    return retval;
}

static void usage(char *progname)
{
    fprintf(stderr,
            "usage: %s [options]\n"
            "\nWhere options are:\n"
            "        -d <device>            -- select NFP device, default 0\n"
            "        -n <nbi>               -- select NBI, default 0\n"
            "        -i <nislands>          -- select # of islands, default 1\n"
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
    args->nislands = ARG_DEFAULT_NUM_ISLANDS;

    while ((o = getopt(argc, argv, "d:n:i:h")) != -1) {
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
        case 'i':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            args->nislands = val;
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
    struct arg_data args;
    int retval;

    NS_LOG_SET_LEVEL(NS_LOG_LVL_INFO);

    parse_options(&args, argc, argv);

    printf("---nbidma_setup---\n");
    nfp = nfp_device_open(0);
    if (!nfp) {
        fprintf(stderr, "error: nfp_device_open failed\n");
        return -1;
    }

    nfp_sal_subs_simevent_all(nfp, &event_handler);

    nfp_cpp = nfp_cpp_from_device_id(0);
    if (!nfp_cpp) {
        fprintf(stderr, "error: nfp_cpp_from_device_id failed\n");
        return -1;
    }

    printf("Configuring NBI%d with %d islands starting with MEI%d and %s\n",
           args.nbi, args.nislands, (args.nbi == NBI0 ? 0 : 6),
           (args.nbi == NBI0 ? "incrementing" : "decrementing"));
    retval = nbidma_configure(nfp_cpp, args.nbi, args.nislands);

    nfp_device_close(nfp);
    nfp_cpp_free(nfp_cpp);

    printf("done\n");

    return retval;
}
