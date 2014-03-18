/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          nfp6000/nfp_qc.h
 * @brief         NFP6000 Queue Controller CSR definitions
 */

#ifndef _NFP6000__NFP_QC_H_
#define _NFP6000__NFP_QC_H_

pyexec<set_output_mode("nfp")>

/*
 * QC CSRs
 */
pyexec<dump_map(QC_Queue_CPP(altname="QC"), docs=True)>

/*
 * QC register structures
 */
#if defined(__NFP_LANG_MICROC)

pyexec<dump_map_structs(QC_Queue_CPP(altname="QC"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_QC_H_ */
