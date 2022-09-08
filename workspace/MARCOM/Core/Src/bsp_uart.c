/** TODO: Task 1 - UART
 *
 * The main purpose of the functions here is to offer implementation for the logging functions
 * in log.c and also allow mainloop.c to receive bytes one by one.
 *
 * In order to initialize the module, the GPIO pins (alternate function, push-pull etc.)
 * and the UART peripheral (baud rate, stop bits etc.) must be initialized.
 * To do this, we use the graphical configurator in the MARCOM.ioc file and
 * call the generated initialization function here in the UART_Init() function.
 *
 * The string sending has to be implemented in UART_SendString() function.
 * We use non-blocking, interrupt-based transfer method in order not to block the rest of the system.
 *
 * After implementing these functions, take a look at the UART frame using the oscilloscope (PD8 pin).
 * Put a screenshot in the report where the beginning and the end of the frame is visible.
 * Try to decode the meaning of each bit and the transmitted byte.
 * Measure the baud rate with the cursor function of the oscilloscope.
 * Please pay extra attention not to short circuit any of the pins!
 * Use the RS-232 connector’s screw as the ground point.
 *
 *
 * TODO: Task 2 - UART reception (part 1)
 *
 * This task is about receiving data from UART because the previous task only contains transmission.
 * UART receive is implemented using interrupts.
 * HAL library provides a uniform structure for handling interrupts. Most of the interrupt handling
 * is implemented in HAL which provides callbacks for the user code that actually deals with the
 * business logic.
 *
 * First the interrupt event forces the microcontroller to save its state and jump to the
 * address corresponding the event source in the interrupt vector table. The address is read
 * from here, written to the PC. This address contains the native interrupt handler
 * (such as USART3_IRQHandler() ) which is independent from HAL.
 * In order to utilize HAL, the programmer must call the HAL interrupt handler to take care of
 * the interrupt (HAL_UART_IRQHandler(&huart3); ). This is done automatically by the generated
 * code in stm32f4xx_it.c.
 * The interrupt handler function of HAL will call back to a user implemented function
 * depending on the situation. If a complete receive transaction finished, it calls the
 * HAL_UART_RxCpltCallback() function.
 * In this task bytes are received one by one. The received byte is saved to
 * lastReceivedUartCommand global variable, which is monitored and handled by mainloop.c.
 * For this reason the second part of this task is implemented in mainloop.c.
 *
 */
 
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "string.h"
#include "bsp_globalfunctions.h"
#include "usart.h"

 /* ----------------- Public global variables ----------------- */

/** Last received command. 0 if none. */
uint8_t lastReceivedUartCommand = 0;

/* ----------------- Private global variables ----------------- */

// Receive buffer for one byte
char rxBuffer;
// Stores the string to be sent, copy here before sending. Used by  UART_SendString() 
#define TXBUFFERSIZE 255
char txBuffer[TXBUFFERSIZE];

/* ----------------- Public functions ----------------- */

/** Initialization */
HAL_StatusTypeDef UART_Init()
{
	// TODO: Task 1 - UART
	// Set up the UART periphery using the GUI by opening MARCOM.ioc file. Use the following settings:
	//  - Instance: USART3
	//  - Asynchronous mode
	//  - No hardware flow control
	//  - TX line: PD8, RX line: PD9
	//  - 115200 bit/s
	//  - 8N1 mode (such as 8 data bits, No parity and 1 stop bit)
	//  - Enable both sending and receiving
	//  - Oversampling: 16
	//  - Enable USART3 global interrupt at the NVIC settings
	// After successful code generation, include the header "usart.h" and call the generated
	// initializer function. Later USART3 periphery can be accessed by the huart3 periphery handle variable. See usart.h

	MX_UART4_Init();
	HAL_UART_MspInit(&huart4);
	HAL_UART_MspDeInit(&huart4);

	// TODO: Task 2 - UART reception (part 1)
	// Enable reception here! To do that, start the reception of one byte, 
	// and store it to rxBuffer. 
	// Use non-blocking mode by calling HAL_UART_Receive_IT().
	// The type of the second argument of HAL_UART_Receive_IT() must be (uint8_t*) 
	// so cast rxBuffer to this type.



	return HAL_OK;
}

/** Send a string, non-blocking */
HAL_StatusTypeDef UART_SendString(char *str)
{
	// TODO: Task 1 - UART
	// Wait until UART is ready to send:
	// We can send only if huart3.gState is either HAL_UART_STATE_READY or 
	// HAL_UART_STATE_BUSY_RX (which means that only reception can be in progress).
	// (This waiting makes our function blocking if a transmission is already happening
	// however we accept that otherwise a queue should be created and we don't want to 
	// complicate it further.)


	// Here UART is ready to send.
	// Send the contents of the str argument over UART, non-blocking using HAL_UART_Transmit_IT()
	// Warning: the contents pointed by str might change till or during transmission.
	// Thus copy the string to txBuffer! Use strncpy() and only maximum TXBUFFERSIZE length!
	// The type of the second argument of HAL_UART_Transmit_IT() must be (uint8_t*) 
	// so cast txBuffer to this type!



	return HAL_OK;
}


/* ----------------- Interrupt handler and callback functions  ----------------- */

// TODO: Task 2 - UART reception (part 1)
// Uncomment the definition of the function HAL_UART_RxCpltCallback()

/** Callback function, called after a successful reception */
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *handle)
{
	// TODO: Task 2 - UART reception (part 1)
	// Received data is in the rxBuffer variable (as specified by the call of HAL_UART_Receive_IT()).

	// Save the last received byte to the global lastReceivedUartCommand variable.
	// Call HAL_UART_Receive_IT() again to start a new reception. If this is not called, 
	// no more bytes are received


}
*/
