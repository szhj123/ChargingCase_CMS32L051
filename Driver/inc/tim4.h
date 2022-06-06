/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    tim4.h
* @brief   This file implements device driver for TM4 module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef TM4_H
#define TM4_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Timer Clock Select Register m (TPSm) 
*/
/* Operating mode and clear mode selection (PRSm03,PRSm02,PRSm01,PRSm00) */
#define _0000_TM4_CKM0_fCLK_0                   (0x0000U) /* ckm0 - fCLK */
#define _0001_TM4_CKM0_fCLK_1                   (0x0001U) /* ckm0 - fCLK/2^1 */
#define _0002_TM4_CKM0_fCLK_2                   (0x0002U) /* ckm0 - fCLK/2^2 */
#define _0003_TM4_CKM0_fCLK_3                   (0x0003U) /* ckm0 - fCLK/2^3 */
#define _0004_TM4_CKM0_fCLK_4                   (0x0004U) /* ckm0 - fCLK/2^4 */
#define _0005_TM4_CKM0_fCLK_5                   (0x0005U) /* ckm0 - fCLK/2^5 */
#define _0006_TM4_CKM0_fCLK_6                   (0x0006U) /* ckm0 - fCLK/2^6 */
#define _0007_TM4_CKM0_fCLK_7                   (0x0007U) /* ckm0 - fCLK/2^7 */
#define _0008_TM4_CKM0_fCLK_8                   (0x0008U) /* ckm0 - fCLK/2^8 */
#define _0009_TM4_CKM0_fCLK_9                   (0x0009U) /* ckm0 - fCLK/2^9 */
#define _000A_TM4_CKM0_fCLK_10                  (0x000AU) /* ckm0 - fCLK/2^10 */
#define _000B_TM4_CKM0_fCLK_11                  (0x000BU) /* ckm0 - fCLK/2^11 */
#define _000C_TM4_CKM0_fCLK_12                  (0x000CU) /* ckm0 - fCLK/2^12 */
#define _000D_TM4_CKM0_fCLK_13                  (0x000DU) /* ckm0 - fCLK/2^13 */
#define _000E_TM4_CKM0_fCLK_14                  (0x000EU) /* ckm0 - fCLK/2^14 */
#define _000F_TM4_CKM0_fCLK_15                  (0x000FU) /* ckm0 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm13,PRSm12,PRSm11,PRSm10) */
#define _0000_TM4_CKM1_fCLK_0                   (0x0000U) /* ckm1 - fCLK */
#define _0010_TM4_CKM1_fCLK_1                   (0x0010U) /* ckm1 - fCLK/2^1 */
#define _0020_TM4_CKM1_fCLK_2                   (0x0020U) /* ckm1 - fCLK/2^2 */
#define _0030_TM4_CKM1_fCLK_3                   (0x0030U) /* ckm1 - fCLK/2^3 */
#define _0040_TM4_CKM1_fCLK_4                   (0x0040U) /* ckm1 - fCLK/2^4 */
#define _0050_TM4_CKM1_fCLK_5                   (0x0050U) /* ckm1 - fCLK/2^5 */
#define _0060_TM4_CKM1_fCLK_6                   (0x0060U) /* ckm1 - fCLK/2^6 */
#define _0070_TM4_CKM1_fCLK_7                   (0x0070U) /* ckm1 - fCLK/2^7 */
#define _0080_TM4_CKM1_fCLK_8                   (0x0080U) /* ckm1 - fCLK/2^8 */
#define _0090_TM4_CKM1_fCLK_9                   (0x0090U) /* ckm1 - fCLK/2^9 */
#define _00A0_TM4_CKM1_fCLK_10                  (0x00A0U) /* ckm1 - fCLK/2^10 */
#define _00B0_TM4_CKM1_fCLK_11                  (0x00B0U) /* ckm1 - fCLK/2^11 */
#define _00C0_TM4_CKM1_fCLK_12                  (0x00C0U) /* ckm1 - fCLK/2^12 */
#define _00D0_TM4_CKM1_fCLK_13                  (0x00D0U) /* ckm1 - fCLK/2^13 */
#define _00E0_TM4_CKM1_fCLK_14                  (0x00E0U) /* ckm1 - fCLK/2^14 */
#define _00F0_TM4_CKM1_fCLK_15                  (0x00F0U) /* ckm1 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm21,PRSm20) */
#define _0000_TM4_CKM2_fCLK_1                   (0x0000U) /* ckm2 - fCLK/2^1 */
#define _0100_TM4_CKM2_fCLK_2                   (0x0100U) /* ckm2 - fCLK/2^2 */
#define _0200_TM4_CKM2_fCLK_4                   (0x0200U) /* ckm2 - fCLK/2^4 */
#define _0300_TM4_CKM2_fCLK_6                   (0x0300U) /* ckm2 - fCLK/2^6 */
/* Operating mode and clear mode selection (30PRSm31,PRSm30) */
#define _0000_TM4_CKM3_fCLK_8                   (0x0000U) /* ckm3 - fCLK/2^8 */
#define _1000_TM4_CKM3_fCLK_10                  (0x1000U) /* ckm3 - fCLK/2^10 */
#define _2000_TM4_CKM3_fCLK_12                  (0x2000U) /* ckm3 - fCLK/2^12 */
#define _3000_TM4_CKM3_fCLK_14                  (0x3000U) /* ckm3 - fCLK/2^14 */

/*
    Timer Channel Start Register m (TSm) 
*/
/* Operation enable (start) trigger of channel 3 higher 8 bits (TSHm3) */
#define _0000_TM4_CH3_H8_START_TRG_OFF          (0x0000U) /* no trigger operation */
#define _0800_TM4_CH3_H8_START_TRG_ON           (0x0800U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 1 higher 8 bits (TSHm1) */
#define _0000_TM4_CH1_H8_START_TRG_OFF          (0x0000U) /* no trigger operation */
#define _0200_TM4_CH1_H8_START_TRG_ON           (0x0200U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 3 (TSm3) */
#define _0000_TM4_CH3_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0008_TM4_CH3_START_TRG_ON              (0x0008U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 2 (TSm2) */
#define _0000_TM4_CH2_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0004_TM4_CH2_START_TRG_ON              (0x0004U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 1 (TSm1) */
#define _0000_TM4_CH1_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0002_TM4_CH1_START_TRG_ON              (0x0002U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 0 (TSm0) */
#define _0000_TM4_CH0_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0001_TM4_CH0_START_TRG_ON              (0x0001U) /* operation is enabled (start trigger is generated) */

/*
    Timer Channel Stop Register m (TTm) 
*/
/* Operation stop trigger of channel 3 higher 8 bits (TTHm3) */
#define _0000_TM4_CH3_H8_STOP_TRG_OFF           (0x0000U) /* no trigger operation */
#define _0800_TM4_CH3_H8_STOP_TRG_ON            (0x0800U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 higher 8 bits (TTHm1) */
#define _0000_TM4_CH1_H8_STOP_TRG_OFF           (0x0000U) /* no trigger operation */
#define _0200_TM4_CH1_H8_STOP_TRG_ON            (0x0200U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 (TTm3) */
#define _0000_TM4_CH3_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0008_TM4_CH3_STOP_TRG_ON               (0x0008U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 2 (TTm2) */
#define _0000_TM4_CH2_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0004_TM4_CH2_STOP_TRG_ON               (0x0004U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (TTm1) */
#define _0000_TM4_CH1_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0002_TM4_CH1_STOP_TRG_ON               (0x0002U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 0 (TTm0) */
#define _0000_TM4_CH0_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0001_TM4_CH0_STOP_TRG_ON               (0x0001U) /* operation is stopped (stop trigger is generated) */

/*
    Timer Mode Register mn (TMRmn) 
*/
/* Selection of macro clock (MCK) of channel n (CKSmn1,CKSmn0) */
#define _0000_TM4_CLOCK_SELECT_CKM0             (0x0000U) /* operation clock CK0 set by PRS register */
#define _8000_TM4_CLOCK_SELECT_CKM1             (0x8000U) /* operation clock CK1 set by PRS register */
#define _4000_TM4_CLOCK_SELECT_CKM2             (0x4000U) /* operation clock CK2 set by PRS register */
#define _C000_TM4_CLOCK_SELECT_CKM3             (0xC000U) /* operation clock CK3 set by PRS register */
/* Selection of count clock (CCK) of channel n (CCSmn) */
#define _0000_TM4_CLOCK_MODE_CKS                (0x0000U) /* macro clock MCK specified by CKSmn bit */
#define _1000_TM4_CLOCK_MODE_TIMN               (0x1000U) /* valid edge of input signal input from TImn pin */
/* Operation explanation of channel 1 or 3 (SPLITmn) */
#define _0000_TM4_16BITS_MODE                   (0x0000U) /* operates as 16 bits timer */
#define _0800_TM4_8BITS_MODE                    (0x0800U) /* operates as 8 bits timer */
/* Selection of slave/master of channel n (MASTERmn) */
#define _0000_TM4_COMBINATION_SLAVE             (0x0000U) /* operates as slave channel */
#define _0800_TM4_COMBINATION_MASTER            (0x0800U) /* operates as master channel */
/* Setting of start trigger or capture trigger of channel n (STSmn2,STSmn1,STSmn0) */
#define _0000_TM4_TRIGGER_SOFTWARE              (0x0000U) /* only software trigger start is valid */
#define _0100_TM4_TRIGGER_TIMN_VALID            (0x0100U) /* TImn input edge is used as a start/capture trigger */
#define _0200_TM4_TRIGGER_TIMN_BOTH             (0x0200U) /* TImn input edges are used as a start/capture trigger */
#define _0400_TM4_TRIGGER_MASTER_INT            (0x0400U) /* interrupt signal of the master channel is used */
/* Selection of TImn pin input valid edge (CISmn1,CISmn0) */
#define _0000_TM4_TIMN_EDGE_FALLING             (0x0000U) /* falling edge */
#define _0040_TM4_TIMN_EDGE_RISING              (0x0040U) /* rising edge */
#define _0080_TM4_TIMN_EDGE_BOTH_LOW            (0x0080U) /* both edges (when low-level width is measured) */
#define _00C0_TM4_TIMN_EDGE_BOTH_HIGH           (0x00C0U) /* both edges (when high-level width is measured) */
/* Operation mode of channel n (MDmn3,MDmn2,MDmn1) */
#define _0000_TM4_MODE_INTERVAL_TIMER           (0x0000U) /* interval timer mode */
#define _0004_TM4_MODE_CAPTURE                  (0x0004U) /* capture mode */
#define _0006_TM4_MODE_EVENT_COUNT              (0x0006U) /* event counter mode */
#define _0008_TM4_MODE_ONE_COUNT                (0x0008U) /* one count mode */
#define _000C_TM4_MODE_HIGHLOW_MEASURE          (0x000CU) /* high-/low-level width measurement mode */
/* Setting of starting counting and interrupt (MDmn0) */
#define _0000_TM4_START_INT_UNUSED              (0x0000U) /* interrupt is not generated when counting is started */
#define _0001_TM4_START_INT_USED                (0x0001U) /* interrupt is generated when counting is started */
/* Operation mode of channel n (MDmn3,MDmn2,MDmn1,MDmn0) */
#define _0001_TM4_MODE_PWM_MASTER               (0x0001U) /* PWM function (master channel) mode */
#define _0009_TM4_MODE_PWM_SLAVE                (0x0009U) /* PWM function (slave channel) mode */
#define _0008_TM4_MODE_ONESHOT                  (0x0008U) /* one-shot pulse output mode */

/*
    Timer Output Mode Register m (TOMm) 
*/
/* Timer output of channel n (TOMm3) */
#define _0000_TM4_CH3_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0008_TM4_CH3_SLAVE_OUTPUT              (0x0008U) /* slave channel output mode */
/* Control of timer output mode of channel 2 (TOMm2) */
#define _0000_TM4_CH2_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0004_TM4_CH2_SLAVE_OUTPUT              (0x0004U) /* slave channel output mode */
/* Control of timer output mode of channel 1 (TOMm1) */
#define _0000_TM4_CH1_MASTER_OUTPUT             (0x0000U) /* master channel output mode */
#define _0002_TM4_CH1_SLAVE_OUTPUT              (0x0002U) /* slave channel output mode */

/*
    Timer Output Level Register 0 (TOLm) 
*/
/* Control of timer output level of channel 3 (TOLm3) */
#define _0000_TM4_CH3_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0008_TM4_CH3_OUTPUT_LEVEL_L            (0x0008U) /* inverted output (active-low) */
/* Control of timer output level of channel 2 (TOLm2) */
#define _0000_TM4_CH2_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0004_TM4_CH2_OUTPUT_LEVEL_L            (0x0004U) /* inverted output (active-low) */
/* Control of timer output level of channel 1 (TOLm1) */
#define _0000_TM4_CH1_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0002_TM4_CH1_OUTPUT_LEVEL_L            (0x0002U) /* inverted output (active-low) */

/*
    Timer Output Register m (TOm) 
*/
/* Timer output of channel 3 (TOm3) */
#define _0000_TM4_CH3_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0008_TM4_CH3_OUTPUT_VALUE_1            (0x0008U) /* timer output value is "1" */
/* Timer output of channel 2 (TOm2) */
#define _0000_TM4_CH2_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0004_TM4_CH2_OUTPUT_VALUE_1            (0x0004U) /* timer output value is "1" */
/* Timer output of channel 1 (TOm1) */
#define _0000_TM4_CH1_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0002_TM4_CH1_OUTPUT_VALUE_1            (0x0002U) /* timer output value is "1" */
/* Timer output of channel 0 (TOm0) */
#define _0000_TM4_CH0_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0001_TM4_CH0_OUTPUT_VALUE_1            (0x0001U) /* timer output value is "1" */

/*
    Timer Output Enable Register m (TOEm) 
*/
/* Timer output enable/disable of channel 3 (TOEm3) */
#define _0000_TM4_CH3_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0008_TM4_CH3_OUTPUT_ENABLE             (0x0008U) /* timer output is enabled */
/* Timer output enable/disable of channel 2 (TOEm2) */
#define _0000_TM4_CH2_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0004_TM4_CH2_OUTPUT_ENABLE             (0x0004U) /* timer output is enabled */
/* Timer output enable/disable of channel 1 (TOEm1) */
#define _0000_TM4_CH1_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0002_TM4_CH1_OUTPUT_ENABLE             (0x0002U) /* timer output is enabled */
/* Timer output enable/disable of channel 0 (TOEm0) */
#define _0000_TM4_CH0_OUTPUT_DISABLE            (0x0000U) /* timer output is disabled */
#define _0001_TM4_CH0_OUTPUT_ENABLE             (0x0001U) /* timer output is enabled */

/*
    Timer I/O select register 0 (TIOS0) 
*/
/* Selection of timer input used with channel 0 (TIS07,TIS06,TIS05) */
#define _00_TM4_CH0_INPUT_TI00                  (0x00U) /* input signal of timer input pin (TI00) */
#define _20_TM4_CH0_NOT_OUTPUT_TRDIOB0          (0x20U) /* PWMOP not ouppuit from TRDIOB0 */
#define _40_TM4_CH0_NOT_OUTPUT_TRDIOD0          (0x40U) /* PWMOP not ouppuit from TRDIOD0 */
#define _60_TM4_CH0_NOT_OUTPUT_TRDIOA1          (0x60U) /* PWMOP not ouppuit from TRDIOA1 */
#define _80_TM4_CH0_NOT_OUTPUT_TRDIOC1          (0x80U) /* PWMOP not ouppuit from TRDIOC1 */
#define _A0_TM4_CH0_NOT_OUTPUT_TRDIOB1          (0xA0U) /* PWMOP not ouppuit from TRDIOB1 */
#define _C0_TM4_CH0_NOT_OUTPUT_TRDIOD1          (0xC0U) /* PWMOP not ouppuit from TRDIOD1 */
#define _E0_TM4_CH0_NOT_OUTPUT_TRDIOC0          (0xE0U) /* PWMOP not ouppuit from TRDIOC0 */
/* Selection of timer input used with channel 0 (TIS04) */
#define _00_TM4_CH0_INPUT_TIS0765               (0x00U) /* input signal specified by the TIS07 to TIS05 bits */
#define _10_TM4_CH0_INPUT_ELC                   (0x10U) /* event input signal from ELC */
/* Enable/disable of TM4 channel 2 output to P17 pin (TIS03) */
#define _00_TM4_CH2_OUTPUT_ENABLE               (0x00U) /* output enabled */
#define _08_TM4_CH2_OUTPUT_DISABLE              (0x08U) /* output disabled */
/* Selection of timer input used with channel 1 (TIS02,TIS01,TIS00) */
#define _00_TM4_CH1_INPUT_TI01                  (0x00U) /* input signal of timer input pin (TI01) */
#define _01_TM4_CH1_INPUT_ELC                   (0x01U) /* event input signal from ELC */
#define _02_TM4_CH1_INPUT_TI01                  (0x02U) /* input signal of timer input pin (TI01) */
#define _03_TM4_CH1_INPUT_TI01                  (0x03U) /* input signal of timer input pin (TI01) */
#define _04_TM4_CH1_INPUT_fIL                   (0x04U) /* low-speed on-chip oscillator clock (fIL) */
#define _05_TM4_CH1_INPUT_fSUB                  (0x05U) /* subsystem clock (fSUB) */

/*
    Noise Filter Enable Register 1  (NFEN1) 
*/
/* Enable/disable using noise filter of TI03 pin or RxD0 pin input signal (TNFEN03) */
#define _00_TM4_CH3_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _08_TM4_CH3_NOISE_ON                    (0x08U) /* noise filter ON */
/* Enable/disable using noise filter of TI02 pin input signal (TNFEN02) */
#define _00_TM4_CH2_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _04_TM4_CH2_NOISE_ON                    (0x04U) /* noise filter ON */
/* Enable/disable using noise filter of TI01 pin input signal (TNFEN01) */
#define _00_TM4_CH1_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _02_TM4_CH1_NOISE_ON                    (0x02U) /* noise filter ON */
/* Enable/disable using noise filter of TI00 pin input signal (TNFEN00) */
#define _00_TM4_CH0_NOISE_OFF                   (0x00U) /* noise filter OFF */
#define _01_TM4_CH0_NOISE_ON                    (0x01U) /* noise filter ON */

/*
    Timer Status Register mn (TSRmn)
*/
/* Counter overflow status of channel n (OVF) */
#define _0000_TM4_OVERFLOW_NOT_OCCURS     (0x0000U) /* overflow does not occur */
#define _0001_TM4_OVERFLOW_OCCURS         (0x0001U) /* overflow occurs */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Clock divisor for TM40 channel 1 */
#define TM40_CHANNEL1_DIVISOR             (1U)      /* fCLK */

/***********************************************************************************************************************
Register bit definitions
***********************************************************************************************************************/
#define TMRMN_CIS_Pos   6

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
	TM4_CHANNEL_0 = 1U,
	TM4_CHANNEL_1 = 2U,
	TM4_CHANNEL_2 = 4U,
	TM4_CHANNEL_3 = 8U
} tm4_channel_t;

typedef enum 
{
	TM4_CH0_INPUT_TI00 			= (0x00U), /* intput signal of timeer input pin (TI00) */
	TM4_CH0_INPUT_ELC 			= (0x10U), /* event input signal from ELC */
	TM4_CH1_INPUT_TI01			= (0x00U), /* input signal of timer input pin (TI01) */
	TM4_CH1_INPUT_ELC 			= (0x01U), /* event input signal from ELC */
	TM4_CH1_INPUT_fIL 			= (0x04U), /* low-speed on-chip oscillator clock (fIL) */
	TM4_CH1_INPUT_fSUB			= (0x05U), /* subsystem clock (fSUB) */
	TM4_CH2_INPUT_TI02 			= (0x00U), /* intput signal of timeer input pin (TI02) */
	TM4_CH3_INPUT_TI03 			= (0x00U)  /* intput signal of timeer input pin (TI03) */
} tm4_input_t;

typedef enum 
{
	TM4_TI_NEGEDGE 	 		= (0x00U), /* falling edge of TI */
	TM4_TI_POSEDGE 	 		= (0x01U), /* rising edge of TI */
	TM4_TI_BOTHEDGE 	 	= (0x02U), /* both edge of TI */
} tm4_edge_t;

typedef enum 
{
	TM4_PULSE_PERIOD_FALLING 	= (0x00U), /* measure falling edge interval of TI */
	TM4_PULSE_PERIOD_RISING 	= (0x01U), /* measure rising edge interval of TI */
	TM4_PULSE_PERIOD_BOTH 	 	= (0x02U), /* measure both edge interval of TI */
	TM4_PULSE_WIDTH_LOW 	    = (0x02U), /* measure low level width of TI */
	TM4_PULSE_WIDTH_HIGH 	    = (0x03U)  /* measure high level width of TI */
} tm4_pulse_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
/* For TM40 pulse measurement */
extern volatile uint32_t g_tm40_ch0_width;
extern volatile uint32_t g_tm40_ch1_width;
extern volatile uint32_t g_tm40_ch2_width;
extern volatile uint32_t g_tm40_ch3_width;
extern volatile uint32_t g_inttm00Taken;
extern volatile uint32_t g_inttm01Taken;
extern volatile uint32_t g_inttm02Taken;
extern volatile uint32_t g_inttm03Taken;
/* For TM41 pulse measurement */
extern volatile uint32_t g_tm41_ch0_width;
extern volatile uint32_t g_tm41_ch1_width;
extern volatile uint32_t g_tm41_ch2_width;
extern volatile uint32_t g_tm41_ch3_width;
extern volatile uint32_t g_inttm10Taken;
extern volatile uint32_t g_inttm11Taken;
extern volatile uint32_t g_inttm12Taken;
extern volatile uint32_t g_inttm13Taken;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void TM40_IntervalTimer(tm4_channel_t ch, uint16_t num);
void TM40_SquareOutput(tm4_channel_t ch, uint16_t num);
void TM40_FreqDivider(tm4_channel_t ch, tm4_edge_t edge, uint16_t num);
void TM40_EventCount(tm4_channel_t ch, tm4_input_t input, tm4_edge_t edge, uint16_t num);
uint32_t TM40_Get_PulsePeriod(tm4_channel_t ch, tm4_input_t input, tm4_pulse_t edge);
uint32_t TM40_Get_PulseWidth(tm4_channel_t ch, tm4_input_t input, tm4_pulse_t level);
void TM40_DelayCounter(tm4_channel_t ch, tm4_input_t input, tm4_edge_t edge, uint16_t delay);
void TM40_One_Shot_Pulse_Output(tm4_edge_t edge, uint16_t delay, uint16_t width);
void TM40_PWM_1Period_1Duty(uint16_t period, uint16_t duty);
void TM40_PWM_1Period_2Duty(uint16_t period, uint16_t duty1, uint16_t duty2);
void TM40_PWM_1Period_3Duty(uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3);
void TM40_PWM_2Period_2Duty(uint16_t period1, uint16_t duty1, uint16_t period2, uint16_t duty2);
void TM40_Channel_Start(tm4_channel_t ch);
void TM40_Channel_Stop(tm4_channel_t ch);

void TM41_IntervalTimer(tm4_channel_t ch, uint16_t num);
void TM41_SquareOutput(tm4_channel_t ch, uint16_t num);
void TM41_FreqDivider(tm4_channel_t ch, tm4_edge_t edge, uint16_t num);
void TM41_EventCount(tm4_channel_t ch, tm4_edge_t edge, uint16_t num);
uint32_t TM41_Get_PulsePeriod(tm4_channel_t ch, tm4_pulse_t edge);
uint32_t TM41_Get_PulseWidth(tm4_channel_t ch, tm4_pulse_t level);
void TM41_DelayCounter(tm4_channel_t ch, tm4_edge_t edge, uint16_t delay);
void TM41_One_Shot_Pulse_Output(tm4_edge_t edge, uint16_t delay, uint16_t width);
void TM41_PWM_1Period_1Duty(uint16_t period, uint16_t duty);
void TM41_PWM_1Period_2Duty(uint16_t period, uint16_t duty1, uint16_t duty2);
void TM41_PWM_1Period_3Duty(uint16_t period, uint16_t duty1, uint16_t duty2, uint16_t duty3);
void TM41_PWM_2Period_2Duty(uint16_t period1, uint16_t duty1, uint16_t period2, uint16_t duty2);
void TM41_Channel_Start(tm4_channel_t ch);
void TM41_Channel_Stop(tm4_channel_t ch);

#endif
