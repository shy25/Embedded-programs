#include "para_unit.h"
#include "BlueNRG1_rng.h"
#include "BlueNRG1_conf.h"


static Ble_Para s_ble_para =
{
        {0x3d, 0x3a, 0x5b, 0x49, 0x68,0xfe},
       {'p','x','1','2','3','4','5','6','7','8','9','0','1','2','3','4'}
};

Ble_Para* ble_para_addr(void){return (&s_ble_para);}

void mac_addr_create(void)
{
    uint8_t* pMacAddr = s_ble_para.mac_addr;
    
    while (RNG_GetFlagStatus() != SET);
    pMacAddr[0] =  (READ_REG(RNG->VAL))&0xff;
    pMacAddr[1] =  ((READ_REG(RNG->VAL))>>8)&0xff;

    while (RNG_GetFlagStatus() != SET);
    pMacAddr[2] =  (READ_REG(RNG->VAL))&0xff;
    pMacAddr[3] =  ((READ_REG(RNG->VAL))>>8)&0xff;

    while (RNG_GetFlagStatus() != SET);
    pMacAddr[4] =  (READ_REG(RNG->VAL))&0xff;
    pMacAddr[5] =  ((READ_REG(RNG->VAL))>>8)&0xff;    
}





