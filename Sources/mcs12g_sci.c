#include "mcs12g_sci.h"

Mcs12gSciDataType gMcs12gSciData;

unsigned char appl_sci_init(){
	return mcs12g_sci_init(&gMcs12gSciData, &gMcs12gSciBswConfigData);	
}
unsigned char appl_sci_update(){
	return mcs12g_sci_update(&gMcs12gSciData);	
}

/**
mStatus;
mUpdateRequest;	
mBaudRatePrescaler;
mParityType;
mParityEnable;
mDataMode;
mLoopbackEnable;
mRIE;
mTIE;
mTCIE; 
/**/

unsigned char mcs12g_sci_init(Mcs12gSciDataType* this, const Mcs12gSciBswConfigDataType* pBswConfigData){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mStatus = 0;
	this->mUpdateRequest = 1;
	this->mBaudRatePrescaler = 156;
	this->mParityType = Mcs12gSciParity_even;
	this->mParityEnable = 1;
	this->mDataMode = Mcs12gSciDataMode_8bit;
	this->mLoopbackEnable = 0;
	this->mRIE = 1;
	this->mTIE = 0;
	this->mTCIE = 0;
	this->mTxDataPointer = 0;
	this->mTxDataLength = 0;
	this->mRxData = 0;
	this->mRxCounter = 0;
	this->mTxCounter = 0;
	
	if( pBswConfigData ){
		this->mBaudRatePrescaler = pBswConfigData->mBaudRatePrescaler;
		this->mParityType = pBswConfigData->mParityType;
		this->mParityEnable = pBswConfigData->mParityEnable;
		this->mDataMode = pBswConfigData->mDataMode;
		this->mLoopbackEnable = pBswConfigData->mLoopbackEnable;
		this->mRIE = pBswConfigData->mRIE;
		this->mTIE = pBswConfigData->mTIE;
		this->mTCIE = pBswConfigData->mTCIE;			
	}
	
	this->mUpdateRequest = 1;
	mcs12g_sci_applyCOnfig(this);	
	return ERROR_OK;	
}
unsigned char mcs12g_sci_update(Mcs12gSciDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		mcs12g_sci_applyConfig(this);	
	}
	if( this->mTxDataLength ){
		for( this->mTxDataIndex = 0; this->mTxDataIndex<this->mTxDataLength; this->mTxDataIndex++ ){
			while( 0==SCI0SR1_TDRE );
			SCI0DRL = *(this->mTxDataPointer+this->mTxDataIndex);	
		}
		this->mTxDataLength = 0;
		this->mTxDataPointer = 0;
	}
	return ERROR_OK;
}

/**
 ** When IREN = 0 then, SCI baud rate = SCI bus clock / (16 x SBR[12:0])
/**/
unsigned char mcs12g_sci_applyConfig(Mcs12gSciDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	SCI0CR2_RE = 0;
	SCI0CR2_TE = 0;
	SCI0BD_SBR = this->mBaudRatePrescaler;
	SCI0BD_IREN = 0;
	SCI0CR1_PT = this->mParityType;
	SCI0CR1_PE = this->mParityEnable;
	SCI0CR1_ILT = 0;
	SCI0CR1_WAKE = 0;
	SCI0CR1_M = this->mDataMode;
	SCI0CR1_RSRC = 0;
	SCI0CR1_SCISWAI = 1;
	SCI0CR1_LOOPS = this->mLoopbackEnable;
	SCI0CR2_RWU = 0;
	SCI0CR2_ILIE = 0;
	SCI0CR2_RIE = this->mRIE;
	SCI0CR2_TIE = this->mTIE;
	SCI0CR2_TCIE = this->mTCIE;
	SCI0SR2_BRK13 = 0;
	SCI0SR2_AMAP = 0;	
	SCI0CR2_RE = 1;
	SCI0CR2_TE = 1;			
	return ERROR_OK;	
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vsci0 void ISR_sci0(){
	if( SCI0SR1_RDRF ){
		gMcs12gSciData.mRxData = SCI0DRL;	
		SCI0SR1_RDRF = 1;		
	}
}
#pragma CODE_SEG DEFAULT