/*
 * Copyright (C) 2016-2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file   lib/npfw/_c/catamaran_app_utils.c
 * @brief  Application-specific ME-based tool for configuring Catamaran NPFW
 */

#include <platform.h>
#include <catamaran_defs.h>

#include <npfw/catamaran_app_utils.h>
#include <npfw/catamaran_utils.h>

/** Maximum number of channels per port. */
#ifndef MAX_CHANNELS_PER_PORT
#define MAX_CHANNELS_PER_PORT 8
#endif

/* Some platforms do not number ports consecutively so the highest
 * port number is greater than the highest port number on the platform.
 * Support either use case by computing NS_PLATFORM_MAX_PORT_NUM if
 * it is not defined, assuming the consecutive port case.
 */
#ifndef NS_PLATFORM_MAX_PORT_NUM
#define NS_PLATFORM_MAX_PORT_NUM (NS_PLATFORM_NUM_PORTS - 1)
#endif


/* set all the LB final sequencers to 1 */
void
catamaran_app_lb_single_sequencer_set(void)
{
    unsigned int i;
    __shared __lmem struct catamaran_lb_entry lmem_vals[16];

    for (i = 0; i < 16; i++)
        lmem_vals[i]._raw = 1;

    for (i = 0; i < 256 / 16; i++)
        catamaran_lb_table_set(0, i * 16, i * 16 + 15, lmem_vals);
}


void
catamaran_app_chan2port_table_init(void)
{
    unsigned int chan;
    unsigned int entry_cnt;
    unsigned int port;
    __lmem struct catamaran_chan2port_entry entries[MAX_CHANNELS_PER_PORT];

    /* Set the configuration for each port. */
    for (port = 0; port <= NS_PLATFORM_MAX_PORT_NUM; ++port) {
#ifdef NS_PLATFORM_PORT_IS_PRESENT
        if (!NS_PLATFORM_PORT_IS_PRESENT(port))
            continue;
#endif

        /* Set the configuration for each channel assigned to the port. */
        entry_cnt = 0;

        for (chan = NS_PLATFORM_MAC_CHANNEL_LO(port);
             chan <= NS_PLATFORM_MAC_CHANNEL_HI(port);
             ++chan) {
            entries[entry_cnt].port      = port;
            entries[entry_cnt].port_mode = CATAMARAN_CHAN_MODE_MAC_DA_MATCH;
            ++entry_cnt;
        }

        /* Commit the configuration for the port. */
        catamaran_chan2port_table_set(NS_PLATFORM_MAC(port),
                                      NS_PLATFORM_MAC_CHANNEL_LO(port),
                                      NS_PLATFORM_MAC_CHANNEL_HI(port),
                                      entries);
    }
}
