/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_me_reset.c
 * @brief       Reset the ME to a reasonable initial state.
 */

#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include <nfp.h>
#include <nfp_resid.h>
#include <nfp_sal.h>
#include <read_mecsr.h>

const char *progname = NULL;


void usage(const char *estr)
{
    if (estr)
        fprintf(stderr, "%s\n", estr);
    fprintf(stderr, "usage: %s ISLAND.MENUM\n", progname);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, "\tISLAND is meiX for some integer X\n");
    fprintf(stderr, "\tor ISLAND is pcieX for some integer X\n");
    fprintf(stderr, "\tor ISLAND is arm0\n");
    fprintf(stderr, "\tor ISLAND is ilaX for some integer X\n");
    fprintf(stderr, "\tMENUM is meY for some integer Y\n");

    exit(1);
}


/* See the System Interconnectivity section of the DB */
#define ARM_ISLAND              1
#define PCIE_ISLAND_BASE        4
#define ME_ISLAND_BASE          32
#define ILA_ISLAND_BASE         48


uint32_t Nfp_mecsr_read(struct nfp_device *dev, int meid, int ctx,
                        unsigned int addr)
{
    uint32_t val;
    int rv = nfp_mecsr_read(dev, meid, ctx, addr, &val);
    if (rv < 0) {
        perror("nfp_mecsr_read()");
        exit(1);
    }
    return val;
}


int get_meid(const char *s)
{
    int island;
    int menum;

    if (strncmp(s, "mei", 3) == 0) {
        if (sscanf(s, "mei%d.me%d", &island, &menum) < 2)
            usage("Invalid ME specification");
        island += ME_ISLAND_BASE;
    } else if (strncmp(s, "pcie", 4) == 0) {
        if (sscanf(s, "pcie%d.me%d", &island, &menum) < 2)
            usage("Invalid ME specification");
        island += PCIE_ISLAND_BASE;
    } else if (strncmp(s, "arm0", 4) == 0) {
        if (sscanf(s, "arm0.me%d", &menum) < 1)
            usage("Invalid ME specification");
        island = ARM_ISLAND;
    } else if (strncmp(s, "ila", 3) == 0) {
        if (sscanf(s, "ila%d.me%d", &island, &menum) < 2)
            usage("Invalid ME specification");
        island += ILA_ISLAND_BASE;
    } else {
        usage("Invalid Island specification");
    }

    return NFP6000_MEID(island, menum);
}


int main(int argc, char *argv[])
{
    int meid;
    int rv;
    struct nfp_device *dev;
    int i;
    uint32_t val;

    progname = argv[0];

    if (argc != 2)
        usage(NULL);

    meid = get_meid(argv[1]);

    dev = nfp_device_open(0);
    if (dev == NULL) {
        perror("nfp_device_open()");
        exit(1);
    }

    val = Nfp_mecsr_read(dev, meid, -1, NFP_ME_MAILBOX0);
    printf("Mailbox0 = 0x%08x  (%u)\n", (unsigned)val, (unsigned)val);
    val = Nfp_mecsr_read(dev, meid, -1, NFP_ME_MAILBOX1);
    printf("Mailbox1 = 0x%08x  (%u)\n", (unsigned)val, (unsigned)val);
    val = Nfp_mecsr_read(dev, meid, -1, NFP_ME_MAILBOX2);
    printf("Mailbox2 = 0x%08x  (%u)\n", (unsigned)val, (unsigned)val);
    val = Nfp_mecsr_read(dev, meid, -1, NFP_ME_MAILBOX3);
    printf("Mailbox3 = 0x%08x  (%u)\n", (unsigned)val, (unsigned)val);

    nfp_device_close(dev);
    return 0;
}
