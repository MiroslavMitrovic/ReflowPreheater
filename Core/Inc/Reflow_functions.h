/*
 * Reflow_functions.h
 *
 *  Created on: 18 Sep 2021
 *      Author: mmitr
 */
#include<stdio.h>
#include<stdlib.h>
#include "main.h"
#include "FLASH_SECTOR.h"
#include "variables.h"
#ifndef INC_REFLOW_FUNCTIONS_H_
#define INC_REFLOW_FUNCTIONS_H_
typedef struct
{
	uint8_t ui8_bank1Percentage;
	uint8_t ui8_bank2Percentage;
	uint16_t u16_ReflowIndexCurrent;
	uint32_t counter_200ms;
	uint32_t counter_1000ms;
	uint32_t counter_250ms;
	volatile float *p_temperature;
	volatile float *p_PIDError;
	FLAGS *p_StatusFlags;

}msTempControlParams;

extern msTempControlParams CtrlParams;

void calculateReflowCurve(ReflowTemplate *p_ReflowParameters, uint16_t *p_ReflowCurve, uint16_t *p_PhaseIndex);

void HandleGui();
void readTemperatureData(volatile float* temperature_val);

void msTempControlHandler(msTempControlParams* CtrlParams, uint16_t* p_ReflowCurve, ReflowTemplate *p_ReflowParameters);

void updateGuiVal(msTempControlParams* CtrlParams, ReflowTemplate *p_ReflowParameters, uint16_t *p_PhaseIndex);

void SwitchDebouncing(void);
void custom_memcpy(void *dest, void *src, size_t n) ;
void reverse(char*, int );
int intToStr(int x, char str[], int d);
void ftoa(float n, unsigned char* res, int afterpoint);
void RefloWConditionsUpdate(void);
void ResetFlags(void);
#endif /* INC_REFLOW_FUNCTIONS_H_ */
