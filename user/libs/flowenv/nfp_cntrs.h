/*
 * Copyright (C) 2012-2015,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          user/libs/flowenv/nfp_cntrs.h
 * @brief         User defined counters support.
 */
#ifndef _LIBS_FLOWENV__NFP_CNTRS_H_
#define _LIBS_FLOWENV__NFP_CNTRS_H_

#include <nfp.h>

struct pkts_bytes_cntr {
    unsigned int packets;
    unsigned long long bytes;
};

/**
 * Read 64bits counters.
 *
 * @param dev       [in] The nfp device to read from.
 * @param base_name [in] The rt-sym of the counters memory.
 * @param start_idx [in] The first counter index to start reading from.
 * @param count     [in] The number of counters to read, 0 indicates all from
 *                       start_idx.
 * @param buf       [in] The buffer to read the counters into (user allocated).
 * @param do_clr    [in] Perform clear after read flag.
 *
 * @return On success - the number of counters read, -1 otherwise.
 *
 * The user allocates buf must be big enough to hold all the required counters.
 */
int nfp_cntrs_64b_read(struct nfp_device *dev, const char *base_name,
                       unsigned int start_idx, unsigned int count,
                       unsigned long long int *buf, unsigned int do_clr);

/**
 * Clear 64bits counters.
 *
 * @param dev       [in] The nfp device.
 * @param base_name [in] The rt-sym of the counters memory.
 * @param start_idx [in] The first counter index to start clearing from.
 * @param count     [in] The number of counters to clear, 0 indicates all from
 *                       start_idx.
 *
 * @return On success - the number of counters cleared, -1 otherwise.
 */
int nfp_cntrs_64b_clr(struct nfp_device *dev, const char *base_name,
                      unsigned int start_idx, unsigned int count);

/**
 * Read Packets and Bytes counters.
 *
 * @param dev       [in] The nfp device to read from.
 * @param base_name [in] The rt-sym of the counters memory.
 * @param start_idx [in] The first counter index to start reading from.
 * @param count     [in] The number of counters to read, 0 indicates all from
 *                       start_idx.
 * @param buf       [in] The buffer to read the counters into (user allocated).
 * @param do_clr    [in] Perform clear after read flag.
 *
 * @return On success - the number of counters read, -1 otherwise.
 *
 * The user allocates buf must be big enough to hold all the required counters.
 */
int nfp_cntrs_pkts_read(struct nfp_device *dev, const char *base_name,
                        unsigned int start_idx, unsigned int count,
                        struct pkts_bytes_cntr *buf, unsigned int do_clr);

/**
 * Clear Packets and Bytes counters.
 *
 * @param dev       [in] The nfp device.
 * @param base_name [in] The rt-sym of the counters memory.
 * @param start_idx [in] The first counter index to start clearing from.
 * @param count     [in] The number of counters to clear, 0 indicates all from
 *                       start_idx.
 *
 * @return On success - the number of counters cleared, -1 otherwise.
 */
int nfp_cntrs_pkts_clr(struct nfp_device *dev, const char *base_name,
                       unsigned int start_idx, unsigned int count);

#endif /* !_LIBS_FLOWENV__NFP_CNTRS_H_ */