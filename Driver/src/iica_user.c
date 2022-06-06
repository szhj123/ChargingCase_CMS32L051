/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    iica_user.c
* @brief   This file implements device driver for IICA module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "CMS32L051.h"
#include "iica.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ16_Handler(void) __attribute__((alias("iica0_interrupt")));

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: iica0_interrupt
* @brief  IICA interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void iica0_interrupt(void)
{
    INTC_ClearPendingIRQ(IICA_IRQn);
    IICA0_Clear_Wakeup();
    if ((IICA->IICS0 & _80_IICA_MASTER_DEVICE) == 0x80U)
    {
        iica0_masterhandler();
    }
    else
    {
        iica0_slavehandler();
    }
}
/***********************************************************************************************************************
* Function Name: iica0_masterhandler
* @brief  This function is IICA0 master handler.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_masterhandler(void)
{
    /* Control for communication */
    if ((0U == (IICA->IICF0 & IICA_IICF0_IICBSY_Msk)) && (g_iica0_tx_cnt != 0U))
    {
        iica0_callback_master_error(MD_SPT);
    }
    /* Control for sended address */
    else
    {
        if ((g_iica0_master_status_flag & _80_IICA_ADDRESS_COMPLETE) == 0U)
        {
            if (IICA->IICS0 & IICA_IICS0_ACKD_Msk)
            {
                g_iica0_master_status_flag |= _80_IICA_ADDRESS_COMPLETE;

                if (IICA->IICS0 & IICA_IICS0_TRC_Msk)
                {
                    IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;     /* interrupt request is generated at the ninth clock's falling edge */

                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        iica0_callback_master_sendend();
                    }
                }
                else
                {
                    IICA->IICCTL00 |= IICA_IICCTL00_ACKE_Msk;     /* enable acknowledgment */
                    IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;    /* interrupt request is generated at the eighth clock's falling edge */
                    IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;     /* cancel wait */
                }
            }
            else
            {
                iica0_callback_master_error(MD_NACK);
            }
        }
        else
        {
            /* Master send control */
            if (IICA->IICS0 & IICA_IICS0_TRC_Msk)
            {
                if ((0U == (IICA->IICS0 & IICA_IICS0_ACKD_Msk)) && (g_iica0_tx_cnt != 0U))
                {
                    iica0_callback_master_error(MD_NACK);
                }
                else
                {
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        iica0_callback_master_sendend();
                    }
                }
            }
            /* Master receive control */
            else
            {
                if (g_iica0_rx_cnt < g_iica0_rx_len)
                {
                    *gp_iica0_rx_address = IICA->IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;

                    if (g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        IICA->IICCTL00 &= ~IICA_IICCTL00_ACKE_Msk;   /* disable acknowledgment */
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;    /* cancel wait */
                        IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;    /* interrupt request is generated at the eighth clock's falling edge */
                    }
                    else
                    {
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;     /* cancel wait */
                    }
                }
                else
                {
                    iica0_callback_master_receiveend();
                }
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: iica0_callback_master_error
* @brief  This function is a callback function when IICA0 master error occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_master_receiveend
* @brief  This function is a callback function when IICA0 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_master_receiveend(void)
{
    IICA->IICCTL00 |= IICA_IICCTL00_SPT_Msk;            /* stop condition is generated */
    while(0U == (IICA->IICS0 & IICA_IICS0_SPD_Msk));    /* stop condition is detected */

    /* Start user code. Do not edit comment generated here */
        g_iica0_rx_end = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_master_sendend
* @brief  This function is a callback function when IICA0 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_master_sendend(void)
{
    IICA->IICCTL00 |= IICA_IICCTL00_SPT_Msk;            /* stop condition is generated */
    while(0U == (IICA->IICS0 & IICA_IICS0_SPD_Msk));    /* stop condition is detected */
    /* Start user code. Do not edit comment generated here */
    g_iica0_tx_end = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: iica0_slavehandler
* @brief  This function is IICA0 slave handler.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_slavehandler(void)
{
    /* Control for stop condition */
    if (IICA->IICS0 & IICA_IICS0_SPD_Msk)
    {
        /* Get stop condition */
        IICA->IICCTL00 &= ~IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 0: disable */
        if(g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE)
        {
            if (g_iica0_slave_status_flag & 0x04U)   /* send flag */
            {
                iica0_callback_slave_sendend();
            }
            if (g_iica0_slave_status_flag & 0x02U)   /* receive flag */
            {
                iica0_callback_slave_receiveend();
            }
        }
        g_iica0_slave_status_flag = 1U;
    }
    else
    {
        if ((g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE) == 0U)
        {
            if (IICA->IICS0 & IICA_IICS0_COI_Msk)
            {
                IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */
                //g_iica0_slave_status_flag |= _80_IICA_ADDRESS_COMPLETE;
                g_iica0_slave_status_flag = _80_IICA_ADDRESS_COMPLETE;

                if (IICA->IICS0 & IICA_IICS0_TRC_Msk)  /* TRC0 == 1 */
                {
                    IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;  /* WTIM0 = 1:  interrupt request is generated at the ninth clock's falling edge */

                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        iica0_callback_slave_sendend();
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;  /* WREL0 = 1U: cancel wait */
                    }
                }
                else
                {
                    IICA->IICCTL00 |=  IICA_IICCTL00_ACKE_Msk;   /* ACKE0 = 1U: enable acknowledgment */
                    IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;   /* WTIM0 = 0U: interrupt request is generated at the eighth clock's falling edge */
                    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                }
            }
            else
            {
                iica0_callback_slave_error(MD_ERROR);
            }
        }
        else
        {
            if (IICA->IICS0 & IICA_IICS0_TRC_Msk)  /* TRC0 == 1 */
            {
                g_iica0_slave_status_flag |= 4U;   /* send flag */
                if ((0U == (IICA->IICS0 & IICA_IICS0_ACKD_Msk)) && (g_iica0_tx_cnt != 0U))
                {
                    iica0_callback_slave_error(MD_NACK);
                }
                else
                {
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        iica0_callback_slave_sendend();
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;  /* WREL0 = 1U: cancel wait */
                    }
                }
            }
            else
            {
                g_iica0_slave_status_flag |= 2U;  /* receive flag */
                if (g_iica0_rx_cnt < g_iica0_rx_len)
                {
                    *gp_iica0_rx_address = IICA->IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;

                    if (g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;   /* WTIM0 = 1:  interrupt request is generated at the ninth clock's falling edge */
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                        iica0_callback_slave_receiveend();
                    }
                    else
                    {
                        IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                    }
                }
                else
                {
                    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                }
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: iica0_callback_slave_error
* @brief  This function is a callback function when IICA0 slave error occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_slave_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */   
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_slave_receiveend
* @brief  This function is a callback function when IICA0 finishes slave reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_slave_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iica0_rx_end = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_slave_sendend
* @brief  This function is a callback function when IICA0 finishes slave transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_slave_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iica0_tx_end = 1;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
