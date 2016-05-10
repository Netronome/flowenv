/*
 * Copyright (C) 2014-2015,  Netronome Systems, Inc.  All rights reserved.
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
 * @file:  init_nbi_tm.uc
 * @brief: NBI Traffic Manager initialisation settings
 *
 */

#ifndef _INIT_NBI_TM_UC_
#define _INIT_NBI_TM_UC_

#include "../init_config.h"
#include "init_nbi_tm_csr.uc"

#ifndef NBI_TM_NUM_SEQUENCERS
    #error "NBI_TM_NUM_SEQUENCERS not defined"
#endif
#ifndef NBI_TM_ENABLE_SEQUENCER0
    #error "NBI_TM_ENABLE_SEQUENCER0 not defined"
#endif
#ifndef NBI_TM_CHANNEL_LEVEL_SELECT
    #error "NBI_TM_CHANNEL_LEVEL_SELECT not defined"
#endif
#ifndef NBI_TM_L1_INPUT_SELECT
    #error "NBI_TM_L1_INPUT_SELECT not defined"
#endif

/* Macro to help parse TM queue configurations */
#define ENABLE_Q(w,x,y,z)       w
#define START_QID(w,x,y,z)      x
#define END_QID(w,x,y,z)        y
#define Q_SIZE(w,x,y,z)         z
#define QCFG_PARAMS(w,x,y,z)    x,y,z

#define NUM_OF_QS(w,x,y,z)      (y - x + 1)
#define SIZE_OF_Q(w,x,y,z)      (1 << z)
#define SIZE_OF_QRANGE(w,x,y,z) (NUM_OF_QS(w,x,y,z) << Q_SIZE(w,x,y,z))
#define SIZE_MASK(w,x,y,z)      (SIZE_OF_Q(w,x,y,z) - 1)

#define ALIGN_HT_PTR(htptr,w,x,y,z)                       \
    ((htptr + SIZE_MASK(w,x,y,z)) & ~SIZE_MASK(w,x,y,z))


/** Nbi_TrafficManager_QCfg
 *
 * Traffic Manager Queue configuration
 *
 * @param NBI_ID          NBI number (can be 0 or 1)
 * @param START_HT_ENTRY  First free entry in the Head-Tail SRAM
 * @param TM_Q_CNT        NBI TM queue count
 * @param START_Q         First queue to configure (inclusive, can be 0-1023)
 * @param END_Q           Last queue to configure (inclusive, can be 0-1023)
 * @param Q_SIZE          Exponent value of the queue size (i.e. 2 ^ Q_SIZE)
 */
#macro Nbi_TrafficManager_QCfg(NBI_ID, START_HT_ENTRY, TM_Q_CNT, START_Q, END_Q, Q_SIZE)
    #if (NBI_ID < 0) || (NBI_ID > 1)
        #error "NBI_ID can only be 0 or 1"
    #endif
    #if (START_HT_ENTRY < 0) || (START_HT_ENTRY > 16383)
        #error "START_HT_ENTRY can only be between 0 and 16383"
    #endif
    #if (TM_Q_CNT < 0) || (TM_Q_CNT > 1023)
        #error "TM_Q_CNT can only be between 0 and 1023"
    #endif
    #if (START_Q < 0) || (START_Q > 1023)
        #error "START_Q can only be between 0 and 1023"
    #endif
    #if (END_Q < 0) || (END_Q > 1023)
        #error "END_Q can only be between 0 and 1023"
    #endif
    #if START_Q > END_Q
        #error "START_Q cannot be higher than END_Q"
    #endif
    #if (Q_SIZE < 3) || (Q_SIZE > 13)
        #error "Q_SIZE can only be between 3 and 13"
    #endif
    #if (Q_SIZE == 13) && ((TM_Q_CNT != 0) || (START_Q != END_Q))
        #error "Can only support 1 queue of Q_SIZE == 13"
    #endif
    #if (START_HT_ENTRY & ((1 << Q_SIZE) - 1))
        #error "Lowest bits in head/tail SRAM starting address are non-zero"
    #endif


    /* Initialize all of the queues specified. */
    #define_eval HT_FREE_PTR (START_HT_ENTRY)
    #define_eval NBI_ISLAND  (NBI_ID + 8)
    #define_eval TM_Q        (START_Q)

    #while (TM_Q <= END_Q)
        Nbi_TrafficManager_TMQueueReg_QueueConfig(NBI_ID, TM_Q,
                                                  1,      // QueueEnable
                                                  1,      // DropEnable
                                                  0,      // REDEnable
                                                  0,      // DMAPacketThreshold
                                                  Q_SIZE, // QueueSize
                                                  0)      // DropRateRangeSelect

        NBITMCPP_TMHeadTailSram_TMHeadTailEntry(NBI_ISLAND, TM_Q,
                                                HT_FREE_PTR, //TailPointer
                                                HT_FREE_PTR) //HeadPointer

        Nbi_TrafficManager_TMQueueReg_QueueDropCountClear(NBI_ID, TM_Q)

        #define_eval TM_Q        (TM_Q + 1)
        #define_eval HT_FREE_PTR (HT_FREE_PTR + (1 << Q_SIZE))
    #endloop

    #if HT_FREE_PTR > 16384
        #error "Ran out of head/tail SRAM during TM queue config"
    #endif

    #undef HT_FREE_PTR
    #undef NBI_ISLAND
    #undef TM_Q
#endm


/** Nbi_TrafficManager_Init
 *
 * Traffic Manager initialisation
 *
 * @param NBI_COUNT  Number of NBIs to initialize (can be 1 or 2)
 */
#macro Nbi_TrafficManager_Init(NBI_COUNT)
    #if (NBI_COUNT < 1) || (NBI_COUNT > 2)
        #error "NBI_COUNT can only be 1 or 2"
    #endif

    #define_eval NBI_ID (0)
    #while (NBI_ID < NBI_COUNT)
        Nbi_TrafficManager_TrafficManagerReg_TrafficManagerConfig(NBI_ID,
        NBI_TM_CHANNEL_LEVEL_SELECT,//ChannelLevelSelect
        0,                          //ErrPoisonEna
        0,                          //L0ChannelMap
        NBI_TM_L1_INPUT_SELECT,     //L1InputSelect
        1,                          //MiniPacketFCEnable
        NBI_TM_NUM_SEQUENCERS,      //NumSequencers
        0,                          //OOBFCEnable
        1,                          //SchedulerEnable
        NBI_TM_ENABLE_SEQUENCER0,   //Sequencer0Enable
        0                           //ShaperEnable
        )
        #define_eval NBI_ID (NBI_ID + 1)
    #endloop

    /*
     * Note: The next head/tail SRAM PTR is partly determined by the size of
     *       the queue for the next range of queues.  The lowest address bits
     *       (from bit 0 to bit Q_SIZE-1) must start with all zeroes.  Thus,
     *       the starting address must be corrected/aligned for the
     *       configuration to work correctly.
     */
    #define_eval HT_SRAM_PTR (0)
    #define_eval TM_Q_CNT    (0)

    /* NBI 0 TM Queue Config Range #0 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE0)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE0))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE0))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE0))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE0))
    #endif

    /* NBI 0 TM Queue Config Range #1 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE1)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE1))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE1))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE1))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE1))
    #endif

    /* NBI 0 TM Queue Config Range #2 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE2)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE2))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE2))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE2))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE2))
    #endif

    /* NBI 0 TM Queue Config Range #3 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE3)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE3))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE3))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE3))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE3))
    #endif

    /* NBI 0 TM Queue Config Range #4 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE4)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE4))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE4))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE4))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE4))
    #endif

    /* NBI 0 TM Queue Config Range #5 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE5)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE5))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE5))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE5))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE5))
    #endif

    /* NBI 0 TM Queue Config Range #6 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE6)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE6))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE6))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE6))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE6))
    #endif

    /* NBI 0 TM Queue Config Range #7 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE7)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE7))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE7))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE7))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE7))
    #endif

    /* NBI 0 TM Queue Config Range #8 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE8)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE8))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE8))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE8))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE8))
    #endif

    /* NBI 0 TM Queue Config Range #9 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE9)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE9))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE9))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE9))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE9))
    #endif

    /* NBI 0 TM Queue Config Range #10 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE10)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE10))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE10))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE10))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE10))
    #endif

    /* NBI 0 TM Queue Config Range #11 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE11)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE11))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE11))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE11))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE11))
    #endif

    /* NBI 0 TM Queue Config Range #12 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE12)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE12))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE12))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE12))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE12))
    #endif

    /* NBI 0 TM Queue Config Range #13 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE13)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE13))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE13))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE13))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE13))
    #endif

    /* NBI 0 TM Queue Config Range #14 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE14)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE14))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE14))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE14))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE14))
    #endif

    /* NBI 0 TM Queue Config Range #15 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE15)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE15))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE15))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE15))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE15))
    #endif

    /* NBI 0 TM Queue Config Range #16 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE16)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE16))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE16))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE16))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE16))
    #endif

    /* NBI 0 TM Queue Config Range #17 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE17)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE17))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE17))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE17))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE17))
    #endif

    /* NBI 0 TM Queue Config Range #18 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE18)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE18))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE18))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE18))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE18))
    #endif

    /* NBI 0 TM Queue Config Range #19 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE19)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE19))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE19))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE19))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE19))
    #endif

    /* NBI 0 TM Queue Config Range #20 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE20)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE20))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE20))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE20))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE20))
    #endif

    /* NBI 0 TM Queue Config Range #21 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE21)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE21))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE21))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE21))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE21))
    #endif

    /* NBI 0 TM Queue Config Range #22 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE22)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE22))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE22))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE22))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE22))
    #endif

    /* NBI 0 TM Queue Config Range #23 */
    #if ENABLE_Q(NBI0_TM_Q_CFG_RANGE23)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI0_TM_Q_CFG_RANGE23))

        Nbi_TrafficManager_QCfg(0, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI0_TM_Q_CFG_RANGE23))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI0_TM_Q_CFG_RANGE23))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI0_TM_Q_CFG_RANGE23))
    #endif


    #define_eval HT_SRAM_PTR (0)
    #define_eval TM_Q_CNT    (0)

    /* NBI 1 TM Queue Config Range #0 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE0)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE0))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE0))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE0))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE0))
    #endif

    /* NBI 1 TM Queue Config Range #1 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE1)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE1))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE1))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE1))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE1))
    #endif

    /* NBI 1 TM Queue Config Range #2 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE2)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE2))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE2))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE2))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE2))
    #endif

    /* NBI 1 TM Queue Config Range #3 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE3)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE3))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE3))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE3))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE3))
    #endif

    /* NBI 1 TM Queue Config Range #4 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE4)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE4))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE4))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE4))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE4))
    #endif

    /* NBI 1 TM Queue Config Range #5 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE5)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE5))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE5))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE5))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE5))
    #endif

    /* NBI 1 TM Queue Config Range #6 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE6)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE6))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE6))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE6))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE6))
    #endif

    /* NBI 1 TM Queue Config Range #7 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE7)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE7))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE7))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE7))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE7))
    #endif

    /* NBI 1 TM Queue Config Range #8 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE8)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE8))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE8))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE8))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE8))
    #endif

    /* NBI 1 TM Queue Config Range #9 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE9)
        #define_eval HT_SRAM_PTR                              \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE9))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE9))

        #define_eval HT_SRAM_PTR                                 \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE9))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE9))
    #endif

    /* NBI 1 TM Queue Config Range #10 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE10)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE10))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE10))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE10))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE10))
    #endif

    /* NBI 1 TM Queue Config Range #11 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE11)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE11))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE11))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE11))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE11))
    #endif

    /* NBI 1 TM Queue Config Range #12 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE12)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE12))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE12))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE12))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE12))
    #endif

    /* NBI 1 TM Queue Config Range #13 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE13)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE13))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE13))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE13))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE13))
    #endif

    /* NBI 1 TM Queue Config Range #14 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE14)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE14))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE14))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE14))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE14))
    #endif

    /* NBI 1 TM Queue Config Range #15 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE15)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE15))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE15))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE15))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE15))
    #endif

    /* NBI 1 TM Queue Config Range #16 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE16)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE16))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE16))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE16))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE16))
    #endif

    /* NBI 1 TM Queue Config Range #17 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE17)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE17))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE17))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE17))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE17))
    #endif

    /* NBI 1 TM Queue Config Range #18 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE18)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE18))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE18))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE18))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE18))
    #endif

    /* NBI 1 TM Queue Config Range #19 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE19)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE19))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE19))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE19))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE19))
    #endif

    /* NBI 1 TM Queue Config Range #20 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE20)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE20))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE20))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE20))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE20))
    #endif

    /* NBI 1 TM Queue Config Range #21 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE21)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE21))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE21))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE21))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE21))
    #endif

    /* NBI 1 TM Queue Config Range #22 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE22)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE22))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE22))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE22))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE22))
    #endif

    /* NBI 1 TM Queue Config Range #23 */
    #if ENABLE_Q(NBI1_TM_Q_CFG_RANGE23)
        #define_eval HT_SRAM_PTR                               \
            (ALIGN_HT_PTR(HT_SRAM_PTR, NBI1_TM_Q_CFG_RANGE23))

        Nbi_TrafficManager_QCfg(1, HT_SRAM_PTR, TM_Q_CNT,
                                QCFG_PARAMS(NBI1_TM_Q_CFG_RANGE23))

        #define_eval HT_SRAM_PTR                                  \
            (HT_SRAM_PTR + SIZE_OF_QRANGE(NBI1_TM_Q_CFG_RANGE23))
        #define_eval TM_Q_CNT (TM_Q_CNT + NUM_OF_QS(NBI1_TM_Q_CFG_RANGE23))
    #endif


    #define_eval NBI_ID (0)
    #while (NBI_ID < NBI_COUNT)
        Nbi_TrafficManager_TrafficManagerReg_MiniPktCreditConfig(NBI_ID,
        128,   //CreditLimit
        0x200, //FPCreditLimit
        1      //MiniPacketFCMode
        )

        Nbi_TrafficManager_TrafficManager_TrafficManagerReg_BlqEvent(NBI_ID,
        0xf, //BLQEventStatusEnable
        0,   //BLQEventNotEmptyEnable
        0,   //BLQEventThreshold0
        0,   //BLQEventThreshold1
        0,   //BLQEventThreshold2
        0,   //BLQEventThreshold3
        0    //DisBLQEventFifoFullAssert
        )

        #define_eval NBI_ID (NBI_ID + 1)
    #endloop

    #undef HT_SRAM_PTR
    #undef TM_Q_CNT
    #undef NBI_ID
#endm


#endif /* _INIT_NBI_TM_UC_ */
