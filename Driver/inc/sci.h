/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    sci.h
* @brief   This file implements device driver for SCI module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef SCI_H
#define SCI_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    IrDA Control Register (IRCR) 
*/
/* IrDA enable (IRE) */
#define _00_IRDA_COMMUNICATION_NORMAL           (0x00U) /* serial I/O pins are used for normal serial communication */
#define _80_IRDA_COMMUNICATION_IRDA             (0x80U) /* serial I/O pins are used for IrDA data communication */
/* IrDA clock selection (IRCKS2,IRCKS1,IRCKS0) */
#define _00_IRDA_B_3_16_SELECTED                (0x00U) /* B*3/16 */
#define _10_IRDA_fCLK_2_SELECTED                (0x10U) /* fCLK/2 */
#define _20_IRDA_fCLK_4_SELECTED                (0x20U) /* fCLK/4 */
#define _30_IRDA_fCLK_8_SELECTED                (0x30U) /* fCLK/8 */
#define _40_IRDA_fCLK_16_SELECTED               (0x40U) /* fCLK/16 */
#define _50_IRDA_fCLK_32_SELECTED               (0x50U) /* fCLK/32 */
#define _60_IRDA_fCLK_64_SELECTED               (0x60U) /* fCLK/64 */
/* IrTxD data polarity switching (IRTXINV) */
#define _00_IRDA_OUTPUT_IRTXD                   (0x00U) /* data to be transmitted is output to IrTxD as is */
#define _08_IRDA_OUTPUT_IRTXD_INVERTED          (0x08U) /* data to be transmitted is output to IrTxD after the polarity is inverted */
/* IrRxD data polarity switching (IRRXINV) */
#define _00_IRDA_OUTPUT_IRRXD                   (0x00U) /* IrRxD input is used as received data as is */
#define _04_IRDA_OUTPUT_IRRXD_INVERTED          (0x04U) /* IrRxD input is used as received data after the polarity is inverted */

/*
    The SPSm register is a 16-bit register that is used to select two types of operation clocks (CKm0, CKm1) that are
commonly supplied to each channel. (SPSm) 
*/
/* Section of operation clock (CKm0) (PRSm00,PRSm01,PRSm02,PRSm03) */
#define _0000_SCI_CK00_fCLK_0                   (0x0000U) /* ck00-fCLK */
#define _0001_SCI_CK00_fCLK_1                   (0x0001U) /* ck00-fCLK/2^1 */
#define _0002_SCI_CK00_fCLK_2                   (0x0002U) /* ck00-fCLK/2^2 */
#define _0003_SCI_CK00_fCLK_3                   (0x0003U) /* ck00-fCLK/2^3 */
#define _0004_SCI_CK00_fCLK_4                   (0x0004U) /* ck00-fCLK/2^4 */
#define _0005_SCI_CK00_fCLK_5                   (0x0005U) /* ck00-fCLK/2^5 */
#define _0006_SCI_CK00_fCLK_6                   (0x0006U) /* ck00-fCLK/2^6 */
#define _0007_SCI_CK00_fCLK_7                   (0x0007U) /* ck00-fCLK/2^7 */
#define _0008_SCI_CK00_fCLK_8                   (0x0008U) /* ck00-fCLK/2^8 */
#define _0009_SCI_CK00_fCLK_9                   (0x0009U) /* ck00-fCLK/2^9 */
#define _000A_SCI_CK00_fCLK_10                  (0x000AU) /* ck00-fCLK/2^10 */
#define _000B_SCI_CK00_fCLK_11                  (0x000BU) /* ck00-fCLK/2^11 */
#define _000C_SCI_CK00_fCLK_12                  (0x000CU) /* ck00-fCLK/2^12 */
#define _000D_SCI_CK00_fCLK_13                  (0x000DU) /* ck00-fCLK/2^13 */
#define _000E_SCI_CK00_fCLK_14                  (0x000EU) /* ck00-fCLK/2^14 */
#define _000F_SCI_CK00_fCLK_15                  (0x000FU) /* ck00-fCLK/2^15 */
/* Section of operation clock (CKm1) (PRSm10,PRSm11,PRSm12,PRSm13,) */
#define _0000_SCI_CK01_fCLK_0                   (0x0000U) /* ck01-fCLK */
#define _0010_SCI_CK01_fCLK_1                   (0x0010U) /* ck01-fCLK/2^1 */
#define _0020_SCI_CK01_fCLK_2                   (0x0020U) /* ck01-fCLK/2^2 */
#define _0030_SCI_CK01_fCLK_3                   (0x0030U) /* ck01-fCLK/2^3 */
#define _0040_SCI_CK01_fCLK_4                   (0x0040U) /* ck01-fCLK/2^4 */
#define _0050_SCI_CK01_fCLK_5                   (0x0050U) /* ck01-fCLK/2^5 */
#define _0060_SCI_CK01_fCLK_6                   (0x0060U) /* ck01-fCLK/2^6 */
#define _0070_SCI_CK01_fCLK_7                   (0x0070U) /* ck01-fCLK/2^7 */
#define _0080_SCI_CK01_fCLK_8                   (0x0080U) /* ck01-fCLK/2^8 */
#define _0090_SCI_CK01_fCLK_9                   (0x0090U) /* ck01-fCLK/2^9 */
#define _00A0_SCI_CK01_fCLK_10                  (0x00A0U) /* ck01-fCLK/2^10 */
#define _00B0_SCI_CK01_fCLK_11                  (0x00B0U) /* ck01-fCLK/2^11 */
#define _00C0_SCI_CK01_fCLK_12                  (0x00C0U) /* ck01-fCLK/2^12 */
#define _00D0_SCI_CK01_fCLK_13                  (0x00D0U) /* ck01-fCLK/2^13 */
#define _00E0_SCI_CK01_fCLK_14                  (0x00E0U) /* ck01-fCLK/2^14 */
#define _00F0_SCI_CK01_fCLK_15                  (0x00F0U) /* ck01-fCLK/2^15 */

/*
    Serial mode register mn (SMRmn) 
*/
/* Selection of operation clock (fMCK) of channel n (CKSmn) */
#define _0000_SCI_CLOCK_SELECT_CK00             (0x0000U) /* operation clock CKm0 set by the SPSm register */
#define _8000_SCI_CLOCK_SELECT_CK01             (0x8000U) /* operation clock CKm1 set by the SPSm register */
/* Selection of transfer clock (fTCLK) of channel n (CCSmn) */
#define _0000_SCI_CLOCK_MODE_CKS                (0x0000U) /* divided operation clock fMCK specified by the CKSmn bit */
#define _4000_SCI_CLOCK_MODE_TI0N               (0x4000U) /* clock input fSCK from the SCKp pin (slave transfer in SPI mode) */
/* Selection of start trigger source (STSmn) */
#define _0000_SCI_TRIGGER_SOFTWARE              (0x0000U) /* only software trigger is valid (selected for SPI, UART transmission, and simplified I2C) */
#define _0100_SCI_TRIGGER_RXD                   (0x0100U) /* valid edge of the RxDq pin (selected for UART reception) */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SCI_EDGE_FALL                     (0x0000U) /* falling edge is detected as the start bit.
                                                             The input communication data is captured as is */
#define _0040_SCI_EDGE_RISING                   (0x0040U) /* rising edge is detected as the start bit.
                                                             The input communication data is inverted and captured */
/* Setting of operation mode of channel n (MDmn2,MDmn1) */
#define _0000_SCI_MODE_SPI                      (0x0000U) /* SPI mode */
#define _0002_SCI_MODE_UART                     (0x0002U) /* UART mode */
#define _0004_SCI_MODE_IIC                      (0x0004U) /* simplified I2C mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SCI_TRANSFER_END                  (0x0000U) /* transfer end interrupt */
#define _0001_SCI_BUFFER_EMPTY                  (0x0001U) /* buffer empty interrupt */

/*
    Serial communication operation setting register mn (SCRmn) 
*/
/* Setting of operation mode of channel n (TXEmn,RXEmn) */
#define _0000_SCI_NOT_COMMUNICATION             (0x0000U) /* disable communication */
#define _4000_SCI_RECEPTION                     (0x4000U) /* reception only */
#define _8000_SCI_TRANSMISSION                  (0x8000U) /* transmission only */
#define _C000_SCI_RECEPTION_TRANSMISSION        (0xC000U) /* transmission/reception */
/* Selection of data and clock phase in SPI mode (DAPmn,CKPmn) */
#define _0000_SCI_TIMING_1                      (0x0000U) /* type 1 */
#define _1000_SCI_TIMING_2                      (0x1000U) /* type 2 */
#define _2000_SCI_TIMING_3                      (0x2000U) /* type 3 */
#define _3000_SCI_TIMING_4                      (0x3000U) /* type 4 */
/* Mask control of error interrupt signal (INTSREx (x = 0 to 3)) (EOCmn) */
#define _0000_SCI_INTSRE_MASK                   (0x0000U) /* disables generation of error interrupt INTSREx (INTSRx is generated) */
#define _0400_SCI_INTSRE_ENABLE                 (0x0400U) /* enables generation of error interrupt INTSREx (INTSRx is not generated if an error occurs) */
/* Setting of parity bit in UART mode (PTCmn1,PTCmn0) */
#define _0000_SCI_PARITY_NONE                   (0x0000U) /* none parity */
#define _0100_SCI_PARITY_ZERO                   (0x0100U) /* zero parity */
#define _0200_SCI_PARITY_EVEN                   (0x0200U) /* even parity */
#define _0300_SCI_PARITY_ODD                    (0x0300U) /* odd parity */
/* Selection of data transfer sequence in SPI and UART modes (DIRmn) */
#define _0000_SCI_MSB                           (0x0000U) /* inputs/outputs data with MSB first */
#define _0080_SCI_LSB                           (0x0080U) /* inputs/outputs data with LSB first */
/* Setting of stop bit in UART mode (SLCmn1,SLCmn0) */
#define _0000_SCI_STOP_NONE                     (0x0000U) /* no stop bit */
#define _0010_SCI_STOP_1                        (0x0010U) /* 1 Stop bit length = 1 bit */
#define _0020_SCI_STOP_2                        (0x0020U) /* stop bit length = 2 bits (mn = 00,02,10 only) */
/* Setting of data length in SPI and UART modes (DLSmn1,DLSmn0) */
#define _0001_SCI_LENGTH_9                      (0x0001U) /* 9-bit data length */
#define _0002_SCI_LENGTH_7                      (0x0002U) /* 7-bit data length */
#define _0003_SCI_LENGTH_8                      (0x0003U) /* 8-bit data length */

/*
    Serial flag clear trigger register mn (SIRmn) 
*/
/* Clear trigger of framing error of channel n (FECTmn) */
#define _0004_SCI_SIRMN_FECTMN                  (0x0004U) /* clears the FEFmn bit of the SSRmn register to 0 */
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define _0002_SCI_SIRMN_PECTMN                  (0x0002U) /* clears the PEFmn bit of the SSRmn register to 0 */
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define _0001_SCI_SIRMN_OVCTMN                  (0x0001U) /* clears the OVFmn bit of the SSRmn register to 0 */

/*
    Serial status register mn (SSRmn) 
*/
/* Communication status indication flag of channel n (TSFmn) */
#define _0040_SCI_UNDER_EXECUTE                 (0x0040U) /* communication is in progress */
/* Buffer register status indication flag of channel n (BFFmn) */
#define _0020_SCI_VALID_STORED                  (0x0020U) /* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEFmn) */
#define _0004_SCI_FRAM_ERROR                    (0x0004U) /* an error occurs (during UART reception) */
/* Parity error detection flag of channel n (PEFmn) */
#define _0002_SCI_PARITY_ERROR                  (0x0002U) /* an error occurs (during UART reception) or ACK is not detected (during I2C transmission) */
/* Overrun error detection flag of channel n (OVFmn) */
#define _0001_SCI_OVERRUN_ERROR                 (0x0001U) /* an overrun error occurs */

/*
    Serial channel start register m (SSm) 
*/
/* Operation start trigger of channel 3 (SSm3) */
#define _0000_SCI_CH3_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0008_SCI_CH3_START_TRG_ON              (0x0008U) /* sets the SEmn bit to 1 and enters the communication wait status */
/* Operation start trigger of channel 2 (SSm2) */
#define _0000_SCI_CH2_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0004_SCI_CH2_START_TRG_ON              (0x0004U) /* sets the SEmn bit to 1 and enters the communication wait status */
/* Operation start trigger of channel 1 (SSm1) */
#define _0000_SCI_CH1_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0002_SCI_CH1_START_TRG_ON              (0x0002U) /* sets the SEmn bit to 1 and enters the communication wait status */
/* Operation start trigger of channel 0 (SSm0) */
#define _0000_SCI_CH0_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0001_SCI_CH0_START_TRG_ON              (0x0001U) /* sets the SEmn bit to 1 and enters the communication wait status */

/*
    Format of Serial channel stop register m (STm) 
*/
/* Operation stop trigger of channel 3 (STm3) */
#define _0000_SCI_CH3_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0008_SCI_CH3_STOP_TRG_ON               (0x0008U) /* clears the SEmn bit to 0 and stops the communication operation */
/* Operation stop trigger of channel 2 (STm2) */
#define _0000_SCI_CH2_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0004_SCI_CH2_STOP_TRG_ON               (0x0004U) /* clears the SEmn bit to 0 and stops the communication operation */
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SCI_CH1_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0002_SCI_CH1_STOP_TRG_ON               (0x0002U) /* clears the SEmn bit to 0 and stops the communication operation */
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SCI_CH0_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0001_SCI_CH0_STOP_TRG_ON               (0x0001U) /* clears the SEmn bit to 0 and stops the communication operation */

/*
    Serial channel enable status register m (SEm) 
*/
/* Indication of operation enable/stop status of channel 3 (SEm3) */
#define _0000_SCI_CH3_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0008_SCI_CH3_STATUS_ENABLE             (0x0008U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 2 (SEm2) */
#define _0000_SCI_CH2_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0004_SCI_CH2_STATUS_ENABLE             (0x0004U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 1 (SEm1) */
#define _0000_SCI_CH1_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0002_SCI_CH1_STATUS_ENABLE             (0x0002U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 0 (SEm0) */
#define _0000_SCI_CH0_STATUS_DISABLE            (0x0000U) /* operation stops */
#define _0001_SCI_CH0_STATUS_ENABLE             (0x0001U) /* operation is enabled */

/*
    Serial output enable register m (SOEm) 
*/
/* Serial output enable/stop of channel 3 (SOEm3) */
#define _0000_SCI_CH3_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0008_SCI_CH3_OUTPUT_ENABLE             (0x0008U) /* enables output by serial communication operation */
/* Serial output enable/stop of channel 2 (SOEm2) */
#define _0000_SCI_CH2_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0004_SCI_CH2_OUTPUT_ENABLE             (0x0004U) /* enables output by serial communication operation */
/* Serial output enable/stop of channel 1 (SOEm1) */
#define _0000_SCI_CH1_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0002_SCI_CH1_OUTPUT_ENABLE             (0x0002U) /* enables output by serial communication operation */
/* Serial output enable/stop of channel 0 (SOEm0) */
#define _0000_SCI_CH0_OUTPUT_DISABLE            (0x0000U) /* stops output by serial communication operation */
#define _0001_SCI_CH0_OUTPUT_ENABLE             (0x0001U) /* enables output by serial communication operation */

/*
    Serial output register m (SOm) 
*/
/* Serial clock output of channel 3 (CKOm3) */
#define _0000_SCI_CH3_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0800_SCI_CH3_CLOCK_OUTPUT_1            (0x0800U) /* serial clock output value is 1 */
/* Serial clock output of channel 2 (CKOm2) */
#define _0000_SCI_CH2_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0400_SCI_CH2_CLOCK_OUTPUT_1            (0x0400U) /* serial clock output value is 1 */
/* Serial clock output of channel 1 (CKOm1) */
#define _0000_SCI_CH1_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0200_SCI_CH1_CLOCK_OUTPUT_1            (0x0200U) /* serial clock output value is 1 */
/* Serial clock output of channel 0 (CKOm0) */
#define _0000_SCI_CH0_CLOCK_OUTPUT_0            (0x0000U) /* serial clock output value is 0 */
#define _0100_SCI_CH0_CLOCK_OUTPUT_1            (0x0100U) /* serial clock output value is 1 */
/* Serial data output of channel 3 (SOm3) */
#define _0000_SCI_CH3_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0008_SCI_CH3_DATA_OUTPUT_1             (0x0008U) /* serial data output value is 1 */
/* Serial data output of channel 2 (SOm2) */
#define _0000_SCI_CH2_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0004_SCI_CH2_DATA_OUTPUT_1             (0x0004U) /* serial data output value is 1 */
/* Serial data output of channel 1 (SOm1) */
#define _0000_SCI_CH1_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0002_SCI_CH1_DATA_OUTPUT_1             (0x0002U) /* serial data output value is 1 */
/* Serial data output of channel 0 (SOm0) */
#define _0000_SCI_CH0_DATA_OUTPUT_0             (0x0000U) /* serial data output value is 0 */
#define _0001_SCI_CH0_DATA_OUTPUT_1             (0x0001U) /* serial data output value is 1 */

/*
    Serial output level register m (SOLm) 
*/
/* Selects inversion of the level of the transmit data of channel n in UART mode (SOLm2) */
#define _0000_SCI_CHANNEL2_NORMAL               (0x0000U) /* communication data is output as is */
#define _0004_SCI_CHANNEL2_INVERTED             (0x0004U) /* communication data is inverted and output */
/* Selects inversion of the level of the transmit data of channel n in UART mode (SOLm0) */
#define _0000_SCI_CHANNEL0_NORMAL               (0x0000U) /* communication data is output as is */
#define _0001_SCI_CHANNEL0_INVERTED             (0x0001U) /* communication data is inverted and output */

/*
    Serial standby control register m (SSCm) 
*/
/* Selection of whether to enable or disable the generation of communication error interrupts in the
SNOOZE mode (SSECm) */
#define _0000_SCI_INTSRE0_ENABLE                (0x0000U) /* enable the generation of error interrupts (INTSRE0/INTSRE2) */
#define _0002_SCI_INTSRE0_DISABLE               (0x0002U) /* disable the generation of error interrupts (INTSRE0/INTSRE2) */
/* Setting of the SNOOZE mode (SWCm) */
#define _0000_SCI_CH0_SNOOZE_OFF                (0x0000U) /* do not use the SNOOZE mode function */
#define _0001_SCI_CH0_SNOOZE_ON                 (0x0001U) /* use the SNOOZE mode function */

/*
    Input switch control register (ISC) 
*/
/* Channel 0 SSI00 input setting in SPI communication and slave mode (SSIE00) */
#define _00_SCI_SSI00_UNUSED                    (0x00U) /* disables SSI00 pin input */
#define _80_SCI_SSI00_USED                      (0x80U) /* enables SSI00 pin input */
/* Switching channel 3 input of timer array unit 0 (ISC1) */
#define _00_SCI_TI03_INPUT                      (0x00U) /* uses the input signal of the TI03 pin as a timer input (normal operation) */
#define _02_SCI_RxD0_INPUT                      (0x02U) /* input signal of the RxD0 pin is used as timer input */
/* Switching external interrupt (INTP0) input (ISC0) */
#define _00_SCI_INTP0_INTERRUPT                 (0x00U) /* uses the input signal of the INTP0 pin as an external interrupt (normal operation) */
#define _01_SCI_RxD0_INTERRUPT                  (0x01U) /* uses the input signal of the RxD0 pin as an external interrupt (wakeup signal detection) */

/*
    Noise filter enable register 0 (NFEN0) 
*/
/* Use of noise filter of RxD2 pin (SNFEN20) */
#define _00_SCI_RXD2_FILTER_OFF                 (0x00U) /* noise filter off */
#define _10_SCI_RXD2_FILTER_ON                  (0x10U) /* noise filter on */
/* Use of noise filter of RxD1 pin (SNFEN10) */
#define _00_SCI_RXD1_FILTER_OFF                 (0x00U) /* noise filter off */
#define _04_SCI_RXD1_FILTER_ON                  (0x04U) /* noise filter on */
/* Use of noise filter of RxD0 pin (SNFEN00) */
#define _00_SCI_RXD0_FILTER_OFF                 (0x00U) /* noise filter off */
#define _01_SCI_RXD0_FILTER_ON                  (0x01U) /* noise filter on */


/* SCI used flag */
#define _00_SCI_IIC_MASTER_IDLE                 (0x00U)
#define _01_SCI_IIC_SEND_FLAG                   (0x01U)
#define _02_SCI_IIC_RECEIVE_FLAG                (0x02U)
#define _04_SCI_IIC_SENDED_ADDRESS_FLAG         (0x04U)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _CE00_SCI_BAUDRATE_DIVISOR              (0xCE00U) /* transfer clock set by dividing the operating clock */
#define _9E00_SCI_BAUDRATE_DIVISOR              (0x9E00U) /* transfer clock set by dividing the operating clock */
#define _1800_SCI_BAUDRATE_DIVISOR              (0x1800U) /* IIC 400K@20MHz transfer clock set by dividing the operating clock */
#define _3000_SCI_BAUDRATE_DIVISOR              (0x3000U) /* IIC 200K@20MHz transfer clock set by dividing the operating clock */
#define _2600_SCI_BAUDRATE_DIVISOR              (0x2600U) /* IIC 400K@32MHz transfer clock set by dividing the operating clock */
#define _4E00_SCI_BAUDRATE_DIVISOR              (0x4E00U) /* IIC 200K@32MHz transfer clock set by dividing the operating clock */
#define _0020_SMRMN_DEFAULT_VALUE               (0x0020U) /* SMRmn default value */
#define _0004_SCRMN_DEFAULT_VALUE               (0x0004U) /* SCRmn default value */
#define IIC_WAITTIME                            (14U) /* change the waiting time according to the system */

#define SLVADDR                                 (0x98U)   /* the IIC Slave Address of DAC on motherboard */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct 
{
    uint8_t prs;  // SPS prescale value
    uint8_t sdr;  // SDR[15:9] value
} uart_baud_t;

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern const uint16_t sps_tbl[16];                     /* sps prescale lookup table */
extern volatile uint8_t * gp_uart0_tx_address;         /* uart0 send buffer address */
extern volatile uint16_t  g_uart0_tx_count;            /* uart0 send data number */
extern volatile uint8_t * gp_uart0_rx_address;         /* uart0 receive buffer address */
extern volatile uint16_t  g_uart0_rx_count;            /* uart0 receive data number */
extern volatile uint16_t  g_uart0_rx_length;           /* uart0 receive data length */
extern volatile uint8_t * gp_spi00_rx_address;         /* spi00 receive buffer address */
extern volatile uint16_t  g_spi00_rx_length;           /* spi00 receive data length */
extern volatile uint16_t  g_spi00_rx_count;            /* spi00 receive data count */
extern volatile uint8_t * gp_spi00_tx_address;         /* spi00 send buffer address */
extern volatile uint16_t  g_spi00_tx_length;           /* spi00 send data length */
extern volatile uint16_t  g_spi00_tx_count;            /* spi00 send data count */
extern volatile uint8_t * gp_spi01_rx_address;         /* spi01 receive buffer address */
extern volatile uint16_t  g_spi01_rx_length;           /* spi01 receive data length */
extern volatile uint16_t  g_spi01_rx_count;            /* spi01 receive data count */
extern volatile uint8_t * gp_spi01_tx_address;         /* spi01 send buffer address */
extern volatile uint16_t  g_spi01_tx_length;           /* spi01 send data length */
extern volatile uint16_t  g_spi01_tx_count;            /* spi01 send data count */
extern volatile uint8_t   g_iic00_master_status_flag;  /* iic00 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic00_tx_address;         /* iic00 send data pointer by master mode */
extern volatile uint16_t  g_iic00_tx_count;            /* iic00 send data size by master mode */
extern volatile uint8_t * gp_iic00_rx_address;         /* iic00 receive data pointer by master mode */
extern volatile uint16_t  g_iic00_rx_count;            /* iic00 receive data size by master mode */
extern volatile uint16_t  g_iic00_rx_length;           /* iic00 receive data length by master mode */
extern volatile uint8_t   g_iic01_master_status_flag;  /* iic01 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic01_tx_address;         /* iic01 send data pointer by master mode */
extern volatile uint16_t  g_iic01_tx_count;            /* iic01 send data size by master mode */
extern volatile uint8_t * gp_iic01_rx_address;         /* iic01 receive data pointer by master mode */
extern volatile uint16_t  g_iic01_rx_count;            /* iic01 receive data size by master mode */
extern volatile uint16_t  g_iic01_rx_length;           /* iic01 receive data length by master mode */
extern volatile uint8_t * gp_uart1_tx_address;         /* uart1 send buffer address */
extern volatile uint16_t  g_uart1_tx_count;            /* uart1 send data number */
extern volatile uint8_t * gp_uart1_rx_address;         /* uart1 receive buffer address */
extern volatile uint16_t  g_uart1_rx_count;            /* uart1 receive data number */
extern volatile uint16_t  g_uart1_rx_length;           /* uart1 receive data length */
extern volatile uint8_t * gp_spi10_rx_address;         /* spi10 receive buffer address */
extern volatile uint16_t  g_spi10_rx_length;           /* spi10 receive data length */
extern volatile uint16_t  g_spi10_rx_count;            /* spi10 receive data count */
extern volatile uint8_t * gp_spi10_tx_address;         /* spi10 send buffer address */
extern volatile uint16_t  g_spi10_tx_length;           /* spi10 send data length */
extern volatile uint16_t  g_spi10_tx_count;            /* spi10 send data count */
extern volatile uint8_t * gp_spi11_rx_address;         /* spi11 receive buffer address */
extern volatile uint16_t  g_spi11_rx_length;           /* spi11 receive data length */
extern volatile uint16_t  g_spi11_rx_count;            /* spi11 receive data count */
extern volatile uint8_t * gp_spi11_tx_address;         /* spi11 send buffer address */
extern volatile uint16_t  g_spi11_tx_length;           /* spi11 send data length */
extern volatile uint16_t  g_spi11_tx_count;            /* spi11 send data count */
extern volatile uint8_t   g_iic10_master_status_flag;  /* iic10 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic10_tx_address;         /* iic10 send data pointer by master mode */
extern volatile uint16_t  g_iic10_tx_count;            /* iic10 send data size by master mode */
extern volatile uint8_t * gp_iic10_rx_address;         /* iic10 receive data pointer by master mode */
extern volatile uint16_t  g_iic10_rx_count;            /* iic10 receive data size by master mode */
extern volatile uint16_t  g_iic10_rx_length;           /* iic10 receive data length by master mode */
extern volatile uint8_t   g_iic11_master_status_flag;  /* iic11 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic11_tx_address;         /* iic11 send data pointer by master mode */
extern volatile uint16_t  g_iic11_tx_count;            /* iic11 send data size by master mode */
extern volatile uint8_t * gp_iic11_rx_address;         /* iic11 receive data pointer by master mode */
extern volatile uint16_t  g_iic11_rx_count;            /* iic11 receive data size by master mode */
extern volatile uint16_t  g_iic11_rx_length;           /* iic11 receive data length by master mode */
extern volatile uint8_t * gp_uart2_tx_address;         /* uart2 send buffer address */
extern volatile uint16_t  g_uart2_tx_count;            /* uart2 send data number */
extern volatile uint8_t * gp_uart2_rx_address;         /* uart2 receive buffer address */
extern volatile uint16_t  g_uart2_rx_count;            /* uart2 receive data number */
extern volatile uint16_t  g_uart2_rx_length;           /* uart2 receive data length */
extern volatile uint8_t * gp_spi20_rx_address;         /* spi20 receive buffer address */
extern volatile uint16_t  g_spi20_rx_length;           /* spi20 receive data length */
extern volatile uint16_t  g_spi20_rx_count;            /* spi20 receive data count */
extern volatile uint8_t * gp_spi20_tx_address;         /* spi20 send buffer address */
extern volatile uint16_t  g_spi20_send_length;         /* spi20 send data length */
extern volatile uint16_t  g_spi20_tx_count;            /* spi20 send data count */
extern volatile uint8_t * gp_spi21_rx_address;         /* spi21 receive buffer address */
extern volatile uint16_t  g_spi21_rx_length;           /* spi21 receive data length */
extern volatile uint16_t  g_spi21_rx_count;            /* spi21 receive data count */
extern volatile uint8_t * gp_spi21_tx_address;         /* spi21 send buffer address */
extern volatile uint16_t  g_spi21_send_length;         /* spi21 send data length */
extern volatile uint16_t  g_spi21_tx_count;            /* spi21 send data count */
extern volatile uint8_t   g_iic20_master_status_flag;  /* iic20 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic20_tx_address;         /* iic20 send data pointer by master mode */
extern volatile uint16_t  g_iic20_tx_count;            /* iic20 send data size by master mode */
extern volatile uint8_t * gp_iic20_rx_address;         /* iic20 receive data pointer by master mode */
extern volatile uint16_t  g_iic20_rx_count;            /* iic20 receive data size by master mode */
extern volatile uint16_t  g_iic20_rx_length;           /* iic20 receive data length by master mode */
extern volatile uint8_t   g_iic21_master_status_flag;  /* iic21 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic21_tx_address;         /* iic21 send data pointer by master mode */
extern volatile uint16_t  g_iic21_tx_count;            /* iic21 send data size by master mode */
extern volatile uint8_t * gp_iic21_rx_address;         /* iic21 receive data pointer by master mode */
extern volatile uint16_t  g_iic21_rx_count;            /* iic21 receive data size by master mode */
extern volatile uint16_t  g_iic21_rx_length;           /* iic21 receive data length by master mode */
extern volatile uint8_t g_iic00_tx_end;                /* iic00 send data end */
extern volatile uint8_t g_iic00_rx_end;                /* iic00 receive data end */
extern volatile uint8_t g_iic01_tx_end;                /* iic01 send data end */
extern volatile uint8_t g_iic01_rx_end;                /* iic01 receive data end */
extern volatile uint8_t g_iic10_tx_end;                /* iic10 send data end */
extern volatile uint8_t g_iic10_rx_end;                /* iic10 receive data end */
extern volatile uint8_t g_iic11_tx_end;                /* iic11 send data end */
extern volatile uint8_t g_iic11_rx_end;                /* iic11 receive data end */
extern volatile uint8_t g_iic20_tx_end;                /* iic20 send data end */
extern volatile uint8_t g_iic20_rx_end;                /* iic20 receive data end */
extern volatile uint8_t g_iic21_tx_end;                /* iic21 send data end */
extern volatile uint8_t g_iic21_rx_end;                /* iic21 receive data end */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
MD_STATUS UART0_Init(uint32_t freq, uint32_t baud);
MD_STATUS UART0_BaudRate(uint32_t fclk_freq, uint32_t baud);
void UART0_Send(uint8_t ch);
char UART0_Receive(void);
void SPI00_Start(void);
void SPI00_Stop(void);
void SPI00_MasterInit(spi_mode_t mode);
MD_STATUS SPI00_MasterSendReceive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
MD_STATUS SPI00_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI00_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI00_SlaveInit(spi_mode_t mode);
MD_STATUS SPI00_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI00_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI01_Start(void);
void SPI01_Stop(void);
void SPI01_MasterInit(spi_mode_t mode);
MD_STATUS SPI01_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI01_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI01_SlaveInit(spi_mode_t mode);
MD_STATUS SPI01_SlaveSendReceive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
MD_STATUS SPI01_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI01_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
void IIC00_Init(void);
void IIC00_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IIC00_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IIC00_Stop(void);
void IIC00_StartCondition(void);
void IIC00_StopCondition(void);
void IIC01_Init(void);
void IIC01_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IIC01_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IIC01_Stop(void);
void IIC01_StartCondition(void);
void IIC01_StopCondition(void);
MD_STATUS UART1_Init(uint32_t freq, uint32_t baud);
MD_STATUS UART1_BaudRate(uint32_t fclk_freq, uint32_t baud);
void UART1_Start(void);
void UART1_Stop(void);
MD_STATUS UART1_Receive(uint8_t * const rx_buf, uint16_t rx_num);
MD_STATUS UART1_Send(uint8_t * const tx_buf, uint16_t tx_num);
void SPI10_Start(void);
void SPI10_Stop(void);
void SPI10_MasterInit(spi_mode_t mode);
MD_STATUS SPI10_MasterSendReceive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
MD_STATUS SPI10_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI10_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI10_SlaveInit(spi_mode_t mode);
MD_STATUS SPI10_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI10_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI11_Start(void);
void SPI11_Stop(void);
void SPI11_MasterInit(spi_mode_t mode);
MD_STATUS SPI11_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI11_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI11_SlaveInit(spi_mode_t mode);
MD_STATUS SPI11_SlaveSendReceive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
MD_STATUS SPI11_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI11_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
void IIC10_Init(void);
void IIC10_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IIC10_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IIC10_Stop(void);
void IIC10_StartCondition(void);
void IIC10_StopCondition(void);
void IIC11_Init(void);
void IIC11_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IIC11_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IIC11_Stop(void);
void IIC11_StartCondition(void);
void IIC11_StopCondition(void);
MD_STATUS UART2_Init(uint32_t freq, uint32_t baud);
MD_STATUS UART2_BaudRate(uint32_t fclk_freq, uint32_t baud);
void UART2_Start(void);
void UART2_Stop(void);
MD_STATUS UART2_Receive(uint8_t * const rx_buf, uint16_t rx_num);
MD_STATUS UART2_Send(uint8_t * const tx_buf, uint16_t tx_num);
void SPI20_MasterInit(spi_mode_t mode);
void SPI20_Start(void);
void SPI20_Stop(void);
MD_STATUS SPI20_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI20_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI20_SlaveInit(spi_mode_t mode);
MD_STATUS SPI20_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI20_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI21_MasterInit(spi_mode_t mode);
void SPI21_Start(void);
void SPI21_Stop(void);
MD_STATUS SPI21_MasterSendReceive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
MD_STATUS SPI21_MasterSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI21_MasterReceive(uint8_t * const rx_buf, uint16_t rx_num);
void SPI21_SlaveInit(spi_mode_t mode);
MD_STATUS SPI21_SlaveSend(uint8_t * const tx_buf, uint16_t tx_num);
MD_STATUS SPI21_SlaveReceive(uint8_t * const rx_buf, uint16_t rx_num);
void IIC20_Init(void);
void IIC20_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IIC20_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IIC20_Stop(void);
void IIC20_StartCondition(void);
void IIC20_StopCondition(void);
void IIC21_Init(void);
void IIC21_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IIC21_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IIC21_Stop(void);
void IIC21_StartCondition(void);
void IIC21_StopCondition(void);
static void uart0_callback_receiveend(void);
static void uart0_callback_softwareoverrun(uint16_t rx_data);
static void uart0_callback_sendend(void);
static void uart0_callback_error(uint8_t err_type);
static void spi00_callback_receiveend(void);
static void spi00_callback_sendend(void);
static void spi00_callback_error(uint8_t err_type);
static void spi01_callback_receiveend(void);
static void spi01_callback_sendend(void);
static void spi01_callback_error(uint8_t err_type);
static void iic00_callback_master_receiveend(void);
static void iic00_callback_master_sendend(void);
static void iic00_callback_master_error(MD_STATUS flag);
static void iic01_callback_master_receiveend(void);
static void iic01_callback_master_sendend(void);
static void iic01_callback_master_error(MD_STATUS flag);
static void uart1_callback_receiveend(void);
static void uart1_callback_softwareoverrun(uint16_t rx_data);
static void uart1_callback_sendend(void);
static void uart1_callback_error(uint8_t err_type);
static void spi10_callback_receiveend(void);
static void spi10_callback_sendend(void);
static void spi10_callback_error(uint8_t err_type);
static void spi11_callback_receiveend(void);
static void spi11_callback_sendend(void);
static void spi11_callback_error(uint8_t err_type);
static void iic10_callback_master_receiveend(void);
static void iic10_callback_master_sendend(void);
static void iic10_callback_master_error(MD_STATUS flag);
static void iic11_callback_master_receiveend(void);
static void iic11_callback_master_sendend(void);
static void iic11_callback_master_error(MD_STATUS flag);
static void uart2_callback_receiveend(void);
static void uart2_callback_softwareoverrun(uint16_t rx_data);
static void uart2_callback_sendend(void);
static void uart2_callback_error(uint8_t err_type);
static void spi20_callback_receiveend(void);
static void spi20_callback_sendend(void);
static void spi20_callback_error(uint8_t err_type);
static void spi21_callback_receiveend(void);
static void spi21_callback_sendend(void);
static void spi21_callback_error(uint8_t err_type);
static void iic20_callback_master_receiveend(void);
static void iic20_callback_master_sendend(void);
static void iic20_callback_master_error(MD_STATUS flag);
static void iic21_callback_master_receiveend(void);
static void iic21_callback_master_sendend(void);
static void iic21_callback_master_error(MD_STATUS flag);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
