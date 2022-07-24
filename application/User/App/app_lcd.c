/********************************************************
* @file       app_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"

#include "app_lcd.h"
#include "app_lcd_picture.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void App_Lcd_Show_Picture_End_Callback(void );
/* Private variables ------------------------------------*/

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();

    App_Lcd_Show_Picture();
}

void App_Lcd_Show_Picture(void )
{
    Drv_Lcd_Show_Picture(gImage_pic, sizeof(gImage_pic), App_Lcd_Show_Picture_End_Callback);
}

static void App_Lcd_Show_Picture_End_Callback(void )
{
    
}

