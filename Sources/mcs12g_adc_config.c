#include "mcs12g_adc_config.h"

/**
unsigned char mStatus;
unsigned char mUpdateRequest;
unsigned char mResolution;	
unsigned char mConversionSequenceLength;
unsigned char mWrap;	
unsigned char mMulti;
unsigned char mScanMode;
unsigned char mChannelSelectCode;
unsigned char mSequenceCompleteInterruptEnable;
/**/

extern const Mcs12gAdcBswConfigDataType gMcs12gAdcBswConfigData = {
	0,
	1,
	Mcs12gAdcResolution_10bit,
	12,
	11,
	1,
	0,
	0,
	0	
};