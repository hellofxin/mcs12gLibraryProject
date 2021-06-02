#include "mcs12g_timer.h"
#include "mcs12g_schedule.h"

Mcs12gTimerDataType gMcs12gTimerData;

unsigned char appl_timer_init(){
	return mcs12g_timer_init(&gMcs12gTimerData, &gMcs12gTimerBswConfigData);	
}
unsigned char appl_timer_update(){
	return mcs12g_timer_update(&gMcs12gTimerData);	
}

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

unsigned char mcs12g_timer_init(Mcs12gTimerDataType* this, const Mcs12gTimerBswConfigDataType* pBswConfigData){
	unsigned char i = 0;
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mStatus = 0;
	this->mUpdateRequest = 1;
	this->mInputCaptureOutputCompareSelect = 0xFF;
	this->mFourceOutput = 0;
	this->mOutputCompareMask = 0;
	this->mOutputCompareData = 0;
	this->mOutputCompareModeLevelLow = 0x55;
	this->mOutputCompareModeLevelHigh = 0x55;
	this->mInputCaptureFallingRisingEdgeLow = 0xFF;
	this->minputCaptureFallingRisingEdgeHigh = 0xFF;
	this->mChannelInterruptEnable = 0xFF;
	this->mTimerCounterResetEnable = 1;
	this->mTimerOverflowInterruptEnable = 0;
	this->mOutputComparePinDisconnect = 0xFF;
	this->mPrecisionTimerPrescaler = 23;
	this->mTimerCounter = 0;
	for( i=0; i<MCS12G_TIMER_CHANNEL_NUMBER; i++ ){
		this->mTimerChannelCounter[i] = 0;	
	}
	
	if( pBswConfigData ){
		this->mInputCaptureOutputCompareSelect = pBswConfigData->mInputCaptureOutputCompareSelect;
		this->mFourceOutput = pBswConfigData->mFourceOutput;
		this->mOutputCompareMask = pBswConfigData->mOutputCompareMask;
		this->mOutputCompareData = pBswConfigData->mOutputCompareData;
		this->mOutputCompareModeLevelLow = pBswConfigData->mOutputCompareModeLevelLow;
		this->mOutputCompareModeLevelHigh = pBswConfigData->mOutputCompareModeLevelHigh;
		this->mInputCaptureFallingRisingEdgeLow = pBswConfigData->mInputCaptureFallingRisingEdgeLow;
		this->minputCaptureFallingRisingEdgeHigh = pBswConfigData->minputCaptureFallingRisingEdgeHigh;
		this->mChannelInterruptEnable = pBswConfigData->mChannelInterruptEnable;
		this->mTimerCounterResetEnable = pBswConfigData->mTimerCounterResetEnable;
		this->mTimerOverflowInterruptEnable = pBswConfigData->mTimerOverflowInterruptEnable;
		this->mOutputComparePinDisconnect = pBswConfigData->mOutputComparePinDisconnect;
		this->mPrecisionTimerPrescaler = pBswConfigData->mPrecisionTimerPrescaler;		
		for( i=0; i<MCS12G_TIMER_CHANNEL_NUMBER; i++ ){
			this->mTimerChannelCounter[i] = pBswConfigData->mTimerChannelCounter[i];	
		}	
	}
	
	this->mUpdateRequest = 1;
	this->mStatus = mcs12g_timer_applyConfig(this);
	return ERROR_OK;	
}

unsigned char mcs12g_timer_update(Mcs12gTimerDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		this->mStatus = mcs12g_timer_applyConfig(this);
	}
	return ERROR_OK;
}

unsigned char mcs12g_timer_applyConfig(Mcs12gTimerDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mUpdateRequest = 0;
	TSCR1_PRNT = 1;	
	TSCR1_TEN = 0; 
	TIOS = this->mInputCaptureOutputCompareSelect;
	CFORC = this->mFourceOutput;
	OC7M = this->mOutputCompareMask;
	OC7D = this->mOutputCompareData;
	TSCR1_TFFCA = 0;
	TSCR1_TSFRZ = 1;
	TSCR1_TSWAI = 1;
	TCTL2 = this->mOutputCompareModeLevelLow;
	TCTL1 = this->mOutputCompareModeLevelHigh;
	TCTL4 = this->mInputCaptureFallingRisingEdgeLow;
	TCTL3 = this->minputCaptureFallingRisingEdgeHigh;
	TIE = this->mChannelInterruptEnable;
	TSCR2_TCRE = this->mTimerCounterResetEnable;
	TSCR2_TOI = this->mTimerOverflowInterruptEnable;
	TC0 = this->mTimerChannelCounter[0];	
	TC1 = this->mTimerChannelCounter[1];	
	TC2 = this->mTimerChannelCounter[2];	
	TC3 = this->mTimerChannelCounter[3];	
	TC4 = this->mTimerChannelCounter[4];	
	TC5 = this->mTimerChannelCounter[5];	
	TC6 = this->mTimerChannelCounter[6];	
	TC7 = this->mTimerChannelCounter[7];		
	OCPD = this->mOutputComparePinDisconnect;
	PTPSR = this->mPrecisionTimerPrescaler;
	TSCR1_TEN = 1; 
	return ERROR_OK;	
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vtimch7 void ISR_timer_channel7(){
	if( TFLG1_C7F ){
		gMcs12gTimerData.mTimerCounter++;	
		//onTimeoutCallback
		appl_schedule_updateTaskFlag();
		TFLG1_C7F = 1;		
	}
}
#pragma CODE_SEG DEFAULT