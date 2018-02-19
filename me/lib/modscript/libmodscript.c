/*
 * Copyright (C) 2017-2018 Netronome Systems, Inc. All rights reserved.
 *
 * @file          lib/modscript/libmodscript.c
 * @brief         Interface to the packet modifier script
 *
 * This file contains the interface to the packet modifier script write
 * functions.
 *
 * It's main purpose is to hide the details of the packet modifier script
 * from the application code.
 *
 */

#include <nfp.h>
#include <nfp/me.h>
#include <nfp/cls.h>
#include <pkt/pkt.h>
#include <std/reg_utils.h>
#include <nfp/mem_bulk.h>
#include <modscript/modscript.h>
#include <modscript/modscript_table.h>


/* Only supported in B0 */
#if (__REVISION_MIN >= __REVISION_C0)
    #error "Unsupported chip revision"
#elif (__REVISION_MAX < __REVISION_B0)
    #error "Unsupported chip revision"
#else
    /* supported */
#endif

/*
* Packet modifier CSRs are configured using the supported script offsets and
* the valid packet offsets - see modscript_init.h
* The number of delete opcodes plus padding and/or NOPs are configured in the
* PktModifier CSRs.
* A table in CLS (modscript_tbl) is used to lookup the applicable indirect
* script values - see modscript_table.h.
* This table is indexed on the packet offset (minus the minimum packet offset),
* and contains:
* - the packet modifier script which is either two or four
*   words in length (CSR idx and offsets - see modscript_struct_t)
* - the offset in the packet at which the script should be written
* - the length to use when writing to the packet (two or four words)
*
* The supported script offsets (B0) plus valid packet offsets
* are listed in table below:
*
* Script Offset     Packet Offsets
* --------------    --------------
* 3=32              40, 41, .. 46
* 4=40              48, 49, .. 54
* 5=48              56, 57, .. 62
* 6=56              64, 65, .. 70, .. 102
* 11=96             104, 105, .. 110
* 12=104            112, 113, .. 118
* 13=112            120, 121, .. 126
* 14=120            128, 129, .. 137, 138 .. 248
*/

__intrinsic struct pkt_ms_info
__modscript_write(__mem40  void *pbuf,
        unsigned char off, __xwrite modscript_struct_t *pwrite,
        __xread uint32_t *rdback, SIGNAL *sig1,
        SIGNAL *sig2)
{
    SIGNAL wr_sig,  rd_sig;
    __xread modscript_struct_t rd_xfer;
    __gpr uint32_t script_idx = off - PKTIO_MIN_NBI_TX_OFFSET;
    __gpr struct pkt_ms_info msi;
    __mem40 unsigned char *mem_ptr;

    msi.off_enc = 0;
    script_idx = script_idx/1;

    if (script_idx < NUM_ENTRIES) {
        cls_read(&rd_xfer, (__cls void *)&modscript_tbl[script_idx][0],
                 sizeof(modscript_struct_t));

        /*
         * Set the encoding:
         * 3=32, 4=40, 5=48, 6=56, 11=96, 12=104, 13=112, 14=120
         */
        msi.off_enc = (rd_xfer.prepend_offset >> 3) - 1;

        /* If encoding invalid, return 0. */
        if (msi.off_enc < 3 || msi.off_enc > 14) {
            msi.off_enc = 0;
            return msi;
        }

        __critical_path();

        reg_cp(&pwrite->value[0], &rd_xfer.value[0], sizeof(rd_xfer));

        mem_ptr = (__mem40 unsigned char *)pbuf + rd_xfer.prepend_offset;

        __mem_write32(&pwrite->value[0], (__mem40 void *)mem_ptr,
                      rd_xfer.prepend_len0 << 2, 4 << 2, sig_done, sig1);
        __mem_read32(rdback, (__mem40 void *)mem_ptr, 1 << 2,
                    1 << 2, sig_done, sig2);

        /* Set the length adjustment to point to the start of packet. */
        msi.len_adj = off;
    }
    return msi;
}

__intrinsic struct pkt_ms_info
modscript_write(__mem40 void *pbuf, unsigned char off)
{
    SIGNAL wr_sig,  rd_sig;
    __gpr struct pkt_ms_info msi;
    __xread uint32_t rd_xfer;

    __xwrite modscript_struct_t wr_xfer;

    msi = __modscript_write(pbuf, off, &wr_xfer, &rd_xfer,&wr_sig,
                            &rd_sig);
    wait_for_all(&wr_sig, &rd_sig);
    return msi;
}
