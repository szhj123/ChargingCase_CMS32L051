#ifndef _APP_KEY_H
#define _APP_KEY_H

#include "drv_key.h"

#define TX_IDLE                       0
#define TX_BUSY                       (!TX_IDLE)

typedef enum
{
    TX_LOW = 0,
    TX_HIGH,
    TX_EXIT
}tx_state_t;

typedef struct _tx_para_t
{
    uint8_t   txStep;
    uint16_t lowLevelTime;
    uint16_t delayCnt;
    uint8_t  txCnt;
    uint8_t  txEn;
}tx_para_t;

void App_Key_Init(void );
void App_Cmd_OpenCase_Tx(void );
void App_Cmd_CloseCase_Tx(void );
uint8_t App_Hall_Get_State(void );

#endif 

