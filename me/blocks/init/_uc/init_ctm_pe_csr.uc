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
 * @file:   init_ctm_pe_csr.uc
 * @brief:  Contains macros to initialise the CTM PE
 */

#ifndef _INIT_CTM_PE_CSR_UC_
#define _INIT_CTM_PE_CSR_UC_


/** CTMXpbMap_MuPacketReg_MUPEConfiguredCredits0
 *
 * Configures the CTM credits for the ME owner
 *
 * @param CTM             CTM number to configure
 * @param BUF_CREDIT      Configures the number of buffer credits in
 *                        PKT_CTM_SHARED_SIZE byte increments.
 * @param PKT_CREDIT      Configures the number of packets allocated to the CTM
 */
#macro CTMXpbMap_MuPacketReg_MUPEConfiguredCredits0(CTM, BUF_CREDIT, PKT_CREDIT)

    .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEConfiguredCredits0.MUPEBufferCredits BUF_CREDIT
    .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEConfiguredCredits0.MUPEPacketCredits PKT_CREDIT

#endm


/** CTMXpbMap_MuPacketReg_MUPEMemConfig
 *
 * Configures the packet engine memory allocation within the CTM
 *
 * @param CTM             CTM number to configure
 * @param TOTAL_BYTES     Total bytes allocated on the CTM
 *
 * The packet engine uses memory from the start of CTM.  This memory
 * must not be used by other software, so it is best practice to
 * reserve it via the linker.
 */
#macro CTMXpbMap_MuPacketReg_MUPEMemConfig(CTM, TOTAL_BYTES)
#if IS_NFPTYPE(__NFP6000)

    #if TOTAL_BYTES <= (64 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 2
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (64 * 1024) reserved
    #elif TOTAL_BYTES <= (128 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 1
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (128 * 1024) reserved
    #elif TOTAL_BYTES <= (256 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 0
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (256 * 1024) reserved
    #else
        #error "ME island " CTM " CTM buffer credits oversubscribed"
    #endif

#elif IS_NFPTYPE(__NFP3800)

    #if TOTAL_BYTES <= (16 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 7
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (16 * 1024) reserved
    #elif TOTAL_BYTES <= (32 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 6
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (32 * 1024) reserved
    #elif TOTAL_BYTES <= (48 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 5
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (48 * 1024) reserved
    #elif TOTAL_BYTES <= (64 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 4
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (64 * 1024) reserved
    #elif TOTAL_BYTES <= (80 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 3
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (80 * 1024) reserved
    #elif TOTAL_BYTES <= (96 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 2
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (96 * 1024) reserved
    #elif TOTAL_BYTES <= (112 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 1
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (112 * 1024) reserved
    #elif TOTAL_BYTES <= (128 * 1024)
        .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEMemConfig.MUPEMemConfig 0
        .alloc_mem i/**/CTM/**/_/**/PKT_RSVD_SYM i/**/CTM.ctm+0 global (128 * 1024) reserved
    #else
        #error "ME island " CTM " CTM buffer credits oversubscribed"
    #endif

#else
    #error "Unsupported chip type selected."
#endif

#endm


/** CTMXpbMap_MuPacketReg_MUPEBufferConfig
 *
 * Configures the CTM shared buffer size
 *
 * @param CTM             CTM number to configure
 * @param SHARED_BUF_SIZE Buffer size in bytes
 *
 * This CSR is not used on the NFP6000 as the shared buffer is always 2kB.
 */
#macro CTMXpbMap_MuPacketReg_MUPEBufferConfig(CTM, SHARED_BUF_SIZE)
    #define_eval _SHARED_SIZE (log2(SHARED_BUF_SIZE) - 11)
    .init_csr xpb:i/**/CTM.CTMXpbMap.MuPacketReg.MUPEBufferConfig.MUPEBufferConfig _SHARED_SIZE
#endm

#endif /* _INIT_CTM_PE_CSR_UC_ */