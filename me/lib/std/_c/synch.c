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
 * @file          lib/std/_c/synch.c
 * @brief         Synchronization primitives
 */

#ifndef _STD__SYNCH_C_
#define _STD__SYNCH_C_

#include <nfp.h>
#include <stdint.h>

#include <nfp/mem_atomic.h>

#include <std/synch.h>


__intrinsic void
synch_cnt_dram_reset(__dram struct synch_cnt *s, uint32_t cnt)
{
    __xwrite uint32_t wrval = cnt;
    mem_write_atomic(&wrval, s, sizeof(wrval));
}

__intrinsic void
synch_cnt_dram_ack(__dram struct synch_cnt *s)
{
    mem_decr32(s);
}

__intrinsic int
synch_cnt_dram_poll(__dram struct synch_cnt *s)
{
    __xread uint32_t rdval;
    mem_read_atomic(&rdval, s, sizeof(rdval));
    return rdval;
}

__intrinsic void
synch_cnt_dram_wait(__dram struct synch_cnt *s)
{
    while (synch_cnt_dram_poll(s)) {}
}

#endif /* !_STD__SYNCH_C_ */
