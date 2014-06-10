/**
 * Copyright (C) 2013-2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file        sim_imb_setup.c
 * @brief       Basic IMB setup of the sim.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include "ns_log.h"

#include "nfp.h"
#include "nfp_cpp.h"
#include "nfp_sal.h"

/* address defines */

#define IMBVAL(m, am, i1, i0) ((((i0) & 0x3f) <<  0) | \
                               (((i1) & 0x3f) <<  6) | \
                               (((am) & 0x1)  << 12) | \
                               (((m)  & 0x7)  << 13))

/* addresses for all the imbs */

/* To generate the table below, follow this with some print statements.
topmap_xpb = HarrierXpbMap(name = 'HarrierXpbMap', access = 'XPB')
iidmap = dict((key, None) for key in range(0, 64)) # py2.6 friendly
for topm in topmap_xpb:
    iid = (topm.offset >> 24) & 0x3F
    if not hasattr(topm, 'IMBXpbMap'):
        iidmap[iid] = 0
        continue
    m = topm.IMBXpbMap
    iidmap[iid] = m
*/
uint32_t iid2imb_base[64] = {
    0xFFFFffff, /*  0: No Island */
    0x010a0000, /*  1: HarrierXpbMap.ArmIsldXpbMap.IMBXpbMap */
    0xFFFFffff, /*  2: No Island */
    0xFFFFffff, /*  3: No Island */
    0x040a0000, /*  4: HarrierXpbMap.Pcie0IsldXpbMap.IMBXpbMap */
    0x050a0000, /*  5: HarrierXpbMap.Pcie1IsldXpbMap.IMBXpbMap */
    0x060a0000, /*  6: HarrierXpbMap.Pcie2IsldXpbMap.IMBXpbMap */
    0x070a0000, /*  7: HarrierXpbMap.Pcie3IsldXpbMap.IMBXpbMap */
    0xFFFFfffe, /*  8: No IMB */
    0xFFFFfffe, /*  9: No IMB */
    0xFFFFffff, /* 10: No Island */
    0xFFFFffff, /* 11: No Island */
    0x0c0a0000, /* 12: HarrierXpbMap.Crypto0IsldXpbMap.IMBXpbMap */
    0x0d0a0000, /* 13: HarrierXpbMap.Crypto1IsldXpbMap.IMBXpbMap */
    0xFFFFffff, /* 14: No Island */
    0xFFFFffff, /* 15: No Island */
    0xFFFFffff, /* 16: No Island */
    0xFFFFffff, /* 17: No Island */
    0xFFFFffff, /* 18: No Island */
    0xFFFFffff, /* 19: No Island */
    0xFFFFffff, /* 20: No Island */
    0xFFFFffff, /* 21: No Island */
    0xFFFFffff, /* 22: No Island */
    0xFFFFffff, /* 23: No Island */
    0xFFFFfffe, /* 24: No IMB */
    0xFFFFfffe, /* 25: No IMB */
    0xFFFFfffe, /* 26: No IMB */
    0xFFFFffff, /* 27: No Island */
    0xFFFFfffe, /* 28: No IMB */
    0xFFFFfffe, /* 29: No IMB */
    0xFFFFffff, /* 30: No Island */
    0xFFFFffff, /* 31: No Island */
    0x200a0000, /* 32: HarrierXpbMap.Me0IsldXpbMap.IMBXpbMap */
    0x210a0000, /* 33: HarrierXpbMap.Me1IsldXpbMap.IMBXpbMap */
    0x220a0000, /* 34: HarrierXpbMap.Me2IsldXpbMap.IMBXpbMap */
    0x230a0000, /* 35: HarrierXpbMap.Me3IsldXpbMap.IMBXpbMap */
    0x240a0000, /* 36: HarrierXpbMap.Me4IsldXpbMap.IMBXpbMap */
    0x250a0000, /* 37: HarrierXpbMap.Me5IsldXpbMap.IMBXpbMap */
    0x260a0000, /* 38: HarrierXpbMap.Me6IsldXpbMap.IMBXpbMap */
    0xFFFFffff, /* 39: No Island */
    0xFFFFffff, /* 40: No Island */
    0xFFFFffff, /* 41: No Island */
    0xFFFFffff, /* 42: No Island */
    0xFFFFffff, /* 43: No Island */
    0xFFFFffff, /* 44: No Island */
    0xFFFFffff, /* 45: No Island */
    0xFFFFffff, /* 46: No Island */
    0xFFFFffff, /* 47: No Island */
    0x300a0000, /* 48: HarrierXpbMap.Ila0IsldXpbMap.IMBXpbMap */
    0x310a0000, /* 49: HarrierXpbMap.Ila1IsldXpbMap.IMBXpbMap */
    0xFFFFffff, /* 50: No Island */
    0xFFFFffff, /* 51: No Island */
    0xFFFFffff, /* 52: No Island */
    0xFFFFffff, /* 53: No Island */
    0xFFFFffff, /* 54: No Island */
    0xFFFFffff, /* 55: No Island */
    0xFFFFffff, /* 56: No Island */
    0xFFFFffff, /* 57: No Island */
    0xFFFFffff, /* 58: No Island */
    0xFFFFffff, /* 59: No Island */
    0xFFFFffff, /* 60: No Island */
    0xFFFFffff, /* 61: No Island */
    0xFFFFffff, /* 62: No Island */
    0xFFFFffff /* 63: No Island */
};

/* [iid][cpptgt]  https://wiki-us.netronome.com/confluence/display/SW/Harrier+BSP+CPP+Addressing+Modes  */
uint32_t imbcatt_bsp_201304[64][16] = {
/* i0  - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    { /* i1  - ArmIsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    /* i2  - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i3  - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    { /* i4  - Pcie0IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i5  - Pcie1IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i6  - Pcie2IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i7  - Pcie3IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    /* i8  - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i9  - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i10 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i11 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    { /* i12 - Crypto0IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i13 - Crypto1IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    /* i14 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i15 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i16 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i17 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i18 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i19 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i20 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i21 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i22 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i23 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i24 - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i25 - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i26 - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i27 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i28 - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i29 - No IMB */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i30 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i31 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    { /* i32 - Me0IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i33 - Me1IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i34 - Me2IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i35 - Me3IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i36 - Me4IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i37 - Me5IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i38 - Me6IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    /* i39 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i40 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i41 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i42 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i43 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i44 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i45 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i46 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i47 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    { /* i48 - Ila0IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    { /* i49 - Ila1IsldXpbMap */
        /* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
        /* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
        /* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
        /* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
        /* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
        /* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
        /* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
        /* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
        /* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
        /* CPP Tgt 15 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */
    },
    /* i50 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i51 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i52 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i53 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i54 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i55 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i56 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i57 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i58 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i59 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i60 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i61 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i62 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
    /* i63 - No Island */
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}
};


uint32_t imbcatt_bsp_20130527[64][16] = {
/* i0  - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i1  - ArmIsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i2  - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i3  - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i4  - Pcie0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i5  - Pcie1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i6  - Pcie2IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i7  - Pcie3IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i8  - No IMB */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i9  - No IMB */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i10 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i11 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i12 - Crypto0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i13 - Crypto1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i14 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i15 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i16 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i17 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i18 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i19 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i20 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i21 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i22 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i23 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i24 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i25 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i26 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i27 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i28 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i29 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i30 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i31 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i32 - Me0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i33 - Me1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i34 - Me2IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i35 - Me3IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i36 - Me4IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i37 - Me5IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i38 - Me6IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i39 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i40 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i41 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i42 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i43 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i44 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i45 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i46 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i47 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i48 - Ila0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i49 - Ila1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 28, 24) /* 0x7718 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  2,  1) /* 0x2081 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i50 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i51 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i52 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i53 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i54 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i55 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i56 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i57 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i58 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i59 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i60 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i61 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i62 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i63 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}
};

uint32_t imbcatt_bsp_20130703[64][16] = {
/* i0  - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i1  - ArmIsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i2  - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i3  - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i4  - Pcie0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i5  - Pcie1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i6  - Pcie2IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i7  - Pcie3IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i8  - No IMB */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i9  - No IMB */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i10 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i11 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i12 - Crypto0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i13 - Crypto1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i14 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i15 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i16 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i17 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i18 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i19 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i20 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i21 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i22 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i23 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i24 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i25 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i26 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i27 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i28 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i29 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i30 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i31 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i32 - Me0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i33 - Me1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i34 - Me2IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i35 - Me3IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i36 - Me4IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i37 - Me5IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i38 - Me6IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i39 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i40 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i41 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i42 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i43 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i44 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i45 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i46 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i47 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{ /* i48 - Ila0IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
{ /* i49 - Ila1IsldXpbMap */
/* CPP Tgt  0 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  1 */ IMBVAL(2, 1, 10,  8) /* 0x5288 */,
/* CPP Tgt  2 */ IMBVAL(1, 0, 24, 24) /* 0x2618 */,
/* CPP Tgt  3 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  4 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  5 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  6 */ IMBVAL(2, 1, 50, 48) /* 0x5cb0 */,
/* CPP Tgt  7 */ IMBVAL(3, 1, 24,  0) /* 0x7600 */,
/* CPP Tgt  8 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt  9 */ IMBVAL(2, 1,  6,  4) /* 0x5184 */,
/* CPP Tgt 10 */ IMBVAL(1, 0,  1,  1) /* 0x2041 */,
/* CPP Tgt 11 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 12 */ IMBVAL(2, 0, 12,  0) /* 0x4300 */,
/* CPP Tgt 13 */ IMBVAL(0, 0,  0,  0) /* 0x0000 */,
/* CPP Tgt 14 */ IMBVAL(1, 0,  1,  0) /* 0x2040 */,
/* CPP Tgt 15 */ IMBVAL(0, 1,  0,  0) /* 0x1000 */
},
/* i50 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i51 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i52 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i53 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i54 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i55 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i56 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i57 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i58 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i59 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i60 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i61 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i62 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
/* i63 - No Island */
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}
};

void xpb_writel(struct nfp_cpp *h, uint32_t a, uint32_t d)
{
    int ret;
    ret = nfp_xpb_writel(h, a, d);
    printf(">%08x=%08x\n", a, d);
    if (ret < 0) {
        fprintf(stderr, "error with xpb write to address %x : %s\n",
                            a, strerror(errno));
    }
}


void setup_imb(struct nfp_cpp *nfp_cpp, uint32_t catts[64][16])
{
    int iid;
    int cppid;
    uint32_t csr_offset;

    for (iid = 0; iid < 64; iid++)
    {
        csr_offset = iid2imb_base[iid];
        if (csr_offset >= 0xFFFFfffe)
            continue;
        for (cppid = 0; cppid < 16; cppid++)
        {
            xpb_writel(nfp_cpp, csr_offset + (4*cppid), catts[iid][cppid]);
        }
    }
}


/*
 * Argument Parsing
 */
#define ARG_DEFAULT_DEVICE  0

struct arg_data {
    int device;
};

static void usage(char *progname)
{
    fprintf(stderr,
            "usage: %s [options]\n"
            "\nWhere options are:\n"
            "        -d <device>            -- select NFP device, default 0\n"
            "        -h                     -- print help\n",
            progname);
}

static int uintarg(const char *s, uint64_t *val)
{
    char *cp;
    uint64_t r;
    r = strtoull(s, &cp, 0);
    if (cp == s) {
        fprintf(stderr, "Invalid integer value: %s\n", s);
        return -1;
    }
    *val = r;
    return 0;
}

static void parse_options(struct arg_data* args, int argc, char *argv[])
{
    int o;
    uint64_t val;

    args->device = ARG_DEFAULT_DEVICE;

    while ((o = getopt(argc, argv, "d:n:h")) != -1) {
        switch(o) {
        case 'h':
            usage(argv[0]);
            exit(0);
            break;
        case 'd':
            if (uintarg(optarg, &val)) {
                usage(argv[0]);
                exit(1);
            }
            args->device = val;
            break;
        default:
            usage(argv[0]);
            exit(1);
            break;
        }
    }


}

int main(int argc, char **argv)
{
    struct nfp_device *nfp;
    struct nfp_cpp *nfp_cpp;
    struct arg_data args;

    NS_LOG_SET_LEVEL(NS_LOG_LVL_INFO);

    parse_options(&args, argc, argv);

    printf("opening nfp_device\n");
    nfp = nfp_device_open(args.device);
    if (!nfp) {
        fprintf(stderr, "error: nfp_device_open failed\n");
        return -1;
    }

    printf("opening nfp_cpp\n");
    nfp_cpp = nfp_cpp_from_device_id(args.device);
    if (!nfp_cpp) {
        fprintf(stderr, "error: nfp_cpp_from_device_id failed\n");
        return -1;
    }

    setup_imb(nfp_cpp, imbcatt_bsp_20130703);

    return 0;
}
