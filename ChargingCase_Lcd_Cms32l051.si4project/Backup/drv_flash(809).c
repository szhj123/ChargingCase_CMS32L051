/********************************************************
* @file       drv_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_flash.h"
#include "drv_timer.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/
static uint8_t flashWrEndFlag = 0;
static uint8_t flashRdEndFlag = 0;

void Drv_Flash_Init(void )
{   
    #if 1
    Hal_Flash_Init();
    #else
    extern const unsigned char gImage_pic[];
    uint8_t  picIndex= 0;
    uint16_t picWidth = 0x84;
    uint16_t picHeight = 0xa2;

    uint32_t falshAddr = 0;

    static uint8_t buf[10];
    
    Hal_Flash_Init();
    
    Drv_Flash_Block_64k_Erase(falshAddr);

    Drv_Flash_Write_With_Loop(falshAddr, (uint8_t *)&picIndex, 1);
    falshAddr += 1;
    
    Drv_Flash_Write_With_Loop(falshAddr, (uint8_t *)&picWidth, 2);
    falshAddr += 2;
    
    Drv_Flash_Write_With_Loop(falshAddr, (uint8_t *)&picHeight, 2);
    falshAddr += 2;
    
    Drv_Flash_Write(falshAddr, (uint8_t *)gImage_pic, 42444);

    Drv_Flash_Read(0, buf, 10);
    #endif 
}

void Drv_Flash_Read_Jedec_Id(void )
{
    uint8_t dummy[3] = {0x00};
    
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_JEDEC_ID);

    Hal_Flash_Multiple_Read(dummy, sizeof(dummy));

    Hal_Flash_Stop();
}

void Drv_Flash_Wait_Bus_Idle(void )
{
    uint8_t status;
    
    Hal_Flash_Start();
    
    Hal_Flash_Single_Write(READ_STATUS_REGISTER);

    do{
        Hal_Flash_Multiple_Read((uint8_t *)&status, 1);
    }while(status & 0x01);

    Hal_Flash_Stop();
}

void Drv_Write_Enable(void )
{
    Hal_Flash_Start();

    Hal_Flash_Single_Write(WRITE_ENABLE);
    
    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Sector_Erase(uint32_t addr )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(SECTOR_ERASE);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Block_64k_Erase(uint32_t addr )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(BLOCK_ERASE_64K);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Write_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(PAGE_PROGRAM);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Send(buf, length );

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Read_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length )
{
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_DATA);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Read(buf, length );

    Hal_Flash_Stop();
}

static void Drv_Flash_Write_End_Callback(void )
{
    flashWrEndFlag = 1;
}

void Drv_Flash_Write_With_DMA(uint32_t addr, uint8_t *buf, uint16_t length )
{
    if(length < 1)
    {
        return ;
    }
    
    Drv_Write_Enable();
    
    Hal_Flash_Start();
    
    Hal_Flash_Single_Write(PAGE_PROGRAM);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));
    
    Hal_Flash_Multiple_Write_With_DMA(buf, length, Drv_Flash_Write_End_Callback);

    while(!flashWrEndFlag);
    flashWrEndFlag = 0;

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Write(uint32_t addr, uint8_t *buf, uint32_t length )
{
    uint16_t firstPageByte;
    uint16_t lastPageByte;
    uint32_t pageNum;
    uint32_t i;
   
    if((addr % PAGE_SIZE) != 0)
    {
        firstPageByte = PAGE_SIZE - (addr % PAGE_SIZE);        
    }
    else
    {
        firstPageByte = 0;
    }

    if(length > firstPageByte)
    {
        pageNum = (length - firstPageByte) / PAGE_SIZE;

        lastPageByte = (length - firstPageByte) % PAGE_SIZE;

        if(firstPageByte)
        {
            Drv_Flash_Write_With_DMA(addr, buf, firstPageByte);
            
            addr += firstPageByte;
        
            buf += firstPageByte;
        }
        
        for(i=0;i<pageNum;i++)
        {
            Drv_Flash_Write_With_DMA(addr, buf, PAGE_SIZE);

            addr += PAGE_SIZE;
            
            buf += PAGE_SIZE;
        }

        if(lastPageByte)
        {
            Drv_Flash_Write_With_DMA(addr, buf, lastPageByte);
        }
    }
    else
    {
        if(length)
        {
            Drv_Flash_Write_With_DMA(addr, buf, length);
        }
    }
}

static void Drv_Flash_Read_End_Callback(void )
{
    flashRdEndFlag = 1;
}

void Drv_Flash_Read(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_DATA);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Read_With_DMA(buf, length, Drv_Flash_Read_End_Callback);

    while(!flashRdEndFlag);
    flashRdEndFlag = 0;
    
    Hal_Flash_Stop();
}


