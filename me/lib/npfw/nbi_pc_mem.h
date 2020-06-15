/*
 * Copyright (C) 2016-2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file   lib/npfw/nbi_pc_mem.h
 * @brief  NFP NBI Preclassifier memory interface.
 */

#ifndef _NPFW__NBI_PC_MEM_H_
#define _NPFW__NBI_PC_MEM_H_

#include <nfp.h>
#include <stdint.h>


/* NBI Preclassifier helper macros. */
#define NBI_PC_MEM_ENTRY_SIZE 16


/**
 * Copy 16B to the NBI Preclassifier local memory from ME local memory.
 *
 * @param nbi            NBI island to write to (0/1)
 * @param lmem_pri_addr  NBI Preclassifier local memory primary address to
 *                       write to, must be a multiple of 16.
 * @param lmem_sec_addr  NBI Preclassifier local memory secondary address to
 *                       write to, must be a multiple of 16, can be same as
 *                       primary address if no secondary address.
 * @param addr           Pointer to the ME local memory start address
 * @param size           Size of the read, must be a multiple of 16
 * @param sig            Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_lmem2pelm_copy(unsigned int nbi,
                                         uint32_t lmem_pri_addr,
                                         uint32_t lmem_sec_addr,
                                         __lmem void *addr, size_t size,
                                         SIGNAL *sig);

__intrinsic void nbi_pc_lmem2pelm_copy(unsigned int nbi, uint32_t lmem_pri_addr,
                                       uint32_t lmem_sec_addr,
                                       __lmem void *addr, size_t size);


/**
 * Copy 16B to the NBI Preclassifier shared memory from ME local memory.
 *
 * @param nbi            NBI island to write to (0/1)
 * @param smem_pri_addr  NBI Preclassifier shared memory primary address to
 *                       write to, must be a multiple of 16.
 * @param smem_sec_addr  NBI Preclassifier shared memory secondary address to
 *                       write to, must be a multiple of 16, can be same as
 *                       primary address if no secondary address.
 * @param addr           Pointer to the ME local memory start address
 * @param size           Size of the read, must be a multiple of 16
 * @param sig            Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_lmem2pesm_copy(unsigned int nbi,
                                         uint32_t smem_pri_addr,
                                         uint32_t smem_sec_addr,
                                         __lmem void *addr, size_t size,
                                         SIGNAL *sig);

__intrinsic void nbi_pc_lmem2pesm_copy(unsigned int nbi, uint32_t smem_pri_addr,
                                       uint32_t smem_sec_addr,
                                       __lmem void *addr, size_t size);


/**
 * Copy 16B to the NBI Preclassifier local memory from a memory location.
 *
 * @param nbi            NBI island to write to (0/1)
 * @param lmem_pri_addr  NBI Preclassifier local memory primary address to
 *                       write to, must be a multiple of 16.
 * @param lmem_sec_addr  NBI Preclassifier local memory secondary address to
 *                       write to, must be a multiple of 16, can be same as
 *                       primary address if no secondary address.
 * @param addr           40-bit pointer to the memory start address
 * @param size           Size of the read, must be a multiple of 16
 * @param sig            Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_mem2pelm_copy(unsigned int nbi,
                                        uint32_t lmem_pri_addr,
                                        uint32_t lmem_sec_addr,
                                        __mem void *addr, size_t size,
                                        SIGNAL *sig);

__intrinsic void nbi_pc_mem2pelm_copy(unsigned int nbi, uint32_t lmem_pri_addr,
                                      uint32_t lmem_sec_addr, __mem void *addr,
                                      size_t size);


/**
 * Copy 16B to the NBI Preclassifier shared memory from a memory location.
 *
 * @param nbi            NBI island to write to (0/1)
 * @param smem_pri_addr  NBI Preclassifier shared memory primary address to
 *                       write to, must be a multiple of 16.
 * @param smem_sec_addr  NBI Preclassifier shared memory secondary address to
 *                       write to, must be a multiple of 16, can be same as
 *                       primary address if no secondary address.
 * @param addr           40-bit pointer to the memory start address
 * @param size           Size of the read, must be a multiple of 16
 * @param sig            Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_mem2pesm_copy(unsigned int nbi,
                                        uint32_t smem_pri_addr,
                                        uint32_t smem_sec_addr,
                                        __mem void *addr, size_t size,
                                        SIGNAL *sig);

__intrinsic void nbi_pc_mem2pesm_copy(unsigned int nbi, uint32_t smem_pri_addr,
                                      uint32_t smem_sec_addr, __mem void *addr,
                                      size_t size);


/**
 * Copy 16B from the NBI Preclassifier local memory into ME local memory.
 *
 * @param nbi        NBI island to read from (0/1)
 * @param lmem_addr  NBI Preclassifier local memory address to read from, must
 *                   be a multiple of 16.
 * @param addr       Pointer to the ME local memory start address
 * @param size       Size of the read, must be a multiple of 16
 * @param sig        Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_pelm2lmem_copy(unsigned int nbi, uint32_t lmem_addr,
                                         __lmem void *addr, size_t size,
                                         SIGNAL *sig);

__intrinsic void nbi_pc_pelm2lmem_copy(unsigned int nbi, uint32_t lmem_addr,
                                       __lmem void *addr, size_t size);


/**
 * Copy 16B from the NBI Preclassifier local memory into a memory location.
 *
 * @param nbi        NBI island to read from (0/1)
 * @param lmem_addr  NBI Preclassifier local memory address to read from, must
 *                   be a multiple of 16.
 * @param addr       40-bit pointer to the memory start address
 * @param size       Size of the read, must be a multiple of 16
 * @param sig        Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_pelm2mem_copy(unsigned int nbi, uint32_t lmem_addr,
                                        __mem void *addr, size_t size,
                                        SIGNAL *sig);

__intrinsic void nbi_pc_pelm2mem_copy(unsigned int nbi, uint32_t lmem_addr,
                                      __mem void *addr, size_t size);


/**
 * Copy 16B from the NBI Preclassifier shared memory into ME local memory.
 *
 * @param nbi        NBI island to read from (0/1)
 * @param smem_addr  NBI Preclassifier shared memory address to read from, must
 *                   be a multiple of 16.
 * @param addr       Pointer to the ME local memory start address
 * @param size       Size of the read, must be a multiple of 16
 * @param sig        Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_pesm2lmem_copy(unsigned int nbi, uint32_t smem_addr,
                                         __lmem void *addr, size_t size,
                                         SIGNAL *sig);

__intrinsic void nbi_pc_pesm2lmem_copy(unsigned int nbi, uint32_t smem_addr,
                                       __lmem void *addr, size_t size);


/**
 * Copy 16B from the NBI Preclassifier shared memory into a memory location.
 *
 * @param nbi        NBI island to read from (0/1)
 * @param smem_addr  NBI Preclassifier shared memory address to read from, must
 *                   be a multiple of 16.
 * @param addr       40-bit pointer to the memory start address
 * @param size       Size of the read, must be a multiple of 16
 * @param sig        Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_pc_pesm2mem_copy(unsigned int nbi, uint32_t smem_addr,
                                        __mem void *addr, size_t size,
                                        SIGNAL *sig);

__intrinsic void nbi_pc_pesm2mem_copy(unsigned int nbi, uint32_t smem_addr,
                                      __mem void *addr, size_t size);


#endif /* !_NPFW__NBI_PC_MEM_H_ */
