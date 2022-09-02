#ifndef _APP_COM_H
#define _APP_COM_H

#include "drv_com.h"



#define CMD_SET_LED                0x01
#define CMD_LCD_SEND_EN            0x02
#define CMD_LCD_SEND_DATA          0x03
#define CMD_LCD_REPLY              0x84

#define CMD_LCD_ACK                1
#define CMD_LCD_NACK               2


void App_Com_Init(void );
void App_Com_Tx_Reply(uint8_t reply );

#endif 

