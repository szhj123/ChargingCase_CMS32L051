/********************************************************
* @file       drv_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_key.h"
#include "app_battery.h"
#include "app_lcd.h"
#include "drv_timer.h"
#include "drv_task.h"
#include "drv_event.h"
/* Private typedef --------------------------------------*/
typedef void (*cmd_handler_t)(void );
/* Private define ---------------------------------------*/
#define CMD_HALL									0
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Hall_Detect_Callback(void );
static void App_Hall_Handler(void *arg );
static void App_Hall_Event_Handler(void *arg );
static void App_Hall_Handler_End_Callback(void *arg );

static void App_Cmd_Tx_Handler(void *arg );
static void App_Cmd_OpenCase_Tx_Callback(void );
static void App_Cmd_CloseCase_Tx_Callback(void );

/* Private variables ------------------------------------*/
tx_para_t txPara;
cmd_handler_t cmd_handler = NULL;

void App_Key_Init(void )
{
    Drv_Key_Init();

    Drv_Key_Regist_Isr_Callback(App_Hall_Detect_Callback);

    Drv_Task_Regist_Period(App_Cmd_Tx_Handler, 0, 1, NULL);
}

static void App_Hall_Detect_Callback(void )
{
    static uint8_t hallTimerId = TIMER_NULL;
    
    Drv_Timer_Delete(hallTimerId);

    hallTimerId = Drv_Timer_Regist_Oneshot(App_Hall_Handler, 500, NULL);
}

static void App_Hall_Handler(void *arg )
{
    uint8_t hallState;
    
    if(Drv_Get_Hall_State())
    {
        hallState = 1;
    }
    else
    {
        hallState = 0;
    }

    Drv_Msg_Queue_Put(App_Hall_Event_Handler, CMD_HALL, &hallState, 1);
}

static void App_Hall_Event_Handler(void *arg )
{
    static uint8_t showTimerId = TIMER_NULL;
    
    msg_t *msg = (msg_t *)arg;

    uint8_t hallState = msg->buf[0];

    if(App_Batt_Get_Usb_State() == USB_PLUG_OUT)
    {
        App_Lcd_Show_Pic();

        App_Batt_Delete_Standby_Timer();

        Drv_Timer_Delete(showTimerId);

        showTimerId = Drv_Timer_Regist_Oneshot(App_Hall_Handler_End_Callback, 5000, NULL);
    }

    if(hallState)
    {
        App_Cmd_OpenCase_Tx();
    }
    else
    {
        App_Cmd_CloseCase_Tx();
    }
}

static void App_Hall_Handler_End_Callback(void *arg )
{   
    App_Lcd_Show_Pic_Disable();
    
    App_Lcd_Clr();

    App_Batt_Send_Event();
}

static void App_Cmd_Tx_Delay_Count(void )
{
    if(txPara.delayCnt < 0xffff)
    {
        txPara.delayCnt++;
    }
}

static void App_Cmd_Tx_Handler(void *arg )
{
    App_Cmd_Tx_Delay_Count();

    if(cmd_handler != NULL)
    {
        cmd_handler();
    }
}

void App_Cmd_OpenCase_Tx(void )
{
    txPara.txStep = 0;
    txPara.delayCnt = 0;
    
    cmd_handler = App_Cmd_OpenCase_Tx_Callback;
}

static void App_Cmd_OpenCase_Tx_Callback(void )
{
    switch(txPara.txStep)
    {
        case 0:
        {
            Drv_Key_Tx_Low();
            
            txPara.delayCnt = 0;

            txPara.txStep = 1;
            
            break;
        }
        case 1:
        {
            if(txPara.delayCnt > 300)
            {
                Drv_Key_Tx_High();

                txPara.delayCnt = 0;

                txPara.txStep = 2;
            }
            
            break;
        }
        case 2:
        {
            if(txPara.delayCnt > 600)
            {
                Drv_Key_Tx_Low();
                
                txPara.delayCnt = 0;
                txPara.txStep = 3;
            }
            break;
        }
        case 3: 
        {
            if(txPara.delayCnt > 100)
            {
                Drv_Key_Tx_High();

                cmd_handler = NULL;
                
                txPara.delayCnt = 0;
                txPara.txStep = 0;
            }
            break;
        }
        default: break;
    }
}

void App_Cmd_CloseCase_Tx(void )
{
    txPara.txStep = 0;
    txPara.delayCnt = 0;
    
    cmd_handler = App_Cmd_CloseCase_Tx_Callback;
}

static void App_Cmd_CloseCase_Tx_Callback(void )
{
    Drv_Key_Tx_High();

    cmd_handler = NULL;
}

uint8_t App_Hall_Get_State(void )
{
    return Drv_Get_Hall_State();
}

