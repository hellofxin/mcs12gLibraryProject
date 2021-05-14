#include "mcs12g_pwm_bsw_cfg.h"

/** 
mStatus;
mUpdateRequest;
mEnable;
mPolarity;
mCenterAligned;
mDuty[MCS12G_PWM_CHANNEL_NUMBER];
mPeriod[MCS12G_PWM_CHANNEL_NUMBER];    
**/

const Mcs12gPwmDataType gMcs12gPwmBswCfgData  = {
	0,
	1,
	0,
	0,
	0, 
	{ 50, 50, 50, 50,			50, 50, 50, 50 }, 
	{ 100, 100, 100, 100, 		100 ,100, 100, 100 }
};

