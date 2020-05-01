/*
 * Copyright (C) 2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file:   init_ctm_pe.uc
 * @brief:  Intermediate CTM packet engine setup
 *
 * @note: The NBI and PCIe DMA init files configure their MUPEConfiguredCredits
 *        allocation.  This file does the configuration for ME owners.
 */

#ifndef _INIT_CTM_PE_UC_
#define _INIT_CTM_PE_UC_

#include "../init_config.h"
#include "init_ctm_pe_csr.uc"


#macro Ctm_Pe_Init(MEI_ID)

    #define_eval _CTM (MEI_ID + 32)

#if !IS_NFPTYPE(__NFP6000)
    CTMXpbMap_MuPacketReg_MUPEBufferConfig(_CTM, PKT_CTM_SHARED_SIZE)
#endif


#if IS_NFPTYPE(__NFP6000)

    #ifdef PKT_MEM_CONFIG
        #define_eval _TOTAL_BYTES (64 * 1024 * (1 << (2 - (PKT_MEM_CONFIG))))
        CTMXpbMap_MuPacketReg_MUPEMemConfig(_CTM, _TOTAL_BYTES)
    #endif

#elif IS_NFPTYPE(__NFP3800)

    #if MEI_ID == 0
        #define_eval _TOTAL_BYTES 0
        #define_eval _TOTAL_PKTS  0

        #if (ENABLE_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND0) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND0))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND0))
        #endif

        #if (ENABLE_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND0) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND0))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND0))
        #endif

        #if (ENABLE_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND0) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND0))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND0))

            CTMXpbMap_MuPacketReg_MUPEConfiguredCredits0(
                _CTM, BUF_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND0),
                PKT_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND0))
        #endif

    #elif MEI_ID == 1

        #define_eval _TOTAL_BYTES 0
        #define_eval _TOTAL_PKTS  0

        #if (ENABLE_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND1) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND1))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND1))
        #endif

        #if (ENABLE_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND1) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND1))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND1))
        #endif

        #if (ENABLE_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND1) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND1))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND1))

            CTMXpbMap_MuPacketReg_MUPEConfiguredCredits0(
                _CTM, BUF_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND1),
                PKT_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND1))
        #endif

    #elif MEI_ID == 2

        #define_eval _TOTAL_BYTES 0
        #define_eval _TOTAL_PKTS  0

        #if (ENABLE_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND2) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND2))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(NBI0_DMA_BPE_CONFIG_ME_ISLAND2))
        #endif

        #if (ENABLE_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND2) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND2))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND2))
        #endif

        #if (ENABLE_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND2) == 1)
            #define_eval _TOTAL_BYTES                                        \
                 (_TOTAL_BYTES + BUF_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND2))
            #define_eval _TOTAL_PKTS                                         \
                 (_TOTAL_PKTS + PKT_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND2))

            CTMXpbMap_MuPacketReg_MUPEConfiguredCredits0(
                _CTM, BUF_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND2),
                PKT_CREDIT_VAL(MEI_DMA_BPE_CONFIG_ME_ISLAND2))
        #endif

    #else
        #error "Invalid MEI_ID."
    #endif

    #if _TOTAL_PKTS > 256
        #error "ME island " MEI_ID " CTM packet credits oversubscribed"
    #endif

    #define_eval _TOTAL_BYTES (_TOTAL_BYTES * PKT_CTM_SHARED_SIZE)
    CTMXpbMap_MuPacketReg_MUPEMemConfig(_CTM, _TOTAL_BYTES)

#else
    #error "Unsupported chip type selected."
#endif

#endm

#endif /* _INIT_CTM_PE_UC_ */
