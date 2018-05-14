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
 * @file        lib/qos_te/libqos_te.c
 * @brief       Micro-C QoS/Traffic Engineering library.
 */

/*
 * The following files implement all the functionality in <qos_te/*.h>.  They
 * may only have dependencies on <nfp.h>, <stdint.h>, <nfp/*.h>, and other
 * include files in <qos_te/*.h>.  They are not protected by header guards and
 * should not be included elsewhere.
 */
#include "_c/fast_meter.c"
#include "_c/red.c"
#include "_c/wred.c"
#include "_c/geared.c"
