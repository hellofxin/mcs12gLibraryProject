#include "mcs12g_pwm_asw_cfg.h"

/** 
mEnable;
mDuty[MCS12G_PWM_CHANNEL_NUMBER];
mPeriod[MCS12G_PWM_CHANNEL_NUMBER];    
**/

const Mcs12gPwmAswConfigDataType gMcs12gPwmAswConfigData = {
	0, 
	{50, 50, 50, 50,	50, 50, 50, 50}, 
	{100, 100 ,100, 100,	100, 100, 100, 100}
};