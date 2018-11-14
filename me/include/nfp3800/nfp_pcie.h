/*
 * Copyright (C) 2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          nfp3800/nfp_pcie.h
 * @brief         NFP3800 PCIe CSR definitions
 *
 * This files is auto-generated. Do not edit!
 */

#ifndef _NFP3800__NFP_PCIE_H_
#define _NFP3800__NFP_PCIE_H_


/*
 * PCIe CSRs
 */
#define NFP_PCIE_SRAM_BASE                                 0x0000
#define NFP_PCIE_SRAM_SIZE                                 0x0004
/* InterruptManagerMap: <base>.InterruptManager */
#define NFP_PCIE_IM                                        0x10000
/* EventManagerMap: <base>.EventManager */
#define NFP_PCIE_EM                                        0x20000
/* PcieToCppExpansionBarFunc: <base>.ExpansionBARConfiguration.PcieToCppExpansionBar_PF0... */
#define NFP_PCIE_BARCFG_PF_P2C(_func)                      (0x30000 + ((_func) * 0xc0))

/*
 * Register: CppToPcieBar
 *   [31:30]   MapType
 *   [29]      OverrideRID
 *   [28:21]   RequesterID
 *   [20:0]    Address
 *
 * Name(s):
 * <base>.ExpansionBARConfiguration.CPPToPCIeBAR0...
 */
#define NFP_PCIE_BARCFG_C2P(_bar)                          (0x30600 + ((_bar) * 0x4))
#define   NFP_PCIE_BARCFG_C2P_TYPE(x)                        (((x) & 3) << 30)
#define   NFP_PCIE_BARCFG_C2P_TYPE_of(x)                     (((x) >> 30) & 3)
#define     NFP_PCIE_BARCFG_C2P_TYPE_MEM                     (0)
#define     NFP_PCIE_BARCFG_C2P_TYPE_IO                      (1)
#define     NFP_PCIE_BARCFG_C2P_TYPE_CFG                     (2)
#define     NFP_PCIE_BARCFG_C2P_TYPE_RSVD                    (3)
#define     NFP_PCIE_BARCFG_C2P_TYPE_bf                      0, 31, 30
#define     NFP_PCIE_BARCFG_C2P_TYPE_msk                     (0x3)
#define     NFP_PCIE_BARCFG_C2P_TYPE_shf                     (30)
#define   NFP_PCIE_BARCFG_C2P_ARI_ENABLE                     (1 << 29)
#define     NFP_PCIE_BARCFG_C2P_ARI_ENABLE_bf                0, 29, 29
#define     NFP_PCIE_BARCFG_C2P_ARI_ENABLE_msk               (0x1)
#define     NFP_PCIE_BARCFG_C2P_ARI_ENABLE_bit               (29)
#define   NFP_PCIE_BARCFG_C2P_ARI(x)                         (((x) & 0xff) << 21)
#define   NFP_PCIE_BARCFG_C2P_ARI_of(x)                      (((x) >> 21) & 0xff)
#define     NFP_PCIE_BARCFG_C2P_ARI_bf                       0, 28, 21
#define     NFP_PCIE_BARCFG_C2P_ARI_msk                      (0xff)
#define     NFP_PCIE_BARCFG_C2P_ARI_shf                      (21)
#define   NFP_PCIE_BARCFG_C2P_ADDR(x)                        (((x) & 0x1fffff) << 0)
#define   NFP_PCIE_BARCFG_C2P_ADDR_of(x)                     (((x) >> 0) & 0x1fffff)
#define     NFP_PCIE_BARCFG_C2P_ADDR_bf                      0, 20, 0
#define     NFP_PCIE_BARCFG_C2P_ADDR_msk                     (0x1fffff)
#define     NFP_PCIE_BARCFG_C2P_ADDR_shf                     (0)


/*
 * Register: CppToPcieBaseExt
 *   [15:0]    Cpp2Pcie_Base_Addr_Ext
 *
 * Name(s):
 * <base>.ExpansionBARConfiguration.CPPToPCIeBaseExt0...
 */
#define NFP_PCIE_BARCFG_C2P_EXT(_bar)                      (0x30620 + ((_bar) * 0x4))
#define   NFP_PCIE_BARCFG_C2P_EXT_CPP2PCI_BASE_ADDR_EXT(x)   (((x) & 0xffff) << 0)
#define   NFP_PCIE_BARCFG_C2P_EXT_CPP2PCI_BASE_ADDR_EXT_of(x) (((x) >> 0) & 0xffff)
#define     NFP_PCIE_BARCFG_C2P_EXT_CPP2PCI_BASE_ADDR_EXT_bf 0, 15, 0
#define     NFP_PCIE_BARCFG_C2P_EXT_CPP2PCI_BASE_ADDR_EXT_msk (0xffff)
#define     NFP_PCIE_BARCFG_C2P_EXT_CPP2PCI_BASE_ADDR_EXT_shf (0)

#define NFP_PCIE_MSIX_INSTR_GEN(_f)                        (0x60000 + ((_f) * 0x4))
#define   NFP_PCIE_PCIE_MSI_SW_GEN_MSI_VEC_NUM(x)            (((x) & 0x1f) << 0)
#define   NFP_PCIE_PCIE_MSI_SW_GEN_MSI_VEC_NUM_of(x)         (((x) >> 0) & 0x1f)
#define     NFP_PCIE_PCIE_MSI_SW_GEN_MSI_VEC_NUM_bf          0, 4, 0
#define     NFP_PCIE_PCIE_MSI_SW_GEN_MSI_VEC_NUM_msk         (0x1f)
#define     NFP_PCIE_PCIE_MSI_SW_GEN_MSI_VEC_NUM_shf         (0)

#define   NFP_PCIE_PCIE_MSIX_SW_GEN_MSIX_VEC_NUM(x)          (((x) & 0xff) << 0)
#define   NFP_PCIE_PCIE_MSIX_SW_GEN_MSIX_VEC_NUM_of(x)       (((x) >> 0) & 0xff)
#define     NFP_PCIE_PCIE_MSIX_SW_GEN_MSIX_VEC_NUM_bf        0, 7, 0
#define     NFP_PCIE_PCIE_MSIX_SW_GEN_MSIX_VEC_NUM_msk       (0xff)
#define     NFP_PCIE_PCIE_MSIX_SW_GEN_MSIX_VEC_NUM_shf       (0)


/*
 * Register: PcietFuncCfgLut
 *   [31]      EntryValid
 *   [29:28]   PhysFuncNum
 *   [24:16]   QueueCount
 *   [8:0]     QueueBaseAddr
 *
 * Name(s):
 * <base>.PCIeTargetFuncCfgLUT0...
 */
#define NFP_PCIE_VF_CFG_LUT(_f)                            (0x70000 + ((_f) * 0x4))
#define   NFP_PCIE_VF_CFG_LUT_VALID                          (1 << 31)
#define     NFP_PCIE_VF_CFG_LUT_VALID_bf                     0, 31, 31
#define     NFP_PCIE_VF_CFG_LUT_VALID_msk                    (0x1)
#define     NFP_PCIE_VF_CFG_LUT_VALID_bit                    (31)
#define   NFP_PCIE_VF_CFG_LUT_PF_NUM(x)                      (((x) & 3) << 28)
#define   NFP_PCIE_VF_CFG_LUT_PF_NUM_of(x)                   (((x) >> 28) & 3)
#define     NFP_PCIE_VF_CFG_LUT_PF_NUM_bf                    0, 29, 28
#define     NFP_PCIE_VF_CFG_LUT_PF_NUM_msk                   (0x3)
#define     NFP_PCIE_VF_CFG_LUT_PF_NUM_shf                   (28)
#define   NFP_PCIE_VF_CFG_LUT_QUEUE_CNT(x)                   (((x) & 0x1ff) << 16)
#define   NFP_PCIE_VF_CFG_LUT_QUEUE_CNT_of(x)                (((x) >> 16) & 0x1ff)
#define     NFP_PCIE_VF_CFG_LUT_QUEUE_CNT_bf                 0, 24, 16
#define     NFP_PCIE_VF_CFG_LUT_QUEUE_CNT_msk                (0x1ff)
#define     NFP_PCIE_VF_CFG_LUT_QUEUE_CNT_shf                (16)
#define   NFP_PCIE_VF_CFG_LUT_QUEUE_BASE(x)                  (((x) & 0x1ff) << 0)
#define   NFP_PCIE_VF_CFG_LUT_QUEUE_BASE_of(x)               (((x) >> 0) & 0x1ff)
#define     NFP_PCIE_VF_CFG_LUT_QUEUE_BASE_bf                0, 8, 0
#define     NFP_PCIE_VF_CFG_LUT_QUEUE_BASE_msk               (0x1ff)
#define     NFP_PCIE_VF_CFG_LUT_QUEUE_BASE_shf               (0)

/* QC_Queue_x4SSB: <base>.Queue0... */
#define NFP_PCIE_QUEUE(_q)                                 (0x400000 + ((_q) * 0x800))

/*
 * Register: DMADescrLegacy0
 *   [31:0]    CPPAddressLo
 *
 * Name(s):
 * <base>.DMAController.DmaCmdInsertHiToPCIeven0
 * <base>.DMAController.DmaCmdInsertHiToPCIodd0
 * <base>.DMAController.DmaCmdInsertMedToPCIeven0
 * <base>.DMAController.DmaCmdInsertMedToPCIodd0
 * <base>.DMAController.DmaCmdInsertLoToPCIeven0
 * <base>.DMAController.DmaCmdInsertLoToPCIodd0
 * <base>.DMAController.DmaCmdInsertHiFrmPCIeven0
 * <base>.DMAController.DmaCmdInsertHiFrmPCIodd0
 * <base>.DMAController.DmaCmdInsertMedFrmPCIeven0
 * <base>.DMAController.DmaCmdInsertMedFrmPCIodd0
 * <base>.DMAController.DmaCmdInsertLoFrmPCIeven0
 * <base>.DMAController.DmaCmdInsertLoFrmPCIodd0
 */
#define NFP_PCIE_DMA_TOPCI_HI_EVEN0                        0x800000
#define NFP_PCIE_DMA_TOPCI_HI_ODD0                         0x800010
#define NFP_PCIE_DMA_TOPCI_MED_EVEN0                       0x800020
#define NFP_PCIE_DMA_TOPCI_MED_ODD0                        0x800030
#define NFP_PCIE_DMA_TOPCI_LO_EVEN0                        0x800040
#define NFP_PCIE_DMA_TOPCI_LO_ODD0                         0x800050
#define NFP_PCIE_DMA_FROMPCI_HI_EVEN0                      0x800060
#define NFP_PCIE_DMA_FROMPCI_HI_ODD0                       0x800070
#define NFP_PCIE_DMA_FROMPCI_MED_EVEN0                     0x800080
#define NFP_PCIE_DMA_FROMPCI_MED_ODD0                      0x800090
#define NFP_PCIE_DMA_FROMPCI_LO_EVEN0                      0x8000a0
#define NFP_PCIE_DMA_FROMPCI_LO_ODD0                       0x8000b0
#define   NFP_PCIE_DMA_CMD0_CPP_ADDR_LO(x)                   (((x) & 0xffffffff) << 0)
#define   NFP_PCIE_DMA_CMD0_CPP_ADDR_LO_of(x)                (((x) >> 0) & 0xffffffff)
#define     NFP_PCIE_DMA_CMD0_CPP_ADDR_LO_bf                 0, 31, 0
#define     NFP_PCIE_DMA_CMD0_CPP_ADDR_LO_msk                (0xffffffff)
#define     NFP_PCIE_DMA_CMD0_CPP_ADDR_LO_shf                (0)


/*
 * Register: DMADescrLegacy1
 *   [31:30]   ModeSelect
 *   [29:14]   DmaMode
 *   [13:12]   CppToken
 *   [11:8]    DmaConfigRegIndex
 *   [7:0]     CPPAddressHi
 *
 * Name(s):
 * <base>.DMAController.DmaCmdInsertHiToPCIeven1
 * <base>.DMAController.DmaCmdInsertHiToPCIodd1
 * <base>.DMAController.DmaCmdInsertMedToPCIeven1
 * <base>.DMAController.DmaCmdInsertMedToPCIodd1
 * <base>.DMAController.DmaCmdInsertLoToPCIeven1
 * <base>.DMAController.DmaCmdInsertLoToPCIodd1
 * <base>.DMAController.DmaCmdInsertHiFrmPCIeven1
 * <base>.DMAController.DmaCmdInsertHiFrmPCIodd1
 * <base>.DMAController.DmaCmdInsertMedFrmPCIeven1
 * <base>.DMAController.DmaCmdInsertMedFrmPCIodd1
 * <base>.DMAController.DmaCmdInsertLoFrmPCIeven1
 * <base>.DMAController.DmaCmdInsertLoFrmPCIodd1
 */
#define NFP_PCIE_DMA_TOPCI_HI_EVEN1                        0x800004
#define NFP_PCIE_DMA_TOPCI_HI_ODD1                         0x800014
#define NFP_PCIE_DMA_TOPCI_MED_EVEN1                       0x800024
#define NFP_PCIE_DMA_TOPCI_MED_ODD1                        0x800034
#define NFP_PCIE_DMA_TOPCI_LO_EVEN1                        0x800044
#define NFP_PCIE_DMA_TOPCI_LO_ODD1                         0x800054
#define NFP_PCIE_DMA_FROMPCI_HI_EVEN1                      0x800064
#define NFP_PCIE_DMA_FROMPCI_HI_ODD1                       0x800074
#define NFP_PCIE_DMA_FROMPCI_MED_EVEN1                     0x800084
#define NFP_PCIE_DMA_FROMPCI_MED_ODD1                      0x800094
#define NFP_PCIE_DMA_FROMPCI_LO_EVEN1                      0x8000a4
#define NFP_PCIE_DMA_FROMPCI_LO_ODD1                       0x8000b4
#define   NFP_PCIE_DMA_CMD1_MODE_SEL(x)                      (((x) & 3) << 30)
#define   NFP_PCIE_DMA_CMD1_MODE_SEL_of(x)                   (((x) >> 30) & 3)
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_0                     (0)
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_1                     (1)
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_2                     (2)
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_3                     (3)
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_bf                    0, 31, 30
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_msk                   (0x3)
#define     NFP_PCIE_DMA_CMD1_MODE_SEL_shf                   (30)
#define   NFP_PCIE_DMA_CMD1_DMA_MODE(x)                      (((x) & 0xffff) << 14)
#define   NFP_PCIE_DMA_CMD1_DMA_MODE_of(x)                   (((x) >> 14) & 0xffff)
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_0                     (0)
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_1                     (1)
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_2                     (2)
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_3                     (3)
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_bf                    0, 29, 14
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_msk                   (0xffff)
#define     NFP_PCIE_DMA_CMD1_DMA_MODE_shf                   (14)
#define   NFP_PCIE_DMA_CMD1_CPP_TOKEN(x)                     (((x) & 3) << 12)
#define   NFP_PCIE_DMA_CMD1_CPP_TOKEN_of(x)                  (((x) >> 12) & 3)
#define     NFP_PCIE_DMA_CMD1_CPP_TOKEN_bf                   0, 13, 12
#define     NFP_PCIE_DMA_CMD1_CPP_TOKEN_msk                  (0x3)
#define     NFP_PCIE_DMA_CMD1_CPP_TOKEN_shf                  (12)
#define   NFP_PCIE_DMA_CMD1_DMA_CFG_INDEX(x)                 (((x) & 0xf) << 8)
#define   NFP_PCIE_DMA_CMD1_DMA_CFG_INDEX_of(x)              (((x) >> 8) & 0xf)
#define     NFP_PCIE_DMA_CMD1_DMA_CFG_INDEX_bf               0, 11, 8
#define     NFP_PCIE_DMA_CMD1_DMA_CFG_INDEX_msk              (0xf)
#define     NFP_PCIE_DMA_CMD1_DMA_CFG_INDEX_shf              (8)
#define   NFP_PCIE_DMA_CMD1_CPP_ADDR_HI(x)                   (((x) & 0xff) << 0)
#define   NFP_PCIE_DMA_CMD1_CPP_ADDR_HI_of(x)                (((x) >> 0) & 0xff)
#define     NFP_PCIE_DMA_CMD1_CPP_ADDR_HI_bf                 0, 7, 0
#define     NFP_PCIE_DMA_CMD1_CPP_ADDR_HI_msk                (0xff)
#define     NFP_PCIE_DMA_CMD1_CPP_ADDR_HI_shf                (0)


/*
 * Register: DMADescrLegacy2
 *   [31:0]    PCIeAddressLo
 *
 * Name(s):
 * <base>.DMAController.DmaCmdInsertHiToPCIeven2
 * <base>.DMAController.DmaCmdInsertHiToPCIodd2
 * <base>.DMAController.DmaCmdInsertMedToPCIeven2
 * <base>.DMAController.DmaCmdInsertMedToPCIodd2
 * <base>.DMAController.DmaCmdInsertLoToPCIeven2
 * <base>.DMAController.DmaCmdInsertLoToPCIodd2
 * <base>.DMAController.DmaCmdInsertHiFrmPCIeven2
 * <base>.DMAController.DmaCmdInsertHiFrmPCIodd2
 * <base>.DMAController.DmaCmdInsertMedFrmPCIeven2
 * <base>.DMAController.DmaCmdInsertMedFrmPCIodd2
 * <base>.DMAController.DmaCmdInsertLoFrmPCIeven2
 * <base>.DMAController.DmaCmdInsertLoFrmPCIodd2
 */
#define NFP_PCIE_DMA_TOPCI_HI_EVEN2                        0x800008
#define NFP_PCIE_DMA_TOPCI_HI_ODD2                         0x800018
#define NFP_PCIE_DMA_TOPCI_MED_EVEN2                       0x800028
#define NFP_PCIE_DMA_TOPCI_MED_ODD2                        0x800038
#define NFP_PCIE_DMA_TOPCI_LO_EVEN2                        0x800048
#define NFP_PCIE_DMA_TOPCI_LO_ODD2                         0x800058
#define NFP_PCIE_DMA_FROMPCI_HI_EVEN2                      0x800068
#define NFP_PCIE_DMA_FROMPCI_HI_ODD2                       0x800078
#define NFP_PCIE_DMA_FROMPCI_MED_EVEN2                     0x800088
#define NFP_PCIE_DMA_FROMPCI_MED_ODD2                      0x800098
#define NFP_PCIE_DMA_FROMPCI_LO_EVEN2                      0x8000a8
#define NFP_PCIE_DMA_FROMPCI_LO_ODD2                       0x8000b8
#define   NFP_PCIE_DMA_CMD2_PCIE_ADDR_LO(x)                  (((x) & 0xffffffff) << 0)
#define   NFP_PCIE_DMA_CMD2_PCIE_ADDR_LO_of(x)               (((x) >> 0) & 0xffffffff)
#define     NFP_PCIE_DMA_CMD2_PCIE_ADDR_LO_bf                0, 31, 0
#define     NFP_PCIE_DMA_CMD2_PCIE_ADDR_LO_msk               (0xffffffff)
#define     NFP_PCIE_DMA_CMD2_PCIE_ADDR_LO_shf               (0)


/*
 * Register: DMADescrLegacy3
 *   [31:20]   XferLength
 *   [19:12]   RequesterID
 *   [11]      OverrideRID
 *   [10:8]    TransClass
 *   [7:0]     PCIeAddressHi
 *
 * Name(s):
 * <base>.DMAController.DmaCmdInsertHiToPCIeven3
 * <base>.DMAController.DmaCmdInsertHiToPCIodd3
 * <base>.DMAController.DmaCmdInsertMedToPCIeven3
 * <base>.DMAController.DmaCmdInsertMedToPCIodd3
 * <base>.DMAController.DmaCmdInsertLoToPCIeven3
 * <base>.DMAController.DmaCmdInsertLoToPCIodd3
 * <base>.DMAController.DmaCmdInsertHiFrmPCIeven3
 * <base>.DMAController.DmaCmdInsertHiFrmPCIodd3
 * <base>.DMAController.DmaCmdInsertMedFrmPCIeven3
 * <base>.DMAController.DmaCmdInsertMedFrmPCIodd3
 * <base>.DMAController.DmaCmdInsertLoFrmPCIeven3
 * <base>.DMAController.DmaCmdInsertLoFrmPCIodd3
 */
#define NFP_PCIE_DMA_TOPCI_HI_EVEN3                        0x80000c
#define NFP_PCIE_DMA_TOPCI_HI_ODD3                         0x80001c
#define NFP_PCIE_DMA_TOPCI_MED_EVEN3                       0x80002c
#define NFP_PCIE_DMA_TOPCI_MED_ODD3                        0x80003c
#define NFP_PCIE_DMA_TOPCI_LO_EVEN3                        0x80004c
#define NFP_PCIE_DMA_TOPCI_LO_ODD3                         0x80005c
#define NFP_PCIE_DMA_FROMPCI_HI_EVEN3                      0x80006c
#define NFP_PCIE_DMA_FROMPCI_HI_ODD3                       0x80007c
#define NFP_PCIE_DMA_FROMPCI_MED_EVEN3                     0x80008c
#define NFP_PCIE_DMA_FROMPCI_MED_ODD3                      0x80009c
#define NFP_PCIE_DMA_FROMPCI_LO_EVEN3                      0x8000ac
#define NFP_PCIE_DMA_FROMPCI_LO_ODD3                       0x8000bc
#define   NFP_PCIE_DMA_CMD3_LENGTH(x)                        (((x) & 0xfff) << 20)
#define   NFP_PCIE_DMA_CMD3_LENGTH_of(x)                     (((x) >> 20) & 0xfff)
#define     NFP_PCIE_DMA_CMD3_LENGTH_bf                      0, 31, 20
#define     NFP_PCIE_DMA_CMD3_LENGTH_msk                     (0xfff)
#define     NFP_PCIE_DMA_CMD3_LENGTH_shf                     (20)
#define   NFP_PCIE_DMA_CMD3_RID(x)                           (((x) & 0xff) << 12)
#define   NFP_PCIE_DMA_CMD3_RID_of(x)                        (((x) >> 12) & 0xff)
#define     NFP_PCIE_DMA_CMD3_RID_bf                         0, 19, 12
#define     NFP_PCIE_DMA_CMD3_RID_msk                        (0xff)
#define     NFP_PCIE_DMA_CMD3_RID_shf                        (12)
#define   NFP_PCIE_DMA_CMD3_RID_OVERRIDE                     (1 << 11)
#define     NFP_PCIE_DMA_CMD3_RID_OVERRIDE_bf                0, 11, 11
#define     NFP_PCIE_DMA_CMD3_RID_OVERRIDE_msk               (0x1)
#define     NFP_PCIE_DMA_CMD3_RID_OVERRIDE_bit               (11)
#define   NFP_PCIE_DMA_CMD3_TRANS_CLASS(x)                   (((x) & 7) << 8)
#define   NFP_PCIE_DMA_CMD3_TRANS_CLASS_of(x)                (((x) >> 8) & 7)
#define     NFP_PCIE_DMA_CMD3_TRANS_CLASS_bf                 0, 10, 8
#define     NFP_PCIE_DMA_CMD3_TRANS_CLASS_msk                (0x7)
#define     NFP_PCIE_DMA_CMD3_TRANS_CLASS_shf                (8)
#define   NFP_PCIE_DMA_CMD3_PCIE_ADDR_HI(x)                  (((x) & 0xff) << 0)
#define   NFP_PCIE_DMA_CMD3_PCIE_ADDR_HI_of(x)               (((x) >> 0) & 0xff)
#define     NFP_PCIE_DMA_CMD3_PCIE_ADDR_HI_bf                0, 7, 0
#define     NFP_PCIE_DMA_CMD3_PCIE_ADDR_HI_msk               (0xff)
#define     NFP_PCIE_DMA_CMD3_PCIE_ADDR_HI_shf               (0)


/*
 * Register: DMADescrConfig
 *   [30]      FrmPcieCppRnd8BOdd
 *   [29]      FreeCtmPacketOdd
 *   [28]      SignalOnlyOdd
 *   [27:26]   EndPaddingOdd
 *   [25:24]   StartPaddingOdd
 *   [23]      IdBasedOrderingOdd
 *   [22]      RelaxedOrderingOdd
 *   [21]      NoSnoopOdd
 *   [20]      Target64bitOdd
 *   [19:16]   CppTargetIDOdd
 *   [14]      FrmPcieCppRnd8BEven
 *   [13]      FreeCtmPacketEven
 *   [12]      SignalOnlyEven
 *   [11:10]   EndPaddingEven
 *   [9:8]     StartPaddingEven
 *   [7]       IdBasedOrderingEven
 *   [6]       RelaxedOrderingEven
 *   [5]       NoSnoopEven
 *   [4]       Target64bitEven
 *   [3:0]     CppTargetIDEven
 *
 * Name(s):
 * <base>.DMAController.DMADescrConfig0 <base>.DMAController.DMADescrConfig1
 * <base>.DMAController.DMADescrConfig2 <base>.DMAController.DMADescrConfig3
 * <base>.DMAController.DMADescrConfig4 <base>.DMAController.DMADescrConfig5
 * <base>.DMAController.DMADescrConfig6 <base>.DMAController.DMADescrConfig7
 */
#define NFP_PCIE_DMA_CFG0                                  0x8000c0
#define NFP_PCIE_DMA_CFG1                                  0x8000c4
#define NFP_PCIE_DMA_CFG2                                  0x8000c8
#define NFP_PCIE_DMA_CFG3                                  0x8000cc
#define NFP_PCIE_DMA_CFG4                                  0x8000d0
#define NFP_PCIE_DMA_CFG5                                  0x8000d4
#define NFP_PCIE_DMA_CFG6                                  0x8000d8
#define NFP_PCIE_DMA_CFG7                                  0x8000dc
#define   NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_ODD            (1 << 30)
#define     NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_ODD_bf       0, 30, 30
#define     NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_ODD_msk      (0x1)
#define     NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_ODD_bit      (30)
#define   NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_ODD               (1 << 29)
#define     NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_ODD_bf          0, 29, 29
#define     NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_ODD_msk         (0x1)
#define     NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_ODD_bit         (29)
#define   NFP_PCIE_DMA_CFG_SIGNAL_ONLY_ODD                   (1 << 28)
#define     NFP_PCIE_DMA_CFG_SIGNAL_ONLY_ODD_bf              0, 28, 28
#define     NFP_PCIE_DMA_CFG_SIGNAL_ONLY_ODD_msk             (0x1)
#define     NFP_PCIE_DMA_CFG_SIGNAL_ONLY_ODD_bit             (28)
#define   NFP_PCIE_DMA_CFG_END_PAD_ODD(x)                    (((x) & 3) << 26)
#define   NFP_PCIE_DMA_CFG_END_PAD_ODD_of(x)                 (((x) >> 26) & 3)
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_DISABLED            (0)
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_16B                 (1)
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_64B                 (2)
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_128B                (3)
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_bf                  0, 27, 26
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_msk                 (0x3)
#define     NFP_PCIE_DMA_CFG_END_PAD_ODD_shf                 (26)
#define   NFP_PCIE_DMA_CFG_START_PAD_ODD(x)                  (((x) & 3) << 24)
#define   NFP_PCIE_DMA_CFG_START_PAD_ODD_of(x)               (((x) >> 24) & 3)
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_DISABLED          (0)
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_16B               (1)
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_64B               (2)
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_128B              (3)
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_bf                0, 25, 24
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_msk               (0x3)
#define     NFP_PCIE_DMA_CFG_START_PAD_ODD_shf               (24)
#define   NFP_PCIE_DMA_CFG_ID_BASED_ORDER_ODD                (1 << 23)
#define     NFP_PCIE_DMA_CFG_ID_BASED_ORDER_ODD_bf           0, 23, 23
#define     NFP_PCIE_DMA_CFG_ID_BASED_ORDER_ODD_msk          (0x1)
#define     NFP_PCIE_DMA_CFG_ID_BASED_ORDER_ODD_bit          (23)
#define   NFP_PCIE_DMA_CFG_RELAXED_ORDER_ODD                 (1 << 22)
#define     NFP_PCIE_DMA_CFG_RELAXED_ORDER_ODD_bf            0, 22, 22
#define     NFP_PCIE_DMA_CFG_RELAXED_ORDER_ODD_msk           (0x1)
#define     NFP_PCIE_DMA_CFG_RELAXED_ORDER_ODD_bit           (22)
#define   NFP_PCIE_DMA_CFG_NO_SNOOP_ODD                      (1 << 21)
#define     NFP_PCIE_DMA_CFG_NO_SNOOP_ODD_bf                 0, 21, 21
#define     NFP_PCIE_DMA_CFG_NO_SNOOP_ODD_msk                (0x1)
#define     NFP_PCIE_DMA_CFG_NO_SNOOP_ODD_bit                (21)
#define   NFP_PCIE_DMA_CFG_TARGET_64_ODD                     (1 << 20)
#define     NFP_PCIE_DMA_CFG_TARGET_64_ODD_bf                0, 20, 20
#define     NFP_PCIE_DMA_CFG_TARGET_64_ODD_msk               (0x1)
#define     NFP_PCIE_DMA_CFG_TARGET_64_ODD_bit               (20)
#define   NFP_PCIE_DMA_CFG_CPP_TARGET_ODD(x)                 (((x) & 0xf) << 16)
#define   NFP_PCIE_DMA_CFG_CPP_TARGET_ODD_of(x)              (((x) >> 16) & 0xf)
#define     NFP_PCIE_DMA_CFG_CPP_TARGET_ODD_bf               0, 19, 16
#define     NFP_PCIE_DMA_CFG_CPP_TARGET_ODD_msk              (0xf)
#define     NFP_PCIE_DMA_CFG_CPP_TARGET_ODD_shf              (16)
#define   NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_EVEN           (1 << 14)
#define     NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_EVEN_bf      0, 14, 14
#define     NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_EVEN_msk     (0x1)
#define     NFP_PCIE_DMA_CFG_FRM_PCIE_CPP_RND8B_EVEN_bit     (14)
#define   NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_EVEN              (1 << 13)
#define     NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_EVEN_bf         0, 13, 13
#define     NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_EVEN_msk        (0x1)
#define     NFP_PCIE_DMA_CFG_FREE_CTM_PACKET_EVEN_bit        (13)
#define   NFP_PCIE_DMA_CFG_SIGNAL_ONLY_EVEN                  (1 << 12)
#define     NFP_PCIE_DMA_CFG_SIGNAL_ONLY_EVEN_bf             0, 12, 12
#define     NFP_PCIE_DMA_CFG_SIGNAL_ONLY_EVEN_msk            (0x1)
#define     NFP_PCIE_DMA_CFG_SIGNAL_ONLY_EVEN_bit            (12)
#define   NFP_PCIE_DMA_CFG_END_PAD_EVEN(x)                   (((x) & 3) << 10)
#define   NFP_PCIE_DMA_CFG_END_PAD_EVEN_of(x)                (((x) >> 10) & 3)
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_DISABLED           (0)
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_16B                (1)
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_64B                (2)
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_128B               (3)
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_bf                 0, 11, 10
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_msk                (0x3)
#define     NFP_PCIE_DMA_CFG_END_PAD_EVEN_shf                (10)
#define   NFP_PCIE_DMA_CFG_START_PAD_EVEN(x)                 (((x) & 3) << 8)
#define   NFP_PCIE_DMA_CFG_START_PAD_EVEN_of(x)              (((x) >> 8) & 3)
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_DISABLED         (0)
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_16B              (1)
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_64B              (2)
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_128B             (3)
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_bf               0, 9, 8
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_msk              (0x3)
#define     NFP_PCIE_DMA_CFG_START_PAD_EVEN_shf              (8)
#define   NFP_PCIE_DMA_CFG_ID_BASED_ORDER_EVEN               (1 << 7)
#define     NFP_PCIE_DMA_CFG_ID_BASED_ORDER_EVEN_bf          0, 7, 7
#define     NFP_PCIE_DMA_CFG_ID_BASED_ORDER_EVEN_msk         (0x1)
#define     NFP_PCIE_DMA_CFG_ID_BASED_ORDER_EVEN_bit         (7)
#define   NFP_PCIE_DMA_CFG_RELAXED_ORDER_EVEN                (1 << 6)
#define     NFP_PCIE_DMA_CFG_RELAXED_ORDER_EVEN_bf           0, 6, 6
#define     NFP_PCIE_DMA_CFG_RELAXED_ORDER_EVEN_msk          (0x1)
#define     NFP_PCIE_DMA_CFG_RELAXED_ORDER_EVEN_bit          (6)
#define   NFP_PCIE_DMA_CFG_NO_SNOOP_EVEN                     (1 << 5)
#define     NFP_PCIE_DMA_CFG_NO_SNOOP_EVEN_bf                0, 5, 5
#define     NFP_PCIE_DMA_CFG_NO_SNOOP_EVEN_msk               (0x1)
#define     NFP_PCIE_DMA_CFG_NO_SNOOP_EVEN_bit               (5)
#define   NFP_PCIE_DMA_CFG_TARGET_64_EVEN                    (1 << 4)
#define     NFP_PCIE_DMA_CFG_TARGET_64_EVEN_bf               0, 4, 4
#define     NFP_PCIE_DMA_CFG_TARGET_64_EVEN_msk              (0x1)
#define     NFP_PCIE_DMA_CFG_TARGET_64_EVEN_bit              (4)
#define   NFP_PCIE_DMA_CFG_CPP_TARGET_EVEN(x)                (((x) & 0xf) << 0)
#define   NFP_PCIE_DMA_CFG_CPP_TARGET_EVEN_of(x)             (((x) >> 0) & 0xf)
#define     NFP_PCIE_DMA_CFG_CPP_TARGET_EVEN_bf              0, 3, 0
#define     NFP_PCIE_DMA_CFG_CPP_TARGET_EVEN_msk             (0xf)
#define     NFP_PCIE_DMA_CFG_CPP_TARGET_EVEN_shf             (0)


/*
 * Register: DMAToQueueStatus0
 *   [31:24]   DmaLoQueAvail
 *   [23:16]   DmaLoQueWrPtr
 *   [13]      DisAriError
 *   [12]      ResetDMA
 *   [11]      MultiBitError
 *   [10]      DisDmaDescMultiBitErr
 *   [9]       HaltOnPfDmaError
 *   [8]       HaltOnRdMultiBitError
 *   [7:6]     DmaError
 *   [5:4]     QueueOverflow
 *   [3]       HaltOnFull
 *   [2]       HighQueueStop
 *   [1]       MediumQueueStop
 *   [0]       LowQueueStop
 *
 * Name(s):
 * <base>.DMAController.DMAQStatToPCI0
 */
#define NFP_PCIE_DMA_QSTS0_TOPCI                           0x8000e0
#define   NFP_PCIE_DMA_TOQSTS0_DMA_LO_AVAIL(x)               (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_TOQSTS0_DMA_LO_AVAIL_of(x)            (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_TOQSTS0_DMA_LO_AVAIL_bf             0, 31, 24
#define     NFP_PCIE_DMA_TOQSTS0_DMA_LO_AVAIL_msk            (0xff)
#define     NFP_PCIE_DMA_TOQSTS0_DMA_LO_AVAIL_shf            (24)
#define   NFP_PCIE_DMA_TOQSTS0_DMA_LO_WRPTR(x)               (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_TOQSTS0_DMA_LO_WRPTR_of(x)            (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_TOQSTS0_DMA_LO_WRPTR_bf             0, 23, 16
#define     NFP_PCIE_DMA_TOQSTS0_DMA_LO_WRPTR_msk            (0xff)
#define     NFP_PCIE_DMA_TOQSTS0_DMA_LO_WRPTR_shf            (16)
#define   NFP_PCIE_DMA_TOQSTS0_DIS_ARI_ERROR                 (1 << 13)
#define     NFP_PCIE_DMA_TOQSTS0_DIS_ARI_ERROR_bf            0, 13, 13
#define     NFP_PCIE_DMA_TOQSTS0_DIS_ARI_ERROR_msk           (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_DIS_ARI_ERROR_bit           (13)
#define   NFP_PCIE_DMA_TOQSTS0_RESET_DMA                     (1 << 12)
#define     NFP_PCIE_DMA_TOQSTS0_RESET_DMA_bf                0, 12, 12
#define     NFP_PCIE_DMA_TOQSTS0_RESET_DMA_msk               (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_RESET_DMA_bit               (12)
#define   NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR                (1 << 11)
#define     NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_bf           0, 11, 11
#define     NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_msk          (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_bit          (11)
#define   NFP_PCIE_DMA_TOQSTS0_DIS_DMADESC_MULTIBIT_ERR      (1 << 10)
#define     NFP_PCIE_DMA_TOQSTS0_DIS_DMADESC_MULTIBIT_ERR_bf 0, 10, 10
#define     NFP_PCIE_DMA_TOQSTS0_DIS_DMADESC_MULTIBIT_ERR_msk (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_DIS_DMADESC_MULTIBIT_ERR_bit (10)
#define   NFP_PCIE_DMA_TOQSTS0_PF_ERROR_HALT                 (1 << 9)
#define     NFP_PCIE_DMA_TOQSTS0_PF_ERROR_HALT_bf            0, 9, 9
#define     NFP_PCIE_DMA_TOQSTS0_PF_ERROR_HALT_msk           (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_PF_ERROR_HALT_bit           (9)
#define   NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_HALT           (1 << 8)
#define     NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_HALT_bf      0, 8, 8
#define     NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_HALT_msk     (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_MULTIBIT_ERROR_HALT_bit     (8)
#define   NFP_PCIE_DMA_TOQSTS0_DMA_ERROR(x)                  (((x) & 3) << 6)
#define   NFP_PCIE_DMA_TOQSTS0_DMA_ERROR_of(x)               (((x) >> 6) & 3)
#define     NFP_PCIE_DMA_TOQSTS0_DMA_ERROR_bf                0, 7, 6
#define     NFP_PCIE_DMA_TOQSTS0_DMA_ERROR_msk               (0x3)
#define     NFP_PCIE_DMA_TOQSTS0_DMA_ERROR_shf               (6)
#define   NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW(x)             (((x) & 3) << 4)
#define   NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_of(x)          (((x) >> 4) & 3)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_NoOvfl       (0)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_LowOvfl      (1)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_MedOvfl      (2)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_HighOvfl     (3)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_bf           0, 5, 4
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_msk          (0x3)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_OVERFLOW_shf          (4)
#define   NFP_PCIE_DMA_TOQSTS0_QUEUE_HALT_FULL               (1 << 3)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_HALT_FULL_bf          0, 3, 3
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_HALT_FULL_msk         (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_QUEUE_HALT_FULL_bit         (3)
#define   NFP_PCIE_DMA_TOQSTS0_HI_QUEUE_STOP                 (1 << 2)
#define     NFP_PCIE_DMA_TOQSTS0_HI_QUEUE_STOP_bf            0, 2, 2
#define     NFP_PCIE_DMA_TOQSTS0_HI_QUEUE_STOP_msk           (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_HI_QUEUE_STOP_bit           (2)
#define   NFP_PCIE_DMA_TOQSTS0_MED_QUEUE_STOP                (1 << 1)
#define     NFP_PCIE_DMA_TOQSTS0_MED_QUEUE_STOP_bf           0, 1, 1
#define     NFP_PCIE_DMA_TOQSTS0_MED_QUEUE_STOP_msk          (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_MED_QUEUE_STOP_bit          (1)
#define   NFP_PCIE_DMA_TOQSTS0_LO_QUEUE_STOP                 (1 << 0)
#define     NFP_PCIE_DMA_TOQSTS0_LO_QUEUE_STOP_bf            0, 0, 0
#define     NFP_PCIE_DMA_TOQSTS0_LO_QUEUE_STOP_msk           (0x1)
#define     NFP_PCIE_DMA_TOQSTS0_LO_QUEUE_STOP_bit           (0)


/*
 * Register: DMAQueueStatus1
 *   [31:24]   DmaHiQueAvail
 *   [23:16]   DmaHiQueWrPtr
 *   [15:8]    DmaMedQueAvail
 *   [7:0]     DmaMedQueWrPtr
 *
 * Name(s):
 * <base>.DMAController.DMAQStatToPCI1 <base>.DMAController.DMAQStatFrmPCI1
 */
#define NFP_PCIE_DMA_QSTS1_TOPCI                           0x8000e4
#define NFP_PCIE_DMA_QSTS1_FROMPCI                         0x8000ec
#define   NFP_PCIE_DMA_QSTS1_DMA_HI_AVAIL(x)                 (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_QSTS1_DMA_HI_AVAIL_of(x)              (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_HI_AVAIL_bf               0, 31, 24
#define     NFP_PCIE_DMA_QSTS1_DMA_HI_AVAIL_msk              (0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_HI_AVAIL_shf              (24)
#define   NFP_PCIE_DMA_QSTS1_DMA_HI_WRPTR(x)                 (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_QSTS1_DMA_HI_WRPTR_of(x)              (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_HI_WRPTR_bf               0, 23, 16
#define     NFP_PCIE_DMA_QSTS1_DMA_HI_WRPTR_msk              (0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_HI_WRPTR_shf              (16)
#define   NFP_PCIE_DMA_QSTS1_DMA_MED_AVAIL(x)                (((x) & 0xff) << 8)
#define   NFP_PCIE_DMA_QSTS1_DMA_MED_AVAIL_of(x)             (((x) >> 8) & 0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_MED_AVAIL_bf              0, 15, 8
#define     NFP_PCIE_DMA_QSTS1_DMA_MED_AVAIL_msk             (0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_MED_AVAIL_shf             (8)
#define   NFP_PCIE_DMA_QSTS1_DMA_MED_WRPTR(x)                (((x) & 0xff) << 0)
#define   NFP_PCIE_DMA_QSTS1_DMA_MED_WRPTR_of(x)             (((x) >> 0) & 0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_MED_WRPTR_bf              0, 7, 0
#define     NFP_PCIE_DMA_QSTS1_DMA_MED_WRPTR_msk             (0xff)
#define     NFP_PCIE_DMA_QSTS1_DMA_MED_WRPTR_shf             (0)


/*
 * Register: DMAFrmQueueStatus0
 *   [31:24]   DmaLoQueAvail
 *   [23:16]   DmaLoQueWrPtr
 *   [15:14]   PktModeStgError
 *   [13]      DisAriError
 *   [12]      ResetDMA
 *   [11]      MultiBitError
 *   [10]      DisDmaDescMultiBitErr
 *   [9]       HaltOnPfDmaError
 *   [8]       HaltOnRdMultiBitError
 *   [7:6]     DmaError
 *   [5:4]     QueueOverflow
 *   [3]       HaltOnFull
 *   [2]       HighQueueStop
 *   [1]       MediumQueueStop
 *   [0]       LowQueueStop
 *
 * Name(s):
 * <base>.DMAController.DMAQStatFrmPCI0
 */
#define NFP_PCIE_DMA_QSTS0_FROMPCI                         0x8000e8
#define   NFP_PCIE_DMA_FRMQSTS0_DMA_LO_AVAIL(x)              (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_FRMQSTS0_DMA_LO_AVAIL_of(x)           (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_LO_AVAIL_bf            0, 31, 24
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_LO_AVAIL_msk           (0xff)
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_LO_AVAIL_shf           (24)
#define   NFP_PCIE_DMA_FRMQSTS0_DMA_LO_WRPTR(x)              (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_FRMQSTS0_DMA_LO_WRPTR_of(x)           (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_LO_WRPTR_bf            0, 23, 16
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_LO_WRPTR_msk           (0xff)
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_LO_WRPTR_shf           (16)
#define   NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR(x)        (((x) & 3) << 14)
#define   NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_of(x)     (((x) >> 14) & 3)
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_NoPmStgErr (0)
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_LowPmStgErr (1)
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_MedPmStgErr (2)
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_HighPmStgErr (3)
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_bf      0, 15, 14
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_msk     (0x3)
#define     NFP_PCIE_DMA_FRMQSTS0_PKT_MODE_STG_ERROR_shf     (14)
#define   NFP_PCIE_DMA_FRMQSTS0_DIS_ARI_ERROR                (1 << 13)
#define     NFP_PCIE_DMA_FRMQSTS0_DIS_ARI_ERROR_bf           0, 13, 13
#define     NFP_PCIE_DMA_FRMQSTS0_DIS_ARI_ERROR_msk          (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_DIS_ARI_ERROR_bit          (13)
#define   NFP_PCIE_DMA_FRMQSTS0_RESET_DMA                    (1 << 12)
#define     NFP_PCIE_DMA_FRMQSTS0_RESET_DMA_bf               0, 12, 12
#define     NFP_PCIE_DMA_FRMQSTS0_RESET_DMA_msk              (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_RESET_DMA_bit              (12)
#define   NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR               (1 << 11)
#define     NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_bf          0, 11, 11
#define     NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_msk         (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_bit         (11)
#define   NFP_PCIE_DMA_FRMQSTS0_DIS_DMADESC_MULTIBIT_ERR     (1 << 10)
#define     NFP_PCIE_DMA_FRMQSTS0_DIS_DMADESC_MULTIBIT_ERR_bf 0, 10, 10
#define     NFP_PCIE_DMA_FRMQSTS0_DIS_DMADESC_MULTIBIT_ERR_msk (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_DIS_DMADESC_MULTIBIT_ERR_bit (10)
#define   NFP_PCIE_DMA_FRMQSTS0_PF_ERROR_HALT                (1 << 9)
#define     NFP_PCIE_DMA_FRMQSTS0_PF_ERROR_HALT_bf           0, 9, 9
#define     NFP_PCIE_DMA_FRMQSTS0_PF_ERROR_HALT_msk          (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_PF_ERROR_HALT_bit          (9)
#define   NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_HALT          (1 << 8)
#define     NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_HALT_bf     0, 8, 8
#define     NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_HALT_msk    (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_MULTIBIT_ERROR_HALT_bit    (8)
#define   NFP_PCIE_DMA_FRMQSTS0_DMA_ERROR(x)                 (((x) & 3) << 6)
#define   NFP_PCIE_DMA_FRMQSTS0_DMA_ERROR_of(x)              (((x) >> 6) & 3)
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_ERROR_bf               0, 7, 6
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_ERROR_msk              (0x3)
#define     NFP_PCIE_DMA_FRMQSTS0_DMA_ERROR_shf              (6)
#define   NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW(x)            (((x) & 3) << 4)
#define   NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_of(x)         (((x) >> 4) & 3)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_NoOvfl      (0)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_LowOvfl     (1)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_MedOvfl     (2)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_HighOvfl    (3)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_bf          0, 5, 4
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_msk         (0x3)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_OVERFLOW_shf         (4)
#define   NFP_PCIE_DMA_FRMQSTS0_QUEUE_HALT_FULL              (1 << 3)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_HALT_FULL_bf         0, 3, 3
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_HALT_FULL_msk        (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_QUEUE_HALT_FULL_bit        (3)
#define   NFP_PCIE_DMA_FRMQSTS0_HI_QUEUE_STOP                (1 << 2)
#define     NFP_PCIE_DMA_FRMQSTS0_HI_QUEUE_STOP_bf           0, 2, 2
#define     NFP_PCIE_DMA_FRMQSTS0_HI_QUEUE_STOP_msk          (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_HI_QUEUE_STOP_bit          (2)
#define   NFP_PCIE_DMA_FRMQSTS0_MED_QUEUE_STOP               (1 << 1)
#define     NFP_PCIE_DMA_FRMQSTS0_MED_QUEUE_STOP_bf          0, 1, 1
#define     NFP_PCIE_DMA_FRMQSTS0_MED_QUEUE_STOP_msk         (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_MED_QUEUE_STOP_bit         (1)
#define   NFP_PCIE_DMA_FRMQSTS0_LO_QUEUE_STOP                (1 << 0)
#define     NFP_PCIE_DMA_FRMQSTS0_LO_QUEUE_STOP_bf           0, 0, 0
#define     NFP_PCIE_DMA_FRMQSTS0_LO_QUEUE_STOP_msk          (0x1)
#define     NFP_PCIE_DMA_FRMQSTS0_LO_QUEUE_STOP_bit          (0)


/*
 * Register: DMACntrlCfg1
 *   [31:28]   DmaFrmCppRate
 *   [27:24]   DmaToPcieRate
 *   [23:20]   DmaToCppRate
 *   [19:16]   DmaFrmPcieRate
 *   [15:12]   DmaFrmPcieIssueLoad
 *   [0]       DmaRateLimitSelect
 *
 * Name(s):
 * <base>.DMAController.DMACntrlConfig1
 */
#define NFP_PCIE_DMA_CTRL_CFG1                             0x8000f8
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_CPP_RATE(x)         (((x) & 0xf) << 28)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_CPP_RATE_of(x)      (((x) >> 28) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_CPP_RATE_bf       0, 31, 28
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_CPP_RATE_msk      (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_CPP_RATE_shf      (28)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_PCIE_RATE(x)         (((x) & 0xf) << 24)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_PCIE_RATE_of(x)      (((x) >> 24) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_PCIE_RATE_bf       0, 27, 24
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_PCIE_RATE_msk      (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_PCIE_RATE_shf      (24)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_CPP_RATE(x)          (((x) & 0xf) << 20)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_CPP_RATE_of(x)       (((x) >> 20) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_CPP_RATE_bf        0, 23, 20
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_CPP_RATE_msk       (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_TO_CPP_RATE_shf       (20)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_RATE(x)        (((x) & 0xf) << 16)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_RATE_of(x)     (((x) >> 16) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_RATE_bf      0, 19, 16
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_RATE_msk     (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_RATE_shf     (16)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_ISSUE_LOAD(x)  (((x) & 0xf) << 12)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_ISSUE_LOAD_of(x) (((x) >> 12) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_ISSUE_LOAD_bf 0, 15, 12
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_ISSUE_LOAD_msk (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_FRM_PCIE_ISSUE_LOAD_shf (12)
#define   NFP_PCIE_DMA_CTRL_CFG1_DMA_RATE_LIMIT_SELECT       (1 << 0)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_RATE_LIMIT_SELECT_BWRateLimit (0)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_RATE_LIMIT_SELECT_IssueRateLimit (1)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_RATE_LIMIT_SELECT_bf  0, 0, 0
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_RATE_LIMIT_SELECT_msk (0x1)
#define     NFP_PCIE_DMA_CTRL_CFG1_DMA_RATE_LIMIT_SELECT_bit (0)


/*
 * Register: DMACntrlCfg2
 *   [31:28]   DmaToCppTh
 *   [27:24]   DmaToPcieTh
 *   [23:20]   DmaFrmCppTh
 *   [19:16]   DmaFrmPcieTh
 *   [14:12]   DmaRate
 *   [11:9]    DmaToCppCredit
 *   [8:6]     DmaToPcieCredit
 *   [5:3]     DmaFrmCppCredit
 *   [2:0]     DmaFrmPcieCredit
 *
 * Name(s):
 * <base>.DMAController.DMACntrlConfig2
 */
#define NFP_PCIE_DMA_CTRL_CFG2                             0x8000fc
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_TH(x)            (((x) & 0xf) << 28)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_TH_of(x)         (((x) >> 28) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_TH_bf          0, 31, 28
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_TH_msk         (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_TH_shf         (28)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_TH(x)           (((x) & 0xf) << 24)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_TH_of(x)        (((x) >> 24) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_TH_bf         0, 27, 24
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_TH_msk        (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_TH_shf        (24)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_TH(x)           (((x) & 0xf) << 20)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_TH_of(x)        (((x) >> 20) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_TH_bf         0, 23, 20
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_TH_msk        (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_TH_shf        (20)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_TH(x)          (((x) & 0xf) << 16)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_TH_of(x)       (((x) >> 16) & 0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_TH_bf        0, 19, 16
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_TH_msk       (0xf)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_TH_shf       (16)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_RATE(x)                 (((x) & 7) << 12)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_RATE_of(x)              (((x) >> 12) & 7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_RATE_bf               0, 14, 12
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_RATE_msk              (0x7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_RATE_shf              (12)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_CREDIT(x)        (((x) & 7) << 9)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_CREDIT_of(x)     (((x) >> 9) & 7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_CREDIT_bf      0, 11, 9
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_CREDIT_msk     (0x7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_CPP_CREDIT_shf     (9)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_CREDIT(x)       (((x) & 7) << 6)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_CREDIT_of(x)    (((x) >> 6) & 7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_CREDIT_bf     0, 8, 6
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_CREDIT_msk    (0x7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_TO_PCIE_CREDIT_shf    (6)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_CREDIT(x)       (((x) & 7) << 3)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_CREDIT_of(x)    (((x) >> 3) & 7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_CREDIT_bf     0, 5, 3
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_CREDIT_msk    (0x7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_CPP_CREDIT_shf    (3)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_CREDIT(x)      (((x) & 7) << 0)
#define   NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_CREDIT_of(x)   (((x) >> 0) & 7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_CREDIT_bf    0, 2, 0
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_CREDIT_msk   (0x7)
#define     NFP_PCIE_DMA_CTRL_CFG2_DMA_FRM_PCIE_CREDIT_shf   (0)


/*
 * Register: DMADescrTPHConfig
 *   [26]      TphCtrlEnaOdd
 *   [25:24]   TphOdd
 *   [23:16]   TphStOdd
 *   [10]      TphCtrlEnaEven
 *   [9:8]     TphEven
 *   [7:0]     TphStEven
 *
 * Name(s):
 * <base>.DMAController.DMADescrTPHConfig0...
 */
#define NFP_PCIE_DMA_DMA_STAG(x)                           (0x800100 + ((x) * 0x4))
#define   NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_ODD                  (1 << 26)
#define     NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_ODD_bf             0, 26, 26
#define     NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_ODD_msk            (0x1)
#define     NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_ODD_bit            (26)
#define   NFP_PCIE_DMA_TPH_TPH_ODD(x)                        (((x) & 3) << 24)
#define   NFP_PCIE_DMA_TPH_TPH_ODD_of(x)                     (((x) >> 24) & 3)
#define     NFP_PCIE_DMA_TPH_TPH_ODD_bf                      0, 25, 24
#define     NFP_PCIE_DMA_TPH_TPH_ODD_msk                     (0x3)
#define     NFP_PCIE_DMA_TPH_TPH_ODD_shf                     (24)
#define   NFP_PCIE_DMA_TPH_TPH_ST_ODD(x)                     (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_TPH_TPH_ST_ODD_of(x)                  (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_TPH_TPH_ST_ODD_bf                   0, 23, 16
#define     NFP_PCIE_DMA_TPH_TPH_ST_ODD_msk                  (0xff)
#define     NFP_PCIE_DMA_TPH_TPH_ST_ODD_shf                  (16)
#define   NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_EVEN                 (1 << 10)
#define     NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_EVEN_bf            0, 10, 10
#define     NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_EVEN_msk           (0x1)
#define     NFP_PCIE_DMA_TPH_TPH_CTRL_ENA_EVEN_bit           (10)
#define   NFP_PCIE_DMA_TPH_TPH_EVEN(x)                       (((x) & 3) << 8)
#define   NFP_PCIE_DMA_TPH_TPH_EVEN_of(x)                    (((x) >> 8) & 3)
#define     NFP_PCIE_DMA_TPH_TPH_EVEN_bf                     0, 9, 8
#define     NFP_PCIE_DMA_TPH_TPH_EVEN_msk                    (0x3)
#define     NFP_PCIE_DMA_TPH_TPH_EVEN_shf                    (8)
#define   NFP_PCIE_DMA_TPH_TPH_ST_EVEN(x)                    (((x) & 0xff) << 0)
#define   NFP_PCIE_DMA_TPH_TPH_ST_EVEN_of(x)                 (((x) >> 0) & 0xff)
#define     NFP_PCIE_DMA_TPH_TPH_ST_EVEN_bf                  0, 7, 0
#define     NFP_PCIE_DMA_TPH_TPH_ST_EVEN_msk                 (0xff)
#define     NFP_PCIE_DMA_TPH_TPH_ST_EVEN_shf                 (0)


/*
 * Register: DMAAllocCtrl
 *   [22]      muPtrOffsetCtrl
 *   [21:20]   AllocLookaheadNeg256bCredit
 *   [19:18]   AllocLookaheadNegBufCredit
 *   [17]      AllocLookaheadEna
 *   [16]      PacketColorEnable
 *   [15]      ResetDMAState
 *   [14]      PollRespNoWaitEna
 *   [12]      NonDepWrBeatsReadEna
 *   [11]      DisBdRamErr
 *   [10]      DisRxPushLastErr
 *   [9]       DisRxAllocInErr
 *   [8]       DisRxBlqWrInErr
 *   [7:5]     PCIeNum
 *   [4]       CtmPollEna
 *   [3:2]     CtmPollIntvl
 *   [1:0]     PollCmdIssueRate
 *
 * Name(s):
 * <base>.DMAController.DMAAllocCtrl
 */
#define NFP_PCIE_DMA_DMA_ALLOC_CTRL                        0x800120
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_MU_PTR_OFFSET_CTRL     (1 << 22)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_MU_PTR_OFFSET_CTRL_SplitOffset (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_MU_PTR_OFFSET_CTRL_NoOffset (0x400000)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_MU_PTR_OFFSET_CTRL_bf 0, 22, 22
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_MU_PTR_OFFSET_CTRL_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_MU_PTR_OFFSET_CTRL_bit (22)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT(x) (((x) & 3) << 20)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_of(x) (((x) >> 20) & 3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_16 (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_32 (1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_48 (2)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_64 (3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_bf 0, 21, 20
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_msk (0x3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG256B_CREDIT_shf (20)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT(x) (((x) & 3) << 18)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT_of(x) (((x) >> 18) & 3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT_NONE (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT__1 (1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT__2 (2)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT__3 (3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT_bf 0, 19, 18
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT_msk (0x3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_NEG_BUF_CREDIT_shf (18)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_ENA    (1 << 17)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_ENA_bf 0, 17, 17
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_ENA_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_ALLOC_LOOKAHEAD_ENA_bit (17)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_PACKET_COLOR_ENABLE    (1 << 16)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_PACKET_COLOR_ENABLE_bf 0, 16, 16
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_PACKET_COLOR_ENABLE_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_PACKET_COLOR_ENABLE_bit (16)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_RESET_DMA_STATE        (1 << 15)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_RESET_DMA_STATE_bf   0, 15, 15
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_RESET_DMA_STATE_msk  (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_RESET_DMA_STATE_bit  (15)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_RESP_NO_WAIT_ENA  (1 << 14)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_RESP_NO_WAIT_ENA_bf 0, 14, 14
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_RESP_NO_WAIT_ENA_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_RESP_NO_WAIT_ENA_bit (14)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_NON_DEPWR_BEAT_READS_ENA (1 << 12)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_NON_DEPWR_BEAT_READS_ENA_bf 0, 12, 12
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_NON_DEPWR_BEAT_READS_ENA_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_NON_DEPWR_BEAT_READS_ENA_bit (12)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_BDRAM_ERR          (1 << 11)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_BDRAM_ERR_Enable (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_BDRAM_ERR_Disable (0x800)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_BDRAM_ERR_bf     0, 11, 11
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_BDRAM_ERR_msk    (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_BDRAM_ERR_bit    (11)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXPUSH_LAST_ERR    (1 << 10)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXPUSH_LAST_ERR_Enable (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXPUSH_LAST_ERR_Disable (0x400)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXPUSH_LAST_ERR_bf 0, 10, 10
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXPUSH_LAST_ERR_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXPUSH_LAST_ERR_bit (10)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXALLOC_IN_ERR     (1 << 9)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXALLOC_IN_ERR_Enable (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXALLOC_IN_ERR_Disable (0x200)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXALLOC_IN_ERR_bf 0, 9, 9
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXALLOC_IN_ERR_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXALLOC_IN_ERR_bit (9)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXBLQWR_IN_ERR     (1 << 8)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXBLQWR_IN_ERR_Enable (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXBLQWR_IN_ERR_Disable (0x100)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXBLQWR_IN_ERR_bf 0, 8, 8
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXBLQWR_IN_ERR_msk (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_DIS_RXBLQWR_IN_ERR_bit (8)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_PCIE_NUM(x)            (((x) & 7) << 5)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_PCIE_NUM_of(x)         (((x) >> 5) & 7)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_PCIE_NUM_bf          0, 7, 5
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_PCIE_NUM_msk         (0x7)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_PCIE_NUM_shf         (5)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_ENA           (1 << 4)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_ENA_Disable (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_ENA_Enable  (0x10)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_ENA_bf      0, 4, 4
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_ENA_msk     (0x1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_ENA_bit     (4)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL(x)      (((x) & 3) << 2)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_of(x)   (((x) >> 2) & 3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_128   (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_256   (1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_512   (2)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_1024  (3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_bf    0, 3, 2
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_msk   (0x3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_CTM_POLL_INTVL_shf   (2)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE(x) (((x) & 3) << 0)
#define   NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_of(x) (((x) >> 0) & 3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_4 (0)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_8 (1)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_12 (2)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_16 (3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_bf 0, 1, 0
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_msk (0x3)
#define     NFP_PCIE_DMA_DMA_ALLOC_CTRL_POLL_CMD_ISSUE_RATE_shf (0)


/*
 * Register: NbiDmaBlqEvent
 *   [22]      ReducedThresh
 *   [21]      ClrRunningEventCount
 *   [20]      DisBLQEventFifoFullAssert
 *   [19:18]   BLQEventThreshold3
 *   [17:16]   BLQEventThreshold2
 *   [15:14]   BLQEventThreshold1
 *   [13:12]   BLQEventThreshold0
 *   [7:4]     BLQEventNotFullEnable
 *   [3:0]     BLQEventStatusEnable
 *
 * Name(s):
 * <base>.DMAController.DMABlqEvent
 */
#define NFP_PCIE_DMA_DMA_BLQ_EVENT                         0x800124
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_REDUCED_THRESH          (1 << 22)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_REDUCED_THRESH_bf     0, 22, 22
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_REDUCED_THRESH_msk    (0x1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_REDUCED_THRESH_bit    (22)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_CLR_RUNNING_EVT_CNT     (1 << 21)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_CLR_RUNNING_EVT_CNT_bf 0, 21, 21
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_CLR_RUNNING_EVT_CNT_msk (0x1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_CLR_RUNNING_EVT_CNT_bit (21)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_DIS_BLQ_EVENT_FIFO_FULL_ASSERT (1 << 20)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_DIS_BLQ_EVENT_FIFO_FULL_ASSERT_bf 0, 20, 20
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_DIS_BLQ_EVENT_FIFO_FULL_ASSERT_msk (0x1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_DIS_BLQ_EVENT_FIFO_FULL_ASSERT_bit (20)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3(x)  (((x) & 3) << 18)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_of(x) (((x) >> 18) & 3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_16_or_4 (0)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_32_or_8 (1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_64_or_16 (2)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_128_or_32 (3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_bf 0, 19, 18
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_msk (0x3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD3_shf (18)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2(x)  (((x) & 3) << 16)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_of(x) (((x) >> 16) & 3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_16_or_4 (0)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_32_or_8 (1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_64_or_16 (2)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_128_or_32 (3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_bf 0, 17, 16
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_msk (0x3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD2_shf (16)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1(x)  (((x) & 3) << 14)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_of(x) (((x) >> 14) & 3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_16_or_4 (0)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_32_or_8 (1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_64_or_16 (2)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_128_or_32 (3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_bf 0, 15, 14
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_msk (0x3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD1_shf (14)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0(x)  (((x) & 3) << 12)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_of(x) (((x) >> 12) & 3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_16_or_4 (0)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_32_or_8 (1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_64_or_16 (2)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_128_or_32 (3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_bf 0, 13, 12
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_msk (0x3)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQEVENT_THRESHOLD0_shf (12)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE(x) (((x) & 0xf) << 4)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE_of(x) (((x) >> 4) & 0xf)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE_Disable (0)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE_Enable (1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE_bf 0, 7, 4
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE_msk (0xf)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_NOT_FULL_ENABLE_shf (4)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE(x) (((x) & 0xf) << 0)
#define   NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE_of(x) (((x) >> 0) & 0xf)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE_Disable (0)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE_Enable (1)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE_bf 0, 3, 0
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE_msk (0xf)
#define     NFP_PCIE_DMA_DMA_BLQ_EVENT_BLQ_EVENT_STATUS_ENABLE_shf (0)


/*
 * Register: NbiDmaBpeChainEnd
 *   [31:0]    BpeChainEnd
 *
 * Name(s):
 * <base>.DMAController.DMABpeChainEnd
 */
#define NFP_PCIE_DMA_BPE_CHAIN_END                         0x800128
#define   NFP_PCIE_DMA_BPE_CHAIN_END_BPE_CHAIN_END(x)        (((x) & 0xffffffff) << 0)
#define   NFP_PCIE_DMA_BPE_CHAIN_END_BPE_CHAIN_END_of(x)     (((x) >> 0) & 0xffffffff)
#define     NFP_PCIE_DMA_BPE_CHAIN_END_BPE_CHAIN_END_bf      0, 31, 0
#define     NFP_PCIE_DMA_BPE_CHAIN_END_BPE_CHAIN_END_msk     (0xffffffff)
#define     NFP_PCIE_DMA_BPE_CHAIN_END_BPE_CHAIN_END_shf     (0)


/*
 * Register: DMABPCfg
 *   [24]      BlqBypassEna
 *   [23]      BPRsvd
 *   [22:19]   CtmBufPad
 *   [18]      CtmBufPadEna
 *   [17:15]   CtmOffsetMsb
 *   [13]      CtmOffset
 *   [12:11]   PriBList
 *   [10:9]    SecBList
 *   [8:5]     SplitLength
 *   [4:0]     BpeHead
 *
 * Name(s):
 * <base>.DMAController.DMABP0Cfg...
 */
#define NFP_PCIE_DMA_DMA_BP_CFG(x)                         (0x800130 + ((x) * 0x4))
#define   NFP_PCIE_DMA_DMA_BP_CFG_BLQ_BYPASS_ENA             (1 << 24)
#define     NFP_PCIE_DMA_DMA_BP_CFG_BLQ_BYPASS_ENA_bf        0, 24, 24
#define     NFP_PCIE_DMA_DMA_BP_CFG_BLQ_BYPASS_ENA_msk       (0x1)
#define     NFP_PCIE_DMA_DMA_BP_CFG_BLQ_BYPASS_ENA_bit       (24)
#define   NFP_PCIE_DMA_DMA_BP_CFG_BP_RSVD                    (1 << 23)
#define     NFP_PCIE_DMA_DMA_BP_CFG_BP_RSVD_bf               0, 23, 23
#define     NFP_PCIE_DMA_DMA_BP_CFG_BP_RSVD_msk              (0x1)
#define     NFP_PCIE_DMA_DMA_BP_CFG_BP_RSVD_bit              (23)
#define   NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD(x)             (((x) & 0xf) << 19)
#define   NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_of(x)          (((x) >> 19) & 0xf)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_bf           0, 22, 19
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_msk          (0xf)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_shf          (19)
#define   NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_ENA            (1 << 18)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_ENA_bf       0, 18, 18
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_ENA_msk      (0x1)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_BUF_PAD_ENA_bit      (18)
#define   NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_MSB(x)          (((x) & 7) << 15)
#define   NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_MSB_of(x)       (((x) >> 15) & 7)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_MSB_bf        0, 17, 15
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_MSB_msk       (0x7)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_MSB_shf       (15)
#define   NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET                 (1 << 13)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_bf            0, 13, 13
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_msk           (0x1)
#define     NFP_PCIE_DMA_DMA_BP_CFG_CTM_OFFSET_bit           (13)
#define   NFP_PCIE_DMA_DMA_BP_CFG_PRI_BP_LIST(x)             (((x) & 3) << 11)
#define   NFP_PCIE_DMA_DMA_BP_CFG_PRI_BP_LIST_of(x)          (((x) >> 11) & 3)
#define     NFP_PCIE_DMA_DMA_BP_CFG_PRI_BP_LIST_bf           0, 12, 11
#define     NFP_PCIE_DMA_DMA_BP_CFG_PRI_BP_LIST_msk          (0x3)
#define     NFP_PCIE_DMA_DMA_BP_CFG_PRI_BP_LIST_shf          (11)
#define   NFP_PCIE_DMA_DMA_BP_CFG_SEC_BP_LIST(x)             (((x) & 3) << 9)
#define   NFP_PCIE_DMA_DMA_BP_CFG_SEC_BP_LIST_of(x)          (((x) >> 9) & 3)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SEC_BP_LIST_bf           0, 10, 9
#define     NFP_PCIE_DMA_DMA_BP_CFG_SEC_BP_LIST_msk          (0x3)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SEC_BP_LIST_shf          (9)
#define   NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH(x)            (((x) & 0xf) << 5)
#define   NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_of(x)         (((x) >> 5) & 0xf)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_256         (0)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_512         (1)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_1K          (2)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_2K          (3)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_4K          (4)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_8K          (5)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_16K         (6)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_RSVD7       (7)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_6K          (8)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_10K         (9)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_12K         (0xa)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_14K         (0xb)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_RSVD12      (0xc)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_RSVD13      (0xd)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_RSVD14      (0xe)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_RSVD15      (0xf)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_bf          0, 8, 5
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_msk         (0xf)
#define     NFP_PCIE_DMA_DMA_BP_CFG_SPLIT_LENGTH_shf         (5)
#define   NFP_PCIE_DMA_DMA_BP_CFG_BPE_HEAD(x)                (((x) & 0x1f) << 0)
#define   NFP_PCIE_DMA_DMA_BP_CFG_BPE_HEAD_of(x)             (((x) >> 0) & 0x1f)
#define     NFP_PCIE_DMA_DMA_BP_CFG_BPE_HEAD_bf              0, 4, 0
#define     NFP_PCIE_DMA_DMA_BP_CFG_BPE_HEAD_msk             (0x1f)
#define     NFP_PCIE_DMA_DMA_BP_CFG_BPE_HEAD_shf             (0)


/*
 * Register: PcieBLQueCtrl0Lo
 *   [31:24]   BLEntryCntLo
 *   [22:12]   BLHdPtr
 *   [10:0]    BLTlPtr
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl0Lo
 */
#define NFP_PCIE_DMA_BLQ_CTRL0_LO                          0x800150
#define   NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_ENTRY_CNT(x)          (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_ENTRY_CNT_of(x)       (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_ENTRY_CNT_bf        0, 31, 24
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_ENTRY_CNT_msk       (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_ENTRY_CNT_shf       (24)
#define   NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_HEAD_PTR(x)           (((x) & 0x7ff) << 12)
#define   NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_HEAD_PTR_of(x)        (((x) >> 12) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_HEAD_PTR_bf         0, 22, 12
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_HEAD_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_HEAD_PTR_shf        (12)
#define   NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_TAIL_PTR(x)           (((x) & 0x7ff) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_TAIL_PTR_of(x)        (((x) >> 0) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_TAIL_PTR_bf         0, 10, 0
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_TAIL_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_LO_BL_TAIL_PTR_shf        (0)


/*
 * Register: PcieBLQueCtrl0Hi
 *   [23:16]   BLQEventFullCnt
 *   [10:8]    BDFifoEntryCnt
 *   [7]       BLQFull
 *   [6]       BLQEmpty
 *   [5:4]     BLQSize
 *   [2:0]     BLEntryCntHi
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl0Hi
 */
#define NFP_PCIE_DMA_BLQ_CTRL0_HI                          0x800154
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EVENT_FULL_CNT(x)    (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EVENT_FULL_CNT_of(x) (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EVENT_FULL_CNT_bf  0, 23, 16
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EVENT_FULL_CNT_msk (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EVENT_FULL_CNT_shf (16)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BD_FIFO_ENTRY_CNT(x)     (((x) & 7) << 8)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BD_FIFO_ENTRY_CNT_of(x)  (((x) >> 8) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BD_FIFO_ENTRY_CNT_bf   0, 10, 8
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BD_FIFO_ENTRY_CNT_msk  (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BD_FIFO_ENTRY_CNT_shf  (8)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_FULL                 (1 << 7)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_FULL_bf            0, 7, 7
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_FULL_msk           (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_FULL_bit           (7)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EMPTY                (1 << 6)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EMPTY_bf           0, 6, 6
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EMPTY_msk          (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_EMPTY_bit          (6)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE(x)              (((x) & 3) << 4)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_of(x)           (((x) >> 4) & 3)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_256           (0)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_512           (1)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_1K            (2)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_2K            (3)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_bf            0, 5, 4
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_msk           (0x3)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BLQ_SIZE_shf           (4)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BL_ENTRY_CNT(x)          (((x) & 7) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL0_HI_BL_ENTRY_CNT_of(x)       (((x) >> 0) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BL_ENTRY_CNT_bf        0, 2, 0
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BL_ENTRY_CNT_msk       (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL0_HI_BL_ENTRY_CNT_shf       (0)


/*
 * Register: PcieBLQueCtrl1Lo
 *   [31:24]   BLEntryCntLo
 *   [22:12]   BLHdPtr
 *   [10:0]    BLTlPtr
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl1Lo
 */
#define NFP_PCIE_DMA_BLQ_CTRL1_LO                          0x800158
#define   NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_ENTRY_CNT_LO(x)       (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_ENTRY_CNT_LO_of(x)    (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_ENTRY_CNT_LO_bf     0, 31, 24
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_ENTRY_CNT_LO_msk    (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_ENTRY_CNT_LO_shf    (24)
#define   NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_HEAD_PTR(x)           (((x) & 0x7ff) << 12)
#define   NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_HEAD_PTR_of(x)        (((x) >> 12) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_HEAD_PTR_bf         0, 22, 12
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_HEAD_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_HEAD_PTR_shf        (12)
#define   NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_TAIL_PTR(x)           (((x) & 0x7ff) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_TAIL_PTR_of(x)        (((x) >> 0) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_TAIL_PTR_bf         0, 10, 0
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_TAIL_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_LO_BL_TAIL_PTR_shf        (0)


/*
 * Register: PcieBLQueCtrl1Hi
 *   [23:16]   BLQEventFullCnt
 *   [10:8]    BDFifoEntryCnt
 *   [7]       BLQFull
 *   [6]       BLQEmpty
 *   [5:4]     BLQSize
 *   [2:0]     BLEntryCntHi
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl1Hi
 */
#define NFP_PCIE_DMA_BLQ_CTRL1_HI                          0x80015c
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EVENT_FULL_CNT(x)    (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EVENT_FULL_CNT_of(x) (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EVENT_FULL_CNT_bf  0, 23, 16
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EVENT_FULL_CNT_msk (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EVENT_FULL_CNT_shf (16)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BD_FIFO_ENTRY_CNT(x)     (((x) & 7) << 8)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BD_FIFO_ENTRY_CNT_of(x)  (((x) >> 8) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BD_FIFO_ENTRY_CNT_bf   0, 10, 8
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BD_FIFO_ENTRY_CNT_msk  (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BD_FIFO_ENTRY_CNT_shf  (8)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_FULL                 (1 << 7)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_FULL_bf            0, 7, 7
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_FULL_msk           (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_FULL_bit           (7)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EMPTY                (1 << 6)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EMPTY_bf           0, 6, 6
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EMPTY_msk          (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_EMPTY_bit          (6)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE(x)              (((x) & 3) << 4)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_of(x)           (((x) >> 4) & 3)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_256           (0)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_512           (1)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_1K            (2)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_2K            (3)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_bf            0, 5, 4
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_msk           (0x3)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BLQ_SIZE_shf           (4)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BL_ENTRY_CNT_HI(x)       (((x) & 7) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL1_HI_BL_ENTRY_CNT_HI_of(x)    (((x) >> 0) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BL_ENTRY_CNT_HI_bf     0, 2, 0
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BL_ENTRY_CNT_HI_msk    (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL1_HI_BL_ENTRY_CNT_HI_shf    (0)


/*
 * Register: PcieBLQueCtrl2Lo
 *   [31:24]   BLEntryCntLo
 *   [22:12]   BLHdPtr
 *   [10:0]    BLTlPtr
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl2Lo
 */
#define NFP_PCIE_DMA_BLQ_CTRL2_LO                          0x800160
#define   NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_ENTRY_CNT_LO(x)       (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_ENTRY_CNT_LO_of(x)    (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_ENTRY_CNT_LO_bf     0, 31, 24
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_ENTRY_CNT_LO_msk    (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_ENTRY_CNT_LO_shf    (24)
#define   NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_HEAD_PTR(x)           (((x) & 0x7ff) << 12)
#define   NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_HEAD_PTR_of(x)        (((x) >> 12) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_HEAD_PTR_bf         0, 22, 12
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_HEAD_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_HEAD_PTR_shf        (12)
#define   NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_TAIL_PTR(x)           (((x) & 0x7ff) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_TAIL_PTR_of(x)        (((x) >> 0) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_TAIL_PTR_bf         0, 10, 0
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_TAIL_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_LO_BL_TAIL_PTR_shf        (0)


/*
 * Register: PcieBLQueCtrl2Hi
 *   [23:16]   BLQEventFullCnt
 *   [10:8]    BDFifoEntryCnt
 *   [7]       BLQFull
 *   [6]       BLQEmpty
 *   [5:4]     BLQSize
 *   [2:0]     BLEntryCntHi
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl2Hi
 */
#define NFP_PCIE_DMA_BLQ_CTRL2_HI                          0x800164
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EVENT_FULL_CNT(x)    (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EVENT_FULL_CNT_of(x) (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EVENT_FULL_CNT_bf  0, 23, 16
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EVENT_FULL_CNT_msk (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EVENT_FULL_CNT_shf (16)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BD_FIFO_ENTRY_CNT(x)     (((x) & 7) << 8)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BD_FIFO_ENTRY_CNT_of(x)  (((x) >> 8) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BD_FIFO_ENTRY_CNT_bf   0, 10, 8
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BD_FIFO_ENTRY_CNT_msk  (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BD_FIFO_ENTRY_CNT_shf  (8)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_FULL                 (1 << 7)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_FULL_bf            0, 7, 7
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_FULL_msk           (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_FULL_bit           (7)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EMPTY                (1 << 6)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EMPTY_bf           0, 6, 6
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EMPTY_msk          (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_EMPTY_bit          (6)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE(x)              (((x) & 3) << 4)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_of(x)           (((x) >> 4) & 3)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_256           (0)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_512           (1)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_1K            (2)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_2K            (3)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_bf            0, 5, 4
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_msk           (0x3)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BLQ_SIZE_shf           (4)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BL_ENTRY_CNT_HI(x)       (((x) & 7) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL2_HI_BL_ENTRY_CNT_HI_of(x)    (((x) >> 0) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BL_ENTRY_CNT_HI_bf     0, 2, 0
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BL_ENTRY_CNT_HI_msk    (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL2_HI_BL_ENTRY_CNT_HI_shf    (0)


/*
 * Register: PcieBLQueCtrl3Lo
 *   [31:24]   BLEntryCntLo
 *   [22:12]   BLHdPtr
 *   [10:0]    BLTlPtr
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl3Lo
 */
#define NFP_PCIE_DMA_BLQ_CTRL3_LO                          0x800168
#define   NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_ENTRY_CNT_LO(x)       (((x) & 0xff) << 24)
#define   NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_ENTRY_CNT_LO_of(x)    (((x) >> 24) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_ENTRY_CNT_LO_bf     0, 31, 24
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_ENTRY_CNT_LO_msk    (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_ENTRY_CNT_LO_shf    (24)
#define   NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_HEAD_PTR(x)           (((x) & 0x7ff) << 12)
#define   NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_HEAD_PTR_of(x)        (((x) >> 12) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_HEAD_PTR_bf         0, 22, 12
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_HEAD_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_HEAD_PTR_shf        (12)
#define   NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_TAIL_PTR(x)           (((x) & 0x7ff) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_TAIL_PTR_of(x)        (((x) >> 0) & 0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_TAIL_PTR_bf         0, 10, 0
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_TAIL_PTR_msk        (0x7ff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_LO_BL_TAIL_PTR_shf        (0)


/*
 * Register: PcieBLQueCtrl3Hi
 *   [23:16]   BLQEventFullCnt
 *   [10:8]    BDFifoEntryCnt
 *   [7]       BLQFull
 *   [6]       BLQEmpty
 *   [5:4]     BLQSize
 *   [2:0]     BLEntryCntHi
 *
 * Name(s):
 * <base>.DMAController.BLQueCtrl3Hi
 */
#define NFP_PCIE_DMA_BLQ_CTRL3_HI                          0x80016c
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EVENT_FULL_CNT(x)    (((x) & 0xff) << 16)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EVENT_FULL_CNT_of(x) (((x) >> 16) & 0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EVENT_FULL_CNT_bf  0, 23, 16
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EVENT_FULL_CNT_msk (0xff)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EVENT_FULL_CNT_shf (16)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BD_FIFO_ENTRY_CNT(x)     (((x) & 7) << 8)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BD_FIFO_ENTRY_CNT_of(x)  (((x) >> 8) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BD_FIFO_ENTRY_CNT_bf   0, 10, 8
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BD_FIFO_ENTRY_CNT_msk  (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BD_FIFO_ENTRY_CNT_shf  (8)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_FULL                 (1 << 7)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_FULL_bf            0, 7, 7
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_FULL_msk           (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_FULL_bit           (7)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EMPTY                (1 << 6)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EMPTY_bf           0, 6, 6
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EMPTY_msk          (0x1)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_EMPTY_bit          (6)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE(x)              (((x) & 3) << 4)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_of(x)           (((x) >> 4) & 3)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_256           (0)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_512           (1)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_1K            (2)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_2K            (3)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_bf            0, 5, 4
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_msk           (0x3)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BLQ_SIZE_shf           (4)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BL_ENTRY_CNT_HI(x)       (((x) & 7) << 0)
#define   NFP_PCIE_DMA_BLQ_CTRL3_HI_BL_ENTRY_CNT_HI_of(x)    (((x) >> 0) & 7)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BL_ENTRY_CNT_HI_bf     0, 2, 0
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BL_ENTRY_CNT_HI_msk    (0x7)
#define     NFP_PCIE_DMA_BLQ_CTRL3_HI_BL_ENTRY_CNT_HI_shf    (0)


/*
 * Register: BlqNullMuPtr
 *   [28:0]    BlqNullMuPtr
 *
 * Name(s):
 * <base>.DMAController.BlqNullMuPtr
 */
#define NFP_PCIE_DMA_BLQ_NULL_MU_PTR                       0x800174
#define   NFP_PCIE_DMA_BLQ_NULL_MU_PTR_BLQ_NULL_MU_PTR(x)    (((x) & 0x1fffffff) << 0)
#define   NFP_PCIE_DMA_BLQ_NULL_MU_PTR_BLQ_NULL_MU_PTR_of(x) (((x) >> 0) & 0x1fffffff)
#define     NFP_PCIE_DMA_BLQ_NULL_MU_PTR_BLQ_NULL_MU_PTR_bf  0, 28, 0
#define     NFP_PCIE_DMA_BLQ_NULL_MU_PTR_BLQ_NULL_MU_PTR_msk (0x1fffffff)
#define     NFP_PCIE_DMA_BLQ_NULL_MU_PTR_BLQ_NULL_MU_PTR_shf (0)


/*
 * Register: PcieDmaRsvd
 *
 * Name(s):
 * <base>.DMAController.PcieDmaRsvd0...
 */
#define NFP_PCIE_DMA_PCIE_DMA_RSVD(x)                      (0x800178 + ((x) * 0x4))


/*
 * Register: NbiDmaBpeCfg
 *   [31:27]   BpeNum
 *   [26:21]   Ctm
 *   [20:10]   PktCredit
 *   [9:0]     BufCredit
 *
 * Name(s):
 * <base>.DMAController.DMABpe0Cfg...
 */
#define NFP_PCIE_DMA_DMA_BPE_CFG(x)                        (0x800180 + ((x) * 0x4))
#define   NFP_PCIE_DMA_DMA_BPE_CFG_BPE_NUM(x)                (((x) & 0x1f) << 27)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_BPE_NUM_of(x)             (((x) >> 27) & 0x1f)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_BPE_NUM_bf              0, 31, 27
#define     NFP_PCIE_DMA_DMA_BPE_CFG_BPE_NUM_msk             (0x1f)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_BPE_NUM_shf             (27)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_CTM(x)                    (((x) & 0x3f) << 21)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_CTM_of(x)                 (((x) >> 21) & 0x3f)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_CTM_bf                  0, 26, 21
#define     NFP_PCIE_DMA_DMA_BPE_CFG_CTM_msk                 (0x3f)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_CTM_shf                 (21)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_PKT_CREDIT(x)             (((x) & 0x7ff) << 10)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_PKT_CREDIT_of(x)          (((x) >> 10) & 0x7ff)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_PKT_CREDIT_bf           0, 20, 10
#define     NFP_PCIE_DMA_DMA_BPE_CFG_PKT_CREDIT_msk          (0x7ff)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_PKT_CREDIT_shf          (10)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_BUF_CREDIT(x)             (((x) & 0x3ff) << 0)
#define   NFP_PCIE_DMA_DMA_BPE_CFG_BUF_CREDIT_of(x)          (((x) >> 0) & 0x3ff)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_BUF_CREDIT_bf           0, 9, 0
#define     NFP_PCIE_DMA_DMA_BPE_CFG_BUF_CREDIT_msk          (0x3ff)
#define     NFP_PCIE_DMA_DMA_BPE_CFG_BUF_CREDIT_shf          (0)

/* DMAPMHeader: <base>.DMAController.DMAPmHeader0... */
#define NFP_PCIE_DMA_DMA_PM_HEADER(x)                      (0x800200 + ((x) * 0x8))

/*
 * Register: AbortStatus
 *   [31:23]   PckNumOdd
 *   [22:17]   CtmOdd
 *   [16]      ValidOdd
 *   [15:7]    PckNumEven
 *   [6:1]     CtmEven
 *   [0]       ValidEven
 *
 * Name(s):
 * <base>.DMAController.AbortStatus0...
 */
#define NFP_PCIE_DMA_ABORT_STATUS(x)                       (0x800280 + ((x) * 0x4))
#define   NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_ODD(x)           (((x) & 0x1ff) << 23)
#define   NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_ODD_of(x)        (((x) >> 23) & 0x1ff)
#define     NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_ODD_bf         0, 31, 23
#define     NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_ODD_msk        (0x1ff)
#define     NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_ODD_shf        (23)
#define   NFP_PCIE_DMA_ABORT_STATUS_CTM_ODD(x)               (((x) & 0x3f) << 17)
#define   NFP_PCIE_DMA_ABORT_STATUS_CTM_ODD_of(x)            (((x) >> 17) & 0x3f)
#define     NFP_PCIE_DMA_ABORT_STATUS_CTM_ODD_bf             0, 22, 17
#define     NFP_PCIE_DMA_ABORT_STATUS_CTM_ODD_msk            (0x3f)
#define     NFP_PCIE_DMA_ABORT_STATUS_CTM_ODD_shf            (17)
#define   NFP_PCIE_DMA_ABORT_STATUS_VALID_ODD                (1 << 16)
#define     NFP_PCIE_DMA_ABORT_STATUS_VALID_ODD_bf           0, 16, 16
#define     NFP_PCIE_DMA_ABORT_STATUS_VALID_ODD_msk          (0x1)
#define     NFP_PCIE_DMA_ABORT_STATUS_VALID_ODD_bit          (16)
#define   NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_EVEN(x)          (((x) & 0x1ff) << 7)
#define   NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_EVEN_of(x)       (((x) >> 7) & 0x1ff)
#define     NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_EVEN_bf        0, 15, 7
#define     NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_EVEN_msk       (0x1ff)
#define     NFP_PCIE_DMA_ABORT_STATUS_PCK_NUM_EVEN_shf       (7)
#define   NFP_PCIE_DMA_ABORT_STATUS_CTM_EVEN(x)              (((x) & 0x3f) << 1)
#define   NFP_PCIE_DMA_ABORT_STATUS_CTM_EVEN_of(x)           (((x) >> 1) & 0x3f)
#define     NFP_PCIE_DMA_ABORT_STATUS_CTM_EVEN_bf            0, 6, 1
#define     NFP_PCIE_DMA_ABORT_STATUS_CTM_EVEN_msk           (0x3f)
#define     NFP_PCIE_DMA_ABORT_STATUS_CTM_EVEN_shf           (1)
#define   NFP_PCIE_DMA_ABORT_STATUS_VALID_EVEN               (1 << 0)
#define     NFP_PCIE_DMA_ABORT_STATUS_VALID_EVEN_bf          0, 0, 0
#define     NFP_PCIE_DMA_ABORT_STATUS_VALID_EVEN_msk         (0x1)
#define     NFP_PCIE_DMA_ABORT_STATUS_VALID_EVEN_bit         (0)


/*
 * Register: NbiDmaBPCtmCrThresh
 *   [29:20]   Threshold2
 *   [19:10]   Threshold1
 *   [9:0]     Threshold0
 *
 * Name(s):
 * <base>.DMAController.DMABP0CtmCrThresh...
 */
#define NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH(x)                (0x8002a0 + ((x) * 0x4))
#define   NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD2(x)     (((x) & 0x3ff) << 20)
#define   NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD2_of(x)  (((x) >> 20) & 0x3ff)
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD2_bf   0, 29, 20
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD2_msk  (0x3ff)
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD2_shf  (20)
#define   NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD1(x)     (((x) & 0x3ff) << 10)
#define   NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD1_of(x)  (((x) >> 10) & 0x3ff)
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD1_bf   0, 19, 10
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD1_msk  (0x3ff)
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD1_shf  (10)
#define   NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD0(x)     (((x) & 0x3ff) << 0)
#define   NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD0_of(x)  (((x) >> 0) & 0x3ff)
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD0_bf   0, 9, 0
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD0_msk  (0x3ff)
#define     NFP_PCIE_DMA_DMA_BP_CTMCR_THRESH_THRESHOLD0_shf  (0)


/*
 * Register: DMATotalCreditCnt
 *   [31:16]   TotalPktCredit
 *   [15:0]    TotalBufCredit
 *
 * Name(s):
 * <base>.DMAController.DMATotalCreditCnt
 */
#define NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT                  0x8002c0
#define   NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_PKT_CREDIT(x) (((x) & 0xffff) << 16)
#define   NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_PKT_CREDIT_of(x) (((x) >> 16) & 0xffff)
#define     NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_PKT_CREDIT_bf 0, 31, 16
#define     NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_PKT_CREDIT_msk (0xffff)
#define     NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_PKT_CREDIT_shf (16)
#define   NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_BUF_CREDIT(x) (((x) & 0xffff) << 0)
#define   NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_BUF_CREDIT_of(x) (((x) >> 0) & 0xffff)
#define     NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_BUF_CREDIT_bf 0, 15, 0
#define     NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_BUF_CREDIT_msk (0xffff)
#define     NFP_PCIE_DMA_DMA_TOTAL_CREDIT_CNT_TOTAL_BUF_CREDIT_shf (0)


/*
 * Register: DMAChksSumEna
 *   [15:0]    DMAChksumEna
 *
 * Name(s):
 * <base>.DMAController.DMAChksSumEna
 */
#define NFP_PCIE_DMA_DMA_CHKSUM_ENA                        0x8002c4
#define   NFP_PCIE_DMA_DMA_CHKSUM_ENA_DMA_CHKSUM_ENA(x)      (((x) & 0xffff) << 0)
#define   NFP_PCIE_DMA_DMA_CHKSUM_ENA_DMA_CHKSUM_ENA_of(x)   (((x) >> 0) & 0xffff)
#define     NFP_PCIE_DMA_DMA_CHKSUM_ENA_DMA_CHKSUM_ENA_bf    0, 15, 0
#define     NFP_PCIE_DMA_DMA_CHKSUM_ENA_DMA_CHKSUM_ENA_msk   (0xffff)
#define     NFP_PCIE_DMA_DMA_CHKSUM_ENA_DMA_CHKSUM_ENA_shf   (0)



/*
 * Register: PcieToCppExpansionBar
 *   [31:29]   MapType
 *   [28:27]   LengthSelect
 *   [26:23]   Target_BaseAddress
 *   [22:21]   Token_BaseAddress
 *   [20:16]   Action_BaseAddress
 *   [15:0]    BaseAddress
 *
 * Name(s):
 * <base>.PCIeToCppExpansionBAR_0_0...
 */
#define NFP_PCIE_BARCFG_PF_P2C_BAR_SUB(_bar, _sub)         (0x0000 + ((_bar) * 0x20) + ((_sub) * 0x4))
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE(x)         (((x) & 7) << 29)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_of(x)      (((x) >> 29) & 7)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_FIXED    (0)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_BULK     (1)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_TARGET   (2)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_GENERAL  (3)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_EXPLICIT0 (4)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_ROCE     (5)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_TRAP     (6)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_RSVD     (7)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_bf       0, 31, 29
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_msk      (0x7)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_MAP_TYPE_shf      (29)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN(x)              (((x) & 3) << 27)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_of(x)           (((x) >> 27) & 3)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_32BIT         (0)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_64BIT         (1)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_RSVD          (2)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_0BYTE         (3)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_bf            0, 28, 27
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_msk           (0x3)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_LEN_shf           (27)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TARGET(x)           (((x) & 0xf) << 23)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TARGET_of(x)        (((x) >> 23) & 0xf)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TARGET_bf         0, 26, 23
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TARGET_msk        (0xf)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TARGET_shf        (23)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TOKEN(x)            (((x) & 3) << 21)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TOKEN_of(x)         (((x) >> 21) & 3)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TOKEN_bf          0, 22, 21
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TOKEN_msk         (0x3)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_TOKEN_shf         (21)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_ACTADDR(x)          (((x) & 0x1f) << 16)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_ACTADDR_of(x)       (((x) >> 16) & 0x1f)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_ACTADDR_bf        0, 20, 16
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_ACTADDR_msk       (0x1f)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_ACTADDR_shf       (16)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_BASE(x)             (((x) & 0xffff) << 0)
#define   NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_BASE_of(x)          (((x) >> 0) & 0xffff)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_BASE_bf           0, 15, 0
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_BASE_msk          (0xffff)
#define     NFP_PCIE_BARCFG_PF_P2C_BAR_SUB_BASE_shf          (0)


/*
 * Register: PcieToCppExpansionBarVf
 *   [31:30]   LengthSelect
 *   [29:26]   Target
 *   [25:24]   Token
 *   [23:22]   MapType
 *   [21:0]    BaseAddress
 *
 * Name(s):
 * <base>.PCIeToCppExpansionBARVf_0_0...
 */
#define NFP_PCIE_BARCFG_VF_P2C_BAR_SUB(_bar, y)            (0x0060 + ((_bar) * 0x8) + ((y) * 0x4))
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN(x)              (((x) & 3) << 30)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_of(x)           (((x) >> 30) & 3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_32BIT         (0)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_64BIT         (1)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_RSVD          (2)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_0BYTE         (3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_bf            0, 31, 30
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_msk           (0x3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_LEN_shf           (30)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TARGET(x)           (((x) & 0xf) << 26)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TARGET_of(x)        (((x) >> 26) & 0xf)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TARGET_bf         0, 29, 26
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TARGET_msk        (0xf)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TARGET_shf        (26)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TOKEN(x)            (((x) & 3) << 24)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TOKEN_of(x)         (((x) >> 24) & 3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TOKEN_bf          0, 25, 24
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TOKEN_msk         (0x3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_TOKEN_shf         (24)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE(x)         (((x) & 3) << 22)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_of(x)      (((x) >> 22) & 3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_MEM      (0)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_ROCE     (1)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_QCTL     (2)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_TRAP     (3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_bf       0, 23, 22
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_msk      (0x3)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_MAP_TYPE_shf      (22)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_BASE(x)             (((x) & 0x3fffff) << 0)
#define   NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_BASE_of(x)          (((x) >> 0) & 0x3fffff)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_BASE_bf           0, 21, 0
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_BASE_msk          (0x3fffff)
#define     NFP_PCIE_BARCFG_VF_P2C_BAR_SUB_BASE_shf          (0)


/*
 * Register: PcieExplicitCmdBar0
 *   [31:30]   SignalType
 *   [29:28]   Token
 *   [23:0]    Address
 *
 * Name(s):
 * <base>.PCIeExplicitCmd_0.PCIeExplicitCmdBAR0...
 */
#define NFP_PCIE_BARCFG_P2CX0(_set)                        (0x0080 + ((_set) * 0x10))
#define   NFP_PCIE_BARCFG_P2CX0_SIGTYPE(x)                   (((x) & 3) << 30)
#define   NFP_PCIE_BARCFG_P2CX0_SIGTYPE_of(x)                (((x) >> 30) & 3)
#define     NFP_PCIE_BARCFG_P2CX0_SIGTYPE_bf                 0, 31, 30
#define     NFP_PCIE_BARCFG_P2CX0_SIGTYPE_msk                (0x3)
#define     NFP_PCIE_BARCFG_P2CX0_SIGTYPE_shf                (30)
#define   NFP_PCIE_BARCFG_P2CX0_TOK(x)                       (((x) & 3) << 28)
#define   NFP_PCIE_BARCFG_P2CX0_TOK_of(x)                    (((x) >> 28) & 3)
#define     NFP_PCIE_BARCFG_P2CX0_TOK_bf                     0, 29, 28
#define     NFP_PCIE_BARCFG_P2CX0_TOK_msk                    (0x3)
#define     NFP_PCIE_BARCFG_P2CX0_TOK_shf                    (28)
#define   NFP_PCIE_BARCFG_P2CX0_ADDR(x)                      (((x) & 0xffffff) << 0)
#define   NFP_PCIE_BARCFG_P2CX0_ADDR_of(x)                   (((x) >> 0) & 0xffffff)
#define     NFP_PCIE_BARCFG_P2CX0_ADDR_bf                    0, 23, 0
#define     NFP_PCIE_BARCFG_P2CX0_ADDR_msk                   (0xffffff)
#define     NFP_PCIE_BARCFG_P2CX0_ADDR_shf                   (0)


/*
 * Register: PcieExplicitCmdBar1
 *   [30:24]   SignalRef
 *   [23:14]   DataMaster
 *   [13:0]    DataRef
 *
 * Name(s):
 * <base>.PCIeExplicitCmd_0.PCIeExplicitCmdBAR1...
 */
#define NFP_PCIE_BARCFG_P2CX1(_set)                        (0x0084 + ((_set) * 0x10))
#define   NFP_PCIE_BARCFG_P2CX1_SIGNAL_REF(x)                (((x) & 0x7f) << 24)
#define   NFP_PCIE_BARCFG_P2CX1_SIGNAL_REF_of(x)             (((x) >> 24) & 0x7f)
#define     NFP_PCIE_BARCFG_P2CX1_SIGNAL_REF_bf              0, 30, 24
#define     NFP_PCIE_BARCFG_P2CX1_SIGNAL_REF_msk             (0x7f)
#define     NFP_PCIE_BARCFG_P2CX1_SIGNAL_REF_shf             (24)
#define   NFP_PCIE_BARCFG_P2CX1_DATA_MASTER(x)               (((x) & 0x3ff) << 14)
#define   NFP_PCIE_BARCFG_P2CX1_DATA_MASTER_of(x)            (((x) >> 14) & 0x3ff)
#define     NFP_PCIE_BARCFG_P2CX1_DATA_MASTER_bf             0, 23, 14
#define     NFP_PCIE_BARCFG_P2CX1_DATA_MASTER_msk            (0x3ff)
#define     NFP_PCIE_BARCFG_P2CX1_DATA_MASTER_shf            (14)
#define   NFP_PCIE_BARCFG_P2CX1_DATA_REF(x)                  (((x) & 0x3fff) << 0)
#define   NFP_PCIE_BARCFG_P2CX1_DATA_REF_of(x)               (((x) >> 0) & 0x3fff)
#define     NFP_PCIE_BARCFG_P2CX1_DATA_REF_bf                0, 13, 0
#define     NFP_PCIE_BARCFG_P2CX1_DATA_REF_msk               (0x3fff)
#define     NFP_PCIE_BARCFG_P2CX1_DATA_REF_shf               (0)


/*
 * Register: PcieExplicitCmdBar2
 *   [31:28]   Target
 *   [27:23]   Action
 *   [22:18]   Length
 *   [17:10]   ByteMask
 *   [9:0]     SignalMaster
 *
 * Name(s):
 * <base>.PCIeExplicitCmd_0.PCIeExplicitCmdBAR2...
 */
#define NFP_PCIE_BARCFG_P2CX2(_set)                        (0x0088 + ((_set) * 0x10))
#define   NFP_PCIE_BARCFG_P2CX2_TGT(x)                       (((x) & 0xf) << 28)
#define   NFP_PCIE_BARCFG_P2CX2_TGT_of(x)                    (((x) >> 28) & 0xf)
#define     NFP_PCIE_BARCFG_P2CX2_TGT_bf                     0, 31, 28
#define     NFP_PCIE_BARCFG_P2CX2_TGT_msk                    (0xf)
#define     NFP_PCIE_BARCFG_P2CX2_TGT_shf                    (28)
#define   NFP_PCIE_BARCFG_P2CX2_ACT(x)                       (((x) & 0x1f) << 23)
#define   NFP_PCIE_BARCFG_P2CX2_ACT_of(x)                    (((x) >> 23) & 0x1f)
#define     NFP_PCIE_BARCFG_P2CX2_ACT_bf                     0, 27, 23
#define     NFP_PCIE_BARCFG_P2CX2_ACT_msk                    (0x1f)
#define     NFP_PCIE_BARCFG_P2CX2_ACT_shf                    (23)
#define   NFP_PCIE_BARCFG_P2CX2_LEN(x)                       (((x) & 0x1f) << 18)
#define   NFP_PCIE_BARCFG_P2CX2_LEN_of(x)                    (((x) >> 18) & 0x1f)
#define     NFP_PCIE_BARCFG_P2CX2_LEN_bf                     0, 22, 18
#define     NFP_PCIE_BARCFG_P2CX2_LEN_msk                    (0x1f)
#define     NFP_PCIE_BARCFG_P2CX2_LEN_shf                    (18)
#define   NFP_PCIE_BARCFG_P2CX2_BYTE_MASK(x)                 (((x) & 0xff) << 10)
#define   NFP_PCIE_BARCFG_P2CX2_BYTE_MASK_of(x)              (((x) >> 10) & 0xff)
#define     NFP_PCIE_BARCFG_P2CX2_BYTE_MASK_bf               0, 17, 10
#define     NFP_PCIE_BARCFG_P2CX2_BYTE_MASK_msk              (0xff)
#define     NFP_PCIE_BARCFG_P2CX2_BYTE_MASK_shf              (10)
#define   NFP_PCIE_BARCFG_P2CX2_SIGNAL_MASTER(x)             (((x) & 0x3ff) << 0)
#define   NFP_PCIE_BARCFG_P2CX2_SIGNAL_MASTER_of(x)          (((x) >> 0) & 0x3ff)
#define     NFP_PCIE_BARCFG_P2CX2_SIGNAL_MASTER_bf           0, 9, 0
#define     NFP_PCIE_BARCFG_P2CX2_SIGNAL_MASTER_msk          (0x3ff)
#define     NFP_PCIE_BARCFG_P2CX2_SIGNAL_MASTER_shf          (0)


/*
 * NFP 6XXX backward-compatible PCIe CSRs
 */
#define NFP_PCIE_DMA_TOPCI_HI                              NFP_PCIE_DMA_TOPCI_HI_EVEN0
#define NFP_PCIE_DMA_TOPCI_MED                             NFP_PCIE_DMA_TOPCI_MED_EVEN0
#define NFP_PCIE_DMA_TOPCI_LO                              NFP_PCIE_DMA_TOPCI_LO_EVEN0
#define NFP_PCIE_DMA_FROMPCI_HI                            NFP_PCIE_DMA_FROMPCI_HI_EVEN0
#define NFP_PCIE_DMA_FROMPCI_MED                           NFP_PCIE_DMA_FROMPCI_MED_EVEN0
#define NFP_PCIE_DMA_FROMPCI_LO                            NFP_PCIE_DMA_FROMPCI_LO_EVEN0
#define   NFP_PCIE_DMA_CMD_LW3                               (3)
#define   NFP_PCIE_DMA_CMD_LENGTH(x)                         (((x) & 0xfff) << 20)
#define   NFP_PCIE_DMA_CMD_LENGTH_of(x)                      (((x) >> 20) & 0xfff)
#define     NFP_PCIE_DMA_CMD_LENGTH_bf                       3, 31, 20
#define     NFP_PCIE_DMA_CMD_LENGTH_msk                      (0xfff)
#define     NFP_PCIE_DMA_CMD_LENGTH_shf                      (20)
#define   NFP_PCIE_DMA_CMD_RID(x)                            (((x) & 0xff) << 12)
#define   NFP_PCIE_DMA_CMD_RID_of(x)                         (((x) >> 12) & 0xff)
#define     NFP_PCIE_DMA_CMD_RID_bf                          3, 19, 12
#define     NFP_PCIE_DMA_CMD_RID_msk                         (0xff)
#define     NFP_PCIE_DMA_CMD_RID_shf                         (12)
#define   NFP_PCIE_DMA_CMD_RID_OVERRIDE                      (1 << 11)
#define     NFP_PCIE_DMA_CMD_RID_OVERRIDE_bf                 3, 11, 11
#define     NFP_PCIE_DMA_CMD_RID_OVERRIDE_msk                (0x1)
#define     NFP_PCIE_DMA_CMD_RID_OVERRIDE_bit                (11)
#define   NFP_PCIE_DMA_CMD_TRANS_CLASS(x)                    (((x) & 7) << 8)
#define   NFP_PCIE_DMA_CMD_TRANS_CLASS_of(x)                 (((x) >> 8) & 7)
#define     NFP_PCIE_DMA_CMD_TRANS_CLASS_bf                  3, 10, 8
#define     NFP_PCIE_DMA_CMD_TRANS_CLASS_msk                 (0x7)
#define     NFP_PCIE_DMA_CMD_TRANS_CLASS_shf                 (8)
#define   NFP_PCIE_DMA_CMD_PCIE_ADDR_HI(x)                   (((x) & 0xff) << 0)
#define   NFP_PCIE_DMA_CMD_PCIE_ADDR_HI_of(x)                (((x) >> 0) & 0xff)
#define     NFP_PCIE_DMA_CMD_PCIE_ADDR_HI_bf                 3, 7, 0
#define     NFP_PCIE_DMA_CMD_PCIE_ADDR_HI_msk                (0xff)
#define     NFP_PCIE_DMA_CMD_PCIE_ADDR_HI_shf                (0)
#define   NFP_PCIE_DMA_CMD_LW2                               (2)
#define   NFP_PCIE_DMA_CMD_PCIE_ADDR_LO(x)                   (((x) & 0xffffffff) << 0)
#define   NFP_PCIE_DMA_CMD_PCIE_ADDR_LO_of(x)                (((x) >> 0) & 0xffffffff)
#define     NFP_PCIE_DMA_CMD_PCIE_ADDR_LO_bf                 2, 31, 0
#define     NFP_PCIE_DMA_CMD_PCIE_ADDR_LO_msk                (0xffffffff)
#define     NFP_PCIE_DMA_CMD_PCIE_ADDR_LO_shf                (0)
#define   NFP_PCIE_DMA_CMD_LW1                               (1)
#define   NFP_PCIE_DMA_CMD_MODE_SEL(x)                       (((x) & 3) << 30)
#define   NFP_PCIE_DMA_CMD_MODE_SEL_of(x)                    (((x) >> 30) & 3)
#define     NFP_PCIE_DMA_CMD_MODE_SEL_0                      (0)
#define     NFP_PCIE_DMA_CMD_MODE_SEL_1                      (1)
#define     NFP_PCIE_DMA_CMD_MODE_SEL_2                      (2)
#define     NFP_PCIE_DMA_CMD_MODE_SEL_3                      (3)
#define     NFP_PCIE_DMA_CMD_MODE_SEL_bf                     1, 31, 30
#define     NFP_PCIE_DMA_CMD_MODE_SEL_msk                    (0x3)
#define     NFP_PCIE_DMA_CMD_MODE_SEL_shf                    (30)
#define   NFP_PCIE_DMA_CMD_DMA_MODE(x)                       (((x) & 0xffff) << 14)
#define   NFP_PCIE_DMA_CMD_DMA_MODE_of(x)                    (((x) >> 14) & 0xffff)
#define     NFP_PCIE_DMA_CMD_DMA_MODE_0                      (0)
#define     NFP_PCIE_DMA_CMD_DMA_MODE_1                      (1)
#define     NFP_PCIE_DMA_CMD_DMA_MODE_2                      (2)
#define     NFP_PCIE_DMA_CMD_DMA_MODE_3                      (3)
#define     NFP_PCIE_DMA_CMD_DMA_MODE_bf                     1, 29, 14
#define     NFP_PCIE_DMA_CMD_DMA_MODE_msk                    (0xffff)
#define     NFP_PCIE_DMA_CMD_DMA_MODE_shf                    (14)
#define   NFP_PCIE_DMA_CMD_CPP_TOKEN(x)                      (((x) & 3) << 12)
#define   NFP_PCIE_DMA_CMD_CPP_TOKEN_of(x)                   (((x) >> 12) & 3)
#define     NFP_PCIE_DMA_CMD_CPP_TOKEN_bf                    1, 13, 12
#define     NFP_PCIE_DMA_CMD_CPP_TOKEN_msk                   (0x3)
#define     NFP_PCIE_DMA_CMD_CPP_TOKEN_shf                   (12)
#define   NFP_PCIE_DMA_CMD_DMA_CFG_INDEX(x)                  (((x) & 0xf) << 8)
#define   NFP_PCIE_DMA_CMD_DMA_CFG_INDEX_of(x)               (((x) >> 8) & 0xf)
#define     NFP_PCIE_DMA_CMD_DMA_CFG_INDEX_bf                1, 11, 8
#define     NFP_PCIE_DMA_CMD_DMA_CFG_INDEX_msk               (0xf)
#define     NFP_PCIE_DMA_CMD_DMA_CFG_INDEX_shf               (8)
#define   NFP_PCIE_DMA_CMD_CPP_ADDR_HI(x)                    (((x) & 0xff) << 0)
#define   NFP_PCIE_DMA_CMD_CPP_ADDR_HI_of(x)                 (((x) >> 0) & 0xff)
#define     NFP_PCIE_DMA_CMD_CPP_ADDR_HI_bf                  1, 7, 0
#define     NFP_PCIE_DMA_CMD_CPP_ADDR_HI_msk                 (0xff)
#define     NFP_PCIE_DMA_CMD_CPP_ADDR_HI_shf                 (0)
#define   NFP_PCIE_DMA_CMD_LW0                               (0)
#define   NFP_PCIE_DMA_CMD_CPP_ADDR_LO(x)                    (((x) & 0xffffffff) << 0)
#define   NFP_PCIE_DMA_CMD_CPP_ADDR_LO_of(x)                 (((x) >> 0) & 0xffffffff)
#define     NFP_PCIE_DMA_CMD_CPP_ADDR_LO_bf                  0, 31, 0
#define     NFP_PCIE_DMA_CMD_CPP_ADDR_LO_msk                 (0xffffffff)
#define     NFP_PCIE_DMA_CMD_CPP_ADDR_LO_shf                 (0)


/*
 * PCIe register structures
 */
#if defined(__NFP_LANG_MICROC)

struct nfp_pcie_sram {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int word:32;
#           else
            unsigned int word:32;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_barcfg_c2p {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int type:2;
            unsigned int ari_enable:1;
            unsigned int ari:8;
            unsigned int addr:21;
#           else
            unsigned int addr:21;
            unsigned int ari:8;
            unsigned int ari_enable:1;
            unsigned int type:2;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_barcfg_c2p_ext {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_16:16;
            unsigned int cpp2pci_base_addr_ext:16;
#           else
            unsigned int cpp2pci_base_addr_ext:16;
            unsigned int __reserved_16:16;
#           endif
        };
        unsigned int __raw;
    };
};

        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_5:27;
            unsigned int msi_vec_num:5;
#           else
            unsigned int msi_vec_num:5;
            unsigned int __reserved_5:27;
#           endif
        } nfp_pcie_pcie_msi_sw_gen;
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_8:24;
            unsigned int msix_vec_num:8;
#           else
            unsigned int msix_vec_num:8;
            unsigned int __reserved_8:24;
#           endif
        } nfp_pcie_pcie_msix_sw_gen;

struct nfp_pcie_vf_cfg_lut {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int valid:1;
            unsigned int __reserved_30:1;
            unsigned int pf_num:2;
            unsigned int __reserved_25:3;
            unsigned int queue_cnt:9;
            unsigned int __reserved_9:7;
            unsigned int queue_base:9;
#           else
            unsigned int queue_base:9;
            unsigned int __reserved_9:7;
            unsigned int queue_cnt:9;
            unsigned int __reserved_25:3;
            unsigned int pf_num:2;
            unsigned int __reserved_30:1;
            unsigned int valid:1;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_cmd0 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int cpp_addr_lo:32;
#           else
            unsigned int cpp_addr_lo:32;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_cmd1 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int mode_sel:2;
            unsigned int dma_mode:16;
            unsigned int cpp_token:2;
            unsigned int dma_cfg_index:4;
            unsigned int cpp_addr_hi:8;
#           else
            unsigned int cpp_addr_hi:8;
            unsigned int dma_cfg_index:4;
            unsigned int cpp_token:2;
            unsigned int dma_mode:16;
            unsigned int mode_sel:2;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_cmd2 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int pcie_addr_lo:32;
#           else
            unsigned int pcie_addr_lo:32;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_cmd3 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int length:12;
            unsigned int rid:8;
            unsigned int rid_override:1;
            unsigned int trans_class:3;
            unsigned int pcie_addr_hi:8;
#           else
            unsigned int pcie_addr_hi:8;
            unsigned int trans_class:3;
            unsigned int rid_override:1;
            unsigned int rid:8;
            unsigned int length:12;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_cfg {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_31:1;
            unsigned int frm_pcie_cpp_rnd8b_odd:1;
            unsigned int free_ctm_packet_odd:1;
            unsigned int signal_only_odd:1;
            unsigned int end_pad_odd:2;
            unsigned int start_pad_odd:2;
            unsigned int id_based_order_odd:1;
            unsigned int relaxed_order_odd:1;
            unsigned int no_snoop_odd:1;
            unsigned int target_64_odd:1;
            unsigned int cpp_target_odd:4;
            unsigned int __reserved_15:1;
            unsigned int frm_pcie_cpp_rnd8b_even:1;
            unsigned int free_ctm_packet_even:1;
            unsigned int signal_only_even:1;
            unsigned int end_pad_even:2;
            unsigned int start_pad_even:2;
            unsigned int id_based_order_even:1;
            unsigned int relaxed_order_even:1;
            unsigned int no_snoop_even:1;
            unsigned int target_64_even:1;
            unsigned int cpp_target_even:4;
#           else
            unsigned int cpp_target_even:4;
            unsigned int target_64_even:1;
            unsigned int no_snoop_even:1;
            unsigned int relaxed_order_even:1;
            unsigned int id_based_order_even:1;
            unsigned int start_pad_even:2;
            unsigned int end_pad_even:2;
            unsigned int signal_only_even:1;
            unsigned int free_ctm_packet_even:1;
            unsigned int frm_pcie_cpp_rnd8b_even:1;
            unsigned int __reserved_15:1;
            unsigned int cpp_target_odd:4;
            unsigned int target_64_odd:1;
            unsigned int no_snoop_odd:1;
            unsigned int relaxed_order_odd:1;
            unsigned int id_based_order_odd:1;
            unsigned int start_pad_odd:2;
            unsigned int end_pad_odd:2;
            unsigned int signal_only_odd:1;
            unsigned int free_ctm_packet_odd:1;
            unsigned int frm_pcie_cpp_rnd8b_odd:1;
            unsigned int __reserved_31:1;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_toqsts0 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int dma_lo_avail:8;
            unsigned int dma_lo_wrptr:8;
            unsigned int __reserved_14:2;
            unsigned int dis_ari_error:1;
            unsigned int reset_dma:1;
            unsigned int multibit_error:1;
            unsigned int dis_dmadesc_multibit_err:1;
            unsigned int pf_error_halt:1;
            unsigned int multibit_error_halt:1;
            unsigned int dma_error:2;
            unsigned int queue_overflow:2;
            unsigned int queue_halt_full:1;
            unsigned int hi_queue_stop:1;
            unsigned int med_queue_stop:1;
            unsigned int lo_queue_stop:1;
#           else
            unsigned int lo_queue_stop:1;
            unsigned int med_queue_stop:1;
            unsigned int hi_queue_stop:1;
            unsigned int queue_halt_full:1;
            unsigned int queue_overflow:2;
            unsigned int dma_error:2;
            unsigned int multibit_error_halt:1;
            unsigned int pf_error_halt:1;
            unsigned int dis_dmadesc_multibit_err:1;
            unsigned int multibit_error:1;
            unsigned int reset_dma:1;
            unsigned int dis_ari_error:1;
            unsigned int __reserved_14:2;
            unsigned int dma_lo_wrptr:8;
            unsigned int dma_lo_avail:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_qsts1 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int dma_hi_avail:8;
            unsigned int dma_hi_wrptr:8;
            unsigned int dma_med_avail:8;
            unsigned int dma_med_wrptr:8;
#           else
            unsigned int dma_med_wrptr:8;
            unsigned int dma_med_avail:8;
            unsigned int dma_hi_wrptr:8;
            unsigned int dma_hi_avail:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_frmqsts0 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int dma_lo_avail:8;
            unsigned int dma_lo_wrptr:8;
            unsigned int pkt_mode_stg_error:2;
            unsigned int dis_ari_error:1;
            unsigned int reset_dma:1;
            unsigned int multibit_error:1;
            unsigned int dis_dmadesc_multibit_err:1;
            unsigned int pf_error_halt:1;
            unsigned int multibit_error_halt:1;
            unsigned int dma_error:2;
            unsigned int queue_overflow:2;
            unsigned int queue_halt_full:1;
            unsigned int hi_queue_stop:1;
            unsigned int med_queue_stop:1;
            unsigned int lo_queue_stop:1;
#           else
            unsigned int lo_queue_stop:1;
            unsigned int med_queue_stop:1;
            unsigned int hi_queue_stop:1;
            unsigned int queue_halt_full:1;
            unsigned int queue_overflow:2;
            unsigned int dma_error:2;
            unsigned int multibit_error_halt:1;
            unsigned int pf_error_halt:1;
            unsigned int dis_dmadesc_multibit_err:1;
            unsigned int multibit_error:1;
            unsigned int reset_dma:1;
            unsigned int dis_ari_error:1;
            unsigned int pkt_mode_stg_error:2;
            unsigned int dma_lo_wrptr:8;
            unsigned int dma_lo_avail:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_ctrl_cfg1 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int dma_frm_cpp_rate:4;
            unsigned int dma_to_pcie_rate:4;
            unsigned int dma_to_cpp_rate:4;
            unsigned int dma_frm_pcie_rate:4;
            unsigned int dma_frm_pcie_issue_load:4;
            unsigned int __reserved_1:11;
            unsigned int dma_rate_limit_select:1;
#           else
            unsigned int dma_rate_limit_select:1;
            unsigned int __reserved_1:11;
            unsigned int dma_frm_pcie_issue_load:4;
            unsigned int dma_frm_pcie_rate:4;
            unsigned int dma_to_cpp_rate:4;
            unsigned int dma_to_pcie_rate:4;
            unsigned int dma_frm_cpp_rate:4;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_ctrl_cfg2 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int dma_to_cpp_th:4;
            unsigned int dma_to_pcie_th:4;
            unsigned int dma_frm_cpp_th:4;
            unsigned int dma_frm_pcie_th:4;
            unsigned int __reserved_15:1;
            unsigned int dma_rate:3;
            unsigned int dma_to_cpp_credit:3;
            unsigned int dma_to_pcie_credit:3;
            unsigned int dma_frm_cpp_credit:3;
            unsigned int dma_frm_pcie_credit:3;
#           else
            unsigned int dma_frm_pcie_credit:3;
            unsigned int dma_frm_cpp_credit:3;
            unsigned int dma_to_pcie_credit:3;
            unsigned int dma_to_cpp_credit:3;
            unsigned int dma_rate:3;
            unsigned int __reserved_15:1;
            unsigned int dma_frm_pcie_th:4;
            unsigned int dma_frm_cpp_th:4;
            unsigned int dma_to_pcie_th:4;
            unsigned int dma_to_cpp_th:4;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_tph {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_27:5;
            unsigned int tph_ctrl_ena_odd:1;
            unsigned int tph_odd:2;
            unsigned int tph_st_odd:8;
            unsigned int __reserved_11:5;
            unsigned int tph_ctrl_ena_even:1;
            unsigned int tph_even:2;
            unsigned int tph_st_even:8;
#           else
            unsigned int tph_st_even:8;
            unsigned int tph_even:2;
            unsigned int tph_ctrl_ena_even:1;
            unsigned int __reserved_11:5;
            unsigned int tph_st_odd:8;
            unsigned int tph_odd:2;
            unsigned int tph_ctrl_ena_odd:1;
            unsigned int __reserved_27:5;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_alloc_ctrl {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_23:9;
            unsigned int mu_ptr_offset_ctrl:1;
            unsigned int alloc_lookahead_neg256b_credit:2;
            unsigned int alloc_lookahead_neg_buf_credit:2;
            unsigned int alloc_lookahead_ena:1;
            unsigned int packet_color_enable:1;
            unsigned int reset_dma_state:1;
            unsigned int poll_resp_no_wait_ena:1;
            unsigned int __reserved_13:1;
            unsigned int non_depwr_beat_reads_ena:1;
            unsigned int dis_bdram_err:1;
            unsigned int dis_rxpush_last_err:1;
            unsigned int dis_rxalloc_in_err:1;
            unsigned int dis_rxblqwr_in_err:1;
            unsigned int pcie_num:3;
            unsigned int ctm_poll_ena:1;
            unsigned int ctm_poll_intvl:2;
            unsigned int poll_cmd_issue_rate:2;
#           else
            unsigned int poll_cmd_issue_rate:2;
            unsigned int ctm_poll_intvl:2;
            unsigned int ctm_poll_ena:1;
            unsigned int pcie_num:3;
            unsigned int dis_rxblqwr_in_err:1;
            unsigned int dis_rxalloc_in_err:1;
            unsigned int dis_rxpush_last_err:1;
            unsigned int dis_bdram_err:1;
            unsigned int non_depwr_beat_reads_ena:1;
            unsigned int __reserved_13:1;
            unsigned int poll_resp_no_wait_ena:1;
            unsigned int reset_dma_state:1;
            unsigned int packet_color_enable:1;
            unsigned int alloc_lookahead_ena:1;
            unsigned int alloc_lookahead_neg_buf_credit:2;
            unsigned int alloc_lookahead_neg256b_credit:2;
            unsigned int mu_ptr_offset_ctrl:1;
            unsigned int __reserved_23:9;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_blq_event {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_23:9;
            unsigned int reduced_thresh:1;
            unsigned int clr_running_evt_cnt:1;
            unsigned int dis_blq_event_fifo_full_assert:1;
            unsigned int blqevent_threshold3:2;
            unsigned int blqevent_threshold2:2;
            unsigned int blqevent_threshold1:2;
            unsigned int blqevent_threshold0:2;
            unsigned int __reserved_8:4;
            unsigned int blq_event_not_full_enable:4;
            unsigned int blq_event_status_enable:4;
#           else
            unsigned int blq_event_status_enable:4;
            unsigned int blq_event_not_full_enable:4;
            unsigned int __reserved_8:4;
            unsigned int blqevent_threshold0:2;
            unsigned int blqevent_threshold1:2;
            unsigned int blqevent_threshold2:2;
            unsigned int blqevent_threshold3:2;
            unsigned int dis_blq_event_fifo_full_assert:1;
            unsigned int clr_running_evt_cnt:1;
            unsigned int reduced_thresh:1;
            unsigned int __reserved_23:9;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_bpe_chain_end {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int bpe_chain_end:32;
#           else
            unsigned int bpe_chain_end:32;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_bp_cfg {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_25:7;
            unsigned int blq_bypass_ena:1;
            unsigned int bp_rsvd:1;
            unsigned int ctm_buf_pad:4;
            unsigned int ctm_buf_pad_ena:1;
            unsigned int ctm_offset_msb:3;
            unsigned int __reserved_14:1;
            unsigned int ctm_offset:1;
            unsigned int pri_bp_list:2;
            unsigned int sec_bp_list:2;
            unsigned int split_length:4;
            unsigned int bpe_head:5;
#           else
            unsigned int bpe_head:5;
            unsigned int split_length:4;
            unsigned int sec_bp_list:2;
            unsigned int pri_bp_list:2;
            unsigned int ctm_offset:1;
            unsigned int __reserved_14:1;
            unsigned int ctm_offset_msb:3;
            unsigned int ctm_buf_pad_ena:1;
            unsigned int ctm_buf_pad:4;
            unsigned int bp_rsvd:1;
            unsigned int blq_bypass_ena:1;
            unsigned int __reserved_25:7;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl0_lo {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int bl_entry_cnt:8;
            unsigned int __reserved_23:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_tail_ptr:11;
#           else
            unsigned int bl_tail_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_23:1;
            unsigned int bl_entry_cnt:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl0_hi {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_24:8;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_11:5;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int blq_full:1;
            unsigned int blq_empty:1;
            unsigned int blq_size:2;
            unsigned int __reserved_3:1;
            unsigned int bl_entry_cnt:3;
#           else
            unsigned int bl_entry_cnt:3;
            unsigned int __reserved_3:1;
            unsigned int blq_size:2;
            unsigned int blq_empty:1;
            unsigned int blq_full:1;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int __reserved_11:5;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_24:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl1_lo {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int bl_entry_cnt_lo:8;
            unsigned int __reserved_23:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_tail_ptr:11;
#           else
            unsigned int bl_tail_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_23:1;
            unsigned int bl_entry_cnt_lo:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl1_hi {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_24:8;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_11:5;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int blq_full:1;
            unsigned int blq_empty:1;
            unsigned int blq_size:2;
            unsigned int __reserved_3:1;
            unsigned int bl_entry_cnt_hi:3;
#           else
            unsigned int bl_entry_cnt_hi:3;
            unsigned int __reserved_3:1;
            unsigned int blq_size:2;
            unsigned int blq_empty:1;
            unsigned int blq_full:1;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int __reserved_11:5;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_24:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl2_lo {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int bl_entry_cnt_lo:8;
            unsigned int __reserved_23:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_tail_ptr:11;
#           else
            unsigned int bl_tail_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_23:1;
            unsigned int bl_entry_cnt_lo:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl2_hi {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_24:8;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_11:5;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int blq_full:1;
            unsigned int blq_empty:1;
            unsigned int blq_size:2;
            unsigned int __reserved_3:1;
            unsigned int bl_entry_cnt_hi:3;
#           else
            unsigned int bl_entry_cnt_hi:3;
            unsigned int __reserved_3:1;
            unsigned int blq_size:2;
            unsigned int blq_empty:1;
            unsigned int blq_full:1;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int __reserved_11:5;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_24:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl3_lo {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int bl_entry_cnt_lo:8;
            unsigned int __reserved_23:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_tail_ptr:11;
#           else
            unsigned int bl_tail_ptr:11;
            unsigned int __reserved_11:1;
            unsigned int bl_head_ptr:11;
            unsigned int __reserved_23:1;
            unsigned int bl_entry_cnt_lo:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_ctrl3_hi {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_24:8;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_11:5;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int blq_full:1;
            unsigned int blq_empty:1;
            unsigned int blq_size:2;
            unsigned int __reserved_3:1;
            unsigned int bl_entry_cnt_hi:3;
#           else
            unsigned int bl_entry_cnt_hi:3;
            unsigned int __reserved_3:1;
            unsigned int blq_size:2;
            unsigned int blq_empty:1;
            unsigned int blq_full:1;
            unsigned int bd_fifo_entry_cnt:3;
            unsigned int __reserved_11:5;
            unsigned int blq_event_full_cnt:8;
            unsigned int __reserved_24:8;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_blq_null_mu_ptr {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_29:3;
            unsigned int blq_null_mu_ptr:29;
#           else
            unsigned int blq_null_mu_ptr:29;
            unsigned int __reserved_29:3;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_pcie_dma_rsvd {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_0:32;
#           else
            unsigned int __reserved_0:32;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_bpe_cfg {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int bpe_num:5;
            unsigned int ctm:6;
            unsigned int pkt_credit:11;
            unsigned int buf_credit:10;
#           else
            unsigned int buf_credit:10;
            unsigned int pkt_credit:11;
            unsigned int ctm:6;
            unsigned int bpe_num:5;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_abort_status {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int pck_num_odd:9;
            unsigned int ctm_odd:6;
            unsigned int valid_odd:1;
            unsigned int pck_num_even:9;
            unsigned int ctm_even:6;
            unsigned int valid_even:1;
#           else
            unsigned int valid_even:1;
            unsigned int ctm_even:6;
            unsigned int pck_num_even:9;
            unsigned int valid_odd:1;
            unsigned int ctm_odd:6;
            unsigned int pck_num_odd:9;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_bp_ctmcr_thresh {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_30:2;
            unsigned int threshold2:10;
            unsigned int threshold1:10;
            unsigned int threshold0:10;
#           else
            unsigned int threshold0:10;
            unsigned int threshold1:10;
            unsigned int threshold2:10;
            unsigned int __reserved_30:2;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_total_credit_cnt {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int total_pkt_credit:16;
            unsigned int total_buf_credit:16;
#           else
            unsigned int total_buf_credit:16;
            unsigned int total_pkt_credit:16;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_dma_dma_chksum_ena {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_16:16;
            unsigned int dma_chksum_ena:16;
#           else
            unsigned int dma_chksum_ena:16;
            unsigned int __reserved_16:16;
#           endif
        };
        unsigned int __raw;
    };
};


struct nfp_pcie_barcfg_pf_p2c_bar_sub {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int map_type:3;
            unsigned int len:2;
            unsigned int target:4;
            unsigned int token:2;
            unsigned int actaddr:5;
            unsigned int base:16;
#           else
            unsigned int base:16;
            unsigned int actaddr:5;
            unsigned int token:2;
            unsigned int target:4;
            unsigned int len:2;
            unsigned int map_type:3;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_barcfg_vf_p2c_bar_sub {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int len:2;
            unsigned int target:4;
            unsigned int token:2;
            unsigned int map_type:2;
            unsigned int base:22;
#           else
            unsigned int base:22;
            unsigned int map_type:2;
            unsigned int token:2;
            unsigned int target:4;
            unsigned int len:2;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_barcfg_p2cx0 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int sigtype:2;
            unsigned int tok:2;
            unsigned int __reserved_24:4;
            unsigned int addr:24;
#           else
            unsigned int addr:24;
            unsigned int __reserved_24:4;
            unsigned int tok:2;
            unsigned int sigtype:2;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_barcfg_p2cx1 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int __reserved_31:1;
            unsigned int signal_ref:7;
            unsigned int data_master:10;
            unsigned int data_ref:14;
#           else
            unsigned int data_ref:14;
            unsigned int data_master:10;
            unsigned int signal_ref:7;
            unsigned int __reserved_31:1;
#           endif
        };
        unsigned int __raw;
    };
};

struct nfp_pcie_barcfg_p2cx2 {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int tgt:4;
            unsigned int act:5;
            unsigned int len:5;
            unsigned int byte_mask:8;
            unsigned int signal_master:10;
#           else
            unsigned int signal_master:10;
            unsigned int byte_mask:8;
            unsigned int len:5;
            unsigned int act:5;
            unsigned int tgt:4;
#           endif
        };
        unsigned int __raw;
    };
};


/*
 * NFP 6XXX backward-compatible PCIe register structures
 */
struct nfp_pcie_dma_cmd {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int cpp_addr_lo:32;
            unsigned int mode_sel:2;
            unsigned int dma_mode:16;
            unsigned int cpp_token:2;
            unsigned int dma_cfg_index:4;
            unsigned int cpp_addr_hi:8;
            unsigned int pcie_addr_lo:32;
            unsigned int length:12;
            unsigned int rid:8;
            unsigned int rid_override:1;
            unsigned int trans_class:3;
            unsigned int pcie_addr_hi:8;
#           else
            unsigned int cpp_addr_lo:32;
            unsigned int cpp_addr_hi:8;
            unsigned int dma_cfg_index:4;
            unsigned int cpp_token:2;
            unsigned int dma_mode:16;
            unsigned int mode_sel:2;
            unsigned int pcie_addr_lo:32;
            unsigned int pcie_addr_hi:8;
            unsigned int trans_class:3;
            unsigned int rid_override:1;
            unsigned int rid:8;
            unsigned int length:12;
#           endif
        };
        unsigned int __raw[4];
    };
};

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP3800__NFP_PCIE_H_ */
