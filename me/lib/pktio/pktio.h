/*
 * Copyright (C) 2017-2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/pktio/pktio.h
 * @brief         Interface to the packet library rx and tx
 */


/*
 *
 * OVERVIEW
 *
 * The purpose of this library is abstract basic packet I/O and state
 * in NFP processors.  Even with flowenv libraries to provide
 * developer-friendly access to common NFP operations, the process of
 * getting packets into and out of the NFP can be quite involved.  The
 * nature of the microC language can complicate this even further.  This
 * library represents a a distillation of best practices attempting to
 * achieve a balance between generality and performance while working in
 * the microC language.  The library is named 'libinfra' for historical
 * reasons.
 *
 * At the heart of this library are the pktio_rx_*() and pktio_tx()
 * functions.  The former receive packets from various types of sources
 * and store the metadata for the packet into a common format.  The
 * latter transmits the packet to the destination (selected from many
 * possible targets) stored in that metadata.  The packet metadata is a
 * thread-local global variable and most of the routines in this library
 * access that state implicitly.  This is generally poor interface
 * design, but its selection was purposeful.  The nfcc compiler has the
 * unfortunate property that it can spill variables with no location
 * declaration to external memory.  This is generally a horrible idea
 * and leads to all sorts of unexpected performance instabilities.
 *
 * While the API could have passed location-qualified packet metadata as
 * parameters to avoid spilling, this would force all packet metadata to
 * get stored in the same location negating one of the most crucial
 * benefits.  It also makes the API that much more ugly which negates
 * one of the other intended benefits.  The fact that we do not pass the
 * state by reference should give the compiler more liberty as far as
 * the placement of those variables.  They need not reside in contiguous
 * address space or even in the same memory location type which can be
 * of great benefit from a resource utilization standpoint.  Finally,
 * having the state kept in global memory makes it much less expensive
 * to wrap the functions in this library in subroutines.  This can offer
 * a significant code store and register usage savings if the structure
 * of the code requires multiple entry or exit points for packets.
 *
 * At the end of the day, it is still possible to have state for
 * multiple packets at the same time.  A simple structure copy can save
 * the global state and/or restore it and the target/source of those
 * operations can live anywhere including transfer registers (if the
 * state were stashed outside of the ME or needed to be passed that way).
 *
 *
 * BASIC USAGE
 *
 * This library supports sourcing and sinking packets from:
 *   - the physical MACs via the NBI (wire)
 *   - the PCIe interconnect (host or "NFD")
 *   - emem work queues (wq)
 * The user may also, of course, drop packets (which takes more effort
 * than one might think) which the library handles by passing the packet
 * to pktio_tx() with a destination of PKT_DROP.  It does not yet provide
 * nice functions for generating packets from scratch nor for cloning
 * packets.  The user must currently write such themselves.
 *
 * A typical packet loop for a general purpose run-to-completion working
 * using this library would usually look something like this:
 *
 *   for (;;) {
 *      if (some_criteria_based_on_ctx())
 *          pktio_rx_host();
 *      else
 *          pktio_rx_wire();
 *
 *      PACKET PROCESSING HERE
 *
 *      pktio_tx();
 *   }
 * It is possible to use the "issue" and "process" variants of the rx
 * calls to use the same thread for different packet sources. For example:
 *
 *   for (;;) {
 *       if (!nfd_in_progress) {
 *           pkt_num = pktio_rx_host_issue(..., sig_done, &sig_nfd);
 *           nfd_in_progress = 1;
 *       }
 *       if (!nbi_in_progress) {
 *          pktio_rx_wire_issue(..., sig_done, &sig_nbi);
 *          nbi_in_progress = 1;
 *       }
 *       for (;;) {
 *           // this gives nbi priority, round robin is recommended
 *           if (signal_test(&sig_nfd)) {
 *               to_process = NBI;
 *               break;
 *           }
 *           if (signal_test(&sig_nbi)) {
 *               to_process = NFD;
 *               break;
 *           }
 *           wait_for_any(&sig_nfd, &sig_nbi);
 *       }
 *       if (to_process == NBI) {
 *           pktio_rx_wire_process(...);
 *           nbi_in_progress = 0;
 *       } else {
 *           pktio_rx_wire_process(...)
 *           nfd_in_progress = 0;
 *       }
 *
 *       # PACKET PROCESSING HERE
 *
 *       pktio_tx();
 *   }
 *
 * Note that implementation a scheme as above will require global transfer
 * registers to be allocated for both the NBI and NFD issue commands. Doing
 * so might only be practical for designs using 4 context mode. One should
 * expect a reasonable performance increase with having all threads servicing
 * both traffic types.
 *
 * It is important to note that receiving from two or more sources at the same
 * time can also lead to suboptimal situations a thread can receive a packet
 * but not be ready to process it due to its current processing. This can occur
 * while other threads may be waiting idle for a packet. Furthermore, improper
 * processing of multiple sources can lead to deadlock.  For example, two
 * threads could each be waiting to submit their packet to reordering (while
 * the reorder queue is full) while each thread has the packet blocking
 * reordering progress for the other's queue waiting in their transfer
 * registers.
 *
 * There is no reason that the choice for a thread to receive from the
 * wire versus the host must be based on the thread number (ctx()), but
 * this tends to be a reasonable way to perform static partitioning of
 * the threads among input sources.
 *
 * A typical packet loop for an ME that is operating as a stage in a
 * processing pipeline would look like this:
 *
 *   for (;;) {
 *       pktio_rx_wq(...);
 *
 *       PACKET PROCESSING HERE
 *
 *       pktio_tx();
 *   }
 *
 * This style would also be applicable for an ME that was receiving and
 * processing control message that the main workers extract from the
 * primary packet stream.
 *
 * Multiplexing traffic from multiple input sources is problematic in
 * the NFP due to some of the very features that increase its
 * performance.  Traffic arriving from the NBI or from the NFD subsystem
 * that manages packetized PCIe access or on NFP-managed rings all use
 * "work queues".  Work queues simplify ordering assurances and decrease
 * polling and code store requirements in the system compared with
 * vanilla memory rings.  They are also the ONLY possibility for
 * receiving traffic from the wire due to the hardware design (and NFD
 * is also not trivial to change).
 *
 * The downside to work queues (in their various forms) is that once a
 * microengine issues the command to receive data from a work queue,
 * they are unable to "take it back".  Issuing that command commits the
 * transfer register and signal resources to the operation until data
 * arrives and the command completes.  If a thread wanted to receive
 * traffic from the wire, from the host and from a single work queue at
 * the same time, it would have to commit 8 + 4 + 4 == 16 of its 32
 * read-transfer registers and three out of 15 signals to the task.
 * Thus far, this has proven too high a cost for too little benefit for
 * this library to support.  So, thus far, there are no API calls for
 * supporting asynchronous packet reception.
 *
 * An alternative to static partitioning is to factor some notion of the
 * current traffic mix to move threads among input sources.  However, it
 * is important to always leave at least one thread on each possible
 * source because otherwise, if no traffic arrives on the other sources,
 * the system will stall processing packets entirely.
 *
 *
 * PACKET METADATA
 *
 * The global metadata for the (currently active) packet is stored in a
 * thread-local variable named 'Pkt'.  This metadata includes the
 * location of the CTM and MU packet buffers for the packet, the length
 * and starting offset of the packet, the packets source and destination
 * and various flags about the packet.  There are no APIs for getting
 * and setting the fields in this metadata:  the application can and
 * should access the fields of the 'Pkt' variable directly.  As
 * mentioned above, this state can be saved and restored via structure
 * copies to other variables of type 'struct pkt_meta'.
 *
 *
 * SOURCES AND DESTINATIONS
 *
 * Each packet metadata block contains a 16-bit packet source and 16-bit
 * packet destination.  The pktio_rx_*() routines initialize the source
 * field for every packet based on the incoming "port" of the packet.
 * They also all initialize the packet destination to PKT_DROP.
 * PKT_DROP is the destination that informs pktio_tx() to free the packet
 * buffers as well as its sequence number.  Thus any packet processing
 * that intends to forward the packet must explicitly set the packet
 * destination.  The packet's source is stored in the 'Pkt.p_src' field
 * and the packets destination is stored in the 'Pkt.p_dst' field.
 *
 * The 16-bit sources and destination values are actually encoded
 * 3-tuples consisting of:
 *   - type
 *   - subsystem ID
 *   - queue number
 * The type is one of DROP, WIRE, HOST, WQ, NONE and DROP_SEQ.  The
 * types DROP, DROP_SEQ and NONE are only valid as packet destinations.
 * The subsystem ID identifies a specific subsystem of the given type
 * that is the source or sink for the packet.  For example, the
 * subsystem ID for WIRE identifies the NBI of the given input or output
 * port.  The subsystem ID for HOST identifies the PCIe island and the
 * subsystem ID for 'WQ' identifies the memory unit that holds the work
 * queue.  The 'queue' then is the actual queue within the subsystem
 * that the packet either arrived on or is going to.
 *
 * The software should generally only set the destination of the packet
 * (Pkt.p_dst) and should set it using the PKT_* preprocessor macros and
 * #defines.
 *
 *   - PKT_DROP indicates that pktio_tx() should drop the packet and its
 *     sequence number if GRO is tracking its sequence number.  Again,
 *     this is the destination
 *
 *   - PKT_DROP_SEQ indicates that pktio_tx() should drop the packet
 *     sequence number from GRO but not otherwise send or drop
 *     the packet.  This is useful for allowing other pakcets to leave
 *     the system in order if a packet processing is taking
 *     exceptionally long.
 *
 *   - PKT_NOTX indicates that pktio_tx() should do nothing with the
 *     packet.  If the system were storing an unsequence packet for
 *     later use but control still needed to pass through the pktio_tx()
 *     call, then this would be the appropriate destination for the
 *     software to set.
 *
 *   - PKT_WIRE_PORT() builds a destination given an NBI and port number
 *     on that NBI.  Physical ports are numbered 0, 1, ... within
 *     libinfra and the library translates these to appropriate TM queue
 *     numbers.
 *
 *   - PKT_HOST_PORT() builds a destination from a PCIe island number
 *     (0..3), a VNIC reference and a queue number within that VNIC.  Two
 *     styles of VNIC references are supported: <vid> and <vtype, vnic>.
 *     <vid> references a VNIC as an index withing all the VNICs on a PCIe
 *     island.  <vtype, vnic> references a VNIC as a type (NFD_VNIC_TYPE_PF,
 *     NFD_VNIC_TYPE_VF, or NFD_VNIC_TYPE_CTRL) and an index within the
 *     VNICs of that type.  By default PKT_HOST_PORT() wraps
 *     PKT_HOST_PORT_VID(), but it can be redefined by the user to wrap
 *     PKT_HOST_PORT_VNIC().
 *
 *     The choice of whether to use <vid> or <vtype, vnic> APIs depends
 *     on a user's current and future needs.  If only one type of vNIC
 *     is required, or if the state of all vNICs is stored in a single
 *     large table, <vid> would be preferable.  If multiple types of
 *     vNICs are used, and the processing and state for each is
 *     significantly different, the <vtype, vnic> APIs would be
 *     preferable.
 *
 *   - PKT_WQ_PORT_BYNAME() builds a work queue destination given the
 *     symbol name used to create the work queue (see mem_ring.h).
 *
 *   - PKT_WQ_PORT() builds a work queue destination from a memory unit
 *     ID returned from MEM_RING_ADDR_TO_MUID() or ISL_TO_MUID() and
 *     from a queue number.  (_BYNAME() is the preferred API, but
 *     this API can be used if the work queue won't be known at compile
 *     time (e.g. if the system is load balancing among multiple work
 *     queues.)
 *
 * The software can query subfields of the packet source or destination
 * using the PKT_PORT_XXX_of() macros which take the Pkt.p_src/Pkt.p_dst
 * fields as an argument and return the various subfields encoded within
 * the port.
 *
 *
 * Note: The preprocessor macro "PORT_TO_CHANNEL(x)" must be defined.  This
 *       macro is used for translating the port number (faceplate port number
 *       starting with 0, and not the SerDes number) to the MAC channel
 *       number.
 *
 *       For example, if the mapping from port to MAC channel is the following:
 *           Port 0 => MAC Channel 0
 *           Port 1 => MAC Channel 4
 *           Port 2 => MAC Channel 8
 *           Port 3 => MAC Channel 12
 *
 *      ...then the "PORT_TO_CHANNEL(x)" macro can be defined as follows:
 *           #define PORT_TO_CHANNEL(x)  ((x) << 2)
 *
 * Note: The mapping from port to MAC channel is specific to the platform
 *       and/or the media configuration (e.g. when a 40GbE QSFP interface is
 *       configured to operate as four 10GbE interfaces).  For more information
 *       about the port to MAC channel mapping, please contact the appropriate
 *       support personnel for the platform.
 *
 * Note: The user may configure the number of Traffic Manager queues in use by
 *       defining PKTIO_MAX_TM_QUEUES. This value must be a power of 2. If not
 *       set, the Traffic Manager queue number may get truncated by a mask based
 *       default maximum.
 *
 * SEQUENCERS AND GLOBAL REORDER (GRO)
 *
 * Packets receive a sequence number when they are received, from a sequencer
 * associated with the ingress port.  They are reordered based on the sequence
 * number before they egress, either by the NBI hardware or in software by GRO.
 * Library users must specify their desired mapping from ingress sequencers to
 * egress sequencers.  The following macros returning the egress sequencer
 * should be defined:
 * PKTIO_NBI_SEQD_MAP_SEQR(_nbi, _seqr), _nbi is 0 or 1
 * PKTIO_NFD_SEQD_MAP_SEQR(_pci, _seqr), _pci is in 0..3
 *
 * If GRO is used, the following macros should also be defined, returning 1
 * if GRO should be used for this sequencer and 0 otherwise:
 * PKTIO_NBI_SEQD_MAP_ISGRO(_nbi, _seqr)
 * PKTIO_NFD_SEQD_MAP_ISGRO(_pci, _seqr)
 *
 * If only one PCI island or NBI is used, the _pci or _nbi parameter in the
 * macros above can be unused in the actual definition.
 *
 * OPTIONAL DEFINES
 *
 * PKTIO_NFD_CPY_START      Specifies the offset to start copying host packet
 *                          data from in MU into CTM.  Must be 64B aligned.
 *                          Defaults to "NFD_IN_DATA_OFFSET & ~0x3F".
 */

#ifndef __PKTIO_H__
#define __PKTIO_H__

#include <pkt/pkt.h>
#include <nfp/mem_ring.h>

/*
 * 35 == offset of 3 MU address bits in C0 40-bit addressing
 *   Those 3 bits are:
 *      1b0 | 2bxx for IMU island 28+xx
 *      1b1 | 2bxx for EMU island 24+xx
 * 8 == the right shift of that address in a mem_ring_addr_t
 * 24 == the base island of EMUs in B0
 * 28 == the base island of IMUs in B0
 */
/* XXX MEM_RING_ADDR_TO_MUID does not support emem_cache symbols currently */
#define MEM_RING_ADDR_TO_MUID(_x) (((_x) >> (35 - 8)) & 0x7)
#define ISL_TO_MUID(_x) \
    (((_x) <= 26) ? (((_x) - 24) | 4) : ((_x) - 28))
#define MUID_TO_MEM_RING_ADDR(_x) ((_x) << (35 - 8))
#define MUID_TO_ISL(_x) \
    (((_x) < 4) ? ((_x) + 28) : (((_x) & 0x3) + 24))

#ifdef PKTIO_NFD_ENABLED
#include <shared/nfd_common.h>
#endif

#ifndef PKTIO_MAX_TM_QUEUES
#define PKTIO_MAX_TM_QUEUES 256
#endif /* PKTIO_MAX_TM_QUEUES */

#if (PKTIO_MAX_TM_QUEUES & (PKTIO_MAX_TM_QUEUES - 1))
#error "PKTIO_MAX_TM_QUEUES must be a power of 2"
#endif

#if PKTIO_MAX_TM_QUEUES > 1024
#error "PKTIO_MAX_TM_QUEUES cannot be larger than 1024"
#endif

#if PKTIO_MAX_TM_QUEUES < 256
/* we silently make sure we don't truncate to less than 8-bits */
#undef PKTIO_MAX_TM_QUEUES
#define PKTIO_MAX_TM_QUEUES 256
#endif

/* Received NBI with/without MAC prepend */
#ifndef NBI_PKT_PREPEND_BYTES
#define NBI_PKT_PREPEND_BYTES 0
#warning "NBI_PKT_PREPEND_BYTES not defined, setting it to 0."
#endif

#if (NBI_PKT_PREPEND_BYTES >= 8)
/*
 * MAC prepend
 * 8 bytes prepended by NBI on ingress.
 * Adapted from implementation in SDN project (me/pktutil.h).
 */

/**
 * MAC packet metadata prepended to the packet
 *
 * NB:  this is not well documented in the DB.  Diagrams imply that the
 * timestamp will follow the parse information.  That may be true
 * internally in the MAC block.  But then the CSR description for
 * IgPrependEn specifies that the timestamp will come first as does
 * the "Ingress Timestamp" section indirectly when it says:
 *   "When the EOP for the packet is received and the parsing is
 *   complete and the timestamp prepend is enabled, the 32-bit
 *   timestamp is written to the first 256-bit word of the packet at a
 *   32-bit offset with TBD written at the 0 offset."
 * Empirical analysis shows that, indeed, the timestamp comes first.
 *
 * Bit    3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 * -----\ 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * Word  +---------------------------------------------------------------+
 *    0  |                          Timestamp                            |
 *       +-----+-+-+-+-+-+-+-+---+---+---+-------------------------------+
 *    1  | CS  |M|E|A|F|D|R|H| L3|MPL|VLN|           Checksum            |
 *       +-----+-+-+-+-+-+-+-+---+---+---+-------------------------------+
 *
 *   CS - Checksum status
 *   M - IPv6 Mobility extension header detected
 *   E - IPv6 ESP extension header detected
 *   A - IPV6 AH extension header detected
 *   F - IPv6 Fragment extension header detected
 *   D - IPv6 Destination extension header detected
 *   R - IPv6 Routing extension header detected
 *   H - IPv6 Hop-by-Hop extension header detected
 *   L3 - Layer 3 indication
 *   MPL - MPLS indication
 *   VLN - VLAN indication
 *   CSUM - 16 bits csum value
 */
struct pktio_mac_prepend {
    union {
        struct {
            unsigned int timestamp:32;

            unsigned int csum_status:3; /**<  layer 4 checksum status */
            unsigned int resv1:7;       /**<  reserved */
            unsigned int l3_info:2;     /**<  layer 3 info */
            unsigned int mpls_count:2;  /**<  Number of MPLS labels
                                         *    (3 = 3 or more) */
            unsigned int vlans_count:2; /**<  Number of VLANs present
                                         *    (3 = 3 or more) */
            unsigned int csum:16;       /**<  16-bit L4 TCP/UDP checksum if
                                         *    TCP/UDP is parse-able. If not
                                         *    16-bit checksum for received
                                         *    packet excluding CRC. */
        };
        uint32_t __raw[2];
    };
};

/**
 * NBI metadata struct comprised of 24 bytes of catamaran metadata as well
 * as 8 bytes of prepended MAC metadata (pkt/pkt.h).
 */
struct pktio_nbi_meta {
    union {
        struct {
            struct nbi_meta_catamaran   nbi;
            struct pktio_mac_prepend    mac;
        };
        uint32_t __raw[8];
    };
};

#else
/**
 * NBI metadata struct comprised of 24 bytes of catamaran metadata with no
 * MAC prepended data.
 */
struct pktio_nbi_meta {
    union {
        struct {
            struct nbi_meta_catamaran   nbi;
        };
        uint32_t __raw[6];
    };
};
#endif /* NBI_PKT_PREPEND_BYTES >= 8 */


#ifdef PKTIO_VLAN_ENABLED
 #define PKTIO_NBI_META_LW_VLAN 1
#else
 #define PKTIO_NBI_META_LW_VLAN 0
#endif

/*
 * LSO and MAC timestamp shares a 32-bit word
 */
#ifdef PKTIO_LSO_ENABLED
#define PKTIO_NBI_META_LW_LSO 1
#elif (NBI_PKT_PREPEND_BYTES >= 8)
#define PKTIO_NBI_META_LW_LSO 1
#else
#define PKTIO_NBI_META_LW_LSO 0
#endif

#define PKTIO_NBI_META_LW (5 + PKTIO_NBI_META_LW_VLAN + PKTIO_NBI_META_LW_LSO)

/**
 * Global packet metadata.
 */
struct pktio_meta {
    union {
        struct {
            struct nbi_meta_pkt_info p_nbi;     /**< Std NBI-formatted metadata
                                                  *  accessor #defines below */

            unsigned int p_ctm_size:2;          /**< CTM buffer encoded size */
            unsigned int p_orig_len:14;         /**< Original RX pkt length */
            unsigned int p_offset:16;           /**< Offset of data in buffer*/

            unsigned int p_src:16;              /**< Source port */
            unsigned int p_dst:16;              /**< Destination port */

            unsigned int p_seq:16;              /**< Sequence number */
            unsigned int p_ro_ctx:5;            /**< Reorder context mapped
                                                  *  from NBI or NFD seqr */
            unsigned int p_is_gro_seq:1;        /**< Is pkt to be reordered
                                                  *  with GRO? */
            unsigned int p_rx_ipv4_csum_ok:1;   /**< Set if IP csum was ok */
            unsigned int p_rx_ipv4_csum_present:1;/**< Set if IP csum present*/
            unsigned int p_rx_l4_csum_ok:1;     /**< Set if L4 csum was ok */
            unsigned int p_rx_l4_csum_present:1;/**< Set if L4 csum present */
            unsigned int p_rx_l4_tcp:1;         /**< Set if L4 is TCP */
            unsigned int p_rx_mac_matched:1;    /**< Dst MAC match port MAC? */
#ifdef MAC_EGRESS_PREPEND_ENABLE
            /* The CSUM Tx flags serves two purposes :
             * 1. For packets received from the host those flags cache the
             *    Tx CSUM flags extracted from the NFD descriptor and are
             *    later used in the Tx CSUM offload performed by the ME.
             *    When this stage is done those bits are cleared.
             * 2. For packets being sent out on the wire those flags are used
             *    to setup the MAC CSUM offload processing.
             */
            unsigned int p_tunnel:1;            /**< A tunnel packet */
            unsigned int resv4:1;               /**< Reserved */
            unsigned int p_tx_l3_csum:1;        /**< Req L3 csum TX offload */
            unsigned int p_tx_l4_csum:1;        /**< Req L4 csum TX offload */
#else
            unsigned int p_tunnel:1;            /**< A tunnel packet */
            unsigned int resv4:3;               /**< Reserved */
#endif

            union {
#ifdef PKTIO_LSO_ENABLED                        /**< LSO if host packet */
                struct {
                    unsigned int p_tx_lso:1;    /**< Pkt was PCIe LSO pkt */
                    unsigned int p_tx_lso_end:1;/**< Pkt is last in series*/
                    unsigned int resv2:6;       /**< Reserved */
                    unsigned int p_tx_lso_seq:8;/**< Pkt num in LSO sequence */
                    unsigned int p_tx_mss:14;   /**< MSS of TCP */
                    unsigned int resv1:2;       /**< Reserved */
                };
#endif
#if NBI_PKT_PREPEND_BYTES >= 8                  /**< timestamp if NBI packet */
                unsigned int p_timestamp:32;    /**< MAC timestamp */
#endif
            };

#ifdef PKTIO_VLAN_ENABLED
            unsigned int p_vlan:16;             /**< VLAN id for RX and TX VLAN
                                                  *  offloading */
            unsigned int resv3:16;              /**< Reserved */
#endif
        };

        uint32_t __raw[PKTIO_NBI_META_LW];
    };
};

/* These are accessor macros for subfields within p_nbi */
#define p_isl p_nbi.isl         /* Island number of the CTM buffer */
#define p_pnum p_nbi.pnum       /* CTM packet number */
#define p_bls p_nbi.bls         /* Buffer list of the MU buffer */
#define p_len p_nbi.len         /* Length of the packet */
#define p_is_split p_nbi.split  /* Set if split between CTM and MU */
#define p_muptr p_nbi.muptr     /* MU buffer handle of the packet */



/*
 * Source and destination port defines and macros.
 */
enum port_type {
    PKT_PTYPE_DROP     = 0,
    PKT_PTYPE_WIRE     = 1,
    PKT_PTYPE_HOST     = 2,
    PKT_PTYPE_WQ       = 3,
    PKT_PTYPE_NONE     = 4
};

enum {
    PKT_DROPT_ALL = 0,
    PKT_DROPT_SEQ = 1,
};

/**
 * Build a port type.
 * @param type          Type of port (wire, host, ..) See enum port_type.
 * @param subsys        Number of NBI or PCIe
 * @param port          Queue number
 */
#define PKT_SET_PORT(type, subsys, port) \
    ((type) << 13) | ((subsys) << 10) | ((port))

#define PKT_DROP \
    PKT_SET_PORT(PKT_PTYPE_DROP, 0, PKT_DROPT_ALL)
#define PKT_DROP_SEQ \
    PKT_SET_PORT(PKT_PTYPE_DROP_SEQ, 0, 0)
#define PKT_NOTX \
    PKT_SET_PORT(PKT_PTYPE_NONE, 0, 0)
#define PKT_WIRE_PORT(_nbi, _q) \
    PKT_SET_PORT(PKT_PTYPE_WIRE, (_nbi), (_q))
#define PKT_HOST_PORT_FROMQ(_pcie, _q) \
    PKT_SET_PORT(PKT_PTYPE_HOST, (_pcie), (_q))
#if defined (NFD_VNIC_TYPE_VF) && defined (NFD_VNIC_TYPE_PF)
#define PKT_HOST_PORT_VNIC(_pcie, _vtype, _vnic, _q)                \
    PKT_HOST_PORT_FROMQ(_pcie, NFD_BUILD_QID(_vtype, _vnic, _q))
#define PKT_HOST_PORT_VID(_pcie, _vid, _q) \
    PKT_HOST_PORT_FROMQ(_pcie, NFD_VID2QID(_vid, _q))
#ifndef PKT_HOST_PORT
#define PKT_HOST_PORT(_pcie, _vid, _q) PKT_HOST_PORT_VID(_pcie, _vid, _q)
#endif
#else
#define PKT_HOST_PORT(_pcie, _vnic, _q) \
    PKT_HOST_PORT_FROMQ(_pcie, NFD_BUILD_QID((_vnic), (_q)))
#endif
#define PKT_WQ_PORT(_muid, _q) \
    PKT_SET_PORT(PKT_PTYPE_WQ, _muid, _q)
#define PKT_WQ_PORT_BYNAME(_name) \
    PKT_SET_PORT(PKT_PTYPE_WQ, \
                   MEM_RING_ADDR_TO_MUID(MEM_RING_GET_MEMADDR(_name)), \
                   MEM_RING_GET_NUM(_name))

#define PKT_PORT_TYPE_of(_port)         (((_port) >> 13) & 0x7)
#define PKT_PORT_SUBSYS_of(_port)       (((_port) >> 10) & 0x7)
#define PKT_PORT_DROPTYPE_of(_port)     ((_port) & 0xff)
#define PKT_PORT_QUEUE_of(_port)        ((_port) & ((PKTIO_MAX_TM_QUEUES) - 1))
#if defined (NFD_VNIC_TYPE_VF) && defined (NFD_VNIC_TYPE_PF)
#define PKT_PORT_EXTRACT_VNIC(_vtype, _vnic, _vqn, _port) \
    NFD_EXTRACT_QID(_vtype, _vnic, _vqn, PKT_PORT_QUEUE_of(_port))
#define PKT_PORT_EXTRACT_VID(_vid, _vqn, _port) \
    NFD_QID2VID(_vid, _vqn, PKT_PORT_QUEUE_of(_port))
#endif
#ifdef NFD_VNIC_TYPE_VF
#define PKT_PORT_VFVNIC_of(_vf)         NFD_VF2VID(NFD_NATQ2VF((_vf)))
#else
#define PKT_PORT_VFVNIC_of(_vf)         NFD_NATQ2VF((_vf))
#endif
#ifdef NFD_VNIC_TYPE_PF
#define PKT_PORT_PFVNIC_of(_pf_port)    NFD_PF2VID(NFD_NATQ2PF((_pf_port)))
#else
#define PKT_PORT_PFVNIC_of(_pf_port)    NFD_NATQ2PF((_pf_port))
#endif
#define PKT_PORT_WQNUM_of(_port)        ((_port) & 0x3ff)
#define PKT_PORT_MUID_of(_port)         (((_port) >> 10) & 0x7)



/* Packet meta; if not defined let the compiler pick where to place it */
#ifndef PKTIO_META_TYPE
#define PKTIO_META_TYPE
#endif

/* Thread-local pkt metadata */
extern PKTIO_META_TYPE struct pktio_meta pkt;

/**
 * Receive a packet from the wire and populate the packet metadata.
 *
 * @return -1 on error and 0 otherwise
 *
 * On a return value of -1, the caller should call pktio_tx_drop() to free the
 * packet buffers.
 */
__intrinsic int pktio_rx_wire(void);

/**
 * Issue a request for a wire packet. This should be followed by a
 * pktio_rx_wire_process call once the request is signalled complete.
 * Note that 'nbi_meta' must be at least the size of the 'pktio_nbi_meta'.
 * It may also be up to 128 bytes. All data beyond the size of 'pktio_nbi_meta'
 * will be packet data copied from the offset PKT_NBI_OFFSET. Note that
 * if the MAC prepend is enabled, the prepend data will be included in the
 * 'pktio_nbi_meta' data and the effective packet data offset will be
 * sizeof(pktio_nbi_meta.nbi) + NBI_PKT_PREPEND_BYTES
 *
 * @param nbi_meta       Pointer to NBI metadata read transfer buffer to use
 * @param nbi_meta_size  Size of the NBI metadata buffer
 * @param sync           Type of synchronisation (sig_done or ctx_swap)
 * @param sig            Signal to use
 *
 */
__intrinsic void
pktio_rx_wire_issue(__xread void *nbi_meta, size_t nbi_meta_size,
                    sync_t sync, SIGNAL *sig);

/**
 * Process the result of an NBI RX issue. This should be preceded by a
 * pktio_rx_wire_issue call.
 *
 * @param nfd_meta  Pointer to NBI metadata read transfer buffer to use
 *
 * @return -1 on error and 0 otherwise
 *
 */
__intrinsic int
pktio_rx_wire_process(__xread void *nbi_meta);

/**
 * Receive a packet from the host and populate the packet metadata
 *
 * @return -1 on error and 0 otherwise
 *
 * On a return value of -1, the caller should call pktio_tx_drop() to free the
 * packet buffers.
 */
__intrinsic int pktio_rx_host(void);

/**
 * Claim a host packet buffer and issue a request for a host packet. This should
 * be followed by a pktio_rx_host_process call once the request is signalled
 * complete.
 *
 * @param nbi_rxd   Pointer to NFD metadata read transfer buffer to use
 * @param sync      Type of synchronisation (sig_done or ctx_swap)
 * @param sig       Signal to use
 *
 * @return the claimed CTM packet number
 */
__intrinsic int
pktio_rx_host_issue(__xread struct nfd_in_pkt_desc *nfd_rxd, sync_t sync,
                    SIGNAL *sig);

/**
 * Process the result of a host RX issue. This should be preceded by a
 * pktio_rx_host_issue call
 *
 * @param nfd_rxd   Pointer to NFD metadata read transfer buffer to use
 * @param ctm_pnum  Previously claimed CTM packet number
 *
 * @return -1 on error and 0 otherwise
 *
 */
__intrinsic int
pktio_rx_host_process(__xread struct nfd_in_pkt_desc *nfd_rxd, int ctm_pnum);

/**
 * Receive a packet from a work queue
 *
 * @param ring_num      The work queue ring number
 * @param ring_addr     The work queue ring mem address
 */
__intrinsic void pktio_rx_wq(int ring_num, mem_ring_addr_t ring_addr);


/**
 * Send a packet to the destination set in Pkt.destination.  This will include
 * submitting the packet to GRO if 'Pkt.unseq' is clear and GRO is enabled.
 *
 * If the packet is going to a WIRE port, TX processing may also include
 * requesting the MAC to offload checksum calculation for the outer IP
 * and TCP/UDP packets if MAC_EGRESS_PREPEND_ENABLE is defined and
 * tx_lx_csum is set.
 *
 * If an error occurs on tx, the packet is dropped.
 *
 * @param app_nfd_flags Application supplied NFD flags to be ORed in
 * @param meta_len      Length of meta data prepended to the packet
 *
 * @return 0 if no error or:
 *      return -1 if no NFD credits
 *      return -2 if packet modifier script error
 *      return -3 if MAC port is paused (on wire)
 */
__intrinsic int pktio_tx_with_meta(unsigned short app_nfd_flags,
                                   unsigned short meta_len);
__intrinsic int pktio_tx(void);

/**
 * Drop a packet.
 * A packet is dropped regardless of Pkt.p_dst (destination).
 * This function is equavalent to calling pktio_tx() with
 * Pkt.p_dst = PKT_PTYPE_DROP
 * Because this function is not an intrinsic, it can be called from the
 * application multiple times without using too much code space.
 * This is normally called when a parsing or any processing error occurs
 * without having to set the destination.
 */
void pktio_tx_drop(void);


/**
 * Give the packet source an opportunity to be initialised.
 *
 * Will not relinquish context until completed. This should be called by a
 * single context on each ME intending to use pktio_rx_*
 */
void pktio_rx_init(void);


/**
 * Give the packet destination an opportunity to be initialised.
 *
 * Will not relinquish context until completed. This should be called by a
 * single context on each ME intending to use pktio_tx
 */
void pktio_tx_init(void);

#endif /* __PKTIO_H__ */
