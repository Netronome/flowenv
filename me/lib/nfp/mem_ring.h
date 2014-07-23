/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/mem_ring.h
 * @brief         NFP memory ring interface
 */
#ifndef _NFP__MEM_RING_H_
#define _NFP__MEM_RING_H_

#include <nfp.h>
#include <types.h>

#if defined (__NFP_LANG_MICROC)

/**
 * High address bits use to specify target EMEM
 * The upper 8bits of a 40bit emem pointer are used for DSF CPP routing.  EMEM
 * ring operations look up the ring address in queue engine cache, but the ME
 * still requires the upper bits of the address to route the command to the
 * right EMEM.  NFCC typically handles DSF CPP routing, so the preferred method
 * to construct a mem_ring_addr_t address is via one of the API supplied below.
 * XXX Support for 32bit addressing?
 */
typedef unsigned int mem_ring_addr_t;

/**
 * Declare the data structure for a ring or journal
 *
 * @param _name         Name of the ring/journal
 * @param _entries      Number of 32bit entries on ring/journal
 */
#define MEM_RING_DECLARE(_name, _entries) \
    __export __emem __align(_entries * 4) unsigned int _name[_entries]
#define MEM_JOURNAL_DECLARE(_name, _entries) \
    __export __emem __align(_entries * 4) unsigned int _name[_entries]
#define MEM_WORKQ_DECLARE(_name, _entries) \
    __export __emem __align(_entries * 4) unsigned int _name[_entries]

/**
 * Configure a memory ring/journal
 *
 * @param _name         Name of the ring/journal
 * @param _rnum         Ring number to use
 */
#define MEM_RING_CONFIGURE(_name, _rnum) \
    mem_ring_setup(_rnum, _name, sizeof(_name))
#define MEM_JOURNAL_CONFIGURE(_name, _rnum) \
    mem_journal_setup(_rnum, _name, sizeof(_name))
#define MEM_WORKQ_CONFIGURE(_name, _rnum) \
    mem_workq_setup(_rnum, _name, sizeof(_name))

/**
 * Construct a mem_ring_addr_t
 *
 *@param base           base address
 *
 * Helper function to construct a mem_ring_addr_t address for the ring
 * given the memory address of the ring. It is preferably to save the
 * value returned by @mem_ring_setup instead if possible.
 */
__intrinsic mem_ring_addr_t mem_ring_get_addr(__dram void *base);

/**
 * Setup/Configure a memory ring
 *
 * @param rnum          ring number
 * @param base          base address
 * @param size          size of ring in bytes (must be a compile time constant)
 *
 * Initializes a DRAM ring with the given size using the memory
 * pointed to by base.  The ring type will always be set to two, and
 * the ring will be marked as empty.
 */
__intrinsic mem_ring_addr_t mem_ring_setup(unsigned int rnum, __dram void *base,
                                           size_t log2size);

/**
 * Setup/Configure a memory journal
 *
 * @param rnum          ring number
 * @param base          base address
 * @param size          size of ring (must be a compile time constant)
 *
 * Initializes a DRAM journal with a given size using the memory
 * pointed to by base.
 */
__intrinsic mem_ring_addr_t mem_journal_setup(unsigned int rnum,
                                              __dram void *base,
                                              size_t log2size);


/**
 * Setup/Configure a memory work queue
 *
 * @param rnum          ring number
 * @param base          base address
 * @param size          size of ring (must be a compile time constant)
 *
 * Initializes a DRAM work queue with a given size using the memory
 * pointed to by base.
 */
__intrinsic mem_ring_addr_t mem_workq_setup(unsigned int rnum,
                                            __dram void *base,
                                            size_t log2size);


/**
 * Get entries off memory ring
 *
 * @param rnum          ring number
 * @param data          output data
 * @param size          size of output
 * @param max_size      used to determine largest op, if size is not a constant
 * @param sync          type of synchronization (must be sig_done)
 * @param sigpair       signal pair to report completion/failure
 *
 * Removes entries from the head of the ring and signal @sigpair[0]
 * when done.  If @sigpair[1] is also raised it indicates that the
 * ring was not sufficiently full to complete the request and that no
 * entries were removed.
 */
__intrinsic void __mem_ring_get(unsigned int rnum, mem_ring_addr_t raddr,
                                __xread void *data,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL_PAIR *sigpair);

/**
 * Get entries off memory ring
 * @param rnum          ring number
 * @param data          output data
 * @param size          size of output (in bytes)
 *
 * Removes entries from the head of the ring and return 0 on success.
 * Leave ring as-is and return -1 if the ring is not sufficiently full
 * to complete the request.
 */
__intrinsic int mem_ring_get(unsigned int rnum, mem_ring_addr_t raddr,
                             __xread void *data, const size_t size);

/**
 * Pop entries off memory ring
 *
 * @param rnum          ring number
 * @param data          output data
 * @param size          size of output
 * @param max_size      used to determine largest op, if size is not a constant
 * @param sync          type of synchronization (must be sig_done)
 * @param sigpair       signal pair to report completion/failure
 *
 * Removes entries from the tail of the ring and signal @sigpair[0]
 * when done.  If @sigpair[1] is also raised it indicates that the
 * ring was not sufficiently full to complete the request and that no
 * entries were removed.
 */
__intrinsic void __mem_ring_pop(unsigned int rnum, mem_ring_addr_t raddr,
                                __xread void *data,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL_PAIR *sigpair);

/**
 * Pop entries off memory ring
 * @param rnum          ring number
 * @param data          output data
 * @param size          size of output (in bytes)
 *
 * Removes entries from the tail of the ring and return 0 on success.
 * Leave ring as-is and return -1 if the ring is not sufficiently full
 * to complete the request.
 */
__intrinsic int mem_ring_pop(unsigned int rnum, mem_ring_addr_t raddr,
                             __xread void *data, const size_t size);

/**
 * Put entries onto memory ring
 * @param rnum          ring number
 * @param data          input data
 * @param size          size of output
 * @param max_size      used to determine largest op, if size is not a constant
 * @param sync          type of synchronization (must be sig_done)
 * @param sigpair       signal pair to report completion/failure
 *
 * Add entries to the tail of the ring. mem[put] returns a status word
 * in data[0] after both signals have been asserted.  It is the
 * caller's responsibility to check the status when using this
 * function.  If data[0] is zero, a error occurred.  If the top bit of
 * data[0] is *not* set, the data was not added and the lower data[0]
 * bits contain the number of 32bit words already on the ring.  If the
 * top bit of data[0] is set, the operation succeeded and the lower
 * bits contain the number of 32bit words already on the ring.
 *
 * Note that the input data must be declared as both read and write
 * register.
 */
__intrinsic void __mem_ring_put(unsigned int rnum, mem_ring_addr_t raddr,
                                __xrw void *data,
                                size_t size, const size_t max_size,
                                sync_t sync, SIGNAL_PAIR *sigpair);

/**
 * Put entries onto memory ring
 * @param rnum          ring number
 * @param data          input data
 * @param size          size of input (in bytes)
 *
 * Add entries to the tail of the ring and return number of bytes
 * already on ring.  Leave ring as-is and return -1 if the ring was
 * too full to complete the request or another error occurred.
 *
 * Note that the input data must be declared as both read and write
 * register.
 */
__intrinsic int mem_ring_put(unsigned int rnum,mem_ring_addr_t raddr,
                             __xrw void *data, const size_t size);


/**
 * Journal entries onto memory ring
 * @param rnum          ring number
 * @param data          input data
 * @param size          size of output
 * @param max_size      used to determine largest op, if size is not a constant
 * @param sync          type of synchronization (must be sig_done)
 * @param sigpair       signal pair to report completion/failure
 *
 * Add entries to the tail of the ring, overwriting oldest entries if
 * ring is full.
 */
__intrinsic void __mem_ring_journal(unsigned int rnum, mem_ring_addr_t raddr,
                                    __xwrite void *data,
                                    size_t size, const size_t max_size,
                                    sync_t sync, SIGNAL_PAIR *sigpair);

/**
 * Journal entries onto memory ring
 * @param rnum          ring number
 * @param data          input data
 * @param size          size of input (in bytes)
 *
 * Add entries to the tail of the ring, overwriting oldest entries if
 * ring is full. A return value of -1 indicates that the ring overflowed.
 * This is not an error strictly for journals.
 */
__intrinsic int mem_ring_journal(unsigned int rnum, mem_ring_addr_t raddr,
                                 __xwrite void *data, const size_t size);

/**
 * Fast journal an entry onto memory ring
 * @param rnum          ring number
 * @param value         value to journal
 *
 * Add entries to the tail of the ring, overwriting oldest entries if
 * ring is full.
 */
__intrinsic void mem_ring_journal_fast(unsigned int rnum, mem_ring_addr_t raddr,
                                       unsigned int value);


/**
 * Put entries onto a work queue
 * @param rnum          work queue "ring" number
 * @param raddr         address bits for the queue engine island
 * @param data          input data
 * @param size          size of input
 * @param max_size      used to determine largest op, if size is not a constant
 * @param sync          type of synchronization
 * @param sig           signal to use for the operation
 *
 * Note that no work queue overflow checking is performed.
 */
__intrinsic void __mem_workq_add_work(unsigned int rnum, mem_ring_addr_t raddr,
                                      __xwrite void *data,
                                      size_t size, const size_t max_size,
                                      sync_t sync, SIGNAL *sig);

/**
 * Put entries onto a work queue
 * @param rnum          work queue "ring" number
 * @param raddr         address bits for the queue engine island
 * @param data          input data
 * @param size          size of input
 *
 * Note that no work queue overflow checking is performed.
 */
__intrinsic void mem_workq_add_work(unsigned int rnum, mem_ring_addr_t raddr,
                                    __xwrite void *data, const size_t size);


/**
 * Put threads onto a work queue
 * @param rnum          work queue "ring" number
 * @param raddr         address bits for the queue engine island
 * @param data          output data
 * @param size          size of output
 * @param max_size      used to determine largest op, if size is not a constant
 * @param sync          type of synchronization
 * @param sig           signal to use for the operation
 *
 * Note that no work queue overflow checking is performed.
 */
__intrinsic void __mem_workq_add_thread(unsigned int rnum,
                                        mem_ring_addr_t raddr,
                                        __xread void *data,
                                        size_t size, const size_t max_size,
                                        sync_t sync, SIGNAL *sig);

/**
 * Put threads onto a work queue
 * @param rnum          work queue "ring" number
 * @param raddr         address bits for the queue engine island
 * @param data          output data
 * @param size          size of output
 *
 * Note that no work queue overflow checking is performed.
 */
__intrinsic void mem_workq_add_thread(unsigned int rnum, mem_ring_addr_t raddr,
                                      __xread void *data, const size_t size);


/**
 * Get current amount of data in memory ring
 * @param rnum          ring number
 */
__intrinsic size_t mem_ring_current_size(unsigned int rnum,
                                         mem_ring_addr_t raddr);

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP__MEM_RING_H_ */
