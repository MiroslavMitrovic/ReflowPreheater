/**
  ******************************************************************************
  * @file    /inc/CRC32.h
  * @author  Miroslav Mitrovic
  * @brief   This file contains the function prototype for CRC32 Calculation.
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
  *
  */
#ifndef INC_CRC32_H_
#define INC_CRC32_H_

#include "Main.h"

#define CRC32_CALCULATION_START_ADDRESS 0x08040000
#define CRC32_CALCULATION_END_ADDRESS	0x0805FFFC
// calculate a checksum on a buffer -- start address = p, length = bytelength
uint32_t crc32_byte(uint8_t const *p, uint32_t bytelength);

// convert Big endian value to Small endian value
uint32_t BE_to_SE_convert(uint32_t value);


uint32_t crc32_check_sw (char *buf, uint32_t len);





#endif /* INC_CRC32_H_ */
