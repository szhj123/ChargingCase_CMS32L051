/********************************************************
* @file       hal_task.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
Hal_Isr_callback_t hal_systick_isr_callback = NULL;

void Hal_Task_Init(Hal_Isr_callback_t callback )
{
    hal_systick_isr_callback = callback;
    
}

