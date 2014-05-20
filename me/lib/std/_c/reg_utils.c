/*
 * Copyright (C) 2014, Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/std/_c/reg_utils.c
 * @brief         Functions to treat structures in registers as memory.
 */

#ifndef _STD__REG_UTILS_C_
#define _STD__REG_UTILS_C_

#include <assert.h>
#include <nfp.h>
#include <types.h>
#include <std/reg_utils.h>

/* This module provides functions to manipulate "memory" regions
 * located in registers (or local memory).  Programs often cache data
 * structures in arrays of registers and it is convenient to have
 * functions to zero or compare these structures.  Unfortunately, the
 * compiler does not provide full support for arrays and such located
 * in all types of registers (primarily due to not all registers sets
 * being addressable via index registers).  This module provides some
 * utility functions, manually unrolling loops.
 */

/* TODO: Investigate if a register type is indexable, convert to a loop. */
/* TODO: Expand to handle larger 128 if in 4 context mode. */

__intrinsic
void
reg_zero(void *s, size_t n)
{
    unsigned int *t = s;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(s));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

    switch (n) {
    case 4:
        t[ 0] = 0;
        break;

    case 8:
        t[ 0] = 0; t[ 1] = 0;
        break;

    case 12:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0;
        break;

    case 16:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        break;

    case 20:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0;
        break;

    case 24:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0;
        break;

    case 28:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0;
        break;

    case 32:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        break;

    case 36:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0;
        break;

    case 40:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0;
        break;

    case 44:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0; t[10] = 0;
        break;

    case 48:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0; t[10] = 0; t[11] = 0;
        break;

    case 52:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0; t[10] = 0; t[11] = 0;
        t[12] = 0;
        break;

    case 56:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0; t[10] = 0; t[11] = 0;
        t[12] = 0; t[13] = 0;
        break;

    case 60:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0; t[10] = 0; t[11] = 0;
        t[12] = 0; t[13] = 0; t[14] = 0;
        break;

    case 64:
        t[ 0] = 0; t[ 1] = 0; t[ 2] = 0; t[ 3] = 0;
        t[ 4] = 0; t[ 5] = 0; t[ 6] = 0; t[ 7] = 0;
        t[ 8] = 0; t[ 9] = 0; t[10] = 0; t[11] = 0;
        t[12] = 0; t[13] = 0; t[14] = 0; t[15] = 0;
        break;
    }
}


__intrinsic
void
reg_cp(void *d, void *s, size_t n)
{
    unsigned int *dst = d;
    unsigned int *src = s;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(d));
    ctassert(__is_in_reg_or_lmem(s));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

    switch (n) {
    case 4:
        dst[ 0] = src[ 0];
        break;

    case 8:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        break;

    case 12:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2];
        break;

    case 16:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        break;

    case 20:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4];
        break;

    case 24:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        break;

    case 28:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6];
        break;

    case 32:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        break;

    case 36:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8];
        break;

    case 40:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        break;

    case 44:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        dst[10] = src[10];
        break;

    case 48:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        dst[10] = src[10]; dst[11] = src[11];
        break;

    case 52:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        dst[10] = src[10]; dst[11] = src[11];
        dst[12] = src[12];
        break;

    case 56:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        dst[10] = src[10]; dst[11] = src[11];
        dst[12] = src[12]; dst[13] = src[13];
        break;

    case 60:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        dst[10] = src[10]; dst[11] = src[11];
        dst[12] = src[12]; dst[13] = src[13];
        dst[14] = src[14];
        break;

    case 64:
        dst[ 0] = src[ 0]; dst[ 1] = src[ 1];
        dst[ 2] = src[ 2]; dst[ 3] = src[ 3];
        dst[ 4] = src[ 4]; dst[ 5] = src[ 5];
        dst[ 6] = src[ 6]; dst[ 7] = src[ 7];
        dst[ 8] = src[ 8]; dst[ 9] = src[ 9];
        dst[10] = src[10]; dst[11] = src[11];
        dst[12] = src[12]; dst[13] = src[13];
        dst[14] = src[14]; dst[15] = src[15];
        break;
    }
}

__intrinsic int reg_eq(void *s1, void *s2, size_t n)
{
    unsigned int *t1 = s1;
    unsigned int *t2 = s2;
    int ret = 0;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(s1));
    ctassert(__is_in_reg_or_lmem(s2));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

    switch (n) {
    case 4:
        ret = t1[ 0] == t2[ 0];
        break;

    case 8:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1]);
        break;

    case 12:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2]);
        break;

    case 16:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3]);
        break;

    case 20:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4]);
        break;

    case 24:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5]);
        break;

    case 28:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6]);
        break;

    case 32:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7]);
        break;

    case 36:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8]);
        break;

    case 40:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9]);
        break;

    case 44:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9] &&
               t1[10] == t2[10]);
        break;

    case 48:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9] &&
               t1[10] == t2[10] && t1[11] == t2[11]);
        break;

    case 52:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9] &&
               t1[10] == t2[10] && t1[11] == t2[11] &&
               t1[12] == t2[12]);
        break;

    case 56:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9] &&
               t1[10] == t2[10] && t1[11] == t2[11] &&
               t1[12] == t2[12] && t1[13] == t2[13]);
        break;

    case 60:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9] &&
               t1[10] == t2[10] && t1[11] == t2[11] &&
               t1[12] == t2[12] && t1[13] == t2[13] &&
               t1[14] == t2[14]);
        break;

    case 64:
        ret = (t1[ 0] == t2[ 0] && t1[ 1] == t2[ 1] &&
               t1[ 2] == t2[ 2] && t1[ 3] == t2[ 3] &&
               t1[ 4] == t2[ 4] && t1[ 5] == t2[ 5] &&
               t1[ 6] == t2[ 6] && t1[ 7] == t2[ 7] &&
               t1[ 8] == t2[ 8] && t1[ 9] == t2[ 9] &&
               t1[10] == t2[10] && t1[11] == t2[11] &&
               t1[12] == t2[12] && t1[13] == t2[13] &&
               t1[14] == t2[14] && t1[15] == t2[15]);
        break;
    }
    return ret;
}

#endif /* !_STD__MEMREG_C_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
