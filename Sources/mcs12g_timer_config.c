#include "mcs12g_timer_config.h"

/**
mStatus;
mUpdateRequest;
mInputCaptureOutputCompareSelect;
mFourceOutput;
mOutputCompareMask;
mOutputCompareData;
mOutputCompareModeLevelLow;
mOutputCompareModeLevelHigh;
mInputCaptureFallingRisingEdgeLow;
minputCaptureFallingRisingEdgeHigh;
mChannelInterruptEnable;
mTimerCounterResetEnable;
mTimerOverflowInterruptEnable;
mTimerChannelCounter[MCS12G_TIMER_CHANNEL_NUMBER];	
mOutputComparePinDisconnect;
mPrecisionTimerPrescaler;
/**/
	
const Mcs12gTimerBswConfigDataType gMcs12gTimerBswConfigData = {
	0,
	1,
	0x80,
	0,
	0,
	0,
	0x00,
	0x40,
	0x00,
	0x00,
	0x80,
	1,
	0, 
	{ 1000, 1000, 1000, 1000, 	1000, 1000, 1000, 1000 },
	0x80,
	23,
	0
};
	
	