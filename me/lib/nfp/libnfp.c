/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/libnfp.c
 * @brief         Standard library for NFP
 */

#include <nfp/nfp.h>
#include <nfp6000/nfp_me.h>

/*
 * Define ctassert() and friends to avoid dependencies on <assert.h>.
 */
#ifndef __CT_ASSERT(expr)
#define __CT_ASSERT(expr) __ct_assert(expr, #expr)
#endif

#ifndef ctassert
#define ctassert(expr)                         \
   do {                                        \
       __intrinsic_begin();                    \
       __CT_ASSERT(expr);                      \
       __intrinsic_end();                      \
   } while (0)
#endif

#ifndef try_ctassert
#define try_ctassert(expr)                      \
    do {                                        \
        __intrinsic_begin();                    \
        if (__is_ct_const(expr))                \
            ctassert(expr);                     \
        __intrinsic_end();                      \
    }  while (0)
#endif

/*
 * The following files implement all the functionality in <nfp/*.h>.
 * They may only have dependencies on <nfp.h> and the other include
 * files in <nfp/*.h>.  They are not protected by header guards and
 * should not be included elsewhere.
 */
#include "_c/mem_bulk.c"
#include "_c/mem_ring.c"

/*
 * The following code implements all the functionality in <nfp.h>.  It
 * should not have any external dependencies (including dependencies
 * on <nfp/*.h> include files).
 */

__noinline void
___rt_assert(void *addr)
{
    local_csr_write(NFP_MECSR_MAILBOX_1, (unsigned int) addr);
    local_csr_write(NFP_MECSR_MAILBOX_0, 0);
    __asm ctx_arb[bpt];
}

__intrinsic unsigned int
local_csr_read(int mecsr)
{
    unsigned int csr_addr;
    unsigned int result;

    ctassert(__is_ct_const(mecsr));

    csr_addr = mecsr>>2;

    __asm {
        local_csr_rd[__ct_const_val(csr_addr)];
        immed[result, 0];
    }

    return result;
}

__intrinsic void
local_csr_write(int mecsr, unsigned int data)
{
    unsigned int csr_addr;

    ctassert(__is_ct_const(mecsr));

    csr_addr = mecsr>>2;

    __asm local_csr_wr[__ct_const_val(csr_addr), data];
}

__intrinsic void
ctx_wait(signal_t sig)
{
    ctassert(sig == kill || sig == voluntary || sig == bpt);

    if (sig == kill)
        __asm ctx_arb[kill];
    else if (sig == voluntary)
        __asm ctx_arb[voluntary];
    else
        __asm ctx_arb[bpt];
}

__intrinsic void
halt(void)
{
    __asm halt;
}

__intrinsic void
sleep(unsigned int cycles)
{
    SIGNAL sig;
    unsigned sig_num, tslo;

    __implicit_write(&sig);
    sig_num = __signal_number(&sig);
    tslo = local_csr_read(NFP_MECSR_TIMESTAMP_LOW);
    tslo += cycles >> 4;
    local_csr_write(NFP_MECSR_ACTIVE_CTX_FUTURE_COUNT, tslo);
    local_csr_write(NFP_MECSR_ACTIVE_FUTURE_COUNT_SIGNAL, sig_num);
    __asm ctx_arb[sig];
}

__intrinsic int
bit_test(unsigned int data, unsigned int bit_pos)
{
    int result = 1;

    ctassert(__is_ct_const(bit_pos));
    __asm {
        br_bset[data, __ct_const_val(bit_pos), match];
        alu[result, --, B, 0];
        match:
    }

    return result;
}

__intrinsic int
inp_state_test(int statename)
{
    int result = 1;

    ctassert(__is_ct_const(statename));

    __asm {
        br_inp_state[__ct_const_val(statename), match];
        alu[result, --, B, 0];
        match:
    }

    return result;
}

__intrinsic unsigned int
__ME(void)
{
    unsigned int menum;
    struct nfp_mecsr_active_ctx_sts ctxsts;

    ctxsts.__raw = local_csr_read(NFP_MECSR_ACTIVE_CTX_STS);
    menum = (ctxsts.il_id << 4) + ctxsts.me_id;

    return menum;
}
