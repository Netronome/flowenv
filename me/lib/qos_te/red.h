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
 * @file          lib/qos_te/red.h
 * @brief         Interface for ME-based Random Early Discard (RED).
 */

#ifndef __RED_H__
#define __RED_H__

#include <nfp.h>
#include <stdint.h>


/*
 * Implementation Details
 *
 *     The ME-based Random Early Discard (RED) feature implements the following
 *     algorithm:
 *
 *         drop probability = (current level - "thresh_red") /
 *                            ("thresh_drop" - "thresh_red")
 *         if drop probability > 100%, then
 *             drop decision = true
 *         else if drop probability > 0%, then
 *             random probability = random value from 0% - 100%
 *             if random probability < drop probability, then
 *                 drop decision = false
 *             else
 *                 drop decision = true
 *         else
 *             drop decision = false
 *
 * Usage Guidelines
 *
 *     The following are the steps required to use the ME-based Random Early
 *     Discard (RED) functionality:
 *
 *     1.  Set the RED configuration for the desired NBI TM queue(s):
 *         e.g.
 *             __lmem struct red_cfg_info sample_red_cfg;
 *             sample_red_cfg.thresh_drop = <100% packet drop threshold>
 *             sample_red_cfg.thresh_red  = <random packet drop threshold>
 *             red_calc_mult(&sample_red_cfg);
 *
 *     2.  Check or poll the queue level of the desired NBI TM queue(s).
 *
 *     3.  Check the RED drop decision before sending packets to the desired
 *         NBI TM queue(s).
 *         e.g.
 *             if (red_check_packet_drop(<polled TM queue level>,
 *                                       &sample_red_cfg))
 *                 <drop packet>
 *             else
 *                 <pass packet>
 *
 * Other Notes and Recommendations
 *
 *     1. If random packet dropping is desired, then the following should be
 *        true about the configuration thresholds:
 *        a. ("thresh_red" + 1) < "thresh_drop"
 *        b. ("thresh_red" + 1) < NBI TM queue size
 *
 *     2. If random packet dropping is undesired, then the following should be
 *        true about the configuration thresholds:
 *        a. "thresh_red" >= "thresh_drop"
 *
 *     3. If any of the configurable thresholds are higher than the NBI TM
 *        queue size, those thresholds will never trigger.
 */


/** Data-structure for RED configuration. */
struct red_cfg_info {
    uint16_t thresh_drop; /**< Threshold where drop % is 100% (0-32768). */
    uint16_t thresh_red;  /**< Threshold where RED kicks in (0-32768). */
    /**
     * RED multiplier (used for RED drop probability calculation).
     * @note Should be set to (0x8000 / (thresh_drop - thresh_red)).
     */
    uint16_t red_mult;
    uint16_t __rsvd;      /**< Reserved for future use. */
};


/**
 * Method for calculating the RED multiplier value.
 * @param red_cfg  Pointer to RED configuration
 * @note The RED and drop thresholds must be set before calling this method.
 * @note This function modifies the 'red_mult' data member within 'red_cfg'.
 */
__intrinsic void red_calc_mult(__lmem struct red_cfg_info *red_cfg);

/**
 * Method for checking if a packet should be dropped based on RED.
 * @param tmq_level  Current/last-measured NBI TM queue level
 * @param red_cfg    RED configuration for the NBI TM queue
 * @return 1 if packet should be dropped, 0 if packet should be enqueued
 */
__intrinsic int red_check_packet_drop(unsigned int tmq_level,
                                      __lmem struct red_cfg_info *red_cfg);


#endif /* __RED_H__ */
