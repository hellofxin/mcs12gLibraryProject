#include "schedule.h"
#include "timer_G96.h"


/**
* @brief scheduler, calling tasks periodically.
* @param None.
* @retval None.
* @note
/**/
void schedule(){
	if( timerFlag_1ms ){
		timerFlag_1ms = 0;
		task_1ms();
	}
	if( timerFlag_5ms ){
		timerFlag_5ms = 0;
		task_5ms();
	}
	if( timerFlag_10ms ){
		timerFlag_10ms = 0;
		task_10ms();
	}
	if( timerFlag_20ms ){
		timerFlag_20ms = 0;
		task_20ms();
	}
	if( timerFlag_50ms ){
		timerFlag_50ms = 0;
		task_50ms();
	}
	if( timerFlag_100ms ){
		timerFlag_100ms = 0;
		task_100ms();
	}
	if( timerFlag_200ms ){
		timerFlag_200ms = 0;
		task_200ms();
	}
	if( timerFlag_1000ms ){
		timerFlag_1000ms = 0;
		task_1000ms();
	}
}