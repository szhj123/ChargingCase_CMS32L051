#ifndef _APP_COM_H
#define _APP_COM_H

#include "drv_com.h"

#define FW_VER_BUILD               0
#define FW_VER_MINOR               0
#define FW_VER_MAJOR               1

#define CMD_SET_LED                0x01
#define CMD_GET_LCD_ERASE          0x02
#define CMD_SET_LCD_DATA           0x03
#define CMD_GET_LCD_ACK            0x04
#define CMD_SET_LCD_ACK            (CMD_GET_LCD_ACK | 0x80)

#define CMD_GET_FW_VERSION         0x09
#define CMD_SET_FW_VERSION         (CMD_GET_FW_VERSION | 0x80)

#define CMD_LCD_ACK                1
#define CMD_LCD_NACK               2


void App_Com_Init(void );
void App_Com_Tx_Reply(uint8_t reply );
void App_Com_Tx_Version(void );

#endif 

