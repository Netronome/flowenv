/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/cls.h
 * @brief         NFP CLS interface
 */
#ifndef _NFP__CLS_H_
#define _NFP__CLS_H_

#include <nfp/nfp.h>
#include <nfp/types.h>


/**
 * Read a multiple of 4B from CLS
 * @param data      pointer to sufficient write transfer registers for the op
 * @param addr      32-bit pointer to the memory start address in local CLS
 * @param size      size of the read, must be a multiple of 4
 * @param max_size  used to determine largest read, if size is not a constant
 * @param sync      type of synchronisation (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * This method provides basic bulk reads to the current island's CLS.  There is
 * currently limited support for size to be a runtime value, and for reads >64B.
 * cls_read() provides a simplified interface where size is assumed to be
 * compile time constant, and the context swaps on an internal signal while
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
 * @param sync      type of synchronisation (sig_done or ctx_swap)
 * @param sig       signal to use
 *
 * This method provides basic bulk writes to the current island's CLS.  There is
 * currently limited support for size to be a runtime value, and for reads >64B.
 * cls_write() provides a simplified interface where size is assumed to be
 * compile time constant, and the context swaps on an internal signal while
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

#endif /* !_NFP__CLS_H_ */
