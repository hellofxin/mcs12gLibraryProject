#ifndef MCS12G_PWM_H
#define MCS12G_PWM_H

#include "mc9s12g128.h"
#include "mcs12g_pwm_bsw_cfg.h"
#include "mcs12g_pwm_asw_cfg.h"

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

extern Mcs12gPwmDataType gMcs12gPwmData;

unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this);
unsigned char mcs12g_pwm_update(Mcs12gPwmDataType* this);


#endif