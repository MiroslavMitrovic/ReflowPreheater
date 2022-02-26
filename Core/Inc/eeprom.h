/**
  ******************************************************************************
  * @file    EEPROM/EEPROM_Emulation/inc/eeprom.h 
  * @author  MCD Application Team/Miroslav Mitrovic
  * @brief   This file contains all the functions prototypes for the EEPROM 
  *          emulation firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */ 
/*/*
   \page CMSIS EEPROM EMULATION
   *
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "variables.h"

/* Exported constants --------------------------------------------------------*/
/* EEPROM emulation firmware error codes */
#define EE_OK      (uint32_t)HAL_OK
#define EE_ERROR   (uint32_t)HAL_ERROR
#define EE_BUSY    (uint32_t)HAL_BUSY
#define EE_TIMEOUT (uint32_t)HAL_TIMEOUT

/* Define the size of the sectors to be used */
#define PAGE_SIZE               (uint32_t)0x20000  /* Page size = 128KByte */

/* Device voltage range supposed to be [2.7V to 3.6V], the operation will 
   be done by word-if half-word is used it should be 2.1-2.7V VOLTAGE_RANGE_2  */

#define VOLTAGE_RANGE           (uint8_t)VOLTAGE_RANGE_2
/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS  ((uint32_t)0x080A0000) /* EEPROM emulation start address:
                                                  from sector2 : after 16KByte of used 
                                                  Flash memory */

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x0000))
#define PAGE0_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))
#define PAGE0_ID               FLASH_SECTOR_9

#define PAGE1_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x20000))
#define PAGE1_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (2 * PAGE_SIZE - 1)))
#define PAGE1_ID               FLASH_SECTOR_10

/* Used Flash pages for EEPROM emulation */
#define PAGE0                 ((uint16_t)0x0000)
#define PAGE1                 ((uint16_t)0x0001) /* Page nb between PAGE0_BASE_ADDRESS & PAGE1_BASE_ADDRESS*/

/* No valid page define */
#define NO_VALID_PAGE         ((uint16_t)0x00AB)

/* Page status definitions */
#define ERASED                ((uint16_t)0xFFFF)     /* Page is empty */
#define RECEIVE_DATA          ((uint16_t)0xEEEE)     /* Page is marked to receive data */
#define VALID_PAGE            ((uint16_t)0x0000)     /* Page containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE  ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL             ((uint8_t)0x80)

/* Variables' number */
#define NB_OF_VAR             ((uint8_t)0x03)

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Virtual address defined by the user: 0xFFFF value is prohibited */
typedef enum FEE_Vars
{
	KP_VirtAddr = 0xAAA0,
	firstHeatUpRate_VirtAddr = 0xAAA1,
	SoakTempeture_VirtAddr = 0xAAA2,
	SoakTime_VirtAddr = 0xAAA3,
	secondHeatUpRate_VirtAddr = 0xAAA4,
	ReflowTempeture_VirtAddr = 0xAAA5,
	ReflowTime_VirtAddr = 0xAAA6,
	ui8_bank1Percentage_VirtAddr = 0xAAA7,
	ui8_bank2Percentage_VirtAddr = 0xAAA8,
	MaxNumOfVirtAddr = 10
}FEE_VirtAddr;


/** @brief Initialization Function of EEPROM Emulation \n
 *  This Function Restore the pages to a known good state in case of page's status
 *   corruption after a power loss.
 *
 *  @param[in] 	none
 *  @param[out] none
 *  @return - Flash error code: on write Flash error
 *         - FLASH_COMPLETE: on success
 */
uint16_t EE_Init(void);
/** @brief  Function that Reads EEPROM Emulation Variable \n
 *  This Function Returns the last stored variable data, if found, which correspond to
 *   the passed virtual address
 *
 *  @param[in] 	VirtAddress Variable virtual address
 *  @param[out] Data Global variable contains the read variable value
 *  @return Success or error status:
 *           - 0: if variable was found
 *           - 1: if the variable was not found
 *           - NO_VALID_PAGE: if no valid page was found.
 */
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t* Data);
/** @brief  Function that writes EEPROM Emulation Variable \n
 *  This Function writes the last stored variable data with the passed virtual address
 *
 *  @param[in] 	VirtAddress Variable virtual address
 *  @param[in] 	Data: 16 bit data to be written
 *  @return Success or error status:
 *           - FLASH_COMPLETE: on success
 *           - PAGE_FULL: if valid page is full
 *           - NO_VALID_PAGE: if no valid page was found
 *           - Flash error code: on write Flash error
 */
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data);
/** @brief Initialization Function of Flash EEPROM Emulation \n
 *  This Function Restore the pages to a known good state in case of page's status
 *   corruption after a power loss.
 *
 *  @param[in] 	none
 *  @param[out] none
 */
void FEE_Init(void);
/** @brief Deinitialization Function of Flash EEPROM Emulation \n
 *  This Function Locks a Flash driver.
 *
 *  @param[in] 	none
 *  @param[out] none
 */
void FEE_DeInit(void);
/** @brief  Function that writes EEPROM Emulation Variable \n
 *  This Function writes the last stored variable data with the passed virtual address
 *
 *  @param[in] 	p_CtrlParams pointer to struct with Control Parameters
 *  @param[in] 	p_ReflowParameters pointer to struct with Reflow Parameters
 *  @return Success or error status:
 *           - HAL_OK
 *           - HAL_ERROR
 */
HAL_StatusTypeDef FEE_WriteCtrlParams(msTempControlParams* p_CtrlParams, ReflowTemplate *p_ReflowParameters);
/** @brief  Function that reads EEPROM Emulation Variable \n
 *  This Function reads the last stored variable data with the passed virtual address
 *
 *  @param[out] 	p_CtrlParams pointer to struct with Control Parameters
 *  @param[out] 	p_ReflowParameters pointer to struct with Reflow Parameters
 *  @return Success or error status:
 *           - HAL_OK
 *           - HAL_ERROR
 */
HAL_StatusTypeDef FEE_ReadCtrlParams(msTempControlParams* p_CtrlParams, ReflowTemplate *p_ReflowParameters);
#endif /* __EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
