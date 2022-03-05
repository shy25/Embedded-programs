/**
  ******************************************************************************
  * @file    BlueNRG1_crmu.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the CRMU firmware 
  *          library.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLUENRG1_CRMU_H
#define BLUENRG1_CRMU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRMU
  * @{
  */

/** @defgroup CRMU_Exported_Types Exported Types
  * @{
  */


/** 
  * @brief  CRMU Reset and Wakeup Sources
  */ 
typedef enum
{
  CRMU_RESET_NONE,
  CRMU_RESET_SYSREQ,
  CRMU_RESET_WDG,
  CRMU_RESET_LOCKUP,
  CRMU_RESET_BLE_BOR,
  CRMU_RESET_BLE_POR,
  CRMU_RESET_BLE_WAKEUP_FROM_IO9,
  CRMU_RESET_BLE_WAKEUP_FROM_IO10,
  CRMU_RESET_BLE_WAKEUP_FROM_IO11,
  CRMU_RESET_BLE_WAKEUP_FROM_IO12,
  CRMU_RESET_BLE_WAKEUP_FROM_IO13,
  CRMU_RESET_BLE_WAKEUP_FROM_TIMER1,
  CRMU_RESET_BLE_WAKEUP_FROM_TIMER2,
} CRMU_RESET_RESON_Type;


/**
  * @}
  */

/** @defgroup CRMU_Exported_Constants Exported Constants
  * @{
  */

/** @defgroup CRMU_Peripherals Peripherals
  * @{
  */
#define CRMU_PERIPH_GPIO                ((uint32_t)0x00000001)
#define CRMU_PERIPH_NVM                 ((uint32_t)0x00000002)
#define CRMU_PERIPH_SYS_CONTROL         ((uint32_t)0x00000004)
#define CRMU_PERIPH_UART                ((uint32_t)0x00000008)
#define CRMU_PERIPH_SPI                 ((uint32_t)0x00000010)
#define CRMU_PERIPH_WDG                 ((uint32_t)0x00000080)
#define CRMU_PERIPH_ADC                 ((uint32_t)0x00000100)
#define CRMU_PERIPH_I2C1                ((uint32_t)0x00000200)
#define CRMU_PERIPH_I2C2                ((uint32_t)0x00000400)
#define CRMU_PERIPH_MTFX1               ((uint32_t)0x00000800)
#define CRMU_PERIPH_MTFX2               ((uint32_t)0x00001000)
#define CRMU_PERIPH_RTC                 ((uint32_t)0x00002000)
#define CRMU_PERIPH_DMA                 ((uint32_t)0x00010000)
#define CRMU_PERIPH_RNG                 ((uint32_t)0x00020000)


/** This macro check if PERIPH is a valid peripheral */
#define IS_CRMU_PERIPH(PERIPH) ((PERIPH & 0x800F3F9F) != 0)


/** This macro check if UART baudrate clock divider is an allowed value */
#define IS_CRMU_UART_BAUDRATE_CLKDIV(V)        ((V>0) && (V<17))

/**
  * @}
  */


/**
  * @}
  */


  
/** @defgroup CRMU_Exported_Functions Exported Functions
  * @{
  */

void CRMU_DeInit(void);
void CRMU_PeripheralClockCmd(uint32_t CRMU_Periph, FunctionalState NewState);

void CRMU_SetUartBaudrate(uint8_t ClockDivider);
CRMU_RESET_RESON_Type CRMU_GetWakeupResetReason(void);

#ifdef __cplusplus
}
#endif

#endif /* BLUENRG1_CRMU_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
