#include "mcs12g_pwm.h"

Mcs12gPwmDataType gMcs12gPwmData;

/**
 **@brief Ӧ�ò�ӿڣ����� pwm ��ʼ�� 
/**/
unsigned char appl_pwm_init(){
	return mcs12g_pwm_init(&gMcs12gPwmData, &gMcs12gPwmAswConfigData, &gMcs12gPwmBswConfigData);	
}

/**
 **@brief Ӧ�ò�ӿڣ��� task ���������ڵ��ø���״̬ 
/**/
unsigned char appl_pwm_update(){
	return mcs12g_pwm_update(&gMcs12gPwmData);	 	
}

/**
 **@brief Ӧ�ò�ӿڣ����� pwm ͨ��ʹ��
 **@parameter enable: enable��ÿһ��bit��Ӧһ��pwmͨ��������enable.bit0��Ӧpwm channel 0��ʹ������ 
/**/
unsigned char appl_pwm_setEnable(unsigned char enable){
	return mcs12g_pwm_setEnable(&gMcs12gPwmData, enable);	
}

/**
 **@brief Ӧ�ò�ӿڣ����� pwm ͨ�� polarity
 **@parameter polarity: polarity��ÿһ��bit��Ӧһ��pwmͨ��������polarity.bit0��Ӧpwm channel 0��polarity����
/**/
unsigned char appl_pwm_setPolarity(unsigned char polarity){
	return mcs12g_pwm_setPolarity(&gMcs12gPwmData, polarity);	
}

/**
 **@brief Ӧ�ò�ӿڣ����� pwm �Ƿ��м����
 **@parameter centerAligned: centerAligned��ÿһ��bit��Ӧһ��pwmͨ��������centerAligned.bit0��Ӧpwm channel 0��centerAligned����
/**/
unsigned char appl_pwm_setCenterAligned(unsigned char centerAligned){
	return mcs12g_pwm_setCenterAligned(&gMcs12gPwmData, centerAligned);	
}

/**
 **@brief Ӧ�ò�ӿڣ����� pwm ĳ channel �� duty �� period 
 **@parameter channel: ĳ��pwmͨ����ţ�����1��2��3��4��5��6��7
 **                      duty: ռ�ձ�
 **                      period: ����
/**/
unsigned char appl_pwm_setDutyPeriod(unsigned char channel, unsigned short duty, unsigned short period){
	return mcs12g_pwm_setDutyPeriod(&gMcs12gPwmData, channel, duty, period);	
}


/**
 **@brief �ײ��ض������ӿڣ���ʼ�� pwm ģ��  
/**/
unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this, const Mcs12gPwmAswConfigDataType* pAswCfgData, const Mcs12gPwmBswConfigDataType* pBswCfgData){
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
 **@brief �ײ��ض������ӿڣ��������ڸ��� pwm ״̬ 
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
 **@brief �ײ��ض������ӿڣ����� pwm ͨ��ʹ�� 
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
 **@brief  �ײ��ض������ӿ�, ���� pwm polarity
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
 **@brief �ײ��ض������ӿڣ����� pwm �м���� 
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
 **@brief �ض������ӿڣ����� pwm ĳ channel �� duty��period 
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

