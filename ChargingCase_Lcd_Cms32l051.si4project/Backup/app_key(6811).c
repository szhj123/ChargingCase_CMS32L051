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
#include "drv_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
#define CMD_HALL									0
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Hall_Detect_Callback(void );
static void App_Hall_Handler(void *arg );
static void App_Hall_Event_Handler(void *arg );
static void App_Lcd_Show_Pic_End_Callbck(void *arg );
/* Private variables ------------------------------------*/

void App_Key_Init(void )
{
    Drv_Key_Init();

    Drv_Key_Regist_Isr_Callback(App_Hall_Detect_Callback);
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
    
    if(Drv_Key_Get_Hall_State())
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

    if(hallState)
    {
        
    }
    else
    {
        
    }

    if(App_Batt_Get_Usb_State() == USB_PLUG_OUT)
    {
        App_Lcd_Show_Picture();

        Drv_Timer_Delete(showTimerId);

        showTimerId = Drv_Timer_Regist_Oneshot(App_Lcd_Show_Pic_End_Callbck, 5000, NULL);
    }
}

static void App_Lcd_Show_Pic_End_Callbck(void *arg )
{
    App_Lcd_Clr();

    App_Batt_Send_Event();
}

