#include "mcs12g_pwm_asw_cfg.h"

/** 
mEnable;
mDuty[MCS12G_PWM_CHANNEL_NUMBER];
mPeriod[MCS12G_PWM_CHANNEL_NUMBER];    
**/

const Mcs12gPwmAswConfigDataType gMcs12gPwmAswConfigData = {
	0 | PWME_PWME0_MASK 
	| PWME_PWME1_MASK
	| PWME_PWME2_MASK
	| PWME_PWME3_MASK
	| PWME_PWME4_MASK
	| PWME_PWME5_MASK
	| PWME_PWME6_MASK
	| PWME_PWME7_MASK, 
	{50, 50, 50, 50,	50, 50, 50, 50}, 
	{100, 100 ,100, 100,	100, 100, 100, 100}
};