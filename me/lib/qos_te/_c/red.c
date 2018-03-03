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
 * @file        lib/qos_te/_c/red.c
 * @brief       Functions to implement ME-based Random Early Discard (RED).
 */

#include <qos_te/red.h>


__intrinsic void
red_calc_mult(__lmem struct red_cfg_info *red_cfg)
{
    /*
     * Calculate the drop probability multiplier.
     *
     * The formula for calculating this is as follows:
     *     size of RED range          = drop threshold - RED threshold
     *     RED probability multiplier = 1.0 / size of RED range
     *
     * Note: Since the ME does not natively support floating point operations,
     *       integer operations are used instead.  The radix/decimal point in
     *       the "red_mult" integer variable is treated as being in between
     *       bits 14 and 15.  Therefore, "0x8000" is equivalent to "1.0".
     *
     *       Using bit 15 to represent "1.0" ensures that the maximum number of
     *       bits can be used to the right of the radix/decimal point, while
     *       also ensuring that the result of any multiply operation fits in a
     *       single 32-bit register (assuming the other operand is also 16 bits
     *       wide).
     */
    red_cfg->red_mult = 0x8000 / (red_cfg->thresh_drop - red_cfg->thresh_red);
}

__intrinsic int
red_check_packet_drop(unsigned int tmq_level,
                      __lmem struct red_cfg_info *red_cfg)
{
    int32_t tmq_diff;
    uint32_t rand_num;
    uint32_t rand_prob;
    uint32_t mult;
    int red_drop_decision = 0;

    if (tmq_level >= red_cfg->thresh_drop) {
        /* Automatically drop all packets when above the max threshold. */
        red_drop_decision = 1;
    } else if (tmq_level > red_cfg->thresh_red) {
        /*
         * Determine the drop probability ratio.
         *
         * Note: This converts the TM queue level into a probability, expressed
         *       in a value that ranges from 0 to 32767.
         */
        mult  = red_cfg->red_mult;
        tmq_diff = tmq_level - red_cfg->thresh_red;

        __asm {
            mul_step[mult, tmq_diff], 16x16_start;
            mul_step[mult, tmq_diff], 16x16_step1;
            mul_step[mult, tmq_diff], 16x16_step2;
            mul_step[rand_prob, --], 16x16_last;
        }

        /* Determine if the packet should be randomly dropped. */
        rand_num = local_csr_read(local_csr_pseudo_random_number) & 0x7fff;

        if (rand_num >= rand_prob)
            red_drop_decision = 1;
    }

    return red_drop_decision;
}
