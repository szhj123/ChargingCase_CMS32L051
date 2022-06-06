/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    rtc.c
* @brief   This file implements device driver for RTC module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "rtc.h"
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
* Function Name: RTC_Init
* @brief  This function initializes the real-time clock module.
* @param  rtccks - select the operaton clock of RTC
* @return None
***********************************************************************************************************************/
void RTC_Init(rtc_cks_t rtccks)
{
    CGC->PER0  |= CGC_PER0_RTCEN_Msk;     /* enables input clock supply */
    if(rtccks == RTC_FSUB) {
        MISC->RTCCL  = 0x00;  /* fRTC = fSUB */
        CGC->OSMC  &= ~(1<<4);/* WUTMMCK0 = 0 */
    }
    if(rtccks == RTC_FIL) {
        MISC->RTCCL  = 0x01;  /* fRTC = fIL */
        CGC->OSMC  |= 1<<4;   /* WUTMMCK0 = 1 */
    }
    if(rtccks == RTC_64MHZ) {
        MISC->RTCCL  = 0xA2;  /* fRTC = fHOCO/1952 */
    }
    if(rtccks == RTC_48MHZ) {
        MISC->RTCCL  = 0x82;  /* fRTC = fHOCO/1464 */
    }
    if(rtccks == RTC_32MHZ) {
        MISC->RTCCL  = 0xC2;  /* fRTC = fHOCO/976 */
    }
    if(rtccks == RTC_16MHZ) {
        MISC->RTCCL  = 0x03;  /* fRTC = fMX/488 */
    }
    if(rtccks == RTC_8MHZ) {
        MISC->RTCCL  = 0x43;  /* fRTC = fMX/244 */
    }
    RTC->RTCC0  = _00_RTC_COUNTER_STOP;     /* stops counter operation */
    RTC->RTCC0 |= _08_RTC_24HOUR_SYSTEM;    /* 24-hour system */
}
/***********************************************************************************************************************
* Function Name: RTC_Start
* @brief  This function enables the real-time clock.
* @param  None
* @return None
***********************************************************************************************************************/
void RTC_Start(void)
{

    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    INTC_EnableIRQ(RTC_IRQn);       /* enable INTRTC interrupt */

    RTC->RTCC0  |= _80_RTC_COUNTER_START;    /* starts counter operation */

    /* confirm the RTC is running */
    RTC->RTCC1 |= RTC_RTCC1_RWAIT_Msk;              /* stops SEC to YEAR counters. Mode to read or write counter value */           
    while((RTC->RTCC1 & RTC_RTCC1_RWST_Msk) == 0);  /* wait RWST = 1 */
    RTC->RTCC1 &= ~RTC_RTCC1_RWAIT_Msk;             /* sets counter operation */
    while((RTC->RTCC1 & RTC_RTCC1_RWST_Msk) != 0);  /* wait RWST = 0 */
}
/***********************************************************************************************************************
* Function Name: RTC_Stop
* @brief  This function disables the real-time clock.
* @param  None
* @return None
***********************************************************************************************************************/
void RTC_Stop(void)
{
    RTC->RTCC0  = _00_RTC_COUNTER_STOP;     /* stops counter operation */
    INTC_DisableIRQ(RTC_IRQn);      /* disable INTRTC interrupt */
    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
}
/***********************************************************************************************************************
* Function Name: RTC_Set_CounterValue
* @brief  This function set the counter value of the real-time clock.
* @param  counter_val
*             - the pointer of the expected real-time clock value(BCD code)
* @return None
***********************************************************************************************************************/
void RTC_Set_CounterValue(rtc_counter_value_t *counter_val)
{

    RTC->RTCC1 |= RTC_RTCC1_RWAIT_Msk;              /* stops SEC to YEAR counters. Mode to read or write counter value */           
    while((RTC->RTCC1 & RTC_RTCC1_RWST_Msk) == 0);  /* wait RWST = 1 */
    
    RTC->SEC   = counter_val->sec;
    RTC->MIN   = counter_val->min;
    RTC->HOUR  = counter_val->hour;
    RTC->DAY   = counter_val->day;
    RTC->WEEK  = counter_val->week;
    RTC->MONTH = counter_val->month;
    RTC->YEAR  = counter_val->year;

    RTC->RTCC1 &= ~RTC_RTCC1_RWAIT_Msk;             /* sets counter operation */
    while((RTC->RTCC1 & RTC_RTCC1_RWST_Msk) != 0);  /* wait RWST = 0 */
}
/***********************************************************************************************************************
* Function Name: RTC_Get_CounterValue
* @brief  This function get the counter value of the real-time clock.
* @param  counter_val
*             - the pointer of the current real-time clock value(BCD code)
* @return None
***********************************************************************************************************************/
void RTC_Get_CounterValue(rtc_counter_value_t *counter_val)
{

    RTC->RTCC1 |= RTC_RTCC1_RWAIT_Msk;              /* stops SEC to YEAR counters. Mode to read or write counter value */           
    while((RTC->RTCC1 & RTC_RTCC1_RWST_Msk) == 0);  /* wait RWST = 1 */
    
    counter_val->sec   = RTC->SEC;    
    counter_val->min   = RTC->MIN;   
    counter_val->hour  = RTC->HOUR;   
    counter_val->day   = RTC->DAY;    
    counter_val->week  = RTC->WEEK;   
    counter_val->month = RTC->MONTH;  
    counter_val->year  = RTC->YEAR;   

    RTC->RTCC1 &= ~RTC_RTCC1_RWAIT_Msk;             /* sets counter operation */
    while((RTC->RTCC1 & RTC_RTCC1_RWST_Msk) != 0);  /* wait RWST = 0 */
}
/***********************************************************************************************************************
* Function Name: RTC_Set_AlarmOn
* @brief  This function enables alarm interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void RTC_Set_AlarmOn(void)
{
    volatile uint16_t w_count;
    INTC_DisableIRQ(RTC_IRQn);      /* disable INTRTC interrupt */
    RTC->RTCC1 |= _80_RTC_ALARM_ENABLE;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_2FRTC; w_count++)
    {
        __NOP();
    }

    RTC->RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;
    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    INTC_EnableIRQ(RTC_IRQn);       /* enable INTRTC interrupt */
}
/***********************************************************************************************************************
* Function Name: RTC_Set_AlarmOff
* @brief  This function disables the alarm interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void RTC_Set_AlarmOff(void)
{
    INTC_DisableIRQ(RTC_IRQn);      /* disable INTRTC interrupt */
    RTC->RTCC1 &= (uint8_t)~_80_RTC_ALARM_ENABLE;
    RTC->RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;
    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
}
/***********************************************************************************************************************
* Function Name: RTC_Set_AlarmValue
* @brief  This function sets alarm value.
* @param  alarm_val - the expected alarm value(BCD code)
* @return None
***********************************************************************************************************************/
void RTC_Set_AlarmValue(rtc_alarm_value_t alarm_val)
{
    INTC_DisableIRQ(RTC_IRQn);      /* disable INTRTC interrupt */
    RTC->RTCC1 &= (uint8_t)~_80_RTC_ALARM_ENABLE;
    RTC->RTCC1 |= _40_RTC_ALARM_INT_ENABLE;
    RTC->ALARMWM = alarm_val.alarmwm;
    RTC->ALARMWH = alarm_val.alarmwh;
    RTC->ALARMWW = alarm_val.alarmww;
    RTC->RTCC1 |= _80_RTC_ALARM_ENABLE;
    RTC->RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;
    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    INTC_EnableIRQ(RTC_IRQn);       /* enable INTRTC interrupt */
}
/***********************************************************************************************************************
* Function Name: RTC_Get_AlarmValue
* @brief  This function gets alarm value.
* @param  alarm_val - the address to save alarm value(BCD code)
* @return None
***********************************************************************************************************************/
void RTC_Get_AlarmValue(rtc_alarm_value_t * const alarm_val)
{
    INTC_DisableIRQ(RTC_IRQn);      /* disable INTRTC interrupt */
    RTC->RTCC1 &= (uint8_t)~_80_RTC_ALARM_ENABLE;
    alarm_val->alarmwm = RTC->ALARMWM;
    alarm_val->alarmwh = RTC->ALARMWH;
    alarm_val->alarmww = RTC->ALARMWW;
    RTC->RTCC1 |= _80_RTC_ALARM_ENABLE;

    RTC->RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;
    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    INTC_EnableIRQ(RTC_IRQn);       /* enable INTRTC interrupt */
}
/***********************************************************************************************************************
* Function Name: RTC_Set_ConstPeriodInterruptOn
* @brief  This function enables constant-period interrupt.
* @param  period - the constant period of INTRTC
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS RTC_Set_ConstPeriodInterruptOn(rtc_int_period_t period)
{
    MD_STATUS status = MD_OK;

    if ((period < HALFSEC) || (period > ONEMONTH))
    {
        status = MD_ARGERROR;
    }
    else
    {
        INTC_DisableIRQ(RTC_IRQn);      /* disable INTRTC interrupt */
        RTC->RTCC0 = (RTC->RTCC0 & (uint8_t)~_07_RTC_INTRTC_CLEAR) | period;
        RTC->RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
        INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
        NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
        INTC_EnableIRQ(RTC_IRQn);       /* enable INTRTC interrupt */
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: RTC_Set_ConstPeriodInterruptOff
* @brief  This function disables constant-period interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void RTC_Set_ConstPeriodInterruptOff(void)
{
    RTC->RTCC0 &= (uint8_t)~(_07_RTC_INTRTC_CLEAR);
    RTC->RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
    INTC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
    NVIC_ClearPendingIRQ(RTC_IRQn); /* clear INTRTC interrupt flag */
}
/***********************************************************************************************************************
* Function Name: RTC_1HZ_Output(void)
* @brief  This function enable the RTC1HZ output. 
* @param  None
* @return None
***********************************************************************************************************************/
void RTC_1HZ_Output(void)
{
    RTC1HZ_PORT_SETTING();
    RTC->RTCC0 &= ~(1<<7);  // RTCE = 0
    RTC->RTCC0 |=  (1<<5);  // RCLOE1 = 1, enable output of the RTC1HZ
    RTC->RTCC0 |=  (1<<7);  // RTCE = 1
}
/***********************************************************************************************************************
* Function Name: IT_Init
* @brief  This function initializes the IntervalTimer module.
* @param  rtccks - select the operaton clock of RTC/IT
* @param  counter_val - the expected interval timer value
* @return None
***********************************************************************************************************************/
void IT_Init(rtc_cks_t rtccks, uint16_t counter_val)
{
    CGC->PER0  |= CGC_PER0_RTCEN_Msk;     /* enables input clock supply */
    if(rtccks == RTC_FSUB) {
        MISC->RTCCL  = 0x00;  /* fRTC = fSUB */
    }
    if(rtccks == RTC_FIL) {
        MISC->RTCCL  = 0x01;  /* fRTC = fIL */
        CGC->OSMC  |= 1<<4;   /* WUTMMCK0 = 1 */
    }
    if(rtccks == RTC_64MHZ) {
        MISC->RTCCL  = 0xA2;  /* fRTC = fHOCO/1952 */
    }
    if(rtccks == RTC_48MHZ) {
        MISC->RTCCL  = 0x82;  /* fRTC = fHOCO/1464 */
    }
    if(rtccks == RTC_32MHZ) {
        MISC->RTCCL  = 0xC2;  /* fRTC = fHOCO/976 */
    }
    if(rtccks == RTC_16MHZ) {
        MISC->RTCCL  = 0x03;  /* fRTC = fMX/488 */
    }
    if(rtccks == RTC_8MHZ) {
        MISC->RTCCL  = 0x43;  /* fRTC = fMX/244 */
    }
    RTC->ITMC = _0000_IT_OPERATION_DISABLE;
    INTC_DisableIRQ(IT_IRQn);       /* disable INTIT interrupt */
    INTC_ClearPendingIRQ(IT_IRQn);  /* clear INTIT interrupt flag */
    RTC->ITMC = counter_val;
}
/***********************************************************************************************************************
* Function Name: IT_Start
* @brief  This function starts IntervalTimer module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IT_Start(void)
{
    INTC_ClearPendingIRQ(IT_IRQn); /* clear INTIT interrupt flag */
    NVIC_ClearPendingIRQ(IT_IRQn); /* clear INTIT interrupt flag */
    INTC_EnableIRQ(IT_IRQn);       /* enable INTIT interrupt */
    RTC->ITMC |= _8000_IT_OPERATION_ENABLE;

    /* confirm the IntervalTimer is running */
    while((RTC->ITMC & _8000_IT_OPERATION_ENABLE) == 0U);  /* wait ITMC.RINTE == 1 */
}
/***********************************************************************************************************************
* Function Name: IT_Stop
* @brief  This function stops IntervalTimer module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IT_Stop(void)
{
    INTC_DisableIRQ(IT_IRQn);      /* disable INTIT interrupt */
    INTC_ClearPendingIRQ(IT_IRQn); /* clear INTIT interrupt flag */
    NVIC_ClearPendingIRQ(IT_IRQn); /* clear INTIT interrupt flag */
    RTC->ITMC &= (uint16_t)~_8000_IT_OPERATION_ENABLE;
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
