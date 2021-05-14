#include "mc9s12g96.h"
#include "clock.h"

/**
 * @brief initailizes clock and watchDog modules.
 * @param None.
 * @retval None.
 * @note if watchDog is disabled, watchDog_init() will not be compiled. 
 * 		otherwise, watchDog_init() is to be compiled.
/**/
void clock_init(){
   	clock_init_PEE();
	watchDog_init();	
}

/**
* @brief PLL Engaged Internal (PEI) mode. The Bus Clock is based on the PLLCLK.
* @param None.
* @retval None.
* @note  f_ref_frq: 00: 1-2 MHz; 01: 2-6 MHz; 10: 6-12 MHz; 11: 12-  MHz;
* 	        OSCE = 1: f_ref = f_osc/(REFDIV+1); OSCE = 0: f_ref = f_IRC1M;
* 	        f_ref = 4MHz
* 	        VCOFRQ: 00: 32-48 MHz; 01: 48-50 MHz;
* 		f_VCO = f_ref *2*(SYNDIV+1);
* 		f_VCO = 40MHz 
/**/
void clock_init_PEE(){
	//IVBR = 0x40;
	CPMUPROT = 0x26;  			//protection of CPMUCLKS register  is disabled;  
	CPMUREFDIV_REFFRQ = 2;
	CPMUREFDIV_REFDIV = 0;   
	CPMUSYNR_VCOFRQ = 0;
	CPMUSYNR_SYNDIV = 1;    
	CPMUPOSTDIV = 0;
	CPMUCLKS_PLLSEL = 1;
	while(!CPMUCLKS_PLLSEL);
	CPMUOSC_OSCE = 1;
	while(!CPMUFLG_UPOSC);
	while(!CPMUFLG_LOCK);     
	CPMUPROT = 0;		 		//protection of CPMUCLKS register  is enabled; 
}

/**
* @brief PLL Engaged External (PEE) mode. The Bus Clock is based on the PLLCLK.
* @param None.
* @retval None.
* @note
/**/
void clock_init_PEI(){
    IVBR = 0x40;
    CPMUREFDIV_REFFRQ = 0;
    CPMUREFDIV_REFDIV = 0;
    CPMUSYNR_VCOFRQ = 1;
    CPMUSYNR_SYNDIV = 19;
    CPMUPOSTDIV = 0x01;
    CPMUCLKS_PLLSEL = 1;
    while(!CPMUCLKS_PLLSEL);
    while(!CPMUFLG_LOCK);
}

/**
* @brief initializes watchdog.
* @param None.
* @retval None.
* @note
/**/
void watchDog_init(){
	CPMUPROT = 0x26;
	CPMUCLKS_COPOSCSEL0 = 1;	   	//COP clock source is OSCCLK;
	CPMUCLKS_COPOSCSEL1 = 0;
	CPMUCLKS_PCE = 1;		       		//COP is enabled during pseudo stop mode;
	CPMUPROT = 0;
	CPMUCOP_CR = 6;			    	//set watch dog timer rate;
	CPMUCOP_RSBCK = 1;			//stop in BDM mode.
}

/**
* @brief resets watchdog.
* @param None.
* @retval None.
* @note
/**/
void watchDog_reset(){
	CPMUARMCOP = 0;
}

/**
* @brief feeds watchdog.
* @param None.
* @retval None.
* @note
/**/
void watchDog_feed(){
	CPMUARMCOP = 0x55;
	CPMUARMCOP = 0xAA;
}

/**
* @brief soft reset.
* @param None.
* @retval None.
* @note
/**/
void resetSoft(){
	asm("JSR 0xFFFE");
}