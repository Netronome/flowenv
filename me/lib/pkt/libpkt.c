/**
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
    __gpr int zero = 0;

    ctassert(__is_ct_const(sync));
    ctassert(sync == ctx_swap || sync == sig_done);

    if (sync == ctx_swap) {
        __asm {
            mem[packet_add_thread, *meta, zero, 0, (msize/4)], \
                ctx_swap[*sig]
        }
    } else {
        __asm {
            mem[packet_add_thread, *meta, zero, 0, (msize/4)], \
                sig_done[*sig]
        }
    }
}


__intrinsic void
pkt_nbi_recv(__xread void *meta, size_t msize)
{
    SIGNAL add_thread_sig;
    __pkt_nbi_recv(meta, msize, ctx_swap, &add_thread_sig);
}


__intrinsic __addr40 void *
pkt_ctm_ptr40_build(unsigned char isl, unsigned int pnum, unsigned int off)
{
    __gpr unsigned int lo;
    __gpr unsigned int hi;
    hi = 0x80 | isl;
    lo = 0x80000000u | (pnum << 16) | off;
    return (__addr40 void *)
        (((unsigned long long)hi << 32) | (unsigned long long)lo);
}


__intrinsic __addr32 void *
pkt_ctm_ptr32_build(unsigned int pnum, unsigned int off)
{
    return (__addr32 void *)((1 << 31) | (pnum << 16) | off);
}


__intrinsic struct pkt_ms_info
__pkt_nop_ms_write(__addr40 void *pp, unsigned char off,
                   __xwrite uint32_t xms[2], sync_t sync,
                    SIGNAL *sig)
{
    __gpr struct pkt_ms_info msi;

    if (off % 8 == 0) {
        msi.off_enc = (off - 8)/8 - 1;
        msi.len_adj = off;
        xms[0] = TM_MS_NOP_w0;
        xms[1] = TM_MS_NOP_w1;
        __mem_write64(xms, (__addr40 unsigned char *)pp + off - 8,
                      2*sizeof(uint32_t), 2*sizeof(uint32_t), sync, sig);
    } else {
        /* TODO: deal with rewrite scripts for arbitrarily aligned offsets */
        __rt_assert();
    }
    return msi;
}


__intrinsic struct pkt_ms_info
pkt_nop_ms_write(__addr40 void *pp, unsigned char off)
{
    SIGNAL sig;
   __xwrite uint32_t ms[2];
    return __pkt_nop_ms_write(pp, off, ms, ctx_swap, &sig);
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

    /* XXX cheat and initialize the structure to 0 by assigning the sequencer */
    /* to the whole value. */
    csr0.__raw = seqr;
    csr0.seq = seq;
    local_csr_write(NFP_MECSR_CMD_INDIRECT_REF_0, csr0.__raw);

    /* XXX cheat by knowing that the least significant byte is the 'magic' */
    /* byte saves an extra initialization step. */
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
        __gpr unsigned int addr_hi = (isl | 0x80) << 24;
        __asm {
            alu[--, --, B, palu.__raw];
            mem[packet_complete_unicast, --, addr_hi, <<8, addr_lo], \
                indirect_ref;
        }
    }
}

#endif /* __PKT__LIBPKT_C */
