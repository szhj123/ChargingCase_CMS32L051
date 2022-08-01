#ifndef _HAL_BATTERY_H
#define _HAL_BATTERY_H

#include "hal_cms32l051.h"

void Hal_Batt_Init(void );
void Hal_Batt_Boost_Enable(void );
void Hal_Batt_Boost_Disable(void );
uint8_t Hal_Batt_Get_Charge_State(void );
uint16_t Hal_Batt_Get_AdcVal(adc_channel_t adcChannel);


#endif 

