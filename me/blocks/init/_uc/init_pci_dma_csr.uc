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
 * @file:   init_pci_dma_csr.uc
 * @brief:  Contains macros to initialise the PCI DMA
 */

#ifndef _INIT_PCI_DMA_CSR_UC_
#define _INIT_PCI_DMA_CSR_UC_


/** PcieInternalTargets_DMAController_DMAAllocCtrl
 *
 * Sets the PCIe DMA Configuration Register
 *
 * @param PCI_ID                The PCI number, 0..3 depending on PCIe islands on chip
 * @param CTM_POLL_INTVL        Configures the amount of time between packet allocation poll commands to a CTM.
 * @param CTM_POLL_ENA          Configures whether the polling function is enabled or disabled
 *
 */
#macro PcieInternalTargets_DMAController_DMAAllocCtrl(PCI_ID,CTM_POLL_INTVL,CTM_POLL_ENA)
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMAAllocCtrl.CtmPollIntvl       CTM_POLL_INTVL      const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMAAllocCtrl.CtmPollEna         CTM_POLL_ENA        const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMAAllocCtrl.PCIeNum            (PCI_ID + 4)        const
#endm



/** PcieInternalTargets_DMAController_DMABPCfg
 *
 * Configures PCIe DMA Buffer Pool Config Registers
 *
 * @param PCI_ID            The PCI number, 0..3 depending on PCIe islands on chip
 * @param BPE_HEAD          Pointer to the first Buffer Pool Entry register in the list associated with this buffer pool.
 * @param SPLIT_LENGTH      Encoded packet size used when deciding to split packets between CTM and internal/external MUs. See pkt/pkt.h enum PKT_CTM_SIZE for non-NFP6xxx chips.
 * @param SEC_BLIST         Secondary Buffer list number associated. There are 4 buffer lists available, which contain buffer descriptors that are used to store packet data in internal/external MUs.
 * @param PRI_BLIST         Primary Buffer list number associated. There are 4 buffer lists available, which contain buffer descriptors that are used to store packet data in internal/external MUs.
 * @param CTM_OFFSET        Defines the offset to add to the data reference when starting to write packet data to the CTM. The space in front of the packet is for the rewrite script used by the packet modifier. 0: 32B offset, 1: 64B offset, 2: 96B offset, 0xf: 512B offset.
 * @param CTM_BUF_PAD_ENA	Enables adding CtmBufPad bytes to the allocation size of the packet.
 * @param CTM_BUF_PAD		Selects the number of 32 bytes to add to the allocation size of the packet. Allows padding to the allocated space in the CTM for smaller packets in increments of 32B. 0=32B, 1=64B, 0xf=512B.
 * @param BLQ_BYPASS_ENA    When set, selects to use a null buffer descriptor if the packet is not split.
 *
 */
#macro PcieInternalTargets_DMAController_DMABPCfg(PCI_ID,PCI_DMA_BP,BPE_HEAD,SPLIT_LENGTH,SEC_BLIST,PRI_BLIST,CTM_OFFSET,CTM_BUF_PAD_ENA, CTM_BUF_PAD, BLQ_BYPASS_ENA)
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.BpeHead      BPE_HEAD       const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.SplitLength  SPLIT_LENGTH   const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.SecBList     SEC_BLIST      const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.PriBList     PRI_BLIST      const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.CtmOffset    (CTM_OFFSET & 1)    const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.CtmOffsetMsb (CTM_OFFSET >> 1)   const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.CtmBufPadEna CTM_BUF_PAD_ENA     const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.CtmBufPad    CTM_BUF_PAD     const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABP/**/PCI_DMA_BP/**/Cfg.BlqBypassEna BLQ_BYPASS_ENA  const
#endm



/** PcieInternalTargets_DMAController_DMABpeCfg
 *
 * Configures the PCIe Buffer Pool Entry Configuration Register
 *
 * @param PCI_ID            The PCI number, 0..3 depending on PCIe islands on chip
 * @param BUF_CREDIT        Configures the number of buffer credits associated with the CTM. The msbit is the sign bit and must be cleared during configuration.
 * @param PKT_CREDIT        Configures the number of packets allocated to the CTM
 * @param CTM               CTM number to use
 * @param BPE_NUM           Buffer Pool Entry Number. When the register is written this value is the latched version of the buffer pool register number 0-31. Used for debug purposes.
 *
 */
#macro PcieInternalTargets_DMAController_DMABpeCfg(PCI_ID,BPE_NUM,CTM,BUF_CREDIT,PKT_CREDIT)
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABpe/**/BPE_NUM/**/Cfg.BufCredit   BUF_CREDIT  const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABpe/**/BPE_NUM/**/Cfg.PktCredit   PKT_CREDIT  const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABpe/**/BPE_NUM/**/Cfg.Ctm         CTM         const
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABpe/**/BPE_NUM/**/Cfg.BpeNum      BPE_NUM     const

    #define_eval _PCI (PCI_ID + 4)
    .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEConfiguredCredits/**/_PCI/**/.MUPEBufferCredits BUF_CREDIT
    .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEConfiguredCredits/**/_PCI/**/.MUPEPacketCredits PKT_CREDIT
    .init_csr xpb:i/**/CTM.CTMXpbMap.MuConfigReg.ConfigCPP.EnableBulkByteMaskSwap 1
    #undef _PCI
#endm


/** PcieInternalTargets_DMAController_DMABpeChainEnd
 *
 * Configures the PCI DMA Buffer Pool Entry Chain End Register
 *
 * @param PCI_ID            The PCI number, 0..3
 * @param BPECHAINEND       Configures BPE module 'n' as the end of the buffer pool entry chain, where 'n' = 0 to 31.
 *
 */
#macro PcieInternalTargets_DMAController_DMABpeChainEnd(PCI_ID, BPECHAINEND)
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.DMABpeChainEnd.BpeChainEnd BPECHAINEND const
#endm


/** PcieInternalTargets_DMAController_BlqNullMuPtr
 *
 * Configures the PCI null MU pointer
 *
 * @param PCI_ID            The PCI number, 0..3
 * @param NULL_MU_PTR       Programmable Null Memory Buffer Pointer.
 *
 */
#macro PcieInternalTargets_DMAController_BlqNullMuPtr(PCI_ID, NULL_MU_PTR)
    .init_csr pcie:pcie/**/PCI_ID.PcieInternalTargets.DMAController.BlqNullMuPtr NULL_MU_PTR const
#endm

#endif /* _INIT_PCI_DMA_CSR_UC_ */