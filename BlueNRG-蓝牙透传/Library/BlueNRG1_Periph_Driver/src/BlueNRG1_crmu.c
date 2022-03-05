/**
  ******************************************************************************
  * @file    BlueNRG1_crmu.c
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file provides all the CRMU firmware functions.
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

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1_crmu.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @defgroup CRMU CRMU Driver
  * @{
  */
  
/** @defgroup CRMU_Private_TypesDefinitions Private Types Definitions
  * @{
  */

/**
  * @}
  */ 

/** @defgroup CRMU_Private_Defines Private Defines
  * @{
  */ 

#define CRMU_SOC_REASON_SYSREQ        (0x00000002)
#define CRMU_SOC_REASON_WDG           (0x00000004)
#define CRMU_SOC_REASON_LOCKUP        (0x00000008)

#define CRMU_BLE_REASON_WAKEUP_RST    (0x00000001)
#define CRMU_BLE_REASON_BOR_RST       (0x00000002 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_POR_RST       (0x00000004 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_IO9      (0x00000008 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_IO10     (0x00000010 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_IO11     (0x00000020 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_IO12     (0x00000040 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_IO13     (0x00000080 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_TIMER1   (0x00000100 | CRMU_BLE_REASON_WAKEUP_RST)
#define CRMU_BLE_REASON_FROM_TIMER2   (0x00000400 | CRMU_BLE_REASON_WAKEUP_RST)


/**
  * @}
  */ 

/** @defgroup CRMU_Private_Macros Private Macros
  * @{
  */


/**
  * @}
  */ 

/** @defgroup CRMU_Private_Variables Private Variables
  * @{
  */

/**
  * @}
  */ 

/** @defgroup CRMU_Private_FunctionPrototypes Private Function Prototypes
  * @{
  */
  

/**
  * @}
  */

/** @defgroup CRMU_Public_Functions Public Functions
* @{
*/


/**
  * @brief  De init function
  * @param  None
  * @retval None
  */
void CRMU_DeInit(void)
{
  CKGEN_SOC->CONTROL      = 0x00000000;
  CKGEN_SOC->CLOCK_EN     = 0x0003FFFF;
  CKGEN_BLE->CLK32K_COUNT = 0x00000000;
  CKGEN_BLE->CLK32K_IT    = 0x00000000;
}


/**
  * @brief  Enables the clock for the specified peripheral.
  * @param  CRMU_Periph: Peripheral to be enabled, this value can be
  *         @arg CRMU_PERIPH_GPIO Clock of GPIO peripheral
  *         @arg CRMU_PERIPH_NVM Clock of NVM peripheral
  *         @arg CRMU_PERIPH_SYS_CONTROL Clock of SYSTEM CONTROL peripheral
  *         @arg CRMU_PERIPH_UART Clock of UART peripheral
  *         @arg CRMU_PERIPH_SPI Clock of SPI peripheral
  *         @arg CRMU_PERIPH_WDG Clock of WATCHDOG peripheral
  *         @arg CRMU_PERIPH_ADC Clock of ADC peripheral
  *         @arg CRMU_PERIPH_I2C1 Clock of I2C1 peripheral
  *         @arg CRMU_PERIPH_I2C2 Clock of I2C2 peripheral
  *         @arg CRMU_PERIPH_MTFX1 Clock of MFTX1 peripheral
  *         @arg CRMU_PERIPH_MTFX2 Clock of MFTX2 peripheral
  *         @arg CRMU_PERIPH_RTC Clock of RTC peripheral
  *         @arg CRMU_PERIPH_DMA Clock of DMA peripheral
  *         @arg CRMU_PERIPH_RNG Clock of RNG peripheral
  * @param NewState: New state of the peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CRMU_PeripheralClockCmd(uint32_t CRMU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_CRMU_PERIPH(CRMU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE) {
    SET_BIT(CKGEN_SOC->CLOCK_EN, CRMU_Periph);
  }
  else {
    CLEAR_BIT(CKGEN_SOC->CLOCK_EN, CRMU_Periph);
  }
}

/**
  * @brief  Get the wakeup reason.
  * @param  None
  * @retval CRMU_RESET_RESON_Type: wakeup reason @ref CRMU_RESET_RESON_Type
  */
CRMU_RESET_RESON_Type CRMU_GetWakeupResetReason(void)
{
  uint32_t tmpSoc, tmpBle;
  
  tmpSoc = CKGEN_SOC->REASON_RST;
  tmpBle = CKGEN_BLE->REASON_RST;

  if ((tmpSoc == 0) &&
      (tmpBle >= CRMU_BLE_REASON_FROM_IO9) && 
      (tmpBle <= CRMU_BLE_REASON_FROM_IO13)) {
    if ((tmpBle & CRMU_BLE_REASON_FROM_IO9) == CRMU_BLE_REASON_FROM_IO9) {
      return CRMU_RESET_BLE_WAKEUP_FROM_IO9;
    }
    if ((tmpBle & CRMU_BLE_REASON_FROM_IO10) == CRMU_BLE_REASON_FROM_IO10) {
      return CRMU_RESET_BLE_WAKEUP_FROM_IO10;
    }
    if ((tmpBle & CRMU_BLE_REASON_FROM_IO11) == CRMU_BLE_REASON_FROM_IO11) {
      return CRMU_RESET_BLE_WAKEUP_FROM_IO11;
    }
    if ((tmpBle & CRMU_BLE_REASON_FROM_IO12) == CRMU_BLE_REASON_FROM_IO12) {
      return CRMU_RESET_BLE_WAKEUP_FROM_IO12;
    }
    if ((tmpBle & CRMU_BLE_REASON_FROM_IO13) == CRMU_BLE_REASON_FROM_IO13) {
      return CRMU_RESET_BLE_WAKEUP_FROM_IO13;
    }
  }

  if ((tmpSoc == 0) &&
      ((tmpBle & CRMU_BLE_REASON_FROM_TIMER1) == CRMU_BLE_REASON_FROM_TIMER1)) {
    return CRMU_RESET_BLE_WAKEUP_FROM_TIMER1;
  }
  if ((tmpSoc == 0) &&
      ((tmpBle & CRMU_BLE_REASON_FROM_TIMER2) == CRMU_BLE_REASON_FROM_TIMER2)) {
    return CRMU_RESET_BLE_WAKEUP_FROM_TIMER2;
  }
  if ((tmpSoc == 0) &&
      ((tmpBle & CRMU_BLE_REASON_POR_RST) == CRMU_BLE_REASON_POR_RST)) {
    return CRMU_RESET_BLE_POR;
  }
  if ((tmpSoc == 0) &&
      ((tmpBle & CRMU_BLE_REASON_BOR_RST) == CRMU_BLE_REASON_BOR_RST)) {
    return CRMU_RESET_BLE_BOR;
  }
  if (tmpSoc == CRMU_SOC_REASON_SYSREQ) {
    return CRMU_RESET_SYSREQ;
  }
  if (tmpSoc == CRMU_SOC_REASON_WDG) {
    return CRMU_RESET_WDG;
  }
  if((tmpSoc == CRMU_SOC_REASON_LOCKUP)) {
    return CRMU_RESET_LOCKUP;
  }

  return CRMU_RESET_NONE;
}


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
