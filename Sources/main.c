#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "mcs12g_clock.h"
#include "mcs12g_timer.h"
#include "mcs12g_schedule.h"
#include "mcs12g_pwm.h"
#include "mcs12g_adc.h"

#include "timer_G96.h"
#include "schedule.h"

unsigned int gSystemCounter;

void main(void) {
	appl_clock_init();
	appl_timer_init();
	appl_schedule_init();
	appl_adc_init();
	appl_pwm_init();
	
 	
	//timer_init();
	EnableInterrupts;
	
	for(;;) {
		//schedule();
		appl_schedule_update();
	} 
}


void task_1ms(){
	
}
void task_5ms(){
	
}
void task_10ms(){
	watchDog_feed();
	//appl_timer_update();
	appl_pwm_update();
	appl_adc_update();
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
	
}
