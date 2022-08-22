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
drv_com_rx_callback_t drv_com_rx_callback = NULL;
com_queue_t comQueue;


void Drv_Com_Init(void )
{
    Hal_Com_Init();

    Hal_Com_Regist_Rx_Callback(Drv_Com_Rx_Handler);
}

void Drv_Com_Regist_Rx_Callback(drv_com_rx_callback_t callback )
{
    drv_com_rx_callback = callback;
}

void Drv_Com_Tx_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback )
{
    Hal_Com_Tx_With_Interrupt(buf, length, callback);   
}

static void Drv_Com_Rx_Handler(uint8_t recvData )
{
    static com_rx_state_t comRxState = COM_RX_SYNC;
    static uint8_t comRxDataCnt = 0;
    static uint8_t comRxDataLength;
    static uint8_t comRxBuf[128];
    static uint8_t comRxDataCalChecksum = 0;

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
                    comRxDataCalChecksum = 0;
                    comRxState = COM_RX_LENGTH;
                }
            }
            break;
        }
        case COM_RX_LENGTH:
        {
            if(recvData > sizeof(comRxBuf))
            {
                comRxDataLength = sizeof(comRxBuf);
            }
            else
            {
                comRxDataLength = recvData;
            }
            
            comRxBuf[comRxDataCnt++] = comRxDataLength;
            comRxDataCalChecksum += comRxDataLength;
            comRxState = COM_RX_DATA;
            break;
        }
        case COM_RX_DATA:
        {
            if(comRxDataCnt < comRxDataLength)
            {
                comRxBuf[comRxDataCnt++] = recvData;
                comRxDataCalChecksum += recvData;
            }

            if(comRxDataCnt == comRxDataLength)
            {
                comRxState = COM_RX_CHECKSUM;
            }
            break;
        }
        case COM_RX_CHECKSUM:
        {
            uint8_t comRxDataChecksum = recvData;

            if(comRxDataCalChecksum == comRxDataChecksum)
            {
                if(drv_com_rx_callback != NULL)
                {
                    drv_com_rx_callback(comRxBuf[1], &comRxBuf[2], comRxDataLength-2);
                }
            }

            comRxDataCnt = 0;
                
            comRxState = COM_RX_SYNC;
            
            break;
        }
    }
    
}

void Drv_Com_Queue_Put(uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    if(length > COM_MAX_DATA_LENGTH)
    {
        length = COM_MAX_DATA_LENGTH;
    }

    for(i=0;i<length;i++)
    {
        comQueue.qBuf[comQueue.tail].dBuf[i] = buf[i];
    }

    comQueue.qBuf[comQueue.tail].length = length;

    comQueue.tail = (comQueue.tail + 1) % COM_MAX_QUEUE_LENGTH;
}

uint8_t Drv_Com_Queue_Get(com_data_t *comData )
{
    uint8_t retVal = 0;
    
    if(comQueue.head != comQueue.tail)
    {
        *comData = comQueue.qBuf[comQueue.head];

        comQueue.head = (comQueue.head + 1) % COM_MAX_QUEUE_LENGTH;

        retVal = 1;
    }

    return retVal;
}


