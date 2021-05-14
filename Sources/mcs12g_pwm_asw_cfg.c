#include "mcs12g_pwm_asw_cfg.h"

/** 
mEnable;
mDuty[MCS12G_PWM_CHANNEL_NUMBER];
mPeriod[MCS12G_PWM_CHANNEL_NUMBER];    
**/

Mcs12gPwmAswCfgDataType gMcs12gPwmAswCfgData = {
	0 | PWME_PWME0_MASK & ~PWME_PWME1_MASK, 
	{50, 50, 50, 50,			50, 50, 50, 50}, 
	{100, 100 ,100, 100,		100, 100, 100, 100}
};