/**
  ******************************************************************************
  * @file    BlueNRG1_sysCtrl.c
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file provides all the System Controller firmware functions.
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
#include "BlueNRG1_sysCtrl.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @defgroup SysCtrl System Controller Driver
  * @{
  */ 

/** @defgroup SysCtrl_Private_TypesDefinitions Private Types Definitions
  * @{
  */

/**
  * @}
  */ 

/** @defgroup SysCtrl_Private_Defines Private Defines
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup SysCtrl_Private_Macros Private Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup SysCtrl_Private_Variables Private Variables
  * @{
  */

/**
  * @}
  */ 

/** @defgroup SysCtrl_Private_FunctionPrototypes Private Function Prototypes
  * @{
  */
  
/**
  * @}
  */
  
/** @defgroup SysCtrl_Public_Functions Public Functions
  * @{
  */


/**
* @brief  Configure the wakeup source from IO.
* @param  IOx: the IO selected as wakeup source, the value can be 
*         @arg WAKEUP_ON_IO9 Wakeup source is IO9
*         @arg WAKEUP_ON_IO10 Wakeup source is IO10
*         @arg WAKEUP_ON_IO11 Wakeup source is IO11
*         @arg WAKEUP_ON_IO12 Wakeup source is IO12
*         @arg WAKEUP_ON_IO13 Wakeup source is IO13
* @param  LevelState: select the level of the wakeup source, the value can be 
*         @arg WAKEUP_ON_HIGH_STATE Wakeup on high state
*         @arg WAKEUP_ON_LOW_STATE Wakeup on low state
* @param  NewState: functional state @ref FunctionalState
*         This parameter can be: ENABLE or DISABLE.
* @retval  None
*/
void SysCtrl_WakeupFromIo(uint8_t IOx, uint8_t LevelState, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_WAKEUP_ON_IOX(IOx));
  assert_param(IS_WAKEUP_ON_STATE(LevelState));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if(LevelState == WAKEUP_ON_HIGH_STATE) {
    SET_BIT(SYSTEM_CTRL->WKP_IO_IS, IOx);
  }
  else {
    CLEAR_BIT(SYSTEM_CTRL->WKP_IO_IS, IOx);
  }
  
  if(NewState == ENABLE) {
    SET_BIT(SYSTEM_CTRL->WKP_IO_IE, IOx);
  }
  else {    
    CLEAR_BIT(SYSTEM_CTRL->WKP_IO_IE, IOx);
  }
  
}

/**
  * @brief  Enable disable the XO clock divider for the system control.
  * @param  XOFreq: configure the system for the correct XO external clock used, the value can be
*         @arg XO_32MHz enable the XO divider and expect a 32 MHz external clock.
*         @arg XO_16MHz disable the XO divider and expect a 16 MHz external clock.
  * @retval None
  */
void SysCtrl_SelectXO(uint8_t XOFreq)
{  
  /* Check the parameters */
  assert_param(IS_XO_FREQ(XOFreq));

  if(XOFreq == XO_32MHz) {
    SYSTEM_CTRL->CTRL_b.MHZ32_SEL = SET;
  }
  else {    
    SYSTEM_CTRL->CTRL_b.MHZ32_SEL = RESET;
  }
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
