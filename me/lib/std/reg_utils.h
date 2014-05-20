/*
 * Copyright (C) 2014 Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/std/reg_utils.h
 * @brief         Functions to treat structures in registers as memory.
 *
 * The C compiler is quite picky/unhelpful when it comes to storing
 * data structures in registers or local memory.  This module provide
 * generic implementations of some useful functions to handle such
 * data structures.
 *
 * Note, these functions essentially manually unroll loops depending
 * on the size_t parameter.  For good performance and small code size
 * it is important that the size parameter is a compile time constant.
 */

#ifndef _STD__REG_UTILS_H_
#define _STD__REG_UTILS_H_

#include <nfp.h>
#include <types.h>


/**
 * Zero a region located in registers.
 *
 * @param s     Pointer to the region
 * @param n     Size of region (in bytes)
 *
 * @s can be located in any type of register (GPR, NN, XFER) or LMEM.
 * @n must be a compile time constant and multiple of 4.
 */
__intrinsic void reg_zero(void *s, size_t n);


/**
 * Copy a region located in registers to another region or memory
 *
 * @param d     Destination
 * @param s     Source
 * @param n     Size of region (in bytes)
 *
 * @d can be located in any type of register (GPR, NN, XFER) or LMEM.
 * @s can be located in any type of register (GPR, NN, XFER) or LMEM.
 * @n must be a compile time constant and multiple of 4.
 */
__intrinsic void reg_cp(void *d, void *s, size_t n);


/**
 * Compare to memory regions located in registers for equality
 *
 * @param s1    Pointer to a region
 * @param s2    Pointer to a region
 * @param n     Size of region (in bytes)
 * @return      1 if the regions are equal, 0 otherwise
 *
 * @s1 and @s2 can be located in any type of register (GPR, NN, XFER) or LMEM.
 * @n must be a compile time constant and multiple of 4.
 */
__intrinsic int reg_eq(void *s1, void *s2, size_t n);

#endif /* !_STD__REG_UTILS_H_ */

/* -*-  Mode:C; c-basic-offset:4; tab-width:4 -*- */
