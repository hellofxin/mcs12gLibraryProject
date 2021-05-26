#ifndef MCS12G_ADC_DATATYPE_H
#define MCS12G_ADC_DATATYPE_H

#define MCS12G_ADC_CHANNEL_NUMBER		12

typedef enum mcs12gAdcResolutionDataType{
	Mcs12gAdcResolution_8bit = 0,
	Mcs12gAdcResolution_10bit = 1		
}Mcs12gAdcResolutionDataType;

typedef struct mcs12gAdcDataType{
	unsigned char mStatus;
	unsigned char mUpdateRequest;
	unsigned char mResolution;	
	unsigned char mConversionSequenceLength;
	unsigned char mWrap;	
	unsigned char mMulti;
	unsigned char mScanMode;
	unsigned char mChannelSelectCode;
	unsigned char mSequenceCompleteInterruptEnable;
	unsigned short mData[MCS12G_ADC_CHANNEL_NUMBER];
}Mcs12gAdcDataType;

typedef struct mcs12gAdcBswConfigDataType{
	unsigned char mStatus;
	unsigned char mUpdateRequest;
	unsigned char mResolution;	
	unsigned char mConversionSequenceLength;
	unsigned char mWrap;	
	unsigned char mMulti;
	unsigned char mScanMode;
	unsigned char mChannelSelectCode;
	unsigned char mSequenceCompleteInterruptEnable;
}Mcs12gAdcBswConfigDataType;


#define IS_MCS12G_ADC_RESOLUTION_DATA_TYPE(p)		( 	Mcs12gAdcResolution_8bit==(p)		\
														|| Mcs12gAdcResolution_10bit==(p)	\
													)

#endif