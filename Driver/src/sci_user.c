/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    sci_user.c
* @brief   This file implements device driver for SCI module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "CMS32L051.h"
#include "sci.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#if defined USE_SCI_UART2_TX 
void IRQ07_Handler(void) __attribute__((alias("uart2_interrupt_send")));
#elif defined USE_SCI_SPI20
void IRQ07_Handler(void) __attribute__((alias("spi20_interrupt")));
#elif defined USE_SCI_IIC20
void IRQ07_Handler(void) __attribute__((alias("iic20_interrupt")));
#endif

#if defined USE_SCI_UART2_RX
void IRQ08_Handler(void) __attribute__((alias("uart2_interrupt_receive")));
#elif defined USE_SCI_SPI21
void IRQ08_Handler(void) __attribute__((alias("spi21_interrupt")));
#elif defined USE_SCI_IIC21
void IRQ08_Handler(void) __attribute__((alias("iic21_interrupt")));
#endif

#if defined USE_SCI_UART0_TX
void IRQ10_Handler(void) __attribute__((alias("uart0_interrupt_send")));
#elif defined USE_SCI_SPI00
void IRQ10_Handler(void) __attribute__((alias("spi00_interrupt")));
#elif defined USE_SCI_IIC00
void IRQ10_Handler(void) __attribute__((alias("iic00_interrupt")));
#endif

#if defined USE_SCI_UART0_RX
void IRQ11_Handler(void) __attribute__((alias("uart0_interrupt_receive")));
#elif defined USE_SCI_SPI01
void IRQ11_Handler(void) __attribute__((alias("spi01_interrupt")));
#elif defined USE_SCI_IIC00
void IRQ11_Handler(void) __attribute__((alias("iic01_interrupt")));
#endif

//#if defined USE_SCI_UART1_TX
//void IRQ13_Handler(void) __attribute__((alias("uart1_interrupt_send")));
//#elif defined USE_SCI_SPI10
//void IRQ13_Handler(void) __attribute__((alias("spi10_interrupt")));
//#elif defined USE_SCI_IIC10
//void IRQ13_Handler(void) __attribute__((alias("iic10_interrupt")));
//#endif

#if defined USE_SCI_UART1_RX
void IRQ14_Handler(void) __attribute__((alias("uart1_interrupt_receive")));
#elif defined USE_SCI_SPI11
void IRQ14_Handler(void) __attribute__((alias("spi11_interrupt")));
#elif defined USE_SCI_IIC11
void IRQ14_Handler(void) __attribute__((alias("iic11_interrupt")));
#endif

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t g_iic00_tx_end;                /* iic00 send data end */
volatile uint8_t g_iic00_rx_end;                /* iic00 receive data end */
volatile uint8_t g_iic01_tx_end;                /* iic01 send data end */
volatile uint8_t g_iic01_rx_end;                /* iic01 receive data end */
volatile uint8_t g_iic10_tx_end;                /* iic10 send data end */
volatile uint8_t g_iic10_rx_end;                /* iic10 receive data end */
volatile uint8_t g_iic11_tx_end;                /* iic11 send data end */
volatile uint8_t g_iic11_rx_end;                /* iic11 receive data end */
volatile uint8_t g_iic20_tx_end;                /* iic20 send data end */
volatile uint8_t g_iic20_rx_end;                /* iic20 receive data end */
volatile uint8_t g_iic21_tx_end;                /* iic21 send data end */
volatile uint8_t g_iic21_rx_end;                /* iic21 receive data end */

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: uart0_interrupt_receive
* @brief  UART0 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart0_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    INTC_ClearPendingIRQ(SR0_IRQn);
    err_type = (uint8_t)(SCI0->SSR01 & 0x0007U);
    SCI0->SIR01 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart0_callback_error(err_type);
    }
    
    rx_data = SCI0->RXD0;

    if (g_uart0_rx_length > g_uart0_rx_count)
    {
        *gp_uart0_rx_address = rx_data;
        gp_uart0_rx_address++;
        g_uart0_rx_count++;

        if (g_uart0_rx_length == g_uart0_rx_count)
        {
            uart0_callback_receiveend();
        }
    }
    else
    {
        uart0_callback_softwareoverrun(rx_data);
    }
}
/***********************************************************************************************************************
* Function Name: uart0_interrupt_send
* @brief  UART0 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart0_interrupt_send(void)
{
    INTC_ClearPendingIRQ(ST0_IRQn);
    if (g_uart0_tx_count > 0U)
    {
        SCI0->TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
    }
    else
    {
        uart0_callback_sendend();
    }
}
/***********************************************************************************************************************
* Function Name: uart0_callback_receiveend
* @brief  This function is a callback function when UART0 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart0_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart0_callback_softwareoverrun
* @brief  This function is a callback function when UART0 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart0_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart0_callback_sendend
* @brief  This function is a callback function when UART0 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart0_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart0_callback_error
* @brief  This function is a callback function when UART0 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart0_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi00_interrupt
* @brief  SPI00 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi00_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    INTC_ClearPendingIRQ(SPI00_IRQn);
    err_type = (uint8_t)(SCI0->SSR00 & _0001_SCI_OVERRUN_ERROR);
    SCI0->SIR00 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi00_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi00_tx_count > 0U || g_spi00_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi00_rx_address)
            {
                *gp_spi00_rx_address = SCI0->SIO00;
                gp_spi00_rx_address++;
                g_spi00_rx_count--;
            }
            else
            {
                sio_dummy = SCI0->SIO00;
            }

            /* send data */
            if (0U != gp_spi00_tx_address)
            {
                SCI0->SIO00 = *gp_spi00_tx_address;
                gp_spi00_tx_address++;
                g_spi00_tx_count--;
            }
            else if((SCI0->SMR00 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI0->SIO00 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi00_rx_count)
            {
                while ((SCI0->SSR00 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != gp_spi00_rx_address)
                {
                    *gp_spi00_rx_address = SCI0->SIO00;
                     g_spi00_rx_count--;
                }
                else
                {
                    sio_dummy = SCI0->SIO00;
                }
                spi00_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi00_tx_address)
            {
                if (((SCI0->SMR00 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI0->SCR00 & _4000_SCI_RECEPTION) != 0))
                {
                    ; /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
                    {
                        ;
                    }
                }
                spi00_callback_sendend();    /* complete send */
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: spi00_callback_receiveend
* @brief  This function is a callback function when spi00 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi00_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    //SPI00_Stop();
    gp_spi00_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi00_callback_error
* @brief  This function is a callback function when spi00 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi00_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi00_callback_sendend
* @brief  This function is a callback function when spi00 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi00_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    gp_spi00_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi01_interrupt
* @brief  SPI01 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi01_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI0->SSR01 & _0001_SCI_OVERRUN_ERROR);
    SCI0->SIR01 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi01_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi01_tx_count > 0U || g_spi01_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi01_rx_address)
            {
                *gp_spi01_rx_address = SCI0->SIO01;
                gp_spi01_rx_address++;
                g_spi01_rx_count--;
            }
            else
            {
                sio_dummy = SCI0->SIO01;
            }

            /* send data */
            if (0U != gp_spi01_tx_address)
            {
                SCI0->SIO01 = *gp_spi01_tx_address;
                gp_spi01_tx_address++;
                g_spi01_tx_count--;
            }
            else if((SCI0->SMR01 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI0->SIO01 = 0xFFU;   // dummy write in master reception mode
            }

        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi01_rx_count)
            {
                while ((SCI0->SSR01 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != gp_spi01_rx_address)
                {
                    *gp_spi01_rx_address = SCI0->SIO01;
                     g_spi01_rx_count--;
                }
                else
                {
                    sio_dummy = SCI0->SIO01;
                }
                spi01_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi01_tx_address)
            {
                if (((SCI0->SMR01 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI0->SCR01 & _4000_SCI_RECEPTION) != 0))
                {
                    ; /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI0->SSR01 & _0040_SCI_UNDER_EXECUTE)
                    {
                        ;
                    }
                }
                spi01_callback_sendend();    /* complete send */
            }
        }
    }
    INTC_ClearPendingIRQ(SPI01_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi01_callback_receiveend
* @brief  This function is a callback function when spi01 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi01_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI01_Stop();
    gp_spi01_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi01_callback_error
* @brief  This function is a callback function when spi01 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi01_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi01_callback_sendend
* @brief  This function is a callback function when spi01 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi01_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI01_Stop();
    gp_spi01_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic00_interrupt
* @brief  IIC00 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
static void iic00_interrupt(void)
{
    if (((SCI0->SSR00 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic00_tx_count != 0U))
    {
        iic00_callback_master_error(MD_NACK);
    }
    else if(((SCI0->SSR00 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic00_tx_count != 0U))
    {
        iic00_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic00_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic00_tx_count > 0U)
            {
                SCI0->SIO00 = *gp_iic00_tx_address;
                gp_iic00_tx_address++;
                g_iic00_tx_count--;
            }
            else
            {
                IIC00_StopCondition();
                iic00_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic00_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
                SCI0->SCR00 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI0->SCR00 |= _4000_SCI_RECEPTION;
                SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
                g_iic00_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic00_rx_length == 1U)
                {
                    SCI0->SOE0 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                }
                
                SCI0->SIO00 = 0xFFU;
            }
            else
            {
                if (g_iic00_rx_count < g_iic00_rx_length)
                {
                    *gp_iic00_rx_address = SCI0->SIO00;
                    gp_iic00_rx_address++;
                    g_iic00_rx_count++;
                    
                    if (g_iic00_rx_count == (g_iic00_rx_length - 1U))
                    {
                        SCI0->SOE0 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                        SCI0->SIO00 = 0xFFU;
                    }
                    else if (g_iic00_rx_count == g_iic00_rx_length)
                    {
                        IIC00_StopCondition();
                        iic00_callback_master_receiveend();
                    }
                    else
                    {
                        SCI0->SIO00 = 0xFFU;
                    }
                }
            }
        }
    }
    INTC_ClearPendingIRQ(IIC00_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic00_callback_master_error
* @brief  This function is a callback function when IIC00 master error occurs.
* @param  flag - status flag
* @param  None
***********************************************************************************************************************/
static void iic00_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic00_callback_master_receiveend
* @brief  This function is a callback function when IIC00 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic00_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic00_rx_end = 1;
    IIC00_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic00_callback_master_sendend
* @brief  This function is a callback function when IIC00 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic00_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic00_tx_end = 1;
    IIC00_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic01_interrupt
* @brief  IIC01 interrupt service routine
* @param  None
* @param  None
***********************************************************************************************************************/
static void iic01_interrupt(void)
{
    if (((SCI0->SSR01 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic01_tx_count != 0U))
    {
        iic01_callback_master_error(MD_NACK);
    }
    else if(((SCI0->SSR01 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic01_tx_count != 0U))
    {
        iic01_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic01_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic01_tx_count > 0U)
            {
                SCI0->SIO01 = *gp_iic01_tx_address;
                gp_iic01_tx_address++;
                g_iic01_tx_count--;
            }
            else
            {
                IIC01_StopCondition();
                iic01_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic01_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI0->ST0 |= _0002_SCI_CH1_STOP_TRG_ON;
                SCI0->SCR01 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI0->SCR01 |= _4000_SCI_RECEPTION;
                SCI0->SS0 |= _0002_SCI_CH1_START_TRG_ON;
                g_iic01_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic01_rx_length == 1U)
                {
                    SCI0->SOE0 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                }
                
                SCI0->SIO01 = 0xFFU;
            }
            else
            {
                if (g_iic01_rx_count < g_iic01_rx_length)
                {
                    *gp_iic01_rx_address = SCI0->SIO01;
                    gp_iic01_rx_address++;
                    g_iic01_rx_count++;
                    
                    if (g_iic01_rx_count == (g_iic01_rx_length - 1U))
                    {
                        SCI0->SOE0 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                        SCI0->SIO01 = 0xFFU;
                    }
                    else if (g_iic01_rx_count == g_iic01_rx_length)
                    {
                        IIC01_StopCondition();
                        iic01_callback_master_receiveend();
                    }
                    else
                    {
                        SCI0->SIO01 = 0xFFU;
                    }
                }
            }
        }
    }
    INTC_ClearPendingIRQ(IIC01_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic01_callback_master_error
* @brief  This function is a callback function when IIC01 master error occurs.
* @param  flag - status flag
* @return None
***********************************************************************************************************************/
static void iic01_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic01_callback_master_receiveend
* @brief  This function is a callback function when IIC01 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic01_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic01_rx_end = 1;
    IIC01_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic01_callback_master_sendend
* @brief  This function is a callback function when IIC01 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic01_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic01_tx_end = 1;
    IIC01_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart1_interrupt_receive
* @brief  UART1 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart1_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    INTC_ClearPendingIRQ(SR1_IRQn);
    err_type = (uint8_t)(SCI0->SSR03 & 0x0007U);
    SCI0->SIR03 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart1_callback_error(err_type);
    }
    
    rx_data = SCI0->RXD1;

    if (g_uart1_rx_length > g_uart1_rx_count)
    {
        *gp_uart1_rx_address = rx_data;
        gp_uart1_rx_address++;
        g_uart1_rx_count++;

        if (g_uart1_rx_length == g_uart1_rx_count)
        {
            uart1_callback_receiveend();
        }
    }
    else
    {
        uart1_callback_softwareoverrun(rx_data);
    }
}
/***********************************************************************************************************************
* Function Name: uart1_interrupt_send
* @brief  UART1 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void uart1_interrupt_send(void)
{
    INTC_ClearPendingIRQ(ST1_IRQn);
    if (g_uart1_tx_count > 0U)
    {
        SCI0->TXD1 = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
    }
    else
    {
        uart1_callback_sendend();
    }
}
/***********************************************************************************************************************
* Function Name: uart1_callback_receiveend
* @brief  This function is a callback function when UART1 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart1_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart1_callback_softwareoverrun
* @brief  This function is a callback function when UART1 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart1_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart1_callback_sendend
* @brief  This function is a callback function when UART1 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart1_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart1_callback_error
* @brief  This function is a callback function when UART1 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart1_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi10_interrupt
* @brief  SPI10 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi10_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    INTC_ClearPendingIRQ(SPI10_IRQn);
    err_type = (uint8_t)(SCI0->SSR02 & _0001_SCI_OVERRUN_ERROR);
    SCI0->SIR02 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi10_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi10_tx_count > 0U || g_spi10_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi10_rx_address)
            {
                *gp_spi10_rx_address = SCI0->SIO10;
                gp_spi10_rx_address++;
                g_spi10_rx_count--;
            }
            else
            {
                sio_dummy = SCI0->SIO10;
            }

            /* send data */
            if (0U != gp_spi10_tx_address)
            {
                SCI0->SIO10 = *gp_spi10_tx_address;
                gp_spi10_tx_address++;
                g_spi10_tx_count--;
            }
            else if((SCI0->SMR02 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI0->SIO10 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi10_rx_count)
            {
                while ((SCI0->SSR02 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != gp_spi10_rx_address)
                {
                    *gp_spi10_rx_address = SCI0->SIO10;
                     g_spi10_rx_count--;
                }
                else
                {
                    sio_dummy = SCI0->SIO10;
                }
                spi10_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi10_tx_address)
            {
                if (((SCI0->SMR02 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI0->SCR02 & _4000_SCI_RECEPTION) != 0))
                {
                    ; /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI0->SSR02 & _0040_SCI_UNDER_EXECUTE)
                    {
                        ;
                    }
                }
                spi10_callback_sendend();    /* complete send */
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: spi10_callback_receiveend
* @brief  This function is a callback function when spi10 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi10_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    //SPI10_Stop();
    gp_spi10_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi10_callback_error
* @brief  This function is a callback function when spi10 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi10_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi10_callback_sendend
* @brief  This function is a callback function when spi10 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi10_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    gp_spi10_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi11_interrupt
* @brief  SPI11 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi11_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI0->SSR03 & _0001_SCI_OVERRUN_ERROR);
    SCI0->SIR03 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi11_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi11_tx_count > 0U || g_spi11_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi11_rx_address)
            {
                *gp_spi11_rx_address = SCI0->SIO11;
                gp_spi11_rx_address++;
                g_spi11_rx_count--;
            }
            else
            {
                sio_dummy = SCI0->SIO11;
            }

            /* send data */
            if (0U != gp_spi11_tx_address)
            {
                SCI0->SIO11 = *gp_spi11_tx_address;
                gp_spi11_tx_address++;
                g_spi11_tx_count--;
            }
            else if((SCI0->SMR03 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI0->SIO11 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi11_rx_count)
            {
                while ((SCI0->SSR03 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != gp_spi11_rx_address)
                {
                    *gp_spi11_rx_address = SCI0->SIO11;
                     g_spi11_rx_count--;
                }
                else
                {
                    sio_dummy = SCI0->SIO11;
                }
                spi11_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi11_tx_address)
            {
                if (((SCI0->SMR03 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI0->SCR03 & _4000_SCI_RECEPTION) != 0))
                {
                    ; /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI0->SSR03 & _0040_SCI_UNDER_EXECUTE)
                    {
                        ;
                    }
                }
                spi11_callback_sendend();    /* complete send */
            }
        }
    }
    INTC_ClearPendingIRQ(SPI11_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi11_callback_receiveend
* @brief  This function is a callback function when spi11 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi11_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI11_Stop();
    gp_spi11_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi11_callback_error
* @brief  This function is a callback function when spi11 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi11_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi11_callback_sendend
* @brief  This function is a callback function when spi11 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi11_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    SPI11_Stop();
    gp_spi11_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart2_interrupt_receive
* @brief  UART2 Receive interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
static void uart2_interrupt_receive(void)
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    INTC_ClearPendingIRQ(SR2_IRQn);
    err_type = (uint8_t)(SCI1->SSR11 & 0x0007U);
    SCI1->SIR11 = (uint16_t)err_type;

    if (err_type != 0U)
    {
        uart2_callback_error(err_type);
    }
    
    rx_data = SCI1->RXD2;

    if (g_uart2_rx_length > g_uart2_rx_count)
    {
        *gp_uart2_rx_address = rx_data;
        gp_uart2_rx_address++;
        g_uart2_rx_count++;

        if (g_uart2_rx_length == g_uart2_rx_count)
        {
            uart2_callback_receiveend();
        }
    }
    else
    {
        uart2_callback_softwareoverrun(rx_data);
    }
    INTC_ClearPendingIRQ(SR2_IRQn);     /* clear INTSR2 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: uart2_interrupt_send
* @brief  UART2 Send interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
static void uart2_interrupt_send(void)
{
    INTC_ClearPendingIRQ(ST2_IRQn);
    if (g_uart2_tx_count > 0U)
    {
        SCI1->TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
    }
    else
    {
        uart2_callback_sendend();
    }
    INTC_ClearPendingIRQ(ST2_IRQn);     /* clear INTST2 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_receiveend
* @brief  This function is a callback function when UART2 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart2_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_softwareoverrun
* @brief  This function is a callback function when UART2 receives an overflow data.
* @param  rx_data - receive data
* @return None
***********************************************************************************************************************/
static void uart2_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_sendend
* @brief  This function is a callback function when UART2 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void uart2_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: uart2_callback_error
* @brief  This function is a callback function when UART2 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void uart2_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi20_interrupt
* @brief  SPI20 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi20_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI1->SSR10 & _0001_SCI_OVERRUN_ERROR);
    SCI1->SIR10 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi20_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi20_tx_count > 0U || g_spi20_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi20_rx_address)
            {
                *gp_spi20_rx_address = SCI1->SIO20;
                gp_spi20_rx_address++;
                g_spi20_rx_count--;
            }
            else
            {
                sio_dummy = SCI1->SIO20;
            }

            /* send data */
            if (0U != gp_spi20_tx_address)
            {
                SCI1->SIO20 = *gp_spi20_tx_address;
                gp_spi20_tx_address++;
                g_spi20_tx_count--;
            }
            else if((SCI1->SMR10 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI1->SIO20 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi20_rx_count)
            {
                while ((SCI1->SSR10 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != gp_spi20_rx_address)
                {
                    *gp_spi20_rx_address = SCI1->SIO20;
                     g_spi20_rx_count--;
                }
                else
                {
                    sio_dummy = SCI1->SIO20;
                }
                spi20_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi20_tx_address)
            {
                if (((SCI1->SMR10 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI1->SCR10 & _4000_SCI_RECEPTION) != 0))
                {
                    ; /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI1->SSR10 & _0040_SCI_UNDER_EXECUTE)
                    {
                        ;
                    }
                }
                spi20_callback_sendend();    /* complete send */
            }
        }
    }
    INTC_ClearPendingIRQ(SPI20_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi20_callback_receiveend
* @brief  This function is a callback function when spi20 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi20_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    //SPI20_Stop();
    gp_spi20_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi20_callback_error
* @brief  This function is a callback function when spi20 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi20_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi20_callback_sendend
* @brief  This function is a callback function when spi20 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi20_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    gp_spi20_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi21_interrupt
* @brief  SPI21 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi21_interrupt(void)
{
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SCI1->SSR11 & _0001_SCI_OVERRUN_ERROR);
    SCI1->SIR11 = (uint16_t)err_type;

    if (1U == err_type)
    {
        spi21_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_spi21_tx_count > 0U || g_spi21_rx_count > 1U)
        {
            /* reveive data */
            if (0U != gp_spi21_rx_address)
            {
                *gp_spi21_rx_address = SCI1->SIO21;
                gp_spi21_rx_address++;
                g_spi21_rx_count--;
            }
            else
            {
                sio_dummy = SCI1->SIO21;
            }

            /* send data */
            if (0U != gp_spi21_tx_address)
            {
                SCI1->SIO21 = *gp_spi21_tx_address;
                gp_spi21_tx_address++;
                g_spi21_tx_count--;
            }
            else if((SCI1->SMR11 & _4000_SCI_CLOCK_MODE_TI0N) == 0)
            {
                SCI1->SIO21 = 0xFFU;   // dummy write in master reception mode
            }
        }
        else 
        {
            /* receive the last data */
            if (1U == g_spi21_rx_count)
            {
                while ((SCI1->SSR11 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != gp_spi21_rx_address)
                {
                    *gp_spi21_rx_address = SCI1->SIO21;
                     g_spi21_rx_count--;
                }
                else
                {
                    sio_dummy = SCI1->SIO21;
                }
                spi21_callback_receiveend();    /* complete receive */
            }
            /* wait the last data sent for DMA transfer in master mode */
            if (0U != gp_spi21_tx_address)
            {
                if (((SCI1->SMR11 & _4000_SCI_CLOCK_MODE_TI0N) != 0) && ((SCI1->SCR11 & _4000_SCI_RECEPTION) != 0))
                {
                    ; /* Do not wait in slave transceiver mode */
                }
                else
                {
                    while (SCI1->SSR11 & _0040_SCI_UNDER_EXECUTE)
                    {
                        ;
                    }
                }
                spi21_callback_sendend();    /* complete send */
            }
        }
    }
    INTC_ClearPendingIRQ(SPI21_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi21_callback_receiveend
* @brief  This function is a callback function when spi21 finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi21_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    //SPI21_Stop();
    gp_spi21_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi21_callback_error
* @brief  This function is a callback function when spi21 reception error occurs.
* @param  err_type - error type value
* @return None
***********************************************************************************************************************/
static void spi21_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi21_callback_sendend
* @brief  This function is a callback function when spi21 finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi21_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    gp_spi21_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic20_interrupt
* @brief  IIC20 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
static void iic20_interrupt(void)
{
    if (((SCI1->SSR10 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic20_tx_count != 0U))
    {
        iic20_callback_master_error(MD_NACK);
    }
    else if(((SCI1->SSR10 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic20_tx_count != 0U))
    {
        iic20_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic20_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic20_tx_count > 0U)
            {
                SCI1->SIO20 = *gp_iic20_tx_address;
                gp_iic20_tx_address++;
                g_iic20_tx_count--;
            }
            else
            {
                IIC20_StopCondition();
                iic20_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic20_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI1->ST1 |= _0001_SCI_CH0_STOP_TRG_ON;
                SCI1->SCR10 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI1->SCR10 |= _4000_SCI_RECEPTION;
                SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;
                g_iic20_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic20_rx_length == 1U)
                {
                    SCI1->SOE1 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                }
                
                SCI1->SIO20 = 0xFFU;
            }
            else
            {
                if (g_iic20_rx_count < g_iic20_rx_length)
                {
                    *gp_iic20_rx_address = SCI1->SIO20;
                    gp_iic20_rx_address++;
                    g_iic20_rx_count++;
                    
                    if (g_iic20_rx_count == (g_iic20_rx_length - 1U))
                    {
                        SCI1->SOE1 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
                        SCI1->SIO20 = 0xFFU;
                    }
                    else if (g_iic20_rx_count == g_iic20_rx_length)
                    {
                        IIC20_StopCondition();
                        iic20_callback_master_receiveend();
                    }
                    else
                    {
                        SCI1->SIO20 = 0xFFU;
                    }
                }
            }
        }
    }
    INTC_ClearPendingIRQ(IIC20_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic20_callback_master_error
* @brief  This function is a callback function when IIC20 master error occurs.
* @param  flag - status flag
* @param  None
***********************************************************************************************************************/
static void iic20_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic20_callback_master_receiveend
* @brief  This function is a callback function when IIC20 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic20_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic20_rx_end = 1;
    IIC20_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic20_callback_master_sendend
* @brief  This function is a callback function when IIC20 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic20_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic20_tx_end = 1;
    IIC20_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic21_interrupt
* @brief  IIC21 interrupt service routine
* @param  None
* @param  None
***********************************************************************************************************************/
static void iic21_interrupt(void)
{
    if (((SCI1->SSR11 & _0002_SCI_PARITY_ERROR) == 0x0002U) && (g_iic21_tx_count != 0U))
    {
        iic21_callback_master_error(MD_NACK);
    }
    else if(((SCI1->SSR11 & _0001_SCI_OVERRUN_ERROR) == 0x0001U) && (g_iic21_tx_count != 0U))
    {
        iic21_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic21_master_status_flag & _01_SCI_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic21_tx_count > 0U)
            {
                SCI1->SIO21 = *gp_iic21_tx_address;
                gp_iic21_tx_address++;
                g_iic21_tx_count--;
            }
            else
            {
                IIC21_StopCondition();
                iic21_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic21_master_status_flag & _04_SCI_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                SCI1->ST1 |= _0002_SCI_CH1_STOP_TRG_ON;
                SCI1->SCR11 &= (uint16_t)~(_C000_SCI_RECEPTION_TRANSMISSION);
                SCI1->SCR11 |= _4000_SCI_RECEPTION;
                SCI1->SS1 |= _0002_SCI_CH1_START_TRG_ON;
                g_iic21_master_status_flag |= _04_SCI_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic21_rx_length == 1U)
                {
                    SCI1->SOE1 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                }
                
                SCI1->SIO21 = 0xFFU;
            }
            else
            {
                if (g_iic21_rx_count < g_iic21_rx_length)
                {
                    *gp_iic21_rx_address = SCI1->SIO21;
                    gp_iic21_rx_address++;
                    g_iic21_rx_count++;
                    
                    if (g_iic21_rx_count == (g_iic21_rx_length - 1U))
                    {
                        SCI1->SOE1 &= (uint16_t)~_0002_SCI_CH1_OUTPUT_ENABLE;
                        SCI1->SIO21 = 0xFFU;
                    }
                    else if (g_iic21_rx_count == g_iic21_rx_length)
                    {
                        IIC21_StopCondition();
                        iic21_callback_master_receiveend();
                    }
                    else
                    {
                        SCI1->SIO21 = 0xFFU;
                    }
                }
            }
        }
    }
    INTC_ClearPendingIRQ(IIC21_IRQn);
}
/***********************************************************************************************************************
* Function Name: iic21_callback_master_error
* @brief  This function is a callback function when IIC21 master error occurs.
* @param  flag - status flag
* @return None
***********************************************************************************************************************/
static void iic21_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic21_callback_master_receiveend
* @brief  This function is a callback function when IIC21 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic21_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic21_rx_end = 1;
    IIC21_Stop();
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iic21_callback_master_sendend
* @brief  This function is a callback function when IIC21 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iic21_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iic21_tx_end = 1;
    IIC21_Stop();
    /* End user code. Do not edit comment generated here */
}
