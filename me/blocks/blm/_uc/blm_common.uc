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
 * @file        blm_common.uc
 * @brief       Common Buffer List Manager Macros
 */

#ifndef __BLM_COMMON_UC__
#define __BLM_COMMON_UC__

#include <stdmac.uc>
#include <ring_utils.uc>

/** @file blm_common.uc Buffer List Manager Macros
 * @addtogroup blm_api Buffer List Manager
 * @{
 *
 * @name Buffer List Manager Macros
 * @{
 *
 */

// API Quick Reference:
// blm_create_global_bpool(nbuffers, rtype, rnum, bbase, bsize)


#define NBI_CPP_ADDRESS(NbiNum)       ((0x000000) | (NbiNum << 30))
#define NBI_DMA_CPP_BLQ_OFFSET(blq)   ((0x008000) | (blq    << 3))
/* NBITMCPP base = 0x200000 + TM BLQ offset = 0x88000 */
#define NBI_TM_CPP_BLQ_OFFSET(blq)    ((0x288000) | (blq    << 3))
/* NBITMCPP base = 0x200000 + TM BLQ_RD CSR offset = 0x90000 */
#define NBI_TM_CPP_BLQ_RD_OFFSET(blq) ((0x280000) | (blq    << 7))

#define xpb_csr_addr(island, slave_idx, tgt_dev, csr_offset)    ((0 <<31)       | \
                                                                (0 <<30)        | \
                                                                (8 <<24)        | \
                                                                (island <<24)   | \
                                                                (slave_idx <<22)| \
                                                                (tgt_dev <<16)  | \
                                                                (csr_offset))

/// @cond INTERNAL_MACROS
/**
 */
#macro _blm_immed32(_reg, val)
    #ifdef __L16
        #undef __L16
    #endif
    #ifdef __H16
        #undef __H16
    #endif
    #define_eval __L16        (val & 0xffff)
    #define_eval __H16        ((val >>16) & 0xffff)
    immed[_reg, __L16]
    #if __H16 > 0
        immed_w1[_reg, __H16]
    #endif
    #undef __L16
    #undef __H16
#endm /* _blm_immed32 */

/**
 *  Get NBI CPP base address
 *
 *  @param oaddr        Out GPR which contains the NBI CPP base address
 *  @param NbiNum       NBI number. 0: NBI Island 8, 1: NBI Island 9
 */
#macro GET_NBI_CPP_BASE_ADDRESS(oaddr, NbiNum)
    #if (isnum(NbiNum))
        #define_eval __addr    NBI_CPP_ADDRESS(NbiNum)
        _blm_immed32(oaddr, __addr)
    #else
        #define_eval __addr    NBI_CPP_ADDRESS(0)
        _blm_immed32(oaddr, __addr)
        alu[oaddr, oaddr, OR, NbiNum, <<30]
    #endif
    #undef __addr
#endm /* NBI_CPP_ADDRESS */

#macro GET_NBI_DMA_CPP_BLQ_OFFSET(ooffset, blq)
    #if (isnum(blq))
        #define_eval __offset  NBI_DMA_CPP_BLQ_OFFSET(blq)
        _blm_immed32(ooffset, __offset)
    #else
        #define_eval __offset  NBI_DMA_CPP_BLQ_OFFSET(0)
        _blm_immed32(ooffset, __offset)
        alu[ooffset, ooffset, OR, blq, <<3]
    #endif
    #undef __offset
#endm /* GET_NBI_DMA_CPP_BLQ_OFFSET */

#macro GET_NBI_TM_CPP_BLQ_OFFSET(ooffset, blq)
    #if (isnum(blq))
        #define_eval __offset  NBI_TM_CPP_BLQ_OFFSET(blq)
        _blm_immed32(ooffset, __offset)
    #else
        #define_eval __offset  NBI_TM_CPP_BLQ_OFFSET(0)
        _blm_immed32(ooffset, __offset)
        alu[ooffset, ooffset, OR, blq, <<3]
    #endif
    #undef __offset
#endm /* GET_NBI_TM_CPP_BLQ_OFFSET */

#macro GET_NBI_TM_CPP_BLQ_RD_OFFSET(ooffset, blq)
    #if (isnum(blq))
        #define_eval __offset  NBI_TM_CPP_BLQ_RD_OFFSET(blq)
        _blm_immed32(ooffset, __offset)
    #else
        #define_eval __offset  NBI_TM_CPP_BLQ_RD_OFFSET(0)
        _blm_immed32(ooffset, __offset)
        alu[ooffset, ooffset, OR, blq, <<7]
    #endif
    #undef __offset
#endm /* GET_NBI_TM_CPP_BLQ_RD_OFFSET */
/// @endcond


/** This macro creates a global buffer pool ring and fills it with buffers
 *
 * @param nbuffers      Number of buffers
 * @param bsize         Size of each buffer (at 2KB boundary, in bytes)
 * @param bbase         40-bit MU start address for buffers right shifted by 11-bits - IMU or EMU only (byte address)
                        Example: If IMU base address(island 28) = 0x9c00100000, bbase = 0x9c00100000 >>11 = 0x13800200
 * @param rtype         Type of ring: DDR_RING, CLS_RING, CTM_RING
 *                      NOTE: Ring must be initailized prior to calling this macro. Ring size >= nbuffers
 * @param rnum          Ring number
 */
#macro blm_create_global_bpool(nbuffers, bsize, bbase, rtype, rnum)
.begin
    .reg $pkt_buf[2]
    .reg tmp_pkt_buf
    .reg num_pkt_buffers
    .reg tmp_buf_size
    .sig dram_pkt_sig
    .xfer_order $pkt_buf

    #if (isnum(bbase))
        immed32(tmp_pkt_buf, bbase)
    #else
        alu[tmp_pkt_buf, --, b, bbase]
    #endif
    #if (isnum(bsize))
       #define_eval __INCR  (bsize >> 11)
       immed32(tmp_buf_size, __INCR)
       #undef __INCR
    #else
       alu[tmp_buf_size, --, b, bsize,>>11]
    #endif
    immed32(num_pkt_buffers, 0)
    alu[$pkt_buf[0], --, b, tmp_pkt_buf]

    .while (num_pkt_buffers < nbuffers)
        ru_enq_to_ring($pkt_buf, rtype, 1, rnum, dram_pkt_sig, SIG_WAIT, PUT_BLIND)
        alu[num_pkt_buffers, num_pkt_buffers, +, 1]
        alu[tmp_pkt_buf, tmp_pkt_buf, +, tmp_buf_size]
        alu[$pkt_buf[0], --, b, tmp_pkt_buf]
    .endw

.end
#endm /* blm_create_global_bpool */

/** @}
 * @}
 */

#endif /* __BLM_COMMON_UC__ */
