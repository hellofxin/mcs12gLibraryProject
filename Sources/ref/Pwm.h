/*
 * Pwm.h
 *
 *  Created on: 2021年5月13日
 *      Author: hexingliang
 */
//#include"Platform_Types.h"
#ifndef PWM_H_
#define PWM_H_

#define E_OK		(0)
#define	E_NOT_OK	(1)


typedef struct PwmChl_tag
{
	uint8 Chl;
	IfxPort_Pin Pin;
	uint8 Range;		//代表PWM频率范围0:0-1K   1:1K-10K
}Pwm_ChannelType;

typedef struct PwmCfg_tag
{
	uint8					ChannelCount;
	struct{
		Pwm_ChannelType 	Channel;	//0-255
		uint32 				FreqCnt;				//Count计数值 1-1000 1000-65535
		uint32				DutyCnt;				//Count计数值
		uint8   			ActLev;					//0-1
	}* Chl;
}Pwm_ConfigType;


extern void Pwm_Init(Pwm_ConfigType* cfg);
extern uint8 Pwm_SetPeriodAndDuty(uint8 Chl,uint32 Freq,uint32 Duty);


#endif /* PWM_H_ */
