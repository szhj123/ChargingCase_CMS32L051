/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    adc.h
* @brief   This file implements device driver for ADC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef ADC_H
#define ADC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Analog input channel specification register (ADS) 
*/
/* Specification of analog input channel (ADISS,ADS3,ADS2,ADS1,ADS0) */
#define _00_AD_INPUT_CHANNEL_0                  (0x00U) /* ANI0 */
#define _01_AD_INPUT_CHANNEL_1                  (0x01U) /* ANI1 */
#define _02_AD_INPUT_CHANNEL_2                  (0x02U) /* ANI2 */
#define _03_AD_INPUT_CHANNEL_3                  (0x03U) /* ANI3 */
#define _04_AD_INPUT_CHANNEL_4                  (0x04U) /* ANI4 */
#define _05_AD_INPUT_CHANNEL_5                  (0x05U) /* ANI5 */
#define _06_AD_INPUT_CHANNEL_6                  (0x06U) /* ANI6 */
#define _07_AD_INPUT_CHANNEL_7                  (0x07U) /* ANI7 */
#define _08_AD_INPUT_CHANNEL_8                  (0x08U) /* ANI8 */
#define _09_AD_INPUT_CHANNEL_9                  (0x09U) /* ANI9 */
#define _0A_AD_INPUT_CHANNEL_10                 (0x0AU) /* ANI10 */
#define _0B_AD_INPUT_CHANNEL_11                 (0x0BU) /* ANI11 */
#define _0C_AD_INPUT_CHANNEL_12                 (0x0CU) /* ANI12 */
#define _0D_AD_INPUT_CHANNEL_13                 (0x0DU) /* ANI13 */
#define _0E_AD_INPUT_CHANNEL_14                 (0x0EU) /* ANI14 */
#define _0F_AD_INPUT_CHANNEL_15                 (0x0FU) /* ANI15 */
#define _10_AD_INPUT_CHANNEL_16                 (0x10U) /* ANI16 */
#define _11_AD_INPUT_CHANNEL_17                 (0x11U) /* ANI17 */
#define _12_AD_INPUT_CHANNEL_18                 (0x12U) /* ANI18 */
#define _13_AD_INPUT_CHANNEL_19                 (0x13U) /* ANI19 */
#define _14_AD_INPUT_CHANNEL_20                 (0x14U) /* ANI20 */
#define _15_AD_INPUT_CHANNEL_21                 (0x15U) /* ANI21 */
#define _16_AD_INPUT_CHANNEL_22                 (0x16U) /* ANI22 */
#define _17_AD_INPUT_CHANNEL_23                 (0x17U) /* ANI23 */
#define _18_AD_INPUT_CHANNEL_24                 (0x18U) /* ANI24 */
#define _19_AD_INPUT_CHANNEL_25                 (0x19U) /* ANI25 */
#define _1A_AD_INPUT_CHANNEL_26                 (0x1AU) /* ANI26 */
#define _1B_AD_INPUT_CHANNEL_27                 (0x1BU) /* ANI27 */
#define _1C_AD_INPUT_CHANNEL_28                 (0x1CU) /* ANI28 */
#define _1D_AD_INPUT_CHANNEL_29                 (0x1DU) /* ANI29 */
#define _1E_AD_INPUT_CHANNEL_30                 (0x1EU) /* ANI30 */
#define _1F_AD_INPUT_CHANNEL_31                 (0x1FU) /* ANI31 */
#define _20_AD_INPUT_CHANNEL_32                 (0x20U) /* ANI32 */
#define _21_AD_INPUT_CHANNEL_33                 (0x21U) /* ANI33 */
#define _22_AD_INPUT_CHANNEL_34                 (0x22U) /* ANI34 */
#define _23_AD_INPUT_CHANNEL_35                 (0x23U) /* ANI35 */
#define _24_AD_INPUT_CHANNEL_36                 (0x24U) /* ANI36 */
#define _3F_AD_INPUT_CHANNEL_OFF                (0x3FU) /* ANIx OFF */
#define _80_AD_INPUT_TEMPERSENSOR               (0x80U) /* temperature sensor output is used to be the input channel */
#define _81_AD_INPUT_INTERREFVOLT               (0x81U) /* internal reference voltage output is used to be the input channel */
#define _00_AD_INPUT_CHANNEL_0_3                (0x00U) /* ANI0 - ANI3 */
#define _01_AD_INPUT_CHANNEL_1_4                (0x01U) /* ANI1 - ANI4 */
#define _02_AD_INPUT_CHANNEL_2_5                (0x02U) /* ANI2 - ANI5 */
#define _03_AD_INPUT_CHANNEL_3_6                (0x03U) /* ANI3 - ANI6 */
#define _04_AD_INPUT_CHANNEL_4_7                (0x04U) /* ANI4 - ANI7 */
#define _05_AD_INPUT_CHANNEL_5_8                (0x05U) /* ANI5 - ANI8 */
#define _06_AD_INPUT_CHANNEL_6_9                (0x06U) /* ANI6 - ANI9 */
#define _07_AD_INPUT_CHANNEL_7_10               (0x07U) /* ANI7 - ANI10 */
#define _08_AD_INPUT_CHANNEL_8_11               (0x08U) /* ANI8 - ANI11 */
#define _09_AD_INPUT_CHANNEL_9_12               (0x09U) /* ANI9 - ANI12 */
#define _0A_AD_INPUT_CHANNEL_10_13              (0x0AU) /* ANI10 - ANI13 */
#define _0B_AD_INPUT_CHANNEL_11_14              (0x0BU) /* ANI11 - ANI14 */
#define _0C_AD_INPUT_CHANNEL_12_15              (0x0CU) /* ANI12 - ANI15 */

/*
    A/D converter mode register 0 (ADM0) 
*/
/* A/D conversion operation control (ADCS) */
#define _00_AD_CONVERSION_DISABLE               (0x00U) /* stops conversion operation */
#define _80_AD_CONVERSION_ENABLE                (0x80U) /* enables conversion operation */

/* A/D conversion clock selection (FR2,FR1,FR0) */
#define _00_AD_CONVERSION_CLOCK_32              (0x00U) /* fCLK/32 */
#define _08_AD_CONVERSION_CLOCK_16              (0x08U) /* fCLK/16 */
#define _10_AD_CONVERSION_CLOCK_8               (0x10U) /* fCLK/8 */
#define _18_AD_CONVERSION_CLOCK_4               (0x18U) /* fCLK/4 */
#define _20_AD_CONVERSION_CLOCK_2               (0x20U) /* fCLK/2 */
#define _28_AD_CONVERSION_CLOCK_1               (0x28U) /* fCLK/1 */
/* A/D voltage comparator operation control (ADCE) */
#define _00_AD_COMPARATOR_DISABLE               (0x00U) /* stops A/D voltage comparator operation */
#define _01_AD_COMPARATOR_ENABLE                (0x01U) /* enables A/D voltage comparator operation */

/*
    A/D converter mode register 1 (ADM1) 
*/
/* Specification of the A/D conversion channel selection mode (ADMD) */
#define _00_AD_OPERMODE_SELECT                  (0x00U) /* select mode */
#define _80_AD_OPERMODE_SCAN                    (0x80U) /* scan mode */
/* AD convertion mode selection (ADSCM) */
#define _00_AD_CONVMODE_CONSELECT               (0x00U) /* sequential convertion mode */
#define _08_AD_CONVMODE_ONESELECT               (0x08U) /* one-shot convertion mode */
#define _00_AD_CONVMODE_SEQUENTIAL              (0x00U) /* sequential convertion mode */
#define _08_AD_CONVMODE_ONESHOT                 (0x08U) /* one-shot convertion mode */
/* A/D conversion mode selection (ADMODE1,ADMODE0) */
#define _00_AD_HISPEED                          (0x00U) /* hispeed convertion mode */
#define _03_AD_LOW_CURRENT                      (0x03U) /* low current convertion mode */

/*
    A/D converter mode register 2 (ADM2) 
*/
/* AD VREF(+) selection (ADREFP1,ADREFP0) */
#define _00_AD_POSITIVE_VDD                     (0x00U) /* use AVDD as VREF(+) */
#define _40_AD_POSITIVE_AVREFP                  (0x40U) /* use EX AVREFP as VREF(+) */
#define _80_AD_POSITIVE_INVREFP                 (0x80U) /* use IN AVREFP(1.45V) as VREF(+) */
/* AD VREF(-) selection (ADREFM) */
#define _00_AD_NEGATIVE_VSS                     (0x00U) /* use AVSS as VREF(-) */
#define _20_AD_NEGATIVE_AVREFM                  (0x20U) /* use AVREFM as VREF(-) */
/* AD conversion result upper/lower bound value selection (ADRCK) */
#define _00_AD_AREA_MODE_1                      (0x00U) /* generates INTAD when ADLL <= ADCRH <= ADUL */
#define _08_AD_AREA_MODE_2_3                    (0x08U) /* generates INTAD when ADUL < ADCRH or ADLL > ADCRH */
/* AD CH number read enable(CHRDE) */
#define _00_AD_CH_NUMBER_READ_DIS               (0x00U) /* can't read AD CH number in SCAN MODE */
#define _02_AD_CH_NUMBER_READ_EN                (0x02U) /* can read AD CH number in SCAN MODE */

/*
    A/D conversion trigger mode select register (ADTRG) 
*/
/* A/D conversion trigger mode selection (ADTMD1,ADTMD0) */
#define _00_AD_TRIGGER_SOFTWARE                 (0x00U) /* software trigger mode */
#define _80_AD_TRIGGER_HARDWARE_NOWAIT          (0x80U) /* hardware trigger mode (no wait) */
#define _C0_AD_TRIGGER_HARDWARE_WAIT            (0xC0U) /* hardware trigger mode (wait) */
/* Trigger signal selection (ADTRS1, ADTRS0) (ADTRS1,ADTRS0) */
#define _00_AD_TRIGGER_INTTM01                  (0x00U) /* INTTM01 */
#define _01_AD_TRIGGER_EVENTC                   (0x01U) /* EVENTC */
#define _02_AD_TRIGGER_INTRTC                   (0x02U) /* INTRTC */
#define _03_AD_TRIGGER_INTIT                    (0x03U) /* INTIT */

/*
    AD test function register (ADTES) 
*/
/* AD test mode signal (ADTES2,ADTES1,ADTES0) */
#define _00_AD_NORMAL_INPUT                     (0x00U) /* normal mode */
#define _01_AD_ZERO_CODE                        (0x01U) /* zero code self-diagnosis */
#define _03_AD_HALF_CODE                        (0x03U) /* half code self-diagnosis */
#define _05_AD_FULL_CODE                        (0x05U) /* full code self-diagnosis */

/*
    A/D charge/discharge control register (ADNDIS) 
*/
/* AD charge/discharge selection (ADNDIS[4]) */
#define _00_AD_DISCHARGE                        (0x00U) /* ad discharge */
#define _10_AD_CHARGE                           (0x01U) /* ad charge */
/* AD charge/discharge time setting (ADNDIS[3:0]) */
#define _00_AD_NO_CHARGE_DISCHARGE              (0x00U) /* no charge/discharge */
#define _02_AD_CHARGE_DISCHARGE_2CLK            (0x02U) /* 2 ADCLK */
#define _03_AD_CHARGE_DISCHARGE_3CLK            (0x03U) /* 3 ADCLK */
#define _04_AD_CHARGE_DISCHARGE_4CLK            (0x04U) /* 4 ADCLK */
#define _05_AD_CHARGE_DISCHARGE_5CLK            (0x05U) /* 5 ADCLK */
#define _06_AD_CHARGE_DISCHARGE_6CLK            (0x06U) /* 6 ADCLK */
#define _07_AD_CHARGE_DISCHARGE_7CLK            (0x07U) /* 7 ADCLK */
#define _08_AD_CHARGE_DISCHARGE_8CLK            (0x08U) /* 8 ADCLK */
#define _09_AD_CHARGE_DISCHARGE_9CLK            (0x09U) /* 9 ADCLK */
#define _0A_AD_CHARGE_DISCHARGE_10CLK           (0x0AU) /* 10 ADCLK */
#define _0B_AD_CHARGE_DISCHARGE_11CLK           (0x0BU) /* 11 ADCLK */
#define _0C_AD_CHARGE_DISCHARGE_12CLK           (0x0CU) /* 12 ADCLK */
#define _0D_AD_CHARGE_DISCHARGE_13CLK           (0x0DU) /* 13 ADCLK */
#define _0E_AD_CHARGE_DISCHARGE_14CLK           (0x0EU) /* 14 ADCLK */
#define _0F_AD_CHARGE_DISCHARGE_15CLK           (0x0FU) /* 15 ADCLK */

// define ADM0 bit Position
#define ADCE_Pos  	0
#define FR_Pos  	3
#define FR0_Pos  	3
#define FR1_Pos  	4
#define FR2_Pos  	5
#define ADCS_Pos  	7

#define ADCE            (1<<ADCE_Pos)
#define ADCS            (1<<ADCS_Pos)

// define ADM1 bit Position
#define ADMODE_Pos  	0 
#define ADMODE0_Pos  	0
#define ADMODE1_Pos  	1 
#define ADSCM_Pos  	    3 	// 0:sequential mode; 1:one-shot mode 
#define ADMD_Pos  	    7  	// 0:select mode; 1:scan mode

// define ADM2 bit Position
#define CHRDE_Pos  	    1 
#define ADRCK_Pos  	    3 
#define ADREFM_Pos  	5 
#define ADREFP_Pos  	6 
#define ADREFP0_Pos  	6
#define ADREFP1_Pos  	7

// define ADTRG bit Position
#define ADTRS0_Pos  	0 
#define ADTRS1_Pos  	1 
#define ADTMD0_Pos  	6 
#define ADTMD1_Pos  	7 


// define ADS bit Position
#define ADISS_Pos  	    7 

#define ADISS           (1<<ADISS_Pos)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _FF_AD_ADUL_VALUE                       (0xFFU) 
#define _00_AD_ADLL_VALUE                       (0x00U) 

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15,
    ADC_CHANNEL_16,
    ADC_CHANNEL_17,
    ADC_CHANNEL_18,
    ADC_CHANNEL_19,
    ADC_CHANNEL_20,
    ADC_CHANNEL_21,
    ADC_CHANNEL_22,
    ADC_CHANNEL_23,
    ADC_CHANNEL_24,
    ADC_CHANNEL_25,
    ADC_CHANNEL_26,
    ADC_CHANNEL_27,
    ADC_CHANNEL_28,
    ADC_CHANNEL_29,
    ADC_CHANNEL_30,
    ADC_CHANNEL_31,
    ADC_CHANNEL_32,
    ADC_CHANNEL_33,
    ADC_CHANNEL_34,
    ADC_CHANNEL_35,
    ADC_CHANNEL_36,
    ADC_CHANNEL_OFF = 63U,
    ADC_TEMPERSENSOR0 = 128U,
    ADC_INTERREFVOLT
} adc_channel_t;

typedef enum
{
    ADNORMALINPUT,
    ADAVREFM = 2U,
    ADAVREFP
} test_channel_t;

typedef enum
{
    ADC_VDD_VSS_REFERENCE_VOLTAGE,
    ADC_AVREFP_AVREFM_REFERENCE_VOLTAGE,
    ADC_INVREFP_VSS_REFERENCE_VOLTAGE
} adc_vref_t;

typedef enum
{
    CLOCK_DIV32,   // fCLK/32
    CLOCK_DIV16,   // fCLK/16
    CLOCK_DIV8,    // fCLK/8
    CLOCK_DIV4,    // fCLK/4
    CLOCK_DIV2,    // fCLK/2
    CLOCK_DIV1     // fCLK/1
} adc_clock_t;

typedef enum
{
    AD_TRG_TM01,
    AD_TRG_ELC,
    AD_TRG_RTC,
    AD_TRG_IT 
} adc_trigger_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern volatile uint8_t  * gp_u1_adc_buf;           /* adc higher 8 bit result buffer address */
extern volatile uint16_t * gp_u2_adc_buf;           /* adc 12 bit result buffer address */
extern volatile uint32_t   g_AdcIntTaken;           /* adc interrupt flag */
extern volatile int16_t    g_temperature;             /* chip temperature */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void ADC_Init(void);
void ADC_Set_OperationOn(void);
void ADC_Set_OperationOff(void);
void ADC_Start(adc_channel_t ch);
void ADC_Stop(void);
//void ADC_Set_RefVoltage(adc_vref_t vref);
void ADC_Set_HardTrigger(uint8_t wait, adc_trigger_t trg);
void ADC_Set_Clock(adc_clock_t fr, uint8_t smp);
uint16_t ADC_Converse(adc_channel_t ch, uint32_t sz, uint16_t *buf);
uint16_t ADC_MidAvg_Filter(uint16_t *buf, uint8_t num);
//double adc_get_temperature(int16_t dat);
int16_t adc_get_temperature(int16_t dat);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
