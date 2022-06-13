#ifndef _DRV_COM_H
#define _DRV_COM_H

#include "hal_com.h"

typedef void (*drv_com_rx_callback_t)(uint8_t cmd, uint8_t *buf, uint16_t length );

typedef enum
{
    COM_RX_SYNC = 0,
    COM_RX_LENGTH,
    COM_RX_DATA,
    COM_RX_CHECKSUM
}com_rx_state_t;

void Drv_Com_Init(void );
void Drv_Com_Regist_Rx_Callback(drv_com_rx_callback_t callback );
void Drv_Com_Send_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback );

#endif 

