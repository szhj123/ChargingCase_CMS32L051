/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    intp_user.c
* @brief   This file implements device driver for INTP module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "CMS32L051.h"
#include "intp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ01_Handler(void) __attribute__((alias("intp_0_interrupt")));
void IRQ02_Handler(void) __attribute__((alias("intp_1_interrupt")));
void IRQ03_Handler(void) __attribute__((alias("intp_2_interrupt")));
void IRQ04_Handler(void) __attribute__((alias("intp_3_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint32_t g_intp0Taken;  	/* INTP0 taken */
volatile uint32_t g_intp1Taken;  	/* INTP1 taken */
volatile uint32_t g_intp2Taken;  	/* INTP2 taken */
volatile uint32_t g_intp3Taken;  	/* INTP3 taken */

/***********************************************************************************************************************
* Function Name: intp_0_interrupt
* @brief  INTP0 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_0_interrupt(void)
{

    INTC_ClearPendingIRQ(INTP0_IRQn);
    intp0_callback();   

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp0_callback
* @brief  This function is a callback function when INTP0 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp0_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp0Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp_1_interrupt
* @brief  INTP1 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_1_interrupt(void)
{
    INTC_ClearPendingIRQ(INTP1_IRQn);
    intp1_callback();   

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp1_callback
* @brief  This function is a callback function when INTP1 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp1_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp1Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp_2_interrupt
* @brief  INTP2 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_2_interrupt(void)
{
    INTC_ClearPendingIRQ(INTP2_IRQn);
    intp2_callback();   

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp2_callback
* @brief  This function is a callback function when INTP2 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp2_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp2Taken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp_3_interrupt
* @brief  INTP3 interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void intp_3_interrupt(void)
{
    INTC_ClearPendingIRQ(INTP3_IRQn);
    intp3_callback();   

    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: intp3_callback
* @brief  This function is a callback function when INTP3 interrupt occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void intp3_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_intp3Taken++;
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
