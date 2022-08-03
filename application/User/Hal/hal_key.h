#ifndef _HAL_KEY_H
#define _HAL_KEY_H

#include "hal_cms32l051.h"

void Hal_Key_Init(void );
void Hal_Key_Regist_Isr_Callback(Hal_Isr_Callback_t callback );
uint8_t Hal_Key_Get_Hall_State(void );
void Hal_Key_Tx_High(void );
void Hal_Key_Tx_Low(void );
void Hal_Key_Isr_Handler(void );

#endif 

