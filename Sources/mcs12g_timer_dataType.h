#ifndef MCS12G_TIMER_DATATYPE_H
#define MCS12G_TIMER_DATATYPE_H

#define MCS12G_TIMER_CHANNEL_NUMBER		8

typedef struct mcs12gTimerDataType{
	unsigned char mStatus;
	unsigned long mTimerClockFrequency;
	unsigned long mTimerCounter;
	unsigned char mUpdateRequest;
	unsigned char mPrecisionTimerPrescaler;
	unsigned char mInputCaptureOutputCompareSelect;
	unsigned char mFourceOutput;
	unsigned char mOutputCompareMask;
	unsigned char mOutputCompareData;
	unsigned char mOutputCompareModeLevelLow;
	unsigned char mOutputCompareModeLevelHigh;
	unsigned char mInputCaptureFallingRisingEdgeLow;
	unsigned char minputCaptureFallingRisingEdgeHigh;
	unsigned char mChannelInterruptEnable;
	unsigned char mTimerCounterResetEnable;
	unsigned char mTimerOverflowInterruptEnable;
	unsigned short mTimerChannelCounter[MCS12G_TIMER_CHANNEL_NUMBER];	
	unsigned char mOutputComparePinDisconnect;
}Mcs12gTimerDataType;

typedef struct mcs12gTimerBswConfigDataType{
	unsigned char mPrecisionTimerPrescaler;
	unsigned char mInputCaptureOutputCompareSelect;
	unsigned char mFourceOutput;
	unsigned char mOutputCompareMask;
	unsigned char mOutputCompareData;
	unsigned char mOutputCompareModeLevelLow;
	unsigned char mOutputCompareModeLevelHigh;
	unsigned char mInputCaptureFallingRisingEdgeLow;
	unsigned char minputCaptureFallingRisingEdgeHigh;
	unsigned char mChannelInterruptEnable;
	unsigned char mTimerCounterResetEnable;
	unsigned char mTimerOverflowInterruptEnable;
	unsigned short mTimerChannelCounter[MCS12G_TIMER_CHANNEL_NUMBER];	
	unsigned char mOutputComparePinDisconnect;
}Mcs12gTimerBswConfigDataType;

#endif