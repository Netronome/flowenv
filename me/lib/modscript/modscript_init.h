/*
 * Copyright (C) 2017,  Netronome Systems, Inc.  All rights reserved.
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
 */

#ifndef __MODSCRIPT_INIT_H__
#define __MODSCRIPT_INIT_H__

#ifndef MAC_EGRESS_PREPEND_BYTES
    /* If MAC egress prepend is enabled, set egress bytes to 4. */
    #ifdef MAC_EGRESS_PREPEND_ENABLE
        #define MAC_EGRESS_PREPEND_BYTES 4
    #else
        #define MAC_EGRESS_PREPEND_BYTES 0
        #warning "MAC_EGRESS_PREPEND_ENABLE or MAC_EGRESS_PREPEND_BYTES not defined, defaulting MAC_EGRESS_PREPEND_BYTES to 0."
    #endif
#endif

#define PREPEND_ENC ((MAC_EGRESS_PREPEND_BYTES/2) << 1)

#define PREPEND_VAL ((PREPEND_ENC << 24) | (PREPEND_ENC << 16) | \
                     (PREPEND_ENC << 8) | PREPEND_ENC)

#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_8 (0xe1e1e1c1 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_8 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_9 (0xe1e1c101 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_9 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_10 (0xe1e1c103 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_10 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_11 (0xe1e1c105 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_11 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_12 (0xe1e1c107 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_12 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_13 (0xe1e1c109 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_13 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_14 (0xe1e1c10b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_14 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_15 (0xe1e1c10d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_15 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_16 (0xe1e1c10f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_16 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_17 (0xe1e1c111 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_17 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_18 (0xe1e1c113 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_18 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_19 (0xe1e1c115 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_19 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_20 (0xe1e1c117 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_20 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_21 (0xe1e1c119 | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_21 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_22 (0xe1e1c11b | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_22 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_23 (0xe1e1c11d | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_23 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_24 (0xe1e1c11f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_24 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_25 (0xe1c1011f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_25 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_26 (0xe1c1031f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_26 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_27 (0xe1c1051f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_27 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_28 (0xe1c1071f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_28 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_29 (0xe1c1091f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_29 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_30 (0xe1c10b1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_30 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_31 (0xe1c10d1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_31 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_32 (0xe1c10f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_32 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_33 (0xe1c1111f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_33 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_34 (0xe1c1131f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_34 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_35 (0xe1c1151f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_35 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_36 (0xe1c1171f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_36 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_37 (0xe1c1191f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_37 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_38 (0xe1c11b1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_38 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_39 (0xe1c11d1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_39 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_40 (0xe1c11f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_40 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_41 (0xc1011f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_41 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_42 (0xc1031f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_42 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_43 (0xc1051f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_43 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_44 (0xc1071f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_44 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_45 (0xc1091f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_45 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_46 (0xc10b1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_46 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_47 (0xc10d1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_47 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_48 (0xc10f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_48 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_48 (0xc10f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_48 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_48 (0xc10f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_48 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_48 (0xc10f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_48 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_49 (0xc1111f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_49 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_49 (0xc1111f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_49 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_49 (0xc1111f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_49 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_49 (0xc1111f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_49 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_50 (0xc1131f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_50 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_50 (0xc1131f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_50 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_50 (0xc1131f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_50 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_50 (0xc1131f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_50 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_51 (0xc1151f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_51 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_51 (0xc1151f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_51 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_51 (0xc1151f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_51 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_51 (0xc1151f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_51 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_52 (0xc1171f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_52 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_52 (0xc1171f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_52 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_52 (0xc1171f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_52 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_52 (0xc1171f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_52 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_53 (0xc1191f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_53 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_53 (0xc1191f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_53 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_53 (0xc1191f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_53 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_53 (0xc1191f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_53 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_54 (0xc11b1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_54 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_54 (0xc11b1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_54 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_54 (0xc11b1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_54 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_54 (0xc11b1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_54 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_55 (0xc11d1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_55 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_55 (0xc11d1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_55 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_55 (0xc11d1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_55 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_55 (0xc11d1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_55 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_56 (0xc11f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_56 (0xe1e1e1e1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_56 (0xc11f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_56 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_56 (0xc11f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_56 (0xe1e1e1e1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_56 (0xc11f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_56 (0xe1e1e1e1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_57 (0x111f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_57 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_57 (0x111f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_57 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_57 (0x111f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_57 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_57 (0x111f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_57 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_58 (0x131f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_58 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_58 (0x131f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_58 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_58 (0x131f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_58 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_58 (0x131f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_58 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_59 (0x151f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_59 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_59 (0x151f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_59 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_59 (0x151f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_59 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_59 (0x151f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_59 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_60 (0x171f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_60 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_60 (0x171f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_60 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_60 (0x171f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_60 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_60 (0x171f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_60 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_61 (0x191f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_61 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_61 (0x191f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_61 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_61 (0x191f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_61 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_61 (0x191f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_61 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_62 (0x1b1f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_62 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_62 (0x1b1f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_62 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_62 (0x1b1f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_62 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_62 (0x1b1f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_62 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_63 (0x1d1f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_63 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_63 (0x1d1f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_63 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_63 (0x1d1f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_63 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_63 (0x1d1f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_63 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_64 (0x1f1f0f0f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_64 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_64 (0x1f1f0f0f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_64 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_64 (0x1f1f0f0f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_64 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_64 (0x1f1f0f0f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_64 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_65 (0x11f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_65 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_65 (0x11f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_65 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_65 (0x11f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_65 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_65 (0x11f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_65 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_66 (0x31f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_66 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_66 (0x31f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_66 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_66 (0x31f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_66 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_66 (0x31f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_66 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_67 (0x51f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_67 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_67 (0x51f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_67 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_67 (0x51f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_67 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_67 (0x51f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_67 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_68 (0x71f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_68 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_68 (0x71f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_68 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_68 (0x71f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_68 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_68 (0x71f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_68 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_69 (0x91f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_69 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_69 (0x91f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_69 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_69 (0x91f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_69 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_69 (0x91f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_69 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_70 (0xb1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_70 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_70 (0xb1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_70 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_70 (0xb1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_70 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_70 (0xb1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_70 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_71 (0xd1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_71 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_71 (0xd1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_71 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_71 (0xd1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_71 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_71 (0xd1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_71 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_72 (0xf1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_72 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_72 (0xf1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_72 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_72 (0xf1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_72 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_72 (0xf1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_72 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_73 (0x111f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_73 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_73 (0x111f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_73 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_73 (0x111f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_73 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_73 (0x111f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_73 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_74 (0x131f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_74 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_74 (0x131f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_74 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_74 (0x131f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_74 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_74 (0x131f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_74 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_75 (0x151f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_75 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_75 (0x151f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_75 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_75 (0x151f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_75 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_75 (0x151f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_75 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_76 (0x171f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_76 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_76 (0x171f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_76 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_76 (0x171f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_76 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_76 (0x171f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_76 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_77 (0x191f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_77 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_77 (0x191f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_77 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_77 (0x191f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_77 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_77 (0x191f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_77 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_78 (0x1b1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_78 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_78 (0x1b1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_78 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_78 (0x1b1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_78 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_78 (0x1b1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_78 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_79 (0x1d1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_79 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_79 (0x1d1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_79 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_79 (0x1d1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_79 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_79 (0x1d1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_79 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_80 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_80 (0xe1e1e1c1 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_80 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_80 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_80 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_80 (0xe1e1e1c1 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_80 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_80 (0xe1e1e1c1 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_81 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_81 (0xe1e1c101 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_81 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_81 (0xe1e1c101 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_81 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_81 (0xe1e1c101 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_81 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_81 (0xe1e1c101 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_82 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_82 (0xe1e1c103 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_82 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_82 (0xe1e1c103 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_82 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_82 (0xe1e1c103 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_82 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_82 (0xe1e1c103 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_83 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_83 (0xe1e1c105 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_83 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_83 (0xe1e1c105 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_83 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_83 (0xe1e1c105 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_83 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_83 (0xe1e1c105 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_84 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_84 (0xe1e1c107 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_84 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_84 (0xe1e1c107 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_84 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_84 (0xe1e1c107 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_84 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_84 (0xe1e1c107 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_85 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_85 (0xe1e1c109 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_85 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_85 (0xe1e1c109 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_85 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_85 (0xe1e1c109 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_85 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_85 (0xe1e1c109 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_86 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_86 (0xe1e1c10b | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_86 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_86 (0xe1e1c10b | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_86 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_86 (0xe1e1c10b | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_86 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_86 (0xe1e1c10b | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_87 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_87 (0xe1e1c10d | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_87 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_87 (0xe1e1c10d | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_87 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_87 (0xe1e1c10d | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_87 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_87 (0xe1e1c10d | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_88 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_88 (0xe1e1c10f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_88 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_88 (0xe1e1c10f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_88 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_88 (0xe1e1c10f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_88 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_88 (0xe1e1c10f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_89 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_89 (0xe1e1c111 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_89 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_89 (0xe1e1c111 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_89 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_89 (0xe1e1c111 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_89 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_89 (0xe1e1c111 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_90 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_90 (0xe1e1c113 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_90 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_90 (0xe1e1c113 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_90 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_90 (0xe1e1c113 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_90 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_90 (0xe1e1c113 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_91 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_91 (0xe1e1c115 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_91 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_91 (0xe1e1c115 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_91 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_91 (0xe1e1c115 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_91 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_91 (0xe1e1c115 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_92 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_92 (0xe1e1c117 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_92 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_92 (0xe1e1c117 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_92 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_92 (0xe1e1c117 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_92 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_92 (0xe1e1c117 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_93 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_93 (0xe1e1c119 | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_93 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_93 (0xe1e1c119 | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_93 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_93 (0xe1e1c119 | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_93 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_93 (0xe1e1c119 | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_94 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_94 (0xe1e1c11b | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_94 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_94 (0xe1e1c11b | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_94 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_94 (0xe1e1c11b | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_94 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_94 (0xe1e1c11b | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_95 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_95 (0xe1e1c11d | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_95 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_95 (0xe1e1c11d | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_95 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_95 (0xe1e1c11d | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_95 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_95 (0xe1e1c11d | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_96 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_96 (0xe1e1c11f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_96 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_96 (0xe1e1c11f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_96 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_96 (0xe1e1c11f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_96 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_96 (0xe1e1c11f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_97 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_97 (0xe1c1011f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_97 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_97 (0xe1c1011f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_97 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_97 (0xe1c1011f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_97 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_97 (0xe1c1011f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_98 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_98 (0xe1c1031f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_98 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_98 (0xe1c1031f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_98 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_98 (0xe1c1031f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_98 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_98 (0xe1c1031f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_99 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_99 (0xe1c1051f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_99 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_99 (0xe1c1051f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_99 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_99 (0xe1c1051f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_99 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_99 (0xe1c1051f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_100 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_100 (0xe1c1071f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_100 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_100 (0xe1c1071f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_100 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_100 (0xe1c1071f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_100 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_100 (0xe1c1071f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_101 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_101 (0xe1c1091f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_101 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_101 (0xe1c1091f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_101 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_101 (0xe1c1091f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_101 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_101 (0xe1c1091f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_102 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_102 (0xe1c10b1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_102 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_102 (0xe1c10b1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_102 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_102 (0xe1c10b1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_102 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_102 (0xe1c10b1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_103 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_103 (0xe1c10d1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_103 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_103 (0xe1c10d1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_103 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_103 (0xe1c10d1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_103 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_103 (0xe1c10d1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_104 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_104 (0xe1c10f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_104 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_104 (0xe1c10f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_104 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_104 (0xe1c10f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_104 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_104 (0xe1c10f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_105 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_105 (0xe1c1111f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_105 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_105 (0xe1c1111f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_105 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_105 (0xe1c1111f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_105 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_105 (0xe1c1111f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_106 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_106 (0xe1c1131f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_106 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_106 (0xe1c1131f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_106 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_106 (0xe1c1131f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_106 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_106 (0xe1c1131f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_107 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_107 (0xe1c1151f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_107 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_107 (0xe1c1151f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_107 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_107 (0xe1c1151f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_107 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_107 (0xe1c1151f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_108 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_108 (0xe1c1171f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_108 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_108 (0xe1c1171f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_108 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_108 (0xe1c1171f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_108 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_108 (0xe1c1171f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_109 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_109 (0xe1c1191f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_109 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_109 (0xe1c1191f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_109 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_109 (0xe1c1191f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_109 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_109 (0xe1c1191f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_110 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_110 (0xe1c11b1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_110 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_110 (0xe1c11b1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_110 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_110 (0xe1c11b1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_110 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_110 (0xe1c11b1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_111 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_111 (0xe1c11d1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_111 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_111 (0xe1c11d1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_111 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_111 (0xe1c11d1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_111 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_111 (0xe1c11d1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_112 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_112 (0xe1c11f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_112 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_112 (0xe1c11f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_112 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_112 (0xe1c11f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_112 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_112 (0xe1c11f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_113 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_113 (0xc1011f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_113 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_113 (0xc1011f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_113 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_113 (0xc1011f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_113 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_113 (0xc1011f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_114 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_114 (0xc1031f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_114 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_114 (0xc1031f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_114 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_114 (0xc1031f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_114 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_114 (0xc1031f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_115 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_115 (0xc1051f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_115 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_115 (0xc1051f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_115 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_115 (0xc1051f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_115 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_115 (0xc1051f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_116 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_116 (0xc1071f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_116 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_116 (0xc1071f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_116 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_116 (0xc1071f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_116 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_116 (0xc1071f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_117 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_117 (0xc1091f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_117 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_117 (0xc1091f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_117 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_117 (0xc1091f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_117 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_117 (0xc1091f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_118 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_118 (0xc10b1f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_118 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_118 (0xc10b1f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_118 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_118 (0xc10b1f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_118 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_118 (0xc10b1f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_119 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_119 (0xc10d1f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_119 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_119 (0xc10d1f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_119 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_119 (0xc10d1f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_119 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_119 (0xc10d1f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_120 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_120 (0xc10f1f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_120 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_120 (0xc10f1f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_120 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_120 (0xc10f1f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_120 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_120 (0xc10f1f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_121 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_121 (0xc1111f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_121 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_121 (0xc1111f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_121 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_121 (0xc1111f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_121 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_121 (0xc1111f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_122 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_122 (0xc1131f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_122 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_122 (0xc1131f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_122 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_122 (0xc1131f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_122 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_122 (0xc1131f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_123 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_123 (0xc1151f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_123 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_123 (0xc1151f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_123 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_123 (0xc1151f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_123 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_123 (0xc1151f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_124 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_124 (0xc1171f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_124 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_124 (0xc1171f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_124 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_124 (0xc1171f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_124 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_124 (0xc1171f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_125 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_125 (0xc1191f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_125 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_125 (0xc1191f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_125 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_125 (0xc1191f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_125 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_125 (0xc1191f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_126 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_126 (0xc11b1f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_126 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_126 (0xc11b1f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_126 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_126 (0xc11b1f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_126 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_126 (0xc11b1f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_127 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_127 (0xc11d1f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_127 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_127 (0xc11d1f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_127 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_127 (0xc11d1f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_127 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_127 (0xc11d1f1f | PREPEND_VAL)
    #endif
#endif
#if defined(__NFP_LANG_ASM)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_128 (0x1f1f1f1f | PREPEND_VAL)
    .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_128 (0xc11f1f1f | PREPEND_VAL)
    #if (__nfp_has_island(9))
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_128 (0x1f1f1f1f | PREPEND_VAL)
        .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_128 (0xc11f1f1f | PREPEND_VAL)
    #endif
#elif defined(__NFP_LANG_MICROC)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_128 (0x1f1f1f1f | PREPEND_VAL)
    __asm .init_csr xpb:Nbi0IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_128 (0xc11f1f1f | PREPEND_VAL)
    #if (_nfp_has_island("nbi1"))
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg0_128 (0x1f1f1f1f | PREPEND_VAL)
        __asm .init_csr xpb:Nbi1IsldXpbMap.NbiTopXpbMap.PktModifier.NbiPmOpcodeRamCnfg.NbiPmOpcode32Cnfg1_128 (0xc11f1f1f | PREPEND_VAL)
    #endif
#endif
#endif
