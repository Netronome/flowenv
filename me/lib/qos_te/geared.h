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
 * @file          lib/qos_te/geared.h
 * @brief         Interface for ME-based Guaranteed-Excess-Aware RED (GEARED).
 */

#ifndef __GEARED_H__
#define __GEARED_H__

#include <qos_te/wred.h>


/*
 * Feature Description
 *
 *     Guaranteed-Excess-Aware Random Early Discard (GEARED) is a congestion
 *     management technique.  GEARED is intended for scenarios where flows
 *     (however flows are defined) are assigned a traffic profile; this traffic
 *     profile defines the following:
 *         - Guaranteed bandwidth - The amount of bandwidth reserved for the
 *                                  flow
 *         - Excess bandwidth     - The amount of additional bandwidth the flow
 *                                  may use, if bandwidth is available to use
 *
 *     These traffic profiles can be implemented using a three-colored marker,
 *     such as ones defined by IETF RFC-2697, RFC-2698 or RFC-4115.  The three
 *     packet colors are re-interpreted as follows:
 *         - Green  - The packet is within the guaranteed bandwidth profile
 *         - Yellow - The packet is outside of the guaranteed bandwidth
 *                    profile, but within the excess bandwidth profile
 *         - Red    - The packet is outside of both the guaranteed and excess
 *                    bandwidth profiles
 *
 *     GEARED is used to enforce these traffic profiles.  The GEARED algorithm
 *     is designed to drop packets marked as "excess" first beforedropping
 *     packets marked as "guaranteed".  This is done by recognizing when
 *     other queues belonging to the same scheduler are in danger of dropping
 *     "guaranteed" packets.
 *
 *     GEARED works independently from the packet scheduler algorithm, and
 *     therefore can work with different scheduler configurations.
 *
 * Implementation Details
 *
 *     The ME-based Guaranteed-Excess-Aware Random Early Discard (GEARED)
 *     feature implements the GEARED algorithm for packets based on the color
 *     of the packet as well as the level of all the queues associated with a
 *     packet scheduler.  The GEARED algorithm uses the WRED configuration
 *     data-structure for the RED thresholds for each packet color.
 *
 *     Note: This implementation treats no-color packets as if they are also
 *           within the guaranteed bandwidth profile.
 *
 *     For details about the configuration data-structure, see <qos_te/wred.h>.
 *
 *     For implementation details of the RED algorithm, see <qos_te/red.h>.
 *
 * Usage Guidelines
 *
 *     The following are the steps required to use the ME-based Guaranteed-
 *     Excess-Aware Random Early Discard (GEARED) functionality:
 *
 *     1.  Set the GEARED configuration for the desired NBI TM queue(s):
 *         e.g.
 *             unsigned int i;
 *             __lmem struct wred_cfg_info geared_cfg[<num of prios>];
 *             for (int i = 0; i < <num of prios>; ++i) {
 *                 geared_cfg[i].no_color.thresh_drop = <no-color 100% thresh>;
 *                 geared_cfg[i].no_color.thresh_red  = <no-color rand thresh>;
 *                 geared_cfg[i].green.thresh_drop    = <green 100% thresh>;
 *                 geared_cfg[i].green.thresh_red     = <green rand thresh>;
 *                 geared_cfg[i].yellow.thresh_drop   = <yellow 100% thresh>;
 *                 geared_cfg[i].yellow.thresh_red    = <yellow rand thresh>;
 *                 geared_cfg[i].red.thresh_drop      = <red 100% thresh>;
 *                 geared_cfg[i].red.thresh_red       = <red rand thresh>;
 *                 wred_calc_mult(&(geared_cfg[i]));
 *             }
 *
 *     2.  Check or poll the queue level of the desired NBI TM queue(s).
 *
 *     3.  Check the GEARED drop decision before sending packets to the desired
 *         NBI TM queue(s).
 *         e.g.
 *             if (geared_check_packet_drop(<outbound packet color>,
 *                                          <packet scheduler priority>,
 *                                          <polled TM scheduler queue levels>,
 *                                          geared_cfg))
 *                 <drop packet>
 *             else
 *                 <pass packet>
 *
 * Other Notes and Recommendations
 *
 *     1. For most GEARED use cases, the following should be true:
 *        a. Given N := <number of packet scheduler queues/priorities>
 *           Given Priority[x] := <priority of a given scheduler queue x>
 *           Given Size[x] := <size of given scheduler queue x>
 *           Given Sum[x], where Sum[x] is defined as follows:
 *               for x = 0 to (N-1)
 *               Sum[x] = 0
 *               for i = 0 to (N-1)
 *                   if (i != x) and (Priority[i] >= Priority[x])
 *                       Sum[x] = Sum[x] + geared_cfg[i].yellow.thresh_drop
 *           Then, for all x from 0 to (N-1), Sum[x] < Size[x]
 *
 *           * Here is an example configuration that meets the above criteria:
 *                 N := 4 scheduler queues/priorities
 *                 Priority[x] := [ Queue 0 : Strict Priority (Highest),
 *                                  Queue 1 : Strict Priority (2nd Highest),
 *                                  Queue 2 : DWRR (Tied For Lowest),
 *                                  Queue 3 : DWRR (Tied For Lowest) ]
 *                 Size[x] := [ Queue 0 : 32,
 *                              Queue 1 : 32,
 *                              Queue 2 : 64,
 *                              Queue 3 : 64 ]
 *                 geared_cfg[x].yellow.thresh_drop := [ Queue 0 : 16,
 *                                                       Queue 1 : 16,
 *                                                       Queue 2 : 16,
 *                                                       Queue 3 : 16 ]
 *                 Sum[x] := [ Queue 0 : 0,
 *                             Queue 1 : geared_cfg[0].yellow.thresh_drop
 *                                       = 16,
 *                             Queue 2 : geared_cfg[0].yellow.thresh_drop
 *                                       + geared_cfg[1].yellow.thresh_drop
 *                                       + geared_cfg[3].yellow.thresh_drop
 *                                       = 48,
 *                             Queue 3 : geared_cfg[0].yellow.thresh_drop
 *                                       + geared_cfg[1].yellow.thresh_drop
 *                                       + geared_cfg[2].yellow.thresh_drop
 *                                       = 48 ]
 *
 *     2. The previous note should also be true for the "red.thresh_drop".
 *
 *     3. For other notes and recommendations about configuration thresholds,
 *        see the "Other Notes and Recommendations" sections in <qos_te/red.h>
 *        and <qos_te/wred.h>.
 */


/**
 * Method for checking if a packet should be dropped based on GEA RED.
 * @param color       Color of the packet that is being checked
 * @param prio        Scheduling priority of the packet that is being checked
 * @param num_prios   Number of scheduling priorities/TM queues for a scheduler
 * @param tmq_levels  Current/last-measure NBI TM queue levels for a scheduler
 * @param wred_cfgs   List of WRED configurations for the NBI TM queues
 * @return 1 if packet should be dropped, 0 if packet should be enqueued
 * @note Guaranteed-Excess-Aware (GEA) RED treats the packet color as an
 *       indicator of whether the packet should be treated as within a
 *       guaranteed bandwidth profile (no-color/green) or excess bandwidth
 *       profile (yellow/red), and then adjusts the packet drop decision to
 *       ensure that excess packets are dropped first before guaranteed
 *       packets, regardless of the scheduling priority.
 */
__intrinsic int geared_check_packet_drop(
                    enum wred_pkt_color color, unsigned int prio,
                    unsigned int num_prios, __lmem uint16_t *tmq_levels,
                    __lmem struct wred_cfg_info *wred_cfgs);


#endif /* __GEARED_H__ */
