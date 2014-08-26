/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          lib/nfp/_c/me.c
 * @brief         ME related functions
 */

#include <assert.h>
#include <nfp.h>

#include <nfp/me.h>

#include <nfp6000/nfp_me.h>

__intrinsic unsigned int
__ME(void)
{
    unsigned int menum;
    struct nfp_mecsr_active_ctx_sts ctxsts;

    ctxsts.__raw = local_csr_read(NFP_MECSR_ACTIVE_CTX_STS);
    menum = (ctxsts.il_id << 4) + ctxsts.me_id;

    return menum;
}

__intrinsic unsigned int
local_csr_read(int mecsr)
{
    unsigned int csr_addr;
    unsigned int result;

    ctassert(__is_ct_const(mecsr));

    csr_addr = mecsr >> 2;

    __asm {
        local_csr_rd[__ct_const_val(csr_addr)];
        immed[result, 0];
    }

    return result;
}

__intrinsic void
local_csr_write(int mecsr, unsigned int data)
{
    unsigned int csr_addr;

    ctassert(__is_ct_const(mecsr));

    csr_addr = mecsr >> 2;

    __asm local_csr_wr[__ct_const_val(csr_addr), data];
}

__intrinsic void
ctx_wait(signal_t sig)
{
    ctassert(sig == kill || sig == voluntary || sig == bpt);

    if (sig == kill)
        __asm ctx_arb[kill];
    else if (sig == voluntary)
        __asm ctx_arb[voluntary];
    else
        __asm ctx_arb[bpt];
}

__intrinsic void
wait_sig_mask(SIGNAL_MASK sigmask)
{
    __asm {
        ctx_arb[--], defer[1]
        local_csr_wr[NFP_MECSR_ACTIVE_CTX_WAKEUP_EVENTS >> 2, sigmask]
    }
}

__intrinsic void
signal_ctx(unsigned int ctx, unsigned int sig_no)
{
    local_csr_write(NFP_MECSR_SAME_ME_SIGNAL,
                    (NFP_MECSR_SAME_ME_SIGNAL_SIG_NO(sig_no) |
                     NFP_MECSR_SAME_ME_SIGNAL_CTX(ctx)));
}

__intrinsic void
signal_next_ctx(unsigned int sig_no)
{
    local_csr_write(NFP_MECSR_SAME_ME_SIGNAL,
                    (NFP_MECSR_SAME_ME_SIGNAL_NEXT_CTX |
                     NFP_MECSR_SAME_ME_SIGNAL_SIG_NO(sig_no)));
}

__intrinsic void
signal_next_me(unsigned int ctx, unsigned int sig_no)
{
    local_csr_write(NFP_MECSR_NEXT_NEIGHBOR_SIGNAL,
                    (NFP_MECSR_NEXT_NEIGHBOR_SIGNAL_SIG_NO(sig_no) |
                     NFP_MECSR_NEXT_NEIGHBOR_SIGNAL_CTX(ctx)));
}

__intrinsic void
signal_prev_me(unsigned int ctx, unsigned int sig_no)
{
    local_csr_write(NFP_MECSR_PREV_NEIGHBOR_SIGNAL,
                    (NFP_MECSR_PREV_NEIGHBOR_SIGNAL_SIG_NO(sig_no) |
                     NFP_MECSR_PREV_NEIGHBOR_SIGNAL_CTX(ctx)));
}

__intrinsic void
set_alarm(unsigned int cycles, SIGNAL *sig)
{
    unsigned sig_num, tslo;

    __implicit_write(sig);
    sig_num = __signal_number(sig);
    tslo = local_csr_read(NFP_MECSR_TIMESTAMP_LOW);
    tslo += cycles >> 4;
    local_csr_write(NFP_MECSR_ACTIVE_CTX_FUTURE_COUNT, tslo);
    local_csr_write(NFP_MECSR_ACTIVE_FUTURE_COUNT_SIGNAL, sig_num);
}

__intrinsic void
clear_alarm(void)
{
    local_csr_write(NFP_MECSR_ACTIVE_FUTURE_COUNT_SIGNAL, 0);
}

__intrinsic void
sleep(unsigned int cycles)
{
    SIGNAL sig;

    __implicit_write(&sig);
    set_alarm(cycles, &sig);
    wait_for_all(&sig);
}

__intrinsic void
halt(void)
{
    __asm halt;
}

__intrinsic int
bit_test(unsigned int data, unsigned int bit_pos)
{
    int result = 1;

    ctassert(__is_ct_const(bit_pos));
    __asm {
        br_bset[data, __ct_const_val(bit_pos), match];
        alu[result, --, B, 0];
        match:
    }

    return result;
}

__intrinsic unsigned int
ffs(unsigned int data)
{
    unsigned result;
    __asm ffs[result, data];
    return result;
}

__intrinsic int
ffs64(unsigned long long int data)
{
    unsigned int hi;

    if ((unsigned int)data != 0) {
        return ffs((unsigned int)data);
    } else {
        hi = (unsigned int)(data >> 32);
        if (hi != 0)
            return ffs(hi) + 32;
        else
            return -1;
    }
}

__intrinsic unsigned int
crc_read(void)
{
    return local_csr_read(NFP_MECSR_CRC_REMAINDER);
}

__intrinsic void
crc_write(unsigned int residue)
{
    local_csr_write(NFP_MECSR_CRC_REMAINDER, residue);
}

__intrinsic unsigned int
crc_32_be(unsigned int data, crc_bytes_t bspec)
{
    unsigned result;

    ctassert(bspec == crc_bytes_0_3 || bspec == crc_bytes_0_2 ||
             bspec == crc_bytes_0_1 || bspec == crc_byte_0 ||
             bspec == crc_bytes_1_3 || bspec == crc_bytes_2_3 ||
             bspec == crc_byte_3);

    if (bspec == crc_bytes_0_3)
        __asm crc_be[crc_32, result, data], bytes_0_3;
    else if (bspec == crc_bytes_0_2)
        __asm crc_be[crc_32, result, data], bytes_0_2;
    else if (bspec == crc_bytes_0_1)
        __asm crc_be[crc_32, result, data], bytes_0_1;
    else if (bspec == crc_byte_0)
        __asm crc_be[crc_32, result, data], byte_0;
    else if (bspec == crc_bytes_1_3)
        __asm crc_be[crc_32, result, data], bytes_1_3;
    else if (bspec == crc_bytes_2_3)
        __asm crc_be[crc_32, result, data], bytes_2_3;
    else /* bspec == crc_byte_3 */
        __asm crc_be[crc_32, result, data], byte_3;

    return result;
}

__intrinsic unsigned int
crc_iscsi_be(unsigned int data, crc_bytes_t bspec)
{
    unsigned result;

    ctassert(bspec == crc_bytes_0_3 || bspec == crc_bytes_0_2 ||
             bspec == crc_bytes_0_1 || bspec == crc_byte_0 ||
             bspec == crc_bytes_1_3 || bspec == crc_bytes_2_3 ||
             bspec == crc_byte_3);

    if (bspec == crc_bytes_0_3)
        __asm crc_be[crc_iscsi, result, data], bytes_0_3;
    else if (bspec == crc_bytes_0_2)
        __asm crc_be[crc_iscsi, result, data], bytes_0_2;
    else if (bspec == crc_bytes_0_1)
        __asm crc_be[crc_iscsi, result, data], bytes_0_1;
    else if (bspec == crc_byte_0)
        __asm crc_be[crc_iscsi, result, data], byte_0;
    else if (bspec == crc_bytes_1_3)
        __asm crc_be[crc_iscsi, result, data], bytes_1_3;
    else if (bspec == crc_bytes_2_3)
        __asm crc_be[crc_iscsi, result, data], bytes_2_3;
    else /* bspec == crc_byte_3 */
        __asm crc_be[crc_iscsi, result, data], byte_3;

    return result;
}

__intrinsic int
inp_state_test(int statename)
{
    int result = 1;

    ctassert(__is_ct_const(statename));

    __asm {
        br_inp_state[__ct_const_val(statename), match];
        alu[result, --, B, 0];
        match:
    }

    return result;
}
