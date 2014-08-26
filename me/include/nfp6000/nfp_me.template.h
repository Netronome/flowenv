/*
 * Copyright (C) 2013-2014,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          nfp6000/nfp_me.h
 * @brief         NFP6000 Microengine CSR definitions
 */

#ifndef _NFP6000__NFP_ME_H_
#define _NFP6000__NFP_ME_H_

pyexec<set_output_mode("nfp")>

pyexec<dump_map(MeCsrCPP(altname="MECSR"), docs=True)>

/*
 * ME CSRs
 */
/*
 * Register: PrevAlu (Note: This is not strictly a CSR)
 *   [31:16]   Data16
 *   [15]      Reserved (0)
 *   [14]      OvSigCtx
 *   [13]      OvSigNum
 *   [12:8]    Length
 *   [7]       OvLen
 *   [6]       OvBmCSR
 *   [5:3]     OveData
 *   [2:1]     OveMaster
 *   [0]       OvSM
 */
#define NFP_MECSR_PREV_ALU_DATA16(x)                       (((x) & 0xffff) << 16)
#define NFP_MECSR_PREV_ALU_DATA16_of(x)                    (((x) >> 16) & 0xffff)
#define   NFP_MECSR_PREV_ALU_DATA16_bf                     0, 31, 16
#define   NFP_MECSR_PREV_ALU_DATA16_mask                   (0xffff)
#define   NFP_MECSR_PREV_ALU_DATA16_shift                  (16)
#define NFP_MECSR_PREV_ALU_OV_SIG_CTX                      (1 << 14)
#define   NFP_MECSR_PREV_ALU_OV_SIG_CTX_bf                 0, 14, 14
#define   NFP_MECSR_PREV_ALU_OV_SIG_CTX_mask               (0x1)
#define   NFP_MECSR_PREV_ALU_OV_SIG_CTX_bit                (14)
#define NFP_MECSR_PREV_ALU_OV_SIG_NUM                      (1 << 13)
#define   NFP_MECSR_PREV_ALU_OV_SIG_NUM_bf                 0, 13, 13
#define   NFP_MECSR_PREV_ALU_OV_SIG_NUM_mask               (0x1)
#define   NFP_MECSR_PREV_ALU_OV_SIG_NUM_bit                (13)
#define NFP_MECSR_PREV_ALU_LENGTH(x)                       (((x) & 0x1f) << 8)
#define NFP_MECSR_PREV_ALU_LENGTH_of(x)                    (((x) >> 8) & 0x1f)
#define   NFP_MECSR_PREV_ALU_LENGTH_bf                     0, 12, 8
#define   NFP_MECSR_PREV_ALU_LENGTH_mask                   (0x1f)
#define   NFP_MECSR_PREV_ALU_LENGTH_shift                  (8)
#define NFP_MECSR_PREV_ALU_OV_LEN                          (1 << 7)
#define   NFP_MECSR_PREV_ALU_OV_LEN_bf                     0, 7, 7
#define   NFP_MECSR_PREV_ALU_OV_LEN_mask                   (0x1)
#define   NFP_MECSR_PREV_ALU_OV_LEN_bit                    (7)
#define NFP_MECSR_PREV_ALU_OV_BM_CSR                       (1 << 6)
#define   NFP_MECSR_PREV_ALU_OV_BM_CSR_bf                  0, 6, 6
#define   NFP_MECSR_PREV_ALU_OV_BM_CSR_mask                (0x1)
#define   NFP_MECSR_PREV_ALU_OV_BM_CSR_bit                 (6)
#define NFP_MECSR_PREV_ALU_OVE_DATA(x)                     (((x) & 7) << 3)
#define NFP_MECSR_PREV_ALU_OVE_DATA_of(x)                  (((x) >> 3) & 7)
#define   NFP_MECSR_PREV_ALU_OVE_DATA_bf                   0, 5, 3
#define   NFP_MECSR_PREV_ALU_OVE_DATA_mask                 (7)
#define   NFP_MECSR_PREV_ALU_OVE_DATA_shift                (3)
#define NFP_MECSR_PREV_ALU_OVE_MASTER(x)                   (((x) & 3) << 1)
#define NFP_MECSR_PREV_ALU_OVE_MASTER_of(x)                (((x) >> 1) & 3)
#define   NFP_MECSR_PREV_ALU_OVE_MASTER_bf                 0, 2, 1
#define   NFP_MECSR_PREV_ALU_OVE_MASTER_mask               (3)
#define   NFP_MECSR_PREV_ALU_OVE_MASTER_shift              (1)
#define NFP_MECSR_PREV_ALU_OV_SM                           (1 << 0)
#define   NFP_MECSR_PREV_ALU_OV_SM_bf                      0, 0, 0
#define   NFP_MECSR_PREV_ALU_OV_SM_mask                    (0x1)
#define   NFP_MECSR_PREV_ALU_OV_SM_bit                     (0)

/*
 * ME CSR register structures
 */
#if defined(__NFP_LANG_MICROC)

pyexec<dump_map_structs(MeCsrCPP(altname="MECSR"))>

struct nfp_mecsr_prev_alu {
    union {
        struct {
#           ifdef BIGENDIAN
            unsigned int data16:16;
            unsigned int res:1;
            unsigned int ov_sig_ctx:1;
            unsigned int ov_sig_num:1;
            unsigned int length:5;
            unsigned int ov_len:1;
            unsigned int ov_bm_csr:1;
            unsigned int ove_data:3;
            unsigned int ove_master:2;
            unsigned int ov_sm:1;
#           else
            unsigned int ov_sm:1;
            unsigned int ove_master:2;
            unsigned int ove_data:3;
            unsigned int ov_bm_csr:1;
            unsigned int ov_len:1;
            unsigned int length:5;
            unsigned int ov_sig_num:1;
            unsigned int ov_sig_ctx:1;
            unsigned int res:1;
            unsigned int data16:16;
#           endif
        };
        unsigned int __raw;
    };
};

#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP6000__NFP_ME_H_ */
