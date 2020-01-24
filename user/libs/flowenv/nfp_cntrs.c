/*
 * Copyright (C) 2012-2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          user/libs/flowenv/nfp_cntrs.c
 * @brief         User defined counters support.
 */
#include <stdlib.h>
#include <errno.h>
#include <nfp_nffw.h>

#include "nfp_cntrs.h"

int
nfp_cntrs_64b_read(struct nfp_device *dev, const char *base_name,
                   unsigned int start_idx, unsigned int count,
                   unsigned long long int *buf, unsigned int do_clr)
{
    const struct nfp_rtsym *sym;
    ssize_t rlen = 0;
    ssize_t wlen = 0;
    char *w_buf;

    sym = nfp_rtsym_lookup(dev, base_name);
    if (!sym)
        return -1;

    /* count = 0 indicates read all counters starting at start_idx */
    if (count == 0) {
        if (start_idx * 8 >= nfp_rtsym_size(sym)) {
            errno = EINVAL;
            return -1;
        } else {
            rlen = nfp_rtsym_size(sym) - (start_idx * 8);
        }
    } else {
        if ((start_idx + count) * 8 > nfp_rtsym_size(sym)) {
            errno = EINVAL;
            return -1;
        } else {
            rlen = count * 8;
        }
    }
    rlen = nfp_rtsym_read(dev, sym, buf, rlen, start_idx * 8);
    if (rlen < 0)
        return -1;

    if (do_clr) {
        wlen = rlen;
        w_buf = malloc(wlen);
        if (w_buf == NULL)
            return -1;

        memset(w_buf, 0, wlen);
        wlen = nfp_rtsym_write(dev, sym, w_buf, wlen, start_idx * 8);
        if (wlen < 0) {
            free(w_buf);
            return -1;
        }
        free(w_buf);
    }
    return rlen / 8;
}

int
nfp_cntrs_64b_clr(struct nfp_device *dev, const char *base_name,
                  unsigned int start_idx, unsigned int count)
{
    const struct nfp_rtsym *sym;
    ssize_t wlen = 0;
    char *w_buf;

    sym = nfp_rtsym_lookup(dev, base_name);
    if (!sym)
        return -1;

    /* count = 0 indicates clear all counters starting at start_idx */
    if (count == 0) {
        if (start_idx * 8 >= nfp_rtsym_size(sym)) {
            errno = EINVAL;
            return -1;
        } else {
            wlen = nfp_rtsym_size(sym) - (start_idx * 8);
        }
    } else {
        if ((start_idx + count) * 8 > nfp_rtsym_size(sym)) {
            errno = EINVAL;
            return -1;
        } else {
            wlen = count * 8;
        }
    }
    w_buf = malloc(wlen);
    if(w_buf == NULL)
        return -1;

    memset(w_buf, 0, wlen);
    wlen = nfp_rtsym_write(dev, sym, w_buf, wlen, start_idx * 8);
    if (wlen < 0) {
        free(w_buf);
        return -1;
    }
    free(w_buf);
    return wlen / 8;
}

int
nfp_cntrs_pkts_read(struct nfp_device *dev, const char *base_name,
                    unsigned int start_idx, unsigned int count,
                    struct pkts_bytes_cntr *buf, unsigned int do_clr)
{
    const struct nfp_rtsym *sym;
    ssize_t rlen = 0;
    ssize_t wlen = 0;
    unsigned long long int *raw_buf;
    int i;

    sym = nfp_rtsym_lookup(dev, base_name);
    if (!sym)
        return -1;

    /* count = 0 indicates read all counters starting at start_idx */
    if (count == 0) {
        if (start_idx * 8 >= nfp_rtsym_size(sym)) {
            errno = EINVAL;
            return -1;
        } else {
            rlen = nfp_rtsym_size(sym) - (start_idx * 8);
        }
    } else {
        if ((start_idx + count) * 8 > nfp_rtsym_size(sym)) {
            errno = EINVAL;
            return -1;
        } else {
            rlen = count * 8;
        }
    }

    raw_buf = malloc(rlen);
    if (raw_buf == NULL)
        return -1;

    rlen = nfp_rtsym_read(dev, sym, raw_buf, rlen, start_idx * 8);
    if (rlen < 0) {
        free(raw_buf);
        return -1;
    }
    for (i = 0; i < rlen/8; i++) {
        buf[i].packets = (unsigned int)(raw_buf[i] >> 35);
        buf[i].bytes = (raw_buf[i] & 0x7ffffffff);
    }
    if (do_clr) {
        wlen = rlen;
        memset(raw_buf, 0, wlen);
        wlen = nfp_rtsym_write(dev, sym, raw_buf, wlen, start_idx * 8);
        if (wlen < 0) {
            free(raw_buf);
            return -1;
        }
    }
    free(raw_buf);
    return rlen / 8;
}

int
nfp_cntrs_pkts_clr(struct nfp_device *dev, const char *base_name,
                   unsigned int start_idx, unsigned int count)
{
    return nfp_cntrs_64b_clr(dev, base_name, start_idx, count);
}
