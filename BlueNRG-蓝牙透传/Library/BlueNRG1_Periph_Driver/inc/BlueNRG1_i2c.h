/**
  ******************************************************************************
  * @file    BlueNRG1_i2c.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the I2C firmware 
  *          library.
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
#ifndef BLUENRG1_I2C_H
#define BLUENRG1_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Types Exported Types
  * @{
  */

/** 
  * @brief  I2C Init structure definition  
  */

typedef struct
{
  uint32_t I2C_ClockSpeed;          /*!< Specifies the clock frequency.
                                         This parameter must be set to a value lower than 3.4MHz */
  
  uint32_t I2C_OperatingMode;       /*!< Specifies the I2C frequency.
                                         This parameter can be a value of @ref I2C_operating_mode */
                                         
  uint32_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode */
  
  uint16_t I2C_Filtering;           /*!< Specifies the I2C filtering.
                                         This parameter can be a value of @ref I2C_filtering */

  uint16_t I2C_OwnAddress1;         /*!< Specifies the first device own address. */
  

  uint16_t I2C_AddressingMode;      /*!< Specifies if 7-bit or 10-bit address is used.
                                         This parameter can be a value of @ref I2C_addressing_mode */
} I2C_InitType;


/** 
  * @brief  I2C Transaction structure definition  
  */
typedef struct {
  uint16_t Operation;               /*!< Specifies the transaction operation: read or write.
                                         This parameter can be a value of @ref I2C_operation */
  
  uint16_t Address;                 /*!< Slave address. */
  
  uint16_t StartByte;               /*!< Enables or disables the start byte.
                                         This parameter can be a value of @ref I2C_start_byte */
  
  uint16_t AddressType;             /*!< Specifies the address type.
                                         This parameter can be a value of @ref I2C_address_type */
  
  uint16_t StopCondition;           /*!< Enables or disables the stop condition.
                                         This parameter can be a value of @ref I2C_stop_condition */
  
  uint16_t Length;                  /*!< Specifies the length of the transaction (number of bytes).
                                         This parameter can be a value of @ref I2C_stop_condition */
} I2C_TransactionType;

/**
  * @}
  */ 

/** 
  * @brief  I2C operation status 
  */
typedef enum {
  I2C_NOP = 0,												/*! <NOP: No operation is in progress */
  I2C_OP_ONGOING = 1,									/*! <ON_GOING: An operation is ongoing */
  I2C_OP_OK = 2,											/*! OK: The operation (OP field) has been completed successfully */
  I2C_OP_ABORTED = 3									/*! <ABORT: The operation (OP field) has been aborted due to the
  																		     occurrence of the event described in the CAUSE field. */
} OP_Status_t;
/**
  * @}
  */ 
  
/** @defgroup I2C_Exported_Constants Exported Constants
  * @{
  */
#define I2C_CR_PE               (0x00000001)

#define I2C_CR_OM_SLAVE         (0x00000000)
#define I2C_CR_OM_MASTER        (0x00000002)
#define I2C_CR_OM_MASTER_SLAVE  (0x00000004)
#define I2C_CR_OM_MSK           (0x00000006)

#define I2C_CR_SAM_7BIT         (0x00000000)
#define I2C_CR_SAM_10BIT        (0x00000004)
#define I2C_CR_SAM_MSK          (0x00000004)

#define I2C_CR_SM_STD           (0x0)
#define I2C_CR_SM_FAST          (0x1)
#define I2C_CR_SM_MSK           (0x3)

#define I2C_CR_SGCM             (0x00000040)

#define I2C_CR_FTX              (0x00000080)
#define I2C_CR_FRX              (0x00000100)

#define I2C_CR_FON_MSK          (0x00006000)

/** This macro checks if PERIPH is a valid I2C peripheral */
#define IS_I2C_ALL_PERIPH(PERIPH) (((PERIPH) == I2C1) || \
                                   ((PERIPH) == I2C2))

#define IS_I2C_TX_THRESHOLD(TXTHR)  ((TXTHR) <= 8)

#define IS_I2C_RX_THRESHOLD(RXTHR)  ((RXTHR) <= 8)

/** @defgroup I2C_filtering Filtering
  * @{
  */

#define I2C_Filtering_Off         ((uint16_t)0x0)    /*!< Disables filtering */
#define I2C_Filtering_1Ck_Spike   ((uint16_t)0x2)   /*!< Filters 1 clock spikes */
#define I2C_Filtering_2Ck_Spikes  ((uint16_t)0x4)   /*!< Filters 2 clock spikes */
#define I2C_Filtering_4Ck_Spikes  ((uint16_t)0x6)   /*!< Filters 4 clock spikes */

/** This macro checks if FILTER is a valid filtering value */
#define IS_I2C_FILTERING(FILTER) (((FILTER) == I2C_Filtering_Off) || \
                           ((FILTER) == I2C_Filtering_1Ck_Spike) || \
                           ((FILTER) == I2C_Filtering_2Ck_Spikes) || \
                           ((FILTER) == I2C_Filtering_4Ck_Spikes))
/**
  * @}
  */


/** @defgroup I2C_operating_mode Operating Mode
  * @{
  */

#define I2C_OperatingMode_Slave         (0x00000000)    /*!< Slave */
#define I2C_OperatingMode_Master        (0x00000001)    /*!< Master */
#define I2C_OperatingMode_MasterSlave   (0x00000002)    /*!< Master/Slave */

/** This macro checks if MODE is a valid operating mode */
#define IS_I2C_OPERATING_MODE(MODE) (((MODE) == I2C_OperatingMode_Master) || \
                                    ((MODE) == I2C_OperatingMode_Slave) || \
                                    ((MODE) == I2C_OperatingMode_MasterSlave))
/**
  * @}
  */


/** @defgroup I2C_addressing_mode Addressing mode
  * @{
  */

#define I2C_AddressingMode_7bit    ((uint16_t)I2C_CR_SAM_7BIT)    /*!< 7-bit address */
#define I2C_AddressingMode_10bit   ((uint16_t)I2C_CR_SAM_10BIT)   /*!< 10-bit address */

/** This macro checks if ADDRESS is a valide addressing mode */
#define IS_I2C_ADDRESSING_MODE(ADDRESS) (((ADDRESS) == I2C_AddressingMode_7bit) || \
                                             ((ADDRESS) == I2C_AddressingMode_10bit))
/**
  * @}
  */

/** @defgroup I2C_operation Operation
  * @{
  */

#define I2C_Operation_Write               ((uint8_t)0)    /*!< Write operation */
#define I2C_Operation_Read                ((uint8_t)1)    /*!< Read operation */

/** This macro checks if OP is a valid operation */
#define IS_I2C_OPERATION(OP) (((OP) == I2C_Operation_Write) || \
                              ((OP) == I2C_Operation_Read))

/**
  * @}
  */
  
/** @defgroup I2C_start_byte Start byte
  * @{
  */

#define I2C_StartByte_Disable             ((uint16_t)0x0000)    /*!< Disables the start byte */
#define I2C_StartByte_Enable              ((uint16_t)0x0800)    /*!< Enables the start byte */

/** This macro checks if SB is a valid StartByte value */
#define IS_I2C_STARTBYTE(SB) (((SB) == I2C_StartByte_Disable) || \
                              ((SB) == I2C_StartByte_Enable))

/**
  * @}
  */

/** @defgroup I2C_address_type Address type
  * @{
  */

#define I2C_AddressType_GeneralCall       ((uint16_t)0x0000)    /*!< General call address type */
#define I2C_AddressType_7Bit              ((uint16_t)0x1000)    /*!< 7-bit address type */
#define I2C_AddressType_10Bit             ((uint16_t)0x2000)    /*!< 10-bit address type */

/** This macro checks if AT is a valid address type */
#define IS_I2C_ADDRESSTYPE(AT) (((AT) == I2C_AddressType_GeneralCall) || \
                                ((AT) == I2C_AddressType_7Bit) || \
                                ((AT) == I2C_AddressType_10Bit))

/**
  * @}
  */

/** @defgroup I2C_stop_condition Stop condition
  * @{
  */

#define I2C_StopCondition_Disable         ((uint16_t)0x0000)    /*!< Disables the stop condition */
#define I2C_StopCondition_Enable          ((uint16_t)0x4000)    /*!< Enables the stop condition */

/** This macro checks if P is a valid stop condition */
#define IS_I2C_STOPCONDITION(P) (((P) == I2C_StopCondition_Disable) || \
                                  ((P) == I2C_StopCondition_Enable))

#define IS_I2C_LENGTH(P)      ((P) <= 0x7FF)

/**
  * @}
  */


/** @defgroup I2C_interrupts_definition Interrupts definition
  * @{
  */
#define I2C_IT_TXFE                     (0x00000001)  /*!< Tx FIFO empty */
#define I2C_IT_TXFNE                    (0x00000002)  /*!< Tx FIFO nearly empty */
#define I2C_IT_TXFF                     (0x00000004)  /*!< Tx FIFO full */
#define I2C_IT_TXFOVR                   (0x00000008)  /*!< Tx FIFO overflow */
#define I2C_IT_RXFE                     (0x00000010)  /*!< Rx FIFO empty */
#define I2C_IT_RXFNF                    (0x00000020)  /*!< Rx FIFO nearly full */
#define I2C_IT_RXFF                     (0x00000040)  /*!< Rx FIFO full */
#define I2C_IT_LBR                      (0x00008000)  /*!< Length number of bytes received */
#define I2C_IT_RFSR                     (0x00010000)  /*!< Read-from-Slave request */
#define I2C_IT_RFSE                     (0x00020000)  /*!< Read-from-Slave empty */
#define I2C_IT_WTSR                     (0x00040000)  /*!< Write-to-Slave request */
#define I2C_IT_MTD                      (0x00080000)  /*!< Master transaction done */
#define I2C_IT_STD                      (0x00100000)  /*!< Slave transaction done */
#define I2C_IT_SAL                      (0x00800000)  /*!< Slave arbitration lost */
#define I2C_IT_MAL                      (0x01000000)  /*!< Master arbitration lost */
#define I2C_IT_BERR                     (0x02000000)  /*!< Bus error */
#define I2C_IT_MTDWS                    (0x10000000)  /*!< Master transaction done without stop */
#define I2C_IT_TIMEOUT                  (0x40000000)  /*!< Timeout or Tlow error */
#define I2C_IT_MSK                      (0x739F807F)  /*!< Interrupt mask */

/** This macro checks if IT is a valid combination of interrupt */
#define IS_I2C_IT(IT) ((((IT) & ~I2C_IT_MSK) == 0x00) && ((IT) != 0x00))

/**
  * @}
  */ 
  
/** @defgroup I2C_own_address1 Own address 1
  * @{
  */

/** This macro checks if ADDRESS1 is a valid address value */
#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x3FF)

/** This macro checks if  ADDRESS2 is a valid address value */
#define IS_I2C_OWN_ADDRESS(ADDRESS2) ((ADDRESS2) <= 0x7F)

/**
  * @}
  */

/** @defgroup I2C_clock_speed Clock speed
  * @{
  */

/** This macro checks if I2C baud rate is a valid value */
#define IS_I2C_CLOCK_SPEED_I2C(SPEED) (((SPEED) >= 1) && ((SPEED) <= 400000))

/**
  * @}
  */


/** @defgroup I2C_DMA_Requests 
  * @{
  */

#define I2C_DMAReq_Tx                      ((uint16_t)0x0200)
#define I2C_DMAReq_Rx                      ((uint16_t)0x0400)
#define IS_I2C_DMAREQ(DMAREQ) ((DMAREQ==I2C_DMAReq_Tx) || (DMAREQ==I2C_DMAReq_Rx))

/**
  * @}
  */ 

/**
  * @}
  */

/** @defgroup I2C_Exported_Functions Exported Functions
  * @{
  */
void I2C_Init(I2C_Type* I2Cx, I2C_InitType* I2C_InitStruct);
void I2C_StructInit(I2C_InitType* I2C_InitStruct);
void I2C_Cmd(I2C_Type* I2Cx, FunctionalState NewState);
void I2C_BeginTransaction(I2C_Type* I2Cx, I2C_TransactionType* tr);
void I2C_NotAcknowledgeConfig(I2C_Type* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_Type* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_Type* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_Type* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_Type* I2Cx, uint32_t I2C_IT, FunctionalState NewState);
void I2C_FillTxFIFO(I2C_Type* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_Type* I2Cx);
void I2C_FlushTx(I2C_Type* I2Cx);
void I2C_FlushRx(I2C_Type* I2Cx);
void I2C_SetTxThreshold(I2C_Type* I2Cx, uint16_t TxThres);
void I2C_SetRxThreshold(I2C_Type* I2Cx, uint16_t RxThres);
void I2C_SoftwareResetCmd(I2C_Type* I2Cx, FunctionalState NewState);
void I2C_TransmitPEC(I2C_Type* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_Type* I2Cx);
void I2C_ARPCmd(I2C_Type* I2Cx, FunctionalState NewState);
ITStatus I2C_GetITStatus(I2C_Type* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_Type* I2Cx, uint32_t I2C_IT);
OP_Status_t I2C_GetStatus(I2C_Type* I2Cx);
void I2C_DMACmd(I2C_Type* I2Cx, uint16_t I2C_DMAReq, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*BLUENRG1_I2C_H */

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
