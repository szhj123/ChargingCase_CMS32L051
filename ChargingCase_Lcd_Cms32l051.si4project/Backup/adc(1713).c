/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc.c
* @brief   This file implements device driver for ADC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions 
***********************************************************************************************************************/
#define ADC_OPERMODE_SELECT     /* ADC Operation mode: select mode */
#define ADC_TRIGGER_SOFTWARE    /* ADC Trigger: software trigger */
#define ADC_CONVMODE_ONESHOT    /* ADC Conversion mode: one-shot */
#define ADC_VREF_VDD_VSS        /* ADC reference voltage: VDD/VSS */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "userdefine.h"
#include "adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: ADC_Init
* @brief  This function initializes the AD converter.
* @param  None
* @return None
***********************************************************************************************************************/
void ADC_Init(void)
{
    INTC_DisableIRQ(ADC_IRQn);          /* disable INTAD interrupt */
    CGC->PER0 |= CGC_PER0_ADCEN_Msk;    /* enables input clock supply */
    ADC->ADM0  = 0x00U;                 /* disable AD conversion and clear ADM0 register */
    INTC_ClearPendingIRQ(ADC_IRQn);     /* clear INTAD interrupt flag */
    NVIC_ClearPendingIRQ(ADC_IRQn);     /* clear INTAD interrupt flag */

    ADC_PORT_SETTING();

    /* AD operation mode: select or scan mode  */
    ADC->ADM0 = _10_AD_CONVERSION_CLOCK_8 | _00_AD_COMPARATOR_DISABLE;
    //ADC->ADM0 = _28_AD_CONVERSION_CLOCK_1 | _00_AD_COMPARATOR_DISABLE;

    /* AD conversion mode setting */
    ADC->ADM1 = _00_AD_HISPEED;
#ifdef ADC_OPERMODE_SELECT     
    ADC->ADM1 |= _00_AD_OPERMODE_SELECT;
#endif
#ifdef ADC_OPERMODE_SCAN     
    ADC->ADM1 |= _80_AD_OPERMODE_SCAN;
#endif

#ifdef ADC_CONVMODE_SEQUENTIAL
    ADC->ADM1 |= _00_AD_CONVMODE_SEQUENTIAL;
#endif
#ifdef ADC_CONVMODE_ONESHOT
    ADC->ADM1 |= _08_AD_CONVMODE_ONESHOT;
#endif

    /* AD reference voltage setting */
#ifdef ADC_VREF_VDD_VSS
    ADC->ADM2 = _00_AD_POSITIVE_VDD | _00_AD_NEGATIVE_VSS | _00_AD_AREA_MODE_1 ;
#endif
#ifdef ADC_VREF_AVREFP_AVREFM
    ADC->ADM2 = _40_AD_POSITIVE_AVREFP | _20_AD_NEGATIVE_AVREFM | _00_AD_AREA_MODE_1 ;
#endif

    /* AD trigger selection */
#ifdef ADC_TRIGGER_SOFTWARE
    ADC->ADTRG = _00_AD_TRIGGER_SOFTWARE;
#endif
#ifdef ADC_TRIGGER_HARDWARE_NOWAIT
    ADC->ADTRG = _80_AD_TRIGGER_HARDWARE_NOWAIT;
#endif
#ifdef ADC_TRIGGER_HARDWARE_WAIT
    ADC->ADTRG = _C0_AD_TRIGGER_HARDWARE_WAIT;
#endif

    /* AD comversion result comprision upper limit setting */
    ADC->ADUL = _FF_AD_ADUL_VALUE;
    /* AD comversion result comprision lower limit setting */
    ADC->ADLL = _00_AD_ADLL_VALUE;

    /* adhard power up */
    ADC->ADM0 |= ADCE;  
}
/***********************************************************************************************************************
* Function Name: ADC_Set_OperationOn
* @brief  This function enables comparator operation.
* @param  None
* @return None
***********************************************************************************************************************/
void ADC_Set_OperationOn(void)
{
    ADC->ADM0 |= ADCE;      /* enables A/D voltage comparator operation */
}
/***********************************************************************************************************************
* Function Name: ADC_Set_OperationOff
* @brief  This function stops comparator operation.
* @param  None
* @return None
***********************************************************************************************************************/
void ADC_Set_OperationOff(void)
{
    ADC->ADM0 &= ~ADCE;      /* stops A/D voltage comparator operation */
}
/***********************************************************************************************************************
* Function Name: ADC_Start
* @brief  This function starts the AD converter.
* @param  ch - specify the conversion channel
* @return None
***********************************************************************************************************************/
void ADC_Start(adc_channel_t ch)
{
    ADC->ADS = ch;
    INTC_ClearPendingIRQ(ADC_IRQn); /* clear INTAD interrupt flag */
    NVIC_ClearPendingIRQ(ADC_IRQn); /* clear INTAD interrupt flag */
    INTC_EnableIRQ(ADC_IRQn);       /* enable INTAD interrupt */

	if((ADC->ADTRG >> 6) != 3) 			/* write ADCS except for hardwait mode */
	{
		ADC->ADM0 |= ADCS;            /* enables conversion operation */
	}
}
/***********************************************************************************************************************
* Function Name: ADC_Stop
* @brief  This function stops the AD converter.
* @param  None
* @return None
***********************************************************************************************************************/
void ADC_Stop(void)
{
    ADC->ADM0 &= ~ADCS;             /* stops conversion operation */
    INTC_DisableIRQ(ADC_IRQn);      /* disable INTAD interrupt */
    INTC_ClearPendingIRQ(ADC_IRQn); /* clear INTAD interrupt flag */
    NVIC_ClearPendingIRQ(ADC_IRQn); /* clear INTAD interrupt flag */
}
/***********************************************************************************************************************
* Function Name: ADC_Set_HardTrigger
* @brief  This function sets the trigger of AD converter.
* @param  wait - 0: NoWait; 1: Wait
* @param  trg - select the hard trigger signal
* @return None
***********************************************************************************************************************/
void ADC_Set_HardTrigger(uint8_t wait, adc_trigger_t trg)
{
    ADC->ADM0 &= ~ADCE;
    if(wait == 0)
    {
        ADC->ADTRG = _80_AD_TRIGGER_HARDWARE_NOWAIT | trg;
    }
    else
    {
        ADC->ADTRG = _C0_AD_TRIGGER_HARDWARE_WAIT   | trg;
    }
    ADC->ADM0 |= ADCE;
}
/***********************************************************************************************************************
* Function Name: ADC_Set_Clock
* @brief  This function sets the operation clock of AD converter.
* @param  fr - specify the value of FR0~2 in ADM0 register
* @param  smp - specify the sample clock number of AD converter
* @return None
***********************************************************************************************************************/
void ADC_Set_Clock(adc_clock_t fr, uint8_t smp)
{
	ADC->ADM0 &= ~(7 << FR_Pos);
	ADC->ADM0 |= fr << FR_Pos;
}
/***********************************************************************************************************************
* Function Name: ADC_Converse
* @brief  This function starts the AD converter and returns the conversion result in the buf
*         It is suitable for software trigger mode with polling mode.
* @param  ch - specify the ad channel
* @param  sz - set the times of ad conversion
* @param  buf - the address where to write the conversion result
* @return average value
***********************************************************************************************************************/
uint16_t ADC_Converse(adc_channel_t ch, uint32_t sz, uint16_t *buf)
{
    uint32_t i;
    volatile uint8_t  flag;
    uint32_t total = 0;
   
    INTC_DisableIRQ(ADC_IRQn);     /* disable INTAD interrupt */
//-----------------------------------------------------------------------
// normal mode
//-----------------------------------------------------------------------
    /* Soft Trigger one-shot select mode */
	ADC->ADM0 &= ~ADCE;
    ADC->ADM1 = _08_AD_CONVMODE_ONESELECT ;
    ADC->ADTRG = _00_AD_TRIGGER_SOFTWARE;
    ADC->ADM0 |= ADCE;
	
    /* specify ad channel */
    ADC->ADS  = ch; 
    
    /* Execute ADC converse and get the conversion result */
    for (i=0; i<sz; i++)
    {
        /* ADC start */
        ADC->ADM0 |= ADCS; 

        /* waiting interrupt flag */
        while(INTC_GetPendingIRQ(ADC_IRQn) == 0);
        INTC_ClearPendingIRQ(ADC_IRQn);     /* clear INTAD interrupt flag */

        /* Get the conversion result */
        *buf++ = ADC->ADCR;
        /* Calculate the total value of the conversion result */
        total += ADC->ADCR;
    } 
    
    return (total / sz); // return average value
}

/***********************************************************************************************************************
* Function Name: ADC_MidAvg_Filter
* @brief  This function gets the middle average of middle values of the AD results.  
* @param  buf - the pointer of the conversion result
* @param  num - set the numbers of ad conversion result
* @return average
***********************************************************************************************************************/
uint16_t ADC_MidAvg_Filter(uint16_t *buf, uint8_t num)
{
    uint8_t i, j;
    uint16_t tmp;
    uint32_t sum;

    /* sort the value from small to large */
    for(i = 0; i < num; i++)
    {
        for(j = 0; j < ((num - 1) - i); j++)
        {
            if(buf[j] > buf[j + 1])
            {
                tmp = buf[j];
                buf[j] = buf[j + 1];
                buf[j + 1] = tmp;
            }
        }
    }

    /* Remove the smallest and largest values, then take the average */
    sum = 0;
    for(i = 2; i < (num - 2); i++)
    {
        sum += buf[i];
    }
    tmp = (uint16_t) (sum / (num - 4));

    return (tmp);
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

