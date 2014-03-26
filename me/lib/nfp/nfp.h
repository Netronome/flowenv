/*
 * Copyright (C) 2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/nfp/nfp.h
 * @brief         Standard definitions
 */
#ifndef _NFP__NFP_H_
#define _NFP__NFP_H_


/* Size specifications */
#define SZ_512          (1 <<  9)
#define SZ_1K           (1 << 10)
#define SZ_2K           (1 << 11)
#define SZ_4K           (1 << 12)
#define SZ_8K           (1 << 13)
#define SZ_16K          (1 << 14)
#define SZ_32K          (1 << 15)
#define SZ_64K          (1 << 16)
#define SZ_128K         (1 << 17)
#define SZ_256K         (1 << 18)
#define SZ_512K         (1 << 19)
#define SZ_1M           (1 << 20)
#define SZ_2M           (1 << 21)
#define SZ_4M           (1 << 22)
#define SZ_8M           (1 << 23)
#define SZ_16M          (1 << 24)
#define SZ_32M          (1 << 25)
#define SZ_64M          (1 << 26)
#define SZ_128M         (1 << 27)
#define SZ_256M         (1 << 28)
#define SZ_512M         (1 << 29)
#define SZ_1G           (1 << 30)
#define SZ_2G           (1 << 31)


#if defined(__NFP_LANG_MICROC)

/* Chip stepping defines */
/* 32xx */
#define __nfp3216  131072
#define __nfp3240  262144
#define __nfp3200 (__nfp3216 | __nfp3240)
#define __nfp32xx __nfp3200

/* 6xxx */
#define __nfp6000  524288

#define __nfp_stepping(major,minor) (((major - 'A') << 4) | minor & 0xf)
#define __REVISION_A0    __nfp_stepping('A', 0)
#define __REVISION_A1    __nfp_stepping('A', 1)
#define __REVISION_B0    __nfp_stepping('B', 0)
#define __REVISION_C0    __nfp_stepping('C', 0)

/*
 * Convenience macros
 */

/* Qualifiers for type declarations */
#define __imem          __declspec(imem)
#define __imem_n(x)     __declspec(imem##x)
#define __emem          __declspec(emem)
#define __emem_n(x)     __declspec(emem##x)
#define __dram          __declspec(dram)
#define __cls           __declspec(cls)
#define __ctm           __declspec(ctm)
#define __lmem          __declspec(local_mem)
#define __export        __declspec(export)
#define __import        __declspec(import)
#define __shared        __declspec(shared)
#define __visible       __declspec(visible)
#define __remote        __declspec(remote)
#define __ptr40         __declspec(ptr40)
#define __xread         __declspec(read_reg)
#define __xwrite        __declspec(write_reg)
#define __xrw           __declspec(read_write_reg)
#define __gpr           __declspec(gp_reg)
#define __nnr           __declspec(nn_local_reg)

#define __align(x)      __declspec(aligned(x))
#define __align2        __declspec(aligned(2))
#define __align4        __declspec(aligned(4))
#define __align8        __declspec(aligned(8))
#define __align16       __declspec(aligned(16))
#define __align32       __declspec(aligned(32))
#define __align64       __declspec(aligned(64))
#define __align128      __declspec(aligned(128))
#define __align256      __declspec(aligned(256))
#define __align512      __declspec(aligned(512))
#define __align1K       __declspec(aligned(SZ_1K))
#define __align2K       __declspec(aligned(SZ_2K))
#define __align4K       __declspec(aligned(SZ_4K))
#define __align8K       __declspec(aligned(SZ_8K))
#define __align16K      __declspec(aligned(SZ_16K))
#define __align32K      __declspec(aligned(SZ_32K))
#define __align64K      __declspec(aligned(SZ_64K))
#define __align128K     __declspec(aligned(SZ_128K))
#define __align256K     __declspec(aligned(SZ_256K))
#define __align512K     __declspec(aligned(SZ_512K))
#define __align1M       __declspec(aligned(SZ_1M))
#define __align2M       __declspec(aligned(SZ_2M))
#define __align4M       __declspec(aligned(SZ_4M))
#define __align8M       __declspec(aligned(SZ_8M))
#define __align16M      __declspec(aligned(SZ_16M))
#define __align32M      __declspec(aligned(SZ_32M))
#define __align64M      __declspec(aligned(SZ_64M))
#define __align128M     __declspec(aligned(SZ_128M))
#define __align256M     __declspec(aligned(SZ_256M))
#define __align512M     __declspec(aligned(SZ_512M))
#define __align1G       __declspec(aligned(SZ_1G))
#define __align2G       __declspec(aligned(SZ_2G))
#define __packed        __declspec(packed)

/**
 * Import variable containing the current MEID.
 * The returned value can be used to specify the CPP master ID.
 */
#define __MEID          __LoadTimeConstant("__UENGINE_ID")

/**
 * Import variable containing the natural counting ME number within the island.
 * The returned value is NOT a valid CPP master number.
 */
#define __MENUM          __LoadTimeConstant("__menum")

/**
 * Import variable containing the island number.
 */
#define __ISLAND          __LoadTimeConstant("__island")

/**
 * Check if value is power of 2
 * @param val           value to check
 */
#define __is_log2(val)  ((((val) - 1) & (val)) == 0)

/**
 * Check if base address is aligned
 * @param base          base address
 * @param align         alignment
 */
#define __is_aligned(base, align) \
    ((((unsigned long) (base)) & ((align) - 1)) == 0)

/**
 * Convert value to log2 value
 * @param val
 *
 * Converts value to log2 value, potentially rounding it down.
 *
 * NOTE: Should only be called with constant values or else the macro
 * will expand to very unefficient code.
 */
#define __log2(val)          \
    ((val) >= SZ_2G   ? 31 : \
     (val) >= SZ_1G   ? 30 : \
     (val) >= SZ_512M ? 29 : \
     (val) >= SZ_256M ? 28 : \
     (val) >= SZ_128M ? 27 : \
     (val) >= SZ_64M  ? 26 : \
     (val) >= SZ_32M  ? 25 : \
     (val) >= SZ_16M  ? 24 : \
     (val) >= SZ_8M   ? 23 : \
     (val) >= SZ_4M   ? 22 : \
     (val) >= SZ_2M   ? 21 : \
     (val) >= SZ_1M   ? 20 : \
     (val) >= SZ_512K ? 19 : \
     (val) >= SZ_256K ? 18 : \
     (val) >= SZ_128K ? 17 : \
     (val) >= SZ_64K  ? 16 : \
     (val) >= SZ_32K  ? 15 : \
     (val) >= SZ_16K  ? 14 : \
     (val) >= SZ_8K   ? 13 : \
     (val) >= SZ_4K   ? 12 : \
     (val) >= SZ_2K   ? 11 : \
     (val) >= SZ_1K   ? 10 : \
     (val) >= 512     ?  9 : \
     (val) >= 256     ?  8 : \
     (val) >= 128     ?  7 : \
     (val) >= 64      ?  6 : \
     (val) >= 32      ?  5 : \
     (val) >= 16      ?  4 : \
     (val) >= 8       ?  3 : \
     (val) >= 4       ?  2 : \
     (val) >= 2       ?  1 : \
     (val) >= 1       ?  0 : -1)


/*
 * Type declarations
 */

/**
 * SIGNAL_MASK data type is used for masks specifying one or more
 * signal registers.
 */
typedef int SIGNAL_MASK;

/**
 * SIGNAL data type is used to declare signal variables.
 */
typedef __declspec(signal) int SIGNAL;

/**
 * SIGNAL_PAIR container type for even/odd signal pair.
 */
typedef __declspec(signal_pair) struct SIGNAL_PAIR {
    int even;           /**< Even signal number.  */
    int odd;            /**< Odd signal number.  */
} SIGNAL_PAIR;

/**
 * Sync types for I/O operations.
 */
typedef enum {
    sig_done,           /**< Continue and set signal when done. */
    ctx_swap            /**< Swap thread out until complete.  */
} sync_t;

/**
 * Signal types for ctx_wait other than mask.
 * The 'kill' signal puts the context into the Sleep state and does not
 * return to the Ready state.
 * The 'voluntary' signal puts the context into the sleep state.  The context
 * is put back into the ready state in one cycle since the Voluntary Event
 * Signal is always set.
 * The 'bpt' (breakpoint) stops all contexts, interrupts the ARM processor,
 * and puts the current context into the Sleep state.  It also sets the
 * CTX_Enable[Breakpoint] bit.  This value is typically used for debugging
 * purposes.  For more information the use of this value, refer to the
 * ctx_arb instruction in the @prm.
 */
typedef enum {
    kill,       /**< Suspend the context. */
    voluntary,  /**< Put context in sleep state. */
    bpt         /**< Breakpoint. */
} signal_t;


/*
 * Built-in functions
 * See the NFCC user's guide for further details.
 */

int __is_ct_const(int v);
int __nfp_meid(int island, int menum); /* island ID, ME number in island */
int __nfp_idstr2meid(const char *idstr); /* MEID string, "iX.meY" */
int __is_in_reg(void *p);

int __is_xfer_reg(void *p);
int __is_read_reg(void *p);
int __is_write_reg(void *p);
#define __is_read_write_reg(_p) (__is_read_reg(_p) && __is_write_reg(_p))

int __is_in_reg_or_lmem(void *p);
int __is_in_dram(void *p);
#define __is_in_mem __is_in_dram
int __is_in_cls(void *p);
int __is_in_ctm(void *p);
int __is_in_lmem(void *p);
int __is_in_ustore(void *p);
int __elem_size(void *p);

int __is_nfp_arch(int chip_mask, int stepping);
int __is_nfp_arch_or_above(int chip_mask, int stepping_at_least);

void __ct_assert(int v, char *reason);
void __ct_Qperfinfo(int mask, char *info);
void __intrinsic_begin(void);
void __intrinsic_end(void);

/**
 * Associate a read write register pair
 * @param rd_buf         read xfer buffer
 * @param wr_buf         write xfer buffer
 * @param ...            optional size to associate
 */
void __associate_read_write_reg_pair_no_spill(
    __declspec(read_reg) void *rd_buf,
    __declspec(write_reg) void *wr_buf, ...);

/**
 * Create signal mask out of parameter list.
 * @param ...           list of SIGNAL, SIGNAL_PAIR or signal masks
 *
 * Each argument must be one of the following: a) address of a SIGNAL
 * variable, b) address of a SIGNAL_PAIR variable, or c) a signal
 * mask.
 *
 * The returned mask represents the hardware signals allocated to your
 * signal variables.  Any number of signals of type SIGNAL between 1
 * and 15 can be specified.
 *
 * @note When a user passes in a signal mask to a function as an int
 * parameter, the compiler cannot always figure out what bits are set
 * in the mask and hence does not know the members of the signal set
 * that is represented by the mask.  The compiler does not know the
 * life range of these signals represented in such a mask.  To get
 * register allocation right, you have to insert calls to
 * implicit_read() (see example below).
 *
 */
SIGNAL_MASK __signals(...);

/**
 * Find the signal number of a signal variable.
 * @param sig           signal variable
 * @param ...           optional microengine number
 *
 * If the signal is declared as remote, the second argument should be
 * an unsigned integer of the microengine on which it resides.
 */
int __signal_number(volatile void *sig, ...);

/**
 * Wait for all provided signals to be set.
 * @param ...           list of SIGNAL or SIGNAL_PAIR variables
 *
 * Perform ctx_arb on all the signal specified in the parameter list.
 * The AND form of the ctx_arb is generated which will only return
 * when all signals are set.
 *
 * @note For signal pairs, both even and odd signals are included in
 * the mask used for the ctx_arb.
 */
void __wait_for_all(...);
#define wait_for_all __wait_for_all

/**
 * Wait for all provided signals to be set.
 * @param ...           list of SIGNAL or SIGNAL_PAIR variables
 *
 * Perform ctx_arb on all the signal specified in the parameter list.
 * The AND form of the ctx_arb is generated which will only return
 * when all signals are set.
 *
 * @note For signal pairs, only even signals are included in the mask used for
 * the ctx_arb.  Odd signals must be explicitly referenced using SIGNAL.odd if
 * they should be included.
 */
void __wait_for_all_single(...);
#define wait_for_all_single __wait_for_all_single

/**
 * Wait for any of provided signals to be set.
 * @param ...           list of SIGNAL or SIGNAL_PAIR variables
 *
 * Perform ctx_arb on all the signal specified in the parameter list.
 * The OR form of the ctx_arb is generated will return when any signal
 * is set.
 *
 * @note For signal pairs, both even and odd signals are included in
 * the mask used for the ctx_arb.
 */
void __wait_for_any(...);
#define wait_for_any __wait_for_any

/**
 * Wait for all provided signals to be set.
 * @param ...           list of SIGNAL or SIGNAL_PAIR variables
 *
 * Perform ctx_arb on all the signal specified in the parameter list.
 * The OR form of the ctx_arb is generated will return when any signal
 * is set.
 *
 * @note For signal pairs, only even signals are included in the mask used for
 * the ctx_arb.  Odd signals must be explicitly referenced using SIGNAL.odd if
 * they should be included.
 */
void __wait_for_any_single(...);
#define wait_for_any_single __wait_for_any_single

/**
 * Find the register number assigned to a transfer register variable.
 * @param xfer          transfer register
 * @param ...           optional microengine number
 *
 * For transfer registers declared as remote, the __xfer_reg_number()
 * intrinsic takes two arguments, the first being the address of the
 * transfer register and the second being the microengine number in
 * which the transfer register resides.
 */
int __xfer_reg_number(volatile void *xfer, ...);

/**
 * Mark signal or transfer register variables as being read.
 * @param sig_or_xfer   signal or transfer register variable
 * @param ...           optional integer argument specifyin the size
 *                      in bytes of the read
 *
 * Take as argument the address of a register variable and indicate
 * that the signal or transfer register is being read asynchronously
 * or implicitly by the hardware.  It is necessary to use this
 * intrinsic to mark all definitions and use points of signal/transfer
 * registers that are not directly visible to the compiler.  This function
 * must be used, for example, when the RX_THREAD_FREELIST CSR is written
 * with the register number allocated to a variable, when a signal is
 * requested by writing into a CSR, or when a signal is tested by
 * doing a ctx_arb with a signal mask generated with __signals().
 */
void __implicit_read(void *sig_or_xfer, ...);

/**
 * Mark signal or transfer register variables as being written.
 * @param sig_or_xfer   signal or transfer register variable
 * @param ...           optional integer argument specifying the size
 *                      in bytes of the write
 *
 * Take as argument the address of a signal or transfer register
 * variable and indicate that the signal or transfer register is being
 * written asynchronously or implicitly by the hardware.  It is
 * necessary to use this intrinsic to mark all definitions and use
 * points of signal/transfer registers that are not directly visible
 * to the compiler.   This function must be used, for example, when the
 * RX_THREAD_FREELIST CSR is written with the register number
 * allocated to a variable, when a signal is requested by writing into
 * a CSR, or when a signal is tested by doing a ctx_arb with a signal
 * mask generated with __signals().
 */
void __implicit_write(void *sig_or_xfer, ...);

/**
 * Mark signal or transfer register variables as being released.
 * @param sig_or_xfer   signal or transfer register variable
 * @param ...           optional integer argument specifying the size
 *                      in bytes to mark as undefined
 *
 * Take as an argument the address of a register variable, and
 * indicate to the compiler that the variable can be considered
 * undefined until the next time it is written to, even if the
 * variable is read.  Undefined variables do not require registers.
 * __implicit_undef() and __implicit_write() are similar in that they
 * can be used to prevent the compiler from storing a prior value of
 * the variable.  Unlike __implicit_write(), however,
 * __implicit_undef() will not cause the compiler to reserve registers
 * for the variable after the call.
 *
 *<b>Example:</b>
 *
 * @code
 * while (1) {
 *   __implicit_undef(&x);
 *   ... /// Other code
 *   if (!error) {
 *      x = 1;
 * }
 * sram_write(&x,...);
 * @endcode
 *
 * In this example the __implicit_undef() will guarantee that
 * registers will not be reserved for "x" in the area marked "Other
 * code".  Without it, the compiler has to assume that the value of
 * "x" from a previous iteration of the loop might be used in the
 * current iteration, since "error" might be true.  Registers would
 * then have to be reserved for "x" throughout the entire loop.  With
 * the __implicit_undef() call, the compiler will see that "x" starts
 * with an undefined value in every loop iteration, and the previous
 * value will not be needed.  __implicit_write() could also be used,
 * but it would have to be placed directly before the "if (!error)"
 * statement, since it is equivalent to writing a new value to "x"
 * which has to be preserved by the compiler in a register.
 * __implicit_undef(), in contrast, "overwrites" any previous value of
 * the variable but does not "write" a new value.
 */
void __implicit_undef(void *sig_or_xfer, ...);

/**
 * Bind a signal or transfer register variable to a register number
 * @param sig_or_reg    signal or transfer register variable
 * @param reg_num       physical register number to bind variable to
 *
 * Take the address of a signal variable or register variable, and
 * bind it to a physical register number.  If the address of a
 * structure or array is passed, the first element of the structure or
 * array will be assigned the physical register number, and every
 * successive element will be assigned a consecutive register number.
 */
void __assign_relative_register(void *sig_or_reg, int reg_num);

/**
 * Mark beginning of no-spill region.
 *
 * Mark the beginning of a "no-spill" program region, where the
 * compiler attempts to keep all the used variables in registers
 * unless they have been explicitly allocated to memory or have had
 * their address taken.
 *
 * This is done at the expense of other program regions, which may
 * incur extra spills.  If the compiler cannot allocate all the
 * variables to registers, compilation will halt with an error
 * message.
 */
void __no_spill_begin(void);

/**
 * Mark the end of a no-spill region.
 *
 * @see __no_spill_begin()
 */
void __no_spill_end(void);

/**
 * Mark the start of a no swap region.
 *
 * Create a region where the compiler will not generate any
 * instructions that will incur a context swap.
 */
void __no_swap_begin(void);

/**
 * Mark the end of a no swap region.
 *
 * @see __no_swap_begin()
 */
void __no_swap_end(void);

/**
 * Test if a signal is set.
 * @param sig           signal to test for
 *
 * Test whether or not a signal is set.  Signal is a user signal
 * variable.  If signal is set it gets cleared as a side effect of
 * testing it.
 */
int signal_test(volatile SIGNAL *sig);

/**
 * Get the current context number.
 *
 * The value of the currently executing context in the range of 0
 * through 7.
 */
#define ctx() __ctx()
unsigned int __ctx(void);

/**
 * Get the current number of contexts.
 *
 * The number of contexts compiled to run.  The range is 0 to 7.
 */
#define n_ctx() __n_ctx()
unsigned int __n_ctx(void);

/**
 * Get the context mode.
 *
 * Mode for number of contexts, either 4 or 8.
 */
#define nctx_mode() __nctx_mode()
unsigned int __nctx_mode(void);


/**
 * Lookup value of a load time constant (import variable)
 * @param name          name of import variable
 */
long long __LoadTimeConstant(char *name);


/**
 * Marks a section of code as being on the critical path of the application.
 *
 * @param ...  Optional argument indicates priority in 0-100.  Default is 100.
 *
 * Takes an optional integer argument (0-100) that specifies the
 * priority of overlapping critical paths.  Higher numbered paths
 * receive higher priority for code layout.  The default is 100 if no
 * argument is specified.
 */
void __critical_path(...);


/*
 * Non built-in functions
 */

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

#endif /* !_NFP__NFP_H_ */
