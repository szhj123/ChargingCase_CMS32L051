#ifndef _APP_BATTERY_H
#define _APP_BATTERY_H

#include "drv_battery.h"

#define CMD_BATT_LEVEL               0x01
#define CMD_BATT_EARBUD_CHG_STATE    0x02
#define CMD_BATT_SLEEP               0x03


#define BATT_VOL_100                 4200
#define BATT_VOL_90                  4060
#define BATT_VOL_80                  3980
#define BATT_VOL_70                  3920
#define BATT_VOL_60                  3870
#define BATT_VOL_50                  3820
#define BATT_VOL_40                  3790
#define BATT_VOL_30                  3770
#define BATT_VOL_20                  3740
#define BATT_VOL_10                  3680
#define BATT_VOL_5                   3450
#define BATT_VOL_0                   3200

#define EARBUD_MIN_CUR               7
#define EARBUD_MAX_CUR               300

typedef enum 
{
    DISCHG_STATE_INIT = 0,
    DISCH_STATE_HANDLER
}dischg_state;

typedef enum
{
    CHG_STATE_INIT = 0,
    CHG_STATE_GET_BATT_ERR_VOL,
    CHG_STATE_HANDLER
}chg_state;

typedef enum _batt_level_state_t
{
    BATT_LEVEL_100 = 100,
    BATT_LEVEL_90 = 90,
    BATT_LEVEL_80 = 80,
    BATT_LEVEL_70 = 70,
    BATT_LEVEL_60 = 60,
    BATT_LEVEL_50 = 50,
    BATT_LEVEL_40 = 40,
    BATT_LEVEL_30 = 30,
    BATT_LEVEL_20 = 20,
    BATT_LEVEL_10 = 10,
    BATT_LEVEL_5 = 5,
    BATT_LEVEL_0 = 0
}batt_level_state_t;

typedef enum _earbud_chg_state_t
{
    EARBUD_CHG_PROCEE = 0,
    EARBUD_CHG_DONE,
    EARBUD_CHG_NULL
}earbud_chg_state_t;

typedef struct _batt_para_t
{
    dischg_state dischgState;
    chg_state chgState;

    uint16_t battVol;
    uint16_t battVolSave;
    uint16_t battVolErr;
    uint16_t earbud_L_Cur;
    uint16_t earbud_R_Cur;

    uint16_t delayCnt;
    

    batt_level_state_t battLevel;
    earbud_chg_state_t earbud_L_Chg_State;
    earbud_chg_state_t earbud_R_Chg_State;

    batt_level_state_t preBattLevel;
    earbud_chg_state_t preEarbud_L_Chg_State;
    earbud_chg_state_t preEarbud_R_Chg_State;
    

}batt_para_t;

void App_Batt_Init(void );
void App_Batt_Set_BatVol(uint16_t battVol );
uint16_t App_Batt_Get_BatVol(void );
void App_Earbud_Set_Cur_L(uint16_t earbudCur );
uint16_t App_Earbud_Get_Cur_L(void );
void App_Earbud_Set_Cur_R(uint16_t earbudCur );
uint16_t App_Earbud_Get_Cur_R(void );
batt_level_state_t App_Batt_Cal_Level(void );
earbud_chg_state_t App_Earbud_Cal_L_Chg_State(void );
earbud_chg_state_t App_Earbud_Cal_R_Chg_State(void );

batt_level_state_t App_Batt_Get_Level(void );
earbud_chg_state_t App_Earbud_Get_L_Chg_State(void );
earbud_chg_state_t App_Earbud_Get_R_Chg_State(void );

void App_Batt_Send_Batt_Level(void );
void App_Batt_Send_Earbud_Chg_State(void );
uint8_t App_Batt_Get_Usb_State(void );
void App_Batt_Delete_Standby_Timer(void );

void App_Batt_Task_Sleep(void );
void App_Batt_Task_Wakeup(void );

void App_Sys_Sleep(void );
void App_Sys_Wakeup(void );


#endif

