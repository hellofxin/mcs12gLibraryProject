#include "mcs12g_sci.h"
#include "mcs12g_clock.h"

Mcs12gSciDataType gMcs12gSciData;

unsigned char gSciDataBuffer[22];
unsigned char gSciDataBufferRx[100];

/**
unsigned char* mTxDataBufferPointer;
unsigned char mTxDataBufferLength;
unsigned char* mTxDataPointer;
unsigned char mTxDataIndex;
unsigned char* mRxDataBufferPointer;
unsigned char mRxDataBufferLength;
unsigned char* mRxDataPointer;
unsigned char mRxDataLength;
unsigned char mRxDataIndex;
unsigned short mTxCounter;
unsigned short mRxCounter;
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

/**
When IREN = 0 then,
SCI baud rate = SCI bus clock / (16 x SBR[12:0])
When IREN = 1 then,
SCI baud rate = SCI bus clock / (32 x SBR[12:1])
/**/

unsigned char mcs12g_sci_init(Mcs12gSciDataType* this, const Mcs12gSciBswConfigDataType* pBswConfigData){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mStatus = 0;
	this->mUpdateRequest = 1;
	this->mBaudRatePrescaler = 156;
	this->mParityType = Mcs12gSciParity_even;
	this->mParityEnable = 0;
	this->mDataMode = Mcs12gSciDataMode_8bit;
	this->mLoopbackEnable = 0;
	this->mRIE = 1;
	this->mTIE = 0;
	this->mTCIE = 0;
	this->mTxDataBufferPointer = 0;
	this->mTxDataLength = 0;
	this->mTxDataPointer = 0;
	this->mTxDataIndex = 0;
	this->mRxDataBufferPointer = 0;
	this->mRxDataBufferLength = 0;
	this->mRxDataPointer = 0;
	this->mRxDataLength = 0;	
	this->mRxDataIndex = 0;		
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
	mcs12g_sci_applyConfig(this);
	mcs12g_sci_postInit(this);
	
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
	mcs12g_sci_update_tx(this);
	return ERROR_OK;
}

/**
 ** When IREN = 0 then, SCI baud rate = SCI bus clock / (16 x SBR[12:0])
/**/
unsigned char mcs12g_sci_applyConfig(Mcs12gSciDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mUpdateRequest = 0;
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
	this->mBaudrate = appl_clock_getBusFrequency()/16/(this->mBaudRatePrescaler);		
	return ERROR_OK;	
}

unsigned char mcs12g_sci_postInit(Mcs12gSciDataType* this){
	unsigned char i = 0;
	for( i=0; i<22; i++ ){
		gSciDataBuffer[i] = i;			
	}	
	this->mTxDataBufferPointer = &gSciDataBuffer[0];
	this->mTxDataLength = 0;	
	this->mRxDataBufferPointer = &gSciDataBufferRx[0];
	this->mRxDataBufferLength = 20;
	this->mRxDataIndex = 0;
	this->mRxDataPointer = this->mRxDataBufferPointer;
	
	gSciDataBuffer[0] = 'S';	
	gSciDataBuffer[1] = 'C';	
	gSciDataBuffer[2] = 'I';	
	gSciDataBuffer[3] = ' ';	
	gSciDataBuffer[4] = 'C';	
	gSciDataBuffer[5] = 'O';	
	gSciDataBuffer[6] = 'M';	
	gSciDataBuffer[7] = '.';	
	gSciDataBuffer[8] = ' ';	
	return ERROR_OK;
}

unsigned char mcs12g_sci_update_tx(Mcs12gSciDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( this->mTxDataLength &&  this->mTxDataBufferPointer ){
		this->mTxDataPointer = this->mTxDataBufferPointer;
		for( this->mTxDataIndex = 0; this->mTxDataIndex<this->mTxDataLength; this->mTxDataIndex++ ){
			while( 0==SCI0SR1_TDRE );
			SCI0DRL = *this->mTxDataPointer++; 
			this->mTxCounter++;
		}
		this->mTxDataLength = 0;
		this->mTxDataBufferPointer = 0;
	}
	return ERROR_OK;	
}

unsigned char mcs12g_sci_update_rx(Mcs12gSciDataType* this){
		this->mRxDataBufferPointer[this->mRxDataIndex++] = SCI0DRL;	
		if( this->mRxDataIndex>=this->mRxDataBufferLength ){
			this->mRxDataIndex = 0;	
		}
		if( this->mRxDataLength< this->mRxDataBufferLength ){
			this->mRxDataLength++;	
		}
		else{
			//onOverflow	
		}		
		this->mRxCounter++;	
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vsci0 void ISR_sci0(){
	if( SCI0SR1_RDRF ){
		mcs12g_sci_update_rx(&gMcs12gSciData);
		SCI0SR1_RDRF = 1;		
	}	
}
#pragma CODE_SEG DEFAULT


unsigned char appl_sci_init(){
	return mcs12g_sci_init(&gMcs12gSciData, &gMcs12gSciBswConfigData);	
}
unsigned char appl_sci_update(){
	return mcs12g_sci_update(&gMcs12gSciData);	
}


/**
 ** @brief 和应用相关较强,要进一步处理
/**/
unsigned char mcs12g_sci_txReq(Mcs12gSciDataType* this){
	if(!this){
		return ERROR_NOT_OK;
	}
	this->mTxDataBufferPointer = &gSciDataBuffer[0];
	this->mTxDataLength = 9;
	return ERROR_OK;
}

unsigned char mcs12g_sci_getRxData(Mcs12gSciDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( this->mRxDataLength>=8 ){
		this->mRxDataLength -= 8;
		this->mRxDataPointer += 8;
	}
	else{
		this->mRxDataPointer += this->mRxDataLength;
		this->mRxDataLength = 0;			
	}
	if( this->mRxDataPointer > &(this->mRxDataBufferPointer[this->mRxDataBufferLength-1]) ){
		this->mRxDataPointer = &this->mRxDataBufferPointer[0] + (this->mRxDataPointer - &this->mRxDataBufferPointer[this->mRxDataBufferLength-1]-1);						
	}	
}