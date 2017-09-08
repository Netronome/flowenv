
/** @file test_nfp_mem_readwrite8.c
* Copyright (C) 2008-2013 Netronome Systems, Inc.  All rights reserved.
*/

#include <nfp.h>
#include <nfp/me.h>
#include <assert.h>

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

#ifdef PS // Programmer studio
    #define UTFE_MEM_BULK_WRITE_READ_64
    #define UTFE_MEM_BULK_WRITE_READ_32
#endif



/* globals */

__xread uint32_t global_read_reg[16];
__xwrite uint32_t global_write_reg[16];

uint32_t test_value = 0x33221100;
uint32_t alternate_test_value = 0x12345600;

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
    for (i = 0; i <= 15; i++)
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

#ifdef PS
    local_csr_write(local_csr_mailbox2, tests_passed);                  // number of test passed
    local_csr_write(local_csr_mailbox3, tests_failed + tests_passed);   // number of test excuted
#endif

#ifndef PS
    for (i = 0; i < 10; i++)
    {
        __asm nop;
    }

    /* Force a breakpoint at the end of the test */
    __asm ctx_arb[bpt]
#endif
}


/*
 * This operation is supplied as a function and not a macro because
 * experience with the 'nfcc' compiler has shown that a simple,
 * single expression will not compile correctly and that the type
 * casting for the intermediate values must be done carefully.
 *
 * A 40-bit packet-address mode pointer in CTM is built as follows:
 *
 *  Bits[2;38] -- Must be 0b10 for "direct access"
 *  Bits[6;32] -- The island of the CTM. (can use '0' for the local island)
 *  Bits[1;31] -- Must be set to 1 to enable packet-addressing mode
 *  Bits[6;25] -- reserved
 *  Bits[9;16] -- The packet number of the CTM buffer
 *  Bits[2;14] -- reserved
 *  Bits[14;0] -- The offset within the CTM buffer
 *
 * Unfortunately, this is only partly documented in the NFP DB.
 */
__intrinsic __addr40 void *pkt_ctm_ptr40(uint32_t isl, unsigned int pnum, unsigned int off)
{
    __gpr unsigned int lo;
    __gpr unsigned int hi;

    hi = 0x80 | isl;
    lo = 0x80000000u | (pnum << 16) | off;

    return (__addr40 void *)(((unsigned long long)hi << 32) | (unsigned long long)lo);
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
    uint32_t            count = 32;

    mem_write64((void*)global_write_reg, paddr, count);
    mem_read64((void*)global_read_reg, paddr, count);

    // Verify that first word
    if (global_read_reg[0] != test_value)
    {
        // FAIL
        local_csr_write(local_csr_mailbox1, __LINE__);                // line nr
        local_csr_write(local_csr_mailbox2, test_value );           // expected
        local_csr_write(local_csr_mailbox3, global_read_reg[0]);       // actual
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
    __addr40 void *pbuf;
    __xwrite uint32_t xcmd = 0x1234abcd;
    __xread uint32_t result;
    SIGNAL sig;
    uint32_t off = 64;


//     __RT_ASSERT(off >= 20);
//     pbuf = pkt_ctm_ptr40(__ME(), 128, 0);   // 24
    pbuf = pkt_ctm_ptr40(24, 128, 0);   // 24: emem0

//     local_csr_write(local_csr_mailbox2, (uint32_t)(((uint64_t)pbuf)>>32));
//     local_csr_write(local_csr_mailbox3, (uint32_t)((uint64_t)pbuf + off));

//     __intrinsic void __mem_write32(__xwrite void *data, __mem void *addr, size_t size, const size_t max_size, sync_t sync, SIGNAL *sig)
//     __mem_write32(xcmd, (__addr40 uint8_t *) pbuf + off - 4, sizeof(*xcmd), sizeof(*xcmd), sync, sig);
    __mem_write32(&xcmd, (__addr40 uint8_t *)pbuf + off, sizeof(xcmd), sizeof(xcmd), ctx_swap, &sig);

//     mem_read32(__xread void *data, __mem void *addr, const size_t size)
    mem_read32(&result, (__addr40 uint8_t *)pbuf + off, sizeof(result));

    // Verify
    if (result != 0x1234abcd)
    {
        // FAIL
        local_csr_write(local_csr_mailbox1, __LINE__);          // line nr
        local_csr_write(local_csr_mailbox2, 0x1234abcd);        // expected
        local_csr_write(local_csr_mailbox3, result);            // actual
        return 1;
    }

    // PASS
    return 0;
}



