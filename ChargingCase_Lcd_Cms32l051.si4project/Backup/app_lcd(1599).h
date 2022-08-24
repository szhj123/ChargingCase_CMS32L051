#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

typedef void (*lcd_show_callback_t)(void );

typedef struct _pic_para_t
{
    uint8_t picIndex;
    uint16_t width;
    uint16_t height;
}pic_para_t;

typedef struct _lcd_para_t
{
    pic_para_t picPara;
    lcd_show_callback_t show_battLevel_callback;
    lcd_show_callback_t l_show_earbudChg_callback; 
    lcd_show_callback_t r_show_earbudChg_callback;

    uint32_t picFlashAddr;
    
    uint8_t l_earbudFlashStep;
    uint8_t r_earbudFlashStep;
    char battLevelStr[5];

    uint16_t battLeveColor;
    
    uint16_t startX;
    uint16_t startY;
    uint8_t  flashCharIndex;
    uint8_t  flashCharLength;

    uint16_t showBattLevelDelayCnt;
    uint16_t l_showEarbudChgDelayCnt;
    uint16_t r_showEarbudChgDelayCnt;
}lcd_para_t;

void App_Lcd_Init(void );
void App_Lcd_Clr(void );
void App_Lcd_Show_Picture(void );
void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel, uint16_t color );
void App_Lcd_Set_BattLevel_Flash(uint8_t battLevel, uint16_t color );
void App_Lcd_Set_EarbudChg_L_Flash(void );
void App_Lcd_Set_EarbudChg_R_Flash(void );
void App_Lcd_Ui_Init(uint8_t battLevel );
void App_Lcd_Show_Bt_Logo(void );
void App_Lcd_Set_Earbud_L_Solid(void );
void App_Lcd_Set_Earbud_R_Solid(void );
void App_Lcd_Background_Led_On(void );
void App_Lcd_Background_Led_Off(void );
void App_Lcd_Set_Pic_Enable(uint8_t *buf, uint16_t length );
void App_Lcd_Set_Pic_Data(uint8_t *buf, uint16_t length );
void App_Lcd_Show_Picture_Handler(void );

#endif 

