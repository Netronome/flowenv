/*
 * Copyright (C) 2015,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/nfp/_c/macstats.c
 * @brief         Read, and optionally accumulate, per port and per channel
 *                MAC statistics.
 */

#include <nfp6000/nfp_me.h>
#include <assert.h>
#include <nfp/macstats.h>


/* Definitions for MACs/Ports/Channels numbers */
#define MAX_MAC_NUMBER      1
#define MAX_PORT_NUMBER     23
#define PORTS_PER_MAC_CORE  12
#define MAX_CHANNEL_NUMBER  127

/* Base addresses for MAC stats access */
#define MACSTATS_BASE           0x100000
#define MACSTATS_HYD0_PORT_BASE (MACSTATS_BASE + 0)
#define MACSTATS_HYD1_PORT_BASE (MACSTATS_BASE + 0x1000)
#define MACSTATS_CHANNEL_BASE   (MACSTATS_BASE + 0x10000)
/* Per port and per channel stats size */
#define MACSTATS_PER_CORE_PORT_SIZE 4096
#define MACSTATS_PER_PORT_SIZE      256
#define MACSTATS_PER_CHANNEL_SIZE   256

#define MACSTATS_CHAN_ADDR_HI(_mac) ((mac) << 30)
#define MACSTATS_CHAN_ADDR_LO(_ch) (MACSTATS_CHANNEL_BASE + \
                                    (_ch) * MACSTATS_PER_CHANNEL_SIZE)

#define MACSTATS_PORT_ADDR_HI(_mac) ((mac) << 30)
#define MACSTATS_PORT_ADDR_LO(_core, _seg) \
                (MACSTATS_BASE + (_core)* MACSTATS_PER_CORE_PORT_SIZE + \
                 (_seg) * MACSTATS_PER_PORT_SIZE)

/* Read 8 stats values from nbi and write to destination */
__intrinsic static void
mac_stats_load(__gpr unsigned int src_hi, __gpr unsigned int src_lo,
               __gpr unsigned int dst_hi, __gpr unsigned int dst_lo)
{
    __xrw unsigned int stats[8];
    SIGNAL sig;
    __asm {
        nbi[read, stats[0], src_hi, <<8, src_lo, 4], ctx_swap[sig];
        alu[stats[0], --, B, stats[1]];
        alu[stats[1], --, B, stats[0]];
        alu[stats[2], --, B, stats[3]];
        alu[stats[3], --, B, stats[2]];
        alu[stats[4], --, B, stats[5]];
        alu[stats[5], --, B, stats[4]];
        alu[stats[6], --, B, stats[7]];
        alu[stats[7], --, B, stats[6]];
        mem[write, stats[0], dst_hi, <<8, dst_lo, 4], ctx_swap[sig];
    }
}

/* Read 8 stats values from nbi and add to destination */
__intrinsic static void
mac_stats_add(__gpr unsigned int src_hi, __gpr unsigned int src_lo,
              __gpr unsigned int dst_hi, __gpr unsigned int dst_lo)
{
    __xrw unsigned int stats[8];
    SIGNAL sig;
    __gpr unsigned int dst_lo2 = dst_lo + 32;
    __asm {
        nbi[read, stats[0], src_hi, <<8, src_lo, 4], ctx_swap[sig];
        alu[stats[0], --, B, stats[0]];
        alu[stats[2], --, B, stats[1]];
        alu[stats[4], --, B, stats[2]];
        alu[stats[6], --, B, stats[3]];
        mem[add64, stats[0], dst_hi, <<8, dst_lo, 4], ctx_swap[sig];
        alu[stats[0], --, B, stats[4]];
        alu[stats[2], --, B, stats[5]];
        alu[stats[4], --, B, stats[6]];
        alu[stats[6], --, B, stats[7]];
        mem[add64, stats[0], dst_hi, <<8, dst_lo2, 4], ctx_swap[sig];
    }
}

int
macstats_port_read(unsigned int mac, unsigned int port,
                   __mem struct macstats_port *port_stats)
{
    unsigned char core;
    unsigned char seg;
    __gpr unsigned int src_hi;
    __gpr unsigned int src_lo;
    __gpr unsigned int dst_hi;
    __gpr unsigned int dst_lo;
    __gpr unsigned int off;

    if (mac > MAX_MAC_NUMBER)
        return -1;

    if (port > MAX_PORT_NUMBER)
        return -1;

    if (port >= PORTS_PER_MAC_CORE)
        core = 1;
    else
        core = 0;
    seg = port - (core * PORTS_PER_MAC_CORE);

    src_hi = MACSTATS_PORT_ADDR_HI(mac);
    src_lo = MACSTATS_PORT_ADDR_LO(core, seg);

    dst_hi = (((unsigned long long)port_stats) >> 8) & 0xFF000000;
    dst_lo = ((unsigned long long)port_stats) & 0xFFFFFFFF;

    for (off = 0; off < sizeof(struct macstats_port); off += 32)
        mac_stats_load(src_hi, src_lo + off, dst_hi, dst_lo + off);

    return 0;
}

int
macstats_port_accum(unsigned int mac, unsigned int port,
                    __mem struct macstats_port_accum *port_stats)
{
    unsigned char core;
    unsigned char seg;
    __gpr unsigned int src_hi;
    __gpr unsigned int src_lo;
    __gpr unsigned int dst_hi;
    __gpr unsigned int dst_lo;
    __gpr unsigned int off;

    if (mac > MAX_MAC_NUMBER)
        return -1;

    if (port > MAX_PORT_NUMBER)
        return -1;

    if (port >= PORTS_PER_MAC_CORE)
        core = 1;
    else
        core = 0;
    seg = port - (core * PORTS_PER_MAC_CORE);

    src_hi = MACSTATS_PORT_ADDR_HI(mac);
    src_lo = MACSTATS_PORT_ADDR_LO(core, seg);

    dst_hi = (((unsigned long long)port_stats) >> 8) & 0xFF000000;
    dst_lo = ((unsigned long long)port_stats) & 0xFFFFFFFF;

    for (off = 0; off < sizeof(struct macstats_port); off += 32)
        mac_stats_add(src_hi, src_lo + off, dst_hi, dst_lo + 2*off);

    /* Fix 40 bit stats accumulation */
    port_stats->RxPIfInOctets += (port_stats->RxPIfInOctets_unused << 32);
    port_stats->RxPIfInOctets_unused = 0;
    port_stats->TxPIfOutOctets += (port_stats->TxPIfOutOctets_unused << 32);
    port_stats->TxPIfOutOctets_unused = 0;

    return 0;
}

int
macstats_channel_read(unsigned int mac, unsigned int channel,
                      __mem struct macstats_channel *channel_stats)
{
    __gpr unsigned int src_hi;
    __gpr unsigned int src_lo;
    __gpr unsigned int src_lo_base;
    __gpr unsigned int dst_hi;
    __gpr unsigned int dst_lo;
    __gpr unsigned int off;

    if (mac > MAX_MAC_NUMBER)
        return -1;

    if (channel > MAX_CHANNEL_NUMBER)
        return -1;

    src_hi = MACSTATS_CHAN_ADDR_HI(mac);
    src_lo = MACSTATS_CHAN_ADDR_LO(channel);

    dst_hi = (((unsigned long long)channel_stats) >> 8) & 0xFF000000;
    dst_lo = ((unsigned long long)channel_stats) & 0xFFFFFFFF;

    for (off = 0; off < sizeof(struct macstats_channel); off += 32)
        mac_stats_load(src_hi, src_lo + off, dst_hi, dst_lo + off);

    return 0;
}

int
macstats_channel_accum(unsigned int mac, unsigned int channel,
                       __mem struct macstats_channel_accum *channel_stats)
{
    __gpr unsigned int src_hi;
    __gpr unsigned int src_lo;
    __gpr unsigned int dst_hi;
    __gpr unsigned int dst_lo;
    __gpr unsigned int off;

    if (mac > MAX_MAC_NUMBER)
        return -1;

    if (channel > MAX_CHANNEL_NUMBER)
        return -1;

    src_hi = MACSTATS_CHAN_ADDR_HI(mac);
    src_lo = MACSTATS_CHAN_ADDR_LO(channel);

    dst_hi = (((unsigned long long)channel_stats) >> 8) & 0xFF000000;
    dst_lo = ((unsigned long long)channel_stats) & 0xFFFFFFFF;

    for (off = 0; off < sizeof(struct macstats_channel); off += 32)
        mac_stats_add(src_hi, src_lo + off, dst_hi, dst_lo + 2*off);

    /* Fix 40 bit stats accumulation */
    channel_stats->RxCIfInOctets +=
            (channel_stats->RxCIfInOctets_unused << 32);
    channel_stats->RxCIfInOctets_unused = 0;
    channel_stats->RxCStatsOctets +=
            (channel_stats->RxCStatsOctets_unused << 32);
    channel_stats->RxCStatsOctets_unused = 0;
    channel_stats->TxCIfOutOctets +=
            (channel_stats->TxCIfOutOctets_unused << 32);
    channel_stats->TxCIfOutOctets_unused = 0;

    return 0;
}