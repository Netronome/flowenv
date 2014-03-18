/*
 * Copyright (C) 2013-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          nfp6000/nfp_me.h
 * @brief         NFP6000 Microengine CSR definitions
 */

#ifndef _NFP6000__NFP_ME_H_
#define _NFP6000__NFP_ME_H_

pyexec<set_output_mode("nfp")>

/*
 * ME CSRs
 */
pyexec<dump_map(MeCsrCPP(altname="MECSR"), docs=True)>

/*
 * ME CSR register structures
 */
#if defined(__NFP_LANG_MICROC)

pyexec<dump_map_structs(MeCsrCPP(altname="MECSR"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_ME_H_ */
