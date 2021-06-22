#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "mcs12g_clock.h"
#include "mcs12g_timer.h"
#include "mcs12g_schedule.h"
#include "mcs12g_pwm.h"
#include "mcs12g_adc.h"
#include "mcs12g_sci.h"
#include "mcs12g_spi.h"

unsigned int gSystemCounter;

void main(void) {
	/**/
	appl_clock_init();
	/**/
	appl_timer_init();
	/**/
	appl_schedule_init();
	/**/
	appl_adc_init();
	/**
	appl_pwm_init();
	/**
	appl_sci_init();
	/**/
	appl_spi_init();
	/**/	
	
	EnableInterrupts;
	
	for(;;) {
		appl_schedule_update();
	} 
}


void task_1ms(){
	
}
void task_5ms(){
	
}
void task_10ms(){
	/**/
	appl_timer_update();
	/**/
	appl_adc_update();
	/**
	appl_pwm_update();
	/**	
	appl_sci_update();
	/**/
	appl_spi_update();
	/**/	
}
void task_20ms(){
	
}
void task_50ms(){
	
}
void task_100ms(){
	gSystemCounter++;	
}
void task_200ms(){
	
}
void task_1000ms(){
	//mcs12g_sci_txReq(&gMcs12gSciData);
	//mcs12g_sci_getRxData(&gMcs12gSciData);
	mcs12g_spi_txRequest(&gMcs12gSpiData);
}
