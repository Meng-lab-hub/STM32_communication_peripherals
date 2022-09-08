/**
*****************************************************************************
** Communication lab - log.c
** Log to UART
*****************************************************************************
*/
#include "stm32f4xx_hal.h"

#include <stdio.h>
#include "log.h"
#include "bsp_uart.h"
#include "bsp_globalfunctions.h"
#include "localsensorprocessing.h"

/* ----------------- Private global variables ----------------- */

unsigned int currentLogLevel = LOGLEVEL_NORMAL;
unsigned int repeatZoneDataEnabled = 0;
char logBuffer[] = "                                                                           ";


/* ----------------- Public functions ----------------- */

/** Initialize. */
void Log_Init()
{
	UART_Init();
}

/** Write string to the log. */
void Log_LogString(char *text, unsigned int logLevel)
{
	// If the log level is higher or equal, send over UART
	if (logLevel>=currentLogLevel)
	{
		UART_SendString(text);
	}
}

/** Write a string and HAL Status with a given log level */
void Log_LogStringAndHalStatus(char *text, unsigned int logLevel, HAL_StatusTypeDef status)
{
	char *statusString =
			(status==HAL_OK) ? "OK" :
			(status==HAL_ERROR ? "ERROR" :
			(status==HAL_BUSY ? "BUSY" :
			(status==HAL_TIMEOUT ? "TIMEOUT" : "UNKNOWN")));

	if (logLevel>=currentLogLevel)
	{
		char buffer[255];
		sprintf(buffer, "%s (%s)\n\r", text, statusString);
		UART_SendString(buffer);
	}
}

/** Regular display of detailed measurement data in the log */
void Log_RepeatZoneData()
{
	if (repeatZoneDataEnabled && repeated_log_delay == 0)
	{
		switch(localZoneID)
		{
		case 0:
			sprintf(logBuffer,">>> LocalZoneID: %u | Temp:%3d | Tilt: %2d | Zones: (%u) %u %u %u <<<\n\r",
					localZoneID, currentTemperature, currentMaxTilt,
					zoneStatus[0], zoneStatus[1], zoneStatus[2], zoneStatus[3]);
			break;
		case 1:
			sprintf(logBuffer,">>> LocalZoneID: %u | Temp:%3d | Tilt: %2d | Zones: %u (%u) %u %u <<<\n\r",
					localZoneID, currentTemperature, currentMaxTilt,
					zoneStatus[0], zoneStatus[1], zoneStatus[2], zoneStatus[3]);
			break;
		case 2:
			sprintf(logBuffer,">>> LocalZoneID: %u | Temp:%3d | Tilt: %2d | Zones: %u %u (%u) %u <<<\n\r",
					localZoneID, currentTemperature, currentMaxTilt,
					zoneStatus[0], zoneStatus[1], zoneStatus[2], zoneStatus[3]);
			break;
		case 3:
			sprintf(logBuffer,">>> LocalZoneID: %u | Temp:%3d | Tilt: %2d | Zones: %u %u %u (%u) <<<\n\r",
					localZoneID, currentTemperature, currentMaxTilt,
					zoneStatus[0], zoneStatus[1], zoneStatus[2], zoneStatus[3]);
			break;
		}
		Log_LogString(logBuffer, LOGLEVEL_NORMAL);

		// Reset "timer"
		repeated_log_delay = 500000;
	}
}
