#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "mcs12g_clock.h"
#include "mcs12g_timer.h"
#include "mcs12g_schedule.h"
#include "mcs12g_pwm.h"
#include "mcs12g_adc.h"
#include "mcs12g_sci.h"
#include "mcs12g_spi.h"

#include "device.h"
#include "deviceSci.h"

unsigned int gSystemCounter;

char fd_sci = -1;
unsigned char sciBufferRx[10];
unsigned char sciBufferTx[10];

void device_init_test(){
	device_register(&gMcs12gDeviceList, &gMcs12gDeviceSci);	
	fd_sci = device_open(&gMcs12gDeviceList, "deviceSci", 0);
}

void main(void) {
	/**/
	appl_clock_init();
	/**/
	appl_timer_init();
	/**/
	appl_schedule_init();
	/**
	appl_adc_init();
	/**
	appl_pwm_init();
	/**
	appl_sci_init();
	/**
	appl_spi_init();
	/**/	
	device_init_test();
	/**/
	
	EnableInterrupts;
	
	for(;;) {
		appl_schedule_update();
	} 
}


void task_1ms(){
	
}
void task_5ms(){
	
}
void task_10ms(){
	/**/
	appl_clock_update();
	/**/
	appl_timer_update();
	/**
	appl_adc_update();
	/**
	appl_pwm_update();
	/**/	
	appl_sci_update();
	/**
	appl_spi_update();
	/**/	
}
void task_20ms(){
	
}
void task_50ms(){
	
}
void task_100ms(){
	gSystemCounter++;
	device_read(&gMcs12gDeviceList, fd_sci,&sciBufferRx[0], 10); 	
}
void task_200ms(){
	
}

unsigned char x,y;
unsigned long result;

void task_1000ms(){
	//mcs12g_sci_txReq(&gMcs12gSciData);
	//mcs12g_sci_getRxData(&gMcs12gSciData);
	//mcs12g_spi_txRequest(&gMcs12gSpiData);
	//result = userPow(x,y);
	device_write(&gMcs12gDeviceList, fd_sci, &sciBufferTx[0], 2);
}

