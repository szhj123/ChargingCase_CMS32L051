#ifndef _DRV_TASK_H
#define _DRV_TASK_H

#include "hal_task.h"

#define TASK_ERROR                0
#define TASK_OK                   (!TASK_ERROR)

typedef enum _task_state_t
{
    TASK_READY = 0,
    TASK_SUSPEND,
    TASK_SLEEP,
    TASK_IDLE
}task_state_t;

typedef struct _task_block_t
{
    void (*handler)(void *);
    void *arg;
    
    uint8_t  id;
    uint16_t ticks;
    uint16_t period;
    
    task_state_t state;

    struct _task_block_t *prev;
    struct _task_block_t *next;
}task_block_t;

void Drv_Task_Init(void );
task_block_t * Drv_Task_Regist_Period(void (*handler)(void *), uint16_t ticks, uint16_t period, void *arg );
task_block_t * Drv_Task_Regist_Oneshot(void (*handler)(void *), uint16_t ticks, void *arg );
int Drv_Task_Delay(task_block_t *task, uint16_t ticks );
int Drv_Task_Sleep(task_block_t *task );
int Drv_Task_Wakeup(task_block_t *task );
int Drv_Task_Delete(task_block_t *task );
void Drv_Task_Scheduler(void );


#endif 

