#ifndef MCS12G_SPI_H
#define MCS12G_SPI_H

#include "mc9s12g128.h"
#include "mcs12g_spi_dataType.h"
#include "mcs12g_spi_config.h"

#define ERROR_OK				0
#define ERROR_NOT_OK		1

extern Mcs12gSpiDataType gMcs12gSpiData;

unsigned char appl_spi_init();
unsigned char appl_spi_update();

unsigned char mcs12g_spi_init(Mcs12gSpiDataType* this, const Mcs12gSpiBswConfigDataType* pBswConfigData);
unsigned char mcs12g_spi_update(Mcs12gSpiDataType* this);

unsigned char mcs12g_spi_applyConfig(Mcs12gSpiDataType* this);
unsigned char mcs12g_spi_postInit(Mcs12gSpiDataType* this);

#endif