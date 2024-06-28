/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*
 * Note:
 *   PY and PZ IOs: if any SOC pin function needs to be routed to these IOs,
 *  besides of IOC, PIOC/BIOC needs to be configured SOC_GPIO_X_xx, so that
 *  expected SoC function can be enabled on these IOs.
 *
 */

#include "board.h"

void init_uart_pins(UART_Type *ptr)
{
    if (ptr == HPM_UART0) {
        HPM_IOC->PAD[IOC_PAD_PY07].FUNC_CTL = IOC_PY07_FUNC_CTL_UART0_RXD;
        HPM_IOC->PAD[IOC_PAD_PY06].FUNC_CTL = IOC_PY06_FUNC_CTL_UART0_TXD;
        /* PY port IO needs to configure PIOC as well */
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_SOC_PY_07;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_SOC_PY_06;
    } else if (ptr == HPM_UART6) {
        HPM_IOC->PAD[IOC_PAD_PE27].FUNC_CTL = IOC_PE27_FUNC_CTL_UART6_RXD;
        HPM_IOC->PAD[IOC_PAD_PE28].FUNC_CTL = IOC_PE28_FUNC_CTL_UART6_TXD;
    } else if (ptr == HPM_UART7) {
        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_UART7_RXD;
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_UART7_TXD;
    } else if (ptr == HPM_UART13) {
        HPM_IOC->PAD[IOC_PAD_PZ08].FUNC_CTL = IOC_PZ08_FUNC_CTL_UART13_RXD;
        HPM_IOC->PAD[IOC_PAD_PZ09].FUNC_CTL = IOC_PZ09_FUNC_CTL_UART13_TXD;
        /* PZ port IO needs to configure BIOC as well */
        HPM_BIOC->PAD[IOC_PAD_PZ08].FUNC_CTL = BIOC_PZ08_FUNC_CTL_SOC_PZ_08;
        HPM_BIOC->PAD[IOC_PAD_PZ09].FUNC_CTL = BIOC_PZ09_FUNC_CTL_SOC_PZ_09;
    } else if (ptr == HPM_UART14) {
        HPM_IOC->PAD[IOC_PAD_PZ10].FUNC_CTL = IOC_PZ10_FUNC_CTL_UART14_RXD;
        HPM_IOC->PAD[IOC_PAD_PZ11].FUNC_CTL = IOC_PZ11_FUNC_CTL_UART14_TXD;
        /* PZ port IO needs to configure BIOC as well */
        HPM_BIOC->PAD[IOC_PAD_PZ10].FUNC_CTL = BIOC_PZ10_FUNC_CTL_SOC_PZ_10;
        HPM_BIOC->PAD[IOC_PAD_PZ11].FUNC_CTL = BIOC_PZ11_FUNC_CTL_SOC_PZ_11;
    } else if (ptr == HPM_PUART) {
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_PUART_RXD;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_PUART_TXD;
    }
}

void init_uart_pin_as_gpio(UART_Type *ptr)
{
    if (ptr == HPM_UART7) {
        /* pull-up */
        HPM_IOC->PAD[IOC_PAD_PC02].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PC03].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_GPIO_C_02;
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_GPIO_C_03;
    } else if (ptr == HPM_UART13) {
        /* pull-up */
        HPM_IOC->PAD[IOC_PAD_PZ08].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PZ09].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

        /* PZ port IO needs to configure BIOC as well */
        HPM_IOC->PAD[IOC_PAD_PZ08].FUNC_CTL = IOC_PZ08_FUNC_CTL_GPIO_Z_08;
        HPM_BIOC->PAD[IOC_PAD_PZ08].FUNC_CTL = BIOC_PZ08_FUNC_CTL_SOC_PZ_08;

        /* PZ port IO needs to configure BIOC as well */
        HPM_IOC->PAD[IOC_PAD_PZ09].FUNC_CTL = IOC_PZ09_FUNC_CTL_GPIO_Z_09;
        HPM_BIOC->PAD[IOC_PAD_PZ09].FUNC_CTL = BIOC_PZ09_FUNC_CTL_SOC_PZ_09;
    }
}

void init_lcd_pins(LCDC_Type *ptr)
{
    (void)ptr;

    HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PB03_FUNC_CTL_DIS0_R_0;
    HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PB04_FUNC_CTL_DIS0_R_1;
    HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PB00_FUNC_CTL_DIS0_R_2;
    HPM_IOC->PAD[IOC_PAD_PA31].FUNC_CTL = IOC_PA31_FUNC_CTL_DIS0_R_3;
    HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_DIS0_R_4;
    HPM_IOC->PAD[IOC_PAD_PA21].FUNC_CTL = IOC_PA21_FUNC_CTL_DIS0_R_5;
    HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_DIS0_R_6;
    HPM_IOC->PAD[IOC_PAD_PA28].FUNC_CTL = IOC_PA28_FUNC_CTL_DIS0_R_7;
    HPM_IOC->PAD[IOC_PAD_PB06].FUNC_CTL = IOC_PB06_FUNC_CTL_DIS0_G_0;
    HPM_IOC->PAD[IOC_PAD_PB01].FUNC_CTL = IOC_PB01_FUNC_CTL_DIS0_G_1;
    HPM_IOC->PAD[IOC_PAD_PA22].FUNC_CTL = IOC_PA22_FUNC_CTL_DIS0_G_2;
    HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_DIS0_G_3;
    HPM_IOC->PAD[IOC_PAD_PA29].FUNC_CTL = IOC_PA29_FUNC_CTL_DIS0_G_4;
    HPM_IOC->PAD[IOC_PAD_PA24].FUNC_CTL = IOC_PA24_FUNC_CTL_DIS0_G_5;
    HPM_IOC->PAD[IOC_PAD_PA30].FUNC_CTL = IOC_PA30_FUNC_CTL_DIS0_G_6;
    HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PA25_FUNC_CTL_DIS0_G_7;
    HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PB05_FUNC_CTL_DIS0_B_0;
    HPM_IOC->PAD[IOC_PAD_PB07].FUNC_CTL = IOC_PB07_FUNC_CTL_DIS0_B_1;
    HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_DIS0_B_2;
    HPM_IOC->PAD[IOC_PAD_PA16].FUNC_CTL = IOC_PA16_FUNC_CTL_DIS0_B_3;
    HPM_IOC->PAD[IOC_PAD_PA12].FUNC_CTL = IOC_PA12_FUNC_CTL_DIS0_B_4;
    HPM_IOC->PAD[IOC_PAD_PA17].FUNC_CTL = IOC_PA17_FUNC_CTL_DIS0_B_5;
    HPM_IOC->PAD[IOC_PAD_PA13].FUNC_CTL = IOC_PA13_FUNC_CTL_DIS0_B_6;
    HPM_IOC->PAD[IOC_PAD_PA18].FUNC_CTL = IOC_PA18_FUNC_CTL_DIS0_B_7;
    HPM_IOC->PAD[IOC_PAD_PA20].FUNC_CTL = IOC_PA20_FUNC_CTL_DIS0_CLK;
    HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_DIS0_EN;
    HPM_IOC->PAD[IOC_PAD_PA19].FUNC_CTL = IOC_PA19_FUNC_CTL_DIS0_HSYNC;
    HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = IOC_PA14_FUNC_CTL_DIS0_VSYNC;

    /* PWM */
    HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_GPIO_B_23;
    /* PWR */
    HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PB12_FUNC_CTL_GPIO_B_12;
}

void init_cap_pins(void)
{
    /* CAP_INT */
    HPM_IOC->PAD[IOC_PAD_PB08].PAD_CTL = IOC_PAD_PAD_CTL_PE_MASK;
    HPM_IOC->PAD[IOC_PAD_PB08].FUNC_CTL = IOC_PB08_FUNC_CTL_GPIO_B_08;
    /* CAP_RST */
    HPM_IOC->PAD[IOC_PAD_PB09].PAD_CTL = IOC_PAD_PAD_CTL_PE_MASK;
    HPM_IOC->PAD[IOC_PAD_PB09].FUNC_CTL = IOC_PB09_FUNC_CTL_GPIO_B_09;
}

void init_trgmux_pins(uint32_t pin)
{
    /* all trgmux pin ALT_SELECT fixed to 16*/
    HPM_IOC->PAD[pin].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(16);
}

void init_i2c_pins_as_gpio(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        /* I2C0 */
        HPM_IOC->PAD[IOC_PAD_PB11].FUNC_CTL = IOC_PB11_FUNC_CTL_GPIO_B_11;
        HPM_IOC->PAD[IOC_PAD_PB10].FUNC_CTL = IOC_PB10_FUNC_CTL_GPIO_B_10;
    } else {
        while (1) {
        }
    }
}

void init_i2c_pins(I2C_Type *ptr)
{
    if (ptr == HPM_I2C0) {
        HPM_IOC->PAD[IOC_PAD_PB11].FUNC_CTL = IOC_PB11_FUNC_CTL_I2C0_SCL
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB10].FUNC_CTL = IOC_PB10_FUNC_CTL_I2C0_SDA
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB11].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
        HPM_IOC->PAD[IOC_PAD_PB10].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
    } else if (ptr == HPM_I2C3) {
        HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PB14_FUNC_CTL_I2C3_SCL
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PB13_FUNC_CTL_I2C3_SDA
                                            | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB14].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
        HPM_IOC->PAD[IOC_PAD_PB13].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
    } else {
        while (1) {
        }
    }
}

void init_sdram_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD13].FUNC_CTL = IOC_PD13_FUNC_CTL_FEMC_DQ_14;
    HPM_IOC->PAD[IOC_PAD_PD12].FUNC_CTL = IOC_PD12_FUNC_CTL_FEMC_DQ_15;
    HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PD10_FUNC_CTL_FEMC_DQ_12;
    HPM_IOC->PAD[IOC_PAD_PD09].FUNC_CTL = IOC_PD09_FUNC_CTL_FEMC_DQ_13;
    HPM_IOC->PAD[IOC_PAD_PD08].FUNC_CTL = IOC_PD08_FUNC_CTL_FEMC_DQ_00;
    HPM_IOC->PAD[IOC_PAD_PD07].FUNC_CTL = IOC_PD07_FUNC_CTL_FEMC_DQ_10;
    HPM_IOC->PAD[IOC_PAD_PD06].FUNC_CTL = IOC_PD06_FUNC_CTL_FEMC_DQ_11;
    HPM_IOC->PAD[IOC_PAD_PD05].FUNC_CTL = IOC_PD05_FUNC_CTL_FEMC_DQ_01;
    HPM_IOC->PAD[IOC_PAD_PD04].FUNC_CTL = IOC_PD04_FUNC_CTL_FEMC_DQ_08;
    HPM_IOC->PAD[IOC_PAD_PD03].FUNC_CTL = IOC_PD03_FUNC_CTL_FEMC_DQ_09;
    HPM_IOC->PAD[IOC_PAD_PD02].FUNC_CTL = IOC_PD02_FUNC_CTL_FEMC_DQ_04;
    HPM_IOC->PAD[IOC_PAD_PD01].FUNC_CTL = IOC_PD01_FUNC_CTL_FEMC_DQ_03;
    HPM_IOC->PAD[IOC_PAD_PD00].FUNC_CTL = IOC_PD00_FUNC_CTL_FEMC_DQ_02;
    HPM_IOC->PAD[IOC_PAD_PC29].FUNC_CTL = IOC_PC29_FUNC_CTL_FEMC_DQ_07;
    HPM_IOC->PAD[IOC_PAD_PC28].FUNC_CTL = IOC_PC28_FUNC_CTL_FEMC_DQ_06;
    HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_FEMC_DQ_05;

    HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PC21_FUNC_CTL_FEMC_A_11;
    HPM_IOC->PAD[IOC_PAD_PC17].FUNC_CTL = IOC_PC17_FUNC_CTL_FEMC_A_09;
    HPM_IOC->PAD[IOC_PAD_PC15].FUNC_CTL = IOC_PC15_FUNC_CTL_FEMC_A_10;
    HPM_IOC->PAD[IOC_PAD_PC12].FUNC_CTL = IOC_PC12_FUNC_CTL_FEMC_A_08;
    HPM_IOC->PAD[IOC_PAD_PC11].FUNC_CTL = IOC_PC11_FUNC_CTL_FEMC_A_07;
    HPM_IOC->PAD[IOC_PAD_PC10].FUNC_CTL = IOC_PC10_FUNC_CTL_FEMC_A_06;
    HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PC09_FUNC_CTL_FEMC_A_01;
    HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PC08_FUNC_CTL_FEMC_A_00;
    HPM_IOC->PAD[IOC_PAD_PC07].FUNC_CTL = IOC_PC07_FUNC_CTL_FEMC_A_05;
    HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PC06_FUNC_CTL_FEMC_A_04;
    HPM_IOC->PAD[IOC_PAD_PC05].FUNC_CTL = IOC_PC05_FUNC_CTL_FEMC_A_03;
    HPM_IOC->PAD[IOC_PAD_PC04].FUNC_CTL = IOC_PC04_FUNC_CTL_FEMC_A_02;

    HPM_IOC->PAD[IOC_PAD_PC14].FUNC_CTL = IOC_PC14_FUNC_CTL_FEMC_BA1;
    HPM_IOC->PAD[IOC_PAD_PC13].FUNC_CTL = IOC_PC13_FUNC_CTL_FEMC_BA0;
    HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PC16_FUNC_CTL_FEMC_DQS | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
    HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_FEMC_CLK;
    HPM_IOC->PAD[IOC_PAD_PC25].FUNC_CTL = IOC_PC25_FUNC_CTL_FEMC_CKE;
    HPM_IOC->PAD[IOC_PAD_PC19].FUNC_CTL = IOC_PC19_FUNC_CTL_FEMC_CS_0;
    HPM_IOC->PAD[IOC_PAD_PC18].FUNC_CTL = IOC_PC18_FUNC_CTL_FEMC_RAS;
    HPM_IOC->PAD[IOC_PAD_PC23].FUNC_CTL = IOC_PC23_FUNC_CTL_FEMC_CAS;
    HPM_IOC->PAD[IOC_PAD_PC24].FUNC_CTL = IOC_PC24_FUNC_CTL_FEMC_WE;
    HPM_IOC->PAD[IOC_PAD_PC30].FUNC_CTL = IOC_PC30_FUNC_CTL_FEMC_DM_0;
    HPM_IOC->PAD[IOC_PAD_PC31].FUNC_CTL = IOC_PC31_FUNC_CTL_FEMC_DM_1;
}

void init_sram_pins(void)
{
                                                                                /* Non-MUX */         /* MUX */
    HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A0 */            /* A16 */
    HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A1 */            /* A17 */
    HPM_IOC->PAD[IOC_PAD_PC04].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A2 */            /* A18 */
    HPM_IOC->PAD[IOC_PAD_PC05].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A3 */            /* A19 */
    HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A4 */            /* A20 */
    HPM_IOC->PAD[IOC_PAD_PC07].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A5 */            /* A21 */
    HPM_IOC->PAD[IOC_PAD_PC10].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A6 */            /* A22 */
    HPM_IOC->PAD[IOC_PAD_PC11].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A7 */            /* A23 */
    HPM_IOC->PAD[IOC_PAD_PC01].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A8 */
    HPM_IOC->PAD[IOC_PAD_PC00].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A9 */
    HPM_IOC->PAD[IOC_PAD_PB31].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A10 */
    HPM_IOC->PAD[IOC_PAD_PB28].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A11 */
    HPM_IOC->PAD[IOC_PAD_PB27].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A12 */
    HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A13 */
    HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A14 */
    HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A15 */
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A16 */
    HPM_IOC->PAD[IOC_PAD_PB18].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A17 */
    HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A18 */
    HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A19 */
    HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A20 */
    HPM_IOC->PAD[IOC_PAD_PB24].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A21 */
    HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A22 */
    HPM_IOC->PAD[IOC_PAD_PB29].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* A23 */

    HPM_IOC->PAD[IOC_PAD_PD08].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D0 */             /* AD0 */
    HPM_IOC->PAD[IOC_PAD_PD05].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D1 */             /* AD1 */
    HPM_IOC->PAD[IOC_PAD_PD00].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D2 */             /* AD2 */
    HPM_IOC->PAD[IOC_PAD_PD01].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D3 */             /* AD3 */
    HPM_IOC->PAD[IOC_PAD_PD02].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D4 */             /* AD4 */
    HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D5 */             /* AD5 */
    HPM_IOC->PAD[IOC_PAD_PC28].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D6 */             /* AD6 */
    HPM_IOC->PAD[IOC_PAD_PC29].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D7 */             /* AD7 */
    HPM_IOC->PAD[IOC_PAD_PD04].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D8 */             /* AD8 */
    HPM_IOC->PAD[IOC_PAD_PD03].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D9 */             /* AD9 */
    HPM_IOC->PAD[IOC_PAD_PD07].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D10 */            /* AD10 */
    HPM_IOC->PAD[IOC_PAD_PD06].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D11 */            /* AD11 */
    HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D12 */            /* AD12 */
    HPM_IOC->PAD[IOC_PAD_PD09].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D13 */            /* AD13 */
    HPM_IOC->PAD[IOC_PAD_PD13].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D14 */            /* AD14 */
    HPM_IOC->PAD[IOC_PAD_PD12].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* D15 */            /* AD15 */

    HPM_IOC->PAD[IOC_PAD_PC20].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* #CE */
    HPM_IOC->PAD[IOC_PAD_PC22].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* #OE */
    HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* #WE */
    HPM_IOC->PAD[IOC_PAD_PC31].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* #UB */
    HPM_IOC->PAD[IOC_PAD_PC30].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* #LB */
    HPM_IOC->PAD[IOC_PAD_PC14].FUNC_CTL = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(12);    /* #ADV */
}

void init_gpio_pins(void)
{
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

#ifdef USING_GPIO0_FOR_GPIOZ
    HPM_IOC->PAD[IOC_PAD_PZ02].FUNC_CTL = IOC_PZ02_FUNC_CTL_GPIO_Z_02;
    HPM_IOC->PAD[IOC_PAD_PZ02].PAD_CTL = pad_ctl;
    /* PZ port IO needs to configure BIOC as well */
    HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = BIOC_PZ02_FUNC_CTL_SOC_PZ_02;
#endif
}

void init_spi_pins(SPI_Type *ptr)
{
    if (ptr == HPM_SPI1) {
        HPM_IOC->PAD[IOC_PAD_PE03].FUNC_CTL = IOC_PE03_FUNC_CTL_SPI1_CSN;
        HPM_IOC->PAD[IOC_PAD_PE04].FUNC_CTL = IOC_PE04_FUNC_CTL_SPI1_MOSI;
        HPM_IOC->PAD[IOC_PAD_PD30].FUNC_CTL = IOC_PD30_FUNC_CTL_SPI1_MISO;
        HPM_IOC->PAD[IOC_PAD_PD31].FUNC_CTL = IOC_PD31_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    } else if (ptr == HPM_SPI2) {
        HPM_IOC->PAD[IOC_PAD_PB24].FUNC_CTL = IOC_PB24_FUNC_CTL_SPI2_CSN;
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_SPI2_MOSI;
        HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PB25_FUNC_CTL_SPI2_MISO;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_SPI2_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    } else if (ptr == HPM_SPI3) {
        HPM_IOC->PAD[IOC_PAD_PB29].FUNC_CTL = IOC_PB29_FUNC_CTL_SPI3_CSN;
        HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PB30_FUNC_CTL_SPI3_MOSI;
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_SPI3_MISO;
        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_SPI3_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    }
}

void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr)
{
    if (ptr == HPM_SPI1) {
        HPM_IOC->PAD[IOC_PAD_PE03].FUNC_CTL = IOC_PE03_FUNC_CTL_GPIO_E_03;
        HPM_IOC->PAD[IOC_PAD_PE04].FUNC_CTL = IOC_PE04_FUNC_CTL_SPI1_MOSI;
        HPM_IOC->PAD[IOC_PAD_PD30].FUNC_CTL = IOC_PD30_FUNC_CTL_SPI1_MISO;
        HPM_IOC->PAD[IOC_PAD_PD31].FUNC_CTL = IOC_PD31_FUNC_CTL_SPI1_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    } else if (ptr == HPM_SPI2) {
        HPM_IOC->PAD[IOC_PAD_PB24].FUNC_CTL = IOC_PB24_FUNC_CTL_GPIO_B_24;
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_SPI2_MOSI;
        HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PB25_FUNC_CTL_SPI2_MISO;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_SPI2_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    } else if (ptr == HPM_SPI3) {
        HPM_IOC->PAD[IOC_PAD_PB29].FUNC_CTL = IOC_PB29_FUNC_CTL_GPIO_B_29;
        HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PB30_FUNC_CTL_SPI3_MOSI;
        HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_SPI3_MISO;
        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_SPI3_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    }
}

void init_pins(void)
{
#ifdef BOARD_CONSOLE_UART_BASE
    init_uart_pins(BOARD_CONSOLE_UART_BASE);
#endif
    init_sdram_pins();
}

void init_gptmr_pins(GPTMR_Type *ptr)
{
    if (ptr == HPM_GPTMR5) {
        /* TMR5 capture 0 */
        HPM_IOC->PAD[IOC_PAD_PF06].FUNC_CTL = IOC_PF06_FUNC_CTL_GPTMR5_CAPT_1;
        /* TMR5 compare 0 */
        HPM_IOC->PAD[IOC_PAD_PF04].FUNC_CTL = IOC_PF04_FUNC_CTL_GPTMR5_COMP_0;
        /* TMR5 compare 1*/
        HPM_IOC->PAD[IOC_PAD_PF09].FUNC_CTL = IOC_PF09_FUNC_CTL_GPTMR5_COMP_1;
        /* TMR5 compare 2*/
        HPM_IOC->PAD[IOC_PAD_PD24].FUNC_CTL = IOC_PD24_FUNC_CTL_TRGM2_P_10;
        trgm_enable_io_output(HPM_TRGM2, 1 << 10);
        trgm_output_t trgm2IoConfig0;
        trgm2IoConfig0.invert = 0;
        trgm2IoConfig0.type = trgm_output_same_as_input;
        trgm2IoConfig0.input = HPM_TRGM2_INPUT_SRC_GPTMR5_OUT2;
        trgm_output_config(HPM_TRGM2, HPM_TRGM2_OUTPUT_SRC_TRGM2_P10, &trgm2IoConfig0);
    }
}

void init_hall_trgm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD19].FUNC_CTL = IOC_PD19_FUNC_CTL_TRGM2_P_09;
    HPM_IOC->PAD[IOC_PAD_PD23].FUNC_CTL = IOC_PD23_FUNC_CTL_TRGM2_P_11;
    HPM_IOC->PAD[IOC_PAD_PD24].FUNC_CTL = IOC_PD24_FUNC_CTL_TRGM2_P_10;
}

void init_qei_trgm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD16].FUNC_CTL = IOC_PD16_FUNC_CTL_TRGM2_P_06;
    HPM_IOC->PAD[IOC_PAD_PD20].FUNC_CTL = IOC_PD20_FUNC_CTL_TRGM2_P_07;
}

void init_i2s_pins(I2S_Type *ptr)
{
    if (ptr == HPM_I2S0) {
        HPM_IOC->PAD[IOC_PAD_PF03].FUNC_CTL = IOC_PF03_FUNC_CTL_I2S0_MCLK;
        HPM_IOC->PAD[IOC_PAD_PF09].FUNC_CTL = IOC_PF09_FUNC_CTL_I2S0_FCLK;
        HPM_IOC->PAD[IOC_PAD_PF06].FUNC_CTL = IOC_PF06_FUNC_CTL_I2S0_BCLK;
        HPM_IOC->PAD[IOC_PAD_PF05].FUNC_CTL = IOC_PF05_FUNC_CTL_I2S0_RXD_1;
        HPM_IOC->PAD[IOC_PAD_PF07].FUNC_CTL = IOC_PF07_FUNC_CTL_I2S0_TXD_1;
    }
}

void init_dao_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB15].FUNC_CTL = IOC_PB15_FUNC_CTL_DAOR_P;
    HPM_IOC->PAD[IOC_PAD_PB16].FUNC_CTL = IOC_PB16_FUNC_CTL_DAOR_N;
}

void init_pdm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PY10].FUNC_CTL = IOC_PY10_FUNC_CTL_PDM0_CLK;
    HPM_IOC->PAD[IOC_PAD_PY11].FUNC_CTL = IOC_PY11_FUNC_CTL_PDM0_D_0;
    /* PY port IO needs to configure PIOC as well */
    HPM_PIOC->PAD[IOC_PAD_PY10].FUNC_CTL = PIOC_PY10_FUNC_CTL_SOC_PY_10;
    HPM_PIOC->PAD[IOC_PAD_PY11].FUNC_CTL = PIOC_PY11_FUNC_CTL_SOC_PY_11;
}

void init_vad_pins(void)
{
    HPM_PIOC->PAD[IOC_PAD_PY10].FUNC_CTL = PIOC_PY10_FUNC_CTL_VAD_CLK;
    HPM_PIOC->PAD[IOC_PAD_PY11].FUNC_CTL = PIOC_PY11_FUNC_CTL_VAD_DAT;
}

void init_cam_pins(CAM_Type *ptr)
{
    if (ptr == HPM_CAM0) {
        HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_CAM0_XCLK;
        HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_CAM0_PIXCLK;
        HPM_IOC->PAD[IOC_PAD_PA06].FUNC_CTL = IOC_PA06_FUNC_CTL_CAM0_VSYNC;
        HPM_IOC->PAD[IOC_PAD_PA05].FUNC_CTL = IOC_PA05_FUNC_CTL_CAM0_HSYNC;
        HPM_IOC->PAD[IOC_PAD_PA07].FUNC_CTL = IOC_PA07_FUNC_CTL_CAM0_D_2;
        HPM_IOC->PAD[IOC_PAD_PA03].FUNC_CTL = IOC_PA03_FUNC_CTL_CAM0_D_3;
        HPM_IOC->PAD[IOC_PAD_PA08].FUNC_CTL = IOC_PA08_FUNC_CTL_CAM0_D_4;
        HPM_IOC->PAD[IOC_PAD_PA09].FUNC_CTL = IOC_PA09_FUNC_CTL_CAM0_D_5;
        HPM_IOC->PAD[IOC_PAD_PA00].FUNC_CTL = IOC_PA00_FUNC_CTL_CAM0_D_6;
        HPM_IOC->PAD[IOC_PAD_PA04].FUNC_CTL = IOC_PA04_FUNC_CTL_CAM0_D_7;
        HPM_IOC->PAD[IOC_PAD_PA01].FUNC_CTL = IOC_PA01_FUNC_CTL_CAM0_D_8;
        HPM_IOC->PAD[IOC_PAD_PA02].FUNC_CTL = IOC_PA02_FUNC_CTL_CAM0_D_9;
    }
}

void init_butn_pins(void)
{
    HPM_BIOC->PAD[IOC_PAD_PZ02].FUNC_CTL = BIOC_PZ02_FUNC_CTL_PBUTN;
    HPM_BIOC->PAD[IOC_PAD_PZ03].FUNC_CTL = BIOC_PZ03_FUNC_CTL_WBUTN;
    HPM_BIOC->PAD[IOC_PAD_PZ04].FUNC_CTL = BIOC_PZ04_FUNC_CTL_PLED;
    HPM_BIOC->PAD[IOC_PAD_PZ05].FUNC_CTL = BIOC_PZ05_FUNC_CTL_WLED;
}

void init_acmp_pins(void)
{
    /* configure to ACMP_COMP_1(ALT16) function */
    HPM_IOC->PAD[IOC_PAD_PE25].FUNC_CTL = IOC_PE25_FUNC_CTL_ACMP_COMP_1;
    /* configure to CMP1_INP7 function */
    HPM_IOC->PAD[IOC_PAD_PE23].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    /* configure to CMP1_INN6 function */
    HPM_IOC->PAD[IOC_PAD_PE21].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_enet_pins(ENET_Type *ptr)
{
    if (ptr == HPM_ENET1) {
        HPM_IOC->PAD[IOC_PAD_PD15].FUNC_CTL = IOC_PD15_FUNC_CTL_GPIO_D_15;

        HPM_IOC->PAD[IOC_PAD_PD11].FUNC_CTL = IOC_PD11_FUNC_CTL_ETH1_MDC;
        HPM_IOC->PAD[IOC_PAD_PD14].FUNC_CTL = IOC_PD14_FUNC_CTL_ETH1_MDIO;

        HPM_IOC->PAD[IOC_PAD_PE18].FUNC_CTL = IOC_PE18_FUNC_CTL_ETH1_RXD_1;
        HPM_IOC->PAD[IOC_PAD_PE19].FUNC_CTL = IOC_PE19_FUNC_CTL_ETH1_TXD_0;
        HPM_IOC->PAD[IOC_PAD_PE20].FUNC_CTL = IOC_PE20_FUNC_CTL_ETH1_RXD_0;

        HPM_IOC->PAD[IOC_PAD_PE14].FUNC_CTL = IOC_PE14_FUNC_CTL_ETH1_TXEN;
        HPM_IOC->PAD[IOC_PAD_PE15].FUNC_CTL = IOC_PE15_FUNC_CTL_ETH1_RXDV;
        HPM_IOC->PAD[IOC_PAD_PE17].FUNC_CTL = IOC_PE17_FUNC_CTL_ETH1_TXD_1;

        HPM_IOC->PAD[IOC_PAD_PE16].FUNC_CTL = IOC_PAD_FUNC_CTL_LOOP_BACK_MASK | IOC_PE16_FUNC_CTL_ETH1_REFCLK;
    }
}

void init_pwm_pins(PWM_Type *ptr)
{
    if (ptr == HPM_PWM0) {
        HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_PWM0_P_7;
        HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_PWM0_P_6;
        HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PB26_FUNC_CTL_PWM0_P_5;
        HPM_IOC->PAD[IOC_PAD_PB27].FUNC_CTL = IOC_PB27_FUNC_CTL_PWM0_P_4;
    } else if (ptr == HPM_PWM1) {
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_PWM1_P_3;
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_PWM1_P_2;
        HPM_IOC->PAD[IOC_PAD_PB24].FUNC_CTL = IOC_PB24_FUNC_CTL_PWM1_P_5;
        HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PB25_FUNC_CTL_PWM1_P_4;
        HPM_IOC->PAD[IOC_PAD_PB29].FUNC_CTL = IOC_PB29_FUNC_CTL_PWM1_P_7;
        HPM_IOC->PAD[IOC_PAD_PB30].FUNC_CTL = IOC_PB30_FUNC_CTL_PWM1_P_6;
    } else if (ptr == HPM_PWM3) {
        HPM_IOC->PAD[IOC_PAD_PE05].FUNC_CTL = IOC_PE05_FUNC_CTL_PWM3_P_4;
    }
}

void init_adc12_pins(void)
{
    /* ADC0.VINP14 */
    HPM_IOC->PAD[IOC_PAD_PE28].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_adc16_pins(void)
{
    /* ADC3.INA2 */
    HPM_IOC->PAD[IOC_PAD_PE29].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_adc_bldc_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PE15].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PE16].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PE17].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_usb_pins(USB_Type *ptr)
{
    if (ptr == HPM_USB0) {
        /* USB0 ID */
        HPM_IOC->PAD[IOC_PAD_PF10].FUNC_CTL = IOC_PF10_FUNC_CTL_GPIO_F_10;
        HPM_IOC->PAD[IOC_PAD_PF10].PAD_CTL = IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1);

        /* USB0 OC */
        HPM_IOC->PAD[IOC_PAD_PF08].FUNC_CTL = IOC_PF08_FUNC_CTL_GPIO_F_08;
        HPM_IOC->PAD[IOC_PAD_PF08].PAD_CTL = IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PE_SET(1);
    }
}

void init_can_pins(CAN_Type *ptr)
{
    if (ptr == HPM_CAN1) {
        HPM_IOC->PAD[IOC_PAD_PE31].FUNC_CTL = IOC_PE31_FUNC_CTL_CAN1_TXD;
        HPM_IOC->PAD[IOC_PAD_PE30].FUNC_CTL = IOC_PE30_FUNC_CTL_CAN1_RXD;
    }
}

void init_sdxc_cmd_pin(SDXC_Type *ptr, bool open_drain, bool is_1v8)
{
    uint32_t cmd_func_ctl = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(17) | IOC_PAD_FUNC_CTL_LOOP_BACK_SET(1);
    uint32_t cmd_pad_ctl = IOC_PAD_PAD_CTL_MS_SET(is_1v8) | IOC_PAD_PAD_CTL_DS_SET(6) | IOC_PAD_PAD_CTL_PE_SET(1) |
                           IOC_PAD_PAD_CTL_PS_SET(1);
    if (open_drain) {
        cmd_pad_ctl |= IOC_PAD_PAD_CTL_OD_MASK;
    }

    if (ptr == HPM_SDXC1) {
        /* SDXC1.CMD */
        HPM_IOC->PAD[IOC_PAD_PD21].FUNC_CTL = cmd_func_ctl;
        HPM_IOC->PAD[IOC_PAD_PD21].PAD_CTL = cmd_pad_ctl;
    }
}

void init_sdxc_cd_pin(SDXC_Type *ptr, bool as_gpio)
{
    uint32_t cd_pad_ctl = IOC_PAD_PAD_CTL_DS_SET(6) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    if (ptr == HPM_SDXC1) {
        /* SDXC1.CDN */
        uint32_t cd_func_alt = as_gpio ? IOC_PD28_FUNC_CTL_GPIO_D_28 : IOC_PD28_FUNC_CTL_SDC1_CDN;
        HPM_IOC->PAD[IOC_PAD_PD28].FUNC_CTL = cd_func_alt;
        HPM_IOC->PAD[IOC_PAD_PD28].PAD_CTL = cd_pad_ctl;
    }
}

void init_sdxc_vsel_pin(SDXC_Type *ptr, bool as_gpio)
{
    uint32_t vsel_pad_ctl = IOC_PAD_PAD_CTL_DS_SET(6) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    if (ptr == HPM_SDXC1) {
        uint32_t vsel_func_alt = as_gpio ? IOC_PD29_FUNC_CTL_GPIO_D_29 : IOC_PD29_FUNC_CTL_SDC1_VSEL;
        HPM_IOC->PAD[IOC_PAD_PD29].FUNC_CTL = vsel_func_alt;
        HPM_IOC->PAD[IOC_PAD_PD29].PAD_CTL = vsel_pad_ctl;
    }
}

void init_sdxc_clk_data_pins(SDXC_Type *ptr, uint32_t width, bool is_1v8)
{
    uint32_t func_ctl = IOC_PAD_FUNC_CTL_ALT_SELECT_SET(17);
    uint32_t pad_ctl = IOC_PAD_PAD_CTL_MS_SET(is_1v8) | IOC_PAD_PAD_CTL_DS_SET(6) | IOC_PAD_PAD_CTL_PE_SET(1) |
                       IOC_PAD_PAD_CTL_PS_SET(1);

    if (ptr == HPM_SDXC1) {
        /* SDXC1.CLK */
        HPM_IOC->PAD[IOC_PAD_PD22].FUNC_CTL = func_ctl;
        HPM_IOC->PAD[IOC_PAD_PD22].PAD_CTL = pad_ctl;

        /* SDXC1.DATA0 */
        HPM_IOC->PAD[IOC_PAD_PD18].FUNC_CTL = func_ctl;
        HPM_IOC->PAD[IOC_PAD_PD18].PAD_CTL = pad_ctl;
        if ((width == 4)) {
            /* SDXC1.DATA1 */
            HPM_IOC->PAD[IOC_PAD_PD17].FUNC_CTL = func_ctl;
            HPM_IOC->PAD[IOC_PAD_PD17].PAD_CTL = pad_ctl;
            /* SDXC1.DATA2 */
            HPM_IOC->PAD[IOC_PAD_PD27].FUNC_CTL = func_ctl;
            HPM_IOC->PAD[IOC_PAD_PD27].PAD_CTL = pad_ctl;
            /* SDXC1.DATA3 */
            HPM_IOC->PAD[IOC_PAD_PD26].FUNC_CTL = func_ctl;
            HPM_IOC->PAD[IOC_PAD_PD26].PAD_CTL = pad_ctl;
        }
    }

}

void init_clk_obs_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_SYSCTL_CLK_OBS_0;
}

void init_wifi_pins(void)
{
    /* WiFi INT */
    HPM_IOC->PAD[IOC_PAD_PE01].FUNC_CTL = IOC_PE01_FUNC_CTL_GPIO_E_01;
    HPM_IOC->PAD[IOC_PAD_PE01].PAD_CTL = IOC_PAD_PAD_CTL_PE_MASK | IOC_PAD_PAD_CTL_PS_MASK;
    /* WiFi RST */
    HPM_IOC->PAD[IOC_PAD_PE02].FUNC_CTL = IOC_PE02_FUNC_CTL_GPIO_E_02;

    init_spi_pins(HPM_SPI0);
}

void init_beep_pwm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PE05].FUNC_CTL = IOC_PE05_FUNC_CTL_PWM3_P_4;
}

void init_led_pins_as_pwm(void)
{
    /* Blue */
    HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_PWM0_P_7;
    /* Green */
    HPM_IOC->PAD[IOC_PAD_PB18].FUNC_CTL = IOC_PB18_FUNC_CTL_PWM1_P_1;
    /* Red */
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_PWM1_P_0;
}

void init_led_pins_as_gpio(void)
{
    HPM_IOC->PAD[IOC_PAD_PB18].FUNC_CTL = IOC_PB18_FUNC_CTL_GPIO_B_18;
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_GPIO_B_19;
    HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_GPIO_B_20;
}

void init_enet_pps_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PF05].FUNC_CTL = IOC_PF05_FUNC_CTL_ETH0_EVTO_0;
    HPM_IOC->PAD[IOC_PAD_PF06].FUNC_CTL = IOC_PF06_FUNC_CTL_ETH0_EVTO_1;
    HPM_IOC->PAD[IOC_PAD_PF09].FUNC_CTL = IOC_PF09_FUNC_CTL_ETH0_EVTO_2;
}

void init_tamper_pins(void)
{
    HPM_BIOC->PAD[IOC_PAD_PZ08].FUNC_CTL = BIOC_PZ08_FUNC_CTL_TAMP_08 | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
    HPM_BIOC->PAD[IOC_PAD_PZ09].FUNC_CTL = BIOC_PZ09_FUNC_CTL_TAMP_09;
    HPM_BIOC->PAD[IOC_PAD_PZ10].FUNC_CTL = BIOC_PZ10_FUNC_CTL_TAMP_10;
}

/* for uart_rx_line_status case, need to a gpio pin to sent break signal */
void init_uart_break_signal_pin(void)
{
    HPM_IOC->PAD[IOC_PAD_PB24].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PB24].FUNC_CTL = IOC_PB24_FUNC_CTL_GPIO_B_24;
}
