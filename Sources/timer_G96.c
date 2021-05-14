#include "mc9s12g96.h"
#include "timer_G96.h"
#include "clock.h"

static unsigned int timerCounter = 0;

unsigned char timerFlag_1ms = 0;
unsigned char timerFlag_5ms = 0;
unsigned char timerFlag_10ms = 0;
unsigned char timerFlag_20ms = 0;
unsigned char timerFlag_50ms = 0;
unsigned char timerFlag_100ms = 0;
unsigned char timerFlag_200ms = 0;
unsigned char timerFlag_1000ms = 0;

/**
 * @brief initializes timer.
 * @param None.
 * @retval None.
 * @note 	f_tim = f_bus/(1+PTPSR);
 *		f_bus = 10MHz, PTPSR = 9, f_tim = 1MHz;
/**/
void timer_init(){
	TSCR1_PRNT = 1;		//enable precision timer;
	TSCR1_TEN = 0; 		//disable timer;
	TSCR1_TSWAI = 1;
	TSCR1_TSFRZ = 1;
	PTPSR = 15;  			//set prescaler of precision timer;
	TIOS_IOS7 = 1;		//set ch7 output compared;
	TC7 = 1000;	     		//set output compare value of ch7;
	TCTL1_OM7 = 0;	   	//set output compare mode of ch7;
	TCTL1_OL7 = 1;	
	TIE_C7I = 1;	       		//enable interrupt;
	TSCR2_TCRE = 1;	  	//timer counter reset enable£»      	
	OCPD_OCPD7 = 1;  	//output compare pin disconnect;
	TSCR1_TEN = 1;		//timer enabled£»		
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vtimch7 void ISR_timCh7(){
	TFLG1_C7F = 1;
	timerCounter++;	
	timerFlag_1ms = 1;
        if( timerCounter%5 == 0 ){
        	timerFlag_5ms = 1;
        }
        if( timerCounter%10 == 0 ){
        	timerFlag_10ms = 1;
        }
        if( timerCounter%20 == 0 ){
        	timerFlag_20ms = 1;
        }
        if( timerCounter%50 == 0 ){
        	timerFlag_50ms = 1;
        }
        if( timerCounter%100 == 0 ){
        	timerFlag_100ms = 1;
        }
        if( timerCounter%200 == 0 ){
        	timerFlag_200ms = 1;
        }
        if( timerCounter%1000 == 0 ){
        	timerFlag_1000ms = 1;
        	timerCounter = 0;
        }
}
#pragma CODE_SEG DEFAULT

unsigned long timer_getCounter(){
	return TCNT;
}
