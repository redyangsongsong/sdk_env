/*
 * Copyright (c) 2024 hpmicro
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
        HPM_IOC->PAD[IOC_PAD_PA00].FUNC_CTL = IOC_PA00_FUNC_CTL_UART0_TXD;
        HPM_IOC->PAD[IOC_PAD_PA01].FUNC_CTL = IOC_PA01_FUNC_CTL_UART0_RXD;
    } else if (ptr == HPM_UART4) {
        HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_SOC_PY_00;
        HPM_IOC->PAD[IOC_PAD_PY00].FUNC_CTL = IOC_PY00_FUNC_CTL_UART4_TXD;
        /* pull-up */
        HPM_IOC->PAD[IOC_PAD_PY01].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_SOC_PY_01;
        HPM_IOC->PAD[IOC_PAD_PY01].FUNC_CTL = IOC_PY01_FUNC_CTL_UART4_RXD;
    } else if (ptr == HPM_PUART) {
        HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_PURT_TXD;
        HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_PURT_RXD;
    } else {
        ;
    }
}

/* for uart_lin case, need to configure pin as gpio to sent break signal */
void init_uart_pin_as_gpio(UART_Type *ptr)
{
    if (ptr == BOARD_UART_LIN) {
        /* pull-up */
        HPM_IOC->PAD[IOC_PAD_PY00].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PY01].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);

        HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_SOC_PY_00;
        HPM_IOC->PAD[IOC_PAD_PY00].FUNC_CTL = IOC_PY00_FUNC_CTL_GPIO_Y_00;

        HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_SOC_PY_01;
        HPM_IOC->PAD[IOC_PAD_PY01].FUNC_CTL = IOC_PY01_FUNC_CTL_GPIO_Y_01;
    }
}

void init_i2c_pins(I2C_Type *ptr)
{
    if (ptr == HPM_I2C3) {  /* Codec */
        HPM_IOC->PAD[IOC_PAD_PB07].FUNC_CTL = IOC_PB07_FUNC_CTL_I2C3_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PB06].FUNC_CTL = IOC_PB06_FUNC_CTL_I2C3_SDA;
        HPM_IOC->PAD[IOC_PAD_PB07].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
        HPM_IOC->PAD[IOC_PAD_PB06].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
    } else if (ptr == HPM_I2C1) {
        HPM_IOC->PAD[IOC_PAD_PC29].FUNC_CTL = IOC_PC29_FUNC_CTL_I2C1_SCL | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PC28].FUNC_CTL = IOC_PC28_FUNC_CTL_I2C1_SDA;
        HPM_IOC->PAD[IOC_PAD_PC29].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
        HPM_IOC->PAD[IOC_PAD_PC28].PAD_CTL = IOC_PAD_PAD_CTL_OD_MASK;
    } else {
        ;
    }
}

void init_femc_pins(void)
{
    uint32_t pad_ctl;

    HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PB00_FUNC_CTL_FEMC_A_00;
    HPM_IOC->PAD[IOC_PAD_PB01].FUNC_CTL = IOC_PB01_FUNC_CTL_FEMC_A_01;
    HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_FEMC_A_02;
    HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PB03_FUNC_CTL_FEMC_A_03;
    HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PB04_FUNC_CTL_FEMC_A_04;
    HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PB05_FUNC_CTL_FEMC_A_05;
    HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PB12_FUNC_CTL_FEMC_A_06;
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PB13_FUNC_CTL_FEMC_A_07;
    HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PB14_FUNC_CTL_FEMC_A_08;
    HPM_IOC->PAD[IOC_PAD_PB15].FUNC_CTL = IOC_PB15_FUNC_CTL_FEMC_A_09;
    HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_FEMC_A_10;
    HPM_IOC->PAD[IOC_PAD_PB16].FUNC_CTL = IOC_PB16_FUNC_CTL_FEMC_A_11;      /* SRAM: NWE */
    HPM_IOC->PAD[IOC_PAD_PB17].FUNC_CTL = IOC_PB17_FUNC_CTL_FEMC_A_12;      /* SRAM: NOE */

    HPM_IOC->PAD[IOC_PAD_PC12].FUNC_CTL = IOC_PC12_FUNC_CTL_FEMC_DQ_00;
    HPM_IOC->PAD[IOC_PAD_PC13].FUNC_CTL = IOC_PC13_FUNC_CTL_FEMC_DQ_01;
    HPM_IOC->PAD[IOC_PAD_PC14].FUNC_CTL = IOC_PC14_FUNC_CTL_FEMC_DQ_02;
    HPM_IOC->PAD[IOC_PAD_PC15].FUNC_CTL = IOC_PC15_FUNC_CTL_FEMC_DQ_03;
    HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PC16_FUNC_CTL_FEMC_DQ_04;
    HPM_IOC->PAD[IOC_PAD_PC17].FUNC_CTL = IOC_PC17_FUNC_CTL_FEMC_DQ_05;
    HPM_IOC->PAD[IOC_PAD_PC18].FUNC_CTL = IOC_PC18_FUNC_CTL_FEMC_DQ_06;
    HPM_IOC->PAD[IOC_PAD_PC19].FUNC_CTL = IOC_PC19_FUNC_CTL_FEMC_DQ_07;
    HPM_IOC->PAD[IOC_PAD_PC04].FUNC_CTL = IOC_PC04_FUNC_CTL_FEMC_DQ_08;
    HPM_IOC->PAD[IOC_PAD_PC05].FUNC_CTL = IOC_PC05_FUNC_CTL_FEMC_DQ_09;
    HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PC06_FUNC_CTL_FEMC_DQ_10;
    HPM_IOC->PAD[IOC_PAD_PC07].FUNC_CTL = IOC_PC07_FUNC_CTL_FEMC_DQ_11;
    HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PC08_FUNC_CTL_FEMC_DQ_12;
    HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PC09_FUNC_CTL_FEMC_DQ_13;
    HPM_IOC->PAD[IOC_PAD_PC10].FUNC_CTL = IOC_PC10_FUNC_CTL_FEMC_DQ_14;
    HPM_IOC->PAD[IOC_PAD_PC11].FUNC_CTL = IOC_PC11_FUNC_CTL_FEMC_DQ_15;

    /* Improve DQ pins driver strength */
    pad_ctl = IOC_PAD_PAD_CTL_SR_SET(1) | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_DS_SET(4);
    HPM_IOC->PAD[IOC_PAD_PC12].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC13].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC14].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC15].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC16].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC17].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC18].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC19].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC04].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC05].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC06].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC07].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC08].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC09].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC10].PAD_CTL = pad_ctl;
    HPM_IOC->PAD[IOC_PAD_PC11].PAD_CTL = pad_ctl;

    HPM_IOC->PAD[IOC_PAD_PC20].FUNC_CTL = IOC_PC20_FUNC_CTL_FEMC_DM_0;     /* SRAM: NLB */
    HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_FEMC_DM_1;     /* SRAM: NUB */

    HPM_IOC->PAD[IOC_PAD_PA13].FUNC_CTL = IOC_PA13_FUNC_CTL_FEMC_BA0;
    HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = IOC_PA14_FUNC_CTL_FEMC_BA1;      /* SRAM: NADV */

    /* SDRAM */
    HPM_IOC->PAD[IOC_PAD_PA12].FUNC_CTL = IOC_PA12_FUNC_CTL_FEMC_CS_0;
/*  HPM_IOC->PAD[IOC_PAD_PA08].FUNC_CTL = IOC_PA08_FUNC_CTL_FEMC_CS_1; */    /* JTAG */       /* SRAM: CS0 */
    HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_FEMC_CAS;
    HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_FEMC_RAS;
    HPM_IOC->PAD[IOC_PAD_PB18].FUNC_CTL = IOC_PB18_FUNC_CTL_FEMC_CKE;
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_FEMC_CLK_0;
    HPM_IOC->PAD[IOC_PAD_PA09].FUNC_CTL = IOC_PA09_FUNC_CTL_FEMC_WE;

    HPM_IOC->PAD[IOC_PAD_PB28].FUNC_CTL = IOC_PB28_FUNC_CTL_FEMC_DQS | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;

    /* SRAM */
/*  HPM_IOC->PAD[IOC_PAD_PA06].FUNC_CTL = IOC_PA06_FUNC_CTL_FEMC_SCLK_0; */    /* JTAG */
    HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_FEMC_SCLK_1;
/*  HPM_IOC->PAD[IOC_PAD_PA07].FUNC_CTL = IOC_PA07_FUNC_CTL_FEMC_SCS_0; */     /* JTAG */     /* SRAM: CS1 */
    HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_FEMC_SCS_1;                       /* SRAM: CS2 */
    HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PC21_FUNC_CTL_FEMC_SRDY;
}

void init_ppi_pins(void)
{
    /* DQ */
    HPM_IOC->PAD[IOC_PAD_PC12].FUNC_CTL = IOC_PC12_FUNC_CTL_PPI0_DQ_00;
    HPM_IOC->PAD[IOC_PAD_PC13].FUNC_CTL = IOC_PC13_FUNC_CTL_PPI0_DQ_01;
    HPM_IOC->PAD[IOC_PAD_PC14].FUNC_CTL = IOC_PC14_FUNC_CTL_PPI0_DQ_02;
    HPM_IOC->PAD[IOC_PAD_PC15].FUNC_CTL = IOC_PC15_FUNC_CTL_PPI0_DQ_03;
    HPM_IOC->PAD[IOC_PAD_PC16].FUNC_CTL = IOC_PC16_FUNC_CTL_PPI0_DQ_04;
    HPM_IOC->PAD[IOC_PAD_PC17].FUNC_CTL = IOC_PC17_FUNC_CTL_PPI0_DQ_05;
    HPM_IOC->PAD[IOC_PAD_PC18].FUNC_CTL = IOC_PC18_FUNC_CTL_PPI0_DQ_06;
    HPM_IOC->PAD[IOC_PAD_PC19].FUNC_CTL = IOC_PC19_FUNC_CTL_PPI0_DQ_07;
    HPM_IOC->PAD[IOC_PAD_PC04].FUNC_CTL = IOC_PC04_FUNC_CTL_PPI0_DQ_08;
    HPM_IOC->PAD[IOC_PAD_PC05].FUNC_CTL = IOC_PC05_FUNC_CTL_PPI0_DQ_09;
    HPM_IOC->PAD[IOC_PAD_PC06].FUNC_CTL = IOC_PC06_FUNC_CTL_PPI0_DQ_10;
    HPM_IOC->PAD[IOC_PAD_PC07].FUNC_CTL = IOC_PC07_FUNC_CTL_PPI0_DQ_11;
    HPM_IOC->PAD[IOC_PAD_PC08].FUNC_CTL = IOC_PC08_FUNC_CTL_PPI0_DQ_12;
    HPM_IOC->PAD[IOC_PAD_PC09].FUNC_CTL = IOC_PC09_FUNC_CTL_PPI0_DQ_13;
    HPM_IOC->PAD[IOC_PAD_PC10].FUNC_CTL = IOC_PC10_FUNC_CTL_PPI0_DQ_14;
    HPM_IOC->PAD[IOC_PAD_PC11].FUNC_CTL = IOC_PC11_FUNC_CTL_PPI0_DQ_15;
    HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PB00_FUNC_CTL_PPI0_DQ_16;
    HPM_IOC->PAD[IOC_PAD_PB01].FUNC_CTL = IOC_PB01_FUNC_CTL_PPI0_DQ_17;
    HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_PPI0_DQ_18;
    HPM_IOC->PAD[IOC_PAD_PB03].FUNC_CTL = IOC_PB03_FUNC_CTL_PPI0_DQ_19;
    HPM_IOC->PAD[IOC_PAD_PB04].FUNC_CTL = IOC_PB04_FUNC_CTL_PPI0_DQ_20;
    HPM_IOC->PAD[IOC_PAD_PB05].FUNC_CTL = IOC_PB05_FUNC_CTL_PPI0_DQ_21;
    HPM_IOC->PAD[IOC_PAD_PB12].FUNC_CTL = IOC_PB12_FUNC_CTL_PPI0_DQ_22;
    HPM_IOC->PAD[IOC_PAD_PB13].FUNC_CTL = IOC_PB13_FUNC_CTL_PPI0_DQ_23;
    HPM_IOC->PAD[IOC_PAD_PB14].FUNC_CTL = IOC_PB14_FUNC_CTL_PPI0_DQ_24;
    HPM_IOC->PAD[IOC_PAD_PB15].FUNC_CTL = IOC_PB15_FUNC_CTL_PPI0_DQ_25;
    HPM_IOC->PAD[IOC_PAD_PA15].FUNC_CTL = IOC_PA15_FUNC_CTL_PPI0_DQ_26;
    HPM_IOC->PAD[IOC_PAD_PB16].FUNC_CTL = IOC_PB16_FUNC_CTL_PPI0_DQ_27;
    HPM_IOC->PAD[IOC_PAD_PB17].FUNC_CTL = IOC_PB17_FUNC_CTL_PPI0_DQ_28;
/*  HPM_IOC->PAD[IOC_PAD_PA06].FUNC_CTL = IOC_PA06_FUNC_CTL_PPI0_DQ_29; */    /* JTAG */
/*  HPM_IOC->PAD[IOC_PAD_PA07].FUNC_CTL = IOC_PA07_FUNC_CTL_PPI0_DQ_30; */    /* JTAG */
    HPM_IOC->PAD[IOC_PAD_PB18].FUNC_CTL = IOC_PB18_FUNC_CTL_PPI0_DQ_31;

    /* DM */
    HPM_IOC->PAD[IOC_PAD_PC20].FUNC_CTL = IOC_PC20_FUNC_CTL_PPI0_DM_0;
    HPM_IOC->PAD[IOC_PAD_PC03].FUNC_CTL = IOC_PC03_FUNC_CTL_PPI0_DM_1;
    HPM_IOC->PAD[IOC_PAD_PA10].FUNC_CTL = IOC_PA10_FUNC_CTL_PPI0_DM_2;
    HPM_IOC->PAD[IOC_PAD_PA11].FUNC_CTL = IOC_PA11_FUNC_CTL_PPI0_DM_3;

    /* CS */
    HPM_IOC->PAD[IOC_PAD_PA12].FUNC_CTL = IOC_PA12_FUNC_CTL_PPI0_CS_0;
/*  HPM_IOC->PAD[IOC_PAD_PA08].FUNC_CTL = IOC_PA08_FUNC_CTL_PPI0_CS_1; */    /* JTAG */
    HPM_IOC->PAD[IOC_PAD_PA14].FUNC_CTL = IOC_PA14_FUNC_CTL_PPI0_CS_2;
    HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_PPI0_CS_3;

    /* CTRL */
    HPM_IOC->PAD[IOC_PAD_PC21].FUNC_CTL = IOC_PC21_FUNC_CTL_PPI0_CTR_0;
    HPM_IOC->PAD[IOC_PAD_PB20].FUNC_CTL = IOC_PB20_FUNC_CTL_PPI0_CTR_1;
    HPM_IOC->PAD[IOC_PAD_PA09].FUNC_CTL = IOC_PA09_FUNC_CTL_PPI0_CTR_2;
    HPM_IOC->PAD[IOC_PAD_PA13].FUNC_CTL = IOC_PA13_FUNC_CTL_PPI0_CTR_3;
    HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_PPI0_CTR_4;
    HPM_IOC->PAD[IOC_PAD_PB27].FUNC_CTL = IOC_PB27_FUNC_CTL_PPI0_CTR_5;
    HPM_IOC->PAD[IOC_PAD_PB26].FUNC_CTL = IOC_PB26_FUNC_CTL_PPI0_CTR_6;
    HPM_IOC->PAD[IOC_PAD_PB25].FUNC_CTL = IOC_PB25_FUNC_CTL_PPI0_CTR_7;

    /* CLK */
    HPM_IOC->PAD[IOC_PAD_PB19].FUNC_CTL = IOC_PB19_FUNC_CTL_PPI0_CLK;
}

void init_sdm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PC00].FUNC_CTL = IOC_PC00_FUNC_CTL_SDM0_CLK_0;
    HPM_IOC->PAD[IOC_PAD_PC01].FUNC_CTL = IOC_PC01_FUNC_CTL_SDM0_DAT_0;
}

/* board PWM provide clock to SDM sensor */
void init_pwm_pin_as_sdm_clock(void)
{
    HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_PWM0_P_2;
}

void init_gpio_pins(void)
{
    /* configure pad setting: pull enable and pull up, schmitt trigger enable */
    /* enable schmitt trigger to eliminate jitter of pin used as button */

    /* Button */
    HPM_IOC->PAD[IOC_PAD_PC23].FUNC_CTL = IOC_PC23_FUNC_CTL_GPIO_C_23;
    HPM_IOC->PAD[IOC_PAD_PC23].PAD_CTL = IOC_PAD_PAD_CTL_HYS_SET(1) | IOC_PAD_PAD_CTL_OD_SET(1);
}

void init_butn_pins(void)
{
    /* configure pad setting: pull enable and pull up, schmitt trigger enable */
    /* enable schmitt trigger to eliminate jitter of pin used as button */

    /* Button */
    HPM_IOC->PAD[IOC_PAD_PC23].FUNC_CTL = IOC_PC23_FUNC_CTL_GPIO_C_23;
    HPM_IOC->PAD[IOC_PAD_PC23].PAD_CTL = IOC_PAD_PAD_CTL_HYS_SET(1) | IOC_PAD_PAD_CTL_OD_SET(1);
}

void init_spi_pins(SPI_Type *ptr)
{
    if (ptr == HPM_SPI2) {
        HPM_IOC->PAD[IOC_PAD_PY05].FUNC_CTL = IOC_PY05_FUNC_CTL_SPI2_CS_0;
        HPM_IOC->PAD[IOC_PAD_PY04].FUNC_CTL = IOC_PY04_FUNC_CTL_SPI2_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PY06].FUNC_CTL = IOC_PY06_FUNC_CTL_SPI2_MISO;
        HPM_IOC->PAD[IOC_PAD_PY07].FUNC_CTL = IOC_PY07_FUNC_CTL_SPI2_MOSI;
        HPM_PIOC->PAD[IOC_PAD_PY05].FUNC_CTL = PIOC_PY05_FUNC_CTL_SOC_PY_05;
        HPM_PIOC->PAD[IOC_PAD_PY04].FUNC_CTL = PIOC_PY04_FUNC_CTL_SOC_PY_04;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_SOC_PY_06;
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_SOC_PY_07;

        /* set max frequency slew rate(200M) */
        HPM_IOC->PAD[IOC_PAD_PY05].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PRS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PY04].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PY06].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PY07].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
    }
}

void init_spi_pins_with_gpio_as_cs(SPI_Type *ptr)
{
    if (ptr == HPM_SPI2) {
        HPM_IOC->PAD[IOC_PAD_PY05].FUNC_CTL = IOC_PY05_FUNC_CTL_GPIO_Y_05;
        HPM_IOC->PAD[IOC_PAD_PY04].FUNC_CTL = IOC_PY04_FUNC_CTL_SPI2_SCLK | IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
        HPM_IOC->PAD[IOC_PAD_PY06].FUNC_CTL = IOC_PY06_FUNC_CTL_SPI2_MISO;
        HPM_IOC->PAD[IOC_PAD_PY07].FUNC_CTL = IOC_PY07_FUNC_CTL_SPI2_MOSI;
        HPM_PIOC->PAD[IOC_PAD_PY05].FUNC_CTL = PIOC_PY05_FUNC_CTL_SOC_PY_05;
        HPM_PIOC->PAD[IOC_PAD_PY04].FUNC_CTL = PIOC_PY04_FUNC_CTL_SOC_PY_04;
        HPM_PIOC->PAD[IOC_PAD_PY06].FUNC_CTL = PIOC_PY06_FUNC_CTL_SOC_PY_06;
        HPM_PIOC->PAD[IOC_PAD_PY07].FUNC_CTL = PIOC_PY07_FUNC_CTL_SOC_PY_07;

        /* set max frequency slew rate(200M) */
        HPM_IOC->PAD[IOC_PAD_PY05].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3) | IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1) | IOC_PAD_PAD_CTL_PRS_SET(1);
        HPM_IOC->PAD[IOC_PAD_PY04].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PY06].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
        HPM_IOC->PAD[IOC_PAD_PY07].PAD_CTL = IOC_PAD_PAD_CTL_SR_MASK | IOC_PAD_PAD_CTL_SPD_SET(3);
    }
}

void init_gptmr_pins(GPTMR_Type *ptr)
{
    if (ptr == HPM_GPTMR0) {
        HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PD10_FUNC_CTL_GPTMR0_COMP_2;
    } else if (ptr == HPM_GPTMR3) {
        HPM_IOC->PAD[IOC_PAD_PY00].FUNC_CTL = IOC_PY00_FUNC_CTL_GPTMR3_COMP_0;
        HPM_IOC->PAD[IOC_PAD_PY01].FUNC_CTL = IOC_PY01_FUNC_CTL_GPTMR3_CAPT_0;
        HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_SOC_PY_00;
        HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_SOC_PY_01;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_GPTMR3_COMP_2;
    }
}

void init_hall_trgm_pins(void)
{
    init_qeiv2_uvw_pins(BOARD_BLDC_QEIV2_BASE);
}

void init_qei_trgm_pins(void)
{
    init_qeiv2_ab_pins(BOARD_BLDC_QEIV2_BASE);
}

void init_acmp_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD26].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK; /* CMP4_INN6/CMP5_INN6/CMP6_INN6/CMP7_INN6 */
}

void init_pwm_fault_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_TRGM_P_02;
}

void init_pwm_pins(PWMV2_Type *ptr)
{
    if (ptr == HPM_PWM1) {
        HPM_IOC->PAD[IOC_PAD_PD08].FUNC_CTL = IOC_PD08_FUNC_CTL_PWM1_P_0;
        HPM_IOC->PAD[IOC_PAD_PD09].FUNC_CTL = IOC_PD09_FUNC_CTL_PWM1_P_1;
        HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PD10_FUNC_CTL_PWM1_P_2;
        HPM_IOC->PAD[IOC_PAD_PD11].FUNC_CTL = IOC_PD11_FUNC_CTL_PWM1_P_3;
        HPM_IOC->PAD[IOC_PAD_PD12].FUNC_CTL = IOC_PD12_FUNC_CTL_PWM1_P_4;
        HPM_IOC->PAD[IOC_PAD_PD13].FUNC_CTL = IOC_PD13_FUNC_CTL_PWM1_P_5;
    }
}

void init_usb_pins(USB_Type *ptr)
{
    if (ptr == HPM_USB0) {
        /* USB0_P */
        HPM_IOC->PAD[IOC_PAD_PD00].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
        /* USB0_N */
        HPM_IOC->PAD[IOC_PAD_PD01].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
        /* USB0_ID */
        HPM_IOC->PAD[IOC_PAD_PC25].FUNC_CTL = IOC_PC25_FUNC_CTL_USB0_ID;
        /* USB0_OC */
        HPM_IOC->PAD[IOC_PAD_PC26].FUNC_CTL = IOC_PC26_FUNC_CTL_USB0_OC;
        /* USB0_PWR */
        HPM_IOC->PAD[IOC_PAD_PC27].FUNC_CTL = IOC_PC27_FUNC_CTL_USB0_PWR;
    }
}

void init_clk_obs_pins(void)
{
    /* HPM_IOC->PAD[IOC_PAD_PB02].FUNC_CTL = IOC_PB02_FUNC_CTL_SYSCTL_CLK_OBS_0; */
}

void init_i2s_pins(I2S_Type *ptr)
{
    if (ptr == HPM_I2S0) {
        HPM_IOC->PAD[IOC_PAD_PA20].FUNC_CTL = IOC_PA20_FUNC_CTL_I2S0_MCLK;
        HPM_IOC->PAD[IOC_PAD_PA21].FUNC_CTL = IOC_PA21_FUNC_CTL_I2S0_BCLK;
        HPM_IOC->PAD[IOC_PAD_PA22].FUNC_CTL = IOC_PA22_FUNC_CTL_I2S0_FCLK;
        HPM_IOC->PAD[IOC_PAD_PB00].FUNC_CTL = IOC_PB00_FUNC_CTL_I2S0_TXD_3;
        HPM_IOC->PAD[IOC_PAD_PA23].FUNC_CTL = IOC_PA23_FUNC_CTL_I2S0_RXD_0;
    } else {
        ;
    }
}

void init_qeo_pins(QEOV2_Type *ptr)
{
    if (ptr == HPM_QEO1) {
        HPM_IOC->PAD[IOC_PAD_PC00].FUNC_CTL = IOC_PC00_FUNC_CTL_QEO1_A;
        HPM_IOC->PAD[IOC_PAD_PC01].FUNC_CTL = IOC_PC01_FUNC_CTL_QEO1_B;
        HPM_IOC->PAD[IOC_PAD_PC02].FUNC_CTL = IOC_PC02_FUNC_CTL_QEO1_Z;
    }
}

void init_sei_pins(SEI_Type *ptr, uint8_t sei_ctrl_idx)
{
    if (ptr == HPM_SEI) {
        if (sei_ctrl_idx == SEI_CTRL_1) {
            HPM_IOC->PAD[IOC_PAD_PB08].FUNC_CTL = IOC_PB08_FUNC_CTL_SEI1_TX;
            HPM_IOC->PAD[IOC_PAD_PB09].FUNC_CTL = IOC_PB09_FUNC_CTL_SEI1_RX;
            HPM_IOC->PAD[IOC_PAD_PB10].FUNC_CTL = IOC_PB10_FUNC_CTL_SEI1_DE;
            HPM_IOC->PAD[IOC_PAD_PB11].FUNC_CTL = IOC_PB11_FUNC_CTL_SEI1_CK;
        }
    }
}

void init_qeiv2_uvw_pins(QEIV2_Type *ptr)
{
    if (ptr == HPM_QEI0) {
        HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_QEI0_A;
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_QEI0_B;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_QEI0_Z;
    }
}

void init_qeiv2_ab_pins(QEIV2_Type *ptr)
{
    if (ptr == HPM_QEI0) {
        HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_QEI0_A;
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_QEI0_B;
    }
}

void init_qeiv2_abz_pins(QEIV2_Type *ptr)
{
    if (ptr == HPM_QEI0) {
        HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_QEI0_A;
        HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_QEI0_B;
        HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_QEI0_Z;
    }
}

void init_rdc_pin(void)
{
    HPM_IOC->PAD[IOC_PAD_PA17].FUNC_CTL = IOC_PA17_FUNC_CTL_RDC0_PWM_P;
    HPM_IOC->PAD[IOC_PAD_PD14].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
    HPM_IOC->PAD[IOC_PAD_PD24].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;
}

void init_dao_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PY03].FUNC_CTL = IOC_PY03_FUNC_CTL_DAO_RP;
    HPM_IOC->PAD[IOC_PAD_PY02].FUNC_CTL = IOC_PY02_FUNC_CTL_DAO_RN;
    HPM_PIOC->PAD[IOC_PAD_PY03].FUNC_CTL = PIOC_PY03_FUNC_CTL_SOC_PY_03;
    HPM_PIOC->PAD[IOC_PAD_PY02].FUNC_CTL = PIOC_PY02_FUNC_CTL_SOC_PY_02;
}

void init_pdm_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD22].FUNC_CTL = IOC_PD22_FUNC_CTL_PDM0_CLK;
    HPM_IOC->PAD[IOC_PAD_PD23].FUNC_CTL = IOC_PD23_FUNC_CTL_PDM0_D_0;
}

void init_enet_pins(ENET_Type *ptr)
{
    if (ptr == HPM_ENET0) {
        HPM_IOC->PAD[IOC_PAD_PD00].FUNC_CTL = IOC_PD00_FUNC_CTL_ETH0_RXCK;
        HPM_IOC->PAD[IOC_PAD_PD01].FUNC_CTL = IOC_PD01_FUNC_CTL_ETH0_RXDV;

        HPM_IOC->PAD[IOC_PAD_PD03].FUNC_CTL = IOC_PD03_FUNC_CTL_ETH0_RXD_0;
        HPM_IOC->PAD[IOC_PAD_PD04].FUNC_CTL = IOC_PD04_FUNC_CTL_ETH0_RXD_1;
        HPM_IOC->PAD[IOC_PAD_PD05].FUNC_CTL = IOC_PD05_FUNC_CTL_ETH0_RXD_2;
        HPM_IOC->PAD[IOC_PAD_PD06].FUNC_CTL = IOC_PD06_FUNC_CTL_ETH0_RXD_3;

        HPM_IOC->PAD[IOC_PAD_PA18].FUNC_CTL = IOC_PA18_FUNC_CTL_ETH0_MDC;
        HPM_IOC->PAD[IOC_PAD_PA19].FUNC_CTL = IOC_PA19_FUNC_CTL_ETH0_MDIO;

        HPM_IOC->PAD[IOC_PAD_PD16].FUNC_CTL = IOC_PD16_FUNC_CTL_ETH0_TXCK;
        HPM_IOC->PAD[IOC_PAD_PD17].FUNC_CTL = IOC_PD17_FUNC_CTL_ETH0_TXEN;

        HPM_IOC->PAD[IOC_PAD_PD18].FUNC_CTL = IOC_PD18_FUNC_CTL_ETH0_TXD_0;
        HPM_IOC->PAD[IOC_PAD_PD19].FUNC_CTL = IOC_PD19_FUNC_CTL_ETH0_TXD_1;
        HPM_IOC->PAD[IOC_PAD_PD20].FUNC_CTL = IOC_PD20_FUNC_CTL_ETH0_TXD_2;
        HPM_IOC->PAD[IOC_PAD_PD21].FUNC_CTL = IOC_PD21_FUNC_CTL_ETH0_TXD_3;
    }
}

void init_enet_pps_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD11].FUNC_CTL = IOC_PD11_FUNC_CTL_ETH0_EVTO_0;
}

void init_adc16_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD26].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;        /* ADC_B: ADC2/3.IN10 */
}

void init_adc_bldc_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD14].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;        /* ADC_IU: ADC0.14 / ADC1.14 */
    HPM_IOC->PAD[IOC_PAD_PD24].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;        /* ADC_IU: ADC2.08 / ADC3.08 */
    HPM_IOC->PAD[IOC_PAD_PD25].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;        /* ADC_IU: ADC2.09 / ADC3.09 */
}

void init_adc_qeiv2_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD25].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;        /* ADC_IW: ADC2.09 / ADC3.09 cos_ch */
    HPM_IOC->PAD[IOC_PAD_PD14].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;        /* ADC_IU: ADC0.14 / ADC1.14 sin_ch */
}

void init_can_pins(MCAN_Type *ptr)
{
    if (ptr == HPM_MCAN1) {
        HPM_IOC->PAD[IOC_PAD_PD30].FUNC_CTL = IOC_PD30_FUNC_CTL_MCAN1_RXD;
        HPM_IOC->PAD[IOC_PAD_PD31].FUNC_CTL = IOC_PD31_FUNC_CTL_MCAN1_TXD;
        HPM_IOC->PAD[IOC_PAD_PD29].FUNC_CTL = IOC_PD29_FUNC_CTL_MCAN1_STBY;
    } else {
        /* Invalid CAN instance */
    }
}

void init_led_pins_as_gpio(void)
{
    HPM_IOC->PAD[IOC_PAD_PA25].FUNC_CTL = IOC_PA25_FUNC_CTL_GPIO_A_25;
}

void init_led_pins_as_pwm(void)
{
    HPM_IOC->PAD[IOC_PAD_PD08].FUNC_CTL = IOC_PD08_FUNC_CTL_TRGM_P_08;
}

void init_plb_pulse_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PD10_FUNC_CTL_TRGM_P_10;
}

void init_plb_ab_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PB23].FUNC_CTL = IOC_PB23_FUNC_CTL_TRGM_P_08;
    HPM_IOC->PAD[IOC_PAD_PB22].FUNC_CTL = IOC_PB22_FUNC_CTL_TRGM_P_09;
    HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_TRGM_P_10;
}

void init_plb_lin_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD08].FUNC_CTL = IOC_PD08_FUNC_CTL_TRGM_P_08;
}

void init_plb_filter_pins(void)
{
    HPM_IOC->PAD[IOC_PAD_PD10].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(0);
    HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PD10_FUNC_CTL_TRGM_P_10;
    HPM_IOC->PAD[IOC_PAD_PD12].FUNC_CTL = IOC_PD12_FUNC_CTL_TRGM_P_12;
}

/* for uart_rx_line_status case, need to a gpio pin to sent break signal */
void init_uart_break_signal_pin(void)
{
    HPM_IOC->PAD[IOC_PAD_PY05].PAD_CTL = IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
    HPM_IOC->PAD[IOC_PAD_PY05].FUNC_CTL = IOC_PY05_FUNC_CTL_GPIO_Y_05;
    HPM_PIOC->PAD[IOC_PAD_PY05].FUNC_CTL = PIOC_PY05_FUNC_CTL_SOC_PY_05;
}

void init_dac_pins(DAC_Type *ptr)
{
    if (ptr == HPM_DAC0) {
        HPM_IOC->PAD[IOC_PAD_PD07].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;  /* DAC0.OUT */
    } else if (ptr == HPM_DAC1) {
        HPM_IOC->PAD[IOC_PAD_PD17].FUNC_CTL = IOC_PAD_FUNC_CTL_ANALOG_MASK;  /* DAC1.OUT */
    }
}

void init_gptmr_channel_pin(GPTMR_Type *ptr, uint32_t channel, bool as_comp)
{
    if ((ptr == HPM_GPTMR0) && (channel == 2) && (as_comp == true)) {
        HPM_IOC->PAD[IOC_PAD_PD10].FUNC_CTL = IOC_PD10_FUNC_CTL_GPTMR0_COMP_2;
    } else if (ptr == HPM_GPTMR3) {
        if (as_comp == false) {
            if (channel == 0) {
                HPM_IOC->PAD[IOC_PAD_PY01].FUNC_CTL = IOC_PY01_FUNC_CTL_GPTMR3_CAPT_0;
                HPM_PIOC->PAD[IOC_PAD_PY01].FUNC_CTL = PIOC_PY01_FUNC_CTL_SOC_PY_01;
            }
        } else {
            if (channel == 0) {
                HPM_IOC->PAD[IOC_PAD_PY00].FUNC_CTL = IOC_PY00_FUNC_CTL_GPTMR3_COMP_0;
                HPM_PIOC->PAD[IOC_PAD_PY00].FUNC_CTL = PIOC_PY00_FUNC_CTL_SOC_PY_00;
            } else if (channel == 2) {
                HPM_IOC->PAD[IOC_PAD_PB21].FUNC_CTL = IOC_PB21_FUNC_CTL_GPTMR3_COMP_2;
            }
        }
    }
}

