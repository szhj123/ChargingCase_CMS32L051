#ifndef _DRV_LED_H
#define _DRV_LED_H

#include "hal_led.h"

#define LED_FLASH_REGULAR_ON_TIME                 400 //ms
#define LED_FLASH_REGULAR_OFF_TIME                400 //ms
#define LED_FLASH_SLOW_ON_TIME                    250 //mS
#define LED_FLASH_SLOW_OFF_TIME                   2000 //ms
#define LED_FLASH_QUICK_ON_TIME                   250 //ms
#define LED_FLASH_QUICK_OFF_TIME                  250 //ms

typedef enum _led_style_t
{
    LED_SOLID_OFF = 0,
    LED_SOLID_ON, 
    LED_FLASH_SLOW,
    LED_FLASH_REGULAR,
    LED_FLASH_QUICK,
    LED_BREATH
}led_style_t;

typedef struct _led_block_t
{
    PORT_TypeDef port;
    PIN_TypeDef  pin;

    uint8_t  name;

    led_style_t style;

    uint16_t onTime;
    uint16_t offTime;
    uint16_t delayCnt;
    uint8_t  speed;
}led_block_t;

void Drv_Led_Init(led_block_t *led );
void Drv_Led_Solid_On(led_block_t *led );
void Drv_Led_Solid_Off(led_block_t *led );
void Drv_Led_Flash(led_block_t *led );

#endif 

