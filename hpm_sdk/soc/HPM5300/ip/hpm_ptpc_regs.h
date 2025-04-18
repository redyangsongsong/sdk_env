/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PTPC_H
#define HPM_PTPC_H

typedef struct {
    struct {
        __RW uint32_t CTRL0;                   /* 0x0: Control Register 0 */
        __RW uint32_t CTRL1;                   /* 0x4: Control Register 1 */
        __R  uint32_t TIMEH;                   /* 0x8: timestamp high */
        __R  uint32_t TIMEL;                   /* 0xC: timestamp low */
        __RW uint32_t TS_UPDTH;                /* 0x10: timestamp update high */
        __RW uint32_t TS_UPDTL;                /* 0x14: timestamp update low */
        __RW uint32_t ADDEND;                  /* 0x18:  */
        __RW uint32_t TARH;                    /* 0x1C:  */
        __RW uint32_t TARL;                    /* 0x20:  */
        __R  uint8_t  RESERVED0[8];            /* 0x24 - 0x2B: Reserved */
        __RW uint32_t PPS_CTRL;                /* 0x2C:  */
        __R  uint32_t CAPT_SNAPH;              /* 0x30:  */
        __RW uint32_t CAPT_SNAPL;              /* 0x34:  */
        __R  uint8_t  RESERVED1[4040];         /* 0x38 - 0xFFF: Reserved */
    } PTPC[2];
    __RW uint32_t TIME_SEL;                    /* 0x2000:  */
    __W  uint32_t INT_STS;                     /* 0x2004:  */
    __RW uint32_t INT_EN;                      /* 0x2008:  */
    __R  uint8_t  RESERVED0[4084];             /* 0x200C - 0x2FFF: Reserved */
    __RW uint32_t PTPC_CAN_TS_SEL;             /* 0x3000:  */
} PTPC_Type;


/* Bitfield definition for register of struct array PTPC: CTRL0 */
/*
 * SUBSEC_DIGITAL_ROLLOVER (RW)
 *
 * Format for ns counter rollover,
 * 1-digital, overflow time 1000000000/0x3B9ACA00
 * 0-binary, overflow time  0x7FFFFFFF
 */
#define PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_MASK (0x200U)
#define PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SHIFT (9U)
#define PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SHIFT) & PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_MASK)
#define PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_MASK) >> PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SHIFT)

/*
 * CAPT_SNAP_KEEP (RW)
 *
 * set  will keep capture snap till software read capt_snapl.
 * If this bit is set, software should read capt_snaph first to avoid wrong result.
 * If this bit is cleared, capture result will be updated at each capture event
 */
#define PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_MASK (0x100U)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_SHIFT (8U)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_SHIFT) & PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_MASK)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_MASK) >> PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_SHIFT)

/*
 * CAPT_SNAP_POS_EN (RW)
 *
 * set will use posege of input capture signal to latch timestamp value
 */
#define PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK (0x80U)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_SHIFT (7U)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_SHIFT) & PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK) >> PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_SHIFT)

/*
 * CAPT_SNAP_NEG_EN (RW)
 *
 */
#define PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK (0x40U)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_SHIFT (6U)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_SHIFT) & PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK)
#define PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK) >> PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_SHIFT)

/*
 * COMP_EN (RW)
 *
 * set to enable compare, will be cleared by HW when compare event triggered
 */
#define PTPC_PTPC_CTRL0_COMP_EN_MASK (0x10U)
#define PTPC_PTPC_CTRL0_COMP_EN_SHIFT (4U)
#define PTPC_PTPC_CTRL0_COMP_EN_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_COMP_EN_SHIFT) & PTPC_PTPC_CTRL0_COMP_EN_MASK)
#define PTPC_PTPC_CTRL0_COMP_EN_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_COMP_EN_MASK) >> PTPC_PTPC_CTRL0_COMP_EN_SHIFT)

/*
 * UPDATE_TIMER (WO)
 *
 * update timer with +/- ts_updt, pulse, clear after set
 */
#define PTPC_PTPC_CTRL0_UPDATE_TIMER_MASK (0x8U)
#define PTPC_PTPC_CTRL0_UPDATE_TIMER_SHIFT (3U)
#define PTPC_PTPC_CTRL0_UPDATE_TIMER_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_UPDATE_TIMER_SHIFT) & PTPC_PTPC_CTRL0_UPDATE_TIMER_MASK)
#define PTPC_PTPC_CTRL0_UPDATE_TIMER_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_UPDATE_TIMER_MASK) >> PTPC_PTPC_CTRL0_UPDATE_TIMER_SHIFT)

/*
 * INIT_TIMER (WO)
 *
 * initial timer with ts_updt, pulse, clear after set
 */
#define PTPC_PTPC_CTRL0_INIT_TIMER_MASK (0x4U)
#define PTPC_PTPC_CTRL0_INIT_TIMER_SHIFT (2U)
#define PTPC_PTPC_CTRL0_INIT_TIMER_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_INIT_TIMER_SHIFT) & PTPC_PTPC_CTRL0_INIT_TIMER_MASK)
#define PTPC_PTPC_CTRL0_INIT_TIMER_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_INIT_TIMER_MASK) >> PTPC_PTPC_CTRL0_INIT_TIMER_SHIFT)

/*
 * FINE_COARSE_SEL (RW)
 *
 * 0: coarse update, ns counter add ss_incr[7:0] each clk
 * 1: fine update, ns counter add ss_incr[7:0] each time addend counter overflow
 */
#define PTPC_PTPC_CTRL0_FINE_COARSE_SEL_MASK (0x2U)
#define PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SHIFT (1U)
#define PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SHIFT) & PTPC_PTPC_CTRL0_FINE_COARSE_SEL_MASK)
#define PTPC_PTPC_CTRL0_FINE_COARSE_SEL_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_FINE_COARSE_SEL_MASK) >> PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SHIFT)

/*
 * TIMER_ENABLE (RW)
 *
 */
#define PTPC_PTPC_CTRL0_TIMER_ENABLE_MASK (0x1U)
#define PTPC_PTPC_CTRL0_TIMER_ENABLE_SHIFT (0U)
#define PTPC_PTPC_CTRL0_TIMER_ENABLE_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL0_TIMER_ENABLE_SHIFT) & PTPC_PTPC_CTRL0_TIMER_ENABLE_MASK)
#define PTPC_PTPC_CTRL0_TIMER_ENABLE_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL0_TIMER_ENABLE_MASK) >> PTPC_PTPC_CTRL0_TIMER_ENABLE_SHIFT)

/* Bitfield definition for register of struct array PTPC: CTRL1 */
/*
 * SS_INCR (RW)
 *
 * constant value used to add ns counter;
 * such as for 50MHz timer clock, set it to 8'd20
 */
#define PTPC_PTPC_CTRL1_SS_INCR_MASK (0xFFU)
#define PTPC_PTPC_CTRL1_SS_INCR_SHIFT (0U)
#define PTPC_PTPC_CTRL1_SS_INCR_SET(x) (((uint32_t)(x) << PTPC_PTPC_CTRL1_SS_INCR_SHIFT) & PTPC_PTPC_CTRL1_SS_INCR_MASK)
#define PTPC_PTPC_CTRL1_SS_INCR_GET(x) (((uint32_t)(x) & PTPC_PTPC_CTRL1_SS_INCR_MASK) >> PTPC_PTPC_CTRL1_SS_INCR_SHIFT)

/* Bitfield definition for register of struct array PTPC: TIMEH */
/*
 * TIMESTAMP_HIGH (RO)
 *
 */
#define PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_SHIFT (0U)
#define PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_GET(x) (((uint32_t)(x) & PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_MASK) >> PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_SHIFT)

/* Bitfield definition for register of struct array PTPC: TIMEL */
/*
 * TIMESTAMP_LOW (RO)
 *
 */
#define PTPC_PTPC_TIMEL_TIMESTAMP_LOW_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_TIMEL_TIMESTAMP_LOW_SHIFT (0U)
#define PTPC_PTPC_TIMEL_TIMESTAMP_LOW_GET(x) (((uint32_t)(x) & PTPC_PTPC_TIMEL_TIMESTAMP_LOW_MASK) >> PTPC_PTPC_TIMEL_TIMESTAMP_LOW_SHIFT)

/* Bitfield definition for register of struct array PTPC: TS_UPDTH */
/*
 * SEC_UPDATE (RW)
 *
 * together with ts_updtl, used to initial or update timestamp
 */
#define PTPC_PTPC_TS_UPDTH_SEC_UPDATE_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SHIFT (0U)
#define PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SET(x) (((uint32_t)(x) << PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SHIFT) & PTPC_PTPC_TS_UPDTH_SEC_UPDATE_MASK)
#define PTPC_PTPC_TS_UPDTH_SEC_UPDATE_GET(x) (((uint32_t)(x) & PTPC_PTPC_TS_UPDTH_SEC_UPDATE_MASK) >> PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SHIFT)

/* Bitfield definition for register of struct array PTPC: TS_UPDTL */
/*
 * ADD_SUB (RW)
 *
 * 1 for sub; 0 for add, used only at update
 */
#define PTPC_PTPC_TS_UPDTL_ADD_SUB_MASK (0x80000000UL)
#define PTPC_PTPC_TS_UPDTL_ADD_SUB_SHIFT (31U)
#define PTPC_PTPC_TS_UPDTL_ADD_SUB_SET(x) (((uint32_t)(x) << PTPC_PTPC_TS_UPDTL_ADD_SUB_SHIFT) & PTPC_PTPC_TS_UPDTL_ADD_SUB_MASK)
#define PTPC_PTPC_TS_UPDTL_ADD_SUB_GET(x) (((uint32_t)(x) & PTPC_PTPC_TS_UPDTL_ADD_SUB_MASK) >> PTPC_PTPC_TS_UPDTL_ADD_SUB_SHIFT)

/*
 * NS_UPDATE (RW)
 *
 */
#define PTPC_PTPC_TS_UPDTL_NS_UPDATE_MASK (0x7FFFFFFFUL)
#define PTPC_PTPC_TS_UPDTL_NS_UPDATE_SHIFT (0U)
#define PTPC_PTPC_TS_UPDTL_NS_UPDATE_SET(x) (((uint32_t)(x) << PTPC_PTPC_TS_UPDTL_NS_UPDATE_SHIFT) & PTPC_PTPC_TS_UPDTL_NS_UPDATE_MASK)
#define PTPC_PTPC_TS_UPDTL_NS_UPDATE_GET(x) (((uint32_t)(x) & PTPC_PTPC_TS_UPDTL_NS_UPDATE_MASK) >> PTPC_PTPC_TS_UPDTL_NS_UPDATE_SHIFT)

/* Bitfield definition for register of struct array PTPC: ADDEND */
/*
 * ADDEND (RW)
 *
 * used in fine update mode only
 */
#define PTPC_PTPC_ADDEND_ADDEND_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_ADDEND_ADDEND_SHIFT (0U)
#define PTPC_PTPC_ADDEND_ADDEND_SET(x) (((uint32_t)(x) << PTPC_PTPC_ADDEND_ADDEND_SHIFT) & PTPC_PTPC_ADDEND_ADDEND_MASK)
#define PTPC_PTPC_ADDEND_ADDEND_GET(x) (((uint32_t)(x) & PTPC_PTPC_ADDEND_ADDEND_MASK) >> PTPC_PTPC_ADDEND_ADDEND_SHIFT)

/* Bitfield definition for register of struct array PTPC: TARH */
/*
 * TARGET_TIME_HIGH (RW)
 *
 * used for generate compare signal if enabled
 */
#define PTPC_PTPC_TARH_TARGET_TIME_HIGH_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_TARH_TARGET_TIME_HIGH_SHIFT (0U)
#define PTPC_PTPC_TARH_TARGET_TIME_HIGH_SET(x) (((uint32_t)(x) << PTPC_PTPC_TARH_TARGET_TIME_HIGH_SHIFT) & PTPC_PTPC_TARH_TARGET_TIME_HIGH_MASK)
#define PTPC_PTPC_TARH_TARGET_TIME_HIGH_GET(x) (((uint32_t)(x) & PTPC_PTPC_TARH_TARGET_TIME_HIGH_MASK) >> PTPC_PTPC_TARH_TARGET_TIME_HIGH_SHIFT)

/* Bitfield definition for register of struct array PTPC: TARL */
/*
 * TARGET_TIME_LOW (RW)
 *
 */
#define PTPC_PTPC_TARL_TARGET_TIME_LOW_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_TARL_TARGET_TIME_LOW_SHIFT (0U)
#define PTPC_PTPC_TARL_TARGET_TIME_LOW_SET(x) (((uint32_t)(x) << PTPC_PTPC_TARL_TARGET_TIME_LOW_SHIFT) & PTPC_PTPC_TARL_TARGET_TIME_LOW_MASK)
#define PTPC_PTPC_TARL_TARGET_TIME_LOW_GET(x) (((uint32_t)(x) & PTPC_PTPC_TARL_TARGET_TIME_LOW_MASK) >> PTPC_PTPC_TARL_TARGET_TIME_LOW_SHIFT)

/* Bitfield definition for register of struct array PTPC: PPS_CTRL */
/*
 * PPS_CTRL (RW)
 *
 */
#define PTPC_PTPC_PPS_CTRL_PPS_CTRL_MASK (0xFU)
#define PTPC_PTPC_PPS_CTRL_PPS_CTRL_SHIFT (0U)
#define PTPC_PTPC_PPS_CTRL_PPS_CTRL_SET(x) (((uint32_t)(x) << PTPC_PTPC_PPS_CTRL_PPS_CTRL_SHIFT) & PTPC_PTPC_PPS_CTRL_PPS_CTRL_MASK)
#define PTPC_PTPC_PPS_CTRL_PPS_CTRL_GET(x) (((uint32_t)(x) & PTPC_PTPC_PPS_CTRL_PPS_CTRL_MASK) >> PTPC_PTPC_PPS_CTRL_PPS_CTRL_SHIFT)

/* Bitfield definition for register of struct array PTPC: CAPT_SNAPH */
/*
 * CAPT_SNAP_HIGH (RO)
 *
 * take snapshot for input capture signal, at pos or neg or both;
 * the result can be kept or updated at each event according to cfg0.bit8
 */
#define PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_SHIFT (0U)
#define PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_GET(x) (((uint32_t)(x) & PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_MASK) >> PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_SHIFT)

/* Bitfield definition for register of struct array PTPC: CAPT_SNAPL */
/*
 * CAPT_SNAP_LOW (RW)
 *
 */
#define PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_MASK (0xFFFFFFFFUL)
#define PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_SHIFT (0U)
#define PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_SET(x) (((uint32_t)(x) << PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_SHIFT) & PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_MASK)
#define PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_GET(x) (((uint32_t)(x) & PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_MASK) >> PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_SHIFT)

/* Bitfield definition for register: TIME_SEL */
/*
 * CAN3_TIME_SEL (RW)
 *
 */
#define PTPC_TIME_SEL_CAN3_TIME_SEL_MASK (0x8U)
#define PTPC_TIME_SEL_CAN3_TIME_SEL_SHIFT (3U)
#define PTPC_TIME_SEL_CAN3_TIME_SEL_SET(x) (((uint32_t)(x) << PTPC_TIME_SEL_CAN3_TIME_SEL_SHIFT) & PTPC_TIME_SEL_CAN3_TIME_SEL_MASK)
#define PTPC_TIME_SEL_CAN3_TIME_SEL_GET(x) (((uint32_t)(x) & PTPC_TIME_SEL_CAN3_TIME_SEL_MASK) >> PTPC_TIME_SEL_CAN3_TIME_SEL_SHIFT)

/*
 * CAN2_TIME_SEL (RW)
 *
 */
#define PTPC_TIME_SEL_CAN2_TIME_SEL_MASK (0x4U)
#define PTPC_TIME_SEL_CAN2_TIME_SEL_SHIFT (2U)
#define PTPC_TIME_SEL_CAN2_TIME_SEL_SET(x) (((uint32_t)(x) << PTPC_TIME_SEL_CAN2_TIME_SEL_SHIFT) & PTPC_TIME_SEL_CAN2_TIME_SEL_MASK)
#define PTPC_TIME_SEL_CAN2_TIME_SEL_GET(x) (((uint32_t)(x) & PTPC_TIME_SEL_CAN2_TIME_SEL_MASK) >> PTPC_TIME_SEL_CAN2_TIME_SEL_SHIFT)

/*
 * CAN1_TIME_SEL (RW)
 *
 */
#define PTPC_TIME_SEL_CAN1_TIME_SEL_MASK (0x2U)
#define PTPC_TIME_SEL_CAN1_TIME_SEL_SHIFT (1U)
#define PTPC_TIME_SEL_CAN1_TIME_SEL_SET(x) (((uint32_t)(x) << PTPC_TIME_SEL_CAN1_TIME_SEL_SHIFT) & PTPC_TIME_SEL_CAN1_TIME_SEL_MASK)
#define PTPC_TIME_SEL_CAN1_TIME_SEL_GET(x) (((uint32_t)(x) & PTPC_TIME_SEL_CAN1_TIME_SEL_MASK) >> PTPC_TIME_SEL_CAN1_TIME_SEL_SHIFT)

/*
 * CAN0_TIME_SEL (RW)
 *
 * set to use ptpc1 for canx
 * clr to use ptpc0 for canx
 */
#define PTPC_TIME_SEL_CAN0_TIME_SEL_MASK (0x1U)
#define PTPC_TIME_SEL_CAN0_TIME_SEL_SHIFT (0U)
#define PTPC_TIME_SEL_CAN0_TIME_SEL_SET(x) (((uint32_t)(x) << PTPC_TIME_SEL_CAN0_TIME_SEL_SHIFT) & PTPC_TIME_SEL_CAN0_TIME_SEL_MASK)
#define PTPC_TIME_SEL_CAN0_TIME_SEL_GET(x) (((uint32_t)(x) & PTPC_TIME_SEL_CAN0_TIME_SEL_MASK) >> PTPC_TIME_SEL_CAN0_TIME_SEL_SHIFT)

/* Bitfield definition for register: INT_STS */
/*
 * COMP_INT_STS1 (W1C)
 *
 */
#define PTPC_INT_STS_COMP_INT_STS1_MASK (0x40000UL)
#define PTPC_INT_STS_COMP_INT_STS1_SHIFT (18U)
#define PTPC_INT_STS_COMP_INT_STS1_SET(x) (((uint32_t)(x) << PTPC_INT_STS_COMP_INT_STS1_SHIFT) & PTPC_INT_STS_COMP_INT_STS1_MASK)
#define PTPC_INT_STS_COMP_INT_STS1_GET(x) (((uint32_t)(x) & PTPC_INT_STS_COMP_INT_STS1_MASK) >> PTPC_INT_STS_COMP_INT_STS1_SHIFT)

/*
 * CAPTURE_INT_STS1 (W1C)
 *
 */
#define PTPC_INT_STS_CAPTURE_INT_STS1_MASK (0x20000UL)
#define PTPC_INT_STS_CAPTURE_INT_STS1_SHIFT (17U)
#define PTPC_INT_STS_CAPTURE_INT_STS1_SET(x) (((uint32_t)(x) << PTPC_INT_STS_CAPTURE_INT_STS1_SHIFT) & PTPC_INT_STS_CAPTURE_INT_STS1_MASK)
#define PTPC_INT_STS_CAPTURE_INT_STS1_GET(x) (((uint32_t)(x) & PTPC_INT_STS_CAPTURE_INT_STS1_MASK) >> PTPC_INT_STS_CAPTURE_INT_STS1_SHIFT)

/*
 * PPS_INT_STS1 (W1C)
 *
 */
#define PTPC_INT_STS_PPS_INT_STS1_MASK (0x10000UL)
#define PTPC_INT_STS_PPS_INT_STS1_SHIFT (16U)
#define PTPC_INT_STS_PPS_INT_STS1_SET(x) (((uint32_t)(x) << PTPC_INT_STS_PPS_INT_STS1_SHIFT) & PTPC_INT_STS_PPS_INT_STS1_MASK)
#define PTPC_INT_STS_PPS_INT_STS1_GET(x) (((uint32_t)(x) & PTPC_INT_STS_PPS_INT_STS1_MASK) >> PTPC_INT_STS_PPS_INT_STS1_SHIFT)

/*
 * COMP_INT_STS0 (W1C)
 *
 */
#define PTPC_INT_STS_COMP_INT_STS0_MASK (0x4U)
#define PTPC_INT_STS_COMP_INT_STS0_SHIFT (2U)
#define PTPC_INT_STS_COMP_INT_STS0_SET(x) (((uint32_t)(x) << PTPC_INT_STS_COMP_INT_STS0_SHIFT) & PTPC_INT_STS_COMP_INT_STS0_MASK)
#define PTPC_INT_STS_COMP_INT_STS0_GET(x) (((uint32_t)(x) & PTPC_INT_STS_COMP_INT_STS0_MASK) >> PTPC_INT_STS_COMP_INT_STS0_SHIFT)

/*
 * CAPTURE_INT_STS0 (W1C)
 *
 */
#define PTPC_INT_STS_CAPTURE_INT_STS0_MASK (0x2U)
#define PTPC_INT_STS_CAPTURE_INT_STS0_SHIFT (1U)
#define PTPC_INT_STS_CAPTURE_INT_STS0_SET(x) (((uint32_t)(x) << PTPC_INT_STS_CAPTURE_INT_STS0_SHIFT) & PTPC_INT_STS_CAPTURE_INT_STS0_MASK)
#define PTPC_INT_STS_CAPTURE_INT_STS0_GET(x) (((uint32_t)(x) & PTPC_INT_STS_CAPTURE_INT_STS0_MASK) >> PTPC_INT_STS_CAPTURE_INT_STS0_SHIFT)

/*
 * PPS_INT_STS0 (W1C)
 *
 */
#define PTPC_INT_STS_PPS_INT_STS0_MASK (0x1U)
#define PTPC_INT_STS_PPS_INT_STS0_SHIFT (0U)
#define PTPC_INT_STS_PPS_INT_STS0_SET(x) (((uint32_t)(x) << PTPC_INT_STS_PPS_INT_STS0_SHIFT) & PTPC_INT_STS_PPS_INT_STS0_MASK)
#define PTPC_INT_STS_PPS_INT_STS0_GET(x) (((uint32_t)(x) & PTPC_INT_STS_PPS_INT_STS0_MASK) >> PTPC_INT_STS_PPS_INT_STS0_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * COMP_INT_STS1 (RW)
 *
 */
#define PTPC_INT_EN_COMP_INT_STS1_MASK (0x40000UL)
#define PTPC_INT_EN_COMP_INT_STS1_SHIFT (18U)
#define PTPC_INT_EN_COMP_INT_STS1_SET(x) (((uint32_t)(x) << PTPC_INT_EN_COMP_INT_STS1_SHIFT) & PTPC_INT_EN_COMP_INT_STS1_MASK)
#define PTPC_INT_EN_COMP_INT_STS1_GET(x) (((uint32_t)(x) & PTPC_INT_EN_COMP_INT_STS1_MASK) >> PTPC_INT_EN_COMP_INT_STS1_SHIFT)

/*
 * CAPTURE_INT_STS1 (RW)
 *
 */
#define PTPC_INT_EN_CAPTURE_INT_STS1_MASK (0x20000UL)
#define PTPC_INT_EN_CAPTURE_INT_STS1_SHIFT (17U)
#define PTPC_INT_EN_CAPTURE_INT_STS1_SET(x) (((uint32_t)(x) << PTPC_INT_EN_CAPTURE_INT_STS1_SHIFT) & PTPC_INT_EN_CAPTURE_INT_STS1_MASK)
#define PTPC_INT_EN_CAPTURE_INT_STS1_GET(x) (((uint32_t)(x) & PTPC_INT_EN_CAPTURE_INT_STS1_MASK) >> PTPC_INT_EN_CAPTURE_INT_STS1_SHIFT)

/*
 * PPS_INT_STS1 (RW)
 *
 */
#define PTPC_INT_EN_PPS_INT_STS1_MASK (0x10000UL)
#define PTPC_INT_EN_PPS_INT_STS1_SHIFT (16U)
#define PTPC_INT_EN_PPS_INT_STS1_SET(x) (((uint32_t)(x) << PTPC_INT_EN_PPS_INT_STS1_SHIFT) & PTPC_INT_EN_PPS_INT_STS1_MASK)
#define PTPC_INT_EN_PPS_INT_STS1_GET(x) (((uint32_t)(x) & PTPC_INT_EN_PPS_INT_STS1_MASK) >> PTPC_INT_EN_PPS_INT_STS1_SHIFT)

/*
 * COMP_INT_STS0 (RW)
 *
 */
#define PTPC_INT_EN_COMP_INT_STS0_MASK (0x4U)
#define PTPC_INT_EN_COMP_INT_STS0_SHIFT (2U)
#define PTPC_INT_EN_COMP_INT_STS0_SET(x) (((uint32_t)(x) << PTPC_INT_EN_COMP_INT_STS0_SHIFT) & PTPC_INT_EN_COMP_INT_STS0_MASK)
#define PTPC_INT_EN_COMP_INT_STS0_GET(x) (((uint32_t)(x) & PTPC_INT_EN_COMP_INT_STS0_MASK) >> PTPC_INT_EN_COMP_INT_STS0_SHIFT)

/*
 * CAPTURE_INT_STS0 (RW)
 *
 */
#define PTPC_INT_EN_CAPTURE_INT_STS0_MASK (0x2U)
#define PTPC_INT_EN_CAPTURE_INT_STS0_SHIFT (1U)
#define PTPC_INT_EN_CAPTURE_INT_STS0_SET(x) (((uint32_t)(x) << PTPC_INT_EN_CAPTURE_INT_STS0_SHIFT) & PTPC_INT_EN_CAPTURE_INT_STS0_MASK)
#define PTPC_INT_EN_CAPTURE_INT_STS0_GET(x) (((uint32_t)(x) & PTPC_INT_EN_CAPTURE_INT_STS0_MASK) >> PTPC_INT_EN_CAPTURE_INT_STS0_SHIFT)

/*
 * PPS_INT_STS0 (RW)
 *
 */
#define PTPC_INT_EN_PPS_INT_STS0_MASK (0x1U)
#define PTPC_INT_EN_PPS_INT_STS0_SHIFT (0U)
#define PTPC_INT_EN_PPS_INT_STS0_SET(x) (((uint32_t)(x) << PTPC_INT_EN_PPS_INT_STS0_SHIFT) & PTPC_INT_EN_PPS_INT_STS0_MASK)
#define PTPC_INT_EN_PPS_INT_STS0_GET(x) (((uint32_t)(x) & PTPC_INT_EN_PPS_INT_STS0_MASK) >> PTPC_INT_EN_PPS_INT_STS0_SHIFT)

/* Bitfield definition for register: PTPC_CAN_TS_SEL */
/*
 * TSU_TBIN3_SEL (RW)
 *
 */
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_MASK (0xFC000000UL)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_SHIFT (26U)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_SET(x) (((uint32_t)(x) << PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_SHIFT) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_MASK)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_GET(x) (((uint32_t)(x) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_MASK) >> PTPC_PTPC_CAN_TS_SEL_TSU_TBIN3_SEL_SHIFT)

/*
 * TSU_TBIN2_SEL (RW)
 *
 */
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_MASK (0x3F00000UL)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_SHIFT (20U)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_SET(x) (((uint32_t)(x) << PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_SHIFT) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_MASK)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_GET(x) (((uint32_t)(x) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_MASK) >> PTPC_PTPC_CAN_TS_SEL_TSU_TBIN2_SEL_SHIFT)

/*
 * TSU_TBIN1_SEL (RW)
 *
 */
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_MASK (0xFC000UL)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_SHIFT (14U)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_SET(x) (((uint32_t)(x) << PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_SHIFT) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_MASK)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_GET(x) (((uint32_t)(x) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_MASK) >> PTPC_PTPC_CAN_TS_SEL_TSU_TBIN1_SEL_SHIFT)

/*
 * TSU_TBIN0_SEL (RW)
 *
 */
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_MASK (0x3F00U)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_SHIFT (8U)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_SET(x) (((uint32_t)(x) << PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_SHIFT) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_MASK)
#define PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_GET(x) (((uint32_t)(x) & PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_MASK) >> PTPC_PTPC_CAN_TS_SEL_TSU_TBIN0_SEL_SHIFT)



/* PTPC register group index macro definition */
#define PTPC_PTPC_0 (0UL)
#define PTPC_PTPC_1 (1UL)


#endif /* HPM_PTPC_H */
