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
 * @file          user/libs/flowenv/nfp_me_crc.c
 * @brief         CRC computation code matching hash_me_crc*[] on the MEs.
 */

#ifndef _NFP_ME_CRC_H
#define _NFP_ME_CRC_H

#include <stdint.h>
#include <stddef.h>

/**
 * Compute the CRC-32 of a byte stream given an initial remainder.
 *
 * @rem:        Initial remainder
 * @p:          Pointer to data to compute CRC over
 * @size:       Size of the data
 * @return:     CRC32 of the data
 *
 * This function does not complement the remainder going in or coming out.
 */
uint32_t nfp_me_crc32(uint32_t rem, void *p, size_t size);

/**
 * Compute the CRC-32C of a byte stream given an initial remainder.
 *
 * @rem:        Initial remainder
 * @p:          Pointer to data to compute CRC over
 * @size:       Size of the data
 * @return:     CRC32C of the data
 *
 * CRC32c is also known as CRC-iSCSI.
 *
 * This function does not complement the remainder going in or coming out.
 */
uint32_t nfp_me_crc32c(uint32_t rem, void *p, size_t len);

#endif  /* _NFP_ME_CRC_H */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
