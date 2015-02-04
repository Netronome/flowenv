/**
 * Copyright (C) 2013-2015 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        nfp_cls.c
 * @brief       Set cluster target memory either from a file or from a static
 *              value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include <nfp.h>


const char *progname = NULL;


/* See the System Interconnectivity section of the DB */
#define ARM_ISLAND              1
#define PCIE_ISLAND_BASE        4
#define ME_ISLAND_BASE          32
#define ILA_ISLAND_BASE         48


void usage(const char *err)
{
    if (err)
        fprintf(stderr, "%s\n", err);
    fprintf(stderr, "Usage\n");
    fprintf(stderr, "\t%s ISLAND ADDR LENGTH\n", progname);
    fprintf(stderr, "\t%s ISLAND ADDR VAL64 LENGTH\n", progname);
    fprintf(stderr, "\t%s ISLAND ADDR FILENAME [MAXLEN]\n", progname);
    fprintf(stderr, "Where\n");
    fprintf(stderr, "\tISLAND is meiX for some integer X\n");
    fprintf(stderr, "\tor ISLAND is pcieX for some integer X\n");
    fprintf(stderr, "\tor ISLAND is arm0\n");
    fprintf(stderr, "\tor ISLAND is ilaX for some integer X\n");
    exit(1);
}


int get_island(const char *s)
{
    int island;
    int menum;

    if (strncmp(s, "mei", 3) == 0) {
        if (sscanf(s, "mei%d", &island) < 1)
            usage("Invalid island specification");
        island += ME_ISLAND_BASE;
    } else if (strncmp(s, "pcie", 4) == 0) {
        if (sscanf(s, "pcie%d", &island) < 1)
            usage("Invalid island specification");
        island += PCIE_ISLAND_BASE;
    } else if (strcmp(s, "arm0") == 0) {
        island = ARM_ISLAND;
    } else if (strncmp(s, "ila", 3) == 0) {
        if (sscanf(s, "ila%d", &island) < 1)
            usage("Invalid island specification");
        island += ILA_ISLAND_BASE;
    } else {
        usage("Invalid Island specification");
    }

    return island;
}


static int cls_dump(struct nfp_device *dev, int island, unsigned long long addr,
                    long long length)
{
    ssize_t rv;
    uint32_t data[2];
    long long nw = 0;

    for ( ; length > 0; addr += 8, length -= 8, nw += 2) {
        if (nw % 4 == 0) {
            if (nw != 0)
                printf("\n");
            printf("%08llx:", addr);
        }

        rv = nfp_cls_read(dev, island, data, 8, addr);
        if (rv != 8) {
            perror("cls_dump() -- nfp_cls_read()");
            return -1;
        }

        printf("  %08x", data[0]);
        if (length > 4)
            printf("  %08x", data[1]);
    }

    printf("\n");

    return 0;
}


static int cls_memset(struct nfp_device *dev, int island,
                      unsigned long long addr, unsigned long long value,
                      long long length)
{
    ssize_t rv;
    uint32_t data[2];

    if (length % 8 != 0)
        usage("Length must be a multiple of 8");

    /* LWBE UGH! */
    data[0] = value & 0xFFFFFFFF;
    data[1] = (value >> 32) & 0xFFFFFFFF;

    for (; length > 0; length -= 8, addr += 8) {
        rv = nfp_cls_write(dev, island, data, 8, addr);
        if (rv != 8) {
            perror("cls_memset() -- nfp_cls_write()");
            return -1;
        }
    }

    return 0;
}


static int file_to_cls(struct nfp_device *dev, int island,
                       unsigned long long addr, FILE *fp, long long maxlen)
{
    size_t nr;
    ssize_t rv;
    uint32_t data[2];
    uint8_t *bp;

    for (nr = fread(data, 1, 8, fp) ; nr > 0 && maxlen > 0;
         addr += 8, maxlen -= 8, nr = fread(data, 1, 8, fp)) {
        if (nr == 8) {
            /* convert to LWBE */
            data[0] = ntohl(data[0]);
            data[1] = ntohl(data[1]);
        } else {
            fprintf(stderr, "File length is not a multiple of 8: padding");
            if (nr < 4) {
                bp = (uint8_t *)&data[0];
                bp += nr;
                while (nr < 4) *bp++ = 0;
                data[1] = 0;
            } else {
                data[0] = ntohl(data[0]);
                bp = (uint8_t *)&data[1];
                bp += nr;
                while (nr < 8) *bp++ = 0;
            }
        }

        rv = nfp_cls_write(dev, island, data, 8, addr);
        if (rv != 8) {
            perror("file_to_cls() -- nfp_cls_write()");
            return -1;
        }
    }

    return 0;
}


int main(int argc, char *argv[])
{
    int rv = 0;
    int island = 0;
    unsigned long long length;
    unsigned long long addr;
    unsigned long long value;
    struct nfp_device *dev;
    FILE *infile = NULL;

    progname = argv[0];

    if (argc != 4 && argc != 5)
        usage(NULL);

    island = get_island(argv[1]);

    addr = strtoull(argv[2], NULL, 0);

    dev = nfp_device_open(0);
    if (dev == NULL) {
        perror("nfp_device_open()");
        return -1;
    }

    if (isdigit(argv[3][0])) {
        if (argc == 4) {
            length = strtoll(argv[3], NULL, 0);
            rv = cls_dump(dev, island, addr, length);
        } else {
            value = strtoull(argv[3], NULL, 0);
            length = strtoll(argv[4], NULL, 0);
            rv = cls_memset(dev, island, addr, value, length);
        }
    } else {
        if (strcmp(argv[3], "-") == 0) {
            infile = stdin;
        } else {
            infile = fopen(argv[3], "r");
            if (infile == NULL) {
                perror("fopen()");
                return -1;
            }
        }
        if (argc == 5)
            length = strtoll(argv[4], NULL, 0);
        else
            length = (unsigned long long)-1;
        rv = file_to_cls(dev, island, addr, infile, length);
    }

    nfp_device_close(dev);
    return rv;
}
