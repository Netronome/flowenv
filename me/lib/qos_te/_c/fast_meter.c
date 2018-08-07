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
 * @file        lib/qos_te/_c/fast_meter.c
 * @brief       Functions to implement fast meters.
 */

#include <assert.h>

#include <nfp/me.h>

#include <qos_te/fast_meter.h>


/** Data-structure for updating fast meter control info and tokens. */
struct fm_flush_data {
    union {
        struct {
            struct fast_meter_ctrl ctrl;      /**< Control and locks. */
            uint32_t               timestamp; /**< Timestamp. */
            struct meter_bucket    bucket;    /**< Token buckets. */
        };
        uint32_t __raw[4];                    /**< Raw data. */
    };
};

/** Data-structure for fetching refresh settings for a fast meter. */
struct fm_refresh_info {
    union {
        struct {
            struct meter_bucket        bucket;    /**< Token buckets. */
            struct fast_meter_settings meter_cfg; /**< Meter settings. */
        };
        uint32_t __raw[6];                        /**< Raw data. */
    };
};

/** Data-structure for a fast meter timestamp update. */
struct fm_ts_update_info {
    union {
        struct {
            struct fast_meter_ctrl ctrl; /**< Control and locks. */
            uint32_t timestamp;          /**< Timestamp. */
        };
        uint32_t __raw[2];               /**< Raw data. */
    };
};

/** Amount of time to sleep between attempts to acquire the fast meter lock. */
#define FM_LOCK__SLEEP_TIME 100


/* ------------------------------------------------------------------------- */


/* ***  Fast Meter Helper Methods.  *** */

/** Helper method to check the timestamp to see if a refresh is needed. */
static __intrinsic int32_t
fm_ts_check(__xrw struct fm_ts_update_info *ctrl_ts_xrw,
            __gpr uint64_t *tstamp)
{
    /* Calculate the elapsed time. */
    *tstamp >>= ctrl_ts_xrw->ctrl.ts_shf;

    /* Ignore upper 32 bits. */
    return ((uint32_t)*tstamp - ctrl_ts_xrw->timestamp);
}

/** Helper method to release the fast meter timestamp update lock. */
static __intrinsic void
fm_ts_update_unlock(__mem40 struct fast_meter_ctrl *meter_ctrl)
{
    __gpr struct fast_meter_ctrl ctrl;

    /* Release the timestamp update lock. */
    ctrl.__raw     = 0;
    ctrl.ts_update = 1;

    mem_bitclr_imm(ctrl.__raw, meter_ctrl);

    /* Note: The critical section for the meter refresh ends at this point. */
}

/** Helper method to acquire the fast meter timestamp update lock. */
static __intrinsic unsigned int
fm_ts_update_lock(__xrw struct fm_ts_update_info *ctrl_ts_xrw,
                  __mem40 struct fast_meter_ctrl *meter_ctrl,
                  __gpr uint64_t *tstamp)
{
    __gpr struct fast_meter_ctrl ctrl;
    SIGNAL_PAIR sig_pair;
    unsigned int ts_update_not_locked = 1;

    /* Attempt to acquire the timestamp update lock. */
    ctrl.__raw              = 0;
    ctrl.ts_update          = 1;
    ctrl_ts_xrw->ctrl.__raw = ctrl.__raw;
    ctrl_ts_xrw->timestamp  = 0;

    __mem_test_set(ctrl_ts_xrw, meter_ctrl, sizeof(struct fm_ts_update_info),
                   sizeof(struct fm_ts_update_info), sig_done, &sig_pair);

    /* Prepare for the timestamp calculation while waiting. */
    *tstamp = me_tsc_read();

    __wait_for_all(&sig_pair);

    /* Make sure the meter was not locked. */
    while (ctrl_ts_xrw->ctrl.lock) {
        /* Check if the timestamp update lock needs to be relinquished. */
        if (!ctrl_ts_xrw->ctrl.ts_update) {
            fm_ts_update_unlock(meter_ctrl);
        }

        /* Attempt to re-acquire the timestamp update lock. */
        mem_test_set(ctrl_ts_xrw, meter_ctrl,
                     sizeof(struct fm_ts_update_info));
    }

    /*
     * Note: The critical section for meter refresh begins with the
     *       successfully acquired timestamp update lock.
     */

    /* Check if the meter is active and is actively refreshing. */
    if ((!ctrl_ts_xrw->ctrl.active || ctrl_ts_xrw->ctrl.skip_meter) &&
        !ctrl_ts_xrw->ctrl.ts_update) {
        fm_ts_update_unlock(meter_ctrl);
    } else {
        ts_update_not_locked = ctrl_ts_xrw->ctrl.ts_update;
    }

    return ts_update_not_locked;
}

/** Helper method to attempt to acquire the timestamp update lock. */
static __intrinsic unsigned int
fm_ts_update_try_lock(__xrw struct fm_ts_update_info *ctrl_ts_xrw,
                      __mem40 struct fast_meter_ctrl *meter_ctrl)
{
    __gpr struct fast_meter_ctrl ctrl;
    unsigned int ts_update_not_locked = 1;

    /* Attempt to acquire the timestamp update lock. */
    ctrl.__raw              = 0;
    ctrl.ts_update          = 1;
    ctrl_ts_xrw->ctrl.__raw = ctrl.__raw;
    ctrl_ts_xrw->timestamp  = 0;

    mem_test_set(ctrl_ts_xrw, meter_ctrl, sizeof(struct fm_ts_update_info));

    /*
     * Note: The critical section for meter refresh begins with the
     *       successfully acquired timestamp update lock.
     */

    /* Check if the meter is locked, inactive, or not actively refreshing. */
    if ((ctrl_ts_xrw->ctrl.lock || !ctrl_ts_xrw->ctrl.active ||
         ctrl_ts_xrw->ctrl.skip_meter) && !ctrl_ts_xrw->ctrl.ts_update) {
        fm_ts_update_unlock(meter_ctrl);
    } else {
        ts_update_not_locked = ctrl_ts_xrw->ctrl.ts_update;
    }

    return ts_update_not_locked;
}

/** Helper method to refresh a fast meter. */
static __intrinsic
void fm_meter_refresh(__mem40 struct fast_meter *meter,
                      __xrw struct fm_ts_update_info *ctrl_ts_xrw,
                      __gpr uint64_t *ts_temp, SIGNAL *sig)
{
    __gpr struct fast_meter_ctrl temp_ctrl;
    __xread struct fm_refresh_info fetch_xr;
    __xwrite struct fm_flush_data flush_xw;
    int32_t time_elapsed;
    uint32_t delta_from_max;

    /* Pre-fetch the rest of the meter info. */
    __mem_read_atomic(&fetch_xr, &(meter->bucket), sizeof(fetch_xr),
                      sizeof(fetch_xr), sig_done, sig);

    /* Check if the meter needs to be refreshed. */
    time_elapsed = fm_ts_check(ctrl_ts_xrw, ts_temp);

    if (time_elapsed > 0) {
        /* Prepare to refresh the meter. */
        temp_ctrl.__raw     = 0;
        temp_ctrl.ts_update = 1;
        flush_xw.ctrl.__raw = 0 - temp_ctrl.__raw;
        flush_xw.timestamp  = time_elapsed;

        __asm ctx_arb[*sig];

        /* Calculate the refresh amount for the short-term bucket. */
        delta_from_max  =
            fetch_xr.meter_cfg.sterm_max - fetch_xr.bucket.short_term_tokens;
        *ts_temp        = fetch_xr.meter_cfg.sterm_rate * time_elapsed;
        flush_xw.bucket.short_term_tokens =
            (*ts_temp < delta_from_max) ? *ts_temp : delta_from_max;

        /* Calculate the refresh amount for the long-term bucket. */
        delta_from_max  =
            fetch_xr.meter_cfg.lterm_max - fetch_xr.bucket.long_term_tokens;
        *ts_temp  = fetch_xr.meter_cfg.lterm_rate * time_elapsed;
        flush_xw.bucket.long_term_tokens =
            (*ts_temp < delta_from_max) ? *ts_temp : delta_from_max;

        /* Update the meter and free the timestamp update lock. */
        __mem_add32(&flush_xw, meter, sizeof(flush_xw), sizeof(flush_xw),
                    sig_done, sig);
    } else {
        /* Free the timestamp update lock. */
        fm_ts_update_unlock(&(meter->ctrl));
    }
}


/* ------------------------------------------------------------------------- */


/* ***  Fast Meter Methods.  *** */

__intrinsic int
fast_meter_lock(__mem40 struct fast_meter *meter, unsigned int max_retries)
{
    __gpr struct fast_meter_ctrl ctrl;
    __xread uint32_t ctrl_xr;
    __xrw uint32_t ctrl_xrw;
    int lock_failed          = -1;
    unsigned int retry_cnt   = 0;
    unsigned int retry_limit = (max_retries) ? max_retries : 1;

    /* Attempt to set the lock bit. */
    ctrl.__raw = 0;
    ctrl.lock  = 1;

    do {
        mem_test_set(&ctrl_xrw, &(meter->ctrl), sizeof(ctrl_xrw));

        if (!(ctrl_xrw & ctrl.__raw)) { /* Lock has just been set. */
            lock_failed = 0;
            break;
        }

        /* Update retry count only if a limit has been specified. */
        if (max_retries) {
            ++retry_cnt;
        }

        sleep(FM_LOCK__SLEEP_TIME);
    } while (retry_cnt <= retry_limit);

    /* Make sure any timestamp updates have completed first. */
    if (!lock_failed) {
        ctrl.__raw     = 0;
        ctrl.ts_update = 1;

        if (ctrl_xrw & ctrl.__raw) {
            do {
                mem_read_atomic(&ctrl_xr, &(meter->ctrl), sizeof(ctrl_xr));

                if (!(ctrl_xr & ctrl.__raw)) { /* Timestamp update unlocked. */
                    break;
                }

                /* Update retry count only if a limit has been specified. */
                if (max_retries) {
                    ++retry_cnt;
                }

                sleep(FM_LOCK__SLEEP_TIME);
            } while (retry_cnt <= retry_limit);

            /* Clear the lock if the timestamp update is still locked. */
            if (ctrl_xr & ctrl.__raw) {
                ctrl.__raw = 0;
                ctrl.lock  = 1;

                mem_bitclr_imm(ctrl.__raw, &(meter->ctrl));

                lock_failed = -1;
            }
        }
    }

    return lock_failed;
}

__intrinsic int
fast_meter_packet(uint32_t meter_amt, __mem40 struct fast_meter *meter,
                  enum meter_color in_pkt_color)
{
    __gpr uint64_t ts_temp;
    __xrw struct fm_ts_update_info ctrl_ts_xrw;
    int out_pkt_color;
    SIGNAL sig;

    try_ctassert(__is_aligned(meter, 8));
    try_ctassert((in_pkt_color >= METER_COLOR_NO_COLOR) &&
                 (in_pkt_color <= METER_COLOR_RED));

    /* Attempt to acquire the timestamp update lock to refresh the meter. */
    if (0 == fm_ts_update_lock(&ctrl_ts_xrw, &(meter->ctrl), &ts_temp)) {
        /*
         * Refresh the meter if needed.
         *
         * Note: This section of code is a performance-critical section of the
         *       fast meter code.  It begins with the timestamp update lock,
         *       and with the timestamp update unlock, which occurs after the
         *       meter refresh, or after the timestamp update unlock for
         *       instances where the meter does not need to be updated.
         */
        fm_meter_refresh(meter, &ctrl_ts_xrw, &ts_temp, &sig);

        /* Perform the packet metering operation. */
        out_pkt_color = mem_meter(meter_amt << ctrl_ts_xrw.ctrl.rdx_pt_shf,
                                  &(meter->bucket), ctrl_ts_xrw.ctrl.rfc_mode,
                                  in_pkt_color);

        /* Clear any outstanding signals. */
        __asm ctx_arb[sig];
    } else if (!ctrl_ts_xrw.ctrl.active) { /* Meter is not active. */
        out_pkt_color = -1;
    } else { /* This thread does not need to refresh the meter. */
        /* Check if the metering operation should proceed. */
        if (!ctrl_ts_xrw.ctrl.skip_meter) {
            /* Perform the packet metering. */
            out_pkt_color = mem_meter(meter_amt << ctrl_ts_xrw.ctrl.rdx_pt_shf,
                                      &(meter->bucket),
                                      ctrl_ts_xrw.ctrl.rfc_mode,
                                      in_pkt_color);
        } else {
            out_pkt_color = in_pkt_color;
        }
    }

    return out_pkt_color;
}

__intrinsic int
fast_meter_refresh(__mem40 struct fast_meter *meter)
{
    __gpr uint64_t ts_temp;
    __xrw struct fm_ts_update_info ctrl_ts_xrw;
    SIGNAL sig;
    int refresh_failed = -1;

    try_ctassert(__is_aligned(meter, 8));

    /* Attempt to acquire the timestamp update lock to refresh the meter. */
    if (0 == fm_ts_update_try_lock(&ctrl_ts_xrw, &(meter->ctrl))) {
        /*
         * Refresh the meter if needed.
         *
         * Note: This section of code is a performance-critical section of the
         *       fast meter code.  It begins with the timestamp update lock,
         *       and with the timestamp update unlock, which occurs after the
         *       meter refresh, or after the timestamp update unlock for
         *       instances where the meter does not need to be updated.
         */
        ts_temp = me_tsc_read();

        fm_meter_refresh(meter, &ctrl_ts_xrw, &ts_temp, &sig);

        /* Clear any outstanding signals. */
        __asm ctx_arb[sig];

        refresh_failed = 0;
    }

    return refresh_failed;
}

__intrinsic void
fast_meter_unlock(__mem40 struct fast_meter *meter)
{
    __gpr struct fast_meter_ctrl ctrl;

    /* Unlock the meter. */
    ctrl.__raw = 0;
    ctrl.lock  = 1;

    mem_bitclr_imm(ctrl.__raw, &(meter->ctrl));
}
