/********************************************************
* @file       app_com.c
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
#include "app_com.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Com_Msg_Set(uint8_t cmd, uint8_t *buf, uint16_t length );
static void App_Com_Rx_Handler(void *arg );

/* Private variables ------------------------------------*/

void App_Com_Init(void )
{
    Drv_Com_Init();

    Drv_Com_Regist_Rx_Callback(App_Com_Msg_Set);

}

static void App_Com_Msg_Set(uint8_t cmd, uint8_t *buf, uint16_t length )
{
    Drv_Msg_Queue_Set(App_Com_Rx_Handler, cmd, buf, length);
}

static void App_Com_Rx_Handler(void *arg )
{
    msg_t *msg = (msg_t *)arg; 

    switch(msg->cmd)
    {
        case CMD_SET_LED:
        {
            App_Led_Set_Para(msg->buf, msg->length);
            break;
        }
        default: break;
    }
}

