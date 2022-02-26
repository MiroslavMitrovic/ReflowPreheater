/**
  ******************************************************************************
  * @file    /src/FLASH_SECTOR.c
  * @author  Miroslav Mitrovic
  * @brief   This Source file provides function delcarations for Flash sectors of STM32F407VGT6 .
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 Yakamooda electronics GmbH.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Yakamooda electronics GmbH under GPL
  *
  *
  ******************************************************************************
  */
/** @addtogroup Flash_Sector
  * @{
  */

//TODO Update main page in Doxygen
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "FLASH_SECTOR.h"
#include "string.h"
#include "stdio.h"
/* Functions------------------------------------------------------------------*/
/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < 0x08003FFF) && (Address >= 0x08000000))
  {
    sector = FLASH_SECTOR_0;
  }
  else if((Address < 0x08007FFF) && (Address >= 0x08004000))
  {
    sector = FLASH_SECTOR_1;
  }
  else if((Address < 0x0800BFFF) && (Address >= 0x08008000))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address < 0x0800FFFF) && (Address >= 0x0800C000))
  {
    sector = FLASH_SECTOR_3;
  }
  else if((Address < 0x0801FFFF) && (Address >= 0x08010000))
  {
    sector = FLASH_SECTOR_4;
  }
  else if((Address < 0x0803FFFF) && (Address >= 0x08020000))
  {
    sector = FLASH_SECTOR_5;
  }
  else if((Address < 0x0805FFFF) && (Address >= 0x08040000))
  {
    sector = FLASH_SECTOR_6;
  }
  else if((Address < 0x0807FFFF) && (Address >= 0x08060000))
  {
    sector = FLASH_SECTOR_7;
  }
  else if((Address < 0x0809FFFF) && (Address >= 0x08080000))
  {
    sector = FLASH_SECTOR_8;
  }
  else if((Address < 0x080BFFFF) && (Address >= 0x080A0000))
  {
    sector = FLASH_SECTOR_9;
  }
  else if((Address < 0x080DFFFF) && (Address >= 0x080C0000))
  {
    sector = FLASH_SECTOR_10;
  }
  else if((Address < 0x080FFFFF) && (Address >= 0x080E0000))
  {
    sector = FLASH_SECTOR_11;
  }

  return sector;
}

/** @brief Gets sector Size \n
 *  This Function returns a sector size.
 *
 *
 *  @param[in] 			Sector
 *  @param[out] 		none
 *  @return 			The size of a given sector
 */
static uint32_t GetSectorSize(uint32_t Sector)
{
  uint32_t sectorsize = 0x00;
  if((Sector == FLASH_SECTOR_0) || (Sector == FLASH_SECTOR_1) || (Sector == FLASH_SECTOR_2) ||  (Sector == FLASH_SECTOR_3))
  {
    sectorsize = 16 * 1024;
  }
  else if((Sector == FLASH_SECTOR_4))
  {
    sectorsize = 64 * 1024;
  }


  else
  {
    sectorsize = 128 * 1024;
  }

  return sectorsize;
}


uint32_t Flash_Write_Data (uint32_t StartSectorAddress, uint32_t *DATA_32)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t SECTORError;
	uint32_t *p_Record = (uint32_t* ) DATA_32;
	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();

	/* Erase the user Flash area */

	/* Get the number of sector to erase from 1st sector */

	uint32_t StartSector = GetSector(StartSectorAddress);
	uint32_t EndSectorAddress = StartSectorAddress + sizeof(uint32_t);
	uint32_t EndSector = GetSector(EndSectorAddress);

	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector        = StartSector;
	EraseInitStruct.NbSectors     = (EndSector - StartSector) + 1;

	/* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	{
		return HAL_FLASH_GetError ();
	}


	/* Program the user Flash area word by word
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
	for(int i = 0; i < sizeof(uint32_t) ; i = i + 4 , StartSectorAddress = StartSectorAddress + 4, p_Record++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartSectorAddress, *p_Record) == HAL_OK)
		{

			//Do nothing
		}
		else
		{
			/* Error occurred while writing data in Flash memory*/
			return HAL_FLASH_GetError ();
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	     to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();

	return 0;
}
//TODO Write the reflow data into ROM, then read from it. Define RO sections and write the data there.
void Flash_Read_Data (uint32_t StartSectorAddress, __IO uint32_t *DATA_32)
{
	uint32_t *p_Data = (uint32_t* ) DATA_32;

	for(int i = 0; i < sizeof(uint32_t) ;	i = i + 4,	p_Data++ ,	StartSectorAddress = StartSectorAddress + 4	)
	{

		*p_Data = *(__IO uint32_t*)StartSectorAddress;

	}
}

void Convert_To_Str (uint32_t *data, char *str)
{
	int numberofbytes = ((strlen((const char*)data) / 4) + ((strlen((const char*)data) % 4) != 0)) *4;

	for (int i=0; i<numberofbytes; i++)
	{
		str[i] = data[i/4] >> (8 * ( i % 4 ));
	}
}
