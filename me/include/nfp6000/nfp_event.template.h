/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          nfp6000/nfp_event.h
 * @brief         NFP6000 EventManager CSR definitions
 */

#ifndef _NFP6000__NFP_EVENT_H_
#define _NFP6000__NFP_EVENT_H_

pyexec<set_output_mode("nfp")>

/*
 * EventManager CSRs
 */
pyexec<dump_map(EventManagerMap(altname="EM"), docs=True)>

/*
 * EventManager register structures
 */
#if defined(__NFP_LANG_MICROC)

pyexec<dump_map_structs(EventManagerMap(altname="EM"))>

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_EVENT_H_ */
