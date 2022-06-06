/********************************************************
* @file       drv_task.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/

#include <stdio.h>
#include "CMS32L051.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Task_Isr_Callback(void );
/* Private variables ------------------------------------*/

void Drv_Task_Init(void )
{
    Hal_Drv_Task_Init(Drv_Task_Isr_Callback);
}


static void Drv_Task_Isr_Callback(void )
{
    
}
