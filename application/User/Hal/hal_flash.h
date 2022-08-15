#ifndef _HAL_FLASH_H
#define _HAL_FLASH_H

#include "hal_cms32l051.h"

typedef void (*spi00_isr_callback_t)(void );

void Hal_Flash_Init(void );
void Hal_Flash_Start(void );
void Hal_Flash_Stop(void );
void Hal_Flash_Single_Write(uint8_t dat );
void Hal_Flash_Multiple_Send(uint8_t *buf, uint16_t length );
void Hal_Flash_Multiple_Read(uint8_t *buf, uint16_t length );
void Hal_Flash_Multiple_Write_With_DMA(uint8_t *buf, uint16_t length , spi00_isr_callback_t callback );
void Hal_Flash_Spi00_Tx_Isr_Handler(void );
void Hal_Flash_Multiple_Read_With_DMA(uint8_t *buf, uint16_t length , spi00_isr_callback_t callback );
void Hal_Flash_Spi00_Rx_Isr_Handler(void );


#endif 

