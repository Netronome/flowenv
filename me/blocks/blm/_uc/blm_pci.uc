/*
 * Copyright (C) 2019-2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file        blm_pci.uc
 * @brief       PCIe Buffer List Manager Macros
 */

#ifndef __BLM_PCI_UC__
#define __BLM_PCI_UC__

#include <stdmac.uc>
#include "blm_common.uc"

/** @file blm_pci.uc Buffer List Manager Macros
 * @addtogroup blm_api Buffer List Manager
 * @{
 *
 * @name Buffer List Manager Macros
 * @{
 *
 */

// API Quick Reference:
// blm_pci_cfg_blq(PcieNum, blq, size, head, tail)
// blm_pci_cfg_blq_evnts(PcieNum, blq, ethres, estatus, enotfull)
// blm_pci_push_mem2dma(PcieNum, blq, addr, offset, n, addToHead)
// blm_pci_recycle(snbi, sblq, dpci, dblq, n)
// blm_pci_blq_commit(PcieNum, BlqStashMem)

/// @cond INTERNAL_MACROS

/* CPP PCIe CSRs */
#define PCI_DMA_CPP_BLQ_OFFSET(_x) (0x0000800150 + ((_x) << 3))
#define PCI_INT_DMABLQEVENT 0x00800124
#define PCI_DBG_ADDR_LO 0x008000f0
#define PCI_DBG_ADDR_HI 0x008000f4
#define_eval PCI_DBG_CMD_WRBLQ ((1 << 26) | (0 << 12))
#define PCI_BDSRAM_SZ 2048

/**
 *  Get PCIe CPP base address
 *
 *  @param oaddr        Out GPR which contains the PCIe CPP base address
 *  @param PcieNum       PCIe number. 0: PCIe Island 4
 */
#macro GET_PCI_CPP_BASE_ADDRESS(oaddr, PcieNum)
    #if (isnum(PcieNum))
        alu[oaddr, --, B, PcieNum, <<30]
    #else
        alu[oaddr, --, B, PcieNum, <<30]
    #endif
#endm /* GET_PCI_CPP_BASE_ADDRESS */

#macro GET_PCI_DMA_CPP_BLQ_OFFSET(ooffset, blq)
    #if (isnum(blq))
        #define_eval __offset  PCI_DMA_CPP_BLQ_OFFSET(blq)
        _blm_immed32(ooffset, __offset)
    #else
        #define_eval __offset  PCI_DMA_CPP_BLQ_OFFSET(0)
        _blm_immed32(ooffset, __offset)
        .reg otmp
        alu[otmp, --, B, blq, <<3]
        alu[ooffset, ooffset, +, otmp]
    #endif
    #undef __offset
#endm /* GET_PCI_DMA_CPP_BLQ_OFFSET */
/// @endcond

/** This macro configures a buffer list queue in PCIe DMA
 *
 * @param PcieNum       PCIe number, 0
 * @param blq           PCIe buffer list queue number, from 0 to 3
 * @param size          Size of the buffer list queue, valid values: 0:256, 1:512, 2:1K, 3:2K
 * @param head          Head pointer
 * @param tail          Tail pointer
 */
#macro blm_pci_cfg_blq(PcieNum, blq, size, head, tail)
.begin
    .reg $x[2]
    .reg addr
    .reg _head _tail
    .reg offset
    .reg val
    .sig pci_sig
    .xfer_order $x

    #if (isnum(PcieNum))
        #if ((PcieNum < 0) || (PcieNum > 0))
            #error "Not a valid PcieNum. PcieNum = [0]."
        #endif
    #else
        #error "PcieNum must be constant."
    #endif

    #if (isnum(blq))
        #if ((blq < 0) || (blq > 3))
            #error "Not a valid blq. blq = [0...3]."
        #endif
    #else
        #error "blq must be constant."
    #endif

    #if (isnum(size))
        #if ((size < 0) || (size > 3))
            #error "Not a valid size for blq. size = [0...3]."
        #endif
    #else
        #error "size must be constant."
    #endif

    GET_PCI_CPP_BASE_ADDRESS(addr, PcieNum)
    GET_PCI_DMA_CPP_BLQ_OFFSET(offset, blq)

    #if (isnum(head))
        _blm_immed32(_head, head)
    #else
        alu[_head, --, b, head]
    #endif
    #if (isnum(tail))
        _blm_immed32(_tail, tail)
    #else
        alu[_tail, --, b, tail]
    #endif

    alu[val, _tail, OR, _head, <<12]
    alu[$x[0], --, b, val]
    alu[val, --, b, size, <<4]
    alu[$x[1], --, b, val]

    pcie[write_int, $x[0], addr, <<8, offset, 1], sig_done[pci_sig]
    wait_blq_cfg#:
      br_!signal[pci_sig, wait_blq_cfg#]
    nop
    alu[offset, offset, +, 4]
    pcie[write_int, $x[1], addr, <<8, offset, 1], sig_done[pci_sig]
    wait_blq_cfg2#:
      br_!signal[pci_sig, wait_blq_cfg2#]
.end
#endm /* blm_pci_cfg_blq */

/** This macro configures events for given buffer list queue.
 *
 * @param PcieNum       PCIe number, 0
 * @param blq           PCIe Buffer list queue number, from 0 to 3
 * @ethres              Event threshold, at which PCIe generates event. Valid values: 0:16, 1:32, 2:64, 3:128
 * @estatus             Enables BLQ Status Events when set. 0:Disable, 1:Enable
 * @enotfull            Enables the generation of BLQ Events when the queue transitions from full to not full. 0:Disable, 1:Enable
 */
#macro blm_pci_cfg_blq_evnts(PcieNum, blq, ethres, estatus, enotfull)
.begin
    .reg $x[1]
    .reg alo, ahi
    .reg val
    .reg n
    .reg tmp
    .sig pci_sig
    .xfer_order $x

    #if (isnum(ethres))
        #if ((ethres < 0) || (ethres > 3))
          #error "Not a valid value for threshold. range = [0...3]."
        #endif
    #else
        #error "ethres must be constant."
    #endif


    GET_PCI_CPP_BASE_ADDRESS(ahi, PcieNum)
    move(alo, PCI_INT_DMABLQEVENT)

    pcie[read_int, $x[0], ahi, <<8, alo, 1], sig_done[pci_sig]
    wait_pcie_rd0#:
      br_!signal[pci_sig, wait_pcie_rd0#]

    alu[val, --, b, $x[0]]
    alu[n, --, b, blq]

    // Clear BLQEventStatus
    alu[--, n, OR, 0]
    alu[val, val, AND~, 1, <<indirect]
    // clear BLQEventNotEmpty
    alu[n, n, +, 4]
    alu[--, n, OR, 0]
    alu[val, val, AND~, 1, <<indirect]
    // clear EventThreshold
    immed[tmp, 0x3000]
    alu[n, --, b, blq, <<1]
    alu[--, n, OR, 0]
    alu[val, val, AND~, tmp, <<indirect]

    // Config BLQEventStatus
    alu[n, --, b, blq]
    alu[--, n, OR, 0]
    alu[val, val, OR, estatus, <<indirect]

    // Config BLQEventNotEmpty
    alu[n, n, +, 4]
    alu[--, n, OR, 0]
    alu[val, val, OR, enotfull, <<indirect]

    // Config EventThreshold
    alu[n, --, b, blq, <<1]
    alu[tmp, --, b, ethres, <<12]
    alu[--, n, OR, 0]
    alu[val, val, OR, tmp, <<indirect]

    alu[$x[0], --, b, val]

    pcie[write_int, $x[0], ahi, <<8, alo, 1], sig_done[pci_sig]
wait_pcie_wr0#:
    br_!signal[pci_sig, wait_pcie_wr0#]

.end
#endm /* blm_pci_cfg_blq_evnts */

/** This macro pushes 'n' buffer pointers to specified blq# in Ingress PCIe from main memory.
 *
 * @param PcieNum       PCIe number, 0
 * @param blq           Buffer list queue number, from 0 to 3
 * @param addr          Starting Address of target memory. n*8 bytes required
 * @param offset        Offset from 'addr'. Final 40-bit address = ((addr << 8) + offset)
 * @param n             Number of buffers to push. MUST be multiple of 2. n = [2,4,6,8,....,32]
 * @param addToHead     if = 1, add buffers to Head else to Tail
 */
#macro blm_pci_push_mem2dma(PcieNum, blq, addr, offset, n, addToHead)
.begin
    .reg override_data
    .reg ov
    .reg $x[2]
    .xfer_order $x
    .set $x[0]
    .set $x[1]
    .sig dummy_sig

    /**
    ov = (0xf<<20)      ; data_master (PCIe DMA = 0xE or 0xF)
    ov = ov | (0xf<<16) ; sig_master (PCIe DMA = 0xE or 0xF)
    ov = ov | (4<<24) ; Master_Island
    ov = ov | (PcieNum<<24) ; LSB of Master_Island
    */
    #define_eval __ov   (0 | \
                         (0xf<<20) | \
                         (0xf<<16) | \
                         (4<<24))
    #if (isnum(PcieNum))
        #define_eval __ov       (__ov | (PcieNum<<24))
        _blm_immed32(ov, __ov)
    #else
        _blm_immed32(ov, __ov)
        alu[ov, ov, OR, PcieNum, <<24]
    #endif
    #undef __ov
    local_csr_wr[CMD_INDIRECT_REF_0, ov]

    #if (!isnum(addToHead))
        #error "addToHead must be constant."
    #endif

    #if ( (addToHead < 0) | (addToHead > 1))
        #error "addToHead must be 0 or 1."
    #endif

    #if (!isnum(n))
        #error "Number of buffers must be constant."
    #endif

    #define_eval __len  ((n/2)-1)

    /**
    override_data = (2<<1) ;override (OM) data_master, signal_master, data_master_island
    override_data = override_data | (1<<3) ;override data_ref (OD)
    override_data = override_data | (1<<7) ;override  LEN
    override_data = override_data | (n<<8) ;override  LEN
    override_data = override_data | (1<<13) ;override (Sig_Ref, 0=no signal)
    override_data = override_data | (blq<<23) ; QueueSelect = data_ref[2;7] (blq<<(16+7)).
    override_data = override_data | (0<<25)   ; AddToHead   = data_ref[1;9] = 1 else AddToTail.
    */
    #define_eval  __override_data       (0            | \
                                         (2<<1)       | \
                                         (1<<3)       | \
                                         (1<<7)       | \
                                         (__len<<8)   | \
                                         (1<<13)      | \
                                         (addToHead<<25))
    #if (isnum(blq))
        #define_eval __override_data        (__override_data | (blq<<23))
        _blm_immed32(override_data, __override_data)
    #else
        _blm_immed32(override_data, __override_data)
        alu[override_data, override_data, OR, blq, <<23]
    #endif
    #undef __override_data
    #undef __len
    #if (isnum(addr))
        .reg __addr
        _blm_immed32(__addr, addr)
    #else
        #define_eval __addr  addr
    #endif
    #if (isnum(offset))
        .reg __offset
        _blm_immed32(__offset, offset)
    #else
        #define_eval __offset  offset
    #endif
    alu[--,--,B,override_data]
    mem[read, $x[0], __addr, <<8, __offset, 1], sig_done[dummy_sig], indirect_ref
    .io_completed dummy_sig
    #ifdef __addr
        #undef __addr
    #endif
    #ifdef __ofset
        #undef __ofset
    #endif
.end
#endm /* blm_pci_push_mem2dma */

/** This macro pops 'n' buffer pointers from specified blq# from Egress NBI and pushes directly to Ingress PCIe.
 *
 * @param snbi          Source NBI number, 0
 * @param sblq          Source Buffer list queue number, from 0 to 3
 * @param dpci          Destination PCIe number, 0
 * @param dblq          Destination Buffer list queue number, from 0 to 3
 * @param n             Number of buffers to pop = ((n+1)*2)
 */
#macro blm_pci_recycle(snbi, sblq, dpci, dblq, n)
.begin
    .reg addr
    .reg offset
    .reg override_data
    .reg ov
    .reg $x[2]
    .xfer_order $x

    #if (!isnum(n))
        #error "Length must be constant."
    #endif

    #define_eval __ov   (0 | \
                        (0xf<<20) | \
                        (0xf<<16) | \
                        (4<<24))
    #if (isnum(dpci))
        #define_eval __ov       (__ov | (dpci<<24))
        _blm_immed32(ov, __ov)
    #else
        _blm_immed32(ov, __ov)
        alu[ov, ov, OR, dpci, <<24]
    #endif
    #undef __ov
    local_csr_wr[CMD_INDIRECT_REF_0, ov]

    /**
    override_data = (1<<1) ;override (OM) data_master, data_master_island
    override_data = override_data | (1<<3) ;override (OD)
    override_data = override_data | (1<<7) ;override  LEN
    override_data = override_data | (n<<8) ;override  LEN
    override_data = override_data | (1<<13) ;override (Sig_Ref, 0=no signal)
    override_data = override_data | (dblq<<23) ; QueueSelect = data_ref[2;7].
    override_data = override_data | (1<<25)   ; AddToHead   = data_ref[1;9].
    */
    #define_eval __override_data        (0              | \
                                        (2<<1)          | \
                                        (1<<3)          | \
                                        (1<<7)          | \
                                        (n<<8)          | \
                                        (1<<13)         | \
                                        (1<<25))
    #if (isnum(dblq))
        #define_eval __override_data        (__override_data | (dblq<<23))
        _blm_immed32(override_data, __override_data)
    #else
        _blm_immed32(override_data, __override_data)
        alu[override_data, override_data, OR, dblq, <<23]
    #endif
    #undef __override_data

    GET_NBI_CPP_BASE_ADDRESS(addr, snbi)
    GET_NBI_TM_CPP_BLQ_RD_OFFSET(offset, sblq)

    .sig bogus_sig
    alu[--,--,B,override_data]
    nbi[read, $x[0], addr, <<8, offset, 1], indirect_ref, sig_done[bogus_sig]
    .io_completed bogus_sig
.end
#endm /* blm_pci_recycle */

/** This macro fills PCIe BDSRAM based on a prefilled/stashed memory
 *
 * @param PcieNum      PCIe number, 0
 * @param BlqStashMem  Stash memory symbol
 */

#macro blm_pci_blq_commit(PcieNum, BlqStashMem)
.begin
    .reg ctl_a_hi, ctl_a_lo, stash_a_hi, stash_a_lo
    .reg $ctlval, $ptrval[8]
    .reg n, end, ctl_val_base
    .xfer_order $ptrval
    .sig s

    /* first we program the blq memory */
    move(ctl_val_base, PCI_DBG_CMD_WRBLQ)
    move(ctl_a_hi, (PcieNum) << 30)
    move(stash_a_hi, ((BlqStashMem >> 8) & 0xff000000))

    move(stash_a_lo, ((BlqStashMem) & 0xffffffff))
    move(n, 0)
    move(end, PCI_BDSRAM_SZ)

pcie_blq_wr_loop#:
    mem[read32, $ptrval[0], stash_a_hi, <<8, stash_a_lo, 1], ctx_swap[s]
    alu[stash_a_lo, stash_a_lo, +, 4]

    alu[$ctlval, ctl_val_base, OR, n]
    move(ctl_a_lo, PCI_DBG_ADDR_LO)
    pcie[write_int, $ctlval, ctl_a_hi, <<8, ctl_a_lo, 1], ctx_swap[s]

    move($ctlval, $ptrval[0])
    move(ctl_a_lo, PCI_DBG_ADDR_HI)
    pcie[write_int, $ctlval, ctl_a_hi, <<8, ctl_a_lo, 1], ctx_swap[s]
    alu[n, n, +, 1]
    alu[--, n, -, end]
    blt[pcie_blq_wr_loop#]
.end
#endm


/** @}
 * @}
 */

#endif /* __BLM_PCI_UC__ */
