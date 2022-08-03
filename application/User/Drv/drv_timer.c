/********************************************************
* @file       drv_timer.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Timer_Isr_Handler(void );
/* Private variables ------------------------------------*/
timer_block_t timerList[TIMER_MAX_NUM];

void Drv_Timer_Init(void )
{
    uint8_t i;
    
    Hal_Timer_Init();

    Hal_Timer_Regist_Isr_Callback(Drv_Timer_Isr_Handler);

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        timerList[i].handler = NULL;
        timerList[i].arg = NULL;
        timerList[i].ticks = 0;
        timerList[i].period = 0;
        timerList[i].isRegist = 0;
    }
}

uint8_t Drv_Timer_Regist(void (*handler)(void *), uint16_t ticks, uint16_t period, void *arg )
{
    uint8_t id;

    for(id=0;id<TIMER_MAX_NUM;id++)
    {
        if(timerList[id].isRegist == 0)
        {
            timerList[id].handler = handler;
            timerList[id].arg = arg;
            timerList[id].id = id;
            timerList[id].ticks = ticks;
            timerList[id].period = period;
            timerList[id].isRegist = 1;

            break;
        }
    }

    return id;
}

uint8_t Drv_Timer_Regist_Period(void (*handler)(void *), uint16_t ticks, uint16_t period, void *arg )
{
    return Drv_Timer_Regist(handler, ticks, period, arg );    
}

uint8_t Drv_Timer_Regist_Oneshot(void (*handler)(void *), uint16_t ticks, void *arg )
{
    return Drv_Timer_Regist(handler, ticks, 0, arg );
}

void Drv_Timer_Delete(uint8_t timerId )
{
    if(timerId == TIMER_NULL)
    {
        return ;
    }

    timerList[timerId].handler = NULL;
    timerList[timerId].arg = NULL;
    timerList[timerId].id = 0;
    timerList[timerId].ticks = 0;
    timerList[timerId].period = 0;
    timerList[timerId].isRegist = 0;
}

static void Drv_Timer_Isr_Handler(void )
{
    uint8_t id;

    for(id=0;id<TIMER_MAX_NUM;id++)
    {
        if(timerList[id].isRegist)
        {
            if(timerList[id].ticks > 0)
            {
                timerList[id].ticks--;
            }

            if(timerList[id].ticks == 0)
            {
                if(timerList[id].handler != NULL)
                {
                    timerList[id].handler(timerList[id].arg);
                }

                if(timerList[id].period)
                {
                    timerList[id].ticks = timerList[id].period;
                }
                else
                {
                    Drv_Timer_Delete(id);
                }
            }
        }
    }
}

