#ifndef MCS12G_SCHEDULE_DATATYPE_H
#define MCS12G_SCHEDULE_DATATYPE_H

typedef void (*TaskFunctionDataType)();

typedef struct taskDataType{
	unsigned char mTaskFlag;
	TaskFunctionDataType mTaskFunction;
	unsigned long mTaskPeriod;	
	unsigned long mTaskExecutionCounter;	
}TaskDataType;

typedef struct mcs12gScheduleDataType{
	unsigned char mStatus;	
	unsigned long mScheduleCounter;
	TaskDataType *mTaskPointer;
	unsigned char mTaskNumber;
}Mcs12gScheduleDataType;


#endif