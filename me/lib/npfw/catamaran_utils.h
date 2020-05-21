/*
 * Copyright (C) 2016-2020, Netronome Systems, Inc.  All rights reserved.
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
 * @file   lib/npfw/catamaran_utils.h
 * @brief  ME-based interface for configuring Catamaran NPFW
 */

#ifndef _CATAMARAN_UTILS_H_
#define _CATAMARAN_UTILS_H_

#include <nfp.h>
#include <stdint.h>


/**
 * Catamaran channel-to-port table entry result.
 */
struct catamaran_chan2port_entry {
    uint8_t port;      /** Port number. */
    uint8_t port_mode; /** Port mode of operation. */
};

/**
 * Catamaran table entry
 */
struct catamaran_lb_entry {
    union {
        struct {
            uint8_t _reserved;
            uint8_t nfp;
            uint8_t bp;
            uint8_t ro_ctx;
        };
        uint32_t _raw;
    };
};


/* Catamaran configuration support API. */

/**
 * Initializes support structures and CLS hash for configuring Catamaran.
 *
 * @param nbi  NBI island to read the Catamaran configuration from (0/1)
 */
void catamaran_support_setup(unsigned int nbi);


/* Catamaran channel-to-port table configuration API. */

/**
 * Retrieves Catamaran channel-to-port table entries.
 *
 * @param nbi         NBI island to read from (0/1)
 * @param chan_start  First channel to retrieve
 * @param chan_end    Last channel to retrieve
 * @param entries     Local memory location to transfer the channel-to-port
 *                    information to, must point to data structure large enough
 *                    to hold the information for all of the specified channels
 */
void catamaran_chan2port_table_get(
         unsigned int nbi, unsigned int chan_start, unsigned int chan_end,
         __lmem struct catamaran_chan2port_entry *entries);

/**
 * Configures Catamaran channel-to-port table entries.
 *
 * @param nbi         NBI island to configure (0/1)
 * @param chan_start  First channel to configure
 * @param chan_end    Last channel to configure
 * @param entries     Local memory location to transfer the channel-to-port
 *                    information from, must point to data structure containing
 *                    the information for all of the specified channels
 */
void catamaran_chan2port_table_set(
         unsigned int nbi, unsigned int chan_start, unsigned int chan_end,
         __lmem struct catamaran_chan2port_entry *entries);


/* Catamaran MAC matching table configuration API. */

/**
 * Adds a Catamaran MAC match table entry.
 *
 * @param nbi           NBI island to configure (0/1)
 * @param mac_addr      MAC address of the entry to add
 * @param result        The MAC match entry result to add (1-65535)
 * @param cls_hash_idx  CLS hash index to use (0-7)
 * @return              0 if entry is available, -1 if entry is unavailable
 */
int catamaran_mac_match_table_add(unsigned int nbi, uint64_t mac_addr,
                                  uint16_t result, unsigned int cls_hash_idx);

/**
 * Looks up and retrieves Catamaran MAC match table entry.
 *
 * @param nbi           NBI island to read from (0/1)
 * @param mac_addr      MAC address to look up
 * @param entry         Local memory location to transfer the MAC match
 *                      information to, if found
 * @param cls_hash_idx  CLS hash index to use (0-7)
 * @return              The MAC match entry result (1-65535), or -1 if entry is
 *                      not found
 */
int catamaran_mac_match_table_get(unsigned int nbi, uint64_t mac_addr,
                                  unsigned int cls_hash_idx);

/**
 * Removes a Catamaran MAC match table entry.
 *
 * @param nbi           NBI island to configure (0/1)
 * @param mac_addr      MAC address of the entry to remove
 * @param cls_hash_idx  CLS hash index to use (0-7)
 * @return              0 if entry is found, -1 if entry is not found
 */
int catamaran_mac_match_table_remove(unsigned int nbi, uint64_t mac_addr,
                                     unsigned int cls_hash_idx);


/**
 * Looks up and retrieves Catamaran Load Balance (LB) table.
 *
 * @param nbi           NBI island to read from (0/1)
 * @param lb_start      LB entry index, less than CATAMARAN_LB_TABLE_SIZE
 * @param lb_end        LB entry index, less than CATAMARAN_LB_TABLE_SIZE
 * @param entries       Array of entry values
 * @return              LB entry value, or -1 if entry is not found
 *
 * The entries array is filled with values between lb_start and lb_end
 * (inclusive) from CATAMARAN_LB_TABLE_BASE0.
 */
int catamaran_lb_table_get(unsigned int nbi, unsigned int lb_start,
                           unsigned int lb_end,
                           __lmem struct catamaran_lb_entry *entries);


/**
 * Performs read-modify-write on Catamaran Load Balance (LB) table.
 *
 * @param nbi           NBI island to read from (0/1)
 * @param lb_start      LB entry index, less than CATAMARAN_LB_TABLE_SIZE
 * @param lb_end        LB entry index, less than CATAMARAN_LB_TABLE_SIZE
 * @param entries       Array of entry values
 * @return              0 for success, or -1 if entry is not found
 *
 * Values in the load balance table between lb_start and lb_end (inclusive)
 * are replaced with data from entries.
 */
int catamaran_lb_table_set(unsigned int nbi, unsigned int lb_start,
                           unsigned int lb_end,
                           __lmem struct catamaran_lb_entry *entries);

#endif /* !_CATAMARAN_UTILS_H_ */
