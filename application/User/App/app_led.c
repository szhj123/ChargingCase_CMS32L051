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

static uint16_t SLOW_ON_TIME = 250;//ms
static uint16_t SLOW_OFF_TIME = 2000;//ms
static uint16_t REGULAR_ON_TIME = 500;//ms
static uint16_t REGULAR_OFF_TIME = 500;//ms
static uint16_t QUICK_ON_TIME = 250;//ms
static uint16_t QUICK_OFF_TIME = 250;//ms
static uint8_t  BREATH_SPEED = 3;


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

void App_Led_Set_Para(uint8_t *buf, uint16_t length )
{
    uint8_t name = buf[0];
    led_style_t style = (led_style_t)buf[1];
    
    SLOW_ON_TIME = (uint16_t )buf[3] << 8 | buf[2];
    SLOW_OFF_TIME = (uint16_t )buf[5] << 8 | buf[4];

    REGULAR_ON_TIME = (uint16_t )buf[7] << 8 | buf[6];
    REGULAR_OFF_TIME = (uint16_t )buf[9] << 8 | buf[8];

    QUICK_ON_TIME = (uint16_t )buf[11] << 8 | buf[10];
    QUICK_OFF_TIME = (uint16_t )buf[13] << 8 | buf[12];
    
    BREATH_SPEED = buf[14];
    
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
    
    led->name = name;

    led->style = style;
    
    switch(style)
    {
        case LED_SOLID_OFF:
        case LED_SOLID_ON:
        {
            led->onTime = 0;
            led->offTime = 0;
            led->delayCnt = 0;
            break;
        }
        case LED_FLASH_SLOW:
        {
            led->onTime = SLOW_ON_TIME;
            led->offTime = SLOW_OFF_TIME;
            led->delayCnt = 0;
            break;
        }
        case LED_FLASH_REGULAR:
        {
            led->onTime = REGULAR_ON_TIME;
            led->offTime = REGULAR_OFF_TIME;
            led->delayCnt = 0;
            break;
        }
        case LED_FLASH_QUICK:
        {
            led->onTime = QUICK_ON_TIME;
            led->offTime = QUICK_OFF_TIME;
            led->delayCnt = 0;
            break;
        }
        case LED_BREATH:
        {
            led->speed = BREATH_SPEED;
            break;
        }
        default: break;
    }
}



