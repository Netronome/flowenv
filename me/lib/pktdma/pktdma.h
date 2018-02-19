/*
 * Copyright (C) 2015-2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/pktdma/pktdma.h
 * @brief         Memory Unit Packet Engine DMA with semaphore protection
 */
#ifndef _PKTDMA__PKTDMA_H_
#define _PKTDMA__PKTDMA_H_

#include <nfp.h>
#include <stdint.h>
#include <types.h>

/**
 * DMA from MU to CTM with semaphore protection.
 *
 * @param ctm_addr  32-bit pointer to the CTM start address
 * @param mem_addr  40-bit pointer to the MU start address
 * @param size      Size of the DMA, must be a multiple of 64B and <= 2048B
 * @param poll_int  Cycles to wait if no credits are available
 *
 * @note poll_int must be less than 0x00100000 (1<<20), see sleep().
 *       pktdma_mu_to_ctm() uses SYNCH_SEM_DEFAULT_POLL.  Use
 *       __pktdma_mu_to_ctm() and increase the interval if there is high
 *       contention for credits.
 * @note Use the real-address mode for ctm_addr, not the packet-address mode
 */
__intrinsic void
__pktdma_mu_to_ctm(__ctm40 void* ctm_addr, __mem40 void* mem_addr, size_t size,
                   uint32_t poll_int);

__intrinsic void
pktdma_mu_to_ctm(__ctm40 void* ctm_addr, __mem40 void* mem_addr, size_t size);

/**
 * DMA from CTM to MU with semaphore protection.
 *
 * @param mem_addr  40-bit pointer to the MU start address
 * @param ctm_addr  32-bit pointer to the CTM start address
 * @param size      Size of the DMA, must be a multiple of 64B and <= 2048B
 * @param poll_int  Cycles to wait if no credits are available
 *
 * @note poll_int must be less than 0x00100000 (1<<20), see sleep().
 *       pktdma_ctm_to_mu() uses SYNCH_SEM_DEFAULT_POLL.  Use
 *       __pktdma_ctm_to_mu() and increase the interval if there is high
 *       contention for credits.
 * @note Use the real-address mode for ctm_addr, not the packet-address mode
 */
__intrinsic void
__pktdma_ctm_to_mu(__mem40 void* mem_addr, __ctm40 void* ctm_addr, size_t size,
                   uint32_t poll_int);

__intrinsic void
pktdma_ctm_to_mu(__mem40 void* mem_addr, __ctm40 void* ctm_addr, size_t size);

#endif  /*_PKTDMA__PKTDMA_H_*/
