/*
 * Copyright 2017 Netronome, Inc.
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
 * @file          lib/nfp/tm_config.h
 * @brief         NBP 6000 NBI Traffic Manager Configuration library
 */
 
/*
 * NOTE: This does not configure the entire TM. Complete TM initialisation must 
 * still be done with libraries provided in me/blocks/init/_uc.
 * The purpose of this library is to enable partial reconfigure during run-time 
 * like in a QoS type use case. 
 *
 * Simplified usage guidelines:
 *
 * 1. At any point during run time, stop transmission to the TM. (the specific
 * mechanism depends on the app). Recommended by not necessary.
 * 2. Disable TM queues that will reconfigured.
 * 3. Wait for TM queues to drain (can wait or poll CSR).
 * 4. Use API's provided, e.g:
 *  nbi_tm_config_shapers(0, &tm_init_spec_ptr->tm_shapers_cluster[0]);
 *  nfp_nbi_tm_config_schedulers(0, &tm_init_spec_ptr->tm_scheduler_cluster[0]);
 *  nfp_nbi_tm_config(0, tm_init_spec_ptr->tm_config);
 *  nfp_nbi_tm_config_queues(0, &tm_init_spec_ptr->tm_queue_cluster[0]);
 * 5. Queues are configured last since this will enable the queues again.
 * 6. Re-enable traffic to TM (if stopped).
 */
 
#ifndef TM_CONFIG_H
#define TM_CONFIG_H
#include <nfp6000/nfp_nbi_tm.h>

#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_LEVELCHECKENABLE_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_DESCQUEUESENABLE_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_SEQUENCER0ENABLE_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_ERR_POISON_ENA_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_SCHEDULERENABLE_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_SHAPERENABLE_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_MINIPACKETFCENABLE_Enabled (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_CHANNELLEVELSELECT_Level_1_sel (1)
#define     NFP_NBI_TM_TRAFFIC_MANAGER_CONFIG_L1INPUTSELECT_L1_Enabled (1)

#define     NFP_NBI_TM_QUEUE_CONFIG_DROPENABLE_Enabled       (1)
#define     NFP_NBI_TM_QUEUE_CONFIG_QUEUEENABLE_Enabled      (1)

#define     NFP_NBI_TM_SCHEDULER_CONFIG_SP1ENABLE_Enabled    (1)
#define     NFP_NBI_TM_SCHEDULER_CONFIG_SP0ENABLE_Enabled    (1)
#define     NFP_NBI_TM_SCHEDULER_CONFIG_DWRRENABLE_Enabled   (1)

#ifndef TM_INIT_MAX_Q_CLUSTERS
#define TM_INIT_MAX_Q_CLUSTERS            24
#endif
#ifndef TM_INIT_MAX_SHAPER_CLUSTERS
#define TM_INIT_MAX_SHAPER_CLUSTERS       24
#endif
#ifndef TM_INIT_MAX_SCHEDULER_CLUSTERS
#define TM_INIT_MAX_SCHEDULER_CLUSTERS       24
#endif

#define L1L2_SCHEDULER_INPUTS               8

/**
 * NBI TM Queue Configuration
 *
 * This structure contains a range of TM Queue to initialise from and
 * including queue number "start" up to and including queue number "end"
 */
struct nfp_nbi_tm_queue_cluster {
    unsigned int                            in_use; /** < If 0, this range will be ignored*/
    unsigned int                            start; /** < First queue */
    unsigned int                            end; /** < Last queue */
    unsigned int                            last; /** < Last cluster in array */
    struct nfp_nbi_tm_queue_config          queue_config; /** < TrafficManager.TMQueueReg.QueueConfigX */
}__declspec(packed);

/**
 * NBI TM Shaper registers
 *
 * This structure contains all the registers pertaining to a specific shapers.
 */
struct nfp_nbi_tm_shaper {
    struct nfp_nbi_tm_shaper_rate           shaper_rate; /** < TrafficManager.TMShaperReg.ShaperRateX */
    struct nfp_nbi_tm_shaper_threshold      shaper_threshold; /** < TrafficManager.TMShaperReg.ShaperThresholdX */
    struct nfp_nbi_tm_shaper_max_overshoot  max_overshoot; /** < TrafficManager.TMShaperReg.ShaperMaxOvershootX */
    struct nfp_nbi_tm_shaper_rate_adjust    rate_adjust; /** < TrafficManager.TMShaperReg.ShaperRateAdjustX*/
}__declspec(packed);

/**
 * NBI TM Shaper Configuration
 *
 * This structure contains a range of TM shapers to initialise from and
 * including shaper number "start" up to and including shaper number "end"
 */
struct nfp_nbi_tm_shaper_cluster {
    unsigned int                            in_use; /** < If 0, this range will be ignored*/
    unsigned int                            start; /** < First shaper */
    unsigned int                            end; /** < Last shaper */
    unsigned int                            last; /** < Last cluster in array */
    struct nfp_nbi_tm_shaper                shaper; /** < See struct nfp_nbi_tm_shaper*/
}__declspec(packed);

/**
 * NBI TM Scheduler Configuration
 *
 * This structure contains a range of TM schedulers to initialise from and
 * including schedulers number "start" up to and including schedulers number "end"
 */
struct nfp_nbi_tm_l1l2_scheduler_cluster {
    unsigned int                            in_use; /** < If 0, this range will be ignored*/
    unsigned int                            start; /** < First scheduler */
    unsigned int                            end; /** < Last scheduler */
    unsigned int                            last; /** < Last cluster in array */
    struct nfp_nbi_tm_scheduler_config      scheduler_config; /** < Will be written to TrafficManagerReg.TrafficManager.TMSchedulerReg.SchedulerConfigX */
    struct nfp_nbi_tm_scheduler_weight      weight[L1L2_SCHEDULER_INPUTS]; /** < DWRR weights. Will be ignored if scheduler is not in DWRR mode*/
}__declspec(packed);

/**
 * NBI TM Configuration specification
 *
 * This structure contains all the information needed to re-initialise the NBI
 * Traffic Manager. It has info for the TM config register, the queues  the
 * shaper and the schedulers.
 */
struct nfp_nbi_tm_config_spec {
    struct nfp_nbi_tm_traffic_manager_config \
        tm_config; /* Will be written to TrafficManagerReg.TrafficManagerConfig */
    struct nfp_nbi_tm_queue_cluster \
        tm_queue_cluster[TM_INIT_MAX_Q_CLUSTERS]; /* An array of queue ranges. All the queues in all the ranges will be initialised according to struct nfp_nbi_tm_queue_cluster */
    struct nfp_nbi_tm_shaper_cluster \
        tm_shapers_cluster[TM_INIT_MAX_SHAPER_CLUSTERS]; /* An array of shaper ranges. All the shapers in all the ranges will be initialised according to struct nfp_nbi_tm_shaper_cluster */
    struct nfp_nbi_tm_l1l2_scheduler_cluster \
        tm_scheduler_cluster[TM_INIT_MAX_SCHEDULER_CLUSTERS]; /* An array of scheduler ranges. All the schedulers in all the ranges will be initialised according to struct nfp_nbi_tm_l1l2_scheduler_cluster */
}__declspec(packed);

/**
 * Configure the NBI Traffic Manager shapers
 * @param nbi               NBI number
 * @param tm_shaper_cluster[] Pointer to an array of struct nfp_nbi_tm_shaper_cluster
 * @return 0 if successful, -1 if the NBI number or a shaper number is out of
 * range
 *
 * This function takes a pointer to an array of struct nfp_nbi_tm_shaper_cluster
 * and configures all the shapers in the ranges found to be in use.
 */
int nbi_tm_config_shapers(unsigned int nbi,
                        __mem struct nfp_nbi_tm_shaper_cluster \
                        tm_shaper_cluster[TM_INIT_MAX_SHAPER_CLUSTERS]);

/**
 * Configure the NBI Traffic Manager schedulers
 * @param nbi                   NBI number
 * @param tm_scheduler_cluster[]  Pointer to an array of struct nfp_nbi_tm_l1l2_scheduler_cluster
 * @return 0 if successful, -1 if the NBI number or a schedulers number is out of
 * range
 *
 * This function takes a pointer to an array of struct nfp_nbi_tm_l1l2_scheduler_cluster
 * and configures all the schedulers in the ranges found to be in use.
 */
int nfp_nbi_tm_config_schedulers(unsigned int nbi,
                        __mem struct nfp_nbi_tm_l1l2_scheduler_cluster \
                        tm_scheduler_cluster[TM_INIT_MAX_SCHEDULER_CLUSTERS]);

/**
 * Configures the NBI Traffic Manager queues
 * @param nbi                   NBI number
 * @param tm_queue_cluster[]  Pointer to an array of struct nfp_nbi_tm_queue_cluster
 * @return 0 if successful, -1 if the NBI number or a schedulers number is out of
 * range. Or if the HeadTail SRAM went out of range.
 *
 * This function takes a pointer to an array of struct nfp_nbi_tm_queue_cluster
 * and configures all the queues in the ranges found to be in use.
 * Additionally the HTSRAM is initialised according to the databook. If the
 * queue sizes provided in the struct are too large, and the next HTSRAM value
 * will point outside of the 16K TM descriptor RAM, the function terminate early
 * and return -1
 */
int nfp_nbi_tm_config_queues(unsigned int nbi,
    __mem struct nfp_nbi_tm_queue_cluster \
    tm_queue_cluster[TM_INIT_MAX_Q_CLUSTERS]);

/**
 * Configures the NBI Traffic Manager Config Register
 * @param nbi                       NBI number
 * @param traffic_manager_config    Pointer to struct nfp_nbi_tm_traffic_manager_config
 * @return 0 if successful, -1 if the NBI number is out of range
 *
 * This function takes a pointer to an array of struct nfp_nbi_tm_traffic_manager_config
 * and configures the TM Config CSR.
 */
int nfp_nbi_tm_config(unsigned int nbi,
    struct nfp_nbi_tm_traffic_manager_config traffic_manager_config);

#endif
