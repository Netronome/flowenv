/*
 * Copyright 2014-15 Netronome, Inc.
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
 * @file          lib/nfp/mem_cam.h
 * @brief         NFP memory CAM interface
 */
#ifndef _NFP__MEM_CAM_H_
#define _NFP__MEM_CAM_H_

#include <nfp.h>

/*
 * NOTE: The 'search.value' fields in the below structures are all
 * declared as full word values rather than bitfields even if the
 * whole word is not use to hold the value.  This is because the
 * 'search' fields are used for input data to the cam functions and
 * typically reside in write transfer registers.  By not using
 * bitfields in the structure definition we can ensure that assignment
 * to the 'search.value' field is not treated as a partial register
 * write (which is not possible or legal for write transfer
 * registers).
 */

/**
 * CAM search and result data for 8bit CAM lookups.
 */
struct mem_cam_8bit {
    union {
        struct {
            unsigned int value; /* Lower 8 bits valid */
            unsigned int __pad;
        } search;

        union {
            struct {
                unsigned int mask_lo;
                unsigned int mask_hi;
            };
            unsigned long long mask;
        } result;
    };
};

/**
 * CAM search and result data for 16bit CAM lookups.
 */
struct mem_cam_16bit {
    union {
        struct {
            unsigned int value; /* Lower 16 bits valid */
            unsigned int __pad;
        } search;

        struct {
            unsigned int __pad:24;
            unsigned int match:8;
            unsigned int mask;
        } result;
    };
};

/**
 * CAM search and result data for 24bit CAM lookups.
 */
struct mem_cam_24bit {
    union {
        struct {
            unsigned int value; /* Lower 24 bits valid */
        } search;

        struct {
            unsigned int mask:16;
            unsigned int data:8;
            unsigned int match:8;
        } result;
    };
};

/**
 * CAM search and result data for 32bit CAM lookups.
 */
struct mem_cam_32bit {
    union {
        struct {
            unsigned int value;
        } search;

        struct {
            unsigned int mask:16;
            unsigned int data:8;
            unsigned int match:8;
        } result;
    };
};

/**
 * Check if CAM lookup resulted in a hit
 * @param data          CAM result data
 *
 * Return true if there was a match.  Note that function is only valid
 * for 16bit, 24bit, and 32bit lookups.  For 8bit lookups the match
 * bitmask in the result must be consulted.
 */
#define mem_cam_lookup_hit(data) ((data).result.match != 0xff)

#define mem_cam_lookup8_hit(data) \
    (!(((data).result.mask_lo == 0) && ((data).result.mask_hi == 0)))

/**
 * Perform CAM lookup
 * @param data          search/result data
 * @param addr          CAM location
 * @param camsize       table size of CAM (128, 256, 384, or 512)
 * @param cambits       entry size of CAM (8, 16, 24, or 32)
 * @param sync          type of synchronization (must be sig_done)
 * @param sigpair       signal pair to report completion on
 *
 * Perform indicated CAM lookup.  The @camsize and @cambits parameters
 * must be constant literals.
 */
__intrinsic void __mem_cam_lookup(__xrw void *data, __mem void *addr,
                                  int camsize, int cambits,
                                  sync_t sync, SIGNAL_PAIR *sigpair);

/**
 * Perform synchronous CAM lookup
 * @param data          search/result data
 * @param addr          CAM location
 * @param camsize       table size of CAM (128, 256, 384, or 512)
 * @param cambits       entry size of CAM (8, 16, 24, or 32)
 *
 * Perform indicated CAM lookup.  Return when operation completes.
 */
__intrinsic void mem_cam_lookup(__xrw void *data, __mem void *addr,
                                int camsize, int cambits);



/*
 * Convenience wrappers around the above generic CAM functions.  These
 * wrappers also ensure that the appropriate search and result data
 * parameters are used.
 */

__intrinsic void __mem_cam128_lookup8(__xrw struct mem_cam_8bit *data,
                                      __mem __align16 void *addr,
                                      sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam128_lookup8(__xrw struct mem_cam_8bit *data,
                                    __mem __align32 void *addr);

__intrinsic void __mem_cam128_lookup16(__xrw struct mem_cam_16bit *data,
                                       __mem __align16 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam128_lookup16(__xrw struct mem_cam_16bit *data,
                                     __mem __align16 void *addr);

__intrinsic void __mem_cam128_lookup24(__xrw struct mem_cam_24bit *data,
                                       __mem __align16 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam128_lookup24(__xrw struct mem_cam_24bit *data,
                                     __mem __align16 void *addr);

__intrinsic void __mem_cam128_lookup32(__xrw struct mem_cam_32bit *data,
                                       __mem __align16 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam128_lookup32(__xrw struct mem_cam_32bit *data,
                                     __mem __align16 void *addr);

__intrinsic void __mem_cam256_lookup8(__xrw struct mem_cam_8bit *data,
                                      __mem __align32 void *addr,
                                      sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam256_lookup8(__xrw struct mem_cam_8bit *data,
                                    __mem __align32 void *addr);

__intrinsic void __mem_cam256_lookup16(__xrw struct mem_cam_16bit *data,
                                       __mem __align32 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam256_lookup16(__xrw struct mem_cam_16bit *data,
                                     __mem __align32 void *addr);

__intrinsic void __mem_cam256_lookup24(__xrw struct mem_cam_24bit *data,
                                       __mem __align32 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam256_lookup24(__xrw struct mem_cam_24bit *data,
                                     __mem __align32 void *addr);

__intrinsic void __mem_cam256_lookup32(__xrw struct mem_cam_32bit *data,
                                       __mem __align32 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam256_lookup32(__xrw struct mem_cam_32bit *data,
                                     __mem __align32 void *addr);

__intrinsic void __mem_cam384_lookup8(__xrw struct mem_cam_8bit *data,
                                      __mem __align64 void *addr,
                                      sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam384_lookup8(__xrw struct mem_cam_8bit *data,
                                    __mem __align64 void *addr);

__intrinsic void __mem_cam384_lookup16(__xrw struct mem_cam_16bit *data,
                                       __mem __align64 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam384_lookup16(__xrw struct mem_cam_16bit *data,
                                     __mem __align64 void *addr);

__intrinsic void __mem_cam384_lookup24(__xrw struct mem_cam_24bit *data,
                                       __mem __align64 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam384_lookup24(__xrw struct mem_cam_24bit *data,
                                     __mem __align64 void *addr);

__intrinsic void __mem_cam384_lookup32(__xrw struct mem_cam_32bit *data,
                                       __mem __align64 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam384_lookup32(__xrw struct mem_cam_32bit *data,
                                     __mem __align64 void *addr);

__intrinsic void __mem_cam512_lookup8(__xrw struct mem_cam_8bit *data,
                                      __mem __align64 void *addr,
                                      sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam512_lookup8(__xrw struct mem_cam_8bit *data,
                                    __mem __align64 void *addr);

__intrinsic void __mem_cam512_lookup16(__xrw struct mem_cam_16bit *data,
                                       __mem __align64 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam512_lookup16(__xrw struct mem_cam_16bit *data,
                                     __mem __align64 void *addr);

__intrinsic void __mem_cam512_lookup24(__xrw struct mem_cam_24bit *data,
                                       __mem __align64 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam512_lookup24(__xrw struct mem_cam_24bit *data,
                                     __mem __align64 void *addr);

__intrinsic void __mem_cam512_lookup32(__xrw struct mem_cam_32bit *data,
                                       __mem __align64 void *addr,
                                       sync_t sync, SIGNAL_PAIR *sigpair);

__intrinsic void mem_cam512_lookup32(__xrw struct mem_cam_32bit *data,
                                     __mem __align64 void *addr);

#endif /* !_NFP__MEM_CAM_H_ */
