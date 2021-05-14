#include "mcs12g_pwm.h"

Mcs12gPwmDataType gMcs12gPwmData;

unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this, const Mcs12gPwmAswCfgDataType* pAswCfgData, const Mcs12gPwmDataType* pBswCfgData){
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}
	if( pAswCfgData ){
		this->mEnable = pAswCfgData->mEnable;
		this->mDuty[0] = pAswCfgData->mDuty[0];	
		this->mDuty[1] = pAswCfgData->mDuty[1];	
		this->mDuty[2] = pAswCfgData->mDuty[2];	
		this->mDuty[3] = pAswCfgData->mDuty[3];	
		this->mDuty[4] = pAswCfgData->mDuty[4];	
		this->mDuty[5] = pAswCfgData->mDuty[5];	
		this->mDuty[6] = pAswCfgData->mDuty[6];	
		this->mDuty[7] = pAswCfgData->mDuty[7];
		this->mPeriod[0] = pAswCfgData->mPeriod[0];	
		this->mPeriod[1] = pAswCfgData->mPeriod[1];	
		this->mPeriod[2] = pAswCfgData->mPeriod[2];	
		this->mPeriod[3] = pAswCfgData->mPeriod[3];	
		this->mPeriod[4] = pAswCfgData->mPeriod[4];	
		this->mPeriod[5] = pAswCfgData->mPeriod[5];	
		this->mPeriod[6] = pAswCfgData->mPeriod[6];	
		this->mPeriod[7] = pAswCfgData->mPeriod[7];	
	}
	else if( pBswCfgData ){
		this->mEnable = pBswCfgData->mEnable;
		this->mDuty[0] = pBswCfgData->mDuty[0];	
		this->mDuty[1] = pBswCfgData->mDuty[1];	
		this->mDuty[2] = pBswCfgData->mDuty[2];	
		this->mDuty[3] = pBswCfgData->mDuty[3];	
		this->mDuty[4] = pBswCfgData->mDuty[4];	
		this->mDuty[5] = pBswCfgData->mDuty[5];	
		this->mDuty[6] = pBswCfgData->mDuty[6];	
		this->mDuty[7] = pBswCfgData->mDuty[7];
		this->mPeriod[0] = pBswCfgData->mPeriod[0];	
		this->mPeriod[1] = pBswCfgData->mPeriod[1];	
		this->mPeriod[2] = pBswCfgData->mPeriod[2];	
		this->mPeriod[3] = pBswCfgData->mPeriod[3];	
		this->mPeriod[4] = pBswCfgData->mPeriod[4];	
		this->mPeriod[5] = pBswCfgData->mPeriod[5];	
		this->mPeriod[6] = pBswCfgData->mPeriod[6];	
		this->mPeriod[7] = pBswCfgData->mPeriod[7];					
	}
	else{
		this->mEnable = 0;
		this->mDuty[0] = 0;
		this->mDuty[1] = 0;
		this->mDuty[2] = 0;
		this->mDuty[3] = 0;
		this->mDuty[4] = 0;
		this->mDuty[5] = 0;
		this->mDuty[6] = 0;	
		this->mDuty[7] = 0;
		this->mPeriod[0] = 0;
		this->mPeriod[1] = 0;
		this->mPeriod[2] = 0;
		this->mPeriod[3] = 0;
		this->mPeriod[4] = 0;
		this->mPeriod[5] = 0;
		this->mPeriod[6] = 0;
		this->mPeriod[7] = 0;
	}
	
	if( pBswCfgData ){
		this->mPolarity = pBswCfgData->mPolarity;
		this->mCenterAligned = pBswCfgData->mCenterAligned;		
	}
	else{
		this->mPolarity = 0;
		this->mCenterAligned = 0;	
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

