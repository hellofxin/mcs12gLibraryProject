#ifndef MCS12G_DEVICE_H
#define MCS12G_DEVICE_H


#define DEVICE_NAME_LENGTH		10

typedef struct deviceType{
	char name[DEVICE_NAME_LENGTH];
	char (*open)(const char* path, unsigned char flag);
	char (*read)(unsigned char fd, void* buffer, unsigned char bufferSize);
	char (*write)(unsigned char fd, void* buffer, unsigned char bufferSize);
	char (*close)(unsigned char fd);
}DeviceType;

#define DEVICE_LIST_LENGTH		10

typedef struct deviceListType{
	DeviceType* mDeviceList[DEVICE_LIST_LENGTH];
	unsigned char mDeviceCounter;
	unsigned char mErrorCounter;
}DeviceListType;

extern DeviceListType gMcs12gDeviceList;

char device_register(DeviceListType* deviceList, DeviceType* device);
char device_unregister(DeviceListType* deviceList, DeviceType* device, unsigned char fd);
char device_open(DeviceListType* deviceList, const char* deviceName, unsigned char flag);
char device_read(DeviceListType* deviceList, unsigned char fd, void* buffer, unsigned char count);
char device_write(DeviceListType* deviceList, unsigned char fd, void* buffer, unsigned char count);
char device_close(DeviceListType* deviceList, unsigned char fd);

#endif
