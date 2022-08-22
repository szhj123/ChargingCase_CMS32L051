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
#include "app_led.h"
#include "app_lcd.h"

/* Private typedef --------------------------------------*/
typedef enum 
{
    COM_TX_INIT = 0,
    COM_TX_PROCESS,
    COM_TX_EXIT
}com_tx_state_t;
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Com_Msg_Set(uint8_t cmd, uint8_t *buf, uint16_t length );
static void App_Com_Rx_Handler(void *arg );
static void App_Com_Tx_Handler(void *arg );
static void App_Com_Tx_End_Callback(void );

/* Private variables ------------------------------------*/
static com_tx_state_t comTxState;
static uint8_t comTxEndFlag;

void App_Com_Init(void )
{
    Drv_Com_Init();

    Drv_Com_Regist_Rx_Callback(App_Com_Msg_Set);

    Drv_Task_Regist_Period(App_Com_Tx_Handler, 0, 1, NULL);
}

static void App_Com_Msg_Set(uint8_t cmd, uint8_t *buf, uint16_t length )
{
    Drv_Msg_Queue_Put(App_Com_Rx_Handler, cmd, buf, length);
}

static void App_Com_Tx_Handler(void *arg )
{
    static com_data_t comData;
    
    switch(comTxState)
    {
        case COM_TX_INIT:
        {
            if(Drv_Com_Queue_Get(&comData))
            {
                comTxState = COM_TX_PROCESS;
            }
            break;
        }
        case COM_TX_PROCESS:
        {
            Drv_Com_Tx_With_Interrupt(comData.dBuf, comData.length, App_Com_Tx_End_Callback);

            comTxState = COM_TX_PROCESS;

            break;
        }
        case COM_TX_EXIT:
        {
            if(comTxEndFlag)
            {
                comTxEndFlag = 0;

                comTxState = COM_TX_INIT;
            }

            break;
        }
        default: break;
    }
}

static void App_Com_Tx_End_Callback(void )
{
    comTxEndFlag = 1;
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
        case CMD_LCD_SEND_EN:
        {
            App_Lcd_Set_Pic_Para(msg->buf, msg->length);

            App_Com_Tx_Reply();
            
        }
        default: break;
    }
}

void App_Com_Tx_Reply(uint8_t reply )
{
    uint8_t buf[6] = {0};
    uint8_t checksum = 0;
    
    buf[0] = 0x5a;
    buf[1] = 0x5a;
    buf[2] = 0x3;
    buf[3] = CMD_LCD_REPLY;
    buf[4] = reply;
    
    for(int i = 0;i<buf[2];i++)
    {
        checksum += buf[i+2];
    }

    buf[5] = (char)checksum;

    Drv_Com_Queue_Put(buf, buf[2]+3);
}

