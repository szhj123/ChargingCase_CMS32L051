/********************************************************
* @file       hal_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_flash.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/

void Hal_Flash_Init(void )
{
    Cms32l051_Spi00_Init();
}

void Hal_Flash_Start(void )
{
    SPI00_Start();
}

void Hal_Flash_Stop(void )
{
    SPI00_Stop();
}

void Hal_Flash_Single_Write(uint8_t dat )
{
    SCI0->SIO00 = dat;
    
    while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
    {
        ;
    }
}

void Hal_Flash_Multiple_Send(uint8_t *buf, uint16_t length )
{
    uint16_t i;

    for(i=0;i<length;i++)
    {
        SCI0->SIO00 = buf[i];
    
        while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }
    }
}

void Hal_Flash_Multiple_Read(uint8_t *buf, uint16_t length )
{
    uint16_t i;
    uint8_t dummy = 0xff;

    for(i=0;i<length;i++)
    {
        SCI0->SIO00 = dummy; 
        
        while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }

        buf[i] = SCI0->SIO00;
    }
}

