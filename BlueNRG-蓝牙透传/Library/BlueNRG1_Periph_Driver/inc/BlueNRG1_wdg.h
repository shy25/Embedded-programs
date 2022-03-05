/**
  ******************************************************************************
  * @file    BlueNRG1_WDG.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the WDG 
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
#ifndef BLUENRG1_WDG_H
#define BLUENRG1_WDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup WDG
  * @{
  */

/** @defgroup WDG_Exported_Types Exported Types
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Exported_Constants Exported Constants
  * @{
  */
    
/**
  * @}
  */
	

/** @defgroup WDG_WriteAccess Write Access
  * @{
  */

#define WDG_WriteAccess_Enable     ((uint32_t)0x1ACCE551)       /*!< Enables WDG write access */
#define WDG_WriteAccess_Disable    ((uint32_t)0x00000000)       /*!< Disables WDG write access */

/** This macro checks if ACCESS is a valid WriteAccess value */
#define IS_WDG_WRITE_ACCESS(ACCESS) (((ACCESS) == WDG_WriteAccess_Enable) || \
                                          ((ACCESS) == WDG_WriteAccess_Disable))

/**
  * @}
  */

/** @defgroup WDG_Exported_Macros Exported Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup WDG_Exported_Functions Exported Functions
  * @{
  */
void WDG_WriteAccessCmd(uint32_t WDG_WriteAccess);
void WDG_SetReload(uint32_t Reload);
uint32_t WDG_GetCounter(void);
void WDG_Enable(void);
void WDG_ITConfig(FunctionalState NewState);
ITStatus WDG_GetITStatus(void);
void WDG_ClearITPendingBit(void);

#ifdef __cplusplus
}
#endif

#endif /* BLUENRG1_WDG_H */
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
