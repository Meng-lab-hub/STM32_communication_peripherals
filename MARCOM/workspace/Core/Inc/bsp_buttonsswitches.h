/**
*****************************************************************************
** Communication lab - buttonsswitches.h
** Handling buttons and switches
*****************************************************************************
*/
#pragma once
#ifndef _BUTTONSSWITCHES_H__
#define _BUTTONSSWITCHES_H__
#include "stm32f4xx.h"

void ButtonsSwitches_Init();

int ButtonsSwitches_GetTestSwitchState();

int ButtonsSwitches_GetGraphicsModeSwitchState();

uint8_t ButtonsSwitches_GetLocalZoneID();

#endif
