/**
*****************************************************************************
** Communication lab - log.h
** Header for logging to the UART
*****************************************************************************
*/
#pragma once
#ifndef _LOG_H__
#define _LOG_H__
#include "stm32f4xx.h"

#define LOGLEVEL_NORMAL		2
#define LOGLEVEL_DETAILED	1

#define REPEAT_ON	1
#define REPEAT_OFF	0

extern unsigned int currentLogLevel;
extern unsigned int repeatZoneDataEnabled;

void Log_Init();
void Log_LogString(char *text, unsigned int logLevel);
void Log_LogStringAndHalStatus(char *text, unsigned int logLevel, HAL_StatusTypeDef status);
void Log_RepeatZoneData();

#endif
