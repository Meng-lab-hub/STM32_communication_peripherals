#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

#include "bsp_buttonsswitches.h"

/* ----------------- Private global variables ----------------- */

#define 	BUTTON_BTN1	(uint16_t)1<<12
#define 	BUTTON_BTN2	(uint16_t)1<<13
#define 	BUTTON_BTN3	(uint16_t)1<<14
#define 	BUTTON_BTN4	(uint16_t)1<<15

#define 	BUTTON_ALL	(uint16_t)0xf000

/* ----------------- Public functions ------------------------ */

void ButtonsSwitches_Init()
{
	__GPIOE_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	// Configure switch inputs
	GPIO_InitTypeDef portInit;
	portInit.Mode = GPIO_MODE_INPUT;
	portInit.Pull = GPIO_NOPULL;
	portInit.Speed = GPIO_SPEED_FAST;
	portInit.Pin = GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOE, &portInit);

	// SWEN output
	portInit.Mode = GPIO_MODE_OUTPUT_PP;
	portInit.Pull = GPIO_NOPULL;
	portInit.Speed = GPIO_SPEED_FAST;
	portInit.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &portInit);

	// Enable switch inputs
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6, GPIO_PIN_SET);
}

/** Read SW3 state */
int ButtonsSwitches_GetTestSwitchState()
{
	return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
}

/** Read SW4 state */
int ButtonsSwitches_GetGraphicsModeSwitchState()
{
	return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);
}

/** Read SW1 and SW2 state*/
uint8_t ButtonsSwitches_GetLocalZoneID()
{
	// Read the switches: SW1: PE2, SW2: PE4
	uint8_t localZoneIDpin0 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
	uint8_t localZoneIDpin1 = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);

	uint8_t localZoneID = localZoneIDpin0 + (localZoneIDpin1<<1);

	return localZoneID;
}
