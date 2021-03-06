/*
 * Copyright (C) 2017,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/net/esp.h
 * @brief         Definitions for ESP header parsing
 *
 * Incomplete, new definitions will be added as/when needed
 */

#ifndef _NET_ESP_H_
#define _NET_ESP_H_

/**
 * ESP type definitions
 */

#if defined(__NFP_LANG_MICROC)

#include <nfp.h>
#include <stdint.h>

/**
 * ESP Header structure
 */
__packed struct esp_hdr {
    uint32_t spi;   /** Security Parameters Index  */
    uint32_t seq;   /** Sequence Number  */
};

#endif /* __NFP_LANG_MICROC */

#endif /* _NET_ESP_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
