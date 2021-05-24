#ifndef MCS12G_CLOCK_H
#define MCS12G_CLOCK_H

#include "mc9s12g128.h"
#include "mcs12g_clock_dataType.h"
#include "mcs12g_clock_config.h"

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

#define ERROR_OK				0
#define ERROR_NOT_OK		1

extern Mcs12gClockDataType gMcs12gClockData;

unsigned char mcs12g_clock_init(Mcs12gClockDataType* this, Mcs12gClockConfigDataType* pConfigData);

#endif