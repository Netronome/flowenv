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
 *
 * @file          libblm_pkt_fl.h
 * @brief         Buffers alloc and free using BLM EMU rings.
 */

#ifndef __NFP_BLM_BUF_API_H__
#define __NFP_BLM_BUF_API_H__

/* flowenv dependency */
#include "mem_ring.h"


/**
 * Get the EMU ring base address.
 *
 * @param rbase [in] The ring's memory base address (use the names allocated
 *                   in blm_iface_c.h)
 */
__intrinsic mem_ring_addr_t nfp_blm_buf_get_ring_addr(__addr40 void* rbase);

/**
 * Allocate buffers from the BLM EMU rings.
 *
 * @param pBuf      [out] Packet buffer Transfer register array.
 * @param rnum      [in]  The ring number to allocate the buffer(s) from.
 * @param rbase     [in]  The ring's memory base address (use the names
 *                         allocated in blm_iface_c.h)
 * @param count     [in]  Number of buffers to allocate
 * @param sigpair   [in]  Signal Pair to use
 * @param sync      [in]  Sync type to use (sig_done or sig_wait)
 */
__intrinsic void __nfp_blm_buf_alloc_base40(__xread void *pBuf,
                                            unsigned int rnum,
                                            __addr40 void *rbase,
                                            unsigned int count,
                                            SIGNAL_PAIR *sigpair,
                                            sync_t sync);

/**
 * Allocate buffers from the BLM EMU rings.
 *
 * @param pBuf      [out] Packet buffer Transfer register array.
 * @param rnum      [in]  The ring number to allocate the buffer(s) from.
 * @param rbase     [in]  The ring's memory address - as returned from
 *                        nfp_blm_buf_get_ring_addr()
 * @param count     [in]  Number of buffers to allocate
 * @param sigpair   [in]  Signal Pair to use
 * @param sync      [in]  Sync type to use (sig_done or sig_wait)
 */
__intrinsic void __nfp_blm_buf_alloc(__xread void* pBuf, unsigned int rnum,
                                     mem_ring_addr_t rbase, unsigned int count,
                                     SIGNAL_PAIR *sigpair, sync_t sync);

/**
 * Allocate buffers from the BLM EMU rings.
 *
 * @param pBuf      [out] Packet buffer Transfer register array.
 * @param rnum      [in]  The ring number to allocate the buffer(s) from.
 * @param rbase     [in]  The ring's memory base address
                          (use the names allocated in blm_iface_c.h)
 * @param count     [in]  Number of buffers to allocate
 *
 * @return 0 on success -1 on error
 */
__intrinsic int nfp_blm_buf_alloc_base40(__xread void* pBuf, unsigned int rnum,
                                         __addr40 void* rbase,
                                         unsigned int count);

/**
 * Allocate buffers from the BLM EMU rings.
 *
 * @param pBuf      [out] Packet buffer Transfer register array.
 * @param rnum      [in]  The ring number to allocate the buffer(s) from.
 * @param rbase     [in]  The ring's memory base address
 *                        as returned from nfp_blm_buf_get_ring_addr
 * @param count     [in]  Number of buffers to allocate
 *
 * @return 0 on success -1 on error
 */
__intrinsic int nfp_blm_buf_alloc(__xread void* pBuf, unsigned int rnum,
                                  mem_ring_addr_t rbase, unsigned int count);

/**
 * Free buffers back into the BLM EMU ring.
 *
 * @param pBuf      [in] Packet buffer Transfer register array.
 * @param rnum      [in] The ring number to free the buffer(s) to.
 * @param rbase     [in] The ring's memory base address
 *                       (use the names allocated in blm_iface_c.h)
 * @param count     [in] Number of buffers to free
 * @param sigpair   [in] Signal Pair to use
 * @param sync      [in] Sync type to use (sig_done or sig_wait)
 */
__intrinsic void __nfp_blm_buf_free_base40(__xrw void* pBuf, unsigned int rnum,
                                           __addr40 void* rbase,
                                           unsigned int count,
                                           SIGNAL_PAIR *sigpair, sync_t sync);

/**
 * Free buffers back into the BLM EMU ring.
 *
 * @param pBuf      [in] Packet buffer Transfer register array.
 * @param rnum      [in] The ring number to free the buffer(s) to.
 * @param rbase     [in] The ring's memory base address
 *                       as returned from nfp_blm_buf_get_ring_addr()
 * @param count     [in] Number of buffers to free
 * @param sigpair   [in] Signal Pair to use
 * @param sync      [in] Sync type to use (sig_done or sig_wait)
 */
__intrinsic void __nfp_blm_buf_free(__xrw void* pBuf, unsigned int rnum,
                                    mem_ring_addr_t rbase, unsigned int count,
                                    SIGNAL_PAIR *sigpair, sync_t sync);

/**
 * Free buffers back into the BLM EMU ring using ring "put" command.
 *
 * @param pBuf      [in] Packet buffer Transfer register array.
 * @param rnum      [in] The ring number to free the buffer(s) to.
 * @param rbase     [in] The ring's memory base address
 *                       (use the names allocated in blm_iface_c.h)
 * @param count     [in] Number of buffers to free
 *
 * @return the size of the ring before the free on success, -1 on error
 */
__intrinsic int nfp_blm_buf_free_base40(__xrw void* pBuf, unsigned int rnum,
                                        __addr40 void* rbase, unsigned int count);

/**
 * Free buffers back into the BLM EMU ring using ring "put" command.
 *
 * @param pBuf      [in] Packet buffer Transfer register array.
 * @param rnum      [in] The ring number to free the buffer(s) to.
 * @param rbase     [in] The ring's memory base address
 *                       as returned from nfp_blm_buf_get_ring_addr()
 * @param count     [in] Number of buffers to free
 *
 * @return the size of the ring before the free on success, -1 on error
 */
__intrinsic int nfp_blm_buf_free(__xrw void* pBuf, unsigned int rnum,
                                 mem_ring_addr_t rbase, unsigned int count);

/**
 * Free a single buffer back into the BLM EMU ring using
 * ring "fast_journal" command.
 *
 * @param pBuf      [in] Packet buffer Transfer register array.
 * @param rnum      [in] The ring number to free the buffer(s) to.
 * @param rbase     [in] The ring's memory base address
 *                       (use the names allocated in blm_iface_c.h)
 */
__intrinsic void nfp_blm_buf_free_j_base40(void* pBuf, unsigned int rnum,
                                           __addr40 void* rbase);

/*
 * Free a single buffer back into the BLM EMU ring using
 * ring "fast_journal" command.
 *
 * @param pBuf      [in] Packet buffer Transfer register array.
 * @param rnum      [in] The ring number to free the buffer(s) to.
 * @param rbase     [in] The ring's memory base address
 *                       as returned from nfp_blm_buf_get_ring_addr()
 */
__intrinsic void nfp_blm_buf_free_j(void* pBuf, unsigned int rnum,
                                    mem_ring_addr_t rbase);

#endif /* __NFP_BLM_BUF_API_H__ */
