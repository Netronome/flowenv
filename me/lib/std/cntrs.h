/*
 * Copyright (C) 2012-2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/std/cntrs.h
 * @brief         Interface for optimized counters access.
 */

#ifndef _STD__CNTRS_H_
#define _STD__CNTRS_H_

#include <nfp.h>

/* Guard against unsupported chip types. */
#if !defined(__NFP_IS_6XXX) && !defined(__NFP_IS_38XX)
    #error "Unsupported chip type"
#endif

/**
 * This API provides an optimized way to handle 64bits and "packets and bytes"
 * counters in the NFP.
 * The API supports 64bit CTM/IMEM/EMEM counters and 64bit CLS counters using
 * the atomic operations of the respective memory type.
 * For the "packets and bytes" counters the API uses the STATS engine available
 * only in the IMEM for NFP6000, and only in the EMEM for NFP3800.
 * The API optimization is achieved by eliminating the 40 bits address split
 * to high and low parts at every counter access. The user must allocate the
 * memory for the counters at a 256Byte aligned address, and use the "get_addr"
 * API functions to retrieve the base address used in the other API functions.
 *
 * Usage examples:
 * ---------------
 *
 *  64 bits counter (same APIs for EMEM/IMEM/CTM counters, for CLS counters
 *  simply use the "cls" API)
 *
 *  //gpr to hold the emem counters base address
 *  __gpr unsigned int emem_cntrs_base;
 *  //Declare an array of 64 64 bits couters in emem
 *  CNTRS64_DECLARE(my_emem_counters, 64, __emem_n(1));
 *  //get the base address
 *  emem_cntrs_base = cntr64_get_addr(my_emem_counters);
 *  //clear, increment and add
 *  cntr64_clr(emem_cntrs_base, 0);
 *  cntr64_incr(emem_cntrs_base, 7);
 *  cntr64_add(emem_cntrs_base, 3, 128);
 *
 *
 *  Packets and bytes counters
 *
 *  //struct to hold the packet and bytes counters base address
 *  __gpr pkt_cntr_addr pkt_cntr_base;
 *  SIGNAL sig;
 *  //Declare an array of 16 apckets and bytes counters
 *  PKT_CNTR_ALLOC_SYM(my_pkt_counters, 16, PKT_CNTR_LOC_DEFAULT);
 *  //get the base address
 *  pkt_cntr_base = PKT_CNTR_GET_ADDR_SYM(my_pkt_counters);
 *  //clear counter at index 0, use base 0, swap out
 *  pkt_cntr_clr(pkt_cntr_base, 0, 0, ctx_swap, &sig);
 *  //add 128 to counter at index 5, use base 0, don't swap out
 *  pkt_cntr_add(pkt_cntr_base, 5, 0, 128, sig_done, &sig);
 *
 *  Note: For NFP3800, "my_pkt_counters" should be located in "__emem".
 *
 * Users that are not interested in the optimized coutners API should simply
 * use the mem_atomic API.
 */


/**
 * Declare the data structure for the 64 bits counters.
 * @param _name         Name of the counters array
 * @param _entries      Number of counters
 * @param _mem_loc      Memory location the counters should be allocated in
 *                      __emem,__emem_n(#),__imem,__imem_n(#),
 *                      __ctm,__ctm_n(#),__cls
 *
 * Using this macro ensures that the counters memory is allocated at the
 * needed alignment.
 */
#define CNTRS64_DECLARE(_name, _entries, _mem_loc) \
    __export __shared _mem_loc __addr40 __align256 unsigned long long int _name[_entries]

/**
 * Declare the data structure for the packets and bytes counters.
 * @param _name         Name of the counters array
 * @param _entries      Number of counters
 * @param _mem_loc      Memory the packets counters should be
 *                      allocated in.
 *                      For NFP6000, __imem, __imem_n(#).
 *                      For NFP3800, __emem, __emem_n(0).
 *
 * Using this macro ensures that the counters memory is allocated at the
 * needed alignment.
 */
#if defined(__NFP_IS_6XXX)
    #define PKTS_CNTRS_DECLARE(_name, _entries, _mem_loc)                   \
        __export __shared _mem_loc __addr40 __align256                      \
        unsigned long long int _name[_entries]
#elif defined(__NFP_IS_38XX)
    /* XXX these "C" memory declarations are older style microC and do not
     * support all memory types.  Please use the PKT_CNTR_ALLOC_SYM() API
     * instead. */
#else
    #error "Unsupported chip type"
#endif


/**
 * Allocate the data structure for the packets and bytes counters.
 * @param _name         Name of the counters array
 * @param _entries      Number of counters
 * @param _mem_loc      Memory the packets counters should be
 *                      allocated in.
 *                      For NFP6000, imem, imemN.
 *                      For NFP3800, emem0.emem_cache_upper.
 *
 * Using this macro ensures that the counters memory is allocated at the
 * needed alignment.  Using the PKT_CNTR_LOC() or PKT_CNTR_LOC_DEFAULT
 * macro for the _mem_loc parameter is recommended for portability between
 * NFP variants.  PKT_CNTR_GET_ADDR_SYM() should be used to get the symbol
 * address in struct pkt_cntr_addr format.
 */
#define PKT_CNTR_ALLOC_SYM(_name, _entries, _mem_loc)                   \
    __asm { .alloc_mem _name _mem_loc global ((_entries) * 8) 256 }

/* Packet and byte counter location helper macros */
#if defined(__NFP_IS_6XXX)
    #define PKT_CNTR_LOC_IND(_n)    imem##_n
    #define PKT_CNTR_LOC(_n)        PKT_CNTR_LOC_IND(_n)

    #define PKT_CNTR_LOC_DEFAULT    imem0
#else
    #define PKT_CNTR_LOC_IND(_n)    emem0.emem_cache_upper
    #define PKT_CNTR_LOC(_n)        PKT_CNTR_LOC_IND(_n)

    #define PKT_CNTR_LOC_DEFAULT    emem0.emem_cache_upper
#endif


/**
 * Get the Packets and bytes counters base address from a symbol name.
 * @param base    40 bits address of the counters memory
 *                (must be 256 bytes aligned)
 * @return Base address as expected for the counters APIs
 */
#define PKT_CNTR_GET_ADDR_SYM(_name) \
    pkt_cntr_get_addr((__mem __addr40 void *) __link_sym(#_name))



/**
 * Packets and bytes counter address.
 */
struct pkt_cntr_addr {
    unsigned int hi;
    unsigned int lo;
};

/**
 * Statistic unpacked address detail (32 bit).
 */
union stats_addr {
    struct {
        unsigned int base:2;   /* Base address select */
        unsigned int:11;
        unsigned int addrs:19; /* Statistic address (64b aligned). */
    };
    unsigned int __raw;
};

/**
 * Stats address packing configuration.
 */
enum stats_addr_pack {
    STATS_ALL_16_BIT_PACKED          = 0x01, /* 16bit packed addresses. */
    STATS_ALL_32_BIT_UNPACKED        = 0x02, /* 32bit unpacked addresses. */
    STATS_FIRST_32_BIT_UNPACKED_ONLY = 0x03  /* First is 32bit unpacked and
                                                remaining are 16bit packed. */
};

/**
 * Log statistic command address field.
 */
union stats_log_cmd {
    struct {
        unsigned int:14;
        enum stats_addr_pack pack:2; /* Addresses packed config. */
        unsigned int bytes:16;       /* Byte count to add.       */
    };
    unsigned int __raw;
};

/**
 * Read (push) statistic command address field.
 */
union stats_push_cmd {
    struct {
        unsigned int base:2;   /* Base address select */
        unsigned int:8;
        unsigned int addrs:19; /* Statistic address (64b aligned). */
        unsigned int:3;
    };
    unsigned int __raw;
};


/*
 * CTM/IMEM/EMEM 64 bits counters APIs.
 */

/**
 * Get the 64 bits ctm/imem/emem counters base address.
 * @param base      40 bits address of the counters memory
 *                  (must be 256 bytes aligned)
 * @return Base address as expected for the counters APIs.
 */
__intrinsic unsigned int cntr64_get_addr(__mem40 void *base);

/**
 * Clear a 64 bits ctm/imem/emem counter.
 * @param base    Counters base address as returned from @cntr64_get_addr()
 * @param offset  Offset (counter index) of the relevant counter from the base
 */
__intrinsic void cntr64_clr(unsigned int base, unsigned int offset);

/**
 * Increment a 64 bits ctm/imem/emem counter.
 * @param base    Counters base address as returned from @cntr64_get_addr()
 * @param offset  Offset (counter index) of the relevant counter from the base
 */
__intrinsic void cntr64_incr(unsigned int base, unsigned int offset);

/**
 * Add a given count value to a 64 bits ctm/imem/emem counter.
 * @param base    Counters base address as returned from @cntr64_get_addr()
 * @param offset  Offset (counter index) of the relevant counter from the base.
 * @param count   Count value to be added
 *
 * The implementation optimizes the usage depending on the type and value
 * of the given count.
 * In case of a count being a CT constant the incr64 or add64_imm variants are
 * used and no ctx_swap is needed, otherwise the add64 variant is used and the
 * SIGNAL and ctx_swap is handled internally.
 */
__intrinsic void cntr64_add(unsigned int base, unsigned int offset,
                            unsigned int count);

/*
 * CLS 64 bits counters APIs.
 */

/**
 * Get the 64 bits cls counters base address.
 * @param base    40 bits address of the counters memory
 *                (must be 256 bytes aligned_
 * @return Base address as expected for the cls counters APIs
 */
__intrinsic unsigned int cntr64_cls_get_addr(__cls void *base);

/**
 * Clear a 64 bits CLS counter.
 * @param base    Counters base address as returned from @cntr64_cls_get_addr()
 * @param offset  Offset (counter index) of the relevant counter from the base
 */
__intrinsic void cntr64_cls_clr(unsigned int base, unsigned int offset);

/**
 * Increment a 64 bits CLS counter.
 * @param base    Counters base address as returned from @cntr64_cls_get_addr()
 * @param offset  Offset (counter index) of the relevant counter from the base
 */
__intrinsic void cntr64_cls_incr(unsigned int base, unsigned int offset);

/**
 * Add a given count value to a 64 bits CLS counter.
 * @param base    Counters base address as returned from @cntr64_cls_get_addr()
 * @param offset  Offset (counter index) of the relevant counter from the base
 * @param count   Count value to be added
 *
 * The implementation optimizes the usage depending on the type and value
 * of the given count.
 * In case of a count being a CT constant the incr64 or add64_imm variants are
 * used and no ctx_swap is needed, otherwise the add64 variant is used and the
 * SIGNAL and ctx_swap is handled internally.
 */
__intrinsic void cntr64_cls_add(unsigned int base, unsigned int offset,
                                unsigned int count);

/*
 * Packets and bytes counters APIs.
 * Handled using the Stats engine in the MU.
 * Each counter is 64 bits wide where the packets count uses 29/28 bits
 * and the bytes count uses 35/34 bits depending on the
 * wrap/saturate configuration.
 *
 * Note: For NFP6000, only the IMEM supports the Stats engine.
 * Note: For NFP3800, only the EMEM supports the Stats engine.
 */

/**
 * Get the Packets and bytes counters base address.
 * @param base    40 bits address of the counters memory
 *                (must be 256 bytes aligned)
 * @return Base address as expected for the counters APIs
 *
 * The packets and bytes counter address is held in a 64 bit structure
 * (pkt_cntr_addr) which splits the 40 bits address to "hi" and "low" parts.
 * The hi part holds the 8 MSBs of the 40 bits address and the low part
 * holds the lower part of the address after transform to an 8 bytes address.
 * This is done to avoid additional computations in the packets and bytes APIs.
 */
__intrinsic struct pkt_cntr_addr pkt_cntr_get_addr(__mem __addr40 void *base);


/**
 * Clears a packets and bytes counter.
 * @param base         Counters base address as returned from
 *                     @cntrs_get_pkt_cntr_addr()
 * @param offset       Offset (counter index) of the counter from the base
 * @param base_select  Selects the wanted MUSEBaseAddr CSR to be used
 * @param sync         Required sync type (sig_done / ctx_swap)
 * @param sig          Signal to use
 */
__intrinsic void pkt_cntr_clr(struct pkt_cntr_addr base, unsigned int offset,
                              unsigned int base_select, sync_t sync,
                              SIGNAL *sig);

/**
 * Add to the packets and bytes counter.
 * @param base         Counters base address as returned from
 *                     @cntrs_get_pkt_cntr_addr()
 * @param offset       Offset (counter index) of the counter from the base
 * @param base_select  Selects the wanted MUSEBaseAddr CSR to be used
 * @param byte_count   Byte count
 * @param sync         Sync type (sig_done / ctx_swap)
 * @param sig          Signal to use
 *
 * Packet count is incremented by 1, bytes count is incremented by
 * the given byte_count.
 */
__intrinsic void pkt_cntr_add(struct pkt_cntr_addr base, unsigned int offset,
                              unsigned int base_select,
                              unsigned short byte_count, sync_t sync,
                              SIGNAL *sig);

/**
 * Reads the packets and bytes counts from a stats counter.
 * @param base         Counters base address as returned from
 *                     @cntrs_get_pkt_cntr_addr()
 * @param offset       Offset (counter index) of the counter from the base
 * @param base_select  Selects the wanted MUSEBaseAddr CSR to be used
 * @param byte_count   Byte count
 *
 * Always swaps out to wait for the result.
 */
__intrinsic void pkt_cntr_read(struct pkt_cntr_addr base, unsigned int offset,
                               unsigned int base_select,
                               unsigned int *pkt_count,
                               unsigned long long *byte_count);

/**
 * Reads and clear the packets and bytes counter.
 * @param base         Counters base address as returned from
 *                     @cntrs_get_pkt_cntr_addr()
 * @param offset       Offset (counter index) of the counter from the base
 * @param base_select  Selects the wanted MUSEBaseAddr CSR to be used
 * @param pkt_count    Packet count
 * @param byte_count   Byte count
 *
 * Always swaps out to wait for the result.
 */
__intrinsic void pkt_cntr_read_and_clr(struct pkt_cntr_addr base,
                                       unsigned int offset,
                                       unsigned int base_select,
                                       unsigned int *pkt_count,
                                       unsigned long long  *byte_count);

#endif /* !_STD__CNTRS_H_ */
