/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
* File Name          : system_bluenrg1.h
* Author             : AMS - VMA
* Version            : V1.0.0
* Date               : 19-May-2015
* Description        : BlueNRG Low Level Init function
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#include "BlueNRG1.h"
#include "system_BlueNRG1.h"
#include "BluenRG1_flash.h"
#include "misc.h"
#include "hal_types.h"

#define RESET_WAKE_DEEPSLEEP_REASONS 0x05
#define CRITICAL_PRIORITY 0
/* OTA tag used to  tag a  valid application on interrupt vector table*/
#if ST_OTA_SERVICE_MANAGER_APPLICATION
#define OTA_VALID_APP_TAG (0xAABBCCDD) /* OTA Service Manager has a special valid tag */
#else
#define OTA_VALID_APP_TAG (0xAA5555AA) 
#endif

 
WEAK_FUNCTION(void NMI_Handler(void) {});
WEAK_FUNCTION(void HardFault_Handler(void) {});
WEAK_FUNCTION(void SVC_Handler(void) {});
WEAK_FUNCTION(void PendSV_Handler(void) {});
WEAK_FUNCTION(void SysTick_Handler(void) {});
WEAK_FUNCTION(void GPIO_Handler(void) {});
WEAK_FUNCTION(void NVM_Handler(void) {});
WEAK_FUNCTION(void UART_Handler(void) {});
WEAK_FUNCTION(void SPI_Handler(void) {});
WEAK_FUNCTION(void Blue_Handler(void) {});
WEAK_FUNCTION(void BATTERY_LOW_Handler(void) {});
WEAK_FUNCTION(void ADV_Handler(void) {});
WEAK_FUNCTION(void MFTX1A_Handler(void) {});
WEAK_FUNCTION(void MFTX1B_Handler(void) {});
WEAK_FUNCTION(void MFTX2A_Handler(void) {});
WEAK_FUNCTION(void MFTX2B_Handler(void) {});
WEAK_FUNCTION(void RTC_Handler(void) {});
WEAK_FUNCTION(void WDG_Handler(void) {});
WEAK_FUNCTION(void ADC_Handler(void) {});
WEAK_FUNCTION(void I2C2_Handler(void) {});
WEAK_FUNCTION(void I2C1_Handler(void) {});
WEAK_FUNCTION(void DMA_Handler(void) {});


int __low_level_init(void) 
{
  // If the reset reason is a wakeup from sleep restore the context
  if ((CKGEN_SOC->REASON_RST == 0) && (CKGEN_BLE->REASON_RST > RESET_WAKE_DEEPSLEEP_REASONS)) {
#ifndef NO_SMART_POWER_MANAGEMENT
          
  void CS_contextRestore(void);
  extern volatile uint8_t wakeupFromSleepFlag;
  wakeupFromSleepFlag = 1; //A wakeup from Standby or Sleep occurred
  CS_contextRestore(); // Restore the context
  //if the context restore worked properly, we should never return here
  while(1) { ; }
#else
  return 0;
#endif   
  }
  return 1;
}


#ifdef __CC_ARM

void RESET_HANDLER(void)
{
  if(__low_level_init()==1)//冷启动
    __main();
  else { //热启动，从低功耗中恢复
    __set_MSP((uint32_t)_INITIAL_SP);
    main();
  }
}


#else /* __CC_ARM */
#ifdef __GNUC__

extern unsigned long _etext;
extern unsigned long _sidata;		/* start address for the initialization values of the .data section. defined in linker script */
extern unsigned long _sdata;		/* start address for the .data section. defined in linker script */
extern unsigned long _edata;		/* end address for the .data section. defined in linker script */
extern unsigned long _sbss;			/* start address for the .bss section. defined in linker script */
extern unsigned long _ebss;			/* end address for the .bss section. defined in linker script */
extern unsigned long _estack;		/* init value for the stack pointer. defined in linker script */

extern int main(void);

void RESET_HANDLER(void)
{
  if(__low_level_init()==1)	{
	  unsigned long *pulSrc, *pulDest;

	  // Copy the data segment initializers from flash to SRAM.
	  pulSrc = &_sidata;
	  for(pulDest = &_sdata; pulDest < &_edata; )
		{
		  *(pulDest++) = *(pulSrc++);
		}

	  // Zero fill the bss segment.
	  for(pulDest = &_sbss; pulDest < &_ebss; )
		{
		  *(pulDest++) = 0;
		}
  }
  // Call the application's entry point.
  __set_MSP((uint32_t)_INITIAL_SP);
  main();
}


#endif /* __GNUC__ */
#endif /* __CC_ARM */

/*系统异常向量表 和 CPU启动序列 
 *编译器的统一化是通过定义条件编译宏来进行统一的
 *
 *add by zhangsb, 2018-05-09 
 */
SECTION(".intvec")
REQUIRED(const intvec_elem __vector_table[]) = {
    _INITIAL_SP,                            /* Stack address                      */
    RESET_HANDLER,           		            /* Reset handler is C initialization. */
    NMI_Handler,                            /* The NMI handler                    */ 
    HardFault_Handler,                      /* The hard fault handler             */ 
    (intfunc) OTA_VALID_APP_TAG,            /* OTA Application                    */
    0x00000000,                             /* Reserved                           */ 
    0x00000000,                             /* Reserved                           */ 
    0x00000000,                             /* Reserved                           */ 
    0x00000000,                             /* Reserved                           */ 
    0x00000000,                             /* Reserved                           */ 
    0x00000000,                             /* Reserved                           */ 
    SVC_Handler,                            /* SVCall                             */ 
    0x00000000,                             /* Reserved                           */ 
    0x00000000,                             /* Reserved                           */ 
    PendSV_Handler,                         /* PendSV                             */ 
    SysTick_Handler,                        /* SysTick_Handler                    */ 
    GPIO_Handler,                           /* IRQ0:  GPIO                        */ 
    NVM_Handler,                            /* IRQ1:  NVM                         */ 
    0x00000000,                             /* IRQ2:                              */ 
    0x00000000,                             /* IRQ3:                              */ 
    UART_Handler,                           /* IRQ4:  UART                        */ 
    SPI_Handler,                            /* IRQ5:  SPI                         */ 
    Blue_Handler,                           /* IRQ6:  Blue                        */ 
    WDG_Handler,                            /* IRQ7:  Watchdog                    */ 
    0x00000000,                             /* IRQ8:                              */ 
    0x00000000,                             /* IRQ9:                              */ 
    0x00000000,                             /* IRQ10:                             */ 
    0x00000000,                             /* IRQ11:                             */ 
    0x00000000,                             /* IRQ12:                             */ 
    ADC_Handler,                            /* IRQ13  ADC                         */ 
    I2C2_Handler,                           /* IRQ14  I2C2                        */ 
    I2C1_Handler,                           /* IRQ15  I2C1                        */ 
    0x00000000,                             /* IRQ16                              */ 
    MFTX1A_Handler,                         /* IRQ17  MFTX1 irq1                  */ 
    MFTX1B_Handler,                         /* IRQ18  MFTX1 irq2                  */ 
    MFTX2A_Handler,                         /* IRQ19  MFTX2 irq1                  */ 
    MFTX2B_Handler,                         /* IRQ20  MFTX2 irq2                  */ 
    RTC_Handler,                            /* IRQ21  RTC                         */ 
    0x00000000,                             /* IRQ22                              */ 
    DMA_Handler,                            /* IRQ23  DMA                         */ 
    0x00000000,                             /* IRQ24                              */ 
    0x00000000,                             /* IRQ25                              */ 
    0x00000000,                             /* IRQ26                              */ 
    0x00000000,                             /* IRQ27                              */ 
    0x00000000,                             /* IRQ28                              */ 
    0x00000000,                             /* IRQ29                              */ 
    0x00000000,                             /* IRQ30                              */ 
    0x00000000                              /* IRQ31                              */ 
};

SECTION(".bss.__blue_RAM")

REQUIRED(static uint8_t __blue_RAM[8*64+12]) = {0,};

/* Device Configuration Registers */
#define ATB0_ANA_ENG_REG    0x3F
#define ATB1_ANA_ENG_REG    0x3E
#define RM1_DIG_ENG_REG     0x3C
#define CLOCK_LOW_ENG_REG   0x3B
#define CLOCK_HIGH_ENG_REG  0x3A
#define PMU_ANA_ENG_REG     0x39
#define CLOCK_ANA_USER_REG  0x34
#define NUMBER_CONFIG_BYTE  0x02
#define END_CONFIG          0x00
  
#define LOW_FREQ_RO     0x1B
#define LOW_FREQ_XO     0x5B
#define HIGH_FREQ_16M   0x40
#define HIGH_FREQ_32M   0x44
#define SMPS_ON         0x4C
#define SMPS_OFF        0x6C
#define SMPS_4_7uH_RM1  0x40
#define SMPS_4_7uH_PMU  0xBE
#define SMPS_10uH_RM1   0x20
#define SMPS_10uH_PMU   0xB2
  
#define COLD_START_CONFIGURATION                         \
{                                                        \
  NUMBER_CONFIG_BYTE, ATB0_ANA_ENG_REG,   0x00,          \
  NUMBER_CONFIG_BYTE, ATB1_ANA_ENG_REG,   0x30,          \
  NUMBER_CONFIG_BYTE, RM1_DIG_ENG_REG,    SMPS_10uH_RM1, \
  NUMBER_CONFIG_BYTE, CLOCK_LOW_ENG_REG,  SMPS_ON,       \
  NUMBER_CONFIG_BYTE, CLOCK_HIGH_ENG_REG, HIGH_FREQ_16M, \
  NUMBER_CONFIG_BYTE, PMU_ANA_ENG_REG,    SMPS_10uH_PMU, \
  NUMBER_CONFIG_BYTE, CLOCK_ANA_USER_REG, LOW_FREQ_XO,   \
  END_CONFIG                                             \
}
  
/*****************************************************************************
 * Function      : DeviceConfiguration
 * Description   : 配置功能模块的时钟
 * Input         : BOOL coldStart  ----是否冷启动   
                   BOOL waitLS_Ready---  ?
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180509
 *   Author      : 
 *   Modification: Created function
1) 高速时钟源配置---根据外部电路对高速时钟源进行配置
2) 低速时钟源配置---根据外部电路对低速时钟源进行配置
3) SMPS配置(?) ---即Switch Mode Power Supply，意思是交换模式开关电源。 简单来说就是smps更省电
4) 冷启动，等待设置完成(RADIO_CONFIG)
5) 等待时钟初始化完成
6) 等待时钟生效
*****************************************************************************/
void DeviceConfiguration(BOOL coldStart, BOOL waitLS_Ready)
{
  uint32_t current_time;
  volatile uint8_t cold_start_config[] = COLD_START_CONFIGURATION;

  /* High Speed Crystal Configuration */
#if (HS_SPEED_XTAL == HS_SPEED_XTAL_32MHZ)
  cold_start_config[14] = HIGH_FREQ_32M;
  /* Set 32MHz_SEL bit in the System controller register */
  SYSTEM_CTRL->CTRL_b.MHZ32_SEL = 1;
#elif (HS_SPEED_XTAL == HS_SPEED_XTAL_16MHZ)
  cold_start_config[14] = HIGH_FREQ_16M;
#else
#error "No definition for High Speed Crystal"
#endif
  
  /* Low Speed Crystal Source */
#if (LS_SOURCE == LS_SOURCE_EXTERNAL_32KHZ)
  cold_start_config[20] = LOW_FREQ_XO;
#elif (LS_SOURCE == LS_SOURCE_INTERNAL_RO)
  cold_start_config[20] = LOW_FREQ_RO;
#else
#error "No definition for Low Speed Crystal Source"
#endif
  
  /* SMPS configuration */
#if (SMPS_INDUCTOR == SMPS_INDUCTOR_10uH)
  cold_start_config[11] = SMPS_ON;
  cold_start_config[8] = SMPS_10uH_RM1;
  cold_start_config[17] = SMPS_10uH_PMU;
#elif (SMPS_INDUCTOR == SMPS_INDUCTOR_4_7uH)
  cold_start_config[11] = SMPS_ON;
  cold_start_config[8] = SMPS_4_7uH_RM1;
  cold_start_config[17] = SMPS_4_7uH_PMU;
#elif (SMPS_INDUCTOR == SMPS_INDUCTOR_NONE)
  cold_start_config[11] = SMPS_OFF;
#else
#error "No definition for SMPS Configuration"
#endif
  
  if (coldStart) {
    /* Cold start configuration device */
    BLUE_CTRL->RADIO_CONFIG = 0x10000U | (uint16_t)((uint32_t)cold_start_config & 0x0000FFFFU);
    while ((BLUE_CTRL->RADIO_CONFIG & 0x10000) != 0);
  }
  
  /* Wait until HS is ready. The slow clock period 
  * measurement is done automatically each time the
  * device enters in active2 state and the HS is ready.
  * The interrupt signals that a measurement is done.
  * 重新计算在active状态的填充值?
  */
  while(CKGEN_BLE->CLK32K_IT == 0);
  CKGEN_BLE->CLK32K_IT = 1;
  CKGEN_BLE->CLK32K_COUNT = 23; //Restore the window length for slow clock measurement.
  CKGEN_BLE->CLK32K_PERIOD = 0;
  
  /* Wait until the RO or 32KHz is ready */
  if (waitLS_Ready) {
          current_time = *(volatile uint32_t *)0x48000010;
          while(((*(volatile uint32_t *)0x48000010)&0x10) == (current_time&0x10));
  }
  
#if (HS_SPEED_XTAL == HS_SPEED_XTAL_32MHZ)
  /* AHB up converter command register write*/
  AHBUPCONV->COMMAND = 0x15;
#endif
}

/*****************************************************************************
 * Function      : SystemInit
 * Description   : 系统初始化
 * Input         : void  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180509
 *   Author      : zhangsb
 *   Modification: Created function
1) vector table重映射
2) 设置中断优先级
3) 蓝牙设备启动参数初始化 ??有疑问，没彻底弄明白
4) 关闭所有外设的时钟
5) 中断使能
*****************************************************************************/
void SystemInit(void)
{
  /* Remap the vector table */
  FLASH->CONFIG = FLASH_PREMAP_MAIN;

  /* Configure all the interrupts priority. 
  * The application can modify the interrupts priority.
  * The  PendSV_IRQn and BLUE_CTRL_IRQn SHALL maintain the highest priority
  */
  NVIC_SetPriority(PendSV_IRQn,    LOW_PRIORITY);
  NVIC_SetPriority(SysTick_IRQn,   LOW_PRIORITY);
  NVIC_SetPriority(GPIO_IRQn,      LOW_PRIORITY);
  NVIC_SetPriority(NVM_IRQn,       LOW_PRIORITY);
  NVIC_SetPriority(UART_IRQn,      LOW_PRIORITY);
  NVIC_SetPriority(SPI_IRQn,       LOW_PRIORITY);
  NVIC_SetPriority(BLUE_CTRL_IRQn, CRITICAL_PRIORITY);
  NVIC_SetPriority(WDG_IRQn,       LOW_PRIORITY);
  NVIC_SetPriority(ADC_IRQn,       LOW_PRIORITY);
  NVIC_SetPriority(I2C2_IRQn,      LOW_PRIORITY);
  NVIC_SetPriority(I2C1_IRQn,      LOW_PRIORITY);
  NVIC_SetPriority(MFTX1A_IRQn,    LOW_PRIORITY);
  NVIC_SetPriority(MFTX1B_IRQn,    LOW_PRIORITY);
  NVIC_SetPriority(MFTX2A_IRQn,    LOW_PRIORITY);
  NVIC_SetPriority(MFTX2B_IRQn,    LOW_PRIORITY);
  NVIC_SetPriority(RTC_IRQn,       LOW_PRIORITY);
  NVIC_SetPriority(DMA_IRQn,       LOW_PRIORITY);

  /* Device Configuration */
  DeviceConfiguration(TRUE, TRUE);
  /* Disable all the peripherals clock except NVM, SYSCTR and RNG */
  CKGEN_SOC->CLOCK_EN = 0x20066;
  __enable_irq();
}


/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/

