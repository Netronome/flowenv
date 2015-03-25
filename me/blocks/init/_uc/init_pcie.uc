/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
 * File: init_pcie.uc
 * Description: Uppermost level of the PCIe Island/s Firmware load-time
 * initialisation process
 *
 *
 */

#ifndef _INIT_PCIE_UC_
#define _INIT_PCIE_UC_

#include "../init_config.h"

#ifndef PCIE_COUNT
    #error "PCIE_COUNT is not defined"
#endif

#macro pcie_init()
    /* NFD Requirement: https://jira.netronome.com/browse/NFDH-22.
     * To be removed once NFD includes this for us */
    #define_eval Q_NUM (0)
    #while (Q_NUM <= 255)
        .init_csr pcie:i4.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusLow 0x80000000 const
        .init_csr pcie:i4.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusHigh 67108864 const
        .init_csr pcie:i5.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusLow 0x80000000 const
        .init_csr pcie:i5.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusHigh 67108864 const
        #if (PCIE_COUNT == 4)
            .init_csr pcie:i6.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusLow 0x80000000 const
            .init_csr pcie:i6.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusHigh 67108864 const
            .init_csr pcie:i7.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusLow 0x80000000 const
            .init_csr pcie:i7.PcieInternalTargets.Queue/**/Q_NUM/**/.ConfigStatusHigh 67108864 const
        #endif
        #define_eval Q_NUM (Q_NUM + 1)
    #endloop
#endm


#endif /* _INIT_PCIE_UC_ */
