/*
 * Copyright 2015 Netronome, Inc.
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
 * @file          lib/net/_c/csum.c
 * @brief         Full checksum calculation functions
 */

#include <assert.h>
#include <nfp.h>
#include <stdint.h>

#include <std/reg_utils.h>
#include <net/ip.h>
#include <net/csum.h>
#include <nfp/mem_bulk.h>

#define UINT32_REG(_a) ((__is_in_lmem(_a)) ? ((__lmem uint32_t *)_a)        \
                                           : ((__gpr  uint32_t *)_a))

#define SUM32(_x) (((_x) >> 16) + (uint16_t)(_x))

#define SUM_64BYTES_T(_sum, _buf, _len)                                     \
    do {                                                                    \
        __gpr uint32_t i;                                                   \
        __gpr uint32_t t_val;                                               \
        __gpr uint32_t val;                                                 \
        __gpr uint32_t rem;                                                 \
        t_val = ((__ctx() << 5) | __xfer_reg_number(_buf)) << 2;            \
        __asm { local_csr_wr[t_index, t_val] }                              \
        __asm { nop }                                                       \
        __asm { nop }                                                       \
        __asm { nop }                                                       \
        for (i = 0; i < _len/sizeof(uint32_t); i++) {                       \
            __asm { alu[val, --, B, *$index++] }                            \
            _sum += SUM32(val);                                             \
        }                                                                   \
        rem = _len & 3;                                                     \
        if (rem > 0) {                                                      \
            __asm { alu[val, --, B, *$index] }                              \
            if (rem == 1) {                                                 \
                val = val & 0xFF000000;                                     \
            } else if (rem == 2) {                                          \
                val = val & 0xFFFF0000;                                     \
            } else if (rem == 3) {                                          \
                val = val & 0xFFFFFF00;                                     \
            }                                                               \
            _sum += SUM32(val);                                             \
        }                                                                   \
    } while (0)


__intrinsic uint16_t
net_csum_mod(uint32_t orig_csum, uint32_t orig_val, uint32_t new_val)
{
    __gpr uint32_t new_csum;

    new_csum = (~orig_csum & 0xFFFF) + (~orig_val & 0xFFFF) + new_val;
    new_csum = SUM32(new_csum);
    new_csum = SUM32(new_csum);

    return (~new_csum) & 0xFFFF;
}

__intrinsic uint16_t
net_csum_ipv4(void *ip, __addr40 void *pkt_ptr)
{
    __gpr uint32_t sum = 0;
    __gpr uint32_t opt_size;
    __gpr uint32_t hl;
    __xread uint32_t ip_opts[10];
    SIGNAL read_sig;

    ctassert(__is_in_reg_or_lmem(ip));

    /* Sum up the standard IP header */
    sum += SUM32(UINT32_REG(ip)[0]);
    sum += SUM32(UINT32_REG(ip)[1]);
    sum += SUM32(UINT32_REG(ip)[2]);
    sum += SUM32(UINT32_REG(ip)[3]);
    sum += SUM32(UINT32_REG(ip)[4]);

    /* Handle IP Options if exist */
    if (__is_in_lmem(ip)) {
        hl = ((__lmem struct ip4_hdr *)ip)->hl;
    } else {
        hl = ((__gpr struct ip4_hdr *)ip)->hl;
    }

    if(hl > NET_IP4_LEN32) {
        opt_size = (hl - NET_IP4_LEN32) * sizeof(uint32_t);
        ((__addr40 uint8_t*)pkt_ptr) -= opt_size;
        /* The read size must be a mult of 8 bytes */
        __mem_read64(ip_opts, pkt_ptr, ((opt_size + 7) & 0x78),
                     sizeof(ip_opts), ctx_swap, &read_sig);
        SUM_64BYTES_T(sum, ip_opts, opt_size);
    }

    /* Fold twice, avoid branches */
    sum = SUM32(sum);
    sum = SUM32(sum);

    return (~sum) & 0xFFFF;
}

static __intrinsic uint16_t
net_csum_l4_ip(uint32_t ip_type, uint32_t protocol,
               void *ip, void *l4_hdr,
               __addr40 void* pkt_ctm, uint32_t ctm_len,
               __addr40 void* pkt_mem, uint32_t mem_len)
{
    __gpr uint32_t sum = 0;
    __xread uint32_t pkt_cache[16];
    __gpr int len;
    __gpr int curr_len;
    __addr40 void* pkt_ptr;
    SIGNAL read_sig;
    __gpr uint32_t tmp;
    __gpr uint32_t l4_len;
    __gpr uint32_t csum_mu = 0;

    ctassert(__is_in_reg_or_lmem(ip));
    ctassert(__is_in_reg_or_lmem(l4_hdr));

    /* Shared part of pseudo header for UDP and TCP */
    sum += SUM32(UINT32_REG(ip)[3]);
    sum += SUM32(UINT32_REG(ip)[4]);

    if (ip_type == NET_ETH_TYPE_IPV6) {
        sum += SUM32(UINT32_REG(ip)[2]);
        sum += SUM32(UINT32_REG(ip)[5]);
        sum += SUM32(UINT32_REG(ip)[6]);
        sum += SUM32(UINT32_REG(ip)[7]);
        sum += SUM32(UINT32_REG(ip)[8]);
        sum += SUM32(UINT32_REG(ip)[9]);
    }

    sum += SUM32(UINT32_REG(l4_hdr)[0]);
    sum += SUM32(UINT32_REG(l4_hdr)[1]);

    if (ip_type == NET_ETH_TYPE_IPV6) {
        sum += SUM32(protocol);
    } else {
        tmp = protocol << 16;
    }

    if (protocol == NET_IP_PROTO_UDP) {
        if (__is_in_lmem(l4_hdr)) {
            l4_len = ((__lmem struct udp_hdr*)l4_hdr)->len;
        } else {
            l4_len = ((__gpr struct udp_hdr*)l4_hdr)->len;
        }
        /* Skip UDP header */
        if (ctm_len > 0) {
            ctm_len -= sizeof(struct udp_hdr);
            ((__addr40 uint8_t*)pkt_ctm) += sizeof(struct udp_hdr);
        } else {
            mem_len -= sizeof(struct udp_hdr);
            ((__addr40 uint8_t*)pkt_mem) += sizeof(struct udp_hdr);
        }
    } else {
        l4_len = ctm_len + mem_len;

        /* Skip basic TCP header */
        if (ctm_len > 0) {
            ctm_len -= sizeof(struct tcp_hdr);
            ((__addr40 uint8_t*)pkt_ctm) += sizeof(struct tcp_hdr);
        } else {
            mem_len -= sizeof(struct tcp_hdr);
            ((__addr40 uint8_t*)pkt_mem) += sizeof(struct tcp_hdr);
        }

        sum += SUM32(UINT32_REG(l4_hdr)[2]);
        sum += SUM32(UINT32_REG(l4_hdr)[3]);
        sum += SUM32(UINT32_REG(l4_hdr)[4]);
    }

    if (ip_type == NET_ETH_TYPE_IPV6) {
        sum += SUM32(l4_len);
    } else {
        tmp |= l4_len;
        sum += SUM32(tmp);
    }
    /* No payload */
    if (ctm_len + mem_len == 0) {
        goto csum_fold;
    }

    /* Handle CTM */
    if (ctm_len > 0) {
        len = ctm_len;
        pkt_ptr = pkt_ctm;

        while (len > 0) {
            if (len > sizeof(pkt_cache))
                curr_len = sizeof(pkt_cache);
            else
                curr_len = len;
            /* The read size must be a mult of 8 bytes */
            __mem_read64(pkt_cache, pkt_ptr, ((curr_len + 7) & 0x78),
                         sizeof(pkt_cache), ctx_swap, &read_sig);
            SUM_64BYTES_T(sum, pkt_cache, curr_len);
            __implicit_read(pkt_cache);
            ((__addr40 uint8_t*)pkt_ptr) += curr_len;
            len -= curr_len;
        }
    }

    /* Handle external MEM */
    if (mem_len > 0) {
        len = mem_len;
        pkt_ptr = pkt_mem;

        while (len > 0) {
            if (len > sizeof(pkt_cache))
                curr_len = sizeof(pkt_cache);
            else
                curr_len = len;
            /* The read size must be a mult of 8 bytes */
            __mem_read64(pkt_cache, pkt_ptr, ((curr_len + 7) & 0x78),
                         sizeof(pkt_cache), ctx_swap, &read_sig);
            SUM_64BYTES_T(sum, pkt_cache, curr_len);
            __implicit_read(pkt_cache);
            ((__addr40 uint8_t*)pkt_ptr) += curr_len;
            len -= curr_len;
        }
    }
csum_fold:
    sum = SUM32(sum);
    sum = SUM32(sum);
    return (~sum) & 0xFFFF;
}

__intrinsic uint16_t
net_csum_ipv4_udp(void *ip, void* udp,
                  __addr40 void* pkt_ctm, uint32_t ctm_len,
                  __addr40 void* pkt_mem, uint32_t mem_len)
{
    ctassert(__is_in_reg_or_lmem(ip));
    ctassert(__is_in_reg_or_lmem(udp));

    return net_csum_l4_ip(NET_ETH_TYPE_IPV4, NET_IP_PROTO_UDP, ip, udp,
                          pkt_ctm, ctm_len, pkt_mem, mem_len);
}

__intrinsic uint16_t
net_csum_ipv4_tcp(void *ip, void* tcp,
                  __addr40 void* pkt_ctm, uint32_t ctm_len,
                  __addr40 void* pkt_mem, uint32_t mem_len)
{
    ctassert(__is_in_reg_or_lmem(ip));
    ctassert(__is_in_reg_or_lmem(tcp));

    return net_csum_l4_ip(NET_ETH_TYPE_IPV4, NET_IP_PROTO_TCP, ip, tcp,
                          pkt_ctm, ctm_len, pkt_mem, mem_len);
}

__intrinsic uint16_t
net_csum_ipv6_udp(void *ip, void *udp,
                  __addr40 void *pkt_ctm, uint32_t ctm_len,
                  __addr40 void *pkt_mem, uint32_t mem_len)
{
    ctassert(__is_in_reg_or_lmem(ip));
    ctassert(__is_in_reg_or_lmem(udp));

    return net_csum_l4_ip(NET_ETH_TYPE_IPV6, NET_IP_PROTO_UDP, ip, udp,
                          pkt_ctm, ctm_len, pkt_mem, mem_len);
}

__intrinsic uint16_t
net_csum_ipv6_tcp(void *ip, void *tcp,
                  __addr40 void *pkt_ctm, uint32_t ctm_len,
                  __addr40 void *pkt_mem, uint32_t mem_len)
{
    ctassert(__is_in_reg_or_lmem(ip));
    ctassert(__is_in_reg_or_lmem(tcp));

    return net_csum_l4_ip(NET_ETH_TYPE_IPV6, NET_IP_PROTO_TCP, ip, tcp,
                          pkt_ctm, ctm_len, pkt_mem, mem_len);
}
