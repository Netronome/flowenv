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
 * @file        lib/qos_te/_c/wred.c
 * @brief       Functions to implement ME-based Weighted RED (WRED).
 */

#include <qos_te/wred.h>


__intrinsic void
wred_calc_mult(__lmem struct wred_cfg_info *wred_cfg)
{
    /* Calculate the (W)RED multipliers for each color. */
    red_calc_mult(&(wred_cfg->no_color));
    red_calc_mult(&(wred_cfg->green));
    red_calc_mult(&(wred_cfg->yellow));
    red_calc_mult(&(wred_cfg->red));
}

__intrinsic int
wred_check_packet_drop(enum wred_pkt_color color,
                       unsigned int tmq_level,
                       __lmem struct wred_cfg_info *wred_cfg)
{
    __lmem struct red_cfg_info *color_cfg;
    int wred_drop_decision;

    switch (color) {
    case WRED_NO_COLOR:
        color_cfg = &(wred_cfg->no_color);
        break;
    case WRED_GREEN:
        color_cfg = &(wred_cfg->green);
        break;
    case WRED_YELLOW:
        color_cfg = &(wred_cfg->yellow);
        break;
    case WRED_RED:
        color_cfg = &(wred_cfg->red);
        break;
    default: /* This is an error if this case is ever reached. */

        /* Default to no-drop in case of parameter error. */
        wred_drop_decision = 0;

        goto wred_check_packet_drop_exit;
        break;
    }

    wred_drop_decision = red_check_packet_drop(tmq_level, color_cfg);

wred_check_packet_drop_exit:

    return wred_drop_decision;
}
