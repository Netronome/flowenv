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
 * @file          user/libs/flowenv/nfp_cls_hash.h
 * @brief         CLS hash compatible with ME version in libstd/hash
 */

#ifndef _NFP_CLS_HASH_H
#define _NFP_CLS_HASH_H

#include <stdint.h>

#define CLS_HASH_M4     (1 << 0)
#define CLS_HASH_M36    (1 << 1)
#define CLS_HASH_M53    (1 << 2)
#define CLS_HASH_M63    (1 << 3)

/**
 * Create a 64-bit hash over a key in LMEM, GPR, NN reg, xread reg
 * @param key       Pointer to the start of the key
 * @param mbits     Represent the Mult values in the hash multiply register
 * @param size      Size of the key, must be a multiple of 8.
 * @return a 64-bit hash of the key
 *
 * @note Choose mbits by ORing CLS_HASH_M# values together.
 */
uint64_t cls_hash(void *key, uint32_t mbits, uint32_t size);

#endif  /* _NFP_CLS_HASH_H */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
