#include "mcs12g_spi.h"

Mcs12gSpiDataType gMcs12gSpiData;

unsigned char appl_spi_init(){
	return mcs12g_spi_init(&gMcs12gSpiData, &gMcs12gSpiBswConfigData);	
}

unsigned char appl_spi_update(){
	return mcs12g_spi_update(&gMcs12gSpiData);	
};

/**
mStatus;
mUpdateRequest;
mMasterEnable;
mLeastSignificantBitFirstEnable;
mSlaveSelectOutputEnable;
mClockPolarity;
mClockPhase;
mTransmitEmptyInterruptEnable;
mDataReceivedInterruptEnable;
mDataWidth;
mSPR;
mSPPR;	
/**/
unsigned char mcs12g_spi_init(Mcs12gSpiDataType* this, const Mcs12gSpiBswConfigDataType* pBswConfigData){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mStatus = 0;
	this->mUpdateRequest = 1;
	this->mMasterEnable = 1;
	this->mLeastSignificantBitFirstEnable = 0;
	this->mSlaveSelectOutputEnable = 1;
	this->mClockPolarity = 0;
	this->mClockPhase = 0;
	this->mTransmitEmptyInterruptEnable = 0;
	this->mDataReceivedInterruptEnable = 1;
	this->mDataWidth = Mcs12gSpiDataWidth_8bit;
	this->mSPR = 2;
	this->mSPPR = 2;
	this->mTxRequest = 0;
	this->mTxData = 0;
	this->mRxData = 0;
	this->mTxCounter = 0;
	this->mRxCounter = 0;
	
	if( pBswConfigData ){
		this->mMasterEnable = pBswConfigData->mMasterEnable;
		this->mLeastSignificantBitFirstEnable = pBswConfigData->mLeastSignificantBitFirstEnable;
		this->mSlaveSelectOutputEnable = pBswConfigData->mSlaveSelectOutputEnable;
		this->mClockPolarity = pBswConfigData->mClockPolarity;
		this->mClockPhase = pBswConfigData->mClockPhase;
		this->mTransmitEmptyInterruptEnable = pBswConfigData->mTransmitEmptyInterruptEnable;
		this->mDataReceivedInterruptEnable = pBswConfigData->mDataReceivedInterruptEnable;
		if( IS_MCS12G_SPI_DATA_WIDTH_DATA_TYPE( pBswConfigData->mDataWidth ) ){
			this->mDataWidth = pBswConfigData->mDataWidth;			
		}		
		this->mSPR = pBswConfigData->mSPR;
		this->mSPPR = pBswConfigData->mSPPR;		
	}
	
	this->mUpdateRequest = 1;
	this ->mStatus = mcs12g_spi_applyConfig(this);
	return ERROR_OK;	
}

unsigned char mcs12g_spi_update(Mcs12gSpiDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		mcs12g_spi_applyConfig(this);
	}
	if( 1==this->mTxRequest && 1==SPI0SR_SPTEF ){
		this->mTxRequest = 0;
		this->mTxCounter++;
		SPI0DR = this->mTxData;		
	}
	return ERROR_OK;
}

unsigned char mcs12g_spi_applyConfig(Mcs12gSpiDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mUpdateRequest = 0;
	SPI0CR1_SPE = 0;
	SPI0CR1_LSBFE = this->mLeastSignificantBitFirstEnable;
	SPI0CR1_SSOE = this->mSlaveSelectOutputEnable;
	SPI0CR1_CPHA = this->mClockPhase;
	SPI0CR1_CPOL = this->mClockPolarity;
	SPI0CR1_MSTR = this->mMasterEnable;
	SPI0CR1_SPTIE = this->mTransmitEmptyInterruptEnable;
	SPI0CR1_SPIE = 1;
	SPI0CR2_SPC0 = 0;
	SPI0CR2_SPISWAI = 1;
	SPI0CR2_MODFEN = 1;
	SPI0CR2_XFRW = this->mDataWidth;
	SPI0BR_SPR = this->mSPR;
	SPI0BR_SPPR = this->mSPPR;
	SPI0CR1_SPE = 1;		
	return ERROR_OK;	
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vspi0 void ISR_spi0(){
	if( SPI0SR_SPIF ){
		gMcs12gSpiData.mRxData = SPI0DR;	
		gMcs12gSpiData.mRxCounter++;
		SPI0SR_SPIF = 1;	
	}
}
#pragma CODE_SEG DEFAULT