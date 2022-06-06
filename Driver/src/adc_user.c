/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc_user.c
* @brief   This file implements device driver for ADC module.
* @version 1.0.0 
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ21_Handler(void) __attribute__((alias("adc_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t  * gp_u1_adc_buf;           /* adc higher 8 bit result buffer address */
volatile uint16_t * gp_u2_adc_buf;           /* adc 12 bit result buffer address */
volatile uint32_t   g_AdcIntTaken;           /* adc interrupt flag */
volatile int16_t    g_temperature = 25;        /* chip temperature */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: adc_interrupt
* @brief  ADC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void adc_interrupt(void)
{
    INTC_ClearPendingIRQ(ADC_IRQn);     /* clear INTAD interrupt flag */
    /* Start user code. Do not edit comment generated here */
    *gp_u1_adc_buf++ = ADC->ADCRH;
    *gp_u2_adc_buf++ = ADC->ADCR;
    g_AdcIntTaken++;
    g_temperature = adc_get_temperature(ADC->ADCR);
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: adc_get_temperature
* @brief  ADC Get temperature
* @param  dat - the adc conversion value of ADC_TEMPERSENSOR0 channel
* @return temperature
***********************************************************************************************************************/
#if 0
double adc_get_temperature(int16_t dat)
{
    double temp;    /* temperature value */

    temp = (double)(TSN->TSN25 - dat) * 60 / (TSN->TSN25 - TSN->TSN85) + 25; /* 12bit dat */

    return (temp);
}
#else
int16_t adc_get_temperature(int16_t dat)
{
    int16_t temp;   /* temperature value */

    temp = (int16_t)(TSN->TSN25 - dat) * 60 / (TSN->TSN25 - TSN->TSN85) + 25; /* 12bit dat */

    return (temp);
}
#endif

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
