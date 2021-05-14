#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "mcs12g_pwm.h"
#include "clock.h"
#include "timer_G96.h"
#include "schedule.h"

unsigned int gSystemCounter;

void main(void) {
	clock_init();
	timer_init();
 	mcs12g_pwm_init(&gMcs12gPwmData, &gMcs12gPwmAswCfgData, &gMcs12gPwmBswCfgData);
	EnableInterrupts;
	
	for(;;) {
		schedule();
	} 
}


void task_1ms(){
	
}
void task_5ms(){
	
}
void task_10ms(){
	watchDog_feed();
	mcs12g_pwm_update(&gMcs12gPwmData);	
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
