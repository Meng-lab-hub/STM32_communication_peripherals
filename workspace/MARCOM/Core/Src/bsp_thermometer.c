/**
*****************************************************************************
** Communication lab - thermometer.c
** I2C thermometer functions, uses the services provided by i2c.h
*****************************************************************************
*/
#include "bsp_i2c.h"
#include "log.h"

/* ----------------- Private global variables  ----------------- */

const uint8_t TempAddr = (uint8_t)0x30;
const uint8_t TempConfReg = (uint8_t)0x08;
const uint8_t TempReg = (uint8_t)0x05;

/* ----------------- Public functions ----------------- */

/** Initialization. */
HAL_StatusTypeDef Thermometer_Init()
{
	HAL_StatusTypeDef result = I2C_Init();
	if (result != HAL_OK)
	{
		Log_LogStringAndHalStatus("Thermometer_Init(): I2C_Init() unsuccessful.", LOGLEVEL_NORMAL, result);
		return result;
	}

	// Init: write 00 to register 8
	uint8_t data = 0;
	result = I2C_WriteRegister(TempAddr, TempConfReg, &data, 1);
	if (result != HAL_OK)
	{
		Log_LogStringAndHalStatus("Thermometer_Init(): thermometer initialization unsuccessful.", LOGLEVEL_NORMAL, result);
		return result;
	}
	return HAL_OK;
}

/** I2C thermometer read actual temperature value */
uint8_t Thermometer_GetTemperature()
{
	uint8_t temperature = 0x00;

	uint8_t data[2];
	if (I2C_ReadRegister(TempAddr, TempReg, data, 2) != HAL_OK)
	{
		return 0xFF;
	}

	uint8_t UpperByte = data[0];
	uint8_t LowerByte = data[1];


	// Combine the values read to get celsius
	UpperByte = UpperByte & 0x1F;
	if ((UpperByte & 0x10) == 0x10){	// < 0°C
		UpperByte = UpperByte & 0x0F;
		temperature = 256 - (UpperByte*16+LowerByte/16);
	}else{	// > 0°C
		temperature = UpperByte*16+LowerByte/16;
	}
	return temperature;
}
