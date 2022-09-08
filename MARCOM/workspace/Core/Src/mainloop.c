/**
*****************************************************************************
** Communication lab - mainloop.c
** Main loop
*****************************************************************************
* TODO: Task 2 - UART reception (part 2)
* Process incoming UART command bytes, implement a switch-case for the commands in MainLoop_Go()
* the rest of the task is in bsp_uart.c, where the reception should be implemented 
*/

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include <stdio.h>
#include "bsp_globalfunctions.h"
#include "log.h"
#include "localsensorprocessing.h"
#include "graphics.h"
#include "bsp_buttonsswitches.h"
#include "bsp_uart.h"
#include "bsp_can.h"

/** Initialization, all subsystems are initialized */
void MainLoop_Init()
{
	GlobalFunctions_Init();
	Log_Init();
	LocalSensorProcessing_Init();
	ButtonsSwitches_Init();
	Graphics_Init();
	CAN_Init();

	Log_LogString("***********************\n\r",LOGLEVEL_NORMAL);
	Log_LogString("*  Communication lab  *\n\r",LOGLEVEL_NORMAL);
	Log_LogString("*       BME AUT       *\n\r",LOGLEVEL_NORMAL);
	Log_LogString("***********************\n\r\n\r",LOGLEVEL_NORMAL);

	localZoneID = ButtonsSwitches_GetLocalZoneID();

	char buffer[100];
	snprintf(buffer,100,"Local Zone ID: %u\n\r",localZoneID);
	Log_LogString(buffer,LOGLEVEL_NORMAL);

	// Show everything at startup
	hasAnyZoneStatusChanged = 1;
	hasLocalZoneStatusChanged = 1;
	hasSensorDataChanged = 1;
}

/** One iteration of the infinite main loop */
void MainLoop_Go()
{
	Log_LogString("MAINLOOP: Main cycle - next iteration\n\r",LOGLEVEL_DETAILED);

	// Handle sensors
	LocalSensorProcessing_Go();
	// handle CAN communication
	CAN_Go();
	// Update graphics LCD (if needed)
	Graphics_Go();
	// Regular display of detailed measurement data in the log
	Log_RepeatZoneData();

	// TODO: Task 2 - UART reception (part 2)
	// Handle incoming UART bytes
	// In case the value of lastReceivedUartCommand variable (defined in bsp_uart.c) is not 0,
	// New byte was received, it must be handled. Use a switch to handle the received byte, finally set the value back to 0.
	// Defined commands:
	// - 'g': Greeting. Use Log_LogString to send a greeting message.
	// - 'n': Normal log level: set the value of the global variable currentLogLevel to LOGLEVEL_NORMAL
	// - 'd': Detailed log level: Set the log level to DETAILED
	// - 'q': Query log level: Send the actual log level to the Log.
	// - 'v': Virtual test switch: Call the function ToggleVirtualTestSwitch() (defined in localsensorprocessing.c)
	//         to send a test alarm over UART.
	// - 'r': Repeat mode: Toggle the value of the global variable repeatZoneDataEnabled (defined in log.c)
	//        From 0 to 1 or from 1 to 0. If the value is not 0, the current measured values are periodically sent over UART.
	// - Unknown character: Send an error message.

	if (lastReceivedUartCommand!=0)
	{
		switch (lastReceivedUartCommand)
		{
		case 'g':	// Greeting
			Log_LogString("Hello!\n\r",LOGLEVEL_NORMAL);
			break;
		case 'n':	// Normal log level
			currentLogLevel = LOGLEVEL_NORMAL;
			Log_LogString("Log level: NORMAL\n\r",LOGLEVEL_NORMAL);
			break;
		case 'd':	// Detailed log level
			currentLogLevel = LOGLEVEL_DETAILED;
			Log_LogString("Log level: DETAILED\n\r",LOGLEVEL_NORMAL);
			break;
		case 'q':	// Query log level
			if (currentLogLevel == LOGLEVEL_DETAILED)
			{
				Log_LogString("Log level: DETAILED\n\r",LOGLEVEL_NORMAL);
			}
			else
			{
				Log_LogString("Log level: NORMAL\n\r",LOGLEVEL_NORMAL);
			}
			break;
		case 'v': // Virtual "test switch" message
			ToggleVirtualTestSwitch();
			break;
		case 'r': // Toggle repeat mode: send detailed zone data to log repeatedly or not
			if (repeatZoneDataEnabled == REPEAT_ON)
			{
				repeatZoneDataEnabled = REPEAT_OFF;
				Log_LogString("Repeat mode OFF\n\r",LOGLEVEL_NORMAL);
			}
			else
			{
				repeatZoneDataEnabled = REPEAT_ON;
				Log_LogString("Repeat mode ON\n\r",LOGLEVEL_NORMAL);
			}
			break;
		default:
			Log_LogString("Unknown command!\n\r",LOGLEVEL_NORMAL);
			break;
		}
		lastReceivedUartCommand=0;
	}
	
	// Clearing the flags indicating changes
	hasAnyZoneStatusChanged = 0;
	hasLocalZoneStatusChanged = 0;
	hasSensorDataChanged = 0;
}
