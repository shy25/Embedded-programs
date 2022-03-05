/**
  ******************************************************************************
  * @file    BlueNRG1_mftx.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the MFTX 
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
#ifndef BLUENRG1_MFTX_H
#define BLUENRG1_MFTX_H

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup MFTX
  * @{
  */

/** @defgroup MFTX_Exported_Types Exported Types
  * @{
  */

/**
  * @brief MFTX Timer Init Structure
  */
 typedef struct
{
  uint32_t MFTXMode;        /*!< Specifies the MFTX mode.
                                 This value can be a value of @ref MFTX_mode */

  uint32_t MFTXClock1;      /*!< Specifies the MFTX clock selection, for counter A.
                                 This value can be a value of @ref MFTX_clock_SEL */
                 
  uint32_t MFTXClock2;      /*!< Specifies the MFTX clock selection, for counter B.
                                 This value can be a value of @ref MFTX_clock_SEL */
                  
  uint8_t MFTXPrescaler;   /*!< Specifies the MFTX prescaler. */
                                  
  uint16_t MFTXCRA;         /*!< Specifies the MFTX CRB init value. */

  uint16_t MFTXCRB;         /*!< Specifies the MFTX CRB init value. */
                                                 
} MFTX_InitType;


/**
  * @}
  */

/** @defgroup MFTX_Exported_Constants Exported Constants
  * @{
  */

/** @defgroup MFTX_Timer_Const MFTX Timer
  * @{
  */

#define IS_MFTX(PERIPH) (((PERIPH) == MFTX1) || ((PERIPH) == MFTX2))
/**
  * @}
  */
  
/** @defgroup MFTX_mode mftx mode
  * @{
  */
  
#define MFTX_MODE_1      ((uint16_t)0x0000) /*!< Mode 1 */
#define MFTX_MODE_1a     ((uint16_t)0x0100) /*!< Mode 1a */
#define MFTX_MODE_2      ((uint16_t)0x0001) /*!< Mode 2 */
#define MFTX_MODE_3      ((uint16_t)0x0002) /*!< Mode 3 */
#define MFTX_MODE_4      ((uint16_t)0x0003) /*!< Mode 4 */

#define IS_MFTX_MODE(MODE) (((MODE) == MFTX_MODE_1) || \
                            ((MODE) == MFTX_MODE_1a) || \
                            ((MODE) == MFTX_MODE_2) || \
                            ((MODE) == MFTX_MODE_3) || \
                            ((MODE) == MFTX_MODE_4))
              
/**
  * @}
  */
  
/** @defgroup MFTX_interrupt interrupt
  * @{
  */
  
#define MFTX_IT_TNA      ((uint32_t)0x1) /*!< interrupt TnAPNA */
#define MFTX_IT_TNB      ((uint32_t)0x2) /*!< interrupt TnAPNB */
#define MFTX_IT_TNC      ((uint32_t)0x4) /*!< interrupt TnAPNC */
#define MFTX_IT_TND      ((uint32_t)0x8) /*!< interrupt TnAPND */

#define IS_MFTX_INTERRUPT(IT) ((((IT) & (~0xF)) == 0x00) && ((IT) != 0x00))

/**
  * @}
  */
              
/** @defgroup MFTX_clock_SEL clock SEL
  * @{
  */
  
#define MFTX_NO_CLK                ((uint32_t)0x0) /*!< Noclock, timer1 stopped */
#define MFTX_PRESCALED_CLK         ((uint32_t)0x1) /*!< Prescaled system clock */
#define MFTX_EXTERNAL_EVENT        ((uint32_t)0x2) /*!< External event on TnB (mode 1 and 3 only) */
#define MFTX_PULSE_ACCUMULATE      ((uint32_t)0x3) /*!< Pulse accumulate (mode 1 and 3 only) */
#define MFTX_LOW_SPEED_CLK         ((uint32_t)0x4) /*!< Low speed clock */

#define IS_MFTX_CLOCK_SEL(MODE) (((MODE) == MFTX_NO_CLK) || \
                                 ((MODE) == MFTX_PRESCALED_CLK) || \
                                 ((MODE) == MFTX_EXTERNAL_EVENT) || \
                                 ((MODE) == MFTX_PULSE_ACCUMULATE) || \
                                 ((MODE) == MFTX_LOW_SPEED_CLK))
                
/**
  * @}
  */

  
/** @defgroup MFTX_Tn_EDGES mftx Tn edges for TnA and TnB
  * @{
  */
  
#define MFTX_FALLING           ((uint32_t)0x0)    /* on rising edge */
#define MFTX_RISING            ((uint32_t)0x1)    /* on falling edge */

#define IS_MFTX_Tn_EDGE(REG) (((REG) == MFTX_FALLING) || ((REG) == MFTX_RISING) )
              
/**
  * @}
  */
  
/** @defgroup MFTX_Pulse-Train_Trigger mftx pulse-train trigger for Mode 1a
  * @{
  */

#define MFTX_TnB_TRIGGER           ((uint32_t)0x0)    /* trigger on TnB edge */
#define MFTX_SOFTWARE_TRIGGER      ((uint32_t)0x1)    /* trigger software */

#define IS_MFTX_PULSETRAIN_TRIGGER(MODE) (((MODE) == MFTX_TnB_TRIGGER) || ((MODE) == MFTX_SOFTWARE_TRIGGER))
  
  /**
  * @}
  */

/** @defgroup MFTX_TnAEN mftx TnAEN value
  * @{
  */

#define MFTX_TnA      0       /* select internal pin TnA */
#define MFTX_TnB      1       /* select internal pin TnB */

#define IS_MFTX_TnX(VALUE) (((VALUE) == MFTX_TnA) || ((VALUE) == MFTX_TnB))
  
  /**
  * @}
  */
  
  
/** @defgroup MFTX_TIMERx mftx timer
  * @{
  */

#define MFTX1_TIMERA           ((uint32_t)0x0)    /*  Timer MFTX1 and input TnA */
#define MFTX1_TIMERB           ((uint32_t)0x1)    /*  Timer MFTX1 and input TnB */
#define MFTX2_TIMERA           ((uint32_t)0x2)    /*  Timer MFTX2 and input TnA */
#define MFTX2_TIMERB           ((uint32_t)0x3)    /*  Timer MFTX2 and input TnB */

#define IS_MFTX_TIMER(VALUE) ((VALUE) <= 3)

#define IS_MFTX_INPUT_IO(VALUE) ((VALUE) < 15)

/**
 * @}
 */
  
/**
 * @}
 */
  
/** @defgroup CRMU_Exported_Functions Exported Functions
 * @{
 */

void MFTX_Init( MFTX_Type* MFTXx, MFTX_InitType* MFTX_InitStruct);
void MFTX_CMD( MFTX_Type* MFTXx, FunctionalState NewState);
void MFTX_StructInit(MFTX_InitType* MFTX_InitStruct);
void MFTX_TnEDGES( MFTX_Type* MFTXx, uint32_t TnA_edge, uint32_t TnB_edge);
void MFTX_PulseTrainTriggerSelect( MFTX_Type* MFTXx, uint32_t Trigger);
void MFTX_PulseTrainSoftwareTrigger( MFTX_Type* MFTXx);
void MFTX_TnXEN( MFTX_Type* MFTXx, uint8_t TnX, FunctionalState NewState);
void MFTX_MFTX_SelectCapturePin( uint32_t TimerType, uint8_t PinNumber);
void MFTX_SetCounter( MFTX_Type* MFTXx, uint16_t Cnt1, uint16_t Cnt2);
void MFTX_SetCounter1(MFTX_Type* MFTXx, uint16_t Cnt);
void MFTX_SetCounter2(MFTX_Type* MFTXx, uint16_t Cnt);
void MFTX_EnableIT( MFTX_Type* MFTXx, uint8_t irqSource, FunctionalState NewState);
void MFTX_ClearIT( MFTX_Type* MFTXx, uint8_t irqSource);
ITStatus MFTX_StatusIT( MFTX_Type* MFTXx, uint8_t irqSource);

#endif /* BLUENRG1_MFTX_H */

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
