/********************************************************
* @file       hal_timer.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_timer.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
static Hal_Isr_Callback_t hal_timer_isr_callback = NULL;

void Hal_Timer_Init(void )
{
    Cms32l051_Tim40_Channel0_Interval_Init();
}

void Hal_Timer_Regist_Isr_Callback(Hal_Isr_Callback_t callback )
{
    hal_timer_isr_callback = callback;
}

void Hal_Timer_Isr_Handler(void )
{
    if(hal_timer_isr_callback != NULL)
    {
        hal_timer_isr_callback();
    }
}


