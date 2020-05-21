/*
 * Copyright 2016-2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file   lib/npfw/catamaran_app_utils.h
 * @brief  Application-specific ME-based tool for configuring Catamaran NPFW
 */

#ifndef _CATAMARAN_APP_UTILS_H_
#define _CATAMARAN_APP_UTILS_H_

#include <nfp.h>
#include <stdint.h>


/** Initializes Catamaran channel-to-port table. */
void catamaran_app_chan2port_table_init(void);

/** Sets all Catamaran LB table sequencers to one */
void catamaran_app_lb_single_sequencer_set(void);

#endif /* !_CATAMARAN_APP_UTILS_H_ */
