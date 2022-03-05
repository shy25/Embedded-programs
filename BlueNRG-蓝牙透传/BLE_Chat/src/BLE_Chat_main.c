#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "BlueNRG1.h"
#include "clock.h"
#include "SDK_EVAL_Config.h"
#include "SDK_EVAL_Com.h"
#include "comm.h"
#include "bluenrg1_stack.h"
#include "ble_status.h"
#include "Chat_config.h"
#include "chat.h"
#include "sleep.h"
#include "app_state.h"
#include "BlueNRG1_wdg.h"
#include "para_center.h"

#define BLE_CHAT_VERSION_STRING "1.0.0" 
#define RC32K_FREQ		32768
#define RELOAD_TIME(sec)        ((sec*RC32K_FREQ)-3) 
#define WDG_TIME        60*3
void initial_myself(void);  
void initial_peripheral(void);

int main(void) 
{

	long nDelays=1000000;
    initial_myself();
    for(nDelays=1000000;nDelays>0;nDelays--); 
    initial_peripheral();

    while(1) 
    {
       
        BTLE_StackTick();

        APP_Tick();

        if(APP_FLAG(CONNECTED))
        {
            comm_service();
        }
        else
        {
            para_service();
            /*Power Save management: enable sleep mode with wakeup on radio
               *operating timings (adverting, connections intervals) 
               */
            BlueNRG_Sleep(SLEEPMODE_WAKETIMER, 0, 0, 0);
        }

        WDG_SetReload(RELOAD_TIME(WDG_TIME));
         
    }
    
}


/* Private functions ---------------------------------------------------------*/	
void WDG_Configuration(void)
{
  NVIC_InitType NVIC_InitStructure;
  
  /* Enable watchdog clocks  */
  CRMU_PeripheralClockCmd(CRMU_PERIPH_WDG, ENABLE);  
  
  /* Set watchdog reload period at 3 minites */
  WDG_SetReload(RELOAD_TIME(WDG_TIME));
  
  /* Enable the watchdog interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = WDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LOW_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void initial_myself(void)
{
  SystemInit();
  SdkEvalIdentification();
  Clock_Init();
}

void initial_peripheral(void)
{
   uint8_t nRet;

   WDG_Configuration();
   WDG_Enable();

   SdkEvalComIOConfig(comm_receive);
  
  nRet = BlueNRG_Stack_Initialization(&BlueNRG_Stack_Init_params);
  if (nRet != BLE_STATUS_SUCCESS) 
  {
    printf("Error in BlueNRG_Stack_Initialization() 0x%02x\r\n", nRet);
    while(1);
  }

  /* 
   *初始化数据子系统
   */
  para_init();

  nRet = CHAT_DeviceInit();
  if (nRet != BLE_STATUS_SUCCESS) 
  {
    printf("CHAT_DeviceInit()--> Failed 0x%02x\r\n", nRet);
    while(1);
  }
  
}

#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  printf("file: %s on line: %d\r\n", file, line); 
  
  /* Infinite loop */
  while (1)
  {
  }
}

#endif


