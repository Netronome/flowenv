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
 * @file          lib/nfp/cls.h
 * @brief         NFP CLS interface
 */
#ifndef _NFP__CLS_H_
#define _NFP__CLS_H_

#include <nfp.h>
#include <stdint.h>
#include <types.h>

/**
 * Read a multiple of 4B from CLS
 * @param data      pointer to sufficient write transfer registers for the op
 * @param addr      32-bit pointer to the memory start address in local CLS
 * @param size      size of the read, must be a multiple of 4
 * @param max_size  used to determine largest read, if size is not a constant
 * @param sync      type of synchronization (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * This function provides basic bulk reads to the current island's CLS.  There
 * is currently limited support for size to be a runtime value, and for reads
 * >64B. cls_read() provides a simplified interface where size is assumed to
 * be compile time constant, and the context swaps on an internal signal while
 * waiting for the read to complete.
 */
__intrinsic void __cls_read(__xread void *data, __cls void *addr,
                            size_t size, const size_t max_size,
                            sync_t sync, SIGNAL *sig);

__intrinsic void cls_read(__xread void *data, __cls void *addr, size_t size);

/**
 * Write a multiple of 4B to CLS
 * @param data      pointer to sufficient write transfer registers for the op
 * @param addr      32-bit pointer to the memory start address in local CLS
 * @param size      size of the write, must be a multiple of 4
 * @param max_size  used to determine largest write, if size is not a constant
 * @param sync      type of synchronization (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * This function provides basic bulk writes to the current island's CLS. There
 * is currently limited support for size to be a runtime value, and for read
 * >64B. cls_write() provides a simplified interface where size is assumed to
 * be compile time constant, and the context swaps on an internal signal while
 * waiting for the write to complete.
 */
__intrinsic void __cls_write(__xwrite void *data, __cls void *addr,
                             size_t size, const size_t max_size,
                             sync_t sync, SIGNAL *sig);

__intrinsic void cls_write(__xwrite void *data, __cls void *addr, size_t size);

/*
 * Endian specific functions.  Parameters as per endian neutral functions above.
 */

__intrinsic void __cls_read_be(__xread void *data, __cls void *addr,
                               size_t size, const size_t max_size,
                               sync_t sync, SIGNAL *sig);

__intrinsic void cls_read_be(__xread void *data, __cls void *addr, size_t size);

__intrinsic void __cls_write_be(__xwrite void *data, __cls void *addr,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL *sig);

__intrinsic void cls_write_be(__xwrite void *data, __cls void *addr,
                              size_t size);



__intrinsic void __cls_read_le(__xread void *data, __cls void *addr,
                               size_t size, const size_t max_size,
                               sync_t sync, SIGNAL *sig);

__intrinsic void cls_read_le(__xread void *data, __cls void *addr, size_t size);

__intrinsic void __cls_write_le(__xwrite void *data, __cls void *addr,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL *sig);

__intrinsic void cls_write_le(__xwrite void *data, __cls void *addr,
                              size_t size);

/**
 * Create a 64-bit hash_index over the transfer registers
 * @param key       pointer to sufficient write transfer registers for the hash
 * @param mask      32-bit pointer to the start of the mask in CLS
 * @param size      size of the key/mask, must be a multiple of 4. Valid [4-128]
 * @param max_size  used to determine largest hash, if size is not a constant
 * @param idx       CLS hash index. Valid [0-7]
 * @param sync      type of synchronisation (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * These functions perform a hash on up to 128 bytes of data in the transfer
 * registers. The user should configure the CLS hash multiply register and
 * initialize the hash before calling this function. See std/hash.h
 * The clear function is the same as hash_mask, but also clears the initial
 * value of hash_index before calculating the new value. cls_hash_mask() can be
 * used to chain several hashes together.
 */
__intrinsic void __cls_hash_mask_clr(__xwrite void *key, __cls void *mask,
                                     size_t size, const size_t max_size,
                                     uint32_t idx, sync_t sync, SIGNAL *sig);

__intrinsic void cls_hash_mask_clr(__xwrite void *key, __cls void *mask,
                                   size_t size, uint32_t idx);

__intrinsic void __cls_hash_mask(__xwrite void *key, __cls void *mask,
                                 size_t size, const size_t max_size,
                                 uint32_t idx, sync_t sync, SIGNAL *sig);

__intrinsic void cls_hash_mask(__xwrite void *key, __cls void *mask,
                               size_t size, uint32_t idx);

/* Bit atomic functions */
/**
 * Clear the bit(s) in multiples of 4B from CLS.
 * @param data     pointer to sufficient write transfer registers for the op
 * @param addr     32-bit pointer to the memory start address in local CLS
 * @param size     size of the write, must be a multiple of 4
 * @param max_size used to determine largest write, if size is not a constant
 * @param sync     type of synchronization (sig_done or ctx_swap)
 * @param sig      signal to use
 *
 * This function provides bit atomic clear of the bit(s) at the specified
 * address according to a bit mask provided in the xfer register(s).
 * A 1 in the bit position of the bit mask signifies that the bit should be
 * cleared.
 * There is currently limited support for size to be a runtime value, and for
 * clears >64B. cls_clr() provides a simplified interface where size is
 * assumed to be compile time constant, and the context swaps on an internal
 * signal while waiting for the write to complete.
 */
__intrinsic void __cls_clr(__xwrite void *data, __cls void *addr, size_t size,
                           const size_t max_size, sync_t sync, SIGNAL *sig);

__intrinsic void cls_clr(__xwrite void *data, __cls void *addr, size_t size);

/**
 * Set the bit(s) in multiples of 4B from CLS.
 * @param data     pointer to sufficient write transfer registers for the op
 * @param addr     32-bit pointer to the memory start address in local CLS
 * @param size     size of the write, must be a multiple of 4
 * @param max_size used to determine largest write, if size is not a constant
 * @param sync     type of synchronization (sig_done or ctx_swap)
 * @param sig      signal to use
 *
 * This function provides bit atomic set of the bit(s) at the specified
 * address according to a bit mask provided in the transfer register(s). A 1
 * in the bit position of the bit mask signifies that the bit should be set.
 * There is currently limited support for size to be a runtime value, and for
 * sets >64B. cls_set() provides a simplified interface where size is assumed
 * to be compile time constant, and the context swaps on an internal signal
 * while waiting for the write to complete.

 */
__intrinsic void __cls_set(__xwrite void *data, __cls void *addr, size_t size,
                           const size_t max_size, sync_t sync, SIGNAL *sig);

__intrinsic void cls_set(__xwrite void *data, __cls void *addr, size_t size);

/**
 * Test and Clear the bit(s) in multiples of 4B from CLS.
 * @param data     pointer to sufficient RW transfer registers for the op
 * @param addr     32-bit pointer to the memory start address in local CLS
 * @param size     size of the write, must be a multiple of 4
 * @param max_size used to determine largest write, if size is not a constant
 * @param sync     type of synchronization (sig_done or ctx_swap)
 * @param sig      signal to use
 *
 * This function provides bit atomic clear of the bit(s) at the specified
 * address according to a bit mask provided in the write transfer register(s)
 * and returns the premodified memory contents in the read transfer
 * register(s). A 1 in the bit position of the bit mask signifies that the bit
 * should be cleared.
 * There is currently limited support for size to be a runtime value, and for
 * test and clears >64B. cls_test_clr() provides a simplified interface
 * where size is assumed to be compile time constant, and the context swaps on
 * an internal signal while waiting for the write to complete.
 */

__intrinsic void __cls_test_clr(__xrw void *data, __cls void *addr,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL *sig);

__intrinsic void cls_test_clr(__xrw void *data, __cls void *addr,
                              size_t size);

/**
 * Test and Set the bit(s) in multiples of 4B from CLS.
 * @param data     pointer to sufficient RW transfer registers for the op
 * @param addr     32-bit pointer to the memory start address in local CLS
 * @param size     size of the write, must be a multiple of 4
 * @param max_size used to determine largest write, if size is not a constant
 * @param sync     type of synchronization (sig_done or ctx_swap)
 * @param sig      signal to use
 *
 * This function provides bit atomic set of the bit(s) at the specified
 * address according to a bit mask provided in the write transfer register(s)
 * and returns the premodified memory contents in the read transfer
 * register(s). A 1 in the bit position of the bit mask signifies that the bit
 * should be set.
 * There is currently limited support for size to be a runtime value,
 * and for test and sets >64B. cls_test_set() provides a simplified interface
 * where size is assumed to be compile time constant, and the context swaps on
 * an internal signal while waiting for the write to complete.
 */
__intrinsic void __cls_test_set(__xrw void *data, __cls void *addr,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL *sig);

__intrinsic void cls_test_set(__xrw void *data, __cls void *addr,
                              size_t size);

/**
 * Single instruction to increment by 1 a value in CLS.
 * @param addr     pointer to the memory address in CLS.
 *
 * These functions provide bit atomic 32 or 64 bit CLS increment by 1.
 */
__intrinsic void cls_incr(__cls void *addr);

__intrinsic void cls_incr64(__cls void *addr);

/**
 * Single instruction to decrement by 1 a value in CLS.
 * @param addr     pointer to the memory address in CLS.
 *
 * These functions provide bit atomic 32 or 64 bit CLS decrement by 1.
 */
__intrinsic void cls_decr(__cls void *addr);

__intrinsic void cls_decr64(__cls void *addr);

#endif /* !_NFP__CLS_H_ */
