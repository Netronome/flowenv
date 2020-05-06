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
 * @file:   init_pci_dma.uc
 * @brief:  Intermediate PCI DMA setup
 *
 * @note:   The Buffer List Manager (BLM) block takes care of following 3
 *          configurations:
 *              PcieInternalTargets_DMAController_DMABlqEvent
 *              PcieInternalTargets_DMAController_BLQueCtrl
 *              BDSram contents
 *          Thereafter, the following are fixed config and do not require
 *          explicit exposure to application developers. They can be
 *          initialized here to static values:
 *              PcieInternalTargets_DMAController_DMAAllocCtrl
 *          Finally, there are registers which are application dependent and
 *          are not configured by the BLM, hence we set these here based on
 *          values specified in init_config.h:
 *              PcieInternalTargets_DMAController_DMABpeChainEnd
 *              PcieInternalTargets_DMAController_DMABpeCfg
 *              PcieInternalTargets_DMAController_DMABPCfg
 *              PcieInternalTargets_DMAController_BlqNullMuPtr
 */

#ifndef _INIT_PCI_DMA_UC_
#define _INIT_PCI_DMA_UC_

#include "../init_config.h"
#include "init_pci_dma_csr.uc"

/* Sanity Checking below */
#ifndef PCI_DMA_SPLIT_LENGTH
    #error "PCI_DMA_SPLIT_LENGTH is not defined"
#endif

#ifndef PCI_DMA_CTM_OFFSET
    #error "PCI_DMA_CTM_OFFSET is not defined"
#endif


/* XXX init_ctm_pe.uc performs credit checks, considering all CTM users */


#macro Pci_Dma_Init(PCI_ID)
    #define PCI_DMA_LOOP 0

    /* The following register does not require modification by developers,
     * hence it can be defined statically here */
    PcieInternalTargets_DMAController_DMAAllocCtrl(PCI_ID,
    0,  //CtmPollIntvl = 128 clock cycles
    1   //Ctm Poll Enabled
    )


    /* Buffer Pool Config: */
    #ifdef PCI_DMA_BLQ_BYPASS
        #ifndef PKT_NULL_MU_PTR
            #error "PKT_NULL_MU_PTR must be defined if PCI_DMA_BLQ_BYPASS is set."
        #endif
        #define _BLQ_BYPASS 1
    #else
        #define _BLQ_BYPASS 0
    #endif

    #ifdef PCI_DMA_CTM_BUF_PAD
        #define _CTM_BUF_PAD        PCI_DMA_CTM_BUF_PAD
        #define _CTM_BUF_PAD_ENA    1
    #else
        #define _CTM_BUF_PAD        0
        #define _CTM_BUF_PAD_ENA    0
    #endif

    /* Buffer Pool 0 */
    #ifdef PCI_DMA_BP0_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            0,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP0_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP0_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 1 */
    #ifdef PCI_DMA_BP1_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            1,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP1_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP1_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 2 */
    #ifdef PCI_DMA_BP2_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            2,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP2_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP2_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 3 */
    #ifdef PCI_DMA_BP3_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            3,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP3_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP3_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 4 */
    #ifdef PCI_DMA_BP4_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            4,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP4_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP4_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 5 */
    #ifdef PCI_DMA_BP5_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            5,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP5_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP5_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 6 */
    #ifdef PCI_DMA_BP6_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            6,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP6_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP6_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    /* Buffer Pool 7 */
    #ifdef PCI_DMA_BP7_BLQ_TARGET
        PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,
            7,  //Pool #
            0,  //BpeHead
            PCI_DMA_SPLIT_LENGTH,
            BLQ_SECONDARY(PCI_DMA_BP7_BLQ_TARGET),
            BLQ_PRIMARY(PCI_DMA_BP7_BLQ_TARGET),
            PCI_DMA_CTM_OFFSET,
            _CTM_BUF_PAD_ENA,
            _CTM_BUF_PAD,
            _BLQ_BYPASS
        )
    #endif
    #undef _BLQ_BYPASS
    #undef _CTM_BUF_PAD
    #undef _CTM_BUF_PAD_ENA


    /* Configure Buffer Pool Entries */
    #if (PCI_ID == 0)
        #if (ENABLE_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND0) == 1)
            PcieInternalTargets_DMAController_DMABpeCfg(PCI_ID,
            PCI_DMA_LOOP, //BpeNum
            32, //Ctm
            BUF_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND0),
            PKT_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND0)
            )
            #define_eval PCI_DMA_LOOP (PCI_DMA_LOOP+1)
        #endif
        #if (ENABLE_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND1) == 1)
            PcieInternalTargets_DMAController_DMABpeCfg(PCI_ID,
            PCI_DMA_LOOP, //BpeNum
            33, //Ctm
            BUF_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND1),
            PKT_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND1)
            )
            #define_eval PCI_DMA_LOOP (PCI_DMA_LOOP+1)
        #endif
        #if (ENABLE_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND2) == 1)
            PcieInternalTargets_DMAController_DMABpeCfg(PCI_ID,
            PCI_DMA_LOOP, //BpeNum
            34, //Ctm
            BUF_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND2),
            PKT_CREDIT_VAL(PCI0_DMA_BPE_CONFIG_ME_ISLAND2)
            )
            #define_eval PCI_DMA_LOOP (PCI_DMA_LOOP+1)
        #endif
    #else
        #error "Unsupported chip type selected."
    #endif

    /* Populate ChainEnd register bit for last valid BPE + unused BPEs */
    #define_eval CHAINEND ((0xFFFFFFFF << (PCI_DMA_LOOP-1)) & 0xFFFFFFFF)
    PcieInternalTargets_DMAController_DMABpeChainEnd(PCI_ID, CHAINEND)
    #undef CHAINEND

    /* Configure the null MU pointer */
    #ifdef PKT_NULL_MU_PTR
        PcieInternalTargets_DMAController_BlqNullMuPtr(PCI_ID, PKT_NULL_MU_PTR)
    #endif

    #undef PCI_DMA_LOOP
#endm

#endif /* _INIT_PCI_DMA_UC_ */
