/*
 * Copyright (C) 2014-2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file        blm_cfg.h
 * @brief
 */

#ifndef __NFP_BLM_CFG_H__
#define __NFP_BLM_CFG_H__


/*
 * This header file is shared between ASM and Micro-C code.
 */
#if defined(__NFP_LANG_ASM)
    #include <constants.uc>
#endif


/*
 * Micro-C code does not support pre-process string matching, so we
 * need to supply memory type definitions to be used by the Micro-C code.
 */
#define BLM_MEM_TYPE_EMEM               0
#define BLM_MEM_TYPE_EMEM_CACHE_UPPER   1

/* Determine the chip type in order to select appropriate default settings. */
#if defined(__NFP_LANG_ASM)
    #if (IS_NFPTYPE(__NFP6000))
        #define BLM_USE_NFP6XXX_DEFAULTS
    #elif (IS_NFPTYPE(__NFP3800))
        #define BLM_USE_NFP38XX_DEFAULTS
    #else
        #error "Unsupported chip type"
    #endif
#else
    #if defined(__NFP_IS_6XXX)
        #define BLM_USE_NFP6XXX_DEFAULTS
    #elif defined(__NFP_IS_38XX)
        #define BLM_USE_NFP38XX_DEFAULTS
    #else
        #error "Unsupported chip type"
    #endif
#endif


#ifdef BLM_CUSTOM_CONFIG
#include "blm_custom.h"
#endif

/**
 * Mask defining which BLQ's are active and serviced by BLM.
 * bits[3:0] = Ingress BLQ enable mask. '1' = Enable, '0' = disable
 * bits[7:4] = Egress  BLQ enable mask. '1' = Enable, '0' = disable
 */
#ifndef BLM_BLQ_ENABLE_MASK
    #define BLM_BLQ_ENABLE_MASK     0xff
#endif

/**
 * Mask defining which BLQ's are active dedicated to PCIe.
 * bits[3:0] = BLQ enable mask. '1' = Enable, '0' = disable
 */
#ifndef BLM_PCI_BLQ_ENABLE_MASK
    #define BLM_PCI_BLQ_ENABLE_MASK 0
#endif

#ifndef BLM_BLQ_NULL_RECYCLE_MASK
    #define BLM_BLQ_NULL_RECYCLE_MASK     0x00
#endif

#if defined(__NFP_LANG_ASM)
    #ifndef BLM_BLQ_EMEM_TYPE
        #ifdef SPLIT_EMU_RINGS
            #define BLM_BLQ_EMEM_TYPE emem
        #else
            #define BLM_BLQ_EMEM_TYPE emem_cache_upper
        #endif
    #endif
#else //defined(__NFP_LANG_MICROC)
    #ifndef BLM_BLQ_EMEM_TYPE
        #ifdef SPLIT_EMU_RINGS
            #define BLM_BLQ_EMEM_TYPE BLM_MEM_TYPE_EMEM
        #else
            #define BLM_BLQ_EMEM_TYPE BLM_MEM_TYPE_EMEM_CACHE_UPPER
        #endif
    #endif
#endif

#ifndef BLM_NBI8_BLQ0_EMU_Q_LOCALITY
    #define BLM_NBI8_BLQ0_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI8_BLQ1_EMU_Q_LOCALITY
    #define BLM_NBI8_BLQ1_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI8_BLQ2_EMU_Q_LOCALITY
    #define BLM_NBI8_BLQ2_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI8_BLQ3_EMU_Q_LOCALITY
    #define BLM_NBI8_BLQ3_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI9_BLQ0_EMU_Q_LOCALITY
    #define BLM_NBI9_BLQ0_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI9_BLQ1_EMU_Q_LOCALITY
    #define BLM_NBI9_BLQ1_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI9_BLQ2_EMU_Q_LOCALITY
    #define BLM_NBI9_BLQ2_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_NBI9_BLQ3_EMU_Q_LOCALITY
    #define BLM_NBI9_BLQ3_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_PCI4_BLQ0_EMU_Q_LOCALITY
    #define BLM_PCI4_BLQ0_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_PCI4_BLQ1_EMU_Q_LOCALITY
    #define BLM_PCI4_BLQ1_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_PCI4_BLQ2_EMU_Q_LOCALITY
    #define BLM_PCI4_BLQ2_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif

#ifndef BLM_PCI4_BLQ3_EMU_Q_LOCALITY
    #define BLM_PCI4_BLQ3_EMU_Q_LOCALITY MU_LOCALITY_DIRECT_ACCESS
#endif


/* The location of the EMU rings */


#ifndef BLM_NBI8_BLQ0_EMU_Q_ISLAND
    #define BLM_NBI8_BLQ0_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI8_BLQ1_EMU_Q_ISLAND
    #define BLM_NBI8_BLQ1_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI8_BLQ2_EMU_Q_ISLAND
    #define BLM_NBI8_BLQ2_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI8_BLQ3_EMU_Q_ISLAND
    #define BLM_NBI8_BLQ3_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI9_BLQ0_EMU_Q_ISLAND
    #define BLM_NBI9_BLQ0_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI9_BLQ1_EMU_Q_ISLAND
    #define BLM_NBI9_BLQ1_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI9_BLQ2_EMU_Q_ISLAND
    #define BLM_NBI9_BLQ2_EMU_Q_ISLAND 24
#endif

#ifndef BLM_NBI9_BLQ3_EMU_Q_ISLAND
    #define BLM_NBI9_BLQ3_EMU_Q_ISLAND 24
#endif

#ifndef BLM_PCI4_BLQ0_EMU_Q_ISLAND
    #define BLM_PCI4_BLQ0_EMU_Q_ISLAND 24
#endif

#ifndef BLM_PCI4_BLQ1_EMU_Q_ISLAND
    #define BLM_PCI4_BLQ1_EMU_Q_ISLAND 24
#endif

#ifndef BLM_PCI4_BLQ2_EMU_Q_ISLAND
    #define BLM_PCI4_BLQ2_EMU_Q_ISLAND 24
#endif

#ifndef BLM_PCI4_BLQ3_EMU_Q_ISLAND
    #define BLM_PCI4_BLQ3_EMU_Q_ISLAND 24
#endif

/* EMU packet buffer alignment - MUST be a power of 2 and a mult of 2048 */
#ifndef EMU_PKTBUF_ALIGNMENT
#define EMU_PKTBUF_ALIGNMENT 2048
#endif

/* Define per "BLQ-EMU pair" packet buffer size - MUST be a mult of 2048 */
#ifndef NBI8_BLQ_EMU_0_PKTBUF_SIZE
#define NBI8_BLQ_EMU_0_PKTBUF_SIZE 2048
#endif
#ifndef NBI8_BLQ_EMU_1_PKTBUF_SIZE
#define NBI8_BLQ_EMU_1_PKTBUF_SIZE 2048
#endif
#ifndef NBI8_BLQ_EMU_2_PKTBUF_SIZE
#define NBI8_BLQ_EMU_2_PKTBUF_SIZE 2048
#endif
#ifndef NBI8_BLQ_EMU_3_PKTBUF_SIZE
#define NBI8_BLQ_EMU_3_PKTBUF_SIZE 2048
#endif

#ifndef NBI9_BLQ_EMU_0_PKTBUF_SIZE
#define NBI9_BLQ_EMU_0_PKTBUF_SIZE 2048
#endif
#ifndef NBI9_BLQ_EMU_1_PKTBUF_SIZE
#define NBI9_BLQ_EMU_1_PKTBUF_SIZE 2048
#endif
#ifndef NBI9_BLQ_EMU_2_PKTBUF_SIZE
#define NBI9_BLQ_EMU_2_PKTBUF_SIZE 2048
#endif
#ifndef NBI9_BLQ_EMU_3_PKTBUF_SIZE
#define NBI9_BLQ_EMU_3_PKTBUF_SIZE 2048
#endif

#ifndef PCI4_BLQ_EMU_0_PKTBUF_SIZE
#define PCI4_BLQ_EMU_0_PKTBUF_SIZE 2048
#endif
#ifndef PCI4_BLQ_EMU_1_PKTBUF_SIZE
#define PCI4_BLQ_EMU_1_PKTBUF_SIZE 2048
#endif
#ifndef PCI4_BLQ_EMU_2_PKTBUF_SIZE
#define PCI4_BLQ_EMU_2_PKTBUF_SIZE 2048
#endif
#ifndef PCI4_BLQ_EMU_3_PKTBUF_SIZE
#define PCI4_BLQ_EMU_3_PKTBUF_SIZE 2048
#endif


/* The size of each of the 4 EMU rings */

#ifndef BLM_NBI8_BLQ0_Q_SIZE
#define BLM_NBI8_BLQ0_Q_SIZE            (4096*4)
#endif
#ifndef BLM_NBI8_BLQ1_Q_SIZE
#define BLM_NBI8_BLQ1_Q_SIZE            (4096*4)
#endif
#ifndef BLM_NBI8_BLQ2_Q_SIZE
#define BLM_NBI8_BLQ2_Q_SIZE            (4096*4)
#endif
#ifndef BLM_NBI8_BLQ3_Q_SIZE
#define BLM_NBI8_BLQ3_Q_SIZE            (4096*4)
#endif

#ifndef BLM_NBI9_BLQ0_Q_SIZE
#define BLM_NBI9_BLQ0_Q_SIZE            (4096*4)
#endif
#ifndef BLM_NBI9_BLQ1_Q_SIZE
#define BLM_NBI9_BLQ1_Q_SIZE            (4096*4)
#endif
#ifndef BLM_NBI9_BLQ2_Q_SIZE
#define BLM_NBI9_BLQ2_Q_SIZE            (4096*4)
#endif
#ifndef BLM_NBI9_BLQ3_Q_SIZE
#define BLM_NBI9_BLQ3_Q_SIZE            (4096*4)
#endif

#ifndef BLM_PCI4_BLQ0_Q_SIZE
#define BLM_PCI4_BLQ0_Q_SIZE            (4096*4)
#endif
#ifndef BLM_PCI4_BLQ1_Q_SIZE
#define BLM_PCI4_BLQ1_Q_SIZE            (4096*4)
#endif
#ifndef BLM_PCI4_BLQ2_Q_SIZE
#define BLM_PCI4_BLQ2_Q_SIZE            (4096*4)
#endif
#ifndef BLM_PCI4_BLQ3_Q_SIZE
#define BLM_PCI4_BLQ3_Q_SIZE            (4096*4)
#endif


/*****************************************************************************
    BLQ and EMU Rings buffers configuration.

    Each of the 4 BLQs has a "shadowing" EMU ring used for flushing
    buffers from the matching TM's BLQ when the matching DMA's BLQ is full.
    Those "shadow" EMU rings are also used for allocating and freeing MU
    buffers from the APP MEs.
    The following section determines how many buffers are to be allocated
    from each of the 5 possible memory regions for EMU rings and for the BLQs.
    The total number of buffers per memory region is the sum of those numbers.

    For NFP-6xxx, the valid BLQ LENs are 512,1024,2048,4096.

    For NFP-38xx, the valid BLQ LENs are 256,512,1024,2048.

*****************************************************************************/

#ifdef BLM_USE_NFP38XX_DEFAULTS
    #define BLM_NBI_DMA_BDSRAM_SZ   2048
    #define BLM_PCI_DMA_BDSRAM_SZ   2048
    /* work around us not being able to reset the blq count for events
     * this work around ignores the first event and runs the blq a little
     * emptier than ideal
     */
#else
    #define BLM_NBI_DMA_BDSRAM_SZ   4096
    #define BLM_PCI_DMA_BDSRAM_SZ   0
#endif

/* Note: Default setting is to divide BDSRAM equally among the 4 BLQs. */
#define BLM_NBI_DMA_DEFAULT_BLQ_LEN (BLM_NBI_DMA_BDSRAM_SZ >> 2)
#define BLM_PCI_DMA_DEFAULT_BLQ_LEN (BLM_PCI_DMA_BDSRAM_SZ >> 2)


/* BLQ and EMU RINGS NBI 8 */

#ifndef BLM_NBI8_BLQ0_LEN
    #define BLM_NBI8_BLQ0_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_NBI8_BLQ1_LEN
    #define BLM_NBI8_BLQ1_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_NBI8_BLQ2_LEN
    #define BLM_NBI8_BLQ2_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_NBI8_BLQ3_LEN
    #define BLM_NBI8_BLQ3_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif

#if (BLM_NBI8_BLQ0_LEN + BLM_NBI8_BLQ1_LEN + BLM_NBI8_BLQ2_LEN + BLM_NBI8_BLQ3_LEN > BLM_NBI_DMA_BDSRAM_SZ)
    #if (BLM_NBI_DMA_BDSRAM_SZ == 4096)
        #error "The total length of all BLQs in NBI8 must not exceed 4096"
    #elif (BLM_NBI_DMA_BDSRAM_SZ == 2048)
        #error "The total length of all BLQs in NBI8 must not exceed 2048"
    #else
        #error "The total length of all BLQs in NBI8 exceeds size of BDSRAM"
    #endif
#endif

/* Ring 0 */

/* The number of buffers from IMEM0 for EMU ring 0 */
#ifndef BLM_NBI8_BLQ0_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_IMEM0_NUM_BUFS    0
#endif
/* The number of buffers from IMEM0 for BLQ ring 0 */
#ifndef BLM_NBI8_BLQ0_BDSRAM_IMEM0_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ0_BDSRAM_IMEM0_NUM_BUFS 0
    #else
        #define BLM_NBI8_BLQ0_BDSRAM_IMEM0_NUM_BUFS \
            (BLM_NBI_DMA_DEFAULT_BLQ_LEN >> 1)
    #endif
#endif
#ifndef BLM_NBI8_BLQ0_EMU_IMEM0_DENSITY
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ0_EMU_IMEM0_DENSITY     0
    #else
        #define BLM_NBI8_BLQ0_EMU_IMEM0_DENSITY     1
    #endif
#endif

#ifndef BLM_NBI8_BLQ0_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ0_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ0_EMU_IMEM1_DENSITY
    #define BLM_NBI8_BLQ0_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ0_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_EMEM0_NUM_BUFS    1024
#endif
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_EMEM0_NUM_BUFS \
        (BLM_NBI_DMA_DEFAULT_BLQ_LEN >> 1)
#endif
#ifndef BLM_NBI8_BLQ0_EMU_EMEM0_DENSITY
    #define BLM_NBI8_BLQ0_EMU_EMEM0_DENSITY     1
#endif

#ifndef BLM_NBI8_BLQ0_EMU_EMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ0_EMU_EMEM1_DENSITY
    #define BLM_NBI8_BLQ0_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ0_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ0_EMU_EMEM2_DENSITY
    #define BLM_NBI8_BLQ0_EMU_EMEM2_DENSITY     0
#endif

/* Number of Buffers from EMEM cache */
/* Number of EMU cache buffers in BDSRAM ring for NBI-8 BLQ-0 */
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-8 BLQ-0 */
#ifndef BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-0 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-0 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-0 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-8 BLQ-1 */
#ifndef BLM_NBI8_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-8 BLQ-1 */
#ifndef BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-1 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-1 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-1 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-8 BLQ-2 */
#ifndef BLM_NBI8_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-8 BLQ-2 */
#ifndef BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-2 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-2 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-2 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-8 BLQ-3 */
#ifndef BLM_NBI8_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-8 BLQ-3 */
#ifndef BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-3 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-3 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-8 BLQ-3 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-9 BLQ-0 */
#ifndef BLM_NBI9_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-9 BLQ-0 */
#ifndef BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-0 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-0 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-0 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-9 BLQ-1 */
#ifndef BLM_NBI9_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-9 BLQ-1 */
#ifndef BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-1 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-1 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-1 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-9 BLQ-2 */
#ifndef BLM_NBI9_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-9 BLQ-2 */
#ifndef BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-2 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-2 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-2 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Number of EMU cache buffers in BDSRAM ring for NBI-9 BLQ-3 */
#ifndef BLM_NBI9_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS   0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS   0
#endif

/* Number of EMU cache buffers in EMU ring for NBI-9 BLQ-3 */
#ifndef BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-3 EMU-0 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_DENSITY
    #define BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-3 EMU-1 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_DENSITY
    #define BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_DENSITY       0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS      0
#endif
/* NBI-9 BLQ-3 EMU-2 Cache Density (applies for both BDSRAM & EMU Ring) */
#ifndef BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_DENSITY
    #define BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_DENSITY       0
#endif

/* Ring 1 */

#ifndef BLM_NBI8_BLQ1_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ1_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ1_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ1_EMU_IMEM0_DENSITY
    #define BLM_NBI8_BLQ1_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ1_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ1_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ1_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ1_EMU_IMEM1_DENSITY
    #define BLM_NBI8_BLQ1_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ1_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ1_EMU_EMEM0_NUM_BUFS    1536
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_EMEM0_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_BDSRAM_EMEM0_NUM_BUFS BLM_NBI_DMA_DEFAULT_BLQ_LEN
    #else
        #define BLM_NBI8_BLQ1_BDSRAM_EMEM0_NUM_BUFS \
            (BLM_NBI_DMA_DEFAULT_BLQ_LEN >> 1)
    #endif
#endif
#ifndef BLM_NBI8_BLQ1_EMU_EMEM0_DENSITY
    #define BLM_NBI8_BLQ1_EMU_EMEM0_DENSITY     2
#endif

#ifndef BLM_NBI8_BLQ1_EMU_EMEM1_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_EMU_EMEM1_NUM_BUFS    0
    #else
        #define BLM_NBI8_BLQ1_EMU_EMEM1_NUM_BUFS    768
    #endif
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_EMEM1_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_BDSRAM_EMEM1_NUM_BUFS 0
    #else
        #define BLM_NBI8_BLQ1_BDSRAM_EMEM1_NUM_BUFS \
            (BLM_NBI_DMA_DEFAULT_BLQ_LEN >> 2)
    #endif
#endif
#ifndef BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY     0
    #else
        #define BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY     1
    #endif
#endif

#ifndef BLM_NBI8_BLQ1_EMU_EMEM2_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_EMU_EMEM2_NUM_BUFS    0
    #else
        #define BLM_NBI8_BLQ1_EMU_EMEM2_NUM_BUFS    768
    #endif
#endif
#ifndef BLM_NBI8_BLQ1_BDSRAM_EMEM2_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_BDSRAM_EMEM2_NUM_BUFS 0
    #else
        #define BLM_NBI8_BLQ1_BDSRAM_EMEM2_NUM_BUFS \
            (BLM_NBI_DMA_DEFAULT_BLQ_LEN >> 2)
    #endif
#endif
#ifndef BLM_NBI8_BLQ1_EMU_EMEM2_DENSITY
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI8_BLQ1_EMU_EMEM2_DENSITY     0
    #else
        #define BLM_NBI8_BLQ1_EMU_EMEM2_DENSITY     1
    #endif
#endif

/* Ring 2 */

#ifndef BLM_NBI8_BLQ2_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_IMEM0_DENSITY
    #define BLM_NBI8_BLQ2_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ2_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_IMEM1_DENSITY
    #define BLM_NBI8_BLQ2_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ2_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_EMEM0_DENSITY
    #define BLM_NBI8_BLQ2_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ2_EMU_EMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_EMEM1_DENSITY
    #define BLM_NBI8_BLQ2_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ2_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI8_BLQ2_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ2_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI8_BLQ2_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ2_EMU_EMEM2_DENSITY
    #define BLM_NBI8_BLQ2_EMU_EMEM2_DENSITY     0
#endif

/* Ring 3 */

#ifndef BLM_NBI8_BLQ3_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_IMEM0_DENSITY
    #define BLM_NBI8_BLQ3_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ3_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_IMEM1_DENSITY
    #define BLM_NBI8_BLQ3_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ3_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_EMEM0_DENSITY
    #define BLM_NBI8_BLQ3_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ3_EMU_EMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_EMEM1_DENSITY
    #define BLM_NBI8_BLQ3_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_NBI8_BLQ3_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI8_BLQ3_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_NBI8_BLQ3_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI8_BLQ3_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_NBI8_BLQ3_EMU_EMEM2_DENSITY
    #define BLM_NBI8_BLQ3_EMU_EMEM2_DENSITY     0
#endif

/*****************************************************************************
    Some notes about the usage of NBI9

    NBI9 will be handled by BLM INSTANCE 1, so the BLQ part is relevant in
    a 2 NBI system.

    The EMU rings part is ONLY relevant when the SPLIT_EMU_RINGS is defined,
    this means each of the BNIs has its own copy of the "shadowing" EMU rings.
    Otherwise we only have one copy of those rings which is shared between
    the two NBIs (so EMU ring 0 "shadows" both BLQs 0, on NBI8 and 9).

*****************************************************************************/

/* BLQ and EMU RINGS NBI 9 */

#ifndef BLM_NBI9_BLQ0_LEN
    #define BLM_NBI9_BLQ0_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_NBI9_BLQ1_LEN
    #define BLM_NBI9_BLQ1_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_NBI9_BLQ2_LEN
    #define BLM_NBI9_BLQ2_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_NBI9_BLQ3_LEN
    #define BLM_NBI9_BLQ3_LEN   BLM_NBI_DMA_DEFAULT_BLQ_LEN
#endif

#if (BLM_NBI9_BLQ0_LEN + BLM_NBI9_BLQ1_LEN + BLM_NBI9_BLQ2_LEN + BLM_NBI9_BLQ3_LEN > BLM_NBI_DMA_BDSRAM_SZ)
    #if (BLM_NBI_DMA_BDSRAM_SZ == 4096)
        #error "The total length of all BLQs in NBI9 must not exceed 4096"
    #elif (BLM_NBI_DMA_BDSRAM_SZ == 2048)
        #error "The total length of all BLQs in NBI9 must not exceed 2048"
    #else
        #error "The total length of all BLQs in NBI9 exceeds size of BDSRAM"
    #endif
#endif

/* Ring 0 */

#ifndef BLM_NBI9_BLQ0_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ0_EMU_IMEM0_DENSITY
    #define BLM_NBI9_BLQ0_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ0_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_IMEM1_NUM_BUFS 512
#endif
#ifndef BLM_NBI9_BLQ0_EMU_IMEM1_DENSITY
    #define BLM_NBI9_BLQ0_EMU_IMEM1_DENSITY     1
#endif

#ifndef BLM_NBI9_BLQ0_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ0_EMU_EMEM0_DENSITY
    #define BLM_NBI9_BLQ0_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ0_EMU_EMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ0_EMU_EMEM1_DENSITY
    #define BLM_NBI9_BLQ0_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ0_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ0_EMU_EMEM2_NUM_BUFS    1024
#endif
#ifndef BLM_NBI9_BLQ0_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ0_BDSRAM_EMEM2_NUM_BUFS 512
#endif
#ifndef BLM_NBI9_BLQ0_EMU_EMEM2_DENSITY
    #define BLM_NBI9_BLQ0_EMU_EMEM2_DENSITY     1
#endif

/* Ring 1 */

#ifndef BLM_NBI9_BLQ1_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ1_EMU_IMEM0_DENSITY
    #define BLM_NBI9_BLQ1_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ1_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ1_EMU_IMEM1_DENSITY
    #define BLM_NBI9_BLQ1_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ1_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_EMEM0_NUM_BUFS    1536
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_EMEM0_NUM_BUFS 512
#endif
#ifndef BLM_NBI9_BLQ1_EMU_EMEM0_DENSITY
    #define BLM_NBI9_BLQ1_EMU_EMEM0_DENSITY     2
#endif

#ifndef BLM_NBI9_BLQ1_EMU_EMEM1_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI9_BLQ1_EMU_EMEM1_NUM_BUFS    0
    #else
        #define BLM_NBI9_BLQ1_EMU_EMEM1_NUM_BUFS    768
    #endif
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_EMEM1_NUM_BUFS
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI9_BLQ1_BDSRAM_EMEM1_NUM_BUFS 0
    #else
        #define BLM_NBI9_BLQ1_BDSRAM_EMEM1_NUM_BUFS 256
    #endif
#endif
#ifndef BLM_NBI9_BLQ1_EMU_EMEM1_DENSITY
    #ifdef BLM_USE_NFP38XX_DEFAULTS
        #define BLM_NBI9_BLQ1_EMU_EMEM1_DENSITY     0
    #else
        #define BLM_NBI9_BLQ1_EMU_EMEM1_DENSITY     1
    #endif
#endif

#ifndef BLM_NBI9_BLQ1_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ1_EMU_EMEM2_NUM_BUFS    768
#endif
#ifndef BLM_NBI9_BLQ1_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ1_BDSRAM_EMEM2_NUM_BUFS 256
#endif
#ifndef BLM_NBI9_BLQ1_EMU_EMEM2_DENSITY
    #define BLM_NBI9_BLQ1_EMU_EMEM2_DENSITY     1
#endif

/* Ring 2 */

#ifndef BLM_NBI9_BLQ2_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_IMEM0_DENSITY
    #define BLM_NBI9_BLQ2_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ2_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_IMEM1_DENSITY
    #define BLM_NBI9_BLQ2_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ2_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_EMEM0_DENSITY
    #define BLM_NBI9_BLQ2_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ2_EMU_EMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_EMEM1_DENSITY
    #define BLM_NBI9_BLQ2_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ2_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ2_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ2_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ2_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ2_EMU_EMEM2_DENSITY
    #define BLM_NBI9_BLQ2_EMU_EMEM2_DENSITY     0
#endif

/* Ring 3 */

#ifndef BLM_NBI9_BLQ3_EMU_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_IMEM0_DENSITY
    #define BLM_NBI9_BLQ3_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ3_EMU_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_IMEM1_DENSITY
    #define BLM_NBI9_BLQ3_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ3_EMU_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_EMEM0_DENSITY
    #define BLM_NBI9_BLQ3_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ3_EMU_EMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_EMEM1_DENSITY
    #define BLM_NBI9_BLQ3_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_NBI9_BLQ3_EMU_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ3_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_NBI9_BLQ3_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_NBI9_BLQ3_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_NBI9_BLQ3_EMU_EMEM2_DENSITY
    #define BLM_NBI9_BLQ3_EMU_EMEM2_DENSITY     0
#endif


/*****************************************************************************
    Some notes about the usage of PCI4

    PCI4 will be handled by BLM INSTANCE 0, with each BLQ assigned to either
    NBI or PCIe.  The BLQ part is relevant if a BLQ is assigned to PCIe.

    The EMU rings part is ONLY relevant when the SPLIT_EMU_RINGS is defined,
    which means each entity would have its own copy of the "shadowing" EMU
    rings.  Otherwise we only have one copy of those rings which is shared
    between the two NBIs and PCIs (so EMU ring 0 "shadows" both BLQs 0,
    on NBI8 and 9).

*****************************************************************************/

/* BLQ and EMU RINGS PCI 4 */

#ifndef BLM_PCI4_BLQ0_LEN
    #define BLM_PCI4_BLQ0_LEN   BLM_PCI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_PCI4_BLQ1_LEN
    #define BLM_PCI4_BLQ1_LEN   BLM_PCI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_PCI4_BLQ2_LEN
    #define BLM_PCI4_BLQ2_LEN   BLM_PCI_DMA_DEFAULT_BLQ_LEN
#endif
#ifndef BLM_PCI4_BLQ3_LEN
    #define BLM_PCI4_BLQ3_LEN   BLM_PCI_DMA_DEFAULT_BLQ_LEN
#endif

#if (BLM_PCI4_BLQ0_LEN + BLM_PCI4_BLQ1_LEN + BLM_PCI4_BLQ2_LEN + BLM_PCI4_BLQ3_LEN > BLM_PCI_DMA_BDSRAM_SZ)
    #if (BLM_PCI_DMA_BDSRAM_SZ == 2048)
        #error "The total length of all BLQs in PCI4 must not exceed 2048"
    #else
        #error "The total length of all BLQs in PCI4 exceeds size of BDSRAM"
    #endif
#endif

/* Ring 0 */

#ifndef BLM_PCI4_BLQ0_EMU_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_IMEM0_DENSITY
    #define BLM_PCI4_BLQ0_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_IMEM1_DENSITY
    #define BLM_PCI4_BLQ0_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_EMEM0_DENSITY
    #define BLM_PCI4_BLQ0_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_EMEM1_DENSITY
    #define BLM_PCI4_BLQ0_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_EMEM2_DENSITY
    #define BLM_PCI4_BLQ0_EMU_EMEM2_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS 0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_DENSITY
    #define BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_DENSITY
    #define BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_DENSITY
    #define BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_DENSITY     0
#endif

/* Ring 1 */

#ifndef BLM_PCI4_BLQ1_EMU_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_IMEM0_DENSITY
    #define BLM_PCI4_BLQ1_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_IMEM1_DENSITY
    #define BLM_PCI4_BLQ1_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_EMEM0_DENSITY
    #define BLM_PCI4_BLQ1_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_EMEM1_DENSITY
    #define BLM_PCI4_BLQ1_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_EMEM2_DENSITY
    #define BLM_PCI4_BLQ1_EMU_EMEM2_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS 0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_DENSITY
    #define BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_DENSITY
    #define BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_DENSITY
    #define BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_DENSITY     0
#endif

/* Ring 2 */

#ifndef BLM_PCI4_BLQ2_EMU_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_IMEM0_DENSITY
    #define BLM_PCI4_BLQ2_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_IMEM1_DENSITY
    #define BLM_PCI4_BLQ2_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_EMEM0_DENSITY
    #define BLM_PCI4_BLQ2_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_EMEM1_DENSITY
    #define BLM_PCI4_BLQ2_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_EMEM2_DENSITY
    #define BLM_PCI4_BLQ2_EMU_EMEM2_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS 0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_DENSITY
    #define BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_DENSITY
    #define BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_DENSITY
    #define BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_DENSITY     0
#endif

/* Ring 3 */

#ifndef BLM_PCI4_BLQ3_EMU_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_IMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_IMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_IMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_IMEM0_DENSITY
    #define BLM_PCI4_BLQ3_EMU_IMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_IMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_IMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_IMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_IMEM1_DENSITY
    #define BLM_PCI4_BLQ3_EMU_IMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_EMEM0_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_EMEM0_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_EMEM0_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_EMEM0_DENSITY
    #define BLM_PCI4_BLQ3_EMU_EMEM0_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_EMEM1_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_EMEM1_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_EMEM1_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_EMEM1_DENSITY
    #define BLM_PCI4_BLQ3_EMU_EMEM1_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_EMEM2_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_EMEM2_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_EMEM2_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_EMEM2_DENSITY
    #define BLM_PCI4_BLQ3_EMU_EMEM2_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS 0
#endif
#ifndef BLM_PCI4_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS 0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_DENSITY
    #define BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_DENSITY
    #define BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_DENSITY     0
#endif

#ifndef BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS
    #define BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS    0
#endif
#ifndef BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_DENSITY
    #define BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_DENSITY     0
#endif

/* MACROs defining the parameter list for the call to "blm_blq_fill"       */
/*                                                                         */
/* #macro blm_blq_fill(NBI_NUM, BLQ_LEN, BDSRAM_OFF, BUF_SIZE,       \     */
/*		IMEM0_NUM_BUFS, IMEM0_BASE, IMEM0_DENSITY,                   \     */
/*      IMEM1_NUM_BUFS, IMEM1_BASE, IMEM1_DENSITY,                   \     */
/*      EMEM0_CACHE_NUM_BUFS, EMEM0_CACHE_BASE, EMEM0_CACHE_DENSITY, \     */
/*      EMEM1_CACHE_NUM_BUFS, EMEM1_CACHE_BASE, EMEM1_CACHE_DENSITY, \     */
/*      EMEM2_CACHE_NUM_BUFS, EMEM2_CACHE_BASE, EMEM2_CACHE_DENSITY, \     */
/*      EMEM0_NUM_BUFS, EMEM0_BASE, EMEM0_DENSITY,                   \     */
/*      EMEM1_NUM_BUFS, EMEM1_BASE, EMEM1_DENSITY,                   \     */
/*      EMEM2_NUM_BUFS, EMEM2_BASE, EMEM2_DENSITY)                         */

#ifndef NBI8_BLQ0_FILL_PARAMS
#define NBI8_BLQ0_FILL_PARAMS \
                8, BLM_NBI8_BLQ0_LEN, 0, NBI8_BLQ_EMU_0_PKTBUF_SIZE, \
                BLM_NBI8_BLQ0_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI8_BLQ0_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI8_BLQ0_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ0_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ0_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM2_DENSITY
#endif

#ifndef NBI8_BLQ1_FILL_PARAMS
#define NBI8_BLQ1_FILL_PARAMS \
                8, BLM_NBI8_BLQ1_LEN, BLM_NBI8_BLQ0_LEN, NBI8_BLQ_EMU_1_PKTBUF_SIZE, \
                BLM_NBI8_BLQ1_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI8_BLQ1_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI8_BLQ1_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ1_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ1_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM2_DENSITY
#endif

#ifndef NBI8_BLQ2_FILL_PARAMS
#define NBI8_BLQ2_FILL_PARAMS \
                8, BLM_NBI8_BLQ2_LEN, (BLM_NBI8_BLQ0_LEN+BLM_NBI8_BLQ1_LEN), NBI8_BLQ_EMU_2_PKTBUF_SIZE, \
                BLM_NBI8_BLQ2_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI8_BLQ2_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI8_BLQ2_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ2_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ2_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM2_DENSITY
#endif

#ifndef NBI8_BLQ3_FILL_PARAMS
#define NBI8_BLQ3_FILL_PARAMS \
                8, BLM_NBI8_BLQ3_LEN, (BLM_NBI8_BLQ0_LEN+BLM_NBI8_BLQ1_LEN+BLM_NBI8_BLQ2_LEN), NBI8_BLQ_EMU_3_PKTBUF_SIZE, \
                BLM_NBI8_BLQ3_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI8_BLQ3_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI8_BLQ3_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ3_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ3_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ0_FILL_PARAMS
#define NBI9_BLQ0_FILL_PARAMS \
                9, BLM_NBI9_BLQ0_LEN, 0, NBI9_BLQ_EMU_0_PKTBUF_SIZE, \
                BLM_NBI9_BLQ0_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI9_BLQ0_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI9_BLQ0_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ0_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ0_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ1_FILL_PARAMS
#define NBI9_BLQ1_FILL_PARAMS \
                9, BLM_NBI9_BLQ1_LEN, BLM_NBI9_BLQ0_LEN, NBI9_BLQ_EMU_1_PKTBUF_SIZE, \
                BLM_NBI9_BLQ1_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI9_BLQ1_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI9_BLQ1_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ1_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ1_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ2_FILL_PARAMS
#define NBI9_BLQ2_FILL_PARAMS \
                9, BLM_NBI9_BLQ2_LEN, (BLM_NBI9_BLQ0_LEN+BLM_NBI9_BLQ1_LEN), NBI9_BLQ_EMU_2_PKTBUF_SIZE, \
                BLM_NBI9_BLQ2_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI9_BLQ2_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI9_BLQ2_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ2_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ2_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ3_FILL_PARAMS
#define NBI9_BLQ3_FILL_PARAMS \
                9, BLM_NBI9_BLQ3_LEN, (BLM_NBI9_BLQ0_LEN+BLM_NBI9_BLQ1_LEN+BLM_NBI9_BLQ2_LEN), NBI9_BLQ_EMU_3_PKTBUF_SIZE, \
                BLM_NBI9_BLQ3_BDSRAM_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_IMEM0_BUFS_BASE, BLM_NBI9_BLQ3_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_IMEM1_BUFS_BASE, BLM_NBI9_BLQ3_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_EMEM0_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_EMEM1_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ3_BDSRAM_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ3_BDSRAM_EMEM2_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ0_FILL_PARAMS
#define PCI4_BLQ0_FILL_PARAMS \
                4, BLM_PCI4_BLQ0_LEN, 0, PCI4_BLQ_EMU_0_PKTBUF_SIZE, \
                BLM_PCI4_BLQ0_BDSRAM_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_IMEM0_BUFS_BASE, BLM_PCI4_BLQ0_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_IMEM1_BUFS_BASE, BLM_PCI4_BLQ0_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_EMEM0_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_EMEM1_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ0_BDSRAM_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ0_BDSRAM_EMEM2_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ1_FILL_PARAMS
#define PCI4_BLQ1_FILL_PARAMS \
                4, BLM_PCI4_BLQ1_LEN, BLM_PCI4_BLQ0_LEN, PCI4_BLQ_EMU_1_PKTBUF_SIZE, \
                BLM_PCI4_BLQ1_BDSRAM_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_IMEM0_BUFS_BASE, BLM_PCI4_BLQ1_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_IMEM1_BUFS_BASE, BLM_PCI4_BLQ1_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_EMEM0_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_EMEM1_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ1_BDSRAM_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ1_BDSRAM_EMEM2_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ2_FILL_PARAMS
#define PCI4_BLQ2_FILL_PARAMS \
                4, BLM_PCI4_BLQ2_LEN, (BLM_PCI4_BLQ0_LEN+BLM_PCI4_BLQ1_LEN), PCI4_BLQ_EMU_2_PKTBUF_SIZE, \
                BLM_PCI4_BLQ2_BDSRAM_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_IMEM0_BUFS_BASE, BLM_PCI4_BLQ2_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_IMEM1_BUFS_BASE, BLM_PCI4_BLQ2_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_EMEM0_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_EMEM1_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ2_BDSRAM_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ2_BDSRAM_EMEM2_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ3_FILL_PARAMS
#define PCI4_BLQ3_FILL_PARAMS \
                4, BLM_PCI4_BLQ3_LEN, (BLM_PCI4_BLQ0_LEN+BLM_PCI4_BLQ1_LEN+BLM_PCI4_BLQ2_LEN), PCI4_BLQ_EMU_3_PKTBUF_SIZE, \
                BLM_PCI4_BLQ3_BDSRAM_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_IMEM0_BUFS_BASE, BLM_PCI4_BLQ3_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_IMEM1_BUFS_BASE, BLM_PCI4_BLQ3_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_EMEM0_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_EMEM1_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ3_BDSRAM_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ3_BDSRAM_EMEM2_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM2_DENSITY
#endif

/* MACROs defining the parameter list for the call to "blm_emu_rings_fill" */
/*                                                                         */
/* #macro blm_emu_ring_fill(NBI_NUM, R_NUM, R_SIZE, R_BASE, BUF_SIZE,\     */
/*		IMEM0_NUM_BUFS, IMEM0_BASE, IMEM0_DENSITY,                   \     */
/*      IMEM1_NUM_BUFS, IMEM1_BASE, IMEM1_DENSITY,                   \     */
/*      EMEM0_CACHE_NUM_BUFS, EMEM0_CACHE_BASE, EMEM0_CACHE_DENSITY, \     */
/*      EMEM1_CACHE_NUM_BUFS, EMEM1_CACHE_BASE, EMEM1_CACHE_DENSITY, \     */
/*      EMEM2_CACHE_NUM_BUFS, EMEM2_CACHE_BASE, EMEM2_CACHE_DENSITY, \     */
/*      EMEM0_NUM_BUFS, EMEM0_BASE, EMEM0_DENSITY,                   \     */
/*      EMEM1_NUM_BUFS, EMEM1_BASE, EMEM1_DENSITY,                   \     */
/*      EMEM2_NUM_BUFS, EMEM2_BASE, EMEM2_DENSITY)                         */

#ifndef NBI8_BLQ0_EMU_RING_FILL_PARAMS
#define NBI8_BLQ0_EMU_RING_FILL_PARAMS \
                8, (BLM_NBI8_BLQ0_Q_SIZE/4), _BLM_NBI8_BLQ0_EMU_Q_BASE, NBI8_BLQ_EMU_0_PKTBUF_SIZE, \
                BLM_NBI8_BLQ0_EMU_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_IMEM0_BUFS_BASE, BLM_NBI8_BLQ0_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ0_EMU_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_IMEM1_BUFS_BASE, BLM_NBI8_BLQ0_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ0_EMU_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_EMEM0_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ0_EMU_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_EMEM1_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ0_EMU_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ0_EMU_EMEM2_BUFS_BASE, BLM_NBI8_BLQ0_EMU_EMEM2_DENSITY
#endif

#ifndef NBI8_BLQ1_EMU_RING_FILL_PARAMS
#define NBI8_BLQ1_EMU_RING_FILL_PARAMS \
                8, (BLM_NBI8_BLQ1_Q_SIZE/4), _BLM_NBI8_BLQ1_EMU_Q_BASE, NBI8_BLQ_EMU_1_PKTBUF_SIZE, \
                BLM_NBI8_BLQ1_EMU_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_IMEM0_BUFS_BASE, BLM_NBI8_BLQ1_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ1_EMU_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_IMEM1_BUFS_BASE, BLM_NBI8_BLQ1_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ1_EMU_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_EMEM0_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ1_EMU_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_EMEM1_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ1_EMU_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ1_EMU_EMEM2_BUFS_BASE, BLM_NBI8_BLQ1_EMU_EMEM2_DENSITY
#endif

#ifndef NBI8_BLQ2_EMU_RING_FILL_PARAMS
#define NBI8_BLQ2_EMU_RING_FILL_PARAMS \
                8, (BLM_NBI8_BLQ2_Q_SIZE/4), _BLM_NBI8_BLQ2_EMU_Q_BASE, NBI8_BLQ_EMU_2_PKTBUF_SIZE, \
                BLM_NBI8_BLQ2_EMU_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_IMEM0_BUFS_BASE, BLM_NBI8_BLQ2_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ2_EMU_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_IMEM1_BUFS_BASE, BLM_NBI8_BLQ2_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ2_EMU_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_EMEM0_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ2_EMU_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_EMEM1_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ2_EMU_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ2_EMU_EMEM2_BUFS_BASE, BLM_NBI8_BLQ2_EMU_EMEM2_DENSITY
#endif

#ifndef NBI8_BLQ3_EMU_RING_FILL_PARAMS
#define NBI8_BLQ3_EMU_RING_FILL_PARAMS \
                8, (BLM_NBI8_BLQ3_Q_SIZE/4), _BLM_NBI8_BLQ3_EMU_Q_BASE, NBI8_BLQ_EMU_3_PKTBUF_SIZE, \
                BLM_NBI8_BLQ3_EMU_IMEM0_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_IMEM0_BUFS_BASE, BLM_NBI8_BLQ3_EMU_IMEM0_DENSITY, \
                BLM_NBI8_BLQ3_EMU_IMEM1_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_IMEM1_BUFS_BASE, BLM_NBI8_BLQ3_EMU_IMEM1_DENSITY, \
                BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI8_BLQ3_EMU_EMEM0_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_EMEM0_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM0_DENSITY, \
                BLM_NBI8_BLQ3_EMU_EMEM1_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_EMEM1_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM1_DENSITY, \
                BLM_NBI8_BLQ3_EMU_EMEM2_NUM_BUFS, _BLM_NBI8_BLQ3_EMU_EMEM2_BUFS_BASE, BLM_NBI8_BLQ3_EMU_EMEM2_DENSITY
#endif

/* NBI 9 */
#ifndef NBI9_BLQ0_EMU_RING_FILL_PARAMS
#define NBI9_BLQ0_EMU_RING_FILL_PARAMS \
                9, (BLM_NBI9_BLQ0_Q_SIZE/4), _BLM_NBI9_BLQ0_EMU_Q_BASE, NBI9_BLQ_EMU_0_PKTBUF_SIZE, \
                BLM_NBI9_BLQ0_EMU_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_IMEM0_BUFS_BASE, BLM_NBI9_BLQ0_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ0_EMU_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_IMEM1_BUFS_BASE, BLM_NBI9_BLQ0_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ0_EMU_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_EMEM0_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ0_EMU_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_EMEM1_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ0_EMU_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ0_EMU_EMEM2_BUFS_BASE, BLM_NBI9_BLQ0_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ1_EMU_RING_FILL_PARAMS
#define NBI9_BLQ1_EMU_RING_FILL_PARAMS \
                9, (BLM_NBI9_BLQ1_Q_SIZE/4), _BLM_NBI9_BLQ1_EMU_Q_BASE, NBI9_BLQ_EMU_1_PKTBUF_SIZE, \
                BLM_NBI9_BLQ1_EMU_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_IMEM0_BUFS_BASE, BLM_NBI9_BLQ1_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ1_EMU_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_IMEM1_BUFS_BASE, BLM_NBI9_BLQ1_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ1_EMU_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_EMEM0_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ1_EMU_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_EMEM1_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ1_EMU_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ1_EMU_EMEM2_BUFS_BASE, BLM_NBI9_BLQ1_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ2_EMU_RING_FILL_PARAMS
#define NBI9_BLQ2_EMU_RING_FILL_PARAMS \
                9, (BLM_NBI9_BLQ2_Q_SIZE/4), _BLM_NBI9_BLQ2_EMU_Q_BASE, NBI9_BLQ_EMU_2_PKTBUF_SIZE, \
                BLM_NBI9_BLQ2_EMU_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_IMEM0_BUFS_BASE, BLM_NBI9_BLQ2_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ2_EMU_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_IMEM1_BUFS_BASE, BLM_NBI9_BLQ2_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ2_EMU_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_EMEM0_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ2_EMU_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_EMEM1_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ2_EMU_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ2_EMU_EMEM2_BUFS_BASE, BLM_NBI9_BLQ2_EMU_EMEM2_DENSITY
#endif

#ifndef NBI9_BLQ3_EMU_RING_FILL_PARAMS
#define NBI9_BLQ3_EMU_RING_FILL_PARAMS \
                9, (BLM_NBI9_BLQ3_Q_SIZE/4), _BLM_NBI9_BLQ3_EMU_Q_BASE, NBI9_BLQ_EMU_3_PKTBUF_SIZE, \
                BLM_NBI9_BLQ3_EMU_IMEM0_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_IMEM0_BUFS_BASE, BLM_NBI9_BLQ3_EMU_IMEM0_DENSITY, \
                BLM_NBI9_BLQ3_EMU_IMEM1_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_IMEM1_BUFS_BASE, BLM_NBI9_BLQ3_EMU_IMEM1_DENSITY, \
                BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM0_CACHE_DENSITY, \
                BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM1_CACHE_DENSITY, \
                BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM2_CACHE_DENSITY, \
                BLM_NBI9_BLQ3_EMU_EMEM0_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_EMEM0_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM0_DENSITY, \
                BLM_NBI9_BLQ3_EMU_EMEM1_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_EMEM1_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM1_DENSITY, \
                BLM_NBI9_BLQ3_EMU_EMEM2_NUM_BUFS, _BLM_NBI9_BLQ3_EMU_EMEM2_BUFS_BASE, BLM_NBI9_BLQ3_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ0_EMU_RING_FILL_PARAMS
#define PCI4_BLQ0_EMU_RING_FILL_PARAMS \
                8, (BLM_PCI4_BLQ0_Q_SIZE/4), _BLM_PCI4_BLQ0_EMU_Q_BASE, PCI4_BLQ_EMU_0_PKTBUF_SIZE, \
                BLM_PCI4_BLQ0_EMU_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_IMEM0_BUFS_BASE, BLM_PCI4_BLQ0_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ0_EMU_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_IMEM1_BUFS_BASE, BLM_PCI4_BLQ0_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ0_EMU_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_EMEM0_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ0_EMU_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_EMEM1_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ0_EMU_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ0_EMU_EMEM2_BUFS_BASE, BLM_PCI4_BLQ0_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ1_EMU_RING_FILL_PARAMS
#define PCI4_BLQ1_EMU_RING_FILL_PARAMS \
                8, (BLM_PCI4_BLQ1_Q_SIZE/4), _BLM_PCI4_BLQ1_EMU_Q_BASE, PCI4_BLQ_EMU_1_PKTBUF_SIZE, \
                BLM_PCI4_BLQ1_EMU_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_IMEM0_BUFS_BASE, BLM_PCI4_BLQ1_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ1_EMU_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_IMEM1_BUFS_BASE, BLM_PCI4_BLQ1_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ1_EMU_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_EMEM0_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ1_EMU_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_EMEM1_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ1_EMU_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ1_EMU_EMEM2_BUFS_BASE, BLM_PCI4_BLQ1_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ2_EMU_RING_FILL_PARAMS
#define PCI4_BLQ2_EMU_RING_FILL_PARAMS \
                8, (BLM_PCI4_BLQ2_Q_SIZE/4), _BLM_PCI4_BLQ2_EMU_Q_BASE, PCI4_BLQ_EMU_2_PKTBUF_SIZE, \
                BLM_PCI4_BLQ2_EMU_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_IMEM0_BUFS_BASE, BLM_PCI4_BLQ2_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ2_EMU_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_IMEM1_BUFS_BASE, BLM_PCI4_BLQ2_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ2_EMU_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_EMEM0_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ2_EMU_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_EMEM1_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ2_EMU_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ2_EMU_EMEM2_BUFS_BASE, BLM_PCI4_BLQ2_EMU_EMEM2_DENSITY
#endif

#ifndef PCI4_BLQ3_EMU_RING_FILL_PARAMS
#define PCI4_BLQ3_EMU_RING_FILL_PARAMS \
                8, (BLM_PCI4_BLQ3_Q_SIZE/4), _BLM_PCI4_BLQ3_EMU_Q_BASE, PCI4_BLQ_EMU_3_PKTBUF_SIZE, \
                BLM_PCI4_BLQ3_EMU_IMEM0_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_IMEM0_BUFS_BASE, BLM_PCI4_BLQ3_EMU_IMEM0_DENSITY, \
                BLM_PCI4_BLQ3_EMU_IMEM1_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_IMEM1_BUFS_BASE, BLM_PCI4_BLQ3_EMU_IMEM1_DENSITY, \
                BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM0_CACHE_DENSITY, \
                BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM1_CACHE_DENSITY, \
                BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM2_CACHE_DENSITY, \
                BLM_PCI4_BLQ3_EMU_EMEM0_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_EMEM0_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM0_DENSITY, \
                BLM_PCI4_BLQ3_EMU_EMEM1_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_EMEM1_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM1_DENSITY, \
                BLM_PCI4_BLQ3_EMU_EMEM2_NUM_BUFS, _BLM_PCI4_BLQ3_EMU_EMEM2_BUFS_BASE, BLM_PCI4_BLQ3_EMU_EMEM2_DENSITY
#endif

/* BLM_BLQX_CACHE_SIZE defines are preferred as the cache serves both
 * PCI and NBI, but maintain the BLM_NBI_BLQX_CACHE_SIZE interface
 * for backwards compatibility.  */
#ifdef BLM_NBI_BLQ0_CACHE_SIZE
#define BLM_BLQ0_CACHE_SIZE BLM_NBI_BLQ0_CACHE_SIZE
#endif
#ifdef BLM_NBI_BLQ1_CACHE_SIZE
#define BLM_BLQ1_CACHE_SIZE BLM_NBI_BLQ1_CACHE_SIZE
#endif
#ifdef BLM_NBI_BLQ2_CACHE_SIZE
#define BLM_BLQ2_CACHE_SIZE BLM_NBI_BLQ2_CACHE_SIZE
#endif
#ifdef BLM_NBI_BLQ3_CACHE_SIZE
#define BLM_BLQ3_CACHE_SIZE BLM_NBI_BLQ3_CACHE_SIZE
#endif

#ifndef BLM_BLQ0_CACHE_SIZE
	#define BLM_BLQ0_CACHE_SIZE 128
#else
    #if ((BLM_BLQ0_CACHE_SIZE & (BLM_BLQ0_CACHE_SIZE - 1)) != 0)
        #error "BLM_BLQ0_CACHE_SIZE is not power of 2."
    #endif
    #if BLM_BLQ0_CACHE_SIZE == 0
        #if BLM_BLQ_ENABLE_MASK & (1 << 0) || BLM_PCI_BLQ_ENABLE_MASK & (1 << 0)
            #error "BLM_BLQ0_CACHE_SIZE cannot be 0 when BLQ0 ingress thread is enabled"
        #endif
    #elif (BLM_BLQ0_CACHE_SIZE < 64)
        #error "BLM_BLQ0_CACHE_SIZE shoud be at least 64."
    #endif
#endif
#ifndef BLM_BLQ1_CACHE_SIZE
	#define BLM_BLQ1_CACHE_SIZE 128
#else
    #if ((BLM_BLQ1_CACHE_SIZE & (BLM_BLQ1_CACHE_SIZE - 1)) != 0)
        #error "BLM_BLQ1_CACHE_SIZE is not power of 2."
    #endif
    #if BLM_BLQ1_CACHE_SIZE == 0
        #if BLM_BLQ_ENABLE_MASK & (1 << 1) || BLM_PCI_BLQ_ENABLE_MASK & (1 << 1)
            #error "BLM_NBI_BLQ1_CACHE_SIZE cannot be 0 when BLQ1 ingress thread is enabled"
        #endif
    #elif (BLM_BLQ1_CACHE_SIZE < 64)
        #error "BLM_BLQ1_CACHE_SIZE shoud be at least 64."
    #endif
#endif
#ifndef BLM_BLQ2_CACHE_SIZE
	#define BLM_BLQ2_CACHE_SIZE 128
#else
    #if ((BLM_BLQ2_CACHE_SIZE & (BLM_BLQ2_CACHE_SIZE - 1)) != 0)
        #error "BLM_BLQ2_CACHE_SIZE is not power of 2."
    #endif
    #if BLM_BLQ2_CACHE_SIZE == 0
        #if BLM_BLQ_ENABLE_MASK & (1 << 2) || BLM_PCI_BLQ_ENABLE_MASK & (1 << 2)
            #error "BLM_NBI_BLQ2_CACHE_SIZE cannot be 0 when BLQ2 ingress thread is enabled"
        #endif
    #elif (BLM_BLQ2_CACHE_SIZE < 64)
        #error "BLM_BLQ2_CACHE_SIZE shoud be at least 64."
    #endif
#endif
#ifndef BLM_BLQ3_CACHE_SIZE
	#define BLM_BLQ3_CACHE_SIZE 64
#else
    #if ((BLM_BLQ3_CACHE_SIZE & (BLM_BLQ3_CACHE_SIZE - 1)) != 0)
        #error "BLM_BLQ3_CACHE_SIZE is not power of 2."
    #endif
    #if BLM_BLQ3_CACHE_SIZE == 0
        #if BLM_BLQ_ENABLE_MASK & (1 << 3) || BLM_PCI_BLQ_ENABLE_MASK & (1 << 3)
            #error "BLM_NBI_BLQ3_CACHE_SIZE cannot be 0 when BLQ3 ingress thread is enabled"
        #endif
    #elif (BLM_BLQ3_CACHE_SIZE < 64)
        #error "BLM_BLQ3_CACHE_SIZE shoud be at least 64."
    #endif
#endif

#endif // __NFP_BLM_CFG_H__
