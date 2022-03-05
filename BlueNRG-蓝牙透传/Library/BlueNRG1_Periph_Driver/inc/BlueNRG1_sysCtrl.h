/**
  ******************************************************************************
  * @file    BlueNRG1_sysCtrl.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the System Controller 
  *          firmware library.
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
#ifndef BLUENRG1_SYSCTRL_H
#define BLUENRG1_SYSCTRL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup SystemControl
  * @{
  */

/** @defgroup sysControl_Exported_Types Exported Types
  * @{
  */

/**
  * @}
  */

/** @defgroup sysControl_Exported_Constants Exported Constants
  * @{
  */


  
/** @defgroup sysControl_IO IO inputselection for wakeup
  * @{
  */
  
#define WAKEUP_ON_IO9       0x00    /* Wakeup source is IO9 */
#define WAKEUP_ON_IO10      0x01    /* Wakeup source is IO10 */
#define WAKEUP_ON_IO11      0x02    /* Wakeup source is IO11 */
#define WAKEUP_ON_IO12      0x04    /* Wakeup source is IO12 */
#define WAKEUP_ON_IO13      0x08    /* Wakeup source is IO13 */

#define WAKEUP_ON_HIGH_STATE    0   /* Wakeup on high state */
#define WAKEUP_ON_LOW_STATE     1   /* Wakeup on low state */

#define IS_WAKEUP_ON_IOX(IO)  ( ((IO) == WAKEUP_ON_IO9 ) || ((IO) == WAKEUP_ON_IO10) || \
                                ((IO) == WAKEUP_ON_IO11) || ((IO) == WAKEUP_ON_IO12) || \
                                ((IO) == WAKEUP_ON_IO13) )

#define IS_WAKEUP_ON_STATE(STATE) ( ((STATE) == WAKEUP_ON_HIGH_STATE) || ((STATE) == WAKEUP_ON_LOW_STATE) )

/**
  * @}
  */

#define XO_32MHz     1    /* The external clock XO used is a 32 MHz */
#define XO_16MHz     0    /* The external clock XO used is a 16 MHz */

#define IS_XO_FREQ(XO) ( ((XO) == XO_32MHz) || ((XO) == XO_16MHz) )

/**
  * @}
  */



/**
  * @}
  */


/** @defgroup sysControl_Exported_Macros Exported Macros
  * @{
  */
  
/**
  * @}
  */

/** @defgroup sysControl_Exported_Functions Exported Functions
  * @{
  */
void SysCtrl_WakeupFromIo(uint8_t IOx, uint8_t LevelState, FunctionalState NewState);
void SysCtrl_SelectXO(uint8_t XOFreq);


#ifdef __cplusplus
}
#endif

#endif /* BLUENRG1_SYSCTRL_H */
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
