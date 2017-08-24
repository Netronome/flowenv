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
 * @file          lib/nfp/_c/tm_config.c
 * @brief         NFP 6000 NBI Traffic Manager Initialisation library
 */


#include <nfp6000/nfp_me.h>
#include <nfp6000/nfp_nbi_tm.h>
#include <nfp/xpb.h>
#include <nfp.h>
#include <nfp/me.h>
#include <nfp/mem_bulk.h>
#include <assert.h>
#include <nfp/tm_config.h>

#define MAX_NBI_NUMBER          1
#define MAX_TM_QUEUE_NUM        1023
#define MAX_TM_L1_L2_SCHED_NUM  143
#define MAX_TM_SHAPER_NUM       144
#define HEAD_TAIL_SRAM_MAX      16384
#define QUEUE_SIZE_MIN          3
/**
 * NBI Traffic Manager CPP bus offset for a given NBI island.
 */
#ifndef NFP_NBI_TM_CPP_OFF
#define NFP_NBI_TM_CPP_OFF(_isl) ((_isl) << 24)
#endif


/**
 * NBI Traffic Manager Head Tail SRAM CPP bus offset for a given NBI island
 */
#ifndef NBI_TM_HEAD_TAIL_SRAM_OFFS
#define NBI_TM_HEAD_TAIL_SRAM_OFFS  0x268000
#endif

#ifndef NBI_TM_HEAD_TAIL_SRAM
#define NBI_TM_HEAD_TAIL_SRAM(_isl) ((NFP_NBI_TM_CPP_OFF(_isl)) | \
    NBI_TM_HEAD_TAIL_SRAM_OFFS)
#endif

/** Base addresses for the NBI TM scheduler config registers. */
#define TM_SCHED_CONFIG_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_REG)

/** Base addresses for the NBI TM L0 scheduler weight registers. */
#define TM_SCHED_L0_WEIGHT_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_REG)

/** Base addresses for the NBI TM L0 scheduler deficit registers. */
#define TM_SCHED_L0_DEFICIT_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_REG)

/** Base addresses for the NBI TM scheduler L1 weight registers. */
#define TM_SCHED_L1_WEIGHT_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_L1_WEIGHT)

/** Base addresses for the NBI TM scheduler L2 weight registers. */
#define TM_SCHED_L2_WEIGHT_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_L2_WEIGHT)

/** Base addresses for the NBI TM scheduler L1 deficit registers. */
#define TM_SCHED_L1_DEFICIT_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_L1_DEFICIT)

/** Base addresses for the NBI TM scheduler L2 deficit registers. */
#define TM_SCHED_L2_DEFICIT_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SCHEDULER_L2_DEFICIT)

/** Base addresses for the NBI TM shaper registers. */
#define TM_SHAPER_XPB_BASE(_nbi)  (NFP_NBI_TM_XPB_OFF(_nbi) + \
    NFP_NBI_TM_SHAPER_REG)

/** Address of the TM queue config register. */
#define TM_QUEUE_CONFIG_ADDR(_nbi, _qnum)                       \
    (TMQ_XPB_BASE(_nbi) + NFP_NBI_TM_QUEUE_CONFIG(_qnum))

/** Address of the TM config register. */
#define TM_CONFIG_REG_ADDR(_nbi)                       \
    (NFP_NBI_TM_XPB_OFF(_nbi) + NFP_NBI_TM_TRAFFIC_MANAGER_REG)

/** Address of the TM scheduler config register. */
#define TM_SCHED_CONFIG_ADDR(_nbi, _sched)                       \
    (TM_SCHED_CONFIG_XPB_BASE(_nbi) + NFP_NBI_TM_SCHEDULER_CONFIG(_sched))

/** Address of the TM L0 scheduler weight register. */
#define TM_SCHED_L0_WEIGHT_ADDR(_nbi, _sched)                       \
    (TM_SCHED_L0_WEIGHT_XPB_BASE(_nbi) + \
    NFP_NBI_TM_SCHEDULER_WEIGHT(((_sched) * L1L2_SCHEDULER_INPUTS)))

/** Address of the TM L1 scheduler weight register. */
#define TM_SCHED_L1_WEIGHT_ADDR(_nbi, _sched)                       \
    (TM_SCHED_L1_WEIGHT_XPB_BASE(_nbi) + \
    NFP_NBI_TM_L1_L2_SCHEDULER_WEIGHT(((_sched) * L1L2_SCHEDULER_INPUTS)))

/** Address of the TM L2 scheduler weight register. */
#define TM_SCHED_L2_WEIGHT_ADDR(_nbi, _sched)                       \
    (TM_SCHED_L2_WEIGHT_XPB_BASE(_nbi) + \
    NFP_NBI_TM_L1_L2_SCHEDULER_WEIGHT(((_sched) * L1L2_SCHEDULER_INPUTS)))

    /** Address of the TM L1 scheduler deficit register. */
#define TM_SCHED_L0_DEFICIT_ADDR(_nbi, _sched)                       \
    (TM_SCHED_L0_DEFICIT_XPB_BASE(_nbi) + \
    NFP_NBI_TM_SCHEDULER_DEFICIT(((_sched) * L1L2_SCHEDULER_INPUTS)))

/** Address of the TM L1 scheduler deficit register. */
#define TM_SCHED_L1_DEFICIT_ADDR(_nbi, _sched)                       \
    (TM_SCHED_L1_DEFICIT_XPB_BASE(_nbi) + \
    NFP_NBI_TM_L1_L2_SCHEDULER_DEFICIT(((_sched) * L1L2_SCHEDULER_INPUTS)))

/** Address of the TM L2 scheduler deficit register. */
#define TM_SCHED_L2_DEFICIT_ADDR(_nbi, _sched)                       \
    (TM_SCHED_L2_DEFICIT_XPB_BASE(_nbi) + \
    NFP_NBI_TM_L1_L2_SCHEDULER_DEFICIT(((_sched) * L1L2_SCHEDULER_INPUTS)))

/** Address of the TM shaper rate register. */
#define TM_SHAPER_RATE_ADDR(_nbi, _shaper)                       \
    (TM_SHAPER_XPB_BASE(_nbi) + NFP_NBI_TM_SHAPER_RATE(_shaper))

/** Address of the TM shaper threshold register. */
#define TM_SHAPER_THRESHOLD_ADDR(_nbi, _shaper)                       \
    (TM_SHAPER_XPB_BASE(_nbi) + NFP_NBI_TM_SHAPER_THRESHOLD(_shaper))

/** Address of the TM shaper max overshoot register. */
#define TM_SHAPER_MAX_OVERSHOOT_ADDR(_nbi, _shaper)                       \
    (TM_SHAPER_XPB_BASE(_nbi) + NFP_NBI_TM_SHAPER_MAX_OVERSHOOT(_shaper))

/** Address of the TM shaper rate adjust register. */
#define TM_SHAPER_RATE_ADJUST_ADDR(_nbi, _shaper)                       \
    (TM_SHAPER_XPB_BASE(_nbi) + NFP_NBI_TM_SHAPER_RATE_ADJUST(_shaper))

static __inline int
nbi_tm_q_config__(uint32_t nbi, uint32_t qnum,
__xread struct nfp_nbi_tm_queue_config queue_config, uint32_t head_tail_sram)
{

    __gpr uint32_t addr_queue_config;
    int ret = 0;
    SIGNAL sig_queue_config;
    __xwrite uint32_t head_tail_sram_xfer[2];
    __gpr uint32_t ht_sram_hi;
    __gpr uint32_t ht_sram_lo;
    SIGNAL sig_head_tail_sram;
    __xwrite uint32_t queue_config_xw;

    if (nbi > MAX_NBI_NUMBER) {
        ret = -1;
        goto out;
    }

    if (qnum > MAX_TM_QUEUE_NUM) {
        ret = -1;
        goto out;
    }
    addr_queue_config = TM_QUEUE_CONFIG_ADDR(nbi, qnum);
    queue_config_xw = queue_config.__raw;

    head_tail_sram_xfer[0] = (head_tail_sram << 14 | head_tail_sram);
    head_tail_sram_xfer[1] = 0;
    ht_sram_hi = (NBI_TM_HEAD_TAIL_SRAM(nbi) >> 8);
    ht_sram_lo = qnum * sizeof(head_tail_sram_xfer);

    __asm {
        ct[xpb_write, *queue_config_xw, addr_queue_config, 0, 1], \
        sig_done[sig_queue_config]
        nbi[write, head_tail_sram_xfer[0], ht_sram_hi, <<8, ht_sram_lo, 1], \
        sig_done[sig_head_tail_sram]
        ctx_arb[sig_queue_config, sig_head_tail_sram]
    }

out:
    return ret;
}

static __inline int
nbi_tm_l1l2_scheduler_config__(uint32_t nbi, uint32_t sched,
    __xread struct nfp_nbi_tm_scheduler_config scheduler_config,
    __xread struct nfp_nbi_tm_scheduler_weight weight[L1L2_SCHEDULER_INPUTS])
{
    int ret = 0;
    __gpr uint32_t addr_sched;
    __gpr uint32_t addr_weight;
    __gpr uint32_t addr_deficit;
    __xwrite uint32_t sched_config_xw;
    __xwrite uint32_t sched_weight_xw[L1L2_SCHEDULER_INPUTS];

    SIGNAL sched_sig, weight_sig, deficit_sig;

    if (nbi > MAX_NBI_NUMBER) {
        ret = -1;
        goto out;
    }

    if (sched > MAX_TM_L1_L2_SCHED_NUM) {
        ret = -1;
        goto out;
    }

    addr_sched = TM_SCHED_CONFIG_ADDR(nbi, sched);


    if (scheduler_config.dwrrenable) {
         __xwrite uint32_t sched_deficit_xw[L1L2_SCHEDULER_INPUTS] = \
                                            {0, 0, 0, 0, 0, 0, 0, 0};
        sched_config_xw = scheduler_config.__raw;
        if (sched < 128) {
            addr_weight = TM_SCHED_L2_WEIGHT_ADDR(nbi, sched);
            addr_deficit = TM_SCHED_L2_DEFICIT_ADDR(nbi, sched);
        } else {
            addr_weight = TM_SCHED_L1_WEIGHT_ADDR(nbi, sched);
            addr_deficit = TM_SCHED_L1_DEFICIT_ADDR(nbi, sched);
        }
        sched_weight_xw[0] = weight[0].__raw;
        sched_weight_xw[1] = weight[1].__raw;
        sched_weight_xw[2] = weight[2].__raw;
        sched_weight_xw[3] = weight[3].__raw;
        sched_weight_xw[4] = weight[4].__raw;
        sched_weight_xw[5] = weight[5].__raw;
        sched_weight_xw[6] = weight[6].__raw;
        sched_weight_xw[7] = weight[7].__raw;

        __asm {
            ct[xpb_write, *sched_config_xw, addr_sched, 0, 1], \
            sig_done[sched_sig]

            ct[xpb_write, sched_weight_xw[0], addr_weight, 0, 8], \
            sig_done[weight_sig]

            ct[xpb_write, sched_deficit_xw[0], addr_deficit, 0, 8], \
            sig_done[deficit_sig]

            ctx_arb[deficit_sig, sched_sig, weight_sig]
        }
    } else {
        xpb_write(addr_sched, scheduler_config.__raw);
    }

out:
    return ret;
}

static __inline int
nbi_tm_shaper_config__(uint32_t nbi, uint32_t shaper,
                    __xread struct nfp_nbi_tm_shaper * tm_shaper)
{
    int ret = 0;

    __gpr uint32_t addr_shaper_rate;
    __gpr uint32_t addr_shaper_threshold;
    __gpr uint32_t addr_max_overshoot;
    __gpr uint32_t addr_rate_adjust;
    __xwrite uint32_t shaper_rate_xw;
    __xwrite uint32_t shaper_threshold_xw;
    __xwrite uint32_t max_overshoot_xw;
    __xwrite uint32_t rate_adjust_xw;
    SIGNAL sig_shaper_rate;
    SIGNAL sig_shaper_threshold;
    SIGNAL sig_max_overshoot;
    SIGNAL sig_rate_adjust;

    if (nbi > MAX_NBI_NUMBER) {
        ret = -1;
        goto out;
    }

    if (shaper > MAX_TM_L1_L2_SCHED_NUM) {
        ret = -1;
        goto out;
    }

    addr_shaper_rate = TM_SHAPER_RATE_ADDR(nbi, shaper);
    addr_shaper_threshold = TM_SHAPER_THRESHOLD_ADDR(nbi, shaper);
    addr_max_overshoot = TM_SHAPER_MAX_OVERSHOOT_ADDR(nbi, shaper);
    addr_rate_adjust = TM_SHAPER_RATE_ADJUST_ADDR(nbi, shaper);

    shaper_rate_xw = tm_shaper->shaper_rate.__raw;
    shaper_threshold_xw = tm_shaper->shaper_threshold.__raw;
    max_overshoot_xw = tm_shaper->max_overshoot.__raw;
    rate_adjust_xw = tm_shaper->rate_adjust.__raw;

    __asm {
        ct[xpb_write, *shaper_rate_xw, addr_shaper_rate, 0, 1], \
        sig_done[sig_shaper_rate]

        ct[xpb_write, *shaper_threshold_xw, addr_shaper_threshold, 0, 1], \
        sig_done[sig_shaper_threshold]

        ct[xpb_write, *max_overshoot_xw, addr_max_overshoot, 0, 1], \
        sig_done[sig_max_overshoot]

        ct[xpb_write, *rate_adjust_xw, addr_rate_adjust, 0, 1], \
        sig_done[sig_rate_adjust]

        ctx_arb[sig_shaper_rate, \
        sig_shaper_threshold, \
        sig_max_overshoot, \
        sig_rate_adjust]
    }

 out:
    return ret;
}

int
nfp_nbi_tm_config_schedulers(uint32_t nbi,
__mem struct nfp_nbi_tm_l1l2_scheduler_cluster \
tm_scheduler_cluster[TM_INIT_MAX_SCHEDULER_CLUSTERS])
{

    __gpr uint32_t i;
    __gpr uint32_t sched;
    __xread struct nfp_nbi_tm_l1l2_scheduler_cluster scheduler_cluster;
    int ret = 0;

    for (i = 0; i < TM_INIT_MAX_SCHEDULER_CLUSTERS; i++) {

        mem_read32(&scheduler_cluster, &tm_scheduler_cluster[i],
                    sizeof(scheduler_cluster));

        if (scheduler_cluster.in_use) {
            for (sched = scheduler_cluster.start;
                sched <= scheduler_cluster.end; sched++) {

                ret = nbi_tm_l1l2_scheduler_config__(nbi, sched,
                    scheduler_cluster.scheduler_config,
                    &scheduler_cluster.weight[0]);

                if(ret)
                    goto out;
            }
        }

        if (scheduler_cluster.last)
            break;
    }

out:
    return ret;
}

int nbi_tm_config_shapers(uint32_t nbi,
__mem struct nfp_nbi_tm_shaper_cluster \
tm_shaper_cluster[TM_INIT_MAX_SCHEDULER_CLUSTERS])
{

    __gpr uint32_t i;
    __gpr uint32_t shaper;
    __xread struct nfp_nbi_tm_shaper_cluster shaper_cluster;
    int ret = 0;

    for (i = 0; i < TM_INIT_MAX_SCHEDULER_CLUSTERS; i++) {

        mem_read32(&shaper_cluster, &tm_shaper_cluster[i],
                    sizeof(shaper_cluster));

        if (shaper_cluster.in_use) {
            for (shaper = shaper_cluster.start;
                shaper <= shaper_cluster.end; shaper++) {

                ret = nbi_tm_shaper_config__(nbi, shaper, &shaper_cluster.shaper);

                if(ret)
                    goto out;

            }
        }
        if (shaper_cluster.last)
            break;
    }

out:
    return ret;
}


int
nfp_nbi_tm_config_queues(uint32_t nbi,
        __mem struct nfp_nbi_tm_queue_cluster \
        tm_queue_cluster[TM_INIT_MAX_Q_CLUSTERS])
{

    __gpr uint32_t i;
    int ret = 0;
    __gpr uint32_t                              qnum;
    __xread struct nfp_nbi_tm_queue_cluster     queue_cluster;
    __gpr uint32_t                              head_tail_sram = 0;
    __gpr uint32_t                              queue_size;
    __gpr uint32_t                              shf_val;

    for (i = 0; i < TM_INIT_MAX_Q_CLUSTERS; i++) {

        mem_read32(&queue_cluster, &tm_queue_cluster[i],
                   sizeof(queue_cluster));

        if (queue_cluster.in_use) {
            queue_size = queue_cluster.queue_config.queuesize;

            /*There is no need to check the MAX and the MAX is 16 and queuesize
            is a 4 bit field*/
            if(queue_size < QUEUE_SIZE_MIN) {
                ret = -1;
                goto out;
            }
            for (qnum = queue_cluster.start;
                qnum <= queue_cluster.end; qnum++) {

                /* To prevent HEAD TAIL SRAM form overwriting the adjacent
                queue's HTSRAM, the initial values are set as a multiple of
                the queue size*/
                shf_val = head_tail_sram >> queue_size;
                if (head_tail_sram & ((1 << queue_size) - 1)) {
                    shf_val = shf_val + 1;
                }
                head_tail_sram = shf_val << queue_size;

                /* To prevent HEAD TAIL SRAM wrapping, a queue and its
                corresponding HT SRAM is only configured if the intended HT
                SRAM value + 2^queue_size will not exceed the MAX value.
                If this happens, the queue config will abort and the function
                will return an error*/
                if((head_tail_sram + (1 << queue_size)) <= HEAD_TAIL_SRAM_MAX) {
                    ret = nbi_tm_q_config__(nbi, qnum,
                        queue_cluster.queue_config,
                        head_tail_sram);
                    if(ret)
                        goto out;

                } else {
                    ret = -1;
                    goto out;
                }

                /* The next head tail SRAM entry has to start 2^queue_size after
                the previous entry*/
                head_tail_sram = head_tail_sram + (1 << queue_size);
            }
        }

        if (queue_cluster.last)
            break;
    }

out:
    return ret;
}

__intrinsic int
nfp_nbi_tm_config(uint32_t nbi,
            struct nfp_nbi_tm_traffic_manager_config traffic_manager_config)
{
    __gpr uint32_t addr;
    int ret = 0;

    if (nbi > MAX_NBI_NUMBER) {
        ret = -1;
        goto out;
    }

    addr = TM_CONFIG_REG_ADDR(nbi);

    xpb_write(addr, traffic_manager_config.__raw);
out:
    return ret;
}

