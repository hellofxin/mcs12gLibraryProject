#include "mc9s12g96.h"
#include "IO_G96.h"
#include "SPI.h"
//#include "errorCode.h"
//#include "ADC.h"
//#include "sleepWakeup.h"

unsigned char canErrorN = 1;

void IO_init_hardwareInput();
void IO_init_can();
void IO_init_SPI();
void IO_init_driverWinLock();
void IO_init_power();

void IO_Read();
void IO_Write();
void check_driver();

/**
 * @brief initalizes IO.
 * @param None.
 * @retval None.
/**/
void IO_init(){
	//IO_init_hardwareInput();
	//IO_init_can();	
	IO_init_SPI();
	//IO_init_driverWinLock();	
	//IO_init_power();
}

void IO_update(){
	check_driver();
}

/**
 * @brief initalizes IO related to hardware input.
 * @param None.
 * @retval None.
/**/
void IO_init_hardwareInput(){
	DDR01AD_DDR1AD1 = 0;	
	DDR01AD_DDR0AD1 = 0;
	DDR01AD_DDR1AD2 = 0;
	DDR01AD_DDR0AD2 = 0;
	DDRT_DDRT4 = 0;
	DDRT_DDRT3 = 0;
	DDRT_DDRT2 = 0;
	DDRT_DDRT1 = 0;
	DDR01AD_DDR1AD0 = 0;
	DDRT_DDRT0 = 0;
	DDR01AD_DDR0AD0 = 0;
	DDR01AD_DDR1AD3 = 0;
	DDRS_DDRS5 = 0;
	DDRS_DDRS6 = 0;
	DDRS_DDRS7 = 0;
	DDR01AD_DDR0AD4 = 0;
	DDRP_DDRP4 = 0;
		
	PER01AD_PER1AD1 = 0;
	PER01AD_PER0AD1 = 0;
	PER01AD_PER1AD2 = 0;
	PER01AD_PER0AD2 = 0;
	PERT_PERT4 = 0;
	PERT_PERT3 = 0;
	PERT_PERT2 = 0;
	PERT_PERT1 = 0;
	PER01AD_PER1AD0 = 0;
	PERT_PERT0 = 0;
	PER01AD_PER0AD0 = 0;
	PER01AD_PER1AD3 = 0;
	PERS_PERS5 = 0;
	PERS_PERS6 = 0;
	PERS_PERS7 = 0;
	PER01AD_PER0AD4 = 0;
	PERP_PERP4 = 0;
	
	PPS01AD_PPS1AD1 = 1;
	PPS01AD_PPS0AD1 = 1;
	PPS01AD_PPS1AD2 = 1;
	PPS01AD_PPS0AD2 = 1;
	PPST_PPST4 = 1;
	PPST_PPST3 = 1;
	PPST_PPST2 = 1;
	PPST_PPST1 = 1;
	PPS01AD_PPS1AD0 = 1;
	PPST_PPST0 = 1;
	PPS01AD_PPS0AD0 = 1;
	PPS01AD_PPS1AD3 = 1;
	PPSS_PPSS5 = 1;
	PPSS_PPSS6 = 1;
	PPSS_PPSS7 = 1;
	PPS01AD_PPS0AD4 = 1;
	PPSP_PPSP4 = 1;
		
	ATDDIEN = 0xFFFF;
}
/**
 * @brief initalizes IO related to SPI.
 * @param None.
 * @retval None.
/**/
void IO_init_SPI(){
	DDRJ_DDRJ0 = 1;
	DDRJ_DDRJ1 = 0;
	DDRJ_DDRJ2 = 1;
	DDRJ_DDRJ3 = 1;
	DDRT_DDRT7 = 1;
	DDRT_DDRT6 = 1;
	DDRT_DDRT5 = 1;
		
	PIN_7708_EN = 1;
	PIN_7708_EN_1 = 1;	
	PIN_7708_CSB = 1;
	PIN_7708_CSB_1 = 1;
}



void IO_init_power(){
	DDRJ_DDRJ6 = 1;
	//PERJ_PERJ6 = 0;
	//PPSJ_PPSJ6 = 1;
	PIN_24_EN = 1;
}


/**
 * @brief gets the status of the input pins updated.
 * @param None.
 * @retval None.
 * @note IO_Read£¬hardware input, get the state of the switch.
/**/
void IO_Read(){
}

/**
 * IO_Write£¬hardware out;
/**/
void IO_Write(){			
}

/**
 * @brief check if driver output is needed.
 * @param None.
 * @retval None.
/**/

unsigned char VehDa_swtMrorUpRaw;
unsigned char VehDa_swtMrorDwnRaw;
unsigned char VehDa_swtMrorLftRaw;
unsigned char VehDa_swtMrorRhtRaw;
unsigned char VehDa_swtDefogRaw;
unsigned char VehDa_drvLftStpLmp = 1;
unsigned char VehDa_swtLftDoorOpnRaw;

void check_driver(){
								       
	if( VehDa_swtMrorUpRaw==1 ){
		NCV_LEFT_MIRROR_UP;
	}
	else if( VehDa_swtMrorDwnRaw==1 ){
		NCV_LEFT_MIRROR_DOWN;
	}
	else if( VehDa_swtMrorLftRaw==1 ){
		NCV_LEFT_MIRROR_LEFT;
	}
	else if( VehDa_swtMrorRhtRaw==1 ){
		NCV_LEFT_MIRROR_RIGHT;
	}      
	else{
		NCV_LEFT_MIRROR_STOP;
	}
	
	if( VehDa_swtLftDoorOpnRaw==1 ){
		NCV_DOOR_BACKGROUND_LED_ON;
	}
	else{
		NCV_DOOR_BACKGROUND_LED_OFF;
	}
	
	if( VehDa_swtDefogRaw==1 ){
		NCV_MIRROR_HEAT_LED_ON;
	}
	else{
		NCV_MIRROR_HEAT_LED_OFF;
	}
	
	if( VehDa_drvLftStpLmp==1 ){
		NCV_STEP_LAMP_ON;
	}
	else{
		NCV_STEP_LAMP_OFF;
	}
	
	//SPI_Tx(&SPI1TxData);
}
