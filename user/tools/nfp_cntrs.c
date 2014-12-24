/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file          user/tools/nfp_cntrs.c
 * @brief         A sample tool/application demonstrating the nfp_cntrs API.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <ctype.h>
#include <errno.h>

#include "nfp_cntrs.h"

#define MAX_64BIT_COUNTERS 32*1024
#define MAX_PCKT_COUNTERS  32*1024

struct parameters
{
    int nfp_num;
    int do_clear;
    int is_pkt_counter;
    int len;
    int no_zero;
};

void usage(void)
{
    printf("nfp_cntrs [options] [symbol:counter-index]\n"
           "options:\n"
           " -n, --nfp <nfp num>  Select which NFP to access (default 0)\n"
           " -c, --clear   Clear counters after reading\n"
           " -p, --packets Print a packets and bytes counter (default 64bits)\n"
           " -z, --zero    Print only non zero counters\n"
           " -l <num>, --len <num> The number of counters to read from base\n"
           "                       (must be >= 1, default all)\n\n");
}

static const struct option g_opt[] = {
    {"help",    no_argument,        NULL, 'h'},
    {"nfp",     required_argument , NULL, 'n'},
    {"clear",   no_argument,        NULL, 'c'},
    {"packets", no_argument,        NULL, 'p'},
    {"len",     required_argument , NULL, 'l'},
    {"zero",    no_argument,        NULL, 'z'},
    {NULL,      0, 0, '\0'}
};

static const char *g_optstr = "hcn:pl:z";

void parse_params(int argc, char *argv[], struct parameters *p)
{
    char c;

    if (argc == 1) {
        usage();
        exit(EXIT_FAILURE);
    }

    while ((c = getopt_long(argc, argv, g_optstr, g_opt, NULL)) != -1) {
        switch (c) {
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
            break;
        case 'c':
            p->do_clear = 1;
            break;
        case 'n':
            p->nfp_num = atoi(optarg);
            break;
        case 'p':
            p->is_pkt_counter = 1;
            break;
        case 'l':
            p->len = atoi(optarg);
            if (p->len < 1) {
                fprintf(stderr, "Length must be >= 1\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'z':
            p->no_zero = 1;
            break;
        default:
            fprintf(stderr, "Unknown option: '%c'\n", c);
            usage();
            exit(EXIT_FAILURE);
            break;
        }
    }
}

int main (int argc, char *argv[])
{
    struct parameters p;
    char *symstr = NULL, *offstr;
    unsigned int offset = 0;
    struct nfp_device *nfp;
    unsigned long long counters64[MAX_64BIT_COUNTERS];
    struct pkts_bytes_cntr countersPkts[MAX_PCKT_COUNTERS];
    int i;
    int num_cntrs = 0;

    memset(&p, 0, sizeof(p));
    parse_params(argc, argv, &p);

    if (optind == argc) {
        fprintf(stderr, "error: counters symbol must be provided\n");
        usage();
        exit(EXIT_FAILURE);
    }

    /* Get target offset */
    symstr = argv[optind++];
    offstr = strchr(symstr, ':');
    if (!offstr) {
        offstr = "0";
    } else {
        offstr[0] = 0;
        offstr++;
    }
    offset = atoi(offstr);

    nfp = nfp_device_open(p.nfp_num);
    if (!nfp) {
        fprintf(stderr, "Failed to open NFP device %d\n", p.nfp_num);
        exit(EXIT_FAILURE);
    }
    if (p.is_pkt_counter) {
        /* We can call this function using p.do_clear, we avoid this to
           practice the call to nfp_cntrs_pkts_cntr_clr later */
        num_cntrs = nfp_cntrs_pkts_read(nfp, symstr, offset,
                                        p.len, countersPkts, 0);
        if (num_cntrs < 0) {
            fprintf(stderr,
                    "Failed to read Packets and Bytes counters from device %d: "
                    "%s\n", p.nfp_num, strerror(errno));
            nfp_device_close(nfp);
            exit(EXIT_FAILURE);
        } else {
            for (i = 0; i < num_cntrs; i++) {
                if (countersPkts[i].packets != 0 ||
                    countersPkts[i].bytes != 0 || p.no_zero == 0)
                    printf("%s[%3d] : Packets %10u, Bytes %12llu\n", symstr,
                           i+offset, countersPkts[i].packets,
                           countersPkts[i].bytes);
            }
        }
        /* Practice the counters clear api */
        if (p.do_clear)
            nfp_cntrs_pkts_clr(nfp, symstr, offset, p.len);
    } else {

        printf("sizeof counters64 = %d\n", (int)sizeof(counters64));
        num_cntrs = nfp_cntrs_64b_read(nfp, symstr, offset,
                                       p.len, counters64, 0);
        if (num_cntrs < 0) {
            fprintf(stderr, "Failed to read 64bit counters from device %d: "
                    "%s\n", p.nfp_num, strerror(errno));
            nfp_device_close(nfp);
            exit(EXIT_FAILURE);
        } else {
            for (i = 0; i < num_cntrs; i ++)
                if (counters64[i] != 0 || p.no_zero == 0)
                    printf("%s[%3d] : %21llu\n", symstr, i+offset,
                            counters64[i]);
        }
        /* Practice the counters clear api */
        if (p.do_clear)
            nfp_cntrs_64b_clr(nfp, symstr, offset, p.len);
    }
    nfp_device_close(nfp);
    return EXIT_SUCCESS;
}
