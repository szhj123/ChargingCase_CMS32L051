/********************************************************
* @file       main.c
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
#include "drv_flash.h"
#include "app_battery.h"
#include "app_event.h"
#include "app_com.h"
#include "app_key.h"
#include "app_lcd.h"
#include "app_led.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/

int main(void )
{
    Drv_Task_Init();

    Drv_Timer_Init();

    //Drv_Flash_Init();

    App_Msg_Init();

    App_Lcd_Init();
    
    App_Key_Init();

    App_Batt_Init();

    
    //App_Com_Init();

    //App_Led_Init();
    
	while(1)
	{	
        Drv_Task_Scheduler();
	}
}



