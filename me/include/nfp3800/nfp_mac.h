/*
 * Copyright (C) 2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          nfp3800/nfp_mac.h
 * @brief         Partial NFP3800 MAC CSR definitions
 *
 * This files is auto-generated. Do not edit!
 */

#ifndef _NFP3800__NFP_MAC_H_
#define _NFP3800__NFP_MAC_H_


/**
 * The NFP3800 has one MAC island. The MAC island has 2 MAC cores and each MAC
 * core may support up to 10 Ethernet ports (supporting speeds such as 10G,
 * 2.5G and 1G).  These NFP MAC ports can be combined to provide higher speed
 * external Ethernet ports (e.g. 5G, 40G or multi-lane 10G).
 *
 * How external ports are wired to NFP MAC Ethernet ports is board-specific.
 * The macros defined in this file only operates on NFP MAC ports and a user
 * has to take the board specific mapping of external ports to NFP MAC ports
 * into account.
 */

/* Maximum Ethernet ports per MAC core and MAC island */
#define NFP_MAX_ETH_PORTS_PER_MAC_CORE 10
#define NFP_MAX_MAC_CORES_PER_MAC_ISL  2
#define NFP_MAX_ETH_PORTS_PER_MAC_ISL                               \
    (NFP_MAX_ETH_PORTS_PER_MAC_CORE * NFP_MAX_MAC_CORES_PER_MAC_ISL)

/* Maximum number of MAC islands supported on the NFP */
#define NFP_MAC_MAX_ISLANDS_PER_NFP    1

/**
 * Macros to determine the MAC core number/core port for a given port number
 */
#define NFP_MAC_ETH_PORT_TO_MAC_CORE(_p)                \
    (_p < NFP_MAX_ETH_PORTS_PER_MAC_CORE ? 0 : 1)
#define NFP_MAC_ETH_PORT_TO_MAC_CORE_PORT(_p)           \
    (_p < NFP_MAX_ETH_PORTS_PER_MAC_CORE                \
     ? _p : _p - NFP_MAX_ETH_PORTS_PER_MAC_CORE)

/**
 * XPB BUS offset for a given MAC island
 */
#define NFP_MAC_XPB_OFF(_isl)  ((_isl << 24) | 0x8400000)


/*
 * MAC Checksum prepend word format
 */

/**
 * Header length definitions
 * @NFP_MAC_CSUM_PREPEND_LEN     RX/TX Checksum prepend length
 * @NFP_MAC_CSUM_PREPEND_LEN32   RX/TX Checksum prepend length
 */
#define NFP_MAC_CSUM_PREPEND_LEN    4
#define NFP_MAC_CSUM_PREPEND_LEN32  (PKT_CSUM_PREPEND_LEN / 4)

/**
 * Format of the CSUM RX prepend word as per section "9.2.6.4 Ingress Parser"
 * of the DB.
 *
 * The NFP MAC block can optionally check the L3/L4 checksum for
 * selected protocols and prepends the result to the buffer.  The
 * format is defined below.
 *
 * @NFP_MAC_RX_CSUM_L4_SUM_of       Summary of L4 checksum
 * @NFP_MAC_RX_CSUM_L3_SUM_of       Summary of L3 checksum
 * @NFP_MAC_RX_CSUM_MPLS_of         Number of MPLS labels (3 = 3 or more)
 * @NFP_MAC_RX_CSUM_VLANS_of        Number of VLANs present (3 = 3 or more)
 * @NFP_MAC_RX_CSUM_CSUM_of         16-bit L4 TCP/UDP checksum if TCP/UDP is
 *                                  parse-able. If not 16-bit checksum for
 *                                  received packet excluding CRC.
 */

#define NFP_MAC_RX_CSUM_L4_SUM_of(_x)           (((_x) >> 29) & 0x7)
#define   NFP_MAC_RX_CSUM_L4_UNSUP              (0)
#define   NFP_MAC_RX_CSUM_L4_ESP                (1)
#define   NFP_MAC_RX_CSUM_L4_TCP_OK             (2)
#define   NFP_MAC_RX_CSUM_L4_TCP_FAIL           (3)
/* Note UDP_OK is also returned when the checksum is not populated (=0) */
#define   NFP_MAC_RX_CSUM_L4_UDP_OK             (4)
#define   NFP_MAC_RX_CSUM_L4_UDP_FAIL           (5)
#define   NFP_MAC_RX_CSUM_L4_AUTH               (6)
#define   NFP_MAC_RX_CSUM_L4_FRAGMENT           (7)


#define NFP_MAC_RX_CSUM_L3_SUM_of(_x)           (((_x) >> 20) & 0x3)
#define   NFP_MAC_RX_CSUM_L3_UNKNOWN            (0)
#define   NFP_MAC_RX_CSUM_L3_IPV6               (1)
#define   NFP_MAC_RX_CSUM_L3_IPV4_FAIL          (2)
#define   NFP_MAC_RX_CSUM_L3_IPV4_OK            (3)

#define NFP_MAC_RX_CSUM_MPLS_of(_x)             (((_x) >> 18) & 0x3)
#define NFP_MAC_RX_CSUM_VLANS_of(_x)            (((_x) >> 16) & 0x3)
#define NFP_MAC_RX_CSUM_CSUM_of(_x)             ((_x) & 0xffff)


/*
 * MAC CSRs
 */
/* MacXPB: <base>.MacCsr */
#define NFP_MAC_MAC_CSR                                    0x0000
/* InterruptManagerMap: <base>.MacIntrMng */
#define NFP_MAC_MAC_INTR_MNG                               0x10000
/* PLLCntlXpb: <base>.PLLCntlXpb */
#define NFP_MAC_PLL_CNTL_XPB                               0x20000
/* MacSerDesCustCtl: <base>.MacSerDesCustCtl0... */
#define NFP_MAC_MAC_SD_CUST_CTL(x)                         (0x30000 + ((x) * 0x40))
/* Mac10Ethernet: <base>.MacEthernet0... */
#define NFP_MAC_MAC_ETH(x)                                 (0x40000 + ((x) * 0x20000))
/* MacMemCtrl: <base>.MacCoresCsrMemCtrl0... */
#define NFP_MAC_MAC_CORES_CSR_MEM_CTRL(x)                  (0x80000 + ((x) * 0x10000))
/* ECCControlMany: <base>.MacCdsEccMon0... */
#define NFP_MAC_MAC_CDS_ECC_MON(x)                         (0xa0000 + ((x) * 0x10000))
/* IslandOverlayExtMap: <base>.MacOvlExt */
#define NFP_MAC_MAC_OVL_EXT                                0x3f0000


/*
 * Macros for NFP_MAC_ETH(x)
 */
/* pyexec<dump_map(MacEthernet(altname="MAC_ETH"), docs=True)> */

/*
 * Macros for NFP_MAC_ETH_CHAN_PCS(x)
 */

/*
 * Register: EthChPcsCtl1
 *   [15]      EthPcsReset
 *   [14]      EthPcsLoopback
 *   [13]      EthSpeedSelection13
 *   [11]      EthLowPower
 *   [6]       EthSpeedSelection6
 *   [5:2]     EthSpeedSel
 *
 * Name(s):
 * <base>.EthChPcsCtl1
 */
#define NFP_MAC_ETH_CH_PCS_CTL_1                           0x0000
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_RESET             (1 << 15)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_RESET_bf        0, 15, 15
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_RESET_msk       (0x1)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_RESET_bit       (15)
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_LOOPBACK          (1 << 14)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_LOOPBACK_bf     0, 14, 14
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_LOOPBACK_msk    (0x1)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_PCS_LOOPBACK_bit    (14)
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_13    (1 << 13)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_13_bf 0, 13, 13
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_13_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_13_bit (13)
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_LOW_POWER             (1 << 11)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_LOW_POWER_bf        0, 11, 11
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_LOW_POWER_msk       (0x1)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_LOW_POWER_bit       (11)
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_6     (1 << 6)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_6_bf 0, 6, 6
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_6_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SELECTION_6_bit (6)
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SEL(x)          (((x) & 0xf) << 2)
#define   NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SEL_of(x)       (((x) >> 2) & 0xf)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SEL_bf        0, 5, 2
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SEL_msk       (0xf)
#define     NFP_MAC_ETH_CH_PCS_CTL_1_ETH_SPEED_SEL_shf       (2)


/*
 * Register: EthChPcsStatus1
 *   [11]      EthTxLpi
 *   [10]      EthRxLpi
 *   [9]       EthTxLpiActive
 *   [8]       EthRxLpiActive
 *   [7]       EthFault
 *   [2]       EthPcsReceiveLink
 *   [1]       EthLowPowerAble
 *
 * Name(s):
 * <base>.EthChPcsStatus1
 */
#define NFP_MAC_ETH_CH_PCS_STATUS_1                        0x0004
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI             (1 << 11)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_bf        0, 11, 11
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_msk       (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_bit       (11)
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI             (1 << 10)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_bf        0, 10, 10
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_msk       (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_bit       (10)
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_ACTIVE      (1 << 9)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_ACTIVE_bf 0, 9, 9
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_ACTIVE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_TX_LPI_ACTIVE_bit (9)
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_ACTIVE      (1 << 8)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_ACTIVE_bf 0, 8, 8
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_ACTIVE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_RX_LPI_ACTIVE_bit (8)
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_FAULT              (1 << 7)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_FAULT_bf         0, 7, 7
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_FAULT_msk        (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_FAULT_bit        (7)
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_PCS_RECEIVE_LINK   (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_PCS_RECEIVE_LINK_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_PCS_RECEIVE_LINK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_PCS_RECEIVE_LINK_bit (2)
#define   NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_LOW_POWER_ABLE     (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_LOW_POWER_ABLE_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_LOW_POWER_ABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_1_ETH_LOW_POWER_ABLE_bit (1)


/*
 * Register: EthChPcsDevId0
 *   [15:0]    EthDevId
 *
 * Name(s):
 * <base>.EthChPcsDevId0
 */
#define NFP_MAC_ETH_CH_PCS_DEV_ID_0                        0x0008
#define   NFP_MAC_ETH_CH_PCS_DEV_ID_0_ETH_DEV_ID(x)          (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_DEV_ID_0_ETH_DEV_ID_of(x)       (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_DEV_ID_0_ETH_DEV_ID_bf        0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_DEV_ID_0_ETH_DEV_ID_msk       (0xffff)
#define     NFP_MAC_ETH_CH_PCS_DEV_ID_0_ETH_DEV_ID_shf       (0)


/*
 * Register: EthChPcsDevId1
 *   [15:0]    EthDevId
 *
 * Name(s):
 * <base>.EthChPcsDevId1
 */
#define NFP_MAC_ETH_CH_PCS_DEV_ID_1                        0x000c
#define   NFP_MAC_ETH_CH_PCS_DEV_ID_1_ETH_DEV_ID(x)          (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_DEV_ID_1_ETH_DEV_ID_of(x)       (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_DEV_ID_1_ETH_DEV_ID_bf        0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_DEV_ID_1_ETH_DEV_ID_msk       (0xffff)
#define     NFP_MAC_ETH_CH_PCS_DEV_ID_1_ETH_DEV_ID_shf       (0)


/*
 * Register: EthChPcsSpeedAbility
 *   [5]       EthSpeed50GCapable
 *   [4]       EthSpeed25GCapable
 *   [3]       EthSpeed100GCapable
 *   [2]       EthSpeed40GCapable
 *   [1]       EthSpeed10PassTs2BaseTlCapable
 *   [0]       EthSpeed10GCapable
 *
 * Name(s):
 * <base>.EthChPcsSpeedAbility
 */
#define NFP_MAC_ETH_CH_PCS_SPEED_ABILITY                   0x0010
#define   NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_50GCAPABLE (1 << 5)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_50GCAPABLE_bf 0, 5, 5
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_50GCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_50GCAPABLE_bit (5)
#define   NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_25GCAPABLE (1 << 4)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_25GCAPABLE_bf 0, 4, 4
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_25GCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_25GCAPABLE_bit (4)
#define   NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_100GCAPABLE (1 << 3)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_100GCAPABLE_bf 0, 3, 3
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_100GCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_100GCAPABLE_bit (3)
#define   NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_40GCAPABLE (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_40GCAPABLE_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_40GCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_40GCAPABLE_bit (2)
#define   NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10PASS_TS_2BASE_TL_CAPABLE (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10PASS_TS_2BASE_TL_CAPABLE_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10PASS_TS_2BASE_TL_CAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10PASS_TS_2BASE_TL_CAPABLE_bit (1)
#define   NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10GCAPABLE (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10GCAPABLE_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10GCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_SPEED_ABILITY_ETH_SPEED_10GCAPABLE_bit (0)


/*
 * Register: EthChPcsDeviInPkg1
 *   [6]       EthTcPresent
 *   [5]       EthDteXsPresent
 *   [4]       EthPhyXsPresent
 *   [3]       EthPCSPresent
 *   [2]       EthWisPresent
 *   [1]       EthPmdPmaPresent
 *   [0]       EthClause22Present
 *
 * Name(s):
 * <base>.EthChPcsDeviInPkg1
 */
#define NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1                   0x0014
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_TC_PRESENT    (1 << 6)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_TC_PRESENT_bf 0, 6, 6
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_TC_PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_TC_PRESENT_bit (6)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_DTE_XS_PRESENT (1 << 5)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_DTE_XS_PRESENT_bf 0, 5, 5
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_DTE_XS_PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_DTE_XS_PRESENT_bit (5)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PHY_XS_PRESENT (1 << 4)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PHY_XS_PRESENT_bf 0, 4, 4
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PHY_XS_PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PHY_XS_PRESENT_bit (4)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PCSPRESENT    (1 << 3)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PCSPRESENT_bf 0, 3, 3
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PCSPRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PCSPRESENT_bit (3)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_WIS_PRESENT   (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_WIS_PRESENT_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_WIS_PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_WIS_PRESENT_bit (2)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PMD_PMA_PRESENT (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PMD_PMA_PRESENT_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PMD_PMA_PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_PMD_PMA_PRESENT_bit (1)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_CLAUSE_22PRESENT (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_CLAUSE_22PRESENT_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_CLAUSE_22PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_1_ETH_CLAUSE_22PRESENT_bit (0)


/*
 * Register: EthChPcsDeviInPkg2
 *   [15]      EthVndrDev2Present
 *   [14]      EthVndrDev1Present
 *   [13]      EthClause22Present
 *
 * Name(s):
 * <base>.EthChPcsDeviInPkg2
 */
#define NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2                   0x0018
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_2PRESENT (1 << 15)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_2PRESENT_bf 0, 15, 15
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_2PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_2PRESENT_bit (15)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_1PRESENT (1 << 14)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_1PRESENT_bf 0, 14, 14
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_1PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_VNDR_DEV_1PRESENT_bit (14)
#define   NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_CLAUSE_22PRESENT (1 << 13)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_CLAUSE_22PRESENT_bf 0, 13, 13
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_CLAUSE_22PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_DEVI_IN_PKG_2_ETH_CLAUSE_22PRESENT_bit (13)


/*
 * Register: EthChPcsCtl2
 *   [2:0]     EthPcsType
 *
 * Name(s):
 * <base>.EthChPcsCtl2
 */
#define NFP_MAC_ETH_CH_PCS_CTL_2                           0x001c
#define   NFP_MAC_ETH_CH_PCS_CTL_2_ETH_PCS_TYPE(x)           (((x) & 7) << 0)
#define   NFP_MAC_ETH_CH_PCS_CTL_2_ETH_PCS_TYPE_of(x)        (((x) >> 0) & 7)
#define     NFP_MAC_ETH_CH_PCS_CTL_2_ETH_PCS_TYPE_bf         0, 2, 0
#define     NFP_MAC_ETH_CH_PCS_CTL_2_ETH_PCS_TYPE_msk        (0x7)
#define     NFP_MAC_ETH_CH_PCS_CTL_2_ETH_PCS_TYPE_shf        (0)


/*
 * Register: EthChPcsStatus2
 *   [15:14]   EthDevPresent
 *   [11]      EthTransmitFault
 *   [10]      EthReceiveFault
 *   [8]       Eth50GBaseRCapable
 *   [7]       Eth25GBaseRCapable
 *   [5]       Eth100GBaseRCapable
 *   [4]       Eth40GBaseRCapable
 *   [3]       Eth10GBaseTCapable
 *   [2]       Eth10GBaseWCapable
 *   [1]       Eth10GBaseXCapable
 *   [0]       Eth10GBaseRCapable
 *
 * Name(s):
 * <base>.EthChPcsStatus2
 */
#define NFP_MAC_ETH_CH_PCS_STATUS_2                        0x0020
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_DEV_PRESENT(x)     (((x) & 3) << 14)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_DEV_PRESENT_of(x)  (((x) >> 14) & 3)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_DEV_PRESENT_bf   0, 15, 14
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_DEV_PRESENT_msk  (0x3)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_DEV_PRESENT_shf  (14)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_TRANSMIT_FAULT     (1 << 11)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_TRANSMIT_FAULT_bf 0, 11, 11
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_TRANSMIT_FAULT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_TRANSMIT_FAULT_bit (11)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_RECEIVE_FAULT      (1 << 10)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_RECEIVE_FAULT_bf 0, 10, 10
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_RECEIVE_FAULT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_RECEIVE_FAULT_bit (10)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_50GBASE_RCAPABLE   (1 << 8)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_50GBASE_RCAPABLE_bf 0, 8, 8
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_50GBASE_RCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_50GBASE_RCAPABLE_bit (8)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_25GBASE_RCAPABLE   (1 << 7)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_25GBASE_RCAPABLE_bf 0, 7, 7
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_25GBASE_RCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_25GBASE_RCAPABLE_bit (7)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_100GBASE_RCAPABLE  (1 << 5)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_100GBASE_RCAPABLE_bf 0, 5, 5
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_100GBASE_RCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_100GBASE_RCAPABLE_bit (5)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_40GBASE_RCAPABLE   (1 << 4)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_40GBASE_RCAPABLE_bf 0, 4, 4
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_40GBASE_RCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_40GBASE_RCAPABLE_bit (4)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_TCAPABLE   (1 << 3)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_TCAPABLE_bf 0, 3, 3
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_TCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_TCAPABLE_bit (3)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_WCAPABLE   (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_WCAPABLE_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_WCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_WCAPABLE_bit (2)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_XCAPABLE   (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_XCAPABLE_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_XCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_XCAPABLE_bit (1)
#define   NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_RCAPABLE   (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_RCAPABLE_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_RCAPABLE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_STATUS_2_ETH_10GBASE_RCAPABLE_bit (0)


/*
 * Register: EthChPcsPkgId0
 *   [15:0]    EthIdentifier
 *
 * Name(s):
 * <base>.EthChPcsPkgId0
 */
#define NFP_MAC_ETH_CH_PCS_PKG_ID_0                        0x0038
#define   NFP_MAC_ETH_CH_PCS_PKG_ID_0_ETH_IDENTIFIER(x)      (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_PKG_ID_0_ETH_IDENTIFIER_of(x)   (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_PKG_ID_0_ETH_IDENTIFIER_bf    0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_PKG_ID_0_ETH_IDENTIFIER_msk   (0xffff)
#define     NFP_MAC_ETH_CH_PCS_PKG_ID_0_ETH_IDENTIFIER_shf   (0)


/*
 * Register: EthChPcsPkgId1
 *   [15:0]    EthIdentifier
 *
 * Name(s):
 * <base>.EthChPcsPkgId1
 */
#define NFP_MAC_ETH_CH_PCS_PKG_ID_1                        0x003c
#define   NFP_MAC_ETH_CH_PCS_PKG_ID_1_ETH_IDENTIFIER(x)      (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_PKG_ID_1_ETH_IDENTIFIER_of(x)   (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_PKG_ID_1_ETH_IDENTIFIER_bf    0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_PKG_ID_1_ETH_IDENTIFIER_msk   (0xffff)
#define     NFP_MAC_ETH_CH_PCS_PKG_ID_1_ETH_IDENTIFIER_shf   (0)


/*
 * Register: EthChPcsEeeCtrlCapability
 *   [11]      EthEee25gbaseRsleep
 *   [10]      EthEee25gbaseRawake
 *   [9]       EthEee40gbaseRsleep
 *   [8]       EthEee40gbaseRawake
 *   [6]       EthEee10gbaseKr
 *   [0]       EthLpiFw
 *
 * Name(s):
 * <base>.EthChPcsEeeCtrlCapability
 */
#define NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY             0x0050
#define   NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RSLEEP (1 << 11)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RSLEEP_bf 0, 11, 11
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RSLEEP_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RSLEEP_bit (11)
#define   NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RAWAKE (1 << 10)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RAWAKE_bf 0, 10, 10
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RAWAKE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_25GBASE_RAWAKE_bit (10)
#define   NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RSLEEP (1 << 9)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RSLEEP_bf 0, 9, 9
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RSLEEP_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RSLEEP_bit (9)
#define   NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RAWAKE (1 << 8)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RAWAKE_bf 0, 8, 8
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RAWAKE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_40GBASE_RAWAKE_bit (8)
#define   NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_10GBASE_KR (1 << 6)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_10GBASE_KR_bf 0, 6, 6
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_10GBASE_KR_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_EEE_10GBASE_KR_bit (6)
#define   NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_LPI_FW  (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_LPI_FW_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_LPI_FW_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_EEE_CTRL_CAPABILITY_ETH_LPI_FW_bit (0)


/*
 * Register: EthChPcsWakeErrCounter
 *   [15:0]    EthCounter
 *
 * Name(s):
 * <base>.EthChPcsWakeErrCounter
 */
#define NFP_MAC_ETH_CH_PCS_WAKE_ERR_COUNTER                0x0058
#define   NFP_MAC_ETH_CH_PCS_WAKE_ERR_COUNTER_ETH_COUNTER(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_WAKE_ERR_COUNTER_ETH_COUNTER_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_WAKE_ERR_COUNTER_ETH_COUNTER_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_WAKE_ERR_COUNTER_ETH_COUNTER_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_WAKE_ERR_COUNTER_ETH_COUNTER_shf (0)


/*
 * Register: EthChPcsBaseRStatus1
 *   [12]      EthRcvLinkStatus
 *   [1]       EthHighBer
 *   [0]       EthBlockLocked
 *
 * Name(s):
 * <base>.EthChPcsBaseRStatus1
 */
#define NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1                  0x0080
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_RCV_LINK_STATUS (1 << 12)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_RCV_LINK_STATUS_bf 0, 12, 12
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_RCV_LINK_STATUS_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_RCV_LINK_STATUS_bit (12)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_HIGH_BER     (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_HIGH_BER_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_HIGH_BER_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_HIGH_BER_bit (1)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_BLOCK_LOCKED (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_BLOCK_LOCKED_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_BLOCK_LOCKED_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_1_ETH_BLOCK_LOCKED_bit (0)


/*
 * Register: EthChPcsBaseRStatus2
 *   [15]      EthBlockLocked
 *   [14]      EthHighBer
 *   [13:8]    EthBerCounter
 *   [7:0]     EthErroredCnt
 *
 * Name(s):
 * <base>.EthChPcsBaseRStatus2
 */
#define NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2                  0x0084
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BLOCK_LOCKED (1 << 15)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BLOCK_LOCKED_bf 0, 15, 15
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BLOCK_LOCKED_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BLOCK_LOCKED_bit (15)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_HIGH_BER     (1 << 14)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_HIGH_BER_bf 0, 14, 14
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_HIGH_BER_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_HIGH_BER_bit (14)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BER_COUNTER(x) (((x) & 0x3f) << 8)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BER_COUNTER_of(x) (((x) >> 8) & 0x3f)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BER_COUNTER_bf 0, 13, 8
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BER_COUNTER_msk (0x3f)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_BER_COUNTER_shf (8)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_ERRORED_CNT(x) (((x) & 0xff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_ERRORED_CNT_of(x) (((x) >> 0) & 0xff)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_ERRORED_CNT_bf 0, 7, 0
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_ERRORED_CNT_msk (0xff)
#define     NFP_MAC_ETH_CH_PCS_BASE_RSTATUS_2_ETH_ERRORED_CNT_shf (0)


/*
 * Register: EthChPcsTestPatSeedA0
 *   [15:0]    EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedA0
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A0                0x0088
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A0_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A0_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A0_ETH_TEST_PAT_SEED_DATA_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A0_ETH_TEST_PAT_SEED_DATA_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A0_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedA1
 *   [15:0]    EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedA1
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A1                0x008c
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A1_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A1_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A1_ETH_TEST_PAT_SEED_DATA_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A1_ETH_TEST_PAT_SEED_DATA_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A1_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedA2
 *   [15:0]    EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedA2
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A2                0x0090
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A2_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A2_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A2_ETH_TEST_PAT_SEED_DATA_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A2_ETH_TEST_PAT_SEED_DATA_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A2_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedA3
 *   [9:0]     EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedA3
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A3                0x0094
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A3_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0x3ff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A3_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0x3ff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A3_ETH_TEST_PAT_SEED_DATA_bf 0, 9, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A3_ETH_TEST_PAT_SEED_DATA_msk (0x3ff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_A3_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedB0
 *   [15:0]    EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedB0
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B0                0x0098
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B0_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B0_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B0_ETH_TEST_PAT_SEED_DATA_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B0_ETH_TEST_PAT_SEED_DATA_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B0_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedB1
 *   [15:0]    EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedB1
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B1                0x009c
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B1_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B1_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B1_ETH_TEST_PAT_SEED_DATA_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B1_ETH_TEST_PAT_SEED_DATA_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B1_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedB2
 *   [15:0]    EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedB2
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B2                0x00a0
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B2_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B2_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B2_ETH_TEST_PAT_SEED_DATA_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B2_ETH_TEST_PAT_SEED_DATA_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B2_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsTestPatSeedB3
 *   [9:0]     EthTestPatSeedData
 *
 * Name(s):
 * <base>.EthChPcsTestPatSeedB3
 */
#define NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B3                0x00a4
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B3_ETH_TEST_PAT_SEED_DATA(x) (((x) & 0x3ff) << 0)
#define   NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B3_ETH_TEST_PAT_SEED_DATA_of(x) (((x) >> 0) & 0x3ff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B3_ETH_TEST_PAT_SEED_DATA_bf 0, 9, 0
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B3_ETH_TEST_PAT_SEED_DATA_msk (0x3ff)
#define     NFP_MAC_ETH_CH_PCS_TEST_PAT_SEED_B3_ETH_TEST_PAT_SEED_DATA_shf (0)


/*
 * Register: EthChPcsBaseRTestCtl
 *   [7]       EthSelectRandom
 *   [3]       EthTransmitTestPatEn
 *   [2]       EthReceiveTestPatEn
 *   [1]       EthSelectSquare
 *   [0]       EthDataPatSel
 *
 * Name(s):
 * <base>.EthChPcsBaseRTestCtl
 */
#define NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL                  0x00a8
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_RANDOM (1 << 7)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_RANDOM_bf 0, 7, 7
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_RANDOM_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_RANDOM_bit (7)
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_TRANSMIT_TEST_PAT_EN (1 << 3)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_TRANSMIT_TEST_PAT_EN_bf 0, 3, 3
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_TRANSMIT_TEST_PAT_EN_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_TRANSMIT_TEST_PAT_EN_bit (3)
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_RECEIVE_TEST_PAT_EN (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_RECEIVE_TEST_PAT_EN_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_RECEIVE_TEST_PAT_EN_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_RECEIVE_TEST_PAT_EN_bit (2)
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_SQUARE (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_SQUARE_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_SQUARE_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_SELECT_SQUARE_bit (1)
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_DATA_PAT_SEL (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_DATA_PAT_SEL_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_DATA_PAT_SEL_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_CTL_ETH_DATA_PAT_SEL_bit (0)


/*
 * Register: EthChPcsBaseRTestErrCnt
 *   [15:0]    EthCounter
 *
 * Name(s):
 * <base>.EthChPcsBaseRTestErrCnt
 */
#define NFP_MAC_ETH_CH_PCS_BASE_RTEST_ERR_CNT              0x00ac
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_ERR_CNT_ETH_COUNTER(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BASE_RTEST_ERR_CNT_ETH_COUNTER_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_ERR_CNT_ETH_COUNTER_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_ERR_CNT_ETH_COUNTER_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_BASE_RTEST_ERR_CNT_ETH_COUNTER_shf (0)


/*
 * Register: EthChPcsBerHiOrderCnt
 *   [15:0]    EthBerCounter
 *
 * Name(s):
 * <base>.EthChPcsBerHiOrderCnt
 */
#define NFP_MAC_ETH_CH_PCS_BER_HI_ORDER_CNT                0x00b0
#define   NFP_MAC_ETH_CH_PCS_BER_HI_ORDER_CNT_ETH_BER_COUNTER(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BER_HI_ORDER_CNT_ETH_BER_COUNTER_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_BER_HI_ORDER_CNT_ETH_BER_COUNTER_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_BER_HI_ORDER_CNT_ETH_BER_COUNTER_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_BER_HI_ORDER_CNT_ETH_BER_COUNTER_shf (0)


/*
 * Register: EthChPcsErrBlkHiOrderCnt
 *   [15]      EthHiOrderCntPresent
 *   [13:0]    EthErrBlkHiOrderCnt
 *
 * Name(s):
 * <base>.EthChPcsErrBlkHiOrderCnt
 */
#define NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT            0x00b4
#define   NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_HI_ORDER_CNT_PRESENT (1 << 15)
#define     NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_HI_ORDER_CNT_PRESENT_bf 0, 15, 15
#define     NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_HI_ORDER_CNT_PRESENT_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_HI_ORDER_CNT_PRESENT_bit (15)
#define   NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_ERR_BLK_HI_ORDER_CNT(x) (((x) & 0x3fff) << 0)
#define   NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_ERR_BLK_HI_ORDER_CNT_of(x) (((x) >> 0) & 0x3fff)
#define     NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_ERR_BLK_HI_ORDER_CNT_bf 0, 13, 0
#define     NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_ERR_BLK_HI_ORDER_CNT_msk (0x3fff)
#define     NFP_MAC_ETH_CH_PCS_ERR_BLK_HI_ORDER_CNT_ETH_ERR_BLK_HI_ORDER_CNT_shf (0)


/*
 * Register: EthChPcsMultilaneAlignStat1
 *   [12]      EthLaneAlignmentStatus
 *   [3]       EthLane3BlockLock
 *   [2]       EthLane2BlockLock
 *   [1]       EthLane1BlockLock
 *   [0]       EthLane0BlockLock
 *
 * Name(s):
 * <base>.EthChPcsMultilaneAlignStat1
 */
#define NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1          0x00c8
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_ALIGNMENT_STATUS (1 << 12)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_ALIGNMENT_STATUS_bf 0, 12, 12
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_ALIGNMENT_STATUS_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_ALIGNMENT_STATUS_bit (12)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_3BLOCK_LOCK (1 << 3)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_3BLOCK_LOCK_bf 0, 3, 3
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_3BLOCK_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_3BLOCK_LOCK_bit (3)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_2BLOCK_LOCK (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_2BLOCK_LOCK_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_2BLOCK_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_2BLOCK_LOCK_bit (2)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_1BLOCK_LOCK (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_1BLOCK_LOCK_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_1BLOCK_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_1BLOCK_LOCK_bit (1)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_0BLOCK_LOCK (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_0BLOCK_LOCK_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_0BLOCK_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_1_ETH_LANE_0BLOCK_LOCK_bit (0)


/*
 * Register: EthChPcsMultilaneAlignStat3
 *   [3]       EthLane3MarkerLock
 *   [2]       EthLane2MarkerLock
 *   [1]       EthLane1MarkerLock
 *   [0]       EthLane0MarkerLock
 *
 * Name(s):
 * <base>.EthChPcsMultilaneAlignStat3
 */
#define NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3          0x00d0
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_3MARKER_LOCK (1 << 3)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_3MARKER_LOCK_bf 0, 3, 3
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_3MARKER_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_3MARKER_LOCK_bit (3)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_2MARKER_LOCK (1 << 2)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_2MARKER_LOCK_bf 0, 2, 2
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_2MARKER_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_2MARKER_LOCK_bit (2)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_1MARKER_LOCK (1 << 1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_1MARKER_LOCK_bf 0, 1, 1
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_1MARKER_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_1MARKER_LOCK_bit (1)
#define   NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_0MARKER_LOCK (1 << 0)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_0MARKER_LOCK_bf 0, 0, 0
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_0MARKER_LOCK_msk (0x1)
#define     NFP_MAC_ETH_CH_PCS_MULTILANE_ALIGN_STAT_3_ETH_LANE_0MARKER_LOCK_bit (0)


/*
 * Register: EthChPcsBipErrCntLane0
 *   [15:0]    EthBipErrCnt
 *
 * Name(s):
 * <base>.EthChPcsBipErrCntLane0
 */
#define NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_0              0x0320
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_0_ETH_BIP_ERR_CNT(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_0_ETH_BIP_ERR_CNT_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_0_ETH_BIP_ERR_CNT_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_0_ETH_BIP_ERR_CNT_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_0_ETH_BIP_ERR_CNT_shf (0)


/*
 * Register: EthChPcsBipErrCntLane1
 *   [15:0]    EthBipErrCnt
 *
 * Name(s):
 * <base>.EthChPcsBipErrCntLane1
 */
#define NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_1              0x0324
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_1_ETH_BIP_ERR_CNT(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_1_ETH_BIP_ERR_CNT_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_1_ETH_BIP_ERR_CNT_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_1_ETH_BIP_ERR_CNT_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_1_ETH_BIP_ERR_CNT_shf (0)


/*
 * Register: EthChPcsBipErrCntLane2
 *   [15:0]    EthBipErrCnt
 *
 * Name(s):
 * <base>.EthChPcsBipErrCntLane2
 */
#define NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_2              0x0328
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_2_ETH_BIP_ERR_CNT(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_2_ETH_BIP_ERR_CNT_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_2_ETH_BIP_ERR_CNT_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_2_ETH_BIP_ERR_CNT_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_2_ETH_BIP_ERR_CNT_shf (0)


/*
 * Register: EthChPcsBipErrCntLane3
 *   [15:0]    EthBipErrCnt
 *
 * Name(s):
 * <base>.EthChPcsBipErrCntLane3
 */
#define NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_3              0x032c
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_3_ETH_BIP_ERR_CNT(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_3_ETH_BIP_ERR_CNT_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_3_ETH_BIP_ERR_CNT_bf 0, 15, 0
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_3_ETH_BIP_ERR_CNT_msk (0xffff)
#define     NFP_MAC_ETH_CH_PCS_BIP_ERR_CNT_LANE_3_ETH_BIP_ERR_CNT_shf (0)


/*
 * Register: EthChPcsLane0Mapping
 *   [1:0]     EthLaneMap
 *
 * Name(s):
 * <base>.EthChPcsLane0Mapping
 */
#define NFP_MAC_ETH_CH_PCS_LANE_0MAPPING                   0x0640
#define   NFP_MAC_ETH_CH_PCS_LANE_0MAPPING_ETH_LANE_MAP(x)   (((x) & 3) << 0)
#define   NFP_MAC_ETH_CH_PCS_LANE_0MAPPING_ETH_LANE_MAP_of(x) (((x) >> 0) & 3)
#define     NFP_MAC_ETH_CH_PCS_LANE_0MAPPING_ETH_LANE_MAP_bf 0, 1, 0
#define     NFP_MAC_ETH_CH_PCS_LANE_0MAPPING_ETH_LANE_MAP_msk (0x3)
#define     NFP_MAC_ETH_CH_PCS_LANE_0MAPPING_ETH_LANE_MAP_shf (0)


/*
 * Register: EthChPcsLane1Mapping
 *   [1:0]     EthLaneMap
 *
 * Name(s):
 * <base>.EthChPcsLane1Mapping
 */
#define NFP_MAC_ETH_CH_PCS_LANE_1MAPPING                   0x0644
#define   NFP_MAC_ETH_CH_PCS_LANE_1MAPPING_ETH_LANE_MAP(x)   (((x) & 3) << 0)
#define   NFP_MAC_ETH_CH_PCS_LANE_1MAPPING_ETH_LANE_MAP_of(x) (((x) >> 0) & 3)
#define     NFP_MAC_ETH_CH_PCS_LANE_1MAPPING_ETH_LANE_MAP_bf 0, 1, 0
#define     NFP_MAC_ETH_CH_PCS_LANE_1MAPPING_ETH_LANE_MAP_msk (0x3)
#define     NFP_MAC_ETH_CH_PCS_LANE_1MAPPING_ETH_LANE_MAP_shf (0)


/*
 * Register: EthChPcsLane2Mapping
 *   [1:0]     EthLaneMap
 *
 * Name(s):
 * <base>.EthChPcsLane2Mapping
 */
#define NFP_MAC_ETH_CH_PCS_LANE_2MAPPING                   0x0648
#define   NFP_MAC_ETH_CH_PCS_LANE_2MAPPING_ETH_LANE_MAP(x)   (((x) & 3) << 0)
#define   NFP_MAC_ETH_CH_PCS_LANE_2MAPPING_ETH_LANE_MAP_of(x) (((x) >> 0) & 3)
#define     NFP_MAC_ETH_CH_PCS_LANE_2MAPPING_ETH_LANE_MAP_bf 0, 1, 0
#define     NFP_MAC_ETH_CH_PCS_LANE_2MAPPING_ETH_LANE_MAP_msk (0x3)
#define     NFP_MAC_ETH_CH_PCS_LANE_2MAPPING_ETH_LANE_MAP_shf (0)


/*
 * Register: EthChPcsLane3Mapping
 *   [1:0]     EthLaneMap
 *
 * Name(s):
 * <base>.EthChPcsLane3Mapping
 */
#define NFP_MAC_ETH_CH_PCS_LANE_3MAPPING                   0x064c
#define   NFP_MAC_ETH_CH_PCS_LANE_3MAPPING_ETH_LANE_MAP(x)   (((x) & 3) << 0)
#define   NFP_MAC_ETH_CH_PCS_LANE_3MAPPING_ETH_LANE_MAP_of(x) (((x) >> 0) & 3)
#define     NFP_MAC_ETH_CH_PCS_LANE_3MAPPING_ETH_LANE_MAP_bf 0, 1, 0
#define     NFP_MAC_ETH_CH_PCS_LANE_3MAPPING_ETH_LANE_MAP_msk (0x3)
#define     NFP_MAC_ETH_CH_PCS_LANE_3MAPPING_ETH_LANE_MAP_shf (0)


/*
 * Macros for NFP_MAC_XPB(x)
 */

/*
 * Register: MacBlkReset
 *   [31:24]   Rfu2
 *   [23]      MacHy1StatRst
 *   [22]      MacHy0StatRst
 *   [21]      MacTxRstMpb
 *   [20]      MacRxRstMpb
 *   [19]      MacTxRstCore
 *   [18]      MacRxRstCore
 *   [17]      MacFcX2RstLk1
 *   [16]      MacFcX2RstLk0
 *   [15]      MacRxRstLk1
 *   [14]      MacRxRstLk0
 *   [13]      MacTxRstLk1
 *   [12]      MacTxRstLk0
 *   [11]      MacRstLk1
 *   [10]      MacRstLk0
 *   [9]       MacX2ClkEnLk1
 *   [8]       MacX2ClkEnLk0
 *   [7]       MacCoreClkEnLk1
 *   [6]       MacCoreClkEnLk0
 *   [5]       MacCoreClkEnHy1
 *   [4]       MacCoreClkEnHy0
 *   [3]       Rfu
 *   [2]       MacSerDesRst
 *   [1]       MacSReset
 *   [0]       MacHReset
 *
 * Name(s):
 * <base>.MacBlkReset
 */
#define NFP_MAC_CSR_MAC_BLOCK_RST                          0x0000
#define   NFP_MAC_CSR_MAC_BLOCK_RST_RFU2(x)                  (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_RFU2_of(x)               (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_RFU2_bf                0, 31, 24
#define     NFP_MAC_CSR_MAC_BLOCK_RST_RFU2_msk               (0xff)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_RFU2_shf               (24)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY1_STAT_RST         (1 << 23)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY1_STAT_RST_bf    0, 23, 23
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY1_STAT_RST_msk   (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY1_STAT_RST_bit   (23)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY0_STAT_RST         (1 << 22)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY0_STAT_RST_bf    0, 22, 22
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY0_STAT_RST_msk   (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_HY0_STAT_RST_bit   (22)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_MPB           (1 << 21)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_MPB_bf      0, 21, 21
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_MPB_msk     (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_MPB_bit     (21)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_MPB           (1 << 20)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_MPB_bf      0, 20, 20
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_MPB_msk     (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_MPB_bit     (20)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_CORE          (1 << 19)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_CORE_bf     0, 19, 19
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_CORE_msk    (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TX_RST_CORE_bit    (19)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_CORE          (1 << 18)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_CORE_bf     0, 18, 18
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_CORE_msk    (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RX_RST_CORE_bit    (18)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK1          (1 << 17)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK1_bf     0, 17, 17
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK1_msk    (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK1_bit    (17)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK0          (1 << 16)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK0_bf     0, 16, 16
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK0_msk    (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_FCX2RST_LK0_bit    (16)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK1            (1 << 15)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK1_bf       0, 15, 15
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK1_msk      (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK1_bit      (15)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK0            (1 << 14)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK0_bf       0, 14, 14
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK0_msk      (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RXRST_LK0_bit      (14)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK1            (1 << 13)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK1_bf       0, 13, 13
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK1_msk      (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK1_bit      (13)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK0            (1 << 12)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK0_bf       0, 12, 12
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK0_msk      (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_TXRST_LK0_bit      (12)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK1              (1 << 11)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK1_bf         0, 11, 11
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK1_msk        (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK1_bit        (11)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK0              (1 << 10)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK0_bf         0, 10, 10
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK0_msk        (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_RST_LK0_bit        (10)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK1          (1 << 9)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK1_bf     0, 9, 9
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK1_msk    (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK1_bit    (9)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK0          (1 << 8)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK0_bf     0, 8, 8
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK0_msk    (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_X2CLKEN_LK0_bit    (8)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK1        (1 << 7)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK1_bf   0, 7, 7
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK1_msk  (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK1_bit  (7)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK0        (1 << 6)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK0_bf   0, 6, 6
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK0_msk  (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_LK0_bit  (6)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY1        (1 << 5)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY1_bf   0, 5, 5
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY1_msk  (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY1_bit  (5)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY0        (1 << 4)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY0_bf   0, 4, 4
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY0_msk  (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_CORECLKEN_HY0_bit  (4)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_RFU                      (1 << 3)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_RFU_bf                 0, 3, 3
#define     NFP_MAC_CSR_MAC_BLOCK_RST_RFU_msk                (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_RFU_bit                (3)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_SERDES_RST           (1 << 2)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_SERDES_RST_bf      0, 2, 2
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_SERDES_RST_msk     (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_SERDES_RST_bit     (2)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_S_RST                (1 << 1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_S_RST_bf           0, 1, 1
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_S_RST_msk          (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_S_RST_bit          (1)
#define   NFP_MAC_CSR_MAC_BLOCK_RST_MAC_H_RST                (1 << 0)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_H_RST_bf           0, 0, 0
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_H_RST_msk          (0x1)
#define     NFP_MAC_CSR_MAC_BLOCK_RST_MAC_H_RST_bit          (0)


/*
 * Register: MacHydBlkReset
 *   [31:20]   MacHydRxSerDesIfRst
 *   [19:16]   Rfu
 *   [15:4]    MacHydTxSerDesIfRst
 *   [3]       MacHydRxFFRst
 *   [2]       MacHydTxFFRst
 *   [1]       MacHydRegRst
 *   [0]       MacHydRefRst
 *
 * Name(s):
 * <base>.MacHyd0BlkReset <base>.MacHyd1BlkReset
 */
#define NFP_MAC_CSR_MAC_HYD0_BLOCK_RST                     0x0004
#define NFP_MAC_CSR_MAC_HYD1BLOCK_RST                      0x0008
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_SERDES_RST(x) (((x) & 0xfff) << 20)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_SERDES_RST_of(x) (((x) >> 20) & 0xfff)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_SERDES_RST_bf 0, 31, 20
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_SERDES_RST_msk (0xfff)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_SERDES_RST_shf (20)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_RFU(x)              (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_RFU_of(x)           (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_RFU_bf            0, 19, 16
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_RFU_msk           (0xf)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_RFU_shf           (16)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_SERDES_RST(x) (((x) & 0xfff) << 4)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_SERDES_RST_of(x) (((x) >> 4) & 0xfff)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_SERDES_RST_bf 0, 15, 4
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_SERDES_RST_msk (0xfff)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_SERDES_RST_shf (4)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_FF_RST   (1 << 3)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_FF_RST_bf 0, 3, 3
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_FF_RST_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_RX_FF_RST_bit (3)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_FF_RST   (1 << 2)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_FF_RST_bf 0, 2, 2
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_FF_RST_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_TX_FF_RST_bit (2)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REG_RST     (1 << 1)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REG_RST_bf 0, 1, 1
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REG_RST_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REG_RST_bit (1)
#define   NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REF_RST     (1 << 0)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REF_RST_bf 0, 0, 0
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REF_RST_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD0_BLOCK_RST_MAC_HYD_REF_RST_bit (0)


/*
 * Register: MacMuxCtrl
 *   [31:10]   RfuMuxCtrl
 *   [9:0]     NbiPoolLive
 *
 * Name(s):
 * <base>.MacMuxCtrl
 */
#define NFP_MAC_CSR_MAC_MUX_CTRL                           0x000c
#define   NFP_MAC_CSR_MAC_MUX_CTRL_RFU_MUX_CTRL(x)           (((x) & 0x3fffff) << 10)
#define   NFP_MAC_CSR_MAC_MUX_CTRL_RFU_MUX_CTRL_of(x)        (((x) >> 10) & 0x3fffff)
#define     NFP_MAC_CSR_MAC_MUX_CTRL_RFU_MUX_CTRL_bf         0, 31, 10
#define     NFP_MAC_CSR_MAC_MUX_CTRL_RFU_MUX_CTRL_msk        (0x3fffff)
#define     NFP_MAC_CSR_MAC_MUX_CTRL_RFU_MUX_CTRL_shf        (10)
#define   NFP_MAC_CSR_MAC_MUX_CTRL_NBI_POOL_LIVE(x)          (((x) & 0x3ff) << 0)
#define   NFP_MAC_CSR_MAC_MUX_CTRL_NBI_POOL_LIVE_of(x)       (((x) >> 0) & 0x3ff)
#define     NFP_MAC_CSR_MAC_MUX_CTRL_NBI_POOL_LIVE_bf        0, 9, 0
#define     NFP_MAC_CSR_MAC_MUX_CTRL_NBI_POOL_LIVE_msk       (0x3ff)
#define     NFP_MAC_CSR_MAC_MUX_CTRL_NBI_POOL_LIVE_shf       (0)


/*
 * Register: MacSerDesEn
 *   [31]      DmeModeHwDisable
 *   [30:24]   Rfu
 *   [23:0]    SerDesEnable
 *
 * Name(s):
 * <base>.MacSerDesEn
 */
#define NFP_MAC_CSR_MAC_SERDES_EN                          0x0010
#define   NFP_MAC_CSR_MAC_SERDES_EN_DME_MODE_HW_DISABLE      (1 << 31)
#define     NFP_MAC_CSR_MAC_SERDES_EN_DME_MODE_HW_DISABLE_bf 0, 31, 31
#define     NFP_MAC_CSR_MAC_SERDES_EN_DME_MODE_HW_DISABLE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SERDES_EN_DME_MODE_HW_DISABLE_bit (31)
#define   NFP_MAC_CSR_MAC_SERDES_EN_RFU(x)                   (((x) & 0x7f) << 24)
#define   NFP_MAC_CSR_MAC_SERDES_EN_RFU_of(x)                (((x) >> 24) & 0x7f)
#define     NFP_MAC_CSR_MAC_SERDES_EN_RFU_bf                 0, 30, 24
#define     NFP_MAC_CSR_MAC_SERDES_EN_RFU_msk                (0x7f)
#define     NFP_MAC_CSR_MAC_SERDES_EN_RFU_shf                (24)
#define   NFP_MAC_CSR_MAC_SERDES_EN_SERDES_ENABLE(x)         (((x) & 0xffffff) << 0)
#define   NFP_MAC_CSR_MAC_SERDES_EN_SERDES_ENABLE_of(x)      (((x) >> 0) & 0xffffff)
#define     NFP_MAC_CSR_MAC_SERDES_EN_SERDES_ENABLE_bf       0, 23, 0
#define     NFP_MAC_CSR_MAC_SERDES_EN_SERDES_ENABLE_msk      (0xffffff)
#define     NFP_MAC_CSR_MAC_SERDES_EN_SERDES_ENABLE_shf      (0)


/*
 * Register: MacSysSupCtrl
 *   [31]      HistoGoodputOnly
 *   [30]      NbiIgPortXoffEn
 *   [29]      SplitMemEnhEg
 *   [28]      SplitMemEnh
 *   [27]      IgParsePaylenEnable
 *   [26]      MacSerDesLaneSwapL23L12
 *   [25]      MacSerDesLaneSwapL11L00
 *   [24]      MacIlkForcePadErr
 *   [23:20]   MacMpbFreeBufFifoLowWm
 *   [19]      MacIgLnkLstFreezeOnErrN
 *   [18]      MacEgLnkLstFreezeOnErrN
 *   [17]      DwrrArbiterDisable
 *   [16]      DwrrWeightWrEnable
 *   [15]      MacIlkLiveIntSel
 *   [14]      Lk1IgDqSegmentedEn
 *   [13]      Lk0IgDqSegmentedEn
 *   [12]      Lk1LinklistEn
 *   [11]      Lk0LinklistEn
 *   [10]      Hy1LinklistEn
 *   [9]       Hy0LinklistEn
 *   [8]       SplitMemIG
 *   [7]       ExtraEthHistMode
 *   [6]       Limiter_Disable_Hy1
 *   [5]       MacSysSupCtrlA
 *   [4]       MacPerfFast2Slow
 *   [3]       TimeStampFrc
 *   [2]       TimeStampSet
 *   [1]       TimeStampRst
 *   [0]       TimeStampEn
 *
 * Name(s):
 * <base>.MacSysSupCtrl
 */
#define NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL                   0x0014
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HISTO_GOODPUT_ONLY (1 << 31)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HISTO_GOODPUT_ONLY_bf 0, 31, 31
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HISTO_GOODPUT_ONLY_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HISTO_GOODPUT_ONLY_bit (31)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_NBI_IG_PORT_XOFF_EN (1 << 30)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_NBI_IG_PORT_XOFF_EN_bf 0, 30, 30
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_NBI_IG_PORT_XOFF_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_NBI_IG_PORT_XOFF_EN_bit (30)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_EG  (1 << 29)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_EG_bf 0, 29, 29
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_EG_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_EG_bit (29)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH     (1 << 28)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_bf 0, 28, 28
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_ENH_bit (28)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_IG_PARSE_PAYLEN_ENABLE (1 << 27)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_IG_PARSE_PAYLEN_ENABLE_bf 0, 27, 27
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_IG_PARSE_PAYLEN_ENABLE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_IG_PARSE_PAYLEN_ENABLE_bit (27)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L23_L12 (1 << 26)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L23_L12_bf 0, 26, 26
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L23_L12_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L23_L12_bit (26)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L11_L00 (1 << 25)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L11_L00_bf 0, 25, 25
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L11_L00_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SERDES_LANE_SWAP_L11_L00_bit (25)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_FORCE_PAD_ERR (1 << 24)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_FORCE_PAD_ERR_bf 0, 24, 24
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_FORCE_PAD_ERR_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_FORCE_PAD_ERR_bit (24)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_MPB_FREE_BUF_FIFO_LOW_WM(x) (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_MPB_FREE_BUF_FIFO_LOW_WM_of(x) (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_MPB_FREE_BUF_FIFO_LOW_WM_bf 0, 23, 20
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_MPB_FREE_BUF_FIFO_LOW_WM_msk (0xf)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_MPB_FREE_BUF_FIFO_LOW_WM_shf (20)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_IG_LNK_LST_FREEZE_ON_ERR_N (1 << 19)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_IG_LNK_LST_FREEZE_ON_ERR_N_bf 0, 19, 19
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_IG_LNK_LST_FREEZE_ON_ERR_N_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_IG_LNK_LST_FREEZE_ON_ERR_N_bit (19)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_EG_LNK_LST_FREEZE_ON_ERR_N (1 << 18)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_EG_LNK_LST_FREEZE_ON_ERR_N_bf 0, 18, 18
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_EG_LNK_LST_FREEZE_ON_ERR_N_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_EG_LNK_LST_FREEZE_ON_ERR_N_bit (18)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_ARBITER_DISABLE (1 << 17)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_ARBITER_DISABLE_bf 0, 17, 17
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_ARBITER_DISABLE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_ARBITER_DISABLE_bit (17)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_WEIGHT_WR_ENABLE (1 << 16)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_WEIGHT_WR_ENABLE_bf 0, 16, 16
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_WEIGHT_WR_ENABLE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_DWRR_WEIGHT_WR_ENABLE_bit (16)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_LIVE_INT_SEL (1 << 15)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_LIVE_INT_SEL_bf 0, 15, 15
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_LIVE_INT_SEL_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_ILK_LIVE_INT_SEL_bit (15)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_IG_DQ_SEGEMENTED_EN (1 << 14)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_IG_DQ_SEGEMENTED_EN_bf 0, 14, 14
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_IG_DQ_SEGEMENTED_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_IG_DQ_SEGEMENTED_EN_bit (14)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_IG_DQ_SEGEMENTED_EN (1 << 13)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_IG_DQ_SEGEMENTED_EN_bf 0, 13, 13
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_IG_DQ_SEGEMENTED_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_IG_DQ_SEGEMENTED_EN_bit (13)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_LINKLIST_EN   (1 << 12)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_LINKLIST_EN_bf 0, 12, 12
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_LINKLIST_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK1_LINKLIST_EN_bit (12)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_LINKLIST_EN   (1 << 11)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_LINKLIST_EN_bf 0, 11, 11
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_LINKLIST_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LK0_LINKLIST_EN_bit (11)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY1_LINKLIST_EN   (1 << 10)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY1_LINKLIST_EN_bf 0, 10, 10
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY1_LINKLIST_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY1_LINKLIST_EN_bit (10)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY0_LINKLIST_EN   (1 << 9)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY0_LINKLIST_EN_bf 0, 9, 9
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY0_LINKLIST_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_HY0_LINKLIST_EN_bit (9)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_IG      (1 << 8)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_IG_bf 0, 8, 8
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_IG_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_SPLIT_MEM_IG_bit (8)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_EXTRA_ETH_HIST_MODE (1 << 7)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_EXTRA_ETH_HIST_MODE_bf 0, 7, 7
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_EXTRA_ETH_HIST_MODE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_EXTRA_ETH_HIST_MODE_bit (7)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LIMITER_DISABLE_HY1 (1 << 6)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LIMITER_DISABLE_HY1_bf 0, 6, 6
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LIMITER_DISABLE_HY1_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_LIMITER_DISABLE_HY1_bit (6)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SYS_SUPPORT_CTRLA (1 << 5)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SYS_SUPPORT_CTRLA_bf 0, 5, 5
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SYS_SUPPORT_CTRLA_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_SYS_SUPPORT_CTRLA_bit (5)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_PERF_FAST_2_SLOW (1 << 4)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_PERF_FAST_2_SLOW_bf 0, 4, 4
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_PERF_FAST_2_SLOW_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_MAC_PERF_FAST_2_SLOW_bit (4)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_FRC     (1 << 3)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_FRC_bf 0, 3, 3
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_FRC_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_FRC_bit (3)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_SET     (1 << 2)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_SET_bf 0, 2, 2
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_SET_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_SET_bit (2)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_RST     (1 << 1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_RST_bf 0, 1, 1
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_RST_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_RST_bit (1)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_EN      (1 << 0)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_EN_bf 0, 0, 0
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_CTRL_TIMESTAMP_EN_bit (0)


/*
 * Register: MacSysSupStat
 *   [31:25]   MacNbiPoolLwm
 *   [24:16]   MacNbiPoolSize
 *   [15]      MacNbiPoolDisable
 *   [14]      MacNbiPoolFairEn
 *   [13]      MacNbiPool2Sel
 *   [12]      MacIgChkOverall
 *   [11]      MacErrStatEn
 *   [10]      MacNoDropErrPktEn
 *   [9:5]     MacEthTsMld2
 *   [4:0]     MacEthTsMld1
 *
 * Name(s):
 * <base>.MacSysSupStat
 */
#define NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT                   0x0018
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_LWM(x) (((x) & 0x7f) << 25)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_LWM_of(x) (((x) >> 25) & 0x7f)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_LWM_bf 0, 31, 25
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_LWM_msk (0x7f)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_LWM_shf (25)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_SIZE(x) (((x) & 0x1ff) << 16)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_SIZE_of(x) (((x) >> 16) & 0x1ff)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_SIZE_bf 0, 24, 16
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_SIZE_msk (0x1ff)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_SIZE_shf (16)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_DISABLE (1 << 15)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_DISABLE_bf 0, 15, 15
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_DISABLE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_DISABLE_bit (15)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_FAIR_EN (1 << 14)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_FAIR_EN_bf 0, 14, 14
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_FAIR_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL_FAIR_EN_bit (14)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL2_SEL (1 << 13)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL2_SEL_bf 0, 13, 13
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL2_SEL_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NBI_POOL2_SEL_bit (13)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_IG_CHK_OVERALL (1 << 12)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_IG_CHK_OVERALL_bf 0, 12, 12
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_IG_CHK_OVERALL_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_IG_CHK_OVERALL_bit (12)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ERR_STAT_EN   (1 << 11)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ERR_STAT_EN_bf 0, 11, 11
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ERR_STAT_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ERR_STAT_EN_bit (11)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NO_DROP_ERR_PKT_EN (1 << 10)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NO_DROP_ERR_PKT_EN_bf 0, 10, 10
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NO_DROP_ERR_PKT_EN_msk (0x1)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_NO_DROP_ERR_PKT_EN_bit (10)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_2(x) (((x) & 0x1f) << 5)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_2_of(x) (((x) >> 5) & 0x1f)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_2_bf 0, 9, 5
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_2_msk (0x1f)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_2_shf (5)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_1(x) (((x) & 0x1f) << 0)
#define   NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_1_of(x) (((x) >> 0) & 0x1f)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_1_bf 0, 4, 0
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_1_msk (0x1f)
#define     NFP_MAC_CSR_MAC_SYS_SUPPORT_STAT_MAC_ETH_TS_MLD_1_shf (0)


/*
 * Register: MacTimeStampNsec
 *   [31:0]    MacTimeStampNsec
 *
 * Name(s):
 * <base>.MacTimeStampNsec
 */
#define NFP_MAC_CSR_MAC_TS_NSEC                            0x001c
#define   NFP_MAC_CSR_MAC_TS_NSEC_MAC_TS_NSEC(x)             (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_TS_NSEC_MAC_TS_NSEC_of(x)          (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_NSEC_MAC_TS_NSEC_bf           0, 31, 0
#define     NFP_MAC_CSR_MAC_TS_NSEC_MAC_TS_NSEC_msk          (0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_NSEC_MAC_TS_NSEC_shf          (0)


/*
 * Register: MacTimeStampSec
 *   [31:0]    MacTimeStampSec
 *
 * Name(s):
 * <base>.MacTimeStampSec
 */
#define NFP_MAC_CSR_MAC_TS_SEC                             0x0020
#define   NFP_MAC_CSR_MAC_TS_SEC_MAC_TS_SEC(x)               (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_TS_SEC_MAC_TS_SEC_of(x)            (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_SEC_MAC_TS_SEC_bf             0, 31, 0
#define     NFP_MAC_CSR_MAC_TS_SEC_MAC_TS_SEC_msk            (0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_SEC_MAC_TS_SEC_shf            (0)


/*
 * Register: MacTimeStampIncr
 *   [19:16]   IncrNsec
 *   [15:0]    IncrFraction
 *
 * Name(s):
 * <base>.MacTimeStampIncr
 */
#define NFP_MAC_CSR_MAC_TS_INCR                            0x0024
#define   NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_NSEC(x)        (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_NSEC_of(x)     (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_NSEC_bf      0, 19, 16
#define     NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_NSEC_msk     (0xf)
#define     NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_NSEC_shf     (16)
#define   NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_FRAC(x)        (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_FRAC_of(x)     (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_FRAC_bf      0, 15, 0
#define     NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_FRAC_msk     (0xffff)
#define     NFP_MAC_CSR_MAC_TS_INCR_MAC_TS_INCR_FRAC_shf     (0)


/*
 * Register: MacTimeStampSetNsec
 *   [31:0]    MacTimeStampSetNsec
 *
 * Name(s):
 * <base>.MacTimeStampSetNsec
 */
#define NFP_MAC_CSR_MAC_TS_SET_NSEC                        0x0028
#define   NFP_MAC_CSR_MAC_TS_SET_NSEC_MAC_TS_SET_NSEC(x)     (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_TS_SET_NSEC_MAC_TS_SET_NSEC_of(x)  (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_SET_NSEC_MAC_TS_SET_NSEC_bf   0, 31, 0
#define     NFP_MAC_CSR_MAC_TS_SET_NSEC_MAC_TS_SET_NSEC_msk  (0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_SET_NSEC_MAC_TS_SET_NSEC_shf  (0)


/*
 * Register: MacTimeStampSetSec
 *   [31:0]    MacTimeStampSetSec
 *
 * Name(s):
 * <base>.MacTimeStampSetSec
 */
#define NFP_MAC_CSR_MAC_TS_SET_SEC                         0x002c
#define   NFP_MAC_CSR_MAC_TS_SET_SEC_MAC_TS_SEC(x)           (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_TS_SET_SEC_MAC_TS_SEC_of(x)        (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_SET_SEC_MAC_TS_SEC_bf         0, 31, 0
#define     NFP_MAC_CSR_MAC_TS_SET_SEC_MAC_TS_SEC_msk        (0xffffffff)
#define     NFP_MAC_CSR_MAC_TS_SET_SEC_MAC_TS_SEC_shf        (0)


/*
 * Register: MacTdmCycleWord3100
 *   [31:28]   MacTdmPortSlot7
 *   [27:24]   MacTdmPortSlot6
 *   [23:20]   MacTdmPortSlot5
 *   [19:16]   MacTdmPortSlot4
 *   [15:12]   MacTdmPortSlot3
 *   [11:8]    MacTdmPortSlot2
 *   [7:4]     MacTdmPortSlot1
 *   [3:0]     MacTdmPortSlot0
 *
 * Name(s):
 * <base>.MacTdm0CycleWord3100 <base>.MacTdm1CycleWord3100
 */
#define NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100               0x0030
#define NFP_MAC_CSR_MAC_TDM1_CYCLE_WORD_3100               0x0038
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT7(x) (((x) & 0xf) << 28)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT7_of(x) (((x) >> 28) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT7_bf 0, 31, 28
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT7_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT7_shf (28)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT6(x) (((x) & 0xf) << 24)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT6_of(x) (((x) >> 24) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT6_bf 0, 27, 24
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT6_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT6_shf (24)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT5(x) (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT5_of(x) (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT5_bf 0, 23, 20
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT5_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT5_shf (20)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT4(x) (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT4_of(x) (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT4_bf 0, 19, 16
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT4_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT4_shf (16)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT3(x) (((x) & 0xf) << 12)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT3_of(x) (((x) >> 12) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT3_bf 0, 15, 12
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT3_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT3_shf (12)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT2(x) (((x) & 0xf) << 8)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT2_of(x) (((x) >> 8) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT2_bf 0, 11, 8
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT2_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT2_shf (8)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT1(x) (((x) & 0xf) << 4)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT1_of(x) (((x) >> 4) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT1_bf 0, 7, 4
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT1_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT1_shf (4)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT0(x) (((x) & 0xf) << 0)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT0_of(x) (((x) >> 0) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT0_bf 0, 3, 0
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT0_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_3100_MAC_TDM_PORT_SLOT0_shf (0)


/*
 * Register: MacTdmCycleWord4732
 *   [7:4]     MacTdmPortSlot9
 *   [3:0]     MacTdmPortSlot8
 *
 * Name(s):
 * <base>.MacTdm0CycleWord4732 <base>.MacTdm1CycleWord4732
 */
#define NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732               0x0034
#define NFP_MAC_CSR_MAC_TDM1_CYCLE_WORD_4732               0x003c
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT9(x) (((x) & 0xf) << 4)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT9_of(x) (((x) >> 4) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT9_bf 0, 7, 4
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT9_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT9_shf (4)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT8(x) (((x) & 0xf) << 0)
#define   NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT8_of(x) (((x) >> 0) & 0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT8_bf 0, 3, 0
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT8_msk (0xf)
#define     NFP_MAC_CSR_MAC_TDM0_CYCLE_WORD_4732_MAC_TDM_PORT_SLOT8_shf (0)


/*
 * Register: MacTdmMode0900
 *   [29:27]   MacTdmModePort9
 *   [26:24]   MacTdmModePort8
 *   [23:21]   MacTdmModePort7
 *   [20:18]   MacTdmModePort6
 *   [17:15]   MacTdmModePort5
 *   [14:12]   MacTdmModePort4
 *   [11:9]    MacTdmModePort3
 *   [8:6]     MacTdmModePort2
 *   [5:3]     MacTdmModePort1
 *   [2:0]     MacTdmModePort0
 *
 * Name(s):
 * <base>.MacTdm0Mode0900 <base>.MacTdm1Mode0900
 */
#define NFP_MAC_CSR_MAC_TDM0_MODE_0900                     0x0040
#define NFP_MAC_CSR_MAC_TDM1_MODE_0900                     0x0048
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9(x) (((x) & 7) << 27)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_of(x) (((x) >> 27) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_bf 0, 29, 27
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_9_shf (27)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8(x) (((x) & 7) << 24)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_of(x) (((x) >> 24) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_bf 0, 26, 24
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_8_shf (24)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7(x) (((x) & 7) << 21)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_of(x) (((x) >> 21) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_bf 0, 23, 21
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_7_shf (21)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6(x) (((x) & 7) << 18)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_of(x) (((x) >> 18) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_BW (3)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_bf 0, 20, 18
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_6_shf (18)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5(x) (((x) & 7) << 15)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_of(x) (((x) >> 15) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_bf 0, 17, 15
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_5_shf (15)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4(x) (((x) & 7) << 12)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_of(x) (((x) >> 12) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_BW (3)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_bf 0, 14, 12
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_4_shf (12)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3(x) (((x) & 7) << 9)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_of(x) (((x) >> 9) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_bf 0, 11, 9
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_3_shf (9)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2(x) (((x) & 7) << 6)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_of(x) (((x) >> 6) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_BW (3)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_BW (5)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_bf 0, 8, 6
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_2_shf (6)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1(x) (((x) & 7) << 3)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_of(x) (((x) >> 3) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_bf 0, 5, 3
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_1_shf (3)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0(x) (((x) & 7) << 0)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_of(x) (((x) >> 0) & 7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (0)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (1)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (2)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (3)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (4)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (5)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (6)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_BW (7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_bf 0, 2, 0
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_msk (0x7)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_0900_MAC_TDM_MODE_PORT_0_shf (0)


/*
 * Register: MacTdmMode1110Crc
 *   [25:16]   MacEgressPortCrcEn
 *
 * Name(s):
 * <base>.MacTdm0Mode1110CrcEn <base>.MacTdm1Mode1110CrcEn
 */
#define NFP_MAC_CSR_MAC_TDM0_MODE_1110_CRC_EN              0x0044
#define NFP_MAC_CSR_MAC_TDM1_MODE_1110_CRC_EN              0x004c
#define   NFP_MAC_CSR_MAC_TDM0_MODE_1110_CRC_EN_MAC_EGRESS_PORT_CRC_EN(x) (((x) & 0x3ff) << 16)
#define   NFP_MAC_CSR_MAC_TDM0_MODE_1110_CRC_EN_MAC_EGRESS_PORT_CRC_EN_of(x) (((x) >> 16) & 0x3ff)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_1110_CRC_EN_MAC_EGRESS_PORT_CRC_EN_bf 0, 25, 16
#define     NFP_MAC_CSR_MAC_TDM0_MODE_1110_CRC_EN_MAC_EGRESS_PORT_CRC_EN_msk (0x3ff)
#define     NFP_MAC_CSR_MAC_TDM0_MODE_1110_CRC_EN_MAC_EGRESS_PORT_CRC_EN_shf (16)


/*
 * Register: MacPortChanAssign
 *   [29:26]   PortNumOfChannels2
 *   [25:20]   PortBaseChan2
 *   [19:16]   PortNumOfChannels1
 *   [15:10]   PortBaseChan1
 *   [9:6]     PortNumOfChannels0
 *   [5:0]     PortBaseChan0
 *
 * Name(s):
 * <base>.MacPort2to0ChanAssign <base>.MacPort5to3ChanAssign
 * <base>.MacPort8to6ChanAssign <base>.MacPort9ChanAssign
 * <base>.MacPort12to10ChanAssign <base>.MacPort15to13ChanAssign
 * <base>.MacPort18to16ChanAssign <base>.MacPort19ChanAssign
 * <base>.MacEgPort2to0ChanAssign <base>.MacEgPort5to3ChanAssign
 * <base>.MacEgPort8to6ChanAssign <base>.MacEgPort9ChanAssign
 * <base>.MacEgPort12to10ChanAssign <base>.MacEgPort15to13ChanAssign
 * <base>.MacEgPort18to16ChanAssign <base>.MacEgPort19ChanAssign
 */
#define NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN            0x0050
#define NFP_MAC_CSR_MAC_PORT_5_TO_3_CHAN_ASSIGN            0x0054
#define NFP_MAC_CSR_MAC_PORT_8_TO_6_CHAN_ASSIGN            0x0058
#define NFP_MAC_CSR_MAC_PORT_9_CHAN_ASSIGN                 0x005c
#define NFP_MAC_CSR_MAC_PORT_12_TO_10_CHAN_ASSIGN          0x0060
#define NFP_MAC_CSR_MAC_PORT_15_TO_13_CHAN_ASSIGN          0x0064
#define NFP_MAC_CSR_MAC_PORT_18_TO_16_CHAN_ASSIGN          0x0068
#define NFP_MAC_CSR_MAC_PORT_19_CHAN_ASSIGN                0x006c
#define NFP_MAC_CSR_MAC_EG_PORT_2_TO_0_CHAN_ASSIGN         0x0240
#define NFP_MAC_CSR_MAC_EG_PORT_5_TO_3_CHAN_ASSIGN         0x0244
#define NFP_MAC_CSR_MAC_EG_PORT_8_TO_6_CHAN_ASSIGN         0x0248
#define NFP_MAC_CSR_MAC_EG_PORT_9_CHAN_ASSIGN              0x024c
#define NFP_MAC_CSR_MAC_EG_PORT_12_TO_10_CHAN_ASSIGN       0x0250
#define NFP_MAC_CSR_MAC_EG_PORT_15_TO_13_CHAN_ASSIGN       0x0254
#define NFP_MAC_CSR_MAC_EG_PORT_18_16_CHAN_ASSIGN          0x0258
#define NFP_MAC_CSR_MAC_EG_PORT_19_CHAN_ASSIGN             0x025c
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS2(x) (((x) & 0xf) << 26)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS2_of(x) (((x) >> 26) & 0xf)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS2_bf 0, 29, 26
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS2_msk (0xf)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS2_shf (26)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN2(x) (((x) & 0x3f) << 20)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN2_of(x) (((x) >> 20) & 0x3f)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN2_bf 0, 25, 20
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN2_msk (0x3f)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN2_shf (20)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS1(x) (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS1_of(x) (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS1_bf 0, 19, 16
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS1_msk (0xf)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS1_shf (16)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN1(x) (((x) & 0x3f) << 10)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN1_of(x) (((x) >> 10) & 0x3f)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN1_bf 0, 15, 10
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN1_msk (0x3f)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN1_shf (10)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS0(x) (((x) & 0xf) << 6)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS0_of(x) (((x) >> 6) & 0xf)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS0_bf 0, 9, 6
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS0_msk (0xf)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_NUM_OF_CHANS0_shf (6)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN0(x) (((x) & 0x3f) << 0)
#define   NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN0_of(x) (((x) >> 0) & 0x3f)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN0_bf 0, 5, 0
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN0_msk (0x3f)
#define     NFP_MAC_CSR_MAC_PORT_2_TO_0_CHAN_ASSIGN_PORT_BASE_CHAN0_shf (0)


/*
 * Register: MacPrePendCtl1
 *   [31:28]   EGSkipOctetsPort3
 *   [27:24]   IGSkipOctetsPort3
 *   [23:20]   EGSkipOctetsPort2
 *   [19:16]   IGSkipOctetsPort2
 *   [15:12]   EGSkipOctetsPort1
 *   [11:8]    IGSkipOctetsPort1
 *   [7:4]     EGSkipOctetsPort0
 *   [3:0]     IGSkipOctetsPort0
 *
 * Name(s):
 * <base>.MacPrePendCtl03to00 <base>.MacPrePendCtl13to10
 */
#define NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00               0x0070
#define NFP_MAC_CSR_MAC_PREPEND_CTL_13_TO_10               0x007c
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_3(x) (((x) & 0xf) << 28)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_3_of(x) (((x) >> 28) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_3_bf 0, 31, 28
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_3_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_3_shf (28)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_3(x) (((x) & 0xf) << 24)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_3_of(x) (((x) >> 24) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_3_bf 0, 27, 24
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_3_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_3_shf (24)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_2(x) (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_2_of(x) (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_2_bf 0, 23, 20
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_2_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_2_shf (20)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_2(x) (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_2_of(x) (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_2_bf 0, 19, 16
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_2_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_2_shf (16)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_1(x) (((x) & 0xf) << 12)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_1_of(x) (((x) >> 12) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_1_bf 0, 15, 12
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_1_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_1_shf (12)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_1(x) (((x) & 0xf) << 8)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_1_of(x) (((x) >> 8) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_1_bf 0, 11, 8
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_1_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_1_shf (8)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_0(x) (((x) & 0xf) << 4)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_0_of(x) (((x) >> 4) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_0_bf 0, 7, 4
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_0_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_EG_SKIP_OCTETS_PORT_0_shf (4)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_0(x) (((x) & 0xf) << 0)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_0_of(x) (((x) >> 0) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_0_bf 0, 3, 0
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_0_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_03_TO_00_IG_SKIP_OCTETS_PORT_0_shf (0)


/*
 * Register: MacPrePendCtl2
 *   [31:28]   EGSkipOctetsPort7
 *   [27:24]   IGSkipOctetsPort7
 *   [23:20]   EGSkipOctetsPort6
 *   [19:16]   IGSkipOctetsPort6
 *   [15:12]   EGSkipOctetsPort5
 *   [11:8]    IGSkipOctetsPort5
 *   [7:4]     EGSkipOctetsPort4
 *   [3:0]     IGSkipOctetsPort4
 *
 * Name(s):
 * <base>.MacPrePendCtl07to04 <base>.MacPrePendCtl17to14
 */
#define NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04               0x0074
#define NFP_MAC_CSR_MAC_PREPEND_CTL_17_TO_14               0x0080
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_7(x) (((x) & 0xf) << 28)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_7_of(x) (((x) >> 28) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_7_bf 0, 31, 28
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_7_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_7_shf (28)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_7(x) (((x) & 0xf) << 24)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_7_of(x) (((x) >> 24) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_7_bf 0, 27, 24
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_7_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_7_shf (24)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_6(x) (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_6_of(x) (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_6_bf 0, 23, 20
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_6_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_6_shf (20)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_6(x) (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_6_of(x) (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_6_bf 0, 19, 16
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_6_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_6_shf (16)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_5(x) (((x) & 0xf) << 12)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_5_of(x) (((x) >> 12) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_5_bf 0, 15, 12
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_5_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_5_shf (12)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_5(x) (((x) & 0xf) << 8)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_5_of(x) (((x) >> 8) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_5_bf 0, 11, 8
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_5_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_5_shf (8)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_4(x) (((x) & 0xf) << 4)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_4_of(x) (((x) >> 4) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_4_bf 0, 7, 4
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_4_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_EG_SKIP_OCTETS_PORT_4_shf (4)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_4(x) (((x) & 0xf) << 0)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_4_of(x) (((x) >> 0) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_4_bf 0, 3, 0
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_4_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_07_TO_04_IG_SKIP_OCTETS_PORT_4_shf (0)


/*
 * Register: MacPrePendCtl3
 *   [31:16]   Rfu
 *   [15:12]   EGSkipOctetsPort9
 *   [11:8]    IGSkipOctetsPort9
 *   [7:4]     EGSkipOctetsPort8
 *   [3:0]     IGSkipOctetsPort8
 *
 * Name(s):
 * <base>.MacPrePendCtl09to08 <base>.MacPrePendCtl19to18
 */
#define NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08               0x0078
#define NFP_MAC_CSR_MAC_PREPEND_CTL_19_TO_18               0x0084
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_RFU(x)        (((x) & 0xffff) << 16)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_RFU_of(x)     (((x) >> 16) & 0xffff)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_RFU_bf      0, 31, 16
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_RFU_msk     (0xffff)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_RFU_shf     (16)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_9(x) (((x) & 0xf) << 12)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_9_of(x) (((x) >> 12) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_9_bf 0, 15, 12
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_9_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_9_shf (12)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_9(x) (((x) & 0xf) << 8)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_9_of(x) (((x) >> 8) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_9_bf 0, 11, 8
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_9_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_9_shf (8)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_8(x) (((x) & 0xf) << 4)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_8_of(x) (((x) >> 4) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_8_bf 0, 7, 4
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_8_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_EG_SKIP_OCTETS_PORT_8_shf (4)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_8(x) (((x) & 0xf) << 0)
#define   NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_8_of(x) (((x) >> 0) & 0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_8_bf 0, 3, 0
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_8_msk (0xf)
#define     NFP_MAC_CSR_MAC_PREPEND_CTL_09_TO_08_IG_SKIP_OCTETS_PORT_8_shf (0)


/*
 * Register: MacPrePendDsaCtl1
 *   [31:30]   DsaTagModePort15
 *   [29:28]   DsaTagModePort14
 *   [27:26]   DsaTagModePort13
 *   [25:24]   DsaTagModePort12
 *   [23:22]   DsaTagModePort11
 *   [21:20]   DsaTagModePort10
 *   [19:18]   DsaTagModePort9
 *   [17:16]   DsaTagModePort8
 *   [15:14]   DsaTagModePort7
 *   [13:12]   DsaTagModePort6
 *   [11:10]   DsaTagModePort5
 *   [9:8]     DsaTagModePort4
 *   [7:6]     DsaTagModePort3
 *   [5:4]     DsaTagModePort2
 *   [3:2]     DsaTagModePort1
 *   [1:0]     DsaTagModePort0
 *
 * Name(s):
 * <base>.MacPrePendDsaCtl15to00 <base>.MacEgPrePendDsaCtl15to00
 */
#define NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00                   0x0088
#define NFP_MAC_CSR_MAC_EG_DSA_CTL_15_TO_00                0x01cc
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_15(x) (((x) & 3) << 30)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_15_of(x) (((x) >> 30) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_15_bf 0, 31, 30
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_15_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_15_shf (30)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_14(x) (((x) & 3) << 28)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_14_of(x) (((x) >> 28) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_14_bf 0, 29, 28
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_14_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_14_shf (28)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_13(x) (((x) & 3) << 26)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_13_of(x) (((x) >> 26) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_13_bf 0, 27, 26
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_13_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_13_shf (26)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_12(x) (((x) & 3) << 24)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_12_of(x) (((x) >> 24) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_12_bf 0, 25, 24
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_12_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_12_shf (24)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_11(x) (((x) & 3) << 22)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_11_of(x) (((x) >> 22) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_11_bf 0, 23, 22
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_11_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_11_shf (22)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_10(x) (((x) & 3) << 20)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_10_of(x) (((x) >> 20) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_10_bf 0, 21, 20
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_10_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_10_shf (20)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_9(x) (((x) & 3) << 18)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_9_of(x) (((x) >> 18) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_9_bf 0, 19, 18
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_9_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_9_shf (18)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_8(x) (((x) & 3) << 16)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_8_of(x) (((x) >> 16) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_8_bf 0, 17, 16
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_8_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_8_shf (16)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_7(x) (((x) & 3) << 14)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_7_of(x) (((x) >> 14) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_7_bf 0, 15, 14
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_7_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_7_shf (14)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_6(x) (((x) & 3) << 12)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_6_of(x) (((x) >> 12) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_6_bf 0, 13, 12
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_6_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_6_shf (12)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_5(x) (((x) & 3) << 10)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_5_of(x) (((x) >> 10) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_5_bf 0, 11, 10
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_5_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_5_shf (10)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_4(x) (((x) & 3) << 8)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_4_of(x) (((x) >> 8) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_4_bf 0, 9, 8
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_4_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_4_shf (8)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_3(x) (((x) & 3) << 6)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_3_of(x) (((x) >> 6) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_3_bf 0, 7, 6
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_3_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_3_shf (6)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_2(x) (((x) & 3) << 4)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_2_of(x) (((x) >> 4) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_2_bf 0, 5, 4
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_2_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_2_shf (4)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_1(x) (((x) & 3) << 2)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_1_of(x) (((x) >> 2) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_1_bf 0, 3, 2
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_1_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_1_shf (2)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0(x) (((x) & 3) << 0)
#define   NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_of(x) (((x) >> 0) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_Mode (0)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_Mode (1)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_Mode (2)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_Mode (3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_bf 0, 1, 0
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_15_TO_00_DSA_TAG_MODE_PORT_0_shf (0)


/*
 * Register: MacPrePendDsaCtl2
 *   [7:6]     DsaTagModePort19
 *   [5:4]     DsaTagModePort18
 *   [3:2]     DsaTagModePort17
 *   [1:0]     DsaTagModePort16
 *
 * Name(s):
 * <base>.MacPrePendDsaCtlLkand23to16 <base>.MacEgPrePendDsaCtlLkand23to16
 */
#define NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16                   0x008c
#define NFP_MAC_CSR_MAC_EG_DSA_CTL_23_TO_16                0x01d0
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_19(x) (((x) & 3) << 6)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_19_of(x) (((x) >> 6) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_19_bf 0, 7, 6
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_19_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_19_shf (6)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_18(x) (((x) & 3) << 4)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_18_of(x) (((x) >> 4) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_18_bf 0, 5, 4
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_18_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_18_shf (4)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_17(x) (((x) & 3) << 2)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_17_of(x) (((x) >> 2) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_17_bf 0, 3, 2
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_17_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_17_shf (2)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16(x) (((x) & 3) << 0)
#define   NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_of(x) (((x) >> 0) & 3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_Mode (0)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_Mode (1)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_Mode (2)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_Mode (3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_bf 0, 1, 0
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_msk (0x3)
#define     NFP_MAC_CSR_MAC_DSA_CTL_23_TO_16_DSA_TAG_MODE_PORT_16_shf (0)


/*
 * Register: MacPcsIpCtrl
 *   [31:27]   IpCtrlRsvdB
 *   [26:20]   PcsFecErrEna
 *   [19:13]   PcsFecEna
 *   [12]      UsgmiiPcs40Bit
 *   [11]      MacMode40GEna
 *   [10]      PcsMode40GEna
 *   [9:0]     Sdn2
 *
 * Name(s):
 * <base>.MacPcsIpCtrl0 <base>.MacPcsIpCtrl1
 */
#define NFP_MAC_CSR_MAC_PCS_IP_CTRL_0                      0x0090
#define NFP_MAC_CSR_MAC_PCS_IP_CTRL_1                      0x0094
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_IP_CTRL_RSVD_B(x)    (((x) & 0x1f) << 27)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_IP_CTRL_RSVD_B_of(x) (((x) >> 27) & 0x1f)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_IP_CTRL_RSVD_B_bf  0, 31, 27
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_IP_CTRL_RSVD_B_msk (0x1f)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_IP_CTRL_RSVD_B_shf (27)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ERR_ENA(x)   (((x) & 0x7f) << 20)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ERR_ENA_of(x) (((x) >> 20) & 0x7f)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ERR_ENA_bf 0, 26, 20
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ERR_ENA_msk (0x7f)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ERR_ENA_shf (20)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ENA(x)       (((x) & 0x7f) << 13)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ENA_of(x)    (((x) >> 13) & 0x7f)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ENA_bf     0, 19, 13
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ENA_msk    (0x7f)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_FEC_ENA_shf    (13)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_USGMII_PCS_40_BIT    (1 << 12)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_USGMII_PCS_40_BIT_bf 0, 12, 12
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_USGMII_PCS_40_BIT_msk (0x1)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_USGMII_PCS_40_BIT_bit (12)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_MAC_MODE_40G_ENA     (1 << 11)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_MAC_MODE_40G_ENA_bf 0, 11, 11
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_MAC_MODE_40G_ENA_msk (0x1)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_MAC_MODE_40G_ENA_bit (11)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_MODE_40G_ENA     (1 << 10)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_MODE_40G_ENA_bf 0, 10, 10
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_MODE_40G_ENA_msk (0x1)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_PCS_MODE_40G_ENA_bit (10)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_SD_N2(x)             (((x) & 0x3ff) << 0)
#define   NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_SD_N2_of(x)          (((x) >> 0) & 0x3ff)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_SD_N2_bf           0, 9, 0
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_SD_N2_msk          (0x3ff)
#define     NFP_MAC_CSR_MAC_PCS_IP_CTRL_0_SD_N2_shf          (0)


/*
 * Register: EgBufferCreditPoolCount
 *   [31]      EgBufferLinklistReady
 *   [29:16]   EgBufferCreditCount1
 *   [13:0]    EgBufferCreditCount
 *
 * Name(s):
 * <base>.EgBufferCreditPoolCount
 */
#define NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT            0x0098
#define   NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_LINKLIST_READY (1 << 31)
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_LINKLIST_READY_bf 0, 31, 31
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_LINKLIST_READY_msk (0x1)
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_LINKLIST_READY_bit (31)
#define   NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT1(x) (((x) & 0x3fff) << 16)
#define   NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT1_of(x) (((x) >> 16) & 0x3fff)
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT1_bf 0, 29, 16
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT1_msk (0x3fff)
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT1_shf (16)
#define   NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT(x) (((x) & 0x3fff) << 0)
#define   NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT_of(x) (((x) >> 0) & 0x3fff)
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT_bf 0, 13, 0
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT_msk (0x3fff)
#define     NFP_MAC_CSR_EG_BUFFER_CREDIT_POOL_COUNT_EG_BUFFER_CREDIT_COUNT_shf (0)


/*
 * Register: TxMpbCreditInit
 *   [31:20]   Rfu
 *   [19:16]   TxMpbCreditDataInit
 *   [15:12]   Rfu2
 *   [11:6]    TxMpbCreditMaxPktInit
 *   [5:0]     TxMpbCreditPktInit
 *
 * Name(s):
 * <base>.TxMpbCreditInit
 */
#define NFP_MAC_CSR_TX_MPB_CREDIT_INIT                     0x009c
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU(x)              (((x) & 0xfff) << 20)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU_of(x)           (((x) >> 20) & 0xfff)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU_bf            0, 31, 20
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU_msk           (0xfff)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU_shf           (20)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_DATA_INIT(x) (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_DATA_INIT_of(x) (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_DATA_INIT_bf 0, 19, 16
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_DATA_INIT_msk (0xf)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_DATA_INIT_shf (16)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU2(x)             (((x) & 0xf) << 12)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU2_of(x)          (((x) >> 12) & 0xf)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU2_bf           0, 15, 12
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU2_msk          (0xf)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_RFU2_shf          (12)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_MAX_PKT_INIT(x) (((x) & 0x3f) << 6)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_MAX_PKT_INIT_of(x) (((x) >> 6) & 0x3f)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_MAX_PKT_INIT_bf 0, 11, 6
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_MAX_PKT_INIT_msk (0x3f)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_MAX_PKT_INIT_shf (6)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_PKT_INIT(x) (((x) & 0x3f) << 0)
#define   NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_PKT_INIT_of(x) (((x) >> 0) & 0x3f)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_PKT_INIT_bf 0, 5, 0
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_PKT_INIT_msk (0x3f)
#define     NFP_MAC_CSR_TX_MPB_CREDIT_INIT_TX_MPB_CREDIT_PKT_INIT_shf (0)


/*
 * Register: IgBufferCreditPoolCount
 *   [31]      IgBufferLinklistReady
 *   [29:16]   IgBufferCreditCount1
 *   [13:0]    IgBufferCreditCount
 *
 * Name(s):
 * <base>.IgBufferCreditPoolCount
 */
#define NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT            0x00a0
#define   NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_LINKLIST_READY (1 << 31)
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_LINKLIST_READY_bf 0, 31, 31
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_LINKLIST_READY_msk (0x1)
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_LINKLIST_READY_bit (31)
#define   NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT1(x) (((x) & 0x3fff) << 16)
#define   NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT1_of(x) (((x) >> 16) & 0x3fff)
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT1_bf 0, 29, 16
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT1_msk (0x3fff)
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT1_shf (16)
#define   NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT(x) (((x) & 0x3fff) << 0)
#define   NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT_of(x) (((x) >> 0) & 0x3fff)
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT_bf 0, 13, 0
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT_msk (0x3fff)
#define     NFP_MAC_CSR_IG_BUFFER_CREDIT_POOL_COUNT_IG_BUFFER_CREDIT_COUNT_shf (0)


/*
 * Register: RxMpbCreditInit
 *   [31:30]   Rfu2
 *   [29:16]   RxMpbCreditDataInit
 *   [15:14]   Rfu
 *   [13:0]    RxMpbCreditBufInit
 *
 * Name(s):
 * <base>.RxMpbCreditInit
 */
#define NFP_MAC_CSR_RX_MPB_CREDIT_INIT                     0x00a4
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU2(x)             (((x) & 3) << 30)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU2_of(x)          (((x) >> 30) & 3)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU2_bf           0, 31, 30
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU2_msk          (0x3)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU2_shf          (30)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_DATA_INIT(x) (((x) & 0x3fff) << 16)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_DATA_INIT_of(x) (((x) >> 16) & 0x3fff)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_DATA_INIT_bf 0, 29, 16
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_DATA_INIT_msk (0x3fff)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_DATA_INIT_shf (16)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU(x)              (((x) & 3) << 14)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU_of(x)           (((x) >> 14) & 3)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU_bf            0, 15, 14
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU_msk           (0x3)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RFU_shf           (14)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_BUF_INIT(x) (((x) & 0x3fff) << 0)
#define   NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_BUF_INIT_of(x) (((x) >> 0) & 0x3fff)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_BUF_INIT_bf 0, 13, 0
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_BUF_INIT_msk (0x3fff)
#define     NFP_MAC_CSR_RX_MPB_CREDIT_INIT_RX_MPB_CREDIT_BUF_INIT_shf (0)


/*
 * Register: TDMRateCreditInit
 *   [31:24]   TDM100GECreditInit
 *   [23:16]   TDM40GECreditInit
 *   [15:8]    TDM10GECreditInit
 *   [7:0]     TDM1GECreditInit
 *
 * Name(s):
 * <base>.MacTdmRateCreditInit
 */
#define NFP_MAC_CSR_TDM_RATE_CREDIT_INIT                   0x00a8
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_100GE_CREDIT_INIT(x) (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_100GE_CREDIT_INIT_of(x) (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_100GE_CREDIT_INIT_bf 0, 31, 24
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_100GE_CREDIT_INIT_msk (0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_100GE_CREDIT_INIT_shf (24)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_40GE_CREDIT_INIT(x) (((x) & 0xff) << 16)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_40GE_CREDIT_INIT_of(x) (((x) >> 16) & 0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_40GE_CREDIT_INIT_bf 0, 23, 16
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_40GE_CREDIT_INIT_msk (0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_40GE_CREDIT_INIT_shf (16)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_10GE_CREDIT_INIT(x) (((x) & 0xff) << 8)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_10GE_CREDIT_INIT_of(x) (((x) >> 8) & 0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_10GE_CREDIT_INIT_bf 0, 15, 8
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_10GE_CREDIT_INIT_msk (0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_10GE_CREDIT_INIT_shf (8)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_1GE_CREDIT_INIT(x) (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_1GE_CREDIT_INIT_of(x) (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_1GE_CREDIT_INIT_bf 0, 7, 0
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_1GE_CREDIT_INIT_msk (0xff)
#define     NFP_MAC_CSR_TDM_RATE_CREDIT_INIT_TDM_1GE_CREDIT_INIT_shf (0)


/*
 * Register: MacInterruptErrStatus0
 *   [31:0]    MacInterruptErrStatus1
 *
 * Name(s):
 * <base>.MacInterruptErrStatus0
 */
#define NFP_MAC_CSR_MAC_INTR_ERR_STATUS_0                  0x00ac
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_0_MAC_INTERRUPT_ERR_STATUS_1(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_0_MAC_INTERRUPT_ERR_STATUS_1_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_0_MAC_INTERRUPT_ERR_STATUS_1_bf 0, 31, 0
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_0_MAC_INTERRUPT_ERR_STATUS_1_msk (0xffffffff)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_0_MAC_INTERRUPT_ERR_STATUS_1_shf (0)


/*
 * Register: MacInterruptErrStatus1
 *   [31]      MacRxPfcChangeInt
 *   [30]      MacTxPfcChangeInt
 *   [29:24]   Rfu
 *   [23:12]   MacLinTrainingInthy1
 *   [11:0]    MacLinTrainingInthy0
 *
 * Name(s):
 * <base>.MacInterruptErrStatus1
 */
#define NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1                  0x00b0
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_RX_PFC_CHANGE_INT (1 << 31)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_RX_PFC_CHANGE_INT_bf 0, 31, 31
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_RX_PFC_CHANGE_INT_msk (0x1)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_RX_PFC_CHANGE_INT_bit (31)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_TX_PFC_CHANGE_INT (1 << 30)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_TX_PFC_CHANGE_INT_bf 0, 30, 30
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_TX_PFC_CHANGE_INT_msk (0x1)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_TX_PFC_CHANGE_INT_bit (30)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_RFU(x)           (((x) & 0x3f) << 24)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_RFU_of(x)        (((x) >> 24) & 0x3f)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_RFU_bf         0, 29, 24
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_RFU_msk        (0x3f)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_RFU_shf        (24)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY1(x) (((x) & 0xfff) << 12)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY1_of(x) (((x) >> 12) & 0xfff)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY1_bf 0, 23, 12
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY1_msk (0xfff)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY1_shf (12)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY0(x) (((x) & 0xfff) << 0)
#define   NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY0_of(x) (((x) >> 0) & 0xfff)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY0_bf 0, 11, 0
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY0_msk (0xfff)
#define     NFP_MAC_CSR_MAC_INTR_ERR_STATUS_1_MAC_LINKT_TRAINING_INT_HY0_shf (0)


/*
 * Register: MacIgEqStatus
 *   [31:26]   IgEqStatusRfu
 *   [25]      Purge
 *   [24:20]   PurgePort
 *   [19:0]    IgEqWt4Eop
 *
 * Name(s):
 * <base>.MacIgEqStatus
 */
#define NFP_MAC_CSR_MAC_IG_EQ_STATUS                       0x00b4
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_STATUS_RFU(x)   (((x) & 0x3f) << 26)
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_STATUS_RFU_of(x) (((x) >> 26) & 0x3f)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_STATUS_RFU_bf 0, 31, 26
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_STATUS_RFU_msk (0x3f)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_STATUS_RFU_shf (26)
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE                 (1 << 25)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_bf            0, 25, 25
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_msk           (0x1)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_bit           (25)
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_PORT(x)         (((x) & 0x1f) << 20)
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_PORT_of(x)      (((x) >> 20) & 0x1f)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_PORT_bf       0, 24, 20
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_PORT_msk      (0x1f)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_PURGE_PORT_shf      (20)
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_WT4EOP(x)       (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_WT4EOP_of(x)    (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_WT4EOP_bf     0, 19, 0
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_WT4EOP_msk    (0xfffff)
#define     NFP_MAC_CSR_MAC_IG_EQ_STATUS_IG_EQ_WT4EOP_shf    (0)


/*
 * Register: MacHyd4Ctrl
 *   [31:28]   MacHydPcsSd_N2
 *   [27:24]   MacHydFecErrEna
 *   [23:20]   MacHydRfu20
 *   [19:16]   MacHydFecEna
 *   [15]      MacHydPcsRxlauiEna2
 *   [14]      MacHydPcsRxlauiEna0
 *   [13]      MacHydPcsFec91SingleLaneEna2
 *   [12]      MacHydPcsFec91SingleLaneEna0
 *   [11]      MacHydRFU11
 *   [10]      MacHydPcs0Mode40Ena
 *   [9:6]     MacHydPcsFec91Ena
 *   [5]       MacHydRFU5
 *   [4]       MacHydCGEna
 *   [3:0]     MacHydSGEna
 *
 * Name(s):
 * <base>.MacHyd1Ctrl
 */
#define NFP_MAC_CSR_MAC_HYD1_CTRL                          0x00b8
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_SD_N2(x)     (((x) & 0xf) << 28)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_SD_N2_of(x)  (((x) >> 28) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_SD_N2_bf   0, 31, 28
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_SD_N2_msk  (0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_SD_N2_shf  (28)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ERR_ENA(x)   (((x) & 0xf) << 24)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ERR_ENA_of(x) (((x) >> 24) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ERR_ENA_bf 0, 27, 24
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ERR_ENA_msk (0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ERR_ENA_shf (24)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU_20(x)        (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU_20_of(x)     (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU_20_bf      0, 23, 20
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU_20_msk     (0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU_20_shf     (20)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ENA(x)       (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ENA_of(x)    (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ENA_bf     0, 19, 16
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ENA_msk    (0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_FEC_ENA_shf    (16)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA2  (1 << 15)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA2_bf 0, 15, 15
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA2_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA2_bit (15)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA0  (1 << 14)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA0_bf 0, 14, 14
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA0_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_RXLAUI_ENA0_bit (14)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_2 (1 << 13)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_2_bf 0, 13, 13
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_2_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_2_bit (13)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_0 (1 << 12)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_0_bf 0, 12, 12
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_0_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_SINGLE_LANE_ENA_0_bit (12)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU11            (1 << 11)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU11_bf       0, 11, 11
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU11_msk      (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU11_bit      (11)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS0_MODE40_ENA  (1 << 10)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS0_MODE40_ENA_bf 0, 10, 10
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS0_MODE40_ENA_msk (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS0_MODE40_ENA_bit (10)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_ENA(x) (((x) & 0xf) << 6)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_ENA_of(x) (((x) >> 6) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_ENA_bf 0, 9, 6
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_ENA_msk (0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_PCS_FEC91_ENA_shf (6)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU5             (1 << 5)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU5_bf        0, 5, 5
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU5_msk       (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_RFU5_bit       (5)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_CG_ENA           (1 << 4)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_CG_ENA_bf      0, 4, 4
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_CG_ENA_msk     (0x1)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_CG_ENA_bit     (4)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_SG_ENA(x)        (((x) & 0xf) << 0)
#define   NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_SG_ENA_of(x)     (((x) >> 0) & 0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_SG_ENA_bf      0, 3, 0
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_SG_ENA_msk     (0xf)
#define     NFP_MAC_CSR_MAC_HYD1_CTRL_MAC_HYD_SG_ENA_shf     (0)


/*
 * Register: MacLiveStatus0
 *   [31:0]    MacLiveStatus0
 *
 * Name(s):
 * <base>.MacLiveStatus0
 */
#define NFP_MAC_CSR_MAC_LIVE_STATUS_0                      0x00bc
#define   NFP_MAC_CSR_MAC_LIVE_STATUS_0_MAC_LIVE_STATUS_0(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_LIVE_STATUS_0_MAC_LIVE_STATUS_0_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_LIVE_STATUS_0_MAC_LIVE_STATUS_0_bf 0, 31, 0
#define     NFP_MAC_CSR_MAC_LIVE_STATUS_0_MAC_LIVE_STATUS_0_msk (0xffffffff)
#define     NFP_MAC_CSR_MAC_LIVE_STATUS_0_MAC_LIVE_STATUS_0_shf (0)


/*
 * Register: MacLiveStatus1
 *   [31:0]    MacLiveStatus1
 *
 * Name(s):
 * <base>.MacLiveStatus1
 */
#define NFP_MAC_CSR_MAC_LIVE_STATUS_1                      0x00c0
#define   NFP_MAC_CSR_MAC_LIVE_STATUS_1_MAC_LIVE_STATUS_1(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_LIVE_STATUS_1_MAC_LIVE_STATUS_1_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_LIVE_STATUS_1_MAC_LIVE_STATUS_1_bf 0, 31, 0
#define     NFP_MAC_CSR_MAC_LIVE_STATUS_1_MAC_LIVE_STATUS_1_msk (0xffffffff)
#define     NFP_MAC_CSR_MAC_LIVE_STATUS_1_MAC_LIVE_STATUS_1_shf (0)


/*
 * Register: MacChanRdAddr
 *   [31:23]   Rfu1
 *   [22:16]   IgChanRdAddr
 *   [15:7]    Rfu0
 *   [6:0]     EgChanRdAddr
 *
 * Name(s):
 * <base>.MacChanRdAddr
 */
#define NFP_MAC_CSR_MAC_CHAN_RD_ADDR                       0x00c4
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU1(x)               (((x) & 0x1ff) << 23)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU1_of(x)            (((x) >> 23) & 0x1ff)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU1_bf             0, 31, 23
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU1_msk            (0x1ff)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU1_shf            (23)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_IG_CHAN_RD_ADDR(x)    (((x) & 0x7f) << 16)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_IG_CHAN_RD_ADDR_of(x) (((x) >> 16) & 0x7f)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_IG_CHAN_RD_ADDR_bf  0, 22, 16
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_IG_CHAN_RD_ADDR_msk (0x7f)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_IG_CHAN_RD_ADDR_shf (16)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU0(x)               (((x) & 0x1ff) << 7)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU0_of(x)            (((x) >> 7) & 0x1ff)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU0_bf             0, 15, 7
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU0_msk            (0x1ff)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_RFU0_shf            (7)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_EG_CHAN_RD_ADDR(x)    (((x) & 0x7f) << 0)
#define   NFP_MAC_CSR_MAC_CHAN_RD_ADDR_EG_CHAN_RD_ADDR_of(x) (((x) >> 0) & 0x7f)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_EG_CHAN_RD_ADDR_bf  0, 6, 0
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_EG_CHAN_RD_ADDR_msk (0x7f)
#define     NFP_MAC_CSR_MAC_CHAN_RD_ADDR_EG_CHAN_RD_ADDR_shf (0)


/*
 * Register: MacChanBufCount
 *   [31:27]   Rfu1
 *   [26:16]   IgChanRdBufCnt
 *   [15:11]   Rfu0
 *   [10:0]    EgChanRdBufCnt
 *
 * Name(s):
 * <base>.MacChanBufCount
 */
#define NFP_MAC_CSR_MAC_CHAN_BUF_COUNT                     0x00c8
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU1(x)             (((x) & 0x1f) << 27)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU1_of(x)          (((x) >> 27) & 0x1f)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU1_bf           0, 31, 27
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU1_msk          (0x1f)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU1_shf          (27)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_IG_CHAN_RD_BUF_CNT(x) (((x) & 0x7ff) << 16)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_IG_CHAN_RD_BUF_CNT_of(x) (((x) >> 16) & 0x7ff)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_IG_CHAN_RD_BUF_CNT_bf 0, 26, 16
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_IG_CHAN_RD_BUF_CNT_msk (0x7ff)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_IG_CHAN_RD_BUF_CNT_shf (16)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU0(x)             (((x) & 0x1f) << 11)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU0_of(x)          (((x) >> 11) & 0x1f)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU0_bf           0, 15, 11
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU0_msk          (0x1f)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_RFU0_shf          (11)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_EG_CHAN_RD_BUF_CNT(x) (((x) & 0x7ff) << 0)
#define   NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_EG_CHAN_RD_BUF_CNT_of(x) (((x) >> 0) & 0x7ff)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_EG_CHAN_RD_BUF_CNT_bf 0, 10, 0
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_EG_CHAN_RD_BUF_CNT_msk (0x7ff)
#define     NFP_MAC_CSR_MAC_CHAN_BUF_COUNT_EG_CHAN_RD_BUF_CNT_shf (0)


/*
 * Register: PauseWaterMark
 *   [31:28]   PWMResv1
 *   [27:16]   PauseWaterMark1
 *   [15:12]   PWMResv0
 *   [11:0]    PauseWaterMark0
 *
 * Name(s):
 * <base>.PauseWaterMark0...
 */
#define NFP_MAC_CSR_PAUSE_WATERMARK(x)                     (0x00cc + ((x) * 0x4))
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV1(x)           (((x) & 0xf) << 28)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV1_of(x)        (((x) >> 28) & 0xf)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV1_bf         0, 31, 28
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV1_msk        (0xf)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV1_shf        (28)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK1(x)    (((x) & 0xfff) << 16)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK1_of(x) (((x) >> 16) & 0xfff)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK1_bf  0, 27, 16
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK1_msk (0xfff)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK1_shf (16)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV0(x)           (((x) & 0xf) << 12)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV0_of(x)        (((x) >> 12) & 0xf)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV0_bf         0, 15, 12
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV0_msk        (0xf)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PWM_RESV0_shf        (12)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK0(x)    (((x) & 0xfff) << 0)
#define   NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK0_of(x) (((x) >> 0) & 0xfff)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK0_bf  0, 11, 0
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK0_msk (0xfff)
#define     NFP_MAC_CSR_PAUSE_WATERMARK_PAUSE_WATERMARK0_shf (0)


/*
 * Register: BufferCounterRw
 *   [31:24]   CounterAddr
 *   [23:22]   Rfu2
 *   [21]      CounterRdBusy
 *   [20:0]    Rfu
 *
 * Name(s):
 * <base>.IgChanUsedBufferCreditsRw
 */
#define NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW         0x01d4
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_ADDR(x) (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_ADDR_of(x) (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_ADDR_bf 0, 31, 24
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_ADDR_msk (0xff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_ADDR_shf (24)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU2(x) (((x) & 3) << 22)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU2_of(x) (((x) >> 22) & 3)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU2_bf 0, 23, 22
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU2_msk (0x3)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU2_shf (22)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_RD_BUSY (1 << 21)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_RD_BUSY_bf 0, 21, 21
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_RD_BUSY_msk (0x1)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_COUNTER_RD_BUSY_bit (21)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU(x)  (((x) & 0x1fffff) << 0)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU_of(x) (((x) >> 0) & 0x1fffff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU_bf 0, 20, 0
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU_msk (0x1fffff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RW_RFU_shf (0)


/*
 * Register: BufferCounterRdData
 *   [31:24]   CounterAddr
 *   [21]      BufferCounterRdDataValid
 *   [15:0]    CounterRdData
 *
 * Name(s):
 * <base>.IgChanUsedBufferCreditsRdData
 */
#define NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA    0x01d8
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_ADDR(x) (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_ADDR_of(x) (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_ADDR_bf 0, 31, 24
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_ADDR_msk (0xff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_ADDR_shf (24)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_BUFFER_COUNTER_RD_DATA_VALID (1 << 21)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_BUFFER_COUNTER_RD_DATA_VALID_bf 0, 21, 21
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_BUFFER_COUNTER_RD_DATA_VALID_msk (0x1)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_BUFFER_COUNTER_RD_DATA_VALID_bit (21)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_RD_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_RD_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_RD_DATA_bf 0, 15, 0
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_RD_DATA_msk (0xffff)
#define     NFP_MAC_CSR_IG_CHAN_USED_BUFFER_CREDITS_RD_DATA_COUNTER_RD_DATA_shf (0)


/*
 * Register: IgPrependEn
 *   [31:26]   Rfu
 *   [25:24]   PrependLk
 *   [23:22]   PrependEn11
 *   [21:20]   PrependEn10
 *   [19:18]   PrependEn9
 *   [17:16]   PrependEn8
 *   [15:14]   PrependEn7
 *   [13:12]   PrependEn6
 *   [11:10]   PrependEn5
 *   [9:8]     PrependEn4
 *   [7:6]     PrependEn3
 *   [5:4]     PrependEn2
 *   [3:2]     PrependEn1
 *   [1:0]     PrependEn0
 *
 * Name(s):
 * <base>.IgPortPrependEn0 <base>.IgPortPrependEn1
 */
#define NFP_MAC_CSR_IG_PORT_PREPEND_EN0                    0x01dc
#define NFP_MAC_CSR_IG_PORT_PREPEND_EN1                    0x01e0
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_RFU(x)             (((x) & 0x3f) << 26)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_RFU_of(x)          (((x) >> 26) & 0x3f)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_RFU_bf           0, 31, 26
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_RFU_msk          (0x3f)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_RFU_shf          (26)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_LK(x)      (((x) & 3) << 24)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_LK_of(x)   (((x) >> 24) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_LK_bf    0, 25, 24
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_LK_msk   (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_LK_shf   (24)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN11(x)    (((x) & 3) << 22)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN11_of(x) (((x) >> 22) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN11_bf  0, 23, 22
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN11_msk (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN11_shf (22)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN10(x)    (((x) & 3) << 20)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN10_of(x) (((x) >> 20) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN10_bf  0, 21, 20
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN10_msk (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN10_shf (20)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN9(x)     (((x) & 3) << 18)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN9_of(x)  (((x) >> 18) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN9_bf   0, 19, 18
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN9_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN9_shf  (18)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN8(x)     (((x) & 3) << 16)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN8_of(x)  (((x) >> 16) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN8_bf   0, 17, 16
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN8_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN8_shf  (16)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN7(x)     (((x) & 3) << 14)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN7_of(x)  (((x) >> 14) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN7_bf   0, 15, 14
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN7_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN7_shf  (14)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN6(x)     (((x) & 3) << 12)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN6_of(x)  (((x) >> 12) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN6_bf   0, 13, 12
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN6_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN6_shf  (12)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN5(x)     (((x) & 3) << 10)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN5_of(x)  (((x) >> 10) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN5_bf   0, 11, 10
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN5_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN5_shf  (10)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN4(x)     (((x) & 3) << 8)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN4_of(x)  (((x) >> 8) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN4_bf   0, 9, 8
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN4_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN4_shf  (8)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN3(x)     (((x) & 3) << 6)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN3_of(x)  (((x) >> 6) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN3_bf   0, 7, 6
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN3_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN3_shf  (6)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN2(x)     (((x) & 3) << 4)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN2_of(x)  (((x) >> 4) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN2_bf   0, 5, 4
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN2_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN2_shf  (4)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN1(x)     (((x) & 3) << 2)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN1_of(x)  (((x) >> 2) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN1_bf   0, 3, 2
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN1_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN1_shf  (2)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0(x)     (((x) & 3) << 0)
#define   NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_of(x)  (((x) >> 0) & 3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_No_Prepend (0)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_Prepend_CHK (1)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_Prepend_TS (2)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_Prepend_TS_CHK (3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_bf   0, 1, 0
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_msk  (0x3)
#define     NFP_MAC_CSR_IG_PORT_PREPEND_EN0_PREPEND_EN0_shf  (0)


/*
 * Register: IgL4TotalSel
 *   [19:0]    L4OverallEn
 *
 * Name(s):
 * <base>.IgPortL4ChksumSel
 */
#define NFP_MAC_CSR_IG_PORT_L4_CHKSUM_SEL                  0x01e4
#define   NFP_MAC_CSR_IG_PORT_L4_CHKSUM_SEL_L4_OVERALL_EN(x) (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_IG_PORT_L4_CHKSUM_SEL_L4_OVERALL_EN_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_IG_PORT_L4_CHKSUM_SEL_L4_OVERALL_EN_bf 0, 19, 0
#define     NFP_MAC_CSR_IG_PORT_L4_CHKSUM_SEL_L4_OVERALL_EN_msk (0xfffff)
#define     NFP_MAC_CSR_IG_PORT_L4_CHKSUM_SEL_L4_OVERALL_EN_shf (0)


/*
 * Register: VlanMatchReg
 *   [31:16]   VlanMask
 *   [15:0]    VlanMatch
 *
 * Name(s):
 * <base>.EgVlanMatchReg0 <base>.IgVlanMatchReg0
 */
#define NFP_MAC_CSR_EG_VLAN_MATCH_REG0                     0x01e8
#define NFP_MAC_CSR_IG_VLAN_MATCH_REG0                     0x01f0
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MASK(x)        (((x) & 0xffff) << 16)
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MASK_of(x)     (((x) >> 16) & 0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MASK_bf      0, 31, 16
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MASK_msk     (0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MASK_shf     (16)
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MATCH(x)       (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MATCH_of(x)    (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MATCH_bf     0, 15, 0
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MATCH_msk    (0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG0_VLAN_MATCH_shf    (0)


/*
 * Register: VlanMatchReg1
 *   [31:16]   VlanMask1
 *   [15:0]    VlanMatch1
 *
 * Name(s):
 * <base>.EgVlanMatchReg1 <base>.IgVlanMatchReg1
 */
#define NFP_MAC_CSR_EG_VLAN_MATCH_REG1                     0x01ec
#define NFP_MAC_CSR_IG_VLAN_MATCH_REG1                     0x01f4
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MASK1(x)       (((x) & 0xffff) << 16)
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MASK1_of(x)    (((x) >> 16) & 0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MASK1_bf     0, 31, 16
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MASK1_msk    (0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MASK1_shf    (16)
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MATCH1(x)      (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MATCH1_of(x)   (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MATCH1_bf    0, 15, 0
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MATCH1_msk   (0xffff)
#define     NFP_MAC_CSR_EG_VLAN_MATCH_REG1_VLAN_MATCH1_shf   (0)


/*
 * Register: MiscStatusCtrl
 *   [1]       EgLLMemMbeLock
 *   [0]       IgLLMemMbeLock
 *
 * Name(s):
 * <base>.MiscStatusCtrl
 */
#define NFP_MAC_CSR_MISC_STATUS_CTRL                       0x01f8
#define   NFP_MAC_CSR_MISC_STATUS_CTRL_EG_LL_MEM_MBE_LOCK    (1 << 1)
#define     NFP_MAC_CSR_MISC_STATUS_CTRL_EG_LL_MEM_MBE_LOCK_bf 0, 1, 1
#define     NFP_MAC_CSR_MISC_STATUS_CTRL_EG_LL_MEM_MBE_LOCK_msk (0x1)
#define     NFP_MAC_CSR_MISC_STATUS_CTRL_EG_LL_MEM_MBE_LOCK_bit (1)
#define   NFP_MAC_CSR_MISC_STATUS_CTRL_IG_LL_MEM_MBE_LOCK    (1 << 0)
#define     NFP_MAC_CSR_MISC_STATUS_CTRL_IG_LL_MEM_MBE_LOCK_bf 0, 0, 0
#define     NFP_MAC_CSR_MISC_STATUS_CTRL_IG_LL_MEM_MBE_LOCK_msk (0x1)
#define     NFP_MAC_CSR_MISC_STATUS_CTRL_IG_LL_MEM_MBE_LOCK_bit (0)


/*
 * Register: EgCmdPrependEn
 *   [31:0]    EgCmdPrependEn
 *
 * Name(s):
 * <base>.EgCmdPrependEn0Lo <base>.EgCmdPrependEn0Hi <base>.EgCmdPrependEn1Lo
 * <base>.EgCmdPrependEn1Hi
 */
#define NFP_MAC_CSR_EG_CMD_PREPEND_EN0_LO                  0x0200
#define NFP_MAC_CSR_EG_CMD_PREPEND_EN0_HI                  0x0204
#define NFP_MAC_CSR_EG_CMD_PREPEND_EN1_LO                  0x0208
#define NFP_MAC_CSR_EG_CMD_PREPEND_EN1_HI                  0x020c
#define   NFP_MAC_CSR_EG_CMD_PREPEND_EN0_LO_EG_CMD_PREPEND_EN(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_EG_CMD_PREPEND_EN0_LO_EG_CMD_PREPEND_EN_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_EG_CMD_PREPEND_EN0_LO_EG_CMD_PREPEND_EN_bf 0, 31, 0
#define     NFP_MAC_CSR_EG_CMD_PREPEND_EN0_LO_EG_CMD_PREPEND_EN_msk (0xffffffff)
#define     NFP_MAC_CSR_EG_CMD_PREPEND_EN0_LO_EG_CMD_PREPEND_EN_shf (0)


/*
 * Register: PfcTxEn
 *   [19:0]    PortPfcTxEn
 *
 * Name(s):
 * <base>.PfcTxEn
 */
#define NFP_MAC_CSR_PFC_TX_EN                              0x0210
#define   NFP_MAC_CSR_PFC_TX_EN_PORT_PFC_TX_EN(x)            (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_PFC_TX_EN_PORT_PFC_TX_EN_of(x)         (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_PFC_TX_EN_PORT_PFC_TX_EN_bf          0, 19, 0
#define     NFP_MAC_CSR_PFC_TX_EN_PORT_PFC_TX_EN_msk         (0xfffff)
#define     NFP_MAC_CSR_PFC_TX_EN_PORT_PFC_TX_EN_shf         (0)


/*
 * Register: EgTxStopEn
 *   [19:0]    PortEgTxStopEn
 *
 * Name(s):
 * <base>.EgTxStopEn
 */
#define NFP_MAC_CSR_EG_TX_STOP_EN                          0x0214
#define   NFP_MAC_CSR_EG_TX_STOP_EN_PORT_EG_TX_STOP_EN(x)    (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_EG_TX_STOP_EN_PORT_EG_TX_STOP_EN_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_EG_TX_STOP_EN_PORT_EG_TX_STOP_EN_bf  0, 19, 0
#define     NFP_MAC_CSR_EG_TX_STOP_EN_PORT_EG_TX_STOP_EN_msk (0xfffff)
#define     NFP_MAC_CSR_EG_TX_STOP_EN_PORT_EG_TX_STOP_EN_shf (0)


/*
 * Register: EgTxStopGpioSel
 *   [24]      EgTxStopGpioInv
 *   [23:20]   EgTxStopGpioEn
 *   [19:15]   EgTxStopGpioPortSel3
 *   [14:10]   EgTxStopGpioPortSel2
 *   [9:5]     EgTxStopGpioPortSel1
 *   [4:0]     EgTxStopGpioPortSel0
 *
 * Name(s):
 * <base>.EgTxStopGpioSel
 */
#define NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL                    0x0218
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_INV (1 << 24)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_INV_bf 0, 24, 24
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_INV_msk (0x1)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_INV_bit (24)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_EN(x) (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_EN_of(x) (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_EN_bf 0, 23, 20
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_EN_msk (0xf)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_EN_shf (20)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_3(x) (((x) & 0x1f) << 15)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_3_of(x) (((x) >> 15) & 0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_3_bf 0, 19, 15
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_3_msk (0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_3_shf (15)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_2(x) (((x) & 0x1f) << 10)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_2_of(x) (((x) >> 10) & 0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_2_bf 0, 14, 10
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_2_msk (0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_2_shf (10)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_1(x) (((x) & 0x1f) << 5)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_1_of(x) (((x) >> 5) & 0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_1_bf 0, 9, 5
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_1_msk (0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_1_shf (5)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_0(x) (((x) & 0x1f) << 0)
#define   NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_0_of(x) (((x) >> 0) & 0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_0_bf 0, 4, 0
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_0_msk (0x1f)
#define     NFP_MAC_CSR_EG_TX_STOP_GPIO_SEL_EG_TX_STOP_GPIO_PORT_SEL_0_shf (0)


/*
 * Register: IgNbiPortXoff
 *   [19:0]    Xoff
 *
 * Name(s):
 * <base>.IgNbiPortXoff
 */
#define NFP_MAC_CSR_IG_NBI_PORT_XOFF                       0x0220
#define   NFP_MAC_CSR_IG_NBI_PORT_XOFF_XOFF(x)               (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_IG_NBI_PORT_XOFF_XOFF_of(x)            (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_IG_NBI_PORT_XOFF_XOFF_bf             0, 19, 0
#define     NFP_MAC_CSR_IG_NBI_PORT_XOFF_XOFF_msk            (0xfffff)
#define     NFP_MAC_CSR_IG_NBI_PORT_XOFF_XOFF_shf            (0)


/*
 * Register: FecStatus
 *   [20:14]   FecUnCorErr
 *   [13:7]    FecCorErr
 *   [6:0]     FecLocked
 *
 * Name(s):
 * <base>.FecStatus0 <base>.FecStatus1
 */
#define NFP_MAC_CSR_FEC_STATUS_0                           0x0228
#define NFP_MAC_CSR_FEC_STATUS_1                           0x022c
#define   NFP_MAC_CSR_FEC_STATUS_0_FEC_UN_COR_ERR(x)         (((x) & 0x7f) << 14)
#define   NFP_MAC_CSR_FEC_STATUS_0_FEC_UN_COR_ERR_of(x)      (((x) >> 14) & 0x7f)
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_UN_COR_ERR_bf       0, 20, 14
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_UN_COR_ERR_msk      (0x7f)
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_UN_COR_ERR_shf      (14)
#define   NFP_MAC_CSR_FEC_STATUS_0_FEC_COR_ERR(x)            (((x) & 0x7f) << 7)
#define   NFP_MAC_CSR_FEC_STATUS_0_FEC_COR_ERR_of(x)         (((x) >> 7) & 0x7f)
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_COR_ERR_bf          0, 13, 7
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_COR_ERR_msk         (0x7f)
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_COR_ERR_shf         (7)
#define   NFP_MAC_CSR_FEC_STATUS_0_FEC_LOCKED(x)             (((x) & 0x7f) << 0)
#define   NFP_MAC_CSR_FEC_STATUS_0_FEC_LOCKED_of(x)          (((x) >> 0) & 0x7f)
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_LOCKED_bf           0, 6, 0
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_LOCKED_msk          (0x7f)
#define     NFP_MAC_CSR_FEC_STATUS_0_FEC_LOCKED_shf          (0)


/*
 * Register: MacEgPortRR
 *   [19:0]    EgPortRR
 *
 * Name(s):
 * <base>.MacEgPortRR
 */
#define NFP_MAC_CSR_MAC_EG_PORT_RR                         0x0264
#define   NFP_MAC_CSR_MAC_EG_PORT_RR_EG_PORT_RR(x)           (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_MAC_EG_PORT_RR_EG_PORT_RR_of(x)        (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_MAC_EG_PORT_RR_EG_PORT_RR_bf         0, 19, 0
#define     NFP_MAC_CSR_MAC_EG_PORT_RR_EG_PORT_RR_msk        (0xfffff)
#define     NFP_MAC_CSR_MAC_EG_PORT_RR_EG_PORT_RR_shf        (0)


/*
 * Register: MacEqInh
 *   [25]      MacEqInhIlk1
 *   [24]      MacEqInhIlk0
 *   [23:20]   MacEqInhEthPortRfu
 *   [19:0]    MacEqInhEthPort
 *
 * Name(s):
 * <base>.MacEqInh
 */
#define NFP_MAC_CSR_EQ_INH                                 0x0278
#define   NFP_MAC_CSR_EQ_INH_ILK1                            (1 << 25)
#define     NFP_MAC_CSR_EQ_INH_ILK1_bf                       0, 25, 25
#define     NFP_MAC_CSR_EQ_INH_ILK1_msk                      (0x1)
#define     NFP_MAC_CSR_EQ_INH_ILK1_bit                      (25)
#define   NFP_MAC_CSR_EQ_INH_ILK0                            (1 << 24)
#define     NFP_MAC_CSR_EQ_INH_ILK0_bf                       0, 24, 24
#define     NFP_MAC_CSR_EQ_INH_ILK0_msk                      (0x1)
#define     NFP_MAC_CSR_EQ_INH_ILK0_bit                      (24)
#define   NFP_MAC_CSR_EQ_INH_ETH_PORT_RFU(x)                 (((x) & 0xf) << 20)
#define   NFP_MAC_CSR_EQ_INH_ETH_PORT_RFU_of(x)              (((x) >> 20) & 0xf)
#define     NFP_MAC_CSR_EQ_INH_ETH_PORT_RFU_bf               0, 23, 20
#define     NFP_MAC_CSR_EQ_INH_ETH_PORT_RFU_msk              (0xf)
#define     NFP_MAC_CSR_EQ_INH_ETH_PORT_RFU_shf              (20)
#define   NFP_MAC_CSR_EQ_INH_ETH_PORT(x)                     (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_EQ_INH_ETH_PORT_of(x)                  (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_EQ_INH_ETH_PORT_bf                   0, 19, 0
#define     NFP_MAC_CSR_EQ_INH_ETH_PORT_msk                  (0xfffff)
#define     NFP_MAC_CSR_EQ_INH_ETH_PORT_shf                  (0)


/*
 * Register: MacEqInhDone
 *   [19:0]    MacEqInhDoneEthPort
 *
 * Name(s):
 * <base>.MacEqInhDone
 */
#define NFP_MAC_CSR_EQ_INH_DONE                            0x027c
#define   NFP_MAC_CSR_EQ_INH_DONE_ETH_PORT(x)                (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_EQ_INH_DONE_ETH_PORT_of(x)             (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_EQ_INH_DONE_ETH_PORT_bf              0, 19, 0
#define     NFP_MAC_CSR_EQ_INH_DONE_ETH_PORT_msk             (0xfffff)
#define     NFP_MAC_CSR_EQ_INH_DONE_ETH_PORT_shf             (0)


/*
 * Register: MacHeadDropCounter
 *   [31:0]    MacHeadDropCounter
 *
 * Name(s):
 * <base>.MacHy0EthIgPktHeadDropCntr0... <base>.MacHy1EthIgPktHeadDropCntr0...
 */
#define NFP_MAC_CSR_MAC_HY0_ETH_IG_PKT_HEAD_DROP_CNTR_(x)  (0x0280 + ((x) * 0x4))
#define NFP_MAC_CSR_MAC_HY1_ETH_IG_PKT_HEAD_DROP_CNTR_(x)  (0x02a8 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_HY0_ETH_IG_PKT_HEAD_DROP_CNTR__MAC_HEAD_DROP_COUNTER(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_HY0_ETH_IG_PKT_HEAD_DROP_CNTR__MAC_HEAD_DROP_COUNTER_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_HY0_ETH_IG_PKT_HEAD_DROP_CNTR__MAC_HEAD_DROP_COUNTER_bf 0, 31, 0
#define     NFP_MAC_CSR_MAC_HY0_ETH_IG_PKT_HEAD_DROP_CNTR__MAC_HEAD_DROP_COUNTER_msk (0xffffffff)
#define     NFP_MAC_CSR_MAC_HY0_ETH_IG_PKT_HEAD_DROP_CNTR__MAC_HEAD_DROP_COUNTER_shf (0)


/*
 * Register: MacEthFifoIfErr
 *   [20]      RemLocFaultSticky
 *   [19:10]   EthTxIfOvr
 *   [9:0]     EthTxIfUnf
 *
 * Name(s):
 * <base>.MacEthFifoIfErr0 <base>.MacEthFifoIfErr1
 */
#define NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0                  0x0400
#define NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_1                  0x0404
#define   NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_REM_LOC_FAULT_STICKY (1 << 20)
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_REM_LOC_FAULT_STICKY_bf 0, 20, 20
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_REM_LOC_FAULT_STICKY_msk (0x1)
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_REM_LOC_FAULT_STICKY_bit (20)
#define   NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_OVR(x) (((x) & 0x3ff) << 10)
#define   NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_OVR_of(x) (((x) >> 10) & 0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_OVR_bf 0, 19, 10
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_OVR_msk (0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_OVR_shf (10)
#define   NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_UNF(x) (((x) & 0x3ff) << 0)
#define   NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_UNF_of(x) (((x) >> 0) & 0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_UNF_bf 0, 9, 0
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_UNF_msk (0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_FIFO_IF_ERR_0_ETH_TX_IF_UNF_shf (0)


/*
 * Register: MacEthAnStatus
 *   [19:10]   EthAnInt
 *   [9:0]     EthAnDone
 *
 * Name(s):
 * <base>.MacEthAnStatus0 <base>.MacEthAnStatus1
 */
#define NFP_MAC_CSR_MAC_ETH_AN_STATUS_0                    0x0408
#define NFP_MAC_CSR_MAC_ETH_AN_STATUS_1                    0x040c
#define   NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_INT(x)      (((x) & 0x3ff) << 10)
#define   NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_INT_of(x)   (((x) >> 10) & 0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_INT_bf    0, 19, 10
#define     NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_INT_msk   (0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_INT_shf   (10)
#define   NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_DONE(x)     (((x) & 0x3ff) << 0)
#define   NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_DONE_of(x)  (((x) >> 0) & 0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_DONE_bf   0, 9, 0
#define     NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_DONE_msk  (0x3ff)
#define     NFP_MAC_CSR_MAC_ETH_AN_STATUS_0_ETH_AN_DONE_shf  (0)


/*
 * Register: MacHiBerStatus
 *   [19:0]    HiBer
 *
 * Name(s):
 * <base>.MacHiBerStatus
 */
#define NFP_MAC_CSR_MAC_HI_BER_STATUS                      0x0414
#define   NFP_MAC_CSR_MAC_HI_BER_STATUS_HI_BER(x)            (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_MAC_HI_BER_STATUS_HI_BER_of(x)         (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_MAC_HI_BER_STATUS_HI_BER_bf          0, 19, 0
#define     NFP_MAC_CSR_MAC_HI_BER_STATUS_HI_BER_msk         (0xfffff)
#define     NFP_MAC_CSR_MAC_HI_BER_STATUS_HI_BER_shf         (0)


/*
 * Register: MacTxPauseStateChange
 *   [19:0]    TxPauseStateChange
 *
 * Name(s):
 * <base>.MacTxPauseStateChange
 */
#define NFP_MAC_CSR_MAC_TX_PAUSE_STATE_CHANGE              0x0418
#define   NFP_MAC_CSR_MAC_TX_PAUSE_STATE_CHANGE_TX_PAUSE_STATE_CHANGE(x) (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_MAC_TX_PAUSE_STATE_CHANGE_TX_PAUSE_STATE_CHANGE_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_MAC_TX_PAUSE_STATE_CHANGE_TX_PAUSE_STATE_CHANGE_bf 0, 19, 0
#define     NFP_MAC_CSR_MAC_TX_PAUSE_STATE_CHANGE_TX_PAUSE_STATE_CHANGE_msk (0xfffff)
#define     NFP_MAC_CSR_MAC_TX_PAUSE_STATE_CHANGE_TX_PAUSE_STATE_CHANGE_shf (0)


/*
 * Register: MacRxPauseStateChange
 *   [19:0]    RxPauseStateChange
 *
 * Name(s):
 * <base>.MacRxPauseStateChange
 */
#define NFP_MAC_CSR_MAC_RX_PAUSE_STATE_CHANGE              0x041c
#define   NFP_MAC_CSR_MAC_RX_PAUSE_STATE_CHANGE_RX_PAUSE_STATE_CHANGE(x) (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_MAC_RX_PAUSE_STATE_CHANGE_RX_PAUSE_STATE_CHANGE_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_MAC_RX_PAUSE_STATE_CHANGE_RX_PAUSE_STATE_CHANGE_bf 0, 19, 0
#define     NFP_MAC_CSR_MAC_RX_PAUSE_STATE_CHANGE_RX_PAUSE_STATE_CHANGE_msk (0xfffff)
#define     NFP_MAC_CSR_MAC_RX_PAUSE_STATE_CHANGE_RX_PAUSE_STATE_CHANGE_shf (0)


/*
 * Register: MacStatsHalfFull
 *   [24]      TxStatHalfFullVld
 *   [23:16]   TxStatAddr
 *   [8]       RxStatHalfFullVld
 *   [7:0]     RxStatAddr
 *
 * Name(s):
 * <base>.MacStatsHalfFullPort0011 <base>.MacStatsHalfFullPort1223
 * <base>.MacStatsHalfFullChan0063 <base>.MacStatsHalfFullChan63127
 */
#define NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11         0x0420
#define NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_12_23         0x0424
#define NFP_MAC_CSR_MAC_STATS_HALF_FULL_CHAN_00_63         0x0428
#define NFP_MAC_CSR_MAC_STATS_HALF_FULL_CHAN_63_127        0x042c
#define   NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_HALF_FULL_VLD (1 << 24)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_HALF_FULL_VLD_bf 0, 24, 24
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_HALF_FULL_VLD_msk (0x1)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_HALF_FULL_VLD_bit (24)
#define   NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_ADDR(x) (((x) & 0xff) << 16)
#define   NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_ADDR_of(x) (((x) >> 16) & 0xff)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_ADDR_bf 0, 23, 16
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_ADDR_msk (0xff)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_TX_STAT_ADDR_shf (16)
#define   NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_HALF_FULL_VLD (1 << 8)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_HALF_FULL_VLD_bf 0, 8, 8
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_HALF_FULL_VLD_msk (0x1)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_HALF_FULL_VLD_bit (8)
#define   NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_ADDR(x) (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_ADDR_of(x) (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_ADDR_bf 0, 7, 0
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_ADDR_msk (0xff)
#define     NFP_MAC_CSR_MAC_STATS_HALF_FULL_PORT_00_11_RX_STAT_ADDR_shf (0)


/*
 * Register: MacIgPortErrStatus
 *   [24]      ErrValid
 *   [23:8]    PayloadLength
 *   [7]       VlanTag
 *   [6]       CtlCharErr
 *   [5]       StackedVlanTag
 *   [4]       SeqErr
 *   [3]       FifoErr
 *   [2]       BadCodeErr
 *   [1]       Crc32Err
 *   [0]       LengthErr
 *
 * Name(s):
 * <base>.MacIgPortErrStatus0...
 */
#define NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS(x)              (0x0500 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_ERR_VALID       (1 << 24)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_ERR_VALID_bf  0, 24, 24
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_ERR_VALID_msk (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_ERR_VALID_bit (24)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_PAYLOAD_LENGTH(x) (((x) & 0xffff) << 8)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_PAYLOAD_LENGTH_of(x) (((x) >> 8) & 0xffff)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_PAYLOAD_LENGTH_bf 0, 23, 8
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_PAYLOAD_LENGTH_msk (0xffff)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_PAYLOAD_LENGTH_shf (8)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_VLAN_TAG        (1 << 7)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_VLAN_TAG_bf   0, 7, 7
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_VLAN_TAG_msk  (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_VLAN_TAG_bit  (7)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CTL_CHAR_ERR    (1 << 6)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CTL_CHAR_ERR_bf 0, 6, 6
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CTL_CHAR_ERR_msk (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CTL_CHAR_ERR_bit (6)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_STACKED_VLAN_TAG (1 << 5)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_STACKED_VLAN_TAG_bf 0, 5, 5
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_STACKED_VLAN_TAG_msk (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_STACKED_VLAN_TAG_bit (5)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_SEQ_ERR         (1 << 4)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_SEQ_ERR_bf    0, 4, 4
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_SEQ_ERR_msk   (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_SEQ_ERR_bit   (4)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_FIFO_ERR        (1 << 3)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_FIFO_ERR_bf   0, 3, 3
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_FIFO_ERR_msk  (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_FIFO_ERR_bit  (3)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_BAD_CODE_ERR    (1 << 2)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_BAD_CODE_ERR_bf 0, 2, 2
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_BAD_CODE_ERR_msk (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_BAD_CODE_ERR_bit (2)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CRC32_ERR       (1 << 1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CRC32_ERR_bf  0, 1, 1
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CRC32_ERR_msk (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_CRC32_ERR_bit (1)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_LENGTH_ERR      (1 << 0)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_LENGTH_ERR_bf 0, 0, 0
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_LENGTH_ERR_msk (0x1)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_STATUS_LENGTH_ERR_bit (0)


/*
 * Register: MacEgTimeStampInserted
 *   [31:0]    TimeStampValue
 *
 * Name(s):
 * <base>.MacEgTimeStampInserted0...
 */
#define NFP_MAC_CSR_MAC_EG_TIME_STAMP_INSERTED(x)          (0x0550 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_EG_TIME_STAMP_INSERTED_TIME_STAMP_VALUE(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_EG_TIME_STAMP_INSERTED_TIME_STAMP_VALUE_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_EG_TIME_STAMP_INSERTED_TIME_STAMP_VALUE_bf 0, 31, 0
#define     NFP_MAC_CSR_MAC_EG_TIME_STAMP_INSERTED_TIME_STAMP_VALUE_msk (0xffffffff)
#define     NFP_MAC_CSR_MAC_EG_TIME_STAMP_INSERTED_TIME_STAMP_VALUE_shf (0)


/*
 * Register: MacIgPortErr
 *   [15:0]    PortErr
 *
 * Name(s):
 * <base>.MacIgPortErr
 */
#define NFP_MAC_CSR_MAC_IG_PORT_ERR                        0x05a8
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_PORT_ERR(x)            (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_MAC_IG_PORT_ERR_PORT_ERR_of(x)         (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_PORT_ERR_bf          0, 15, 0
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_PORT_ERR_msk         (0xffff)
#define     NFP_MAC_CSR_MAC_IG_PORT_ERR_PORT_ERR_shf         (0)


/*
 * Register: MacEgDropCtrl
 *   [19:0]    Drop
 *
 * Name(s):
 * <base>.MacEgDropCtrlErr <base>.MacEgDropCtrlAll
 */
#define NFP_MAC_CSR_MAC_EG_DROP_CTRL_ERR                   0x05b4
#define NFP_MAC_CSR_MAC_EG_DROP_CTRL_ALL                   0x05b8
#define   NFP_MAC_CSR_MAC_EG_DROP_CTRL_ERR_DROP(x)           (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_MAC_EG_DROP_CTRL_ERR_DROP_of(x)        (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_MAC_EG_DROP_CTRL_ERR_DROP_bf         0, 19, 0
#define     NFP_MAC_CSR_MAC_EG_DROP_CTRL_ERR_DROP_msk        (0xfffff)
#define     NFP_MAC_CSR_MAC_EG_DROP_CTRL_ERR_DROP_shf        (0)


/*
 * Register: MacSerialCount
 *   [31:26]   SerialCountRFU
 *   [25:8]    BaudCount
 *   [7:0]     FracCount
 *
 * Name(s):
 * <base>.MacSerialLedCount
 */
#define NFP_MAC_CSR_MAC_SERIAL_LED_COUNT                   0x05bc
#define   NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_SERIAL_COUNT_RFU(x) (((x) & 0x3f) << 26)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_SERIAL_COUNT_RFU_of(x) (((x) >> 26) & 0x3f)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_SERIAL_COUNT_RFU_bf 0, 31, 26
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_SERIAL_COUNT_RFU_msk (0x3f)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_SERIAL_COUNT_RFU_shf (26)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_BAUD_COUNT(x)     (((x) & 0x3ffff) << 8)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_BAUD_COUNT_of(x)  (((x) >> 8) & 0x3ffff)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_BAUD_COUNT_bf   0, 25, 8
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_BAUD_COUNT_msk  (0x3ffff)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_BAUD_COUNT_shf  (8)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_FRAC_COUNT(x)     (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_FRAC_COUNT_of(x)  (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_FRAC_COUNT_bf   0, 7, 0
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_FRAC_COUNT_msk  (0xff)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_COUNT_FRAC_COUNT_shf  (0)


/*
 * Register: MacSerialCtrl
 *   [31]      SerialEnable
 *   [30]      SerialUnInvert
 *   [29]      SerialLsbFirst
 *   [28]      Serial8N1
 *   [27]      SerialOe
 *   [26:10]   SerialCtrlRFU
 *   [9:5]     LedClrBitNum
 *   [4:0]     LedSetBitNum
 *
 * Name(s):
 * <base>.MacSerialLedCtrl
 */
#define NFP_MAC_CSR_MAC_SERIAL_LED_CTRL                    0x05c0
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_ENABLE      (1 << 31)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_ENABLE_bf 0, 31, 31
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_ENABLE_msk (0x1)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_ENABLE_bit (31)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_UN_INVERT   (1 << 30)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_UN_INVERT_bf 0, 30, 30
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_UN_INVERT_msk (0x1)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_UN_INVERT_bit (30)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_LSB_FIRST   (1 << 29)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_LSB_FIRST_bf 0, 29, 29
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_LSB_FIRST_msk (0x1)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_LSB_FIRST_bit (29)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_8N1         (1 << 28)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_8N1_bf    0, 28, 28
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_8N1_msk   (0x1)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_8N1_bit   (28)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_OE          (1 << 27)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_OE_bf     0, 27, 27
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_OE_msk    (0x1)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_OE_bit    (27)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_CTRL_RFU(x) (((x) & 0x1ffff) << 10)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_CTRL_RFU_of(x) (((x) >> 10) & 0x1ffff)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_CTRL_RFU_bf 0, 26, 10
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_CTRL_RFU_msk (0x1ffff)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_SERIAL_CTRL_RFU_shf (10)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_CLR_BIT_NUM(x) (((x) & 0x1f) << 5)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_CLR_BIT_NUM_of(x) (((x) >> 5) & 0x1f)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_CLR_BIT_NUM_bf 0, 9, 5
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_CLR_BIT_NUM_msk (0x1f)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_CLR_BIT_NUM_shf (5)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_SET_BIT_NUM(x) (((x) & 0x1f) << 0)
#define   NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_SET_BIT_NUM_of(x) (((x) >> 0) & 0x1f)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_SET_BIT_NUM_bf 0, 4, 0
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_SET_BIT_NUM_msk (0x1f)
#define     NFP_MAC_CSR_MAC_SERIAL_LED_CTRL_LED_SET_BIT_NUM_shf (0)


/*
 * Register: MacPfcGen1Shot
 *   [31:24]   Pfc1Shot3
 *   [23:16]   Pfc1Shot2
 *   [15:8]    Pfc1Shot1
 *   [7:0]     Pfc1Shot0
 *
 * Name(s):
 * <base>.MacPfcGen1Shot00... <base>.MacPfcGen1Shot10...
 */
#define NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0(x)                 (0x05c4 + ((x) * 0x4))
#define NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_1(x)                 (0x05d0 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_3(x)     (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_3_of(x)  (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_3_bf   0, 31, 24
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_3_msk  (0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_3_shf  (24)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_2(x)     (((x) & 0xff) << 16)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_2_of(x)  (((x) >> 16) & 0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_2_bf   0, 23, 16
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_2_msk  (0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_2_shf  (16)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_1(x)     (((x) & 0xff) << 8)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_1_of(x)  (((x) >> 8) & 0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_1_bf   0, 15, 8
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_1_msk  (0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_1_shf  (8)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_0(x)     (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_0_of(x)  (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_0_bf   0, 7, 0
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_0_msk  (0xff)
#define     NFP_MAC_CSR_MAC_PFC_GEN_1SHOT_0_PFC_1SHOT_0_shf  (0)


/*
 * Register: MacTxPfcInhEn
 *   [31:24]   PfcInh3
 *   [23:16]   PfcInh2
 *   [15:8]    PfcInh1
 *   [7:0]     PfcInh0
 *
 * Name(s):
 * <base>.MacTxPfcInhEn00... <base>.MacTxPfcInhEn10...
 */
#define NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0(x)                 (0x05dc + ((x) * 0x4))
#define NFP_MAC_CSR_MAC_TX_PFC_INH_EN_1(x)                 (0x05e8 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_3(x)       (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_3_of(x)    (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_3_bf     0, 31, 24
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_3_msk    (0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_3_shf    (24)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_2(x)       (((x) & 0xff) << 16)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_2_of(x)    (((x) >> 16) & 0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_2_bf     0, 23, 16
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_2_msk    (0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_2_shf    (16)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_1(x)       (((x) & 0xff) << 8)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_1_of(x)    (((x) >> 8) & 0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_1_bf     0, 15, 8
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_1_msk    (0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_1_shf    (8)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_0(x)       (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_0_of(x)    (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_0_bf     0, 7, 0
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_0_msk    (0xff)
#define     NFP_MAC_CSR_MAC_TX_PFC_INH_EN_0_PFC_INH_0_shf    (0)


/*
 * Register: MacIgChDropOnExcd
 *   [31:0]    DropOnExcd
 *
 * Name(s):
 * <base>.MacIgChDropOnExcd0...
 */
#define NFP_MAC_CSR_MAC_IG_CH_DROP_ON_EXCD_(x)             (0x05f4 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_IG_CH_DROP_ON_EXCD__DROP_ON_EXCD(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_MAC_IG_CH_DROP_ON_EXCD__DROP_ON_EXCD_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_MAC_IG_CH_DROP_ON_EXCD__DROP_ON_EXCD_bf 0, 31, 0
#define     NFP_MAC_CSR_MAC_IG_CH_DROP_ON_EXCD__DROP_ON_EXCD_msk (0xffffffff)
#define     NFP_MAC_CSR_MAC_IG_CH_DROP_ON_EXCD__DROP_ON_EXCD_shf (0)


/*
 * Register: MacPfcIgnEn
 *   [31:24]   PfcIgn3
 *   [23:16]   PfcIgn2
 *   [15:8]    PfcIgn1
 *   [7:0]     PfcIgn0
 *
 * Name(s):
 * <base>.MacPfcIgnEn00... <base>.MacPfcIgnEn10...
 */
#define NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0(x)                 (0x0604 + ((x) * 0x4))
#define NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_1(x)                 (0x0610 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_3(x)       (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_3_of(x)    (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_3_bf     0, 31, 24
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_3_msk    (0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_3_shf    (24)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_2(x)       (((x) & 0xff) << 16)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_2_of(x)    (((x) >> 16) & 0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_2_bf     0, 23, 16
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_2_msk    (0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_2_shf    (16)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_1(x)       (((x) & 0xff) << 8)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_1_of(x)    (((x) >> 8) & 0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_1_bf     0, 15, 8
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_1_msk    (0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_1_shf    (8)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_0(x)       (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_0_of(x)    (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_0_bf     0, 7, 0
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_0_msk    (0xff)
#define     NFP_MAC_CSR_MAC_EG_PFC_IGN_EN_0_PFC_IGN_0_shf    (0)


/*
 * Register: MacPfcReMap
 *   [31]      PortEgDqRrEn
 *   [30]      PortEgDqLo2HiPri
 *   [23:21]   PfcReMap7
 *   [20:18]   PfcReMap6
 *   [17:15]   PfcReMap5
 *   [14:12]   PfcReMap4
 *   [11:9]    PfcReMap3
 *   [8:6]     PfcReMap2
 *   [5:3]     PfcReMap1
 *   [2:0]     PfcReMap0
 *
 * Name(s):
 * <base>.MacPfcReMap0...
 */
#define NFP_MAC_CSR_MAC_PFC_REMAP(x)                       (0x061c + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PORT_EG_DQ_RR_EN         (1 << 31)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PORT_EG_DQ_RR_EN_bf    0, 31, 31
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PORT_EG_DQ_RR_EN_msk   (0x1)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PORT_EG_DQ_RR_EN_bit   (31)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PCP_EG_DQ_LO_2_HI_PRI    (1 << 30)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PCP_EG_DQ_LO_2_HI_PRI_bf 0, 30, 30
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PCP_EG_DQ_LO_2_HI_PRI_msk (0x1)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PCP_EG_DQ_LO_2_HI_PRI_bit (30)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP7(x)            (((x) & 7) << 21)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP7_of(x)         (((x) >> 21) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP7_bf          0, 23, 21
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP7_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP7_shf         (21)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP6(x)            (((x) & 7) << 18)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP6_of(x)         (((x) >> 18) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP6_bf          0, 20, 18
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP6_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP6_shf         (18)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP5(x)            (((x) & 7) << 15)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP5_of(x)         (((x) >> 15) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP5_bf          0, 17, 15
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP5_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP5_shf         (15)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP4(x)            (((x) & 7) << 12)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP4_of(x)         (((x) >> 12) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP4_bf          0, 14, 12
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP4_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP4_shf         (12)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP3(x)            (((x) & 7) << 9)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP3_of(x)         (((x) >> 9) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP3_bf          0, 11, 9
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP3_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP3_shf         (9)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP2(x)            (((x) & 7) << 6)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP2_of(x)         (((x) >> 6) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP2_bf          0, 8, 6
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP2_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP2_shf         (6)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP1(x)            (((x) & 7) << 3)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP1_of(x)         (((x) >> 3) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP1_bf          0, 5, 3
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP1_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP1_shf         (3)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP0(x)            (((x) & 7) << 0)
#define   NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP0_of(x)         (((x) >> 0) & 7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP0_bf          0, 2, 0
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP0_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PFC_REMAP_PFC_REMAP0_shf         (0)


/*
 * Register: MacPcpReMap
 *   [31]      PortIgDqRrEn
 *   [30]      PortIgDqLo2HiPri
 *   [29:24]   UntaggedChan
 *   [23:21]   PcpReMap7
 *   [20:18]   PcpReMap6
 *   [17:15]   PcpReMap5
 *   [14:12]   PcpReMap4
 *   [11:9]    PcpReMap3
 *   [8:6]     PcpReMap2
 *   [5:3]     PcpReMap1
 *   [2:0]     PcpReMap0
 *
 * Name(s):
 * <base>.MacPcpReMap0...
 */
#define NFP_MAC_CSR_MAC_PCP_REMAP(x)                       (0x0680 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PORT_IG_DQ_RR_EN         (1 << 31)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PORT_IG_DQ_RR_EN_bf    0, 31, 31
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PORT_IG_DQ_RR_EN_msk   (0x1)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PORT_IG_DQ_RR_EN_bit   (31)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_IG_DQ_LO_2_HI_PRI    (1 << 30)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_IG_DQ_LO_2_HI_PRI_bf 0, 30, 30
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_IG_DQ_LO_2_HI_PRI_msk (0x1)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_IG_DQ_LO_2_HI_PRI_bit (30)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_MAC_UNTAGD_ABS(x)        (((x) & 0x3f) << 24)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_MAC_UNTAGD_ABS_of(x)     (((x) >> 24) & 0x3f)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_MAC_UNTAGD_ABS_bf      0, 29, 24
#define     NFP_MAC_CSR_MAC_PCP_REMAP_MAC_UNTAGD_ABS_msk     (0x3f)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_MAC_UNTAGD_ABS_shf     (24)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP7(x)            (((x) & 7) << 21)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP7_of(x)         (((x) >> 21) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP7_bf          0, 23, 21
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP7_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP7_shf         (21)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP6(x)            (((x) & 7) << 18)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP6_of(x)         (((x) >> 18) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP6_bf          0, 20, 18
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP6_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP6_shf         (18)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP5(x)            (((x) & 7) << 15)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP5_of(x)         (((x) >> 15) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP5_bf          0, 17, 15
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP5_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP5_shf         (15)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP4(x)            (((x) & 7) << 12)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP4_of(x)         (((x) >> 12) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP4_bf          0, 14, 12
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP4_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP4_shf         (12)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP3(x)            (((x) & 7) << 9)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP3_of(x)         (((x) >> 9) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP3_bf          0, 11, 9
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP3_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP3_shf         (9)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP2(x)            (((x) & 7) << 6)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP2_of(x)         (((x) >> 6) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP2_bf          0, 8, 6
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP2_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP2_shf         (6)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP1(x)            (((x) & 7) << 3)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP1_of(x)         (((x) >> 3) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP1_bf          0, 5, 3
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP1_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP1_shf         (3)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP0(x)            (((x) & 7) << 0)
#define   NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP0_of(x)         (((x) >> 0) & 7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP0_bf          0, 2, 0
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP0_msk         (0x7)
#define     NFP_MAC_CSR_MAC_PCP_REMAP_PCP_REMAP0_shf         (0)


/*
 * Register: MacFlushDropCounter
 *   [31:16]   MacFlushDropCounter1
 *   [15:0]    MacFlushDropCounter0
 *
 * Name(s):
 * <base>.MacHy0EthEgPktFlushDropCntr0... <base>.MacHy1EthEgPktFlushDropCntr0...
 */
#define NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR_(x) (0x06d0 + ((x) * 0x4))
#define NFP_MAC_CSR_MAC_HY1_ETH_EG_PKT_FLUSH_DROP_CNTR_(x) (0x06e4 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_1(x) (((x) & 0xffff) << 16)
#define   NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_1_of(x) (((x) >> 16) & 0xffff)
#define     NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_1_bf 0, 31, 16
#define     NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_1_msk (0xffff)
#define     NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_1_shf (16)
#define   NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_0(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_0_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_0_bf 0, 15, 0
#define     NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_0_msk (0xffff)
#define     NFP_MAC_CSR_MAC_HY0_ETH_EG_PKT_FLUSH_DROP_CNTR__MAC_FLUSH_DROP_COUNTER_0_shf (0)


/*
 * Register: MacPortHwm
 *   [31:27]   PortDropDelta1
 *   [26:16]   PortHwm1
 *   [15:11]   PortDropDelta0
 *   [10:0]    PortHwm0
 *
 * Name(s):
 * <base>.MacPortHwm0...
 */
#define NFP_MAC_CSR_MAC_PORT_HWM(x)                        (0x0700 + ((x) * 0x4))
#define   NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA1(x)        (((x) & 0x1f) << 27)
#define   NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA1_of(x)     (((x) >> 27) & 0x1f)
#define     NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA1_bf      0, 31, 27
#define     NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA1_msk     (0x1f)
#define     NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA1_shf     (27)
#define   NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM1(x)              (((x) & 0x7ff) << 16)
#define   NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM1_of(x)           (((x) >> 16) & 0x7ff)
#define     NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM1_bf            0, 26, 16
#define     NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM1_msk           (0x7ff)
#define     NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM1_shf           (16)
#define   NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA0(x)        (((x) & 0x1f) << 11)
#define   NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA0_of(x)     (((x) >> 11) & 0x1f)
#define     NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA0_bf      0, 15, 11
#define     NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA0_msk     (0x1f)
#define     NFP_MAC_CSR_MAC_PORT_HWM_POR_DROP_DELTA0_shf     (11)
#define   NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM0(x)              (((x) & 0x7ff) << 0)
#define   NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM0_of(x)           (((x) >> 0) & 0x7ff)
#define     NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM0_bf            0, 10, 0
#define     NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM0_msk           (0x7ff)
#define     NFP_MAC_CSR_MAC_PORT_HWM_PORT_HWM0_shf           (0)


/*
 * Register: SinglePortFifoEn
 *   [19:0]    Enable
 *
 * Name(s):
 * <base>.EgSinglePortFifoEn
 */
#define NFP_MAC_CSR_EG_SINGLE_PORT_FIFO_EN                 0x0730
#define   NFP_MAC_CSR_EG_SINGLE_PORT_FIFO_EN_ENABLE(x)       (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_EG_SINGLE_PORT_FIFO_EN_ENABLE_of(x)    (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_EG_SINGLE_PORT_FIFO_EN_ENABLE_bf     0, 19, 0
#define     NFP_MAC_CSR_EG_SINGLE_PORT_FIFO_EN_ENABLE_msk    (0xfffff)
#define     NFP_MAC_CSR_EG_SINGLE_PORT_FIFO_EN_ENABLE_shf    (0)


/*
 * Register: PortIgnoreFc
 *   [19:0]    Ignore
 *
 * Name(s):
 * <base>.EgPortOnlyIgnoreFc
 */
#define NFP_MAC_CSR_EG_PORT_ONLY_IGNORE_FC                 0x0734
#define   NFP_MAC_CSR_EG_PORT_ONLY_IGNORE_FC_IGNORE(x)       (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_EG_PORT_ONLY_IGNORE_FC_IGNORE_of(x)    (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_EG_PORT_ONLY_IGNORE_FC_IGNORE_bf     0, 19, 0
#define     NFP_MAC_CSR_EG_PORT_ONLY_IGNORE_FC_IGNORE_msk    (0xfffff)
#define     NFP_MAC_CSR_EG_PORT_ONLY_IGNORE_FC_IGNORE_shf    (0)


/*
 * Register: LLMemRdData
 *   [29:18]   LLRdOffsetAddr
 *   [17]      LLRdDataValid
 *   [15:0]    LLRdData
 *
 * Name(s):
 * <base>.EgLnkLstRdData <base>.IgLnkLstRdData
 */
#define NFP_MAC_CSR_EG_LNKLST_RDDATA                       0x07b0
#define NFP_MAC_CSR_IG_LNKLST_RDDATA                       0x07b4
#define   NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_OFFSET_ADDR(x)  (((x) & 0xfff) << 18)
#define   NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_OFFSET_ADDR_of(x) (((x) >> 18) & 0xfff)
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_OFFSET_ADDR_bf 0, 29, 18
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_OFFSET_ADDR_msk (0xfff)
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_OFFSET_ADDR_shf (18)
#define   NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_VALID      (1 << 17)
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_VALID_bf 0, 17, 17
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_VALID_msk (0x1)
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_VALID_bit (17)
#define   NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA(x)         (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_of(x)      (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_bf       0, 15, 0
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_msk      (0xffff)
#define     NFP_MAC_CSR_EG_LNKLST_RDDATA_LL_RD_DATA_shf      (0)


/*
 * Register: LLMemRdWr
 *   [31:30]   Rfu
 *   [29:18]   LLOffsetAddr
 *   [17]      LLRdBusy
 *   [16]      LLWrBusy
 *   [15:0]    LLWrData
 *
 * Name(s):
 * <base>.EgLnkLstRdWr <base>.IgLnkLstRdWr
 */
#define NFP_MAC_CSR_EG_LNKLST_RDWR                         0x07b8
#define NFP_MAC_CSR_IG_LNKLST_RDWR                         0x07bc
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_RFU(x)                  (((x) & 3) << 30)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_RFU_of(x)               (((x) >> 30) & 3)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_RFU_bf                0, 31, 30
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_RFU_msk               (0x3)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_RFU_shf               (30)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_LL_OFFSET_ADDR(x)       (((x) & 0xfff) << 18)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_LL_OFFSET_ADDR_of(x)    (((x) >> 18) & 0xfff)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_OFFSET_ADDR_bf     0, 29, 18
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_OFFSET_ADDR_msk    (0xfff)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_OFFSET_ADDR_shf    (18)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_LL_RD_BUSY              (1 << 17)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_RD_BUSY_bf         0, 17, 17
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_RD_BUSY_msk        (0x1)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_RD_BUSY_bit        (17)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_BUSY              (1 << 16)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_BUSY_bf         0, 16, 16
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_BUSY_msk        (0x1)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_BUSY_bit        (16)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_DATA(x)           (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_DATA_of(x)        (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_DATA_bf         0, 15, 0
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_DATA_msk        (0xffff)
#define     NFP_MAC_CSR_EG_LNKLST_RDWR_LL_WR_DATA_shf        (0)


/*
 * Register: SerDes4RdWr
 *   [31]      SerDesRdBusy
 *   [30]      SerDesWrBusy
 *   [29:16]   SerDesOffsetAddr
 *   [15:0]    SerDesWrData
 *
 * Name(s):
 * <base>.SerDes4RdWr03To00 <base>.SerDes4RdWr07To04 <base>.SerDes4RdWr11To08
 * <base>.SerDes4RdWr15To12 <base>.SerDes4RdWr19To16
 */
#define NFP_MAC_CSR_SERDES4_RDWR_03_00                     0x07c0
#define NFP_MAC_CSR_SERDES4_RDWR_07_04                     0x07c4
#define NFP_MAC_CSR_SERDES4_RDWR_11_08                     0x07c8
#define NFP_MAC_CSR_SERDES4_RDWR_15_12                     0x07cc
#define NFP_MAC_CSR_SERDES4_RDWR_19_16                     0x07d0
#define   NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_RD_BUSY  (1 << 31)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_RD_BUSY_bf 0, 31, 31
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_RD_BUSY_msk (0x1)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_RD_BUSY_bit (31)
#define   NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_BUSY  (1 << 30)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_BUSY_bf 0, 30, 30
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_BUSY_msk (0x1)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_BUSY_bit (30)
#define   NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_OFFSET_ADDR(x) (((x) & 0x3fff) << 16)
#define   NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_OFFSET_ADDR_of(x) (((x) >> 16) & 0x3fff)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_OFFSET_ADDR_bf 0, 29, 16
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_OFFSET_ADDR_msk (0x3fff)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_OFFSET_ADDR_shf (16)
#define   NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_DATA_bf 0, 15, 0
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_DATA_msk (0xffff)
#define     NFP_MAC_CSR_SERDES4_RDWR_03_00_MAC_SERDES_WR_DATA_shf (0)


/*
 * Register: TdmMemRdWr
 *   [31:30]   TdmMemRdWrRFU1
 *   [29:24]   TdmMemRdWrAddr
 *   [23:22]   TdmMemRdWrRFU0
 *   [21]      TdmMemRdBusy
 *   [20]      TdmMemWrBusy
 *   [19:16]   TdmMemUnused
 *   [15]      TdmPortArbEnable
 *   [14:0]    TdmPortWeightWrData
 *
 * Name(s):
 * <base>.IgDqTdmMemoryRW
 */
#define NFP_MAC_CSR_TDM_MEM_RDWR                           0x07d8
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU1(x)     (((x) & 3) << 30)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU1_of(x)  (((x) >> 30) & 3)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU1_bf   0, 31, 30
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU1_msk  (0x3)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU1_shf  (30)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_ADDR(x)     (((x) & 0x3f) << 24)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_ADDR_of(x)  (((x) >> 24) & 0x3f)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_ADDR_bf   0, 29, 24
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_ADDR_msk  (0x3f)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_ADDR_shf  (24)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU0(x)     (((x) & 3) << 22)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU0_of(x)  (((x) >> 22) & 3)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU0_bf   0, 23, 22
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU0_msk  (0x3)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_WR_RFU0_shf  (22)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_BUSY           (1 << 21)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_BUSY_bf      0, 21, 21
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_BUSY_msk     (0x1)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_RD_BUSY_bit     (21)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_WR_BUSY           (1 << 20)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_WR_BUSY_bf      0, 20, 20
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_WR_BUSY_msk     (0x1)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_WR_BUSY_bit     (20)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_UNUSED(x)         (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_UNUSED_of(x)      (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_UNUSED_bf       0, 19, 16
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_UNUSED_msk      (0xf)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_MEM_UNUSED_shf      (16)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_ARB_ENABLE       (1 << 15)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_ARB_ENABLE_bf  0, 15, 15
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_ARB_ENABLE_msk (0x1)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_ARB_ENABLE_bit (15)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_WEIGHTWR_DATA(x) (((x) & 0x7fff) << 0)
#define   NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_WEIGHTWR_DATA_of(x) (((x) >> 0) & 0x7fff)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_WEIGHTWR_DATA_bf 0, 14, 0
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_WEIGHTWR_DATA_msk (0x7fff)
#define     NFP_MAC_CSR_TDM_MEM_RDWR_TDM_PORT_WEIGHTWR_DATA_shf (0)


/*
 * Register: SerDes4RdData
 *   [31]      SerDesRdDataValid
 *   [29:16]   SerDesRdOffsetAddr
 *   [15:0]    SerDesRdData
 *
 * Name(s):
 * <base>.SerDes4RdData03To00 <base>.SerDes4RdData07To04
 * <base>.SerDes4RdData11To08 <base>.SerDes4RdData15To12
 * <base>.SerDes4RdData19To16
 */
#define NFP_MAC_CSR_SERDES4_RDDATA_03_00                   0x07e0
#define NFP_MAC_CSR_SERDES4_RDDATA_07_04                   0x07e4
#define NFP_MAC_CSR_SERDES4_RDDATA_11_08                   0x07e8
#define NFP_MAC_CSR_SERDES4_RDDATA_15_12                   0x07ec
#define NFP_MAC_CSR_SERDES4_RDDATA_19_16                   0x07f0
#define   NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_VALID (1 << 31)
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_VALID_bf 0, 31, 31
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_VALID_msk (0x1)
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_VALID_bit (31)
#define   NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_OFFSET_ADDR(x) (((x) & 0x3fff) << 16)
#define   NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_OFFSET_ADDR_of(x) (((x) >> 16) & 0x3fff)
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_OFFSET_ADDR_bf 0, 29, 16
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_OFFSET_ADDR_msk (0x3fff)
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_OFFSET_ADDR_shf (16)
#define   NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA(x) (((x) & 0xffff) << 0)
#define   NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_of(x) (((x) >> 0) & 0xffff)
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_bf 0, 15, 0
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_msk (0xffff)
#define     NFP_MAC_CSR_SERDES4_RDDATA_03_00_MAC_SERDES_RD_DATA_shf (0)


/*
 * Register: TdmMemRdData
 *   [29:24]   TdmMemRdAddr
 *   [21]      TdmMemRdDataValid
 *   [19:16]   TdmPortUnusedRdRet
 *   [15]      TdmPortArbEnable
 *   [14:0]    TdmPortWeightRdData
 *
 * Name(s):
 * <base>.IgDqTdmMemoryRdData
 */
#define NFP_MAC_CSR_TDM_MEM_RDDATA                         0x07f8
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_ADDR(x)      (((x) & 0x3f) << 24)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_ADDR_of(x)   (((x) >> 24) & 0x3f)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_ADDR_bf    0, 29, 24
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_ADDR_msk   (0x3f)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_ADDR_shf   (24)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_DATA_VALID   (1 << 21)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_DATA_VALID_bf 0, 21, 21
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_DATA_VALID_msk (0x1)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_MEM_RD_DATA_VALID_bit (21)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_UNUSED_RD_RET(x) (((x) & 0xf) << 16)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_UNUSED_RD_RET_of(x) (((x) >> 16) & 0xf)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_UNUSED_RD_RET_bf 0, 19, 16
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_UNUSED_RD_RET_msk (0xf)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_UNUSED_RD_RET_shf (16)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_ARB_ENABLE     (1 << 15)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_ARB_ENABLE_bf 0, 15, 15
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_ARB_ENABLE_msk (0x1)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_ARB_ENABLE_bit (15)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_WEIGHTRD_DATA(x) (((x) & 0x7fff) << 0)
#define   NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_WEIGHTRD_DATA_of(x) (((x) >> 0) & 0x7fff)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_WEIGHTRD_DATA_bf 0, 14, 0
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_WEIGHTRD_DATA_msk (0x7fff)
#define     NFP_MAC_CSR_TDM_MEM_RDDATA_TDM_PORT_WEIGHTRD_DATA_shf (0)


/*
 * Register: SerDesCkMuxSel2
 *   [23]      SerDesCkMuxSelCdrL23
 *   [22]      SerDesCkMuxSelCdrL22
 *   [21]      SerDesCkMuxSelCdrL21
 *   [20]      SerDesCkMuxSelCdrL20
 *   [19]      SerDesCkMuxSelCdrL19
 *   [18]      SerDesCkMuxSelCdrL18
 *   [17]      SerDesCkMuxSelCdrL17
 *   [16]      SerDesCkMuxSelCdrL16
 *   [15]      SerDesCkMuxSelCdrL15
 *   [14]      SerDesCkMuxSelCdrL14
 *   [13]      SerDesCkMuxSelCdrL13
 *   [12]      SerDesCkMuxSelCdrL12
 *   [11]      SerDesCkMuxSelCdrL11
 *   [10]      SerDesCkMuxSelCdrL10
 *   [9]       SerDesCkMuxSelCdrL09
 *   [8]       SerDesCkMuxSelCdrL08
 *   [7]       SerDesCkMuxSelCdrL07
 *   [6]       SerDesCkMuxSelCdrL06
 *   [5]       SerDesCkMuxSelCdrL05
 *   [4]       SerDesCkMuxSelCdrL04
 *   [3]       SerDesCkMuxSelCdrL03
 *   [2]       SerDesCkMuxSelCdrL02
 *   [1]       SerDesCkMuxSelCdrL01
 *   [0]       SerDesCkMuxSelCdrL00
 *
 * Name(s):
 * <base>.SerDesCkMuxSelCdr
 */
#define NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR                  0x07fc
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_23 (1 << 23)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_23_bf 0, 23, 23
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_23_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_23_bit (23)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_22 (1 << 22)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_22_bf 0, 22, 22
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_22_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_22_bit (22)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_21 (1 << 21)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_21_bf 0, 21, 21
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_21_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_21_bit (21)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CD_20 (1 << 20)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CD_20_bf 0, 20, 20
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CD_20_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CD_20_bit (20)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_19 (1 << 19)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_19_bf 0, 19, 19
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_19_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_19_bit (19)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_18 (1 << 18)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_18_bf 0, 18, 18
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_18_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_18_bit (18)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_17 (1 << 17)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_17_bf 0, 17, 17
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_17_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_17_bit (17)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_16 (1 << 16)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_16_bf 0, 16, 16
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_16_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_16_bit (16)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_15 (1 << 15)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_15_bf 0, 15, 15
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_15_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_15_bit (15)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_14 (1 << 14)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_14_bf 0, 14, 14
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_14_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_14_bit (14)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_13 (1 << 13)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_13_bf 0, 13, 13
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_13_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_13_bit (13)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_12 (1 << 12)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_12_bf 0, 12, 12
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_12_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_12_bit (12)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_11 (1 << 11)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_11_bf 0, 11, 11
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_11_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_11_bit (11)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_10 (1 << 10)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_10_bf 0, 10, 10
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_10_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_10_bit (10)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_09 (1 << 9)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_09_bf 0, 9, 9
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_09_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_09_bit (9)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_08 (1 << 8)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_08_bf 0, 8, 8
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_08_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_08_bit (8)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_07 (1 << 7)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_07_bf 0, 7, 7
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_07_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_07_bit (7)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_06 (1 << 6)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_06_bf 0, 6, 6
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_06_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_06_bit (6)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_05 (1 << 5)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_05_bf 0, 5, 5
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_05_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_05_bit (5)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_04 (1 << 4)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_04_bf 0, 4, 4
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_04_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_04_bit (4)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_03 (1 << 3)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_03_bf 0, 3, 3
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_03_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_03_bit (3)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_02 (1 << 2)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_02_bf 0, 2, 2
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_02_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_02_bit (2)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_01 (1 << 1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_01_bf 0, 1, 1
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_01_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_01_bit (1)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_00 (1 << 0)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_00_bf 0, 0, 0
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_00_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_CDR_SERDES_CK_MUX_SEL_CDR_00_bit (0)


/*
 * Register: SerDesPdLn
 *   [23:0]    SerDesLanePowerDown
 *
 * Name(s):
 * <base>.SerDesPdRx <base>.SerDesPdTx
 */
#define NFP_MAC_CSR_SERDES_PD_RX                           0x0800
#define NFP_MAC_CSR_SERDES_PD_TX                           0x0804
#define   NFP_MAC_CSR_SERDES_PD_RX_SERDES_LANE_POWER_DOWN(x) (((x) & 0xffffff) << 0)
#define   NFP_MAC_CSR_SERDES_PD_RX_SERDES_LANE_POWER_DOWN_of(x) (((x) >> 0) & 0xffffff)
#define     NFP_MAC_CSR_SERDES_PD_RX_SERDES_LANE_POWER_DOWN_bf 0, 23, 0
#define     NFP_MAC_CSR_SERDES_PD_RX_SERDES_LANE_POWER_DOWN_msk (0xffffff)
#define     NFP_MAC_CSR_SERDES_PD_RX_SERDES_LANE_POWER_DOWN_shf (0)


/*
 * Register: SerDesPdSy
 *   [9:5]     SerDesMainResetB
 *   [4:0]     SerDesSynthPowerDown
 *
 * Name(s):
 * <base>.SerDesPdSy
 */
#define NFP_MAC_CSR_SERDES_PD_SY                           0x0808
#define   NFP_MAC_CSR_SERDES_PD_SY_SERDES_MAIN_RESET_B(x)    (((x) & 0x1f) << 5)
#define   NFP_MAC_CSR_SERDES_PD_SY_SERDES_MAIN_RESET_B_of(x) (((x) >> 5) & 0x1f)
#define     NFP_MAC_CSR_SERDES_PD_SY_SERDES_MAIN_RESET_B_bf  0, 9, 5
#define     NFP_MAC_CSR_SERDES_PD_SY_SERDES_MAIN_RESET_B_msk (0x1f)
#define     NFP_MAC_CSR_SERDES_PD_SY_SERDES_MAIN_RESET_B_shf (5)
#define   NFP_MAC_CSR_SERDES_PD_SY_SERDES_SYNTH_POWER_DOWN(x) (((x) & 0x1f) << 0)
#define   NFP_MAC_CSR_SERDES_PD_SY_SERDES_SYNTH_POWER_DOWN_of(x) (((x) >> 0) & 0x1f)
#define     NFP_MAC_CSR_SERDES_PD_SY_SERDES_SYNTH_POWER_DOWN_bf 0, 4, 0
#define     NFP_MAC_CSR_SERDES_PD_SY_SERDES_SYNTH_POWER_DOWN_msk (0x1f)
#define     NFP_MAC_CSR_SERDES_PD_SY_SERDES_SYNTH_POWER_DOWN_shf (0)


/*
 * Register: SerDesCkMuxSel
 *   [31:26]   SerDesCkMuxSel_RFU
 *   [25]      SerDesCkMuxSelGang1918
 *   [24]      SerDesCkMuxSelGang1716
 *   [23]      SerDesCkMuxSelL19
 *   [22]      SerDesCkMuxSelL18
 *   [21]      SerDesCkMuxSelL17
 *   [20]      SerDesCkMuxSelL16
 *   [19]      SerDesCkMuxSelGang1512
 *   [18]      SerDesCkMuxSelL15
 *   [17]      SerDesCkMuxSelL14
 *   [16]      SerDesCkMuxSelL13
 *   [15]      SerDesCkMuxSelL12
 *   [14]      SerDesCkMuxSelGang1108
 *   [13]      SerDesCkMuxSelL11
 *   [12]      SerDesCkMuxSelL10
 *   [11]      SerDesCkMuxSelL09
 *   [10]      SerDesCkMuxSelL08
 *   [9]       SerDesCkMuxSelGang0704
 *   [8]       SerDesCkMuxSelL07
 *   [7]       SerDesCkMuxSelL06
 *   [6]       SerDesCkMuxSelL05
 *   [5]       SerDesCkMuxSelL04
 *   [4]       SerDesCkMuxSelGang0300
 *   [3]       SerDesCkMuxSelL03
 *   [2]       SerDesCkMuxSelL02
 *   [1]       SerDesCkMuxSelL01
 *   [0]       SerDesCkMuxSelL00
 *
 * Name(s):
 * <base>.SerDesCkMuxSel
 */
#define NFP_MAC_CSR_SERDES_CK_MUX_SEL                      0x080c
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_RFU(x) (((x) & 0x3f) << 26)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_RFU_of(x) (((x) >> 26) & 0x3f)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_RFU_bf 0, 31, 26
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_RFU_msk (0x3f)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_RFU_shf (26)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1918 (1 << 25)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1918_bf 0, 25, 25
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1918_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1918_bit (25)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1716 (1 << 24)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1716_bf 0, 24, 24
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1716_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1716_bit (24)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_19 (1 << 23)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_19_bf 0, 23, 23
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_19_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_19_bit (23)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_18 (1 << 22)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_18_bf 0, 22, 22
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_18_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_18_bit (22)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_17 (1 << 21)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_17_bf 0, 21, 21
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_17_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_17_bit (21)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_16 (1 << 20)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_16_bf 0, 20, 20
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_16_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_16_bit (20)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1512 (1 << 19)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1512_bf 0, 19, 19
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1512_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1512_bit (19)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_15 (1 << 18)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_15_bf 0, 18, 18
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_15_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_15_bit (18)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_14 (1 << 17)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_14_bf 0, 17, 17
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_14_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_14_bit (17)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_13 (1 << 16)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_13_bf 0, 16, 16
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_13_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_13_bit (16)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_12 (1 << 15)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_12_bf 0, 15, 15
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_12_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_12_bit (15)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1108 (1 << 14)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1108_bf 0, 14, 14
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1108_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_1108_bit (14)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_11 (1 << 13)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_11_bf 0, 13, 13
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_11_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_11_bit (13)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_10 (1 << 12)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_10_bf 0, 12, 12
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_10_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_10_bit (12)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_09 (1 << 11)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_09_bf 0, 11, 11
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_09_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_09_bit (11)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_08 (1 << 10)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_08_bf 0, 10, 10
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_08_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_08_bit (10)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0704 (1 << 9)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0704_bf 0, 9, 9
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0704_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0704_bit (9)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_07 (1 << 8)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_07_bf 0, 8, 8
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_07_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_07_bit (8)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_06 (1 << 7)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_06_bf 0, 7, 7
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_06_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_06_bit (7)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_05 (1 << 6)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_05_bf 0, 6, 6
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_05_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_05_bit (6)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_04 (1 << 5)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_04_bf 0, 5, 5
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_04_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_04_bit (5)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0300 (1 << 4)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0300_bf 0, 4, 4
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0300_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_GANG_0300_bit (4)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_03 (1 << 3)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_03_bf 0, 3, 3
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_03_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_03_bit (3)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_02 (1 << 2)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_02_bf 0, 2, 2
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_02_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_02_bit (2)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_01 (1 << 1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_01_bf 0, 1, 1
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_01_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_01_bit (1)
#define   NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_00 (1 << 0)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_00_bf 0, 0, 0
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_00_msk (0x1)
#define     NFP_MAC_CSR_SERDES_CK_MUX_SEL_SERDES_CK_MUX_SEL_00_bit (0)


/*
 * Register: SerDesSigDetect
 *   [19:0]    SerDesLaneSigDetect
 *
 * Name(s):
 * <base>.SerDesSigDetect
 */
#define NFP_MAC_CSR_SERDES_SIG_DETECT                      0x0810
#define   NFP_MAC_CSR_SERDES_SIG_DETECT_SERDES_LANE_SIGNAL_DETECT(x) (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_SERDES_SIG_DETECT_SERDES_LANE_SIGNAL_DETECT_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_SERDES_SIG_DETECT_SERDES_LANE_SIGNAL_DETECT_bf 0, 19, 0
#define     NFP_MAC_CSR_SERDES_SIG_DETECT_SERDES_LANE_SIGNAL_DETECT_msk (0xfffff)
#define     NFP_MAC_CSR_SERDES_SIG_DETECT_SERDES_LANE_SIGNAL_DETECT_shf (0)


/*
 * Register: SerDesSigDetectOvr
 *   [19:0]    SerDesLaneSigDetectOvr
 *
 * Name(s):
 * <base>.SerDesSigDetectOvr
 */
#define NFP_MAC_CSR_SERDES_SIG_DETECT_OVR                  0x0814
#define   NFP_MAC_CSR_SERDES_SIG_DETECT_OVR_SERDES_LANE_SIGNAL_DETECT_OVR(x) (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_SERDES_SIG_DETECT_OVR_SERDES_LANE_SIGNAL_DETECT_OVR_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_SERDES_SIG_DETECT_OVR_SERDES_LANE_SIGNAL_DETECT_OVR_bf 0, 19, 0
#define     NFP_MAC_CSR_SERDES_SIG_DETECT_OVR_SERDES_LANE_SIGNAL_DETECT_OVR_msk (0xfffff)
#define     NFP_MAC_CSR_SERDES_SIG_DETECT_OVR_SERDES_LANE_SIGNAL_DETECT_OVR_shf (0)


/*
 * Register: SerDesActDetect
 *   [19:0]    SerDesPortActDetect
 *
 * Name(s):
 * <base>.SerDesEthRxActDetect <base>.SerDesEthTxActDetect
 */
#define NFP_MAC_CSR_SERDES_ETH_RX_ACT_DETECT               0x0818
#define NFP_MAC_CSR_SERDES_ETH_TX_ACT_DETECT               0x081c
#define   NFP_MAC_CSR_SERDES_ETH_RX_ACT_DETECT_SERDES_PORT_ACTIVITY_DETECT(x) (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_SERDES_ETH_RX_ACT_DETECT_SERDES_PORT_ACTIVITY_DETECT_of(x) (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_SERDES_ETH_RX_ACT_DETECT_SERDES_PORT_ACTIVITY_DETECT_bf 0, 19, 0
#define     NFP_MAC_CSR_SERDES_ETH_RX_ACT_DETECT_SERDES_PORT_ACTIVITY_DETECT_msk (0xfffff)
#define     NFP_MAC_CSR_SERDES_ETH_RX_ACT_DETECT_SERDES_PORT_ACTIVITY_DETECT_shf (0)


/*
 * Register: SerDesLinkUp
 *   [19:0]    SerDesLinkUp
 *
 * Name(s):
 * <base>.SerDesLinkUp
 */
#define NFP_MAC_CSR_SERDES_LINK_UP                         0x0820
#define   NFP_MAC_CSR_SERDES_LINK_UP_SERDES_LINK_UP(x)       (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_SERDES_LINK_UP_SERDES_LINK_UP_of(x)    (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_SERDES_LINK_UP_SERDES_LINK_UP_bf     0, 19, 0
#define     NFP_MAC_CSR_SERDES_LINK_UP_SERDES_LINK_UP_msk    (0xfffff)
#define     NFP_MAC_CSR_SERDES_LINK_UP_SERDES_LINK_UP_shf    (0)


/*
 * Register: ParityErrInject
 *   [5]       InjectIgParErrDescMem
 *   [4]       InjectIgParErrTsmpMem
 *   [3]       InjectIgParErrRsltMem
 *   [2]       InjectEgParErrDescMem
 *   [1]       InjectEgParErrRslt1Mem
 *   [0]       InjectEgParErrRslt0Mem
 *
 * Name(s):
 * <base>.ParityErrInject
 */
#define NFP_MAC_CSR_PARITY_ERR_INJECT                      0x0824
#define   NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_DESC_MEM (1 << 5)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_DESC_MEM_bf 0, 5, 5
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_DESC_MEM_msk (0x1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_DESC_MEM_bit (5)
#define   NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_TSMP_MEM (1 << 4)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_TSMP_MEM_bf 0, 4, 4
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_TSMP_MEM_msk (0x1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_TSMP_MEM_bit (4)
#define   NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_RSLT_MEM (1 << 3)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_RSLT_MEM_bf 0, 3, 3
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_RSLT_MEM_msk (0x1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_IG_PAR_ERR_RSLT_MEM_bit (3)
#define   NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_DESC_MEM (1 << 2)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_DESC_MEM_bf 0, 2, 2
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_DESC_MEM_msk (0x1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_DESC_MEM_bit (2)
#define   NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT1_MEM (1 << 1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT1_MEM_bf 0, 1, 1
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT1_MEM_msk (0x1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT1_MEM_bit (1)
#define   NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT0_MEM (1 << 0)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT0_MEM_bf 0, 0, 0
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT0_MEM_msk (0x1)
#define     NFP_MAC_CSR_PARITY_ERR_INJECT_INJECT_EG_PAR_ERR_RSLT0_MEM_bit (0)


/*
 * Register: BlockLock
 *   [19:0]    BlockLock
 *
 * Name(s):
 * <base>.BlockLock
 */
#define NFP_MAC_CSR_BLOCK_LOCK                             0x082c
#define   NFP_MAC_CSR_BLOCK_LOCK_BLOCK_LOCK(x)               (((x) & 0xfffff) << 0)
#define   NFP_MAC_CSR_BLOCK_LOCK_BLOCK_LOCK_of(x)            (((x) >> 0) & 0xfffff)
#define     NFP_MAC_CSR_BLOCK_LOCK_BLOCK_LOCK_bf             0, 19, 0
#define     NFP_MAC_CSR_BLOCK_LOCK_BLOCK_LOCK_msk            (0xfffff)
#define     NFP_MAC_CSR_BLOCK_LOCK_BLOCK_LOCK_shf            (0)


/*
 * Register: IgParityErrStatus
 *   [14:12]   IgParErrType
 *   [10:0]    IgParErrAddr
 *
 * Name(s):
 * <base>.IgParityErrStatus
 */
#define NFP_MAC_CSR_IG_PARITY_ERR_STATUS                   0x0840
#define   NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_TYPE(x) (((x) & 7) << 12)
#define   NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_TYPE_of(x) (((x) >> 12) & 7)
#define     NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_TYPE_bf 0, 14, 12
#define     NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_TYPE_msk (0x7)
#define     NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_TYPE_shf (12)
#define   NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_ADDR(x) (((x) & 0x7ff) << 0)
#define   NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_ADDR_of(x) (((x) >> 0) & 0x7ff)
#define     NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_ADDR_bf 0, 10, 0
#define     NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_ADDR_msk (0x7ff)
#define     NFP_MAC_CSR_IG_PARITY_ERR_STATUS_IG_PAR_ERR_ADDR_shf (0)


/*
 * Register: EgParityErrStatus
 *   [30:28]   EgParErrType1
 *   [25:16]   EgParErrAddr1
 *   [14:12]   EgParErrType0
 *   [9:0]     EgParErrAddr0
 *
 * Name(s):
 * <base>.EgParityErrStatus
 */
#define NFP_MAC_CSR_EG_PARITY_ERR_STATUS                   0x0844
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE1(x) (((x) & 7) << 28)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE1_of(x) (((x) >> 28) & 7)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE1_bf 0, 30, 28
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE1_msk (0x7)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE1_shf (28)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR1(x) (((x) & 0x3ff) << 16)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR1_of(x) (((x) >> 16) & 0x3ff)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR1_bf 0, 25, 16
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR1_msk (0x3ff)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR1_shf (16)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE0(x) (((x) & 7) << 12)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE0_of(x) (((x) >> 12) & 7)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE0_bf 0, 14, 12
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE0_msk (0x7)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_TYPE0_shf (12)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR0(x) (((x) & 0x3ff) << 0)
#define   NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR0_of(x) (((x) >> 0) & 0x3ff)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR0_bf 0, 9, 0
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR0_msk (0x3ff)
#define     NFP_MAC_CSR_EG_PARITY_ERR_STATUS_EG_PAR_ERR_ADDR0_shf (0)


/*
 * Register: MemErrDropCounts
 *   [31:24]   IgMemErrDrop1
 *   [23:16]   IgMemErrDrop0
 *   [15:8]    EgMemErrDrop1
 *   [7:0]     EgMemErrDrop0
 *
 * Name(s):
 * <base>.MemErrDropCounts
 */
#define NFP_MAC_CSR_MEM_ERR_DROP_COUNTS                    0x0848
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_1(x) (((x) & 0xff) << 24)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_1_of(x) (((x) >> 24) & 0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_1_bf 0, 31, 24
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_1_msk (0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_1_shf (24)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_0(x) (((x) & 0xff) << 16)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_0_of(x) (((x) >> 16) & 0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_0_bf 0, 23, 16
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_0_msk (0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_IG_MEM_ERR_DROP_0_shf (16)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_1(x) (((x) & 0xff) << 8)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_1_of(x) (((x) >> 8) & 0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_1_bf 0, 15, 8
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_1_msk (0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_1_shf (8)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_0(x) (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_0_of(x) (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_0_bf 0, 7, 0
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_0_msk (0xff)
#define     NFP_MAC_CSR_MEM_ERR_DROP_COUNTS_EG_MEM_ERR_DROP_0_shf (0)


/*
 * Register: AssertConfig0
 *   [31:0]    AssertConfigCsr0
 *
 * Name(s):
 * <base>.AssertConfig0
 */
#define NFP_MAC_CSR_ASSERT_CONFIG_CSR0                     0x084c
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR0_ASSERT_CONFIG_CSR0(x) (((x) & 0xffffffff) << 0)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR0_ASSERT_CONFIG_CSR0_of(x) (((x) >> 0) & 0xffffffff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR0_ASSERT_CONFIG_CSR0_bf 0, 31, 0
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR0_ASSERT_CONFIG_CSR0_msk (0xffffffff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR0_ASSERT_CONFIG_CSR0_shf (0)


/*
 * Register: AssertConfig1
 *   [31:18]   AssertConfigCsr1Disable
 *   [17]      AssertConfigCsr1EnaFsm1
 *   [16]      AssertConfigCsr1EnaFsm0
 *   [15:8]    AssertConfigCsr1FsmCfg1
 *   [7:0]     AssertConfigCsr1FsmCfg0
 *
 * Name(s):
 * <base>.AssertConfig1
 */
#define NFP_MAC_CSR_ASSERT_CONFIG_CSR1                     0x0850
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_DISABLE(x) (((x) & 0x3fff) << 18)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_DISABLE_of(x) (((x) >> 18) & 0x3fff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_DISABLE_bf 0, 31, 18
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_DISABLE_msk (0x3fff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_DISABLE_shf (18)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM1 (1 << 17)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM1_bf 0, 17, 17
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM1_msk (0x1)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM1_bit (17)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM0 (1 << 16)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM0_bf 0, 16, 16
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM0_msk (0x1)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_ENA_FSM0_bit (16)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG1(x) (((x) & 0xff) << 8)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG1_of(x) (((x) >> 8) & 0xff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG1_bf 0, 15, 8
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG1_msk (0xff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG1_shf (8)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG0(x) (((x) & 0xff) << 0)
#define   NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG0_of(x) (((x) >> 0) & 0xff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG0_bf 0, 7, 0
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG0_msk (0xff)
#define     NFP_MAC_CSR_ASSERT_CONFIG_CSR1_ASSERT_CONFIG_CSR1_FSM_CFG0_shf (0)


/*
 * Macros for Mac statistics
 */
/* EthPortStatsHyd: <base>.MacEthPortStatsHyd0... */
#define NFP_MAC_STATS_MAC_ETH_PORT_STATS_HY(x)             (0x0000 + ((x) * 0x1000))
/* ChannelStatsSeg: <base>.MacChannelStats0... */
#define NFP_MAC_STATS_MAC_CHNL_STATS(x)                    (0x10000 + ((x) * 0x100))


#endif /* !_NFP3800__NFP_MAC_H_ */
