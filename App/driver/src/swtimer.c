/*
 * swtimer.c
 *
 *  Created on: Nov 9, 2023
 *      Author: alren
 */

#include "swtimer.h"

#define SWTIMER_MAX_CH			8

typedef struct
{
	bool enable;
	SwtimerMode_t mode;
	uint32_t counter;
	uint32_t reload;
	void (*func)(void *arg);
	void *func_arg;
}swtime_t;

static uint8_t swtimer_count = 0;
static swtime_t swtime_tbl[SWTIMER_MAX_CH];

extern TIM_HandleTypeDef htim4;

bool swtimerInit(void)
{
	for(int i=0; i<SWTIMER_MAX_CH; i++)
	{
		swtime_tbl[i].enable = false;
		swtime_tbl[i].counter = 0;
		swtime_tbl[i].func = NULL;
		swtime_tbl[i].func_arg = NULL;
	}
	HAL_TIM_Base_Start_IT(&htim4);
	return true;
}

bool swtimerGetCh(uint8_t *p_ch)
{
	if(swtimer_count >= SWTIMER_MAX_CH)
	{
		return false;
	}

	*p_ch = swtimer_count;

	//if( swtime_tbl[swtimer_count].is_set == false)
	//{
		swtimer_count++;
	//}


	return true;
}

bool swtimerSet(uint8_t ch,
				void (*func)(void *arg),
				void *func_arg,
				SwtimerMode_t mode,
				uint32_t time_ms)

{
	if(ch >= SWTIMER_MAX_CH)
	{
		return false;
	}

	swtime_tbl[ch].func = func;
	swtime_tbl[ch].func_arg = func_arg;
	swtime_tbl[ch].mode = mode;
	swtime_tbl[ch].counter = 0;
	swtime_tbl[ch].reload = time_ms;
	swtime_tbl[ch].enable = false;

	return true;
}

bool swtimerStart(uint8_t ch)
{
	if(ch >= SWTIMER_MAX_CH)
	{
		return false;
	}
	swtime_tbl[ch].counter = 0;
	swtime_tbl[ch].enable = true;

	return true;
}

bool swtimerStop(uint8_t ch)
{
	if(ch >= SWTIMER_MAX_CH)
	{
		return false;
	}

	swtime_tbl[ch].enable = false;

	return true;
}

void swtimerISR(void)
{
	for(int i=0; i<swtimer_count; i++)
	{
		if(swtime_tbl[i].enable == true)
		{
			swtime_tbl[i].counter++;
			if(swtime_tbl[i].counter >= swtime_tbl[i].reload)
			{
				if(swtime_tbl[i].func != NULL)
				{
					swtime_tbl[i].func(swtime_tbl[i].func_arg);
				}
				swtime_tbl[i].counter = 0;
				if(swtime_tbl[i].mode == SWTIMER_ONETIME)
				{
					swtime_tbl[i].enable = false;
				}
			}
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *him)
{
	if(him == &htim4)
	{
		swtimerISR();
	}

}


