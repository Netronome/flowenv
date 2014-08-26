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
 * @file        libpkt.c
 * @brief       Basic packet operations for the NFP6xxx
 */
#include <assert.h>
#include <nfp.h>
#include <stdint.h>
#include <types.h>

#include <nfp/me.h>
#include <nfp/mem_bulk.h>

#include <nfp6000/nfp_me.h>

#include <pkt/pkt.h>

#ifndef __PKT__LIBPKT_C
#define __PKT__LIBPKT_C


__intrinsic void
__pkt_nbi_recv(__xread void *meta, size_t msize, sync_t sync, SIGNAL *sig)
{
    unsigned int zero = 0;
    unsigned int count = (msize >> 2);

    ctassert(__is_ct_const(sync));
    ctassert(sync == ctx_swap || sync == sig_done);
    ctassert(__is_ct_const(msize));

    /* TODO: modify to allow for variable msize and msize > 64 */
    ctassert(msize % 4 == 0);
    ctassert(msize >= 24);
    ctassert(msize <= 64);

    if (sync == ctx_swap) {
        __asm {
            mem[packet_add_thread, *meta, zero, 0, count], ctx_swap[*sig]
        }
    } else {
        __asm {
            mem[packet_add_thread, *meta, zero, 0, count], sig_done[*sig]
        }
    }
}


__intrinsic void
pkt_nbi_recv(__xread void *meta, size_t msize)
{
    SIGNAL add_thread_sig;
    __pkt_nbi_recv(meta, msize, ctx_swap, &add_thread_sig);
}


/*
 * This operation is supplied as a function and not a macro because
 * experience with the 'nfcc' compiler has shown that a simple,
 * single expression will not compile correctly and that the type
 * casting for the intermediate values must be done carefully.
 *
 * A 40-bit packet-address mode pointer in CTM is built as follows:
 *
 *  Bits[2;38] -- Must be 0b10 for "direct access"
 *  Bits[6;32] -- The island of the CTM. (can use '0' for the local island)
 *  Bits[1;31] -- Must be set to 1 to enable packet-addressing mode
 *  Bits[6;25] -- reserved
 *  Bits[9;16] -- The packet number of the CTM buffer
 *  Bits[2;14] -- reserved
 *  Bits[14;0] -- The offset within the CTM buffer
 *
 * Unfortunately, this is only partly documented in the NFP DB.
 */
__intrinsic __addr40 void *
pkt_ctm_ptr40(unsigned char isl, unsigned int pnum, unsigned int off)
{
    __gpr unsigned int lo;
    __gpr unsigned int hi;
    hi = 0x80 | isl;
    lo = 0x80000000u | (pnum << 16) | off;
    return (__addr40 void *)
        (((unsigned long long)hi << 32) | (unsigned long long)lo);
}


/*
 * A 32-bit packet-address mode pointer in CTM is built as follows:
 *
 *  Bits[1;31] -- Must be set to 1 to enable packet-addressing mode
 *  Bits[6;25] -- reserved
 *  Bits[9;16] -- The packet number of the CTM buffer
 *  Bits[2;14] -- reserved
 *  Bits[14;0] -- The offset within the CTM buffer
 *
 * Unfortunately, this is only partly documented in the NFP DB.
 *
 * Note that because the top 8 bits are left as 0 in the actual memory
 * command that uses this address, this type of address can only refer
 * to a packet in ones local CTM memory.
 */
__intrinsic __addr32 void *
pkt_ctm_ptr32(unsigned int pnum, unsigned int off)
{
    return (__addr32 void *)((1 << 31) | (pnum << 16) | off);
}


__intrinsic struct pkt_ms_info
__pkt_nop_ms_write(__addr40 void *pbuf, unsigned char off,
                   __xwrite uint32_t xms[2], sync_t sync,
                    SIGNAL *sig)
{
    __gpr struct pkt_ms_info msi;

    if (off % 8 == 0) {
        msi.off_enc = (off - 8)/8 - 1;
        msi.len_adj = off;
        xms[0] = TM_MS_NOP_w0;
        xms[1] = TM_MS_NOP_w1;
        __mem_write64(xms, (__addr40 unsigned char *)pbuf + off - 8,
                      2*sizeof(uint32_t), 2*sizeof(uint32_t), sync, sig);
    } else {
        /* TODO: deal with rewrite scripts for arbitrarily aligned offsets */
        __rt_assert();
    }
    return msi;
}


__intrinsic struct pkt_ms_info
pkt_nop_ms_write(__addr40 void *pbuf, unsigned char off)
{
    SIGNAL sig;
   __xwrite uint32_t ms[2];
    return __pkt_nop_ms_write(pbuf, off, ms, ctx_swap, &sig);
}


__intrinsic void
pkt_nbi_send(unsigned char isl, unsigned int pnum,
             __gpr const struct pkt_ms_info *msi, unsigned int len,
             unsigned int nbi, unsigned int txq, unsigned int seqr,
             unsigned int seq)
{
    __gpr unsigned int addr_lo;
    __gpr struct pkt_iref_csr0 csr0;
    __gpr struct pkt_iref_palu palu;

    /*
     * The "packet processing complete" commands require a special encoding
     * in the address field.  The packet number goes in bits [25:16] and
     * the _ending_offset_ of the packet goes in bits [13:0] of the address.
     * To get the ending offset, we add the packet length to a value
     * calculated based on the starting offset of the modification script,
     * the modification script's length, and any padding between it and
     * the start of the packet.
     *
     * See NFP 6xxx Databook Section 9.2.2.7.9 "Packet Processing Complete
     * Target Command and Packet Ready Master Command"
     */
    addr_lo = (pnum << 16) | (len + msi->len_adj);

    csr0.__raw = 0;
    csr0.seqr = seqr;
    csr0.seq = seq;
    local_csr_write(NFP_MECSR_CMD_INDIRECT_REF_0, csr0.__raw);

    /*
     * XXX We clear the reserved bits of the previous ALU instruction 
     * structure by assigning the whole 32-bit value the MAGIC constant.
     * This constant starts at bit 0 of the structure anyways.
     */
    palu.__raw = PKT_IREF_PALU_MAGIC;
    palu.nbi = nbi;
    palu.txq = txq;
    palu.ms_off = msi->off_enc;

    if (isl == 0) {
        __asm {
            alu[--, --, B, palu.__raw];
            mem[packet_complete_unicast, --, addr_lo, 0], indirect_ref;
        }
    } else {
        /*
         * When sending to a non-local island requires using a full 40-bit
         * address.  The top 8 bits of this address must be as follows:
         *   [2;38] -- Must be 0b10 to represent "direct access" locality.
         *   [6;32] -- The island of the CTM holding the packet.
         *
         * We put these 8 bits in the top 8 bits of addr_hi, and then use
         * the <<8 to put them into place in the 40-bit address.
         */
        __gpr unsigned int addr_hi = (isl | 0x80) << 24;
        __asm {
            alu[--, --, B, palu.__raw];
            mem[packet_complete_unicast, --, addr_hi, <<8, addr_lo], \
                indirect_ref;
        }
    }
}

#endif /* __PKT__LIBPKT_C */
