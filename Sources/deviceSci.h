#ifndef MCS12G_DEVICE_SCI_H
#define MCS12G_DEVICE_SCI_H

#include "device.h"

extern DeviceType gMcs12gDeviceSci;

char deviceSci_open(const char* path, unsigned char flag);
char deviceSci_read(unsigned char fd, void* buffer, unsigned char count);
char deviceSci_write(unsigned char fd, void* buffer, unsigned char count);
char deviceSci_close(unsigned char fd);

#endif


