/** TODO: Task 4 - SPI (part 1)
 * SPI communication is implemented in this source, providing low level functions for the 
 * bsp_accelerometer.c that contains device specific functions and builds on top of the 
 * low level SPI driver. 
 *
 * The task here is to initialize the SPI peripheral (SPI_Init() function) and
 * implement all communication functions (SPI_EnableChip(), SPI_Send(), SPI_Receive() and
 * SPI_SendReceive()).
 *
 * These are used by bsp_accelerometer.c to communicate with the LIS302DL MEMS sensor.
 */
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "bsp_globalfunctions.h"
#include "spi.h"

/* ----------------- Private, global variables ------------------- */

const uint32_t spi_timeout = 5000;

/* ----------------- Public functions ------------------------ */

/** Initialization of SPI peripheral */
HAL_StatusTypeDef SPI_Init()
{
	// TODO: Task 4 - SPI (part 1)
	// Setup the SPI periphery using the GUI by opening the file MARCOM.ioc. Use the following settings:
	//  - Instance: SPI1
	//  - Full-Duplex Master Mode
	//  - Clock prescaler: 16
	//  - Low clock polarity
	//  - Clock phase 1 EDGE
	//  - CRC calculation disabled
	//  - Software based NSS signal
	//  - SCK line: PA5, MISO line: PA6, MOSI line: PA7
	// Setup the PE3 pin as GPIO output, it will be used as the slave select (NSS) signal by software.
	// After generating the source, include "spi.h" and call the initializer function.
	MX_SPI1_Init();
	HAL_SPI_MspInit(&spi1);

	return HAL_OK;
}

/** Enable or disable the MEMS IC */
void SPI_EnableChip(int enable)
{
	// TODO: Task 4 - SPI (part 1)
	// For setting the PE3 GPIO pin (slave select) use fuction HAL_GPIO_WritePin()
	// Note that in case of 'true' enable value the active low slave select signal has to be set to zero
	HAL_GPIO_WritePin(GPIOx);
}

/** SPI send data */
HAL_StatusTypeDef SPI_Send(uint8_t* pData, uint16_t dataSize)
{
	// TODO: Task 4 - SPI (part 1)
	// For sending data over SPI, use the HAL_SPI_Transmit() function with the available 
	// parameters and the 'spi_timeout' constant.

	return HAL_OK;
}

/** SPI receive data */
HAL_StatusTypeDef SPI_Receive(uint8_t* pData, uint16_t dataSize)
{
	// TODO: Task 4 - SPI (part 1)
	// For receiving data from SPI, use the HAL_SPI_Receive() function with the available 
	// parameters and the 'spi_timeout' constant.
	// Erase the dummy code returning zeros.

	for(int i=0; i<dataSize; i++)
	{
		pData[i]=0;
	}
	return HAL_OK;
}

/** SPI sending and receiving at the same time */
HAL_StatusTypeDef SPI_SendReceive(uint8_t* pDataIn, uint8_t *pDataOut, uint16_t dataSize)
{
	// TODO: Task 4 - SPI (part 1)
	// Use the HAL_SPI_TransmitReceive() function with the available parameters 
	// and the 'spi_timeout' constant.
	// Erase the dummy code returning zeros.

	for(int i=0; i<dataSize; i++)
	{
		pDataIn[i]=0;
	}
	return HAL_OK;
}
