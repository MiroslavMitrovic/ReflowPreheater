/*
 * Reflow_functions.c
 *
 *  Created on: 18 Sep 2021
 *      Author: mmitr
 */
#include "Reflow_functions.h"
#include "FLASH_SECTOR.h"
#include "main.h"
#include "variables.h"
#include "i2c-lcd.h"
#include "string.h"
#include "eeprom.h"
#include "stdlib.h"
#include <stdio.h>
#include <math.h>
volatile uint16_t PIDBank1;
volatile uint16_t PIDBank2;
volatile float32_t pid_error;
volatile uint32_t PidKorekcija;
float32_t PidCorr;
uint32_t PidCorrLim;
const float  alpha=0.1;
static float avg_temp=-100;
uint16_t ReflowIndex=0;
uint8_t ReflowEnable;

char ConsoleMSG[20];
FLAGS Flags;
uint8_t State;
uint8_t FlagBank1;
uint8_t FlagBank2;
uint8_t ui8_bank1Percentage;
uint8_t ui8_bank2Percentage;
volatile uint8_t ui8_encButtonPressed;

uint32_t interruptCnt=0;
extern uint8_t PIDFlag;
uint16_t counterBank1;
uint16_t counterBank2;
arm_pid_instance_f32 PID;
msTempControlParams CtrlParams;
uint32_t u32_EEPromErrCnt;

// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
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

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
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
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}




void calculateReflowCurve(ReflowTemplate *p_ReflowParameters, uint16_t *p_ReflowCurve, uint16_t *p_PhaseIndex){

	static uint16_t PhaseIndex[6];
	static uint16_t ReflowCurve[15000];
	size_t s_ReflowCurve;
	size_t s_PhaseIndex;
	int index;

	index=0;
	s_ReflowCurve=0;
	s_PhaseIndex=0;

	float timestep = 0.5;
	for(int i =0;i<4000;i++){
		ReflowCurve[i]=0;

		if(5>i)
		{
		PhaseIndex[i]=0;
		}
		else
		{

		}
	}


	//First Heat Up:
	while (24 + timestep * p_ReflowParameters->firstHeatUpRate <= p_ReflowParameters->SoakTempeture) {
	ReflowCurve[index] = 24 + timestep * p_ReflowParameters->firstHeatUpRate;
	index++;
	timestep = timestep + 0.5;
	}
	PhaseIndex[1]=index;

	//Soak
	int Soakduration = 2*p_ReflowParameters->SoakTime;

	for(int i=0;i<Soakduration;i++){
		ReflowCurve[index+i]=p_ReflowParameters->SoakTempeture;
	}


	//Second Heat Up:
	index = index + Soakduration;
	PhaseIndex[2]=index;
	timestep = 0.5;
	while (p_ReflowParameters->SoakTempeture + timestep * p_ReflowParameters->secondHeatUpRate <= p_ReflowParameters->ReflowTempeture) {
	ReflowCurve[index] = p_ReflowParameters->SoakTempeture + (uint8_t)timestep * p_ReflowParameters->secondHeatUpRate;
	index++;
	timestep = timestep + 0.5;
	}
	PhaseIndex[3]=index;

	//Reflow
	int Reflowduration = 2*p_ReflowParameters->ReflowTime;

	for(int i=0;i<Reflowduration;i++){
		ReflowCurve[index+i]=p_ReflowParameters->ReflowTempeture;
	}

	index = index + Reflowduration;
	ReflowCurve[index]=0;
	PhaseIndex[4]=index;

	//Cooldown
	timestep = 0.5;
	while (p_ReflowParameters->ReflowTempeture - timestep * 1.8 >= 24) {
	ReflowCurve[index] = p_ReflowParameters->ReflowTempeture - timestep * 1.8;
	index++;
	timestep = timestep + 0.5;
	PhaseIndex[5]=index;
	}
	s_ReflowCurve = sizeof(ReflowCurve);
	s_PhaseIndex  = sizeof(PhaseIndex);

	if(0<s_ReflowCurve || 0< s_PhaseIndex)
	{
		//custom_memcpy(p_PhaseIndex,&PhaseIndex,s_PhaseIndex);
		memcpy((uint8_t*)p_PhaseIndex,(uint8_t*)PhaseIndex,s_PhaseIndex);
		memcpy((uint8_t*)p_ReflowCurve,(uint8_t*)ReflowCurve,s_ReflowCurve);

	}
	else
	{
		while(1);
	}

}

void HandleGui(){
	//###################ErrorCheck##########################

uint32_t	u32_encoder_cnt_loc;
float		f_hx;
unsigned char enc_string[10] = {"    "};
static uint8_t State_gui	 = MaxNumberofS_x_States;

/*TODO SORT THE WRITE STRING TO CLEAR AFTER EVERY WRITE*/

	u32_encoder_cnt_loc=0;

	lcd_clear_cmd();

	if (-1==temperature)
	{
		int errorCnt=0;
		State=Error;

		lcd_put_cur(1, 0);
		lcd_send_string("Sensor Error");
		HAL_Delay(2000);
		lcd_clear_cmd();
		while(1)
		{
			if(0==errorCnt)
			{

			lcd_put_cur(0, 0);
			lcd_send_string("Recconnect");
			lcd_put_cur(1, 0);
			lcd_send_string("Sensor");
			errorCnt++;
			}
			if (-1!=temperature)
			{
				break;
			}
			else
			{

			}
			//HAL_Delay(200);
		}
	}
	else
	{
		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Initializing...");
		lcd_put_cur(1, 0);
		lcd_send_string("Sensor OK");
		//do nothing
	}

	//###################Menu1##########################
//	//FEE_Init();
//	  FLASH_EraseInitTypeDef EraseInitStruct;
//	  //EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
//	  //FLASH_TYPEERASE_SECTORS
//	  EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
//	  EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
//	  EraseInitStruct.Sector = 9;
//	  EraseInitStruct.NbSectors = 2;
//	  uint32_t SectorError2;
//	  volatile HAL_StatusTypeDef status_erase2;
//
//
//
//	  status_erase2 = HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError2);
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


	if( HAL_ERROR == FEE_ReadCtrlParams( &CtrlParams, p_ReflowParameters ) )
	{
		CtrlParams.ui8_bank1Percentage=100;
		CtrlParams.ui8_bank2Percentage=100;
		p_ReflowParameters->KP=200;
		p_ReflowParameters->ReflowTempeture=250;
		p_ReflowParameters->ReflowTime=100;
		p_ReflowParameters->SoakTempeture=110;
		p_ReflowParameters->SoakTime=150;
		p_ReflowParameters->firstHeatUpRate=2.0;
		p_ReflowParameters->secondHeatUpRate=2.0;
		/*FlashWrite*/
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR | FLASH_FLAG_PGPERR);
		FEE_WriteCtrlParams(&CtrlParams,p_ReflowParameters);




	}
	else
	{
//		uint32_t u32_feeCounter=0;
//		while(1)
//				{
//
//				u32_feeCounter++;
//					if(2500 == u32_feeCounter)
//					{
//						u32_feeCounter=0;
//						break;
//					}
//					else
//					{}
//				}
	}

	FLASH_FlushCaches();
	HAL_FLASH_Lock();
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
		u32_encoder_cnt_loc = TIM1->CNT/4;



//		if( 999 == u32_encoder_cnt_loc )
//		{
//			State_gui = s_1000;
//		}
//
//		if(99 == u32_encoder_cnt_loc )
//		{
//			State_gui = s_100;
//		}
//
//		if(9 == u32_encoder_cnt_loc )
//		{
//			State_gui = s_10;
//		}
//
//		if ( (1000 >= u32_encoder_cnt_loc) && (s_1000 == State_gui ) )
//		{
//			lcd_clear_cmd();
//			State_gui = MaxNumberofS_x_States;
//		}
//		if ( (100 >= u32_encoder_cnt_loc) && (s_100 == State_gui ) )
//		{
//			lcd_clear_cmd();
//			State_gui = MaxNumberofS_x_States;
//		}
//		if ( (10 >= u32_encoder_cnt_loc) && (s_10 == State_gui ) )
//		{
//			lcd_clear_cmd();
//			State_gui = MaxNumberofS_x_States;
//		}


		sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
		lcd_clear_cmd();

		lcd_put_cur(0, 0);

		lcd_send_string("Enter T1[degC]");

		lcd_put_cur(1, 0);

		lcd_send_string("T1=");

		lcd_put_cur(1, 3);

		lcd_send_string(&enc_string);
		HAL_Delay(200);

		if(true==ui8_encButtonPressed)
		{

			p_ReflowParameters->SoakTempeture=u32_encoder_cnt_loc;
			 ui8_encButtonPressed=false;
			break;
		}

	}
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
		u32_encoder_cnt_loc=TIM1->CNT/4;

		sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
		lcd_clear_cmd();

		lcd_put_cur(0, 0);

		lcd_send_string("Enter t1 [s]");

		lcd_put_cur(1, 0);

		lcd_send_string("t1=");

		lcd_put_cur(1, 3);

		lcd_send_string(&enc_string);
		HAL_Delay(200);

		if(true == ui8_encButtonPressed)
		{

			p_ReflowParameters->SoakTime = u32_encoder_cnt_loc;
			ui8_encButtonPressed = false;
			break;
		}

	}
	//###################Menu3##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT = (p_ReflowParameters->ReflowTempeture) * 4;
		while(1)
		{


			if(1800<TIM1->CNT)
			{
				TIM1->CNT=1800;
			}
			else
			{

			}
			u32_encoder_cnt_loc=TIM1->CNT/4;
			sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
			lcd_clear_cmd();

			lcd_put_cur(0, 0);

			lcd_send_string("Enter T2[degC]");

			lcd_put_cur(1, 0);

			lcd_send_string("T2=");

			lcd_put_cur(1, 3);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				p_ReflowParameters->ReflowTempeture=u32_encoder_cnt_loc;
				ui8_encButtonPressed=false;
				break;
			}

		}
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
			u32_encoder_cnt_loc=TIM1->CNT/4;
			sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
			lcd_clear_cmd();

			lcd_put_cur(0, 0);

			lcd_send_string("Enter t2 [s]");

			lcd_put_cur(1, 0);

			lcd_send_string("t2=");

			lcd_put_cur(1, 3);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				p_ReflowParameters->ReflowTime=u32_encoder_cnt_loc;
				ui8_encButtonPressed=false;
				break;
			}

		}
		//###################Menu5##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT=(uint16_t)(p_ReflowParameters->firstHeatUpRate * 400.00);
		while(1)
		{


			if(1600<TIM1->CNT)
			{
				TIM1->CNT=1600;

			}
			else
			{

			}
			f_hx=TIM1->CNT/400.00;
			sprintf(&enc_string,"%3.2f",f_hx);
			lcd_clear_cmd();

			lcd_put_cur(0, 0);

			lcd_send_string("Enter h1[degC/s]");

			lcd_put_cur(1, 0);

			lcd_send_string("h1=");

			lcd_put_cur(1, 4);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				p_ReflowParameters->firstHeatUpRate=f_hx;
				ui8_encButtonPressed=false;
				break;
			}

		}
		//###################Menu6##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT=(uint16_t)(p_ReflowParameters->secondHeatUpRate * 400.00);
		while(1)
		{

			if(1600<TIM1->CNT)
			{
				TIM1->CNT=1600;

			}
			else
			{

			}
			f_hx=TIM1->CNT/400.00;
			sprintf(&enc_string,"%3.2f",f_hx);

			lcd_put_cur(0, 0);

			lcd_send_string("Enter h2[degC/s]");

			lcd_put_cur(1, 0);

			lcd_send_string("h2=");

			lcd_put_cur(1, 4);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				p_ReflowParameters->secondHeatUpRate=f_hx;
				ui8_encButtonPressed=false;
				break;
			}

		}

		//###################Menu6##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT=(uint16_t)p_ReflowParameters->KP *4;
		while(1)
		{


			if(8000<TIM1->CNT)
			{
				TIM1->CNT=8000;
			}
			else
			{

			}
			u32_encoder_cnt_loc=TIM1->CNT/4;
			sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
			lcd_clear_cmd();

			lcd_put_cur(0, 0);

			lcd_send_string("Enter KP");

			lcd_put_cur(1, 0);

			lcd_send_string("KP=");

			lcd_put_cur(1, 4);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				p_ReflowParameters->KP=(float32_t)u32_encoder_cnt_loc;
				ui8_encButtonPressed=false;
				break;
			}

		}

		//###################Menu7##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT = CtrlParams.ui8_bank1Percentage * 4;
		while(1)
		{


			if(400<TIM1->CNT)
			{
				TIM1->CNT=400;

			}
			else
			{

			}
			u32_encoder_cnt_loc=TIM1->CNT/4;
			sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
			lcd_clear_cmd();

			lcd_put_cur(0, 0);

			lcd_send_string("Enter b1[%]");

			lcd_put_cur(1, 0);

			lcd_send_string("b1=");

			lcd_put_cur(1, 4);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				CtrlParams.ui8_bank1Percentage=u32_encoder_cnt_loc;
				ui8_encButtonPressed=false;
				break;
			}

		}
		//###################Menu8##########################
		HAL_Delay(100);
		lcd_clear_cmd();
		TIM1->CNT = CtrlParams.ui8_bank2Percentage * 4;
		while(1)
		{

			if(400<TIM1->CNT)
			{
				TIM1->CNT=400;

			}
			else
			{

			}
			u32_encoder_cnt_loc=TIM1->CNT/4;
			sprintf(&enc_string,"%u",u32_encoder_cnt_loc);
			lcd_clear_cmd();

			lcd_put_cur(0, 0);

			lcd_send_string("Enter b2[%]");

			lcd_put_cur(1, 0);

			lcd_send_string("b2=");

			lcd_put_cur(1, 4);

			lcd_send_string(&enc_string);
			HAL_Delay(200);

			if(true==ui8_encButtonPressed)
			{

				CtrlParams.ui8_bank2Percentage=u32_encoder_cnt_loc;
				ui8_encButtonPressed=false;
				break;
			}

		}


		HAL_FLASH_Unlock();
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR | FLASH_FLAG_PGPERR);
		FEE_WriteCtrlParams(&CtrlParams,p_ReflowParameters);

		HAL_FLASH_Lock();



		Flags.StartFlag=true;


}

void readTemperatureData(volatile float* temperature_val)
{

			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
			uint8_t data8[2]={0};
			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_RESET);
			HAL_SPI_Receive(&hspi1,data8,2,300);
			HAL_GPIO_WritePin(SPI1_CS_GPIO_Port,SPI1_CS_Pin,GPIO_PIN_SET);
			uint16_t sum={0};
			sum=(uint16_t) data8[1] | (uint16_t) data8[0]<< 8 ;
			if(sum &	0x0004)//No TC connected, error -1
			{
				(*temperature_val)=-1;
			}
			else
			{
				(*temperature_val)=((sum>>3)/4.0);
			}


}

void msTempControlHandler(msTempControlParams* CtrlParams, uint16_t* p_ReflowCurve, ReflowTemplate *p_ReflowParameters )
{


  uint8_t *p_bank1Percentage = &CtrlParams->ui8_bank1Percentage;
  uint8_t *p_bank2Percentage = &CtrlParams->ui8_bank2Percentage;
  volatile float *p_temperature = CtrlParams->p_temperature;
  volatile float *p_PIDError = CtrlParams->p_PIDError;
  uint16_t ui16_Bank1Limit;
  uint16_t ui16_Bank2Limit;
  uint16_t ReflowIndex = CtrlParams->u16_ReflowIndexCurrent;
  volatile float pid_error;
  static float32_t f32_PidCorr;
  static uint32_t u32_PidCorr;
  PID.Kp = p_ReflowParameters->KP;
  PID.Ki = p_ReflowParameters->Ki;
  PID.Kd = p_ReflowParameters->KD;
/*TODO modify temperature reading and PID ctrl in same time period*/
  if( ((*p_bank1Percentage) != 0) &&  ((*p_bank2Percentage) != 0) )
  {
	  ui16_Bank1Limit = 999 * (*p_bank1Percentage) / 100;
	  ui16_Bank2Limit = 999 * (*p_bank2Percentage) / 100;
  }
  else
  {

  }


  /*Temperature Readout*/
  readTemperatureData(p_temperature);
  if(avg_temp ==-100)
  {
	  avg_temp = (*p_temperature);
  }
  else
  {

  }
  avg_temp = alpha * (*p_temperature) + (1 - alpha) * avg_temp;
  (*p_temperature) = avg_temp;


  if(1 == ReflowEnable)
  {

	  //TODO need to perform modification of PID controller in order to get half power
	  //Error
	  //pid_error =temperature  -(float32_t)ReflowCurve[ReflowIndex];
	  //Error for power limitation
	  pid_error = (float32_t) *(p_ReflowCurve+ReflowIndex)-temperature;
	  *p_PIDError = pid_error;
	  *(CtrlParams->p_PIDError) = *(p_PIDError);
	  //Correction
	  f32_PidCorr = arm_pid_f32(&PID, pid_error);
	  u32_PidCorr = (uint32_t)f32_PidCorr;
	  //Correction limits bank1-set value
	  if (u32_PidCorr > (ui16_Bank1Limit))
	  {
		  PIDBank1 = ui16_Bank1Limit;
	  }
	  else
	  {
		  PIDBank1 = u32_PidCorr;
	  }
	  //Correction limits bank2-set value
	  if(u32_PidCorr > ui16_Bank2Limit)
	  {
		  PIDBank2 = ui16_Bank2Limit;
	  }
	  else
	  {
		  PIDBank2 = u32_PidCorr;
	  }
	  if (u32_PidCorr < 0)
	  {
		  PIDBank1 = 0;
		  PIDBank2 = 0;
	  }
	  else
	  {

	  }
	  //				if( (0<=PidCorrLim) && (450>=PidCorrLim)	)
	  //				{
	  //					PIDBank1 = PidCorrLim;
	  //					PIDBank2 = PidCorrLim;
	  //				}
	  //				else
	  //				{
	  //
	  //				}
	  //				if( (0<=PidCorrLim) && (750>=PidCorrLim)	)
	  //				{
	  //					PIDBank1 = PidCorrLim;
	  //				}
	  //				else
	  //				{
	  //
	  //				}
	  //P Control without power limitation
	  //TIM3->CCR2=999-PIDBank1;
	  //TIM3->CCR3=450-PIDBank2;
	  //P Control with power limitation
	  TIM3->CCR2 = PIDBank1;
	  TIM3->CCR3 = PIDBank2;
	  if((TIM3->CCR2>0) || (TIM3->CCR3>0))
	  {
		  HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_SET);
	  }
	  else
	  {
		  HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_RESET);
	  }

	  if(	(ReflowIndex >= (PhaseIndex_main[0]+10)	)	&&	(ReflowIndex < PhaseIndex_main[1])	 )
	  {
		  //sprintf(ConsoleMSG,"HEAT UP");
		  Flags.initComplete = TRUE;
		  State = Preheat;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[1])
	  {
		  //sprintf(ConsoleMSG,"SOAK");
		  Flags.preheatComplete_1 = TRUE;
		  State = Soak;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[2])
	  {
		  //sprintf(ConsoleMSG,"HEAT UP");

		  Flags.soakComplete = TRUE;
		  State = Preheat;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if(ReflowIndex == PhaseIndex_main[3])
	  {
		  //sprintf(ConsoleMSG,"REFLOW");
		  Flags.preheatComplete_2 = TRUE;
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
		  //sprintf(ConsoleMSG,"COOL DOWN");
		  Flags.reflowComplete = TRUE;
		  State = Cooldown;
	  }
	  else
	  {
		  //do nothing.
	  }
	  if (PhaseIndex_main[5] == ReflowIndex)
	  {
		  //sprintf(ConsoleMSG,"FINISHED");
		  Flags.cooldownComplete = TRUE;
		  State = Finish;
		  ReflowEnable = 0;
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
///@startuml
/// Alice -> BOB : HELLO
/// BOB --> Alice : World
///@enduml
//
void updateGuiVal(msTempControlParams* CtrlParams, ReflowTemplate *p_ReflowParameters, uint16_t *p_PhaseIndex)
{
	unsigned char gui_stringFloat[7] = {"\0"};
	unsigned char gui_stringInt  [4] = {"\0"};
	unsigned char gui_stringTime[10] = {"\0"};
	static uint8_t u8_ClearLCDFlag = 0;

	volatile float32_t *p_temperature    = CtrlParams->p_temperature;
	volatile float32_t *p_PIDError       = CtrlParams->p_PIDError;
	volatile float32_t f_PIDError    = 0;
	uint32_t u32_SoakTemperature     = p_ReflowParameters->SoakTempeture;
	uint16_t u16_ReflowIndexCurrent  = CtrlParams->u16_ReflowIndexCurrent;
	uint16_t u16_FirstHeatupTime     =    p_PhaseIndex[1] / 2;
	uint16_t u16_SoakTime   	     =  ( p_PhaseIndex[2] - p_PhaseIndex[1] ) /2;
	uint16_t u16_SecondHeatupTime    =  ( p_PhaseIndex[3] - p_PhaseIndex[2] ) /2;
	uint16_t u16_ReflowTime 	     =  ( p_PhaseIndex[4] - p_PhaseIndex[3] ) /2;
	uint16_t u16_CooldownTime        =  ( p_PhaseIndex[5] - p_PhaseIndex[4] ) /2;
	uint32_t u32_ReflowTemperature   = p_ReflowParameters->ReflowTempeture;
	uint16_t u16_CooldownTemperature = 24;
	static uint16_t u16_timeRemaining = 0;
	bool b_SoakComplete              = CtrlParams->p_StatusFlags->soakComplete;
	bool b_ReflowComplete            = CtrlParams->p_StatusFlags->reflowComplete;
	bool b_PreheatComplete_1         = CtrlParams->p_StatusFlags->preheatComplete_1;
	bool b_PreheatComplete_2         = CtrlParams->p_StatusFlags->preheatComplete_2;
	bool b_InitComplete              = CtrlParams->p_StatusFlags->initComplete;
	bool b_CooldownComplete          = CtrlParams->p_StatusFlags->cooldownComplete;
	static uint8_t State			 = s_1000;
	/*TODO add clear buffer and lcd clear commands */
#warning "add the condition to clear lcd when it is in cooldown phase"
#warning "solve Td write float negative values"

	lcd_clear_cmd();



	f_PIDError = *p_PIDError;
	if(0 > f_PIDError)
	{
		f_PIDError = f_PIDError *(-1);
	}
	else
	{

	}

	ftoa( (*p_temperature), gui_stringFloat, 2);



	lcd_put_cur(0, 0);

	lcd_send_string("T=");

	lcd_put_cur(0, 2);

	lcd_send_string(&gui_stringFloat);

	ftoa( f_PIDError, gui_stringFloat, 2);

	lcd_put_cur(1, 0);

	lcd_send_string("Td=");

	lcd_put_cur(1,3);

	lcd_send_string(&gui_stringFloat);


	/*First Heatup Phase*/
	if( (true == b_InitComplete) && (true != b_PreheatComplete_1) )
	{



		u16_timeRemaining = u16_FirstHeatupTime - (u16_ReflowIndexCurrent/2);





		utoa(u32_SoakTemperature,gui_stringInt,10);

		lcd_put_cur(0, 9);
		lcd_send_string("T=");
		lcd_put_cur(0, 11);
		lcd_send_string(&gui_stringInt);

		utoa(u16_timeRemaining,gui_stringInt,10);
		lcd_put_cur(1,9);
		lcd_send_string("t=");
		lcd_put_cur(1, 11);
		lcd_send_string(&gui_stringInt);


	}

	/*SOAK time and Temperature*/
	if( (true == b_PreheatComplete_1) && (true != b_SoakComplete) )
	{

		u16_timeRemaining = u16_SoakTime - ( (u16_ReflowIndexCurrent/2) - u16_FirstHeatupTime );





		utoa(u32_SoakTemperature,gui_stringInt,10);
		lcd_put_cur(0, 9);
		lcd_send_string("T=");
		lcd_put_cur(0, 11);
		lcd_send_string(&gui_stringInt);

		utoa(u16_timeRemaining,gui_stringInt,10);
		lcd_put_cur(1, 9);
		lcd_send_string("t=");
		lcd_put_cur(1, 11);
		lcd_send_string(&gui_stringInt);
	}



	/*Second Heatup */
	if( (true == b_SoakComplete) && (true != b_PreheatComplete_2) )
	{

		u16_timeRemaining = u16_SecondHeatupTime - ( (u16_ReflowIndexCurrent/2) - u16_FirstHeatupTime - u16_SoakTime );


		utoa(u32_ReflowTemperature,gui_stringInt,10);
		lcd_put_cur(0, 9);
		lcd_send_string("T=");
		lcd_put_cur(0, 11);
		lcd_send_string(&gui_stringInt);

		utoa(u16_timeRemaining,gui_stringInt,10);
		lcd_put_cur(1, 9);
		lcd_send_string("t=");
		lcd_put_cur(1, 11);
		lcd_send_string(&gui_stringInt);

	}



	/*Reflow  */
	if( (true == b_PreheatComplete_2) && (true != b_ReflowComplete) && (true == b_SoakComplete) )
	{

		u16_timeRemaining = u16_ReflowTime - ( (u16_ReflowIndexCurrent/2) - u16_FirstHeatupTime - u16_SoakTime - u16_SecondHeatupTime );


		utoa(u32_ReflowTemperature,gui_stringInt,10);
		lcd_put_cur(0, 9);
		lcd_send_string("T=");
		lcd_put_cur(0, 11);
		lcd_send_string(&gui_stringInt);

		utoa(u16_timeRemaining,gui_stringInt,10);
		lcd_put_cur(1, 9);
		lcd_send_string("t=");
		lcd_put_cur(1, 11);
		lcd_send_string(&gui_stringInt);
	}



	/*Cooldown  */
	if( (true == b_ReflowComplete) && (true != b_CooldownComplete) )
	{


		u16_timeRemaining = u16_CooldownTime - ( (u16_ReflowIndexCurrent/2) - u16_FirstHeatupTime - u16_SoakTime - u16_SecondHeatupTime - u16_ReflowTime );



		utoa(u16_CooldownTemperature,gui_stringInt,10);
		lcd_put_cur(0, 9);
		lcd_send_string("T=");
		lcd_put_cur(0, 11);
		lcd_send_string(&gui_stringInt);

		utoa(u16_timeRemaining,gui_stringInt,10);
		lcd_put_cur(1, 9);
		lcd_send_string("t=");
		lcd_put_cur(1, 11);
		lcd_send_string(&gui_stringInt);



	}

	/*Cooldown  */
	if( (true == b_CooldownComplete) )
	{

		lcd_clear_cmd();
		lcd_put_cur(0, 0);
		lcd_send_string("Reflow");
		lcd_put_cur(1, 0);
		lcd_send_string("Finished!");
		while(1)
		{
			if(true == ui8_encButtonPressed)
			{

				ui8_encButtonPressed=false;
				break;
			}
		}
	}



}
void ResetFlags(void)
{

	  ReflowEnable = 1;

	  Flags.StartFlag = false;
	  Flags.cooldownComplete = false;
	  Flags.initComplete = false;
	  Flags.preheatComplete_1 = false;
	  Flags.preheatComplete_2 = false;
	  Flags.reflowComplete = false;
	  Flags.soakComplete = false;
	  b_dataEnter = false;


}

void RefloWConditionsUpdate(void)
{
	uint16_t u16_Counter = 0;




	lcd_clear_cmd();
	lcd_put_cur(0, 0);
	lcd_send_string("Reflow Again ?");
	lcd_put_cur(1, 0);
	lcd_send_string("Yes/No");


	 TIM1->CNT = 10;

	while(1)
		{
		u16_Counter = TIM1->CNT;

		if((10 < u16_Counter)  )
		{
			lcd_put_cur(1, 5);
			lcd_send_cmd(LCD_BLINK_CURSOR_ON);
			while(1)
			{
				if(true == ui8_encButtonPressed)
				{
					lcd_clear_cmd();
					lcd_put_cur(0, 0);
					lcd_send_string("Turn OFF or");
					lcd_put_cur(1, 0);
					lcd_send_string("Restart!");
					lcd_send_cmd(LCD_CURSOR_OFF);

					ui8_encButtonPressed = false;
					break;
				}
			}
			break;
		}
		else if ( (10 > u16_Counter))
		{
			lcd_put_cur(1, 0);
			lcd_send_cmd(LCD_BLINK_CURSOR_ON);
			while(1)
			{
				if(true == ui8_encButtonPressed)
				{
					ResetFlags();
					ui8_encButtonPressed = false;
					NVIC_SystemReset(); /*Init a system reset*/

					break;

				}

			}
		}

		}

}




void SwitchDebouncing(void)
{
//  //RedButton Pressed
//  if(false==redButtonPressedStat)
//  {
//  	if(__HAL_GPIO_EXTI_GET_FLAG(RedButton_Pin))
//  	{
//
//  		redButtonPressed++;
//  		redButtonPressedStat=true;
//
//  	}
//  	else
//  	{
//  		redButtonPressedStat=false;
//  	}
//
//  }
//  else
//  {
//
//  }
//TODO make this as a function in funtions_ReflowPreheater.h
//  //Da bi timer ovako radio htim2.Init.Period mora biti veci od 0!
//  	  	 static unsigned long counterTIM2=0;
//  	  	 static unsigned  debounceCntRed=0;
//  	  	 static unsigned  debounceCntGreen=0;
//
//  	  	 count_TIM2++;
//
//  	  	 //ispod je debouncing funkcionalnost iskoriscena pomocu timera od 1ms
//
////red button
//     	if(false==redButtonPressedStatDeb)
//     	{
//  	  	 if(true==redButtonPressedStat)
//     		{
//  	  		  debounceCntRed++;
//     		if(DEBOUNCING_TIME_MS<debounceCntRed)
//     			{
//     				redButtonPressedStatDeb=true;
//     				debounceCntRed=0;
//
//     			}
//     			else
//     			{
//     				//do nothing
//     			}
//     		}
//     	}
//     	else
//     	{
//     			//do nothing
//     	}
//     	if(true==redButtonPressedStatDeb)
//     	{
//			 if(!(HAL_GPIO_ReadPin(RedButton_GPIO_Port, RedButton_Pin)))
//			{
//				 redButtonPressedStat=false;
//				 redButtonPressedStatDeb=false;
//			}
//			 else
//			 {
//				 //do nothing
//			 }
//     	}
// //green button
//     	if(false==greenButtonPressedStatDeb)
//     	{
//     		if(true==greenButtonPressedStat)
//     		{
//     			debounceCntGreen++;
//     			if(DEBOUNCING_TIME_MS<debounceCntGreen)
//     			{
//     				greenButtonPressedStatDeb=true;
//     				debounceCntGreen=0;
//     			}
//     			else
//     			{
//     					//do nothing
//     			}
//     		}
//     		else
//     		{
//     			 //do nothing
//     		}
//     	}
//     	else
//     	{
//     		//do nothing
//     	}
//
//     		if(true==greenButtonPressedStatDeb)
//     		{
//				if(!(HAL_GPIO_ReadPin(GreenButton_GPIO_Port, GreenButton_Pin)))
//				{
//					greenButtonPressedStat=false;
//					greenButtonPressedStatDeb=false;
//				}
//				else
//				{
//					//do nothing
//				}
//     		}
//     		else
//     		{
//     			//do nothing
//     		}
//
}
void custom_memcpy(void *dest, void *src, size_t n)
{
   int i,value_src,value_dest;
   //cast src and dest to char*
   char *src_char = (char *)src;
   value_src=*src_char;
   char *dest_char = (char *)dest;
   value_dest=*dest_char;
   for (i=0; i<n; i++)
      dest_char[i] = src_char[i]; //copy contents byte by byte
}
