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
 * @file          nfp6000/nfp_pcie.h
 * @brief         NFP6000 PCIe CSR definitions
 */

#ifndef _NFP6000__NFP_PCIE_H_
#define _NFP6000__NFP_PCIE_H_

pyexec<set_output_mode("nfp")>

/*
 * PCIe CSRs
 */
pyexec<dump_map(PcieInternalTargets(altname="PCIE"), docs=True)>

/*
 * PCIe register structures
 */
#if defined(__NFP_LANG_MICROC)

pyexec<dump_map_structs(PcieInternalTargets(altname="PCIE"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_PCIE_H_ */
