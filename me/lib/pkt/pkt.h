/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/pkt/pkt.h
 * @brief         Interface for ME packet manipulation routines
 */
#ifndef _PKT__PKT_H_
#define _PKT__PKT_H_

#include <nfp.h>
#include <stdint.h>
#include <types.h>

#if defined(__NFP_LANG_MICROC)

/**
 * Packet Metadata Format from the NBI
 *
 * Bit    3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 * -----\ 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * Word  +-----------+-------------------+---+---------------------------+
 *    0  | CTM Island|   Packet Number   |Bls|      Packet Length        |
 *       +-+---+-----+-------------------+---+---------------------------+
 *    1  |S|Rsv|                   MU Pointer                            |
 *       +-+---+---------------------------------------------------------+
 *    2  |                      Preclass Meta 0                          |
 *       +---------------------------------------------------------------+
 *    3  |                      Preclass Meta 1                          |
 *       +---------------------------------------------------------------+
 *    4  |                      Preclass Meta 2                          |
 *       +---------------------------------------------------------------+
 *    5  |                      Preclass Meta 3                          |
 *       +---------------------------------------------------------------+
 *
 *      S -> 1 if packet is split between CTM and MU data
 *      Bls -> Buffer List
 */


/**
 * Structure describing the invariant part of the packet metadata that
 * the NBI/CTM Packet Engine delivers to the ME.  The NBI traffic manager
 * also requires this data at the beginning of the CTM buffer in the
 * same format for packet transmission.  However, the TM ignores the
 * Packet Lenght field and uses an encoded address (see below) to get the
 * the transmission length.
 */
struct nbi_meta_pkt_info {
    union {
        struct {
#ifdef BIGENDIAN
            unsigned int isl:6;         /**< Island of the CTM of the packet */
            unsigned int pnum:10;       /**< Packet number of the packet */
            unsigned int bls:2;         /**< Buffer list of the MU buffer */
            unsigned int len:14;        /**< Length of the packet in bytes */

            unsigned int split:1;       /**< Set if pkt split between CTM/MU */
            unsigned int resv0:2;       /**< Reserved */
            unsigned int muptr:29;      /**< Pointer to the MU buffer >>11 */
#else /* BIGENDIAN */
            unsigned int len:14;        /**< Length of the packet in bytes */
            unsigned int bls:2;         /**< Buffer list of the MU buffer */
            unsigned int pktn:10;       /**< Packet number of the packet */
            unsigned int isl:6;         /**< Island of the CTM of the packet */

            unsigned int muptr:29;      /**< Pointer to the MU buffer >>11 */
            unsigned int resv0:2;       /**< Reserved */
            unsigned int split:1;       /**< Set if pkt split between CTM/MU */
#endif /* BIGENDIAN */
        };
        uint32_t __raw[2];
    };
};


/**
 * Structure describing the NBI/CTM PE metadata for a packet delivered by
 * the "null" picoengine load.  This load immediately sends the packet
 * without inspection.  For IPv4 traffic, this causes the sequencer and
 * sequence number to be loaded as shown below.  For IPv6 and non-IP
 * packets this is not as well defined.  Basically, only use the
 * "null" load for basic first try testing.
 */
struct nbi_meta_null {
    union {
        struct {
            struct nbi_meta_pkt_info pkt_info;
#ifdef BIGENDIAN
            unsigned int resv1:6;       /**< Reserved */
            unsigned int seq:10;        /**< Packet sequence number */
            unsigned int resv2:3;       /**< Reserved */
            unsigned int seqr:5;        /**< Packet sequencer */
            unsigned int resv3:8;       /**< Reserved */
#else /* BIGENDIAN */
            unsigned int resv3:8;       /**< Reserved */
            unsigned int seqr:5;        /**< Packet sequencer */
            unsigned int resv2:3;       /**< Reserved */
            unsigned int seq:10;        /**< Packet sequence number */
            unsigned int resv1:6;       /**< Reserved */
#endif /* BIGENDIAN */
            unsigned int preclass[3];   /**< Unkonwn preclassifier metadata */
        };
        uint32_t __raw[6];
    };
};


/* TODO: Add "wire" and other default "comes-with-NFP" NBI loads */


/**
 * Sending or freeing a packet is an involved process in the NFP 6xxx.
 * There are numerous fields that one must override in the DSF CPP
 * command, some in unconventional ways.  This requires using both the
 * previous ALU instruction and the CmdIndirectRev0 CSR in the ME to
 * build the command.  It also requires building the address of the
 * packet in an unusual way.
 *
 * References:
 *  - NFP 6xxx PRM Section 2.1.6.4.6 "NFP-6xxx (Normal) Indirect
 *    Reference Formats"
 *  - NFP 6xxx DB Section 9.2.2.7.9 "Packet Processing Complete Target
 *    Command and Packet Ready Master Command"
 */


/**
 * The bitfields for the CmdIndirectRef0 CSR when sending/freeing CTM
 * packets.  This structure defines the fields as the CTM packet engine
 * sees them instead of how the ME and the DSF CPP bus sees the fields.
 * For example, the sequencer number field goes in the CPP bytemask
 * field.  The sequence number overlaps the signal master, data master
 * and data master island fields.  The reserved fields should be left
 * as zero.
 */
struct pkt_iref_csr0 {
    union {
        struct {
#ifdef BIGENDIAN
            unsigned int resv0:2;       /**< Reserved, set to 0 */
            unsigned int seq:14;        /**< NBI TM sequence number */
            unsigned int resv1:8;       /**< Reserved, set to 0 */
            unsigned int seqr:8;        /**< NBI TM sequencer number */
#else /* BIGENDIAN */
            unsigned int seqr:8;        /**< NBI TM sequencer number */
            unsigned int resv1:8;       /**< Reserved, set to 0 */
            unsigned int seq:14;        /**< NBI TM sequence number */
            unsigned int resv0:2;       /**< Reserved, set to 0 */
#endif /* BIGENDIAN */
        };

        uint32_t __raw;
    };
};


/**
 * Bitfield format of the previous ALU instruction result for the
 * indirect reference required to send or drop a CTM packet.  This
 * structure defines the fields as the CTM packet engine understands
 * them rather than how the ME and DSF CPP bus sees them.
 */
struct pkt_iref_palu {
    union {
        struct {
#ifdef BIGENDIAN
            unsigned int resv0:2;       /**< Reserved: set to 0 */
            unsigned int nbi:2;         /**< NBI to send the packet to */
            unsigned int resv1:2;       /**< Never set retry bit */
            unsigned int txq:10;        /**< TX queue to send the packet to */
            unsigned int resv2:3;       /**< No override sig num or sig ctx */
            unsigned int ms_off:5;      /**< Encoded mod script offset */
            unsigned int magic:8;       /**< PKT_IREF_PALU_MAGIC: see below */
#else /* BIGENDIAN */
            unsigned int magic:8;       /**< PKT_IREF_PALU_MAGIC: see below */
            unsigned int ms_off:5;      /**< Encoded mod script offset */
            unsigned int resv2:3;       /**< no override sig num or sig ctx */
            unsigned int txq:10;        /**< TX queue to send the packet to */
            unsigned int resv1:2;       /**< Never set retry bit */
            unsigned int nbi:2;         /**< NBI to send the packet to */
            unsigned int resv0:2;       /**< Reserved: set to 0 */
#endif /* BIGENDIAN */
        };

        uint32_t __raw;
    };
};


/**
 * Previous ALU for Packet Processing Complete must override:
 *  * Signal master from CSR0 (seq number)  (1 << 0)
 *
 *  * Data master from CSR0 (seq number)    (1 << 1)
 *    Data master island from CSR0 (seq number)
 *
 *  * Data reference (from prev alu DATA16, for TXQ and NBI) (1 << 3)
 *
 *  * Bytemask from CSR0 (TM sequencer)  (1 << 6)
 *
 *  * Length (from prev ALU length, for offset of rewrite script) (1 << 7)
 */
#define PKT_IREF_PALU_MAGIC     0xcb



/**
 * Holds information pertaining to the addition of a modification script to
 * the beginning of a CTM buffer.
 */
struct pkt_ms_info {
    uint16_t off_enc;   /**< encoded MS offset */
    uint16_t len_adj;   /**< # of bytes to add to the length on PPC */
};


/**
 * Modification Script format
 *
 * In order to send a packet in the NFP 6xxx A0/A1 chip, one
 * must prepend the packet with a "modification script" for the NBI 
 * TM packet modifier.  One must do this even if one does not want 
 * any modifications to the packet.
 *
 * The script must be placed at an 8-byte aligned location in
 * CTM memory and must be a multiple of 8 bytes in length.  The
 * packet must also have the first 8 bytes of CTM memory containing
 * crucial TM metadata.  So, the script can not go at offset 0.
 *
 * It is also important to note that TM calculates the starting
 * offset of the packet data by adding the starting offset of
 * the modification script to the length of the modification script.
 * This implies that a packet can only start at an 8-byte aligned
 * address, by default.
 *
 * The way to get around this is to create an 8-byte modification 
 * script starting at the nearest 8-byte address boundary 8 or more
 * bytes below the start of the packet that deletes the intervening
 * bytes between the modification script and the start of the packet.
 * It is extremely annoying and a waste of time and I/O bandwidth all
 * to "do nothing".
 *
 * NFP 6xxx B0 and later chips will allow NOT using a modification
 * script as well as arbitrary byte offsets for the start of packet
 * when the modification script is disabled.  (The packet must still 
 * start at start at byte 8 or later in the CTM buffer).
 *
 * See:
 *  - NFP 6xxx Databook Section 7.2.4.1 "Modification Script"
 */

#define TM_MS_DIRECT_wrd        0
#define TM_MS_DIRECT_shf        31
#define TM_MS_DIRECT_bit        31

#define TM_MS_OPCODE_shf        16
#define TM_MS_OPCODE_msk        0xFF

#define TM_MS_OFFSET_shf        8
#define TM_MS_OFFSET_msk        0xFF

#define TM_MS_RDATA_LEN_shf     0
#define TM_MS_RDATA_LEN_msk     0x1F


#define TM_MS_OP_NOP            0xE0    /* OP(3)=7|BYTES(4)=?|MOD_RDATA(1)=? */


/**
 * NOP Rewrite Script word 0 format
 **/
#define TM_MS_NOP_w0            ((1 << TM_MS_DIRECT_shf) | \
                                 (TM_MS_OP_NOP << TM_MS_OPCODE_shf) | \
                                 (0 << TM_MS_OFFSET_shf) | \
                                 (0 << TM_MS_RDATA_LEN_shf))

/**
 * Rewrite Script word 1 format
 */
#define TM_MS_NOP_w1            0




/**
 * Receive a packet from a the local island's CTM workq.
 *
 * @param meta  Pointer to the location to store the packet metadata
 * @param msize The size of the metadata buffer (in bytes)
 * @param sync  The type of synchronization (sig_done or ctx_swap)
 * @param sig   The signal to use.
 */
__intrinsic void __pkt_nbi_recv(__xread void *meta, size_t msize, sync_t sync,
                                SIGNAL *sig);

__intrinsic void pkt_nbi_recv(__xread void *meta, size_t msize);


/**
 * Build a 40-bit pointer to the start of a CTM packet buffer from the CTM
 * island and packet number.
 *
 * @param isl   The CTM buffer island
 * @param pnum  The CTM packet number
 * @param off   The offset within the CTM buffer
 */
__intrinsic __addr40 void *
    pkt_ctm_ptr40_build(unsigned char isl, unsigned int pnum, unsigned int off);


/**
 * Build a 32-bit pointer to the start of a CTM packet buffer from the CTM
 * island and packet number.  Can only refer to a packet in the current
 * island.
 *
 * @param pnum  The CTM packet number
 * @param off   The offset within the CTM buffer
 */
__intrinsic __addr32 void *
    pkt_ctm_ptr32_build(unsigned int pnum, unsigned int off);


/**
 * Write a NOP modification script to the beginning of a packet and
 * return the metadata required to send the packet.  The pointer must 
 * point to the first byte of the packet to go over the wire (or the 
 * MAC prepend data that precedes it).  There must be at least 16 bytes
 * between this pointer and the beginning of the CTM buffer.
 *
 * @param pp    A pointer to the start of the packet buffer
 * @param off   The starting offset of the packet data
 * @param xms   Transfer registers to hold the script
 * @param sync  The type of synchronization (sig_done or ctx_swap)
 * @param sig   The signal to use.
 */
__intrinsic struct pkt_ms_info
    __pkt_nop_ms_write(__addr40 void *pp, unsigned char off, 
                       __xwrite uint32_t xms[2], sync_t sync, SIGNAL *sig);

__intrinsic struct pkt_ms_info
    pkt_nop_ms_write(__addr40 void *pp, unsigned char off);



/**
 * Send a packet to an NBI port.
 *
 * @param isl   The island of the CTM packet
 * @param pnum  The packet number of the CTM packet
 * @param msi   The modification script info required for transmission
 * @param len   The length of the packet from the start of the
 *              packet data (which immediately follows the rewrite
 *              script plus padding)
 * @param nbi   The NBI TM to send the packet to
 * @param txq   The NBI TM TX queue to send the packet to
 * @param seqr  The NBI TM sequencer to send the packet to
 * @param seq   The NBI TM sequence number of the packet
 *
 */
__intrinsic void pkt_nbi_send(unsigned char isl, unsigned int pnum,
                              __gpr const struct pkt_ms_info *msi,
                              unsigned int len, unsigned int nbi,
                              unsigned int txq, unsigned int seqr,
                              unsigned int seq);


/* TODO: Add pkt_drop() */

#endif /* __NFP_LANG_MICROC */

#endif /* !_PKT__PKT_H_ */
