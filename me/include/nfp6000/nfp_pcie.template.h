/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
