#ifndef _COMM_H_
#define _COMM_H_
#include <stdbool.h>
#include <stdint.h>

void comm_time(void);  
void comm_receive(uint8_t* data_buffer, uint16_t Nb_bytes); 
void comm_service(void); 

#endif /* _COMM_H_ */




