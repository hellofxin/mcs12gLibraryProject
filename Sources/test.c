#include "mc9s12g96.h"
#include <hidef.h> 
#include "test.h"

TYPE_NCV7708Data 	_SPI1TxData;

unsigned int SPI_checkTxData(){
	if( NCV_OUTL4 && NCV_OUTH4 ){
		NCV_OUT4OFF;
	}
	else{
	}
	if( NCV_OUTL5 && NCV_OUTH5 ){
		NCV_OUT5OFF;
	}
	else{
	}
	if( NCV_OUTL6 && NCV_OUTH6 ){
		NCV_OUT6OFF;
	}
	else{
	}
	return 0;
}