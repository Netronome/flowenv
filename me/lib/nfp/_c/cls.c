/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/_c/cls.c
 * @brief         NFP CLS interface
 */

#include <nfp/nfp.h>
#include <nfp/cls.h>
#include <nfp6000/nfp_me.h>

#define _CLS_CMD(cmdname, data, addr, size, max_size, sync, sig, cmin, cmax) \
do {                                                                    \
    struct nfp_mecsr_prev_alu ind;                                      \
    unsigned int count = (size >> 2);                                   \
    unsigned int max_count = (max_size >> 2);                           \
                                                                        \
    ctassert(__is_ct_const(max_size));                                  \
    ctassert(__is_ct_const(sync));                                      \
    ctassert(sync == sig_done || sync == ctx_swap);                     \
                                                                        \
    if (__is_ct_const(size)) {                                          \
        ctassert(size != 0);                                            \
        ctassert(__is_aligned(size, 4));                                \
                                                                        \
        if(size <= (cmax * 4)) {                                        \
            if (sync == sig_done) {                                     \
                __asm { cls[cmdname, *data, addr, 0, __ct_const_val(count)], \
                        sig_done[*sig] }                                \
            } else {                                                    \
                __asm { cls[cmdname, *data, addr, 0, __ct_const_val(count)], \
                        ctx_swap[*sig] }                                \
            }                                                           \
        } else {                                                        \
            ctassert(size <= 128);                                      \
                                                                        \
            /* Setup length in PrevAlu for the indirect */              \
            ind.__raw = 0;                                              \
            ind.ov_len = 1;                                             \
            ind.length = count - 1;                                     \
                                                                        \
            if (sync == sig_done) {                                     \
                __asm { alu[--, --, B, ind.__raw] }                     \
                __asm { cls[cmdname, *data, addr, 0, __ct_const_val(count)], \
                        sig_done[*sig], indirect_ref }                  \
            } else {                                                    \
                __asm { alu[--, --, B, ind.__raw] }                     \
                __asm { cls[cmdname, *data, addr, 0, __ct_const_val(count)], \
                        ctx_swap[*sig], indirect_ref }                  \
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
            __asm { cls[cmdname, *data, addr, 0, __ct_const_val(max_count)], \
                    sig_done[*sig], indirect_ref }                      \
        } else {                                                        \
            __asm { alu[--, --, B, ind] }                               \
            __asm { cls[cmdname, *data, addr, 0, __ct_const_val(max_count)], \
                    ctx_swap[*sig], indirect_ref }                      \
        }                                                               \
    }                                                                   \
} while (0)

__intrinsic void
__cls_read_be(__xread void *data, __cls void *addr,
              size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    ctassert(__is_read_reg(data));
    _CLS_CMD(read_be, data, addr, size, max_size, sync, sig, 1, 8);
}

__intrinsic void
cls_read_be(__xread void *data, __cls void *addr, size_t size)
{
    SIGNAL sig;
    __cls_read_be(data, addr, size, size, ctx_swap, &sig);
}

__intrinsic void
__cls_write_be(__xwrite void *data, __cls void *addr,
               size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    ctassert(__is_write_reg(data));
    _CLS_CMD(write_be, data, addr, size, max_size, sync, sig, 1, 8);
}

__intrinsic void
cls_write_be(__xwrite void *data, __cls void *addr, size_t size)
{
    SIGNAL sig;
    __cls_write_be(data, addr, size, size, ctx_swap, &sig);
}

__intrinsic void
__cls_read_le(__xread void *data, __cls void *addr,
              size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    ctassert(__is_read_reg(data));
    _CLS_CMD(read_le, data, addr, size, max_size, sync, sig, 1, 8);
}

__intrinsic void
cls_read_le(__xread void *data, __cls void *addr, size_t size)
{
    SIGNAL sig;
    __cls_read_le(data, addr, size, size, ctx_swap, &sig);
}

__intrinsic void
__cls_write_le(__xwrite void *data, __cls void *addr,
               size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    ctassert(__is_write_reg(data));
    _CLS_CMD(write_le, data, addr, size, max_size, sync, sig, 1, 8);
}

__intrinsic void
cls_write_le(__xwrite void *data, __cls void *addr, size_t size)
{
    SIGNAL sig;
    __cls_write_le(data, addr, size, size, ctx_swap, &sig);
}


/*
 * Endian neutral version of the above functions.
 */

#if __BIGENDIAN

__intrinsic void
__cls_read(__xread void *data, __cls void *addr,
           size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    __cls_read_be(data, addr, size, max_size, sync, sig);
}

__intrinsic void
cls_read(__xread void *data, __cls void *addr, size_t size)
{
    cls_read_be(data, addr, size);
}

__intrinsic void
__cls_write(__xwrite void *data, __cls void *addr,
            size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    __cls_write_be(data, addr, size, max_size, sync, sig);
}

__intrinsic void
cls_write(__xwrite void *data, __cls void *addr, size_t size)
{
    cls_write_be(data, addr, size);
}

#else /* __LITLEENDIAN */

__intrinsic void
__cls_read(__xread void *data, __cls void *addr,
           size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    __cls_read_le(data, addr, size, max_size, sync, sig);
}

__intrinsic void
cls_read(__xread void *data, __cls void *addr, size_t size)
{
    cls_read_le(data, addr, size, size);
}

__intrinsic void
__cls_write(__xwrite void *data, __cls void *addr,
            size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
{
    __cls_write_le(data, addr, size, max_size, sync, sig);
}

__intrinsic void
cls_write(__xwrite void *data, __cls void *addr, size_t size)
{
    cls_write_le(data, addr, size, size);
}

#endif /* __LITLEENDIAN */
