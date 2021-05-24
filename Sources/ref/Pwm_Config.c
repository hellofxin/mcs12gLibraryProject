/*
 * Pwm_Config.c
 *
 *  Created on: 2021Äê5ÔÂ18ÈÕ
 *      Author: hexingliang
 */
#include "Pwm.h"

Pwm_ChannelType PwmChl[] =
{
	{0,IfxPort_P15_6},		//Channel 0
	{1,IfxPort_P15_7},		//Channel 1
	{2,IfxPort_P15_8},		//Channel 2
};

Pwm_ConfigType config[] =
{
		3,	/*  */
		{
			0,
			100,
			10,
			0
		}
};
