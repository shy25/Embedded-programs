#include "para_center.h"
#include "BlueNRG1_flash.h"
#include "para_unit.h"
#include <string.h>

#define PARA_ZONE_NUM           2
#define PARA_ZONE_FST           62
#define PARA_ZONE_SEC           63

#define ZONE_ADDR(n)             (FLASH_START + N_BYTES_PAGE*(n))

#define CUR_ZONE                (s_ParaSaveCnt&0x01)
#define CUR_PAGE                (CUR_ZONE ? PARA_ZONE_SEC : PARA_ZONE_FST )
#define CUR_ADDR_BASE           ZONE_ADDR(CUR_PAGE)


volatile uint32_t save_flags = 0;
#define PARA_FLAG(type) (save_flags & (0x01<<type))
#define PARA_FLAG_SET(type) (save_flags |= (0x01<<type))
#define PARA_FLAG_CLEAR(type) (save_flags &= ~(0x01<<type))

//第一次启动标识
#define IS_FIRST_RUNNING        (s_ParaSaveCnt == 0xffffffff)

typedef struct Para_Cell_tag
{
    uint32_t stamp;
    union
    {
        char res[N_WORDS_ROW * N_BYTES_WORD - sizeof(uint32_t)*2];
        Ble_Para ble_para;  
       
    }data;
    uint32_t crc;
}Para_Cell;



Para_Cell s_cell_object;
volatile uint32_t s_ParaSaveCnt = 0;

uint32_t get_valid_stamp()
{
    uint32_t ret ,tmp;
    ret = *(volatile uint32_t*)(ZONE_ADDR(PARA_ZONE_FST));
    tmp = *(volatile uint32_t*)(ZONE_ADDR(PARA_ZONE_SEC));

    return ( (ret > tmp) ? ret : tmp );
}

void clear_para()
{
    //擦除flash range
    FLASH_ErasePage(CUR_PAGE);
}

void load_cell_data(uint32_t type)
{
    assert_param(type < PARA_TYPE_NUM);
    
    uint32_t *pSrc  = (uint32_t *)(CUR_ADDR_BASE+ type*sizeof(Para_Cell));
    uint32_t *pDest = (uint32_t *)(&s_cell_object);
    for (uint32_t ui = 0; ui < N_WORDS_ROW; ui++)
    {
        *pDest++ = *pSrc++;
    }
}

void save_cell_data(uint32_t type)
{
    assert_param(type < PARA_TYPE_NUM);
    
    uint32_t* pSrc = (uint32_t *)(&s_cell_object);
    for (uint32_t ui = 0; ui < (N_WORDS_ROW>>2); ui++)
    {
        FLASH_ProgramWordBurst(ui, CUR_PAGE, pSrc);
        pSrc +=4;//每次16个字节，4words
    }
    
}

void load_ble_para()
{ 
    load_cell_data(BLE_PARA_TYPE);

    Ble_Para* ble_para_addr(void);
    Ble_Para* pBlePara=ble_para_addr();
    memcpy((void *)(pBlePara), (void *)(&s_cell_object.data.ble_para), sizeof(Ble_Para)); 
}

void save_ble_para()
{
    s_cell_object.stamp = s_ParaSaveCnt;
    
    Ble_Para* ble_para_addr(void);
    Ble_Para* pBlePara=ble_para_addr();
    memcpy((void *)(&s_cell_object.data.ble_para), (void *)(pBlePara), sizeof(Ble_Para));
    save_cell_data(BLE_PARA_TYPE);
    PARA_FLAG_CLEAR(BLE_PARA_TYPE);
    
}

void load_all_para(void)
{
    load_ble_para();
}

void save_all_para(void)
{
    s_ParaSaveCnt++;
    
    clear_para();
    
    save_ble_para();
    //...
}

void para_service(void)
{
    if(save_flags >0)
    {
        save_all_para();
		
		NVIC_SystemReset();
        save_flags = 0;
    }
}

void para_init(void)
{
    s_ParaSaveCnt = get_valid_stamp();

    //...to do
    if(IS_FIRST_RUNNING)
    {
        s_ParaSaveCnt = 0;
        
        void mac_addr_create(void);
        mac_addr_create();
        save_all_para();
        save_all_para();
        return ;
    }

    load_all_para();
}

void save_request(uint32_t type)
{
    assert_param(type < PARA_TYPE_NUM);
    
    PARA_FLAG_SET(type);
}

