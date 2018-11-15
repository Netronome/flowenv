/*
 * Copyright (C) 2017-2018,  Netronome Systems, Inc.  All rights reserved.
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
 * @file          unit_tests/utfe_mem_bulk.c
 * @brief         This file describes NTI compatible tests for mem_bulk enine.
 */


#include <nfp.h>
#include <assert.h>
#include <nfp/me.h>
#include <nfp/mem_bulk.h>
#include <pkt/pkt.h>


/*
<yaml>
tests:
# common defines used for all tests, unless overwritten within the test itself
  - name: defaults
# Assembler or compiler flags
    flags:
        - -chip nfp-6xxx
        - -Qrevision_min=0
        - <-O1, -O2, -Od> -ng
#        - <-O1, -O2, -Od>
        - -Ob1 -W3
        - -Qbigendian -Qnctx=8 -Qspill=1 -Qnctx_mode=8 -Qnn_mode=0 -Qlm_start=0
        - -Zi
# Assembler or compiler includes
    inc:
        - $TOOLCHAIN_INC_DIR/standardlibrary/microc/include
        - $TOOLCHAIN_INC_DIR/flowenv-ng.hg/me/include/
        - $TOOLCHAIN_INC_DIR/flowenv-ng.hg/me/lib/
# Additional files used when compiling microc
    cfiles:
        - $TOOLCHAIN_INC_DIR/standardlibrary/microc/src/rtl.c
        - $TOOLCHAIN_INC_DIR/flowenv-ng.hg/me/lib/nfp/_c/mem_bulk.c
        - $TOOLCHAIN_INC_DIR/flowenv-ng.hg/me/lib/nfp/_c/me.c
        - $TOOLCHAIN_INC_DIR/flowenv-ng.hg/me/lib/nfp/libnfp.c
# Linker flags
    nfld_flags:
        - -chip nfp-6xxx
        - -g
# Linker assignment of list file to ME
    nfld_list:
        - i32.me4:$FNAME.list
# Linker name of nffw (elf) file to generate
    nfld_elf: -elf64 $FNAME.nffw
# Simulation options
    sim:
        - meids:
            - mei0.me4:-1
# Total number of steps to run the simulator
          run: 2000
# The step interval when running the simulator
          stepsize: 20
# The expected result of running a test
    expected_result: True
</yaml>
*/



/* prototypes */

int32_t utfe_mem_bulk_write_read_64(void);
int32_t utfe_mem_bulk_write_read_32(void);

#ifdef ALL_TEST
    #define UTFE_MEM_BULK_WRITE_READ_64
    #define UTFE_MEM_BULK_WRITE_READ_32
#endif



/* globals */
#define MAX_SIZE    16

__xread uint32_t global_read_reg[MAX_SIZE];
__xwrite uint32_t global_write_reg[MAX_SIZE];

uint32_t test_value = 0x33221100;


/* main test loop */
void main(void)
{
    uint32_t tests_passed = 0;
    uint32_t tests_failed = 0;
    uint32_t i = 0;

    // only one context
    if ( ctx() != 0)
    {
        return;
    }

    // setup write registers
    for (i = 0; i < MAX_SIZE; i++)
    {
        global_write_reg[i] = test_value + i;
    }

    // write non-zero value to mailbox0, this to detect if a function does not return
    // if a function is aborted then all 4 mailboxes have value 0 (specific for non-nti test)
    local_csr_write(local_csr_mailbox0, 2);     // ERROR
    local_csr_write(local_csr_mailbox1, 0);
    local_csr_write(local_csr_mailbox2, 0);
    local_csr_write(local_csr_mailbox3, 0);

#ifdef UTFE_MEM_BULK_WRITE_READ_64
    if (utfe_mem_bulk_write_read_64() == 0) {
        tests_passed++;
    }  else {
        tests_failed++;
    }
#endif

#ifdef UTFE_MEM_BULK_WRITE_READ_32
    if (utfe_mem_bulk_write_read_32() == 0) {
        tests_passed++;
    }  else {
        tests_failed++;
    }
#endif

    /* Use the mailboxes to indicate results from running the test
    * Mailbox0 = 0 for a Pass, else indicates a error condition
    */
    if (tests_failed == 0)
    {
        local_csr_write(local_csr_mailbox0, 0);     // OK
    } else {
        local_csr_write(local_csr_mailbox0, 1);     // ERROR
    }

#ifdef ALL_TEST
    local_csr_write(local_csr_mailbox2, tests_passed);                  // number of test passed
    local_csr_write(local_csr_mailbox3, tests_failed + tests_passed);   // number of test excuted
#endif

    for (;;)
        ;


// #ifndef ALL_TEST
//     for (i = 0; i < 10; i++)
//     {
//         __asm nop;
//     }
//
//     /* Force a breakpoint at the end of the test */
//     __asm ctx_arb[bpt]
// #endif
}



/*
<yaml>
  - name: utfe_mem_bulk_write_read_64
    info: Test utfe_mem_bulk_write_read64_ctx_swap
    summary: test mem rd wr 64
    defs:
        - UTFE_MEM_BULK_WRITE_READ_64
</yaml>
*/
int32_t utfe_mem_bulk_write_read_64(void)
{
    __addr40 uint8_t   *paddr = (__addr40 uint8_t*)0x100;

    mem_write64((void*)global_write_reg, paddr, sizeof(global_write_reg));
    mem_read64((void*)global_read_reg, paddr, sizeof(global_read_reg));

    // Verify that first word
    if (global_read_reg[MAX_SIZE - 1] != test_value + MAX_SIZE - 1)
    {
        // FAIL
        local_csr_write(local_csr_mailbox1, __LINE__);                      // line nr
        local_csr_write(local_csr_mailbox2, (test_value + MAX_SIZE - 1));   // expected
        local_csr_write(local_csr_mailbox3, global_read_reg[MAX_SIZE - 1]); // actual
        return 1;
    }

    // PASS
    return 0;
}


/*
<yaml>
  - name: utfe_mem_bulk_write_read_32
    info: Test
    summary: test
    defs:
        - UTFE_MEM_BULK_WRITE_READ_32
</yaml>
*/
int32_t utfe_mem_bulk_write_read_32(void)
{
    __gpr uint32_t test_val = 0x1234abc0;   // some random test value
    __addr40 void *pbuf;
    __xwrite uint32_t xcmd = test_val;
    __xread uint32_t result;
    SIGNAL sig;
    uint32_t off = 0;

    // 0: ctm on this island, 1: addr 0x0001_0000, 4: addr offset
    pbuf = pkt_ctm_ptr40(0, 1, 4);
    mem_write32(&xcmd, (__addr40 uint8_t *)pbuf + off, sizeof(xcmd));
    mem_read32(&result, (__addr40 uint8_t *)pbuf + off, sizeof(result));

    // nfp-mem -v -l32 i32.ctm:0x00010000'
    // 0x0000010000:  0x00000000 0x1234abc0 0x00000000 0x00000000
    // 0x0000010010:  0x00000000 0x00000000 0x00000000 0x00000000

    // Verify
    if (result != test_val)
    {
        // FAIL
        local_csr_write(local_csr_mailbox1, __LINE__);      // line nr
        local_csr_write(local_csr_mailbox2, test_val);      // expected
        local_csr_write(local_csr_mailbox3, result);        // actual
        return 1;
    }

    // PASS
    return 0;
}



