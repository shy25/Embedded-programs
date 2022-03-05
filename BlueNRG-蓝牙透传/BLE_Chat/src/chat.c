#include <stdio.h>
#include <string.h>
#include "gp_timer.h"
#include "ble_const.h" 
#include "bluenrg1_stack.h"
#include "app_state.h"
#include "osal.h"
#include "gatt_db.h"
#include "SDK_EVAL_Config.h"
#include "chat.h"
#include "para_unit.h"
//#include "OTA_btl.h"

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/



//#define ADVTISE_INTERVAL      1600 //1000000/625---广播频率为1s
#define ADVTISE_INTERVAL      3200 //2000000/625---广播频率为2s
#define ADVTISE_GAP           100
#define ADVTISE_MIN           (ADVTISE_INTERVAL-ADVTISE_GAP)
#define ADVTISE_MAX           (ADVTISE_INTERVAL+ADVTISE_GAP)


/* Private macros ------------------------------------------------------------*/

#define MIN(a,b)            ((a) < (b) )? (a) : (b) 
#define BLE_PACK_SIZE_MAX   20

#define BLE_INVALID_ON_MAX  60*2 // 2minites

uint8_t connInfo[20];
volatile int app_flags = SET_CONNECTABLE;
volatile uint16_t connection_handle = 0;

volatile uint32_t vs_uiVailOnCnt = 0;

/** 
 * @brief  Handle of TX,RX  Characteristics.
 */ 
/* UUIDs */
UUID_t UUID_Tx;
UUID_t UUID_Rx;

uint8_t CHAT_DeviceInit(void)
{
	uint8_t ret;
	uint16_t service_handle;
	uint16_t dev_name_char_handle;
	uint16_t appearance_char_handle;
	uint8_t role = GAP_PERIPHERAL_ROLE;


	/* Configure Public address */
    Ble_Para* ble_para_addr(void);
	ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,     \
                                    CONFIG_DATA_PUBADDR_LEN,        \
                                    ble_para_addr()->mac_addr);

	if(ret != BLE_STATUS_SUCCESS)
	{
		printf("Setting BD_ADDR failed: 0x%02x\r\n", ret);
		return ret;
	}

	/* Set the TX power to -2 dBm */
	aci_hal_set_tx_power_level(1, 4);

	/* GATT Init */
	ret = aci_gatt_init();
	if (ret != BLE_STATUS_SUCCESS) 
	{
		printf ("Error in aci_gatt_init(): 0x%02x\r\n", ret);
		return ret;
	} 
	else 
	{
		printf ("aci_gatt_init() --> SUCCESS\r\n");
	}

	/* GAP Init */
	ret = aci_gap_init( role,               \
	                    0x00,               \
	                    DEV_NAME_SIZE,      \
	                    &service_handle,    \
			            &dev_name_char_handle, \
			            &appearance_char_handle);
    
	if (ret != BLE_STATUS_SUCCESS) 
	{
		printf ("Error in aci_gap_init() 0x%02x\r\n", ret);
		return ret;
	}
	else 
	{
		printf ("aci_gap_init() --> SUCCESS\r\n");
	}

	/* Set the device name */
    Ble_Para* ble_para_addr(void);
	ret = aci_gatt_update_char_value(   service_handle,             \
                                        dev_name_char_handle,       \
			                            0,                          \
			                            DEV_NAME_SIZE,              \
			                            ble_para_addr()->device_name);
    
	if (ret != BLE_STATUS_SUCCESS) 
	{
		printf ("Error in Gatt Update characteristic value 0x%02x\r\n", ret);
		return ret;
	} 
	else 
	{
		printf ("aci_gatt_update_char_value() --> SUCCESS\r\n");
	}

	ret = Add_Chat_Service();
	if (ret != BLE_STATUS_SUCCESS) 
	{
		printf("Error in Add_Chat_Service 0x%02x\r\n", ret);
		return ret;
	} 
	else 
	{
		printf("Add_Chat_Service() --> SUCCESS\r\n");
	}

	return BLE_STATUS_SUCCESS;
}

void ble_send_data(const uint8_t* pSrc, uint32_t uiLen)
{
    uint32_t ui = 0;
    
    assert_param(pSrc && (uiLen >0));
    
    while(ui < uiLen)
    {
        /*20Byte进行分包 add by zhangsb, 2018-05-04 */
        uint32_t len = MIN(BLE_PACK_SIZE_MAX, uiLen - ui); 

        struct timer tm;
        Timer_Set(&tm, CLOCK_SECOND*10); //设置超时时间                        
        while(aci_gatt_update_char_value(chatServHandle,TXCharHandle,   \
                                         0,                             \
                                         len,(uint8_t *)pSrc+ui)        \
                                         ==  BLE_STATUS_INSUFFICIENT_RESOURCES)
        { 

            APP_FLAG_SET(TX_BUFFER_FULL);

            while(APP_FLAG(TX_BUFFER_FULL))
            {
                BTLE_StackTick(); 
                
                /* Radio is busy (buffer full).
                    *超时限制发送
                    */
                if(Timer_Expired(&tm)) 
                {
                    break;
                }
            }     
        }
        
        ui += len; 
        
    }

    vs_uiVailOnCnt = 0;
}
/*******************************************************************************
 * Function Name  : Make_Connection.
 * Description    : If the device is a Client create the connection. Otherwise puts
 *                  the device in discoverable mode.
 * Input          : none.
 * Return         : none.
 *******************************************************************************/
void Make_Connection(void)
{  
	tBleStatus ret;

	hci_le_set_scan_response_data(0,NULL);

    uint8_t name[] = {AD_TYPE_COMPLETE_LOCAL_NAME,'J', 'X',               \
                      '0', '0', '0', '0', '0',\
                      '0', '0', '0', '0', '0', \
                      '0', '0', '0', '1'};
    
    Ble_Para* ble_para_addr(void);
    memcpy(name+1, ble_para_addr()->device_name, DEV_NAME_SIZE);
    
    ret = aci_gap_set_discoverable(ADV_IND,             \
                                    ADVTISE_MIN,        \
                                    ADVTISE_MAX,        \
                                    PUBLIC_ADDR,        \
                                    NO_WHITE_LIST_USE,  \
			                        sizeof(name),       \
			                        name,               \
			                        0, NULL, 0, 0);

	if (ret != BLE_STATUS_SUCCESS)
		printf ("Error in aci_gap_set_discoverable(): 0x%02x\r\n", ret);
	//else
	//	printf ("aci_gap_set_discoverable() --> SUCCESS\r\n");                                 
}

/*******************************************************************************
 * Function Name  : APP_Tick.
 * Description    : Tick to run the application state machine.
 * Input          : none.
 * Return         : none.
 *******************************************************************************/
void APP_Tick(void)
{
	if(APP_FLAG(SET_CONNECTABLE))
	{
		Make_Connection();
		APP_FLAG_CLEAR(SET_CONNECTABLE);
	}
}/* end APP_Tick() */


/* ***************** BlueNRG-1 Stack Callbacks ********************************/

/*******************************************************************************
 * Function Name  : hci_le_connection_complete_event_isr.
 * Description    : This event indicates that a new connection has been created.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void hci_le_connection_complete_event_isr(uint8_t Status,
		uint16_t Connection_Handle,
		uint8_t Role,
		uint8_t Peer_Address_Type,
		uint8_t Peer_Address[6],
		uint16_t Conn_Interval,
		uint16_t Conn_Latency,
		uint16_t Supervision_Timeout,
		uint8_t Master_Clock_Accuracy)

{ 
	connection_handle = Connection_Handle;
    vs_uiVailOnCnt = 0;//连接开始计时
	APP_FLAG_SET(CONNECTED);
}/* end hci_le_connection_complete_event_isr() */

/*******************************************************************************
 * Function Name  : hci_le_connection_complete_event.
 * Description    : This event indicates that a new connection has been created.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void hci_le_connection_complete_event(uint8_t Status,
		uint16_t Connection_Handle,
		uint8_t Role,
		uint8_t Peer_Address_Type,
		uint8_t Peer_Address[6],
		uint16_t Conn_Interval,
		uint16_t Conn_Latency,
		uint16_t Supervision_Timeout,
		uint8_t Master_Clock_Accuracy)

{ 
	hci_le_connection_complete_event_isr(Status,
			Connection_Handle,
			Role,
			Peer_Address_Type,
			Peer_Address,
			Conn_Interval,
			Conn_Latency,
			Supervision_Timeout,
			Master_Clock_Accuracy);

}/* end hci_le_connection_complete_event() */


/*******************************************************************************
 * Function Name  : hci_disconnection_complete_event_isr.
 * Description    : This event occurs when a connection is terminated.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void hci_disconnection_complete_event_isr(uint8_t Status,
		uint16_t Connection_Handle,
		uint8_t Reason)
{
	APP_FLAG_CLEAR(CONNECTED);
	/* Make the device connectable again. */
	APP_FLAG_SET(SET_CONNECTABLE);
	APP_FLAG_CLEAR(NOTIFICATIONS_ENABLED);
	APP_FLAG_CLEAR(TX_BUFFER_FULL);

	APP_FLAG_CLEAR(START_READ_TX_CHAR_HANDLE);
	APP_FLAG_CLEAR(END_READ_TX_CHAR_HANDLE);
	APP_FLAG_CLEAR(START_READ_RX_CHAR_HANDLE); 
	APP_FLAG_CLEAR(END_READ_RX_CHAR_HANDLE);

}/* end hci_disconnection_complete_event() */


/*******************************************************************************
 * Function Name  : aci_gatt_attribute_modified_event.
 * Description    : This event occurs when an attribute is modified.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void aci_gatt_attribute_modified_event(uint16_t Connection_Handle,
		uint16_t Attr_Handle,
		uint16_t Offset,
		uint8_t Attr_Data_Length,
		uint8_t Attr_Data[])
{
	Attribute_Modified_CB(Attr_Handle, Attr_Data_Length, Attr_Data);      
}



/*******************************************************************************
 * Function Name  : aci_gatt_tx_pool_available_event.
 * Description    : This event occurs when a TX pool available is received.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void aci_gatt_tx_pool_available_event(uint16_t Connection_Handle,
		uint16_t Available_Buffers)
{       
	/* It allows to notify when at least 2 GATT TX buffers are available */
	APP_FLAG_CLEAR(TX_BUFFER_FULL);
} 

/*******************************************************************************
 * Function Name  : aci_gatt_read_permit_req_event.
 * Description    : This event is given when a read request is received
 *                  by the server from the client.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void aci_gatt_read_permit_req_event(uint16_t Connection_Handle,
                                 uint16_t Attribute_Handle,
                                 uint8_t Offset)
{
}

void active_disconnect(void)
{
    aci_gap_terminate(connection_handle, 0x1A);
}

void ble_time(void)
{
    if(APP_FLAG(CONNECTED))
    {
        vs_uiVailOnCnt++;
        if(vs_uiVailOnCnt > CLOCK_SECOND*BLE_INVALID_ON_MAX)
        {
            active_disconnect();
            vs_uiVailOnCnt = 0;  
        }
    }
}




