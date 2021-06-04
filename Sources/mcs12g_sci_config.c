#include "mcs12g_sci_config.h"

/**
	unsigned char mUpdateRequest;	
	unsigned char mBaudRatePrescaler;
	unsigned char mParityType;
	unsigned char mParityEnable;
	unsigned char mDataMode;
	unsigned char mLoopbackEnable;
	unsigned char mRIE;
	unsigned char mTIE;
	unsigned char mTCIE; 
/**/
const Mcs12gSciBswConfigDataType gMcs12gSciBswConfigData = {
	1,
	156,
	Mcs12gSciParity_even,
	0,
	Mcs12gSciDataMode_8bit,
	1,
	1,
	0,
	0		
};