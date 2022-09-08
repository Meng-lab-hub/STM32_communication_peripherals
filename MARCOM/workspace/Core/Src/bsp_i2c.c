/** TODO: Task 3 - I2C
 * The solution of the I2C task has to be prepared in this file.
 * The low level functions of this file are used by thermometer.c, that implements the protocol to 
 * communication with the thermometer IC using the functions provided here.
 *
 * First the GPIO pins and the I2C1 peripheral must be initialized.
 * To do this, we use the graphical configurator in the MARCOM.ioc file and
 * call the generated initialization function here in the I2C_Init() function.
 *
 * I2C_ReadRegister() and I2C_WriteRegister() functions are responsible to read or write a register in the thermometer. 
 * HAL library provides a lot of help in this: it generates the start condition, I2C addressing, sending the address 
 * of the target register, reading or writing the register and the stop condition, all in the background. 
 *
 * In order to read a register from the thermometer, the following transaction must be executed:
 * START, thermometer address, write, register address, restart, thermometer address, read, [read the data], stop.
 *
 * This is a common way to communicate with I2C devices, thus the HAL library has an implementation for it.
 * */

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

#include "bsp_globalfunctions.h"
#include "i2c.h"

/* ----------------- Private, global variables ------------------- */

const uint32_t i2c_timeout = 5000;

/* ----------------- Public functions ------------------------ */

/** I2C Initialization. */
HAL_StatusTypeDef I2C_Init()
{
	// TODO: Task 3 - I2C
	// Set up the I2C periphery using the GUI by opening MARCOM.ioc file. Use the following settings:
	//  - Instance: I2C1
	//  - I2C mode
	//  - Speed Mode: Standard
	//  - Clock speed: 100 000 Hz
	//  - Clock No Stretch Mode: Disabled
	//  - 7 bites addressing
	//  - Dual Address Acknowledged: Disabled
	//  - Primary Slave Address: 0
	//  - General Call address detection: Disabled
	//  - SDA line: PB9, SCL line: PB6
	// After generating the source code, include "i2c.h" header file and call
	// initializer function. The periphery will later be accessed
	// by the handle variable hi2c1. See the header "i2c.h"

	MX_I2C1_Init();

	return HAL_OK;
}

/** Register read using I2C. */
HAL_StatusTypeDef I2C_ReadRegister(uint16_t deviceAddress, uint8_t registerAddress, uint8_t *pData, uint16_t dataSize)
{
	// TODO: Task 3 - I2C
	
	// Use HAL_I2C_Mem_Read() to read registers from an I2C device:
	// - deviceAddress is the I2C address of the device
	// - registerAddress is the addres of the register inside the I2C device
	// - dataSize is the number of bytes to read starting from registerAddress
	// - pData points to the buffer where data is read
	// - set timeout to i2c_timeout global constant
	// Remove the template code that fills pData with zeros.

	return HAL_I2C_Mem_Read(&hi2c1, deviceAddress, (uint16_t)registerAddress, 1, pData, dataSize, i2c_timeout);
	// Note: Casting registerAddress is not obligatory.

	/*
	for(int i=0; i<dataSize; i++)
	{
		pData[i]=0;
	}
	return HAL_OK;
	*/
}

/** Write a register over I2C. */
HAL_StatusTypeDef I2C_WriteRegister(uint16_t deviceAddress, uint8_t registerAddress, uint8_t *pData, uint16_t dataSize)
{
	// TODO: Task 3 - I2C
	// Use HAL_I2C_Mem_Write() similar to the reading
	// The size of the memory address must be specified in bytes (1 byte).

	return HAL_I2C_Mem_Write(&hi2c1, deviceAddress, (uint16_t)registerAddress, 1, pData, dataSize, i2c_timeout);
	// Note: Casting registerAddress is not obligatory.
}
