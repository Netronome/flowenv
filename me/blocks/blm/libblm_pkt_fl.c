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
 *
 * A Micro-c implementation for buffer allocation and free from the BLM
 * EMU rings.
 * see blm_iface_c.h for RING IDs allocation and for Ring memory
 * allocation.
 * The BLM code will initialize the rings (i.e. write the queue descriptors)
 * when the compile time swith "BLM_INIT_EMU_RINGS" is defined.
 *
 * This implemetation tries to folow the ASM inplementation.
 * (See libblm_pkt_fl.uc for ASM details).
 *
 * @file        libblm_pkt_fl.c
 * @brief
 *
 */

#include "libblm_pkt_fl.h"
#include <nfp6000/nfp_me.h>

__intrinsic mem_ring_addr_t
nfp_blm_buf_get_ring_addr(__addr40 void* rbase)
{
    return mem_ring_get_addr(rbase);
}

__intrinsic void
__nfp_blm_buf_alloc_base40(__xread void* pBuf, unsigned int rnum,
                           __addr40 void* rbase, unsigned int count,
                           SIGNAL_PAIR *sigpair, sync_t sync)
{
    mem_ring_addr_t raddr_hi;
    raddr_hi = mem_ring_get_addr(rbase);
    __mem_ring_get(rnum, raddr_hi, pBuf, (count<<2), 64, sync, sigpair);
}

__intrinsic void
__nfp_blm_buf_alloc(__xread void* pBuf, unsigned int rnum,
                    mem_ring_addr_t rbase, unsigned int count,
                    SIGNAL_PAIR *sigpair, sync_t sync)
{
    __mem_ring_get(rnum, rbase, pBuf, (count<<2), 64, sync, sigpair);
}

__intrinsic int
nfp_blm_buf_alloc_base40(__xread void* pBuf, unsigned int rnum,
                         __addr40 void* rbase, unsigned int count)
{
    mem_ring_addr_t raddr_hi;
    raddr_hi = mem_ring_get_addr(rbase);
    return mem_ring_get(rnum, raddr_hi, pBuf, (count << 2));
}

__intrinsic int
nfp_blm_buf_alloc(__xread void* pBuf, unsigned int rnum, mem_ring_addr_t rbase,
                  unsigned int count)
{
    return mem_ring_get(rnum, rbase, pBuf, (count << 2));
}

__intrinsic void
__nfp_blm_buf_free_base40(__xrw void* pBuf, unsigned int rnum,
                          __addr40 void* rbase, unsigned int count,
                          SIGNAL_PAIR *sigpair, sync_t sync)
{
    mem_ring_addr_t raddr_hi;
    raddr_hi = mem_ring_get_addr(rbase);
    __mem_ring_put(rnum, raddr_hi, pBuf, (count << 2), 64, sync, sigpair);
}

__intrinsic void
__nfp_blm_buf_free(__xrw void* pBuf, unsigned int rnum, mem_ring_addr_t rbase,
                   unsigned int count, SIGNAL_PAIR *sigpair, sync_t sync)
{
    __mem_ring_put(rnum, rbase, pBuf, (count << 2), 64, sync, sigpair);
}

__intrinsic int
nfp_blm_buf_free_base40(__xrw void* pBuf, unsigned int rnum,
                        __addr40 void* rbase, unsigned int count)
{
    mem_ring_addr_t raddr_hi;
    raddr_hi = mem_ring_get_addr(rbase);
    return mem_ring_put(rnum, raddr_hi, pBuf, (count << 2));
}

__intrinsic int
nfp_blm_buf_free(__xrw void* pBuf, unsigned int rnum, mem_ring_addr_t rbase,
                 unsigned int count)
{
    return mem_ring_put(rnum, rbase, pBuf, (count << 2));
}

__intrinsic void
nfp_blm_buf_free_j_base40(void* pBuf, unsigned int rnum, __addr40 void* rbase)
{
    mem_ring_addr_t raddr_hi;
    raddr_hi = mem_ring_get_addr(rbase);
    nfp_blm_buf_free_j(pBuf, rnum, raddr_hi);
}

__intrinsic void
nfp_blm_buf_free_j(void* pBuf, unsigned int rnum, mem_ring_addr_t rbase)
{
    struct nfp_mecsr_prev_alu ind;
    ind.__raw = 0;
    ind.data16 = rnum;
    ind.ove_data = 1;
    __asm {
        alu[--, --, B, ind.__raw];
        mem[fast_journal,--, rbase, <<8, pBuf], indirect_ref;
    }
}
