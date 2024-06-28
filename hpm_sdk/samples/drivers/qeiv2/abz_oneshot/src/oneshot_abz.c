/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_soc_feature.h"
#include "hpm_trgm_drv.h"
#include "hpm_qeiv2_drv.h"
#include "hpm_synt_drv.h"

#define PULSE0_NUM 64
#define PULSE1_NUM 128

#ifndef APP_QEI_BASE
#define APP_QEI_BASE BOARD_BLDC_QEIV2_BASE
#endif
#ifndef APP_QEI_IRQ
#define APP_QEI_IRQ  BOARD_BLDC_QEIV2_IRQ
#endif
#ifndef APP_MOTOR_CLK
#define APP_MOTOR_CLK BOARD_BLDC_QEI_CLOCK_SOURCE
#endif

static volatile bool s_pos_cmp_matched;
static volatile bool s_pulse0_matched;
static volatile bool s_pulse1_matched;
static volatile bool s_cycle0_matched;
static volatile bool s_cycle1_matched;
static volatile uint32_t z, ph, spd, tm, phcnt, pos, angle;
static volatile uint32_t pulse_snap0, pulse_snap1;
static volatile uint32_t cycle_snap0, cycle_snap1;


/* Static function declaration */
static void qeiv2_init(void);

/* Function definition */
int main(void)
{
    uint32_t speed;

    board_init();
    init_qeiv2_ab_pins(APP_QEI_BASE);
    synt_enable_timestamp(HPM_SYNT, true);
    qeiv2_init();

    printf("qeiv2 abz encoder example\n");

    for (uint32_t i = 0; i < 10; i++) {
        printf("z: 0x%x, phase: 0x%x\n", qeiv2_get_current_count(APP_QEI_BASE, qeiv2_counter_type_z), qeiv2_get_phase_cnt(APP_QEI_BASE));
    }

    while (1) {
        if (s_pos_cmp_matched) {
            s_pos_cmp_matched = false;
            z = qeiv2_get_count_on_read_event(APP_QEI_BASE, qeiv2_counter_type_z);
            ph = qeiv2_get_count_on_read_event(APP_QEI_BASE, qeiv2_counter_type_phase);
            spd = qeiv2_get_count_on_read_event(APP_QEI_BASE, qeiv2_counter_type_speed);
            tm = qeiv2_get_count_on_read_event(APP_QEI_BASE, qeiv2_counter_type_timer);
            phcnt = qeiv2_get_phase_cnt(APP_QEI_BASE);
            pos = qeiv2_get_postion(APP_QEI_BASE);
            angle = qeiv2_get_angle(APP_QEI_BASE);
            printf("pos_cmp_matched---z:%#x, phase:%#x, spd:%#x, tm:%#x, phase_cnt:%#x, pos:%#x, angle:%#x\n", z, ph, spd, tm, phcnt, pos, angle);
        }

        if (s_pulse0_matched) {
            s_pulse0_matched = false;
            cycle_snap0 = qeiv2_get_pulse0_cycle_snap0(APP_QEI_BASE);
            cycle_snap1 = qeiv2_get_pulse0_cycle_snap1(APP_QEI_BASE);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap0) * PULSE0_NUM * 360 / 4096;
            printf("pulse0 --- cycle_snap0: %#10x, spd: %d deg/s,\n", cycle_snap0, speed);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap1) * PULSE0_NUM * 360 / 4096;
            printf("pulse0 --- cycle_snap1: %#10x, spd: %d deg/s,\n", cycle_snap1, speed);
        }

        if (s_pulse1_matched) {
            s_pulse1_matched = false;
            cycle_snap0 = qeiv2_get_pulse1_cycle_snap0(APP_QEI_BASE);
            cycle_snap1 = qeiv2_get_pulse1_cycle_snap1(APP_QEI_BASE);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap0) * PULSE1_NUM * 360 / 4096;
            printf("pulse1 --- cycle_snap0: %#10x, spd: %d deg/s,\n", cycle_snap0, speed);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap1) * PULSE1_NUM * 360 / 4096;
            printf("pulse1 --- cycle_snap1: %#10x, spd: %d deg/s,\n", cycle_snap1, speed);
        }

        if (s_cycle0_matched) {
            s_cycle0_matched = false;
            pulse_snap0 = qeiv2_get_cycle0_pulse_snap0(APP_QEI_BASE);
            pulse_snap1 = qeiv2_get_cycle0_pulse_snap1(APP_QEI_BASE);
            cycle_snap0 = qeiv2_get_cycle0_pulse0cycle_snap0(APP_QEI_BASE);
            cycle_snap1 = qeiv2_get_cycle0_pulse0cycle_snap1(APP_QEI_BASE);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap0) * pulse_snap0 * 360 / 4096;
            printf("cycle0 --- pulse_snap0: %#10x, cylce_snap0: %#10x, spd : %d deg/s\n", pulse_snap0, cycle_snap0, speed);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap1) * pulse_snap1 * 360 / 4096;
            printf("cycle0 --- pulse_snap1: %#10x, cylce_snap1: %#10x, spd : %d deg/s\n", pulse_snap1, cycle_snap1, speed);
        }

        if (s_cycle1_matched) {
            s_cycle1_matched = false;
            pulse_snap0 = qeiv2_get_cycle1_pulse_snap0(APP_QEI_BASE);
            pulse_snap1 = qeiv2_get_cycle1_pulse_snap1(APP_QEI_BASE);
            cycle_snap0 = qeiv2_get_cycle1_pulse1cycle_snap0(APP_QEI_BASE);
            cycle_snap1 = qeiv2_get_cycle1_pulse1cycle_snap1(APP_QEI_BASE);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap0) * pulse_snap0 * 360 / 4096;
            printf("cycle1 --- pulse_snap0: %#10x, cylce_snap0: %#10x, spd : %d deg/s\n", pulse_snap0, cycle_snap0, speed);
            speed = (clock_get_frequency(APP_MOTOR_CLK) / cycle_snap1) * pulse_snap1 * 360 / 4096;
            printf("cycle1 --- pulse_snap1: %#10x, cylce_snap1: %#10x, spd : %d deg/s\n", pulse_snap1, cycle_snap1, speed);
        }
    }

    return 0;
}

void isr_qei(void)
{
    uint32_t status = qeiv2_get_status(APP_QEI_BASE);

    qeiv2_clear_status(APP_QEI_BASE, status);

    if ((status & QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK) != 0) {
        s_pos_cmp_matched = true;
    }

    if ((status & QEIV2_EVENT_PULSE0_FLAG_MASK) != 0) {
        s_pulse0_matched = true;
    }

    if ((status & QEIV2_EVENT_PULSE1_FLAG_MASK) != 0) {
        s_pulse1_matched = true;
    }

    if ((status & QEIV2_EVENT_CYCLE0_FLAG_MASK) != 0) {
        s_cycle0_matched = true;
    }

    if ((status & QEIV2_EVENT_CYCLE1_FLAG_MASK) != 0) {
        s_cycle1_matched = true;
    }
}
SDK_DECLARE_EXT_ISR_M(APP_QEI_IRQ, isr_qei)


static void qeiv2_init(void)
{
    qeiv2_phcnt_cmp_match_config_t phcnt_cmp_config = {0};
    qeiv2_reset_counter(APP_QEI_BASE);

    qeiv2_set_z_phase(APP_QEI_BASE, 0);
    qeiv2_set_phase_cnt(APP_QEI_BASE, 0);

    qeiv2_set_work_mode(APP_QEI_BASE, qeiv2_work_mode_abz);
    qeiv2_select_spd_tmr_register_content(APP_QEI_BASE, qeiv2_spd_tmr_as_spd_tm);
    qeiv2_config_z_phase_counter_mode(APP_QEI_BASE, qeiv2_z_count_inc_on_phase_count_max);
    qeiv2_config_phmax_phparam(APP_QEI_BASE, 4096);
    qeiv2_pause_pos_counter_on_fault(APP_QEI_BASE, true);
    qeiv2_config_abz_uvw_signal_edge(APP_QEI_BASE, true, true, false, true, true);

    intc_m_enable_irq_with_priority(APP_QEI_IRQ, 1);

    phcnt_cmp_config.phcnt_cmp_value = 4000;
    phcnt_cmp_config.ignore_rotate_dir = true;
    phcnt_cmp_config.ignore_zcmp = true;
    qeiv2_config_phcnt_cmp_match_condition(APP_QEI_BASE, &phcnt_cmp_config);
    qeiv2_enable_load_read_trigger_event(APP_QEI_BASE, QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK);
    qeiv2_enable_irq(APP_QEI_BASE, QEIV2_EVENT_POSITION_COMPARE_FLAG_MASK);

    qeiv2_enable_trig_pulse0(APP_QEI_BASE);
    qeiv2_set_pulse0_num(APP_QEI_BASE, PULSE0_NUM);

    qeiv2_disable_pulse0_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_pulse0_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_irq(APP_QEI_BASE, QEIV2_EVENT_PULSE0_FLAG_MASK);
    qeiv2_sw_restart_pulse0(APP_QEI_BASE);

    qeiv2_enable_trig_pulse1(APP_QEI_BASE);
    qeiv2_set_pulse1_num(APP_QEI_BASE, PULSE1_NUM);
    qeiv2_disable_pulse1_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_pulse1_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_irq(APP_QEI_BASE, QEIV2_EVENT_PULSE1_FLAG_MASK);
    qeiv2_sw_restart_pulse1(APP_QEI_BASE);

    qeiv2_enable_trig_cycle0(APP_QEI_BASE);
    qeiv2_set_cycle0_num(APP_QEI_BASE, 25000000);
    qeiv2_disable_cycle0_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_cycle0_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_irq(APP_QEI_BASE, QEIV2_EVENT_CYCLE0_FLAG_MASK);
    qeiv2_sw_restart_cycle0(APP_QEI_BASE);

    qeiv2_enable_trig_cycle1(APP_QEI_BASE);
    qeiv2_set_cycle1_num(APP_QEI_BASE, 25000000);
    qeiv2_disable_cycle1_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_cycle1_oneshot_mode(APP_QEI_BASE);
    qeiv2_enable_irq(APP_QEI_BASE, QEIV2_EVENT_CYCLE1_FLAG_MASK);
    qeiv2_sw_restart_cycle1(APP_QEI_BASE);

    qeiv2_release_counter(APP_QEI_BASE);

}
