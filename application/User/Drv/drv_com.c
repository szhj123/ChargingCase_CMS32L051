/********************************************************
* @file       drv_com.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_com.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Com_Rx_Handler(uint8_t recvData );

/* Private variables ------------------------------------*/

void Drv_Com_Init(void )
{
    Hal_Com_Init();

    Hal_Com_Regist_Rx_Callback(Drv_Com_Rx_Handler);
}



void Drv_Com_Send_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback )
{
    Hal_Com_Send_With_Interrupt(buf, length, callback);   
}

static void Drv_Com_Rx_Handler(uint8_t recvData )
{
    static com_rx_state_t comRxState = COM_RX_SYNC;
    static uint8_t comRxDataCnt;
    static uint8_t comRxBuf[128];

    switch(comRxState)
    {
        case COM_RX_SYNC:
        {
            if(recvData == 0x5a)
            {
                comRxDataCnt++;
                if(comRxDataCnt == 2)
                {
                    comRxDataCnt = 0;
                    comRxState = COM_RX_LENGTH:
                }
            }
            break;
        }
        case COM_RX_LENGTH:
        {
            if(recvData > sizeof(comRxBuf))
            break;
        }
    }
    
}

