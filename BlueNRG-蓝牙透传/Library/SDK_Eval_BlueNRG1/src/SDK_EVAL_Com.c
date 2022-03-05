
/* Includes ------------------------------------------------------------------*/
#include "SDK_EVAL_Com.h"
#include <stdio.h>

/**
 * @brief  IO_Receive_Data User callback 
 */
typedef struct _IO_ReceiveCallBack
{
  /**
   * callback to notify the applicatio with the received I/O data
   */ 
  IO_RECEIVE_DATA_USER_CALLBACK_TYPE IO_user_application;
} IO_ReceiveCallBack;

/* IO User Callback used to handle received data from I/O channel*/
static IO_ReceiveCallBack IO_Receive_Data;

/**
 * @brief  Send a byte on Serial port
 * @param  tx_data byte to be sent
 * @retval None
 */
static void SdkEvalUart_Send_Data(uint8_t tx_data)
{
  /* wait for the transmission end */
  while (UART_GetFlagStatus(UART_FLAG_TXFE) == RESET);
  /* send the data */
  UART_SendData(tx_data);
}/* end SdkEvalUart_Send_Data() */


/**
 * @brief  Configures Uart port.
 * @param  baudrate UART baudrate
 * @retval None
 */
void SdkEvalComUartInit(uint32_t baudrate)
{
  UART_InitType UART_InitStructure;
  
  /* GPIO Periph clock enable */
  CRMU_PeripheralClockCmd(CRMU_PERIPH_UART | CRMU_PERIPH_GPIO, ENABLE);
  
  GPIO_InitType GPIO_InitStructure;
  
  /* Configure GPIO_Pin_8 and GPIO_Pin_11 as UART_TXD and UART_RXD*/
  GPIO_InitStructure.GPIO_Pin = SDK_EVAL_UART_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = SDK_EVAL_UART_TX_MODE;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_Init(&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = SDK_EVAL_UART_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = SDK_EVAL_UART_RX_MODE;
  GPIO_Init(&GPIO_InitStructure);

  /* 
  ------------ USART configuration -------------------
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  UART_InitStructure.UART_BaudRate = baudrate;
  UART_InitStructure.UART_WordLengthTransmit = UART_WordLength_8b;
  UART_InitStructure.UART_WordLengthReceive = UART_WordLength_8b;
  UART_InitStructure.UART_StopBits = UART_StopBits_1;
//  UART_InitStructure.UART_Parity = UART_Parity_No;
  UART_InitStructure.UART_Parity = UART_Parity_Even;

  UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
  UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;
  UART_InitStructure.UART_FifoEnable = DISABLE;
  UART_Init(&UART_InitStructure);

  /* Enable USART */
  UART_Cmd(ENABLE);
}


/**
 * @brief  Enable UART IRQ request.
 * @param  EnableIrq: functional state @ref FunctionalState
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void SdkEvalComUartIrqConfig(FunctionalState EnableIrq)
{
    /* NVIC configuration */
    NVIC_InitType NVIC_InitStructure;

    /* Enable the UART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = UART_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LOW_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd = EnableIrq;
    NVIC_Init(&NVIC_InitStructure);

    UART_ITConfig(UART_IT_RX, EnableIrq);
    
}


/**
 * @brief  Serial IRQ handler body to be put on user USART_IRQHandler()
 * @param  None
 * @retval None
 */
void SdkEvalComIOUartIrqHandler(void)
{
  uint8_t read_data; 

  if(UART_GetITStatus(UART_IT_RX) != RESET)   {

     while(!UART_GetFlagStatus(UART_FLAG_RXFE)) {

      /* Read byte from the receive FIFO */
      read_data = (uint8_t) (UART_ReceiveData() & 0xFF);
     
      /* IO Receive Data: it handles the received data within the  User Application Function 
         defined as parameter of SdkEvalComIOConfig() */
      SdkEvalComIOReceiveData(&read_data,1);
     }
     /* Clear the USART1 Receive interrupt */
     UART_ClearITPendingBit(UART_IT_RX);
   }  
}


/**
 * @brief  Configure the selected I/O communciation channel
 * @param  io_receive_function user callback
 * @retval None
 */
void SdkEvalComIOConfig(IO_RECEIVE_DATA_USER_CALLBACK_TYPE io_receive_function)
{
  IO_Receive_Data.IO_user_application = io_receive_function;
  /* Init Serial Uart */
  SdkEvalComUartInit(UART_BAUDRATE);
  SdkEvalComUartIrqConfig(ENABLE);
}


/**
 * @brief  Send a byte on selected I/O port
 * @param  tx_data byte to be sent
 * @retval None
 */
void SdkEvalComIOSendData(uint8_t tx_data)
{
  SdkEvalUart_Send_Data(tx_data);
}

/**
 * @brief  Receive data on selected I/O port
 * @param  rx_data pointer to buffer of received
 * @param  data_size number of received data 
 * @retval None
 */
void SdkEvalComIOReceiveData(uint8_t * rx_data, uint16_t data_size)
{
  if(IO_Receive_Data.IO_user_application)
    IO_Receive_Data.IO_user_application(rx_data,data_size);
}


#ifdef __CC_ARM

#include <stdio.h>

/* keil debug port defines */
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

/* KEIL fputc implementation template allowing to redirect printf output towards serial port (USART/USB) */
int fputc(int c, FILE *f) {

  SdkEvalComIOSendData((uint8_t) c);
  
  return 1;
  
}

#endif

