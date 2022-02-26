/**
  ******************************************************************************
  * @file    /inc/FLASH_SECTOR.h
  * @author  Miroslav Mitrovic
  * @brief   This header file provides headers for Flash sectors of STM32F407VGT6 .
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

#ifndef INC_FLASH_SECTOR_H_
#define INC_FLASH_SECTOR_H_

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <math.h>
/* Function Prototypes---------------------------------------------------------*/
/** @brief Write the Data to the Flash \n
 *  This function writes data to the flash by 4 bytes.
 *
 *
 *  @param[in] 			StartSectorAddress Start sector address
 *  @param[out] 		DATA_32
 *  @return 			none
 */
uint32_t Flash_Write_Data (uint32_t StartSectorAddress, uint32_t *DATA_32 );
/** @brief This function reads data from memory \n
 *  This Function will read data from memory by 4 bytes.
 *
 *
 *  @param[in] 			StartSectorAddress Start address of sector
 *  @param[out] 		DATA_32 pointer to struct where the data will be placed
 *  @return 			none
 */
void Flash_Read_Data (uint32_t StartSectorAddress,__IO uint32_t *DATA_32);
/** @brief Convert Data to String \n
 *  This Function converts data to string.
 *
 *
 *  @param[in] 			data pointer to data to be converted
 *  @param[out] 		str  pointer for the data that will hold the string
 *  @return 			none
 */
void Convert_To_Str (uint32_t *data, char *str);
/** @brief Gets the sector of a given address \n
 *  This Function returns a sector of given address.
 *
 *
 *  @param[in] 			Address Memory address
 *  @param[out] 		none
 *  @return 			Sector of given address
 */
uint32_t GetSector(uint32_t Address);



#endif /* INC_FLASH_SECTOR_H_ */
