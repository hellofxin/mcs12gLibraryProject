#include "mcs12g_timer_config.h"

/**
mPrecisionTimerPrescaler;
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
/**/
	
/**
 ** @brief 一般只需调整mPrecisionTimerPrescaler和mTimerChannelCounter的值；
 ** Ftimer = Fbus/(mPrecisionTimerPrescaler+1)
 ** 当timer的硬件计数器的计数值达到mTimerChannelCounter[x(比如7)],时，产生中断
/**/
const Mcs12gTimerBswConfigDataType gMcs12gTimerBswConfigData = {
	23,
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
	0x80
};
	
	