/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mcl_control.h"
#include "hpm_mcl_math.h"
#include "math.h"

#define SQRT3      (1.7320508075688773f)    /**< sqrt(3) */
#define SQRT3_DIV3 (0.5773502691896258f)    /**< sqrt(3)/3 */

float hpm_mcl_control_sin(float x)
{
    return sinf(x);
}

float hpm_mcl_control_cos(float x)
{
    return cosf(x);
}

float hpm_mcl_control_arctan(float y, float x)
{
    return atan2((double)y, (double)x);
}

hpm_mcl_stat_t hpm_mcl_control_clarke(float ia, float ib, float ic,
                    float *alpha, float *beta)
{
    (void)ic;
    MCL_ASSERT_OPT(alpha != NULL, mcl_invalid_pointer);
    MCL_ASSERT_OPT(beta != NULL, mcl_invalid_pointer);
    *alpha = ia;
    *beta = SQRT3_DIV3 * ia + (SQRT3_DIV3 * 2) * ib;

    return mcl_success;
}

hpm_mcl_stat_t hpm_mcl_control_park(float alpha, float beta, float sin_x, float cos_x,
                    float *d, float *q)
{
    MCL_ASSERT_OPT(d != NULL, mcl_invalid_pointer);
    MCL_ASSERT_OPT(q != NULL, mcl_invalid_pointer);
    *d = cos_x * alpha + sin_x * beta;
    *q = -sin_x * alpha + cos_x *beta;

    return mcl_success;
}

hpm_mcl_stat_t hpm_mcl_control_pi(float ref, float sens, mcl_control_pid_t *pid_x, float *output)
{
    float err;
    float val;

    MCL_ASSERT_OPT(output != NULL, mcl_invalid_pointer);
    err = ref - sens;
    pid_x->integral += pid_x->cfg.ki * err;
    MCL_VALUE_LIMIT(pid_x->integral, pid_x->cfg.integral_min, pid_x->cfg.integral_max);
    val = pid_x->cfg.kp * err + pid_x->integral;
    MCL_VALUE_LIMIT(val, pid_x->cfg.output_min, pid_x->cfg.output_max);
    *output = val;

    return mcl_success;
}

hpm_mcl_stat_t hpm_mcl_control_inv_park(float d, float q, float sin_x,
                        float cos_x, float *alpha, float *beta)
{
    MCL_ASSERT_OPT(alpha != NULL, mcl_invalid_pointer);
    MCL_ASSERT_OPT(beta != NULL, mcl_invalid_pointer);
    *alpha = cos_x * d - sin_x * q;
    *beta = sin_x * d + cos_x * q;

    return mcl_success;
}

hpm_mcl_stat_t hpm_mcl_control_svpwm(float alpha, float beta, float vbus, mcl_control_svpwm_duty_t *duty)
{
    float val0, val1;
    float val2, val3;
    float val4, val5, val6;
    mcl_svpwm_sector_t sector;

    MCL_ASSERT_OPT(duty != NULL, mcl_invalid_pointer);
    MCL_ASSERT(vbus != 0, mcl_invalid_argument);
    vbus = 1 / (vbus * 2 / 3);
    alpha = alpha * vbus;
    beta = beta * vbus;
    val0 = beta / alpha;
    val1 = alpha / beta;

    if (beta > 0) {
        if (alpha > 0) {
            if (val0 < SQRT3) {
                sector = svpwm_sector1;
            } else {
                sector = svpwm_sector2;
            }
        } else if (val1 > -SQRT3_DIV3) {
            sector = svpwm_sector2;
        } else {
            sector = svpwm_sector3;
        }
    } else if (alpha > 0) {
        if (val0 < -SQRT3) {
            sector = svpwm_sector5;
        } else {
            sector = svpwm_sector6;
        }
    } else if (val0 < SQRT3) {
        sector = svpwm_sector4;
    } else {
        sector = svpwm_sector5;
    }
    val2 = SQRT3_DIV3 * beta;
    val3 = SQRT3_DIV3 * 2 * beta;


    switch (sector) {
    case svpwm_sector1:
        val4 = (alpha - val2);
        val5 = (1 - val4 - val3) / 2;
        val4 += val5;
        val6 = val4 + val3;
        duty->a = val5;
        duty->b = val4;
        duty->c = val6;
        break;
    case svpwm_sector2:
        val4 = alpha + val2;
        val2 = val2 - alpha;
        val5 = (1 - val4 - val2) / 2;
        val2 += val5;
        val6 = val2 + val4;
        duty->a = val2;
        duty->b = val5;
        duty->c = val6;
        break;
    case svpwm_sector3:
        val4 = -alpha - val2;
        val5 = (1 - val4 - val3) / 2;
        val3 += val5;
        val6 = val3 + val4;
        duty->a = val6;
        duty->b = val5;
        duty->c = val3;
        break;
    case svpwm_sector4:
        val4 = val2 - alpha;
        val5 = (1 - val4 + val3) / 2;
        val3 = val5 - val3;
        val6 = val3 + val4;
        duty->a = val6;
        duty->b = val3;
        duty->c = val5;
        break;
    case svpwm_sector5:
        val4 = alpha - val2;
        val2 = -val2 - alpha;
        val5 = (1 - val4 - val2) / 2;
        val2 += val5;
        val6 = val2 + val4;
        duty->a = val2;
        duty->b = val6;
        duty->c = val5;
        break;
    case svpwm_sector6:
        val4 = val2 + alpha;
        val5 = (1 - val4 + val3) / 2;
        val4 += val5;
        val6 = val4 - val3;
        duty->a = val5;
        duty->b = val6;
        duty->c = val4;
        break;

    default:
        duty->a = 0;
        duty->b = 0;
        duty->c = 0;
        break;
    }

    MCL_VALUE_LIMIT(duty->a, 0, 1);
    MCL_VALUE_LIMIT(duty->b, 0, 1);
    MCL_VALUE_LIMIT(duty->c, 0, 1);

    return mcl_success;
}

hpm_mcl_stat_t hpm_mcl_control_step_svpwm(float alpha, float beta, float vbus, mcl_control_svpwm_duty_t *duty)
{
    float ta0on = 0, ta1on = 0, tb0on = 0, tb1on = 0;

    MCL_ASSERT_OPT(duty != NULL, mcl_invalid_pointer);
    MCL_ASSERT(vbus != 0, mcl_invalid_argument);
    vbus = 1 / (vbus * 2 / 3);
    alpha = alpha * vbus;
    beta = beta * vbus;

    if (alpha > 0) {
        ta1on = alpha;
    } else {
        ta0on = -alpha;
    }
    if (beta > 0) {
        tb1on = beta;
    } else {
        tb0on = -beta;
    }

    MCL_VALUE_LIMIT(ta0on, 0, 1);
    MCL_VALUE_LIMIT(ta1on, 0, 1);
    MCL_VALUE_LIMIT(tb0on, 0, 1);
    MCL_VALUE_LIMIT(tb1on, 0, 1);

    duty->a0 = ta0on;
    duty->a1 = ta1on;
    duty->b0 = tb0on;
    duty->b1 = tb1on;

    return mcl_success;
}

hpm_mcl_stat_t hpm_mcl_control_get_block_sector(hall_phase_t hall, uint8_t u, uint8_t v, uint8_t w, uint8_t *sector)
{
    const uint8_t hall_tbl_120[8] = {0, 4, 2, 3, 6, 5, 1, 0};
    const uint8_t hall_tbl_60[8] = {5, 4, 0, 3, 6, 0, 1, 2};

    if (hall == phase_120) {
        *sector = hall_tbl_120[(u<<2) | (v<<1) | w];
    } else if (hall == phase_60) {
        *sector = hall_tbl_60[(u<<2) | (v<<1) | w];
    } else {
        MCL_ASSERT(false, mcl_invalid_argument);
    }
    return mcl_success;
}

float hpm_mcl_control_lowpass_filter(float input, float *mem, float k)
{
    float output;

    output = k * input + (1 - k) * (*mem);
    *mem = output;

    return output;
}

hpm_mcl_stat_t hpm_mcl_control_dead_area_polarity_detection(mcl_control_dead_area_compensation_t *dead_area,
                float id, float iq, float theta,
                float deadtime, float ts, mcl_control_dead_area_pwm_offset_t *pwm_out)
{
    float out_d, out_q, sens_theta;
    int8_t ia = 0, ib = 0, ic = 0;

    out_q = hpm_mcl_control_lowpass_filter(iq, &dead_area->q_mem, dead_area->cfg.lowpass_k);
    out_d = hpm_mcl_control_lowpass_filter(id, &dead_area->d_mem, dead_area->cfg.lowpass_k);
    sens_theta = atan2f(out_q, out_d);
    theta += sens_theta;
    theta = MCL_ANGLE_MOD_X(0, MCL_2PI, theta);

    if ((theta >= (MCL_PI * (11.0f / 6))) || (theta < (MCL_PI * (1.0f / 6)))) {
        ia = 1;
        ib = -1;
        ic = -1;
    } else if ((theta >= (MCL_PI * (1.0f / 6))) && (theta < (MCL_PI * (1.0f / 2)))) {
        ia = 1;
        ib = 1;
        ic = -1;
    } else if ((theta >= (MCL_PI * (1.0f / 2))) && (theta < (MCL_PI * (5.0f / 6)))) {
        ia = -1;
        ib = 1;
        ic = -1;
    } else if ((theta >= (MCL_PI * (5.0f / 6))) && (theta < (MCL_PI * (7.0f / 6)))) {
        ia = -1;
        ib = 1;
        ic = 1;
    } else if ((theta >= (MCL_PI * (7.0f / 6))) && (theta < (MCL_PI * (3.0f / 2)))) {
        ia = -1;
        ib = -1;
        ic = 1;
    } else if ((theta >= (MCL_PI * (3.0f / 2))) && (theta < (MCL_PI * (11.0f / 6)))) {
        ia = 1;
        ib = -1;
        ic = 1;
    }
    pwm_out->a_offset = 2.0f * deadtime * ia / ts;
    pwm_out->b_offset = 2.0f * deadtime * ib / ts;
    pwm_out->c_offset = 2.0f * deadtime * ic / ts;

    return mcl_success;
}

void hpm_mcl_control_smc_init(mcl_control_smc_t *smc_cfg)
{
    smc_cfg->cfg.factor.smc_g = smc_cfg->cfg.const_data.sample_ts /
                                            smc_cfg->cfg.const_data.inductor;
    smc_cfg->cfg.factor.smc_f = 1 - (smc_cfg->cfg.const_data.res / smc_cfg->cfg.const_data.inductor)
                                            * smc_cfg->cfg.const_data.sample_ts;
}

void hpm_mcl_control_smc_process(mcl_control_smc_t *smc_cfg, float ualpha, float ubeta, float ialpha, float ibeta)
{
    float alhpa_err;
    float beta_err;
    float speed;
    float sens, ref;

    smc_cfg->ialpha_mem = smc_cfg->cfg.factor.smc_f *
                                        smc_cfg->ialpha_mem + smc_cfg->cfg.factor.smc_g *
                                        (ualpha - smc_cfg->alpha_cal - smc_cfg->zalpha_cal);
    smc_cfg->ibeta_mem = smc_cfg->cfg.factor.smc_f *
                                        smc_cfg->ibeta_mem + smc_cfg->cfg.factor.smc_g *
                                        (ubeta - smc_cfg->beta_cal - smc_cfg->zbeta_cal);

    alhpa_err = smc_cfg->ialpha_mem - ialpha;
    beta_err = smc_cfg->ibeta_mem - ibeta;

    if (fabs(alhpa_err) < smc_cfg->cfg.factor.zero) {
        smc_cfg->zalpha_cal = 2 * alhpa_err * smc_cfg->cfg.factor.ksmc;
    } else if (alhpa_err >= smc_cfg->cfg.factor.zero) {
        smc_cfg->zalpha_cal = smc_cfg->cfg.factor.ksmc;
    } else if (alhpa_err <= -smc_cfg->cfg.factor.zero) {
        smc_cfg->zalpha_cal = -smc_cfg->cfg.factor.ksmc;
    }

    if (fabs(beta_err) < smc_cfg->cfg.factor.zero) {
        smc_cfg->zbeta_cal = 2 * alhpa_err * smc_cfg->cfg.factor.ksmc;
    } else if (beta_err >= smc_cfg->cfg.factor.zero) {
        smc_cfg->zbeta_cal = smc_cfg->cfg.factor.ksmc;
    } else if (beta_err <= -smc_cfg->cfg.factor.zero) {
        smc_cfg->zbeta_cal = -smc_cfg->cfg.factor.ksmc;
    }

    smc_cfg->alpha_cal = (1 - smc_cfg->cfg.factor.filter_coeff) *
                                        smc_cfg->alpha_cal + smc_cfg->cfg.factor.filter_coeff *
                                        smc_cfg->zalpha_cal;

    smc_cfg->beta_cal = (1 - smc_cfg->cfg.factor.filter_coeff) *
                                        smc_cfg->beta_cal + smc_cfg->cfg.factor.filter_coeff *
                                        smc_cfg->zbeta_cal;
    ref = -smc_cfg->alpha_cal * cosf(smc_cfg->theta_mem);
    sens = smc_cfg->beta_cal * sinf(smc_cfg->theta_mem);
    hpm_mcl_control_pi(ref, sens, &smc_cfg->cfg.pll, &speed);
    smc_cfg->theta_mem += speed * smc_cfg->cfg.const_data.loop_ts;
    smc_cfg->theta_mem = MCL_ANGLE_MOD_X(0, MCL_2PI, smc_cfg->theta_mem);
    smc_cfg->theta = MCL_ANGLE_MOD_X(0, MCL_2PI, smc_cfg->theta_mem + smc_cfg->cfg.theta0);

}

hpm_mcl_stat_t hpm_mcl_control_init(mcl_control_t *control, mcl_control_cfg_t *cfg)
{
    MCL_ASSERT(control != NULL, mcl_invalid_pointer);
    MCL_ASSERT(cfg != NULL, mcl_invalid_pointer);

    /**
     * @brief Data initialisation
     *
     */
    control->cfg = cfg;
    control->cfg->currentd_pid_cfg.integral = 0;
    control->cfg->currentq_pid_cfg.integral = 0;
    control->cfg->position_pid_cfg.integral = 0;
    control->cfg->speed_pid_cfg.integral = 0;
    control->cfg->dead_area_compensation_cfg.d_mem = 0;
    control->cfg->dead_area_compensation_cfg.q_mem = 0;
    control->cfg->smc_cfg.ialpha_mem = 0;
    control->cfg->smc_cfg.ibeta_mem = 0;
    control->cfg->smc_cfg.cfg.pll.integral = 0;

    /**
     * @brief function initialisation
     *
     */
    control->method.arctan_x = &hpm_mcl_control_arctan;
    control->method.clarke = &hpm_mcl_control_clarke;
    control->method.cos_x = &hpm_mcl_control_cos;
    control->method.currentd_pid = &hpm_mcl_control_pi;
    control->method.currentq_pid = &hpm_mcl_control_pi;
    control->method.invpark = &hpm_mcl_control_inv_park;
    control->method.park = &hpm_mcl_control_park;
    control->method.position_pid = &hpm_mcl_control_pi;
    control->method.sin_x = &hpm_mcl_control_sin;
    control->method.speed_pid = &hpm_mcl_control_pi;
    control->method.svpwm = &hpm_mcl_control_svpwm;
    control->method.step_svpwm = &hpm_mcl_control_step_svpwm;
    control->method.get_block_sector = &hpm_mcl_control_get_block_sector;
    control->method.dead_area_polarity_detection = &hpm_mcl_control_dead_area_polarity_detection;
    control->method.smc_init = &hpm_mcl_control_smc_init;
    control->method.smc_process = &hpm_mcl_control_smc_process;
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.arctan_x, control->cfg->callback.method.arctan_x);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.clarke, control->cfg->callback.method.clarke);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.cos_x, control->cfg->callback.method.cos_x);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.currentd_pid, control->cfg->callback.method.currentd_pid);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.invpark, control->cfg->callback.method.invpark);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.park, control->cfg->callback.method.park);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.position_pid, control->cfg->callback.method.position_pid);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.sin_x, control->cfg->callback.method.sin_x);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.speed_pid, control->cfg->callback.method.speed_pid);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.svpwm, control->cfg->callback.method.svpwm);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.step_svpwm, control->cfg->callback.method.step_svpwm);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.get_block_sector, control->cfg->callback.method.get_block_sector);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.dead_area_polarity_detection, control->cfg->callback.method.dead_area_polarity_detection);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.smc_init, control->cfg->callback.method.smc_init);
    MCL_FUNCTION_INIT_IF_NO_EMPTY(control->method.smc_process, control->cfg->callback.method.smc_process);

    control->cfg->callback.init();

    return mcl_success;
}
