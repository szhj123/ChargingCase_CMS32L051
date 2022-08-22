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
uint8_t rdBuf[10];

void Drv_Flash_Init(void )
{
    Hal_Flash_Init();

    Drv_Flash_Read(0, rdBuf, 10);
   
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
   
    if((addr % PAGE_SIZE))
    {
        firstPageByte = PAGE_SIZE - (addr % PAGE_SIZE);        
    }
    else
    {
        firstPageByte = 0;
    }

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

    Drv_Flash_Write_With_DMA(addr, buf, lastPageByte);
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


