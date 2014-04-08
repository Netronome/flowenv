/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/libnfp.c
 * @brief         Standard library for NFP
 */


#include <assert.h>
#include <nfp.h>

#include <nfp6000/nfp_me.h>

/*
 * The following files implement all the functionality in <nfp/*.h>.
 * They may only have dependencies on <nfp.h> and the other include
 * files in <nfp/*.h>.  They are not protected by header guards and
 * should not be included elsewhere.
 */
#include "_c/cls.c"
#include "_c/me.c"
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


