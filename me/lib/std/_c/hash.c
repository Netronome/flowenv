/*
 * Copyright (C) 2014-2015,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/std/_c/hash.c
 * @brief         Functions to perform a hash over a register region.
 */

#ifndef _STD__HASH_C_
#define _STD__HASH_C_

#include <assert.h>
#include <nfp.h>
#include <std/hash.h>

/* macro for hash_me_crc32 and hash_me_crc32c implementation */
#define _HASH_SWITCH_CASE_IMPLEMENT(n, EXEC_MACRO)                          \
{                                                                           \
    switch (n) {                                                            \
        case 4:                                                             \
            EXEC_MACRO( 0);                                                 \
            break;                                                          \
        case 8:                                                             \
            EXEC_MACRO( 0); EXEC_MACRO( 1);                                 \
            break;                                                          \
        case 12:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2);                 \
            break;                                                          \
        case 16:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            break;                                                          \
        case 20:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4);                                                 \
            break;                                                          \
        case 24:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5);                                 \
            break;                                                          \
        case 28:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6);                 \
            break;                                                          \
        case 32:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            break;                                                          \
        case 36:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8);                                                 \
            break;                                                          \
        case 40:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9);                                 \
            break;                                                          \
        case 44:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9); EXEC_MACRO(10);                 \
            break;                                                          \
        case 48:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9); EXEC_MACRO(10); EXEC_MACRO( 11);\
            break;                                                          \
        case 52:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9); EXEC_MACRO(10); EXEC_MACRO(11); \
            EXEC_MACRO(12);                                                 \
            break;                                                          \
        case 56:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9); EXEC_MACRO(10); EXEC_MACRO(11); \
            EXEC_MACRO(12); EXEC_MACRO(13);                                 \
            break;                                                          \
        case 60:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9); EXEC_MACRO(10); EXEC_MACRO(11); \
            EXEC_MACRO(12); EXEC_MACRO(13); EXEC_MACRO(14);                 \
            break;                                                          \
        case 64:                                                            \
            EXEC_MACRO( 0); EXEC_MACRO( 1); EXEC_MACRO( 2); EXEC_MACRO( 3); \
            EXEC_MACRO( 4); EXEC_MACRO( 5); EXEC_MACRO( 6); EXEC_MACRO( 7); \
            EXEC_MACRO( 8); EXEC_MACRO( 9); EXEC_MACRO(10); EXEC_MACRO(11); \
            EXEC_MACRO(12); EXEC_MACRO(13); EXEC_MACRO(14); EXEC_MACRO(15); \
            break;                                                          \
        }                                                                   \
}



/* Note we could offer a function which does not require the size to
 * be multiple of 32bit but it would get really tedious to unroll */
__intrinsic uint32_t
hash_me_crc32(void *s, size_t n, uint32_t init)
{
    __gpr uint32_t result;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(s));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

    crc_write(init);

#ifdef __HASH_ME_CRC32
    #error "Attempting to redefine __HASH_ME_CRC32"
#endif

    /* every type has to be explicitly cast */
    if (__is_in_lmem(s)) {
#define __HASH_ME_CRC32(_x)                                       \
        crc_32_be(((__lmem unsigned int *)s)[_x], crc_bytes_0_3)

        _HASH_SWITCH_CASE_IMPLEMENT(n, __HASH_ME_CRC32)

#undef __HASH_ME_CRC32
    } else {
        /* normal register type */
#define __HASH_ME_CRC32(_x)                                       \
        crc_32_be(((__gpr unsigned int *)s)[_x], crc_bytes_0_3)

        _HASH_SWITCH_CASE_IMPLEMENT(n, __HASH_ME_CRC32)

#undef __HASH_ME_CRC32
    }

    /* when jira THSDK-1392 is fixed we should be able to do:
     *     return crc_read();
     * for the meantime we have to manually wait 5 cycles before
     * reading the crc_remainder
     */
    __asm {
        nop;
        nop;
        nop;
        nop;
        nop;
        local_csr_rd[crc_remainder];
        immed[result, 0];
    }

    return result;
}


/* Note we could offer a function which does not require the size to
 * be multiple of 32bit but it would get really tedious to unroll */
__intrinsic uint32_t
hash_me_crc32c(void *s, size_t n, uint32_t init)
{
    __gpr uint32_t result;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_reg_or_lmem(s));
    ctassert(__is_ct_const(n));
    ctassert(n <= 64);
    ctassert((n % 4) == 0);

    crc_write(init);

#ifdef __HASH_ME_CRC32C
    #error "Attempting to redefine __HASH_ME_CRC32C"
#endif

    /* every type has to be explicitly cast */
    if (__is_in_lmem(s)) {
#define __HASH_ME_CRC32C(_x)                                       \
        crc_iscsi_be(((__lmem unsigned int *)s)[_x], crc_bytes_0_3)

        _HASH_SWITCH_CASE_IMPLEMENT(n, __HASH_ME_CRC32C)

#undef __HASH_ME_CRC32C
    } else {
        /* normal register type */
#define __HASH_ME_CRC32C(_x)                                       \
        crc_iscsi_be(((__gpr unsigned int *)s)[_x], crc_bytes_0_3)

        _HASH_SWITCH_CASE_IMPLEMENT(n, __HASH_ME_CRC32C)

#undef __HASH_ME_CRC32C
    }

    /* when jira THSDK-1392 is fixed we should be able to do:
     *     return crc_read();
     * for the meantime we have to manually wait 5 cycles before
     * reading the crc_remainder
     */
    __asm {
        nop;
        nop;
        nop;
        nop;
        nop;
        local_csr_rd[crc_remainder];
        immed[result, 0];
    }

    return result;
}

#endif /* !_STD__HASH_C_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
