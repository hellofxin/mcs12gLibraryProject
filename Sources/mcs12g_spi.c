#include "mcs12g_spi.h"
#include "mcs12g_clock.h"
#include "test.h"

Mcs12gSpiDataType gMcs12gSpiData;

/**
unsigned short* mTxDataPointer;
unsigned char mTxDataLength;
unsigned short mRxData;
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
	this->mBaudrate = 0;
	this->mUpdateRequest = 1;
	this->mMasterEnable = 1;
	this->mLeastSignificantBitFirstEnable = 0;
	this->mSlaveSelectOutputEnable = 1;
	this->mClockPolarity = 0;
	this->mClockPhase = 1;
	this->mTransmitEmptyInterruptEnable = 0;
	this->mDataReceivedInterruptEnable = 1;
	this->mDataWidth = Mcs12gSpiDataWidth_8bit;
	this->mSPR = 2;
	this->mSPPR = 2;
	this->mTxDataPointer = 0;
	this->mTxDataLength = 0;
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
	this ->mStatus = mcs12g_spi_applyConfig(this);
	mcs12g_spi_postInit(this);

	return ERROR_OK;	
}

unsigned char mcs12g_spi_update(Mcs12gSpiDataType* this){
	unsigned short data;
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		mcs12g_spi_applyConfig(this);
	}
       mcs12g_spi_update_tx(this);
	return ERROR_OK;
}

unsigned char mcs12g_spi_applyConfig(Mcs12gSpiDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mUpdateRequest = 0;
	SPI1CR1_SPE = 0;
	SPI1CR1_LSBFE = this->mLeastSignificantBitFirstEnable;
	SPI1CR1_SSOE = this->mSlaveSelectOutputEnable;
	SPI1CR1_CPHA = this->mClockPhase;
	SPI1CR1_CPOL = this->mClockPolarity;
	SPI1CR1_MSTR = this->mMasterEnable;
	SPI1CR1_SPTIE = this->mTransmitEmptyInterruptEnable;
	SPI1CR1_SPIE = 1;
	SPI1CR2_SPC0 = 0;
	SPI1CR2_SPISWAI = 1;
	SPI1CR2_MODFEN = 1;
	SPI1CR2_XFRW = this->mDataWidth;
	SPI1BR_SPR = this->mSPR;
	SPI1BR_SPPR = this->mSPPR;
	SPI1CR1_SPE = 1;	
	this->mBaudrate = appl_clock_getBusFrequency()/(this->mSPPR+1)/userPow(2,this->mSPR+1);	
	return ERROR_OK;	
}

unsigned char mcs12g_spi_update_tx(Mcs12gSpiDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( this->mTxDataLength && this->mTxDataPointer ){
		while( 0==SPI1SR_SPTEF );
		SPI_checkTxData();
		this->mTxData = *this->mTxDataPointer;
		SPI1DR = this->mTxData; 
		this->mTxCounter++;
		this->mTxDataPointer = 0;
		this->mTxDataLength = 0;
	}	
	return ERROR_OK;
}

unsigned char mcs12g_spi_update_rx(Mcs12gSpiDataType* this){
	gMcs12gSpiData.mRxData = SPI1DR;	
	gMcs12gSpiData.mRxCounter++;	
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vspi1 void ISR_spi1(){
	if( SPI1SR_SPIF ){
	  	mcs12g_spi_update_rx(&gMcs12gSpiData);
		SPI1SR_SPIF = 1;	
	}
}
#pragma CODE_SEG DEFAULT


unsigned char appl_spi_init(){
	return mcs12g_spi_init(&gMcs12gSpiData, &gMcs12gSpiBswConfigData);	
}

unsigned char appl_spi_update(){
	return mcs12g_spi_update(&gMcs12gSpiData);	
}

unsigned long userPow(unsigned char x, unsigned char y){
	unsigned char i = 0;
	unsigned long result = 1;
	if( x==0 ){
		return 0;
	}
	for(i=0; i<y; i++){
		result *= x;
	}
	return result;
}


/**
 ** @brief 和应用强相关，需要进一步处理
/**/
unsigned char mcs12g_spi_postInit(Mcs12gSpiDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mTxDataPointer = (unsigned short*)&_SPI1TxData;
	NCV_DATA_SET_DEFAULT;
	NCV_STEP_LAMP_ON;
	DDRT_DDRT7 = 1;
	PTT_PTT7 = 1;	
	return ERROR_OK;
}

unsigned char mcs12g_spi_txRequest(Mcs12gSpiDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mTxDataPointer = (unsigned short*)&_SPI1TxData;
	this->mTxDataLength = 1;
	return ERROR_OK;	
}