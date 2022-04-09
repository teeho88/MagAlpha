/*****
 * Author: TEEHO Nguyen
Description:
- This library supplies some basic function to interface with MagAlpha through SPI
- To use this library you need to implement some __weak function:
+ void MagAlpha_Init(int SPI_MODE, int baudrate);
+ void MagAlpha_SPI_Write(uint16_t data);
+ uint16_t MagAlpha_SPI_Read();
+ void MagAlpha_SPI_Select();
+ void MagAlpha_SPI_Deselect();
+ void MagAlpha_DelayMs(int ms);
+ void MagAlpha_DelayUs(int us);
******/

#include "MagAlpha.h"

//MagAlpha Read/Write Register Command
#define READ_REG_COMMAND    (0b010 << 13)
#define WRITE_REG_COMMAND   (0b100 << 13)

__weak void MagAlpha_Init(int SPI_MODE, int baudrate){
	UNUSED(SPI_MODE);
	/* NOTE : This function should not be modified, when this function is needed,
		            it could be implemented in the user file
		   */
}

__weak void MagAlpha_SPI_Write(uint16_t data){
	UNUSED(data);
	/* NOTE : This function should not be modified, when this function is needed,
	            it could be implemented in the user file
	   */
}

__weak uint16_t MagAlpha_SPI_Read(){
	return 0;
	/* NOTE : This function should not be modified, when this function is needed,
		            it could be implemented in the user file
		   */
}

__weak void MagAlpha_SPI_Select(){
	/* NOTE : This function should not be modified, when this function is needed,
		            it could be implemented in the user file
		   */
}

__weak void MagAlpha_SPI_Deselect(){
	/* NOTE : This function should not be modified, when this function is needed,
		            it could be implemented in the user file
		   */
}

__weak void MagAlpha_DelayMs(int ms){
	/* NOTE : This function should not be modified, when this function is needed,
		            it could be implemented in the user file
		   */
}

__weak void MagAlpha_DelayUs(int us){
	/* NOTE : This function should not be modified, when this function is needed,
		            it could be implemented in the user file
		   */
}

float MagAlpha_ReadAngle(){
  uint16_t angle;
  float angleInDegree;
  angle = MagAlpha_ReadRaw();
  angleInDegree = (angle*360.0)/65536.0;
  return angleInDegree;
}

uint16_t MagAlpha_ReadRaw(){
	uint16_t angle;
	MagAlpha_SPI_Select();
	angle = MagAlpha_SPI_Read(); //Read 16-bit angle
	MagAlpha_SPI_Deselect();
	return angle;
}

uint8_t MagAlpha_ReadRegister(uint8_t address){
  uint8_t readbackRegisterValue;
  MagAlpha_SPI_Select();
  MagAlpha_SPI_Write(READ_REG_COMMAND | ((address & 0x1F) << 8) | 0x00);
  MagAlpha_SPI_Deselect();
  MagAlpha_DelayUs(1); //Wait for tIdleReg (about 750ns) before register readout
  MagAlpha_SPI_Select();
  readbackRegisterValue = ((MagAlpha_SPI_Read() & 0xFF00) >> 8);
  MagAlpha_SPI_Deselect();
  MagAlpha_DelayUs(1); //Wait for tIdleReg (about 750ns) before register readout
  return readbackRegisterValue;
}

uint8_t MagAlpha_WriteRegister(uint8_t address, uint8_t value){
  uint8_t readbackRegisterValue;
  MagAlpha_SPI_Select();
  MagAlpha_SPI_Write(WRITE_REG_COMMAND | ((address & 0x1F) << 8) | value);
  MagAlpha_SPI_Deselect();
  MagAlpha_DelayMs(20);                      //Wait for 20ms to change from writting command to readout
  MagAlpha_SPI_Select();
  readbackRegisterValue = ((MagAlpha_SPI_Read() & 0xFF00) >> 8);
  MagAlpha_SPI_Deselect();
  //readbackRegisterValue should be equal to the written value
  return readbackRegisterValue;
}



