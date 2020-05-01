/*
 * Copyright (C) 2020,  Netronome Systems, Inc.  All rights reserved.
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
 * @file:   init_ctm.uc
 * @brief:  Uppermost level of the CTM Island/s initialisation process
 *
 */

 /*
  * The abstraction of the CTM initialisation looks like this:
  *
  * Top most level. The ctm_init() calls the distinct setup macros for the
  * packet engine.
  *     init_ctm.uc
  *
  * Intermediate level.
  *     init_ctm_pe.uc
  *
  * Bottom level. All macros use the .init_csr directives to set the
  * registers.
  *     init_ctm_pe_csr.uc
  */

#ifndef _INIT_CTM_UC_
#define _INIT_CTM_UC_

#include "../init_config.h"
#include "init_ctm_pe.uc"

#macro ctm_init()

    #define MEI_ID 0
    #while (MEI_ID <= 6)

        #if __nfp_has_island(32 + MEI_ID)
            Ctm_Pe_Init(MEI_ID)
        #endif

        #define_eval MEI_ID (MEI_ID + 1)
    #endloop

#endm

#endif /* _INIT_CTM_UC_ */