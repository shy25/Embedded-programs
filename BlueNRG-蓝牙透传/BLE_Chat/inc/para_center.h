#ifndef _PARA_CENTER_H
#define _PARA_CENTER_H
#define PARA_TYPE_NUM           8
#define BLE_PARA_TYPE           0
#include <stdint.h>

void para_init(void);
void para_service(void);
void save_request(uint32_t type);


#endif /* _PARA_CENTER_H */


