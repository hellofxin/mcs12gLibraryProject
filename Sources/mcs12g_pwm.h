#ifndef MCS12G_PWM_H
#define MCS12G_PWM_H

#include "mc9s12g128.h"
#include "mcs12g_pwm_dataType.h"
#include "mcs12g_pwm_bsw_cfg.h"
#include "mcs12g_pwm_asw_cfg.h"

extern Mcs12gPwmDataType gMcs12gPwmData;

unsigned char appl_pwm_init();
unsigned char appl_pwm_update();

unsigned char appl_pwm_setEnable(unsigned char enable);
unsigned char appl_pwm_setPolarity(unsigned char polarity);
unsigned char appl_pwm_setCenterAligned(unsigned char centerAligned);
unsigned char appl_pwm_setDutyPeriod(unsigned char channel, unsigned short duty, unsigned short period);

unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this, const Mcs12gPwmAswCfgDataType* pAswCfgData, const Mcs12gPwmBswCfgDataType* pBswCfgData);
unsigned char mcs12g_pwm_update(Mcs12gPwmDataType* this);

unsigned char mcs12g_pwm_setEnable(Mcs12gPwmDataType* this, unsigned char enable);
unsigned char mcs12g_pwm_setPolarity(Mcs12gPwmDataType* this, unsigned char polarity);
unsigned char mcs12g_pwm_setCenterAligned(Mcs12gPwmDataType* this, unsigned char centerAligned);
unsigned char mcs12g_pwm_setDutyPeriod(Mcs12gPwmDataType* this, unsigned char channel, unsigned short duty, unsigned short period);


#endif