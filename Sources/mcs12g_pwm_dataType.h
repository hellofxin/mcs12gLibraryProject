#ifndef MCS12G_PWM_DATATYPE_H
#define MCS12G_PWM_DATATYPE_H

#define MCS12G_PWM_CHANNEL_NUMBER		8

typedef struct mcs12gPwmDataType{
	unsigned char mStatus;
	unsigned char mUpdateRequest;
	unsigned char mEnable;
	unsigned char mPolarity;
	unsigned char mCenterAligned;
	unsigned char mDuty[MCS12G_PWM_CHANNEL_NUMBER];
	unsigned char mPeriod[MCS12G_PWM_CHANNEL_NUMBER];    
}Mcs12gPwmDataType;

typedef struct mcs12gPwmAswCfgDataType{
	unsigned char mEnable;
	unsigned char mDuty[MCS12G_PWM_CHANNEL_NUMBER];
	unsigned char mPeriod[MCS12G_PWM_CHANNEL_NUMBER];    
}Mcs12gPwmAswCfgDataType;

typedef Mcs12gPwmDataType Mcs12gPwmBswCfgDataType;

#endif