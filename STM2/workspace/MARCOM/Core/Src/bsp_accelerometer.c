/**
*****************************************************************************
** Communication lab - bsp_accelerometer.c
** Functions of the LIS302DL MEMS sensor can be found here.
** After init, the measurement results can be obtained by function Accelerometer_GetTilt()
** The low-level SPI functions being in bsp_spi.h are used for communication.
*****************************************************************************
* TODO: Task 4 - SPI (part 2)
* Device specific functions LIS302DL_Write() and LIS302DL_Read() are implemented here 
* by using the low-level SPI functions. 
*
* Higher level functions provided here (Accelerometer_Init() and Accelerometer_GetTilt()) 
* use these device specific functions to initialize and use the sensor.

*/
#include "bsp_spi.h"
#include "log.h"
#include "bsp_lis302dl_defines.h"

void LIS302DL_Init(LIS302DL_InitTypeDef *LIS302DL_InitStruct);
void LIS302DL_FilterConfig(LIS302DL_FilterConfigTypeDef *LIS302DL_FilterConfigStruct);
void LIS302DL_Write(uint8_t* pData, uint8_t WriteAddr, uint16_t dataSize);
void LIS302DL_Read(uint8_t* pData, uint8_t ReadAddr, uint16_t dataSize);

/* ----------------- Private, global variables ------------------- */
// In case of an error, has the MEMS sensor error already be signaled in the log?
// Necessary to avoid overwhelming the log with the same message.
int memsErrorReported = 0;

/* ----------------- Public functions ------------------------ */

/** Initializing the MEMS sensor. It contains the SPI initialization as well. */
void Accelerometer_Init()
{
	HAL_StatusTypeDef result = SPI_Init();
	if (result != HAL_OK)
	{
		Log_LogStringAndHalStatus("Accelerometer_Init: SPI_Init() failed.\n\r", LOGLEVEL_NORMAL, result);
		return;
	}

	LIS302DL_InitTypeDef LIS302DL_InitStructure;
	LIS302DL_InitStructure.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
	LIS302DL_InitStructure.Output_DataRate = LIS302DL_DATARATE_100;
	LIS302DL_InitStructure.Axes_Enable = LIS302DL_XYZ_ENABLE;
	LIS302DL_InitStructure.Full_Scale = LIS302DL_FULLSCALE_2_3;
	LIS302DL_InitStructure.Self_Test = LIS302DL_SELFTEST_NORMAL;
	LIS302DL_Init(&LIS302DL_InitStructure);
	// The sensor needs some time
	HAL_Delay(30);
	// MEMS High Pass Filter setting
	LIS302DL_FilterConfigTypeDef LIS302DL_FilterStruct;
	LIS302DL_FilterStruct.HighPassFilter_Data_Selection = LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER;
	LIS302DL_FilterStruct.HighPassFilter_CutOff_Frequency = LIS302DL_HIGHPASSFILTER_LEVEL_1;
	LIS302DL_FilterStruct.HighPassFilter_Interrupt = LIS302DL_HIGHPASSFILTERINTERRUPT_1_2;
	LIS302DL_FilterConfig(&LIS302DL_FilterStruct);

	memsErrorReported = 0;
}

/** Provides the actual acceleration vector. Zero return value indicates success. */
int Accelerometer_GetTilt(int8_t *Xg, int8_t *Yg, int8_t *Zg)
{
	unsigned char uBuffer[6];
	uint8_t temp = 0x00;

	LIS302DL_Read(&temp, LIS302DL_WHO_AM_I_ADDR, 1);
	if (temp != 0x3B)
	{
		if (!memsErrorReported)
		{
			Log_LogString("Error: MEMS sensor not found on SPI! Please check jumper JP3, it should be open.\n\r",LOGLEVEL_NORMAL);
			memsErrorReported = 1;
		}
		*Xg = 0x00;
		*Yg = 0x00;
		*Zg = 0x00;
		return 1;
	}
	else
	{
		HAL_Delay(50);
		LIS302DL_Read(uBuffer, LIS302DL_OUT_X_ADDR, 6);
		*Xg = (signed char)(uBuffer[2])/2;
		*Yg = (signed char)(uBuffer[0])/2;
		*Zg = (signed char)(uBuffer[4])/2;
		return 0;
	}
}

/* ----------------- Private functions --------------------------- */

/** LIS302DL IC initialization, called by Accelerometer_Init() */
void LIS302DL_Init(LIS302DL_InitTypeDef *LIS302DL_InitStruct)
{
  uint8_t ctrl = 0x00;

  /* MEMS settings: data rate, power mode, full scale, self test and axes */
  ctrl = (uint8_t) (LIS302DL_InitStruct->Output_DataRate | LIS302DL_InitStruct->Power_Mode | \
                    LIS302DL_InitStruct->Full_Scale | LIS302DL_InitStruct->Self_Test | \
                    LIS302DL_InitStruct->Axes_Enable);

  /* Write settings to the CTRL_REG1 register of the sensor IC */
  LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG1_ADDR, 1);
}

/** LIS302DL filter settings, called by Accelerometer_Init() */
void LIS302DL_FilterConfig(LIS302DL_FilterConfigTypeDef *LIS302DL_FilterConfigStruct)
{
  uint8_t ctrl = 0x00;

  /* CTRL_REG2 register read */
  LIS302DL_Read(&ctrl, LIS302DL_CTRL_REG2_ADDR, 1);

  /* Clear corresponding bits first */
  ctrl &= (uint8_t)~(LIS302DL_FILTEREDDATASELECTION_OUTPUTREGISTER | \
                     LIS302DL_HIGHPASSFILTER_LEVEL_3 | \
                     LIS302DL_HIGHPASSFILTERINTERRUPT_1_2);
  /* Then set them appropriately: MEMS high pass filter cut-off level, interrupt and data selection bits. */
  ctrl |= (uint8_t)(LIS302DL_FilterConfigStruct->HighPassFilter_Data_Selection | \
                    LIS302DL_FilterConfigStruct->HighPassFilter_CutOff_Frequency | \
                    LIS302DL_FilterConfigStruct->HighPassFilter_Interrupt);

  /* Write settings back to CTRL_REG2 register */
  LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG2_ADDR, 1);
}

/** Writing a specific LIS302DL register (addressed by WriteAddr) */
void LIS302DL_Write(uint8_t* pData, uint8_t WriteAddr, uint16_t dataSize)
{
	if(dataSize > 0x01)
	{
		// In case of writing multiple bytes, the first byte has to be modified 
		// in order to signalize multibyte command
		WriteAddr |= (uint8_t)MULTIPLEBYTE_CMD;
	}

	// TODO: Task 4 - SPI (part 2)
	// Using the functions provided by bsp_spi.h perform the following:
	// 1. Select the LIS302DL IC (chip select)
	// 2. Send the value of WriteAddr over SPI (this will select the register in the sensor to be written)
	// 3. Send the actual data passed by pData and dataSize
	// 4. Disable chip select


}

/** Reading a specific LIS302DL register (addressed by ReadAddr) */
void LIS302DL_Read(uint8_t* pData, uint8_t ReadAddr, uint16_t dataSize)
{
	// In the first byte the reading operation and optionally multibyte transfer are signalized
	if(dataSize > 0x01)
	{
		ReadAddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);
	}
	else
	{
		ReadAddr |= (uint8_t)READWRITE_CMD;
	}

	// TODO: Task 4 - SPI (part 2)
	// Using the functions provided by bsp_spi.h perform the following:
	// 1. Select the LIS302DL IC (chip select)
	// 2. Send the value of ReadAddr over SPI (this will select the register in the sensor to be read)
	// 3. Receive dataSize amount of bytes and save them to the buffer pointed by pData
	// 4. Disable chip select
	// 5. Erase the dummy code returning zeros
	// (Don't forget to solve the tasks in bsp_spi.c as well!)

	for(int i=0; i<dataSize; i++)
	{
		pData[i]=0;
	}
}
