#include "device.h"

DeviceListType gMcs12gDeviceList;

char device_register(DeviceListType* deviceList, DeviceType* device){
	if( !deviceList || !device ){
		return -1;
	}
	deviceList->mDeviceList[deviceList->mDeviceCounter++] = device;
	return 0;
}

char device_unregister(DeviceListType* deviceList, DeviceType* device, unsigned char fd){
	if( !deviceList || !device ){
		return -1;
	}
	if( deviceList->mDeviceList[fd]==device ){
		deviceList->mDeviceList[fd] = 0;
		if(deviceList->mDeviceCounter){
			deviceList->mDeviceCounter--;
		}
	}
	return 0;
}

char device_find(DeviceListType* deviceList, const char* deviceName, unsigned char flag){
	unsigned char i = 0;
	if( !deviceList || !deviceName ){
		return -1;
	}
	for(i=0; i<deviceList->mDeviceCounter; i++){
		if( strcmp(deviceList->mDeviceList[i]->name, deviceName)==0 ){
			return i;
		}
	}
	return -2;
}

char device_open(DeviceListType* deviceList, const char* deviceName, unsigned char flag){
	char fd = -1;
	char status = 0;
	if( !deviceList || !deviceName ){
		return -1;
	}
	fd = device_find(deviceList, deviceName, flag);
	if( fd<0 ){
		return -2;
	}
	if( deviceList->mDeviceList[fd]->open ){
		status = deviceList->mDeviceList[fd]->open(deviceName, flag);
	}
	if( 0!=status){
		deviceList->mErrorCounter++;
		return status;
	}
	return fd;
}

char device_read(DeviceListType* deviceList, unsigned char fd, void* buffer, unsigned char count){
	unsigned char status = 0;
	if( !deviceList || !buffer ){
		return -1;
	}
	if( 0!=deviceList->mDeviceList[fd] ){
		status = deviceList->mDeviceList[fd]->read(fd, buffer, count);
	}
	if( 0!=status ){
		deviceList->mErrorCounter++;
	}
	return status;
}

char device_write(DeviceListType* deviceList, unsigned char fd, void* buffer, unsigned char count){
	unsigned char status = 0;
	if( !deviceList || !buffer ){
		return -1;
	}
	if( 0!=deviceList->mDeviceList[fd] ){
		status = deviceList->mDeviceList[fd]->write(fd, buffer, count);
	}
	if( 0!=status ){
		deviceList->mErrorCounter++;
	}
	return status;
}

char device_close(DeviceListType* deviceList, unsigned char fd){
	unsigned char status = 0;
	if( !deviceList ){
		return -1;
	}
	if( deviceList->mDeviceList[fd] ){
		status = deviceList->mDeviceList[fd]->close(fd);
	}
	if( 0!=status ){
		deviceList->mErrorCounter++;
	}
	return status;
}
