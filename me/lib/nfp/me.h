/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/me.h
 * @brief         Interface for common ME related functions and types
 */
#ifndef _NFP__ME_H_
#define _NFP__ME_H_

#include <nfp.h>

#if defined(__NFP_LANG_MICROC)

/**
 * Wait for signal.
 * @param sig           signal
 *
 * Swap out the current context and wait for the specified signal
 * (bpt, voluntary, kill).  Please use the __wait_for_all(),
 * __wait_for_any(), or signal_test() functions to wait for user
 * signal variables.
 */
__intrinsic void ctx_wait(signal_t sig);

/**
 * Yield execution to another thread.
 */
#define ctx_swap() ctx_wait(voluntary)

/**
 * Halt all contexts on the microengine.
 */
__intrinsic void halt(void);

/**
 * Sleep for a number of cycles.
 * @param cycles        approx number of cycles to sleep
 */
__intrinsic void sleep(unsigned int cycles);

/**
 * Test the bit_pos in data word and return a 1 if set or 0 if clear.
 * @param data      Data word to test
 * @param bit_pos   Bit position in data to test
 *
 * This method explicitly uses the br_bset instruction.  The compiler will
 * try to use br_bset and br_bclr for regular C tests where possible.
 */
__intrinsic int bit_test(unsigned int data, unsigned int bit_pos);

/*
 * Input state names.
 */
enum inp_state_e {
    inp_state_nn_empty          = 0x0,
    inp_state_nn_full           = 0x1,
    inp_state_scr_ring0_status  = 0x2,
    inp_state_scr_ring1_status  = 0x3,
    inp_state_scr_ring2_status  = 0x4,
    inp_state_scr_ring3_status  = 0x5,
    inp_state_scr_ring4_status  = 0x6,
    inp_state_scr_ring5_status  = 0x7,
    inp_state_scr_ring6_status  = 0x8,
    inp_state_scr_ring7_status  = 0x9,
    inp_state_scr_ring8_status  = 0xA,
    inp_state_scr_ring9_status  = 0xB,
    inp_state_scr_ring10_status = 0xC,
    inp_state_scr_ring11_status = 0xD,
    inp_state_scr_ring0_full    = inp_state_scr_ring0_status,
    inp_state_scr_ring1_full    = inp_state_scr_ring1_status,
    inp_state_scr_ring2_full    = inp_state_scr_ring2_status,
    inp_state_scr_ring3_full    = inp_state_scr_ring3_status,
    inp_state_scr_ring4_full    = inp_state_scr_ring4_status,
    inp_state_scr_ring5_full    = inp_state_scr_ring5_status,
    inp_state_scr_ring6_full    = inp_state_scr_ring6_status,
    inp_state_scr_ring7_full    = inp_state_scr_ring7_status,
    inp_state_scr_ring8_full    = inp_state_scr_ring8_status,
    inp_state_scr_ring9_full    = inp_state_scr_ring9_status,
    inp_state_scr_ring10_full   = inp_state_scr_ring10_status,
    inp_state_scr_ring11_full   = inp_state_scr_ring11_status,
    inp_state_fci_not_empty     = 0xE,
    inp_state_fci_full          = 0xF,
    inp_state_fcififo_empty     = 0xE,
    inp_state_fcififo_full      = 0xF
};

/**
 * Tests the value of the specified input state name.
 * @param statename     state to test
 *
 * Test the value of the specified state name and return 1 if the
 * state is set or 0 if clear.  The argument state must be a constant
 * literal as required by the microcode assembler.
 */
__intrinsic int inp_state_test(int statename);

/**
 * Get the current microengine number.
 */
__intrinsic unsigned int __ME(void);

/**
 * Read local ME CSR
 * @param mecsr         CSR number
 */
__intrinsic unsigned int local_csr_read(int mecsr);

/**
 * Write local ME CSR
 * @param mecsr         CSR number
 * @param data          data to write
 */
__intrinsic void local_csr_write(int mecsr, unsigned int data);


#endif /* __NFP_LANG_MICROC */

#endif /* !_NFP__NFP_ME_H_ */
