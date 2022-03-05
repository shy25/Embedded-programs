/**
******************************************************************************
* @file    BlueNRG1_flash.c
* @author  VMA Application Team
* @version V1.0.0
* @date    31-June-2015
* @brief   This file provides all the FLASH firmware functions.
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
#include "BlueNRG1_flash.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
* @{
*/

/** @defgroup FLASH FLASH Driver
* @{
*/ 

/** @defgroup FLASH_Private_TypesDefinitions Private Types Definitions
* @{
*/

/**
* @}
*/ 

/** @defgroup FLASH_Private_Defines Private Defines
* @{
*/ 

#define EraseTimeout          ((uint32_t)0x000B0000)  /*!< Erase timeout */
#define ProgramTimeout        ((uint32_t)0x00002000)  /*!< Program timeout */

/**
* @}
*/ 

/** @defgroup FLASH_Private_Macros Private Macros
* @{
*/


/**
* @}
*/ 

/** @defgroup FLASH_Private_Variables Private Variables
* @{
*/

/**
* @}
*/ 

/** @defgroup FLASH_Private_FunctionPrototypes Private Function Prototypes
* @{
*/

/**
* @}
*/

/** @defgroup FLASH_Public_Functions Public Functions
* @{
*/


/**
* @brief  Define a certain number of wait state for the system.
* @param  WaitStateNumb: Number of wait state to configure.
* @retval None
*/
void FLASH_SetWaitState(uint8_t WaitState)
{
  /* Check the parameters */
  assert_param(IS_WAIT_STATE(WaitState));
  
  FLASH->CONFIG = WaitState<<4;
}



/**
* @brief  Erases a specified FLASH sector.
* @param  sectors: Selected sector to erase.
* @retval None
*/
void FLASH_ErasePage(uint16_t PageNumber)
{
  uint16_t pageAddress;
  
  assert_param(IS_PAGE_NUMBER(PageNumber));
  
  pageAddress = (PageNumber * N_BYTES_PAGE)>>2;/* word =4 byte */
  
  /* Clear IRQ */
  FLASH->IRQRAW = 0x3F;
  
  /* Write the page address */
  FLASH->ADDRESS = pageAddress;
  
  /* Write the ERASE command */
  FLASH->COMMAND = FLASH_ERASE;
  
  FLASH_WaitBusy();
  
  /* Verify */  
  // return;
}

/**
* @brief  Erases all main Flash sectors.
* @retval None
*/
void FLASH_EraseAllMainSectors(void)
{
  /* Clear IRQ */
  FLASH->IRQRAW = 0x3F;
  
  /* Write the ERASE command */
  FLASH->COMMAND = FLASH_MASSERASE;
  
  FLASH_WaitBusy();
  
  /* Verify */  
  // return ;
}

/**
* @brief  Flash write 32 bits.
* @param  Address: address to write
* @param  Data: Data to write
* @retval None
*/
void FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  assert_param(IS_FLASH_ADDRESS(Address));
  
  /* Clear IRQ */
  FLASH->IRQRAW = 0x3F;
  
  /* Write the page address */
  FLASH->ADDRESS = Address>>2;
  
  /* Write the data to program */
  FLASH->DATA0 = Data;
  
  /* Write the ERASE command */
  FLASH->COMMAND = FLASH_WRITE;
  
  FLASH_WaitBusy();
  
  /* Verify */  
  // return ;
}

/**
* @brief  Flash write 32 bits.
* @param  WordNumber: word number
* @param  PageNumber: page number
* @param	Data: Data to write
* @retval None
*/
void FLASH_ProgramWordBurst(uint32_t WordNumber, uint32_t PageNumber, uint32_t* Data)
{
  uint16_t wordAddress;

  /*check parameter*/
  assert_param(IS_PAGE_NUMBER(PageNumber));
  assert_param(IS_WORD_NUMBER(WordNumber));
  
  /* Each WordNumber is referring to 16 bytes */
  wordAddress = (PageNumber * N_BYTES_PAGE + WordNumber * 4 * N_BYTES_WORD) >> 2;
  
//  assert_param(IS_FLASH_ADDRESS(wordAddress));
  
  /* Clear IRQ */
  FLASH->IRQRAW = 0x3F;
  
  /* Write the page address */
  FLASH->ADDRESS = wordAddress;
  
  /* Write the data to program */
  FLASH->DATA0 = Data[0];
  FLASH->DATA1 = Data[1];
  FLASH->DATA2 = Data[2];
  FLASH->DATA3 = Data[3];
  
  /* Write the ERASE command */
  FLASH->COMMAND = FLASH_BURSTWRITE;
  
  FLASH_WaitBusy();
  
  /* Verify */  
  // return ;
}


/**
* @brief  Wait loop for CMDDONE status
* @param  None
* @retval None
*/
void FLASH_WaitBusy(void)
{
  while(FLASH->IRQRAW_b.CMDDONE != SET);  
}

/**
* @brief  Enables or disables the specified FLASH interrupts.
* @param  FlashFlag: the value can be 
*         @arg Flash_CMDDONE Flash command done
*         @arg Flash_CMDSTART Flash command start
*         @arg Flash_CMDERR Flash command error
*         @arg Flash_ILLCMD Flash illegal command written
*         @arg Flash_READOK Flash mass read was OK  
*         @arg Flash_FLNREADY Flash not ready (sleep)
* @param  NewState: functional state @ref FunctionalState
*   This parameter can be: ENABLE or DISABLE.
* @retval None 
*/
void FLASH_ITConfig(uint32_t FlashFlag, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FLASH_FLAG(FlashFlag)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE) {
    SET_BIT(FLASH->IRQMASK, FlashFlag);
  }
  else {
    CLEAR_BIT(FLASH->IRQMASK, FlashFlag);
  }
}


/**
* @brief  Checks whether the specified FLASH raw flag is set or not.
* @param  FlashFlag: the FLASH flag to check, this can be
*         @arg Flash_CMDDONE Flash command done
*         @arg Flash_CMDSTART Flash command start
*         @arg Flash_CMDERR Flash command error
*         @arg Flash_ILLCMD Flash illegal command written
*         @arg Flash_READOK Flash mass read was OK  
*         @arg Flash_FLNREADY Flash not ready (sleep)
* @retval FlagStatus SET or RESET status of the requested flag
*/
FlagStatus FLASH_GetFlagStatus(uint32_t FlashFlag)
{
  /* Check the parameters */
  assert_param(IS_FLASH_FLAG(FlashFlag));
  
  if((FLASH->IRQRAW & FlashFlag) != (uint32_t)RESET) {
    return SET;
  }
  else {
    return RESET;
  }
}

/**
* @brief  Clears the specific Flash pending flags.
* @param  FlashFlag: the FLASH flag to clear, this can be
*         @arg Flash_CMDDONE Flash command done
*         @arg Flash_CMDSTART Flash command start
*         @arg Flash_CMDERR Flash command error
*         @arg Flash_ILLCMD Flash illegal command written
*         @arg Flash_READOK Flash mass read was OK  
*         @arg Flash_FLNREADY Flash not ready (sleep)
* @retval None
*/
void FLASH_ClearFlag(uint32_t FlashFlag)
{
  assert_param(IS_FLASH_FLAG(FlashFlag)) ;
  
  /* Clear the flags */
  FLASH->IRQRAW = FlashFlag;
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
