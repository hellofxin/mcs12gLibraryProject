#ifndef MCS12G_SPI_DATATYPE_H
#define MCS12G_SPI_DATATYPE_H

typedef enum mcs12gSpiDataWidthDataType{
	Mcs12gSpiDataWidth_8bit = 0,
	Mcs12gSpiDataWidth_16bit = 1	
}Mcs12gSpiDataWidthDataType;

#define IS_MCS12G_SPI_DATA_WIDTH_DATA_TYPE(p)	(	Mcs12gSpiDataWidth_8bit==(p)		\
													|| Mcs12gSpiDataWidth_16bit==(p)	\
												)			

typedef struct mcs12gSpiDataType{
	unsigned char mStatus;
	unsigned long mBaudrate;
	unsigned short* mTxDataPointer;
	unsigned char mTxDataLength;
	unsigned short mTxData;
	unsigned short mRxData;
	unsigned short mTxCounter;
	unsigned short mRxCounter;
	unsigned char mUpdateRequest;
	unsigned char mMasterEnable;
	unsigned char mLeastSignificantBitFirstEnable;
	unsigned char mSlaveSelectOutputEnable;
	unsigned char mClockPolarity;
	unsigned char mClockPhase;
	unsigned char mTransmitEmptyInterruptEnable;
	unsigned char mDataReceivedInterruptEnable;
	unsigned char mDataWidth;
	unsigned char mSPR;
	unsigned char mSPPR;		
}Mcs12gSpiDataType;


typedef struct mcs12gSpiBswConfigDataType{
	unsigned char mMasterEnable;
	unsigned char mLeastSignificantBitFirstEnable;
	unsigned char mSlaveSelectOutputEnable;
	unsigned char mClockPolarity;
	unsigned char mClockPhase;
	unsigned char mTransmitEmptyInterruptEnable;
	unsigned char mDataReceivedInterruptEnable;
	unsigned char mDataWidth;
	unsigned char mSPR;
	unsigned char mSPPR;		
}Mcs12gSpiBswConfigDataType;

#endif