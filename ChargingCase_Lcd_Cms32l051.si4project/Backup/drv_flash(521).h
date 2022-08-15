#ifndef _DRV_FLASH_H
#define _DRV_FLASH_H

#include "hal_flash.h"

#define WRITE_ENABLE                        0x06
#define WRITE_DISABLE                       0x04
#define READ_STATUS_REGISTER                0x05
#define WRITE_STATUS_REGISTER               0x01
#define READ_DATA                           0x03
#define FAST_READ                           0x0b
#define PAGE_PROGRAM                        0x02
#define SECTOR_ERASE                        0x20
#define BLOCK_ERASE_32K                     0x52
#define BLOCK_ERASE_64K                     0xd8
#define CHIP_ERASE                          0x60
#define READ_JEDEC_ID                       0x9f

#define ERASE_SECTOR_SIZE                   4096
#define ERASE_32K_BLOCK_SIZE                32768u
#define ERASE_64K_BLOCK_SIZE                65536u
#define PAGE_SIZE                           256


void Drv_Flash_Init(void );
void Drv_Flash_Read_Jedec_Id(void );
void Drv_Flash_Sector_Erase(uint32_t addr );
void Drv_Flash_Write_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length );
void Drv_Flash_Read_With_Loop(uint32_t add, uint8_t *buf, uint16_t length );

#endif 

