/*
 * FLASH_SECTOR.h
 *
 *  Created on: April 07, 2021
 *      Author: Miroslav Mitrović
 */
#include <stdlib.h>
#include "arm_math.h"

#ifndef INC_FLASH_SECTOR_H_
#define INC_FLASH_SECTOR_H_

typedef struct {
	float32_t KP ;
	float32_t Ki ;
	float32_t KD ;
	float32_t firstHeatUpRate;
	uint32_t SoakTempeture ;
	uint32_t SoakTime ;
	float32_t secondHeatUpRate;
	uint32_t ReflowTempeture ;
	uint32_t ReflowTime;
}ReflowTemplate;
extern ReflowTemplate ReflowParameters;
extern ReflowTemplate ReflowParametersRead;
uint32_t Flash_Write_Data (uint32_t StartSectorAddress, ReflowTemplate *DATA_32 );
void Flash_Read_Data (uint32_t StartPageAddress,__IO ReflowTemplate *DATA_32);
void Convert_To_Str (uint32_t *data, char *str);
uint32_t GetSector(uint32_t Address);



#endif /* INC_FLASH_SECTOR_H_ */
