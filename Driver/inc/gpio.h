/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    gpio.h
* @brief   This file implements device driver for GPIO module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef GPIO_H
#define GPIO_H
#ifndef __CORE_CM0PLUS_H_GENERIC
#include "core_cm0plus.h"
#endif

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
	PORT0 = 0,
	PORT1 = 1,
	PORT2 = 2,
	PORT3 = 3,
	PORT4 = 4,
	PORT5 = 5,
	PORT6 = 6,
	PORT7 = 7,
	PORT12 = 12,
	PORT13 = 13,
	PORT14 = 14,
	
}PORT_TypeDef;

typedef enum {
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	
}PIN_TypeDef;

typedef enum {
	INPUT = 0,
	PULLUP_INPUT,
	TTL_INPUT,
	ANALOG_INPUT,
	OUTPUT,
	OPENDRAIN_OUTPUT,
	PULLDOWN_INPUT,
}PIN_ModeDef;

typedef enum {
  P00_CFG = 0x00,
  P01_CFG = 0x01,
  P10_CFG = 0x08,
  P11_CFG = 0x09,
  P12_CFG = 0x0A,
  P13_CFG = 0x0B,
  P14_CFG = 0x0C,
  P15_CFG = 0x0D,
  P16_CFG = 0x0E,
  P17_CFG = 0x0F,
  P20_CFG = 0x10,
  P21_CFG = 0x11,
  P22_CFG = 0x12,
  P23_CFG = 0x13,
  P24_CFG = 0x14,
  P25_CFG = 0x15,
  P26_CFG = 0x16,
  P27_CFG = 0x17,
  P30_CFG = 0x18,
  P31_CFG = 0x19,
  P40_CFG = 0x20,
  P41_CFG = 0x21,
  P50_CFG = 0x28,
  P51_CFG = 0x29,
  P60_CFG = 0x30,
  P61_CFG = 0x31,
  P62_CFG = 0x32,
  P63_CFG = 0x33,
  P70_CFG = 0x38,
  P71_CFG = 0x39,
  P72_CFG = 0x3A,
  P73_CFG = 0x3B,
  P74_CFG = 0x3C,
  P75_CFG = 0x3D,
  P120_CFG = 0x40,
  P121_CFG = 0x41,
  P122_CFG = 0x42,
  P123_CFG = 0x43,
  P124_CFG = 0x44,
  P130_CFG = 0x48,
  P136_CFG = 0x4E,
  P137_CFG = 0x4F,
  P140_CFG = 0x50,
  P146_CFG = 0x56,
  P147_CFG = 0x57,
}IO_CfgType;

typedef enum {
  IOCFG_GPIO = 0x00,
  IOCFG_TO10 = 0x01,
  IOCFG_TO11 = 0x02,
  IOCFG_TO12 = 0x03,
  IOCFG_TO13 = 0x04,
  IOCFG_SDO00 = 0x05,
  IOCFG_TXD0 = 0x05,
  IOCFG_SDO20 = 0x06,
  IOCFG_TXD2 = 0x06,
  IOCFG_CLKBUZ0 = 0x07,
  IOCFG_SCLKO00 = 0x08,
  IOCFG_SCLKO20 = 0x09,
  IOCFG_TXD1 = 0x0A,
}IO_CfgDef;

typedef enum {
	
  TI10_PCFG = 0x00,                     /*!< (@ 0x00000860) TI10 alternate function pin configuration register         */
  TI11_PCFG = 0x01,                     /*!< (@ 0x00000861) TI11 alternate function pin configuration register         */
  TI12_PCFG = 0x02,                     /*!< (@ 0x00000862) TI12 alternate function pin configuration register         */
  TI13_PCFG = 0x03,                     /*!< (@ 0x00000863) TI13 alternate function pin configuration register         */
  INTP0_PCFG = 0x04,                    /*!< (@ 0x00000864) INTP0 alternate function pin configuration register        */
  INTP1_PCFG = 0x05,                    /*!< (@ 0x00000865) INTP1 alternate function pin configuration register        */
  INTP2_PCFG = 0x06,                    /*!< (@ 0x00000866) INTP2 alternate function pin configuration register        */
  INTP3_PCFG = 0x07,                    /*!< (@ 0x00000867) INTP3 alternate function pin configuration register        */
  
  SDI00_PCFG = 0x08,                    /*!< (@ 0x00000868) SDI00/RXD0/SDA00 alternate function pin configuration
                                                                    register                                                   */
  SDA00_PCFG = 0x08,                    /*!< (@ 0x00000868) SDI00/RXD0/SDA00 alternate function pin configuration
                                                                    register                                                   */
  RXD0_PCFG = 0x08,                     /*!< (@ 0x00000868) SDI00/RXD0/SDA00 alternate function pin configuration
                                                                    register                                                   */
  SCLKI00_PCFG = 0x09,                  /*!< (@ 0x00000869) SCLKI00 alternate function pin configuration
                                                                    register                                                   */
  SS00_PCFG = 0x0a,                     /*!< (@ 0x0000086A) SS00 alternate function pin configuration register         */
  
  SDI20_PCFG = 0x0b,                    /*!< (@ 0x0000086B) SDI20/RXD2/IrRXD alternate function pin configuration
                                                                    register                                                   */
  IRRXD_PCFG = 0x0b,                    /*!< (@ 0x0000086B) SDI20/RXD2/IrRXD alternate function pin configuration
                                                                    register                                                   */
  RXD2_PCFG = 0x0b,                     /*!< (@ 0x0000086B) SDI20/RXD2/IrRXD alternate function pin configuration
                                                                    register                                                   */
  
  SCLKI20_PCFG = 0x0c,                  /*!< (@ 0x0000086C) SCLKI20 alternate function pin configuration
                                                                    register                                                   */
  SDAA0_PCFG = 0x0d,                    /*!< (@ 0x0000086D) SDAA0 alternate function pin configuration register        */
  SCLA0_PCFG = 0x0e,                    /*!< (@ 0x0000086E) SCLA0 alternate function pin configuration register        */
  
  RXD1_PCFG = 0x0f,                     /*!< (@ 0x0000086F) RXD1 alternate function pin configuration register         */
  SDA10_PCFG = 0x0f,                    /*!< (@ 0x0000086F) SDA10 alternate function pin configuration register        */
  SDI10_PCFG = 0x0f,                    /*!< (@ 0x0000086F) SDI10 alternate function pin configuration register        */
	
}PortInput_CfgType;

typedef enum {
	
	PORTINPUT_CFG_GPIO = 0x00,
  PORTINPUT_CFG_P00 = 0x01,
  PORTINPUT_CFG_P01 = 0x02,
  PORTINPUT_CFG_P10 = 0x03,
  PORTINPUT_CFG_P11 = 0x04,
  PORTINPUT_CFG_P12 = 0x05,
  PORTINPUT_CFG_P13 = 0x06,
  PORTINPUT_CFG_P14 = 0x07,
  PORTINPUT_CFG_P15 = 0x08,
  PORTINPUT_CFG_P16 = 0x09,
  PORTINPUT_CFG_P17 = 0x0a,
  PORTINPUT_CFG_P20 = 0x0b,
  PORTINPUT_CFG_P21 = 0x0c,
  PORTINPUT_CFG_P22 = 0x0d,
  PORTINPUT_CFG_P23 = 0x0e,
  PORTINPUT_CFG_P24 = 0x0f,
  PORTINPUT_CFG_P25 = 0x10,
  PORTINPUT_CFG_P26 = 0x11,
  PORTINPUT_CFG_P27 = 0x12,
  PORTINPUT_CFG_P30 = 0x13,
  PORTINPUT_CFG_P31 = 0x14,
  PORTINPUT_CFG_P40 = 0x15,
  PORTINPUT_CFG_P41 = 0x16,
  PORTINPUT_CFG_P50 = 0x17,
  PORTINPUT_CFG_P51 = 0x18,
  PORTINPUT_CFG_P60 = 0x19,
  PORTINPUT_CFG_P61 = 0x1a,
  PORTINPUT_CFG_P62 = 0x1b,
  PORTINPUT_CFG_P63 = 0x1c,
  PORTINPUT_CFG_P70 = 0x1d,
  PORTINPUT_CFG_P71 = 0x1e,
  PORTINPUT_CFG_P72 = 0x1f,
  PORTINPUT_CFG_P73 = 0x20,
  PORTINPUT_CFG_P74 = 0x21,
  PORTINPUT_CFG_P75 = 0x22,
  PORTINPUT_CFG_P120 = 0x23,
  PORTINPUT_CFG_P121 = 0x24,
  PORTINPUT_CFG_P122 = 0x25,
  PORTINPUT_CFG_P123 = 0x26,
  PORTINPUT_CFG_P124 = 0x27,
  PORTINPUT_CFG_P130 = 0x28,
  PORTINPUT_CFG_P136 = 0x29,
  PORTINPUT_CFG_P137 = 0x2a,
  PORTINPUT_CFG_P140 = 0x2b,
  PORTINPUT_CFG_P146 = 0x2c,
  PORTINPUT_CFG_P147 = 0x2d,
	
}PortInput_CfgDef;

typedef enum {
	SPI_REMAP_NOPORT = 0,
	SPI_REMAP_GROUP1 = 1,//P50=>NSS P51=>SCK P17=>MISO P16=>MOSI 
	SPI_REMAP_GROUP2 = 2,//P63=>NSS P31=>SCK P75=>MISO P74=>MOSI 
	SPI_REMAP_GROUP3 = 3,//P25=>NSS P24=>SCK P23=>MISO P22=>MOSI 
	
}SPI_CfgDef;

#define PIN_MASK_0                 ((uint8_t)(0x01))  /*!< Pin 0 selected    */
#define PIN_MASK_1                 ((uint8_t)(0x02))  /*!< Pin 1 selected    */
#define PIN_MASK_2                 ((uint8_t)(0x04))  /*!< Pin 2 selected    */
#define PIN_MASK_3                 ((uint8_t)(0x08))  /*!< Pin 3 selected    */
#define PIN_MASK_4                 ((uint8_t)(0x10))  /*!< Pin 4 selected    */
#define PIN_MASK_5                 ((uint8_t)(0x20))  /*!< Pin 5 selected    */
#define PIN_MASK_6                 ((uint8_t)(0x40))  /*!< Pin 6 selected    */
#define PIN_MASK_7                 ((uint8_t)(0x80))  /*!< Pin 7 selected    */


/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void GPIO_Output_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Input_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_PullUp_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_PullUp_Disable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_PullDown_Enable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_PullDown_Disable(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Nch_OpenDrain(__IO uint8_t *port, uint8_t pinMsk);
void GPIO_Set_Value(__IO uint8_t *port, uint8_t value);
uint8_t GPIO_Get_Value(__IO uint8_t *port);


void PORT_Init(PORT_TypeDef PORTx,PIN_TypeDef PINx,PIN_ModeDef MODEx);
// void PORT_SetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
// void PORT_ClrBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
// void PORT_ToggleBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
// uint8_t PORT_GetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx);
void PORT_Output_Cfg(IO_CfgType PORT_CFGx, IO_CfgDef CFGx);
void PORT_Input_Cfg(PortInput_CfgType PORT_CFGx, PortInput_CfgDef CFGx);
void SPI_Cfg(SPI_CfgDef CFGx);

/*****************************************************************************
 ** \brief	 PORT_SetBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_SetBit(PORTx,PINx)  do{\
											*((uint8_t*)((uint8_t*)&PORT->PSET0+PORTx)) = (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_ClrBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_ClrBit(PORTx,PINx)  do{\
											*((uint8_t*)((uint8_t*)&PORT->PCLR0+PORTx)) = (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_ToggleBit
 **			 
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  none
 ** \note	 
*****************************************************************************/
#define   PORT_ToggleBit(PORTx,PINx)  do{\
											*((uint8_t*)((uint8_t*)&PORT->P0+PORTx)) ^= (1<<PINx);\
										   }while(0)
/*****************************************************************************
 ** \brief	 PORT_GetBit
 **	
 ** \param [in] PORTx : PORT_TypeDef
 **				PINx: PIN_TypeDef
 ** \return  PORT Bit
 ** \note	 
*****************************************************************************/
#define   PORT_GetBit(PORTx,PINx)  (*((uint8_t*)((uint8_t*)&PORT->P0+PORTx)) & (1<<PINx))


#endif
