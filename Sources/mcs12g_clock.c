#include "mcs12g_clock.h"

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

/**
mStatus;	
mOscillatorFrequency;
mPLLFrequency;
mBusFrequency;
mReferenceFrequency;
mREFDIV;
mVCOFrequency;
mSYNDIV;
mPOSTDIV;
/**/

Mcs12gClockDataType gMcs12gClockData;


unsigned char mcs12g_clock_init(Mcs12gClockDataType* this, const Mcs12gClockBswConfigDataType* pConfigData){
	if( !this ){
		return  ERROR_NOT_OK;
	}
	this->mStatus = 0;
	this->mOscillatorFrequency = OscillatorFrequency_8MHZ;
	this->mPLLFrequency = 48000000;
	this->mBusFrequency = 24000000;
	this->mReferenceFrequency = ReferenceFrequency_1MHZ_2MHZ;
	this->mREFDIV = 0;
	this->mVCOFrequency = VCOFrequency_32MHZ_48MHZ;
	this->mSYNDIV = 23;
	this->mPOSTDIV = 0;
	
	if( pConfigData ){
		if( 	IS_OSCILLATOR_FREQUENCY( this->mOscillatorFrequency ) 
			&& IS_REFERENCE_FREQUENCY_DATA_TYPE( this->mReferenceFrequency )
			&& IS_VCO_FREQUENCY_DATA_TYPE( this->mVCOFrequency )
		){
			this->mOscillatorFrequency = pConfigData->mOscillatorFrequency;
			this->mReferenceFrequency = pConfigData->mReferenceFrequency;
			this->mREFDIV = pConfigData->mREFDIV;
			this->mVCOFrequency = pConfigData->mVCOFrequency;
			this->mSYNDIV = pConfigData->mSYNDIV;
			this->mPOSTDIV = pConfigData->mPOSTDIV;		
		}
	}	
	mcs12g_clock_applyConfig(this);
	return ERROR_OK;	
}

unsigned char mcs12g_clock_update(Mcs12gClockDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	if( 1==this->mUpdateRequest ){
		this->mUpdateRequest = 0;
		mcs12g_clock_applyConfig(this);			
	}
	return ERROR_OK;
}

unsigned char mcs12g_clock_applyConfig(Mcs12gClockDataType* this){
	static unsigned long timeoutCounter = 0;
	unsigned long timeoutCounterMax = 60000;
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mUpdateRequest = 0;
	CPMUPROT = 0x26;
	CPMUOSC_OSCE = 0;
	CPMUCLKS_PLLSEL = 1;	
	CPMUREFDIV_REFFRQ = this->mReferenceFrequency;
	CPMUREFDIV_REFDIV = this->mREFDIV;
	CPMUSYNR_VCOFRQ = this->mVCOFrequency;
	CPMUSYNR_SYNDIV = this->mSYNDIV;
	CPMUPOSTDIV_POSTDIV = this->mPOSTDIV;
	CPMUOSC_OSCE = 1;
	timeoutCounter = 0;
	while( (!CPMUFLG_LOCK || !CPMUFLG_UPOSC) &&  timeoutCounter<timeoutCounterMax){
		timeoutCounter++;	
	}
	if( timeoutCounter>=timeoutCounterMax ){
		// timeout callback	
		this->mStatus = ERROR_NOT_OK;
	}	
	CPMUPROT = 0;
	this->mPLLFrequency = this->mOscillatorFrequency/(this->mREFDIV+1)*2*(this->mSYNDIV+1)/(this->mPOSTDIV+1);
	this->mBusFrequency = this->mPLLFrequency/2;
	return ERROR_OK;
}

unsigned long mcs12g_clock_getBusFrequency(Mcs12gClockDataType* this){
	if( !this ){
		return ERROR_NOT_OK;
	}
	return this->mBusFrequency;
}


unsigned char appl_clock_init(){
	return mcs12g_clock_init(&gMcs12gClockData, &gMcs12gClockBswConfigData);	
}

unsigned char appl_clock_update(){
	return mcs12g_clock_update(&gMcs12gClockData);	
}

unsigned long appl_clock_getBusFrequency(){
	return mcs12g_clock_getBusFrequency(&gMcs12gClockData);	
}