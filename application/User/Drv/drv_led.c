/********************************************************
* @file       drv_led.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_led.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Led_Init(led_block_t *led )
{
    Hal_Led_Gpio_Init(led->port, led->pin);
}

void Drv_Led_Solid_On(led_block_t *led )
{
    led->delayCnt = 0;
    
    Hal_Led_Set_On(led->port, led->pin);
}

void Drv_Led_Solid_Off(led_block_t *led )
{
    led->delayCnt = 0;
    
    Hal_Led_Set_Off(led->port, led->pin);
}

void Drv_Led_Flash(led_block_t *led )
{
    if(led->delayCnt < 0xffff)
    {
        led->delayCnt++;
    }
        
    if(Hal_Led_Get_State(led->port, led->pin) == LED_ON)
    {
        if(led->delayCnt > led->onTime)
        {
            Hal_Led_Set_Off(led->port, led->pin);

            led->delayCnt = 0;
        }
    }
    else
    {
        if(led->delayCnt > led->offTime)
        {
            Hal_Led_Set_On(led->port, led->pin);

            led->delayCnt = 0;
        }
    }
}


