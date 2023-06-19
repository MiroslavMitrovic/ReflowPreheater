/**
  ******************************************************************************
  * @file    /inc/Reflow_functions.h
  * @author  Miroslav Mitrovic
  * @brief   This file contains all the functions prototypes for the Reflow functions.
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
  *
   @subpage REFLOW
   @image
   @startuml

   package "Application"{
 [Application] - Main.c
 note right of Main.c
	Application
	source file
end note
}

 package "Base Software"{
	[FEE]
	[I2CLCD]
	[REFLOW]
	[FLASH_SECTOR]
}
package "Drivers"{
	[CMSIS]..>[STM32F4xx]
	[DSP]
	[STM32F4xx_HAL_Driver]


}
	[Application]-->[FEE] : use
	[Application]-->[I2CLCD] : use
	[Application]-->[REFLOW] : use
	[Application]-->[FLASH_SECTOR] : use
	[Application]-->[CMSIS] : use
	[Application]-->[DSP] : use
	[Application]-->[STM32F4xx_HAL_Driver] : use
@enduml
   *
*/

#ifndef INC_REFLOW_FUNCTIONS_H_
#define INC_REFLOW_FUNCTIONS_H_
/* Includes ------------------------------------------------------------------*/
#include	<stdio.h>
#include	"arm_math.h"
#include	<stdbool.h>
/* Defines -------------------------------------------------------------------*/
#define REFLOW_CURVE_SIZE 15000U		///< Define for size of the reflow Curve
/* Enums ---------------------------------------------------------------------*/
typedef enum STATES						///< Enum for STATES
{
	Initializing = 0,
	Preheat = 1,
	Soak = 2,
	Reflow = 3,
	Cooldown = 4,
	Finish = 5,
	Error = 6,
	MaxNumOfPhases = 7
} STATE;
/* Structs ---------------------------------------------------------------------*/
typedef  struct
{
	bool 	StartFlag;
	bool  	initComplete;
	bool 	preheatComplete_1;
	bool 	soakComplete;
	bool 	preheatComplete_2;
	bool 	reflowComplete;
	bool	cooldownComplete;
} FLAGS;									///< Status State Flags Struct definition

extern FLAGS StateFlag;						///< Status State Flags Struct declaration

typedef struct
{
	uint8_t ui8_bank1Percentage;
	uint8_t ui8_bank2Percentage;
	uint16_t u16_ReflowIndexCurrent;
	uint32_t counter_1ms;
	uint32_t counter_10ms;
	uint32_t counter_100ms;
	uint32_t counter_250ms;
	uint32_t counter_1000ms;
	uint32_t counter_500ms;
	volatile float32_t *p_temperature;
	volatile float32_t *p_PIDError;
	FLAGS *p_StatusFlags;

}msTempControlParams;

typedef struct {
	float32_t	KP;
	float32_t	KI;
	float32_t	KD;
	float32_t	firstHeatUpRate;
	uint32_t	SoakTempeture;
	uint32_t	SoakTime;
	float32_t	secondHeatUpRate;
	uint32_t	ReflowTempeture;
	uint32_t 	ReflowTime;
}ReflowTemplate;

extern ReflowTemplate ReflowParameters;
extern msTempControlParams CtrlParams;
extern arm_pid_instance_f32 PID;


/* Functions ---------------------------------------------------------------------*/

/** @brief Calculation of Reflow Curve \n
 *  This Function calculate Reflow curve based on input parameters
 *  such as Soak and Reflow temperatures, gradient of heat and time for each phase
 *
 *  @param[in] p_ReflowParameters pointer to struct where are Reflow parameters
 *  @param[in,out] p_ReflowCurve pointer to Reflow Curve array
 *  @param[in,out] p_PhaseIndex pointer to  phase index array
 *  @return none
 */
void calculateReflowCurve(ReflowTemplate *p_ReflowParameters, uint16_t *p_ReflowCurve, uint16_t *p_PhaseIndex);
/** @brief Handle of GUI menu \n
 *  This function handles data input from user and stores this data into FEE.
 *
 *  @param  none
 *  @return none
 */
void HandleGui();

/** @brief Get Temperature data \n
 * Get temperature value from MAX6675 interface
 *
 *  @param[out] p_temperature_val pointer to the temperature value from thermocouple
 *  @return none
 */
static void readTemperatureData(volatile float* p_temperature_val);
/** @brief read Temperature data \n
 * read temperature value from MAX6675 interface
 *
 *  @param[out] p_temperature_val pointer to the temperature value from thermocouple
 *  @return none
 */
void readTemperatureData_ex(volatile float* p_temperature_val);
/** @brief read Temperature data \n
 * read temperature value from MAX6675 interface
 *
 *  @param[out] p_temperature_val pointer to the temperature value from thermocouple
 *  @return none
 */
void getTemperatureData(volatile float* p_temperature_val);
/** @brief Control of Heaters \n
 *  This Function controls the heating process according to the input parameters
 *
 *  @param[in] CtrlParams pointer to struct where are control parameters stored
 *  @param[in] p_ReflowCurve pointer to Reflow Curve array
 *  @param[in] p_ReflowParameters pointer where Reflow parameters are stored
 *  @return none
 */
/** @brief Get Temperature data \n
 * Get temperature value from MAX6675 interface
 *
 *  @param[out] p_temperature_val pointer to the temperature value
 *  @return none
 */
void msTempControlHandler(msTempControlParams* CtrlParams, uint16_t* p_ReflowCurve, ReflowTemplate *p_ReflowParameters);
/** @brief Show current Temperature and Time remaining values on LCD\n
 *  This Function controls shows current Temperature and Time remaining values on LCD and also error as difference between set and measured temperature.
 *
 *  @param[in] CtrlParams pointer to struct where are control parameters stored
 *  @param[in] p_ReflowParameters pointer where Reflow parameters are stored
 *  @param[in] p_PhaseIndex pointer to  phase index array
 *  @return none
 */
void updateGuiVal(msTempControlParams* CtrlParams, ReflowTemplate *p_ReflowParameters, uint16_t *p_PhaseIndex);
/** @brief String Reverse\n
 *  This Function Reverses a string 'str' of length 'len'.
 *
 *  @param[in, out] str pointer to string
 *  @param[in] len lenght of string
 *  @return none
 */
void reverse(unsigned char* str, int len );
/** @brief Int to String conversion\n
 *  Converts a given integer x to string str[].
 *  d is the number of digits required in the output.
 *  If d is more than the number of digits in x,
 *  then 0s are added at the beginning.
 *
 *  @param[in] x integer to be converted
 *  @param[in, out] str array of string
 *  @param[in] d decimal part
 *  @return none
 */
int intToStr(int x, unsigned char str[], int d);
/** @brief Float to String conversion\n
 *  Converts a given float n to string res.
 *  afterpoint is the number of digits after dot.
 *
 *
 *  @param[in] n float to be converted
 *  @param[out] res output string
 *  @param[in] afterpoint number after dot.
 *  @return none
 */
void ftoa(float n, unsigned char* res, int afterpoint);
/** @brief Reflow again option\n
 *  This function provides an option to restart the reflow procedure again.
 *  @param  none
 *  @return none
 */
void ReflowAgain(void);
/** @brief Reset Reflow Status Flags\n
 *  This function performs a Reset of all Reflow Status Flags.
 *  @param  none
 *  @return none
 */
void ResetFlags(void);
/** @brief Check if Temperature Sensor is connected\n
 *  This function performs a Check if Temperature Sensor is connected, and if not
 *  it stays in while loop until sensor is reconnected.
 *  @param[in] 	temperature value
 *	@param[out]	none
 *  @return 	none
 */
void f_GuiErrorCheck(volatile float temperature);
/** @brief Displays Sensor OK message\n
 *  This function performs Displays Sensor OK message if sensor is connected.
 *  @param[in]  none
 *	@param[out]	none
 *  @return 	none
 */
void f_GuiSensorInitOKmsg(void);
/** @brief Displays and Stores Values for Soak Temperature\n
 *  This function Displays and Stores Values for Soak Temperature.
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuSoakTemp(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for Soak Time\n
 *  This function Displays and Stores Values for Soak Time.
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuSoakTime(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for Reflow Temperature\n
 *  This function Displays and Stores Values for Reflow Temperature.
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuReflowTemp(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for Reflow Time\n
 *  This function Displays and Stores Values for Reflow Time.
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuReflowTime(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for Soak Temperature Gradient\n
 *  This function Displays and Stores Values for Soak Temperature Gradient[degC/s].
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuSoakTempGrad(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for KP\n
 *  This function Displays and Stores Values for KP[/].
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuKPUpdate(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for KI\n
 *  This function Displays and Stores Values for KI[/].
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuKIUpdate(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for KD\n
 *  This function Displays and Stores Values for KD[/].
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuKDUpdate(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for Reflow Temperature Gradient\n
 *  This function Displays and Stores Values for Reflow Temperature Gradient[degC/s].
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are stored
 *  @return 	none
 */
void f_GuiMenuReflowTempGrad(ReflowTemplate *p_ReflowParameters);
/** @brief Displays and Stores Values for heater bank1 power\n
 *  This function Displays and Stores Values for heater bank1 power[%].
 *	@param[in,out]	p_CtrlParams pointer where are Control parameter values are stored
 *  @return 	none
 */
void f_GuiMenuBank1Update(msTempControlParams *p_CtrlParams);
/** @brief Displays and Stores Values for heater bank2 power\n
 *  This function Displays and Stores Values for heater bank2 power[%].
 *	@param[in,out]	p_CtrlParams pointer where are Control parameter values are stored
 *  @return 	none
 */
void f_GuiMenuBank2Update(msTempControlParams *p_CtrlParams);
/** @brief Reads values from FEE or stores Default values\n
 *  This function Reads values from FEE or stores Default values if the values are not available.
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are read/stored
 *	@param[in,out]	p_CtrlParams pointer where are Control parameter values are read/stored
 *  @return 	none
 */
void f_GuiFEEUpdateRead(msTempControlParams *p_CtrlParams, ReflowTemplate *p_ReflowParameters);
/** @brief Writes values to FEE\n
 *  This function writes values to FEE
 *	@param[in,out]	p_ReflowParameters pointer where are Reflow parameter values are read/stored
 *	@param[in,out]	p_CtrlParams pointer where are Control parameter values are read/stored
 *  @return 	none
 */
void f_GuiFEEUpdateWrite(msTempControlParams *p_CtrlParams, ReflowTemplate *p_ReflowParameters);
/** @brief Updates Values of Temperature and Error on LCD\n
 *  This function Displays Temperature and Error on LCD in [degC].
 *	@param[in]	p_temperature pointer where are current temperature values stored
 *	@param[in]	f_PIDError where is error stored.
 *  @return 	none
 */
void f_updateGuiValTempError(volatile float32_t *p_temperature, volatile float32_t f_PIDError);
/** @brief Updates Values of First Gradient and Time remaining on LCD\n
 *  This function Displays values of First Gradient and Time remaining on LCD.
 *	@param[in]	u32_SoakTemperature
 *	@param[in]	u16_FirstHeatupTime time neccesary to temperature to be achieved
 *	@param[in]	u16_ReflowIndexCurrent current time of reflow
 *  @return 	none
 */
void f_updateGuiValGradientSoakParam(uint32_t u32_SoakTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent);
/** @brief Updates Values of Soak Temperature and Time remaining on LCD\n
 *  This function Displays values of Soak Temperature and Time remaining on LCD.
 *	@param[in]	u32_SoakTemperature
 *	@param[in]	u16_FirstHeatupTime time neccesary to temperature to be achieved
 *	@param[in]	u16_ReflowIndexCurrent current time of reflow
 *	@param[in]  u16_SoakTime Soak time that was entered
 *  @return 	none
 */
void f_updateGuiValSoakParam(uint32_t u32_SoakTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,uint16_t u16_SoakTime);
/** @brief Updates Values of  Second Gradient and Time remaining on LCD\n
 *  This function Displays values of Second Gradient and Time remaining on LCD.
 *	@param[in]	u32_ReflowTemperature
 *	@param[in]	u16_FirstHeatupTime time neccesary to temperature to be achieved
 *	@param[in]	u16_ReflowIndexCurrent current time of reflow
 *	@param[in]  u16_SoakTime Soak time that was entered
 *	@param[in]  u16_SecondHeatupTime Heatup time for second gradient
 *  @return 	none
 */
void f_updateGuiValGradientReflowParam(uint32_t u32_ReflowTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,
							 uint16_t u16_SoakTime, uint16_t u16_SecondHeatupTime);
/** @brief Updates Values of Reflow Temperature and Time remaining on LCD\n
 *  This function Displays values of Reflow Temperature and Time remaining on LCD.
 *	@param[in]	u32_ReflowTemperature
 *	@param[in]	u16_FirstHeatupTime time neccesary to temperature to be achieved
 *	@param[in]	u16_ReflowIndexCurrent current time of reflow
 *	@param[in]  u16_SoakTime Soak time that was entered
 *	@param[in]  u16_SecondHeatupTime Heatup time for second gradient
  *	@param[in]  u16_ReflowTime Reflow time that was entered
 *  @return 	none
 */
void f_updateGuiValReflowParam(uint32_t u32_ReflowTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,
								uint16_t u16_SoakTime, uint16_t u16_SecondHeatupTime, uint16_t u16_ReflowTime);
/** @brief Updates Values of Reflow Temperature and Time remaining on LCD\n
 *  This function Displays values of Reflow Temperature and Time remaining on LCD.
 *	@param[in]	u16_CooldownTemperature
 *	@param[in]	u16_FirstHeatupTime time neccesary to temperature to be achieved
 *	@param[in]	u16_ReflowIndexCurrent current time of reflow
 *	@param[in]  u16_SoakTime Soak time that was entered
 *	@param[in]  u16_SecondHeatupTime Heatup time for second gradient
 *	@param[in]  u16_ReflowTime Reflow time that was entered
 *	@param[in]  u16_CooldownTime Cooldown time that was calculated
 *  @return 	none
 */
void f_updateGuiValCoolDownParam(uint32_t u16_CooldownTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,
								uint16_t u16_SoakTime, uint16_t u16_SecondHeatupTime, uint16_t u16_ReflowTime, uint16_t u16_CooldownTime);
/** @brief Displays Sensor OK message\n
 *  This function performs Displays Sensor OK message if sensor is connected.
 *  @param[in]  none
 *	@param[out]	none
 *  @return 	none
 */
void f_updateGuiReflowFinished(void);

#endif /* INC_REFLOW_FUNCTIONS_H_ */
