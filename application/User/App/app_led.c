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
    .name = LED_CHARGING,
    .style = LED_FLASH_REGULAR,
    .onTime = LED_FLASH_REGULAR_ON_TIME,
    .offTime = LED_FLASH_REGULAR_OFF_TIME,
    .delayCnt = 0,
    .speed = 0
};

led_block_t ledBattery = 
{
    .port = PORT7,
    .pin = PIN2,
    .name = LED_BATTERY,
    .style = LED_FLASH_QUICK,
    .onTime = LED_FLASH_QUICK_ON_TIME,
    .offTime = LED_FLASH_QUICK_OFF_TIME,
    .delayCnt = 0,
    .speed = 0
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



void App_Led_Set(uint8_t *buf, uint16_t length )
{
    led_block_t *led = NULL;
    uint8_t name = buf[0];
    uint8_t style = buf[1];
    uint16_t onTime = (uint16_t )buf[3] << 8 | buf[2];
    uint16_t offTime = (uint16_t )buf[5] << 8 | buf[4];
    uint8_t speed = buf[6];

    
    
    if(name == LED_CHARGING)
    {
        led = (led_block_t *)&ledCharging;
    }
    else if(name == LED_BATTERY)
    {
        led = (led_block_t *)&ledBattery;
    }

    led->name = name;
    led->style = (led_style_t)style;
    led->onTime = onTime;
    led->offTime = offTime;
    led->speed = speed;
    
    App_Led_Set_Flash(name, style);
}

void App_Led_Set_Flash(uint8_t name, led_style_t style )
{
    led_block_t *led = NULL;

    if(name == LED_CHARGING)
    {
        led = (led_block_t *)&ledCharging;
    }
    else if(name == LED_BATTERY)
    {
        led = (led_block_t *)&ledBattery;
    }
    
    switch(style)
    {
        case LED_SOLID_OFF
    }
}



