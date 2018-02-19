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
 * @file        lib/pktio/libpktio.c
 * @brief       Functions to interface with the packet rx and tx
 */

/*
 * This file contains the interface to the rx and tx functions.  It
 * currently only defines the application side of the interface and
 * only provide the interface in MicroC.
 *
 * It's main purpose is to hide the details of receiving and transmitting
 * packets from the application code. Regardless of the source a packet is,
 * a generic RX descriptor is returned. Similarly a generic TX descriptor
 * is used to send to any destination.
 *
 */
#include <assert.h>
#include <nfp.h>
#include <stdint.h>

/* Library Includes */
#include <nfp/me.h>
#include <nfp/mem_bulk.h>
#include <nfp/mem_ring.h>
#include <nfp/cls.h>
#include <nfp6000/nfp_me.h>
#include <nfp6000/nfp_mac.h>
#include <std/cntrs.h>
#include <std/reg_utils.h>

/* Blocks */
#ifdef PKTIO_NFD_ENABLED
#include <shared/nfp_net_ctrl.h>
#include <vnic/pci_in.h>
#include <vnic/pci_out.h>
#endif

#ifdef PKTIO_GRO_ENABLED
#include <gro_cli.h>
#endif

#include <blm/blm.h>
#include <pktio/pktio.h>
#include <modscript/modscript.h>

#if (__REVISION_MAX < __REVISION_B0)
#error "Unsupported chip type"
#endif

struct pktio_handle {
    union {
        struct {
            uint8_t ph_isl;
            uint8_t pad;
            uint16_t ph_pnum;
        };
        uint32_t __raw;
    };
};


/*
 * Defines
 */

/* GRO will stall if DMA drops are enabled */
#if (GRO_NUM_BLOCKS > 0 && defined NBI_DMA_BP_DROP_ENABLE)
    #if (NBI_DMA_BP_DROP_ENABLE != 0)
            #error "DMA DROP must be disabled when GRO is used"
    #endif
#endif

/* Check defines */
#ifndef PKTIO_NBI_SEQD_MAP_SEQR
#error "PKTIO_NBI_SEQD_MAP_SEQR must be defined to map the NBI seqr to NBI or GRO"
#endif

#ifdef PKTIO_GRO_ENABLED
    #ifndef PKTIO_NBI_SEQD_MAP_ISGRO
    #error "PKTIO_NBI_SEQD_MAP_ISGRO must be defined to configure GRO reordering for NBI"
    #endif
#endif

#ifdef PKTIO_NFD_ENABLED
    #ifndef PKTIO_NFD_SEQD_MAP_SEQR
    #error "PKTIO_NFD_SEQD_MAP_SEQR must be defined to map the NFD seqr to NBI or GRO"
    #endif

    #ifdef PKTIO_GRO_ENABLED
        #ifndef PKTIO_NFD_SEQD_MAP_ISGRO
        #error "PKTIO_NFD_SEQD_MAP_ISGRO must be defined to configure GRO reordering for NFD"
        #endif
    #endif

    #ifndef PKTIO_NFD_CPY_START
        #define PKTIO_NFD_CPY_START (NFD_IN_DATA_OFFSET & ~0x3F)
    #endif
#endif


#ifdef PKTIO_NFD_ENABLED
    #if ((NFD_CFG_PF_CAP|NFD_CFG_VF_CAP) & NFP_NET_CFG_CTRL_TXVLAN)
        #ifndef PKTIO_VLAN_ENABLED
            #warning "Firmware supports VLAN offloading but PKTIO_VLAN_ENABLED is not set"
        #endif /* PKTIO_VLAN_ENABLED */
    #endif
#else  /* NFD TX VLAN offload configured */
    #ifdef PKTIO_VLAN_ENABLED
        #warning "PKTIO_VLAN_ENABLED is set but NFD is not configured to support it."
    #endif /* PKTIO_VLAN_ENABLED */
#endif /* NFD TX VLAN offload configured */


/*
 * Half of the packet and buffer credits allocated to the ME
 */
#ifndef ME_CTM_ALLOC_MAX_PKT_CREDITS
#define ME_CTM_ALLOC_MAX_PKT_CREDITS 256
#endif

#ifndef ME_CTM_ALLOC_MAX_BUF_CREDITS
#define ME_CTM_ALLOC_MAX_BUF_CREDITS 64
#endif

/*
 * Can get per packet using pkt_status_read or from DMA engine,
 * see EAS DMA 2.2.4.6 NbiDmaBPCfg Reg
 */
#ifndef SPLIT_LENGTH
#warning "SPLIT_LENGTH is not defined, default to 3."
#define SPLIT_LENGTH 3    /* Split when the pkt is greater than 2K Bytes */
#endif

/*
 * Mapping between port and MAC channel.
 * If not user defined (see pktio.h for more information),
 * this macro maps i.e. port 1 to channel 16
 */
#ifndef PORT_TO_CHANNEL(x)
 #define PORT_TO_CHANNEL(x) ((x) << 4)
 #warning "PORT_TO_CHANNEL(x) is undefined!"
#endif
/*
 * Mapping between channel and TM queue
 */
#ifndef CHANNEL_TO_TMQ(y)
 #define CHANNEL_TO_TMQ(y) (y << 3)
 #warning "CHANNEL_TO_TMQ(y) is undefined!"
#endif


 /* Note: Define this macro if a different behavior is desired for the NBI
  *       metadata error handling. */
 #ifndef HANDLE_NBI_METADATA_ERR(_nbi_rxd)
 #define HANDLE_NBI_METADATA_ERR(_nbi_rxd)         \
     do {                                          \
         PKTIO_CNTR_INC(PKTIO_CNTR_ERR_FROM_WIRE); \
         return -1;                                \
     } while (0)
#endif

 /* Note: Define this macro if a different behavior is desired for the NBI
  *       metadata error checking. */
 #ifndef NBI_METADATA_ERR_CHECK(_meta)
 #define NBI_METADATA_ERR_CHECK(_meta) ((_meta).ie != 0)
 #endif

/* Debug counters */
#ifdef PKTIO_CNTRS_ENABLE
    #define PKTIO_CNTR_RX_FROM_WIRE         0
    #define PKTIO_CNTR_ERR_FROM_WIRE        1
    #define PKTIO_CNTR_RX_FROM_HOST         2
    #define PKTIO_CNTR_ERR_FROM_HOST        3
    #define PKTIO_CNTR_TX_DROP              4
    #define PKTIO_CNTR_TX_TO_WIRE           5
    #define PKTIO_CNTR_TX_TO_HOST           6
    #define PKTIO_CNTR_ERR_TO_HOST          7
    #define PKTIO_CNTR_ERR_TO_WIRE          8
    #define PKTIO_CNTR_ERR_MAC_PORT_PAUSED  9
    #define PKTIO_CNTR_INVALID_METADATA_FROM_WIRE 10

__shared __gpr uint32_t pktio_cntrs_base;
    CNTRS64_DECLARE(vr_pktio_cntrs_base, 32, __emem);
    #define PKTIO_CNTR_INC(_cntr) \
                    cntr64_incr(pktio_cntrs_base, _cntr)
    #define PKTIO_CNTRS_SET_BASE(_base)  \
                    (_base) = cntr64_get_addr(vr_pktio_cntrs_base)
#else
    #define PKTIO_CNTR_INC(_cntr)
    #define PKTIO_CNTRS_SET_BASE(_base)
#endif


/* Only support single NFD work queue */
#define NFD_IN_WQ           0

/* NFD CTM size and type */
#define MIN_CTM_TYPE        PKT_CTM_SIZE_256
#define MIN_CTM_SIZE        (256 << MIN_CTM_TYPE)

#ifndef NFD_PKT_CTM_SIZE
#define NFD_CTM_TYPE MIN_CTM_TYPE
#else
#define NFD_CTM_TYPE NFD_PKT_CTM_SIZE
#endif

#define NFD_CTM_SIZE (256 << NFD_CTM_TYPE)


/* CTM credit management, required for RX from host. Use all of CTM RX */
#define CTM_ALLOC_ERR                   0xffffffff

__export __shared __cls struct ctm_pkt_credits ctm_credits =
    {ME_CTM_ALLOC_MAX_PKT_CREDITS, ME_CTM_ALLOC_MAX_BUF_CREDITS};

/* Declaration of pkt */
PKTIO_META_TYPE struct pktio_meta pkt;


/*
 * This routine takes about 7 cycles to execute in the worst case for small
 * packets.  As it turns out it takes 7-9 cycles plus a serial I/O to read in
 * the packet status and get the CTM split from the packet engine.  So it's a
 * win just to compute the CTM size manually.
 */
__intrinsic static void
compute_ctm_size(__xread struct pktio_nbi_meta *rxd)
{
    /* if SPLIT_LEN == 0, assume initialized to 0 already */
#if SPLIT_LENGTH > 0
    uint32_t len = (rxd->nbi.__raw[0] + (PKT_NBI_OFFSET - 1));
    uint32_t x;

    /*
     * Computing: len + offset - 1
     *   00 0000 xxxx xxxx .. 11 1111 xxxx xxxx
     */

#if SPLIT_LENGTH == 1
    /*
     * 00 0000 xxxx xxxx -> 00
     * 00 0001 xxxx xxxx .. 11 1111 xxxx xxxx -> 01
     */

    len = ((len >> 8) & 0x3f) != 0;

#elif SPLIT_LENGTH == 2

    /*
     * 00 0000 xxxx xxxx -> 00
     * 00 0001 xxxx xxxx -> 01
     * 00 0010 xxxx xxxx .. 11 1111 xxxx xxxx -> 10
     */

    len = ((len >> 9) & 0x1f) ? 2 : (len >> 8) & 1;

#else /* SPLIT_LENGTH == 3 */

    /*
     * 00 0000 xxxx xxxx -> 00
     * 00 0001 xxxx xxxx -> 01
     * 00 0010 xxxx xxxx .. 00 0011 xxxx xxxx -> 10
     * 00 0100 xxxx xxxx .. 11 1111 xxxx xxxx -> 11
     * N.B. that for sizes 1025 .. 16384:
     *   00 1000 xxxx xxxx .. 11 1111 xxxx xxxx
     * the rxd->pktio_meta.split bit will be set.
     */

    if ((len >> 10) & 0x3F) {
        len = 3;
    } else {
        __critical_path();
        len = (len >> 8) & 3;
        x = (len >> 1) & 1;
        len = len ^ x;
    }

#endif /* SPLIT_LENGTH == 3 */

    pkt.p_ctm_size = len;

#endif /* SPLIT_LENGTH > 0 */
}


#ifdef PKTIO_GRO_ENABLED
__intrinsic void
drop_packet(__xwrite struct gro_meta_drop *gmeta)
{
    blm_buf_free(pkt.p_muptr, pkt.p_bls);
    pkt_ctm_free(pkt.p_isl, pkt.p_pnum);

    /* If packet has to be reordered, drop with GRO if enabled otherwise
     * drop with NBI. */

    if (pkt.p_is_gro_seq)  {
        gro_cli_build_drop_seq_meta(gmeta);
    } else
#ifdef PKTIO_NBI_SEQR_ENABLED
    if (pkt.p_ro_ctx) {
        __gpr struct pkt_ms_info msi = {0,0}; /* dummy msi */
        /* Notify the NBI to ignore this packet's sequence number */
        pkt_nbi_drop_seq(pkt.p_isl,
                         pkt.p_pnum,
                         &msi,
                         pkt.p_len,
                         0,
                         0,
                         pkt.p_ro_ctx,
                         pkt.p_seq,
                         pkt.p_ctm_size);
    } else
#endif
    ;
}

#else

__intrinsic void
drop_packet()
{
    blm_buf_free(pkt.p_muptr, pkt.p_bls);
    pkt_ctm_free(pkt.p_isl, pkt.p_pnum);

    /* If ordered packet, drop with seq number in NBI. */
#ifdef PKTIO_NBI_SEQR_ENABLED
    if (pkt.p_ro_ctx) {
        __gpr struct pkt_ms_info msi = {0,0}; /* dummy msi */
        /* Notify the NBI to ignore this packet's sequence number */
        pkt_nbi_drop_seq(pkt.p_isl,
                         pkt.p_pnum,
                         &msi,
                         pkt.p_len,
                         0,
                         0,
                         pkt.p_ro_ctx,
                         pkt.p_seq,
                         pkt.p_ctm_size);
    }
#endif
}

#endif

__intrinsic void
pktio_rx_wire_issue(__xread void *nbi_meta, size_t nbi_meta_size, sync_t sync,
                    SIGNAL *sig)
{
    __pkt_nbi_recv_with_hdrs(nbi_meta, nbi_meta_size, PKT_NBI_OFFSET,
                             sync, sig);
}

__intrinsic int
pktio_rx_wire_process(__xread void *nbi_meta)
{
    __xread struct pktio_nbi_meta *nbi_rxd = nbi_meta;

    reg_zero((void *)pkt.__raw, sizeof(pkt));
    pkt.p_offset = PKT_NBI_OFFSET + NBI_PKT_PREPEND_BYTES;
    pkt.p_nbi = nbi_rxd->nbi.pkt_info;
    pkt.p_len -= NBI_PKT_PREPEND_BYTES;
    pkt.p_orig_len = pkt.p_len;
    pkt.p_src = PKT_WIRE_PORT(nbi_rxd->nbi.meta_type,
                              PORT_TO_CHANNEL(nbi_rxd->nbi.port));
    compute_ctm_size(nbi_rxd);

    /**
     * If sequencer > 0, we set the reorder context.
     * The reorder context can be either GRO or NBI.
     * In the case of GRO reordering, typically the NBI sequencers map to
     * GRO sequencers 1, 3, 5, 7.
     * If NBI reordering, typically the NBI sequencers are mapped as 1:1
     * Use the PKTIO_NBI_SEQD_MAP_ISGRO macro to indicate if GRO reordering
     * will be used.
     * Use the PKTIO_NBI_SEQD_MAP_SEQR macro to map the NBI received sequencer
     * to GRO or NBI.
     * Sequencer 0 is for unsequenced packets, leave reorder context at 0 for
     * no reordering
     */
    pkt.p_seq = nbi_rxd->nbi.seq;
    if (nbi_rxd->nbi.seqr) {
        __critical_path();
        /* map NBI seqr's to GRO or map NBI seqr's to NBI if GRO disabled */
        pkt.p_ro_ctx = PKTIO_NBI_SEQD_MAP_SEQR(nbi_rxd->nbi.meta_type,
                                               nbi_rxd->nbi.seqr);
#ifdef PKTIO_GRO_ENABLED
        pkt.p_is_gro_seq = PKTIO_NBI_SEQD_MAP_ISGRO(nbi_rxd->nbi.meta_type,
                                                    nbi_rxd->nbi.seqr);
#endif
    }

#if NBI_PKT_PREPEND_BYTES >= 8
    /* Set the MAC prepend checksum info for layer 3*/
    if (nbi_rxd->mac.l3_info == NFP_MAC_RX_CSUM_L3_IPV4_OK) {
        pkt.p_rx_ipv4_csum_ok = 1;
        pkt.p_rx_ipv4_csum_present = 1;
    } else if (nbi_rxd->mac.l3_info == NFP_MAC_RX_CSUM_L3_IPV4_FAIL) {
        pkt.p_rx_ipv4_csum_ok = 0;
        pkt.p_rx_ipv4_csum_present = 1;
    } else {
        pkt.p_rx_ipv4_csum_present = 0;
    }

    /* Set the MAC prepend checksum info for layer 4*/
    if (nbi_rxd->mac.csum_status == NFP_MAC_RX_CSUM_L4_TCP_OK) {
        __critical_path();
        pkt.p_rx_l4_tcp = 1;
        pkt.p_rx_l4_csum_ok = 1;
        pkt.p_rx_l4_csum_present = 1;
    } else if (nbi_rxd->mac.csum_status == NFP_MAC_RX_CSUM_L4_TCP_FAIL) {
        pkt.p_rx_l4_tcp = 1;
        pkt.p_rx_l4_csum_ok = 0;
        pkt.p_rx_l4_csum_present = 1;
    } else if (nbi_rxd->mac.csum_status == NFP_MAC_RX_CSUM_L4_UDP_OK) {
        /* Note UDP_OK is also returned when
         * the checksum is not populated (=0) */
        pkt.p_rx_l4_csum_ok = 1;
        pkt.p_rx_l4_csum_present = 1;
    } else if (nbi_rxd->mac.csum_status == NFP_MAC_RX_CSUM_L4_UDP_FAIL) {
        pkt.p_rx_l4_csum_ok = 0;
        pkt.p_rx_l4_csum_present = 1;
    }

    pkt.p_timestamp = nbi_rxd->mac.timestamp;
#endif

#ifdef NBI_MAC_MATCHED
    pkt.p_rx_mac_matched = NBI_MAC_MATCHED(nbi_rxd->nbi);
#endif

    /* Check for metadata invalid. */
    if (nbi_rxd->nbi.meta_valid == 0) {
        PKTIO_CNTR_INC(PKTIO_CNTR_INVALID_METADATA_FROM_WIRE);
        return -1;
    }

    if (NBI_METADATA_ERR_CHECK(nbi_rxd->nbi)) {
        HANDLE_NBI_METADATA_ERR(*nbi_rxd);
    }

    PKTIO_CNTR_INC(PKTIO_CNTR_RX_FROM_WIRE);
    return 0;
}

__intrinsic int
pktio_rx_wire(void)
{
    SIGNAL sig;
    __xread struct pktio_nbi_meta nbi_rxd;

    pktio_rx_wire_issue(&nbi_rxd, sizeof(nbi_rxd), ctx_swap, &sig);

    return pktio_rx_wire_process(&nbi_rxd);
}


#ifdef PKTIO_NFD_ENABLED
__intrinsic int
pktio_rx_host_issue(__xread struct nfd_in_pkt_desc *nfd_rxd, sync_t sync,
                    SIGNAL *sig)
{
    uint32_t ctm_pnum;

    /* First allocate a CTM, this is where TM looks for the buffer
     * metadata and beginning of the packet.  To minimise the amount
     * of data that has to be copied, the smallest CTM packet size
     * is allocated (256B). */

    /* Poll for a CTM packet until one is returned.  Note, if we never
     * get one the thread hangs but nothing is in-process yet anyway,
     * which is why we do this before actually receiving the packet. */
    for (ctm_pnum = CTM_ALLOC_ERR; ctm_pnum == CTM_ALLOC_ERR;) {
        ctm_pnum = pkt_ctm_alloc(&ctm_credits, __ISLAND, NFD_CTM_TYPE, 1, 1);
    }

    /* now receive the next packet from host */
    __nfd_in_recv(0, NFD_IN_WQ, nfd_rxd, sync, sig);

    return ctm_pnum;
}

__intrinsic int
pktio_rx_host_process(__xread struct nfd_in_pkt_desc *nfd_rxd, int ctm_pnum)
{
    uint16_t i, cpy_end, cpy_start;
    __xread uint64_t buf_xr[8];
    __xwrite uint64_t buf_xw[8];
    __mem40 void *ctm_ptr;
    __mem40 void *mu_ptr;

    reg_zero((void *)pkt.__raw, sizeof(pkt));
    /* nbi_meta (pkt_info) is located in the first two words of pktio_meta */
    nfd_in_fill_meta((void *)&pkt.p_nbi, nfd_rxd);

    pkt.p_isl = __ISLAND;
    pkt.p_pnum = ctm_pnum;

    pkt.p_offset = NFD_IN_DATA_OFFSET;
    pkt.p_orig_len = pkt.p_len;
    pkt.p_ctm_size = NFD_CTM_TYPE;

    pkt.p_src = PKT_HOST_PORT_FROMQ(nfd_rxd->intf, nfd_rxd->q_num);

#ifdef MAC_EGRESS_PREPEND_ENABLE
    /* Checksum offloads */
    if (nfd_rxd->flags & PCIE_DESC_TX_CSUM) {
        if (nfd_rxd->flags & PCIE_DESC_TX_ENCAP) {
            pkt.p_tx_l3_csum = 1;
            pkt.p_tx_l4_csum = 1;
        } else {
            if (nfd_rxd->flags & PCIE_DESC_TX_IP4_CSUM)
                pkt.p_tx_l3_csum = 1;
            if (nfd_rxd->flags &
                (PCIE_DESC_TX_TCP_CSUM | PCIE_DESC_TX_UDP_CSUM))
                pkt.p_tx_l4_csum = 1;
        }
    }
#endif

    /* Tunnel packet */
    if (nfd_rxd->flags & (PCIE_DESC_TX_ENCAP))
        pkt.p_tunnel = 1;

    pkt.p_seq = nfd_in_get_seqn(nfd_rxd);

    /**
     * Map NFD seqr to GRO or NBI or no reordering
     * If GRO reordering, typically the NFD sequencers map to
     * GRO sequencers 0, 2, 4, 6.
     * The NFD sequencer can also be mapped to NBI reordering.
     * Use the PKTIO_NFD_SEQD_MAP_ISGRO macro to indicate if GRO reordering
     * will be used.
     * Use the PKTIO_NFD_SEQD_MAP_SEQR macro to map the NFD received sequencer
     * to GRO or NBI.
     * Leave reorder context at 0 for no reordering
     */
    pkt.p_ro_ctx = PKTIO_NFD_SEQD_MAP_SEQR(nfd_rxd->intf,
                                           NFD_IN_SEQR_NUM(nfd_rxd->q_num));

#ifdef PKTIO_GRO_ENABLED
    pkt.p_is_gro_seq =
            PKTIO_NFD_SEQD_MAP_ISGRO(nfd_rxd->intf,
                                     NFD_IN_SEQR_NUM(nfd_rxd->q_num));
#endif

#ifdef PKTIO_LSO_ENABLED
    /* Setup the LSO flags if requested */
    if (nfd_rxd->flags & PCIE_DESC_TX_LSO) {
        pkt.p_tx_lso = 1;
        pkt.p_tx_lso_end = nfd_rxd->lso_end;
#ifdef NFP_NET_CFG_CTRL_LSO2
        pkt.p_tx_lso_seq = nfd_rxd->lso_seq_cnt;
#else
        pkt.p_tx_lso_seq = nfd_rxd->l4_offset;
#endif
        pkt.p_tx_mss = nfd_rxd->mss;
    }
#endif

#ifdef PKTIO_VLAN_ENABLED
    if (nfd_rxd->flags & PCIE_DESC_TX_VLAN)
        pkt.p_vlan = nfd_rxd->vlan;
#endif

    if (nfd_rxd->invalid) {
        PKTIO_CNTR_INC(PKTIO_CNTR_ERR_FROM_HOST);
        return -1;
    }

    __critical_path();

    ctassert(__is_aligned(PKTIO_NFD_CPY_START, 64));
    cpy_start = PKTIO_NFD_CPY_START;
    cpy_end = pkt.p_len + NFD_IN_DATA_OFFSET;
    if (cpy_end > NFD_CTM_SIZE) {
        pkt.p_is_split = 1;
        cpy_end = NFD_CTM_SIZE;
    } else {
        pkt.p_is_split = 0;
    }

    /* TODO - investigate use of CTM DMA to do data copy or other
     * alternatives to copy rather than read/write 64B of xfer regs.
     * Also might want to overlap next read with previous write I/O. */
    for (i = cpy_start; i < cpy_end; i += sizeof(buf_xr)) {
        /* get a handle to both the mu and ctm pkt pointers */
        mu_ptr = (__mem40 void *)(((uint64_t)pkt.p_muptr << 11) | i);
        ctm_ptr = pkt_ctm_ptr40(__ISLAND, ctm_pnum, i);

        mem_read64(buf_xr, mu_ptr, sizeof(buf_xr));
        reg_cp(buf_xw, buf_xr, sizeof(buf_xw));
        mem_write64(buf_xw, ctm_ptr, sizeof(buf_xw));
    }

    /*
     * Writing two 32-bit words of metadata to the start of the CTM buffer
     * is done only when transmit on wire. If tx is to host (PCIe),
     * then we skip this step. */
    PKTIO_CNTR_INC(PKTIO_CNTR_RX_FROM_HOST);

    return 0;
}

__intrinsic int
pktio_rx_host(void)
{
    SIGNAL sig;
    __xread struct nfd_in_pkt_desc nfd_rxd;
    int ctm_pnum;

    ctm_pnum = pktio_rx_host_issue(&nfd_rxd, ctx_swap, &sig);

    return pktio_rx_host_process(&nfd_rxd, ctm_pnum);
}
#endif

__intrinsic void
pktio_rx_wq(int ring_num, mem_ring_addr_t ring_addr)
{
    __xread struct pktio_handle xph;
    __xread struct pktio_meta xpm;
    __mem40 void *p;

    mem_workq_add_thread(ring_num, ring_addr, &xph, sizeof(xph));
    p = pkt_ctm_ptr40(xph.ph_isl, xph.ph_pnum, 0);
    mem_read32(&xpm, p, sizeof(xpm));
    pkt = xpm;
    pkt.p_is_gro_seq = 0;
    pkt.p_ro_ctx = 0;
    pkt.p_dst = PKT_DROP;
}

__intrinsic int
pktio_tx_with_meta(unsigned short app_nfd_flags, unsigned short meta_len)
{
    __mem40 void *ctm_ptr;
    SIGNAL info_sig;
    SIGNAL mac_write_sig;
    SIGNAL pms_sig1;
    SIGNAL pms_sig2;
    __xwrite modscript_struct_t pms_write;
    __xread uint32_t pms_readback;
    __gpr struct pkt_ms_info msi;
    uint16_t flags;
    uint32_t offset;
    uint32_t len;
    uint32_t ret = 0;
    uint64_t port_bit;
    int dst_subsys = PKT_PORT_SUBSYS_of(pkt.p_dst);
    int dst_q = PKT_PORT_QUEUE_of(pkt.p_dst);
#ifdef PKTIO_GRO_ENABLED
    __xwrite union gro_meta gmeta;
#endif

    /*
     * There is only one instance of gro_cli_send() as it takes up some code
     * store and register usage.
     * Therefore; it is called at the end of the function in the case where
     * GRO reordering is enabled for the packet. */

    switch(PKT_PORT_TYPE_of(pkt.p_dst)) {
        case PKT_PTYPE_WIRE: {
            volatile __xwrite struct nbi_meta_pkt_info  info;

            ctm_ptr = pkt_ctm_ptr40(pkt.p_isl, pkt.p_pnum, 0);

            /* We do all the memory writes and then wait for all the
             * I/O operations to complete.
             * The packet meta data is written without a signal so that we
             * do not have to use signal masks.
             * Use a packet modifier script write which returns the signals.*/

            /* If the source is not NBI, we need to write MAC packet meta
             * (struct nbi_meta_pkt_info) to front */
            if (PKT_PORT_TYPE_of(pkt.p_src) != PKT_PTYPE_WIRE) {
                uint32_t hi, lo;
                info = pkt.p_nbi;
                hi = (uint64_t)(ctm_ptr) >> 8;
                __asm mem[write, info, hi, <<8, 0, 1]

                /* Since we are going to write a modscript after this,
                 * we know this write completes when the modscript write
                 * completes.  Therefore it needs no signalling.  */
            }

            /* Write MAC egress prepend */
            offset = pkt.p_offset;
            len = pkt.p_len;

#ifdef MAC_EGRESS_PREPEND_ENABLE
            {
                /* Fire off MAC egress write */
                __xwrite uint32_t xmac;
                __pkt_mac_egress_cmd_write(ctm_ptr,
                                           offset,
                                           pkt.p_tx_l3_csum,
                                           pkt.p_tx_l4_csum,
                                           &xmac,
                                           sig_done,
                                           &mac_write_sig);
                offset -= 4;
                len += 4;
            }
#endif

            /* Fire off write of modification script */
            msi = __modscript_write(ctm_ptr, offset, &pms_write, &pms_readback,
                                    &pms_sig1, &pms_sig2);

            /* Wait for modscript write and MAC egress write I/O operations to
             * complete.
             * If some are not defined, nfcc will optimise the signals away */
            wait_for_all(&pms_sig1, &pms_sig2, &mac_write_sig);

            /* If unsupported offset, drop the packet */
            if (msi.off_enc == 0) {
                PKTIO_CNTR_INC(PKTIO_CNTR_ERR_TO_WIRE);
                ret = -2;
                goto drop;
            }
            __critical_path();
            dst_q = CHANNEL_TO_TMQ(dst_q);

#ifdef PKTIO_GRO_ENABLED
            if (pkt.p_is_gro_seq) {
                __critical_path();
                gro_cli_build_nbi_meta(&gmeta.nbi,
                                       pkt.p_isl,
                                       pkt.p_pnum,
                                       pkt.p_ctm_size,
                                       ((msi.off_enc + 1) << 3),
                                       len + offset,
                                       dst_subsys,
                                       dst_q);
            } else
#endif
            {
                pkt_nbi_send(pkt.p_isl,
                             pkt.p_pnum,
                             &msi,
                             len,
                             dst_subsys,
                             dst_q,
                             pkt.p_ro_ctx,
                             pkt.p_seq,
                             pkt.p_ctm_size);
            }
            PKTIO_CNTR_INC(PKTIO_CNTR_TX_TO_WIRE);
        } break;

#ifdef PKTIO_NFD_ENABLED
        case PKT_PTYPE_HOST: {
            if (!nfd_out_get_credit(dst_subsys, dst_q, 1)) {
                PKTIO_CNTR_INC(PKTIO_CNTR_ERR_TO_HOST);
                ret = -1;
                goto drop;
            } else {
                __gpr struct nfd_out_input noi;

                reg_zero(&noi, sizeof(noi));
                nfd_out_fill_desc(&noi,
                                  (void *)&pkt.p_nbi,
                                  0,
                                  pkt.p_ctm_size,
                                  pkt.p_offset,
                                  meta_len);
                nfd_out_check_ctm_only(&noi);

                /* populate RX offload flags if present */
                flags = PCIE_DESC_RX_EOP;
                if (pkt.p_rx_ipv4_csum_present) {
                    flags |= PCIE_DESC_RX_IP4_CSUM;
                    if (pkt.p_rx_ipv4_csum_ok)
                        flags |= PCIE_DESC_RX_IP4_CSUM_OK;
                }
                if (pkt.p_rx_l4_csum_present) {
                    if (pkt.p_rx_l4_tcp) {
                        flags |= PCIE_DESC_RX_TCP_CSUM;
                        if (pkt.p_rx_l4_csum_ok)
                            flags |= PCIE_DESC_RX_TCP_CSUM_OK;
                    } else {
                        flags |= PCIE_DESC_RX_UDP_CSUM;
                        if (pkt.p_rx_l4_csum_ok)
                            flags |= PCIE_DESC_RX_UDP_CSUM_OK;
                    }
                }
                /* OR in the flags supplied from the app, those might include
                   inner checksum flags */
                flags |= app_nfd_flags;

#ifdef PKTIO_VLAN_ENABLED
                if (pkt.p_vlan)
                    flags |= PCIE_DESC_RX_VLAN;
                nfd_out_dummy_vlan(&noi, pkt.p_vlan, flags);
#else
                nfd_out_dummy_vlan(&noi, 0, flags);
#endif
                noi.rxd.dd = 1;

#ifdef PKTIO_GRO_ENABLED
                if (pkt.p_is_gro_seq) {
                    gro_cli_nfd_desc2meta(&gmeta.nfd, &noi, dst_subsys, dst_q);
                } else
#endif
                {
                   nfd_out_send(dst_subsys, dst_q, &noi);
                }
                PKTIO_CNTR_INC(PKTIO_CNTR_TX_TO_HOST);
            }
        } break;
#endif

        case PKT_PTYPE_WQ: {
            struct pktio_handle ph;
            __xwrite struct pktio_meta xwq;
            xwq = pkt;
            ctm_ptr = pkt_ctm_ptr40(pkt.p_isl, pkt.p_pnum, 0);
            mem_write32(&xwq, ctm_ptr, sizeof(xwq));
            ph.__raw = 0;
            ph.ph_isl = pkt.p_isl;
            ph.ph_pnum = pkt.p_pnum;

#ifdef PKTIO_GRO_ENABLED
            if (pkt.p_is_gro_seq) {
                gro_cli_build_workq_meta1(&gmeta.memq,
                                          MUID_TO_ISL(dst_subsys),
                                          dst_q,
                                          ph.__raw);
            } else
#endif
            {
                uint32_t ma = MUID_TO_MEM_RING_ADDR(dst_subsys);
                __xwrite struct pktio_handle xph = ph;
                mem_workq_add_work(dst_q, ma, &xph, sizeof(xph));
            }
        } break;

        case PKT_PTYPE_NONE:
            goto done;
            break;

        case PKT_PTYPE_DROP:
        default:
            PKTIO_CNTR_INC(PKTIO_CNTR_TX_DROP);
drop:
#ifdef PKTIO_GRO_ENABLED
            drop_packet(&gmeta.drop);
#else
            drop_packet();
#endif
    }

#ifdef PKTIO_GRO_ENABLED
    if (pkt.p_is_gro_seq) {
        __critical_path();
        gro_cli_send(&gmeta, pkt.p_ro_ctx, pkt.p_seq);
    }
#endif

done:
    return ret;
}

__intrinsic int
pktio_tx(void)
{
    return pktio_tx_with_meta(0, 0);
}

void
pktio_tx_drop(void)
{
#ifdef PKTIO_GRO_ENABLED
    __xwrite union gro_meta gmeta;

    drop_packet(&gmeta.drop);
#else
    drop_packet();
#endif
    PKTIO_CNTR_INC(PKTIO_CNTR_TX_DROP);

#ifdef PKTIO_GRO_ENABLED
    if (pkt.p_is_gro_seq) {
        gro_cli_send(&gmeta, pkt.p_ro_ctx, pkt.p_seq);
    }
#endif
    return;
}

void
pktio_rx_init()
{
#ifdef PKTIO_NFD_ENABLED
    nfd_in_recv_init();
#endif
}


void
pktio_tx_init()
{
    PKTIO_CNTRS_SET_BASE(pktio_cntrs_base);
#ifdef PKTIO_NFD_ENABLED
    nfd_out_send_init();
#endif
#ifdef PKTIO_GRO_ENABLED
    gro_cli_init();
#endif
}
