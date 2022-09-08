/**
*****************************************************************************
** Communication lab - glcd.c
** Graphics LCD functions
*****************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

#include "bsp_glcd.h"
#include "bsp_globalfunctions.h"
#include "font.h"

void GLCD_MSP_Init(void);

/* ----------------- Public functions  ----------------- */

void GLCD_Init(void)
{
	// Default states of GPIOs
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);	// GLCD_RW = 0
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);		// GLCD_E = 1
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);	// GLCD_RESET = 0
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);	// #GLCDEN = 0
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);		// Backlight = 1 (PWM 100%)

	// Init GLCD functions
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);	// GLCD_E = 0
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);	// GLCD_RESET = 1

	GLCD_Write(3,0,0x3F); 	//GLCD on
	GLCD_Write(3,0,0xC0);	//GLCD Start Line
	GLCD_Clear();			//Clear display
}

void GLCDEN(int newState)
{
	if(newState)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	}
}

/** Writes the value of g_data to the selected display driver (cs_s->CS1, CS2), instruction/data accordingly to the settings
* General purpose write function for the LCD (8 bits, instruction/data)
* 	cs_s, 1 = CS1, 2 = CS2, 3 = CS1&CS2
* 	d_i, 0 = instruction, 1 = data
*/
void GLCD_Write(char cs_s,char d_i,char g_data)
{
	uint16_t data = 0x0000;
	switch(cs_s)
	{
	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		break;
	}
	switch(d_i)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
		break;
	}

	data = GPIOE->IDR;
	data &= 0x00FF;
	data |= g_data << 8;
	GPIOE->ODR = data;

	Sys_DelayUs(1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
	Sys_DelayUs(2);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	Sys_DelayUs(4);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

/** Clear the display. */
void GLCD_Clear(void)
{
	char x,y;
	for(x=0;x<8;x++)
	{
		GLCD_Write(3,0,0x40);
		GLCD_Write(3,0,(0xB8|x));
		for(y=0;y<64;y++)
		{
			GLCD_Write(3,1,0x00);
		}
	}
}

/** Set the value at the intersection of a line and column based on m_data
 * 		m_data: pattern to draw
 * 		cX: row (0-7)
 * 		cY: column (0-127) */
void GLCD_Write_Block(char m_data,char cX,char cY)
{
	char chip=1;
	if(cY>=64)
	{
		chip=2;
		cY-=64;
	}
	GLCD_Write(chip,0,(0x40|cY));
	GLCD_Write(chip,0,(0xB8|cX));
	GLCD_Write(chip,1,m_data);
}

/** Write a string to the display. */
void GLCD_WriteString(const char* string,char Y, char X)
{
	char temp = 0;
	int i=0;
	while(string[i]!='\0')
	{
		temp = string[i];
		GLCD_Write_Char(temp-32,X,Y+6*i);
		i++;
	}
}

/** Write a character to the display. */
void GLCD_Write_Char(char cPlace,char cX,char cY)
{
	char i=0;
	char chip=1;
	if(cY>=64)
	{
		chip=2;
		cY-=64;
	}
	GLCD_Write(chip,0,(0x40|cY));
	GLCD_Write(chip,0,(0xB8|cX));
	for (i=0;i<5;i++)
	{
	  if (cY+i >= 64)
	  {
		  chip=2;
		  GLCD_Write(chip,0,(0x40|(cY+i-64)));
		  GLCD_Write(chip,0,(0xB8|cX));
	  }
	  GLCD_Write(chip,1,fontdata[cPlace*5+i]);
	}
}
