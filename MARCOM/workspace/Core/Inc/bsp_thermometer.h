/**
*****************************************************************************
** Communication lab - thermometer.h
** Header for the I2C thermometer
*****************************************************************************
*/
#pragma once
#ifndef _THERMOMETER_H__
#define _THERMOMETER_H__

#include "stm32f4xx_hal.h"

HAL_StatusTypeDef Thermometer_Init();
uint8_t Thermometer_GetTemperature();

#endif
