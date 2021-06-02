#ifndef MCS12G_SCI_H
#define MCS12G_SCI_H

#include "mc9s12g128.h"
#include "mcs12g_sci_dataType.h"
#include "mcs12g_sci_config.h"

#define ERROR_OK				0
#define ERROR_NOT_OK		1

extern Mcs12gSciDataType gMcs12gSciData;

unsigned char appl_sci_init();
unsigned char appl_sci_update();

unsigned char mcs12g_sci_init(Mcs12gSciDataType* this, const Mcs12gSciBswConfigDataType* pBswConfigData);
unsigned char mcs12g_sci_update(Mcs12gSciDataType* this);
unsigned char mcs12g_sci_applyConfig(Mcs12gSciDataType* this);

#endif