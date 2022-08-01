/********************************************************
* @file       hal_cms32l051.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_cms32l051.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/

void Cms32l051_Systick_Init(void )
{
    SystemCoreClockUpdate();

    SysTick_Config(SystemCoreClock / 1000);
}

void Cms32l051_Gpio_Init(void )
{
    PORT_Init(PORT3, PIN1, OUTPUT);

    PORT_Init(PORT13, PIN6, OUTPUT);

    PORT_Init(PORT12, PIN0, OUTPUT);

    PORT_Init(PORT14, PIN7, OUTPUT);
}

void Cms32l051_Uart0_Init(void )
{
    SystemCoreClockUpdate();

    UART0_Init(SystemCoreClock, 115200);

    INTC_EnableIRQ(SR0_IRQn);
}

void Cms32l051_Spi20_Init(void )
{
    uint8_t dap, ckp;

    spi_mode_t mode = SPI_MODE_0;
    
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI1->SIR10 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR10 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI1->SCR10 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
	SCI1->SDR10 = 0 << 9; 	// fMCK/(1+n)x2 = fMCK/2
    //SCI1->SDR10 = 1 << 9; 	// fMCK/(1+n)x2 = fMCK/4
    //SCI1->SDR10 = 2 << 9;		// fMCK/(1+n)x2 = fMCK/6
    //SCI1->SDR10 = 3 << 9;		// fMCK/(1+n)x2 = fMCK/8
	//SCI1->SDR10 = 7 << 9;		// fMCK/(1+n)x2 = fMCK/16
    //SCI1->SDR10 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI1->SO1 &= ~_0100_SCI_CH0_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI1->SO1 |= _0100_SCI_CH0_CLOCK_OUTPUT_1;
    }
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set SSn pin */
    SS20_PORT_SETTING();
    /* Set SCLK20 pin */
    SCLKO20_PORT_SETTING();
    /* Set SDO20 pin */
    SDO20_PORT_SETTING();
}


