#include "deviceSci.h"
#include "mcs12g_sci.h"


DeviceType gMcs12gDeviceSci = {
	 "deviceSci",
	deviceSci_open,
	deviceSci_read,
	deviceSci_write,
	deviceSci_close
};  ;

char deviceSci_open(const char* path, unsigned char flag){
	appl_sci_init();
	return 0;
}

char deviceSci_read(unsigned char fd, void* buffer, unsigned char count){
	mcs12g_sci_getRxData(&gMcs12gSciData, (unsigned char*)buffer, count);
	return 0;
}

char deviceSci_write(unsigned char fd, void* buffer, unsigned char count){
	mcs12g_sci_txReq(&gMcs12gSciData, (unsigned char*)buffer, count);
	return 0;		
}

char deviceSci_close(unsigned char fd){
			      	
}
