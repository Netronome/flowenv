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
 * @file        lib/qos_te/_c/geared.c
 * @brief       Functions to implement ME-based GEARED.
 */

#include <qos_te/geared.h>


__intrinsic int
geared_check_packet_drop(enum wred_pkt_color color, unsigned int prio,
                         unsigned int num_prios, __lmem uint16_t *tmq_levels,
                         __lmem struct wred_cfg_info *wred_cfgs)
{
    int i;
    unsigned int geared_thresh;
    int geared_drop_decision = wred_check_packet_drop(color, tmq_levels[prio],
                                                      &(wred_cfgs[prio]));

    if (!geared_drop_decision && (color ==  WRED_YELLOW)) {
        /* Check if lower priorities might drop guaranteed packets. */
        geared_thresh = 0;

        for (i = prio + 1; i < num_prios; ++i) {
            /* Compute the TM queue level where guaranteed drops may occur. */
            geared_thresh += wred_cfgs[i].yellow.thresh_drop;

            if (geared_thresh < tmq_levels[i]) {
                geared_drop_decision = 1;
                break;
            }
        }
    } else if (!geared_drop_decision && (color ==  WRED_RED)) {
        /* Check if lower priorities might drop guaranteed packets. */
        geared_thresh = 0;

        for (i = prio + 1; i < num_prios; ++i) {
            /* Compute the TM queue level where guaranteed drops may occur. */
            geared_thresh += wred_cfgs[i].red.thresh_drop;

            if (geared_thresh < tmq_levels[i]) {
                geared_drop_decision = 1;
                break;
            }
        }
    }

    return geared_drop_decision;
}
