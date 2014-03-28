/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/_c/mem_bulk.c
 * @brief         NFP memory bulk interface
 */

#include <nfp/nfp.h>
#include <nfp/mem_bulk.h>
#include <nfp6000/nfp_me.h>


#define _MEM_CMD(cmdname, data, addr, size, max_size, sync, sig)        \
do {                                                                    \
    struct nfp_mecsr_prev_alu ind;                                      \
    unsigned int count = (size >> 3);                                   \
    unsigned int max_count = (max_size >> 3);                           \
    unsigned int addr_hi, addr_lo;                                      \
                                                                        \
    ctassert(__is_ct_const(sync));                                      \
    try_ctassert(size != 0);                                            \
    try_ctassert(__is_aligned(size, 8));                                \
    try_ctassert(size <= 128);                                          \
    ctassert(sync == sig_done || sync == ctx_swap);                     \
                                                                        \
    /* This code is inefficient if addr is >256B aligned, */            \
    /* but will work for 40bit or 32bit pointers. */                    \
                                                                        \
    addr_hi = ((unsigned long long int)addr>>8) & 0xff000000;           \
    addr_lo = (unsigned long long int)addr & 0xffffffff;                \
                                                                        \
    if (__is_ct_const(size)) {                                          \
        if (size <= 64) {                                               \
            if (sync == sig_done) {                                     \
                __asm { mem[cmdname, *data, addr_hi, <<8, addr_lo,      \
                            __ct_const_val(count)], sig_done[*sig] }    \
            } else {                                                    \
                __asm { mem[cmdname, *data, addr_hi, <<8, addr_lo,      \
                            __ct_const_val(count)], ctx_swap[*sig] }    \
            }                                                           \
        } else {                                                        \
            /* Setup length in PrevAlu for the indirect */              \
            ind.__raw = 0;                                              \
            ind.ov_len = 1;                                             \
            ind.length = count - 1;                                     \
                                                                        \
            if (sync == sig_done) {                                     \
                __asm { alu[--, --, B, ind.__raw] }                     \
                __asm { mem[cmdname, *data, addr_hi, <<8, addr_lo,      \
                            __ct_const_val(count)], sig_done[*sig],     \
                            indirect_ref }                              \
            } else {                                                    \
                __asm { alu[--, --, B, ind.__raw] }                     \
                __asm { mem[cmdname, *data, addr_hi, <<8, addr_lo,      \
                            __ct_const_val(count)], ctx_swap[*sig],     \
                            indirect_ref }                              \
            }                                                           \
        }                                                               \
    } else {                                                            \
        /* Setup length in PrevAlu for the indirect */                  \
        ind.__raw = 0;                                                  \
        ind.ov_len = 1;                                                 \
        ind.length = count - 1;                                         \
                                                                        \
        if (sync == sig_done) {                                         \
            __asm { alu[--, --, B, ind.__raw] }                         \
            __asm { mem[cmdname, *data, addr_hi, <<8, addr_lo,          \
                        __ct_const_val(max_count)], sig_done[*sig],     \
                        indirect_ref }                                  \
        } else {                                                        \
            __asm { alu[--, --, B, ind.__raw] }                         \
            __asm { mem[cmdname, *data, addr_hi, <<8, addr_lo,          \
                        __ct_const_val(max_count)], ctx_swap[*sig],     \
                        indirect_ref }                                  \
        }                                                               \
    }                                                                   \
} while (0)

__intrinsic void
__mem_read64(__xread void *data, __dram void *addr,
             size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    ctassert(__is_read_reg(data));
    _MEM_CMD(read, data, addr, size, max_size, sync, sig);
}

__intrinsic void
mem_read64(__xread void *data, __dram void *addr, const size_t size)
{
    SIGNAL sig;
    __mem_read64(data, addr, size, size, ctx_swap, &sig);
}

__intrinsic void
__mem_write64(__xwrite void *data, __dram void *addr,
              size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    ctassert(__is_write_reg(data));
    _MEM_CMD(write, data, addr, size, max_size, sync, sig);
}

__intrinsic void
mem_write64(__xwrite void *data, __dram void *addr, const size_t size)
{
    SIGNAL sig;

    __mem_write64(data, addr, size, size, ctx_swap, &sig);
}
