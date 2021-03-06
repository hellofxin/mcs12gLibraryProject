#ifndef SPI_H
#define SPI_H

//#include "mc9s12g96.h"

#define NCV_CHANNEL_ON	1
#define NCV_CHANNEL_OFF 	0

typedef union{	
	word NCV_DATA_WORD;
	struct{	
		// high byte;			
		word NCV_DATA_BIT8		:1;
		word NCV_DATA_BIT9		:1;
		word NCV_DATA_BIT10		:1;
		word NCV_DATA_BIT11		:1;
		word NCV_DATA_BIT12		:1;
		word NCV_DATA_BIT13		:1;
		word NCV_DATA_BIT14		:1;
		word NCV_DATA_BIT15		:1;	
		// low byte;
		word NCV_DATA_BIT0		:1;
		word NCV_DATA_BIT1		:1;
		word NCV_DATA_BIT2		:1;
		word NCV_DATA_BIT3		:1;
		word NCV_DATA_BIT4		:1;
		word NCV_DATA_BIT5		:1;
		word NCV_DATA_BIT6		:1;
		word NCV_DATA_BIT7		:1;			
	}NCV_DATA_BITS;
	struct{
		// high byte;				
		word 						:1;
		word NCV_DATA_OUT5		:2;
		word NCV_DATA_OUT6		:2;
		word						:1;
		word						:1;
		word						:1;
		// low byte;
		word 						:1;	
		word 						:1;
		word 						:1;
		word 						:1;
		word 						:1;
		word 						:1;
		word 						:1;
		word 						:1;					
	}NCV_DATA_mergedBits;
}TYPE_NCV7708Data;
extern TYPE_NCV7708Data 	_SPI1TxData;

#define SPI1TxData 		( _SPI1TxData.NCV_DATA_WORD )
// 成员运算符优先级高于取地址运算符，不用括号也可以；
#define NCV_SRR			( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT0 )
#define NCV_OUTL1	      	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT1 )
#define NCV_OUTH1	  	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT2 )
#define NCV_OUTL2	   	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT3 )
#define NCV_OUTH2	 	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT4 )
#define NCV_OUTL3	  	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT5 )
#define NCV_OUTH3	  	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT6 )
#define NCV_OUTL4 		( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT7 )
#define NCV_OUTH4	   	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT8 )
#define NCV_OUTL5	   	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT9 )
#define NCV_OUTH5	   	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT10 )
#define NCV_OUTL6	  	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT11 )
#define NCV_OUTH6	  	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT12 )
#define NCV_OCD	  		( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT13 )
#define NCV_ULD	  		( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT14 )
#define NCV_OVLO	 	( _SPI1TxData.NCV_DATA_BITS.NCV_DATA_BIT15 )

#define NCV_STEP_LAMP					NCV_OUTH1
#define NCV_MIRROR_HEAT_LED			NCV_OUTH2
#define NCV_DOOR_BACKGROUND_LED 	NCV_OUTH3

#define NCV_OUT5			( _SPI1TxData.NCV_DATA_mergedBits.NCV_DATA_OUT5 )
#define NCV_OUT6			( _SPI1TxData.NCV_DATA_mergedBits.NCV_DATA_OUT6 )

#define NCV_OUT4OFF		{ (NCV_OUTL4 = NCV_CHANNEL_OFF); (NCV_OUTH4 = NCV_CHANNEL_OFF); }
#define NCV_OUT4LOW		{ (NCV_OUTL4 = NCV_CHANNEL_ON); (NCV_OUTH4 = NCV_CHANNEL_OFF); }
#define NCV_OUT4HIGH		{ (NCV_OUTL4 = NCV_CHANNEL_OFF); (NCV_OUTH4 = NCV_CHANNEL_ON); }

#define NCV_OUT5OFF		( NCV_OUT5 = 0 )
#define NCV_OUT5LOW		( NCV_OUT5 = 1 )
#define NCV_OUT5HIGH		( NCV_OUT5 = 2 )
#define NCV_OUT6OFF		( NCV_OUT6 = 0 ) 
#define NCV_OUT6LOW		( NCV_OUT6 = 1 )
#define NCV_OUT6HIGH		( NCV_OUT6 = 2 )

#define NCV_STEP_LAMP_ON					( NCV_STEP_LAMP = NCV_CHANNEL_ON )
#define NCV_STEP_LAMP_OFF					( NCV_STEP_LAMP = NCV_CHANNEL_OFF )
#define NCV_MIRROR_HEAT_LED_ON			( NCV_MIRROR_HEAT_LED = NCV_CHANNEL_ON )
#define NCV_MIRROR_HEAT_LED_OFF			( NCV_MIRROR_HEAT_LED = NCV_CHANNEL_OFF )
#define NCV_DOOR_BACKGROUND_LED_ON 	( NCV_DOOR_BACKGROUND_LED = NCV_CHANNEL_ON )
#define NCV_DOOR_BACKGROUND_LED_OFF 	( NCV_DOOR_BACKGROUND_LED = NCV_CHANNEL_OFF )	
#define NCV_LEFT_MIRROR_STOP				{ NCV_OUT4OFF; NCV_OUT5OFF; NCV_OUT6OFF;}
#define NCV_LEFT_MIRROR_UP 				{ NCV_LEFT_MIRROR_STOP; NCV_OUT4LOW; NCV_OUT6HIGH; }
#define NCV_LEFT_MIRROR_DOWN			{ NCV_LEFT_MIRROR_STOP; NCV_OUT4HIGH; NCV_OUT6LOW; }	
#define NCV_LEFT_MIRROR_LEFT				{ NCV_LEFT_MIRROR_STOP; NCV_OUT5HIGH; NCV_OUT6LOW; }
#define NCV_LEFT_MIRROR_RIGHT			{ NCV_LEFT_MIRROR_STOP; NCV_OUT5LOW; NCV_OUT6HIGH; }	


#define NCV_DATA_SET_DEFAULT				{	(NCV_SRR = NCV_CHANNEL_ON);   	\
												(NCV_ULD = NCV_CHANNEL_ON);		\
												(NCV_OCD = NCV_CHANNEL_ON);		\
 												(NCV_OVLO = NCV_CHANNEL_ON);	\
 											}
#define SET_NCV_ULD			( NCV_ULD = 1 )
#define RESET_NCV_ULD		( NCV_ULD = 0 ) 
#define RESET_NCV_DEFAULT	{											\
								(NCV_ULD = NCV_CHANNEL_OFF);		\
								(NCV_OCD = NCV_CHANNEL_OFF);		\
 								(NCV_OVLO = NCV_CHANNEL_OFF);		\
 							}



extern TYPE_NCV7708Data 	_SPI1TxData;


#endif