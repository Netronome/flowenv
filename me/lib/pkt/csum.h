/*
 * Copyright 2012-2015 Netronome, Inc.
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
 * @file          lib/pkt/csum.h
 * @brief         Definitions for handling checksums
 *
 * This file contains definitions to handle the MAC checksum prepend
 * word, if configured.
 */

#ifndef _PKT_CSUM_H_
#define _PKT_CSUM_H_

/**
 * Header length definitions
 * @PKT_CSUM_PREPEND_LEN     RX/TX Checksum prepend length
 * @PKT_CSUM_PREPEND_LEN32   RX/TX Checksum prepend length
 */
#define PKT_CSUM_PREPEND_LEN    4
#define PKT_CSUM_PREPEND_LEN32  (PKT_CSUM_PREPEND_LEN / 4)

/**
 * Format of the CSUM RX prepend word as per section "10.2.10.4 Ingress
 * Parser" of the DB.
 *
 * The NFP MAC block can optionally check the L3/L4 checksum for
 * selected protocols and prepends the result to the buffer.  The
 * format is defined below.
 *
 * @NFP_MAC_RX_CSUM_L4_SUM_of   Summary of L4 checksum
 * @NFP_MAC_RX_CSUM_L3_of       L3 (checksum) summary
 * @NFP_MAC_RX_CSUM_CSUM_of     16-bit L4 TCP/UDP checksum if TCP/UDP is
 *                              parsable. If not 16-bit checksum for
 *                              received packet excluding CRC.
 */

#define NFP_MAC_RX_CSUM_L4_SUM_of(_x)           (((_x) >> 29) & 0x7)
#define   NFP_MAC_RX_CSUM_L4_UNSUP              (0)
#define   NFP_MAC_RX_CSUM_L4_ESP                (1)
#define   NFP_MAC_RX_CSUM_L4_TCP_OK             (2)
#define   NFP_MAC_RX_CSUM_L4_TCP_FAIL           (3)
/* Note UDP_OK is also returned when the checksum is not populated (=0) */
#define   NFP_MAC_RX_CSUM_L4_UDP_OK             (4)
#define   NFP_MAC_RX_CSUM_L4_UDP_FAIL           (5)
#define   NFP_MAC_RX_CSUM_L4_AUTH               (6)
#define   NFP_MAC_RX_CSUM_L4_FRAGMENT           (7)


#define NFP_MAC_RX_CSUM_L3_of(_x)               (((_x) >> 20) & 0x3)
#define   NFP_MAC_RX_CSUM_L3_UNKNOWN            (0)
#define   NFP_MAC_RX_CSUM_L3_IPV6               (1)
#define   NFP_MAC_RX_CSUM_L3_IPV4_FAIL          (2)
#define   NFP_MAC_RX_CSUM_L3_IPV4_OK            (3)

#define NFP_MAC_RX_CSUM_CSUM_of(_x)             ((_x) & 0xffff)

#endif /* _PKT_CSUM_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
