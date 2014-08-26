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
 * @file          nfp6000/nfp_cls.h
 * @brief         NFP6000 CLS CSR definitions
 */

#ifndef _NFP6000__NFP_CLS_H_
#define _NFP6000__NFP_CLS_H_

pyexec<set_output_mode("nfp")>

/*
 * CLS CSRs
 */
pyexec<dump_map(ClusterScratchCppMap(altname="CLS"), docs=True)>

/*
 * Event manager CSRs are accessed at 8-byte offsets in CLS
 */
#define NFP_CLS_EM_CSR_SPACING                             8

/*
 * CLS register structures
 */
#if defined(__NFP_LANG_MICROC)

pyexec<dump_map_structs(ClusterScratchCppMap(altname="CLS"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_CLS_H_ */
