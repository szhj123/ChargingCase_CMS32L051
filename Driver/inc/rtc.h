/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    rtc.h
* @version 1.0.0
* @brief   This file implements device driver for RTC module.
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef RTC_H
#define RTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Real-time clock control register 0 (RTCC0) 
*/
/* High-accuracy real-time clock operation control (RTCE) */
#define _00_RTC_COUNTER_STOP                   (0x00U) /* stops counter operation */
#define _80_RTC_COUNTER_START                  (0x80U) /* starts counter operation. */
/* RTC1HZ pin output control (RCLOE1) */
#define _00_RTC_RTC1HZ_DISABLE                 (0x00U) /* disables output of the RTC1HZ pin (1 Hz) */
#define _20_RTC_RTC1HZ_ENABLE                  (0x20U) /* enables output of the RTC1HZ pin (1 Hz). */
/* 12-/24-hour system select (AMPM) */
#define _00_RTC_12HOUR_SYSTEM                  (0x00U) /* 12-hour system */
#define _08_RTC_24HOUR_SYSTEM                  (0x08U) /* 24-hour system */
#define _08_RTC_RTCC0_AMPM                     (0x08U) /* AMPM bit status detect */
#define _08_RTC_HOURSYSTEM_CLEAR               (0x08U) /* hour system select  clear */
/* Constant-period interrupt (INTRTC) selection (CT2,CT1,CT0) */
#define _00_RTC_INTRTC_NOT_GENERATE            (0x00U) /* does not use fixed-cycle interrupt function */
#define _01_RTC_INTRTC_CLOCK_0                 (0x01U) /* once per 0.5 s (synchronized with second count up) */
#define _02_RTC_INTRTC_CLOCK_1                 (0x02U) /* once per 1 s (same time as second count up) */
#define _03_RTC_INTRTC_CLOCK_2                 (0x03U) /* once per 1 m (second 00 of every minute) */
#define _04_RTC_INTRTC_CLOCK_3                 (0x04U) /* once per 1 hour (minute 00 and second 00 of every hour) */
#define _05_RTC_INTRTC_CLOCK_4                 (0x05U) /* once per 1 day (hour 00, minute 00, and second 00 of every day) */
#define _06_RTC_INTRTC_CLOCK_5                 (0x06U) /* once per 1 month(Day 1, hour 00 a.m., minute 00, and second 00 of every month) */
#define _07_RTC_INTRTC_CLEAR                   (0x07U) /* INTRTC clear */

/*
    Real-time clock control register 1 (RTCC1) 
*/
/* Alarm operation control (WALE) */
#define _00_RTC_ALARM_DISABLE                  (0x00U) /* match operation is invalid */
#define _80_RTC_ALARM_ENABLE                   (0x80U) /* match operation is valid */
/* Control of alarm interrupt function operation (WALIE) */
#define _00_RTC_ALARM_INT_DISABLE              (0x00U) /* does not generate interrupt on matching of alarm */
#define _40_RTC_ALARM_INT_ENABLE               (0x40U) /* generates interrupt on matching of alarm */
/* Alarm detection status flag (WAFG) */
#define _00_RTC_ALARM_MISMATCH                 (0x00U) /* alarm mismatch */
#define _10_RTC_ALARM_MATCH                    (0x10U) /* detection of matching of alarm */
/* Constant-period interrupt status flag (RIFG) */
#define _00_RTC_INTC_NOTGENERATE_FALG          (0x00U) /* constant-period interrupt is not generated */
#define _08_RTC_INTC_GENERATE_FLAG             (0x08U) /* constant-period interrupt is generated */
/* Wait status flag of high-accuracy real-time clock (RWST) */
#define _00_RTC_COUNTER_OPERATING              (0x00U) /* counter is operating */
#define _02_RTC_COUNTER_STOP                   (0x02U) /* mode to read or write counter value */
/* Wait control of high-accuracy real-time clock (RWAIT) */
#define _00_RTC_COUNTER_SET                    (0x00U) /* sets counter operation */
#define _01_RTC_COUNTER_PAUSE                  (0x01U) /* stops SEC to YEAR counters. Mode to read or write counter value */

#define RWAIT    (1<<0U)
#define RWST     (1<<1U)
#define RIFG     (1<<3U)

/*
    12-bit Interval Timer Control Register (ITMC)
*/
/* 12-bit Interval timer operation control (RINTE) */
#define _0000_IT_OPERATION_DISABLE        (0x0000U) /* Count operation stopped */
#define _8000_IT_OPERATION_ENABLE         (0x8000U) /* Count operation started */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RTC_WAITTIME                       (320U)
#define RTC_WAITTIME_2FRTC                 (2U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct 
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t week;
    uint8_t month;
    uint8_t year;
}rtc_counter_value_t;

typedef struct
{
    uint8_t alarmwm;
    uint8_t alarmwh;
    uint8_t alarmww;
}rtc_alarm_value_t;

typedef enum
{ 
    HOUR12,
    HOUR24
}rtc_hour_system_t;

typedef enum 
{
    HALFSEC = 1U,
    ONESEC,
    ONEMIN,
    ONEHOUR,
    ONEDAY,
    ONEMONTH
}rtc_int_period_t;

typedef enum 
{
    SUNDAY   = 0x00U,
    MONDAY   = 0x01U,
    TUESDAY  = 0x02U,
    WEDNESDAY= 0x03U,
    THURSDAY = 0x04U,
    FRIDAY   = 0x05U,
    SATURDAY = 0x06U
}rtc_week_t;

typedef enum 
{
    RTC_FSUB,
    RTC_FIL,
    RTC_64MHZ,  /* fHOCO = 64MHz */
    RTC_48MHZ,  /* fHOCO = 48MHz */
    RTC_32MHZ,  /* fHOCO = 32MHz */
    RTC_16MHZ,  /* fMX   = 16MHz */
    RTC_8MHZ,   /* fMX   =  8MHz */
} rtc_cks_t;

typedef enum 
{
    RTC_IRQ_DISABLE,
    RTC_IRQ_ENABLE 
} rtc_irq_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern rtc_counter_value_t date_time;
extern volatile uint32_t g_rtcIntTaken;
extern volatile uint32_t g_ItIntTaken;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void RTC_Init(rtc_cks_t rtccks);
void RTC_Start(void);
void RTC_Stop(void);
void RTC_Set_CounterValue(rtc_counter_value_t *counter_val);
void RTC_Get_CounterValue(rtc_counter_value_t *counter_val);
void RTC_Set_AlarmOn(void);
void RTC_Set_AlarmOff(void);
void RTC_Set_AlarmValue(rtc_alarm_value_t alarm_val);
void RTC_Get_AlarmValue(rtc_alarm_value_t * const alarm_val);
uint16_t RTC_Set_ConstPeriodInterruptOn(rtc_int_period_t period);
void RTC_Set_ConstPeriodInterruptOff(void);
void RTC_1HZ_Output(void);
uint16_t RTC_Set_CorrectionValue(double freq, uint32_t target);
static void rtc_callback_alarm(void);
static void rtc_callback_constperiod(void);
void IT_Init(rtc_cks_t rtccks, uint16_t counter_val);
void IT_Start(void);
void IT_Stop(void);
static void it_callback(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
