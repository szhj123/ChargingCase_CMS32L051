/********************************************************
* @file       hal_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_lcd.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void Hal_Lcd_Spi_Init(void );
/* Private variables ------------------------------------*/
static Hal_Isr_Callback_t lcd_isr_callback = NULL;
static uint8_t lcdClrReqFlag;

void Hal_Lcd_Init(void )
{
    PORT_Init(PORT3, PIN1, OUTPUT);

    PORT_Init(PORT13, PIN6, OUTPUT);

    PORT_Init(PORT12, PIN0, OUTPUT);

    PORT_Init(PORT14, PIN7, OUTPUT);

    Hal_Lcd_Spi_Init();
    
    
}

static void Hal_Lcd_Spi_Init(void )
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

void Hal_Lcd_Spi_Send_With_DMA(const uint8_t *buf, uint16_t length, Hal_Isr_Callback_t callback )
{
    LCD_CS_LOW();

	LCD_RS_HIGH();

    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;

    SCI1->SCR10 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
    SCI1->SCR10 |= _8000_SCI_TRANSMISSION;

    /* write transfer data with DMA */
    DMAVEC->VEC[DMA_VECTOR_SPI20] = CTRL_DATA_SPI20;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_RPTINT_Pos) | 
                                          (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                          (0 << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMBLS = 1;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMACT = length-1;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMRLD = length-1;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMSAR = (uint32_t)&buf[1];
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMDAR = (uint32_t)&SCI1->SIO20;

    /* init DMA registers */
    CGC->PER1 |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR = DMAVEC_BASE;
    DMA_Enable(DMA_VECTOR_SPI20);
    
    /* clear INTSPI10 interrupt flag */
    INTC_ClearPendingIRQ(SPI20_IRQn);
    NVIC_ClearPendingIRQ(SPI20_IRQn);
    /* enable INTSPI10 interrupt */
    INTC_EnableIRQ(SPI20_IRQn);

    lcd_isr_callback = callback;

    lcdClrReqFlag = 1;

    SCI1->SIO20 = buf[0]; /* started by writing data to SDR[7:0] */
}

void Hal_Lcd_Spi_Send_One_Byte(uint8_t dat )
{
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;

    SCI1->SIO20 = dat; /* started by writing data to SDR[7:0] */
    while (SCI1->SSR10 & _0040_SCI_UNDER_EXECUTE)
    {
        ;
    }
}

void Hal_Lcd_Send_With_Loop(uint8_t *buf, uint16_t length )
{
    uint16_t i;

    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;
    
    for(i=0;i<length;i++)
    {
        SCI1->SIO20 = buf[i]; /* started by writing data to SDR[7:0] */
        while (SCI1->SSR10 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }
    }
}

void Hal_Lcd_Isr_Handler(void )
{
    if(lcdClrReqFlag)
    {
        lcdClrReqFlag = 0;
        
		LCD_CS_HIGH();
        
        if(lcd_isr_callback != NULL)
        {
            lcd_isr_callback();
        }
    }
}

