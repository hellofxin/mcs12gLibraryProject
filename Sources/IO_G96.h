#ifndef IO_G96_H
#define IO_G96_H 

#define PIN_24_EN			PTJ_PTJ6
#define PIN_RESET_N	
#define PIN_LOCK_OCL_N		PT01AD_PT0AD4
#define PIN_WIN_OCL_N		PTP_PTP4		

#define PIN_CAN_EN			PTM_PTM2
#define PIN_CAN_ERR_N		PTJ_PTJ7 	
#define PIN_CAN_WAKE    		PTJ_PTJ4
#define PIN_CAN_STB_N	 	PTM_PTM3

#define PIN_7708_CSB 			PTJ_PTJ3
#define PIN_7708_EN 			PTT_PTT7
#define PIN_7708_CSB_1		PTT_PTT6
#define PIN_7708_EN_1		PTT_PTT5

#define PIN_LOCK_EN			PTP_PTP1
#define PIN_LOCK_PHASE		PTP_PTP2
#define PIN_LOCK_MODE		PTP_PTP3

#define PIN_WIN_EN			PTP_PTP5
#define PIN_WIN_PHASE		PTP_PTP6
#define PIN_WIN_MODE		PTP_PTP7

#define PIN_INPUT_MODE_PULL_DOWN	0
#define PIN_INPUT_MODE_PULL_UP		1
#define SWITCH_ON						1
#define SWITCH_OFF						0
#define HIGH								1
#define LOW								0

/**
 * @brief define the input pins corresponding to switches;
/**/
#define PIN_VehDa_swtLftWinUpRaw 		PT01AD_PT1AD1
#define PIN_VehDa_swtLftWinDwnRaw 		PT01AD_PT0AD1
#define PIN_VehDa_swtDrvRhtWinUpRaw 	PT01AD_PT1AD2
#define PIN_VehDa_swtDrvRhtWinDwnRaw 	PT01AD_PT0AD2
#define PIN_VehDa_swtLftMrorSelRaw		PTT_PTT4
#define PIN_VehDa_swtRhtMrorSelRaw		PTT_PTT3
#define PIN_VehDa_swtMrorUpRaw 			PTT_PTT2
#define PIN_VehDa_swtMrorDwnRaw 		PTT_PTT1
#define PIN_VehDa_swtMrorLftRaw 			PT01AD_PT1AD0
#define PIN_VehDa_swtMrorRhtRaw 			PTT_PTT0
#define PIN_VehDa_swtDefogRaw 			PT01AD_PT0AD0
#define PIN_VehDa_swtKeyLckRaw 			PT01AD_PT1AD3
#define PIN_VehDa_swtKeyUnlckRaw 		PTS_PTS5
#define PIN_VehDa_swtLftKeyFdbkRaw 		PTS_PTS6
#define PIN_VehDa_swtLftDoorOpnRaw 		PTS_PTS7

#define CAN_SET_MODE_STANDBY	      	{ (PIN_CAN_STB_N = LOW); (PIN_CAN_EN = LOW); }
#define CAN_SET_MODE_GO_TO_SLEEP	{ (PIN_CAN_STB_N = LOW); (PIN_CAN_EN = HIGH); }
#define CAN_SET_MODE_LISTEN_ONLY	{ (PIN_CAN_STB_N = HIGH); (PIN_CAN_EN = LOW); }	
#define CAN_SET_MODE_NORMAL			{ (PIN_CAN_STB_N = HIGH); (PIN_CAN_EN = HIGH); }

#define IS_CAN_MODE_STANDBY	      		( (LOW == PIN_CAN_STB_N ) && (LOW == PIN_CAN_EN) )
#define IS_CAN_MODE_GO_TO_SLEEP		( (LOW == PIN_CAN_STB_N) && (HIGH == PIN_CAN_EN) )
#define IS_CAN_MODE_LISTEN_ONLY		( (HIGH == PIN_CAN_STB_N) && (LOW == PIN_CAN_EN) )	
#define IS_CAN_MODE_NORMAL			( (HIGH == PIN_CAN_STB_N) && (HIGH == PIN_CAN_EN) )
	
 /**
 * @brief HW_OUT;
 /**/
extern unsigned char VehDa_drvLftWinUp;
extern unsigned char VehDa_drvLftWinDwn;
extern unsigned char VehDa_stLftWinMove;		//can out
extern unsigned char VehDa_drvLftMrorUp;
extern unsigned char VehDa_drvLftMrorDwn;
extern unsigned char VehDa_stLftMrorUpDwn;     	//can out
extern unsigned char VehDa_drvLftMrorLft;
extern unsigned char VehDa_drvLftMrorRht;
extern unsigned char VehDa_stLftMrorLftRht; 		//can out
extern unsigned char VehDa_drvLftBackLmp;	 	//can out
extern unsigned char VehDa_drvDefogIndLmp;		 //can out
extern unsigned char VehDa_drvLftLck;
extern unsigned char VehDa_drvLftUnlck;
extern unsigned char VehDa_stLftLckMove;
extern unsigned char VehDa_drvLftStpLmp;			 //can out

/**
 * @brief HW_INPUT;
/**/
extern unsigned char VehDa_swtMrorUpRaw;
extern unsigned char VehDa_swtMrorDwnRaw;
extern unsigned char VehDa_swtMrorLftRaw;
extern unsigned char VehDa_swtMrorRhtRaw;
extern unsigned char VehDa_swtDefogRaw;
extern unsigned char VehDa_swtLftKeyFdbkRaw;
extern unsigned char VehDa_swtLftDoorOpnRaw;

/**
 * @brief DM1
/**/
extern unsigned char VehDa_stLftWinActvDTC;
extern unsigned char VehDa_stLftMrorUDActvDTC;
extern unsigned char VehDa_stLftMrorLRActvDTC;
extern unsigned char VehDa_stLftBackLmpActvDTC;
extern unsigned char VehDa_stDefogIndLmpActvDTC;
extern unsigned char VehDa_stLftLckActvDTC;
extern unsigned char VehDa_stLftStpLmpActvDTC;
extern unsigned char VehDa_stBattVltActvDTC;
extern unsigned char VehDa_stPowerSupp1ActvDTC;
extern unsigned char VehDa_stPowerSupp2ActvDTC;


extern unsigned char canErrorN;

void IO_init();
void IO_update();

void lock_motor_reverse();
void lock_motor_forward();
void lock_motor_stop();
void win_motor_reverse();
void win_motor_forward();
void win_motor_stop();

void can_setMode_standby();
void can_setMode_goToSleep();
void can_setMode_listenOnly();
void can_setMode_normal();

#endif