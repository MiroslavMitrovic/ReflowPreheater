/**
  ******************************************************************************
  * @file    /src/Reflow_functions.c
  * @author  Miroslav Mitrovic
  * @brief   This file provides Reflow functions.
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
/** @addtogroup Reflow
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include <i2c_lcd.h>
#include "string.h"
#include "eeprom.h"
#include "FLASH_SECTOR.h"



/* Global Variables------------------------------------------------------------*/
const float  alpha = 0.1;				///< Coefficient for filter
static float avg_temp =	-100;			///< Start value for average temperature calculation
uint8_t ReflowEnable;


FLAGS StateFlag;
uint8_t State;
uint8_t FlagBank1;
uint8_t FlagBank2;
uint8_t ui8_bank1Percentage;
uint8_t ui8_bank2Percentage;
volatile uint8_t ui8_encButtonPressed;

uint8_t PIDFlag;
uint16_t counterBank1;
uint16_t counterBank2;
arm_pid_instance_f32 PID;
msTempControlParams *p_CtrlParams = &CtrlParams;
extern uint32_t u32_EEPromErrCnt;
void reverse(unsigned char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}


int intToStr(int x, unsigned char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, unsigned char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.';

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}




void calculateReflowCurve(ReflowTemplate *p_ReflowParameters, uint16_t *p_ReflowCurve, uint16_t *p_PhaseIndex){

	uint16_t PhaseIndex[6];
	uint16_t ReflowCurve[REFLOW_CURVE_SIZE];
	size_t s_ReflowCurve;
	size_t s_PhaseIndex;
	int index;

	index = 0;
	s_ReflowCurve = 0;
	s_PhaseIndex = 0;
	float timestep = 0.5;

	/*Init Arrays with Zeros*/
	memset(ReflowCurve,0, REFLOW_CURVE_SIZE * sizeof(uint16_t));
	memset(PhaseIndex,0, 6 * sizeof(uint16_t));

	//First Heat Up:
	while (24 + (timestep * p_ReflowParameters->firstHeatUpRate) <= p_ReflowParameters->SoakTempeture)
	{
	ReflowCurve[index] = 24 + (timestep * p_ReflowParameters->firstHeatUpRate);
	index++;
	timestep = timestep + 0.5;
	}
	PhaseIndex[1] = index;

	//Soak
	int Soakduration = 2*p_ReflowParameters->SoakTime;

	for(int i = 0; i < Soakduration;i++)
	{
		ReflowCurve[index+i] = p_ReflowParameters->SoakTempeture;
	}

	//Second Heat Up:
	index = index + Soakduration;
	PhaseIndex[2] = index;
	timestep = 0.5;
	while (p_ReflowParameters->SoakTempeture + (timestep * p_ReflowParameters->secondHeatUpRate) <= p_ReflowParameters->ReflowTempeture)
	{
	ReflowCurve[index] = p_ReflowParameters->SoakTempeture + (uint8_t)timestep * p_ReflowParameters->secondHeatUpRate;
	index++;
	timestep = timestep + 0.5;
	}
	PhaseIndex[3] = index;

	//Reflow
	int Reflowduration = 2*p_ReflowParameters->ReflowTime;

	for(int i = 0;i < Reflowduration;i++)
	{
		ReflowCurve[index+i] = p_ReflowParameters->ReflowTempeture;
	}

	index = index + Reflowduration;
	ReflowCurve[index] = 0;
	PhaseIndex[4] = index;

	//Cooldown
	timestep = 0.5;
	while (p_ReflowParameters->ReflowTempeture - (timestep * 1.8) >= 24)
	{
	ReflowCurve[index] = p_ReflowParameters->ReflowTempeture - (timestep * 1.8);
	index++;
	timestep = timestep + 0.5;
	PhaseIndex[5] = index;
	}
	s_ReflowCurve = sizeof(ReflowCurve);
	s_PhaseIndex  = sizeof(PhaseIndex);

	if(0 < s_ReflowCurve || 0 < s_PhaseIndex)
	{
		memcpy((uint8_t*)p_PhaseIndex, (uint8_t*)PhaseIndex, s_PhaseIndex);
		memcpy((uint8_t*)p_ReflowCurve, (uint8_t*)ReflowCurve, s_ReflowCurve);

	}
	else
	{
		Error_Handler();
	}
}

void HandleGui()
{
	lcd_clear_cmd();
	f_GuiErrorCheck(temperature);
	f_GuiSensorInitOKmsg();
	f_GuiFEEUpdateRead(p_CtrlParams, p_ReflowParameters);
	f_GuiMenuSoakTemp(p_ReflowParameters);
	f_GuiMenuSoakTime(p_ReflowParameters);
	f_GuiMenuReflowTemp(p_ReflowParameters);
	f_GuiMenuReflowTime(p_ReflowParameters);
	f_GuiMenuSoakTempGrad(p_ReflowParameters);
	f_GuiMenuKPUpdate(p_ReflowParameters);
	f_GuiMenuKIUpdate(p_ReflowParameters);
	f_GuiMenuKDUpdate(p_ReflowParameters);
	f_GuiMenuReflowTempGrad(p_ReflowParameters);
	f_GuiMenuBank1Update(p_CtrlParams);
	f_GuiMenuBank2Update(p_CtrlParams);
	f_GuiFEEUpdateWrite(p_CtrlParams, p_ReflowParameters);
}

static void readTemperatureData(volatile float32_t* p_temperature_val)
{
	uint8_t data8[2] = {0};
	uint16_t sum = {0};

			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
			HAL_SPI_Receive(&hspi1,data8,2,300);
			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);

			sum=(uint16_t) data8[1] | (uint16_t) data8[0]<< 8 ;
			if(sum & 0x0004)//No TC connected, error -1
			{
				(*p_temperature_val) = -1;
			}
			else
			{
				(*p_temperature_val) = ((sum >> 3) / 4.0);
			}


}


 void  readTemperatureData_ex(volatile float32_t* p_temperature_val)
{
	uint8_t data8[2] = {0};
	uint16_t sum = {0};

			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
			HAL_SPI_Receive(&hspi1,data8,2,300);
			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);

			sum=(uint16_t) data8[1] | (uint16_t) data8[0]<< 8 ;
			if(sum & 0x0004)//No TC connected, error -1
			{
				(*p_temperature_val) = -1;
			}
			else
			{
				(*p_temperature_val) = ((sum >> 3) / 4.0);
			}


}


 getTemperatureData(volatile float32_t* p_temperature_val)
 {

	 readTemperatureData(p_temperature_val);

 }


void msTempControlHandler(msTempControlParams* CtrlParams, uint16_t* p_ReflowCurve, ReflowTemplate *p_ReflowParameters )
{


  uint8_t	*p_bank1Percentage	= &CtrlParams->ui8_bank1Percentage;
  uint8_t	*p_bank2Percentage	= &CtrlParams->ui8_bank2Percentage;
  FLAGS		*p_Statusflags		= CtrlParams->p_StatusFlags;
  volatile float32_t *p_temperature = CtrlParams->p_temperature;
  volatile float32_t *p_PIDError 	= CtrlParams->p_PIDError;
  uint16_t ReflowIndex = CtrlParams->u16_ReflowIndexCurrent;
  uint16_t ui16_Bank1Limit;
  uint16_t ui16_Bank2Limit;
  volatile 	float32_t	f32_pid_error;
  static 	volatile  	int32_t	i32_pid_error;
  volatile 	float32_t	f32_Temperature;
  static 	float32_t	f32_PidCorr;
  static	uint32_t	u32_PidCorr;
  volatile 	uint16_t	u16_PIDBank1;
  volatile 	uint16_t 	u16_PIDBank2;


  PID.Kp = p_ReflowParameters->KP;
  PID.Ki = p_ReflowParameters->KI;
  PID.Kd = p_ReflowParameters->KD;
  f32_Temperature = 0;
  u16_PIDBank1 = 0;
  u16_PIDBank2 = 0;
  //f32_PidCorr = 0;
  if( ((*p_bank1Percentage) != 0) &&  ((*p_bank2Percentage) != 0) )
  {
	  ui16_Bank1Limit = 999 * (*p_bank1Percentage) / 100;
	  ui16_Bank2Limit = 999 * (*p_bank2Percentage) / 100;
  }
  else
  {

  }

  /*Temperature Readout*/
  //readTemperatureData(p_temperature);
  if(avg_temp == -100)
  {
	  avg_temp = (*p_temperature);
  }
  else
  {

  }

  avg_temp = alpha * (*p_temperature) + (1 - alpha) * avg_temp;
  (*p_temperature) = avg_temp;
  f32_Temperature = (*p_temperature);

  if(TRUE == StateFlag.StartFlag)
  {
	  f32_pid_error =  (float32_t) *(p_ReflowCurve+ReflowIndex) - f32_Temperature;
	  *p_PIDError = f32_pid_error;
	  *(CtrlParams->p_PIDError) = *(p_PIDError);

	  //Correction
	  f32_PidCorr =  arm_pid_f32(&PID, (f32_pid_error ));
	  u32_PidCorr = (uint32_t)f32_PidCorr;
	  i32_pid_error = (int32_t)((f32_pid_error * 100.00));

	  if( 0 > i32_pid_error )
	  {
		  PID.Ki = 0 ; /*Stop integrating when the setpoint is reached*/
		  PID.state[2] = 0;
		  u32_PidCorr = 0;
	  }
	  else
	  {
		  PID.Ki = p_ReflowParameters->KI;
	  }
	  if( 999 < u32_PidCorr )
	  {
		  PID.Ki = 0 ; /*Stop integrating when the max value is reached*/
		  PID.state[2] = 999;

	  }
	  else{}



	  //Correction limits bank1-set value
	  if (u32_PidCorr > (ui16_Bank1Limit))
	  {
		  u16_PIDBank1 = ui16_Bank1Limit;
	  }
	  else
	  {
		  u16_PIDBank1 = u32_PidCorr;
	  }
	  //Correction limits bank2-set value
	  if(u32_PidCorr > ui16_Bank2Limit)
	  {

		  u16_PIDBank2 = ui16_Bank2Limit;
	  }
	  else
	  {
		  u16_PIDBank2 = u32_PidCorr;
	  }
	  if (0 > u32_PidCorr)
	  {
		  u16_PIDBank1 = 0;
		  u16_PIDBank2 = 0;
	  }
	  else
	  {

	  }

	  TIM3->CCR2 = u16_PIDBank1;
	  TIM3->CCR3 = u16_PIDBank2;

	  if((0 < TIM3->CCR2 ) || (0 < TIM3->CCR3 ))
	  {
		  HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_SET);
	  }
	  else
	  {
		  HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_RESET);
	  }

	  if(	(ReflowIndex >= (PhaseIndex_main[0]+10)	)	&&	(ReflowIndex < PhaseIndex_main[1])	 )
	  {
		  StateFlag.initComplete = TRUE;
		  p_Statusflags->initComplete = StateFlag.initComplete;
		  State = Preheat;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[1])
	  {
		  StateFlag.preheatComplete_1 = TRUE;
		  p_Statusflags->preheatComplete_1 = StateFlag.preheatComplete_1;
		  State = Soak;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[2])
	  {
		  StateFlag.soakComplete = TRUE;
		  p_Statusflags->soakComplete = StateFlag.soakComplete;
		  State = Preheat;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[3])
	  {
		  StateFlag.preheatComplete_2 = TRUE;
		  p_Statusflags->preheatComplete_2 = StateFlag.preheatComplete_2;
		  State = Reflow;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[4])
	  {
		  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
		  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
		  HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_RESET);
		  StateFlag.reflowComplete = TRUE;
		  p_Statusflags->reflowComplete = StateFlag.reflowComplete;
		  State = Cooldown;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if (PhaseIndex_main[5] == ReflowIndex)
	  {
		  StateFlag.cooldownComplete = TRUE;
		  p_Statusflags->cooldownComplete = StateFlag.cooldownComplete;
		  State = Finish;
		  StateFlag.StartFlag = FALSE;
		  p_Statusflags->StartFlag = StateFlag.StartFlag;
		  PIDFlag = 0;

	  }
	  else
	  {
		  //do nothing.
	  }

  }
  else
  {
	  ReflowIndex = 0;
  }
}

void updateGuiVal(msTempControlParams* CtrlParams, ReflowTemplate *p_ReflowParameters, uint16_t *p_PhaseIndex)
{
	volatile float32_t *p_temperature	= CtrlParams->p_temperature;
	volatile float32_t *p_PIDError   	= CtrlParams->p_PIDError;
	volatile float32_t f_PIDError    	= 0;
	uint32_t u32_SoakTemperature     	= p_ReflowParameters->SoakTempeture;
	uint16_t u16_ReflowIndexCurrent  	= CtrlParams->u16_ReflowIndexCurrent;
	uint16_t u16_FirstHeatupTime     	=    p_PhaseIndex[1];
	uint16_t u16_SoakTime   	    	=  ( p_PhaseIndex[2] - p_PhaseIndex[1] );
	uint16_t u16_SecondHeatupTime    	=  ( p_PhaseIndex[3] - p_PhaseIndex[2] );
	uint16_t u16_ReflowTime 	     	=  ( p_PhaseIndex[4] - p_PhaseIndex[3] );
	uint16_t u16_CooldownTime        	=  ( p_PhaseIndex[5] - p_PhaseIndex[4] );
	uint32_t u32_ReflowTemperature   	= p_ReflowParameters->ReflowTempeture;
	uint16_t u16_CooldownTemperature 	= 24;
	bool b_SoakComplete              	= CtrlParams->p_StatusFlags->soakComplete;
	bool b_ReflowComplete            	= CtrlParams->p_StatusFlags->reflowComplete;
	bool b_PreheatComplete_1         	= CtrlParams->p_StatusFlags->preheatComplete_1;
	bool b_PreheatComplete_2         	= CtrlParams->p_StatusFlags->preheatComplete_2;
	bool b_InitComplete              	= CtrlParams->p_StatusFlags->initComplete;
	bool b_CooldownComplete          	= CtrlParams->p_StatusFlags->cooldownComplete;


	lcd_clear_cmd();
	f_PIDError = *p_PIDError;
	f_PIDError = fabsf(f_PIDError);

	/*Show Temperature and Error*/
	f_updateGuiValTempError(p_temperature, f_PIDError);
	/*First Heatup Phase*/
	if( (TRUE == b_InitComplete) && (TRUE != b_PreheatComplete_1) )
	{
		f_updateGuiValGradientSoakParam( u32_SoakTemperature, u16_FirstHeatupTime, u16_ReflowIndexCurrent);
	}
	else{}
	/*SOAK time and Temperature*/
	if( (TRUE == b_PreheatComplete_1) && (TRUE != b_SoakComplete) )
	{
		f_updateGuiValSoakParam(u32_SoakTemperature, u16_FirstHeatupTime, u16_ReflowIndexCurrent, u16_SoakTime);
	}
	else{}
	/*Second Heatup */
	if( (TRUE == b_SoakComplete) && (TRUE != b_PreheatComplete_2) )
	{
		f_updateGuiValGradientReflowParam(u32_ReflowTemperature, u16_FirstHeatupTime, u16_ReflowIndexCurrent, u16_SoakTime, u16_SecondHeatupTime);
	}
	else{}
	/*Reflow  */
	if( (TRUE == b_PreheatComplete_2) && (TRUE != b_ReflowComplete) && (TRUE == b_SoakComplete) )
	{
		f_updateGuiValReflowParam(u32_ReflowTemperature, u16_FirstHeatupTime, u16_ReflowIndexCurrent, u16_SoakTime, u16_SecondHeatupTime, u16_ReflowTime);
	}
	else{}
	/*Cooldown  */
	if( (TRUE == b_ReflowComplete) && (TRUE != b_CooldownComplete) )
	{
		f_updateGuiValCoolDownParam(u16_CooldownTemperature, u16_FirstHeatupTime, u16_ReflowIndexCurrent, u16_SoakTime, u16_SecondHeatupTime, u16_ReflowTime, u16_CooldownTime);
	}
	else{}
	/*Cooldown Complete  */
	if( (TRUE == b_CooldownComplete) )
	{
		f_updateGuiReflowFinished();
	}
	else{}
}
void ResetFlags(void)
{


	  StateFlag.StartFlag = FALSE;
	  StateFlag.cooldownComplete = FALSE;
	  StateFlag.initComplete = FALSE;
	  StateFlag.preheatComplete_1 = FALSE;
	  StateFlag.preheatComplete_2 = FALSE;
	  StateFlag.reflowComplete = FALSE;
	  StateFlag.soakComplete = FALSE;



}


void ReflowAgain(void)
{
	uint16_t u16_Counter = 0;

	lcd_clear_cmd();
	lcd_put_cur(0, 0);
	lcd_send_string("Reflow Again ?");
	lcd_put_cur(1, 0);
	lcd_send_string("Yes/No");
	TIM1->CNT = 10;
	ui8_encButtonPressed = FALSE;
	while(1)
	{
		u16_Counter = TIM1->CNT;

		if((10 < u16_Counter)  )
		{
			TIM1->CNT = 11;
			lcd_put_cur(1, 5);
			lcd_send_cmd(LCD_BLINK_CURSOR_ON);

			if(TRUE == ui8_encButtonPressed)
			{
				lcd_clear_cmd();
				lcd_put_cur(0, 0);
				lcd_send_string("Turn OFF or");
				lcd_put_cur(1, 0);
				lcd_send_string("Restart!");
				lcd_send_cmd(LCD_CURSOR_OFF);
				ui8_encButtonPressed = FALSE;
				HAL_Delay(5000);
				break;
			}

		}
		else if ( (10 > u16_Counter))
		{
			TIM1->CNT = 9;
			lcd_put_cur(1, 0);
			lcd_send_cmd(LCD_BLINK_CURSOR_ON);

			if(TRUE == ui8_encButtonPressed)
			{
				ResetFlags();
				ui8_encButtonPressed = FALSE;
				NVIC_SystemReset(); /*Init a system reset*/
			}
		}

	}

}

void f_GuiErrorCheck(volatile float temperature)
{

	//###################ErrorCheck##########################
	if (-1 == temperature)
	{
		int errorCnt = 0;
		State = Error;

		lcd_put_cur(1, 0);
		lcd_send_string("Sensor Error");
		HAL_Delay(2000);
		lcd_clear_cmd();
		while(1)
		{
			if(0 == errorCnt)
			{
				lcd_put_cur(0, 0);
				lcd_send_string("Reconnect");
				lcd_put_cur(1, 0);
				lcd_send_string("Sensor");
				errorCnt++;
			}
			else
			{

			}
			if (-1 != temperature)
			{
				break;
			}
			else
			{
				//do nothing
			}
		}
	}
}

void f_GuiSensorInitOKmsg(void)
{

	lcd_clear_cmd();
	lcd_put_cur(0, 0);
	lcd_send_string("Initializing...");
	lcd_put_cur(1, 0);
	lcd_send_string("Sensor OK");

}
void f_GuiMenuSoakTemp(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu1##########################
	lcd_clear_cmd();
	TIM1->CNT = (p_ReflowParameters->SoakTempeture) * 4;

	while(1)
	{
		if(1800 < TIM1->CNT)
		{
			TIM1->CNT = 1800;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT/4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter T1[degC]");
		lcd_put_cur(1, 0);
		lcd_send_string("T1=");
		lcd_put_cur(1, 3);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->SoakTempeture = u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
		else
		{

		}
	}
}
void f_GuiFEEUpdateRead(msTempControlParams *p_CtrlParams, ReflowTemplate *p_ReflowParameters)
{
	//###################FEE Read##########################

	HAL_FLASH_Unlock();
	/* Unlock the Flash Program Erase controller */
	/* EEPROM Init */
	if( EE_Init() != EE_OK)
	{
		u32_EEPromErrCnt++;
	}
	else
	{

	}


	if( HAL_ERROR == FEE_ReadCtrlParams( p_CtrlParams, p_ReflowParameters ) )
	{
		p_CtrlParams->ui8_bank1Percentage = 100;
		p_CtrlParams->ui8_bank2Percentage = 100;
		p_ReflowParameters->KP = 200;
		p_ReflowParameters->ReflowTempeture = 250;
		p_ReflowParameters->ReflowTime = 100;
		p_ReflowParameters->SoakTempeture = 110;
		p_ReflowParameters->SoakTime = 150;
		p_ReflowParameters->firstHeatUpRate = 2.0;
		p_ReflowParameters->secondHeatUpRate = 2.0;
		/*FlashWrite*/
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR | FLASH_FLAG_PGPERR);
		FEE_WriteCtrlParams(p_CtrlParams, p_ReflowParameters);
	}
	else
	{

	}

	FLASH_FlushCaches();
	HAL_FLASH_Lock();
}
void f_GuiMenuSoakTime(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu2##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (p_ReflowParameters->SoakTime) * 4;

	while(1)
	{
		if(10000 < TIM1->CNT)
		{
			TIM1->CNT = 10000;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT / 4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter t1 [s]");
		lcd_put_cur(1, 0);
		lcd_send_string("t1=");
		lcd_put_cur(1, 3);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->SoakTime = u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
	}
}
void f_GuiMenuReflowTemp(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu3##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (p_ReflowParameters->ReflowTempeture) * 4;

	while(1)
	{
		if(1800 < TIM1->CNT)
		{
			TIM1->CNT = 1800;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT / 4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter T2[degC]");
		lcd_put_cur(1, 0);
		lcd_send_string("T2=");
		lcd_put_cur(1, 3);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->ReflowTempeture = u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
		else
		{

		}
	}
}
void f_GuiMenuReflowTime(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu4##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (p_ReflowParameters->ReflowTime) * 4;

	while(1)
	{
		if(10000 < TIM1->CNT)
		{
			TIM1->CNT = 10000;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT / 4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter t2 [s]");
		lcd_put_cur(1, 0);
		lcd_send_string("t2=");
		lcd_put_cur(1, 3);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->ReflowTime = u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
		else
		{

		}
	}
}
void f_GuiMenuSoakTempGrad(ReflowTemplate *p_ReflowParameters)
{
	unsigned char 	enc_string[10] = {"    "};
	float			f_hx;

	f_hx = 0.0;
	//###################Menu5##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (uint16_t)(p_ReflowParameters->firstHeatUpRate * 400.00);
	while(1)
	{
		if(1600 < TIM1->CNT)
		{
			TIM1->CNT = 1600;
		}
		else
		{

		}

		f_hx = TIM1->CNT / 400.00;
		sprintf((char*)&enc_string,"%3.2f",f_hx);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter h1[degC/s]");
		lcd_put_cur(1, 0);
		lcd_send_string("h1=");
		lcd_put_cur(1, 4);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->firstHeatUpRate = f_hx;
			ui8_encButtonPressed = FALSE;
			break;
		}
		else
		{

		}
	}
}
void f_GuiMenuKPUpdate(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu6##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (uint16_t)p_ReflowParameters->KP * 4;

	while(1)
	{
		if(8000 < TIM1->CNT)
		{
			TIM1->CNT = 8000;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT / 4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter KP");
		lcd_put_cur(1, 0);
		lcd_send_string("KP=");
		lcd_put_cur(1, 4);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->KP = (float32_t)u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
	}
}
void f_GuiMenuKIUpdate(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu7##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (uint16_t)p_ReflowParameters->KI * 4;

	while(1)
	{
		if(8000 < TIM1->CNT)
		{
			TIM1->CNT = 8000;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT / 4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter KI");
		lcd_put_cur(1, 0);
		lcd_send_string("KI=");
		lcd_put_cur(1, 4);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->KI = (float32_t)u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
	}
}

void f_GuiMenuKDUpdate(ReflowTemplate *p_ReflowParameters)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu8##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (uint16_t)p_ReflowParameters->KD * 4;

	while(1)
	{
		if(8000 < TIM1->CNT)
		{
			TIM1->CNT = 8000;
		}
		else
		{

		}

		u16_encoder_cnt_loc = TIM1->CNT / 4;
		sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Enter KD");
		lcd_put_cur(1, 0);
		lcd_send_string("KD=");
		lcd_put_cur(1, 4);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->KD = (float32_t)u16_encoder_cnt_loc;
			ui8_encButtonPressed = FALSE;
			break;
		}
	}
}


void f_GuiMenuReflowTempGrad(ReflowTemplate *p_ReflowParameters)
{
	unsigned char 	enc_string[10] = {"    "};
	float			f_hx;

	f_hx = 0.0;
	//###################Menu9##########################
	HAL_Delay(100);
	lcd_clear_cmd();
	TIM1->CNT = (uint16_t)(p_ReflowParameters->secondHeatUpRate * 400.00);

	while(1)
	{
		if(1600 < TIM1->CNT)
		{
			TIM1->CNT = 1600;
		}
		else
		{

		}

		f_hx = TIM1->CNT / 400.00;
		sprintf((char*)&enc_string,"%3.2f",f_hx);
		lcd_put_cur(0, 0);
		lcd_send_string("Enter h2[degC/s]");
		lcd_put_cur(1, 0);
		lcd_send_string("h2=");
		lcd_put_cur(1, 4);
		lcd_send_string((char*)&enc_string);
		HAL_Delay(200);

		if(TRUE == ui8_encButtonPressed)
		{
			p_ReflowParameters->secondHeatUpRate = f_hx;
			ui8_encButtonPressed = FALSE;
			break;
		}
		else
		{

		}
	}
}
void f_GuiMenuBank1Update(msTempControlParams *p_CtrlParams)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu10##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT = CtrlParams.ui8_bank1Percentage * 4;

		while(1)
		{
			if(400 < TIM1->CNT)
			{
				TIM1->CNT = 400;
			}
			else
			{

			}

			u16_encoder_cnt_loc = TIM1->CNT/4;
			sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
			lcd_clear_cmd();
			lcd_put_cur(0, 0);
			lcd_send_string("Enter b1[%]");
			lcd_put_cur(1, 0);
			lcd_send_string("b1=");
			lcd_put_cur(1, 4);
			lcd_send_string((char*)&enc_string);
			HAL_Delay(200);

			if(TRUE == ui8_encButtonPressed)
			{
				CtrlParams.ui8_bank1Percentage = u16_encoder_cnt_loc;
				ui8_encButtonPressed = FALSE;
				break;
			}
			else
			{

			}
		}
}
void f_GuiMenuBank2Update(msTempControlParams *p_CtrlParams)
{
	uint16_t		u16_encoder_cnt_loc;
	unsigned char 	enc_string[10] = {"    "};
	u16_encoder_cnt_loc = 0;
	//###################Menu11##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT = CtrlParams.ui8_bank2Percentage * 4;

		while(1)
		{
			if(400 < TIM1->CNT)
			{
				TIM1->CNT = 400;
			}
			else
			{

			}

			u16_encoder_cnt_loc = TIM1->CNT / 4;
			sprintf((char*)&enc_string,"%u",u16_encoder_cnt_loc);
			lcd_clear_cmd();
			lcd_put_cur(0, 0);
			lcd_send_string("Enter b2[%]");
			lcd_put_cur(1, 0);
			lcd_send_string("b2=");
			lcd_put_cur(1, 4);
			lcd_send_string((char*)&enc_string);
			HAL_Delay(200);

			if(TRUE == ui8_encButtonPressed)
			{
				CtrlParams.ui8_bank2Percentage = u16_encoder_cnt_loc;
				ui8_encButtonPressed = FALSE;
				break;
			}
			else
			{

			}
		}
}
void f_GuiFEEUpdateWrite(msTempControlParams *p_CtrlParams, ReflowTemplate *p_ReflowParameters)
{
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR | FLASH_FLAG_PGPERR);
	FEE_WriteCtrlParams(p_CtrlParams, p_ReflowParameters);
	HAL_FLASH_Lock();
	StateFlag.StartFlag = FALSE;
}

void f_updateGuiValTempError(volatile float32_t *p_temperature, volatile float32_t f_PIDError)
{
	unsigned char gui_stringFloat[7] = {"\0"};

	ftoa( (*p_temperature), gui_stringFloat, 2);
	lcd_put_cur(0, 0);
	lcd_send_string("T=");
	lcd_put_cur(0, 2);
	lcd_send_string((char*)&gui_stringFloat);
	ftoa( f_PIDError, gui_stringFloat, 2);
	lcd_put_cur(1, 0);
	lcd_send_string("Td=");
	lcd_put_cur(1,3);
	lcd_send_string((char*)&gui_stringFloat);
}
void f_updateGuiValGradientSoakParam(uint32_t u32_SoakTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent)
{
	uint16_t u16_timeRemaining = 0;
	unsigned char gui_stringInt  [4] = {"\0"};

	u16_timeRemaining = (u16_FirstHeatupTime - (u16_ReflowIndexCurrent)) / 2;

	utoa(u32_SoakTemperature, (char*)gui_stringInt, 10);
	lcd_put_cur(0, 9);
	lcd_send_string("T=");
	lcd_put_cur(0, 11);
	lcd_send_string((char*)&gui_stringInt);

	utoa(u16_timeRemaining, (char*)gui_stringInt, 10);
	lcd_put_cur(1,9);
	lcd_send_string("t=");
	lcd_put_cur(1, 11);
	lcd_send_string((char*)&gui_stringInt);
}
void f_updateGuiValSoakParam(uint32_t u32_SoakTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,uint16_t u16_SoakTime)
{
	uint16_t u16_timeRemaining = 0;
	unsigned char gui_stringInt  [4] = {"\0"};

	u16_timeRemaining =( u16_SoakTime - ( (u16_ReflowIndexCurrent) - u16_FirstHeatupTime )) / 2;

	utoa(u32_SoakTemperature,(char*)gui_stringInt,10);
	lcd_put_cur(0, 9);
	lcd_send_string("T=");
	lcd_put_cur(0, 11);
	lcd_send_string((char*)&gui_stringInt);

	utoa(u16_timeRemaining, (char*)gui_stringInt,10);
	lcd_put_cur(1, 9);
	lcd_send_string("t=");
	lcd_put_cur(1, 11);
	lcd_send_string((char*)&gui_stringInt);
}
void f_updateGuiValGradientReflowParam(uint32_t u32_ReflowTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,
							 uint16_t u16_SoakTime, uint16_t u16_SecondHeatupTime){

	uint16_t u16_timeRemaining = 0;
	unsigned char gui_stringInt  [4] = {"\0"};

	u16_timeRemaining = (u16_SecondHeatupTime - ( (u16_ReflowIndexCurrent) - u16_FirstHeatupTime - u16_SoakTime )) / 2;

	utoa(u32_ReflowTemperature, (char*)gui_stringInt,10);
	lcd_put_cur(0, 9);
	lcd_send_string("T=");
	lcd_put_cur(0, 11);
	lcd_send_string((char*)&gui_stringInt);

	utoa(u16_timeRemaining,(char*)gui_stringInt,10);
	lcd_put_cur(1, 9);
	lcd_send_string("t=");
	lcd_put_cur(1, 11);
	lcd_send_string((char*)&gui_stringInt);
}
void f_updateGuiValReflowParam(uint32_t u32_ReflowTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,
								uint16_t u16_SoakTime, uint16_t u16_SecondHeatupTime, uint16_t u16_ReflowTime){

	uint16_t u16_timeRemaining = 0;
	unsigned char gui_stringInt  [4] = {"\0"};

	u16_timeRemaining = (u16_ReflowTime - ( (u16_ReflowIndexCurrent) - u16_FirstHeatupTime - u16_SoakTime - u16_SecondHeatupTime )) / 2;

	utoa(u32_ReflowTemperature, (char*)gui_stringInt,10);
	lcd_put_cur(0, 9);
	lcd_send_string("T=");
	lcd_put_cur(0, 11);
	lcd_send_string((char*)&gui_stringInt);

	utoa(u16_timeRemaining, (char*)gui_stringInt,10);
	lcd_put_cur(1, 9);
	lcd_send_string("t=");
	lcd_put_cur(1, 11);
	lcd_send_string((char*)&gui_stringInt);
}
void f_updateGuiValCoolDownParam(uint32_t u16_CooldownTemperature, uint32_t u16_FirstHeatupTime, uint16_t u16_ReflowIndexCurrent,
								uint16_t u16_SoakTime, uint16_t u16_SecondHeatupTime, uint16_t u16_ReflowTime, uint16_t u16_CooldownTime){
	uint16_t u16_timeRemaining = 0;
	unsigned char gui_stringInt  [4] = {"\0"};

	u16_timeRemaining = (u16_CooldownTime - ( (u16_ReflowIndexCurrent)  - u16_FirstHeatupTime - u16_SoakTime - u16_SecondHeatupTime - u16_ReflowTime )) / 2;

	utoa(u16_CooldownTemperature, (char*)gui_stringInt,10);
	lcd_put_cur(0, 9);
	lcd_send_string("T=");
	lcd_put_cur(0, 11);
	lcd_send_string((char*)&gui_stringInt);

	utoa(u16_timeRemaining, (char*)gui_stringInt,10);
	lcd_put_cur(1, 9);
	lcd_send_string("t=");
	lcd_put_cur(1, 11);
	lcd_send_string((char*)&gui_stringInt);
}
void f_updateGuiReflowFinished(void)
{
	lcd_clear_cmd();
	lcd_put_cur(0, 0);
	lcd_send_string("Reflow");
	lcd_put_cur(1, 0);
	lcd_send_string("Finished!");
	while(1)
	{
		if(TRUE == ui8_encButtonPressed)
		{

			ui8_encButtonPressed = FALSE;
			break;
		}
	}
}
