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
 * @file        wire.c
 * @brief       Basic wire app in a worker ME.
 */
#include <nfp.h>

#include <nfp/me.h>

#include <nfp6000/nfp_me.h>

#include <pkt/pkt.h>

#ifndef PKT_NBI_OFFSET
#warning "PKT_NBI_OFFSET not #defined: assuming 64"
#define PKT_NBI_OFFSET 64
#endif

#ifndef MY_NBI
#warning "No MY_NBI #defined: assuming 0"
#define MY_NBI 0
#endif

#define OUT_TXQ 0

__shared int nrecv = 0;
__shared int nsent = 0;


void main(void)
{
    __gpr struct pkt_ms_info msi;
    __addr40 char *pbuf;
    __xread struct nbi_meta_null nbi_meta;
    __xread struct nbi_meta_pkt_info *pi = &nbi_meta.pkt_info;

    if (ctx() == 0) {
        local_csr_write(local_csr_mailbox_0, 0);
        local_csr_write(local_csr_mailbox_1, 0);
    }


    for (;;) {
        pkt_nbi_recv(&nbi_meta, sizeof(nbi_meta));

        nrecv++;
        local_csr_write(local_csr_mailbox_0, nrecv);

        pbuf = pkt_ctm_ptr40(pi->isl, pi->pnum, 0);
        msi = pkt_msd_noop_write(pbuf, PKT_NBI_OFFSET);
        pkt_nbi_send(0, pi->pnum, &msi, pi->len, MY_NBI ^ 1, OUT_TXQ,
                     nbi_meta.seqr, nbi_meta.seq);

        nsent++;
        local_csr_write(local_csr_mailbox_1, nsent);
    }
}
