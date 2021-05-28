#ifndef MCS12G_TIMER_H
#define MCS12G_TIMER_H

#include "mc9s12g128.h"
#include "mcs12g_timer_dataType.h"
#include "mcs12g_timer_config.h"

#define ERROR_OK				0
#define ERROR_NOT_OK		1

extern Mcs12gTimerDataType gMcs12gTimerData;

unsigned char appl_timer_init();
unsigned char appl_timer_update();

unsigned char mcs12g_timer_init(Mcs12gTimerDataType* this, const Mcs12gTimerBswConfigDataType* pBswConfigData);
unsigned char mcs12g_timer_update(Mcs12gTimerDataType* this); 

unsigned char mcs12g_timer_applyConfig(Mcs12gTimerDataType* this); 


#endif