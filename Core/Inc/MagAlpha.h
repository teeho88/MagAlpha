/*****
 * Author: TEEHO Nguyen
Description:
- This library supplies some basic functions to interface with MagAlpha through SPI
- To use this library you need to implement some __weak functions:
+ void MagAlpha_Init(int SPI_MODE, int baudrate);
+ void MagAlpha_SPI_Write(uint16_t data);
+ uint16_t MagAlpha_SPI_Read();
+ void MagAlpha_SPI_Select();
+ void MagAlpha_SPI_Deselect();
+ void MagAlpha_DelayMs(int ms);
+ void MagAlpha_DelayUs(int us);
******/

#ifndef MAGALPHA_H
#define MAGALPHA_H

/* User include begin */
#include "main.h"
/* User include end */

//Only support SPI mode 0 and 3
enum SPI_MODE{
	SPI_MODE_0 = 0,
	SPI_MODE_3 = 1
};

void MagAlpha_Init(int SPI_MODE, int baudrate);
void MagAlpha_SPI_Write(uint16_t data);
uint16_t MagAlpha_SPI_Read();
void MagAlpha_SPI_Select();
void MagAlpha_SPI_Deselect();
void MagAlpha_DelayMs(int ms);
void MagAlpha_DelayUs(int us);
float MagAlpha_ReadAngle();
uint16_t MagAlpha_ReadRaw();
uint8_t MagAlpha_ReadRegister(uint8_t address);
uint8_t MagAlpha_WriteRegister(uint8_t address, uint8_t value);

#endif
