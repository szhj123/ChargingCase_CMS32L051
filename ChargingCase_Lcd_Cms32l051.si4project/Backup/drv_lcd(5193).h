#ifndef _DRV_LCD_H
#define _DRV_LCD_H

#include "hal_lcd.h"

void Drv_Lcd_Init(void );
void Drv_Lcd_Clr(uint16_t color );
void Drv_Lcd_Show_Picture(const uint8_t *buf, uint32_t length, Hal_Isr_Callback_t callback );
void Drv_Lcd_Set_Position(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY );
void Drv_Lcd_Wr_Cmd(uint8_t cmd );
void Drv_Lcd_Wr_Data(uint8_t dat );
void Drv_LCD_BackLed_On(void );
void Drv_LCD_BackLed_Off(void );
void Drv_Lcd_Delay_Us(uint16_t us );

#endif 


