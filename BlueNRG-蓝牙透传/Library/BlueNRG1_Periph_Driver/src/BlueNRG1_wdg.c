/**
  ******************************************************************************
  * @file    BlueNRG1_WDG.c
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file provides all the WDG firmware functions.
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
#include "BlueNRG1_wdg.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @defgroup WDG WDG Driver
  * @{
  */

/** @defgroup WDG_Private_TypesDefinitions Private Types Definitions
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_Defines Private Defines
  * @{
  */


/**
  * @}
  */ 

/** @defgroup WDG_Private_Macros Private Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_Variables Private Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_FunctionPrototypes Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Private_Functions Private Functions
  * @{
  */

/**
  * @}
  */
	
/** @defgroup WDG_Public_Functions Public Functions
* @{
*/

/**
  * @brief  Enables or disables write access to WDG_PR and WDG_RLR registers.
  * @param  WDG_WriteAccess: new state of write access to WDG_PR and WDG_RLR registers.
  *   This parameter can be one of the following values:
  *     @arg WDG_WriteAccess_Enable: Enable write access to WDG_PR and WDG_RLR registers
  *     @arg WDG_WriteAccess_Disable: Disable write access to WDG_PR and WDG_RLR registers
  * @retval None
  */
void WDG_WriteAccessCmd(uint32_t WDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_WDG_WRITE_ACCESS(WDG_WriteAccess));
  WDG->LOCK = WDG_WriteAccess;
}

/**
  * @brief  Sets WDG Reload value.
  * @param  Reload: specifies the WDG Reload value.
  *   This parameter must be a number greater than 0.
  * @retval None
  */
void WDG_SetReload(uint32_t Reload)
{
  /* Check the parameters */
  assert_param(Reload > 0);
  WDG->LR = Reload;
}

/**
  * @brief  Enables WDG reset.
  * @param  None
  * @retval None
  */
void WDG_Enable(void)
{
  WDG->CR_b.INTEN = SET;
  WDG->CR_b.RESEN = SET;
}

/**
  * @brief  Gets the WDG counter value.
  * @param  None
  * @retval WDG counter value.
  */
uint32_t WDG_GetCounter(void)
{
  return WDG->VAL;
}

/**
  * @brief  Enables or disables the WDG interrupt.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDG_ITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE) {
    WDG->CR_b.INTEN = SET;
  }
  else {
    WDG->CR_b.INTEN = RESET;
  }
}

/**
  * @brief  Checks whether the WDG interrupt has occurred or not. 
  * @param  None
  * @retval  ITStatus: functional state @ref ITStatus
  *         This parameter can be: SET or RESET.
  */
ITStatus WDG_GetITStatus(void)
{
  FlagStatus bitstatus = RESET;

  /* Check the status of the WDG interrupt */
  if (WDG->RIS != (uint32_t)RESET) {
    bitstatus = SET;
  }
  
  return  bitstatus;
}

/**
  * @brief  Clears the WDG's interrupt pending bit.
  * @param  None
  * @retval None
  */
void WDG_ClearITPendingBit(void)
{
  WDG->ICR = 0xFFFFFFFF;
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
