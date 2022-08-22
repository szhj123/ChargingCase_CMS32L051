#ifndef _HAL_FLASH_H
#define _HAL_FLASH_H

#include "hal_cms32l051.h"

void Hal_Flash_Init(void );
void Hal_Flash_Start(void );
void Hal_Flash_Stop(void );
void Hal_Flash_Single_Write(uint8_t dat );
void Hal_Flash_Multiple_Write_With_Loop(uint8_t *buf, uint16_t length );
void Hal_Flash_Multiple_Read_With_Loop(uint8_t *buf, uint16_t length );


#endif 

