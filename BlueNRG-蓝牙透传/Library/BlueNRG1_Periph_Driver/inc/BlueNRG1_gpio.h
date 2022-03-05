/**
  ******************************************************************************
  * @file    BlueNRG1_gpio.h
  * @author  VMA Application Team
  * @version V1.0.0
  * @date    31-June-2015
  * @brief   This file contains all the functions prototypes for the GPIO 
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
#ifndef BLUENRG1_GPIO_H
#define BLUENRG1_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1.h"

/** @addtogroup BLUENRG1_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */


/** @defgroup GPIO_Exported_Types Exported Types
  * @{
  */

/** 
  * @brief  GPIO Init structure definition
  */
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */
  
  uint32_t GPIO_Mode;             /*!< Specifies the operating mode for the selected pin.
                                      This parameter can be a value of @ref GPIO_mode_define */

  FunctionalState GPIO_HighPwr;   /*!< Specifies the GPIO strength for the selected pin.
                                      This parameter can be any value of @ref GPIO_strength_define */
  
  FunctionalState GPIO_Pull;          /*!< Specifies the GPIO pull down state for the selected pin.
                                      This parameter can be a value of @ref GPIO_pulVal_define */
} GPIO_InitType;


/**
  * @brief  GPIO Init structure definition
  */
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */
  
  uint32_t GPIO_IrqSense;         /*!< Specifies the GPIO interrupt sense to be configured.
                                      This parameter can be any value of @ref GPIO_interrupt_sense */
  
  uint32_t GPIO_Event;            /*!< Specifies the GPIO level sense to be configured.
                                      This parameter can be any value of @ref GPIO_event */
  
} GPIO_EXTIConfigType;

/** 
  * @brief  Bit_SET and Bit_RESET enumeration  
  */
typedef enum
{
  Bit_RESET = 0,  /*!< Specifies the GPIO reset state */
  Bit_SET         /*!< Specifies the GPIO set state */
} BitAction;

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants Exported Constants
  * @{
  */


/* GPIO direction */
#define GPIO_INPUT_DIR  0
#define GPIO_OUTPUT_DIR 1


/* GPIO Interrupt configuration macro */
#define INT_EDGE_DETECTION               0x0
#define INT_LEVEL_DETECTION              0x1
#define INT_SINGLE_EDGE_DETECTION        0x0
#define INT_BOTH_EDGE_DETECTION          0x1
#define INT_FALLING_LOW_LEVEL_DETECTION  0x0
#define INT_RISING_HIGH_LEVEL_DETECTION  0x1


	
/** @defgroup GPIO_mode_define Mode Definition
  * @{
  */  
#define GPIO_Input                  0  /*!< GPIO input selected */
#define Serial1_Mode                1  /*!< Serial1 mode selected */
#define Serial0_Mode                4  /*!< Serial0 mode selected */
#define Microphone_Mode             5  /*!< Microphone mode selected */
#define GPIO_Output                 6  /*!< GPIO output mode selected */

/**
  * @}
  */

/** @defgroup GPIO_speed_define Speed Definition
  * @{
  */  
#define GPIO_Strength_2mA                 (0x0)  /*!< GPIO drive strength 2 mA */
#define GPIO_Strength_4mA                 (0x1)  /*!< GPIO drive strength 4 mA */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIO_pins_define GPIO Pin Definition
  * @{
  */
#define GPIO_Pin_0                 (0x00000001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 (0x00000002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 (0x00000004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 (0x00000008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 (0x00000010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 (0x00000020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 (0x00000040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 (0x00000080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 (0x00000100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 (0x00000200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                (0x00000400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                (0x00000800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                (0x00001000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                (0x00002000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                (0x00004000)  /*!< Pin 14 selected */
#define GPIO_Pin_All               (0x00007FFF)  /*!< All pins selected */

/** Number of total available GPIO pins */
#define GPIO_PIN_COUNT               (26)

#define IS_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || ((PIN) == GPIO_Pin_1) || \
                            ((PIN) == GPIO_Pin_2) || ((PIN) == GPIO_Pin_3) || \
                            ((PIN) == GPIO_Pin_4) || ((PIN) == GPIO_Pin_5) || \
                            ((PIN) == GPIO_Pin_6) || ((PIN) == GPIO_Pin_7) || \
                            ((PIN) == GPIO_Pin_8) || ((PIN) == GPIO_Pin_9) || \
                            ((PIN) == GPIO_Pin_10) || ((PIN) == GPIO_Pin_11) || \
                            ((PIN) == GPIO_Pin_12) || ((PIN) == GPIO_Pin_13) || \
                            ((PIN) == GPIO_Pin_14))

/**
  * @}
  */

/** @defgroup GPIO_interrupt_sense Interrupt Sense Definition
  * @{
  */
#define GPIO_IrqSense_Edge      (0)   /*!< Edge detection */
#define GPIO_IrqSense_Level     (1)   /*!< Level detection */
/**
  * @}
  */


/** @defgroup GPIO_event Event	Active Edge Definition	
  * @{
  */
#define GPIO_Event_Low           (0)   /*!< Low level or falling edge detection */
#define GPIO_Event_High          (1)   /*!< High level or rising edge detection */
#define GPIO_Event_Both          (2)   /*!< Both edges detection */
/**
  * @}
  */  

/**
  * @}
  */

/** @defgroup GPIO_Exported_Macros Exported Macros
* @{
*/

/** This macro checks if ACTION is a valid bit action */
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

/** This macro checks if CMD is a valid pull comand */
#define IS_GPIO_PULL(CMD) (((CMD) == GPIO_Pull_Enable) || \
                               ((CMD) == GPIO_Pull_Disable))

/** This macro checks if MODE is a valid mode for GPIO */
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Input) || \
                            ((MODE) == GPIO_Output) || \
                            ((MODE) == Serial1_Mode) || \
                            ((MODE) == Serial0_Mode) || \
                            ((MODE) == Microphone_Mode))
														
/** This macro checks if STRENGTH is valid for GPIO */
#define IS_GPIO_STRENGTH(STR) (((SPEED) == GPIO_Strength_2mA) || \
                              ((SPEED) == GPIO_Strength_4mA))

/** This macro checks if PIN is a valid pin combination value */
#define IS_GPIO_PINS(PIN) ((((PIN) & (uint32_t)(~GPIO_Pin_All)) == 0x00000000) && ((PIN) != 0x00000000))


/** This macro checks if IS is a valid interrupt sense value */
#define IS_GPIO_IRQSENSE(IS) (((IS) == GPIO_IrqSense_Edge) || \
                              ((IS) == GPIO_IrqSense_Level))


/** This macro checks if EV is a valid GPIO_Event value */
#define IS_GPIO_EVENT(EV) (((EV) == GPIO_Event_Low) || \
                           ((EV) == GPIO_Event_High) || \
                           ((EV) == GPIO_Event_Both))
/**
  * @}
  */


/** @defgroup GPIO_Exported_Functions Exported Functions
  * @{
  */

/* Initialization */
void GPIO_DeInit(void);																					/*!< GPIO deinitialization. */
void GPIO_Init(GPIO_InitType* GPIO_InitStruct);									/*!< GPIO initialization. */
void GPIO_StructInit(GPIO_InitType* GPIO_InitStruct);						/*!< Initialization of the GPIO_InitType Structure. */

/* Data read */
BitAction GPIO_ReadBit(uint32_t GPIO_Pin);												/*!< Read GPIO pin logic state. */

/* Data write */
void GPIO_WriteBit(uint32_t GPIO_Pin, BitAction BitVal);				/*!< Write new GPIO pin logic state. */

/* Bit operations */
void GPIO_SetBits(uint32_t GPIO_Pin);														/*!< Set selected GPIO pin. */
void GPIO_ResetBits(uint32_t GPIO_Pin);													/*!< Reset selected GPIO pin. */
void GPIO_ToggleBits(uint32_t GPIO_Pin);													/*!< Toggle selected GPIO pin. */

/* GPIO interrupts */
void GPIO_EXTIStructInit(GPIO_EXTIConfigType* GPIO_EXTIInitStruct); /*!< Initialization of the GPIO_EXTIInit Structure. */
void GPIO_EXTIConfig(GPIO_EXTIConfigType* EXTIConfig);					/*!< Selects the GPIO pin used as EXTI Line. */
void GPIO_EXTICmd(uint32_t GPIO_Pin, FunctionalState NewState);	/*!< Enables or disables interrupts on specified pins. */
void GPIO_ClearITPendingBit(uint32_t GPIO_Pin);									/*!< Clears the GPIOx interrupt pending bits. */
FlagStatus GPIO_GetITPendingBit(uint32_t GPIO_Pin);								/*!< Checks whether the specified enabled GPIO interrupt is active. */


#ifdef __cplusplus
}
#endif

#endif /* BLUENRG1_GPIO_H */
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
