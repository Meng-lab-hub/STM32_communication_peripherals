/**
*****************************************************************************
** Communication - graphics.h
** Graphics display
*****************************************************************************
*/
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

#include <stdio.h>
#include "bsp_buttonsswitches.h"
#include "Log.h"
#include "bsp_glcd.h"
#include "zonemap.h"
#include "localsensorprocessing.h"

void ShowDrawingGraphics();
void ShowDetailedGraphics();

/* ----------------- Private global variables ----------------- */

// Allocated for text messages
char buffer[] = "                        ";

// Has the graphics mode changed between text or floorplan? (since the last iteration)
unsigned char hasGraphicsModeChanged = 1;

// Graphics mode in the last iteration. If it has changed, redraw is required
uint8_t prevGraphicsMode = 0xFF;	// It has changed by default to force a redraw

/* ----------------- Public functions ----------------- */

/** Init graphics display. */
void Graphics_Init()
{
	GLCD_Init();
}

/** Loop for the graphics activities, called by the main loop */
void Graphics_Go()
{
	// Get actual display mode (details or graphics)
	uint8_t graphicsMode = ButtonsSwitches_GetGraphicsModeSwitchState();

	if (graphicsMode != prevGraphicsMode)
	{
		// Must redraw
		hasGraphicsModeChanged = 1;
		prevGraphicsMode = graphicsMode;
		// Log
		Log_LogString("GRH: Mode has changed.\n\r",LOGLEVEL_NORMAL);
	}

	if (graphicsMode)
	{
		ShowDetailedGraphics();
	}
	else
	{
		ShowDrawingGraphics();
	}

	hasGraphicsModeChanged = 0;
}

/* ----------------- Private functions ----------------- */

/** Draw floorplan. */
void Send_BackgroundImage()
{
	int i,j,k=0;
	for (i=0;i<8;i++){
		for(j=0;j<128;j++){
			GLCD_Write_Block(zoneMap[k],i,j);
			k++;
		}
	}
}

/** Draw details screen. */
void ShowDetailedGraphics()
{
	// Redraw only if needed...
	if (hasAnyZoneStatusChanged || hasSensorDataChanged || hasGraphicsModeChanged)
	{
		if (hasGraphicsModeChanged)
		{
			GLCD_Clear();
			GLCD_WriteString("Comm lab - BME AUT",0,0);

			sprintf(buffer,"LocalZoneID:%u",localZoneID);
			GLCD_WriteString(buffer,3,2);

			sprintf(buffer,"Temp:%d",currentTemperature);
			GLCD_WriteString(buffer,3,3);

			sprintf(buffer,"Tilt:%d",currentMaxTilt);
			GLCD_WriteString(buffer,3,4);

			sprintf(buffer,"Zones:%u %u %u %u",
					zoneStatus[0],zoneStatus[1],zoneStatus[2],zoneStatus[3]);
			GLCD_WriteString(buffer,3,5);

			// Log
			Log_LogString("GRH: Redraw (details)\n\r",LOGLEVEL_DETAILED);
		}
		else
		{
			sprintf(buffer,"%u   ",localZoneID);
			GLCD_WriteString(buffer,3+12*6,2);

			sprintf(buffer,"%d   ",currentTemperature);
			GLCD_WriteString(buffer,3+5*6,3);

			sprintf(buffer,"%d   ",currentMaxTilt);
			GLCD_WriteString(buffer,3+5*6,4);

			sprintf(buffer,"%u %u %u %u     ",
					zoneStatus[0],zoneStatus[1],zoneStatus[2],zoneStatus[3]);
			GLCD_WriteString(buffer,3+6*6,5);
		}
	}
}

/** Draw floorplan screen, if needed. */
void ShowDrawingGraphics()
{
	unsigned char zoneBaseCol[] = {5, 34, 70, 85};
	unsigned char zoneBaseRow[] = {5, 2, 2, 5};
	int zoneID = 0;
	char zoneString[5];	// enough memory for 4 chars + closing 0
	if (hasGraphicsModeChanged)
	{
		GLCD_Clear();
		Send_BackgroundImage();
		Log_LogString("GRH: Zonemap redrawn\n\r",LOGLEVEL_DETAILED);
	}
	if (hasAnyZoneStatusChanged || hasGraphicsModeChanged)
	{
		for(zoneID=0; zoneID<4; zoneID++)
		{
			zoneString[0] = (zoneStatus[zoneID] & ALARM_FIRE) ? 98+32 : ' ';	// 98: fire char
			zoneString[1] = (zoneStatus[zoneID] & ALARM_STEALTH) ? 99+32 : ' ';	// 99: person char
			zoneString[2] = (zoneStatus[zoneID] & ALARM_TEST) ? 'T' : ' ';	// 99: T char
			zoneString[3] = (zoneStatus[zoneID] & ALARM_TEST_UART) ? 'V' : ' ';	// 99: V char
			zoneString[4] = 0;
			GLCD_WriteString(zoneString,zoneBaseCol[zoneID],zoneBaseRow[zoneID]);
		}
		Log_LogString("GRH: Redrawn (drawing)\n\r",LOGLEVEL_DETAILED);
	}
}
