#include "mcs12g_schedule.h"

TaskDataType gMcs12gScheduleTask[MCS12G_SCHEDULE_TASK_NUMBER] = { 
	{ 0, task_5ms, 5, 0 },
	{ 0, task_10ms, 10, 0 },
	{ 0, task_20ms, 20, 0 },
	{ 0, task_100ms, 100, 0 },
	{ 0, task_1000ms, 1000, 0 }
};

Mcs12gScheduleDataType gMcs12gScheduleData;


unsigned char mcs12g_schedule_init(Mcs12gScheduleDataType* this, TaskDataType* taskPointer, unsigned char taskNumber){
	unsigned char i = 0;
	if( !this || !taskPointer || !taskNumber ){
		return ERROR_NOT_OK;	
	}
	this->mStatus = 0;
	this->mTaskNumber = taskNumber;
	this->mTaskPointer = taskPointer;
	for( i=0; i<this->mTaskNumber; i++ ){
		this->mTaskPointer[i].mTaskFlag = 0;
		this->mTaskPointer[i].mTaskExecutionCounter = 0;
	}
	return ERROR_OK;
}

unsigned char mcs12g_schedule_update(Mcs12gScheduleDataType* this){
	unsigned char i =0;
	if( !this ){
		return ERROR_NOT_OK;
	}
	for( i=0; i<this->mTaskNumber; i++ ){
		if( this->mTaskPointer[i].mTaskFlag ){
			this->mTaskPointer[i].mTaskFlag = 0;	
			if( this->mTaskPointer[i].mTaskFunction ){
				this->mTaskPointer[i].mTaskFunction(); 
				this->mTaskPointer[i].mTaskExecutionCounter++;
			}
		}
	}
	return ERROR_OK;
}

unsigned char mcs12g_schedule_updateTaskFlag(Mcs12gScheduleDataType* this){
	unsigned char i = 0;
	if( !this ){
		return ERROR_NOT_OK;
	}
	this->mScheduleCounter++;
	for( i=0; i<this->mTaskNumber; i++ ){
		if( 0 == this->mScheduleCounter % this->mTaskPointer[i].mTaskPeriod ){
			this->mTaskPointer[i].mTaskFlag = 1;	
		}
	}
    	return ERROR_OK;
}


unsigned char appl_schedule_init(){
	return mcs12g_schedule_init(&gMcs12gScheduleData, &gMcs12gScheduleTask[0], MCS12G_SCHEDULE_TASK_NUMBER); 	
}
unsigned char appl_schedule_update(){
	return mcs12g_schedule_update(&gMcs12gScheduleData);	
}
unsigned char appl_schedule_updateTaskFlag(){
	return mcs12g_schedule_updateTaskFlag(&gMcs12gScheduleData);	
}

