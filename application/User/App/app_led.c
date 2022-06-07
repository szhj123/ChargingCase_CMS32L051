/********************************************************
* @file       app_led.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"

#include "app_led.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Led_Handler(void *arg );
static void App_Led_Flash(led_block_t *led );

/* Private variables ------------------------------------*/
led_block_t ledCharging = 
{
    .port = PORT7,
    .pin  = PIN1,
    .style = LED_FLASH_REGULAR,
    .onTime = LED_FLASH_REGULAR_ON_TIME,
    .offTime = LED_FLASH_REGULAR_OFF_TIME,
    .delayCnt = 0
};

led_block_t ledBattery = 
{
    .port = PORT7,
    .pin = PIN2,
    .style = LED_FLASH_QUICK,
    .onTime = LED_FLASH_QUICK_ON_TIME,
    .offTime = LED_FLASH_QUICK_OFF_TIME,
    .delayCnt = 0
};


void App_Led_Init(void )
{
    Drv_Led_Init(&ledCharging);

    Drv_Led_Init(&ledBattery);

    Drv_Timer_Regist_Period(App_Led_Handler, 0, 1, NULL);
}

static void App_Led_Handler(void *arg )
{
    App_Led_Flash(&ledCharging);

    App_Led_Flash(&ledBattery);
}

static void App_Led_Flash(led_block_t *led )
{
    switch(led->style)
    {
        case LED_SOLID_OFF:
        {
            Drv_Led_Solid_Off(led);
            break;
        }
        case LED_SOLID_ON:
        {
            Drv_Led_Solid_On(led);
            break;
        }
        case LED_FLASH_SLOW:
        case LED_FLASH_REGULAR:
        case LED_FLASH_QUICK:
        {
            Drv_Led_Flash(led);
        }
        default: break;
    }
}

