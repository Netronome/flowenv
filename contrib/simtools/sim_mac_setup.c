/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_mac_setup.c
 * @brief       Set up a MAC in the NFP simulator.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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



/* MAC address defines */

#define MACCSR_MACTDMRATECREDITINIT(nbi)        (0x004000a8 + ((nbi) << 24))
#define MACCSR_MACSYSSUPCTRL(nbi)               (0x00400014 + ((nbi) << 24))
#define MACCSR_MACSERDESEN(nbi)                 (0x00400010 + ((nbi) << 24))
#define MACCSR_MACBLKRESET(nbi)                 (0x00400000 + ((nbi) << 24))
#define MACCSR_MACHYD0BLKRESET(nbi)             (0x00400004 + ((nbi) << 24))
#define MACCSR_MACHYD1BLKRESET(nbi)             (0x00400008 + ((nbi) << 24))
#define MACCSR_MACTDM0CYCLEWORD3100(nbi)        (0x00400030 + ((nbi) << 24))
#define MACCSR_MACTDM0CYCLEWORD4732(nbi)        (0x00400034 + ((nbi) << 24))
#define MACCSR_MACTDM1CYCLEWORD3100(nbi)        (0x00400038 + ((nbi) << 24))
#define MACCSR_MACTDM1CYCLEWORD4732(nbi)        (0x0040003c + ((nbi) << 24))
#define MACCSR_MACTDM0MODE0900(nbi)             (0x00400040 + ((nbi) << 24))
#define MACCSR_MACTDM0MODE1110CRCEN(nbi)        (0x00400044 + ((nbi) << 24))
#define MACCSR_MACTDM1MODE1110CRCEN(nbi)        (0x0040004c + ((nbi) << 24))
#define MACCSR_MACEGBUFPOOLCNT(nbi)             (0x00400098 + ((nbi) << 24))
#define MACCSR_MACIGBUFPOOLCNT(nbi)             (0x004000a0 + ((nbi) << 24))
#define MACCSR_MACPORT2TO0CHANASSIGN(nbi)       (0x00400050 + ((nbi) << 24))
#define MACCSR_EGCMDPREPENDEN0LO(nbi)           (0x00400200 + ((nbi) << 24))
#define MACCSR_EGCMDPREPENDEN0HI(nbi)           (0x00400204 + ((nbi) << 24))
#define MACCSR_EGCMDPREPENDEN1LO(nbi)           (0x00400208 + ((nbi) << 24))
#define MACCSR_EGCMDPREPENDEN1HI(nbi)           (0x0040020c + ((nbi) << 24))
#define MACCSR_MACPORTCHANASSIGN(nbi,x)        ((0x00400050 + ((nbi) << 24)) + (x)*4)
#define MACCSR_MACPCPREMAP0(nbi)                (0x00400680 + ((nbi) << 24))
#define MACCSR_IGDQTDMMEMORYRW(nbi)             (0x004007d8 + ((nbi) << 24))
#define MACCSR_MACEGPORTCHANASSIGN(nbi,x)       ((0x00400240 + ((nbi) << 24)) + (x)*4)
#define MACCSR_ETHACTCTLSEG(nbi,hy)  (0x00443000 + ((nbi) << 24) + (hy)*0x20000)
#define MACCSR_ETHMODECTLSEG(nbi,hy) (0x00443004 + ((nbi) << 24) + (hy)*0x20000)

struct tdm_mem_cfg{
    int start; int finish; int arb_enable; uint32_t dwrr_weight;
};

struct mac_info{
    int nbi[2];
    int enabled[2];
    uint32_t eg_bufpool_count[2];
    uint32_t in_bufpool_count[2];
    int ready[2];
};

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

void mac_tdm_mem_configure(struct nfp_device *nfp, struct nfp_cpp *nfp_cpp, int nbi_island, struct tdm_mem_cfg* cfg, int debug_print)
{
    int i, j;
    uint32_t val;
    for (i = cfg->start; i <= cfg->finish; i++) {
        val = (i << 24) | (1 << 20) | (cfg->arb_enable << 15) | (cfg->dwrr_weight << 0);
        xpb_writel(nfp_cpp, MACCSR_IGDQTDMMEMORYRW(nbi_island), val);
        if (debug_print)
            printf("%d %08x = %08x\n", i, MACCSR_IGDQTDMMEMORYRW(nbi_island), val);
        /* step until the rdy bit (20) clears */
        for (j = 0; j < 10; j++) {
            step_sim(nfp, 3);
            nfp_xpb_readl(nfp_cpp, MACCSR_IGDQTDMMEMORYRW(nbi_island), &val);
            if ((val & (1 << 20)) == 0) {
                break;
            }
        }
    }
}


int mac_configure(struct nfp_device *nfp, struct nfp_cpp *nfp_cpp, struct mac_info* mac_info)
{

    //uint32_t val;
    uint64_t steps_start, steps_end;
    int i,j;
    struct tdm_mem_cfg tdm_mem_config;



    steps_start = nfp_sal_cycle_count(nfp);

    for(j=0;j<2;j++)
    {
        if (mac_info->enabled[j]) {
            printf("NBI %d (island %d) MAC interface setup\n", j,mac_info->nbi[j]);
            /* From RV's harrier_core_cluster_mac_island_cfg */
            xpb_writel(nfp_cpp, MACCSR_MACTDMRATECREDITINIT(mac_info->nbi[j]),
                    0xff190303);
            xpb_writel(nfp_cpp, MACCSR_MACSYSSUPCTRL(mac_info->nbi[j]), 0x10200);
            xpb_writel(nfp_cpp, MACCSR_MACSERDESEN(mac_info->nbi[j]), 0xffffff);
            xpb_writel(nfp_cpp, MACCSR_MACBLKRESET(mac_info->nbi[j]), 0x3ffff7);
            step_sim(nfp, 10);
            xpb_writel(nfp_cpp, MACCSR_MACBLKRESET(mac_info->nbi[j]), 0x3ffc17);
            step_sim(nfp, 10);
            xpb_writel(nfp_cpp, MACCSR_MACBLKRESET(mac_info->nbi[j]), 0x3ffc13);
            step_sim(nfp, 10);
            xpb_writel(nfp_cpp, MACCSR_MACBLKRESET(mac_info->nbi[j]), 0x3ff13);
            step_sim(nfp, 10);
            xpb_writel(nfp_cpp, MACCSR_MACHYD0BLKRESET(mac_info->nbi[j]), 0xfff0fffd);
            xpb_writel(nfp_cpp, MACCSR_MACSYSSUPCTRL(mac_info->nbi[j]), 0x10201);
            xpb_writel(nfp_cpp, MACCSR_MACTDM0CYCLEWORD3100(mac_info->nbi[j]),0x00);
            xpb_writel(nfp_cpp, MACCSR_MACTDM0CYCLEWORD4732(mac_info->nbi[j]),0xdd00);
            xpb_writel(nfp_cpp, MACCSR_MACTDM1CYCLEWORD3100(mac_info->nbi[j]),0xdddddddd);
            xpb_writel(nfp_cpp, MACCSR_MACTDM1CYCLEWORD4732(mac_info->nbi[j]),0xdddd);
            xpb_writel(nfp_cpp, MACCSR_MACTDM0MODE0900(mac_info->nbi[j]), 0x4);
            xpb_writel(nfp_cpp, MACCSR_MACTDM0MODE1110CRCEN(mac_info->nbi[j]),0xfff0004);
            xpb_writel(nfp_cpp, MACCSR_MACTDM1MODE1110CRCEN(mac_info->nbi[j]),0xfff0004);
            xpb_writel(nfp_cpp, MACCSR_EGCMDPREPENDEN0LO(mac_info->nbi[j]), 0x0);
            xpb_writel(nfp_cpp, MACCSR_EGCMDPREPENDEN0HI(mac_info->nbi[j]), 0x0);
            xpb_writel(nfp_cpp, MACCSR_EGCMDPREPENDEN1LO(mac_info->nbi[j]), 0x0);
            xpb_writel(nfp_cpp, MACCSR_EGCMDPREPENDEN1HI(mac_info->nbi[j]), 0x0);
            xpb_writel(nfp_cpp, MACCSR_MACPCPREMAP0(mac_info->nbi[j]), 0x0);
            for (i = 0; i < 2; i++) {
                xpb_writel(nfp_cpp, MACCSR_ETHACTCTLSEG(mac_info->nbi[j], i), 0xc01);
                xpb_writel(nfp_cpp, MACCSR_ETHMODECTLSEG(mac_info->nbi[j], i), 0x2);
            }
            xpb_writel(nfp_cpp, MACCSR_MACHYD0BLKRESET(mac_info->nbi[j]), 0x0); //start traffic

            /* channel assignment setup for all 24 ports */
            i = 0; /* port 0-11*/
            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i),
                    0x01002200);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i),
                    0x01002200);

            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i+1),
                    0x02408018);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i+1),
                    0x02408018);

            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i+2),
                    0x0300b028);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i+2),
                    0x0300b028);

            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i+3),
                    0x03c0e034);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i+3),
                    0x03c0e034);

            i = 4; /*port 12-24*/
            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i),
                    0x01002200);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i),
                    0x01002200);

            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i+1),
                    0x02408018);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i+1),
                    0x02408018);

            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i+2),
                    0x0300b028);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i+2),
                    0x0300b028);

            xpb_writel(nfp_cpp, MACCSR_MACPORTCHANASSIGN(mac_info->nbi[j], i+3),
                    0x03c0e034);
            xpb_writel(nfp_cpp, MACCSR_MACEGPORTCHANASSIGN(mac_info->nbi[j], i+3),
                    0x03c0e034);

            /* setup TDM to assign more slots to port 0 */

            printf("setting up port TDM\n");
            tdm_mem_config.start = 0;
            tdm_mem_config.finish = 8;
            tdm_mem_config.dwrr_weight = 2560;
            tdm_mem_config.arb_enable = 1;
            mac_tdm_mem_configure(nfp, nfp_cpp, mac_info->nbi[j], &tdm_mem_config, 0);

            tdm_mem_config.start = 9;
            tdm_mem_config.finish = 11;
            tdm_mem_config.dwrr_weight = 2560;
            tdm_mem_config.arb_enable = 0;
            mac_tdm_mem_configure(nfp, nfp_cpp, mac_info->nbi[j], &tdm_mem_config, 0);

            tdm_mem_config.start = 12;
            tdm_mem_config.finish = 20;
            tdm_mem_config.dwrr_weight = 2560;
            tdm_mem_config.arb_enable = 1;
            mac_tdm_mem_configure(nfp, nfp_cpp, mac_info->nbi[j], &tdm_mem_config, 0);

            tdm_mem_config.start = 21;
            tdm_mem_config.finish = 25;
            tdm_mem_config.dwrr_weight = 2560;
            tdm_mem_config.arb_enable = 0;
            mac_tdm_mem_configure(nfp, nfp_cpp, mac_info->nbi[j], &tdm_mem_config, 0);

            nfp_sal_tweak(nfp, NFP_SAL_TWEAK_MACRESET, mac_info->nbi[j] - NBI0_ISLAND);
        }
    }


    printf("waiting for the MAC(s) to become ready (this may take a while)\n");


    for (i = 0; i < 512 / 4; i++) {
        step_sim(nfp, 128 / 4);
        int all_ready = 1;
        for (j = 0; j < 2; j++) {
            if (mac_info->enabled[j]) {
                nfp_xpb_readl(nfp_cpp, MACCSR_MACEGBUFPOOLCNT(mac_info->nbi[j]),
                        &mac_info->eg_bufpool_count[j]);
                nfp_xpb_readl(nfp_cpp, MACCSR_MACIGBUFPOOLCNT(mac_info->nbi[j]),
                        &mac_info->in_bufpool_count[j]);
                if ((mac_info->eg_bufpool_count[j] & (1 << 31))||(mac_info->in_bufpool_count[j] & (1 << 31))) {
                    printf("MAC %d ready\n",j);
                    mac_info->ready[j] = 1;
                }
            }
        }
        for (j = 0; j < 2; j++) {
            if (mac_info->enabled[j]) {
                if (mac_info->ready[j])
                    all_ready = 1;
                else
                    all_ready = 0;
            }
        }
        if (all_ready) {
            printf("all MAC(s) ready\n");
            break;
        }
    }

    steps_end = nfp_sal_cycle_count(nfp);
    printf("MAC setup took %ld ME clock cycles\n", steps_end - steps_start);

    nfp_device_close(nfp);
    nfp_cpp_free(nfp_cpp);

    return 0;
}

void usage(char *argv[])
{
    fprintf(stdout,
            "usage:%s <NBI#> ...  Perform MAC setup. <NBI#> can only be 0 or 1\n"
            "If no or incorrect arguments are given, NBI 0 will be setup\n",
            argv[0]);
}


static void parse_options(struct mac_info* usr_args, int argc,
        char *argv[])
{

    int nbi,i;
    usr_args->enabled[0] = 0;
    usr_args->enabled[0] = 0;
    usr_args->nbi[0] = NBI0_ISLAND;
    usr_args->nbi[1] = NBI1_ISLAND;
    usr_args->ready[0] = 0;
    usr_args->ready[1] = 0;

    if ((argc < 2) || (argc > 3)) {
        usage(argv);
        usr_args->enabled[0] = 1;
    } else {
        for (i = 1; i < argc; i++) {
            nbi = atoi(argv[i]);
            if (nbi > NBI1) {
                usage(argv);
                exit(1);
            }
            usr_args->enabled[nbi] = 1;
        }
    }

}

int main(int argc, char **argv)
{
    struct nfp_device *nfp;
    struct nfp_cpp *nfp_cpp;
    struct mac_info mac_info;

    uint32_t retval;


    NS_LOG_SET_LEVEL(NS_LOG_LVL_INFO);
    parse_options(&mac_info,argc,argv);

    printf("opening nfp_device\n");
    nfp = nfp_device_open(0);
    if (!nfp) {
        fprintf(stderr, "error: nfp_device_open failed\n");
        return -1;
    }

    nfp_sal_subs_simevent_all(nfp, &event_handler);

    printf("opening nfp_cpp\n");
    nfp_cpp = nfp_cpp_from_device_id(0);
    if (!nfp_cpp) {
        fprintf(stderr, "error: nfp_cpp_from_device_id failed\n");
        return -1;
   }

    step_sim(nfp, 200);

    retval = mac_configure(nfp, nfp_cpp, &mac_info);

    printf("done\n");

    return retval;
}
