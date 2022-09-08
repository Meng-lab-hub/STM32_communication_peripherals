/**
*****************************************************************************
** Communication lab - mainloop.h
** UART Communication
*****************************************************************************
*/
#pragma once
#ifndef _UART_H__
#define _UART_H__

/** Last byte received over UART */
extern uint8_t lastReceivedUartCommand;

void UART_Init();

void UART_SendString(const char* str);

#endif
