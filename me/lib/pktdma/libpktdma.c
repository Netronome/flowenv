/*
 * Copyright (C) 2014-2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file        /lib/pktdma/libpktdma.c
 * @brief       Memory Unit Packet Engine DMA with semaphore protection
 */

#include <nfp.h>
#include <stdint.h>
#include <types.h>

#include <std/synch.h>
#include <nfp/mem_pe.h>
#include <nfp/mem_atomic.h>

/* You may have no more than 16 outstanding DMA commands per CTM. */
#define DMA_CMDS_PER_CTM   16

SEM_CLS_DECLARE(libpktdma_sem, DMA_CMDS_PER_CTM);

__intrinsic void
__pktdma_mu_to_ctm(__ctm40 void* ctm_addr, __mem40 void* mem_addr, size_t size,
                   uint32_t poll_int)
{
    SEM_WAIT(libpktdma_sem, poll_int);

    mem_pe_dma_mu_to_ctm(ctm_addr, mem_addr, size);

    SEM_POST(libpktdma_sem);
}

__intrinsic void
pktdma_mu_to_ctm(__ctm40 void* ctm_addr, __mem40 void* mem_addr, size_t size)
{
    __pktdma_mu_to_ctm(ctm_addr, mem_addr, size, SYNCH_SEM_DEFAULT_POLL);
}

__intrinsic void
__pktdma_ctm_to_mu(__mem40 void* mem_addr, __ctm40 void* ctm_addr, size_t size,
                   uint32_t poll_int)
{
    SEM_WAIT(libpktdma_sem, poll_int);

    mem_pe_dma_ctm_to_mu(mem_addr, ctm_addr, size);

    SEM_POST(libpktdma_sem);
}

__intrinsic void
pktdma_ctm_to_mu(__mem40 void* mem_addr, __ctm40 void* ctm_addr, size_t size)
{
    __pktdma_ctm_to_mu(mem_addr, ctm_addr, size, SYNCH_SEM_DEFAULT_POLL);
}
