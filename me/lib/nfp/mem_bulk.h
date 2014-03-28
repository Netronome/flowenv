/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/mem_bulk.h
 * @brief         NFP memory bulk interface
 */
#ifndef _NFP__MEM_BULK_H_
#define _NFP__MEM_BULK_H_

#include <nfp/nfp.h>
#include <nfp/types.h>

/**
 * Read a multiple of 8B from a memory unit (EMEM, IMEM, or CTM)
 * @param data      pointer to sufficient read transfer registers for the op
 * @param addr      40-bit pointer to the memory start address
 * @param size      size of the read, must be a multiple of 8
 * @param max_size  used to determine largest read, if size is not a constant
 * @param sync      type of synchronisation (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * This method provides basic bulk reads from NFP memory units.  No special
 * alignment is assumed about address when converting from a 40bit pointer to
 * "src_op" fields in the __asm command, which makes the method general, but
 * suboptimal if it is guaranteed to be 256B aligned.  There is currently
 * limited support for size to be a runtime value, and for reads >64B, see
 * THSDK-1161.  mem_read64() provides a simplified interface where size is
 * assumed to be compile time constant, and the context swaps on an internal
 * signal while waiting for the read to complete.
 */
__intrinsic void __mem_read64(__xread void *data, __dram void *addr,
                              size_t size, const size_t max_size,
                              sync_t sync, SIGNAL *sig);

__intrinsic void mem_read64(__xread void *data, __dram void *addr,
                            const size_t size);


/**
 * Write a multiple of 8B to a memory unit (EMEM, IMEM, or CTM)
 * @param data      pointer to sufficient write transfer registers for the op
 * @param addr      40-bit pointer to the memory start address
 * @param size      size of the write, must be a multiple of 8
 * @param max_size  used to determine largest write, if size is not a constant
 * @param sync      type of synchronisation (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * This method provides basic bulk writes to NFP memory units.  No special
 * alignment is assumed about address when converting from a 40bit pointer to
 * "src_op" fields in the __asm command, which makes the method general, but
 * suboptimal if it is guaranteed to be 256B aligned.  There is currently
 * limited support for size to be a runtime value, and for reads >64B, see
 * THSDK-1161.  mem_write64() provides a simplified interface where size is
 * assumed to be compile time constant, and the context swaps on an internal
 * signal while waiting for the write to complete.
 */
__intrinsic void __mem_write64(__xwrite void *data, __dram void *addr,
                               size_t size, const size_t max_size,
                               sync_t sync, SIGNAL *sig);

__intrinsic void mem_write64(__xwrite void *data, __dram void *addr,
                             const size_t size);

#endif /* !_NFP__MEM_BULK_H_ */
