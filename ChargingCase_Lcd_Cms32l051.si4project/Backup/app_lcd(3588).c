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
#include "stdio.h"
#include "drv_task.h"
#include "drv_timer.h"
#include "app_lcd.h"
#include "drv_lcd_picture.h"

/* Private typedef --------------------------------------*/
typedef void (*lcd_dislay_callback_t)(void );
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void App_Lcd_Display_Handler(void *arg );
static void App_Lcd_Show_Picture_End_Callback(void );
/* Private variables ------------------------------------*/
lcd_dislay_callback_t lcd_display_batt_level_callback = NULL;
lcd_dislay_callback_t lcd_display_earbud_chg_callabck = NULL;


void App_Lcd_Init(void )
{
    Drv_Lcd_Init();

    Drv_Task_Regist_Period(App_Lcd_Display_Handler, 0, 1, NULL);
}

static void App_Lcd_Display_Handler(void *arg )
{
    if(lcd_display_batt_level_callback != NULL)
    {
        lcd_display_batt_level_callback();
    }

    if(lcd_display_earbud_chg_callabck != NULL)
    {
        lcd_display_earbud_chg_callabck();
    }
    
}

void App_Lcd_Show_Picture(void )
{
    Drv_Lcd_Show_Picture(gImage_bt_logo, sizeof(gImage_bt_logo), App_Lcd_Show_Picture_End_Callback);
}

static void App_Lcd_Show_Picture_End_Callback(void )
{
    
}

void App_Lcd_Display_BattLeve_Solid(uint8_t battLevel )
{
    char buf[4];
    lcd_display_batt_level_callback = NULL;

    sprintf(buf, "%d", battLevel);

    buf[3] = '%';
    
    Drv_Lcd_Show_String(32, 10, (const uint8_t *)buf, WHITE, BLACK, 32, 0);
}

