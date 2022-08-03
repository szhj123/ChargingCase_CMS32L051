#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

typedef void (*lcd_show_callback_t)(void );


typedef struct _lcd_para_t
{
    lcd_show_callback_t show_battLevel_callback;
    lcd_show_callback_t l_show_earbudChg_callback; 
    lcd_show_callback_t r_show_earbudChg_callback;
    uint8_t l_earbudFlashStep;
    uint8_t r_earbudFlashStep;
    char battLevelStr[5];

    uint16_t battLeveColor;
    
    uint16_t startX;
    uint16_t startY;

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

#endif 

