/*
 * Copyright 2012-2014 Netronome, Inc.
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
 * @file          lib/hash/cam_hash_ctrl.h
 * @brief         Control interface for a CAM assisted hash table
 */

#ifndef _CAM_HASH_CTRL_H_
#define _CAM_HASH_CTRL_H_

/**
 * @CAMHT_MAX_KEY_SZ            Maximum size of the hash key
 * @CAMHT_BUCKET_ENTRIES        Number of entries in a hash bucket
 * @CAMHT_ENTRY_SZ              Size of an entry in a bucket
 * @CAMHT_BUCKET_MASK()         Mask for first hash value to get the bucket idx
 * @CAMHT_BUCKET_IDX()          Get the bucket index from a hash value
 * @CAMHT_BUCKET_HASH()         Convert second hash to a value used
 *                              for the CAM lookup.
 * @CAMHT_BUCKET_HASH_of()      Return the hash value for a value in a bucket
 * @CAMHT_BUCKET_OFF()          Address offset of given bucket index
 * @CAMHT_TBL_IDX()             Given a bucket and an entry in a bucket,
 *                              return the index into the table.
 * @CAMHT_IDX2OFF()             Return the offset for a given table index
 * @CAMHT_IDX2BUCKET()          Return the bucket index for a given table index
 * @CAMHT_IDX2ENTRY()           Return the entry index inside a bucket for
 *                              a given table index
 *
 * @CAMHT_HASH_TBL()            Symbol name for the hash table
 * @CAMHT_KEY_TBL()             Symbol name for the key table
 *
 * Note, bit 0 in the second hash value (used for the CAM lookup) is
 * always set to distinguish a empty entry from an entry with a zero
 * hash value.
 */
#define CAMHT_MAX_KEY_SZ              (64)
#define CAMHT_MAX_KEY_SZ32            (CAMHT_MAX_KEY_SZ/4)
#define CAMHT_BUCKET_ENTRIES          (8)
#define CAMHT_ENTRY_SZ                (4)
#define CAMHT_BUCKET_MASK(_entries)   (((_entries) / CAMHT_BUCKET_ENTRIES) - 1)
#define CAMHT_BUCKET_IDX(_h, _entries) ((_h) & CAMHT_BUCKET_MASK(_entries))
#define CAMHT_BUCKET_HASH(_hash)      (((_hash) & 0x00ffffff) | 0x1)
#define CAMHT_BUCKET_HASH_of(_x)      ((_x) & 0x00ffffff)
#define CAMHT_BUCKET_OFF(_x)          ((_x) * CAMHT_BUCKET_ENTRIES * \
                                       CAMHT_ENTRY_SZ)
#define CAMHT_TBL_IDX(_bkt, _entry)   ((_bkt) * CAMHT_BUCKET_ENTRIES + (_entry))
#define CAMHT_IDX2OFF(_idx)           ((_idx) * CAMHT_ENTRY_SZ)
#define CAMHT_IDX2BUCKET(_idx)        ((_idx) / CAMHT_BUCKET_ENTRIES)
#define CAMHT_IDX2ENTRY(_idx)         ((_idx) % CAMHT_BUCKET_ENTRIES)

#define CAMHT_HASH_TBL(_name)         _name##_hash_tbl
#define CAMHT_KEY_TBL(_name)          _name##_key_tbl

#if defined(__STDC__)
/**
 * Structure of a hash bucket.
 * Can be used on the host
 */
struct camht_bucket {
    uint32_t entries[CAMHT_BUCKET_ENTRIES];
};
#endif

#endif /* _CAM_HASH_CTRL_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
