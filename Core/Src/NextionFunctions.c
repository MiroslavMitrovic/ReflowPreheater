/*
 * NextionFunctions.c
 *
 *  Created on: 7 Apr 2021
 *      Author: mmitr
 */
#include "main.h"
#include "stm32f4xx_it.h"
#include "NextionLib.h"
#include "Pid.h"
#include"FLASH_SECTOR.h"
#include <stdlib.h>
#include "string.h"
#include "functions.h"
#define ARM_MATH_CM4
#include "arm_math.h"
#include <stdio.h>
#include <stdbool.h>
UART_HandleTypeDef huart1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim6;
uint8_t ReflowEnable = 0;
extern uint16_t ReflowIndex;
float32_t debug = 0;
uint8_t Cmd_End[3]={0xFF, 0xFF, 0xFF};
uint8_t UART_Recieved_Data[5]={'p','0','x','x','x'};
uint8_t UART_Recieved_Flag = 0;
char input[20];
uint16_t PhaseIndex[6]={0};
char ConsoleMSG[20];
ReflowTemplate ReflowParameters;
ReflowTemplate ReflowParametersRead;
volatile float temperature=0.0;
arm_pid_instance_f32 PID;
bool flagMiki;
uint8_t data[2];
extern uint8_t ReflowCurve[4000];
float duty;
uint32_t data_flash[] = {400, 200, 0, 50, 900, 2};
uint8_t State;
FLAGS Flags;
uint8_t PIDFlag;



void SaveParameters(){
	Flash_Write_Data(0x080A0000, &ReflowParameters);
}
void LoadParameters(){
	Flash_Read_Data(0x080A0000, &ReflowParameters);
}





void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Receive_IT(&huart1, UART_Recieved_Data, 5);
	UART_Recieved_Flag =1;
}

void NEXTION_SendString (char *ID, char *string){
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%s\"", ID, string);
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);

}

void NEXTION_SendFloat (char *ID, float32_t number){
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%.2f\"", ID, number);
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}

void NEXTION_SenduInt (char *ID, uint32_t number){
	char buf[50];
	int len = sprintf(buf, "%s.txt=\"%lu\"", ID, number);
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}

void NEXTION_CMD (const char *string){
//TODO MM modified strlen parameter to fit
	HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}

void UpdatePage(){
	NEXTION_SendFloat("t1",ReflowParameters.firstHeatUpRate);
	NEXTION_SenduInt("t2", ReflowParameters.SoakTempeture);
	NEXTION_SenduInt("t3", ReflowParameters.SoakTime);
	NEXTION_SendFloat("t4",ReflowParameters.secondHeatUpRate);
	NEXTION_SenduInt("t5", ReflowParameters.ReflowTempeture);
	NEXTION_SenduInt("t6", ReflowParameters.ReflowTime);
}

void NextionDrawDot(uint32_t x, uint32_t y){

	char buf[50];
	int len = sprintf(buf, "cirs %lu,%lu,2,BLUE", x, y);
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}

void NextionDrawTemp(uint32_t x, uint32_t y){

	uint8_t miki1;
	uint8_t miki2;
	char buf[50];
	int len = sprintf(buf, "cirs %lu,%lu,2,RED", x, y);
	miki1=HAL_UART_Transmit(&huart1, (uint8_t *)buf, len, 1000);
	miki2=HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
}



float32_t HandleKeyPad(void) {

	//clear Input
	for (int i = 0; i < 20; i++) {
		input[i] = 0;
	}

	uint8_t index = 0;

	NEXTION_SendString("t0", "");
	UART_Recieved_Flag = 0;

	while (strncmp((char*) UART_Recieved_Data, "enter", 5) != 0)
	{

		if(strncmp((char*) UART_Recieved_Data, "abbre", 5) == 0)
		{
			return 9999;
		}
		else
		{
			//do nothing.
		}
		if(strncmp((char*) UART_Recieved_Data, "kback", 5) == 0)
				return 8888;
		else
		{
			//do nothing
		}


		if (UART_Recieved_Flag == 1) {
			input[index] = UART_Recieved_Data[4];
			UART_Recieved_Flag = 0;
			index++;
			NEXTION_SendString("t0", input);
		}
	}
	return atof(input);
}


void Update_Page_3() {
	flagMiki=true;
	uint8_t defaultUart[5] = {'p','3','x','x','x'};
	for(int i=0;i<5;i++){
		UART_Recieved_Data[i]=defaultUart[i];
	}

	NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);
	NEXTION_SenduInt("t1", ReflowParameters.SoakTime);
	NEXTION_SenduInt("t2", ReflowParameters.SoakTempeture);
	NEXTION_SendFloat("t3", ReflowParameters.secondHeatUpRate);
	NEXTION_SenduInt("t4", ReflowParameters.ReflowTime);
	NEXTION_SenduInt("t5", ReflowParameters.ReflowTempeture);

}

void Update_Page_0() {
	uint8_t defaultUart[5] = {'p','0','x','x','x'};
	for(int i=0;i<5;i++){
		UART_Recieved_Data[i]=defaultUart[i];
	}

	float32_t dx =0.23; //275px / 400s //92px 400s
	float32_t dy = 0.5458; //200px / 240 Grad 131px 240deg
	uint32_t OffsetX = 28;
	uint32_t OffsetY = 153; //151

		//Reflow Aktuelle Temperatur anzeigen:
		if (ReflowEnable == 1)
			NextionDrawTemp(OffsetX + (uint32_t)((float32_t)(ReflowIndex)*dx), OffsetY - (uint32_t)((float32_t)(temperature)*dy));



	NEXTION_SendFloat("t0", temperature);
	NEXTION_SendFloat("t1", ReflowParameters.firstHeatUpRate);
	NEXTION_SenduInt("t3", ReflowParameters.SoakTime);
	NEXTION_SenduInt("t2", ReflowParameters.SoakTempeture);
	NEXTION_SendFloat("t4", ReflowParameters.secondHeatUpRate);
	NEXTION_SenduInt("t6", ReflowParameters.ReflowTime);
	NEXTION_SenduInt("t5", ReflowParameters.ReflowTempeture);
	NEXTION_SendString("g1", ConsoleMSG);

	HAL_UART_Receive_IT(&huart1, UART_Recieved_Data, 5);

}

void Update_Page_2() {
	uint8_t defaultUart[5] = {'p','2','x','x','x'};
	for(int i=0;i<5;i++){
		UART_Recieved_Data[i]=defaultUart[i];
	}

	NEXTION_SendFloat("t0", ReflowParameters.KP);
	NEXTION_SendFloat("t1", ReflowParameters.Ki);
	NEXTION_SendFloat("t2", ReflowParameters.KD);
}



void HandleGui(){
	//###################ErrorCheck##########################
	if (-1==temperature)
	{
		State=Error;
	}

	//###################Page0##########################

	if(strncmp((char *)UART_Recieved_Data, "p0xxx", 5) == 0){
			Update_Page_0();
			}

	if(strncmp((char *)UART_Recieved_Data, "p0b02", 5) == 0){
			Update_Page_3();
			}

	if(strncmp((char *)UART_Recieved_Data, "p0b00", 5) == 0){
			startReflow();
			Update_Page_0();
			}

	if(strncmp((char *)UART_Recieved_Data, "p0b01", 5) == 0){
			stopReflow();
			Update_Page_0();
			}

	if(strncmp((char *)UART_Recieved_Data, "p0b02", 5) == 0){
			Update_Page_3();

	}


	//###################Page2##########################

	  if(strncmp((char *)UART_Recieved_Data, "p2xxx", 5) == 0){
		Update_Page_2();
		}

		  if(strncmp((char *)UART_Recieved_Data, "p2b00", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.KP;
			  }
	    ReflowParameters.KP = Output;
	    PID.Kp = ReflowParameters.KP;
		arm_pid_init_f32(&PID, 1);
		Update_Page_2();
		NEXTION_CMD("page 2");

		}

		  if(strncmp((char *)UART_Recieved_Data, "p2b01", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.Ki;
			  }
			  ReflowParameters.Ki = Output;
			  	    PID.Ki = ReflowParameters.Ki;
			arm_pid_init_f32(&PID, 1);
			Update_Page_2();
			NEXTION_CMD("page 2");

		}

		  if(strncmp((char *)UART_Recieved_Data, "p2b02", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.KD;
			  }
			  ReflowParameters.KD = Output;
			 			  	    PID.Kd = ReflowParameters.KD;
			arm_pid_init_f32(&PID, 1);
			Update_Page_2();
			NEXTION_CMD("page 2");

		}

		  if(strncmp((char *)UART_Recieved_Data, "p2b03", 5) == 0){
			Update_Page_3();
		}







	//###################Page 3########################

	  if(strncmp((char *)UART_Recieved_Data, "p3xxx", 5) == 0){
		Update_Page_3();
		}

		  if(strncmp((char *)UART_Recieved_Data, "p3b00", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.firstHeatUpRate;
			  }

			  if(Output < 0.2)
				  Output = 0.2;

		ReflowParameters.firstHeatUpRate = Output;
		Update_Page_3();
		NEXTION_CMD("page 3");
		calculateReflowCurve();

		}
		//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

		  if(strncmp((char *)UART_Recieved_Data, "p3b01", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.SoakTime;
			  }
			ReflowParameters.SoakTime = Output;
			Update_Page_3();
			NEXTION_CMD("page 3");
			calculateReflowCurve();

		}
		//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

		  if(strncmp((char *)UART_Recieved_Data, "p3b02", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.SoakTempeture;
			  }
			ReflowParameters.SoakTempeture = Output;
			Update_Page_3();
			NEXTION_CMD("page 3");
			calculateReflowCurve();

		}
		//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

		  if(strncmp((char *)UART_Recieved_Data, "p3b03", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.secondHeatUpRate;
			  }
			  if(Output < 0.2)
						  Output = 0.2;
			ReflowParameters.secondHeatUpRate = Output;
			Update_Page_3();
			NEXTION_CMD("page 3");
			calculateReflowCurve();

		}


		//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

		  if(strncmp((char *)UART_Recieved_Data, "p3b04", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.ReflowTime;
			  }
			ReflowParameters.ReflowTime = Output;
			Update_Page_3();
			NEXTION_CMD("page 3");
			calculateReflowCurve();

		}
		//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);

		  if(strncmp((char *)UART_Recieved_Data, "p3b05", 5) == 0){
			  float32_t Output =0;
			  Output = HandleKeyPad();
			  while(Output == 9999){
					uint8_t defaultUart[5] = {'x','x','x','x','x'};
					for(int i=0;i<5;i++){
						UART_Recieved_Data[i]=defaultUart[i];
					}
				  Output = HandleKeyPad();
			  }
			  if(Output == 8888){
				 Output = ReflowParameters.ReflowTempeture;
			  }
			ReflowParameters.ReflowTempeture = Output;
			Update_Page_3();
			NEXTION_CMD("page 3");
			calculateReflowCurve();

		}

		  if(strncmp((char *)UART_Recieved_Data, "p3b06", 5) == 0){
			Update_Page_2();
		}

		  if(strncmp((char *)UART_Recieved_Data, "p3b07", 5) == 0){
			Update_Page_0();
			Draw_Reflow_Curve();
			SaveParameters();
		}
		//NEXTION_SendFloat("t0", ReflowParameters.firstHeatUpRate);


//	NEXTION_SendFloat("t0",ReflowParameters.firstHeatUpRate );
//	NEXTION_SenduInt("t1",ReflowParameters.SoakTime );
//	NEXTION_SenduInt("t2",ReflowParameters.SoakTempeture );
//	NEXTION_SendFloat("t3",ReflowParameters.secondHeatUpRate );
//	NEXTION_SenduInt("t4",ReflowParameters.ReflowTime );
//	NEXTION_SenduInt("t5",ReflowParameters.ReflowTempeture );
}

void startReflow(){

if(0==ReflowEnable)
{
	initFlags();
	State=Initializing;
}
ReflowEnable = 1;
NEXTION_CMD("page 0");
Draw_Reflow_Curve();
sprintf(ConsoleMSG,"REFLOW START");
Update_Page_0();
HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);//Startuje NVIC interrupta za zero crossing
HAL_TIM_Base_Start_IT(&htim5);
}

void stopReflow(){
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);//Stopira NVIC interrupta za zero crossing
	//HAL_TIM_Base_Stop_IT(&htim5);
	if(ReflowEnable ==1){
		ReflowEnable = 0;
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_RESET);
		sprintf(ConsoleMSG,"STOPPED");
		Update_Page_0();
		PIDFlag=0;
	}
}

void Draw_Reflow_Curve(){

	float32_t dx =0.23; //275px / 400s //92px 400s
	float32_t dy = 0.5458; //200px / 240 Grad 131px 240deg
	uint32_t OffsetX = 28;
	uint32_t OffsetY = 153; //151



//	float32_t dx = 0.625 / 4; //275px / 880s / 500 ms
//	float32_t dy = 0.8333; //200px / 240 Grad
//	uint32_t OffsetX = 35;
//	uint32_t OffsetY = 230;

	uint32_t index = 0;



	while(ReflowCurve[index] != 0){

		NextionDrawDot(OffsetX + (uint32_t)((float32_t)(index)*dx), OffsetY - (uint32_t)((float32_t)(ReflowCurve[index])*dy));
		index= index + 4;

		if(strncmp((char *)UART_Recieved_Data, "p0b02", 5) == 0)
			break;
	}
}

void setReflowParameters(){
	ReflowParameters.KP = 200; //203
	ReflowParameters.Ki = 0; //5.2
	ReflowParameters.KD = 0;
	ReflowParameters.firstHeatUpRate = 1.2;
	ReflowParameters.SoakTempeture = 100;
	ReflowParameters.SoakTime = 100;
	ReflowParameters.secondHeatUpRate = 1.2;
	ReflowParameters.ReflowTempeture = 210;
	ReflowParameters.ReflowTime =100;
	sprintf(ConsoleMSG,"IDLE");
}

void calculateReflowCurve(){
	for(int i =0;i<4000;i++){
		ReflowCurve[i]=0;
	}

	int index = 0;
	float timestep = 0.5;
	//First Heat Up:
	while (24 + timestep * ReflowParameters.firstHeatUpRate <= ReflowParameters.SoakTempeture) {
	ReflowCurve[index] = 24 + timestep * ReflowParameters.firstHeatUpRate;
	index++;
	timestep = timestep + 0.5;
	}
	PhaseIndex[1]=index;

	//Soak
	int Soakduration = 2*ReflowParameters.SoakTime;

	for(int i=0;i<Soakduration;i++){
		ReflowCurve[index+i]=ReflowParameters.SoakTempeture;
	}


	//Second Heat Up:
	index = index + Soakduration;
	PhaseIndex[2]=index;
	timestep = 0.5;
	while (ReflowParameters.SoakTempeture + timestep * ReflowParameters.secondHeatUpRate <= ReflowParameters.ReflowTempeture) {
	ReflowCurve[index] = ReflowParameters.SoakTempeture + (uint8_t)timestep * ReflowParameters.secondHeatUpRate;
	index++;
	timestep = timestep + 0.5;
	}
	PhaseIndex[3]=index;

	//Reflow
	int Reflowduration = 2*ReflowParameters.ReflowTime;

	for(int i=0;i<Reflowduration;i++){
		ReflowCurve[index+i]=ReflowParameters.ReflowTempeture;
	}

	index = index + Reflowduration;
	ReflowCurve[index]=0;
	PhaseIndex[4]=index;

	//Cooldown
	timestep = 0.5;
	while (ReflowParameters.ReflowTempeture - timestep * 1.8 >= 24) {
	ReflowCurve[index] = ReflowParameters.ReflowTempeture - timestep * 1.8;
	index++;
	timestep = timestep + 0.5;
	PhaseIndex[5]=index;
	}




}

void initFlags(void)
{
	Flags.StartFlag=TRUE;
	Flags.initComplete=FALSE;
	Flags.preheatComplete=FALSE;
	Flags.soakComplete=FALSE;
	Flags.reflowComplete=FALSE;
	Flags.cooldownComplete=FALSE;
}

