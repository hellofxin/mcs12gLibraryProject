#ifndef MCS12G_SCHEDULE_H
#define MCS12G_SCHEDULE_H

#include "mcs12g_schedule_dataType.h"

#define ERROR_OK				0
#define ERROR_NOT_OK		1
#define MCS12G_SCHEDULE_TASK_NUMBER	5

extern Mcs12gScheduleDataType gMcs12gScheduleData;
extern TaskDataType gMcs12gScheduleTask[];

unsigned char appl_schedule_init();
unsigned char appl_schedule_update();
unsigned char appl_schedule_updateTaskFlag();

unsigned char mcs12g_schedule_init(Mcs12gScheduleDataType* this, TaskDataType* taskPointer, unsigned char taskNumber);
unsigned char mcs12g_schedule_update(Mcs12gScheduleDataType* this);
unsigned char mcs12g_schedule_updateTaskFlag(Mcs12gScheduleDataType* this);

void task_5ms();
void task_10ms();
void task_20ms();
void task_50ms();
void task_100ms();
void task_200ms();
void task_1000ms();

#endif