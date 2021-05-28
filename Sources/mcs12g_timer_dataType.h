#ifndef MCS12G_TIMER_DATATYPE_H
#define MCS12G_TIMER_DATATYPE_H

#define MCS12G_TIMER_CHANNEL_NUMBER		8

typedef struct mcs12gTimerDataType{
	unsigned char mStatus;
	unsigned char mUpdateRequest;
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
	unsigned char mPrecisionTimerPrescaler;
	unsigned long mTimerCounter;
}Mcs12gTimerDataType;


typedef Mcs12gTimerDataType Mcs12gTimerBswConfigDataType;

#endif