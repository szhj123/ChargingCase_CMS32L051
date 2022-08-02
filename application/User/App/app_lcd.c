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
static void App_Lcd_EarbudChg_L_Flash(void );
static void App_Lcd_EarbudChg_R_Flash(void );
/* Private variables ------------------------------------*/
task_block_t *taskLcd = NULL;


lcd_dislay_callback_t lcd_display_batt_level_callback = NULL;
lcd_dislay_callback_t lcd_display_earbudChg_l_callabck = NULL;
lcd_dislay_callback_t lcd_display_earbudChg_r_callabck = NULL;

static uint8_t l_earbudFlashStep;
static uint8_t r_earbudFlashStep;

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();

    taskLcd = Drv_Task_Regist_Period(App_Lcd_Display_Handler, 0, 1, NULL);
}

static void App_Lcd_Display_Handler(void *arg )
{
    if(lcd_display_batt_level_callback != NULL)
    {
        lcd_display_batt_level_callback();
    }

    if(lcd_display_earbudChg_l_callabck != NULL)
    {
        lcd_display_earbudChg_l_callabck();
    }

    if(lcd_display_earbudChg_r_callabck != NULL)
    {
        lcd_display_earbudChg_r_callabck();
    }
    
}

void App_Lcd_Show_Picture(void )
{
    Drv_Lcd_Show_Picture(gImage_bt_logo, sizeof(gImage_bt_logo), App_Lcd_Show_Picture_End_Callback);
}

static void App_Lcd_Show_Picture_End_Callback(void )
{
    
}

void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel )
{
    char buf[5];
    
    lcd_display_batt_level_callback = NULL;

    sprintf(buf, "%3d", battLevel);

    buf[3] = '%';
    buf[4] = '\0';
    
    Drv_Lcd_Show_String(32, 10, (const uint8_t *)buf, WHITE, BLACK, 32, 0);
}

void App_Lcd_Set_EarbudChg_L_Flash(void )
{
    Drv_Lcd_Fill(35, 50, 50, 55, WHITE);
    Drv_Lcd_Draw_Rectangle(30, 55, 55, 115, WHITE);

    l_earbudFlashStep = 0;

    lcd_display_earbudChg_l_callabck = App_Lcd_EarbudChg_L_Flash;
}

static void App_Lcd_EarbudChg_L_Flash(void )
{
    switch(l_earbudFlashStep)
    {
        case 0:
        {
            Drv_Lcd_Fill(35, 104, 51, 112, RED);
            l_earbudFlashStep = 1;
            break;
        }
        case 1:
        {
            Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
            Drv_Lcd_Fill(35, 104, 51, 112, RED);
            l_earbudFlashStep = 2;
            break;
        }
        case 2: 
        {
            Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
            Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
            Drv_Lcd_Fill(35, 104, 51, 112, RED);
            l_earbudFlashStep = 3;
            break;
        }
        case 3:
        {
            Drv_Lcd_Fill(35, 71, 51, 79, GREEN);
            Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
            Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
            Drv_Lcd_Fill(35, 104, 51, 112, RED);
            l_earbudFlashStep = 4;
            break;
        }
        case 4:
        {
            Drv_Lcd_Fill(35, 60, 51, 68, GREEN);
            Drv_Lcd_Fill(35, 71, 51, 79, GREEN);
            Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
            Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
            Drv_Lcd_Fill(35, 104, 51, 112, RED);
            l_earbudFlashStep = 5;
            break;
        }
        case 5:
        {
            Drv_Lcd_Fill(35, 60, 51, 68, BLACK);
            Drv_Lcd_Fill(35, 71, 51, 79, BLACK);
            Drv_Lcd_Fill(35, 82, 51, 90, BLACK);
            Drv_Lcd_Fill(35, 93, 51, 101, BLACK);
            Drv_Lcd_Fill(35, 104, 51, 112, BLACK);
            l_earbudFlashStep = 0;
            break;
        }
        default: break;
    }

    Drv_Task_Delay(taskLcd, 250);
}

void App_Lcd_Set_EarbudChg_R_Flash(void )
{
    Drv_Lcd_Fill(85, 50, 100, 55, WHITE);
    Drv_Lcd_Draw_Rectangle(80, 55, 105, 115, WHITE);
    
    r_earbudFlashStep = 0;

    lcd_display_earbudChg_r_callabck = App_Lcd_EarbudChg_R_Flash;
}

static void App_Lcd_EarbudChg_R_Flash(void )
{
    switch(r_earbudFlashStep)
    {
        case 0:
        {
            Drv_Lcd_Fill(85, 104, 101, 112, RED);
            r_earbudFlashStep = 1;
            break;
        }
        case 1:
        {
            Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
            Drv_Lcd_Fill(85, 104, 101, 112, RED);
            r_earbudFlashStep = 2;
            break;
        }
        case 2:
        {
            Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
            Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
            Drv_Lcd_Fill(85, 104, 101, 112, RED);
            r_earbudFlashStep = 3;
            break;
        }
        case 3:
        {
            Drv_Lcd_Fill(85, 71, 101, 79, GREEN);
            Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
            Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
            Drv_Lcd_Fill(85, 104, 101, 112, RED);
            r_earbudFlashStep = 4;
            break;
        }
        case 4:
        {
            Drv_Lcd_Fill(85, 60, 101, 68, GREEN);
            Drv_Lcd_Fill(85, 71, 101, 79, GREEN);
            Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
            Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
            Drv_Lcd_Fill(85, 104, 101, 112, RED);
            r_earbudFlashStep = 5;
            break;
        }
        case 5:
        {
            Drv_Lcd_Fill(85, 60, 101, 68, BLACK);
            Drv_Lcd_Fill(85, 71, 101, 79, BLACK);
            Drv_Lcd_Fill(85, 82, 101, 90, BLACK);
            Drv_Lcd_Fill(85, 93, 101, 101, BLACK);
            Drv_Lcd_Fill(85, 104, 101, 112, BLACK);
            r_earbudFlashStep = 0;
            break;
        }
        default: break;
    }

    Drv_Task_Delay(taskLcd, 250);
}

