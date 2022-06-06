/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    pga.c
* @brief   This file implements device driver for PGA module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "pga.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

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
* Function Name: PGA_Init
* @brief  This function initializes the Programmable Gain Amplifier module.
* @param  ch - specify the pga channel number
*            1: pga0; 2: pga1; 3: pga0&1
* @param  vref - GND selection of feedback resistance
* @param  gain - Programmable gain amplifier amplification factor selection
* @param  pgaoen - Enable PGAOUT output to port.
* @return None
***********************************************************************************************************************/
void PGA_Init(pga_channel_t ch, pga_vref_t vref, pga_gain_t gain, uint8_t pgaoen)
{
    CGC->PER1 |= CGC_PER1_PGACMPEN_Msk;    /* enables input clock supply */
    TESOPT = 0x3DU; 

    if(ch & 0x01) 
    {
        PGA->PGA0CTL = 0x00U;     /* PGA operation stopped */
        PGA->PGA0CTL = vref << 3 | gain;
        TESCTL &= ~(1 << 0);      /* PGAO0 output disable */ 
        TESCTL |= pgaoen << 0;    /* PGAO0 output enable */ 
        /* Set PGA0 pin */
        PGA0IN_PORT_SETTING();
        if(vref == PGA_PGAGND_REFERENCE_VOLTAGE)
        {
            PGA0GND_PORT_SETTING();
        }
        if(pgaoen)
        {
            PGA0O_PORT_SETTING();
        }
    }

    if(ch & 0x02) 
    {
        PGA->PGA1CTL = 0x00U;     /* PGA operation stopped */
        PGA->PGA1CTL = vref<< 3 | gain;
        TESCTL &= ~(1 << 1);      /* PGAO1 output disable */ 
        TESCTL |= pgaoen << 1;    /* PGAO1 output enable */ 
        /* Set PGA1 pin */
        PGA1IN_PORT_SETTING();
        if(vref == PGA_PGAGND_REFERENCE_VOLTAGE)
        {
            PGA1GND_PORT_SETTING();
        }
        if(pgaoen)
        {
            PGA1O_PORT_SETTING();
        }
    }
}

/***********************************************************************************************************************
* Function Name: PGA_Start
* @brief  This function starts the  programmable gain amplifier.
* @param  ch - specify the pga channel number
*            1: pga0; 2: pga1; 3: pga0&1
* @return None
***********************************************************************************************************************/
void PGA_Start(pga_channel_t ch)
{     
    if(ch & 0x01) 
    {
        PGA->PGA0CTL |= PGAEN;     /* PGA0 operation enabled */
    }
    if(ch & 0x02) 
    {
        PGA->PGA1CTL |= PGAEN;     /* PGA1 operation enabled */
    }
}
/***********************************************************************************************************************
* Function Name: PGA_Stop
* @brief  This function stops the  programmable gain amplifier.
* @param  ch - specify the pga channel number
*            1: pga0; 2: pga1; 3: pga0&1
* @return None
***********************************************************************************************************************/
void PGA_Stop(pga_channel_t ch)
{
    if(ch & 0x01) 
    {
        PGA->PGA0CTL &= ~PGAEN;     /* PGA0 operation stopped */
    }
    if(ch & 0x02) 
    {
        PGA->PGA1CTL &= ~PGAEN;     /* PGA1 operation stopped */
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
