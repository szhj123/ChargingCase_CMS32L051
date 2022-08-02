#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

void App_Lcd_Init(void );
void App_Lcd_Show_Picture(void );
void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel );
void App_Lcd_Set_EarbudChg_L_Flash(void );
void App_Lcd_Set_EarbudChg_R_Flash(void );

#endif 

