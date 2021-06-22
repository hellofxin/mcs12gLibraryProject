#include "mcs12g_sci_config.h"

/**
unsigned char mBaudRatePrescaler;
unsigned char mParityType;
unsigned char mParityEnable;
unsigned char mDataMode;
unsigned char mLoopbackEnable;
unsigned char mRIE;
unsigned char mTIE;
unsigned char mTCIE; 
/**/

/**
When IREN = 0 then,
SCI baud rate = SCI bus clock / (16 x SBR[12:0])
When IREN = 1 then,
SCI baud rate = SCI bus clock / (32 x SBR[12:1])
/**/

/**
 ** @brief IREN=0;
 **
/**/
const Mcs12gSciBswConfigDataType gMcs12gSciBswConfigData = {
	156,
	Mcs12gSciParity_even,
	0,
	Mcs12gSciDataMode_8bit,
	0,
	1,
	0,
	0		
};