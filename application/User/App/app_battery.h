#ifndef _APP_BATTERY_H
#define _APP_BATTERY_H

#include "drv_battery.h"

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
#define BATT_VOL_0                   3300

typedef enum 
{
    DISCHG_STATE_INIT = 0,
    DISCH_STATE_HANDLER
}dischg_state;

typedef enum
{
    CHG_STATE_INIT = 0,
    CHG_STATE_GET_BATT_ERR_VOL,
    CHR_STATE_HANDLER
}chg_state;

typedef enum _batt_level_state_t
{
    BATT_LEVEL_100 = 0,
    BATT_LEVEL_90,
    BATT_LEVEL_80,
    BATT_LEVEL_70,
    BATT_LEVEL_60,
    BATT_LEVEL_50,
    BATT_LEVEL_40,
    BATT_LEVEL_30,
    BATT_LEVEL_20,
    BATT_LEVEL_10,
    BATT_LEVEL_5,
    BATT_LEVEL_0
}batt_level_state_t;

typedef enum _earbud_chg_state_t
{
    EARBUD_CHG_PROCEE = 0,
    EARBUD_CHG_DONE
}earbud_chg_state_t;

typedef struct _batt_para_t
{
    dischg_state dischgState;
    chg_state chgState;

    uint16_t battVol;
    uint16_t earbudCur_l;
    uint16_t earbudCur_r;

    batt_level_state_t battLevel;
    earbud_chg_state_t earbudChgState_l;
    earbud_chg_state_t earbudChgState_r;

}batt_para_t;

void App_Batt_Init(void );
void App_Batt_Set_BatVol(uint16_t battVol );
uint16_t App_Batt_Get_BatVol(void );
void App_Earbud_Set_Cur_L(uint16_t earbudCur );
uint16_t App_Earbud_Get_Cur_L(void );
void App_Earbud_Set_Cur_R(uint16_t earbudCur );
uint16_t App_Earbud_Get_Cur_R(void );

#endif 
