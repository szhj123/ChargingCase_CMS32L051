#ifndef _HAL_TASK_H
#define _HAL_TASK_H

#include "hal_cms32l051.h"

void Hal_Task_Init(void );
void Hal_Task_Regist_Isr_Callabck(Hal_Isr_Callback_t callback );
void Hal_Task_Isr_Handler(void );

#endif 

