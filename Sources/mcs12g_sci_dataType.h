#ifndef MCS12G_SCI_DATATYPE_H
#define MCS12G_SCI_DATATYPE_H

typedef enum mcs12gSciParityDataType{
	Mcs12gSciParity_even = 0,
	Mcs12gSciParity_odd = 1	
}Mcs12gSciParityDataType;

#define IS_MCS12G_SCI_PARITY_DATA_TYPE(p)		( 	Mcs12gSciParity_even==(p)		\
												|| Mcs12gSciParity_odd==(p)	\
											)

typedef enum mcs12gSciDataModeDataType{
	Mcs12gSciDataMode_8bit = 0,
	Mcs12gSciDataMode_9bit = 1	
}Mcs12gSciDataModeDataType;

#define IS_MCS12G_SCI_DATA_MODE_DATA_TYPE(p)	( 	Mcs12gSciDataMode_8bit==(p)		\
													|| Mcs12gSciDataMode_9bit==(p)	\
												)	

typedef struct mcs12gSciDataType{
	unsigned char mStatus;
	unsigned long mBaudrate;
	unsigned char* mTxDataBufferPointer;
	unsigned char mTxDataLength;
	unsigned char* mTxDataPointer;
	unsigned char mTxDataIndex;
	unsigned char* mRxDataBufferPointer;
	unsigned char mRxDataBufferLength;
	unsigned char mRxDataIndex;
	unsigned char* mRxDataPointer;
	unsigned char mRxDataLength;
	unsigned short mTxCounter;
	unsigned short mRxCounter;
	unsigned char mFlushRxDataBuffer;
	unsigned char mUpdateRequest;	
	unsigned char mBaudRatePrescaler;
	unsigned char mParityType;
	unsigned char mParityEnable;
	unsigned char mDataMode;
	unsigned char mLoopbackEnable;
	unsigned char mRIE;
	unsigned char mTIE;
	unsigned char mTCIE; 
}Mcs12gSciDataType;

typedef struct mcs12gSciBswConfigDataType{
	unsigned char mBaudRatePrescaler;
	unsigned char mParityType;
	unsigned char mParityEnable;
	unsigned char mDataMode;
	unsigned char mLoopbackEnable;
	unsigned char mRIE;
	unsigned char mTIE;
	unsigned char mTCIE; 
}Mcs12gSciBswConfigDataType;

#endif