/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 */

#include "board.h"

#if (portasmHAS_MTIME == 0)
#define configMTIME_BASE_ADDRESS                (0)
#define configMTIMECMP_BASE_ADDRESS             (0)
#else
#define configMTIME_BASE_ADDRESS                (HPM_MCHTMR_BASE)
#define configMTIMECMP_BASE_ADDRESS             (HPM_MCHTMR_BASE + 8UL)
#endif

#define configUSE_PREEMPTION                    1
#define configCPU_CLOCK_HZ                      ((uint32_t) 24000000)
#define configTICK_RATE_HZ                      ((TickType_t) 1000)
#define configMAX_PRIORITIES                    (32)
#define configMINIMAL_STACK_SIZE                (256)
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 0
#define configUSE_APPLICATION_TASK_TAG          0
#define configGENERATE_RUN_TIME_STATS           0

/* Memory allocation definitions. */
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTOTAL_HEAP_SIZE                   ((size_t) (8 * 1024))

/* Hook function definitions. */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCHECK_FOR_STACK_OVERFLOW          0
#define configUSE_MALLOC_FAILED_HOOK            0
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0

/* Run time and task stats gathering definitions. */
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/* Set the following definitions to 1 to include the API function, or zero to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTaskAbortDelay                 1
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xSemaphoreGetMutexHolder        1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         2

/* Software timer definitions. */
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                4
#define configTIMER_TASK_STACK_DEPTH            (configMINIMAL_STACK_SIZE)

/* Task priorities.*/
#ifndef uartPRIMARY_PRIORITY
    #define uartPRIMARY_PRIORITY                (configMAX_PRIORITIES - 3)
#endif

/* Normal assert() semantics without relying on the provision of an assert.h header file. */
#define configASSERT(x) if ((x) == 0) { taskDISABLE_INTERRUPTS(); __asm volatile("ebreak"); for (;;); }

/*
 * The size of the global output buffer that is available for use when there
 * are multiple command interpreters running at once (for example, one on a UART
 * and one on TCP/IP).  This is done to prevent an output buffer being defined by
 * each implementation - which would waste RAM.  In this case, there is only one
 * command interpreter running.
 */

/*
 * The buffer into which output generated by FreeRTOS+CLI is placed.  This must
 * be at least big enough to contain the output of the task-stats command, as the
 * example implementation does not include buffer overlow checking.
 */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE        2096
#define configINCLUDE_QUERY_HEAP_COMMAND         1

/* This file is included from assembler files - make sure C code is not included in assembler files. */
#ifndef __ASSEMBLER__
    void vAssertCalled(const char *pcFile, unsigned long ulLine);
    void vConfigureTickInterrupt(void);
    void vClearTickInterrupt(void);
    void vPreSleepProcessing(unsigned long uxExpectedIdleTime);
    void vPostSleepProcessing(unsigned long uxExpectedIdleTime);
#endif /* __ASSEMBLER__ */

/****** Hardware/compiler specific settings. *******/
/*
 * The application must provide a function that configures a peripheral to
 * create the FreeRTOS tick interrupt, then define configSETUP_TICK_INTERRUPT()
 * in FreeRTOSConfig.h to call the function.
 */
#define configSETUP_TICK_INTERRUPT() vConfigureTickInterrupt()
#define configCLEAR_TICK_INTERRUPT() vClearTickInterrupt()

/*
 * The configPRE_SLEEP_PROCESSING() and configPOST_SLEEP_PROCESSING() macros
 * allow the application writer to add additional code before and after the MCU is
 * placed into the low power state respectively.  The empty implementations
 * provided in this demo can be extended to save even more power.
 */
#define configPRE_SLEEP_PROCESSING(uxExpectedIdleTime) vPreSleepProcessing(uxExpectedIdleTime);
#define configPOST_SLEEP_PROCESSING(uxExpectedIdleTime) vPostSleepProcessing(uxExpectedIdleTime);


/* Compiler specifics. */
#define fabs(x) __builtin_fabs(x)

/* Enable Hardware Stack Protection and Recording mechanism. */
#define configHSP_ENABLE                       0

/* Record the highest address of stack. */
#if (configHSP_ENABLE == 1 && configRECORD_STACK_HIGH_ADDRESS != 1)
#define configRECORD_STACK_HIGH_ADDRESS        1
#endif

#endif /* FREERTOS_CONFIG_H */
