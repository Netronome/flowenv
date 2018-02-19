/*
 * Copyright 2017-2018 Netronome Systems, Inc. All rights reserved.
 *
 * @file          lib/modscript/modscript.h
 * @brief         Header of the packet modifier script interface
 *
 * This file contains the prototypes of the packet modifier script write
 * functions.
 *
 */

#ifndef __MODSCRIPT_H__
#define __MODSCRIPT_H__

#include <nfp.h>
#include <modscript/modscript.h>


/* Only supported in B0 */
#if (__REVISION_MIN >= __REVISION_C0)
    #error "Unsupported chip revision"
#elif (__REVISION_MAX < __REVISION_B0)
    #error "Unsupported chip revision"
#else
    /* supported */
#endif

/* This is the min allowable offset for packet to start. */
#define PKTIO_MIN_NBI_TX_OFFSET  40

/* This is the max allowable offset for packet to start. */
#define PKTIO_MAX_NBI_TX_OFFSET  248

/**
 * Packet modifier rewrite script details to write to packet:
 * what to write (indirect script)
 * where to write (offset in packet)
 * number of words (length) to write.
 */
typedef union modscript_struct_t {
    struct {
        unsigned int direct         : 1;  /**< First word of what to write */
        unsigned int unused         : 4;
        unsigned int offset_len     : 3;
        unsigned int opcode_index   : 8;
        unsigned int rdata_index    : 8;
        unsigned int rdata_location : 2;
        unsigned int rdata_length   : 6;

        unsigned int offset_0       : 8; /**< Second word of what to write */
        unsigned int offset_1       : 8;
        unsigned int offset_2       : 8;
        unsigned int offset_3       : 8;

        unsigned int offset_4       : 8; /**< Third word of what to write */
        unsigned int offset_5       : 8;
        unsigned int offset_6       : 8;
        unsigned int offset_7       : 8;

        unsigned int valid          : 1;
        unsigned int reserved       : 20;
        unsigned int prepend_len0   : 3; /**< Num of 32-bit words to write */
        unsigned int prepend_offset : 8; /**< Offset to write to in packet */
    };
    unsigned int value[4];
} modscript_struct_t;



/**
* Lookup the appropriate rewrite script from pkt_mod_script_tbl using the
* provided offset and write it to pbuf.
*
* @param pbuf   Packet buffer
* @param off    Start of data in pbuf (used to calculate modifier script)
* @return       Returns pkt_msi_info
*/
__intrinsic struct pkt_ms_info modscript_write(__mem40 void *pbuf,
                    unsigned char off);


/**
* Lookup the appropriate rewrite script from pkt_mod_script_tbl using the
* provided offset and write it to pbuf. All signals are
* passed to calling function for optimisation.
*
* @param pbuf   Packet buffer
* @param off    Start of data in pbuf (used to calculate modifier script)
* @param pwrite The packet modifier script write xfer
* @param rdback The read value
* @param sig1   The write signal to use
* @param sig2   The read back signal to use
* @return       Returns pkt_msi_info
*/
__intrinsic struct pkt_ms_info __modscript_write(__mem40 void *pbuf,
                    unsigned char off, __xwrite modscript_struct_t *pwrite,
                    __xread unsigned int *rdback, SIGNAL *sig1,
                    SIGNAL *sig2);

#endif /* __MODSCRIPT_H__ */

