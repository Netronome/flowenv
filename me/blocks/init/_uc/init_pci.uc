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
 * @file:   init_pci.uc
 * @brief:  Uppermost level of the PCI Island/s initialisation process
 *
 */

 /*
  * The abstraction of the PCI initialisation looks like this:
  *
  * Top most level. The pci_init() calls the distinct setup macros for the
  * packet engine.
  *     init_pci.uc
  *
  * Intermediate level.
  *     init_pci_dma.uc
  *
  * Bottom level. All macros use the .init_csr directives to set the
  * registers.
  *     init_pci_dma_csr.uc
  */

#ifndef _INIT_PCI_UC_
#define _INIT_PCI_UC_

#include "../init_config.h"
#include "init_pci_dma.uc"

#macro pci_init()

    #define PCI_ID 0
    #while (PCI_ID < 4)

        #if __nfp_has_island(4 + PCI_ID)
            Pci_Dma_Init(PCI_ID)
        #endif

        #define_eval PCI_ID (PCI_ID + 1)
    #endloop

#endm

#endif /* _INIT_PCI_UC_ */