/**
*****************************************************************************
** Communication lab - LocalSensorProcessing.c
** Sensor handling
*****************************************************************************
*/
#include <stdio.h>
#include "localsensorprocessing.h"
#include "bsp_thermometer.h"
#include "log.h"
#include "bsp_accelerometer.h"
#include "bsp_buttonsswitches.h"

void collectSensorData();
void SetLocalZoneStatus(unsigned int alarmType, unsigned char status);

/* ----------------- Public global variables ----------------- */

// Reference temperature (based on the first measurement after reset)
signed int referenceTemperature = 0;
// Last temperature reading
signed int currentTemperature = 0;
// Last MEMS value (is the tilt over the threshold?)
// Maximum angle of the 3 axes
signed int currentMaxTilt = 0;
// last value of the Test Switch
uint8_t TestSwitchState = 0;
// last value of the Virtual "Test Switch"
uint8_t virtualTestSwitchState = 0;

// Local Zone ID, set after reset based on the switches
uint8_t localZoneID = 0;

// State of all the zones
uint8_t zoneStatus[MAX_ZONE_NUM];
// Has any of the sensor reading changed?
//	if changed, update the display
uint8_t hasSensorDataChanged = 0;
// Has a value in zoneStatus array changed?
uint8_t hasAnyZoneStatusChanged = 0;
// Has the state of the local zone changed?
uint8_t hasLocalZoneStatusChanged = 0;

/* ----------------- Private global variables ----------------- */

// Sensor readings in the last iteration (previous values)
signed int prevTemp = 0;
signed int prevMaxTilt = 0;
uint8_t prevTestSwitchState = 0;

/* ----------------- Public functions ----------------- */

/** Sensor initialization. */
void LocalSensorProcessing_Init()
{
	Thermometer_Init();
	Accelerometer_Init();

	char buffer[100];
	// Set reference temperature at startup, the alarm will be based on this value
	// Get temperature data, set referenceTemperature
	referenceTemperature = Thermometer_GetTemperature();
	snprintf(buffer,100,"Temperature reference: %d\n\r",referenceTemperature);
	Log_LogString(buffer,LOGLEVEL_NORMAL);

	// Get local zone ID
	localZoneID = ButtonsSwitches_GetLocalZoneID();

}

/** Processing all local sensors, one iteration, called by the main loop*/
void LocalSensorProcessing_Go()
{
	// Refresh sensor readings
	collectSensorData();

	// Has any of the reading changed? If yes, LCD must be updated
	if ((currentTemperature != prevTemp) || (currentMaxTilt != prevMaxTilt) || (TestSwitchState != prevTestSwitchState))
	{
		hasSensorDataChanged=1;
	}
	prevTemp = currentTemperature;
	prevMaxTilt = currentMaxTilt;
	prevTestSwitchState = TestSwitchState;

	// Save zone state to previous
	uint8_t prevZoneStatus = zoneStatus[localZoneID];

	// Check for alerts
	SetLocalZoneStatus(ALARM_FIRE, currentTemperature >= referenceTemperature+2);
	SetLocalZoneStatus(ALARM_STEALTH, currentMaxTilt > 5);
	SetLocalZoneStatus(ALARM_TEST, TestSwitchState);
	SetLocalZoneStatus(ALARM_TEST_UART, virtualTestSwitchState);

	// if a status has changed, send over CAN network
	if (prevZoneStatus != zoneStatus[localZoneID])
	{
		hasLocalZoneStatusChanged=1;
		hasAnyZoneStatusChanged=1;
		// logging
		char buffer[100];
		sprintf(buffer,"Local zone (%u) state: %u\n\r",localZoneID, zoneStatus[localZoneID]);
		Log_LogString(buffer,LOGLEVEL_NORMAL);
	}
}

/** Change the state of the virtual "test switch" */
void ToggleVirtualTestSwitch()
{
	virtualTestSwitchState = virtualTestSwitchState ? 0 : 1;
}


/* ----------------- Private functions ----------------- */

/** Collect sensor readings and save to global variables. */
void collectSensorData()
{
	currentTemperature = Thermometer_GetTemperature();

	char buffer[100];
	snprintf(buffer,100,"Actual temperature: %u\n\r",currentTemperature);
	Log_LogString(buffer,LOGLEVEL_DETAILED);

	// Read MEMS data, update CurrentMaxTilt
	int8_t x,y,z;
	Accelerometer_GetTilt(&x, &y, &z);
	x = x>=0 ? x : -x;
	y = y>=0 ? y : -y;
	currentMaxTilt = x>y ? x : y;

	sprintf(buffer,"Actual tilt: %u\n\r",currentMaxTilt);
	Log_LogString(buffer,LOGLEVEL_DETAILED);

	TestSwitchState = ButtonsSwitches_GetTestSwitchState();
	sprintf(buffer,"Actual test switch state: %u\n\r", TestSwitchState);
	Log_LogString(buffer,LOGLEVEL_DETAILED);
}

/** Set local alarm states */
void SetLocalZoneStatus(unsigned int alarmType, unsigned char status)
{
	if (status)
	{
		zoneStatus[localZoneID] |= alarmType;
	}
	else
	{
		zoneStatus[localZoneID] &= ~alarmType;
	}
}

