/** TODO: Task 5 - CAN
 * CAN communication has to be implemented in this source file.
 *
 * The initialization of the CAN peripheral is similar to the others: GPIO
 * pins and the embedded CAN module must be initialized.
 * Use the configurator by opening MARCOM.ioc, and call the generated initializer
 * function from CAN_Init().
 * This is complemented by setting up a CAN message filter. This filter describes
 * which messages the peripheral listens to or ignores. As CAN uses message
 * identifiers instead of device addressing, each device can filter which
 * messages are relevant or not.
 *
 * For transmitting and receiving messages, use CAN_TxHeaderTypeDef and
 * CAN_RxHeaderTypeDef type structures (global variables txHeader and rxHeader
 * are already defined), as well as byte arrays to store the data payload of messages
 * before sending and after receiving them (global arrays txBuffer and rxBuffer).
 * In order to send, the fields of the header structure must be filled, and data copied
 * to the buffer, then pass them to an outgoing mailbox handled by the HAL library.
 * Receiving a message results in calling a callback function where we can process
 * the received data.
 *
 * Both sending and receiving is implemented using interrupts, in order not
 * to block other functions and maximize performance and efficiency.
 * The HAL driver hides the handling of interrupts from us, so it is enough to
 * just pass the completed message to the outgoing mailbox and process the received
 * message in the callback function.
 */
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

#include <stdio.h>
#include "log.h"
#include "localsensorprocessing.h"
#include "bsp_globalfunctions.h"

/* ----------------- Private, global variables ------------------- */

// TODO: Task 5 - CAN
// Uncomment the following variable declarations!

// Global variables to store transmitted and received messages
/*
CAN_TxHeaderTypeDef txHeader;
uint8_t txBuffer[8];
CAN_RxHeaderTypeDef rxHeader;
uint8_t rxBuffer[8];
*/

/* ----------------- Public functions ------------------------ */

/** Initialization of CAN peripheral */
HAL_StatusTypeDef CAN_Init()
{
	// TODO: Task 5 - CAN
	// Set up the CAN periphery using the GUI by opening the MARCOM.ioc file.
	// Use the following settings:
	// - Instance: CAN1
	// - Prescaler: 4
	// - First bit segment is 6 quanta, second is 8 quanta
	// - ReSynchronization Jump Width: 1 quantum
	// - TX line: PD1, RX line: PD0
	// - Enable CAN1 TX and CAN1 RX0 interrupts at the NVIC settings
	//   Also set the following priorities:
	//   - CAN1 TX:  Preemption Priority 0, Sub Priority 2
	//   - CAN1 RX0: Preemption Priority 0, Sub Priority 1
	// After generating the source, include the generated "can.h" file and call the
	// initialization function in it. Later the CAN periphery instance can be accessed by the
	// hcan1 handle variable. See the contents of can.h



	// Next the message filter has to be set. In our case this enables the
	// reception of incoming messages on FIFO0. This can be done by filling a
	// struct variable of type CAN_FilterTypeDef and calling HAL_CAN_ConfigFilter()
	// Note that the address of the filter descriptor has to be passed!
	// Set FilterBank and SlaveStartFilterBank to 0 (no constants for these.
	// Set filter to be active (ENABLE)
	// Use FIFO0 (CAN_FILTER_FIFO0)
	// We are going to filter based on the message ID: (CAN_FILTERMODE_IDMASK), CAN_FILTERSCALE_32BIT
	// All of IdLow, IdHigh, MaskIdLow, MaskIdHigh values are 0.
	// Check the return value for success. If the setting was unsuccessful,
	// return the error code and log it using the function: Log_LogStringAndHalStatus()



	// After successful configuration, start the CAN periphery using function HAL_CAN_Start()
	// Allow the "message pending" interrupt for FIFO0 using the function HAL_CAN_ActivateNotification()


	// Finally print to the Log whether CAN_Init was successful.

	return HAL_OK;
}

/** Sending a CAN message */
HAL_StatusTypeDef CAN_SendMessage(uint8_t zoneID, uint8_t newStatus)
{
	// TODO: Task 5 - CAN
	// First check whether the CAN periphery is ready to send:
	// Ready if the value of hcan1.State is HAL_CAN_STATE_READY,
	// or if not, at least an outgoing mailbox is available.
	// This can be checked by the function HAL_CAN_GetTxMailboxesFreeLevel()
	// If the return value is greater than 0, there is an empty outgoing mailbox.
	// If the CAN periphery is not ready, return the HAL_BUSY value.



	// If the system is ready to send, fill in the txHeader structure (it is a global variable)
	// with the parameters of the outgoing message, and copy the data contents to the global txBuffer variable.
	// Use standard message structure (set the IDE field to CAN_ID_STD)
	// Use normal message sending (set the RTR field to CAN_RTR_DATA)
	// Set the (standard) message ID to 0x321, the extended ID is not relevant here.
	// The message should contain 2 bytes of data (DLC=2),
	//   the first one is the zone ID (txBuffer[0])
	//   the second is newStatus (txBuffer[1])



	// Notify the CAN periphery of the pending message by calling HAL_CAN_AddTxMessage().
	// Use the periphery handle, message header and the data buffer as arguments,
	// and a uint32_t pointer where the function will write which mailbox was used to send the message.
	// This value will not be used so create a local variable and pass its address.



	// In case of success, log the successful message sending.


	return HAL_OK;
}

/** This function is called periodically from the main loop. When status change is detected, it sends the new status to the CAN bus. */
void CAN_Go()
{
	if (hasLocalZoneStatusChanged)
	{
		HAL_StatusTypeDef result = CAN_SendMessage(localZoneID, zoneStatus[localZoneID]);
		if (result != HAL_OK)
		{
			Log_LogStringAndHalStatus("CAN_SendMessage: failed.\n\r", LOGLEVEL_NORMAL, result);
		}
	}

	if (hasAnyZoneStatusChanged)
	{
		repeated_log_delay = 0;
	}
}

/* ----------------- Interrupt handler and callback functions ----------------- */

/** Process a received CAN message */
void ProcessReceivedCanMessage(uint8_t zoneID, uint8_t newStatus)
{
	// Save received status change 
	zoneStatus[zoneID] = newStatus;
	hasAnyZoneStatusChanged = 1;

	// If the received message indicates a status change in our zone, we 
	// set this flag as well (however, this should have already been set by 
	// LocalSensorProcessing)
	if (localZoneID==zoneID)
	{
		hasLocalZoneStatusChanged = 1;
	}
	// Since this function is called from an interrupt service routine, we 
	// don't send any log message to the UART.
}

// TODO: Task 5 - CAN
// Uncomment the function definitions of HAL_CAN_RxFifo0MsgPendingCallback()
// and HAL_CAN_ErrorCallback()


/** Callback function, which is called when a CAN message was received successfully */
/*
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	// TODO: Task 5 - CAN
	// This function is called when an incoming message was received by a FIFO
	// Read the message header and the data contents from the FIFO using the function HAL_CAN_GetRxMessage()
	// Use the global rxHeader and rxBuffer buffers to store the header and the data
	// Use the periphery handle from the argument, instead the global CAN handle!
	// Check whether the incoming message (standard) is indeed 0x321 and the data length is 2.
	// If these conditions are satisfied, call ProcessReceivedCanMessage() function, which takes care of the message processing.
	// The function has two arguments, zoneID and newStatus, these are the first two bytes of the message data.

}
*/

/** Error callback function of CAN */
/*
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *handle)
{
	char buffer[255];
	snprintf(buffer, 255, "HAL_CAN_ErrorCallback: CAN error: %u\n\r", (unsigned int)handle->ErrorCode);
	Log_LogString(buffer, LOGLEVEL_NORMAL);
}
*/
