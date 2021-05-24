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

const Mcs12gPwmBswConfigDataType gMcs12gPwmBswConfigData  = {
	0,
	1,
	0 | PWME_PWME0_MASK | PWME_PWME1_MASK,
	0 | PWMPOL_PPOL0_MASK & ~PWMPOL_PPOL1_MASK,
	0 & ~PWMCAE_CAE0_MASK | PWMCAE_CAE1_MASK, 
	{ 50, 50, 50, 50,			50, 50, 50, 50 }, 
	{ 100, 100, 100, 100, 		100 ,100, 100, 100 }
};

unsigned char mcs12g_pwm_postInit(Mcs12gPwmDataType* this){
	return ERROR_PWM_OK;	
}

