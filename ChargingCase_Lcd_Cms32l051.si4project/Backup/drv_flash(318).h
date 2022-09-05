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

#define INTERNALE_FLASH_SECTOR_SIZE         512

#define BLD_START_ADDR                      0
#define BLD_MAX_SIZE                        0x1800
#define APP1_START_ADDR                     (BLD_START_ADDR + BLD_MAX_SIZE)
#define APP1_MAX_SIZE                       0x7400
#define APP2_START_ADDR                     (APP1_START_ADDR + APP1_MAX_SIZE)
#define APP2_MAX_SIZE                       0x7400

#define USER_DATA_START_ADDR                0x500200

typedef struct _user_data_t
{
    uint8_t fwUpgFlag;
}user_data_t;

void Drv_Flash_Init(void );
void Drv_Flash_Read_Jedec_Id(void );
void Drv_Flash_Sector_Erase(uint32_t addr );
void Drv_Flash_Block_64k_Erase(uint32_t addr );
void Drv_Flash_Chip_Erase(void );
void Drv_Flash_Write_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length );
void Drv_Flash_Read_With_Loop(uint32_t add, uint8_t *buf, uint16_t length );
void Drv_Flash_Write(uint32_t addr, uint8_t *buf, uint32_t length );
void Drv_Flash_Read(uint32_t addr, uint8_t *buf, uint32_t length );

int Drv_Internal_Flash_Sector_Erase(uint32_t adr );
int Drv_Internal_Flash_ProgramPage (uint32_t adr, uint32_t sz, uint8_t *buf);
void Drv_Flash_App2_Erase(uint32_t fwSize );
void Drv_Flash_App2_Program(uint32_t dataOffsetAddr, uint8_t *buf, uint32_t length );
uint16_t Drv_Flash_App2_Get_Checksum(uint32_t fwSize );

void Drv_Flash_Set_Upg_Flag(uint8_t flag );
void Drv_Flash_Save_User_Data(void );


void Bootloader_Run(void );

#endif 

