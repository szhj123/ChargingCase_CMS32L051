/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    userdefine.h
* @brief   This file includes user definition.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__

typedef unsigned short 	MD_STATUS;
/* Status list definition */
#define MD_STATUSBASE        (0x00U)
#define MD_OK                (MD_STATUSBASE + 0x00U) /* register setting OK */
#define MD_SPT               (MD_STATUSBASE + 0x01U) /* IIC stop */
#define MD_NACK              (MD_STATUSBASE + 0x02U) /* IIC no ACK */
#define MD_BUSY1             (MD_STATUSBASE + 0x03U) /* busy 1 */
#define MD_BUSY2             (MD_STATUSBASE + 0x04U) /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U) /* IIC OVERRUN occur */

/* Error list definition */
#define MD_ERRORBASE         (0x80U)
#define MD_ERROR             (MD_ERRORBASE + 0x00U)  /* error */
#define MD_ARGERROR          (MD_ERRORBASE + 0x01U)  /* error agrument input error */
#define MD_ERROR1            (MD_ERRORBASE + 0x02U)  /* error 1 */
#define MD_ERROR2            (MD_ERRORBASE + 0x03U)  /* error 2 */
#define MD_ERROR3            (MD_ERRORBASE + 0x04U)  /* error 3 */
#define MD_ERROR4            (MD_ERRORBASE + 0x05U)  /* error 4 */
#define MD_ERROR5            (MD_ERRORBASE + 0x06U)  /* error 5 */
#endif

#define TESOPT	*((volatile uint8_t *)(0x4004384C))  /*!< (@ 0x4004384C) PGA protect register                          */
#define TESCTL	*((volatile uint8_t *)(0x4004384D))  /*!< (@ 0x4004384D) PGA output control register                   */
#define TRMW    *((volatile uint8_t *)(0x40021C08))
#define TRMR    *((volatile uint8_t *)(0x40021C09))
#define TRMT    *((volatile uint8_t *)(0x40021C0A))
#define CNTLD   *((volatile uint16_t *)(0x40021C28)) /*!< (@ 0x40021C28) counter load value of wakeup time             */
	
//#define RTL_SIMULATION

/***********************************************************************************************************************
Macro definitions of SCI usage:
Each channel of SCI has three functions: UART, SPI, and IIC. You can only choose one function to use.
***********************************************************************************************************************/
/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART0_TX      /*! Using CH0 of SCI0 as UART Transmitter */
#define USE_SCI_SPI00         /*! Using CH0 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC00         /*! Using CH0 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART0_RX      /*! Using CH1 of SCI0 as UART Receiver */
#define USE_SCI_SPI01         /*! Using CH1 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC01         /*! Using CH1 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_TX      /*! Using CH2 of SCI0 as UART Transmitter */
#define USE_SCI_SPI10         /*! Using CH2 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC10         /*! Using CH2 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART1_RX      /*! Using CH3 of SCI0 as UART Receiver */
#define USE_SCI_SPI11         /*! Using CH3 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC11         /*! Using CH3 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_TX      /*! Using CH0 of SCI1 as UART Transmitter */
//#define USE_SCI_SPI20         /*! Using CH0 of SCI1 as SPI Transmitter or Receiver */
#define USE_SCI_IIC20         /*! Using CH0 of SCI1 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
//#define USE_SCI_UART2_RX      /*! Using CH1 of SCI1 as UART Receiver */
//#define USE_SCI_SPI21         /*! Using CH1 of SCI1 as SPI Transmitter or Receiver */
#define USE_SCI_IIC21         /*! Using CH1 of SCI1 as IIC Transmitter or Receiver */

/* ToDo: You can define the following MACRO and USE_SCI_UART2_TX or USE_SCI_UART2_RX MACROs to use Infra-Red transmitter or receiver */
//#define USE_IRDA              /*! Enable Infra-Red transmission with UART2 */

/***********************************************************************************************************************
DMA Control Data Set definitions
***********************************************************************************************************************/
#define SPI00_WITH_DMA
#define CTRL_DATA_SPI00 0

//#define SPI01_WITH_DMA
//#define CTRL_DATA_SPI01 2

//#define SPI10_WITH_DMA
//#define CTRL_DATA_SPI10 4

#define SPI11_WITH_DMA
#define CTRL_DATA_SPI11 6

//#define SPI20_WITH_DMA
//#define CTRL_DATA_SPI20 8

//#define SPI21_WITH_DMA
//#define CTRL_DATA_SPI21 10

#define SPI_WITH_DMA
#define CTRL_DATA_SPI 12

#define ADC_WITH_DMA
#define CTRL_DATA_ADC   14

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    SPI_MODE_0 = 0,  // Mode 0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1 
    SPI_MODE_1 = 1,  // Mode 1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0 
    SPI_MODE_2 = 2,  // Mode 2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1 
    SPI_MODE_3 = 3,  // Mode 3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0 
} spi_mode_t;

/** @addtogroup Peripherals_Port_Setting_Definations
  * @{
  */

/* ================================================================================================================== */
/* ================                                       TM40                                       ================ */
/* ================================================================================================================== */
/**
  * @brief TM40 TI00~3 and TO00~3 Port Setting 
  */

#define TI00_PORT_SETTING() do{ \
        PORT->P00CFG = 0x00;	    /* P00 default alternate function */ \
        PORT->PM0  |=  (1 << 0);    /* P00 is used as TI00 input */ \
        PORT->PMC0 &= ~(1 << 0);    /* P00 digital function */ \
}while(0)

#define TI01_PORT_SETTING() do{ \
        PORT->P16CFG = 0x00;	    /* P16 default alternate function */ \
        PORT->PM1  |=  (1 << 6);    /* P16 is used as TI01 input */ \
        PORT->PMC1 &= ~(1 << 6);    /* P16 digital function */ \
}while(0)

#define TI02_PORT_SETTING() do{ \
        PORT->P17CFG = 0x00;	    /* P17 default alternate function */ \
        PORT->PM1  |=  (1 << 7);    /* P17 is used as TI02 input */ \
        PORT->PMC1 &= ~(1 << 7);    /* P17 digital function */ \
}while(0)

#define TI03_PORT_SETTING() do{ \
        PORT->P31CFG = 0x00;	    /* P31 default alternate function */ \
        PORT->PM3  |=  (1 << 1);    /* P31 is used as TI03 input */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define TO00_PORT_SETTING() do{ \
        PORT->P01CFG = 0x00;	    /* P01 default alternate fucntion */ \
        PORT->P0   &= ~(1 << 1);    /* P01 output low level */ \
        PORT->PM0  &= ~(1 << 1);    /* P01 is used as TO00 output */ \
        PORT->POM0 &= ~(1 << 1);    /* P01 is normal output mode */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

#define TO01_PORT_SETTING() do{ \
        PORT->P16CFG = 0x00;	    /* P16 default alternate function */ \
        PORT->P1   &= ~(1 << 6);    /* P16 output low level */ \
        PORT->PM1  &= ~(1 << 6);    /* P16 is used as TO01 output */ \
        PORT->POM1 &= ~(1 << 6);    /* P16 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 6);    /* P16 digital function */ \
}while(0)

#define TO02_PORT_SETTING() do{ \
        PORT->P17CFG = 0x00;	    /* P17 default alternate function */ \
        PORT->P1   &= ~(1 << 7);    /* P17 output low level */ \
        PORT->PM1  &= ~(1 << 7);    /* P17 is used as TO02 output */ \
        PORT->POM1 &= ~(1 << 7);    /* P17 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 7);    /* P17 digital function */ \
}while(0)

#define TO03_PORT_SETTING() do{ \
        PORT->P31CFG = 0x00;	    /* P31 default alternate function */ \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as TO03 output */ \
        PORT->POM3 &= ~(1 << 1);    /* P31 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       TM41                                       ================ */
/* ================================================================================================================== */

/**
  * @brief TM41 TI10~3 and TO10~3 Port Setting 
  */

/* ToDo: You can allocate the TI10 to any desired pins with TI10PCFG register */
#define TI10_PORT_SETTING() do{ \
        PORT->TI10PCFG = 0x03;	    /* allocate TI10 to P10 */ \
        PORT->PM1  |=  (1 << 0);    /* P10 is used as TI10 input */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

/* ToDo: You can allocate the TI11 to any desired pins with TI11PCFG register */
#define TI11_PORT_SETTING() do{ \
        PORT->TI11PCFG = 0x04;	    /* allocate TI11 to P11 */ \
        PORT->PM1  |=  (1 << 1);    /* P11 is used as TI11 input */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

/* ToDo: You can allocate the TI12 to any desired pins with TI12PCFG register */
#define TI12_PORT_SETTING() do{ \
        PORT->TI12PCFG = 0x05;	    /* allocate TI12 to P12 */ \
        PORT->PM1  |=  (1 << 2);    /* P12 is used as TI12 input */ \
        PORT->PMC1 &= ~(1 << 2);    /* P12 digital function */ \
}while(0)

/* ToDo: You can allocate the TI13 to any desired pins with TI13PCFG register */
#define TI13_PORT_SETTING() do{ \
        PORT->TI13PCFG = 0x06;	    /* allocate TI13 to P13 */ \
        PORT->PM1  |=  (1 << 3);    /* P13 is used as TI13 input */ \
        PORT->PMC1 &= ~(1 << 3);    /* P13 digital function */ \
}while(0)

/* ToDo: You can allocate the TO10 to any desired pins with PxxCFG register */
#define TO10_PORT_SETTING() do{ \
        PORT->P14CFG = 0x01;	    /* allocate TO10 to P14 */ \
        PORT->P1   &= ~(1 << 4);    /* P14 output low level */ \
        PORT->PM1  &= ~(1 << 4);    /* P14 is used as TO10 output */ \
        PORT->POM1 &= ~(1 << 4);    /* P14 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

/* ToDo: You can allocate the TO11 to any desired pins with PxxCFG register */
#define TO11_PORT_SETTING() do{ \
        PORT->P15CFG = 0x02;	    /* allocate TO11 to P15 */ \
        PORT->P1   &= ~(1 << 5);    /* P15 output low level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as TO11 output */ \
        PORT->POM1 &= ~(1 << 5);    /* P15 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

/* ToDo: You can allocate the TO12 to any desired pins with PxxCFG register */
#define TO12_PORT_SETTING() do{ \
        PORT->P50CFG = 0x03;	    /* allocate TO12 to P50 */ \
        PORT->P5   &= ~(1 << 0);    /* P50 output low level */ \
        PORT->PM5  &= ~(1 << 0);    /* P50 is used as TO12 output */ \
        PORT->POM5 &= ~(1 << 0);    /* P50 is normal output mode */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

/* ToDo: You can allocate the TO13 to any desired pins with PxxCFG register */
#define TO13_PORT_SETTING() do{ \
        PORT->P51CFG = 0x04;	    /* allocate TO13 to P51 */ \
        PORT->P5   &= ~(1 << 1);    /* P51 output low level */ \
        PORT->PM5  &= ~(1 << 1);    /* P51 is used as TO13 output */ \
        PORT->POM5 &= ~(1 << 1);    /* P51 is normal output mode */ \
        PORT->PMC5 &= ~(1 << 1);    /* P51 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       EPWM                                       ================ */
/* ================================================================================================================== */

/**
  * @brief EPWM Port Setting（Alternative to fixed port)
  */

/* ToDo: You should modify the defination according to your application */
#define EPWM_PORT_SETTING() do{ \
        EPWMO00_PORT_SETTING(); \
        EPWMO01_PORT_SETTING(); \
        EPWMO02_PORT_SETTING(); \
        EPWMO03_PORT_SETTING(); \
        EPWMO04_PORT_SETTING(); \
        EPWMO05_PORT_SETTING(); \
        EPWMO06_PORT_SETTING(); \
        EPWMO07_PORT_SETTING(); \
}while(0)

#define EPWMO00_PORT_SETTING() do{ \
        PORT->P10CFG = 0x00;        /* P10 default Alternate function */ \
        PORT->P1   &= ~(1 << 0);    /* P10 output low level */ \
        PORT->PM1  &= ~(1 << 0);    /* P10 is used as EPWMO00 output */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

#define EPWMO01_PORT_SETTING() do{ \
        PORT->P11CFG = 0x00;        /* P11 default Alternate function */ \
        PORT->P1   &= ~(1 << 1);    /* P11 output low level */ \
        PORT->PM1  &= ~(1 << 1);    /* P11 is used as EPWMO01 output */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

#define EPWMO02_PORT_SETTING() do{ \
        PORT->P12CFG = 0x00;        /* P12 default Alternate function */ \
        PORT->P1   &= ~(1 << 2);    /* P12 output low level */ \
        PORT->PM1  &= ~(1 << 2);    /* P12 is used as EPWMO02 output */ \
        PORT->PMC1 &= ~(1 << 2);    /* P12 digital function */ \
}while(0)

#define EPWMO03_PORT_SETTING() do{ \
        PORT->P13CFG = 0x00;        /* P13 default Alternate function */ \
        PORT->P1   &= ~(1 << 3);    /* P13 output low level */ \
        PORT->PM1  &= ~(1 << 3);    /* P13 is used as EPWMO03 output */ \
        PORT->PMC1 &= ~(1 << 3);    /* P13 digital function */ \
}while(0)

#define EPWMO04_PORT_SETTING() do{ \
        PORT->P14CFG = 0x00;        /* P14 default Alternate function */ \
        PORT->P1   &= ~(1 << 4);    /* P14 output low level */ \
        PORT->PM1  &= ~(1 << 4);    /* P14 is used as EPWMO04 output */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

#define EPWMO05_PORT_SETTING() do{ \
        PORT->P15CFG = 0x00;        /* P15 default Alternate function */ \
        PORT->P1   &= ~(1 << 5);    /* P15 output low level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as EPWMO05 output */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

#define EPWMO06_PORT_SETTING() do{ \
        PORT->P16CFG = 0x00;        /* P16 default Alternate function */ \
        PORT->P1   &= ~(1 << 6);    /* P16 output low level */ \
        PORT->PM1  &= ~(1 << 6);    /* P16 is used as EPWMO06 output */ \
        PORT->PMC1 &= ~(1 << 6);    /* P16 digital function */ \
}while(0)

#define EPWMO07_PORT_SETTING() do{ \
        PORT->P17CFG = 0x00;        /* P17 default Alternate function */ \
        PORT->P1   &= ~(1 << 7);    /* P17 output low level */ \
        PORT->PM1  &= ~(1 << 7);    /* P17 is used as EPWMO07 output */ \
        PORT->PMC1 &= ~(1 << 7);    /* P17 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      RTC1HZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief RTC1HZ Port Setting (Alternative to fixed port)
  */

#define RTC1HZ_PORT_SETTING() do{ \
        PORT->P30CFG = 0x00;        /* P30 default Alternate function */ \
        PORT->P3   &= ~(1 << 0);    /* P30 output low level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as RTC1HZ output */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      CLKBUZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief CLKBUZ0 Port Setting (CLKBUZ0 alternative to any port, CLKBUZ1 alternative to fixed port)
  */

/* ToDo: You can allocate the CLKBUZ0 to any desired pins with PxxCFG register */
#define CLKBUZ0_PORT_SETTING() do{ \
        PORT->P140CFG = 0x07;       /* allocate CLKBUZ0 to P140 */ \
        PORT->P14   &= ~(1 << 0);   /* P140 output low level */ \
        PORT->PM14  &= ~(1 << 0);   /* P140 is used as CLKBUZ0 output */ \
        PORT->PMC14 &= ~(1 << 0);   /* P140 digital function */ \
}while(0)

#define CLKBUZ1_PORT_SETTING() do{ \
        PORT->P15CFG = 0x00;        /* P15 default Alternate function */ \
        PORT->P1   &= ~(1 << 5);    /* P15 output low level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as CLKBUZ1 output */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        ADC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief ADC Port Setting
  */

/* ToDo: Please comment out the following unused ANIx setting according to your application needs. */
#define ADC_PORT_SETTING() do{ \
        PORT->PMC2 |= (1 << 0);   /* Set ANI0(P20) pin: It is necessary for ADC_VREF_AVREFP_AVREFM, used as AVREFP */ \
        PORT->PMC2 |= (1 << 1);   /* Set ANI1(P21) pin: It is necessary for ADC_VREF_AVREFP_AVREFM, used as AVREFM */ \
        PORT->PMC2 |= (1 << 2);   /* Set ANI2(P22) pin */ \
        PORT->PMC2 |= (1 << 3);   /* Set ANI3(P23) pin */ \
        PORT->PMC2 |= (1 << 4);   /* Set ANI4(P24) pin */ \
        PORT->PMC2 |= (1 << 5);   /* Set ANI5(P25) pin */ \
        PORT->PMC2 |= (1 << 6);   /* Set ANI6(P26) pin */ \
        PORT->PMC2 |= (1 << 7);   /* Set ANI7(P27) pin */ \
        PORT->PMC1 |= (1 << 1);   /* Set ANI8(P11) pin */ \
        PORT->PMC1 |= (1 << 0);   /* Set ANI9(P10) pin */ \
        PORT->PMC0 |= (1 << 1);   /* Set ANI10(P01) pin */ \
        PORT->PMC0 |= (1 << 0);   /* Set ANI11(P00) pin */ \
        PORT->PMC14|= (1 << 7);   /* Set ANI12(P147) pin */ \
        PORT->PMC1 |= (1 << 2);   /* Set ANI13(P12) pin */ \
        PORT->PMC12|= (1 << 0);   /* Set ANI14(P120) pin */ \
        PORT->PMC14|= (1 << 6);   /* Set ANI15(P146) pin */ \
        PORT->PMC1 |= (1 << 3);   /* Set ANI16(P13) pin */ \
        PORT->PMC1 |= (1 << 4);   /* Set ANI17(P14) pin */ \
        PORT->PMC1 |= (1 << 5);   /* Set ANI18(P15) pin */ \
        PORT->PMC1 |= (1 << 6);   /* Set ANI19(P16) pin */ \
        PORT->PMC1 |= (1 << 7);   /* Set ANI20(P17) pin */ \
        PORT->PMC3 |= (1 << 0);   /* Set ANI21(P30) pin */ \
        PORT->PMC3 |= (1 << 1);   /* Set ANI22(P31) pin */ \
        /* PORT->PMC5 |= (1 << 0); */  /* Set ANI23(P50) pin */ \
        /* PORT->PMC5 |= (1 << 1); */  /* Set ANI24(P51) pin */ \
        PORT->PMC6 |= (1 << 0);   /* Set ANI25(P60) pin */ \
        PORT->PMC6 |= (1 << 1);   /* Set ANI26(P61) pin */ \
        PORT->PMC6 |= (1 << 2);   /* Set ANI27(P62) pin */ \
        PORT->PMC6 |= (1 << 3);   /* Set ANI28(P63) pin */ \
        PORT->PMC7 |= (1 << 0);   /* Set ANI29(P70) pin */ \
        PORT->PMC7 |= (1 << 1);   /* Set ANI30(P71) pin */ \
        PORT->PMC7 |= (1 << 2);   /* Set ANI31(P72) pin */ \
        PORT->PMC7 |= (1 << 3);   /* Set ANI32(P73) pin */ \
        PORT->PMC7 |= (1 << 4);   /* Set ANI33(P74) pin */ \
        PORT->PMC7 |= (1 << 5);   /* Set ANI34(P75) pin */ \
        PORT->PMC13|= (1 << 0);   /* Set ANI35(P130) pin */ \
        PORT->PMC13|= (1 << 6);   /* Set ANI36(P136) pin */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        CMP                                       ================ */
/* ================================================================================================================== */

// /**
//   * @brief CMP Port Setting
//   */

// #define VCOUT0_PORT_SETTING() do { \
//         PORT->PM12  &= ~(1 << 0);  /* VCOUT0 output to P120 */ \
//         PORT->PMC12 &= ~(1 << 0);  /* VCOUT0 output to P120 */ \
// }while(0)

// #define VCOUT1_PORT_SETTING() do { \
//         PORT->PM5   &= ~(1 << 0);  /* VCOUT1 output to P50 */ \
//         PORT->PMC5  &= ~(1 << 0);  /* VCOUT1 output to P50 */ \
// }while(0)

// /* ToDo: Please comment out the VREF0 setting if don't used VREF0 as negative(-) side input of CMP */
// #define CMP0_PORT_SETTING() do{ \
//         PORT->PMC2  |= (1 << 2);  /* Set VCIN0(P22) pin */ \
//         PORT->PMC14 |= (1 << 7);  /* Set VREF0(P147) pin */ \
//         VCOUT0_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT0 signal to port */ \
// }while(0)

// /* ToDo: Please comment out the VCINxx setting if don't used it as positive(+) side input of CMP */
// #define CMP1_PORT_SETTING() do{ \
//         PORT->PMC0  |= (1 << 0);  /* Set VCIN10(P00) pin */ \
//         PORT->PMC0  |= (1 << 1);  /* Set VCIN11(P01) pin */ \
//         PORT->PMC2  |= (1 << 0);  /* Set VCIN12(P20) pin */ \
//         PORT->PMC2  |= (1 << 1);  /* Set VCIN13(P21) pin */ \
//         VCOUT1_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT1 signal to port */ \
// }while(0)

/* ================================================================================================================== */
/* ================                                        PGA                                       ================ */
/* ================================================================================================================== */

// /**
//   * @brief PGA Port Setting
//   */

// #define PGA0O_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 4);   /* PGA0O output to P24 */ \
// }while(0)

// #define PGA1O_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 2);   /* PGA1O output to P22 */ \
// }while(0)

// #define PGA0IN_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 2);  /* PGA0IN input from P22 */ \
// }while(0)

// #define PGA0GND_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 3);  /* PGA0GND input from P23 */ \
// }while(0)

// #define PGA1IN_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 4);  /* PGA1IN input from P24 */ \
// }while(0)

// #define PGA1GND_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 5);  /* PGA1GND input from P25 */ \
// }while(0)

/* ================================================================================================================== */
/* ================                                       SCI0                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART0 Port Setting（Alternative to any port) 
  */

/* ToDo: You can allocate the TXD0 to any desired pins with PxxCFG register */
#define TXD0_PORT_SETTING() do{ \
        PORT->P51CFG = 0x05;        /* allocate TXD0 to P51 */ \
        PORT->P5   |=  (1 << 1);    /* P51 output high level */ \
        PORT->PM5  &= ~(1 << 1);    /* P51 is used as TXD0 output */ \
        PORT->POM5 &= ~(1 << 1);    /* P51 is normal output mode */ \
        PORT->PMC5 &= ~(1 << 1);    /* P51 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD0 to any desired pins with RXD0PCFG register */
#define RXD0_PORT_SETTING() do{ \
        PORT->RXD0PCFG = 0x17;      /* allocate RXD0 to P50 */ \
        PORT->PM5  |=  (1 << 0);    /* P50 is used as RXD0 input */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

/**
  * @brief SPI00 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SS00 to any desired pins with SS00PCFG register */
#define SS00_PORT_SETTING() do{ \
        PORT->SS00PCFG = 0x1B;       /* allocate SS00 to P62 */ \
        PORT->PM6  |=  (1 << 2);     /* P62 is used as SS00 input */ \
        PORT->PU6  |=  (1 << 2);     /* P62 pull up resistor enable */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_SET() do{ \
        PORT->PSET6 = (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_CLR() do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

/* ToDo: You can allocate the SCLKI00 to any desired pins with SCLKI00PCFG register */
#define SCLKI00_PORT_SETTING() do{ \
        PORT->SCLKI00PCFG = 0x13;    /* allocate SCLKI00 to P30 */ \
        PORT->PM3  |=  (1 << 0);     /* P30 is used as SCLK00 input */ \
        PORT->PMC3 &= ~(1 << 0);     /* P30 digital function */ \
}while(0)

/* ToDo: You can allocate the SCLKO00 to any desired pins with PxxCFG register */
#define SCLKO00_PORT_SETTING() do{ \
        PORT->P30CFG = 0x08;        /* allocate SCLKO00 to P30 */ \
        PORT->P3   |=  (1 << 0);    /* P30 output high level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as SCLK00 output */ \
        PORT->POM3 &= ~(1 << 0);    /* P30 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO00 to any desired pins with PxxCFG register */
#define SDO00_PORT_SETTING() do{ \
        PORT->P51CFG = 0x05;        /* allocate SDO00 to P51 */ \
        PORT->P5   |=  (1 << 1);    /* P51 output high level */ \
        PORT->PM5  &= ~(1 << 1);    /* P51 is used as SDO00 output */ \
        PORT->POM5 &= ~(1 << 1);    /* P51 is normal output mode */ \
        PORT->PMC5 &= ~(1 << 1);    /* P51 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI00 to any desired pins with SDI00PCFG register */
#define SDI00_PORT_SETTING() do{ \
        PORT->SDI00PCFG = 0x17;     /* allocate SDI00 to P50 */ \
        PORT->PM5  |=  (1 << 0);    /* P50 is used as SDI00 input */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

/**
  * @brief IIC00 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SCL00 to any desired pins with PxxCFG register */
#define SCL00_PORT_SETTING() do{ \
        PORT->P30CFG = 0x08;        /* allocate SCL00 to P30 */ \
        PORT->P3   |=  (1 << 0);    /* P30 output high level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as SCL00 output */ \
        PORT->POM3 |=  (1 << 0);    /* P30 is N-ch open-drain output mode */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

/* ToDo: You can allocate the SDA00 to any desired pins with SDA00PCFG register */
#define SDA00_PORT_SETTING() do{ \
        PORT->SDA00PCFG = 0x17;     /* allocate SDA00 to P50 */ \
        PORT->P5   |=  (1 << 0);    /* P50 output high level */ \
        PORT->PM5  &= ~(1 << 0);    /* P50 is used as SDA00 inout */ \
        PORT->POM5 |=  (1 << 0);    /* P50 is N-ch open-drain output mode */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

/**
  * @brief SPI01 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SETTING() do{ \
        PORT->P62CFG = 0x00;         /* P62 default GPIO function */ \
        PORT->P6   |=  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS01 output */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SET() do{ \
        PORT->PSET6 = (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_CLR() do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI01_PORT_SETTING() do{ \
        PORT->P75CFG = 0x00;        /* P75 default Alternate function */ \
        PORT->PM7  |=  (1 << 5);    /* P75 is used as SCLK00 input */ \
        PORT->PMC7 &= ~(1 << 5);    /* P75 digital function */ \
}while(0)

#define SCLKO01_PORT_SETTING() do{ \
        PORT->P75CFG = 0x00;        /* P75 default Alternate function */ \
        PORT->P7   |=  (1 << 5);    /* P75 output high level */ \
        PORT->PM7  &= ~(1 << 5);    /* P75 is used as SCLK00 output */ \
        PORT->POM7 &= ~(1 << 5);    /* P75 is normal output mode */ \
        PORT->PMC7 &= ~(1 << 5);    /* P75 digital function */ \
}while(0)

#define SDO01_PORT_SETTING() do{ \
        PORT->P73CFG = 0x00;        /* P73 default Alternate function */ \
        PORT->P7   |=  (1 << 3);    /* P73 output high level */ \
        PORT->PM7  &= ~(1 << 3);    /* P73 is used as SDO01 output */ \
        PORT->POM7 &= ~(1 << 3);    /* P73 is normal output mode */ \
        PORT->PMC7 &= ~(1 << 3);    /* P73 digital function */ \
}while(0)

#define SDI01_PORT_SETTING() do{ \
        PORT->P74CFG = 0x00;        /* P74 default Alternate function */ \
        PORT->PM7  |=  (1 << 4);    /* P74 is used as SDI01 input */ \
        PORT->PMC7 &= ~(1 << 4);    /* P74 digital function */ \
}while(0)

/**
  * @brief IIC01 Port Setting (Alternative to fixed port)
  */

#define SCL01_PORT_SETTING() do{ \
        PORT->P75CFG = 0x00;        /* P75 default Alternate function */ \
        PORT->P7   |=  (1 << 5);    /* P75 output high level */ \
        PORT->PM7  &= ~(1 << 5);    /* P75 is used as SCL01 output */ \
        PORT->POM7 |=  (1 << 5);    /* P75 is N-ch open-drain output mode */ \
        PORT->PMC7 &= ~(1 << 5);    /* P75 digital function */ \
}while(0)

#define SDA01_PORT_SETTING() do{ \
        PORT->P74CFG = 0x00;        /* P74 default Alternate function */ \
        PORT->P7   |=  (1 << 4);    /* P74 output high level */ \
        PORT->PM7  &= ~(1 << 4);    /* P74 is used as SDA01 inout */ \
        PORT->POM7 |=  (1 << 4);    /* P74 is N-ch open-drain output mode */ \
        PORT->PMC7 &= ~(1 << 4);    /* P74 digital function */ \
}while(0)

/**
  * @brief UART1 Port Setting (Alternative to any port)
  */

/* ToDo: You can allocate the TXD1 to any desired pins with PxxCFG register */
#define TXD1_PORT_SETTING() do{ \
        PORT->P00CFG = 0x0A;        /* allocate TXD1 to P00 */ \
        PORT->P0   |=  (1 << 0);    /* P00 output high level */ \
        PORT->PM0  &= ~(1 << 0);    /* P00 is used as TXD1 output */ \
        PORT->POM0 &= ~(1 << 0);    /* P00 is normal output mode */ \
        PORT->PMC0 &= ~(1 << 0);    /* P00 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD1 to any desired pins with RXD1PCFG register */
#define RXD1_PORT_SETTING() do{ \
        PORT->RXD1PCFG = 0x02;      /* allocate RXD1 to P01 */ \
        PORT->PM0  |=  (1 << 1);    /* P01 is used as RXD1 input */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

/**
  * @brief SPI10 Port Setting (SCLK10 alternative to fixed port, SDI10/SDO10 alternative to any port)
  */

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SETTING() do{ \
        PORT->P62CFG = 0x00;         /* P62 default GPIO function */ \
        PORT->P6   |=  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS10 output */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SET() do{ \
        PORT->PSET6 = (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_CLR() do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI10_PORT_SETTING() do{ \
        PORT->P130CFG = 0x00;       /* P130 default Alternate function */ \
        PORT->PM13  |=  (1 << 0);   /* P130 is used as SCLK10 input */ \
        PORT->PMC13 &= ~(1 << 0);   /* P130 digital function */ \
}while(0)

#define SCLKO10_PORT_SETTING() do{ \
        PORT->P130CFG = 0x00;       /* P130 default Alternate function */ \
        PORT->P13   |=  (1 << 0);   /* P130 output high level */ \
        PORT->PM13  &= ~(1 << 0);   /* P130 is used as SCLK10 output */ \
        PORT->POM13 &= ~(1 << 0);   /* P130 is normal output mode */ \
        PORT->PMC13 &= ~(1 << 0);   /* P130 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO10 to any desired pins with PxxCFG register */
#define SDO10_PORT_SETTING() do{ \
        PORT->P00CFG = 0x0A;        /* allocate SDO10 to P00 */ \
        PORT->P0   |=  (1 << 0);    /* P00 output high level */ \
        PORT->PM0  &= ~(1 << 0);    /* P00 is used as SDO10 output */ \
        PORT->POM0 &= ~(1 << 0);    /* P00 is normal output mode */ \
        PORT->PMC0 &= ~(1 << 0);    /* P00 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI10 to any desired pins with SDI10PCFG register */
#define SDI10_PORT_SETTING() do{ \
        PORT->SDI10PCFG = 0x02;     /* allocate SDI10 to P01 */ \
        PORT->PM0  |=  (1 << 1);    /* P01 is used as SDI10 input */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

/**
  * @brief IIC10 Port Setting (SCL10 alternative to fixed port, SDA10 alternative to any port)
  */

#define SCL10_PORT_SETTING() do{ \
        PORT->P130CFG = 0x00;       /* P130 default Alternate function */ \
        PORT->P13   |=  (1 << 0);   /* P130 output  */ \
        PORT->PM13  &= ~(1 << 0);   /* P130 is used as SCL10 output */ \
        PORT->POM13 |=  (1 << 0);   /* P130 is N-ch open-drain output mode */ \
        PORT->PMC13 &= ~(1 << 0);   /* P130 digital function */ \
}while(0)

/* ToDo: You can allocate the SDA10 to any desired pins with SDA10PCFG register */
#define SDA10_PORT_SETTING() do{ \
        PORT->SDA10PCFG = 0x02;     /* allocate SDA10 to P01 */ \
        PORT->P0   |=  (1 << 1);    /* P01 output high level */ \
        PORT->PM0  &= ~(1 << 1);    /* P01 is used as SDA10 inout */ \
        PORT->POM0 |=  (1 << 1);    /* P01 is N-ch open-drain output mode */ \
        PORT->PMC0 &= ~(1 << 1);    /* P01 digital function */ \
}while(0)

/**
  * @brief SPI11 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SETTING() do{ \
        PORT->P62CFG = 0x00;         /* P62 default GPIO function */ \
        PORT->P6   |=  (1 << 2);     /* P62 output high level */ \
        PORT->PM6  &= ~(1 << 2);     /* P62 is used as SS11 output */ \
        PORT->PMC6 &= ~(1 << 2);     /* P62 digital function */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SET() do{ \
        PORT->PSET6 = (1 << 2);      /* P62 output high level */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_CLR() do{ \
        PORT->PCLR6 = (1 << 2);      /* P62 output low level */ \
}while(0)

#define SCLKI11_PORT_SETTING() do{ \
        PORT->P10CFG = 0x00;        /* P10 default Alternate function */ \
        PORT->PM1  |=  (1 << 0);    /* P10 is used as SCLK11 input */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

#define SCLKO11_PORT_SETTING() do{ \
        PORT->P10CFG = 0x00;        /* P10 default Alternate function */ \
        PORT->P1   |=  (1 << 0);    /* P10 output high level */ \
        PORT->PM1  &= ~(1 << 0);    /* P10 is used as SCLK11 output */ \
        PORT->POM1 &= ~(1 << 0);    /* P10 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

#define SDO11_PORT_SETTING() do{ \
        PORT->P12CFG = 0x00;        /* P12 default Alternate function */ \
        PORT->P1   |=  (1 << 2);    /* P12 output high level */ \
        PORT->PM1  &= ~(1 << 2);    /* P12 is used as SDO11 output */ \
        PORT->POM1 &= ~(1 << 2);    /* P12 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 2);    /* P12 digital function */ \
}while(0)

#define SDI11_PORT_SETTING() do{ \
        PORT->P11CFG = 0x00;        /* P11 default Alternate function */ \
        PORT->PM1  |=  (1 << 1);    /* P11 is used as SDI11 input */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

/**
  * @brief IIC11 Port Setting (Alternative to fixed port)
  */

#define SCL11_PORT_SETTING() do{ \
        PORT->P10CFG = 0x00;        /* P10 default Alternate function */ \
        PORT->P1   |=  (1 << 0);    /* P10 output high level */ \
        PORT->PM1  &= ~(1 << 0);    /* P10 is used as SCL11 output */ \
        PORT->POM1 |=  (1 << 0);    /* P10 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

#define SDA11_PORT_SETTING() do{ \
        PORT->P11CFG = 0x00;        /* P11 default Alternate function */ \
        PORT->P1   |=  (1 << 1);    /* P11 output high level */ \
        PORT->PM1  &= ~(1 << 1);    /* P11 is used as SDA11 inout */ \
        PORT->POM1 |=  (1 << 1);    /* P11 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SCI1                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART2 Port Setting（Alternative to any port) 
  */

/* ToDo: You can allocate the TXD2 to any desired pins with PxxCFG register */
#define TXD2_PORT_SETTING() do{ \
        PORT->P13CFG = 0x06;        /* allocate TXD2 to P13 */ \
        PORT->P1   |=  (1 << 3);    /* P13 output high level */ \
        PORT->PM1  &= ~(1 << 3);    /* P13 is used as TXD2 output */ \
        PORT->POM1 &= ~(1 << 3);    /* P13 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 3);    /* P13 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD2 to any desired pins with RXD2PCFG register */
#define RXD2_PORT_SETTING() do{ \
        PORT->RXD2PCFG = 0x07;      /* allocate RXD2 to P14 */ \
        PORT->PM1  |=  (1 << 4);    /* P14 is used as RXD2 input */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

/**
  * @brief SPI20 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SETTING() do{ \
        PORT->P63CFG = 0x00;         /* P63 default GPIO function */ \
        PORT->P6   |=  (1 << 3);     /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);     /* P63 is used as SS20 output */ \
        PORT->PMC6 &= ~(1 << 3);     /* P63 digital function */ \
}while(0)

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_SET() do{ \
        PORT->PSET6 = (1 << 3);      /* P63 output high level */ \
}while(0)

/* ToDo: You can allocate the SS20 to any desired pins */
#define SS20_PORT_CLR() do{ \
        PORT->PCLR6 = (1 << 3);      /* P63 output low level */ \
}while(0)

/* ToDo: You can allocate the SCLKI20 to any desired pins with SCLKI20PCFG register */
#define SCLKI20_PORT_SETTING() do{ \
        PORT->SCLKI20PCFG = 0x08;    /* allocate SCLK20 to P15 */ \
        PORT->PM1  |=  (1 << 5);     /* P15 is used as SCLK20 input */ \
        PORT->PMC1 &= ~(1 << 5);     /* P15 digital function */ \
}while(0)

/* ToDo: You can allocate the SCLKO20 to any desired pins with PxxCFG register */
#define SCLKO20_PORT_SETTING() do{ \
        PORT->P15CFG = 0x09;        /* allocate SCLK20 to P15 */ \
        PORT->P1   |=  (1 << 5);    /* P15 output high level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as SCLK20 output */ \
        PORT->POM1 &= ~(1 << 5);    /* P15 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO20 to any desired pins with PxxCFG register */
#define SDO20_PORT_SETTING() do{ \
        PORT->P13CFG = 0x06;        /* allocate SDO20 to P13 */ \
        PORT->P1   |=  (1 << 3);    /* P13 output high level */ \
        PORT->PM1  &= ~(1 << 3);    /* P13 is used as SDO20 output */ \
        PORT->POM1 &= ~(1 << 3);    /* P13 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 3);    /* P13 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI20 to any desired pins with SDI20PCFG register */
#define SDI20_PORT_SETTING() do{ \
        PORT->SDI20PCFG = 0x07;     /* allocate SDI20 to P14 */ \
        PORT->PM1  |=  (1 << 4);    /* P14 is used as SDI20 input */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

/**
  * @brief IIC20 Port Setting（SCL20 alternative to any port, SDA20 alternative to fixed port)
  */

/* ToDo: You can allocate the SCL20 to any desired pins with PxxCFG register */
#define SCL20_PORT_SETTING() do{ \
        PORT->P15CFG = 0x09;        /* allocate SCL20 to P15 */ \
        PORT->P1   |=  (1 << 5);    /* P15 output high level */ \
        PORT->PM1  &= ~(1 << 5);    /* P15 is used as SCL20 output */ \
        PORT->POM1 |=  (1 << 5);    /* P15 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 5);    /* P15 digital function */ \
}while(0)

#define SDA20_PORT_SETTING() do{ \
        PORT->P14CFG = 0x00;        /* allocate SDA20 to P14 */ \
        PORT->P1   |=  (1 << 4);    /* P14 output high level */ \
        PORT->PM1  &= ~(1 << 4);    /* P14 is used as SDA20 inout */ \
        PORT->POM1 |=  (1 << 4);    /* P14 is N-ch open-drain output mode */ \
        PORT->PMC1 &= ~(1 << 4);    /* P14 digital function */ \
}while(0)

/**
  * @brief SPI21 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SETTING() do{ \
        PORT->P63CFG = 0x00;         /* P63 default GPIO function */ \
        PORT->P6   |=  (1 << 3);     /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);     /* P63 is used as SS21 output */ \
        PORT->PMC6 &= ~(1 << 3);     /* P63 digital function */ \
}while(0)

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_SET() do{ \
        PORT->PSET6 = (1 << 3);      /* P63 output high level */ \
}while(0)

/* ToDo: You can allocate the SS21 to any desired pins */
#define SS21_PORT_CLR() do{ \
        PORT->PCLR6 = (1 << 3);      /* P63 output low level */ \
}while(0)

#define SCLKI21_PORT_SETTING() do{ \
        PORT->P70CFG = 0x00;        /* P70 default Alternate function */ \
        PORT->PM7  |=  (1 << 0);    /* P70 is used as SCLK21 input */ \
        PORT->PMC7 &= ~(1 << 0);    /* P70 digital function */ \
}while(0)

#define SCLKO21_PORT_SETTING() do{ \
        PORT->P70CFG = 0x00;        /* P70 default Alternate function */ \
        PORT->P7   |=  (1 << 0);    /* P70 output high level */ \
        PORT->PM7  &= ~(1 << 0);    /* P70 is used as SCLK21 output */ \
        PORT->POM7 &= ~(1 << 0);    /* P70 is normal output mode */ \
        PORT->PMC7 &= ~(1 << 0);    /* P70 digital function */ \
}while(0)

#define SDO21_PORT_SETTING() do{ \
        PORT->P72CFG = 0x00;        /* P72 default Alternate function */ \
        PORT->P7   |=  (1 << 2);    /* P72 output high level */ \
        PORT->PM7  &= ~(1 << 2);    /* P72 is used as SDO21 output */ \
        PORT->POM7 &= ~(1 << 2);    /* P72 is normal output mode */ \
        PORT->PMC7 &= ~(1 << 2);    /* P72 digital function */ \
}while(0)

#define SDI21_PORT_SETTING() do{ \
        PORT->P71CFG = 0x00;        /* P71 default Alternate function */ \
        PORT->PM7  |=  (1 << 1);    /* P71 is used as SDI21 input */ \
        PORT->PMC7 &= ~(1 << 1);    /* P71 digital function */ \
}while(0)

/**
  * @brief IIC21 Port Setting (Alternative to fixed port)
  */

#define SCL21_PORT_SETTING() do{ \
        PORT->P70CFG = 0x00;        /* P70 default Alternate function */ \
        PORT->P7   |=  (1 << 0);    /* P70 output high level */ \
        PORT->PM7  &= ~(1 << 0);    /* P70 is used as SCL21 output */ \
        PORT->POM7 |=  (1 << 0);    /* P70 is N-ch open-drain output mode */ \
        PORT->PMC7 &= ~(1 << 0);    /* P70 digital function */ \
}while(0)

#define SDA21_PORT_SETTING() do{ \
        PORT->P71CFG = 0x00;        /* P71 default Alternate function */ \
        PORT->P7   |=  (1 << 1);    /* P71 output high level */ \
        PORT->PM7  &= ~(1 << 1);    /* P71 is used as SDA21 inout */ \
        PORT->POM7 |=  (1 << 1);    /* P71 is N-ch open-drain output mode */ \
        PORT->PMC7 &= ~(1 << 1);    /* P71 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       SPI                                        ================ */
/* ================================================================================================================== */

/**
  * @brief SPI Port Setting（Alternative to three group port)
  */

/* ToDo: Please define one of the following macro and comment out others accroding to your application */
//#define SPI_SLAVE_PORT_GROUP1
//#define SPI_MASTER_PORT_GROUP1
//#define SPI_SLAVE_PORT_GROUP2
#define SPI_MASTER_PORT_GROUP2
//#define SPI_SLAVE_PORT_GROUP3
//#define SPI_MASTER_PORT_GROUP3

#ifdef SPI_SLAVE_PORT_GROUP1
#define NSS_PORT_SETTING() do{ \
        PORT->PM5  |=  (1 << 0);    /* P50 is used as SS00 input */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->SPIPCFG = 0x01;       /* SPI ports group 1 */ \
        PORT->PM5  |=  (1 << 1);    /* P51 is used as SCK input */ \
        PORT->PMC5 &= ~(1 << 1);    /* P51 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
        PORT->PM1  |=  (1 << 6);    /* P16 is used as MOSI input */ \
        PORT->PMC1 &= ~(1 << 6);    /* P16 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
        PORT->P1   &= ~(1 << 7);    /* P17 output low level */ \
        PORT->PM1  &= ~(1 << 7);    /* P17 is used as MISO output */ \
        PORT->POM1 &= ~(1 << 7);    /* P17 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 7);    /* P17 digital function */ \
}while(0)
#endif

#ifdef SPI_MASTER_PORT_GROUP1
#define NSS_PORT_SETTING() do{ \
        PORT->P5   |=  (1 << 0);    /* P50 output high level */ \
        PORT->PM5  &= ~(1 << 0);    /* P50 is used as NSS output */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        PORT->PSET5 =  (1 << 0);    /* P50 output high level */ \
}while(0)

#define NSS_PORT_CLR() do{ \
        PORT->PCLR5 =  (1 << 0);    /* P50 output low level */ \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->SPIPCFG = 0x01;       /* SPI ports group 1 */ \
        PORT->P5   &= ~(1 << 1);    /* P51 output low level */ \
        PORT->PM5  &= ~(1 << 1);    /* P51 is used as SCK output */ \
        PORT->POM5 &= ~(1 << 1);    /* P51 is normal output mode */ \
        PORT->PMC5 &= ~(1 << 1);    /* P51 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
        PORT->P1   &= ~(1 << 6);    /* P16 output low level */ \
        PORT->PM1  &= ~(1 << 6);    /* P16 is used as MOSI output */ \
        PORT->POM1 &= ~(1 << 6);    /* P16 is normal output mode */ \
        PORT->PMC1 &= ~(1 << 6);    /* P16 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
        PORT->PM1  |=  (1 << 7);    /* P17 is used as MISO input */ \
        PORT->PMC1 &= ~(1 << 7);    /* P17 digital function */ \
}while(0)
#endif

#ifdef SPI_SLAVE_PORT_GROUP2
#define NSS_PORT_SETTING() do{ \
        PORT->PM6  |=  (1 << 3);    /* P63 is used as SS00 input */ \
        PORT->PMC6 &= ~(1 << 3);    /* P63 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->SPIPCFG = 0x02;       /* SPI ports group 2 */ \
        PORT->PM3  |=  (1 << 1);    /* P31 is used as SCK input */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
        PORT->PM7  |=  (1 << 4);    /* P74 is used as MOSI input */ \
        PORT->PMC7 &= ~(1 << 4);    /* P74 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
        PORT->P7   &= ~(1 << 5);    /* P75 output low level */ \
        PORT->PM7  &= ~(1 << 5);    /* P75 is used as MISO output */ \
        PORT->POM7 &= ~(1 << 5);    /* P75 is normal output mode */ \
        PORT->PMC7 &= ~(1 << 5);    /* P75 digital function */ \
}while(0)
#endif

#ifdef SPI_MASTER_PORT_GROUP2
#define NSS_PORT_SETTING() do{ \
        PORT->P6   |=  (1 << 3);    /* P63 output high level */ \
        PORT->PM6  &= ~(1 << 3);    /* P63 is used as NSS output */ \
        PORT->PMC6 &= ~(1 << 3);    /* P63 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        PORT->PSET6 =  (1 << 3);    /* P63 output high level */ \
}while(0)

#define NSS_PORT_CLR() do{ \
        PORT->PCLR6 =  (1 << 3);    /* P63 output low level */ \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->SPIPCFG = 0x02;       /* SPI ports group 2 */ \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as SCK output */ \
        PORT->POM3 &= ~(1 << 1);    /* P31 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
        PORT->P7   &= ~(1 << 4);    /* P74 output low level */ \
        PORT->PM7  &= ~(1 << 4);    /* P74 is used as MOSI output */ \
        PORT->POM7 &= ~(1 << 4);    /* P74 is normal output mode */ \
        PORT->PMC7 &= ~(1 << 4);    /* P74 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
        PORT->PM7  |=  (1 << 5);    /* P75 is used as MISO input */ \
        PORT->PMC7 &= ~(1 << 5);    /* P75 digital function */ \
}while(0)
#endif

#ifdef SPI_SLAVE_PORT_GROUP3
#define NSS_PORT_SETTING() do{ \
        PORT->PM2  |=  (1 << 5);    /* P25 is used as SS00 input */ \
        PORT->PMC2 &= ~(1 << 5);    /* P25 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->SPIPCFG = 0x03;       /* SPI ports group 3 */ \
        PORT->PM2  |=  (1 << 4);    /* P24 is used as SCK input */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
        PORT->PM2  |=  (1 << 2);    /* P22 is used as MOSI input */ \
        PORT->PMC2 &= ~(1 << 2);    /* P22 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
        PORT->P2   &= ~(1 << 3);    /* P23 output low level */ \
        PORT->PM2  &= ~(1 << 3);    /* P23 is used as MISO output */ \
        PORT->POM2 &= ~(1 << 3);    /* P23 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 3);    /* P23 digital function */ \
}while(0)
#endif

#ifdef SPI_MASTER_PORT_GROUP3
#define NSS_PORT_SETTING() do{ \
        PORT->P2   |=  (1 << 5);    /* P25 output high level */ \
        PORT->PM2  &= ~(1 << 5);    /* P25 is used as NSS output */ \
        PORT->PMC2 &= ~(1 << 5);    /* P25 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        PORT->PSET2 =  (1 << 5);    /* P25 output high level */ \
}while(0)

#define NSS_PORT_CLR() do{ \
        PORT->PCLR2 =  (1 << 5);    /* P25 output low level */ \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->SPIPCFG = 0x03;       /* SPI ports group 3 */ \
        PORT->P2   &= ~(1 << 4);    /* P24 output low level */ \
        PORT->PM2  &= ~(1 << 4);    /* P24 is used as SCK output */ \
        PORT->POM2 &= ~(1 << 4);    /* P24 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
        PORT->P2   &= ~(1 << 2);    /* P22 output low level */ \
        PORT->PM2  &= ~(1 << 2);    /* P22 is used as MOSI output */ \
        PORT->POM2 &= ~(1 << 2);    /* P22 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 2);    /* P22 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
        PORT->PM2  |=  (1 << 3);    /* P23 is used as MISO input */ \
        PORT->PMC2 &= ~(1 << 3);    /* P23 digital function */ \
}while(0)
#endif

/* ================================================================================================================== */
/* ================                                       IICA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief IICA0 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SCLA0 to any desired pins with SCLA0PCFG register */
#define SCLA0_PORT_SETTING() do{ \
        PORT->SCLA0PCFG = 0x19;     /* allocate SCLA0 to P60 */ \
        PORT->P6   &= ~(1 << 0);    /* P60 output low level */ \
        PORT->PM6  &= ~(1 << 0);    /* P60 is used as SCLA0 output */ \
        PORT->PMC6 &= ~(1 << 0);    /* P60 digital function */ \
}while(0)

/* ToDo: You can allocate the SDAA0 to any desired pins with SDAA0PCFG register */
#define SDAA0_PORT_SETTING() do{ \
        PORT->SDAA0PCFG = 0x1A;     /* allocate SDAA0 to P61 */ \
        PORT->P6   &= ~(1 << 1);    /* P61 output low level */ \
        PORT->PM6  &= ~(1 << 1);    /* P61 is used as SDAA0 inout */ \
        PORT->PMC6 &= ~(1 << 1);    /* P61 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       INTP                                       ================ */
/* ================================================================================================================== */
/**
  * @brief INTP Port Setting 
  */
/* ToDo: You can allocate the INTP0 to any desired pins with INTP0PCFG register */
#define INTP0_PORT_SETTING() do{ \
        PORT->INTP0PCFG = 0x29;     /* allocate INTP0 to P136 */ \
        PORT->PM13  |=  (1 << 6);   /* P136 is used as INTP0 input */ \
        PORT->PMC13 &= ~(1 << 6);   /* P136 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP1 to any desired pins with INTP1PCFG register */
#define INTP1_PORT_SETTING() do{ \
        PORT->INTP1PCFG = 0x17;     /* allocate INTP1 to P50 */ \
        PORT->PM5  |=  (1 << 0);    /* P50 is used as INTP1 input */ \
        PORT->PMC5 &= ~(1 << 0);    /* P50 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP2 to any desired pins with INTP2PCFG register */
#define INTP2_PORT_SETTING() do{ \
        PORT->INTP2PCFG = 0x18;     /* allocate INTP2 to P51 */ \
        PORT->PM5  |=  (1 << 1);    /* P51 is used as INTP2 input */ \
        PORT->PMC5 &= ~(1 << 1);    /* P51 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP3 to any desired pins with INTP3PCFG register */
#define INTP3_PORT_SETTING() do{ \
        PORT->INTP3PCFG = 0x13;     /* allocate INTP3 to P30 */ \
        PORT->PM3  |=  (1 << 0);    /* P30 is used as INTP3 input */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

/** @} */ /* End of group Peripherals_Port_Setting_Definations */

#endif
