/**
  ******************************************************************************
  * @file    BlueNRG1_mftx.c
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file provides all the MFTX firmware functions.
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
#include "BlueNRG1_mftx.h"


/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @defgroup MFTX MFTX Driver
  * @{
  */
  
/** @defgroup MFTX_Private_TypesDefinitions Private Types Definitions
  * @{
  */

/**
  * @}
  */ 

/** @defgroup MFTX_Private_Defines Private Defines
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup MFTX_Private_Macros Private Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup MFTX_Private_Variables Private Variables
  * @{
  */

/**
  * @}
  */ 

/** @defgroup MFTX_Private_FunctionPrototypes Private Function Prototypes
  * @{
  */
  
  /**
  * @}
  */ 

/** @defgroup MFTX_Public_Functions Public Functions
  * @{
  */

/**
  *@brief Initializes the MFTXx peripheral according to the specified
  *       parameters in the MFTX_InitStruct.
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  MFTX_InitStruct: pointer to a @ref MFTX_InitType structure that
  *         contains the configuration information for the specified MFTX peripheral.
  *@retval None
  */
void MFTX_Init( MFTX_Type* MFTXx, MFTX_InitType* MFTX_InitStruct)
{
  
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_MODE(MFTX_InitStruct->MFTXMode));
  assert_param(IS_MFTX_CLOCK_SEL(MFTX_InitStruct->MFTXClock1));
  assert_param(IS_MFTX_CLOCK_SEL(MFTX_InitStruct->MFTXClock2));
  
  MFTXx->TNMCTRL_b.TNAEN = RESET;
  MFTXx->TNMCTRL_b.TNBEN = RESET;
  
  MFTXx->TNCKC_b.TNC1CSEL = MFTX_NO_CLK;
  MFTXx->TNCKC_b.TNC2CSEL = MFTX_NO_CLK;
  
  if(MFTX_InitStruct->MFTXMode == MFTX_MODE_1a) {
    MFTXx->TNMCTRL_b.TNMDSEL = MFTX_MODE_1;
    MFTXx->TNMCTRL_b.TNPTEN = SET;
  }
  else {
    MFTXx->TNMCTRL_b.TNMDSEL = MFTX_InitStruct->MFTXMode;
    MFTXx->TNMCTRL_b.TNPTEN = RESET;
  }
  
  MFTXx->TNPRSC = MFTX_InitStruct->MFTXPrescaler;
  MFTXx->TNMCTRL_b.TNEN = SET;
  MFTXx->TNCRA = MFTX_InitStruct->MFTXCRA;
  MFTXx->TNCRB = MFTX_InitStruct->MFTXCRB;
  MFTXx->TNMCTRL_b.TNEN = RESET;
  
  MFTXx->TNCKC_b.TNC1CSEL = MFTX_InitStruct->MFTXClock1;
  MFTXx->TNCKC_b.TNC2CSEL = MFTX_InitStruct->MFTXClock2;
}

/**
  * @brief  Fills each MFTX_InitStruct member with its default value.
  * @param  MFTX_InitStruct : pointer to a @ref MFTX_InitType structure which will
  *         be initialized.
  * @retval None
  */
void MFTX_StructInit(MFTX_InitType* MFTX_InitStruct)
{
  /* Reset MFTX init structure parameters values */
  MFTX_InitStruct->MFTXClock1 = MFTX_NO_CLK;
  MFTX_InitStruct->MFTXClock2 = MFTX_NO_CLK;
  MFTX_InitStruct->MFTXCRA = 0;
  MFTX_InitStruct->MFTXCRB = 0;
  MFTX_InitStruct->MFTXMode = MFTX_MODE_1;
  MFTX_InitStruct->MFTXPrescaler = 0;
}

/**
  *@brief  Enable/Disable the MFTX
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  *@retval None
  */
void MFTX_CMD( MFTX_Type* MFTXx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE) {
    MFTXx->TNMCTRL_b.TNEN = SET;
  }
  else {
    MFTXx->TNMCTRL_b.TNEN = RESET;
  }
}


/**
  *@brief  Configure edges sensibility of TnA and TnB
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  TnA_edge : falling or rising edge
  *@param  TnB_edge : falling or rising edge, these values can be
  *         @arg MFTX_FALLING on rising edge
  *         @arg MFTX_RISING on falling edge
  *@retval None
  */
void MFTX_TnEDGES( MFTX_Type* MFTXx, uint32_t TnA_edge, uint32_t TnB_edge)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_Tn_EDGE(TnA_edge));
  assert_param(IS_MFTX_Tn_EDGE(TnB_edge));
  
  MFTXx->TNMCTRL_b.TNAEDG = TnA_edge;
  MFTXx->TNMCTRL_b.TNBEDG = TnB_edge;
}

/**
  *@brief  Select trigger source for pulse-train generation in Mode 1a
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  Trigger : software or TnB trigger, this value can be
  *         @arg MFTX_TnB_TRIGGER trigger on TnB edge
  *         @arg MFTX_SOFTWARE_TRIGGER trigger software
  *@retval None
  */
void MFTX_PulseTrainTriggerSelect( MFTX_Type* MFTXx, uint32_t Trigger)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_PULSETRAIN_TRIGGER(Trigger));
  
  MFTXx->TNMCTRL_b.TNPTSE = Trigger;
}

/**
  *@brief  Pulse-train trigger generation in Mode 1a
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@retval None
  */
void MFTX_PulseTrainSoftwareTrigger( MFTX_Type* MFTXx)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  
  MFTXx->TNMCTRL_b.TNPTET = SET;
}

/**
  *@brief  Set or Reset TnAEN bit
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  TnX : set or reset, @ref MFTX_TnAEN
  *         @arg MFTX_TnA select internal pin TnA
  *         @arg MFTX_TnB select internal pin TnB
  *@param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  *@retval None
  */
void MFTX_TnXEN( MFTX_Type* MFTXx, uint8_t TnX, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_TnX(TnX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if(TnX == MFTX_TnA) {
    MFTXx->TNMCTRL_b.TNAEN = NewState;
  }
  else if(TnX == MFTX_TnB) {
    MFTXx->TNMCTRL_b.TNBEN = NewState;
  }
}


/**
  *@brief  Set or Reset TnAEN bit
  *@param  TimerType : select the timer and the pin, this value can be
  *         @arg MFTX1_TIMERA Select Timer MFTX1 and input TnA
  *         @arg MFTX1_TIMERB Select Timer MFTX1 and input TnB
  *         @arg MFTX2_TIMERA Select Timer MFTX2 and input TnA
  *         @arg MFTX2_TIMERB Select Timer MFTX2 and input TnB
  *@param  PinNumber : the IO number from IO0 to IO14 (0, 1, .. 14)
  *@retval None
  */
void MFTX_MFTX_SelectCapturePin( uint32_t TimerType, uint8_t PinNumber)
{
  /* Check the parameters */
  assert_param(IS_MFTX_TIMER(TimerType));
  assert_param(IS_MFTX_INPUT_IO(PinNumber));
  
  /* set counter */
  if(TimerType == MFTX1_TIMERA) {
    GPIO->MFTX_b.MFTX1_TIMER_A = PinNumber;
  }
  else if(TimerType == MFTX1_TIMERB) {
    GPIO->MFTX_b.MFTX1_TIMER_B = PinNumber;
  }
  else if(TimerType == MFTX2_TIMERA) {
    GPIO->MFTX_b.MFTX2_TIMER_A = PinNumber;
  }
  else if(TimerType == MFTX2_TIMERB) {
    GPIO->MFTX_b.MFTX2_TIMER_B = PinNumber;
  }
  
}


/**
  *@brief  Set the timer counter.
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  Cnt1 : set the counter value for CNT1
  *@param  Cnt2 : set the counter value for CNT2
  *@retval None
  */
void MFTX_SetCounter(MFTX_Type* MFTXx, uint16_t Cnt1, uint16_t Cnt2)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  
  /* set counter */
  MFTXx->TNCNT1 = Cnt1;
  MFTXx->TNCNT2 = Cnt2;
}


/**
  *@brief  Set the timer counter1.
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  Cnt1 : set the counter value for CNT1
  *@retval None
  */
void MFTX_SetCounter1(MFTX_Type* MFTXx, uint16_t Cnt)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  
  /* set counter */
  MFTXx->TNCNT1 = Cnt;
}


/**
  *@brief  Set the timer counter2.
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  Cnt2 : set the counter value for CNT2
  *@retval None
  */
void MFTX_SetCounter2(MFTX_Type* MFTXx, uint16_t Cnt)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  
  /* set counter */
  MFTXx->TNCNT2 = Cnt;
}

/**
  *@brief  Enable specific MFTX interrupt
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  irqSource: interrupt source to enable, this value can be
  *         @arg MFTX_IT_TNA Select the interrupt source A
  *         @arg MFTX_IT_TNB Select the interrupt source B
  *         @arg MFTX_IT_TNC Select the interrupt source C
  *         @arg MFTX_IT_TND Select the interrupt source D
  *@param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  *@retval None
  */
void MFTX_EnableIT(MFTX_Type* MFTXx, uint8_t irqSource, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_INTERRUPT(irqSource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE) {
    SET_BIT(MFTXx->TNICTRL, (irqSource << 4));
  }
  else {
    CLEAR_BIT(MFTXx->TNICTRL, (irqSource << 4));
  }
}

/**
  *@brief Clear specific MFTX interrupt
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  irqSource: interrupt source to enable, this value can be
  *         @arg MFTX_IT_TNA Select the interrupt source A
  *         @arg MFTX_IT_TNB Select the interrupt source B
  *         @arg MFTX_IT_TNC Select the interrupt source C
  *         @arg MFTX_IT_TND Select the interrupt source D
  *@retval None
  */
void MFTX_ClearIT(MFTX_Type* MFTXx, uint8_t irqSource)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_INTERRUPT(irqSource));
  
  SET_BIT(MFTXx->TNICLR, irqSource);
}

/**
  *@brief Return interrupt status
  *@param  MFTXx: where x can be 1 or 2 to select the MFTX peripheral @ref MFTX_Type
  *@param  irqSource: interrupt source to enable, this value can be
  *         @arg MFTX_IT_TNA Select the interrupt source A
  *         @arg MFTX_IT_TNB Select the interrupt source B
  *         @arg MFTX_IT_TNC Select the interrupt source C
  *         @arg MFTX_IT_TND Select the interrupt source D
  *@retval  ITStatus: functional state @ref ITStatus
  *         This parameter can be: SET or RESET.
  */
ITStatus MFTX_StatusIT( MFTX_Type* MFTXx, uint8_t irqSource)
{
  /* Check the parameters */
  assert_param(IS_MFTX(MFTXx));
  assert_param(IS_MFTX_INTERRUPT(irqSource));
  
  if((MFTXx->TNICTRL & irqSource) != (uint32_t)RESET) {
    return SET;
  }
  else {
    return RESET;
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
