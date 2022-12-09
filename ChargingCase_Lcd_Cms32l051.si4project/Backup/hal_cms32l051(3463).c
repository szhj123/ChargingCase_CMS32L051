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
    //SystemCoreClockUpdate();
    SystemCoreClock = 64000000;

    SysTick_Config(SystemCoreClock / 1000);
}

void Cms32l051_Gpio_Init(void )
{
    //p23, ldo vdd, output
    //p22, ctrl, output
    //p21, charging state, pull-up input
    //p20, en boost, output
    PORT_Init(PORT2, PIN2, OUTPUT);
    PORT_Init(PORT2, PIN1, PULLUP_INPUT);
    PORT_Init(PORT2, PIN0, OUTPUT);

    PORT_SetBit(PORT2, PIN2);
    PORT_SetBit(PORT2, PIN0);
    
    //p147, lcd background led, output
    //p137, sclk, input
    //p136, lcd rst, output
    //p120, lcd cs, output
    //p31,  lcd rs, output
    PORT_Init(PORT14, PIN7, OUTPUT);
    //PORT_Init(PORT13, PIN7, PULLUP_INPUT);
    PORT_Init(PORT13, PIN6, OUTPUT);
    PORT_Init(PORT12, PIN0, OUTPUT);
    PORT_Init(PORT3, PIN1, OUTPUT);

    //p50, hall detect, input
    //p40, swdio, input
    PORT_Init(PORT4, PIN0, PULLUP_INPUT);
    //p30, hall detect, input
    PORT_Init(PORT5, PIN0, INPUT);
    PORT_Init(PORT3, PIN0, INPUT);

    //p74, r_adc, adc
    //p73, l_adc, adc input
}

void Cms32l051_Intp_Init(void )
{
    //p30, intp2
    //p50, intp1, 
    INTP_Init(1 << 2, INTP_BOTH);
    INTP_Init(1 << 1, INTP_BOTH);

    INTP_Start(1<<2);
    INTP_Start(1<<1);
}

void Cms32l051_Tim40_Channel0_Interval_Init(void )
{
    //SystemCoreClockUpdate();
    
    SystemCoreClock = 64000000;
    
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _00F0_TM4_CKM1_fCLK_15 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40->TT0 |= TM4_CHANNEL_0;    
    /* clear interrupt flag */
    INTC_ClearPendingIRQ(TM00_IRQn);
    NVIC_ClearPendingIRQ(TM00_IRQn);
    /* Channel 0 is used as interval timer */
    TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                  _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
    TM40->TDR00 = (SystemCoreClock / 1000) - 1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* enable interrupt */
    INTC_EnableIRQ(TM00_IRQn);
        
    /* Start specify channel */
    TM40->TS0 |= TM4_CHANNEL_0;
}


void Cms32l051_Uart0_Init(void )
{
    //SystemCoreClockUpdate();
    
    SystemCoreClock = 64000000;

    UART0_Init(SystemCoreClock, 115200);

    INTC_EnableIRQ(SR0_IRQn);
}

void Cms32l051_Uart1_Init(void )
{
    //SystemCoreClockUpdate();
    
    SystemCoreClock = 64000000;
    
    UART1_Init(SystemCoreClock, 921600);
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
	//SCI1->SDR10 = 0 << 9; 	// fMCK/(1+n)x2 = fMCK/2
    SCI1->SDR10 = 1 << 9; 	// fMCK/(1+n)x2 = fMCK/4
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

void Cms32l051_Spi00_Init(void )
{
    uint8_t dap, ckp;
    spi_mode_t mode = SPI_MODE_0;
    
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI0->SPS0 &= ~SCI0_SPS0_PRS01_Msk;
    SCI0->SPS0 |= (0 << SCI0_SPS0_PRS01_Pos);
    SCI0->SIR00 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR00 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR00 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI0->SDR00 = 1 << 9;
    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI0->SO0 &= ~_0100_SCI_CH0_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI0->SO0 |= _0100_SCI_CH0_CLOCK_OUTPUT_1;
    }
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set SSn pin */
    SS00_PORT_SETTING();
    /* Set SCLK00 pin */
    SCLKO00_PORT_SETTING();
    /* Set SDI00 pin */
    SDI00_PORT_SETTING();
    /* Set SDO00 pin */
    SDO00_PORT_SETTING();
} 

void Cms32l051_Adc_Init(void )
{
    ADC_Init();

    ADC->ADM2 = _80_AD_POSITIVE_INVREFP | _00_AD_NEGATIVE_VSS | _00_AD_AREA_MODE_1 ;
}

