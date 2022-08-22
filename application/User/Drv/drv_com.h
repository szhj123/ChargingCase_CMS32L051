#ifndef _DRV_COM_H
#define _DRV_COM_H

#include "hal_com.h"

typedef void (*drv_com_rx_callback_t)(uint8_t cmd, uint8_t *buf, uint16_t length );

#define COM_MAX_DATA_LENGTH        24   
#define COM_MAX_QUEUE_LENGTH       8

typedef struct _com_data_t
{
    uint8_t dBuf[COM_MAX_DATA_LENGTH];
    uint8_t length;
}com_data_t;

typedef struct _com_queue_t
{
    com_data_t qBuf[COM_MAX_QUEUE_LENGTH];
    uint8_t head;
    uint8_t tail;
}com_queue_t;

typedef enum
{
    COM_RX_SYNC = 0,
    COM_RX_LENGTH,
    COM_RX_DATA,
    COM_RX_CHECKSUM
}com_rx_state_t;

void Drv_Com_Init(void );
void Drv_Com_Regist_Rx_Callback(drv_com_rx_callback_t callback );
void Drv_Com_Tx_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback );
void Drv_Com_Queue_Put(uint8_t *buf, uint8_t length );
uint8_t Drv_Com_Queue_Get(com_data_t *comData );

#endif 

