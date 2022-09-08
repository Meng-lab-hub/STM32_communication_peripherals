/**
*****************************************************************************
** Communication lab - bsp_accelerometer.h
** Accelerometer interface
*****************************************************************************
*/
#pragma once
#ifndef _ACCELEROMETER_H__
#define _ACCELEROMETER_H__

/** Initialization of the accelerometer */
void Accelerometer_Init();

/** Provides the actual acceleration vector. Zero return value indicates success. */
int Accelerometer_GetTilt(int8_t *Xg, int8_t *Yg, int8_t *Zg);

#endif
