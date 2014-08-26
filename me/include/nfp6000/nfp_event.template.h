/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          nfp6000/nfp_event.h
 * @brief         NFP6000 EventManager CSR definitions
 */

#ifndef _NFP6000__NFP_EVENT_H_
#define _NFP6000__NFP_EVENT_H_

pyexec<set_output_mode("nfp")>

/*
 * Event bus provider numbers
 */
#define NFP_EVENT_PROVIDER_INDEX(_ind)          ((_ind) & 3)
#define NFP_EVENT_PROVIDER_INDEX_of(_pvdr)      ((_pvdr) & 3)
#define NFP_EVENT_PROVIDER_INDEX_bf             0, 1, 0
#define   NFP_EVENT_PROVIDER_INDEX_CLS          0
#define   NFP_EVENT_PROVIDER_INDEX_CTM          1
#define   NFP_EVENT_PROVIDER_INDEX_ARM          2
#define   NFP_EVENT_PROVIDER_INDEX_PCIE         2
#define   NFP_EVENT_PROVIDER_INDEX_CRYPTO       2
#define   NFP_EVENT_PROVIDER_INDEX_ILA          2
#define   NFP_EVENT_PROVIDER_INDEX_ARM_PER      3
#define   NFP_EVENT_PROVIDER_INDEX_NBI          0
#define   NFP_EVENT_PROVIDER_INDEX_MAC          1
#define   NFP_EVENT_PROVIDER_INDEX_EMU          0
#define   NFP_EVENT_PROVIDER_INDEX_IMU          0
#define NFP_EVENT_PROVIDER_ISL(_isl)            (((_isl) & 0x3f) << 2)
#define NFP_EVENT_PROVIDER_ISL_of(_pvdr)        (((_pvdr) >> 2) & 0x3f)
#define NFP_EVENT_PROVIDER_ISL_bf               0, 7, 2
#define NFP_EVENT_PROVIDER_NUM(_isl, _pvdr)     (NFP_EVENT_PROVIDER_ISL(_isl) | \
                                                 NFP_EVENT_PROVIDER_INDEX(_pvdr))

/*
 * Event data as seen on the event bus
 */
#define NFP_EVENT_TYPE(_type)                   ((_type) & 0xf)
#define NFP_EVENT_TYPE_of(_ev)                  ((_ev) & 0xf)
#define NFP_EVENT_TYPE_bf                       0, 3, 0
#define   NFP_EVENT_TYPE_FIFO_NOT_EMPTY         0
#define   NFP_EVENT_TYPE_FIFO_NOT_FULL          1
#define   NFP_EVENT_TYPE_FIFO_ABOVE_WM          2
#define   NFP_EVENT_TYPE_STATS_FULL_WRAP        2
#define   NFP_EVENT_TYPE_FIFO_BELOW_WM          3
#define   NFP_EVENT_TYPE_STATS_HALFWAY          3
#define   NFP_EVENT_TYPE_STATUS_CHANGED         4
#define   NFP_EVENT_TYPE_VALUE_UPDATED          5
#define   NFP_EVENT_TYPE_STATUS_COMPL           6
#define   NFP_EVENT_TYPE_FIFO_UNDERFLOW         8
#define   NFP_EVENT_TYPE_FIFO_OVERFLOW          9
#define   NFP_EVENT_TYPE_ECC_SINGLE_CORRECTION  10
#define   NFP_EVENT_TYPE_ECC_MULTI_ERROR        11
#define   NFP_EVENT_TYPE_ECC_SINGLE_ERROR       12
#define   NFP_EVENT_TYPE_STATS_SYSOP_COMPL      13
#define   NFP_EVENT_TYPE_RESERVED               14
#define   NFP_EVENT_TYPE_GLOBAL_FILTERS_OVFLOW  15
#define NFP_EVENT_SOURCE(_src)                  (((_src) & 0xfff) << 4)
#define NFP_EVENT_SOURCE_of(_ev)                (((_ev) >> 4) & 0xfff)
#define NFP_EVENT_SOURCE_bf                     0, 15, 4
#define NFP_EVENT_PROVIDER(_pvdr)                (((_pvdr) & 0xff) << 16)
#define NFP_EVENT_PROVIDER_of(_ev)              (((_ev) >> 16) & 0xff)
#define NFP_EVENT_PROVIDER_bf                   0, 23, 16
#define NFP_EVENT_MATCH(_pvdr, _src, _type)     (NFP_EVENT_PROVIDER(_pvdr) | \
                                                NFP_EVENT_SOURCE(_src) | \
                                                NFP_EVENT_TYPE(_type))

/*
 * EventManager CSRs
 */
pyexec<dump_map(EventManagerMap(altname="EM"), docs=True)>

pyexec<dump_map(EventFilterMap(altname="EM_FILTER"), docs=True)>

/*
 * EventManager register structures
 */
#if defined(__NFP_LANG_MICROC)

struct nfp_event_match {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int reserved:8;
            unsigned int provider:8;
            unsigned int source:12;
            unsigned int type:4;
#           else
            unsigned int type:4;
            unsigned int source:12;
            unsigned int provider:8;
            unsigned int reserved:8;
#           endif
        };
        unsigned int __raw;
    };
};

pyexec<dump_map_structs(EventManagerMap(altname="EM"))>

pyexec<dump_map_structs(EventFilterMap(altname="EM_FILTER"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_EVENT_H_ */
