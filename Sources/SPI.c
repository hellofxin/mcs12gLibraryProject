#include "mc9s12g96.h"
#include <hidef.h> 
//#include "IO_G96.h"
#include "SPI.h"
//#include "errorCode.h"

TYPE_NCV7708Data 	_SPI1TxData;
unsigned int SPI1RxData = 0;
SPIDataBuffer 	SPI1TxDataBuffer;

/**
 * @brief initalizes SPI.
 * @param None.
 * @retval None.
 * @note f_SPI = f_bus/( (1+SPI1BR_SPPR)*2^(1+SPI1BR_SPR) );
 *		f_bus = 10MHz, SPI1BR_SPPR = 4,  SPI1BR_SPR = 0, f_SPI = 1000KHz;
/**/
void SPI_init(){
	SPI1CR1_SPE = 0;			//disable SPI;
	SPI1CR1_MSTR = 1;     	//set master mode;
	SPI1CR1_CPOL = 0;	   	//active high;
	SPI1CR1_CPHA = 1;    		//sample even;
	SPI1CR1_SSOE = 1;	 	//slave select output enable;
	SPI1CR1_LSBFE = 1;	  	//LSB  first enable;
	SPI1CR2_XFRW = 1;	 	//transfer width£»
	/** 
	 * when SS is used by SPI, CS is automatically controlled by SPI;
	 * if two driver chips are to be controlled by one SPI module, SS shouldn't be used by SPI;
	/**/
	SPI1CR2_MODFEN = 1; 	//SS port pin is used by SPI;
	SPI1CR2_BIDIROE = 0;   	//BIDIR output enable;
	SPI1CR2_SPISWAI = 0;
	SPI1CR2_SPC0 = 0;		//enables bidirectional pin configurations;
	SPI1BR_SPPR = 2;		  	//baud rate prescaler;
	SPI1BR_SPR = 2;		      	//baud rate;
	SPI1CR1_SPIE = 1;	     	//SPI RX, MODF interrupt enable;
	SPI1CR1_SPTIE = 0;     	//SPI transmit empty interrupt enable;
	SPI1CR1_SPE = 1;		   	//SPI enable;
	
	DDRT_DDRT7 = 1;
	PTT_PTT7  = 1;

	NCV_DATA_SET_DEFAULT;
}

#pragma CODE_SEG NON_BANKED
interrupt VectorNumber_Vspi1 void ISR_SPI1(){
	if( SPI1SR_SPIF ){
		//PIN_7708_CSB = 1;
		SPI1RxData = SPI1DR;
	}
	else if( SPI1SR_MODF ){
	}		
}
#pragma CODE_SEG DEFAULT

/**
 * @brief sends several bytes via SPI. 
 * @param _buffer: the address of the data to be sent.
 * @param _dataLength: the length of the data to be sent.
 * @retval ERROR_CODE, indicating status. 
/**/
unsigned int SPI_sendBytes(unsigned int _buffer[], unsigned char _dataLength){
	SPI1TxDataBuffer.pData = _buffer;     
	if( _dataLength <= 5 ){
		SPI1TxDataBuffer.dataLength = _dataLength;
		//RESET_ERROR_CODE_SPI_DATA_LENGTH;	
	}
	else{
		SPI1TxDataBuffer.dataLength = 0;
		//SET_ERROR_CODE_SPI_DATA_LENGTH;
	}
	while( SPI1TxDataBuffer.dataLength ){	  		
		while( !SPI1SR_SPTEF );
		DisableInterrupts;
		//PIN_7708_CSB = 0;
		SPI1DR = *SPI1TxDataBuffer.pData++;						     
		while( !SPI1SR_SPTEF );
		SPI1TxDataBuffer.dataLength--;	
		EnableInterrupts;								       
	}
	SPI1TxDataBuffer.pData = 0;
	return 0;	
}

/**
 * @brief check if the transmitted data is correct.
 * @param None.
 * @retval ERROR_CODE, indicating the status of the transmitted data.
/**/
unsigned int SPI_checkTxData(){
	if( NCV_OUTL4 && NCV_OUTH4 ){
		NCV_OUT4OFF;
		//SET_ERROR_CODE_NCV_OUT4_SHORT_CIRCUIT;
	}
	else{
		//RESET_ERROR_CODE_NCV_OUT4_SHORT_CIRCUIT;
	}
	if( NCV_OUTL5 && NCV_OUTH5 ){
		NCV_OUT5OFF;
		//SET_ERROR_CODE_NCV_OUT5_SHORT_CIRCUIT;
	}
	else{
		//RESET_ERROR_CODE_NCV_OUT5_SHORT_CIRCUIT;
	}
	if( NCV_OUTL6 && NCV_OUTH6 ){
		NCV_OUT6OFF;
		//SET_ERROR_CODE_NCV_OUT6_SHORT_CIRCUIT;
	}
	else{
		//RESET_ERROR_CODE_NCV_OUT6_SHORT_CIRCUIT;
	}
	return 0;
}

/**
 * @brief sends byte via SPI.
 * @param _pData: the address of the data to be sent.
 * @retval ERROR_CODE, indicating status.
/**/
unsigned int SPI_Tx(unsigned int *_pData){
	SPI_checkTxData();
	SPI_sendBytes(_pData, 1);
	return 0;
}

void spi_update(){
	SPI_Tx(&_SPI1TxData);	
}


/**/