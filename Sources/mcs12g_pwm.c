#include "mcs12g_pwm.h"

Mcs12gPwmDataType gMcs12gPwmData;

/**
 **@brief 
/**/
unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this, const Mcs12gPwmAswCfgDataType* pAswCfgData, const Mcs12gPwmBswCfgDataType* pBswCfgData){
	unsigned char i = 0;
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}	
	this->mStatus = 0;
	this->mUpdateRequest = 1;
	this->mEnable = 0;
	this->mPolarity = 0;
	this->mCenterAligned = 0;
	for( i=0; i<MCS12G_PWM_CHANNEL_NUMBER; i++ ){
		this->mDuty[i] = 0;
		this->mPeriod[i] = 0;
	}
	
	if( pBswCfgData ){
		this->mEnable = pBswCfgData->mEnable;
		this->mPolarity = pBswCfgData->mPolarity;
		this->mCenterAligned = pBswCfgData->mCenterAligned;		
		for( i=0; i<MCS12G_PWM_CHANNEL_NUMBER; i++ ){
			this->mDuty[i] = pBswCfgData->mDuty[i];
			this->mPeriod[i] = pBswCfgData->mPeriod[i];
		}
	}
	
	if( pAswCfgData ){
		this->mEnable = pAswCfgData->mEnable;
		for( i=0; i<MCS12G_PWM_CHANNEL_NUMBER; i++ ){
			this->mDuty[i] = pAswCfgData->mDuty[i];
			this->mPeriod[i] = pAswCfgData->mPeriod[i];
		}
	}
	
	this->mStatus = 0;
        this->mUpdateRequest = 1;
	this->mStatus = mcs12g_pwm_update(this);     
	this->mStatus = mcs12g_pwm_postInit(this);
	return this->mStatus;
}

/**
 **@brief 
/**/
unsigned char mcs12g_pwm_update(Mcs12gPwmDataType* this){
	if( !this ){	
		return ERROR_PWM_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		PWME = 0;
		PWMPOL = this->mPolarity;
		PWMCLK = 0xFF;
		PWMPRCLK_PCKA = 4;
		PWMPRCLK_PCKB = 4;
		PWMCAE = this->mCenterAligned;
		PWMCTL =  PWMCTL_PFRZ_MASK | PWMCTL_PSWAI_MASK;
		PWMCLKAB = PWMCLKAB_PCLKAB2_MASK |  PWMCLKAB_PCLKAB3_MASK | PWMCLKAB_PCLKAB6_MASK | PWMCLKAB_PCLKAB7_MASK;
		PWMSCLA = 50;
		PWMSCLB = 50;
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

/**
 **@brief 
/**/
unsigned char mcs12g_pwm_setEnable(Mcs12gPwmDataType* this, unsigned char enable){
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}
	this->mEnable = enable;
	this->mUpdateRequest = 1;
	return ERROR_PWM_OK;
}

/**
 **@brief 
/**/
unsigned char mcs12g_pwm_setPolarity(Mcs12gPwmDataType* this, unsigned char polarity){
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}
	this->mPolarity = polarity;
	this->mUpdateRequest = 1;
	return ERROR_PWM_OK;
}

/**
 **@brief 
/**/
unsigned char mcs12g_pwm_setCenterAligned(Mcs12gPwmDataType* this, unsigned char centerAligned){
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}
	this->mCenterAligned = centerAligned;
	this->mUpdateRequest = 1;
	return ERROR_PWM_OK;
}

/**
 **@brief 
/**/
unsigned char mcs12g_pwm_setDutyPeriod(Mcs12gPwmDataType* this, unsigned char channel, unsigned short duty, unsigned short period){
	if( !this ){
		return ERROR_PWM_NOT_OK;
	}
	if( !IS_MCS12G_PWM_CHANNEL_NUMBER(channel) ){
		return ERROR_PWM_NOT_OK;
	}
	this->mDuty[channel] = duty;
	this->mPeriod[channel] = period;
	this->mUpdateRequest = 1;
	return ERROR_PWM_OK;	
}

