/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    rtc_user.c
* @brief   This file implements device driver for RTC module.
* @version 1.0.0
* @date    2019/5/23
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "CMS32L051.h"
#include "rtc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ22_Handler(void) __attribute__((alias("rtc_interrupt")));
void IRQ23_Handler(void) __attribute__((alias("it_interrupt")));

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
rtc_counter_value_t date_time;
volatile uint32_t g_rtcIntTaken;
volatile uint32_t g_ItIntTaken;

/*******************************************************************************************
* 函数名称: str2bcdtime
* 描   述 : 把符串转为BCD码时间             
* 输入参数: 将要转换的保存文件名字符串的数组 ，以及转换之后将要保存bcd时间的数组
* 输出参数: 无
* 返   回 : 无
********************************************************************************************/
static void str2bcdtime(char date_buf[], char bcd_buf[])
{
    /* DATE格式为： “2019/03/25 19:32:00” */
    /* BCD 时间格式为 “190325193200” */ 
    bcd_buf[0] = (char)((date_buf[2] - '0')<<4) + (date_buf[3] - '0');
    bcd_buf[1] = (char)((date_buf[5] - '0')<<4) + (date_buf[6] - '0');
    bcd_buf[2] = (char)((date_buf[8] - '0')<<4) + (date_buf[9] - '0');
    bcd_buf[3] = (char)((date_buf[11] - '0')<<4) + (date_buf[12] - '0');
    bcd_buf[4] = (char)((date_buf[14] - '0')<<4) + (date_buf[15] - '0');
    bcd_buf[5] = (char)((date_buf[17] - '0')<<4) + (date_buf[18] - '0');
}

/***********************************************************************************************************************
* 函数名称: double_round
* 描   述 : 双精度浮点数值取整运算
* 参   数 : 双精度浮点数
* 返   回 : 整数
***********************************************************************************************************************/
static int double_round(double f) {
    return (f >= 0 ? (int)(f + 0.5) : (int)(f-1));
}

/***********************************************************************************************************************
* Function Name: RTC_Set_CorrectionValue(double freq, uint32_t target) 
* @brief  This function calulate and setting the correct value of RTC
* @param  freq - the frequency of fRTC
* @param  target - the target frequency. such as 32768Hz
* @return None
***********************************************************************************************************************/
uint16_t RTC_Set_CorrectionValue(double freq, uint32_t target) 
{
    double errors; // ppm unit
    uint16_t reg_dev, reg_sign, reg_num, reg_value;
    double correct_value;

    errors = (target - freq) * 1000000 / target;
    //printf("errors = %5.1f\r\n", errors);
    if(fabs(errors) < 4165.6) {
        reg_dev = 1; // errors corrects at 00 second
        correct_value = (freq / target - 1) * 32768 * 60;
    }
    else {
        reg_dev = 0; // errors corrects at 00/20/40 second
        correct_value = (freq / target - 1) * 32768 * 20;
    }
    
    //printf("correct_value = %d\r\n", double_round(correct_value));
    if(correct_value == 0) {
        reg_value = 0x0000;
    }
    else if(correct_value > 0) {
        reg_sign = 0;
        reg_num = double_round(correct_value) / 2 + 1;
        reg_value = reg_dev << 15 | reg_sign << 12 | reg_num;
    }
    else {
        reg_sign = 1;
        reg_num = ~(double_round(correct_value) / -2 - 1) & 0xFFF;
        reg_value = reg_dev << 15 | reg_sign << 12 | reg_num;
    }

    //printf("SUBCUD = %04X\r\n", reg_value);
    RTC->SUBCUD = reg_value;
    return (reg_value);
}
#if 0
/***********************************************************************************************************************
* Function Name: rtc_correction
* @brief  This function demonstrates RTC clock correction.
* @param  freq - the frequency of fRTC
* @return None
***********************************************************************************************************************/
void rtc_correction(uint32_t fclk_freq) 
{
  char date[10];
  char time[10];
  char string[20];
  char bcd[20];
  uint8_t dat, item;

  printf("\nRTC Correction Test...\n");
  RTC_Init(RTC_32MHZ);
  RTC_Start();
  RTC_1HZ_Output();

  printf("\n请设置RTC的时间：输入格式：年/月/日  时:分:秒 例如: 2019/03/22 18:20:00\n");

  scanf("%s%s", date, time);
  sprintf(string, "%s %s", date, time);
  str2bcdtime(string, bcd);
  date_time.year  = bcd[0];
  date_time.month = bcd[1];
  date_time.week  = MONDAY; 
  date_time.day   = bcd[2];
  date_time.hour  = bcd[3];
  date_time.min   = bcd[4];
  date_time.sec   = bcd[5];
  //printf(("\r\n"));

  RTC_Set_CorrectionValue((double)(fclk_freq)/976, 32768);
  RTC_Set_CounterValue(&date_time);
  RTC_Set_ConstPeriodInterruptOn(ONESEC);

  while(1) {
      dat = getchar();
      //-----------------------------------------------------------------------
      // constant period interrupt once per second
      //-----------------------------------------------------------------------
      if(dat == 's') {
          RTC_Set_ConstPeriodInterruptOn(ONESEC);
          printf("\n");
      }
      //-----------------------------------------------------------------------
      // constant period interrupt once per minute
      //-----------------------------------------------------------------------
      if(dat == 'm') {
          RTC_Set_ConstPeriodInterruptOn(ONEMIN);
          printf("\n");
      }
      //-----------------------------------------------------------------------
      // constant period interrupt once per hour
      //-----------------------------------------------------------------------
      if(dat == 'h') {
          RTC_Set_ConstPeriodInterruptOn(ONEHOUR);
          printf("\n");
      }
  
  } // while end
  
}
#endif

/***********************************************************************************************************************
* Function Name: rtc_interrupt
* @brief  RTC interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void rtc_interrupt(void)
{
    if (RTC->RTCC1 & RTC_RTCC1_WAFG_Msk)
    {
        RTC->RTCC1 &= (uint8_t)~_10_RTC_ALARM_MATCH;        /* clear WAFG */
        INTC_ClearPendingIRQ(RTC_IRQn);                     /* clear INTRTC flag */
        rtc_callback_alarm();
    }

    if (RTC->RTCC1 & RTC_RTCC1_RIFG_Msk)
    {
        RTC->RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG; /* clear RIFG */
        INTC_ClearPendingIRQ(RTC_IRQn);                     /* clear INTRTC flag */
        rtc_callback_constperiod();
    }
}
/***********************************************************************************************************************
* Function Name: it_interrupt
* @brief  15bit Interval Timer interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void it_interrupt(void)
{
    INTC_ClearPendingIRQ(IT_IRQn);                          /* clear INTIT flag */
    it_callback(); 
}
/***********************************************************************************************************************
* Function Name: rtc_callback_alarm
* @brief  This function is real-time clock constant-period interrupt service handler.
* @param  None
* @return None
***********************************************************************************************************************/
static void rtc_callback_alarm(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: rtc_callback_constperiod
* @brief  This function is real-time clock constant-period interrupt service handler.
* @param  None
* @return None
***********************************************************************************************************************/
static void rtc_callback_constperiod(void)
{
    /* Start user code. Do not edit comment generated here */
    g_rtcIntTaken++;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: it_callback
* @brief  This function is 15-bit interval timer interrupt service handler.
* @param  None
* @return None
***********************************************************************************************************************/
static void it_callback(void)
{
    /* Start user code. Do not edit comment generated here */
    g_ItIntTaken++;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
