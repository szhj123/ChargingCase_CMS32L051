/********************************************************
* @file       drv_event.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_event.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
msg_queue_t msgQueue;

void Drv_Msg_Init(void )
{
    uint8_t i;

    for(i=0;i<MSG_QUEUE_MAX_LENGTH;i++)
    {
        memset((void *)&msgQueue.msgBuf[i], 0, sizeof(msg_t));
    }
}

void Drv_Msg_Queue_Add(void (*handler)(void *), uint8_t cmd, uint8_t *buf, uint8_t length )
{
    uint8_t i;
    
    msgQueue.msgBuf[msgQueue.rear].handler = handler;    
    msgQueue.msgBuf[msgQueue.rear].cmd = cmd;
    msgQueue.msgBuf[msgQueue.rear].length = length;

    for(i=0;i<length;i++)
    {
        msgQueue.msgBuf[msgQueue.rear].buf[i] = buf[i];
    }

    msgQueue.rear = (msgQueue.rear + 1) % MSG_QUEUE_MAX_LENGTH;
}

uint8_t Drv_Msg_Queue_Get(msg_t *msg )
{
    uint8_t ret = 0;
    
    if(msgQueue.head != msgQueue.rear)
    {
        *msg = msgQueue.msgBuf[msgQueue.head];

        msgQueue.head = (msgQueue.head + 1) % MSG_QUEUE_MAX_LENGTH;

        ret = 1;
    }

    return ret;
}

