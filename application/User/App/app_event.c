/********************************************************
* @file       app_event.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_task.h"
#include "drv_timer.h"
#include "drv_event.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Msg_Handler(void *arg );
/* Private variables ------------------------------------*/

void App_Msg_Init(void )
{
    Drv_Msg_Init();

    Drv_Task_Regist_Period(App_Msg_Handler, 0, 1, NULL);
}

static void App_Msg_Handler(void *arg )
{
    
}
