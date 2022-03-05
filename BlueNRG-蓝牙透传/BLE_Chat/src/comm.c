#include "comm.h"
#include "chat.h"
#include "BlueNRG1_conf.h"
#include "para_unit.h"
#include "para_center.h"

#define NULL                0
typedef bool            lock_t;
#define RECV_BUF_SIZE      2048
#define RECV_INTERVAL_MAX  10 

uint8_t                   s_ucRcregBuf[RECV_BUF_SIZE];    
volatile     uint32_t     s_uiSendCnt=0;                  
volatile     uint32_t     s_uiRcregTotal=0;               
volatile     lock_t        s_ucSendLock=false;             

#define DATA_HEADER             0x68
#define  IS_HEADER(x) (x==DATA_HEADER)


void Hex2Bcd(const uint8_t* pSrc, uint8_t* pDest, uint32_t nLen)
{
    assert_param(pSrc && pDest && (nLen>0));
    
    uint32_t i;
    for (i = 0; i < nLen; i++)
    {
        pDest[i*2]      = ((pSrc[i]&0xf0)>>4);
        pDest[i*2+1]    = (pSrc[i]&0x0f);
    }
}

void Hex2BcdAscii(const uint8_t* pSrc, uint8_t* pDest, uint32_t nLen)
{
    assert_param(pSrc && pDest && (nLen>0));
    
    uint32_t i;
    for (i = 0; i < nLen; i++)
    {
        pDest[i*2]      = ((pSrc[i]&0xf0)>>4)+0x30;
        pDest[i*2+1]    = (pSrc[i]&0x0f)+0x30;
    }
}

void process_frame(void)
{
    //68 10 04 00 00 00 00 00 00 95 03 A0 18 00 CC 16 
    uint32_t curIndex = 0;

    while((curIndex < s_uiRcregTotal)&& \
            !(IS_HEADER(s_ucRcregBuf[curIndex]))\
         )  curIndex++;
            

    if(curIndex < s_uiRcregTotal)
    {
        uint8_t* pData = s_ucRcregBuf+curIndex;

        if((0x95 == pData[9])  && \
           (0x03 == pData[10]) && \
           (0xa0 == pData[11]) && \
           (0x18 == pData[12]) && \
           (0x16 == pData[15]) )
        {
            Ble_Para* ble_para_addr(void);
            uint8_t* pDeviceName = ble_para_addr()->device_name;
            pDeviceName[0] = 'J';
            pDeviceName[1] = 'X';

            uint8_t tmp[7];//ÐèÒªµ¹Ðò
            tmp[0] = pData[8],tmp[1] = pData[7];
            tmp[2] = pData[6],tmp[3] = pData[5];
            tmp[4] = pData[4],tmp[5] = pData[3];
            tmp[6] = pData[2];
            
            Hex2BcdAscii(tmp, pDeviceName+2, 7);
            save_request(BLE_PARA_TYPE);
        }
    }
}

void comm_time(void)
{
  if((s_uiRcregTotal>0) && (s_uiSendCnt < RECV_INTERVAL_MAX))   
  {
      s_uiSendCnt++;    
      s_ucSendLock=true;     
  }
}

void comm_receive(uint8_t* data_buffer, uint16_t Nb_bytes)
{
    assert_param(data_buffer&&(Nb_bytes > 0));

    uint16_t ui = 0;
    
    for(ui = 0;ui < Nb_bytes;ui++)
    {
        ++s_uiRcregTotal;
        if(s_uiRcregTotal>RECV_BUF_SIZE)  
        {
           s_uiRcregTotal=RECV_BUF_SIZE;
        }
        s_ucRcregBuf[s_uiRcregTotal-1]=data_buffer[ui];
    }
    
    s_uiSendCnt=0;  
}

void comm_service(void)
{
    if(s_uiSendCnt>=RECV_INTERVAL_MAX&&s_ucSendLock) 
    {
        s_ucSendLock=false;    
        assert_param(s_uiRcregTotal <= RECV_BUF_SIZE);
        process_frame();
        
        ble_send_data(s_ucRcregBuf, s_uiRcregTotal);
        s_uiRcregTotal=0; 
    }

}

