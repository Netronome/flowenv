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
 * @file          lib/lu/cam_hash.h
 * @brief         Interface for a CAM assisted hash table
 */

#ifndef _LU__CAM_HASH_H_
#define _LU__CAM_HASH_H_

#include <nfp.h>
#include <stdint.h>
#include <types.h>

/**
 * This module provides an implementation for a CAM assisted hash
 * table.  It provides a very efficient lookup mechanism suitable for
 * large data structures such as a flow tables.  A single memory
 * operation can determine either a potential match or no match.  A
 * subsequent memory access is required to determine if a potential
 * match is a real match.
 *
 * The hash table is fixed in size with @_nb_entries and consists of
 * two tables/arrays: One table containing hash values (organised in
 * fixed buckets of size @CAMHT_BUCKET_ENTRIES) and a table containing
 * the keys.  Two hash functions are used for a key lookup: The first
 * hash provides a (suitably masked) index for a bucket and the second
 * hash is used in a CAM lookup within the bucket.  This structure
 * supports up to @CAMHT_BUCKET_ENTRIES collisions on the first hash
 * but does not allow for collisions on the second hash with in the
 * bucket (though support for this could be added).
 *
 * The combination of bucket index and the index of the matching entry
 * in the bucket (returned by the CAM lookup) provides the index into
 * the key table (and possibly other associated tables).
 *
 * The key table is organised in entries of type @_entry_type.  The
 * entry type must be at least the size of the key but may be larger,
 * for example, to align the keys to a cache line or to store
 * additional information along with the key.
 */


/* The current implementation only represents the minimum set of
 * features which are currently needed.  It can easily be extended in
 * a number of ways:
 *
 * - Add more API functions, e.g. for adding entries or for providing
 *   asynchronous access functions.
 *
 * - Provide more configuration options.  One can use a single 32bit
 *   compile time constant for flags indicating things like: 24/32bit
 *   CAM lookup, size of the bucket/CAM lookup, type of hash functions
 *   to use etc. Being a compile time constant the C compiler will be
 *   able to generate efficient code.  The config word should also be
 *   stored in EMEM for the host to be able to determine the
 *   configuration of a particular hash table.
 *
 * - Add support for accessing the top 8bits when 24bit CAM lookups
 *   are used. These can be used as flags associated with an entry and
 *   may provide some optimisation opportunities.
 *
 * - Add support for CLS based hash tables.
 */

/* Include definitions shared with the host */
#include "cam_hash_ctrl.h"


#define CAMHT_NB_ENTRIES(_name) _name##_nb_entries
#define CAMHT_ENTRY_SZ(_name) _name##_entry_sz

/**
 * Declare/Define a new hash table
 * @param _name        Global name for the hash table
 * @param _nb_entries  Total number of entries in the hash table
 * @param _entry_type  The type for each entry
 *
 * Note the _entry_type may be different to the type of the key.
 */
#define CAMHT_DECLARE(_name, _nb_entries, _entry_type)              \
    __export __emem uint32_t CAMHT_HASH_TBL(_name)[_nb_entries];    \
    __export __emem _entry_type CAMHT_KEY_TBL(_name)[_nb_entries];  \
    static const int32_t CAMHT_NB_ENTRIES(_name) = _nb_entries;     \
    static const int32_t CAMHT_ENTRY_SZ(_name) = sizeof(_entry_type);

/**
 * Look up a key in a hash table
 * @param _name        Hash table name
 * @param _key         A pointer to the key structure
 * @param _idx         Return hash table entry index or -1 if not found.
 *
 * This macro is a wrapper around @camht_lookup().  See its
 * description for details.
 */
#define CAMHT_LOOKUP(_name, _key)                                       \
    camht_lookup(CAMHT_HASH_TBL(_name), CAMHT_KEY_TBL(_name),           \
                 CAMHT_NB_ENTRIES(_name), CAMHT_ENTRY_SZ(_name),        \
                 _key, sizeof(*_key))

/**
 * Lookup a key in the hash table
 * @param hash_tbl     Address of the hash table
 * @param key_tbl      Address of the key table
 * @param entries      Total number of entries in the hash table
 * @param key          Pointer to the key to lookup
 * @param key_sz       Size of the key
 * @param entry_sz     Size of an entry in the key table
 * @return             Hash table entry index or -1 if not found.
 *
 * This function performs the full hash table lookup synchronously.
 * It will compute the hash values, perform a lookup in the hash table
 * and compare any matching keys.
 */
__intrinsic int32_t camht_lookup(__mem void *hash_tbl, __mem void *key_tbl,
                                 int32_t entries, size_t entry_sz,
                                 void *key, size_t key_sz);


/**
 * Look up a key in a hash table
 * @param _name        Hash table name
 * @param _key         A pointer to the key structure
 * @param _idx         Return hash table entry index or -1 if not found.
 *
 * This macro is a wrapper around @camht_lookup_idx().  See its
 * description for details.
 */
#define CAMHT_LOOKUP_IDX(_name, _key)                                   \
    camht_lookup_idx(CAMHT_HASH_TBL(_name), CAMHT_NB_ENTRIES(_name),    \
                     (void *)_key, sizeof(*_key))

/**
 * Lookup a key in the hash table
 * @param hash_tbl     Address of the hash table
 * @param entries      Total number of entries in the hash table
 * @param key          Pointer to the key to lookup
 * @param key_sz       Size of the key
 * @return             A index if a match was found. -1 on error.
 *
 * This function performs the partial hash table lookup.  It computes
 * hash values and perform a lookup in the hash table.  It will *not*
 * compare the key.  Use this function if a hash table entry contains
 * additional information apart from the hash key itself.
 */
__intrinsic int32_t camht_lookup_idx(__mem void *hash_tbl, int32_t entries,
                                     void *key, size_t key_sz);

#endif /* _LU__CAM_HASH_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */