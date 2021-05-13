#include "mcs12g_pwm.h"

Mcs12gPwmDataType gMcs12gPwmData;

unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this){
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}
	this->mStatus = 0;
        this->mUpdateRequest = 1;
	this->mStatus = mcs12g_pwm_update(this);     
	return this->mStatus;
}

unsigned char mcs12g_pwm_update(Mcs12gPwmDataType* this){
	if( !this ){	
		return ERROR_PWM_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		PWME = 0;
		PWMPOL = this->mPolarity;
		PWMCLK = 0;
		PWMPRCLK = 0;
		PWMCAE = this->mCenterAligned;
		PWMCTL =  PWMCTL_PFRZ_MASK | PWMCTL_PSWAI_MASK;
		PWMCLKAB = PWMCLKAB_PCLKAB2_MASK |  PWMCLKAB_PCLKAB3_MASK | PWMCLKAB_PCLKAB6_MASK | PWMCLKAB_PCLKAB7_MASK;
		PWMSCLA = 1;
		PWMSCLB = 1;
		PWMPER0 = this->mPeriod[0];
		PWMPER1 = this->mPeriod[1];
		PWMPER2 = this->mPeriod[2];
		PWMPER3 = this->mPeriod[3];
		PWMPER4 = this->mPeriod[4];
		PWMPER5 = this->mPeriod[5];
		PWMPER6 = this->mPeriod[6];
		PWMPER7 = this->mPeriod[7];
		PWMDTY0 = this->mDuty[0];
		PWMDTY1 = this->mDuty[1];
		PWMDTY2 = this->mDuty[2];
		PWMDTY3 = this->mDuty[3];
		PWMDTY4 = this->mDuty[4];
		PWMDTY5 = this->mDuty[5];
		PWMDTY6 = this->mDuty[6];
		PWMDTY7 = this->mDuty[7];
		PWME = this->mEnable;	
	}		
	return ERROR_PWM_OK;
}

