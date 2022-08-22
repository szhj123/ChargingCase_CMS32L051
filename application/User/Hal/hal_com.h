#ifndef _HAL_COM_H
#define _HAL_COM_H

#include "hal_cms32l051.h"

typedef void (*hal_com_tx_end_callback_t)(void );
typedef void (*hal_com_rx_end_callback_t)(uint8_t );

void Hal_Com_Init(void );
void Hal_Com_Regist_Rx_Callback(hal_com_rx_end_callback_t callback );
void Hal_Com_Tx_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback );
void Hal_Com_Tx_Isr_Handler(void );
void Hal_Com_Rx_Isr_Handler(void );

#endif 

