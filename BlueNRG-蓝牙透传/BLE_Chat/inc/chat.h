
#ifndef _CHAT_H_
#define _CHAT_H_
#include <stdint.h>


uint8_t CHAT_DeviceInit(void);
void APP_Tick(void);
void ble_send_data(const uint8_t* pSrc, uint32_t uiLen);
void ble_time(void);

#endif // _CHAT_H_
