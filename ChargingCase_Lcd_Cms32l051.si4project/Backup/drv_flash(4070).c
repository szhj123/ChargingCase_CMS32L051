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
/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/
uint8_t wrBuf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint8_t rdBuf[10];

void Drv_Flash_Init(void )
{
    Hal_Flash_Init();

    Drv_Flash_Read_Jedec_Id();

    Drv_Flash_Read_With_Loop(10, rdBuf, 10);
    
    Drv_Flash_Sector_Erase(0);

    Drv_Flash_Read_With_Loop(0, rdBuf, 10);

    //Drv_Flash_Write_With_Loop(0, wrBuf, 10);
    
    //Drv_Flash_Read_With_Loop(0, rdBuf, 10);
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

