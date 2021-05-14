#ifndef MCS12G_PWM_H
#define MCS12G_PWM_H

#include "mc9s12g128.h"
#include "mcs12g_pwm_dataType.h"
#include "mcs12g_pwm_bsw_cfg.h"
#include "mcs12g_pwm_asw_cfg.h"

extern Mcs12gPwmDataType gMcs12gPwmData;

unsigned char mcs12g_pwm_init(Mcs12gPwmDataType* this, const Mcs12gPwmAswCfgDataType* pAswCfgData, const Mcs12gPwmDataType* pBswCfgData);
unsigned char mcs12g_pwm_update(Mcs12gPwmDataType* this);


#endif