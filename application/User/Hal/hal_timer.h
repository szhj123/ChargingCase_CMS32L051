#ifndef _HAL_TIMER_H
#define _HAL_TIMER_H

#include "hal_cms32l051.h"

void Hal_Timer_Init(void );
void Hal_Timer_Regist_Isr_Callback(Hal_Isr_Callback_t callback );
void Hal_Timer_Isr_Handler(void );

#endif 

