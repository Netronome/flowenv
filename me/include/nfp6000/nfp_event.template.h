/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
#define   NFP_EVENT_PROVIDER_INDEX_EMU_PVDR1    0
#define   NFP_EVENT_PROVIDER_INDEX_EMU_PVDR2    1
#define   NFP_EVENT_PROVIDER_INDEX_IMU_LB       0
#define   NFP_EVENT_PROVIDER_INDEX_IMU_STATS    1
#define   NFP_EVENT_PROVIDER_INDEX_IMU_DCACHE   2
#define   NFP_EVENT_PROVIDER_INDEX_IMU          3
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
#define   NFP_EVENT_TYPE_DMA                    2
#define   NFP_EVENT_TYPE_PROCESS                3
#define   NFP_EVENT_TYPE_STATUS                 4
#define   NFP_EVENT_TYPE_STATS_HALF_WAY         5
#define   NFP_EVENT_TYPE_FIFO_UNDERFLOW         8
#define   NFP_EVENT_TYPE_FIFO_OVERFLOW          9
#define   NFP_EVENT_TYPE_ECC_SINGLE_CORRECTION  10
#define   NFP_EVENT_TYPE_ECC_MULTI_ERROR        11
#define   NFP_EVENT_TYPE_ECC_SINGLE_ERROR       12
#define   NFP_EVENT_TYPE_STATS_OVERFLOW         13
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
