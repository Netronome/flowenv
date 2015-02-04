/*
 * Copyright (C) 2012-2015,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/net/gre.h
 * @brief         Definitions for GRE header parsing
 *
 * Incomplete, new definitions will be added as/when needed
 */

#ifndef _NET_GRE_H_
#define _NET_GRE_H_

/**
 * GRE Flags
 */
#define NET_GRE_FLAGS_SEQ_PRESENT      0x1
#define NET_GRE_FLAGS_KEY_PRESENT      0x2
#define NET_GRE_FLAGS_CSUM_PRESENT     0x8

#if defined(__NFP_LANG_MICROC)
#include <nfp.h>
#include <stdint.h>

/**
 * GRE header structure
 */
__packed struct gre_hdr {
    uint8_t  flags;                     /** Flags */
    uint8_t  misc;                      /** Misc bits */
    uint16_t proto;                     /** Protocol */
    /* Potentially followed by 32bit words depending on flags */
};
#endif /* __NFP_LANG_MICROC */

#endif /* _NET_GRE_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
