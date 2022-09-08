/**
*****************************************************************************
** Communication lab - localsensorprocessing.h
** Header for sensor processing
*****************************************************************************
*/
#pragma once
#ifndef _LOCALSENSORPROCESSING_H__
#define _LOCALSENSORPROCESSING_H__
#include "stm32f4xx.h"

// Last measured temperature
extern signed int currentTemperature;
// Last measured value of the MEMS accelerometer (is there a tilt above threshold?)
// Maximal value of the 3 axes
extern signed int currentMaxTilt;

// ID of the local zone. Is read from the switches after reset.
extern uint8_t localZoneID;

#define MAX_ZONE_NUM 4
extern uint8_t zoneStatus[MAX_ZONE_NUM];	// Status of all zones
extern uint8_t hasSensorDataChanged;		// Has any sensor value changed?
						// If yes, then LCD content has to be refreshed.
extern uint8_t hasAnyZoneStatusChanged;		// Has any value in the zoneStatus array changed?
extern uint8_t hasLocalZoneStatusChanged;	// Has the status of the local zone changed?

// Alarm status bits
#define ALARM_FIRE 1
#define ALARM_STEALTH 2
#define ALARM_TEST 4
#define ALARM_TEST_UART 8

void LocalSensorProcessing_Init();
void LocalSensorProcessing_Go();
void ToggleVirtualTestSwitch();

#endif
