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
 * @file          lib/qos_te/wred.h
 * @brief         Interface for ME-based WRED.
 */

#ifndef __WRED_H__
#define __WRED_H__

#include <nfp/mem_atomic.h>
#include <qos_te/red.h>


/*
 * Implementation Details
 *
 *     The ME-based Weighted Random Early Discard (WRED) feature implements the
 *     RED algorithm for packets based on the color of the packet.  The WRED
 *     configuration data-structure supports independent thresholds for each
 *     packet color.  Four packet colors are supported by this implementation:
 *         - No-Color
 *         - Green
 *         - Yellow
 *         - Red
 *
 *     For implementation details of the RED algorithm, see <qos_te/red.h>.
 *
 * Usage Guidelines
 *
 *     The following are the steps required to use the ME-based Weighted Random
 *     Early Discard (WRED) functionality:
 *
 *     1.  Set the WRED configuration for the desired NBI TM queue(s):
 *         e.g.
 *             __lmem struct wred_cfg_info sample_wred_cfg;
 *             sample_wred_cfg.no_color.thresh_drop = <no-color 100% thresh>
 *             sample_wred_cfg.no_color.thresh_red  = <no-color random thresh>
 *             sample_wred_cfg.green.thresh_drop    = <green 100% thresh>
 *             sample_wred_cfg.green.thresh_red     = <green random thresh>
 *             sample_wred_cfg.yellow.thresh_drop   = <yellow 100% thresh>
 *             sample_wred_cfg.yellow.thresh_red    = <yellow random thresh>
 *             sample_wred_cfg.red.thresh_drop      = <red 100% thresh>
 *             sample_wred_cfg.red.thresh_red       = <red random thresh>
 *             wred_calc_mult(&sample_wred_cfg);
 *
 *     2.  Check or poll the queue level of the desired NBI TM queue(s).
 *
 *     3.  Check the WRED drop decision before sending packets to the desired
 *         NBI TM queue(s).
 *         e.g.
 *             if (wred_check_packet_drop(<outbound packet color>,
 *                                        <polled TM queue level>,
 *                                        &sample_wred_cfg))
 *                 <drop packet>
 *             else
 *                 <pass packet>
 *
 * Other Notes and Recommendations
 *
 *     1. For most WRED use cases, the following should be true:
 *        a. "red.thresh_drop" <= "yellow.thresh_drop" <= "green.thresh_drop"
 *        b. "red.thresh_red" <= "yellow.thresh_red" <= "green.thresh_red"
 *
 *     2. For other notes and recommendations about configuration thresholds,
 *        see the "Other Notes and Recommendations" section in <qos_te/red.h>.
 */


/** Enumeration of WRED packet colors. */
enum wred_pkt_color {
    /* Note: Use a value that distinguishes no-color from green. */
    WRED_NO_COLOR = METER_COLOR_GREEN - 1,
    WRED_GREEN    = METER_COLOR_GREEN,
    WRED_YELLOW   = METER_COLOR_YELLOW,
    WRED_RED      = METER_COLOR_RED
};

/**
 * Macro to convert meter color to WRED packet color.
 * @note The resulting packet color from the atomic engine metering command
 *       makes no distinction between no-color and green; both will translate
 *       to a WRED packet color of green.
 */
#define METER_COLOR_TO_WRED_COLOR(_meter_color) \
    ((enum wred_pkt_color) (_meter_color))

/** Data-structure for WRED configuration. */
struct wred_cfg_info {
    struct red_cfg_info no_color; /**< No-color WRED configuration. */
    struct red_cfg_info green;    /**< Green WRED configuration. */
    struct red_cfg_info yellow;   /**< Yellow WRED configuration. */
    struct red_cfg_info red;      /**< Red WRED configuration. */
};


/**
 * Method for calculating the multiplier values for WRED.
 * @param wred_cfg  Pointer to WRED configuration
 * @note All (W)RED and drop thresholds must be set before calling this method.
 * @note This function modifies the 'red_mult' data members within 'wred_cfg'.
 */
__intrinsic void wred_calc_mult(__lmem struct wred_cfg_info *wred_cfg);

/**
 * Method for checking if a packet should be dropped based on WRED.
 * @param color      Color of the packet that is being checked
 * @param tmq_level  Current/last-measured NBI TM queue level
 * @param wred_cfg   WRED configuration for the NBI TM queue
 * @return 1 if packet should be dropped, 0 if packet should be enqueued
 */
__intrinsic int wred_check_packet_drop(enum wred_pkt_color color,
                                       unsigned int tmq_level,
                                       __lmem struct wred_cfg_info *wred_cfg);


#endif /* __WRED_H__ */
