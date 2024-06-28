
#ifndef FREERTOS_HPMICRO_VECTORS_H
#define FREERTOS_HPMICRO_VECTORS_H
/* This file is only used by Hpimcro FreeRTOS interrupt vector mode support */

#if !defined(DISABLE_IRQ_PREEMPTIVE) || (DISABLE_IRQ_PREEMPTIVE == 0)
.macro NESTED_IRQ_HANDLING
    csrsi mstatus, 8
.endm
#else
.macro NESTED_IRQ_HANDLING
.endm
#endif

.macro DEFINE_IRQ_HANDLER irq
  .weak irq_handler_wrapper_\irq
  .type irq_handler_wrapper_\irq, function
  .func
  irq_handler_wrapper_\irq:
    j .
    .endfunc

  .global default_isr_\irq
  .type default_isr_\irq, function
  .long default_isr_\irq
  .func
  default_isr_\irq:
      portcontextSAVE_INTERRUPT_CONTEXT
      NESTED_IRQ_HANDLING
      call irq_handler_wrapper_\irq
      csrci mstatus, 8
      lui a4, 0xe4200
      li a3, \irq
      store_x a3, 4(a4)
      portcontextRESTORE_CONTEXT
      .endfunc
.endm

/* Define the weak user isr handler wrapper function for all interrupts and isr handler entry function placed in __vector_table
 * default_isr_xxx is placed in __vector_table. Once an interrupt occur, soc will turn to the default_isr_xxx point, if vector mode
 * is enabled.
 * irq_handler_wrapper_xxx is user defined isr handler. It is defined by macro SDK_DECLARE_EXT_ISR_M and have the weak verion in
 * this file */

DEFINE_IRQ_HANDLER	1
DEFINE_IRQ_HANDLER	2
DEFINE_IRQ_HANDLER	3
DEFINE_IRQ_HANDLER	4
DEFINE_IRQ_HANDLER	5
DEFINE_IRQ_HANDLER	6
DEFINE_IRQ_HANDLER	7
DEFINE_IRQ_HANDLER	8
DEFINE_IRQ_HANDLER	9
DEFINE_IRQ_HANDLER	10
DEFINE_IRQ_HANDLER	11
DEFINE_IRQ_HANDLER	12
DEFINE_IRQ_HANDLER	13
DEFINE_IRQ_HANDLER	14
DEFINE_IRQ_HANDLER	15
DEFINE_IRQ_HANDLER	16
DEFINE_IRQ_HANDLER	17
DEFINE_IRQ_HANDLER	18
DEFINE_IRQ_HANDLER	19
DEFINE_IRQ_HANDLER	20
DEFINE_IRQ_HANDLER	21
DEFINE_IRQ_HANDLER	22
DEFINE_IRQ_HANDLER	23
DEFINE_IRQ_HANDLER	24
DEFINE_IRQ_HANDLER	25
DEFINE_IRQ_HANDLER	26
DEFINE_IRQ_HANDLER	27
DEFINE_IRQ_HANDLER	28
DEFINE_IRQ_HANDLER	29
DEFINE_IRQ_HANDLER	30
DEFINE_IRQ_HANDLER	31
DEFINE_IRQ_HANDLER	32
DEFINE_IRQ_HANDLER	33
DEFINE_IRQ_HANDLER	34
DEFINE_IRQ_HANDLER	35
DEFINE_IRQ_HANDLER	36
DEFINE_IRQ_HANDLER	37
DEFINE_IRQ_HANDLER	38
DEFINE_IRQ_HANDLER	39
DEFINE_IRQ_HANDLER	40
DEFINE_IRQ_HANDLER	41
DEFINE_IRQ_HANDLER	42
DEFINE_IRQ_HANDLER	43
DEFINE_IRQ_HANDLER	44
DEFINE_IRQ_HANDLER	45
DEFINE_IRQ_HANDLER	46
DEFINE_IRQ_HANDLER	47
DEFINE_IRQ_HANDLER	48
DEFINE_IRQ_HANDLER	49
DEFINE_IRQ_HANDLER	50
DEFINE_IRQ_HANDLER	51
DEFINE_IRQ_HANDLER	52
DEFINE_IRQ_HANDLER	53
DEFINE_IRQ_HANDLER	54
DEFINE_IRQ_HANDLER	55
DEFINE_IRQ_HANDLER	56
DEFINE_IRQ_HANDLER	57
DEFINE_IRQ_HANDLER	58
DEFINE_IRQ_HANDLER	59
DEFINE_IRQ_HANDLER	60
DEFINE_IRQ_HANDLER	61
DEFINE_IRQ_HANDLER	62
DEFINE_IRQ_HANDLER	63
DEFINE_IRQ_HANDLER	64
DEFINE_IRQ_HANDLER	65
DEFINE_IRQ_HANDLER	66
DEFINE_IRQ_HANDLER	67
DEFINE_IRQ_HANDLER	68
DEFINE_IRQ_HANDLER	69
DEFINE_IRQ_HANDLER	70
DEFINE_IRQ_HANDLER	71
DEFINE_IRQ_HANDLER	72
DEFINE_IRQ_HANDLER	73
DEFINE_IRQ_HANDLER	74
DEFINE_IRQ_HANDLER	75
DEFINE_IRQ_HANDLER	76
DEFINE_IRQ_HANDLER	77
DEFINE_IRQ_HANDLER	78
DEFINE_IRQ_HANDLER	79
DEFINE_IRQ_HANDLER	80
DEFINE_IRQ_HANDLER	81
DEFINE_IRQ_HANDLER	82
DEFINE_IRQ_HANDLER	83
DEFINE_IRQ_HANDLER	84
DEFINE_IRQ_HANDLER	85
DEFINE_IRQ_HANDLER	86
DEFINE_IRQ_HANDLER	87
DEFINE_IRQ_HANDLER	88
DEFINE_IRQ_HANDLER	89
DEFINE_IRQ_HANDLER	90
DEFINE_IRQ_HANDLER	91
DEFINE_IRQ_HANDLER	92
DEFINE_IRQ_HANDLER	93
DEFINE_IRQ_HANDLER	94
DEFINE_IRQ_HANDLER	95
DEFINE_IRQ_HANDLER	96
DEFINE_IRQ_HANDLER	97
DEFINE_IRQ_HANDLER	98
DEFINE_IRQ_HANDLER	99
DEFINE_IRQ_HANDLER	100
DEFINE_IRQ_HANDLER	101
DEFINE_IRQ_HANDLER	102
DEFINE_IRQ_HANDLER	103
DEFINE_IRQ_HANDLER	104
DEFINE_IRQ_HANDLER	105
DEFINE_IRQ_HANDLER	106
DEFINE_IRQ_HANDLER	107
DEFINE_IRQ_HANDLER	108
DEFINE_IRQ_HANDLER	109
DEFINE_IRQ_HANDLER	110
DEFINE_IRQ_HANDLER	111
DEFINE_IRQ_HANDLER	112
DEFINE_IRQ_HANDLER	113
DEFINE_IRQ_HANDLER	114
DEFINE_IRQ_HANDLER	115
DEFINE_IRQ_HANDLER	116
DEFINE_IRQ_HANDLER	117
DEFINE_IRQ_HANDLER	118
DEFINE_IRQ_HANDLER	119
DEFINE_IRQ_HANDLER	120
DEFINE_IRQ_HANDLER	121
DEFINE_IRQ_HANDLER	122
DEFINE_IRQ_HANDLER	123
DEFINE_IRQ_HANDLER	124
DEFINE_IRQ_HANDLER	125
DEFINE_IRQ_HANDLER	126
DEFINE_IRQ_HANDLER	127
DEFINE_IRQ_HANDLER	128
DEFINE_IRQ_HANDLER	129
DEFINE_IRQ_HANDLER	130
DEFINE_IRQ_HANDLER	131
DEFINE_IRQ_HANDLER	132
DEFINE_IRQ_HANDLER	133
DEFINE_IRQ_HANDLER	134
DEFINE_IRQ_HANDLER	135
DEFINE_IRQ_HANDLER	136
DEFINE_IRQ_HANDLER	137
DEFINE_IRQ_HANDLER	138
DEFINE_IRQ_HANDLER	139
DEFINE_IRQ_HANDLER	140
DEFINE_IRQ_HANDLER	141
DEFINE_IRQ_HANDLER	142
DEFINE_IRQ_HANDLER	143
DEFINE_IRQ_HANDLER	144
DEFINE_IRQ_HANDLER	145
DEFINE_IRQ_HANDLER	146
DEFINE_IRQ_HANDLER	147
DEFINE_IRQ_HANDLER	148
DEFINE_IRQ_HANDLER	149
DEFINE_IRQ_HANDLER	150


#endif