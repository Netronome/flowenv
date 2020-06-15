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
 * @file   lib/npfw/nbi_cpp.h
 * @brief  NFP NBI CPP interface
 */

#ifndef _NPFW__NBI_CPP_H_
#define _NPFW__NBI_CPP_H_

#include <nfp.h>
#include <stdint.h>


/**
 * Copy a multiple of 8B (write64), 16B (write128), 32B (write256) to the
 * NBI/MAC from local memory, using the CPP interface.
 *
 * @param nbi       NBI/MAC island to write to (0/1)
 * @param nbi_addr  NBI/MAC address to write to, must be a multiple of 8
 * @param addr      Pointer to the local memory start address
 * @param size      Size of the write, must be a multiple of the base size
 * @param sig       Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_cpp_lmem2nbi_copy64(unsigned int nbi, uint32_t nbi_addr,
                                           __lmem void *addr, size_t size,
                                           SIGNAL *sig);

__intrinsic void __nbi_cpp_lmem2nbi_copy128(unsigned int nbi,
                                            uint32_t nbi_addr,
                                            __lmem void *addr, size_t size,
                                            SIGNAL *sig);

__intrinsic void __nbi_cpp_lmem2nbi_copy256(unsigned int nbi,
                                            uint32_t nbi_addr,
                                            __lmem void *addr, size_t size,
                                            SIGNAL *sig);

__intrinsic void nbi_cpp_lmem2nbi_copy64(unsigned int nbi, uint32_t nbi_addr,
                                         __lmem void *addr, size_t size);

__intrinsic void nbi_cpp_lmem2nbi_copy128(unsigned int nbi, uint32_t nbi_addr,
                                          __lmem void *addr, size_t size);

__intrinsic void nbi_cpp_lmem2nbi_copy256(unsigned int nbi, uint32_t nbi_addr,
                                          __lmem void *addr, size_t size);


/**
 * Copy a multiple of 8B (write64), 16B (write128), 32B (write256) to the
 * NBI/MAC from a memory location, using the CPP interface.
 *
 * @param nbi       NBI/MAC island to write to (0/1)
 * @param nbi_addr  NBI/MAC address to write to, must be a multiple of 8
 * @param addr      40-bit pointer to the memory start address
 * @param size      Size of the write, must be a multiple of the base size
 * @param sig       Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_cpp_mem2nbi_copy64(unsigned int nbi, uint32_t nbi_addr,
                                          __mem void *addr, size_t size,
                                          SIGNAL *sig);

__intrinsic void __nbi_cpp_mem2nbi_copy128(unsigned int nbi, uint32_t nbi_addr,
                                           __mem void *addr, size_t size,
                                           SIGNAL *sig);

__intrinsic void __nbi_cpp_mem2nbi_copy256(unsigned int nbi, uint32_t nbi_addr,
                                           __mem void *addr, size_t size,
                                           SIGNAL *sig);

__intrinsic void nbi_cpp_mem2nbi_copy64(unsigned int nbi, uint32_t nbi_addr,
                                        __mem void *addr, size_t size);

__intrinsic void nbi_cpp_mem2nbi_copy128(unsigned int nbi, uint32_t nbi_addr,
                                         __mem void *addr, size_t size);

__intrinsic void nbi_cpp_mem2nbi_copy256(unsigned int nbi, uint32_t nbi_addr,
                                         __mem void *addr, size_t size);


/**
 * Copy a multiple of 8B (read64), 16B (read128), 32B (read256) from the
 * NBI/MAC into local memory, using the CPP interface.
 *
 * @param nbi       NBI/MAC island to read from (0/1)
 * @param nbi_addr  NBI/MAC address to read from, must be a multiple of 8
 * @param addr      Pointer to the local memory start address
 * @param size      Size of the read, must be a multiple of the base size
 * @param sig       Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_cpp_nbi2lmem_copy64(unsigned int nbi, uint32_t nbi_addr,
                                           __lmem void *addr, size_t size,
                                           SIGNAL *sig);

__intrinsic void __nbi_cpp_nbi2lmem_copy128(unsigned int nbi,
                                            uint32_t nbi_addr,
                                            __lmem void *addr, size_t size,
                                            SIGNAL *sig);

__intrinsic void __nbi_cpp_nbi2lmem_copy256(unsigned int nbi,
                                            uint32_t nbi_addr,
                                            __lmem void *addr, size_t size,
                                            SIGNAL *sig);

__intrinsic void nbi_cpp_nbi2lmem_copy64(unsigned int nbi, uint32_t nbi_addr,
                                         __lmem void *addr, size_t size);

__intrinsic void nbi_cpp_nbi2lmem_copy128(unsigned int nbi, uint32_t nbi_addr,
                                          __lmem void *addr, size_t size);

__intrinsic void nbi_cpp_nbi2lmem_copy256(unsigned int nbi, uint32_t nbi_addr,
                                          __lmem void *addr, size_t size);


/**
 * Copy a multiple of 8B (read64), 16B (read128), 32B (read256) from the
 * NBI/MAC into a memory location, using the CPP interface.
 *
 * @param nbi       NBI/MAC island to read from (0/1)
 * @param nbi_addr  NBI/MAC address to read from, must be a multiple of 8
 * @param addr      40-bit pointer to the memory start address
 * @param size      Size of the read, must be a multiple of the base size
 * @param sig       Signal to use
 *
 * @note One or more ctx_swap's will be invoked with this function
 */
__intrinsic void __nbi_cpp_nbi2mem_copy64(unsigned int nbi, uint32_t nbi_addr,
                                          __mem void *addr, size_t size,
                                          SIGNAL *sig);

__intrinsic void __nbi_cpp_nbi2mem_copy128(unsigned int nbi, uint32_t nbi_addr,
                                           __mem void *addr, size_t size,
                                           SIGNAL *sig);

__intrinsic void __nbi_cpp_nbi2mem_copy256(unsigned int nbi, uint32_t nbi_addr,
                                           __mem void *addr, size_t size,
                                           SIGNAL *sig);

__intrinsic void nbi_cpp_nbi2mem_copy64(unsigned int nbi, uint32_t nbi_addr,
                                        __mem void *addr, size_t size);

__intrinsic void nbi_cpp_nbi2mem_copy128(unsigned int nbi, uint32_t nbi_addr,
                                         __mem void *addr, size_t size);

__intrinsic void nbi_cpp_nbi2mem_copy256(unsigned int nbi, uint32_t nbi_addr,
                                         __mem void *addr, size_t size);


#endif /* !_NPFW__NBI_CPP_H_ */
