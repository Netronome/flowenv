/**
 * Copyright (C) 2013-2015 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        rtsym.c
 * @brief       Dump runtime symbols in the current environment.
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

#include <nfp.h>

struct nfp_device *nfp;
struct nfp_cpp *nfp_cpp;
const struct nfp_rtsym *sym;

int main(int argc, char **argv)
{
    int idx;
    uint32_t val32[256];
    size_t rsize;

    nfp = nfp_device_open(0);
    if (!nfp) {
        fprintf(stderr, "error: nfp_device_open (%d) failed\n", 0);
        exit(EXIT_FAILURE);
    }

    if (argc == 1)
    {
        for (idx = 0; idx < nfp_rtsym_count(nfp); idx++)
        {
            sym = nfp_rtsym_get(nfp, idx);
            printf("Symbol %d: %s (%d)\n", idx, sym->name, sym->target);
        }
    }
    else
    {
        sym = nfp_rtsym_lookup(nfp, argv[1]);
        if (!sym)
        {
            printf("Symbol not found\n");
            return 1;
        }
        printf("Name: %s\n", sym->name);
        printf("Addr: 0x%llx\n", (long long)sym->addr);
        printf("Size: 0x%llx\n", (long long)sym->size);
        printf("Domain: 0x%x\n", sym->domain);
        rsize = sym->size;
        if (rsize > sizeof(val32))
            rsize = sizeof(val32);
        if (nfp_rtsym_read(nfp, sym, val32, rsize, 0) != rsize) {
            printf("0x%llx: error\n", (long long)sym->addr);
        } else {
            if (rsize > 64)
                rsize = 64;
            for (idx = 0; idx < rsize/4; idx++)
                printf("0x%llx: 0x%08x\n", (long long)sym->addr + (idx * 4),
                    val32[idx]);
        }
    }

    nfp_device_close(nfp);

    return 0;
}

