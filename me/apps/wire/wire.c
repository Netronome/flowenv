/**
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
    __addr40 char *pkt;
    __xread struct nbi_meta_null nbi_meta;
    __xread struct nbi_meta_pkt_info *pi = &nbi_meta.pkt_info;

    if (ctx() == 0) {
        local_csr_write(NFP_MECSR_MAILBOX_0, 0);
        local_csr_write(NFP_MECSR_MAILBOX_1, 0);
    }


    for (;;) {
        pkt_nbi_recv(&nbi_meta, sizeof(nbi_meta));

        nrecv++;
        local_csr_write(NFP_MECSR_MAILBOX_0, nrecv);

        pkt = pkt_ctm_ptr40_build(pi->isl, pi->pnum, 0);
        msi = pkt_nop_ms_write(pkt, PKT_NBI_OFFSET);
        pkt_nbi_send(0, pi->pnum, &msi, pi->len, MY_NBI ^ 1, OUT_TXQ,
                     nbi_meta.seqr, nbi_meta.seq);

        nsent++;
        local_csr_write(NFP_MECSR_MAILBOX_1, nsent);
    }
}
