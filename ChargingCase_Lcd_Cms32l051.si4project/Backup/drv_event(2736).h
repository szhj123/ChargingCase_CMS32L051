#ifndef _DRV_EVENT_H
#define _DRV_EVENT_H

#include "hal_cms32l051.h"

#define MSG_DATA_MAX_LENGTH                64
#define MSG_QUEUE_MAX_LENGTH               16

typedef struct _msg_t
{
    void (*handler)(void *);
    uint8_t cmd;
    uint8_t buf[MSG_DATA_MAX_LENGTH];
    uint8_t length;
}msg_t;


typedef struct _msg_queue_t
{
    msg_t msgBuf[MSG_QUEUE_MAX_LENGTH];
    uint8_t head;
    uint8_t rear;
}msg_queue_t;


void Drv_Msg_Init(void );
void Drv_Msg_Queue_Set(void (*handler)(void *), uint8_t cmd, uint8_t *buf, uint8_t length );
uint8_t Drv_Msg_Queue_Get(msg_t *msg );

#endif 

