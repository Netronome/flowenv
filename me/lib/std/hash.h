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
 * @file          lib/std/hash.h
 * @brief         Functions to perform a hash over a register region.
 *
 * These functions manually unroll loops depending on the size_t
 * parameter. For good performance and small code size it is important
 * that the size parameter is a compile time constant.
 */

#ifndef _STD__HASH_H_
#define _STD__HASH_H_

#include <stdint.h>

/**
 * Compute the CRC32 over a region located in registers
 *
 * @param s     Pointer to a region
 * @param n     Size of region (in bytes)
 * @param init  Initial seed value
 * @return      CRC32 checksum
 *
 * @s can be located in GPR or NN register or LM.
 * @n must be a compile time constant and multiple of 4.
 */
__intrinsic uint32_t hash_me_crc32(void *s, size_t n, uint32_t init);

/**
 * Compute the CRC32-C (iSCSI)  over a region located in registers
 *
 * @param s     Pointer to a region
 * @param n     Size of region (in bytes)
 * @param init  Initial seed value
 * @return      CRC32-C checksum
 *
 * @s can be located in  GPR or NN register or LM.
 * @n must be a compile time constant and multiple of 4.
 */
 __intrinsic uint32_t hash_me_crc32c(void *s, size_t n, uint32_t init);

#endif /* !_STD__HASH_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
