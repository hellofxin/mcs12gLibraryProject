#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "mcs12g_pwm.h"

void main(void) {

 	mcs12g_pwm_init(&gMcs12gPwmData, &gMcs12gPwmAswCfgData, &gMcs12gPwmBswCfgData);
	EnableInterrupts;
	
	for(;;) {
		_FEED_COP(); 
		mcs12g_pwm_update(&gMcs12gPwmData);
	} 
}
