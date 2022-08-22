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
void Drv_Flash_Loop_Wait(uint16_t n);
/* Private variables ------------------------------------*/
uint8_t wrBuf[] = {0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5, 0xa5};
uint8_t rdBuf[10];
uint16_t flashWaitCnt;
static uint8_t flashWriteEndFlag;

void Drv_Flash_Init(void )
{
    Hal_Flash_Init();
    
    Drv_Flash_Read_With_Loop(0, rdBuf, 5);
    
    Drv_Flash_Sector_Erase(0);

    Drv_Flash_Read_With_Loop(0, rdBuf, 5);

    //Drv_Flash_Write_With_Loop(0, wrBuf, 10);
    Drv_Flash_Write(0, wrBuf, 5);
    
    Drv_Flash_Read_With_Loop(0, rdBuf, 5);
}

void Drv_Flash_Read_Jedec_Id(void )
{
    uint8_t dummy[3] = {0x00};
    
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_JEDEC_ID);

    Hal_Flash_Multiple_Read_With_Loop(dummy, sizeof(dummy));

    Hal_Flash_Stop();
}

void Drv_Flash_Wait_Bus_Idle(void )
{
    uint8_t status;
    
    Hal_Flash_Start();
    
    Hal_Flash_Single_Write(READ_STATUS_REGISTER);

    do{
        Hal_Flash_Multiple_Read_With_Loop((uint8_t *)&status, 1);
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

void Drv_Flash_Write_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(PAGE_PROGRAM);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Write_With_Loop(buf, length );

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

    Hal_Flash_Multiple_Read_With_Loop(buf, length );

    Hal_Flash_Stop();
}

void Drv_Flash_Write_End_Callback(void )
{
    flashWriteEndFlag = 1;

    
}

void Drv_Flash_Write_With_DMA(uint32_t addr, uint8_t * buf, uint16_t length )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(PAGE_PROGRAM);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    //Hal_Flash_Write_With_DMA(buf, length, Drv_Flash_Write_End_Callback);

    Hal_Flash_Write_With_Interrupt(buf, length, Drv_Flash_Write_End_Callback);

    while(!flashWriteEndFlag);

    flashWriteEndFlag = 0;

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
    
}

void Drv_Flash_Write(uint32_t addr, uint8_t *buf, uint32_t length )
{
    uint32_t pageNum = 0;
    uint32_t firstPageRemainByte = 0;
    uint32_t lastPageRemainByte = 0;
    uint32_t i;

    if((addr % PAGE_SIZE) == 0)
    {
        firstPageRemainByte = 0;
        pageNum = length / PAGE_SIZE;
        lastPageRemainByte = length % PAGE_SIZE;
    }
    else
    {
        firstPageRemainByte = PAGE_SIZE - (addr % PAGE_SIZE);
        pageNum   = (length - firstPageRemainByte) / PAGE_SIZE;
        lastPageRemainByte = (length - firstPageRemainByte) % PAGE_SIZE;
    }

    if(firstPageRemainByte)
    {
        Drv_Flash_Write_With_DMA(addr, buf, firstPageRemainByte);

        addr += firstPageRemainByte;
        buf += firstPageRemainByte;
    }

    for(i=0;i<pageNum;i++)
    {
        Drv_Flash_Write_With_DMA(addr, buf, PAGE_SIZE);

        addr += PAGE_SIZE;
        buf += PAGE_SIZE;
    }

    Drv_Flash_Write_With_DMA(addr, buf, lastPageRemainByte);
}

