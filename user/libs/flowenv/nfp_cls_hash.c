/*
 * Copyright 2014-15 Netronome, Inc.
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
 * @file          user/libs/flowenv/nfp_cls_hash.c
 * @brief         CLS hash compatible with ME version in libstd/hash
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "nfp_cls_hash.h"

/* 128-bit rotate functions */
static __uint128_t
rotl_128(__uint128_t value, int shift) {
    return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}

static __uint128_t
rotr_128(__uint128_t value, int shift) {
    return (value >> shift) | (value << (sizeof(value) * 8 - shift));
}

/*
 * The aim of this cls_hash function is to take the input data (key) A(x) and
 * multiply it by M(x) modulo2, and divide by a generator polynomial G(x) and
 * take the remainder R(x) as in:
 *  A(x) . M(x) = G(x) . Q(x) + R(x)
 *
 * Where G(x) comes from the IXP SHac for 64-bits:
 *  G(x) = x^64 + x^54 + x^35 + x^17 + 1
 *
 * Regardless of Q(x) what we need to calculate is R(x) which must be a
 * polynomial in the form Sum(i=0,63) r(i).x^i
 *
 * Assuming A(x).M(x) = x^64, then we must have Q(x)=1 so that Q(x).G(x) has
 * x^64 in it and no other higher powers of x. This means that if
 * A(x).M(x) = x^64 then
 *  R(x) = x^54 + x^35 + x^17 + 1
 *
 * Similarly, assuming A(x).M(x) = x^65 then
 *  R(x) = x^55 + x^36 + x^18 + x
 *
 * Continuing with this, you get to A(x).M(x) = x^74 where
 *  R(x) = x^64 + x^45 + x^27 + x^10;
 * but now we also have to go back to R(x) for x^64, so this actually gets to
 *  R(x) = x^45 + x^27 + x^10 + x^54 + x^35 + x^17 + 1
 *
 * You can continue this forever. Now, A(x).M(x) is a polynomial of order 126 at
 * most, and so we only need to find out the remainders for x^64 through x^126.
 */
uint64_t
cls_hash(void *key, uint32_t mbits, uint32_t size)
{
    __uint128_t prod;
    __uint128_t scratch;
    __uint128_t maskclr = 0xffffffffffffffff;
    __uint128_t remainder = 0;
    uint64_t high;
    uint64_t key_idx;

    uint32_t i;
    uint32_t words = size >> 3;
    const uint64_t c1 = 1;

    /* Mask preserves top 64 bits and clears bottom 64-bits during hash calc */
    maskclr = maskclr << 64;

    for (i = 0; i < words; i++) {
        key_idx = ((uint64_t*)key)[i];

        /* Remainder is initialized to zero. This simulates hash_mask_clear
           in micro code. */
        prod =  (remainder << 64) + key_idx;

        /* hash multiplication equation
           m63.x^63 + m53.x^53 + m36.x^36 + m4.x^4 */
        if ( mbits & CLS_HASH_M4 ) {
            scratch = ((prod >> 4 ) ^ key_idx);
            prod = rotr_128(prod, 4) & maskclr;
            prod = prod | scratch;
            prod = rotl_128(prod, 4);
        }

        if ( mbits & CLS_HASH_M36 ) {
            scratch = ((prod >> 36 ) ^ key_idx);
            prod = rotr_128(prod, 36) & maskclr;
            prod = prod | scratch;
            prod = rotl_128(prod, 36);
        }

        if ( mbits & CLS_HASH_M53 ) {
            scratch = ((prod >> 53 ) ^ key_idx);
            prod = rotr_128(prod, 53) & maskclr;
            prod = prod | scratch;
            prod = rotl_128(prod, 53);
        }

        if ( mbits & CLS_HASH_M63 ) {
            scratch = ((prod >> 63 ) ^ key_idx);
            prod = rotr_128(prod, 63) & maskclr;
            prod = prod | scratch;
            prod = rotl_128(prod, 63);
        }

        /* Use the high word bits to select the generator polynomial and
           calculate the remainder. */
        remainder = prod & 0xffffffffffffffff;
        high = (prod >> 64) & 0xffffffffffffffff;

        if (high & (c1<< 0)) { remainder = remainder ^ 0x0040000800020001; }
        if (high & (c1<< 1)) { remainder = remainder ^ 0x0080001000040002; }
        if (high & (c1<< 2)) { remainder = remainder ^ 0x0100002000080004; }
        if (high & (c1<< 3)) { remainder = remainder ^ 0x0200004000100008; }
        if (high & (c1<< 4)) { remainder = remainder ^ 0x0400008000200010; }
        if (high & (c1<< 5)) { remainder = remainder ^ 0x0800010000400020; }
        if (high & (c1<< 6)) { remainder = remainder ^ 0x1000020000800040; }
        if (high & (c1<< 7)) { remainder = remainder ^ 0x2000040001000080; }
        if (high & (c1<< 8)) { remainder = remainder ^ 0x4000080002000100; }
        if (high & (c1<< 9)) { remainder = remainder ^ 0x8000100004000200; }
        if (high & (c1<<10)) { remainder = remainder ^ 0x0040200808020401; }
        if (high & (c1<<11)) { remainder = remainder ^ 0x0080401010040802; }
        if (high & (c1<<12)) { remainder = remainder ^ 0x0100802020081004; }
        if (high & (c1<<13)) { remainder = remainder ^ 0x0201004040102008; }
        if (high & (c1<<14)) { remainder = remainder ^ 0x0402008080204010; }
        if (high & (c1<<15)) { remainder = remainder ^ 0x0804010100408020; }
        if (high & (c1<<16)) { remainder = remainder ^ 0x1008020200810040; }
        if (high & (c1<<17)) { remainder = remainder ^ 0x2010040401020080; }
        if (high & (c1<<18)) { remainder = remainder ^ 0x4020080802040100; }
        if (high & (c1<<19)) { remainder = remainder ^ 0x8040101004080200; }
        if (high & (c1<<20)) { remainder = remainder ^ 0x00c0202808120401; }
        if (high & (c1<<21)) { remainder = remainder ^ 0x0180405010240802; }
        if (high & (c1<<22)) { remainder = remainder ^ 0x030080a020481004; }
        if (high & (c1<<23)) { remainder = remainder ^ 0x0601014040902008; }
        if (high & (c1<<24)) { remainder = remainder ^ 0x0c02028081204010; }
        if (high & (c1<<25)) { remainder = remainder ^ 0x1804050102408020; }
        if (high & (c1<<26)) { remainder = remainder ^ 0x30080a0204810040; }
        if (high & (c1<<27)) { remainder = remainder ^ 0x6010140409020080; }
        if (high & (c1<<28)) { remainder = remainder ^ 0xc020280812040100; }
        if (high & (c1<<29)) { remainder = remainder ^ 0x80005018240a0201; }
        if (high & (c1<<30)) { remainder = remainder ^ 0x0040a03848160403; }
        if (high & (c1<<31)) { remainder = remainder ^ 0x00814070902c0806; }
        if (high & (c1<<32)) { remainder = remainder ^ 0x010280e12058100c; }
        if (high & (c1<<33)) { remainder = remainder ^ 0x020501c240b02018; }
        if (high & (c1<<34)) { remainder = remainder ^ 0x040a038481604030; }
        if (high & (c1<<35)) { remainder = remainder ^ 0x0814070902c08060; }
        if (high & (c1<<36)) { remainder = remainder ^ 0x10280e12058100c0; }
        if (high & (c1<<37)) { remainder = remainder ^ 0x20501c240b020180; }
        if (high & (c1<<38)) { remainder = remainder ^ 0x40a0384816040300; }
        if (high & (c1<<39)) { remainder = remainder ^ 0x814070902c080600; }
        if (high & (c1<<40)) { remainder = remainder ^ 0x02c0e12858120c01; }
        if (high & (c1<<41)) { remainder = remainder ^ 0x0581c250b0241802; }
        if (high & (c1<<42)) { remainder = remainder ^ 0x0b0384a160483004; }
        if (high & (c1<<43)) { remainder = remainder ^ 0x16070942c0906008; }
        if (high & (c1<<44)) { remainder = remainder ^ 0x2c0e12858120c010; }
        if (high & (c1<<45)) { remainder = remainder ^ 0x581c250b02418020; }
        if (high & (c1<<46)) { remainder = remainder ^ 0xb0384a1604830040; }
        if (high & (c1<<47)) { remainder = remainder ^ 0x6030942409040081; }
        if (high & (c1<<48)) { remainder = remainder ^ 0xc061284812080102; }
        if (high & (c1<<49)) { remainder = remainder ^ 0x8082509824120205; }
        if (high & (c1<<50)) { remainder = remainder ^ 0x0144a1384826040b; }
        if (high & (c1<<51)) { remainder = remainder ^ 0x02894270904c0816; }
        if (high & (c1<<52)) { remainder = remainder ^ 0x051284e12098102c; }
        if (high & (c1<<53)) { remainder = remainder ^ 0x0a2509c241302058; }
        if (high & (c1<<54)) { remainder = remainder ^ 0x144a1384826040b0; }
        if (high & (c1<<55)) { remainder = remainder ^ 0x2894270904c08160; }
        if (high & (c1<<56)) { remainder = remainder ^ 0x51284e12098102c0; }
        if (high & (c1<<57)) { remainder = remainder ^ 0xa2509c2413020580; }
        if (high & (c1<<58)) { remainder = remainder ^ 0x44e1384026060b01; }
        if (high & (c1<<59)) { remainder = remainder ^ 0x89c270804c0c1602; }
        if (high & (c1<<60)) { remainder = remainder ^ 0x13c4e108981a2c05; }
        if (high & (c1<<61)) { remainder = remainder ^ 0x2789c2113034580a; }
        if (high & (c1<<62)) { remainder = remainder ^ 0x4f1384226068b014; }
        if (high & (c1<<63)) { remainder = remainder ^ 0x9e270844c0d16028; }
    }

    /* nfcc is little word endian, so the words need swapped here */
    return (remainder<<32) | (remainder>>32);
}
