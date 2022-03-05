/**
  ******************************************************************************
  * @file    BlueNRG1_rtc.c
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file provides all the RTC firmware functions.
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
#include "BlueNRG1_rtc.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC RTC Driver
  * @{
  */ 

/** @defgroup RTC_Private_TypesDefinitions Private Types Definitions
  * @{
  */

/**
  * @}
  */ 

/** @defgroup RTC_Private_Defines Private Defines
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup RTC_Private_Macros Private Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup RTC_Private_Variables Private Variables
  * @{
  */

/**
  * @}
  */ 

/** @defgroup RTC_Private_FunctionPrototypes Private Function Prototypes
  * @{
  */
  
/**
  * @}
  */
  
/** @defgroup RTC_Public_Functions Public Functions
* @{
*/

/**
  * @brief  Initializes the RTC peripheral according to the specified
  *         parameters in the RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to a @ref RTC_InitType structure that
  *         contains the configuration information for the specified RTC peripheral.
  * @retval None
  */
void RTC_Init(RTC_InitType* RTC_InitStruct)
{
  uint32_t tmpreg;
  
  /* Check the parameters */
  assert_param(IS_RTC_TIMER_MODE(RTC_InitStruct->RTC_operatingMode));
  
  tmpreg = RTC_InitStruct->RTC_operatingMode | (RTC_InitStruct->RTC_PATTERN_SIZE & 0x7F) << 4;
  
  RTC->TCR = tmpreg;
  RTC->TLR1 = RTC_InitStruct->RTC_TLR1;
  RTC->TLR2 = RTC_InitStruct->RTC_TLR2;
  RTC->TPR1 = RTC_InitStruct->RTC_PATTERN1;
  RTC->TPR2 = RTC_InitStruct->RTC_PATTERN2;
  RTC->TPR3 = RTC_InitStruct->RTC_PATTERN3;
  RTC->TPR4 = RTC_InitStruct->RTC_PATTERN4;

}

/**
  * @brief  Enables or disables selected RTC peripheral.
  * @param  RTCx: Select the coresponding RTC.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE) {
    RTC->TCR_b.EN = SET;
  }
  else {
    RTC->TCR_b.EN = RESET;
    
  }
}

/**
  * @brief  Enables or disables selected RTC interrupt.
  * @param  RTC_IT: specifies the RTC interrupts sources, the value can be
  *         @arg RTC_IT_CLOCKWATCH RTC clock watch interrupt flag
  *         @arg RTC_IT_TIMER RTC timer interrupt flag
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_IT_Config(uint32_t RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_RTC_IT(RTC_IT));
  
  if (RTC_IT == RTC_IT_CLOCKWATCH) {
    /* Enable the selected RTC interrupts */
    RTC->IMSC_b.WIMSC = NewState;
  }
  else {
    /* Disable the selected RTC interrupts */
    RTC->IMSC_b.TIMSC = NewState;
  }
}

/**
  * @brief  Return the RTC interrupt status for the specified IT.
  * @param  RTC_IT: specifies the RTC interrupts sources, the value can be
  *         @arg RTC_IT_CLOCKWATCH RTC clock watch interrupt flag
  *         @arg RTC_IT_TIMER RTC timer interrupt flag
  * @retval  ITStatus: functional state @ref ITStatus
  *         This parameter can be: SET or RESET.
  */
ITStatus RTC_IT_Status(uint32_t RTC_IT)
{
  /* Check the parameters */
  assert_param(IS_RTC_IT(RTC_IT));

  /* Check the status of the specified RTC flag */
  if ((RTC->RIS & RTC_IT) != (uint32_t)RESET) {
    /* RTC_IT is set */
    return SET;
  }
  else {
    /* RTC_IT is reset */
    return RESET;
  }
}

/**
  * @brief  Clear selected RTC interrupt.
  * @param  RTC_IT: specifies the RTC interrupts sources, the value can be
  *         @arg RTC_IT_CLOCKWATCH RTC clock watch interrupt flag
  *         @arg RTC_IT_TIMER RTC timer interrupt flag
  * @retval None
  */
void RTC_IT_Clear(uint32_t RTC_IT)
{
  /* Check the parameters */
  assert_param(IS_RTC_IT(RTC_IT));
  
  RTC->ICR = RTC_IT;
}


/**
  * @brief  Enables or disables selected RTC clockwatch.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ClockwatchCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE) {
    RTC->CTCR_b.CWEN = SET;
  }
  else {
    RTC->CTCR_b.CWEN = RESET;
  }
}

/**
  * @brief  Initialize the RTC clockwatch with present time and date.
  * @param  RTC_DateTime: pointer to a @ref RTC_DateTimeType structure that
  *         contains the specified time and date setting.
  * @retval None
  */
void RTC_SetTimeDate(RTC_DateTimeType* RTC_DateTime)
{
  uint32_t temp=0;
  
  /* Check the parameters */
  assert_param(IS_SECOND(RTC_DateTime->Second));
  assert_param(IS_MINUTE(RTC_DateTime->Minute));
  assert_param(IS_HOUR(RTC_DateTime->Hour));
  assert_param(IS_WEEKDAY(RTC_DateTime->WeekDay));
  assert_param(IS_MONTHDAY(RTC_DateTime->MonthDay));
  assert_param(IS_MONTH(RTC_DateTime->Month));
  assert_param(IS_YEAR(RTC_DateTime->Year));
  
  /** Select seconds from the data structure */
  temp = (RTC_DateTime->Second & 0x3f);
  
  /** Select minutes from the data structure */
  temp |= (RTC_DateTime->Minute & 0x3f)<<6;
  
  /** Select hours from the data structure */
  temp |= (RTC_DateTime->Hour & 0x1f)<<12;
  
  /** Select week day from the data structure */
  temp |= (RTC_DateTime->WeekDay & 0x7)<<17;
  
  /** Select month day from the data structure */
  temp |= (RTC_DateTime->MonthDay & 0x1f)<<20;
  
  /** Select month from the data structure */
  temp |= (RTC_DateTime->Month & 0x0f)<<25;
  
  /* Store data to load register */
  RTC->CWDLR = temp;
  RTC->CWYLR = RTC_DateTime->Year;
}

/**
  * @brief  Set the RTC clockwatch match date and time registers.
  * @param  RTC_MatchDataTime: pointer to a @ref RTC_DateTimeType structure that
  *         contains the matching time and date setting.
  * @retval None
  */
void RTC_SetMatchTimeDate(RTC_DateTimeType* RTC_MatchDataTime)
{
  uint32_t temp=0;
  
  /* Check the parameters */
  assert_param(IS_SECOND(RTC_MatchDataTime->Second));
  assert_param(IS_MINUTE(RTC_MatchDataTime->Minute));
  assert_param(IS_HOUR(RTC_MatchDataTime->Hour));
  assert_param(IS_MATCH_WEEKDAY(RTC_MatchDataTime->WeekDay));
  assert_param(IS_MATCH_MONTHDAY(RTC_MatchDataTime->MonthDay));
  assert_param(IS_MATCH_MONTH(RTC_MatchDataTime->Month));
  assert_param(IS_MATCH_YEAR(RTC_MatchDataTime->Year));
  
  /** Select seconds from the data structure */
  temp = (RTC_MatchDataTime->Second & 0x3f);
  
  /** Select minutes from the data structure */
  temp |= (RTC_MatchDataTime->Minute & 0x3f)<<6;
  
  /** Select hours from the data structure */
  temp |= (RTC_MatchDataTime->Hour & 0x1f)<<12;
  
  /** Select week day from the data structure */
  temp |= (RTC_MatchDataTime->WeekDay & 0x7)<<17;
  
  /** Select month day from the data structure */
  temp |= (RTC_MatchDataTime->MonthDay & 0x1f)<<20;
  
  /** Select month from the data structure */
  temp |= (RTC_MatchDataTime->Month & 0x0f)<<25;
  
  /* Store data to load register */
  RTC->CWDMR = temp;
  RTC->CWYMR = RTC_MatchDataTime->Year;
}

/**
  * @brief  Set the RTC clockwatch match date and time registers.
  * @param  RTC_DataTime: pointer to a @ref RTC_DateTimeType structure that
  *         is filled with the configured values of time and date.
  * @retval None
  */
void RTC_GetTimeDate(RTC_DateTimeType* RTC_DataTime)
{
  /** Select seconds from the RTC register */
  RTC_DataTime->Second = (RTC->CWDR & 0x3f);
  
  /** Select minutes from the RTC register */
  RTC_DataTime->Minute= ((RTC->CWDR >> 6) & 0x3f);
  
  /** Select hours from the RTC register */
  RTC_DataTime->Hour= ((RTC->CWDR >> 12) & 0x1f);
  
  /** Select week day from the RTC register */
  RTC_DataTime->WeekDay = ((RTC->CWDR >>17) & 0x7);
  
  /** Select month day from the RTC register */
  RTC_DataTime->MonthDay = ((RTC->CWDR >> 20) & 0x1f);
  
  /** Select month from the RTC register */
  RTC_DataTime->Month = ((RTC->CWDR >>25) & 0x0f);
  
  /** Select year from the RTC register */
  RTC_DataTime->Year = ((RTC->CWYR >> 25) & 0x0f);
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
