#include "mcs12g_adc.h"

unsigned char appl_adc_init(){
	return mcs12g_adc_init(&gMcs12gAdcData, &gMcs12gAdcBswConfigData);	
}
unsigned char appl_adc_update(){
	return mcs12g_adc_update(&gMcs12gAdcData);	
}

/**
mStatus;
mUpdateRequest;
mResolution;	
mConversionSequenceLength;
mWrap;	
mMulti;
mScanMode;
mChannelSelectCode;
mSequenceCompleteInterruptEnable;
short mData[MCS12G_ADC_CHANNEL_NUMBER];
/**/

Mcs12gAdcDataType gMcs12gAdcData;

unsigned char mcs12g_adc_init(Mcs12gAdcDataType* this, const Mcs12gAdcBswConfigDataType* pConfigData){
	unsigned char i = 0;
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mStatus = 0;
	this->mUpdateRequest = 1;
	this->mResolution = Mcs12gAdcResolution_10bit;
	this->mConversionSequenceLength = 1;
	this->mWrap = 0;
	this->mMulti = 0;
	this->mScanMode = 0;	
	this->mChannelSelectCode = 0;
	this->mSequenceCompleteInterruptEnable = 0;
	for(i=0; i<MCS12G_ADC_CHANNEL_NUMBER; i++){
		this->mData[i] = 0;
	}
	
	if( pConfigData ){
		this->mResolution = pConfigData->mResolution;;
		this->mConversionSequenceLength = pConfigData->mConversionSequenceLength;
		this->mWrap = pConfigData->mWrap;
		this->mMulti = pConfigData->mMulti;
		this->mScanMode = pConfigData->mScanMode;	
		this->mChannelSelectCode = pConfigData->mChannelSelectCode; 
		this->mSequenceCompleteInterruptEnable =  pConfigData->mSequenceCompleteInterruptEnable;
	}
	
	this->mUpdateRequest = 1;
	this->mStatus = mcs12g_adc_applyConfig(this);
	return ERROR_OK;
}

unsigned char mcs12g_adc_update(Mcs12gAdcDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;	
		this->mStatus = mcs12g_adc_applyConfig(this);	
	}
	if( ATDSTAT0_SCF ){
		this->mData[0] = ATDDR0;
		this->mData[1] = ATDDR1;
		this->mData[2] = ATDDR2;
		this->mData[3] = ATDDR3;
		this->mData[4] = ATDDR4;
		this->mData[5] = ATDDR5;
		this->mData[6] = ATDDR6;
		this->mData[7] = ATDDR7;
		this->mData[8] = ATDDR8;
		this->mData[9] = ATDDR9;
		this->mData[10] = ATDDR10;
		this->mData[11] = ATDDR11;
		ATDSTAT0_SCF = 1;
	}
	ATDCTL5_CC = this->mChannelSelectCode;
	return ERROR_OK;	
}

unsigned char mcs12g_adc_applyConfig(Mcs12gAdcDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mUpdateRequest = 0;	
	ATDCTL0_WRAP = this->mWrap;
	ATDCTL1_SMP_DIS = 1;
	ATDCTL1_SRES = this->mResolution;
	ATDCTL2_ASCIE = this->mSequenceCompleteInterruptEnable;
	ATDCTL2_AFFC = 1;
	ATDCTL3_FRZ = 2;
	ATDCTL3_FIFO = 0;
	ATDCTL3_S8C = (this->mConversionSequenceLength&8)>0? 1:0;
	ATDCTL3_S4C = (this->mConversionSequenceLength&4)>0? 1:0;
	ATDCTL3_S2C = (this->mConversionSequenceLength&2)>0? 1:0;
	ATDCTL3_S1C = (this->mConversionSequenceLength&1)>0? 1:0;
	ATDCTL3_DJM = 1;
	ATDCTL4_PRS = 1;
	ATDCTL4_SMP = 1;
	ATDCTL5_MULT = this->mMulti;
	ATDCTL5_SCAN = this->mScanMode;
	ATDDIEN = 0xFFFF;
	return ERROR_OK;
}