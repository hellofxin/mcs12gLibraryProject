#include "mcs12g_spi_config.h"

/**
mMasterEnable;
mLeastSignificantBitFirstEnable;
mSlaveSelectOutputEnable;
mClockPolarity;
mClockPhase;
mTransmitEmptyInterruptEnable;
mDataReceivedInterruptEnable;
mDataWidth;
mSPR;
mSPPR;	
/**/

/**
 ** BaudRateDivisor = (SPPR + 1) * 2^(SPR + 1)
 ** Baud Rate = BusClock / BaudRateDivisor
/**/

const Mcs12gSpiBswConfigDataType gMcs12gSpiBswConfigData = {
	1,
	1,
	1,
	0,
	1,
	0,
	1,
	Mcs12gSpiDataWidth_16bit,
	2,
	2	
};