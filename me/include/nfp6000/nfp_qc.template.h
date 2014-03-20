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

enum pcie_qc_event {
    PCIE_QC_EVENT_NO_EVENT = 0,     /**  Never generate events */
    PCIE_QC_EVENT_NOT_EMPTY = 1,    /**  Event on not empty */
    PCIE_QC_EVENT_GE_MARK = 2,      /**  Event on >= watermark */
    PCIE_QC_EVENT_LT_MARK = 3       /**  Event on < watermark */
};

enum pcie_qc_watermark {
    PCIE_QC_WM_4 = 0,
    PCIE_QC_WM_8 = 1,
    PCIE_QC_WM_16 = 2,
    PCIE_QC_WM_32 = 3,
    PCIE_QC_WM_64 = 4,
    PCIE_QC_WM_128 = 5,
    PCIE_QC_WM_256 = 6,
    PCIE_QC_WM_512 = 7,
};

enum pcie_qc_q_size {
    PCIE_QC_SZ_256 = 0,
    PCIE_QC_SZ_512 = 1,
    PCIE_QC_SZ_1k = 2,
    PCIE_QC_SZ_2k = 3,
    PCIE_QC_SZ_4k = 4,
    PCIE_QC_SZ_8k = 5,
    PCIE_QC_SZ_16k = 6,
    PCIE_QC_SZ_32k = 7,
    PCIE_QC_SZ_64k = 8,
    PCIE_QC_SZ_128k = 9,
    PCIE_QC_SZ_256k = 10,
};

pyexec<dump_map_structs(QC_Queue_CPP(altname="QC"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_QC_H_ */
