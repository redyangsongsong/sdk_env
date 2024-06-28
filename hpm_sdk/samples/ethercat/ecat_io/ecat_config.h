/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef ECAT_CONFIG_H
#define ECAT_CONFIG_H

#include "board.h"

/* ecat timer */
#define ECAT_TIMER_GPTMR        HPM_GPTMR0
#define ECAT_TIMER_GPTMR_CH     (0U)
#define ECAT_TIMER_GPTMR_CLK    (clock_gptmr0)
#define ECAT_TIMER_GPTRM_IRQ    IRQn_GPTMR0

/* ecat eeprom emulation function */
#define ECAT_EEPROM_FLASH_OFFSET      (4096 * 256)
#define ECAT_EEPROM_FLASH_SECTOR_SIZE (4096)
#define ECAT_EEPROM_FLASH_SECTOR_CNT  (16) /* suitable for 2K bytes eeprom space */
/* if a eeprom context generated by SSC, could use it to init EEPROM context in eeprom emulation function */
#define ECAT_INIT_EEPROM_CONTEXT_IN_PROGRAM (0)
/* EEPROM size in bytes, indicate the size of the actual connected eeprom */
#define ECAT_EEPROM_SIZE_BYTE         (16 * 1024)  /* 16K bytes = 128K bits */


/* ecat reset function */
#define ECAT_RESET_ESC_PERIPHERAL  0    /* ESC reset request will reset ethercat slave controller only, not suggest */
#define ECAT_RESET_ESC_WITH_MCU    1    /* ESC reset request will reset ethercat slave controller and mcu */


#endif /* ECAT_CONFIG_H */