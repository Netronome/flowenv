/*
 * Copyright 2012-2015 Netronome, Inc.
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
 * @file          lib/lu/_c/cam_hash.c
 * @brief         CAM assisted hash table implementation
 */

#ifndef _CAM_HASH_C_
#define _CAM_HASH_C_

#include <assert.h>
#include <nfp.h>
#include <stdint.h>

#include <nfp/mem_bulk.h>
#include <nfp/mem_cam.h>

#include <std/hash.h>
#include <std/reg_utils.h>

#include <lu/cam_hash.h>

__intrinsic int32_t
camht_lookup(__mem void *hash_tbl, __mem void *key_tbl,
             int32_t entries, size_t entry_sz,
             void *key, size_t key_sz)
{
    __gpr int32_t idx;
    __xread uint32_t ht_key[CAMHT_MAX_KEY_SZ32];
    int32_t ret;

    __mem char* kt;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_mem(hash_tbl));
    ctassert(__is_in_mem(key_tbl));

    ctassert(__is_in_reg(key));

    ctassert(__is_ct_const(entries));
    ctassert((entries % CAMHT_BUCKET_ENTRIES) == 0);

    ctassert(__is_ct_const(key_sz));
    ctassert(key_sz <= CAMHT_MAX_KEY_SZ);
    ctassert((key_sz % 4) == 0);

    ctassert(__is_ct_const(entry_sz));
    ctassert(entry_sz <= 64);
    ctassert((entry_sz % 4) == 0);

    /* Do the hash table lookup.
     *
     * We declare an array of __xread registers above with the max
     * sized key, but here we only read up to @key_sz (which is a
     * compile time constant) and subsequently only use up to @key_sz
     * transfer registers.  We rely on the C compiler to realise this
     * and only allocate @key_sz read transfer registers (which it
     * does).
     */
    idx = camht_lookup_idx(hash_tbl, entries, key, key_sz);
    if (idx < 0) {
        ret = -1;
        goto out;
    }

    /* compare keys */
    kt = key_tbl;
    kt += (idx * entry_sz);
    mem_read64(ht_key, kt, key_sz);
    if (reg_eq(ht_key, key, key_sz)) {
        ret = idx;
        goto out;
    }

    ret = -1;
out:
    return ret;
}


__intrinsic int32_t
camht_lookup_idx(__mem void *hash_tbl, int32_t entries,
                 void *key, size_t key_sz)
{
    __gpr uint32_t crc32;
    __gpr uint32_t crc32c;
    __gpr uint32_t b_idx;
    __gpr uint32_t b_entry;
    __xrw struct mem_cam_24bit cam;
    int32_t ret;

    __mem uint32_t *ht;

    /* Make sure the parameters are as we expect */
    ctassert(__is_in_mem(hash_tbl));

    ctassert(__is_in_reg(key));

    ctassert(__is_ct_const(entries));
    ctassert((entries % CAMHT_BUCKET_ENTRIES) == 0);

    ctassert(__is_ct_const(key_sz));
    ctassert(key_sz <= CAMHT_MAX_KEY_SZ);
    ctassert((key_sz % 4) == 0);

    /* Compute the CRC-32 and CRC-32C hash from the key */
    crc32  = hash_me_crc32(key, key_sz, 0);
    crc32c = hash_me_crc32c(key, key_sz, 0);

    /* Calculate bucket index and do a CAM lookup in the bucket */
    ht = hash_tbl;
    b_idx = CAMHT_BUCKET_IDX(crc32, entries);
    ht += b_idx * CAMHT_BUCKET_ENTRIES;

    cam.search.value = CAMHT_BUCKET_HASH(crc32c);
    mem_cam256_lookup24(&cam, ht);
    if (!mem_cam_lookup_hit(cam)) {
        ret = -1;
        goto out;
    }

    ret = (b_idx * CAMHT_BUCKET_ENTRIES) + cam.result.match;
out:
    return ret;
}

#endif /* !_CAM_HASH_C_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
