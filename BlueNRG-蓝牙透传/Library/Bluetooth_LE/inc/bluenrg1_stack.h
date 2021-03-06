#ifndef BLUENRG1_STACK_H
#define BLUENRG1_STACK_H
/**
  ******************************************************************************
  * @file    bluenrg1_stack.h
  * @author  AMS - VMA RF Application team
  * @version V1.0.0
  * @date    21-Sept-2015
  * @brief   Header file for BlueNRG-1 BLE stack initialization and sleep timer
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
#include <stdint.h>
#include <bluenrg1_api.h>
#include <bluenrg1_events.h>

 
/**
*  
* This macro returns the amount of memory, in bytes, needed for the storage of GATT database elements
* and other data structures whose size depends on the number of supported connections.
*
* @param NUM_LINKS: Maximum number of simultaneous connections that the device will support. Valid values are from 1 to 8.
* @param NUM_GATT_ATTRIBUTES: Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes
* @param NUM_GATT_SERVICES: Maximum number of Services that can be stored in the GATT database. Note that the GAP and GATT services are automatically added so this parameter should be 2 plus the number of user services
* @param ATT_VALUE_ARRAY_SIZE: Size of the storage area for Attribute values.
*/
#define TOTAL_BUFFER_SIZE(NUM_LINKS,NUM_GATT_ATTRIBUTES,NUM_GATT_SERVICES,ATT_VALUE_ARRAY_SIZE) (\
  852 + ((((ATT_VALUE_ARRAY_SIZE)-1)|3)+1) + \
  ((((23*NUM_LINKS)-1)|3)+1) + \
  (248*NUM_LINKS) + \
  (40*NUM_GATT_ATTRIBUTES) + \
  (48*NUM_GATT_SERVICES) \
)

/**
*  
* This macro returns the amount of memory, in bytes, needed for the storage of non-volatile data for bonded devices
*
* @param FLASH_SEC_DB_SIZE: Size of the database used to store security information for bonded devices. The recommended value for this parameter is 1024.
* @param FLASH_SERVER_DB_SIZE: Size of the database used for service change notification for bonded devices.  The recommended value for this parameter is 1024.
* @note: the total buffer size is rounded-up to the next multiple of on flash sector size, i.e. 2048 bytes
*/
#define TOTAL_FLASH_BUFFER_SIZE(FLASH_SEC_DB_SIZE, FLASH_SERVER_DB_SIZE) (\
  ((((FLASH_SEC_DB_SIZE+FLASH_SERVER_DB_SIZE)-1)|2047)+1)\
  )
  
/**
* This symbol defines the size of non-volatile device identification data
*/
#define TOTAL_DEVICE_ID_DATA_SIZE (56)

/**
*
* This structure contains low level hardware configuration data for the device
*/ 
typedef struct {
  uint32_t hot_ana_config_table[8]; /**< Low level configuration table for the radio subsystem. Currently all elements should be set to 0x00 */
  uint32_t max_conn_event_length;   /**< Maximum duration of the connection event when the device is in Slave mode in units of 625/256 us (~2.44 us) */
  uint16_t slave_sca ;              /**< Sleep clock accuracy in Slave mode (ppm value)*/
  uint8_t master_sca ;              /**< Sleep clock accuracy in Master mode (0 to 7 corresponding to 500, 250, 150, 100, 75, 50, 30, 20 ppm)*/
  uint8_t ls_source;                /**< Source for the 32 kHz slow speed clock: 1: internal RO; 0: external crystal */
  uint16_t hs_startup_time ;        /**< Start up time of the high speed (16 or 32 MHz) crystal oscillator in units of 625/256 us (~2.44 us)*/
} hardware_config_table_t;

/**
*
* This structure contains memory and low level hardware configuration data for the device
*/ 
typedef struct {
  uint8_t* bleStartFlashAddress;    /**< Start address for the non-volatile memory area allocated according to TOTAL_FLASH_BUFFER_SIZE (Aligned to 2048 bytes flash sector boundary) */
  uint32_t secDbSize;               /**< Size of the database used to store security information for bonded devices (FLASH_SEC_DB_SIZE used in the calculation of TOTAL_FLASH_BUFFER_SIZE) */
  uint32_t serverDbSize;            /**< Size of the database used for service change notification for bonded devices (FLASH_SERVER_DB_SIZE used in the calculation of TOTAL_FLASH_BUFFER_SIZE) */
  uint8_t* stored_device_id_data_p; /**< Address of the const device id data vector (56 bytes, 32bit aligned FLASH area, all elements must be initialized to 0xFF) */
  uint8_t* bleStartRamAddress;      /**< Start address of the RAM buffer for GATT database allocated according to TOTAL_BUFFER_SIZE (32bit aligned RAM area) */ 
  uint16_t numAttrRecord;           /**< Maximum number of Attributes (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services) that can be stored in the GATT database. Note that certain characteristics and relative descriptors are added automatically during device initialization so this parameters should be 9 plus the number of user Attributes (NUM_GATT_ATTRIBUTES used in the calculation of TOTAL_BUFFER_SIZE) */
  uint16_t numAttrServ;             /**< Maximum number of Services that can be stored in the GATT database. Note that the GAP and GATT services are automatically added so this parameter should be 2 plus the number of user services (NUM_GATT_SERVICES used in the calculation of TOTAL_BUFFER_SIZE)*/
  uint16_t attrValueArrSize;        /**< Size of the storage area for Attribute values (ATT_VALUE_ARRAY_SIZE used in the calculation of TOTAL_BUFFER_SIZE)*/
  uint8_t  numOfLinks;              /**< Maximum number of simultaneous connections that the device will support. Valid values are from 1 to 8 (NUM_LINKS used in the calculation of TOTAL_BUFFER_SIZE). */
  hardware_config_table_t hardware_config;  /**< Structure containing low level hardware configuration data for the device */
} BlueNRG_Stack_Initialization_t;

 
/**
 * BTLE_StackTick 
 *
 * The BTLE Stack Tick function executes the processing of all Host Stack layers. This function has to be executed regularly to process incoming Link Layer packets and to process Host Layers procedures.
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 */
void BTLE_StackTick(void);

/**
 * BlueNRG_Stack_Initialization 
 *
 * @param[in]  BlueNRG_Stack_Init_params_p      pointer to the const structure containing memory and low level 
 *                                              hardware configuration data for the device
 *
 * The BTLE Stack initialization routine
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return Value indicating success or error code.
 *
 */
tBleStatus BlueNRG_Stack_Initialization(const BlueNRG_Stack_Initialization_t *BlueNRG_Stack_Init_params_p);


/**
 * BlueNRG_Stack_Perform_Deep_Sleep_Check 
 *
 * Return the BTLE Stack matching sleep mode
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 *  SLEEPMODE_RUNNING       = 0,
 *  SLEEPMODE_CPU_HALT      = 1,
 *  SLEEPMODE_WAKETIMER     = 2,
 *  SLEEPMODE_NOTIMER       = 3,
 */
uint8_t BlueNRG_Stack_Perform_Deep_Sleep_Check(void);

/**
* RAL_Isr
* 
 * Radio ISR routine. This is the base function called for any radio ISR.
* 
 * @return
*/
void RAL_Isr(void);

/**
 * HAL_VTimerStart_ms 
 *
 * @param[in]  timerNum            The virtual timer number [0..3]
 * @param[in]  msRelTimeout        The relative time, from current time, expressed in ms
 *                                 Note: abs(msRelTimeout) <= 5242879
 *
 * Starts a one-shot virtual timer for the given relative timeout value expressed in ms
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 * 0: no error (the timerNum virtual timer is valid)
 */
int HAL_VTimerStart_ms(uint8_t timerNum, int32_t msRelTimeout);

/**
 * HAL_VTimer_Stop 
 *
 * @param[in]  timerNum            The virtual timer number [0..3]
 *
 * Stops the one-shot virtual timer specified if found
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 */
void HAL_VTimer_Stop(uint8_t timerNum);

/**
 * HAL_VTimerTimeoutCallback
 *
 * @param[in]  timerNum            The virtual timer number [0..3]
 *
 * This function will be called on the expiry of a one-shot virtual timer
 * HAL_VTimerTimeoutCallback will notify the virtual timer number
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 */
void HAL_VTimerTimeoutCallback(uint8_t timerNum);

/**
 * HAL_VTimerGetCurrentTime_sysT32
 *
 * This function return the current reference time expressed in internal time units.
 * The returned value can be used as absolute time parameter where needed in the other
 * HAL_VTimer* APIs
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 * 32bit absolute current time expressed in internal time units.
 */
uint32_t HAL_VTimerGetCurrentTime_sysT32(void);

/**
 * HAL_VTimerAcc_sysT32_ms
 *
 * @param[in]  sysTime            Absolute time expressed in internal time units.
 * @param[in]  msTime             Signed relative time expressed in ms.
 *                                Note: abs(msTime) <= 5242879
 *
 * This function return the sum of an absolute time and a signed relative time.
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 * 32bit resulting absolute time expressed in internal time units.
 */
uint32_t HAL_VTimerAcc_sysT32_ms(uint32_t sysTime, int32_t msTime);


/**
 * HAL_VTimerDiff_ms_sysT32
 *
 * @param[in]  sysTime1           Absolute time expressed in internal time units.
 * @param[in]  sysTime2           Absolute time expressed in internal time units.
 *
 * This function return the difference between two absolute times: sysTime1-sysTime2.
 * The resulting value is expressed in ms.
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 * 32bit resulting signed relative time expressed in ms.
 */
int32_t HAL_VTimerDiff_ms_sysT32(uint32_t sysTime1, uint32_t sysTime2);

/**
 * HAL_VTimerStart_sysT32
 *
 * @param[in]  timerNum       The virtual timer number [0..3]
 * @param[in]  time           Absolute time expressed in internal time units.
 *
 * Starts a one-shot virtual timer for the given absolute timeout value expressed in
 *  internal time units.
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 * 0: no error (the timerNum virtual timer is idle)
 */
int HAL_VTimerStart_sysT32(uint8_t timerNum, uint32_t time);


/**
 * HAL_VTimerExpiry_sysT32
 *
 * @param[in]  timerNum       The virtual timer number [0..3]
 * @param[out] sysTime        Absolute time expressed in internal time units.
 *
 * Returns the absolute expiry time, expressed in internal time units, of a running 
 *  virtual timer.
 *
 * @note The API name and parameters are subject to change in future releases.
 * @return
 * 0: no error (the timerNum virtual timer is running)
 */
int HAL_VTimerExpiry_sysT32(uint8_t timerNum, uint32_t *sysTime); 

#endif // defined( BLUENRG1_STACK_H )

