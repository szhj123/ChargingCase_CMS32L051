/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    iica.h
* @brief   This file implements device driver for IICA module.
* @version 1.0.0 
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef IICA_H
#define IICA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    IICA control register n0 (IICCTLn0) 
*/
/* I2C operation enable (IICEn) */
#define _00_IICA_OPERATION_STOP                       (0x00U) /* stop operation */
#define _80_IICA_OPERATION_ENABLE                     (0x80U) /* enable operation */
/* Exit from communications (LRELn) */
#define _00_IICA_OPERATION_NORMAL                     (0x00U) /* normal operation */
#define _40_IICA_OPERATION_STANDBY                    (0x40U) /* this exits from the current communications and sets standby mode */
/* Wait cancellation (WRELn) */
#define _00_IICA_NOTCANCEL_WAIT                       (0x00U) /* do not cancel wait */
#define _20_IICA_CANCEL_WAIT                          (0x20U) /* cancel wait */
/* Enable/disable generation of interrupt request when stop condition is detected (SPIEn) */
#define _00_IICA_INTERRUPT_REQUEST_DISABLE            (0x00U) /* disable */
#define _10_IICA_INTERRUPT_REQUEST_ENABLE             (0x10U) /* enable */
/* Control of wait and interrupt request generation (WTIMn) */
#define _00_IICA_INTERRUPT_REQUEST_EIGHTH             (0x00U) /* interrupt request is generated at the eighth clock's falling edge */
#define _08_IICA_INTERRUPT_REQUEST_NINTH              (0x08U) /* interrupt request is generated at the ninth clock's falling edge */
/* Acknowledgment control (ACKEn) */
#define _00_IICA_ACKOWNLEDGMENT_DISABLE               (0x00U) /* disable acknowledgment */
#define _04_IICA_ACKOWNLEDGMENT_ENABLE                (0x04U) /* enable acknowledgment */
/* Start condition trigger (STTn) */
#define _00_IICA_NOTGENERATE_START                    (0x00U) /* do not generate a start condition */
#define _02_IICA_GENERATE_START                       (0x02U) /* generate a start condition */
/* Stop condition trigger (SPTn) */
#define _00_IICA_NOTGENERATE_STOP                     (0x00U) /* stop condition is not generated */
#define _01_IICA_GENERATE_STOP                        (0x01U) /* stop condition is generated */

/*
    IICA status register n (IICSn) 
*/
/* Master status check flag (MSTSn) */
#define _00_IICA_SLAVE_DEVICE                         (0x00U) /* slave device status or communication standby status */
#define _80_IICA_MASTER_DEVICE                        (0x80U) /* master device communication status */
/* Detection of arbitration loss (ALDn) */
#define _00_IICA_RESULT_WIN                           (0x00U) /* this status means either that there was no arbitration or that the arbitration result was a win */
#define _40_IICA_RESULT_LOSS                          (0x40U) /* this status indicates the arbitration result was a loss. The MSTSn bit is cleared */
/* Detection of extension code reception (EXCn) */
#define _00_IICA_NOTRECEIVED_CODE                     (0x00U) /* extension code was not received */
#define _20_IICA_RECEIVED_CODE                        (0x20U) /* extension code was received */
/* Detection of matching addresses (COIn) */
#define _00_IICA_ADDRESS_NOTMATCH                     (0x00U) /* addresses do not match */
#define _10_IICA_ADDRESS_MATCH                        (0x10U) /* addresses match */
/* Detection of transmit/receive status (TRCn) */
#define _00_IICA_RECEIVE_STATUS                       (0x00U) /* receive status */
#define _08_IICA_TRANSMIT_STATUS                      (0x08U) /* transmit status */
/* Detection of acknowledge (ACKDn) */
#define _00_IICA_ACKNOWLEDGE_NOTDETECTED              (0x00U) /* acknowledge was not detected */
#define _04_IICA_ACKNOWLEDGE_DETECTED                 (0x04U) /* acknowledge was detected */
/* Detection of start condition (STDn) */
#define _00_IICA_NOTDETECTED_START                    (0x00U) /* start condition was not detected */
#define _02_IICA_DETECTED_START                       (0x02U) /* start condition was detected */
/* Detection of stop condition (SPDn) */
#define _00_IICA_NOTDETECTED_STOP                     (0x00U) /* stop condition was not detected */
#define _01_IICA_DETECTED_STOP                        (0x01U) /* stop condition was detected */

/*
    IICA flag register n (IICFn) 
*/
/* STTn clear flag (STCFn) */
#define _00_IICA_GENERATE_START_CONDITION             (0x00U) /* generate start condition */
#define _80_IICA_NOTGENERATE_START_CONDITION          (0x80U) /* start condition generation unsuccessful */
/* I2C bus status flag (IICBSYn) */
#define _00_IICA_RESULT_WIN_STATUS                    (0x00U) /* bus release status */
#define _40_IICA_RESULT_LOSS_STATUS                   (0x40U) /* bus communication status */
/* Initial start enable trigger (STCENn) */
#define _00_IICA_UOPN_DETECTION                       (0x00U) /* enable generation of a start condition upon detection of a stop
                                                                 condition */
#define _02_IICA_WITHOUT_DETECTION                    (0x02U) /* enable generation of a start condition without detecting a stop
                                                                 condition */
/* Communication reservation function disable bit (IICRSVn) */
#define _00_IICA_RESERVATION_ENABLE                   (0x00U) /* enable communication reservation */
#define _01_IICA_RESERVATION_DISABLE                  (0x01U) /* disable communication reservation */

/*
    IICA control register n1 (IICCTLn1) 
*/
/* Control of address match wakeup (WUPn) */
#define _00_IICA_MATCH_STOP                           (0x00U) /* stops operation of address match wakeup function in STOP mode */
#define _80_IICA_MATCH_ENABLE                         (0x80U) /* enables operation of address match wakeup function in STOP mode */
/* Detection of SCLAn pin level (CLDn) */
#define _00_IICA_SCLAn_LOW                            (0x00U) /* the SCLAn pin was detected at low level */
#define _20_IICA_SCLAn_HIGH                           (0x20U) /* the SCLAn pin was detected at high level */
/* Detection of SDAAn pin level (DADn) */
#define _00_IICA_SDAAn_LOW                            (0x00U) /* the SDAAn pin was detected at low level */
#define _10_IICA_SDAAn_HIGH                           (0x10U) /* the SDAAn pin was detected at high level */
/* Operation mode switching (SMCn) */
#define _00_IICA_OPERATE_STANDARD                     (0x00U) /* operates in standard mode */
#define _08_IICA_OPERATE_FAST                         (0x08U) /* operates in fast mode */
/* Digital filter operation control (DFCn) */
#define _00_IICA_FILTER_OFF                           (0x00U) /* digital filter off */
#define _04_IICA_FILTER_ON                            (0x04U) /* digital filter on */
/* Operation clock (fMCK) control (PRSn) */
#define _00_IICA_FCLK_SELECTED                        (0x00U) /* selects fCLK */
#define _01_IICA_FCLK_2_SELECTED                      (0x01U) /* selects fCLK/2 */

/* IICA used flag */
#define _80_IICA_ADDRESS_COMPLETE                     (0x80U)
#define _00_IICA_MASTER_FLAG_CLEAR                    (0x00U)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _10_IICA0_MASTERADDRESS                       (0x10U) /* set the master address value */
#define _98_IICA0_SLAVEADDRESS                        (0x98U) /* set the slave address value */
#define _4B_IICA_LOW_WIDTH                            (0x4BU) /* 100Kbps@32MHz: set the low-level width (tLOW) of the SCLAn pin signal */
#define _53_IICA_HIGH_WIDTH                           (0x53U) /* 100Kbps@32MHz: set the high-level width of the SCLAn pin signal */
#define _14_IICA_LOW_WIDTH                            (0x14U) /* 400Kbps@32MHz: set the low-level width (tLOW) of the SCLAn pin signal */
#define _12_IICA_HIGH_WIDTH                           (0x12U) /* 400Kbps@32MHz: set the high-level width of the SCLAn pin signal */
#define _08_IICA_LOW_WIDTH                            (0x08U) /* 1Mbps@32MHz: set the low-level width (tLOW) of the SCLAn pin signal */
#define _08_IICA_HIGH_WIDTH                           (0x08U) /* 1Mbps@32MHz: set the high-level width of the SCLAn pin signal */

//#define IICA_STANDARD_MODE
#define IICA_FAST_MODE

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables
***********************************************************************************************************************/
extern volatile uint8_t   g_iica0_master_status_flag;  /* iica0 master flag */ 
extern volatile uint8_t   g_iica0_slave_status_flag;   /* iica0 slave flag */
extern volatile uint8_t * gp_iica0_rx_address;         /* iica0 receive buffer address */
extern volatile uint16_t  g_iica0_rx_cnt;              /* iica0 receive data length */
extern volatile uint16_t  g_iica0_rx_len;              /* iica0 receive data count */
extern volatile uint8_t * gp_iica0_tx_address;         /* iica0 send buffer address */
extern volatile uint16_t  g_iica0_tx_cnt;              /* iica0 send data count */
extern volatile uint8_t   g_iica0_tx_end;              /* iica0 send data end */
extern volatile uint8_t   g_iica0_rx_end;              /* iica0 receive data end */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void IICA0_Init(void);
MD_STATUS IICA0_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, uint8_t wait);
MD_STATUS IICA0_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, uint8_t wait);
void IICA0_SlaveSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void IICA0_SlaveReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void IICA0_Set_Wakeup(void);
void IICA0_Clear_Wakeup(void);
void IICA0_Stop(void);
void IICA0_StopCondition(void);
static void iica0_masterhandler(void);
static void iica0_callback_master_sendend(void);
static void iica0_callback_master_receiveend(void);
static void iica0_callback_master_error(MD_STATUS flag);
static void iica0_slavehandler(void);
static void iica0_callback_slave_sendend(void);
static void iica0_callback_slave_receiveend(void);
static void iica0_callback_slave_error(MD_STATUS flag);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
