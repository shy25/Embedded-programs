/**
  ******************************************************************************
  * @file    BlueNRG1_uart.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the UART 
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
#ifndef BLUENRG1_UART_H
#define BLUENRG1_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */ 

/** @defgroup UART_Exported_Types Exported Types
  * @{
  */ 

/** 
  * @brief  UART Init Structure definition  
  */ 
typedef struct
{
  uint32_t UART_BaudRate;            /*!< This member configures the UART communication baud rate. */

  uint16_t UART_WordLengthTransmit;  /*!< Specifies the number of data bits transmitted in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */
																					 
  uint16_t UART_WordLengthReceive;   /*!< Specifies the number of data bits received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

  uint16_t UART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

  uint16_t UART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity */
 
  uint16_t UART_Mode;                /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Mode */

  uint16_t UART_HardwareFlowControl; /*!< Specifies whether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_Hardware_Flow_Control */
                                           
  FunctionalState UART_FifoEnable;          /*!< Specifies whether the FIFO is enabled or disabled.
                                           This parameter can be a value of @ref UART_Fifo_Enable */
                                           
} UART_InitType;


/**
  * @}
  */ 

/** @defgroup UART_Exported_Constants Exported Constants
  * @{
  */

#define UART_UARTCR_UARTEN      (0x0001)
#define UART_UARTCR_SIREN       (0x0002)
#define UART_UARTCR_SIRLP       (0x0004)
#define UART_UARTCR_LBE         (0x0080)

#define UART_UARTLCR_H_BRK      (0x0001)
#define UART_UARTLCR_H_PEN      (0x0002)
#define UART_UARTLCR_H_EPS      (0x0004) 
#define UART_UARTLCR_H_FEN      (0x0010)


/** @defgroup UART_Word_Length Word Length
  * @{
  */ 

#define UART_WordLength_5b                  (0)  /*!< 5-bit word length */
#define UART_WordLength_6b                  (1)  /*!< 6-bit word length */
#define UART_WordLength_7b                  (2)  /*!< 7-bit word length */
#define UART_WordLength_8b                  (3)  /*!< 8-bit word length */

/** This macro checks if LENGTH is a valid UART word length value */
#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WordLength_5b) || \
                                     ((LENGTH) == UART_WordLength_6b) || \
                                     ((LENGTH) == UART_WordLength_7b) || \
                                     ((LENGTH) == UART_WordLength_8b))
/**
  * @}
  */ 

/** @defgroup UART_Stop_Bits Stop Bits
  * @{
  */ 
  
#define UART_StopBits_1                     (0)  /*!< 1 stop bit */
#define UART_StopBits_2                     (1)  /*!< 2 stop bits */

/** This macro checks if STOPBITS is a valid UART stop bits value */
#define IS_UART_STOPBITS(STOPBITS) (((STOPBITS) == UART_StopBits_1) || \
                                     ((STOPBITS) == UART_StopBits_2))
/**
  * @}
  */ 

/** @defgroup UART_Parity Parity
  * @{
  */ 
  
#define UART_Parity_No                      (0)  /*!< No parity */
#define UART_Parity_Even                    (1)  /*!< Even parity */
#define UART_Parity_Odd                     (2)  /*!< Odd parity */

/** This macro checks if PARITY is a valid UART parity value */
#define IS_UART_PARITY(PARITY) (((PARITY) == UART_Parity_No) || \
                                 ((PARITY) == UART_Parity_Even) || \
                                 ((PARITY) == UART_Parity_Odd))
/**
  * @}
  */ 

/** @defgroup UART_Mode Mode
  * @{
  */ 
  
#define UART_Mode_Rx                        (0x01)  /*!< Enables Rx */
#define UART_Mode_Tx                        (0x02)  /*!< Enables Tx */

/** This macro checks if MODE is a valid UART mode value */
#define IS_UART_MODE(MODE) ( (MODE)<= 3)

/**
  * @}
  */ 

/** @defgroup UART_Hardware_Flow_Control Hardware Flow Control
  * @{
  */ 
#define UART_HardwareFlowControl_None       (0x00)  /*!< Disable the hardware flow control */
#define UART_HardwareFlowControl_RTS        (0x01)  /*!< Enables the RTS hardware flow control */
#define UART_HardwareFlowControl_CTS        (0x02)  /*!< Enables the CTS hardware flow control */
#define UART_HardwareFlowControl_RTS_CTS    (0x03)  /*!< Enables the RTS and CTS hardware flow control */

/** This macro checks if CONTROL is a valid UART hardware flow control value */
#define IS_UART_HARDWARE_FLOW_CONTROL(CONTROL) ( (CONTROL) <= 3 )

/**
  * @}
  */ 

/** @defgroup UART_Last_Bit Last Bit
  * @{
  */

#define UART_LastBit_Disable                ((uint16_t)0x0000)  /*!< Enables the last bit */
#define UART_LastBit_Enable                 ((uint16_t)0x0100)  /*!< Disables the last bit */

/** This macro checks if LASTBIT is a valid UART last bit value */
#define IS_UART_LASTBIT(LASTBIT) (((LASTBIT) == UART_LastBit_Disable) || \
                                   ((LASTBIT) == UART_LastBit_Enable))
/**
  * @}
  */ 

/** @defgroup UART_Interrupt_definition Interrupt definition
  * @{
  */

#define UART_IT_TXFE                (0x1000)  /*!< Tx FIFO empty interrupt */
#define UART_IT_XO                  (0x0800)  /*!< XOFF interrupt */
#define UART_IT_OE                  (0x0400)  /*!< Overrun error interrupt */
#define UART_IT_BE                  (0x0200)  /*!< Break error interrupt */
#define UART_IT_PE                  (0x0100)  /*!< Parity error interrupt */
#define UART_IT_FE                  (0x0080)  /*!< Framing error interrupt */
#define UART_IT_RT                  (0x0040)  /*!< Receive error interrupt */
#define UART_IT_TX                  (0x0020)  /*!< Transmit interrupt */
#define UART_IT_RX                  (0x0010)  /*!< Receive interrupt */
#define UART_IT_CTS                 (0x0002)  /*!< CTS interrupt */

/** This macro checks if IT is a valid combination of UART interrupt value */
#define IS_UART_CONFIG_IT(IT) ((((IT) & (uint16_t)~0x1FF2) == 0x00) && ((IT) != (uint16_t)0x0000))



/**
  * @}
  */


/** @defgroup UART_Flags Flags
  * @{
  */

#define UART_FLAG_CTS                       ((uint32_t)0x00000001)  /*!< Clear to send flag */
#define UART_FLAG_BUSY                      ((uint32_t)0x00000008)  /*!< Busy flag */
#define UART_FLAG_RXFE                      ((uint32_t)0x00000010)  /*!< Receive FIFO empty flag */
#define UART_FLAG_TXFF                      ((uint32_t)0x00000020)  /*!< Transmit FIFO full flag */
#define UART_FLAG_RXFF                      ((uint32_t)0x00000040)  /*!< Receive FIFO full flag */
#define UART_FLAG_TXFE                      ((uint32_t)0x00000080)  /*!< Transmit FIFO empty flag */

#define UART_FLAG_FE                        ((uint32_t)0x80000001)  /*!< Framing error flag */
#define UART_FLAG_PE                        ((uint32_t)0x80000002)  /*!< Parity error flag */
#define UART_FLAG_BE                        ((uint32_t)0x80000004)  /*!< Break error flag */
#define UART_FLAG_OE                        ((uint32_t)0x80000008)  /*!< Overrun error flag */

/** This macro checks if FLAG is a valid UART flag */
#define IS_UART_FLAG(FLAG) (((FLAG) == UART_FLAG_CTS) || ((FLAG) == UART_FLAG_BUSY) || \
                             ((FLAG) == UART_FLAG_RXFE) || ((FLAG) == UART_FLAG_TXFF) || \
                             ((FLAG) == UART_FLAG_RXFF) || ((FLAG) == UART_FLAG_TXFE) || \
                             ((FLAG) == UART_FLAG_OE) || ((FLAG) == UART_FLAG_FE) || \
                             ((FLAG) == UART_FLAG_PE) || ((FLAG) == UART_FLAG_BE) )

/** This macro checks if FLAG is a valid UART clearable flag */
#define IS_UART_CLEAR_FLAG(FLAG) (((FLAG) == UART_FLAG_FE) || ((FLAG) == UART_FLAG_PE) || \
                             ((FLAG) == UART_FLAG_BE) || ((FLAG) == UART_FLAG_OE)) 

/** This macro checks if BAUDRATE is a valid UART baudrate */
#define IS_UART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) <= 1000000))

/** This macro checks if DATA is a valid UART data */
#define IS_UART_DATA(DATA) ((DATA) <= 0x1FF)

/**
  * @}
  */

/** @defgroup UART_Fifo_Level FIFO Level
  * @{
  */
  
#define FIFO_LEV_1_8       (0)       /*!< Interrupt FIFO becomes >= 1/8 full */
#define FIFO_LEV_1_4       (1)       /*!< Interrupt FIFO becomes >= 1/4 full */
#define FIFO_LEV_1_2       (2)       /*!< Interrupt FIFO becomes >= 1/2 full */
#define FIFO_LEV_3_4       (3)       /*!< Interrupt FIFO becomes >= 3/4 full */
#define FIFO_LEV_7_8       (4)       /*!< Interrupt FIFO becomes >= 7/8 full */

/** This macro checks if TX_FIFO_LEV is a valid Tx FIFO level */
#define IS_FIFO_LEV(FIFO_LEV) ( ((FIFO_LEV) == FIFO_LEV_1_8) || \
                                ((FIFO_LEV) == FIFO_LEV_1_4) || \
                                ((FIFO_LEV) == FIFO_LEV_1_2) || \
                                ((FIFO_LEV) == FIFO_LEV_3_4) || \
                                ((FIFO_LEV) == FIFO_LEV_7_8))

/**
  * @}
  */

/** @defgroup USART_DMA_Requests 
  * @{
  */

#define USART_DMAReq_Tx                      ((uint8_t)0x02)
#define USART_DMAReq_Rx                      ((uint8_t)0x01)
#define IS_USART_DMAREQ(DMAREQ) (DMAREQ<(uint8_t)4 && DMAREQ!=(uint8_t)0 )

/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup UART_Exported_Macros Exported Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup UART_Exported_Functions Exported Functions
  * @{
  */

void UART_Init(UART_InitType* UART_InitStruct);
void UART_StructInit(UART_InitType* UART_InitStruct);
void UART_Cmd(FunctionalState NewState);
void UART_ITConfig(uint16_t UART_IT, FunctionalState NewState);
void UART_SendData(uint16_t Data);
uint16_t UART_ReceiveData(void);
void UART_BreakCmd(FunctionalState NewState);
FlagStatus UART_GetFlagStatus(uint32_t UART_FLAG);
void UART_ClearFlag(uint32_t UART_FLAG);
ITStatus UART_GetITStatus(uint16_t UART_IT);
void UART_ClearITPendingBit(uint16_t UART_IT);
void UART_FifoInterruptLevelConfig(uint8_t UART_TX_FIFO_LEV, uint8_t UART_RX_FIFO_LEV);

void USART_DMACmd(uint8_t USART_DMAReq, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* BLUENRG1_UART_H */
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
