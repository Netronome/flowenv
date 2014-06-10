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

__intrinsic void
reg_zero(void *s, size_t n)
{
    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(s));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

#ifdef __REG_ZERO
    #error "Attempting to redefine __REG_ZERO"
#endif

#define __REG_ZERO(_x) ((unsigned int *)s)[_x] = 0

    /* switch on number of bytes */
    switch (n) {
    case 4:
        __REG_ZERO( 0);
        break;

    case 8:
        __REG_ZERO( 0); __REG_ZERO( 1);
        break;

    case 12:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2);
        break;

    case 16:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        break;

    case 20:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4);
        break;

    case 24:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5);
        break;

    case 28:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6);
        break;

    case 32:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        break;

    case 36:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8);
        break;

    case 40:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9);
        break;

    case 44:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9); __REG_ZERO(10);
        break;

    case 48:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9); __REG_ZERO(10); __REG_ZERO( 11);
        break;

    case 52:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9); __REG_ZERO(10); __REG_ZERO(11);
        __REG_ZERO(12);
        break;

    case 56:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9); __REG_ZERO(10); __REG_ZERO(11);
        __REG_ZERO(12); __REG_ZERO(13);
        break;

    case 60:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9); __REG_ZERO(10); __REG_ZERO(11);
        __REG_ZERO(12); __REG_ZERO(13); __REG_ZERO(14);
        break;

    case 64:
        __REG_ZERO( 0); __REG_ZERO( 1); __REG_ZERO( 2); __REG_ZERO( 3);
        __REG_ZERO( 4); __REG_ZERO( 5); __REG_ZERO( 6); __REG_ZERO( 7);
        __REG_ZERO( 8); __REG_ZERO( 9); __REG_ZERO(10); __REG_ZERO(11);
        __REG_ZERO(12); __REG_ZERO(13); __REG_ZERO(14); __REG_ZERO(15);
        break;
    }
#undef __REG_ZERO
}

__intrinsic void
reg_cp(void *d, void *s, size_t n)
{
    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(d));
    ctassert(__is_in_reg_or_lmem(s));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

#ifdef __REG_CP
    #error "Attempting to redefine __REG_CP"
#endif

#define __REG_CP(_x) (((unsigned int *)d)[_x] = ((unsigned int *)s)[_x])

    /* switch on number of bytes */
    switch (n) {
    case 4:
        __REG_CP( 0);
        break;

    case 8:
        __REG_CP( 0); __REG_CP( 1);
        break;

    case 12:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2);
        break;

    case 16:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        break;

    case 20:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4);
        break;

    case 24:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5);
        break;

    case 28:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6);
        break;

    case 32:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        break;

    case 36:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8);
        break;

    case 40:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9);
        break;

    case 44:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9); __REG_CP(10);
        break;

    case 48:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9); __REG_CP(10); __REG_CP(11);
        break;

    case 52:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9); __REG_CP(10); __REG_CP(11);
        __REG_CP(12);
        break;

    case 56:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9); __REG_CP(10); __REG_CP(11);
        __REG_CP(12); __REG_CP(13);
        break;

    case 60:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9); __REG_CP(10); __REG_CP(11);
        __REG_CP(12); __REG_CP(13); __REG_CP(14);
        break;

    case 64:
        __REG_CP( 0); __REG_CP( 1); __REG_CP( 2); __REG_CP( 3);
        __REG_CP( 4); __REG_CP( 5); __REG_CP( 6); __REG_CP( 7);
        __REG_CP( 8); __REG_CP( 9); __REG_CP(10); __REG_CP(11);
        __REG_CP(12); __REG_CP(13); __REG_CP(14); __REG_CP(15);
        break;
    }
#undef __REG_CP
}

__intrinsic int
reg_eq(void *s1, void *s2, size_t n)
{
    int ret = 0;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(s1));
    ctassert(__is_in_reg_or_lmem(s2));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

#ifdef __REG_EQ
    #error "Attempting to redefine __REG_EQ"
#endif

#define __REG_EQ(_x) (((unsigned int *)s1)[_x] == ((unsigned int *)s2)[_x])

    /* switch on number of bytes */
    switch (n) {
    case 4:
        ret = __REG_EQ( 0);
        break;

    case 8:
        ret = (__REG_EQ( 0) && __REG_EQ( 1));
        break;

    case 12:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2));
        break;

    case 16:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3));
        break;

    case 20:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4));
        break;

    case 24:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5));
        break;

    case 28:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6));
        break;

    case 32:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7));
        break;

    case 36:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8));
        break;

    case 40:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9));
        break;

    case 44:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9) && __REG_EQ(10));
        break;

    case 48:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9) && __REG_EQ(10) && __REG_EQ(11));
        break;

    case 52:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9) && __REG_EQ(10) && __REG_EQ(11) &&
               __REG_EQ(12));
        break;

    case 56:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9) && __REG_EQ(10) && __REG_EQ(11) &&
               __REG_EQ(12) && __REG_EQ(13));
        break;

    case 60:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9) && __REG_EQ(10) && __REG_EQ(11) &&
               __REG_EQ(12) && __REG_EQ(13) && __REG_EQ(14));
        break;

    case 64:
        ret = (__REG_EQ( 0) && __REG_EQ( 1) && __REG_EQ( 2) && __REG_EQ( 3) &&
               __REG_EQ( 4) && __REG_EQ( 5) && __REG_EQ( 6) && __REG_EQ( 7) &&
               __REG_EQ( 8) && __REG_EQ( 9) && __REG_EQ(10) && __REG_EQ(11) &&
               __REG_EQ(12) && __REG_EQ(13) && __REG_EQ(14) && __REG_EQ(15));
        break;
    }
    return ret;
#undef __REG_EQ
}

#endif /* !_STD__MEMREG_C_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
