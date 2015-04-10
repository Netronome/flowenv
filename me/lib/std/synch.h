/*
 * Copyright 2012-2015 Netronome, Inc.
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
 * @file          lib/std/synch.h
 * @brief         Synchronization primitives
 */

#ifndef _STD__SYNCH_H_
#define _STD__SYNCH_H_

#include <nfp.h>
#include <stdint.h>

struct synch_cnt {
    uint32_t value;
};

/**
 * Reset DRAM synch counter
 * @param s     synch counter
 * @param cnt   reset value
 */
__intrinsic void synch_cnt_dram_reset(__dram struct synch_cnt *s, uint32_t cnt);

/**
 * Ack DRAM synch counter
 * @param s     synch counter
 */
__intrinsic void synch_cnt_dram_ack(__dram struct synch_cnt *s);

/**
 * Poll DRAM synch counter
 * @param s     synch counter
 *
 * Poll synch counter and return non-nil if not zero.
 */
__intrinsic int synch_cnt_dram_poll(__dram struct synch_cnt *s);

/**
 * Wait for DRAM synch counter to reach zero
 * @param s     synch counter
 */
__intrinsic void synch_cnt_dram_wait(__dram struct synch_cnt *s);

#endif /* !_STD__SYNCH_H_ */
