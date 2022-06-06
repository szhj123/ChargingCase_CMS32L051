/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    gpio.c
* @brief   This file implements device driver for GPIO module.
* @version 1.0.0  
* @date    2019/6/26
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "gpio.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/**
 * @brief Set specified GPIO as output function. 
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param pinMsk 
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_Output_Enable(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x060) &= ~pinMsk;  /*!< PMC=0: Digital Function   */
    *(port + 0x020) &= ~pinMsk;  /*!< PM =0: Output Function    */
}

/**
 * @brief Set specified GPIO as input function. 
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param pinMsk 
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_Input_Enable(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x060) &= ~pinMsk;  /*!< PMC=0: Digital Function   */
    *(port + 0x020) |=  pinMsk;  /*!< PM =1: Input Function     */
}

/**
 * @brief Enable pull up resister of input GPIO . 
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param pinMsk 
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_PullUp_Enable(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x060) &= ~pinMsk;  /*!< PMC=0: Digital Function   */
    *(port + 0x030) |=  pinMsk;  /*!< PU =1: Pull Up enable         */
}

/**
 * @brief Disable pull up resister of input GPIO . 
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param pinMsk 
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_PullUp_Disable(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x030) &=  ~pinMsk;  /*!< PU =0: Pull Up disable        */
}

/**
 * @brief Enable pull down resister of input GPIO . 
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param pinMsk 
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_PullDown_Enable(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x060) &= ~pinMsk;  /*!< PMC=0: Digital Function   */
    *(port + 0x040) |=  pinMsk;  /*!< PD =1: Pull Down enable         */
}

/**
 * @brief Disable pull down resister of input GPIO . 
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param pinMsk 
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_PullDown_Disable(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x040) &=  ~pinMsk;  /*!< PD =0: Pull Down disable        */
}

/**
 * @brief Nch Open Drain Output mode
 *
 * @param port address, such as &P0, &P1, &P3, &P5, &P7
 * @param pinMsk
 *             e.g., bit0: 0x01, bit1: 0x02, bit0~3: 0x0F, bit0~7: 0xFF
 */
void GPIO_Nch_OpenDrain(__IO uint8_t *port, uint8_t pinMsk)
{
    *(port + 0x050) |=  pinMsk;  /*!< POM =1: Nch OpenDrain Output */
}

/**
 * @brief Set specified value to GPIO output
 *
 * @param port port address, such as &P0, &P1, &P2...
 * @param value 
 */
void GPIO_Set_Value(__IO uint8_t *port, uint8_t value)
{
    *port = value;           /*!< PL = value */
}

/**
 * @brief Get value from GPIO input 
 *
 * @param port port address, such as &P0, &P1, &P2...
 *
 * @return 
 */
uint8_t GPIO_Get_Value(__IO uint8_t *port)
{
    PORT->PMS = 0x01;        /*!< Digital output level of the pin is read */        
    return (*port);          /*!< PL = value                              */
}

/**
  * @brief  Initializes the PORTx
  * @param  PORTx: where x can be 0~7, 12~14
  * @param  PINx: where x can be 0~7
  * @param  MODEx: such as INPUT,PULLUP_INPUT,TTL_INPUT,ANALOG_INPUT,OUTPUT,OPENDRAIN_OUTPUT,PULLDOWN_INPUT      
	*
  * @retval None
  */
void PORT_Init(PORT_TypeDef PORTx,PIN_TypeDef PINx,PIN_ModeDef MODEx)
{
  uint8_t mode = MODEx;
	uint8_t pos = 1<<PINx;
	
	switch(mode)
	{
		case INPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PM0+PORTx)) |= pos;
			//*((volatile uint8_t*)(&PORT->PIM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->POM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PU0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PD0+PORTx)) &= ~pos;
			break;
		case PULLUP_INPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PM0+PORTx)) |= pos;
			//*((volatile uint8_t*)(&PORT->PIM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->POM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PU0+PORTx)) |= pos;
			*((volatile uint8_t*)(&PORT->PD0+PORTx)) &= ~pos;
			break;
		case TTL_INPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PM0+PORTx)) |= pos;
			//*((volatile uint8_t*)(&PORT->PIM0+PORTx)) |= pos;
			*((volatile uint8_t*)(&PORT->POM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PU0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PD0+PORTx)) &= ~pos;
			break;
		case ANALOG_INPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) |= pos;
			break;
		case OUTPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PM0+PORTx)) &= ~pos;
			//*((volatile uint8_t*)(&PORT->PIM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->POM0+PORTx)) &= ~pos;
			break;
		case OPENDRAIN_OUTPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PM0+PORTx)) &= ~pos;
			//*((volatile uint8_t*)(&PORT->PIM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->POM0+PORTx)) |= pos;
			break;
		case PULLDOWN_INPUT:
			*((volatile uint8_t*)(&PORT->PMC0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PM0+PORTx)) |= pos;
			//*((volatile uint8_t*)(&PORT->PIM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->POM0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PU0+PORTx)) &= ~pos;
			*((volatile uint8_t*)(&PORT->PD0+PORTx)) |= pos;
			break;	
	}
	
}


// /**
//   * @brief  Set the PORTx bit
//   * @param  PORTx: where x can be 0~7, 12~14
//   * @param  PINx: where x can be 0~7    
// 	*
//   * @retval None
//   */
// void PORT_SetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
// {
// 	uint8_t pos = 1<<PINx;
// 	*((volatile uint8_t*)(&PORT->PSET0+PORTx)) = pos;
// }

// /**
//   * @brief  Clear the PORTx bit
//   * @param  PORTx: where x can be 0~7, 12~14
//   * @param  PINx: where x can be 0~7    
// 	*
//   * @retval None
//   */
// void PORT_ClrBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
// {
// 	uint8_t pos = 1<<PINx;
// 	*((volatile uint8_t*)(&PORT->PCLR0+PORTx)) = pos;
// }

// /**
//   * @brief  Toggle the PORTx bit
//   * @param  PORTx: where x can be 0~7, 12~14
//   * @param  PINx: where x can be 0~7    
// 	*
//   * @retval None
//   */
// void PORT_ToggleBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
// {
// 	uint8_t pos = 1<<PINx;
// 	*((volatile uint8_t*)(&PORT->P0+PORTx)) ^= pos;
// }

// /**
//   * @brief  Get the PORTx bit
//   * @param  PORTx: where x can be 0~7, 12~14
//   * @param  PINx: where x can be 0~7    
// 	*
//   * @retval None
//   */
// uint8_t PORT_GetBit(PORT_TypeDef PORTx,PIN_TypeDef PINx)
// {
// 	uint8_t pos = 1<<PINx;
// 	PORT->PMS = 0x01;        /*!< Digital output level of the pin is read */
// 	return *((volatile uint8_t*)(&PORT->P0+PORTx))&pos;
// }


/**
  * @brief  Config the PORTx remap output peripheral function
  * @param  PORT_CFGx: such as P00_CFG ...
  * @param  CFGx: such as IOCFG_INTP0 ...
  *
  * @retval None
  */
void PORT_Output_Cfg(IO_CfgType PORT_CFGx, IO_CfgDef CFGx)
{
	*((volatile uint8_t*)(&PORT->P00CFG+PORT_CFGx)) = CFGx;
}

/**
  * @brief  Config the PORTx remap input peripheral function
  * @param  PORT_CFGx: such as PORTINPUT_CFG_GPIO ...
  * @param  CFGx: such as PORTINPUT_CFG_P00 ...
  *
  * @retval None
  */
void PORT_Input_Cfg(PortInput_CfgType PORT_CFGx, PortInput_CfgDef CFGx)
{
	*((volatile uint8_t*)(&PORT->TI10PCFG+PORT_CFGx)) = CFGx;
}

/**
  * @brief  Config the PORTx remap SPI peripheral function
  * @param  PORT_CFGx: such as PORTINPUT_CFG_GPIO ...
  * @param  CFGx: such as PORTINPUT_CFG_P00 ...
  *
  * @retval None
  */
void SPI_Cfg(SPI_CfgDef CFGx)
{
	PORT->SPIPCFG = CFGx;
}
