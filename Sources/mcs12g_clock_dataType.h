#ifndef MCS12G_CLOCK_DATATYPE_H
#define MCS12G_CLOCK_DATATYPE_H

/**
# step1
REFCLK Frequency Ranges(OSCE=1) 		REFFRQ[1:0]
1MHz <= fREF <= 2MHz 				00
2MHz < fREF <= 6MHz 					01
6MHz < fREF <= 12MHz 				10
fREF >12MHz 							11

If XOSCLCP is enabled (OSCE=1) 			Fref = Fosc/(REFDIV +1)
If XOSCLCP is disabled (OSCE=0) 		fREF = fIRC1M


# step2
VCOCLK Frequency Ranges 				VCOFRQ[1:0]
32MHz <= fVCO<= 48MHz 				00
48MHz < fVCO<= 50MHz 				01
Reserved 							10
Reserved 							11

If PLL has locked (LOCK=1) 				fVCO = 2*Fref*(SYNDIV+1)


# step3
If PLL is locked (LOCK=1) 				Fpll = Fvco/(POSTDIV +1)
If PLL is not locked (LOCK=0) 			fPLL = Fvco/4
If PLL is selected (PLLSEL=1) 			Fbus = Fpll/2
/**/


#define OscillatorFrequency_4MHZ 		4000000
#define OscillatorFrequency_8MHZ		8000000
#define OscillatorFrequency_20MHZ		20000000	

#define IS_OSCILLATOR_FREQUENCY(p)	( 	OscillatorFrequency_4MHZ==(p)		\
										|| OscillatorFrequency_8MHZ==(p)	\
										|| OscillatorFrequency_20MHZ==(p)	\
									)	

typedef enum referenceFrequencyRangeDataType{
	ReferenceFrequency_1MHZ_2MHZ = 0,
	ReferenceFrequency_2MHZ_6MHZ = 1,
	ReferenceFrequency_6MHZ_12MHZ = 2,
	ReferenceFrequency_12MHZ_andAbove = 3,
	ReferenceFrequency_default = ReferenceFrequency_6MHZ_12MHZ	
}ReferenceFrequencyDataType;

typedef enum vcoFrequencyRangeDataType{
	VCOFrequency_32MHZ_48MHZ = 0,
	VCOFrequency_48MHZ_50MHZ = 1,
	VCOFrequency_default = VCOFrequency_32MHZ_48MHZ			
}VCOFrequencyDataType;

typedef struct mcs12gClockDataType{
	unsigned char mStatus;	
	unsigned long mOscillatorFrequency;
	unsigned long mPLLFrequency;
	unsigned long mBusFrequency;
	unsigned char mUpdateRequest;
	unsigned char mReferenceFrequency;
	unsigned char mREFDIV;
	unsigned char mVCOFrequency;
	unsigned char mSYNDIV;
	unsigned char mPOSTDIV;	
}Mcs12gClockDataType;

typedef struct mcs12gClockBswConfigDataType{
	unsigned long mOscillatorFrequency;
	unsigned char mReferenceFrequency;
	unsigned char mREFDIV;
	unsigned char mVCOFrequency;
	unsigned char mSYNDIV;
	unsigned char mPOSTDIV;	
}Mcs12gClockBswConfigDataType;


#define IS_REFERENCE_FREQUENCY_DATA_TYPE(p)		(	ReferenceFrequency_1MHZ_2MHZ==(p)			\
													|| ReferenceFrequency_2MHZ_6MHZ==(p)			\
													|| ReferenceFrequency_6MHZ_12MHZ==(p)		\
													|| ReferenceFrequency_12MHZ_andAbove==(p)		\
												)	
												
#define IS_VCO_FREQUENCY_DATA_TYPE(p)			(	VCOFrequency_32MHZ_48MHZ==(p)				\
													|| VCOFrequency_48MHZ_50MHZ==(p)			\
												)														

#endif