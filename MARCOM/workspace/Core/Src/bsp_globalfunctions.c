/**
*****************************************************************************
** Communication lab - globalfunctions.c
** Misc, common functions
*****************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "bsp_globalfunctions.h"
#include "tim.h"
#include "gpio.h"

/* ----------------- Public global variables ----------------- */
/* ----------------- Private local variables ----------------- */

// Timer decrements the value every microsecond if it is greater than 0
volatile int sys_delay = 0;
volatile unsigned long repeated_log_delay = 0;

/* ----------------- Public functions ----------------- */

/** Initialization of global functions */
void GlobalFunctions_Init(void)
{
	MX_GPIO_Init();
	MX_TIM4_Init();

	HAL_TIM_Base_Start_IT(&htim4);
}

/** Delay microseconds, blocked */
void Sys_DelayUs(int us)
{
	sys_delay = us;
	while(sys_delay);
}

/** Delay milliseconds, blocked */
void Sys_DelayMs(int ms)
{
	sys_delay = ms*1000;
	while(sys_delay);
}

/* ----------------- Interrupt handling and callback functions----------------- */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *handle)
{
	UNUSED(handle);

	if (sys_delay>0)
	{
		sys_delay--;
	}

	if (repeated_log_delay>0)
	{
		repeated_log_delay--;
	}
}
