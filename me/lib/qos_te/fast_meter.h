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
 * @file          lib/qos_te/fast_meter.h
 * @brief         Interface for a fast-refreshing, variable-precision meter.
 */

#ifndef __FAST_METER_H__
#define __FAST_METER_H__

#include <nfp.h>
#include <stdint.h>

#include <nfp/mem_atomic.h>


/*
 * Feature Description
 *
 *     The "fast meter" feature is a metering design that is primarily
 *     self-refreshing-- that is, the MEs processing packets of the datapath
 *     refresh the meter token buckets the vast majority of the time.
 *
 *     This self-refreshing aspect of the fast meter translates into faster, or
 *     or more frequent, refresh cycles; this allows for the burst sizes for
 *     the meter to be smaller (the refresh cycle should occur before the point
 *     in time where the bucket would normally be filled to the max).  Smaller
 *     burst sizes are required for certain traffic engineering scenarios or
 *     features, such as WRED, where very large bursts of packets of the same
 *     color effectively cause WRED to devolve into RED (that is, the queues
 *     are filled with only one packet color for large percentages of time).
 *
 *     The fast meter design also supports the ability to refresh fractions of
 *     a token per refresh cycle.  This allows for greater precision when
 *     specifying the meter information rate (which is typically expressed in
 *     packets per second or bits/bytes per second).  This is accomplished by
 *     allowing the radix-point (or decimal point) to be shifted to the left,
 *     such that values to the right of the radix-point represent fractions of
 *     a token (and values to the left of the radix-point represent whole
 *     tokens).  Below is an example of how this works:
 *
 *         Given the following:
 *             Number of fractional bits := 8 bits
 *             Timestamp shift amount    := 0 (one per 2^0 * 16 clock cycles)
 *             Desired rate              := 500 MBps
 *             Desired burst size        := 20000 Bytes
 *             TCLK (ME clock)           := 1.2 GHz
 *
 *         Then the meter settings should be as follows:
 *             rdx_pt_shf       = 8
 *             ts_shf           = 0
 *             burst size       = 20000 Bytes << rdx_pt_shf
 *                              = 0x4e2000
 *             information rate = round(500 MBps * (1 << rdx_pt_shf) /
 *                                      (TCLK >> (ts_shf + 4)))
 *                              = 0x6ab
 *
 *             Note: A ME timestamp increments one out of 16 ME clock cycles;
 *                   so the ME timestamp rate is equal to "TCLK >> 4".
 *             Note: For the burst size, the value is interpreted as 20000
 *                   whole tokens, and 0/256 of a token.  (The fractional
 *                   token amounts should be zero for the burst sizes.)
 *             Note: For the information rate, the value is interpreted as 6
 *                   whole tokens and 171/256 of a token, per 2^0 * 16 ME clock
 *                   cycles; this is approximately 500.1 MBps.
 *
 * Implementation Details
 *
 *     The fast meter designs have four major parts:
 *         1.  Token buckets for the meter.
 *         2.  Token bucket settings (maximum burst sizes, token refill rates).
 *         3.  A 32-bit timestamp of when the meter was last refreshed.
 *         4.  Configuration/control information for the meter.
 *
 *     The token buckets are designed to use the metering command provided by
 *     the MU atomic engine.  These are described in the NFP databook, in the
 *     Programmer's Reference Manual, and also in <nfp/mem_atomic.h>.
 *
 *     The token bucket settings are used when the token buckets are refreshed,
 *     specifying how many tokens to fill each bucket, up to a specified
 *     maximum amount, which is the burst size.
 *
 *     The timestamp indicates when the token buckets for the meter were last
 *     refreshed.  This timestamp is derived from the ME timestamp and from
 *     the timestamp shift amount field in the control word; this is how the
 *     meter timestamp is derived:
 *
 *         timestamp = (ME timestamp >> timestamp shift amount) & 0xFFFFFFFF
 *
 *     The configuration and control information contain the following:
 *         - A flag to indicate whether the meter is active or disabled
 *         - A lock bit for modifying the meter configuration
 *         - A lock bit for refreshing the meter token buckets and timestamp
 *         - A flag to indicate whether the metering operation should be
 *             skipped; this effectively sets the meter rate to infinity
 *         - A flag for the metering RFC mode (see <nfp/mem_atomic.h> for
 *             details).
 *         - The radix point shift amount, which can be used to increase the
 *             precision of the meter information rate.
 *         - The timestamp shift amount, which can be used to reduce the
 *             refresh frequency.
 *
 *     Note: Even though the fast meter design handles the refreshing of the
 *           meter whenever packets are being metered, the meter still needs to
 *           be refreshed infrequently, at least once before the signed 32-bit
 *           counter rolls over from positive to negative; this polling period
 *           can be calculated as follows:
 *
 *               Polling refresh period < ((2 ^ 31) / (TCLK >> 4))
 *
 *               Note: For a TCLK of 1.2 GHz, the polling refreshing period is
 *                     approximately 28 seconds or less.
 *
 * Usage Guidelines
 *
 *     The following are the recommended steps for using the fast meter design:
 *
 *     1.  Instantiate the fast meter data-structure(s).
 *     2.  Instantiate a polling mechanism to periodically refresh meters.
 *         - This polling mechanism should call the following method:
 *             - fast_meter_refresh(...)
 *     3.  Configure the fast meter data-structure with the desired settings.
 *         - If locking is required for the meter, the following methods can be
 *             used for locking/unlocking the specific meter:
 *             - fast_meter_lock(...)
 *             - fast_meter_unlock(...)
 *     4.  Call the packet metering method:
 *         - fast_meter_packet(...)
 *
 * Other Notes and Recommendations
 *
 *     1.  The settings of the fast meter correspond to the following terms
 *         described in IETF RFCs for metering:
 *         - For IETF RFC 2698:
 *             Long-term refresh rate    => Committed Information Rate (CIR)
 *             Long-term maximum tokens  => Committed Burst Size (CBS)
 *             Short-term refresh rate   => Peak Information Rate (PIR)
 *             Short-term maximum tokens => Peak Burst Size (PBS)
 *         - For IETF RFC 2697/4115:
 *             Long-term refresh rate    => Committed Information Rate (CIR)
 *             Long-term maximum tokens  => Committed Burst Size (CBS)
 *             Short-term refresh rate   => Excess Information Rate (EIR)
 *             Short-term maximum tokens => Excess Burst Size (EBS)
 *
 *     2.  It is standard practice for the short-term and long-term maximum
 *         tokens to be whole numbers, that is, that the fractional token
 *         amount always be zero.
 *
 *     3.  For the two tokens buckets associated with the meter, the following
 *         must be true:
 *
 *             - Short-term refresh rate <= short-term maximum tokens
 *             - Long-term refresh rate <= long-term maximum tokens
 *
 *         Otherwise, the maximum tokens/burst size, effectively becomes the
 *         refresh rate/information rate.
 *
 *     4.  Assuming the above is true, the effective information rate can be
 *         calculated as follows:
 *
 *             refresh frequency = (TCLK / 16) / (1 << timestamp shift)
 *             information rate = refresh rate per refresh * refresh frequency
 *
 *     5.  The Nyquist Sampling Theorem is a useful guide as to how to set the
 *         timestamp shift amount.  The Nyquist Sampling Theorem states that
 *         the sampling frequency should be at least twice the highest
 *         frequency being sampled.  The exact interpretation of "the highest
 *         frequency being sampled" is dependent on the particular application
 *         or use case.  In general, however, a higher sampling frequency is
 *         generally more desirable.
 *
 *     6.  The radix-point shift amount must be set to a value where there are
 *         enough bits to the left of the radix point for the larger value for
 *         the maximum tokens.  This can be expressed as follows:
 *
 *             Given the following:
 *                 Long-term maximum tokens  (LMax) := 9000
 *                 Short-term maximum tokens (SMax) := 18000
 *
 *             This equates to the following:
 *                 Bits for long-term maximum tokens  (bits(LMax)) = 14
 *                 Bits for short-term maximum tokens (bits(SMax)) = 15
 *
 *             Then the programmer must ensure the following:
 *                 rdx_pt_shf <= 32 - max(bits(LMax), bits(SMax))
 *
 *     7.  In general, more bits to the right of the radix points results in a
 *         more precise information rate, as this increases the number of
 *         significant bits (or digits).
 *
 *
 * Fast Meter Data-Structure Format
 *
 *     Bit   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 *     ----\ 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *     Word +-------------------------------+-+-+-+-+-+---------+---------+-+
 *        0 |             rsvd              |U|L|A|S|r| Ts Shf  |RdxPtShf |M|
 *          +-------------------------------+-+-+-+-+-+---------+---------+-+
 *        1 |                     Shifted ME Timestamp                      |
 *          +---------------------------------------------------------------+
 *        2 |                    Short-Term Token Bucket                    |
 *          +---------------------------------------------------------------+
 *        3 |                    Long-Term Token Bucket                     |
 *          +---------------------------------------------------------------+
 *        4 |                   Short-Term Maximum Tokens                   |
 *          +---------------------------------------------------------------+
 *        5 |                   Long-Term Maximum Tokens                    |
 *          +---------------------------------------------------------------+
 *        4 |                    Short-Term Refresh Rate                    |
 *          +---------------------------------------------------------------+
 *        5 |                    Long-Term Refresh Rate                     |
 *          +---------------------------------------------------------------+
 *
 *      U := Timestamp (U)pdate lock
 *          -- Used for refreshing the meter token buckets + timestamp
 *      L := Meter (L)ock
 *          -- Used for modifying the meter configuration
 *      A := (Active)
 *          -- Used to indicate the meter is active/enabled
 *      S := (S)kip Metering
 *          -- Skip metering operation; meter has unlimited bandwidth
 *      Ts Shf := Timestamp Shift
 *          -- Used to adjust the refresh frequency/granularity
 *      RdxPtShf := Radix Point Shift
 *          -- Used to adjust shift the radix point for higher precision rates
 *      M := RFC (M)ode
 *          -- Used to indicate type of metering algorithm
 *              - 0 : Peak mode (RFC 2698)
 *              - 1 : Excess mode (RFC 2697/4115)
 */


/** Data-structure for the fast meter control word. */
struct fast_meter_ctrl {
    union {
        struct {
            uint16_t __rsvd0;              /**< Reserved for future use. */
            /**
             * Lock for timestamp update.
             * @note This lock prevents other MEs or contexts from refreshing
             *       the meter; this does not block the packet metering
             *       operation.
             */
            unsigned int ts_update   : 1;
            /**
             * Full lock for the meter.
             * @note When this lock bit is asserted, no other ME or contexts
             *       can use or modify the meter.
             */
            unsigned int lock        : 1;
            unsigned int active      : 1;  /**< Meter active flag. */
            unsigned int skip_meter  : 1;  /**< Skip metering operation. */
            unsigned int __rsvd1     : 1;  /**< Reserved for future use. */
            unsigned int ts_shf      : 5;  /**< Timestamp shift amount. */
            unsigned int rdx_pt_shf  : 5;  /**< Radix point shift amount. */
            enum meter_mode rfc_mode : 1;  /**< Meter RFC type. */
        };
        uint32_t __raw;                    /**< Raw data. */
    };
};

/** Data-structure for the fast meter rate and burst settings. */
struct fast_meter_settings {
    union {
        uint32_t excess_burst;    /**< Excess burst size (EBS). */
        uint32_t peak_burst;      /**< Peak burst size (PBS). */
        uint32_t sterm_max;       /**< Short-term token max. */
    };
    union {
        uint32_t committed_burst; /**< Committed burst size (CBS). */
        uint32_t lterm_max;       /**< Long-term token max. */
    };
    union {
        uint32_t excess_rate;     /**< Excess information rate (EIR). */
        uint32_t peak_rate;       /**< Peak information rate (PIR). */
        uint32_t sterm_rate;      /**< Short-term token rate. */
    };
    union {
        uint32_t committed_rate;  /**< Committed information rate (CIR). */
        uint32_t lterm_rate;      /**< Long-term token rate. */
    };
};

/** Data-structure for a fast meter. */
struct fast_meter {
    union {
        struct {
            /** Word 0: Locks and configuration data. */
            struct fast_meter_ctrl     ctrl;
            /** Word 1: Timestamp of the last update.*/
            uint32_t                   timestamp;
            /** Words 2-3: Meter token buckets. */
            struct meter_bucket        bucket;
            /** Words 4-7: Meter rate and burst size settings. */
            struct fast_meter_settings meter_cfg;
        };
        uint32_t __raw[8]; /**< Raw data. */
    };
};


/**
 * Method for locking a fast meter.
 * @param meter        Pointer to the meter (must be 8-byte aligned).
 * @param max_retries  Number of retries for locking (0 for infinite).
 * @return 0 for success, -1 for failure.
 * @note Once locked, packet metering and meter service should be blocked from
 *       other threads.
 */
__intrinsic int fast_meter_lock(__mem40 struct fast_meter *meter,
                                unsigned int max_retries);

/**
 * Method for metering a packet using a fast meter.
 * @param meter_amt     Number of tokens to remove from the token bucket.
 * @param meter         Pointer to the meter (must be 8-byte aligned).
 * @param in_pkt_color  Incoming packet color.
 * @return The resulting packet color (green, yellow or red), or -1 for error.
 * @note The resulting color encoding is defined by 'enum meter_color'.
 * @note An error only occurs if the meter is inactive.
 */
__intrinsic int fast_meter_packet(uint32_t meter_amt,
                                  __mem40 struct fast_meter *meter,
                                  enum meter_color in_pkt_color);

/**
 * Method for refreshing a fast meter.
 * @param meter  Pointer to the meter (must be 8-byte aligned).
 * @return 0 for success, -1 if the meter is inactive or locked.
 */
__intrinsic int fast_meter_refresh(__mem40 struct fast_meter *meter);

/**
 * Method for unlocking a fast meter.
 * @param meter  Pointer to the meter (must be 8-byte aligned).
 */
__intrinsic void fast_meter_unlock(__mem40 struct fast_meter *meter);


#endif /* __FAST_METER_H__ */
