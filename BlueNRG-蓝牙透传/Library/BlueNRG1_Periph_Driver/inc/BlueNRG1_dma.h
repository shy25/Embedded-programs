/**
  ******************************************************************************
  * @file    BlueNRG1_dma.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the DMA firmware 
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
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLUENRG1_DMA_H
#define BLUENRG1_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA DMA Driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  DMA Init structure definition
  */

typedef struct
{
  uint32_t DMA_PeripheralBaseAddr; /*!< Specifies the peripheral base address for DMAy Channelx. */

  uint32_t DMA_MemoryBaseAddr;     /*!< Specifies the memory base address for DMAy Channelx. */

  uint32_t DMA_DIR;                /*!< Specifies if the peripheral is the source or destination.
                                        This parameter can be a value of @ref DMA_data_transfer_direction */

  uint32_t DMA_BufferSize;         /*!< Specifies the buffer size, in data unit, of the specified Channel. 
                                        The data unit is equal to the configuration set in DMA_PeripheralDataSize
                                        or DMA_MemoryDataSize members depending in the transfer direction. */

  uint32_t DMA_PeripheralInc;      /*!< Specifies whether the Peripheral address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */

  uint32_t DMA_MemoryInc;          /*!< Specifies whether the memory address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode */

  uint32_t DMA_PeripheralDataSize; /*!< Specifies the Peripheral data width.
                                        This parameter can be a value of @ref DMA_peripheral_data_size */

  uint32_t DMA_MemoryDataSize;     /*!< Specifies the Memory data width.
                                        This parameter can be a value of @ref DMA_memory_data_size */

  uint32_t DMA_Mode;               /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_circular_normal_mode.
                                        @note: The circular buffer mode cannot be used if the memory-to-memory
                                              data transfer is configured on the selected Channel */

  uint32_t DMA_Priority;           /*!< Specifies the software priority for the DMAy Channelx.
                                        This parameter can be a value of @ref DMA_priority_level */

  uint32_t DMA_M2M;                /*!< Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
                                        This parameter can be a value of @ref DMA_memory_to_memory */
}DMA_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants
  * @{
  */

#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA_CH0) || \
                                   ((PERIPH) == DMA_CH1) || \
                                   ((PERIPH) == DMA_CH2) || \
                                   ((PERIPH) == DMA_CH3) || \
                                   ((PERIPH) == DMA_CH4) || \
                                   ((PERIPH) == DMA_CH5) || \
                                   ((PERIPH) == DMA_CH6) || \
                                   ((PERIPH) == DMA_CH7))

/** @defgroup DMA_data_transfer_direction 
  * @{
  */

#define DMA_DIR_PeripheralDST              ((uint32_t)0x00000010)
#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)
#define IS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralDST) || \
                         ((DIR) == DMA_DIR_PeripheralSRC))
/**
  * @}
  */

/** @defgroup DMA_peripheral_incremented_mode 
  * @{
  */

#define DMA_PeripheralInc_Enable           ((uint32_t)0x00000040)
#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)
#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Enable) || \
                                            ((STATE) == DMA_PeripheralInc_Disable))
/**
  * @}
  */

/** @defgroup DMA_memory_incremented_mode 
  * @{
  */

#define DMA_MemoryInc_Enable               ((uint32_t)0x00000080)
#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)
#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Enable) || \
                                        ((STATE) == DMA_MemoryInc_Disable))
/**
  * @}
  */

/** @defgroup DMA_peripheral_data_size 
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    ((uint32_t)0x00000100)
#define DMA_PeripheralDataSize_Word        ((uint32_t)0x00000200)
#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || \
                                           ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
                                           ((SIZE) == DMA_PeripheralDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_memory_data_size 
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        ((uint32_t)0x00000400)
#define DMA_MemoryDataSize_Word            ((uint32_t)0x00000800)
#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word))
/**
  * @}
  */

/** @defgroup DMA_circular_normal_mode 
  * @{
  */

#define DMA_Mode_Circular                  ((uint32_t)0x00000020)
#define DMA_Mode_Normal                    ((uint32_t)0x00000000)
#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Circular) || ((MODE) == DMA_Mode_Normal))
/**
  * @}
  */

/** @defgroup DMA_priority_level 
  * @{
  */

#define DMA_Priority_VeryHigh              ((uint32_t)0x00003000)
#define DMA_Priority_High                  ((uint32_t)0x00002000)
#define DMA_Priority_Medium                ((uint32_t)0x00001000)
#define DMA_Priority_Low                   ((uint32_t)0x00000000)
#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || \
                                   ((PRIORITY) == DMA_Priority_High) || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_Low))
/**
  * @}
  */

/** @defgroup DMA_memory_to_memory 
  * @{
  */

#define DMA_M2M_Enable                     ((uint32_t)0x00004000)
#define DMA_M2M_Disable                    ((uint32_t)0x00000000)
#define IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Enable) || ((STATE) == DMA_M2M_Disable))

/**
  * @}
  */

/** @defgroup DMA_interrupts_definition 
  * @{
  */

#define DMA_IT_TC                          ((uint32_t)0x00000002)
#define DMA_IT_HT                          ((uint32_t)0x00000004)
#define DMA_IT_TE                          ((uint32_t)0x00000008)
#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00))

#define DMA_IT_GL0                        ((uint32_t)0x00000001)
#define DMA_IT_TC0                        ((uint32_t)0x00000002)
#define DMA_IT_HT0                        ((uint32_t)0x00000004)
#define DMA_IT_TE0                        ((uint32_t)0x00000008)
#define DMA_IT_GL1                        ((uint32_t)0x00000010)
#define DMA_IT_TC1                        ((uint32_t)0x00000020)
#define DMA_IT_HT1                        ((uint32_t)0x00000040)
#define DMA_IT_TE1                        ((uint32_t)0x00000080)
#define DMA_IT_GL2                        ((uint32_t)0x00000100)
#define DMA_IT_TC2                        ((uint32_t)0x00000200)
#define DMA_IT_HT2                        ((uint32_t)0x00000400)
#define DMA_IT_TE2                        ((uint32_t)0x00000800)
#define DMA_IT_GL3                        ((uint32_t)0x00001000)
#define DMA_IT_TC3                        ((uint32_t)0x00002000)
#define DMA_IT_HT3                        ((uint32_t)0x00004000)
#define DMA_IT_TE3                        ((uint32_t)0x00008000)
#define DMA_IT_GL4                        ((uint32_t)0x00010000)
#define DMA_IT_TC4                        ((uint32_t)0x00020000)
#define DMA_IT_HT4                        ((uint32_t)0x00040000)
#define DMA_IT_TE4                        ((uint32_t)0x00080000)
#define DMA_IT_GL5                        ((uint32_t)0x00100000)
#define DMA_IT_TC5                        ((uint32_t)0x00200000)
#define DMA_IT_HT5                        ((uint32_t)0x00400000)
#define DMA_IT_TE5                        ((uint32_t)0x00800000)
#define DMA_IT_GL6                        ((uint32_t)0x01000000)
#define DMA_IT_TC6                        ((uint32_t)0x02000000)
#define DMA_IT_HT6                        ((uint32_t)0x04000000)
#define DMA_IT_TE6                        ((uint32_t)0x08000000)
#define DMA_IT_GL7                        ((uint32_t)0x10000000)
#define DMA_IT_TC7                        ((uint32_t)0x20000000)
#define DMA_IT_HT7                        ((uint32_t)0x40000000)
#define DMA_IT_TE7                        ((uint32_t)0x80000000)

/*******************  Bit definition for DMA_ISR register  ********************/
#define  DMA_ISR_GIF0                        ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt flag */
#define  DMA_ISR_TCIF0                       ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete flag */
#define  DMA_ISR_HTIF0                       ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer flag */
#define  DMA_ISR_TEIF0                       ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error flag */
#define  DMA_ISR_GIF1                        ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt flag */
#define  DMA_ISR_TCIF1                       ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete flag */
#define  DMA_ISR_HTIF1                       ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer flag */
#define  DMA_ISR_TEIF1                       ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error flag */
#define  DMA_ISR_GIF2                        ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt flag */
#define  DMA_ISR_TCIF2                       ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete flag */
#define  DMA_ISR_HTIF2                       ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer flag */
#define  DMA_ISR_TEIF2                       ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error flag */
#define  DMA_ISR_GIF3                        ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt flag */
#define  DMA_ISR_TCIF3                       ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete flag */
#define  DMA_ISR_HTIF3                       ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer flag */
#define  DMA_ISR_TEIF3                       ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error flag */
#define  DMA_ISR_GIF4                        ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt flag */
#define  DMA_ISR_TCIF4                       ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete flag */
#define  DMA_ISR_HTIF4                       ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer flag */
#define  DMA_ISR_TEIF4                       ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error flag */
#define  DMA_ISR_GIF5                        ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt flag */
#define  DMA_ISR_TCIF5                       ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete flag */
#define  DMA_ISR_HTIF5                       ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer flag */
#define  DMA_ISR_TEIF5                       ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error flag */
#define  DMA_ISR_GIF6                        ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt flag */
#define  DMA_ISR_TCIF6                       ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete flag */
#define  DMA_ISR_HTIF6                       ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer flag */
#define  DMA_ISR_TEIF6                       ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error flag */
#define  DMA_ISR_GIF7                        ((uint32_t)0x10000000)        /*!< Channel 7 Global interrupt flag */
#define  DMA_ISR_TCIF7                       ((uint32_t)0x20000000)        /*!< Channel 7 Transfer Complete flag */
#define  DMA_ISR_HTIF7                       ((uint32_t)0x40000000)        /*!< Channel 7 Half Transfer flag */
#define  DMA_ISR_TEIF7                       ((uint32_t)0x80000000)        /*!< Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_IFCR register  *******************/
#define  DMA_IFCR_CGIF0                      ((uint32_t)0x00000001)        /*!< Channel 1 Global interrupt clearr */
#define  DMA_IFCR_CTCIF0                     ((uint32_t)0x00000002)        /*!< Channel 1 Transfer Complete clear */
#define  DMA_IFCR_CHTIF0                     ((uint32_t)0x00000004)        /*!< Channel 1 Half Transfer clear */
#define  DMA_IFCR_CTEIF0                     ((uint32_t)0x00000008)        /*!< Channel 1 Transfer Error clear */
#define  DMA_IFCR_CGIF1                      ((uint32_t)0x00000010)        /*!< Channel 2 Global interrupt clear */
#define  DMA_IFCR_CTCIF1                     ((uint32_t)0x00000020)        /*!< Channel 2 Transfer Complete clear */
#define  DMA_IFCR_CHTIF1                     ((uint32_t)0x00000040)        /*!< Channel 2 Half Transfer clear */
#define  DMA_IFCR_CTEIF1                     ((uint32_t)0x00000080)        /*!< Channel 2 Transfer Error clear */
#define  DMA_IFCR_CGIF2                      ((uint32_t)0x00000100)        /*!< Channel 3 Global interrupt clear */
#define  DMA_IFCR_CTCIF2                     ((uint32_t)0x00000200)        /*!< Channel 3 Transfer Complete clear */
#define  DMA_IFCR_CHTIF2                     ((uint32_t)0x00000400)        /*!< Channel 3 Half Transfer clear */
#define  DMA_IFCR_CTEIF2                     ((uint32_t)0x00000800)        /*!< Channel 3 Transfer Error clear */
#define  DMA_IFCR_CGIF3                      ((uint32_t)0x00001000)        /*!< Channel 4 Global interrupt clear */
#define  DMA_IFCR_CTCIF3                     ((uint32_t)0x00002000)        /*!< Channel 4 Transfer Complete clear */
#define  DMA_IFCR_CHTIF3                     ((uint32_t)0x00004000)        /*!< Channel 4 Half Transfer clear */
#define  DMA_IFCR_CTEIF3                     ((uint32_t)0x00008000)        /*!< Channel 4 Transfer Error clear */
#define  DMA_IFCR_CGIF4                      ((uint32_t)0x00010000)        /*!< Channel 5 Global interrupt clear */
#define  DMA_IFCR_CTCIF4                     ((uint32_t)0x00020000)        /*!< Channel 5 Transfer Complete clear */
#define  DMA_IFCR_CHTIF4                     ((uint32_t)0x00040000)        /*!< Channel 5 Half Transfer clear */
#define  DMA_IFCR_CTEIF4                     ((uint32_t)0x00080000)        /*!< Channel 5 Transfer Error clear */
#define  DMA_IFCR_CGIF5                      ((uint32_t)0x00100000)        /*!< Channel 6 Global interrupt clear */
#define  DMA_IFCR_CTCIF5                     ((uint32_t)0x00200000)        /*!< Channel 6 Transfer Complete clear */
#define  DMA_IFCR_CHTIF5                     ((uint32_t)0x00400000)        /*!< Channel 6 Half Transfer clear */
#define  DMA_IFCR_CTEIF5                     ((uint32_t)0x00800000)        /*!< Channel 6 Transfer Error clear */
#define  DMA_IFCR_CGIF6                      ((uint32_t)0x01000000)        /*!< Channel 7 Global interrupt clear */
#define  DMA_IFCR_CTCIF6                     ((uint32_t)0x02000000)        /*!< Channel 7 Transfer Complete clear */
#define  DMA_IFCR_CHTIF6                     ((uint32_t)0x04000000)        /*!< Channel 7 Half Transfer clear */
#define  DMA_IFCR_CTEIF6                     ((uint32_t)0x08000000)        /*!< Channel 7 Transfer Error clear */
#define  DMA_IFCR_CGIF7                      ((uint32_t)0x10000000)        /*!< Channel 7 Global interrupt clear */
#define  DMA_IFCR_CTCIF7                     ((uint32_t)0x20000000)        /*!< Channel 7 Transfer Complete clear */
#define  DMA_IFCR_CHTIF7                     ((uint32_t)0x40000000)        /*!< Channel 7 Half Transfer clear */
#define  DMA_IFCR_CTEIF7                     ((uint32_t)0x80000000)        /*!< Channel 7 Transfer Error clear */
    
#define IS_DMA_CLEAR_IT(IT) ((IT) != 0x00)

#define IS_DMA_GET_IT(IT) (((IT) == DMA_IT_GL0) || ((IT) == DMA_IT_TC0) || \
                           ((IT) == DMA_IT_HT0) || ((IT) == DMA_IT_TE0) || \
                           ((IT) == DMA_IT_GL1) || ((IT) == DMA_IT_TC1) || \
                           ((IT) == DMA_IT_HT1) || ((IT) == DMA_IT_TE1) || \
                           ((IT) == DMA_IT_GL2) || ((IT) == DMA_IT_TC2) || \
                           ((IT) == DMA_IT_HT2) || ((IT) == DMA_IT_TE2) || \
                           ((IT) == DMA_IT_GL3) || ((IT) == DMA_IT_TC3) || \
                           ((IT) == DMA_IT_HT3) || ((IT) == DMA_IT_TE3) || \
                           ((IT) == DMA_IT_GL4) || ((IT) == DMA_IT_TC4) || \
                           ((IT) == DMA_IT_HT4) || ((IT) == DMA_IT_TE4) || \
                           ((IT) == DMA_IT_GL5) || ((IT) == DMA_IT_TC5) || \
                           ((IT) == DMA_IT_HT5) || ((IT) == DMA_IT_TE5) || \
                           ((IT) == DMA_IT_GL6) || ((IT) == DMA_IT_TC6) || \
                           ((IT) == DMA_IT_HT6) || ((IT) == DMA_IT_TE6) || \
                           ((IT) == DMA_IT_GL7) || ((IT) == DMA_IT_TC7) || \
                           ((IT) == DMA_IT_HT7) || ((IT) == DMA_IT_TE7))

/**
  * @}
  */

/** @defgroup DMA_flags_definition 
  * @{
  */
#define DMA_FLAG_GL0                      ((uint32_t)0x00000001)
#define DMA_FLAG_TC0                      ((uint32_t)0x00000002)
#define DMA_FLAG_HT0                      ((uint32_t)0x00000004)
#define DMA_FLAG_TE0                      ((uint32_t)0x00000008)
#define DMA_FLAG_GL1                      ((uint32_t)0x00000010)
#define DMA_FLAG_TC1                      ((uint32_t)0x00000020)
#define DMA_FLAG_HT1                      ((uint32_t)0x00000040)
#define DMA_FLAG_TE1                      ((uint32_t)0x00000080)
#define DMA_FLAG_GL2                      ((uint32_t)0x00000100)
#define DMA_FLAG_TC2                      ((uint32_t)0x00000200)
#define DMA_FLAG_HT2                      ((uint32_t)0x00000400)
#define DMA_FLAG_TE2                      ((uint32_t)0x00000800)
#define DMA_FLAG_GL3                      ((uint32_t)0x00001000)
#define DMA_FLAG_TC3                      ((uint32_t)0x00002000)
#define DMA_FLAG_HT3                      ((uint32_t)0x00004000)
#define DMA_FLAG_TE3                      ((uint32_t)0x00008000)
#define DMA_FLAG_GL4                      ((uint32_t)0x00010000)
#define DMA_FLAG_TC4                      ((uint32_t)0x00020000)
#define DMA_FLAG_HT4                      ((uint32_t)0x00040000)
#define DMA_FLAG_TE4                      ((uint32_t)0x00080000)
#define DMA_FLAG_GL5                      ((uint32_t)0x00100000)
#define DMA_FLAG_TC5                      ((uint32_t)0x00200000)
#define DMA_FLAG_HT5                      ((uint32_t)0x00400000)
#define DMA_FLAG_TE5                      ((uint32_t)0x00800000)
#define DMA_FLAG_GL6                      ((uint32_t)0x01000000)
#define DMA_FLAG_TC6                      ((uint32_t)0x02000000)
#define DMA_FLAG_HT6                      ((uint32_t)0x04000000)
#define DMA_FLAG_TE6                      ((uint32_t)0x08000000)
#define DMA_FLAG_GL7                      ((uint32_t)0x10000000)
#define DMA_FLAG_TC7                      ((uint32_t)0x20000000)
#define DMA_FLAG_HT7                      ((uint32_t)0x40000000)
#define DMA_FLAG_TE7                      ((uint32_t)0x80000000)

#define IS_DMA_CLEAR_FLAG(FLAG) ((FLAG) != 0x00)

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA_FLAG_GL0) || ((FLAG) == DMA_FLAG_TC0) || \
                               ((FLAG) == DMA_FLAG_HT0) || ((FLAG) == DMA_FLAG_TE0) || \
                               ((FLAG) == DMA_FLAG_GL1) || ((FLAG) == DMA_FLAG_TC1) || \
                               ((FLAG) == DMA_FLAG_HT1) || ((FLAG) == DMA_FLAG_TE1) || \
                               ((FLAG) == DMA_FLAG_GL2) || ((FLAG) == DMA_FLAG_TC2) || \
                               ((FLAG) == DMA_FLAG_HT2) || ((FLAG) == DMA_FLAG_TE2) || \
                               ((FLAG) == DMA_FLAG_GL3) || ((FLAG) == DMA_FLAG_TC3) || \
                               ((FLAG) == DMA_FLAG_HT3) || ((FLAG) == DMA_FLAG_TE3) || \
                               ((FLAG) == DMA_FLAG_GL4) || ((FLAG) == DMA_FLAG_TC4) || \
                               ((FLAG) == DMA_FLAG_HT4) || ((FLAG) == DMA_FLAG_TE4) || \
                               ((FLAG) == DMA_FLAG_GL5) || ((FLAG) == DMA_FLAG_TC5) || \
                               ((FLAG) == DMA_FLAG_HT5) || ((FLAG) == DMA_FLAG_TE5) || \
                               ((FLAG) == DMA_FLAG_GL6) || ((FLAG) == DMA_FLAG_TC6) || \
                               ((FLAG) == DMA_FLAG_HT6) || ((FLAG) == DMA_FLAG_TE6) || \
                               ((FLAG) == DMA_FLAG_GL7) || ((FLAG) == DMA_FLAG_TC7) || \
                               ((FLAG) == DMA_FLAG_HT7) || ((FLAG) == DMA_FLAG_TE7))
/**
  * @}
  */

/** @defgroup DMA_Buffer_Size 
  * @{
  */

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the DMA configuration to the default reset state *****/ 
void DMA_DeInit(DMA_CH_Type* DMAy_Channelx);

/* Initialization and Configuration functions *********************************/
void DMA_Init(DMA_CH_Type* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_CH_Type* DMAy_Channelx, FunctionalState NewState);

/* Data Counter functions *****************************************************/
void DMA_SetCurrDataCounter(DMA_CH_Type* DMAy_Channelx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(DMA_CH_Type* DMAy_Channelx);

/* Interrupts and flags management functions **********************************/
void DMA_ITConfig(DMA_CH_Type* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG);
void DMA_ClearFlag(uint32_t DMA_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMA_IT);
void DMA_ClearITPendingBit(uint32_t DMA_IT);

#ifdef __cplusplus
}
#endif

#endif /*BLUENRG1_DMA_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
