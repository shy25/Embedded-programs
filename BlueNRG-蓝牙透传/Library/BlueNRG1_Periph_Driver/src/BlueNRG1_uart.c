/**
  ******************************************************************************
  * @file    BlueNRG1_uart.c
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file provides all the UART firmware functions.
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
#include "BlueNRG1_uart.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @defgroup UART UART Driver
  * @{
  */

/** @defgroup UART_Private_TypesDefinitions Private Types Definitions
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_Defines Private Defines
  * @{
  */
#define UART_CLOCK       (16000000)

/**
  * @}
  */

/** @defgroup UART_Private_Macros Private Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_Variables Private Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_FunctionPrototypes Private Function Prototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Public_Functions Public Functions
  * @{
  */


/**
  * @brief  Enables or disables the USART peripheral.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE) {
    /* Enable the selected UART by setting the UARTEN bit in the UARTCR register */
    UART->CR_b.UARTEN = SET;
  }
  else {
    /* Disable the selected UART by clearing the UARTEN bit in the UARTCR register */
    UART->CR_b.UARTEN = RESET;
  }
}

/**
  * @brief  Initializes the UART peripheral according to the specified
  *         parameters in the UART_InitStruct.
  * @param  UART_InitStruct: pointer to a @ref UART_InitType structure
  *         that contains the configuration information for the specified UART.
  * @retval None
  */
void UART_Init(UART_InitType* UART_InitStruct)
{
  uint32_t divider;
  uint16_t ibrd, fbrd;

  /* Check the parameters */
  assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));  
  assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLengthTransmit));
  assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLengthReceive));
  assert_param(IS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
  assert_param(IS_UART_PARITY(UART_InitStruct->UART_Parity));
  assert_param(IS_UART_MODE(UART_InitStruct->UART_Mode));
  assert_param(IS_UART_HARDWARE_FLOW_CONTROL(UART_InitStruct->UART_HardwareFlowControl));
  assert_param(IS_FUNCTIONAL_STATE(UART_InitStruct->UART_FifoEnable));
  
  /*---------------------------- UART BaudRate Configuration -----------------------*/
  /*<<7 然后再 >>7 是为了提高精确度 add by zhangsb, 2018-05-09 */
  divider = (UART_CLOCK<<7) / (16 * UART_InitStruct->UART_BaudRate);
  
  ibrd = divider >> 7;
  UART->IBRD = ibrd;
  fbrd = ((divider - (ibrd <<7) + 1) >> 1);
  if (fbrd > 0x3f) {
    ibrd++;
    fbrd = (fbrd - 0x3F) & 0x3F;
  }
  UART->FBRD = fbrd;    
  
  /*---------------------------- UART Word Length Configuration -----------------------*/
	UART->LCRH_TX_b.WLEN_TX = UART_InitStruct->UART_WordLengthTransmit;
	UART->LCRH_RX_b.WLEN_RX = UART_InitStruct->UART_WordLengthReceive;
  
  /*---------------------------- UART Stop Bits Configuration -----------------------*/
	UART->LCRH_TX_b.STP2_TX = UART_InitStruct->UART_StopBits;
  
  /*---------------------------- UART Parity Configuration -----------------------*/
  if(UART_InitStruct->UART_Parity == UART_Parity_No) {
    UART->LCRH_TX_b.PEN_TX = RESET;
  }
  else if(UART_InitStruct->UART_Parity == UART_Parity_Odd) {
    UART->LCRH_TX_b.PEN_TX = SET;
    UART->LCRH_TX_b.EPS_TX = RESET;
  }
  else {
    UART->LCRH_TX_b.PEN_TX = SET;
    UART->LCRH_TX_b.EPS_TX = SET;    
  }

  /*---------------------------- UART Mode Configuration -----------------------*/
  UART->CR_b.RXE = UART_InitStruct->UART_Mode&1;
  UART->CR_b.TXE = (UART_InitStruct->UART_Mode>>1)&1;

  /*---------------------------- UART Hardware flow control Configuration -----------------------*/
  UART->CR_b.RTSEN = UART_InitStruct->UART_HardwareFlowControl&1;
  UART->CR_b.CTSEN = (UART_InitStruct->UART_HardwareFlowControl>>1)&1;


  /*---------------------------- UART Fifo Configuration -----------------------*/
  UART->LCRH_TX_b.FEN_TX = (uint8_t)UART_InitStruct->UART_FifoEnable;

}

/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a @ref UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitType* UART_InitStruct)
{
  /* UART_InitStruct members default value */
  UART_InitStruct->UART_BaudRate = 115200;
  UART_InitStruct->UART_WordLengthTransmit = UART_WordLength_8b;
  UART_InitStruct->UART_WordLengthReceive = UART_WordLength_8b;
  UART_InitStruct->UART_StopBits = UART_StopBits_1;
  UART_InitStruct->UART_Parity = UART_Parity_No;
  UART_InitStruct->UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
  UART_InitStruct->UART_HardwareFlowControl = UART_HardwareFlowControl_None; 
  UART_InitStruct->UART_FifoEnable = DISABLE;
}

/**
  * @brief  Enables or disables the specified UART interrupts.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *   This parameter can be a any combination of the following values:
	*   @arg UART_IT_TXFE:  Tx FIFO empty interrupt
  *   @arg UART_IT_XO:    XOFF interrupt
  *   @arg UART_IT_OE:    Overrun error interrupt
  *   @arg UART_IT_BE:    Break error interrupt
  *   @arg UART_IT_PE:    Parity error interrupt
  *   @arg UART_IT_FE:    Framing error interrupt
  *   @arg UART_IT_RT:    Receive timeout interrupt
  *   @arg UART_IT_TX:    Transmit interrupt
  *   @arg UART_IT_RX:    Receive interrupt
  *   @arg UART_IT_CTS:   CTS interrupt.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(uint16_t UART_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_CONFIG_IT(UART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE) {
    /* Enable specified interrupts */
    SET_BIT(UART->IMSC, UART_IT);
  }
  else {
    /* Disable specified interrupts */
    CLEAR_BIT(UART->IMSC, UART_IT);
  }
}

/**
  * @brief  Transmits single data through the UART peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void UART_SendData(uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_UART_DATA(Data)); 
    
  /* Transmit Data */
  UART->DR = (Data & (uint16_t)0x01FF);
}

/**
  * @brief  Returns the most recent received data by the UART peripheral.
  * @param  None
  * @retval uint16_t: The received data.
  */
uint16_t UART_ReceiveData(void)
{
  /* Check the parameters */
  
  /* Receive Data */
  return (uint16_t)(UART->DR & 0x00FF);
}

/**
  * @brief  Enables or disables the break command.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_BreakCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  UART->LCRH_TX_b.BRK = (uint8_t)NewState;
}


/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UART_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg UART_FLAG_CTS:   Clear to send
  *     @arg UART_FLAG_BUSY:  UART busy
  *     @arg UART_FLAG_RXFE:  Receive FIFO empty
  *     @arg UART_FLAG_TXFF:  Transmit FIFO full
  *     @arg UART_FLAG_RXFF:  Receive FIFO full
  *     @arg UART_FLAG_TXFE:  Transmit FIFO empty
  *     @arg UART_FLAG_FE:    Framing error
  *     @arg UART_FLAG_PE:    Parity error
  *     @arg UART_FLAG_BE:    Break error
  *     @arg UART_FLAG_OE:    Overrun error.
* @retval FlagStatus: functional state @ref FlagStatus
*         This parameter can be: SET or RESET.
  */
FlagStatus UART_GetFlagStatus(uint32_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_UART_FLAG(UART_FLAG));
  
  if (UART_FLAG & 0x80000000) {//出错的处理
    if (UART->RSR & UART_FLAG) {
      return SET;
    }
    else {
      return RESET;
    }
  }
  else {
    if (UART->FR & UART_FLAG) {
      return SET;
    }
    else {
      return RESET;
    }  
  }
  
}

/**
  * @brief  Clears the UART pending flags.
  * @param  UART_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg UART_FLAG_FE:  Framing error
  *     @arg UART_FLAG_PE:  Parity error
  *     @arg UART_FLAG_BE:  Break error
  *     @arg UART_FLAG_OE:  Overrun error
  * @retval None
  */
void UART_ClearFlag(uint32_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_UART_CLEAR_FLAG(UART_FLAG));
   
  UART->ECR = UART_FLAG;
}

/**
  * @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  UART_IT: specifies the UART interrupt source to check.
  *   This parameter can be one of the following values:
	*   @arg UART_IT_TXFE:  Tx FIFO empty interrupt
  *   @arg UART_IT_XO:    XOFF interrupt
  *   @arg UART_IT_OE:    Overrun error interrupt
  *   @arg UART_IT_BE:    Break error interrupt
  *   @arg UART_IT_PE:    Parity error interrupt
  *   @arg UART_IT_FE:    Framing error interrupt
  *   @arg UART_IT_RT:    Receive timeout interrupt
  *   @arg UART_IT_TX:    Transmit interrupt
  *   @arg UART_IT_RX:    Receive interrupt
  *   @arg UART_IT_CTS:   CTS interrupt
  * @retval  ITStatus: functional state @ref ITStatus
  *         This parameter can be: SET or RESET.
  */
ITStatus UART_GetITStatus(uint16_t UART_IT)
{
  /* Check the parameters */
  assert_param(IS_UART_CONFIG_IT(UART_IT));
   
  if ((UART->RIS & UART_IT) != (uint16_t)RESET) {
    return SET;
  }
  else {
    return RESET;
  }  
}

/**
  * @brief  Clears the UART interrupt pending bits.
  * @param  UART_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
	*   @arg UART_IT_TXFE:  Tx FIFO empty interrupt
  *   @arg UART_IT_XO:    XOFF interrupt
  *   @arg UART_IT_OE:    Overrun error interrupt
  *   @arg UART_IT_BE:    Break error interrupt
  *   @arg UART_IT_PE:    Parity error interrupt
  *   @arg UART_IT_FE:    Framing error interrupt
  *   @arg UART_IT_RT:    Receive timeout interrupt
  *   @arg UART_IT_TX:    Transmit interrupt
  *   @arg UART_IT_RX:    Receive interrupt
  *   @arg UART_IT_CTS:   CTS interrupt
  *   
  * @retval None
  */
void UART_ClearITPendingBit(uint16_t UART_IT)
{
  /* Check the parameters */
  assert_param(IS_UART_CONFIG_IT(UART_IT));
  
  UART->ICR = UART_IT;
}


/**
  * @brief  Sets the UART interrupt FIFO level.
  * @param  UART_TX_FIFO_LEV: specifies the transmit interrupt FIFO level.
  *   This parameter can be one of the following values:
  *   @arg FIFO_TX_LEV_1_8: interrupt when Tx FIFO becomes <= 1/8 full 
  *   @arg FIFO_TX_LEV_1_4: interrupt when Tx FIFO becomes <= 1/4 full 
  *   @arg FIFO_TX_LEV_1_2: interrupt when Tx FIFO becomes <= 1/2 full 
  *   @arg FIFO_TX_LEV_3_4: interrupt when Tx FIFO becomes <= 3/4 full 
  *   @arg FIFO_TX_LEV_7_8: interrupt when Tx FIFO becomes <= 7/8 full 
  * @param  UART_RX_FIFO_LEV: specifies the receive interrupt FIFO level.
  *   This parameter can be one of the following values:
  *   @arg FIFO_RX_LEV_1_8: interrupt when Rx FIFO becomes >= 1/8 full 
  *   @arg FIFO_RX_LEV_1_4: interrupt when Rx FIFO becomes >= 1/4 full 
  *   @arg FIFO_RX_LEV_1_2: interrupt when Rx FIFO becomes >= 1/2 full 
  *   @arg FIFO_RX_LEV_3_4: interrupt when Rx FIFO becomes >= 3/4 full 
  *   @arg FIFO_RX_LEV_7_8: interrupt when Rx FIFO becomes >= 7/8 full 
  *   
  * @retval None
  */
void UART_FifoInterruptLevelConfig(uint8_t UART_TX_FIFO_LEV, uint8_t UART_RX_FIFO_LEV)
{
    /* Check the parameters */
  assert_param(IS_FIFO_LEV(UART_TX_FIFO_LEV));
  assert_param(IS_FIFO_LEV(UART_RX_FIFO_LEV));

  UART->IFLS_b.TXIFLSEL = UART_TX_FIFO_LEV;
  UART->IFLS_b.RXIFLSEL = UART_RX_FIFO_LEV;
}


/**
  * @brief  Enables or disables the USART DMA interface.
  * @param  USART_DMAReq: specifies the DMA request.
  *   This parameter can be any combination of the following values:
  *     @arg USART_DMAReq_Tx: USART DMA transmit request.
  *     @arg USART_DMAReq_Rx: USART DMA receive request.
  * @param  NewState: functional state @ref FunctionalState
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void USART_DMACmd(uint8_t USART_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  if (NewState != DISABLE)
  {
    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
       DMAR bits in the USART CR3 register */
    UART->DMACR |= USART_DMAReq;
  }
  else
  {
    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
       DMAR bits in the USART CR3 register */
    UART->DMACR &= (uint8_t)~USART_DMAReq;
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
