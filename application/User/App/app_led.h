#ifndef _APP_LED_H
#define _APP_LED_H

#include "drv_led.h"

#define LED_CHARGING                 1
#define LED_BATTERY                  2

void App_Led_Init(void );
void App_Led_Set_Para(uint8_t *buf, uint16_t length );
void App_Led_Set_Flash(uint8_t name, led_style_t style );


#endif 

