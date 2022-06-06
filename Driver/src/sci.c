/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    sci.c
* @brief   This file implements device driver for SCI module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "stdlib.h"
#include "CMS32L051.h"
#include "userdefine.h"
#include "sci.h"
#include "dma.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
const uint16_t sps_tbl[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
volatile uint8_t *gp_uart0_tx_address;       /* uart0 transmit buffer address */
volatile uint16_t g_uart0_tx_count;          /* uart0 transmit data number */
volatile uint8_t *gp_uart0_rx_address;       /* uart0 receive buffer address */
volatile uint16_t g_uart0_rx_count;          /* uart0 receive data number */
volatile uint16_t g_uart0_rx_length;         /* uart0 receive data length */
volatile uint8_t *gp_spi00_rx_address;       /* spi00 receive buffer address */
volatile uint16_t g_spi00_rx_length;         /* spi00 receive data length */
volatile uint16_t g_spi00_rx_count;          /* spi00 receive data count */
volatile uint8_t *gp_spi00_tx_address;       /* spi00 send buffer address */
volatile uint16_t g_spi00_tx_length;         /* spi00 send data length */
volatile uint16_t g_spi00_tx_count;          /* spi00 send data count */
volatile uint8_t *gp_spi01_rx_address;       /* spi01 receive buffer address */
volatile uint16_t g_spi01_rx_length;         /* spi01 receive data length */
volatile uint16_t g_spi01_rx_count;          /* spi01 receive data count */
volatile uint8_t *gp_spi01_tx_address;       /* spi01 send buffer address */
volatile uint16_t g_spi01_tx_length;         /* spi01 send data length */
volatile uint16_t g_spi01_tx_count;          /* spi01 send data count */
volatile uint8_t g_iic00_master_status_flag; /* iic00 start flag for send address check by master mode */
volatile uint8_t *gp_iic00_tx_address;       /* iic00 send data pointer by master mode */
volatile uint16_t g_iic00_tx_count;          /* iic00 send data size by master mode */
volatile uint8_t *gp_iic00_rx_address;       /* iic00 receive data pointer by master mode */
volatile uint16_t g_iic00_rx_count;          /* iic00 receive data size by master mode */
volatile uint16_t g_iic00_rx_length;         /* iic00 receive data length by master mode */
volatile uint8_t g_iic01_master_status_flag; /* iic01 start flag for send address check by master mode */
volatile uint8_t *gp_iic01_tx_address;       /* iic01 send data pointer by master mode */
volatile uint16_t g_iic01_tx_count;          /* iic01 send data size by master mode */
volatile uint8_t *gp_iic01_rx_address;       /* iic01 receive data pointer by master mode */
volatile uint16_t g_iic01_rx_count;          /* iic01 receive data size by master mode */
volatile uint16_t g_iic01_rx_length;         /* iic01 receive data length by master mode */
volatile uint8_t *gp_uart1_tx_address;       /* uart1 transmit buffer address */
volatile uint16_t g_uart1_tx_count;          /* uart1 transmit data number */
volatile uint8_t *gp_uart1_rx_address;       /* uart1 receive buffer address */
volatile uint16_t g_uart1_rx_count;          /* uart1 receive data number */
volatile uint16_t g_uart1_rx_length;         /* uart1 receive data length */
volatile uint8_t *gp_spi10_rx_address;       /* spi10 receive buffer address */
volatile uint16_t g_spi10_rx_length;         /* spi10 receive data length */
volatile uint16_t g_spi10_rx_count;          /* spi10 receive data count */
volatile uint8_t *gp_spi10_tx_address;       /* spi10 send buffer address */
volatile uint16_t g_spi10_tx_length;         /* spi10 send data length */
volatile uint16_t g_spi10_tx_count;          /* spi10 send data count */
volatile uint8_t *gp_spi11_rx_address;       /* spi11 receive buffer address */
volatile uint16_t g_spi11_rx_length;         /* spi11 receive data length */
volatile uint16_t g_spi11_rx_count;          /* spi11 receive data count */
volatile uint8_t *gp_spi11_tx_address;       /* spi11 send buffer address */
volatile uint16_t g_spi11_tx_length;         /* spi11 send data length */
volatile uint16_t g_spi11_tx_count;          /* spi11 send data count */
volatile uint8_t g_iic10_master_status_flag; /* iic10 start flag for send address check by master mode */
volatile uint8_t *gp_iic10_tx_address;       /* iic10 send data pointer by master mode */
volatile uint16_t g_iic10_tx_count;          /* iic10 send data size by master mode */
volatile uint8_t *gp_iic10_rx_address;       /* iic10 receive data pointer by master mode */
volatile uint16_t g_iic10_rx_count;          /* iic10 receive data size by master mode */
volatile uint16_t g_iic10_rx_length;         /* iic10 receive data length by master mode */
volatile uint8_t g_iic11_master_status_flag; /* iic11 start flag for send address check by master mode */
volatile uint8_t *gp_iic11_tx_address;       /* iic11 send data pointer by master mode */
volatile uint16_t g_iic11_tx_count;          /* iic11 send data size by master mode */
volatile uint8_t *gp_iic11_rx_address;       /* iic11 receive data pointer by master mode */
volatile uint16_t g_iic11_rx_count;          /* iic11 receive data size by master mode */
volatile uint16_t g_iic11_rx_length;         /* iic11 receive data length by master mode */
volatile uint8_t *gp_uart2_tx_address;       /* uart2 transmit buffer address */
volatile uint16_t g_uart2_tx_count;          /* uart2 transmit data number */
volatile uint8_t *gp_uart2_rx_address;       /* uart2 receive buffer address */
volatile uint16_t g_uart2_rx_count;          /* uart2 receive data number */
volatile uint16_t g_uart2_rx_length;         /* uart2 receive data length */
volatile uint8_t *gp_spi20_rx_address;       /* spi20 receive buffer address */
volatile uint16_t g_spi20_rx_length;         /* spi20 receive data length */
volatile uint16_t g_spi20_rx_count;          /* spi20 receive data count */
volatile uint8_t *gp_spi20_tx_address;       /* spi20 send buffer address */
volatile uint16_t g_spi20_tx_length;         /* spi20 send data length */
volatile uint16_t g_spi20_tx_count;          /* spi20 send data count */
volatile uint8_t *gp_spi21_rx_address;       /* spi21 receive buffer address */
volatile uint16_t g_spi21_rx_length;         /* spi21 receive data length */
volatile uint16_t g_spi21_rx_count;          /* spi21 receive data count */
volatile uint8_t *gp_spi21_tx_address;       /* spi21 send buffer address */
volatile uint16_t g_spi21_tx_length;         /* spi21 send data length */
volatile uint16_t g_spi21_tx_count;          /* spi21 send data count */
volatile uint8_t g_iic20_master_status_flag; /* iic20 start flag for send address check by master mode */
volatile uint8_t *gp_iic20_tx_address;       /* iic20 send data pointer by master mode */
volatile uint16_t g_iic20_tx_count;          /* iic20 send data size by master mode */
volatile uint8_t *gp_iic20_rx_address;       /* iic20 receive data pointer by master mode */
volatile uint16_t g_iic20_rx_count;          /* iic20 receive data size by master mode */
volatile uint16_t g_iic20_rx_length;         /* iic20 receive data length by master mode */
volatile uint8_t g_iic21_master_status_flag; /* iic21 start flag for send address check by master mode */
volatile uint8_t *gp_iic21_tx_address;       /* iic21 send data pointer by master mode */
volatile uint16_t g_iic21_tx_count;          /* iic21 send data size by master mode */
volatile uint8_t *gp_iic21_rx_address;       /* iic21 receive data pointer by master mode */
volatile uint16_t g_iic21_rx_count;          /* iic21 receive data size by master mode */
volatile uint16_t g_iic21_rx_length;         /* iic21 receive data length by master mode */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: UART0_Init
* @brief  This function initializes the UART0 module.
*         Date Length: 8 bit; Parity: none; Stop: 1 bit              
* @param  freq - the frequency of fCLK
* @param  baud - the expected baud rate
* @return MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART0_Init(uint32_t freq, uint32_t baud)
{
    MD_STATUS status;

    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->SPS0 = (0 << SCI0_SPS0_PRS00_Pos) | (3 << SCI0_SPS0_PRS00_Pos);
    /* transmission channel */
    SCI0->SMR00 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI0->SCR00 = _0004_SCRMN_DEFAULT_VALUE | _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR00 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _01_SCI_RXD0_FILTER_ON;
    SCI0->SIR01 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR01 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI0->SCR01 = _0004_SCRMN_DEFAULT_VALUE | _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR01 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* output enable */
    SCI0->SO0 |= _0001_SCI_CH0_DATA_OUTPUT_1;
    SCI0->SOL0 &= (uint16_t)~_0001_SCI_CHANNEL0_INVERTED;
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set TxD0 pin */
    TXD0_PORT_SETTING();
    /* Set RxD0 pin */
    RXD0_PORT_SETTING();
    /* UART0 Start, Setting baud rate */
    status = UART0_BaudRate(freq, baud);
    return (status);
}

/***********************************************************************************************************************
* Function Name: UART_BaudRateCal
* @brief  This function search the setting value for specified freq and baud of UART
* @param  fclk_freq
*             - the frequency of fCLK clock. unit Hz.
* @param  baud
*             - the target baud rate, unit bps.
* @param  pvalue
*             - the pointer of calculated result
* @return MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART_BaudRateCal(uint32_t fclk_freq, uint32_t baud, uart_baud_t *pvalue)
{
    MD_STATUS status = MD_ERROR;

    int32_t baud_err;
    uint32_t baud_cal;
    uint32_t fmck_freq;
    unsigned char i, j;

    for (i = 0; i < 16; i++)
    {
        fmck_freq = fclk_freq / sps_tbl[i];
        for (j = 2; j < 128; j++)
        {
            baud_cal = fmck_freq / (j + 1) / 2;
            baud_err = 10000 * baud_cal / baud - 10000;  /* n ten thousandths */
            if (abs(baud_err) < 20)  /* 0.2% */
            {
                pvalue->prs = i;
                pvalue->sdr = j;
                //printf("fclk_freq = %10dHz, baud = %6dbps, prs = %2d, sdr = %3d, errors = %3d\n", fclk_freq, baud, pvalue->prs, pvalue->sdr, baud_err);
                status = MD_OK;
                return (status);
            }
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART0_BaudRate
* @brief  This function sets the baud rate of UART0.
* @param  fclk_freq
*             - the frequency of fCLK clock. unit Hz.
* @param  baud
*             - the target baud rate, unit bps.
* @return None
***********************************************************************************************************************/
MD_STATUS UART0_BaudRate(uint32_t fclk_freq, uint32_t baud)
{
    MD_STATUS status;
    uart_baud_t pvalue;

#ifndef RTL_SIMULATION
    status = UART_BaudRateCal(fclk_freq, baud, &pvalue);
#else
    pvalue.prs = 0x04;
    pvalue.sdr = 0x67;
    status = MD_OK;
#endif

    if (status == MD_OK)
    {
        SCI0->ST0 = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
        SCI0->SPS0 &= ~SCI0_SPS0_PRS00_Msk;
        SCI0->SPS0 |= pvalue.prs;
        SCI0->SDR00 = pvalue.sdr << 9;
        SCI0->SDR01 = pvalue.sdr << 9;
        SCI0->SS0 |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART0_Send
* @brief  This function sends UART0 data.
* @param  ch - transfer char
* @return None
***********************************************************************************************************************/
void UART0_Send(uint8_t ch)
{
    SCI0->TXD0 = ch;
    while (SCI0->SSR00 & (_0040_SCI_UNDER_EXECUTE | _0020_SCI_VALID_STORED))
    {
        ;
    }
    return;
}

/***********************************************************************************************************************
* Function Name: UART0_Receive
* @brief  This function receives UART0 data.
* @param  None
* @return char
***********************************************************************************************************************/
char UART0_Receive()
{
    while ((SCI0->SSR01 & _0020_SCI_VALID_STORED) == 0)
    {
        ;
    }
    return SCI0->RXD0;
}
/***********************************************************************************************************************
* Function Name: SPI00_MasterInit
* @brief  This function initializes the SPI00 module as Master.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI00_MasterInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
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
    SCI0->SDR00 = _CE00_SCI_BAUDRATE_DIVISOR;
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
/***********************************************************************************************************************
* Function Name: SPI00_Start
* @brief  This function starts the SPI00 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI00_Start(void)
{
    /* SSn Active */
    SS00_PORT_CLR();
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
    /* clear INTSPI00 interrupt flag */
    INTC_ClearPendingIRQ(SPI00_IRQn);
    NVIC_ClearPendingIRQ(SPI00_IRQn);
    /* enable INTSPI00 interrupt */
    INTC_EnableIRQ(SPI00_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI00_Stop
* @brief  This function stops the SPI00 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI00_Stop(void)
{
    /* disable INTSPI00 interrupt */
    INTC_DisableIRQ(SPI00_IRQn);
    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
    /* clear INTSPI00 interrupt flag */
    INTC_ClearPendingIRQ(SPI00_IRQn);
    /* SSn Inactive */
    SS00_PORT_SET();
}
/***********************************************************************************************************************
* Function Name: SPI00_MasterSendReceive
* @brief  This function sends and receives SPI00 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI00_MasterSendReceive(uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR00 |= _C000_SCI_RECEPTION_TRANSMISSION;

#ifdef SPI00_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)&SCI0->SIO00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)rx_buf;

        /* write transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMSAR = (uint32_t)tx_buf + 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMDAR = (uint32_t)&SCI0->SIO00;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);
#endif
#ifdef SPI00_WITH_DMA
        g_spi00_rx_count = 1;                      /* receive data count */
        g_spi00_tx_count = 1;                      /* send data count */
        gp_spi00_tx_address = tx_buf;              /* send buffer pointer */
        gp_spi00_rx_address = rx_buf + tx_num - 1; /* receive buffer pointer */
#else
        g_spi00_rx_count = tx_num;    /* receive data count */
        g_spi00_tx_count = tx_num;    /* send data count */
        gp_spi00_tx_address = tx_buf; /* send buffer pointer */
        gp_spi00_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI00_Start();
        SCI0->SIO00 = *gp_spi00_tx_address; /* started by writing data to SDR[7:0] */
        gp_spi00_tx_address++;
        g_spi00_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_MasterSend
* @brief  This function sends SPI10 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI00_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR00 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR00 |= _8000_SCI_TRANSMISSION;

#ifdef SPI00_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)&SCI0->SIO00;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);
#endif
#ifdef SPI00_WITH_DMA
        g_spi00_tx_count = 1;         /* send data count */
        gp_spi00_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi00_tx_count = tx_num;    /* send data count */
        gp_spi00_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI00_Start();
        SCI0->SIO00 = *gp_spi00_tx_address; /* started by writing data to SDR[7:0] */
        gp_spi00_tx_address++;
        g_spi00_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_MasterReceive
* @brief  This function receives SPI00 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI00_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio00 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR00 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR00 |= _4000_SCI_RECEPTION;

#ifdef SPI00_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)&SCI0->SIO00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)rx_buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMSAR = (uint32_t)&dummy_sio00;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMDAR = (uint32_t)&SCI0->SIO00;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);
#endif
#ifdef SPI00_WITH_DMA
        g_spi00_rx_count = 1;                      /* receive data count */
        gp_spi00_rx_address = rx_buf + rx_num - 1; /* receive buffer pointer */
#else
        g_spi00_rx_count = rx_num;    /* receive data count */
        gp_spi00_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI00_Start();
        SCI0->SIO00 = dummy_sio00;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI00_SlaveInit
* @brief  This function initializes the SPI00 module. Slave transmission/reception operation.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI00_SlaveInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI0->SIR00 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR00 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR00 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI0->SDR00 = 0x0000;
    /* Set output enable */
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set SS00 pin */
    SS00_PORT_SETTING();
    /* SS00 chip selection enable */
    MISC->ISC |= MISC_ISC_SSIE00_Msk;
    /* Set SCLK00 pin */
    SCLKI00_PORT_SETTING();
    /* Set SDI00 pin */
    SDI00_PORT_SETTING();
    /* Set SDO00 pin */
    SDO00_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI00_SlaveSend
* @brief  This function sends SPI00 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI00_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR00 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR00 |= _8000_SCI_TRANSMISSION;

#ifdef SPI00_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)&SCI0->SIO00;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);
#endif
#ifdef SPI00_WITH_DMA
        g_spi00_tx_count = 1;         /* send data count */
#else
        g_spi00_tx_count = tx_num;    /* send data count */
#endif
        gp_spi00_tx_address = tx_buf; /* send buffer pointer */

        SPI00_Start();
        gp_spi00_tx_address++;
        g_spi00_tx_count--;
        SCI0->SIO00 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI00_SlaveReceive
* @brief  This function receives SPI00 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI00_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio00 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR00 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR00 |= _4000_SCI_RECEPTION;

#ifdef SPI00_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)&SCI0->SIO00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);
#endif

#ifdef SPI00_WITH_DMA
        g_spi00_rx_count = 0; /* receive data count */
#else
        g_spi00_rx_count = rx_num;    /* receive data count */
#endif
        gp_spi00_rx_address = rx_buf; /* receive buffer pointer */

        SPI00_Start();
        SCI0->SIO00 = dummy_sio00;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI01_MasterInit
* @brief  This function initializes the SPI01 module.
*         Master transmission/reception operation 
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI01_MasterInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI0->SPS0 &= ~SCI0_SPS0_PRS01_Msk;
    SCI0->SPS0 |= (0 << SCI0_SPS0_PRS01_Pos);
    SCI0->SIR01 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR01 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR01 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI0->SDR01 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI0->SO0 &= ~_0200_SCI_CH1_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI0->SO0 |= _0200_SCI_CH1_CLOCK_OUTPUT_1;
    }
    SCI0->SOE0 |= _0002_SCI_CH1_OUTPUT_ENABLE;

    /* Set SSn pin */
    SS01_PORT_SETTING();
    /* Set SCLK01 pin */
    SCLKO01_PORT_SETTING();
    /* Set SDI01 pin */
    SDI01_PORT_SETTING();
    /* Set SDO01 pin */
    SDO01_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI01_MasterSend
* @brief  This function sends SPI01 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI01_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR01 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR01 |= _8000_SCI_TRANSMISSION;

#ifdef SPI01_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI01] = CTRL_DATA_SPI01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMDAR = (uint32_t)&SCI0->SIO01;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI01 % 8);
#endif
#ifdef SPI01_WITH_DMA
        g_spi01_tx_count = 1;         /* send data count */
        gp_spi01_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi01_tx_count = tx_num;    /* send data count */
        gp_spi01_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI01_Start();
        gp_spi01_tx_address++;
        g_spi01_tx_count--;
        SCI0->SIO01 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI01_MasterReceive
* @brief  This function receives SPI01 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI01_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio01 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR01 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR01 |= _4000_SCI_RECEPTION;

#ifdef SPI01_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI01] = CTRL_DATA_SPI01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMSAR = (uint32_t)&SCI0->SIO01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMDAR = (uint32_t)rx_buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMSAR = (uint32_t)&dummy_sio01;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMDAR = (uint32_t)&SCI0->SIO01;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI01 % 8);
#endif
#ifdef SPI01_WITH_DMA
        g_spi01_rx_count = 1;                  /* receive data count */
        gp_spi01_rx_address = rx_buf + rx_num - 1; /* receive buffer pointer */
#else
        g_spi01_rx_count = rx_num;    /* receive data count */
        gp_spi01_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI01_Start();
        SCI0->SIO01 = dummy_sio01;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI01_SlaveInit
* @brief  This function initializes the SPI01 module.
*         Slave transmission/reception operation. 
* @param  mode
*               - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*               - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*               - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*               - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI01_SlaveInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI0->SIR01 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR01 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR01 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI0->SDR01 = 0x0000;
    NVIC_SetPriority(SPI01_IRQn, 0); /* Set higher priority to execute slave ISR firstly */
    /* Set output enable */
    SCI0->SOE0 |= _0002_SCI_CH1_OUTPUT_ENABLE;

    SCLKI01_PORT_SETTING();
    SDI01_PORT_SETTING();
    SDO01_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI01_Start
* @brief  This function starts the SPI01 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI01_Start(void)
{
    /* SSn Active */
    SS01_PORT_CLR();
    SCI0->SOE0 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    SCI0->SS0 |= _0002_SCI_CH1_START_TRG_ON;
    /* clear INTSPI01 interrupt flag */
    INTC_ClearPendingIRQ(SPI01_IRQn);
    NVIC_ClearPendingIRQ(SPI01_IRQn);
    /* enable INTSPI01 interrupt */
    INTC_EnableIRQ(SPI01_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI01_Stop
* @brief  This function stops the SPI01 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI01_Stop(void)
{
    /* disable INTSPI01 interrupt */
    INTC_DisableIRQ(SPI01_IRQn);
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0008_SCI_CH3_OUTPUT_ENABLE;
    /* clear INTSPI01 interrupt flag */
    INTC_ClearPendingIRQ(SPI01_IRQn);
    NVIC_ClearPendingIRQ(SPI01_IRQn);
    /* SSn Inactive */
    SS01_PORT_SET();
}
/***********************************************************************************************************************
* Function Name: SPI01_SlaveSendReceive
* @brief  This function sends and receives SPI01 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI01_SlaveSendReceive(uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR01 |= _C000_SCI_RECEPTION_TRANSMISSION;

#ifdef SPI01_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI01] = CTRL_DATA_SPI01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACT = tx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMRLD = tx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMSAR = (uint32_t)&SCI0->SIO01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMDAR = (uint32_t)rx_buf;

        /* write transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMSAR = (uint32_t)tx_buf + 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMDAR = (uint32_t)&SCI0->SIO01;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI01 % 8);
#endif
#ifdef SPI01_WITH_DMA
        g_spi01_rx_count = 0;                      /* receive data count */
        g_spi01_tx_count = 1;                      /* send data count */
        gp_spi01_tx_address = tx_buf;              /* send buffer pointer */
        gp_spi01_rx_address = rx_buf + tx_num; /* receive buffer pointer */
#else
        g_spi01_rx_count = tx_num;    /* receive data count */
        g_spi01_tx_count = tx_num;    /* send data count */
        gp_spi01_tx_address = tx_buf; /* send buffer pointer */
        gp_spi01_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI01_Start();
        gp_spi01_tx_address++;
        g_spi01_tx_count--;
        SCI0->SIO01 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI01_SlaveSend
* @brief  This function sends SPI01 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI01_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR01 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR01 |= _8000_SCI_TRANSMISSION;

#ifdef SPI01_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI01] = CTRL_DATA_SPI01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMDAR = (uint32_t)&SCI0->SIO01;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI01 % 8);
#endif
#ifdef SPI01_WITH_DMA
        g_spi01_tx_count = 1;         /* send data count */
#else
        g_spi01_tx_count = tx_num;    /* send data count */
#endif
        gp_spi01_tx_address = tx_buf; /* send buffer pointer */

        SPI01_Start();
        gp_spi01_tx_address++;
        g_spi01_tx_count--;
        SCI0->SIO01 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI01_SlaveReceive
* @brief  This function receives SPI01 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI01_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio01 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR01 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR01 |= _4000_SCI_RECEPTION;

#ifdef SPI01_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI01] = CTRL_DATA_SPI01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMSAR = (uint32_t)&SCI0->SIO01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI01 % 8);
#endif

#ifdef SPI01_WITH_DMA
        g_spi01_rx_count = 0; /* receive data count */
#else
        g_spi01_rx_count = rx_num;    /* receive data count */
#endif
        gp_spi01_rx_address = rx_buf; /* receive buffer pointer */

        SPI01_Start();
        SCI0->SIO01 = dummy_sio01;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: IIC00_Init
* @brief  This function initializes the IIC00 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC00_Init(void)
{
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    //SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | _0001_SCI_CK00_fCLK_1;
    SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | _0004_SCI_CK00_fCLK_4;

    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;

    SCI0->SIR00 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR00 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
    SCI0->SCR00 = _0004_SCRMN_DEFAULT_VALUE | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                  _0000_SCI_MSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR00 = _3000_SCI_BAUDRATE_DIVISOR;
    SCI0->SO0 |= _0100_SCI_CH0_CLOCK_OUTPUT_1 | _0001_SCI_CH0_DATA_OUTPUT_1;
    /* Set SCL00 pin */
    SCL00_PORT_SETTING();
    /* Set SDA00 pin */
    SDA00_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IIC00_MasterSend
* @brief  This function starts transferring data for IIC00 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC00_MasterSend(uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    g_iic00_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC00 master status flag */
    adr &= 0xFEU;                                         /* send mode */
    g_iic00_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
    SCI0->SCR00 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR00 |= _8000_SCI_TRANSMISSION;
    /* Set paramater */
    g_iic00_tx_count = tx_num;
    gp_iic00_tx_address = tx_buf;
    /* Start condition */
    IIC00_StartCondition();
    INTC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
    NVIC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
    INTC_EnableIRQ(IIC00_IRQn);       /* enable INTIIC00 interrupt flag */
    NVIC_SetPriority(IIC00_IRQn, 3);  /* low priority */
    SCI0->SIO00 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC00_MasterReceive
* @brief  This function starts receiving data for IIC00 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC00_MasterReceive(uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    g_iic00_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
    adr |= 0x01U;                                          /* receive mode */
    g_iic00_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
    SCI0->SCR00 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR00 |= _8000_SCI_TRANSMISSION;
    /* Set parameter */
    g_iic00_rx_length = rx_num;
    g_iic00_rx_count = 0U;
    gp_iic00_rx_address = rx_buf;
    /* Start condition */
    IIC00_StartCondition();
    INTC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
    NVIC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
    INTC_EnableIRQ(IIC00_IRQn);       /* enable INTIIC00 interrupt flag */
    NVIC_SetPriority(IIC00_IRQn, 3);  /* low priority */
    SCI0->SIO00 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC00_Stop
* @brief  This function stops the IIC00 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC00_Stop(void)
{
    INTC_DisableIRQ(IIC00_IRQn); /* disable INTIIC00 interrupt flag */
    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
    INTC_ClearPendingIRQ(IIC00_IRQn); /* clear INTIIC00 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: IIC00_StartCondition
* @brief  This function starts IIC00 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC00_StartCondition(void)
{
    volatile uint8_t w_count;

    SCI0->SO0 &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 &= (uint16_t) ~(_0100_SCI_CH0_CLOCK_OUTPUT_1);
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: IIC00_StopCondition
* @brief  This function stops IIC00 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC00_StopCondition(void)
{
    volatile uint8_t w_count;

    g_iic00_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC00 master status flag */
    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
    SCI0->SO0 &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);
    SCI0->SO0 |= _0100_SCI_CH0_CLOCK_OUTPUT_1;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 |= _0001_SCI_CH0_DATA_OUTPUT_1;
}

/***********************************************************************************************************************
* Function Name: IIC01_Init
* @brief  This function initializes the IIC01 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC01_Init(void)
{
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | _0001_SCI_CK00_fCLK_1;

    SCI0->ST0 |= _0002_SCI_CH1_STOP_TRG_ON;

    SCI0->SIR01 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR01 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
    SCI0->SCR01 = _0004_SCRMN_DEFAULT_VALUE | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                  _0000_SCI_MSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR01 = _CE00_SCI_BAUDRATE_DIVISOR;
    SCI0->SO0 |= _0200_SCI_CH1_CLOCK_OUTPUT_1 | _0002_SCI_CH1_DATA_OUTPUT_1;
    /* Set SCL01 pin */
    SCL01_PORT_SETTING();
    /* Set SDA01 pin */
    SDA01_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IIC01_MasterSend
* @brief  This function starts transferring data for IIC01 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC01_MasterSend(uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    g_iic01_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC01 master status flag */
    adr &= 0xFEU;                                         /* send mode */
    g_iic01_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
    SCI0->SCR01 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR01 |= _8000_SCI_TRANSMISSION;
    /* Set paramater */
    g_iic01_tx_count = tx_num;
    gp_iic01_tx_address = tx_buf;
    /* Start condition */
    IIC01_StartCondition();
    INTC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
    NVIC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
    INTC_EnableIRQ(IIC01_IRQn);       /* enable INTIIC01 interrupt flag */
    SCI0->SIO01 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC01_MasterReceive
* @brief  This function starts receiving data for IIC01 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC01_MasterReceive(uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    g_iic01_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
    adr |= 0x01U;                                          /* receive mode */
    g_iic01_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
    SCI0->SCR01 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR01 |= _8000_SCI_TRANSMISSION;
    /* Set parameter */
    g_iic01_rx_length = rx_num;
    g_iic01_rx_count = 0U;
    gp_iic01_rx_address = rx_buf;
    /* Start condition */
    IIC01_StartCondition();
    INTC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
    NVIC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
    INTC_EnableIRQ(IIC01_IRQn);       /* enable INTIIC01 interrupt flag */
    SCI0->SIO01 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC01_Stop
* @brief  This function stops the IIC01 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC01_Stop(void)
{
    INTC_DisableIRQ(IIC01_IRQn); /* disable INTIIC01 interrupt flag */
    SCI0->ST0 |= _0002_SCI_CH1_STOP_TRG_ON;
    INTC_ClearPendingIRQ(IIC01_IRQn); /* clear INTIIC01 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: IIC01_StartCondition
* @brief  This function starts IIC01 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC01_StartCondition(void)
{
    volatile uint8_t w_count;

    SCI0->SO0 &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 &= (uint16_t) ~(_0200_SCI_CH1_CLOCK_OUTPUT_1);
    SCI0->SOE0 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    SCI0->SS0 |= _0002_SCI_CH1_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: IIC01_StopCondition
* @brief  This function stops IIC01 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC01_StopCondition(void)
{
    volatile uint8_t w_count;

    SCI0->ST0 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
    SCI0->SO0 &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);
    SCI0->SO0 |= _0200_SCI_CH1_CLOCK_OUTPUT_1;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 |= _0002_SCI_CH1_DATA_OUTPUT_1;
}

/***********************************************************************************************************************
* Function Name: UART1_Init
* @brief  This function initializes the UART1 module.
*         Date Length: 8 bit; Parity: none; Stop: 1 bit              
* @param  freq - the frequency of fCLK
* @param  baud - the expected baud rate
* @return status - MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART1_Init(uint32_t freq, uint32_t baud)
{
    MD_STATUS status;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON | _0004_SCI_CH2_STOP_TRG_ON;
    INTC_DisableIRQ(ST1_IRQn);       /* disable INTST1 interrupt */
    INTC_DisableIRQ(SR1_IRQn);       /* disable INTSR1 interrupt */
    INTC_DisableIRQ(SRE1_IRQn);      /* disable INTSRE1 interrupt */
    INTC_ClearPendingIRQ(ST1_IRQn);  /* clear INTST1 interrupt flag */
    INTC_ClearPendingIRQ(SR1_IRQn);  /* clear INTSR1 interrupt flag */
    INTC_ClearPendingIRQ(SRE1_IRQn); /* clear INTSRE1 interrupt flag */

    /* transmission channel */
    SCI0->SMR02 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI0->SCR02 = _0004_SCRMN_DEFAULT_VALUE | _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR02 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _04_SCI_RXD1_FILTER_ON;
    SCI0->SIR03 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR03 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI0->SCR03 = _0004_SCRMN_DEFAULT_VALUE | _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR03 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* output enable */
    SCI0->SO0 |= _0004_SCI_CH2_DATA_OUTPUT_1;
    SCI0->SOL0 &= (uint16_t)~_0004_SCI_CHANNEL2_INVERTED;
    SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
    /* Set TxD1 pin */
    TXD1_PORT_SETTING();
    /* Set RxD1 pin */
    RXD1_PORT_SETTING();
    /* UART1 Start, Setting baud rate */
    status = UART1_BaudRate(freq, baud);
    UART1_Start();

    return (status);
}
/***********************************************************************************************************************
* Function Name: UART1_BaudRate
* @brief  This function sets the baud rate of UART0.
* @param  fclk_freq - the frequency of fCLK clock. unit Hz.
* @param  baud - the target baud rate, unit bps.
* @return status - MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART1_BaudRate(uint32_t fclk_freq, uint32_t baud)
{
    MD_STATUS status;
    uart_baud_t pvalue;

    status = UART_BaudRateCal(fclk_freq, baud, &pvalue);

    if (status == MD_OK)
    {
        SCI0->ST0 = _0008_SCI_CH3_STOP_TRG_ON | _0004_SCI_CH2_STOP_TRG_ON;
        SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | pvalue.prs;
        SCI0->SDR02 = pvalue.sdr << 9;
        SCI0->SDR03 = pvalue.sdr << 9;
        SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON | _0004_SCI_CH2_START_TRG_ON;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART1_Start
* @brief  This function starts the UART1 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void UART1_Start(void)
{
    SCI0->SO0 |= _0004_SCI_CH2_DATA_OUTPUT_1;
    SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
    SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON | _0004_SCI_CH2_START_TRG_ON;
    INTC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
    INTC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
    NVIC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
    NVIC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
    INTC_EnableIRQ(ST1_IRQn);       /* enable INTST1 interrupt */
    INTC_EnableIRQ(SR1_IRQn);       /* enable INTSR1 interrupt */
}
/***********************************************************************************************************************
* Function Name: UART1_Stop
* @brief  This function stops the UART1 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void UART1_Stop(void)
{
    INTC_DisableIRQ(ST1_IRQn); /* disable INTST1 interrupt */
    INTC_DisableIRQ(SR1_IRQn); /* disable INTSR1 interrupt */
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON | _0004_SCI_CH2_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0004_SCI_CH2_OUTPUT_ENABLE;
    INTC_ClearPendingIRQ(ST1_IRQn); /* clear INTST1 interrupt flag */
    INTC_ClearPendingIRQ(SR1_IRQn); /* clear INTSR1 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: UART1_Receive
* @brief  This function receives UART1 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS UART1_Receive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart1_rx_count = 0U;
        g_uart1_rx_length = rx_num;
        gp_uart1_rx_address = rx_buf;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: UART1_Send
* @brief  This function sends UART1 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS UART1_Send(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart1_tx_address = tx_buf;
        g_uart1_tx_count = tx_num;
        SCI0->TXD1 = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI10_MasterInit
* @brief  This function initializes the SPI10 module as Master.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI10_MasterInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0004_SCI_CH2_STOP_TRG_ON;
    SCI0->SPS0 &= ~SCI0_SPS0_PRS01_Msk;
    SCI0->SPS0 |= (0 << SCI0_SPS0_PRS01_Pos);
    SCI0->SIR02 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR02 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR02 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    //SCI0->SDR02 = 21 << 9;  /* fMCK/44 */
    SCI0->SDR02 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI0->SO0 &= ~_0400_SCI_CH2_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI0->SO0 |= _0400_SCI_CH2_CLOCK_OUTPUT_1;
    }
    SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
    /* Set SSn pin */
    SS10_PORT_SETTING();
    /* Set SCLK10 pin */
    SCLKO10_PORT_SETTING();
    /* Set SDI10 pin */
    SDI10_PORT_SETTING();
    /* Set SDO10 pin */
    SDO10_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI10_Start
* @brief  This function starts the SPI10 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI10_Start(void)
{
    /* SSn Active */
    SS10_PORT_CLR();
    SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
    SCI0->SS0 |= _0004_SCI_CH2_START_TRG_ON;
    /* clear INTSPI10 interrupt flag */
    INTC_ClearPendingIRQ(SPI10_IRQn);
    NVIC_ClearPendingIRQ(SPI10_IRQn);
    /* enable INTSPI10 interrupt */
    INTC_EnableIRQ(SPI10_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI10_Stop
* @brief  This function stops the SPI10 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI10_Stop(void)
{
    /* disable INTSPI10 interrupt */
    INTC_DisableIRQ(SPI10_IRQn);
    SCI0->ST0 |= _0004_SCI_CH2_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0004_SCI_CH2_OUTPUT_ENABLE;
    /* clear INTSPI10 interrupt flag */
    INTC_ClearPendingIRQ(SPI10_IRQn);
    NVIC_ClearPendingIRQ(SPI10_IRQn);
    /* SSn Inactive */
    SS10_PORT_SET();
}
/***********************************************************************************************************************
* Function Name: SPI10_MasterSendReceive
* @brief  This function sends and receives SPI10 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI10_MasterSendReceive(uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR02 |= _C000_SCI_RECEPTION_TRANSMISSION;

#ifdef SPI10_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI10] = CTRL_DATA_SPI10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMSAR = (uint32_t)&SCI0->SIO10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMDAR = (uint32_t)rx_buf;

        /* write transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMSAR = (uint32_t)tx_buf + 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMDAR = (uint32_t)&SCI0->SIO10;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI10 % 8);
#endif
#ifdef SPI10_WITH_DMA
        g_spi10_rx_count = 1;                      /* receive data count */
        g_spi10_tx_count = 1;                      /* send data count */
        gp_spi10_tx_address = tx_buf;              /* send buffer pointer */
        gp_spi10_rx_address = rx_buf + tx_num - 1; /* receive buffer pointer */
#else
        g_spi10_rx_count = tx_num;    /* receive data count */
        g_spi10_tx_count = tx_num;    /* send data count */
        gp_spi10_tx_address = tx_buf; /* send buffer pointer */
        gp_spi10_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI10_Start();
        SCI0->SIO10 = *gp_spi10_tx_address; /* started by writing data to SDR[7:0] */
        gp_spi10_tx_address++;
        g_spi10_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI10_MasterSend
* @brief  This function sends SPI10 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI10_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR02 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR02 |= _8000_SCI_TRANSMISSION;

#ifdef SPI10_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI10] = CTRL_DATA_SPI10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMDAR = (uint32_t)&SCI0->SIO10;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI10 % 8);
#endif
#ifdef SPI10_WITH_DMA
        g_spi10_tx_count = 1;         /* send data count */
        gp_spi10_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi10_tx_count = tx_num;    /* send data count */
        gp_spi10_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI10_Start();
        SCI0->SIO10 = *gp_spi10_tx_address; /* started by writing data to SDR[7:0] */
        gp_spi10_tx_address++;
        g_spi10_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI10_MasterReceive
* @brief  This function receives SPI10 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI10_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio10 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR02 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR02 |= _4000_SCI_RECEPTION;

#ifdef SPI10_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI10] = CTRL_DATA_SPI10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMSAR = (uint32_t)&SCI0->SIO10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMDAR = (uint32_t)rx_buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMSAR = (uint32_t)&dummy_sio10;
        DMAVEC->CTRL[CTRL_DATA_SPI10 + 1].DMDAR = (uint32_t)&SCI0->SIO10;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI10 % 8);
#endif
#ifdef SPI10_WITH_DMA
        g_spi10_rx_count = 1;                      /* receive data count */
        gp_spi10_rx_address = rx_buf + rx_num - 1; /* receive buffer pointer */
#else
        g_spi10_rx_count = rx_num;    /* receive data count */
        gp_spi10_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI10_Start();
        SCI0->SIO10 = dummy_sio10;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI10_SlaveInit
* @brief  This function initializes the SPI10 module. Slave transmission/reception operation.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI10_SlaveInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0004_SCI_CH2_STOP_TRG_ON;
    SCI0->SIR02 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR02 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR02 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI0->SDR02 = 0x0000;
    NVIC_SetPriority(SPI10_IRQn, 0); /* Set higher priority to execute slave ISR firstly */
    /* Set output enable */
    SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;

    SCLKI10_PORT_SETTING();
    SDI10_PORT_SETTING();
    SDO10_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI10_SlaveSend
* @brief  This function sends SPI10 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI10_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR02 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR02 |= _8000_SCI_TRANSMISSION;

#ifdef SPI10_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI10] = CTRL_DATA_SPI10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMDAR = (uint32_t)&SCI0->SIO10;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI10 % 8);
#endif
#ifdef SPI10_WITH_DMA
        g_spi10_tx_count = 1;         /* send data count */
#else
        g_spi10_tx_count = tx_num;    /* send data count */
#endif
        gp_spi10_tx_address = tx_buf; /* send buffer pointer */

        SPI10_Start();
        gp_spi10_tx_address++;
        g_spi10_tx_count--;
        SCI0->SIO10 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI10_SlaveReceive
* @brief  This function receives SPI10 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI10_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio10 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR02 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR02 |= _4000_SCI_RECEPTION;

#ifdef SPI10_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI10] = CTRL_DATA_SPI10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMSAR = (uint32_t)&SCI0->SIO10;
        DMAVEC->CTRL[CTRL_DATA_SPI10].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI10 % 8);
#endif

#ifdef SPI10_WITH_DMA
        g_spi10_rx_count = 0; /* receive data count */
#else
        g_spi10_rx_count = rx_num;    /* receive data count */
#endif
        gp_spi10_rx_address = rx_buf; /* receive buffer pointer */

        SPI10_Start();
        SCI0->SIO10 = dummy_sio10;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI11_MasterInit
* @brief  This function initializes the SPI11 module.
*         Master transmission/reception operation 
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI11_MasterInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;
    SCI0->SPS0 &= ~SCI0_SPS0_PRS01_Msk;
    SCI0->SPS0 |= (0 << SCI0_SPS0_PRS01_Pos);
    SCI0->SIR03 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR03 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR03 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
  //SCI0->SDR03 = 0 << 9; 	// fMCK/(1+n)x2 = fMCK/2
  //SCI0->SDR03 = 1 << 9; 	// fMCK/(1+n)x2 = fMCK/4
  //SCI0->SDR03 = 2 << 9;		// fMCK/(1+n)x2 = fMCK/6
  SCI0->SDR03 = 3 << 9;		// fMCK/(1+n)x2 = fMCK/8  
	//SCI0->SDR03 = 5 << 9;		// fMCK/(1+n)x2 = fMCK/12
	//SCI0->SDR03 = 7 << 9;		// fMCK/(1+n)x2 = fMCK/16
	//SCI0->SDR03 = 15 << 9;	// fMCK/(1+n)x2 = fMCK/32
	//SCI0->SDR03 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI0->SO0 &= ~_0800_SCI_CH3_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI0->SO0 |= _0800_SCI_CH3_CLOCK_OUTPUT_1;
    }
    SCI0->SOE0 |= _0008_SCI_CH3_OUTPUT_ENABLE;

    /* Set SSn pin */
    SS11_PORT_SETTING();
    /* Set SCLK11 pin */
    SCLKO11_PORT_SETTING();
    /* Set SDI11 pin */
    SDI11_PORT_SETTING();
    /* Set SDO11 pin */
    SDO11_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI11_MasterSend
* @brief  This function sends SPI11 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI11_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR03 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR03 |= _8000_SCI_TRANSMISSION;

#ifdef SPI11_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI11] = CTRL_DATA_SPI11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMDAR = (uint32_t)&SCI0->SIO11;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI11 % 8);
#endif
#ifdef SPI11_WITH_DMA
        g_spi11_tx_count = 1;         /* send data count */
#else
        g_spi11_tx_count = tx_num;    /* send data count */
#endif
        gp_spi11_tx_address = tx_buf; /* send buffer pointer */

        SPI11_Start();
        gp_spi11_tx_address++;
        g_spi11_tx_count--;
        SCI0->SIO11 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI11_MasterReceive
* @brief  This function receives SPI11 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI11_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio11 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR03 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR03 |= _4000_SCI_RECEPTION;

#ifdef SPI11_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI11] = CTRL_DATA_SPI11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMSAR = (uint32_t)&SCI0->SIO11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMDAR = (uint32_t)rx_buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMSAR = (uint32_t)&dummy_sio11;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMDAR = (uint32_t)&SCI0->SIO11;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI11 % 8);
#endif
#ifdef SPI11_WITH_DMA
        g_spi11_rx_count = 1;                      /* receive data count */
        gp_spi11_rx_address = rx_buf + rx_num - 1; /* receive buffer pointer */
#else
        g_spi11_rx_count = rx_num;    /* receive data count */
        gp_spi11_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI11_Start();
        SCI0->SIO11 = dummy_sio11;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI11_SlaveInit
* @brief  This function initializes the SPI11 module.
*         Slave transmission/reception operation. 
* @param  mode
*               - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*               - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*               - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*               - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI11_SlaveInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;
    SCI0->SIR03 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR03 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI0->SCR03 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI0->SDR03 = 0x0000;
    NVIC_SetPriority(SPI11_IRQn, 0); /* Set higher priority to execute slave ISR firstly */
    /* Set output enable */
    SCI0->SOE0 |= _0008_SCI_CH3_OUTPUT_ENABLE;

    /* Set SCK11 pin */
    SCLKI11_PORT_SETTING();
    /* Set SDI11 pin */
    SDI11_PORT_SETTING();
    /* Set SDO11 pin */
    SDO11_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI11_Start
* @brief  This function starts the SPI11 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI11_Start(void)
{
    /* SSn Active */
    SS11_PORT_CLR();
    SCI0->SOE0 |= _0008_SCI_CH3_OUTPUT_ENABLE;
    SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON;
    /* clear INTSPI11 interrupt flag */
    INTC_ClearPendingIRQ(SPI11_IRQn);
    NVIC_ClearPendingIRQ(SPI11_IRQn);
    /* enable INTSPI11 interrupt */
    INTC_EnableIRQ(SPI11_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI11_Stop
* @brief  This function stops the SPI11 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI11_Stop(void)
{
    /* disable INTSPI11 interrupt */
    INTC_DisableIRQ(SPI11_IRQn);
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0008_SCI_CH3_OUTPUT_ENABLE;
    /* clear INTSPI11 interrupt flag */
    INTC_ClearPendingIRQ(SPI11_IRQn);
    NVIC_ClearPendingIRQ(SPI11_IRQn);
    /* SSn Inactive */
    SS11_PORT_SET();
}
/***********************************************************************************************************************
* Function Name: SPI11_SlaveSendReceive
* @brief  This function sends and receives SPI11 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI11_SlaveSendReceive(uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR03 |= _C000_SCI_RECEPTION_TRANSMISSION;

#ifdef SPI11_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI11] = CTRL_DATA_SPI11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACT = tx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMRLD = tx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMSAR = (uint32_t)&SCI0->SIO11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMDAR = (uint32_t)rx_buf;

        /* write transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMSAR = (uint32_t)tx_buf + 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11 + 1].DMDAR = (uint32_t)&SCI0->SIO11;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI11 % 8);
#endif
#ifdef SPI11_WITH_DMA
        g_spi11_rx_count = 0;                      /* receive data count */
        g_spi11_tx_count = 1;                      /* send data count */
        gp_spi11_tx_address = tx_buf;              /* send buffer pointer */
        gp_spi11_rx_address = rx_buf + tx_num; /* receive buffer pointer */
#else
        g_spi11_rx_count = tx_num;    /* receive data count */
        g_spi11_tx_count = tx_num;    /* send data count */
        gp_spi11_tx_address = tx_buf; /* send buffer pointer */
        gp_spi11_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI11_Start();
        gp_spi11_tx_address++;
        g_spi11_tx_count--;
        SCI0->SIO11 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI11_SlaveSend
* @brief  This function sends SPI11 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI11_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR03 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR03 |= _8000_SCI_TRANSMISSION;

#ifdef SPI11_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI11] = CTRL_DATA_SPI11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMDAR = (uint32_t)&SCI0->SIO11;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI11 % 8);
#endif
#ifdef SPI11_WITH_DMA
        g_spi11_tx_count = 1;         /* send data count */
#else
        g_spi11_tx_count = tx_num;    /* send data count */
#endif
        gp_spi11_tx_address = tx_buf; /* send buffer pointer */

        SPI11_Start();
        gp_spi11_tx_address++;
        g_spi11_tx_count--;
        SCI0->SIO11 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI11_SlaveReceive
* @brief  This function receives SPI11 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI11_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio11 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI0->SCR03 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR03 |= _4000_SCI_RECEPTION;

#ifdef SPI11_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI11] = CTRL_DATA_SPI11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMSAR = (uint32_t)&SCI0->SIO11;
        DMAVEC->CTRL[CTRL_DATA_SPI11].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI11 % 8);
#endif

#ifdef SPI11_WITH_DMA
        g_spi11_rx_count = 0; /* receive data count */
#else
        g_spi11_rx_count = rx_num;    /* receive data count */
#endif
        gp_spi11_rx_address = rx_buf; /* receive buffer pointer */

        SPI11_Start();
        SCI0->SIO11 = dummy_sio11;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: IIC10_Init
* @brief  This function initializes the IIC10 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC10_Init(void)
{
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    //SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | _0001_SCI_CK00_fCLK_1;
    SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | _0004_SCI_CK00_fCLK_4;

    SCI0->ST0 |= _0004_SCI_CH2_STOP_TRG_ON;

    SCI0->SIR02 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR02 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
    SCI0->SCR02 = _0004_SCRMN_DEFAULT_VALUE | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                  _0000_SCI_MSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR02 = _3000_SCI_BAUDRATE_DIVISOR;
    SCI0->SO0 |= _0400_SCI_CH2_CLOCK_OUTPUT_1 | _0004_SCI_CH2_DATA_OUTPUT_1;
    /* Set SCL10 pin */
    SCL10_PORT_SETTING();
    /* Set SDA10 pin */
    SDA10_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IIC10_MasterSend
* @brief  This function starts transferring data for IIC10 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC10_MasterSend(uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    g_iic10_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC10 master status flag */
    adr &= 0xFEU;                                         /* send mode */
    g_iic10_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
    SCI0->SCR02 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR02 |= _8000_SCI_TRANSMISSION;
    /* Set paramater */
    g_iic10_tx_count = tx_num;
    gp_iic10_tx_address = tx_buf;
    /* Start condition */
    IIC10_StartCondition();
    INTC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
    NVIC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
    INTC_EnableIRQ(IIC10_IRQn);       /* enable INTIIC10 interrupt flag */
    NVIC_SetPriority(IIC10_IRQn, 3);  /* low priority */
    SCI0->SIO10 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC10_MasterReceive
* @brief  This function starts receiving data for IIC10 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC10_MasterReceive(uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    g_iic10_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
    adr |= 0x01U;                                          /* receive mode */
    g_iic10_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
    SCI0->SCR02 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR02 |= _8000_SCI_TRANSMISSION;
    /* Set parameter */
    g_iic10_rx_length = rx_num;
    g_iic10_rx_count = 0U;
    gp_iic10_rx_address = rx_buf;
    /* Start condition */
    IIC10_StartCondition();
    INTC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
    NVIC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
    INTC_EnableIRQ(IIC10_IRQn);       /* enable INTIIC10 interrupt flag */
    NVIC_SetPriority(IIC10_IRQn, 3);  /* low priority */
    SCI0->SIO10 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC10_Stop
* @brief  This function stops the IIC10 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC10_Stop(void)
{
    INTC_DisableIRQ(IIC10_IRQn); /* disable INTIIC10 interrupt flag */
    SCI0->ST0 |= _0004_SCI_CH2_STOP_TRG_ON;
    INTC_ClearPendingIRQ(IIC10_IRQn); /* clear INTIIC10 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: IIC10_StartCondition
* @brief  This function starts IIC10 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC10_StartCondition(void)
{
    volatile uint8_t w_count;

    SCI0->SO0 &= (uint16_t) ~(_0004_SCI_CH2_DATA_OUTPUT_1);

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 &= (uint16_t) ~(_0400_SCI_CH2_CLOCK_OUTPUT_1);
    SCI0->SOE0 |= _0004_SCI_CH2_OUTPUT_ENABLE;
    SCI0->SS0 |= _0004_SCI_CH2_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: IIC10_StopCondition
* @brief  This function stops IIC10 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC10_StopCondition(void)
{
    volatile uint8_t w_count;

    g_iic10_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC10 master status flag */
    SCI0->ST0 |= _0004_SCI_CH2_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0004_SCI_CH2_OUTPUT_ENABLE;
    SCI0->SO0 &= (uint16_t) ~(_0004_SCI_CH2_DATA_OUTPUT_1);
    SCI0->SO0 |= _0400_SCI_CH2_CLOCK_OUTPUT_1;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 |= _0004_SCI_CH2_DATA_OUTPUT_1;
}

/***********************************************************************************************************************
* Function Name: IIC11_Init
* @brief  This function initializes the IIC11 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC11_Init(void)
{
    CGC->PER0 |= CGC_PER0_SCI0EN_Msk;
    SCI0->SPS0 = _0000_SCI_CK01_fCLK_0 | _0001_SCI_CK00_fCLK_1;

    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;

    SCI0->SIR03 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI0->SMR03 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
    SCI0->SCR03 = _0004_SCRMN_DEFAULT_VALUE | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                  _0000_SCI_MSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI0->SDR03 = _CE00_SCI_BAUDRATE_DIVISOR;
    SCI0->SO0 |= _0800_SCI_CH3_CLOCK_OUTPUT_1 | _0008_SCI_CH3_DATA_OUTPUT_1;
    /* Set SCL11 pin */
    SCL11_PORT_SETTING();
    /* Set SDA11 pin */
    SDA11_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IIC11_MasterSend
* @brief  This function starts transferring data for IIC11 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC11_MasterSend(uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    g_iic11_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC11 master status flag */
    adr &= 0xFEU;                                         /* send mode */
    g_iic11_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
    SCI0->SCR03 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR03 |= _8000_SCI_TRANSMISSION;
    /* Set paramater */
    g_iic11_tx_count = tx_num;
    gp_iic11_tx_address = tx_buf;
    /* Start condition */
    IIC11_StartCondition();
    INTC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
    NVIC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
    INTC_EnableIRQ(IIC11_IRQn);       /* enable INTIIC11 interrupt flag */
    SCI0->SIO11 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC11_MasterReceive
* @brief  This function starts receiving data for IIC11 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC11_MasterReceive(uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    g_iic11_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
    adr |= 0x01U;                                          /* receive mode */
    g_iic11_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
    SCI0->SCR03 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI0->SCR03 |= _8000_SCI_TRANSMISSION;
    /* Set parameter */
    g_iic11_rx_length = rx_num;
    g_iic11_rx_count = 0U;
    gp_iic11_rx_address = rx_buf;
    /* Start condition */
    IIC11_StartCondition();
    INTC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
    NVIC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
    INTC_EnableIRQ(IIC11_IRQn);       /* enable INTIIC11 interrupt flag */
    SCI0->SIO11 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC11_Stop
* @brief  This function stops the IIC11 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC11_Stop(void)
{
    INTC_DisableIRQ(IIC11_IRQn); /* disable INTIIC11 interrupt flag */
    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;
    INTC_ClearPendingIRQ(IIC11_IRQn); /* clear INTIIC11 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: IIC11_StartCondition
* @brief  This function starts IIC11 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC11_StartCondition(void)
{
    volatile uint8_t w_count;

    SCI0->SO0 &= (uint16_t) ~(_0008_SCI_CH3_DATA_OUTPUT_1);

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 &= (uint16_t) ~(_0800_SCI_CH3_CLOCK_OUTPUT_1);
    SCI0->SOE0 |= _0008_SCI_CH3_OUTPUT_ENABLE;
    SCI0->SS0 |= _0008_SCI_CH3_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: IIC11_StopCondition
* @brief  This function stops IIC11 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC11_StopCondition(void)
{
    volatile uint8_t w_count;

    SCI0->ST0 |= _0008_SCI_CH3_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0008_SCI_CH3_OUTPUT_ENABLE;
    SCI0->SO0 &= (uint16_t) ~(_0008_SCI_CH3_DATA_OUTPUT_1);
    SCI0->SO0 |= _0800_SCI_CH3_CLOCK_OUTPUT_1;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI0->SO0 |= _0008_SCI_CH3_DATA_OUTPUT_1;
}
/***********************************************************************************************************************
* Function Name: UART2_Init
* @brief  This function initializes the UART2 module.
*         Date Length: 8 bit; Parity: none; Stop: 1 bit              
* @param  freq - the frequency of fCLK
* @param  baud - the expected baud rate
* @return status - MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART2_Init(uint32_t freq, uint32_t baud)
{
    MD_STATUS status;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
    INTC_DisableIRQ(ST2_IRQn);       /* disable INTST2 interrupt */
    INTC_DisableIRQ(SR2_IRQn);       /* disable INTSR2 interrupt */
    INTC_DisableIRQ(SRE2_IRQn);      /* disable INTSRE2 interrupt */
    INTC_ClearPendingIRQ(ST2_IRQn);  /* clear INTST2 interrupt flag */
    INTC_ClearPendingIRQ(SR2_IRQn);  /* clear INTSR2 interrupt flag */
    INTC_ClearPendingIRQ(SRE2_IRQn); /* clear INTSRE2 interrupt flag */

#ifdef USE_IRDA
    CGC->PER0 |= CGC_PER0_IRDAEN_Msk;
    IRDA->IRCR = _00_IRDA_B_3_16_SELECTED | _00_IRDA_OUTPUT_IRTXD | _00_IRDA_OUTPUT_IRRXD;
    IRDA->IRCR |= _80_IRDA_COMMUNICATION_IRDA;
#endif
    /* transmission channel */
    SCI1->SMR10 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI1->SCR10 = _0004_SCRMN_DEFAULT_VALUE | _8000_SCI_TRANSMISSION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI1->SDR10 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* reception channel */
    MISC->NFEN0 |= _10_SCI_RXD2_FILTER_ON;
    SCI1->SIR11 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR11 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0100_SCI_TRIGGER_RXD | _0000_SCI_EDGE_FALL | _0002_SCI_MODE_UART | _0000_SCI_TRANSFER_END;
    SCI1->SCR11 = _0004_SCRMN_DEFAULT_VALUE | _4000_SCI_RECEPTION | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0080_SCI_LSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI1->SDR11 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* output enable */
    SCI1->SO1 |= _0001_SCI_CH0_DATA_OUTPUT_1;
    SCI1->SOL1 &= (uint16_t)~_0001_SCI_CHANNEL0_INVERTED;
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set TxD2 pin */
    TXD2_PORT_SETTING();
    /* Set RxD2 pin */
    RXD2_PORT_SETTING();
    /* UART2 Start, Setting baud rate */
    status = UART2_BaudRate(freq, baud);
    UART2_Start();

    return (status);
}
/***********************************************************************************************************************
* Function Name: UART2_BaudRate
* @brief  This function sets the baud rate of UART0.
* @param  fclk_freq - the frequency of fCLK clock. unit Hz.
* @param  baud - the target baud rate, unit bps.
* @return status - MD_OK, MD_ERROR
***********************************************************************************************************************/
MD_STATUS UART2_BaudRate(uint32_t fclk_freq, uint32_t baud)
{
    MD_STATUS status;
    uart_baud_t pvalue;

    status = UART_BaudRateCal(fclk_freq, baud, &pvalue);

    if (status == MD_OK)
    {
        SCI1->ST1 = _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
        SCI1->SPS1 = _0000_SCI_CK01_fCLK_0 | pvalue.prs;
        SCI1->SDR10 = pvalue.sdr << 9;
        SCI1->SDR11 = pvalue.sdr << 9;
        SCI1->SS1 |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: UART2_Start
* @brief  This function starts the UART2 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void UART2_Start(void)
{
    SCI1->SO1 |= _0001_SCI_CH0_DATA_OUTPUT_1;
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0002_SCI_CH1_START_TRG_ON | _0001_SCI_CH0_START_TRG_ON;
    INTC_ClearPendingIRQ(ST2_IRQn); /* clear INTST2 interrupt flag */
    INTC_ClearPendingIRQ(SR2_IRQn); /* clear INTSR2 interrupt flag */
    NVIC_ClearPendingIRQ(ST2_IRQn); /* clear INTST2 interrupt flag */
    NVIC_ClearPendingIRQ(SR2_IRQn); /* clear INTSR2 interrupt flag */
    INTC_EnableIRQ(ST2_IRQn);       /* enable INTST2 interrupt */
    INTC_EnableIRQ(SR2_IRQn);       /* enable INTSR2 interrupt */
}
/***********************************************************************************************************************
* Function Name: UART2_Stop
* @brief  This function stops the UART2 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void UART2_Stop(void)
{
    INTC_DisableIRQ(ST2_IRQn); /* disable INTST2 interrupt */
    INTC_DisableIRQ(SR2_IRQn); /* disable INTSR2 interrupt */
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON | _0001_SCI_CH0_STOP_TRG_ON;
    SCI1->SOE1 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
    INTC_ClearPendingIRQ(ST2_IRQn); /* clear INTST2 interrupt flag */
    INTC_ClearPendingIRQ(SR2_IRQn); /* clear INTSR2 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: UART2_Receive
* @brief  This function receives UART2 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS UART2_Receive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart2_rx_count = 0U;
        g_uart2_rx_length = rx_num;
        gp_uart2_rx_address = rx_buf;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: UART2_Send
* @brief  This function sends UART2 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS UART2_Send(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart2_tx_address = tx_buf;
        g_uart2_tx_count = tx_num;
        SCI1->TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI20_MasterInit
* @brief  This function initializes the SPI20 module.
*         Master transmission/reception operation 
* @param  mode
*               - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*               - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*               - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*               - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI20_MasterInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
    //SPS0 = (0 << SCI0_SPS0_PRS00_Pos) | (3 << SCI0_SPS0_PRS00_Pos);
    SCI1->SIR10 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR10 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI1->SCR10 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
	//SCI1->SDR10 = 0 << 9; 	// fMCK/(1+n)x2 = fMCK/2
    //SCI1->SDR10 = 1 << 9; 	// fMCK/(1+n)x2 = fMCK/4
    //SCI1->SDR10 = 2 << 9;		// fMCK/(1+n)x2 = fMCK/6
    SCI1->SDR10 = 3 << 9;		// fMCK/(1+n)x2 = fMCK/8
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
    /* Set SDI20 pin */
    SDI20_PORT_SETTING();
    /* Set SDO20 pin */
    SDO20_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI20_Start
* @brief  This function starts the SPI20 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI20_Start(void)
{
    /* SSn Active */
    SS20_PORT_CLR();
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;
    /* clear INTSPI20 interrupt flag */
    INTC_ClearPendingIRQ(SPI20_IRQn);
    /* enable INTSPI20 interrupt */
    INTC_EnableIRQ(SPI20_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI20_Stop
* @brief  This function stops the SPI20 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI20_Stop(void)
{
    /* disable INTSPI20 interrupt */
    INTC_DisableIRQ(SPI20_IRQn);
    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI1->SOE1 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
    /* clear INTSPI20 interrupt flag */
    INTC_ClearPendingIRQ(SPI20_IRQn);
    /* SSn Inactive */
    SS20_PORT_SET();
}
/***********************************************************************************************************************
* Function Name: SPI20_MasterSend
* @brief  This function sends data with Most Significant Byte First and polling-based.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI20_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPI20_Start();
        do
        {
            SCI1->SIO20 = tx_buf[--tx_num]; /* started by writing data to SDR[7:0] */
#if 1
            while(INTC_GetPendingIRQ(SPI20_IRQn) == 0);
            INTC_ClearPendingIRQ(SPI20_IRQn);
#else
            __WFI();
#endif
        } while (tx_num);
        SPI20_Stop();
    }
    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI20_MasterReceive
* @brief  This function receives data with Most Significant Byte First and polling-based.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI20_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio20 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPI20_Start();
        do
        {
            SCI1->SIO20 = dummy_sio20; /* dummy write */
#if 1
            while(INTC_GetPendingIRQ(SPI20_IRQn) == 0);
            INTC_ClearPendingIRQ(SPI20_IRQn);
#else
            __WFI();
#endif
        rx_buf[--rx_num];
        } while (rx_num);
        SPI20_Stop();
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI20_SlaveInit
* @brief  This function initializes the SPI20 module. Slave transmission/reception operation.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI20_SlaveInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI1->SIR10 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR10 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI1->SCR10 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI1->SDR10 = 0x0000;
    NVIC_SetPriority(SPI20_IRQn, 0); /* Set higher priority to execute slave ISR firstly */
    /* Set output enable */
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    /* Set SCLK21 pin */
    SCLKI20_PORT_SETTING();
    /* Set SDI21 pin */
    SDI20_PORT_SETTING();
    /* Set SDO21 pin */
    SDO20_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI20_SlaveSend
* @brief  This function sends SPI20 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI20_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR10 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI1->SCR10 |= _8000_SCI_TRANSMISSION;

#ifdef SPI20_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI20] = CTRL_DATA_SPI20;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMDAR = (uint32_t)&SCI1->SIO20;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI20 % 8);
#endif
#ifdef SPI20_WITH_DMA
        g_spi20_tx_count = 1;         /* send data count */
#else
        g_spi20_tx_count = tx_num;    /* send data count */
#endif
        gp_spi20_tx_address = tx_buf; /* send buffer pointer */

        SPI20_Start();
        gp_spi20_tx_address++;
        g_spi20_tx_count--;
        SCI1->SIO20 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI20_SlaveReceive
* @brief  This function receives SPI20 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI20_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio20 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR10 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI1->SCR10 |= _4000_SCI_RECEPTION;

#ifdef SPI20_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI20] = CTRL_DATA_SPI20;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMSAR = (uint32_t)&SCI1->SIO20;
        DMAVEC->CTRL[CTRL_DATA_SPI20].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI20 % 8);
#endif

#ifdef SPI20_WITH_DMA
        g_spi20_rx_count = 0; /* receive data count */
#else
        g_spi20_rx_count = rx_num;    /* receive data count */
#endif
        gp_spi20_rx_address = rx_buf; /* receive buffer pointer */

        SPI20_Start();
        SCI1->SIO20 = dummy_sio20;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI21_MasterInit
* @brief  This function initializes the SPI21 module.
*         Master transmission/reception operation 
* @param  mode
*               - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*               - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*               - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*               - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI21_MasterInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    //SPS0 = (0 << SCI0_SPS0_PRS00_Pos) | (3 << SCI0_SPS0_PRS00_Pos);
    SCI1->SIR11 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR11 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI1->SCR11 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI1->SDR11 = _CE00_SCI_BAUDRATE_DIVISOR;
    /* Set output enable */
    if ((mode == SPI_MODE_0) || (mode == SPI_MODE_1))
    {
        SCI1->SO1 &= ~_0200_SCI_CH1_CLOCK_OUTPUT_1;
    }
    if ((mode == SPI_MODE_2) || (mode == SPI_MODE_3))
    {
        SCI1->SO1 |= _0200_SCI_CH1_CLOCK_OUTPUT_1;
    }
    SCI1->SOE1 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    /* Set SSn pin */
    SS21_PORT_SETTING();
    /* Set SCLK21 pin */
    SCLKO21_PORT_SETTING();
    /* Set SDI21 pin */
    SDI21_PORT_SETTING();
    /* Set SDO21 pin */
    SDO21_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI21_Start
* @brief  This function starts the SPI21 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI21_Start(void)
{
    /* SSn Active */
    SS21_PORT_CLR();
    SCI1->SOE1 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    SCI1->SS1 |= _0002_SCI_CH1_START_TRG_ON;
    /* clear INTSPI21 interrupt flag */
    INTC_ClearPendingIRQ(SPI21_IRQn);
    /* enable INTSPI21 interrupt */
    INTC_EnableIRQ(SPI21_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI21_Stop
* @brief  This function stops the SPI21 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI21_Stop(void)
{
    /* disable INTSPI21 interrupt */
    INTC_DisableIRQ(SPI21_IRQn);
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI1->SOE1 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
    /* clear INTSPI20 interrupt flag */
    INTC_ClearPendingIRQ(SPI21_IRQn);
    /* SSn Inactive */
    SS21_PORT_SET();
}
/***********************************************************************************************************************
* Function Name: SPI21_MasterSendReceive
* @brief  This function sends and receives SPI21 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  rx_buf - receive buffer pointer
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI21_MasterSendReceive(uint8_t *const tx_buf, uint16_t tx_num, uint8_t *const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR11 |= _C000_SCI_RECEPTION_TRANSMISSION;

#ifdef SPI21_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI21] = CTRL_DATA_SPI21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMSAR = (uint32_t)&SCI1->SIO21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMDAR = (uint32_t)rx_buf;

        /* write transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMSAR = (uint32_t)tx_buf + 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMDAR = (uint32_t)&SCI1->SIO21;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI21 % 8);
#endif
#ifdef SPI21_WITH_DMA
        g_spi21_rx_count = 1;                      /* receive data count */
        g_spi21_tx_count = 1;                      /* send data count */
        gp_spi21_tx_address = tx_buf;              /* send buffer pointer */
        gp_spi21_rx_address = rx_buf + tx_num - 1; /* receive buffer pointer */
#else
        g_spi21_rx_count = tx_num;    /* receive data count */
        g_spi21_tx_count = tx_num;    /* send data count */
        gp_spi21_tx_address = tx_buf; /* send buffer pointer */
        gp_spi21_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI21_Start();
        SCI1->SIO21 = *gp_spi21_tx_address; /* started by writing data to SDR[7:0] */
        gp_spi21_tx_address++;
        g_spi21_tx_count--;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI21_MasterSend
* @brief  This function sends data with Most Significant Byte First and polling-based.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI21_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR11 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI1->SCR11 |= _8000_SCI_TRANSMISSION;

#ifdef SPI21_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI21] = CTRL_DATA_SPI21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMDAR = (uint32_t)&SCI1->SIO21;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI21 % 8);
#endif
#ifdef SPI21_WITH_DMA
        g_spi21_tx_count = 1;         /* send data count */
        gp_spi21_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi21_tx_count = tx_num;    /* send data count */
        gp_spi21_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI21_Start();
        SCI1->SIO21 = *gp_spi21_tx_address; /* started by writing data to SDR[7:0] */
        gp_spi21_tx_address++;
        g_spi21_tx_count--;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI21_MasterReceive
* @brief  This function receives SPI21 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI21_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio21 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR11 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI1->SCR11 |= _4000_SCI_RECEPTION;

#ifdef SPI21_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI21] = CTRL_DATA_SPI21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMSAR = (uint32_t)&SCI1->SIO21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMDAR = (uint32_t)rx_buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMACT = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMRLD = rx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMSAR = (uint32_t)&dummy_sio21;
        DMAVEC->CTRL[CTRL_DATA_SPI21 + 1].DMDAR = (uint32_t)&SCI1->SIO21;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI21 % 8);
#endif
#ifdef SPI21_WITH_DMA
        g_spi21_rx_count = 1;                      /* receive data count */
        gp_spi21_rx_address = rx_buf + rx_num - 1; /* receive buffer pointer */
#else
        g_spi21_rx_count = rx_num;    /* receive data count */
        gp_spi21_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI21_Start();
        SCI1->SIO21 = dummy_sio21;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI21_SlaveInit
* @brief  This function initializes the SPI21 module. Slave transmission/reception operation.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
* @return None
***********************************************************************************************************************/
void SPI21_SlaveInit(spi_mode_t mode)
{
    uint8_t dap, ckp;
    dap = ~mode & 0x01;
    ckp = (~mode & 0x02) >> 1;
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI1->SIR11 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR11 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _4000_SCI_CLOCK_MODE_TI0N |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_MODE_SPI | _0000_SCI_TRANSFER_END;
    SCI1->SCR11 = _0004_SCRMN_DEFAULT_VALUE | _C000_SCI_RECEPTION_TRANSMISSION | dap << 13 | ckp << 12 | _0000_SCI_INTSRE_MASK |
                  _0000_SCI_PARITY_NONE | _0000_SCI_MSB | _0000_SCI_STOP_NONE | _0003_SCI_LENGTH_8;
    SCI1->SDR11 = 0x0000;
    NVIC_SetPriority(SPI21_IRQn, 0); /* Set higher priority to execute slave ISR firstly */
    /* Set output enable */
    SCI1->SOE1 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    /* Set SCLK21 pin */
    SCLKI21_PORT_SETTING();
    /* Set SDI21 pin */
    SDI21_PORT_SETTING();
    /* Set SDO21 pin */
    SDO21_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI21_SlaveSend
* @brief  This function sends SPI21 data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI21_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR11 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI1->SCR11 |= _8000_SCI_TRANSMISSION;

#ifdef SPI21_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI21] = CTRL_DATA_SPI21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMDAR = (uint32_t)&SCI1->SIO21;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI21 % 8);
#endif
#ifdef SPI21_WITH_DMA
        g_spi21_tx_count = 1;         /* send data count */
#else
        g_spi21_tx_count = tx_num;    /* send data count */
#endif
        gp_spi21_tx_address = tx_buf; /* send buffer pointer */

        SPI21_Start();
        gp_spi21_tx_address++;
        g_spi21_tx_count--;
        SCI1->SIO21 = tx_buf[0]; /* started by writing data to SDR[7:0] */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI21_SlaveReceive
* @brief  This function receives SPI21 data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI21_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    static uint8_t dummy_sio21 = 0xFFU;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SCI1->SCR11 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI1->SCR11 |= _4000_SCI_RECEPTION;

#ifdef SPI21_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI21] = CTRL_DATA_SPI21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMSAR = (uint32_t)&SCI1->SIO21;
        DMAVEC->CTRL[CTRL_DATA_SPI21].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI21 % 8);
#endif

#ifdef SPI21_WITH_DMA
        g_spi21_rx_count = 0; /* receive data count */
#else
        g_spi21_rx_count = rx_num;    /* receive data count */
#endif
        gp_spi21_rx_address = rx_buf; /* receive buffer pointer */

        SPI21_Start();
        SCI1->SIO21 = dummy_sio21;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: IIC20_Init
* @brief  This function initializes the IIC20 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC20_Init(void)
{
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    //SCI1->SPS1 = _0000_SCI_CK01_fCLK_0 | _0001_SCI_CK00_fCLK_1;
    SCI1->SPS1 = _0000_SCI_CK01_fCLK_0 | _0004_SCI_CK00_fCLK_4;

    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;

    SCI1->SIR10 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR10 = _0020_SMRMN_DEFAULT_VALUE | _0000_SCI_CLOCK_SELECT_CK00 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
    SCI1->SCR10 = _0004_SCRMN_DEFAULT_VALUE | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                  _0000_SCI_MSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI1->SDR10 = _3000_SCI_BAUDRATE_DIVISOR;
    SCI1->SO1 |= _0100_SCI_CH0_CLOCK_OUTPUT_1 | _0001_SCI_CH0_DATA_OUTPUT_1;
    /* Set SCL20 pin */
    SCL20_PORT_SETTING();
    /* Set SDA20 pin */
    SDA20_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IIC20_MasterSend
* @brief  This function starts transferring data for IIC20 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC20_MasterSend(uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    g_iic20_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC20 master status flag */
    adr &= 0xFEU;                                         /* send mode */
    g_iic20_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
    SCI1->SCR10 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI1->SCR10 |= _8000_SCI_TRANSMISSION;
    /* Set paramater */
    g_iic20_tx_count = tx_num;
    gp_iic20_tx_address = tx_buf;
    /* Start condition */
    IIC20_StartCondition();
    INTC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
    NVIC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
    INTC_EnableIRQ(IIC20_IRQn);       /* enable INTIIC20 interrupt flag */
    NVIC_SetPriority(IIC20_IRQn, 3);  /* low priority */
    SCI1->SIO20 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC20_MasterReceive
* @brief  This function starts receiving data for IIC20 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC20_MasterReceive(uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    g_iic20_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
    adr |= 0x01U;                                          /* receive mode */
    g_iic20_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
    SCI1->SCR10 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI1->SCR10 |= _8000_SCI_TRANSMISSION;
    /* Set parameter */
    g_iic20_rx_length = rx_num;
    g_iic20_rx_count = 0U;
    gp_iic20_rx_address = rx_buf;
    /* Start condition */
    IIC20_StartCondition();
    INTC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
    NVIC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
    INTC_EnableIRQ(IIC20_IRQn);       /* enable INTIIC20 interrupt flag */
    NVIC_SetPriority(IIC20_IRQn, 3);  /* low priority */
    SCI1->SIO20 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC20_Stop
* @brief  This function stops the IIC20 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC20_Stop(void)
{
    INTC_DisableIRQ(IIC20_IRQn); /* disable INTIIC20 interrupt flag */
    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
    INTC_ClearPendingIRQ(IIC20_IRQn); /* clear INTIIC20 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: IIC20_StartCondition
* @brief  This function starts IIC20 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC20_StartCondition(void)
{
    volatile uint8_t w_count;

    SCI1->SO1 &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI1->SO1 &= (uint16_t) ~(_0100_SCI_CH0_CLOCK_OUTPUT_1);
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: IIC20_StopCondition
* @brief  This function stops IIC20 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC20_StopCondition(void)
{
    volatile uint8_t w_count;

    g_iic20_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC20 master status flag */
    SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI1->SOE1 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SO1 &= (uint16_t) ~(_0001_SCI_CH0_DATA_OUTPUT_1);
    SCI1->SO1 |= _0100_SCI_CH0_CLOCK_OUTPUT_1;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI1->SO1 |= _0001_SCI_CH0_DATA_OUTPUT_1;
}

/***********************************************************************************************************************
* Function Name: IIC21_Init
* @brief  This function initializes the IIC21 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC21_Init(void)
{
    CGC->PER0 |= CGC_PER0_SCI1EN_Msk;
    SCI1->SPS1 = _0000_SCI_CK01_fCLK_0 | _0001_SCI_CK00_fCLK_1;

    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;

    SCI1->SIR11 = _0004_SCI_SIRMN_FECTMN | _0002_SCI_SIRMN_PECTMN | _0001_SCI_SIRMN_OVCTMN;
    SCI1->SMR11 = _0020_SMRMN_DEFAULT_VALUE | _8000_SCI_CLOCK_SELECT_CK01 | _0000_SCI_CLOCK_MODE_CKS |
                  _0000_SCI_TRIGGER_SOFTWARE | _0000_SCI_EDGE_FALL | _0004_SCI_MODE_IIC | _0000_SCI_TRANSFER_END;
    SCI1->SCR11 = _0004_SCRMN_DEFAULT_VALUE | _0000_SCI_TIMING_1 | _0000_SCI_INTSRE_MASK | _0000_SCI_PARITY_NONE |
                  _0000_SCI_MSB | _0010_SCI_STOP_1 | _0003_SCI_LENGTH_8;
    SCI1->SDR11 = _CE00_SCI_BAUDRATE_DIVISOR;
    SCI1->SO1 |= _0200_SCI_CH1_CLOCK_OUTPUT_1 | _0002_SCI_CH1_DATA_OUTPUT_1;
    /* Set SCL21 pin */
    SCL21_PORT_SETTING();
    /* Set SDA21 pin */
    SDA21_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IIC21_MasterSend
* @brief  This function starts transferring data for IIC21 in master mode.
* @param  adr - set address for select slave
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC21_MasterSend(uint8_t adr, uint8_t *const tx_buf, uint16_t tx_num)
{
    g_iic21_master_status_flag = _00_SCI_IIC_MASTER_IDLE; /* clear IIC21 master status flag */
    adr &= 0xFEU;                                         /* send mode */
    g_iic21_master_status_flag = _01_SCI_IIC_SEND_FLAG;   /* set master status flag */
    SCI1->SCR11 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI1->SCR11 |= _8000_SCI_TRANSMISSION;
    /* Set paramater */
    g_iic21_tx_count = tx_num;
    gp_iic21_tx_address = tx_buf;
    /* Start condition */
    IIC21_StartCondition();
    INTC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
    NVIC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
    INTC_EnableIRQ(IIC21_IRQn);       /* enable INTIIC21 interrupt flag */
    SCI1->SIO21 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC21_MasterReceive
* @brief  This function starts receiving data for IIC21 in master mode.
* @param  adr - set address for select slave
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IIC21_MasterReceive(uint8_t adr, uint8_t *const rx_buf, uint16_t rx_num)
{
    g_iic21_master_status_flag = _00_SCI_IIC_MASTER_IDLE;  /* clear master status flag */
    adr |= 0x01U;                                          /* receive mode */
    g_iic21_master_status_flag = _02_SCI_IIC_RECEIVE_FLAG; /* set master status flag */
    SCI1->SCR11 &= (uint16_t) ~(_C000_SCI_RECEPTION_TRANSMISSION);
    SCI1->SCR11 |= _8000_SCI_TRANSMISSION;
    /* Set parameter */
    g_iic21_rx_length = rx_num;
    g_iic21_rx_count = 0U;
    gp_iic21_rx_address = rx_buf;
    /* Start condition */
    IIC21_StartCondition();
    INTC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
    NVIC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
    INTC_EnableIRQ(IIC21_IRQn);       /* enable INTIIC21 interrupt flag */
    SCI1->SIO21 = adr;
}
/***********************************************************************************************************************
* Function Name: IIC21_Stop
* @brief  This function stops the IIC21 operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC21_Stop(void)
{
    INTC_DisableIRQ(IIC21_IRQn); /* disable INTIIC21 interrupt flag */
    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    INTC_ClearPendingIRQ(IIC21_IRQn); /* clear INTIIC21 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: IIC21_StartCondition
* @brief  This function starts IIC21 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC21_StartCondition(void)
{
    volatile uint8_t w_count;

    SCI1->SO1 &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI1->SO1 &= (uint16_t) ~(_0200_SCI_CH1_CLOCK_OUTPUT_1);
    SCI1->SOE1 |= _0002_SCI_CH1_OUTPUT_ENABLE;
    SCI1->SS1 |= _0002_SCI_CH1_START_TRG_ON;
}
/***********************************************************************************************************************
* Function Name: IIC21_StopCondition
* @brief  This function stops IIC21 condition.
* @param  None
* @return None
***********************************************************************************************************************/
void IIC21_StopCondition(void)
{
    volatile uint8_t w_count;

    SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
    SCI1->SOE1 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
    SCI1->SO1 &= (uint16_t) ~(_0002_SCI_CH1_DATA_OUTPUT_1);
    SCI1->SO1 |= _0200_SCI_CH1_CLOCK_OUTPUT_1;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= IIC_WAITTIME; w_count++)
    {
        __NOP();
    }

    SCI1->SO1 |= _0002_SCI_CH1_DATA_OUTPUT_1;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
