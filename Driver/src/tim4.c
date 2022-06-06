/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    tim4.c
* @brief   This file implements device driver for TM4 module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "userdefine.h"
#include "tim4.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TM40_ch1 pulse measurement */

/***********************************************************************************************************************
* Function Name: TM40_IntervalTimer
* @brief  TM40 specified channel operates as interval timer mode.
* @param  ch - specify the channel number
* @param  num - specify the number count clock
* @return None
***********************************************************************************************************************/
void TM40_IntervalTimer(tm4_channel_t ch, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _00F0_TM4_CKM1_fCLK_15 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used as interval timer */
            TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR00 = num - 1;
            TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used as interval timer */
            TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR01 = num - 1;
            TM40->TOE0 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM01_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used as interval timer */
            TM40->TMR02 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR02 = num - 1;
            TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM02_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used as interval timer */
            TM40->TMR03 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR03 = num - 1;
            TM40->TOE0 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM03_IRQn);
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM40_Channel_Start(ch);

#if 0   
    /* polling INTTMmn interrupt flag */
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            while(INTC_GetPendingIRQ(TM00_IRQn) == 0);
            INTC_ClearPendingIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_1:
            while(INTC_GetPendingIRQ(TM01_IRQn) == 0);
            INTC_ClearPendingIRQ(TM01_IRQn);
            break;
        case TM4_CHANNEL_2:
            while(INTC_GetPendingIRQ(TM02_IRQn) == 0);
            INTC_ClearPendingIRQ(TM02_IRQn);
            break;
        case TM4_CHANNEL_3:
            while(INTC_GetPendingIRQ(TM03_IRQn) == 0);
            INTC_ClearPendingIRQ(TM03_IRQn);
            break;
        default: 
            break;
    }

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
#endif  
}
/***********************************************************************************************************************
* Function Name: TM40_SquareOutput
* @brief  TM40 specified channel operates as square wave output mode.
* @param  ch - specify the channel number
* @param  num - specify the number of count clock 
* @return None
***********************************************************************************************************************/
void TM40_SquareOutput(tm4_channel_t ch, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used as interval timer */
            TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR00 = num - 1;
            TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM40->TOE0 |=  _0001_TM4_CH0_OUTPUT_ENABLE;
            TO00_PORT_SETTING();
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used as interval timer */
            TM40->TMR01 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR01 = num - 1;
            TM40->TOM0 &= ~_0002_TM4_CH1_SLAVE_OUTPUT;
            TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;
            TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;
            TO01_PORT_SETTING();
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used as interval timer */
            TM40->TMR02 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR02 = num - 1;
            TM40->TOM0 &= ~_0004_TM4_CH2_SLAVE_OUTPUT;
            TM40->TOL0 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;
            TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM40->TOE0 |=  _0004_TM4_CH2_OUTPUT_ENABLE;
            TO02_PORT_SETTING();
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used as interval timer */
            TM40->TMR03 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM40->TDR03 = num - 1;
            TM40->TOM0 &= ~_0008_TM4_CH3_SLAVE_OUTPUT;
            TM40->TOL0 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;
            TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM40->TOE0 |=  _0008_TM4_CH3_OUTPUT_ENABLE;
            TO03_PORT_SETTING();
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM40_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM40_FreqDivider
* @brief  TM40 specified channel operates as frequency divider mode.
* @param  ch - specify the channel number
* @param  edge - specify the input edge of TI
* @param  num - specify the number of divider
* @return None
***********************************************************************************************************************/
void TM40_FreqDivider(tm4_channel_t ch, tm4_edge_t edge, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    if(ch == TM4_CHANNEL_0) 
    {
        /* clear interrupt flag */
        INTC_ClearPendingIRQ(TM00_IRQn);
        NVIC_ClearPendingIRQ(TM00_IRQn);
        /* Channel 0 is used as interval timer */
        TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                      (edge << TMRMN_CIS_Pos) | _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
        if(edge == TM4_TI_BOTHEDGE)
        {
            TM40->TDR00 = num - 1;
        }
        else
        {
            TM40->TDR00 = num / 2 - 1;
        }
        TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
        TM40->TOE0 |=  _0001_TM4_CH0_OUTPUT_ENABLE;
        TI00_PORT_SETTING();
        TO00_PORT_SETTING();
    }

    /* Start specify channel */
    TM40_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM40_EventCount
* @brief  TM40 specified channel operates as external event counter.
* @param  ch - specify the channel number
* @param  intput - specify the input of TI
* @param  edge - specify the input edge of TI
* @param  num - specify the number of specifed edge of TI
* @return None
***********************************************************************************************************************/
void TM40_EventCount(tm4_channel_t ch, tm4_input_t input, tm4_edge_t edge, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _000A_TM4_CKM0_fCLK_10; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used to external event counter */
            TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM40->TDR00 = num - 1;
            TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH0_INPUT_TI00)
            {
                MISC->NFEN1 |= _01_TM4_CH0_NOISE_ON;
                TI00_PORT_SETTING();
            }
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used to external event counter */
            TM40->TMR01 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM40->TDR01 = num - 1;
            TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH1_INPUT_TI01)
            {
                MISC->NFEN1 |= _02_TM4_CH1_NOISE_ON;
                TI01_PORT_SETTING();
            }
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used to external event counter */
            TM40->TMR02 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM40->TDR02 = num - 1;
            TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN1 |= _04_TM4_CH2_NOISE_ON;
            TI02_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used to external event counter */
            TM40->TMR03 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM40->TDR03 = num - 1;
            TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN1 |= _08_TM4_CH3_NOISE_ON;
            TI03_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM40_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM40_Get_PulsePeriod
* @brief  This function measures the pulse period with polling mode for TM4 module.
* @param  ch - specify the channel number
* @param  intput - specify the input of TI
* @param  edge - specify the input edge of TI
* @return period - return the pulse period at specified edge
***********************************************************************************************************************/
uint32_t TM40_Get_PulsePeriod(tm4_channel_t ch, tm4_input_t input, tm4_pulse_t edge)
{
    uint32_t period;

    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used to measure input pulse interval */
            TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH0_INPUT_TI00)
            {
                MISC->NFEN1 |= _01_TM4_CH0_NOISE_ON;
                TI00_PORT_SETTING();
            }
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_1:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used to measure input pulse interval */
            TM40->TMR01 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH1_INPUT_TI01)
            {
                MISC->NFEN1 |= _02_TM4_CH1_NOISE_ON;
                TI01_PORT_SETTING();
            }
            /* enable interrupt */
            INTC_EnableIRQ(TM01_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used to measure input pulse interval */
            TM40->TMR02 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN1 |= _04_TM4_CH2_NOISE_ON;
            TI02_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM02_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used to measure input pulse interval */
            TM40->TMR03 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN1 |= _08_TM4_CH3_NOISE_ON;
            TI03_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM03_IRQn);
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM40_Channel_Start(ch);
    
    /* polling INTTMmn interrupt flag */
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            g_inttm00Taken = 0;
            while(g_inttm00Taken < 2);
            period = g_tm40_ch0_width;
            break;
        case TM4_CHANNEL_1:
            g_inttm01Taken = 0;
            while(g_inttm01Taken < 2);
            period = g_tm40_ch1_width;
            break;
        case TM4_CHANNEL_2:
            g_inttm02Taken = 0;
            while(g_inttm02Taken < 2);
            period = g_tm40_ch2_width;
            break;
        case TM4_CHANNEL_3:
            g_inttm03Taken = 0;
            while(g_inttm03Taken < 2);
            period = g_tm40_ch3_width;
            break;
        default: 
            break;
    }

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    return (period); 
}
/***********************************************************************************************************************
* Function Name: TM40_Get_PulseWidth
* @brief  This function measures the pulse width with polling mode for TM4 module.
* @param  ch - specify the channel number
* @param  intput - specify the input of TI
* @param  level - specify the input levle of TI
* @return width - return the pulse width at specified level
***********************************************************************************************************************/
uint32_t TM40_Get_PulseWidth(tm4_channel_t ch, tm4_input_t input, tm4_pulse_t level)
{
    uint32_t width;

    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used to measure input pulse width */
            TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH0_INPUT_TI00)
            {
                MISC->NFEN1 |= _01_TM4_CH0_NOISE_ON;
                TI00_PORT_SETTING();
            }
            /* enable interrupt */
            INTC_EnableIRQ(TM00_IRQn);
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used to measure input pulse width */
            TM40->TMR01 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH1_INPUT_TI01)
            {
                MISC->NFEN1 |= _02_TM4_CH1_NOISE_ON;
                TI01_PORT_SETTING();
            }
            /* enable interrupt */
            INTC_EnableIRQ(TM01_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used to measure input pulse width */
            TM40->TMR02 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN1 |= _04_TM4_CH2_NOISE_ON;
            TI02_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM02_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used to measure input pulse width */
            TM40->TMR03 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN1 |= _08_TM4_CH3_NOISE_ON;
            TI03_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM03_IRQn);
            break;
        default: 
            break;
    }

    /* Start specify channel */
    TM40_Channel_Start(ch);
    
    /* polling INTTMmn interrupt flag */
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            g_inttm00Taken = 0;
            while(g_inttm00Taken < 1);
            width = g_tm40_ch0_width;
            break;
        case TM4_CHANNEL_1:
            g_inttm01Taken = 0;
            while(g_inttm01Taken < 1);
            width = g_tm40_ch1_width;
            break;
        case TM4_CHANNEL_2:
            g_inttm02Taken = 0;
            while(g_inttm02Taken < 1);
            width = g_tm40_ch2_width;
        case TM4_CHANNEL_3:
            g_inttm03Taken = 0;
            while(g_inttm03Taken < 1);
            width = g_tm40_ch3_width;
            break;
        default: 
            break;
    }

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    return (width); 
}
/***********************************************************************************************************************
* Function Name: TM40_DelayCounter
* @brief  This function initializes the TM4 module.
* @param  ch - specify the channel number
* @param  intput - specify the input of TI
* @param  edge - specify the input edge of TI
* @param  delay - specify the delay number of TI
* @return None
***********************************************************************************************************************/
void TM40_DelayCounter(tm4_channel_t ch, tm4_input_t input, tm4_edge_t edge, uint16_t delay)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM00_IRQn);
            NVIC_ClearPendingIRQ(TM00_IRQn);
            /* Channel 0 is used to measure input pulse width */
            TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM40->TDR00 = delay - 1;
            TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH0_INPUT_TI00)
            {
                MISC->NFEN1 |= _01_TM4_CH0_NOISE_ON;
                TI00_PORT_SETTING();
            }
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM01_IRQn);
            NVIC_ClearPendingIRQ(TM01_IRQn);
            /* Channel 1 is used to measure input pulse width */
            TM40->TMR01 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM40->TDR01 = delay - 1;
            TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->TIOS0 |= input;
            if(input == TM4_CH1_INPUT_TI01)
            {
                MISC->NFEN1 |= _02_TM4_CH1_NOISE_ON;
                TI01_PORT_SETTING();
            }
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM02_IRQn);
            NVIC_ClearPendingIRQ(TM02_IRQn);
            /* Channel 2 is used to measure input pulse width */
            TM40->TMR02 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM40->TDR02 = delay - 1;
            TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN1 |= _04_TM4_CH2_NOISE_ON;
            TI02_PORT_SETTING();
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM03_IRQn);
            NVIC_ClearPendingIRQ(TM03_IRQn);
            /* Channel 3 is used to measure input pulse width */
            TM40->TMR03 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM40->TDR03 = delay - 1;
            TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM40->TOE0 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN1 |= _08_TM4_CH3_NOISE_ON;
            TI03_PORT_SETTING();
            break;
        default: 
            break;
    }

    /* Start specify channel */
    TM40_Channel_Start(ch);   
}
/***********************************************************************************************************************
* Function Name: TM40_One_Shot_Pulse_Output
* @brief  This function initializes the TM4 module as one-shot pulse output function.
* @param  edge - the valid edge of TI 
* @param  delay - the delay time from TI valid edge 
* @param  width - the pulse width of output
* @return None
***********************************************************************************************************************/
void TM40_One_Shot_Pulse_Output(tm4_edge_t edge, uint16_t delay, uint16_t width)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0100_TM4_TRIGGER_TIMN_VALID | (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT;
    TM40->TDR00 = delay - 2;
    TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0008_TM4_MODE_ONE_COUNT;
    TM40->TDR01 = width;
    TM40->TOM0 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO01_PORT_SETTING();

    /* Start specify channel */
    TM40_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1);
}
/***********************************************************************************************************************
* Function Name: TM40_PWM_1Period_1Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period - the period of PWM waveform
* @param  duty - the duty factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM40_PWM_1Period_1Duty(uint16_t period, uint16_t duty)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM40->TDR00 = period - 1;
    TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR01 = duty;
    TM40->TOM0 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO01_PORT_SETTING();

    /* Start specify channel */
    TM40_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1);
}
/***********************************************************************************************************************
* Function Name: TM40_PWM_1Period_2Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period - the period of PWM waveform
* @param  duty1 - the duty1 factor of PWM waveform
* @param  duty2 - the duty2 factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM40_PWM_1Period_2Duty(uint16_t period, uint16_t duty1, uint16_t duty2)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM40->TDR00 = period - 1;
    TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR01 = duty1;
    TM40->TOM0 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO01_PORT_SETTING();
    /* slave channel */
    TM40->TMR02 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR02 = duty2;
    TM40->TOM0 |=  _0004_TM4_CH2_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0004_TM4_CH2_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO02_PORT_SETTING();

    /* Start specify channel */
    TM40_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2);
}
/***********************************************************************************************************************
* Function Name: TM40_PWM_1Period_3Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period - the period of PWM waveform
* @param  duty1 - the duty1 factor of PWM waveform
* @param  duty2 - the duty2 factor of PWM waveform
* @param  duty3 - the duty3 factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM40_PWM_1Period_3Duty(uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM40->TDR00 = period - 1;
    TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR01 = duty1;
    TM40->TOM0 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO01_PORT_SETTING();
    /* slave channel */
    TM40->TMR02 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR02 = duty2;
    TM40->TOM0 |=  _0004_TM4_CH2_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0004_TM4_CH2_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO02_PORT_SETTING();
    /* slave channel */
    TM40->TMR03 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR03 = duty3;
    TM40->TOM0 |=  _0008_TM4_CH3_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0008_TM4_CH3_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO03_PORT_SETTING();

    /* Start specify channel */
    TM40_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2 | TM4_CHANNEL_3);
}
/***********************************************************************************************************************
* Function Name: TM40_PWM_2Period_2Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period1 - the period1 of PWM waveform
* @param  duty1 - the duty1 factor of PWM waveform
* @param  period2 - the period2 of PWM waveform
* @param  duty2 - the duty2 factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM40_PWM_2Period_2Duty(uint16_t period1, uint16_t duty1, uint16_t period2, uint16_t duty2)
{
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM40->TMR00 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM40->TDR00 = period1 - 1;
    TM40->TO0  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM40->TMR01 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR01 = duty1;
    TM40->TOM0 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO01_PORT_SETTING();
    /* master channel */
    TM40->TMR02 = _8000_TM4_CLOCK_SELECT_CKM1 | _0800_TM4_COMBINATION_MASTER | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM40->TDR02 = period2 - 1;
    TM40->TO0  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
    TM40->TOE0 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
    TO02_PORT_SETTING();
    /* slave channel */
    TM40->TMR03 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM40->TDR03 = duty2;
    TM40->TOM0 |=  _0008_TM4_CH3_SLAVE_OUTPUT;       /* slave channel output mode */
    TM40->TOL0 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM40->TO0  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM40->TOE0 |=  _0008_TM4_CH3_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO03_PORT_SETTING();

    /* Start specify channel */
    TM40_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2 | TM4_CHANNEL_3);
}
/***********************************************************************************************************************
* Function Name: TM40_Channel_Start
* @brief  This function starts TM40 channel counter.
* @param  ch - specify the channel number
* @return None
***********************************************************************************************************************/
void TM40_Channel_Start(tm4_channel_t ch)
{
    TM40->TS0 |= ch;
}
/***********************************************************************************************************************
* Function Name: TM4_Channel1_Stop
* @brief  This function stops TM40 channel counter.
* @param  ch - specify the channel number
* @return None
***********************************************************************************************************************/
void TM40_Channel_Stop(tm4_channel_t ch)
{
    TM40->TT0 |= ch;
}
/***********************************************************************************************************************
* Function Name: TM41_IntervalTimer
* @brief  TM41 specified channel operates as interval timer mode.
* @param  ch - specify the channel number
* @param  num - specify the number count clock
* @return None
***********************************************************************************************************************/
void TM41_IntervalTimer(tm4_channel_t ch, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _00F0_TM4_CKM1_fCLK_15 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM10_IRQn);
            NVIC_ClearPendingIRQ(TM10_IRQn);
            /* Channel 0 is used as interval timer */
            TM41->TMR10 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR10 = num - 1;
            TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM10_IRQn);
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM11_IRQn);
            NVIC_ClearPendingIRQ(TM11_IRQn);
            /* Channel 1 is used as interval timer */
            TM41->TMR11 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR11 = num - 1;
            TM41->TOE1 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM11_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM12_IRQn);
            NVIC_ClearPendingIRQ(TM12_IRQn);
            /* Channel 2 is used as interval timer */
            TM41->TMR12 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR12 = num - 1;
            TM41->TOE1 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM12_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM13_IRQn);
            NVIC_ClearPendingIRQ(TM13_IRQn);
            /* Channel 3 is used as interval timer */
            TM41->TMR13 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR13 = num - 1;
            TM41->TOE1 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            /* enable interrupt */
            INTC_EnableIRQ(TM13_IRQn);
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM41_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM41_SquareOutput
* @brief  TM41 specified channel operates as square wave output mode.
* @param  ch - specify the channel number
* @param  num - specify the number of count clock 
* @return None
***********************************************************************************************************************/
void TM41_SquareOutput(tm4_channel_t ch, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM10_IRQn);
            NVIC_ClearPendingIRQ(TM10_IRQn);
            /* Channel 0 is used as interval timer */
            TM41->TMR10 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR10 = num - 1;
            TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM41->TOE1 |=  _0001_TM4_CH0_OUTPUT_ENABLE;
            TO10_PORT_SETTING();
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM11_IRQn);
            NVIC_ClearPendingIRQ(TM11_IRQn);
            /* Channel 1 is used as interval timer */
            TM41->TMR11 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR11 = num - 1;
            TM41->TOM1 &= ~_0002_TM4_CH1_SLAVE_OUTPUT;
            TM41->TOL1 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;
            TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM41->TOE1 |=  _0002_TM4_CH1_OUTPUT_ENABLE;
            TO11_PORT_SETTING();
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM12_IRQn);
            NVIC_ClearPendingIRQ(TM12_IRQn);
            /* Channel 2 is used as interval timer */
            TM41->TMR12 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR12 = num - 1;
            TM41->TOM1 &= ~_0004_TM4_CH2_SLAVE_OUTPUT;
            TM41->TOL1 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;
            TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM41->TOE1 |=  _0004_TM4_CH2_OUTPUT_ENABLE;
            TO12_PORT_SETTING();
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM13_IRQn);
            NVIC_ClearPendingIRQ(TM13_IRQn);
            /* Channel 3 is used as interval timer */
            TM41->TMR13 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                          _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
            TM41->TDR13 = num - 1;
            TM41->TOM1 &= ~_0008_TM4_CH3_SLAVE_OUTPUT;
            TM41->TOL1 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;
            TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM41->TOE1 |=  _0008_TM4_CH3_OUTPUT_ENABLE;
            TO13_PORT_SETTING();
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM41_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM41_FreqDivider
* @brief  TM41 specified channel operates as frequency divider mode.
* @param  ch - specify the channel number
* @param  edge - specify the input edge of TI
* @param  num - specify the number of divider
* @return None
***********************************************************************************************************************/
void TM41_FreqDivider(tm4_channel_t ch, tm4_edge_t edge, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    if(ch == TM4_CHANNEL_0) 
    {
        /* clear interrupt flag */
        INTC_ClearPendingIRQ(TM10_IRQn);
        NVIC_ClearPendingIRQ(TM10_IRQn);
        /* Channel 0 is used as interval timer */
        TM41->TMR10 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                      (edge << TMRMN_CIS_Pos) | _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
        if(edge == TM4_TI_BOTHEDGE)
        {
            TM41->TDR10 = num - 1;
        }
        else
        {
            TM41->TDR10 = num / 2 - 1;
        }
        TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
        TM41->TOE1 |=  _0001_TM4_CH0_OUTPUT_ENABLE;
        TI10_PORT_SETTING();
        TO10_PORT_SETTING();
    }

    /* Start specify channel */
    TM41_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM41_EventCount
* @brief  TM41 specified channel operates as external event counter.
* @param  ch - specify the channel number
* @param  edge - specify the input edge of TI
* @param  num - specify the number of specifed edge of TI
* @return None
***********************************************************************************************************************/
void TM41_EventCount(tm4_channel_t ch, tm4_edge_t edge, uint16_t num)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _000A_TM4_CKM0_fCLK_10; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM10_IRQn);
            NVIC_ClearPendingIRQ(TM10_IRQn);
            /* Channel 0 is used to external event counter */
            TM41->TMR10 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM41->TDR10 = num - 1;
            TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->NFEN2 |= _01_TM4_CH0_NOISE_ON;
            TI10_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM10_IRQn);
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM11_IRQn);
            NVIC_ClearPendingIRQ(TM11_IRQn);
            /* Channel 1 is used to external event counter */
            TM41->TMR11 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM41->TDR11 = num - 1;
            TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->NFEN2 |= _02_TM4_CH1_NOISE_ON;
            TI11_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM11_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM12_IRQn);
            NVIC_ClearPendingIRQ(TM12_IRQn);
            /* Channel 2 is used to external event counter */
            TM41->TMR12 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM41->TDR12 = num - 1;
            TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN2 |= _04_TM4_CH2_NOISE_ON;
            TI12_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM12_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM13_IRQn);
            NVIC_ClearPendingIRQ(TM13_IRQn);
            /* Channel 3 is used to external event counter */
            TM41->TMR13 = _0000_TM4_CLOCK_SELECT_CKM0 | _1000_TM4_CLOCK_MODE_TIMN | _0000_TM4_TRIGGER_SOFTWARE |
                         (edge << TMRMN_CIS_Pos) | _0006_TM4_MODE_EVENT_COUNT;
            TM41->TDR13 = num - 1;
            TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN2 |= _08_TM4_CH3_NOISE_ON;
            TI13_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM13_IRQn);
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM41_Channel_Start(ch);
}
/***********************************************************************************************************************
* Function Name: TM41_Get_PulsePeriod
* @brief  This function measures the pulse period with polling mode for TM4 module.
* @param  ch - specify the channel number
* @param  edge - specify the input edge of TI
* @return period - return the pulse period at specified edge
***********************************************************************************************************************/
uint32_t TM41_Get_PulsePeriod(tm4_channel_t ch, tm4_pulse_t edge)
{
    uint32_t period;

    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM10_IRQn);
            NVIC_ClearPendingIRQ(TM10_IRQn);
            /* Channel 0 is used to measure input pulse interval */
            TM41->TMR10 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->NFEN2 |= _01_TM4_CH0_NOISE_ON;
            TI10_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM10_IRQn);
            break;
        case TM4_CHANNEL_1:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM11_IRQn);
            NVIC_ClearPendingIRQ(TM11_IRQn);
            /* Channel 1 is used to measure input pulse interval */
            TM41->TMR11 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->NFEN2 |= _02_TM4_CH1_NOISE_ON;
            TI11_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM11_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM12_IRQn);
            NVIC_ClearPendingIRQ(TM12_IRQn);
            /* Channel 2 is used to measure input pulse interval */
            TM41->TMR12 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN2 |= _04_TM4_CH2_NOISE_ON;
            TI12_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM12_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM13_IRQn);
            NVIC_ClearPendingIRQ(TM13_IRQn);
            /* Channel 3 is used to measure input pulse interval */
            TM41->TMR13 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                         (edge << TMRMN_CIS_Pos) | _0004_TM4_MODE_CAPTURE | _0000_TM4_START_INT_UNUSED;
            TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN2 |= _08_TM4_CH3_NOISE_ON;
            TI13_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM13_IRQn);
            break;
        default: 
            break;
    }
    /* Start specify channel */
    TM41_Channel_Start(ch);
    
    /* polling INTTMmn interrupt flag */
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            g_inttm10Taken = 0;
            while(g_inttm10Taken < 2);
            period = g_tm41_ch0_width;
            break;
        case TM4_CHANNEL_1:
            g_inttm11Taken = 0;
            while(g_inttm11Taken < 2);
            period = g_tm41_ch1_width;
            break;
        case TM4_CHANNEL_2:
            g_inttm12Taken = 0;
            while(g_inttm12Taken < 2);
            period = g_tm41_ch2_width;
            break;
        case TM4_CHANNEL_3:
            g_inttm13Taken = 0;
            while(g_inttm13Taken < 2);
            period = g_tm41_ch3_width;
            break;
        default: 
            break;
    }

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    return (period); 
}
/***********************************************************************************************************************
* Function Name: TM41_Get_PulseWidth
* @brief  This function initializes the TM4 module.
* @param  ch - specify the channel number
* @param  level - specify the input levle of TI
* @return width - return the pulse width at specified level
***********************************************************************************************************************/
uint32_t TM41_Get_PulseWidth(tm4_channel_t ch, tm4_pulse_t level)
{
    uint32_t width;

    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM10_IRQn);
            NVIC_ClearPendingIRQ(TM10_IRQn);
            /* Channel 0 is used to measure input pulse width */
            TM41->TMR10 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->NFEN2 |= _01_TM4_CH0_NOISE_ON;
            TI10_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM10_IRQn);
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM11_IRQn);
            NVIC_ClearPendingIRQ(TM11_IRQn);
            /* Channel 1 is used to measure input pulse width */
            TM41->TMR11 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->NFEN2 |= _02_TM4_CH1_NOISE_ON;
            TI11_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM11_IRQn);
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM12_IRQn);
            NVIC_ClearPendingIRQ(TM12_IRQn);
            /* Channel 2 is used to measure input pulse width */
            TM41->TMR12 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN2 |= _04_TM4_CH2_NOISE_ON;
            TI12_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM12_IRQn);
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM13_IRQn);
            NVIC_ClearPendingIRQ(TM13_IRQn);
            /* Channel 3 is used to measure input pulse width */
            TM41->TMR13 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0200_TM4_TRIGGER_TIMN_BOTH |
                         (level << TMRMN_CIS_Pos) | _000C_TM4_MODE_HIGHLOW_MEASURE;
            TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN2 |= _08_TM4_CH3_NOISE_ON;
            TI13_PORT_SETTING();
            /* enable interrupt */
            INTC_EnableIRQ(TM13_IRQn);
            break;
        default: 
            break;
    }

    /* Start specify channel */
    TM41_Channel_Start(ch);
    
    /* polling INTTMmn interrupt flag */
    switch(ch) 
    {
        case TM4_CHANNEL_0:
            g_inttm10Taken = 0;
            while(g_inttm10Taken < 1);
            width = g_tm41_ch0_width;
            break;
        case TM4_CHANNEL_1:
            g_inttm11Taken = 0;
            while(g_inttm11Taken < 1);
            width = g_tm41_ch1_width;
            break;
        case TM4_CHANNEL_2:
            g_inttm12Taken = 0;
            while(g_inttm12Taken < 1);
            width = g_tm41_ch2_width;
        case TM4_CHANNEL_3:
            g_inttm13Taken = 0;
            while(g_inttm13Taken < 1);
            width = g_tm41_ch3_width;
            break;
        default: 
            break;
    }

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    return (width); 
}
/***********************************************************************************************************************
* Function Name: TM41_DelayCounter
* @brief  This function initializes the TM4 module.
* @param  ch - specify the channel number
* @param  edge - specify the input edge of TI
* @param  delay - specify the delay number of TI
* @return None
***********************************************************************************************************************/
void TM41_DelayCounter(tm4_channel_t ch, tm4_edge_t edge, uint16_t delay)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM41_Channel_Stop(ch);  
    
    switch(ch) 
    {
        case TM4_CHANNEL_0: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM10_IRQn);
            NVIC_ClearPendingIRQ(TM10_IRQn);
            /* Channel 0 is used to measure input pulse width */
            TM41->TMR10 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM41->TDR10 = delay - 1;
            TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
            MISC->NFEN2 |= _01_TM4_CH0_NOISE_ON;
            TI10_PORT_SETTING();
            break;
        case TM4_CHANNEL_1: 
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM11_IRQn);
            NVIC_ClearPendingIRQ(TM11_IRQn);
            /* Channel 1 is used to measure input pulse width */
            TM41->TMR11 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM41->TDR11 = delay - 1;
            TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0002_TM4_CH1_OUTPUT_ENABLE;
            MISC->NFEN2 |= _02_TM4_CH1_NOISE_ON;
            TI11_PORT_SETTING();
            break;
        case TM4_CHANNEL_2:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM12_IRQn);
            NVIC_ClearPendingIRQ(TM12_IRQn);
            /* Channel 2 is used to measure input pulse width */
            TM41->TMR12 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM41->TDR12 = delay - 1;
            TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
            MISC->NFEN2 |= _04_TM4_CH2_NOISE_ON;
            TI12_PORT_SETTING();
            break;
        case TM4_CHANNEL_3:
            /* clear interrupt flag */
            INTC_ClearPendingIRQ(TM13_IRQn);
            NVIC_ClearPendingIRQ(TM13_IRQn);
            /* Channel 3 is used to measure input pulse width */
            TM41->TMR13 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0100_TM4_TRIGGER_TIMN_VALID |
                          (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT | _0000_TM4_START_INT_UNUSED;
            TM41->TDR13 = delay - 1;
            TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;
            TM41->TOE1 &= ~_0008_TM4_CH3_OUTPUT_ENABLE;
            MISC->NFEN2 |= _08_TM4_CH3_NOISE_ON;
            TI13_PORT_SETTING();
            break;
        default: 
            break;
    }

    /* Start specify channel */
    TM41_Channel_Start(ch);   
}
/***********************************************************************************************************************
* Function Name: TM41_One_Shot_Pulse_Output
* @brief  This function initializes the TM4 module as one-shot pulse output function.
* @param  edge - the valid edge of TI 
* @param  delay - the delay time from TI valid edge 
* @param  width - the pulse width of output
* @return None
***********************************************************************************************************************/
void TM41_One_Shot_Pulse_Output(tm4_edge_t edge, uint16_t delay, uint16_t width)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM41->TMR10 = _8000_TM4_CLOCK_SELECT_CKM1 | _0100_TM4_TRIGGER_TIMN_VALID | (edge << TMRMN_CIS_Pos) | _0008_TM4_MODE_ONE_COUNT;
    TM41->TDR10 = delay - 2;
    TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM41->TMR11 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0008_TM4_MODE_ONE_COUNT;
    TM41->TDR11 = width;
    TM41->TOM1 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO11_PORT_SETTING();

    /* Start specify channel */
    TM41_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1);
}
/***********************************************************************************************************************
* Function Name: TM41_PWM_1Period_1Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period - the period of PWM waveform
* @param  duty - the duty factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM41_PWM_1Period_1Duty(uint16_t period, uint16_t duty)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM41->TMR10 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM41->TDR10 = period - 1;
    TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM41->TMR11 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR11 = duty;
    TM41->TOM1 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO11_PORT_SETTING();

    /* Start specify channel */
    TM41_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1);
}
/***********************************************************************************************************************
* Function Name: TM41_PWM_1Period_2Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period - the period of PWM waveform
* @param  duty1 - the duty1 factor of PWM waveform
* @param  duty2 - the duty2 factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM41_PWM_1Period_2Duty(uint16_t period, uint16_t duty1, uint16_t duty2)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM41->TMR10 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM41->TDR10 = period - 1;
    TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM41->TMR11 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR11 = duty1;
    TM41->TOM1 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO11_PORT_SETTING();
    /* slave channel */
    TM41->TMR12 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR12 = duty2;
    TM41->TOM1 |=  _0004_TM4_CH2_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0004_TM4_CH2_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO12_PORT_SETTING();

    /* Start specify channel */
    TM41_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2);
}
/***********************************************************************************************************************
* Function Name: TM41_PWM_1Period_3Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period - the period of PWM waveform
* @param  duty1 - the duty1 factor of PWM waveform
* @param  duty2 - the duty2 factor of PWM waveform
* @param  duty3 - the duty3 factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM41_PWM_1Period_3Duty(uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM41->TMR10 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM41->TDR10 = period - 1;
    TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM41->TMR11 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR11 = duty1;
    TM41->TOM1 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO11_PORT_SETTING();
    /* slave channel */
    TM41->TMR12 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR12 = duty2;
    TM41->TOM1 |=  _0004_TM4_CH2_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0004_TM4_CH2_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0004_TM4_CH2_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO12_PORT_SETTING();
    /* slave channel */
    TM41->TMR13 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR13 = duty3;
    TM41->TOM1 |=  _0008_TM4_CH3_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0008_TM4_CH3_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO13_PORT_SETTING();

    /* Start specify channel */
    TM41_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2 | TM4_CHANNEL_3);
}
/***********************************************************************************************************************
* Function Name: TM41_PWM_2Period_2Duty
* @brief  This function initializes the TM4 module as PWM function.
* @param  period1 - the period1 of PWM waveform
* @param  duty1 - the duty1 factor of PWM waveform
* @param  period2 - the period2 of PWM waveform
* @param  duty2 - the duty2 factor of PWM waveform
* @return None
***********************************************************************************************************************/
void TM41_PWM_2Period_2Duty(uint16_t period1, uint16_t duty1, uint16_t period2, uint16_t duty2)
{
    CGC->PER0 |= CGC_PER0_TM41EN_Msk;    /* enables input clock supply */
    TM41->TPS1 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _0000_TM4_CKM1_fCLK_0 | _0000_TM4_CKM0_fCLK_0; 

    /* master channel */
    TM41->TMR10 = _8000_TM4_CLOCK_SELECT_CKM1 | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM41->TDR10 = period1 - 1;
    TM41->TO1  &= ~_0001_TM4_CH0_OUTPUT_VALUE_1;
    TM41->TOE1 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* slave channel */
    TM41->TMR11 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR11 = duty1;
    TM41->TOM1 |=  _0002_TM4_CH1_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0002_TM4_CH1_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0002_TM4_CH1_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0002_TM4_CH1_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO11_PORT_SETTING();
    /* master channel */
    TM41->TMR12 = _8000_TM4_CLOCK_SELECT_CKM1 | _0800_TM4_COMBINATION_MASTER | _0000_TM4_TRIGGER_SOFTWARE | _0001_TM4_MODE_PWM_MASTER;
    TM41->TDR12 = period2 - 1;
    TM41->TO1  &= ~_0004_TM4_CH2_OUTPUT_VALUE_1;
    TM41->TOE1 &= ~_0004_TM4_CH2_OUTPUT_ENABLE;
    TO12_PORT_SETTING();
    /* slave channel */
    TM41->TMR13 = _8000_TM4_CLOCK_SELECT_CKM1 | _0400_TM4_TRIGGER_MASTER_INT | _0009_TM4_MODE_PWM_SLAVE;
    TM41->TDR13 = duty2;
    TM41->TOM1 |=  _0008_TM4_CH3_SLAVE_OUTPUT;       /* slave channel output mode */
    TM41->TOL1 &= ~_0008_TM4_CH3_OUTPUT_LEVEL_L;     /* positive logic output (active-high) */
    TM41->TO1  &= ~_0008_TM4_CH3_OUTPUT_VALUE_1;     /* TOmp default output level */
    TM41->TOE1 |=  _0008_TM4_CH3_OUTPUT_ENABLE;      /* Enable TOmp output by counting operation */
    TO13_PORT_SETTING();

    /* Start specify channel */
    TM41_Channel_Start(TM4_CHANNEL_0 | TM4_CHANNEL_1 | TM4_CHANNEL_2 | TM4_CHANNEL_3);
}
/***********************************************************************************************************************
* Function Name: TM41_Channel_Start
* @brief  This function starts TM41 channel counter.
* @param  ch - specify the channel number
* @return None
***********************************************************************************************************************/
void TM41_Channel_Start(tm4_channel_t ch)
{
    TM41->TS1 |= ch;
}
/***********************************************************************************************************************
* Function Name: TM4_Channel1_Stop
* @brief  This function stops TM41 channel counter.
* @param  ch - specify the channel number
* @return None
***********************************************************************************************************************/
void TM41_Channel_Stop(tm4_channel_t ch)
{
    TM41->TT1 |= ch;
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
