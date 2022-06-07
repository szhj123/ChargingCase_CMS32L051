#ifndef _HAL_LED_H
#define _HAL_LED_H

#include "hal_cms32l051.h"

#define LED_OFF                 0
#define LED_ON                  (!LED_OFF)

void Hal_Led_Gpio_Init(PORT_TypeDef port, PIN_TypeDef pin );
void Hal_Led_Set_On(PORT_TypeDef port, PIN_TypeDef pin );
void Hal_Led_Set_Off(PORT_TypeDef port, PIN_TypeDef pin );
uint8_t Hal_Led_Get_State(PORT_TypeDef port, PIN_TypeDef pin );

#endif 

