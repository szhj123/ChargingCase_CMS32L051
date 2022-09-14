#ifndef _DRV_KEY_H
#define _DRV_KEY_H

#include "hal_key.h"

void Drv_Key_Init(void );
void Drv_Key_Regist_Isr_Callback(Hal_Isr_Callback_t callback );
uint8_t Drv_Get_Hall_State(void );
void Drv_Key_Tx_High(void );
void Drv_Key_Tx_Low(void );

#endif 

