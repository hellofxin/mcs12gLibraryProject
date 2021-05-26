#ifndef MCS12G_ADC_H
#define MCS12G_ADC_H

#include "mc9s12g128.h"
#include "mcs12g_adc_dataType.h"
#include "mcs12g_adc_config.h"

#define ERROR_OK				0
#define ERROR_NOT_OK		1

extern Mcs12gAdcDataType gMcs12gAdcData;

unsigned char appl_adc_init();
unsigned char appl_adc_update();

unsigned char mcs12g_adc_init(Mcs12gAdcDataType* this, const Mcs12gAdcBswConfigDataType* pConfigData);
unsigned char mcs12g_adc_update(Mcs12gAdcDataType* this);

unsigned char mcs12g_adc_applyConfig(Mcs12gAdcDataType* this);

#endif