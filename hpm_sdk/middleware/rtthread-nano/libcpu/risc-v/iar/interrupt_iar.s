/*
 * Copyright (c) 2021-2024 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "cpuport.h"

    SECTION CSTACK:DATA:NOROOT(3)

    EXTERN rt_thread_switch_interrupt_flag
    EXTERN rt_interrupt_from_thread
    EXTERN rt_interrupt_to_thread
    EXTERN rt_interrupt_enter
    EXTERN irq_handler_trap
    EXTERN rt_interrupt_leave



    SECTION `.isr_vector`:CODE:ROOT(3)
    PUBLIC rtt_risc_v_trap_handler
rtt_risc_v_trap_handler:
#ifdef ARCH_RISCV_FPU
    addi    sp, sp, -32 * FREGBYTES
    FSTORE  f0, 0 * FREGBYTES(sp)
    FSTORE  f1, 1 * FREGBYTES(sp)
    FSTORE  f2, 2 * FREGBYTES(sp)
    FSTORE  f3, 3 * FREGBYTES(sp)
    FSTORE  f4, 4 * FREGBYTES(sp)
    FSTORE  f5, 5 * FREGBYTES(sp)
    FSTORE  f6, 6 * FREGBYTES(sp)
    FSTORE  f7, 7 * FREGBYTES(sp)
    FSTORE  f8, 8 * FREGBYTES(sp)
    FSTORE  f9, 9 * FREGBYTES(sp)
    FSTORE  f10, 10 * FREGBYTES(sp)
    FSTORE  f11, 11 * FREGBYTES(sp)
    FSTORE  f12, 12 * FREGBYTES(sp)
    FSTORE  f13, 13 * FREGBYTES(sp)
    FSTORE  f14, 14 * FREGBYTES(sp)
    FSTORE  f15, 15 * FREGBYTES(sp)
    FSTORE  f16, 16 * FREGBYTES(sp)
    FSTORE  f17, 17 * FREGBYTES(sp)
    FSTORE  f18, 18 * FREGBYTES(sp)
    FSTORE  f19, 19 * FREGBYTES(sp)
    FSTORE  f20, 20 * FREGBYTES(sp)
    FSTORE  f21, 21 * FREGBYTES(sp)
    FSTORE  f22, 22 * FREGBYTES(sp)
    FSTORE  f23, 23 * FREGBYTES(sp)
    FSTORE  f24, 24 * FREGBYTES(sp)
    FSTORE  f25, 25 * FREGBYTES(sp)
    FSTORE  f26, 26 * FREGBYTES(sp)
    FSTORE  f27, 27 * FREGBYTES(sp)
    FSTORE  f28, 28 * FREGBYTES(sp)
    FSTORE  f29, 29 * FREGBYTES(sp)
    FSTORE  f30, 30 * FREGBYTES(sp)
    FSTORE  f31, 31 * FREGBYTES(sp)
#endif
    /* save all from thread context */
#ifndef __riscv_32e
    addi sp, sp, -32 * REGBYTES
#else
    addi sp, sp, -16 * REGBYTES
#endif

    STORE x1,   1 * REGBYTES(sp)
    STORE x4,   4 * REGBYTES(sp)
    STORE x5,   5 * REGBYTES(sp)
    STORE x6,   6 * REGBYTES(sp)
    STORE x7,   7 * REGBYTES(sp)
    STORE x8,   8 * REGBYTES(sp)
    STORE x9,   9 * REGBYTES(sp)
    STORE x10, 10 * REGBYTES(sp)
    STORE x11, 11 * REGBYTES(sp)
    STORE x12, 12 * REGBYTES(sp)
    STORE x13, 13 * REGBYTES(sp)
    STORE x14, 14 * REGBYTES(sp)
    STORE x15, 15 * REGBYTES(sp)
#ifndef __riscv_32e
    STORE x16, 16 * REGBYTES(sp)
    STORE x17, 17 * REGBYTES(sp)
    STORE x18, 18 * REGBYTES(sp)
    STORE x19, 19 * REGBYTES(sp)
    STORE x20, 20 * REGBYTES(sp)
    STORE x21, 21 * REGBYTES(sp)
    STORE x22, 22 * REGBYTES(sp)
    STORE x23, 23 * REGBYTES(sp)
    STORE x24, 24 * REGBYTES(sp)
    STORE x25, 25 * REGBYTES(sp)
    STORE x26, 26 * REGBYTES(sp)
    STORE x27, 27 * REGBYTES(sp)
    STORE x28, 28 * REGBYTES(sp)
    STORE x29, 29 * REGBYTES(sp)
    STORE x30, 30 * REGBYTES(sp)
    STORE x31, 31 * REGBYTES(sp)
#endif

    li    t0,   0x80
    STORE t0,   2 * REGBYTES(sp)

    mv  s0, sp

    /* switch to interrupt stack */
    la t0, SFE(CSTACK)
    mv sp, t0

    /* interrupt handle */
    call  rt_interrupt_enter
    call  irq_handler_trap
    call  rt_interrupt_leave

    /* switch to from thread stack */
    mv  sp, s0

    /* need to switch new thread */
    la    s0, rt_thread_switch_interrupt_flag
    lw    s2, 0(s0)
    beqz  s2, spurious_interrupt
    /* clear switch interrupt flag */
    sw    zero, 0(s0)

    csrr  a0, mepc
    STORE a0, 0 * REGBYTES(sp)

    la    s0, rt_interrupt_from_thread
    LOAD  s1, 0(s0)
    STORE sp, 0(s1)

    la    s0, rt_interrupt_to_thread
    LOAD  s1, 0(s0)
    LOAD  sp, 0(s1)

    LOAD  a0,  0 * REGBYTES(sp)
    csrw  mepc, a0

spurious_interrupt:
    LOAD  x1,   1 * REGBYTES(sp)

    /* Remain in M-mode after mret */
    li    t0, 0x00001800
    csrs  mstatus, t0
    LOAD  t0,   2 * REGBYTES(sp)
    csrs  mstatus, t0

    LOAD  x4,   4 * REGBYTES(sp)
    LOAD  x5,   5 * REGBYTES(sp)
    LOAD  x6,   6 * REGBYTES(sp)
    LOAD  x7,   7 * REGBYTES(sp)
    LOAD  x8,   8 * REGBYTES(sp)
    LOAD  x9,   9 * REGBYTES(sp)
    LOAD  x10, 10 * REGBYTES(sp)
    LOAD  x11, 11 * REGBYTES(sp)
    LOAD  x12, 12 * REGBYTES(sp)
    LOAD  x13, 13 * REGBYTES(sp)
    LOAD  x14, 14 * REGBYTES(sp)
    LOAD  x15, 15 * REGBYTES(sp)
#ifndef __riscv_32e
    LOAD  x16, 16 * REGBYTES(sp)
    LOAD  x17, 17 * REGBYTES(sp)
    LOAD  x18, 18 * REGBYTES(sp)
    LOAD  x19, 19 * REGBYTES(sp)
    LOAD  x20, 20 * REGBYTES(sp)
    LOAD  x21, 21 * REGBYTES(sp)
    LOAD  x22, 22 * REGBYTES(sp)
    LOAD  x23, 23 * REGBYTES(sp)
    LOAD  x24, 24 * REGBYTES(sp)
    LOAD  x25, 25 * REGBYTES(sp)
    LOAD  x26, 26 * REGBYTES(sp)
    LOAD  x27, 27 * REGBYTES(sp)
    LOAD  x28, 28 * REGBYTES(sp)
    LOAD  x29, 29 * REGBYTES(sp)
    LOAD  x30, 30 * REGBYTES(sp)
    LOAD  x31, 31 * REGBYTES(sp)

    addi  sp, sp, 32 * REGBYTES
#else
    addi  sp, sp, 16 * REGBYTES
#endif

#ifdef ARCH_RISCV_FPU
    FLOAD   f0, 0 * FREGBYTES(sp)
    FLOAD   f1, 1 * FREGBYTES(sp)
    FLOAD   f2, 2 * FREGBYTES(sp)
    FLOAD   f3, 3 * FREGBYTES(sp)
    FLOAD   f4, 4 * FREGBYTES(sp)
    FLOAD   f5, 5 * FREGBYTES(sp)
    FLOAD   f6, 6 * FREGBYTES(sp)
    FLOAD   f7, 7 * FREGBYTES(sp)
    FLOAD   f8, 8 * FREGBYTES(sp)
    FLOAD   f9, 9 * FREGBYTES(sp)
    FLOAD   f10, 10 * FREGBYTES(sp)
    FLOAD   f11, 11 * FREGBYTES(sp)
    FLOAD   f12, 12 * FREGBYTES(sp)
    FLOAD   f13, 13 * FREGBYTES(sp)
    FLOAD   f14, 14 * FREGBYTES(sp)
    FLOAD   f15, 15 * FREGBYTES(sp)
    FLOAD   f16, 16 * FREGBYTES(sp)
    FLOAD   f17, 17 * FREGBYTES(sp)
    FLOAD   f18, 18 * FREGBYTES(sp)
    FLOAD   f19, 19 * FREGBYTES(sp)
    FLOAD   f20, 20 * FREGBYTES(sp)
    FLOAD   f21, 21 * FREGBYTES(sp)
    FLOAD   f22, 22 * FREGBYTES(sp)
    FLOAD   f23, 23 * FREGBYTES(sp)
    FLOAD   f24, 24 * FREGBYTES(sp)
    FLOAD   f25, 25 * FREGBYTES(sp)
    FLOAD   f26, 26 * FREGBYTES(sp)
    FLOAD   f27, 27 * FREGBYTES(sp)
    FLOAD   f28, 28 * FREGBYTES(sp)
    FLOAD   f29, 29 * FREGBYTES(sp)
    FLOAD   f30, 30 * FREGBYTES(sp)
    FLOAD   f31, 31 * FREGBYTES(sp)

    addi    sp, sp, 32 * FREGBYTES
#endif
    mret

    END