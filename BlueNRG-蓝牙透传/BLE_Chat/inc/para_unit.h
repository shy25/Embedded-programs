#ifndef _PARA_UNIT_H_
#define _PARA_UNIT_H_
#include <stdint.h>

#define DEV_NAME_SIZE     16 // 'J' + 'X' + Êý×Ö*14
#define MAC_ADDR_SIZE     6  // 48bit = 6BYTES

typedef struct Ble_Para_tag
{
  uint8_t mac_addr[MAC_ADDR_SIZE];
  uint8_t device_name[DEV_NAME_SIZE];
}Ble_Para;

#endif /* _PARA_UNIT_H_ */
