/*
 * functions.c
 *
 *  Created on: May 16, 2020
 *      Author: miki
 */
#include "functions.h"
#include "variables.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stm32f4xx_hal_gpio.h>
#include <stdbool.h>
#define LCD_I2C_SLAVE_ADDRESS 0x7E 						//adresa i2c interfejsa za LCD
extern TIME time;
//extern I2C_HandleTypeDef hi2c1; 						//stavi hi2c koji koristis
static volatile uint32_t counter2=0;
uint16_t counter_us;
uint16_t counter_us2;

/*----------------------------------------------------------------------------------------------------------------------
 * Fucntion for PID control of incubator heater, it returns the value of error which is used as a correction for switching TRIAC
 * that powers the heater
 * --------------------------------------------------------------------------------------------------------------------*/
int PID_control(int setpoint, float Kp, float Ki ,float Kd, volatile float *p_temperature )
{
			Time= millis();                //current time
	        elapsedTime = (double)(Time - timePrev);        //calculate elapsed time

	        PID_greska = (*p_temperature)-setpoint  ;                                // PID error

	        PID_i += PID_greska * elapsedTime;                // integral part
	        PID_d = (PID_greska - PID_prethodna_greska)/elapsedTime;   // derivative part
	        if(PID_greska<0)
	             {PID_i=0;}
	        PID_vrednost = Kp*PID_greska + Ki*PID_i +Kd*PID_d ;                //PID correction

	        PID_prethodna_greska = PID_greska;                                //saves current error for future iteration
	        timePrev = Time;                        //saves current time for future iteration

	        if(PID_vrednost > 9800)
	        	    	{
	        	    	PID_vrednost = 9800; //maximum value of control in case of 10ms time
	        	    	};
	       if(PID_vrednost <0)
	        {
	        	PID_vrednost = 0; ////minimum value of control in case of 10ms time
	       	};
	    return (volatile unsigned int) PID_vrednost;
}
/*-----------------------------------------------------------------------------------------------
 * Heater power control through delay function which switches ON TRIAC
 * ----------------------------------------------------------------------------------------------*/
void kontrola_grejac(volatile uint32_t PID_Error)
{
	const uint16_t max_firing_delay1=9800;	//heater bank 1
	const uint16_t max_firing_delay2=7000;	//heater bank 2
	static uint16_t PID_Error2=0;

	if(PID_Error>max_firing_delay2)
	{
		PID_Error2=max_firing_delay2;
	}
	else
	{
		PID_Error2=PID_Error;
	}

//	HAL_GPIO_WritePin(PIFiringPin_GPIO_Port, PIFiringPin_Pin, GPIO_PIN_SET);//HALGPIOPINSET bank 1
//	HAL_GPIO_WritePin(PIFiringPin2_GPIO_Port, PIFiringPin2_Pin, GPIO_PIN_SET);//HALGPIOPINSET bank 2
//	HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)
	//__HAL_TIM_GET_COUNTER(&htim3)
//	 __HAL_TIM_SET_COUNTER(&htim5,0);
//	delay_us(9800);
//	HAL_GPIO_WritePin(PIFiringPin_GPIO_Port, PIFiringPin_Pin, GPIO_PIN_RESET); //HALGPIOPINRESET bank 1
//	HAL_GPIO_WritePin(PIFiringPin2_GPIO_Port, PIFiringPin2_Pin, GPIO_PIN_RESET); //HALGPIOPINRESET bank 2

/*	if(	counter_us	>=	(max_firing_delay1-PID_Error)	)
	{//Ovaj delay kontrolise snagu grejaca
		counter_us=0;
		HAL_GPIO_WritePin(PIFiringPin_GPIO_Port, PIFiringPin_Pin, GPIO_PIN_RESET); //HALGPIOPINRESET bank 1
	}
	else
	{

	}

	if(	counter_us2	>=	(max_firing_delay2-PID_Error2)	)
	{//Ovaj delay kontrolise snagu grejaca
		counter_us2=0;
		HAL_GPIO_WritePin(PIFiringPin2_GPIO_Port, PIFiringPin2_Pin, GPIO_PIN_RESET); //HALGPIOPINRESET bank 2
	}
	else
	{

	}
*/
	//delay_us(100);
	//zero_croosing=0;//false
}
/*-----------------------------------------------------------------------------------------------------------------------
 * Funkcija koja vrsi ocitavanje temperature i vlaznosti vazduha putem i2c Bus-a i vraca dbl* na niz gde su vrednosti
 * Temperature i Relativne vlaznosti vazduha skladistene
 * -----------------------------------------------------------------------------------------------------------------------*/
double * DHT12_ocitavanje(int DHT12_address)
{
	uint8_t data[6];

	data[0]=0x00;//pocetna adresa
//	HAL_I2C_Master_Transmit(&hi2c1,DHT12_address,data,1,10);
//	HAL_I2C_Master_Receive(&hi2c1,DHT12_address,&data[1],5,10);
	RH_int=data[1];
	RH_dec=data[2];
	T_int=data[3];
	T_dec=data[4];

	if(data[5]==(data[1]+data[2]+data[3]+data[4]))//checksum provera
	{

		sprintf(RH_val,"%2d.%1d",RH_int,RH_dec);
		sprintf(T_val,"%2d.%1d",T_int,T_dec);
		RHT_val[0]=atof(T_val);
		RHT_val[1]=atof(RH_val);
		return RHT_val;

	}
	else
	{
		return  NULL;
	}

}
/*---------------------------------------------------------------------------------
 * Funkcija koja vadi vreme preko i2c interfejsa i upisuje isti u struct time.
 *
 *--------------------------------------------------------------------------------*/
void getTimeDate_DS3231(int DS3231_I2C_address)
{
	uint8_t get_time[7]={0};

//	HAL_I2C_Mem_Read(&hi2c1,DS3231_I2C_address,0x00,1,get_time,7,1000);

	time.seconds=hextodec(get_time[0]);
	time.minutes=hextodec(get_time[1]);
	time.hours=hextodec(get_time[2]);
	time.day=hextodec(get_time[3]);
	time.date=hextodec(get_time[4]);
	time.month=hextodec(get_time[5]);
	time.year=hextodec(get_time[6]);
}
/*---------------------------------------------------------------------------------
 * Funkcija koja setuje vreme na DS3231 RTC modulu preko i2c interfejsa
 *
 *--------------------------------------------------------------------------------*/
void setTime_DS3231(int DS3231_I2C_address,uint8_t sec, uint8_t min, uint8_t hours, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0]=dectohex(sec);
	set_time[1]=dectohex(min);
	set_time[2]=dectohex(hours);
	set_time[3]=dectohex(dow);
	set_time[4]=dectohex(dom);
	set_time[5]=dectohex(month);
	set_time[6]=dectohex(year);
//	HAL_I2C_Mem_Write(&hi2c1,DS3231_I2C_address,0x00,1,set_time,7,1000);
}
/*-----------------------------------------------------------------------------
 *Funkcija koja vrsi konverziju iz decimalnih brojeva u hex brojeve
 *-----------------------------------------------------------------------------*/
uint8_t dectohex(int val)
{
	return(uint8_t)((val/10*16)+(val%10));
}
/*-----------------------------------------------------------------------------
 * Funkcija koja vrsi konverziju iz hex brojeva u decimalne brojeve
 * ---------------------------------------------------------------------------*/
int hextodec(uint8_t val)
{
	return (int)((val/16*10)+(val%16));
}
/*-----------------------------------------------------------------------------
 * funkcija koja trazi adresu uredjaja na I2C magistrali i vraca vrednost adrese
 * ---------------------------------------------------------------------------*/
int find_I2C_deviceAddress(void)
{
	uint8_t i=0;
	for(i=0;i<255;i++)
	{
	//	if(HAL_I2C_IsDeviceReady(&hi2c1,i,1,10)==HAL_OK)
		{
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
			return i;
			break;
		}
	}
	return -1;//greska
}
/*-----------------------------------------------------------------------------
 * funkcija koja salje komandu na LCD kontroler putem i2c BUS-a
 * ---------------------------------------------------------------------------*/
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);      //4BIT HI
	data_l = ((cmd<<4)&0xf0); //4BIT LO
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
//	HAL_I2C_Master_Transmit (&hi2c1,LCD_I2C_SLAVE_ADDRESS,(uint8_t *) data_t, 4, 100);
}
/*-----------------------------------------------------------------------------
 * funkcija koja salje podatke na LCD kontroler putem i2c BUS-a
 * ---------------------------------------------------------------------------*/
void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  	//en=1, rs=0
	data_t[1] = data_u|0x09;  	//en=0, rs=0
	data_t[2] = data_l|0x0D;  	//en=1, rs=0
	data_t[3] = data_l|0x09;  	//en=0, rs=0
	//HAL_I2C_Master_Transmit (&hi2c1, LCD_I2C_SLAVE_ADDRESS,(uint8_t *) data_t, 4, 100);
}
/*-----------------------------------------------------------------------------
 * funkcija koja brise sve podatke i CGRAM-a LCD kontroler putem i2c BUS-a
 * ---------------------------------------------------------------------------*/
void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	//lcd_send_cmd (0x80);
	/*for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
	*/
}
/*-----------------------------------------------------------------------------
 * funkcija koja setuje poziciju cursora na LCD ekranu
 * ---------------------------------------------------------------------------*/
void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}
/*-----------------------------------------------------------------------------
 * Inicijalizacija samog LCD-a
 * ---------------------------------------------------------------------------*/
void lcd_init (void)
{
	// 4 BIT inicijalizacija
	HAL_Delay(50);  // cekaj >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // cekaj >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // cekaj  >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mod
	HAL_Delay(10);

  // inicijalizacija displeja
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0 display,C=0 cursor, B=0 blink  ---> display OFF, blink OFF, cursor OFF
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor OFF ,blink OFF
}
/*-----------------------------------------------------------------------------
 * Funkcija koja salje ceo string
 * ---------------------------------------------------------------------------*/
void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void setpointChange(void)
{
};
/*-----------------------------------------------------------------------------
 * Funkcija koja kontrolise okretanje step motora i njegovu brzinu.
 * Brzinu okretanja odredjuje parametar int delay.
 *
 * ---------------------------------------------------------------------------*/
//void stepperMotorControlFD(int delay)
//{
//	/*--------------------------------------------------------------------------
//	 * Full Drive mod koraci
//	 *  1 1 0 0
//	 *  0 1 1 0
//	 *  0 0 1 1
//	 *  1 0 0 1
//	 *-------------------------------------------------------------------------- */
//	int count=0;
//	//Rezolucija motora je 0.70175 po koraku, odnosno 513 koraka za 360 stepeni
//	//Kako bi se ovaj motor okrenuo pun krug za 1 sekundu, potrebno je koristiti
//	//delay od 2ms.
//	while(count<513)
//	{
//	//Step 1
//	HAL_GPIO_WritePin(StepperMotorPin1_GPIO_Port, StepperMotorPin1_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(StepperMotorPin2_GPIO_Port, StepperMotorPin2_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(StepperMotorPin3_GPIO_Port, StepperMotorPin3_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin4_GPIO_Port, StepperMotorPin4_Pin, GPIO_PIN_RESET );
//	delay_ms(delay);
//	//Step 2
//	HAL_GPIO_WritePin(StepperMotorPin1_GPIO_Port, StepperMotorPin1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin2_GPIO_Port, StepperMotorPin2_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(StepperMotorPin3_GPIO_Port, StepperMotorPin3_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(StepperMotorPin4_GPIO_Port, StepperMotorPin4_Pin, GPIO_PIN_RESET );
//	delay_ms(delay);
//	//Step 3
//	HAL_GPIO_WritePin(StepperMotorPin1_GPIO_Port, StepperMotorPin1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin2_GPIO_Port, StepperMotorPin2_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin3_GPIO_Port, StepperMotorPin3_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(StepperMotorPin4_GPIO_Port, StepperMotorPin4_Pin, GPIO_PIN_SET );
//	delay_ms(delay);
//	//Step 4
//	HAL_GPIO_WritePin(StepperMotorPin1_GPIO_Port, StepperMotorPin1_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(StepperMotorPin2_GPIO_Port, StepperMotorPin2_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin3_GPIO_Port, StepperMotorPin3_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin4_GPIO_Port, StepperMotorPin4_Pin, GPIO_PIN_SET );
//	delay_ms(delay);
//	HAL_GPIO_WritePin(StepperMotorPin1_GPIO_Port, StepperMotorPin1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin2_GPIO_Port, StepperMotorPin2_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin3_GPIO_Port, StepperMotorPin3_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(StepperMotorPin4_GPIO_Port, StepperMotorPin4_Pin, GPIO_PIN_RESET );
//	delay_ms(delay);
//	count++;
//	}
//
//};
//void show_time(void)
//{
//	char * strptr;
//	sprintf(lcd_string,"Vreme:%02d:%02d:%02d",time.hours, time.minutes,time.seconds); //string koji ispisuje vreme
//	delay_ms(50);
//	lcd_put_cur(1,0);
//	delay_ms(50);
//	lcd_send_string(lcd_string);
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//	  *(strptr++)=0;
//	}
//};
//void show_date_and_time(void)
//{
//	char * strptr;
//	sprintf(lcd_string,"Datum:%02d-%02d-%02d",time.date, time.month,time.year);	//string koji ispisuje datum
//	GLCD_TEXT_INIT();
//	glcd_clear_buffer();
//	glcd_tiny_draw_string(0,0,lcd_string);
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//	  *(strptr++)=0;
//	}
//	sprintf(lcd_string,"Vreme:%02d:%02d:%02d",time.hours, time.minutes,time.seconds); //string koji ispisuje vreme
//	glcd_tiny_draw_string(0,2,lcd_string);
//	glcd_write();
//
//
//};
//void show_tempAndHumidity(void)
//{
//	char * strptr;
//	strptr=lcd_string;
//	float lcd_temperature=0.0;
//	float lcd_humidity=0.0;
//	float temp_array[10];
//	float hum_array[10];
//	uint8_t array_size;
//
//
//	while(*(strptr) !='\0')
//	{
//		*(strptr++)=0;
//	}
//
////	delay_ms(30);
////	lcd_put_cur(0, 0);
////	delay_ms(30);
//
//
//	for(int i=0;i<10;i++)
//	{
//		//initalizaton of values for filtering
//		BMP280_calc_values();
//		temp_array[i]=temperatura;
//		hum_array[i]=RelVlaz;
//		HAL_Delay(100);
//	}
//	// filtering of values
//	//Temperature
//	array_size = (	sizeof(temp_array) /sizeof(float)	);
//	filter_avg(temp_array,array_size,&lcd_temperature);
//	//humidity
//	array_size = (	sizeof(hum_array)/sizeof(float)	);
//	filter_avg(hum_array,array_size,&lcd_humidity);
//	//LCD write
//	sprintf(lcd_string,"T=%2.1f[degC]",lcd_temperature);
//	glcd_tiny_draw_string(0,0,lcd_string);
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//		*(strptr++)=0;
//	}
//	sprintf(lcd_string,"RV=%2.1f[%%]",RelVlaz);
//	glcd_tiny_draw_string(0,2,lcd_string);
//	glcd_write();
//
//};
//void show_lowHumWarning(void)
//{
//	char * strptr;
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//		*(strptr++)=0;
//	}
//	lcd_clear();
//	delay_ms(50);
//	lcd_put_cur(0, 0);
//	strcpy(lcd_string,"Niska vlaznost!");
//	lcd_send_string(lcd_string);
//	delay_ms(50);
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//		  *(strptr++)=0;
//	}
//
//};
//void start_menu_1(void){
//		GLCD_TEXT_INIT();
//		glcd_clear_buffer();
//		glcd_tiny_draw_string(0,0,"*Inkubator v1.0*");
//		glcd_tiny_draw_string(0, 1, "Miroslav Mitrovic");
//		glcd_tiny_draw_string(0, 3, "Tel:0691311063");
//		glcd_write();
//}
//void start_menu_2(void){
//
//			//enum for menu items
//			enum menu
//			{
//				InitMenu,
//				StartInkub,
//				ShowTempAndHumidity,
//				Settings
//			};
//			//initialization for menu status counter
//			uint8_t menu_status_cnt=0; //incubation start
//			//uint8_t init_menu_stat=0;
//
//
//			GLCD_TEXT_INIT();
//
//
//			while(1){
//				//cycle trough menu on next item
//
//				if(InitMenu==menu_status_cnt)
//				{
//					glcd_clear_buffer();
//					glcd_tiny_draw_string(0, 1,	"1.Start Inkub");
//					glcd_tiny_draw_string(0, 3,	"2.Prikaz T/RH");
//					glcd_tiny_draw_string(0, 5,	"3.Podesavanja");
//					glcd_draw_rect(0, 5, 84, 13, BLACK); 	//Adds the rectangle over the menu item 1
//					glcd_write();
//					menu_status_cnt++;
//					HAL_Delay(90);
//
//				}
//				else
//				{
//					//do nothing
//				}
////				HAL_Delay(50);
//				if((true==greenButtonPressedStatDeb) &&
//						(true!=redButtonPressedStatDeb) && (StartInkub==menu_status_cnt))
//				{
//					glcd_draw_rect(0, 5, 84, 13, WHITE);	//removes the rectangle over the menu item 1
//					glcd_draw_rect(0, 21, 84, 12, BLACK);	//adds the rectangle over the menu item 2
//					glcd_write();
//					HAL_Delay(90);
////					//if the switch is still active, values will be slowly switched
////					if((true==greenButtonPressedStatDeb) &&
////					(true!=redButtonPressedStatDeb) && (StartInkub==menu_status_cnt))
////					{
////						switchHold(500);
////					}
////					else
////					{
////						//do nothing
////					}
//					menu_status_cnt++;
//
//				}
//				else
//				{
//						//do nothing
//				}
////				HAL_Delay(50);
//
//				if((true==redButtonPressedStatDeb)&&
//						(true!=greenButtonPressedStatDeb) && (StartInkub==menu_status_cnt))
//				{
//			 	  //getTimeDate_DS3231(DS3231_ADDRESS_I2C);	//extract current time
//			 	  incub_menu_1(25, 0, 0);					//time of 25 days necessary for incubation completion
//			 	  break;
//				}
//				else
//				{
//							//do nothing
//				}
////				HAL_Delay(50);
//
//				if((true==greenButtonPressedStatDeb) &&
//					(true!=redButtonPressedStatDeb) &&(ShowTempAndHumidity==menu_status_cnt))
//				{
//
//					glcd_draw_rect(0, 21, 84, 12, WHITE);	//Removes the rectangle over the menu item 2
//					glcd_draw_rect(0, 37, 84, 12, BLACK);	//adds the rectangle over the menu item 3
//					glcd_write();
//					menu_status_cnt++;
//					HAL_Delay(90);
//
//				}
//				else
//				{
//					//do nothing
//				}
////				HAL_Delay(50);
//
//				if((true==redButtonPressedStatDeb)&&
//				(true!=greenButtonPressedStatDeb) && (ShowTempAndHumidity==menu_status_cnt))
//				{
//				glcd_clear_buffer();
//				show_tempAndHumidity();							//shows temperature and humidity on LCD
//				HAL_Delay(10000);
//				break;
//
//				}
//				else
//				{
//					//do nothing
//				}
////				HAL_Delay(50);
//
//				if((true==greenButtonPressedStatDeb) &&
//					(true!=redButtonPressedStatDeb) &&(Settings==menu_status_cnt))
//				{
//					glcd_draw_rect(0, 37, 84, 12, WHITE);	//Removes the rectangle over the menu item 3
//
//					glcd_write();
//					menu_status_cnt++;
//					if(Settings<menu_status_cnt)
//					{
//						menu_status_cnt=0;
//					}
//					HAL_Delay(90);
//
//				}
//				else
//				{
//					//do nothing
//				}
////				HAL_Delay(50);
//
//			}
//
//
//
////			HAL_Delay(5000);
////			glcd_draw_rect(0, 5, 84, 13, WHITE);
////			glcd_draw_rect(0, 21, 84, 12, BLACK);
////			glcd_write();
//
//
//
//};
//void start_menu_3(void){
////	char * strptr;
////		strptr=lcd_string;
////		while(*(strptr) !='\0')
////		{
////			*(strptr++)=0;
////		}
////		lcd_clear();
////		delay_ms(50);
////		lcd_put_cur(0, 0);
////		strcpy(lcd_string,"1.Start Inkubacij");
////		lcd_send_string(lcd_string);
////		delay_ms(50);
////		strptr=lcd_string;
////		while(*(strptr) !='\0')
////		{
////			  *(strptr++)=0;
////		}
////		lcd_put_cur(1, 0);
////		strcpy(lcd_string,"2.Prikaz Temp");
////		lcd_send_string(lcd_string);
////		delay_ms(50);
////		strptr=lcd_string;
//};
//void incub_menu_1(uint8_t days, uint8_t hours, uint8_t minutes)
//{
//
//
//
//		GLCD_TEXT_INIT();
//		glcd_clear_buffer();
//		glcd_tiny_draw_string(0,0,	"*Inkubacija Zapoceta*");
//		glcd_tiny_draw_string(0, 2,	"Vreme do kraja:");
//
//			char * strptr;
//			strptr=lcd_string;
//			while(*(strptr) !='\0')
//			{
//				*(strptr++)=0;
//			}
//		//remaining days display
//			itoa(days,lcd_string,10);
//			strptr=lcd_string;
//			while(*(strptr) !='\0')
//			{
//				strptr++;
//			}
//			strcpy(strptr," Dana ");
//			while(*(strptr) !='\0')
//			{
//				strptr++;
//			}
//			itoa(hours,strptr,10);
//			while(*(strptr) !='\0')
//			{
//				strptr++;
//			}
//			strcpy(strptr," Sata ");
//			while(*(strptr) !='\0')
//			{
//				strptr++;
//			}
//			itoa(minutes,strptr,10);
//			while(*(strptr) !='\0')
//			{
//				strptr++;
//			}
//			strcpy(strptr," Minuta");
//			glcd_tiny_draw_string(0, 3,lcd_string);
//			glcd_write();
//
//			*(ui8_ptrInkubStatus)=TRUE; //triggers incubation phase
//			HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);//Startuje NVIC interrupta za zero crossing
//
//
//};
////on each change values will be updated and shown on request
//void incub_menu_2(uint8_t days, uint8_t hours, uint8_t minutes)
//{
//	char * strptr;
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//		*(strptr++)=0;
//	}
//
//	GLCD_TEXT_INIT();
//	glcd_clear_buffer();
//	glcd_tiny_draw_string(0,0,	"Vreme do kraja");
//
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//	  *(strptr++)=0;
//	}
//	lcd_put_cur(1, 0);
//	//remaining days display
//	itoa(days,lcd_string,10);
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//		strptr++;
//	}
//	strcpy(strptr," d ");
//	while(*(strptr) !='\0')
//	{
//		strptr++;
//	}
//	itoa(hours,strptr,10);
//	while(*(strptr) !='\0')
//	{
//		strptr++;
//	}
//	strcpy(strptr," h ");
//	lcd_send_string(lcd_string);
//	delay_ms(50);
//	strptr=lcd_string;
//	while(*(strptr) !='\0')
//	{
//		strptr++;
//	}
//	itoa(minutes,strptr,10);
//	while(*(strptr) !='\0')
//	{
//		strptr++;
//	}
//	strcpy(strptr," m");
//	glcd_tiny_draw_string(0, 2,lcd_string);
//	glcd_bar_graph_horizontal(10,40,65,6,250);
//
//	glcd_write();
//};
bool debouncingFunct(ulong debounceVal)
{
	static ulong startDebounceTime=0;
	static ulong currentDebounceTime=0;
	static ulong dbncCnt=0;
	if(0==dbncCnt)
	{
		startDebounceTime=millis();
	}
	else
	{
		//do nothing
	}

	currentDebounceTime=millis();

	//Debouncing check
	if(currentDebounceTime>(startDebounceTime+debounceVal))
	{
		debouncingStat=true;
		dbncCnt=0;
	}
	else
	{
		debouncingStat=false;
		dbncCnt++;
	}

	return debouncingStat; //returns the status of completed debouncing



}
void switchHold(ulong HoldTime)
{

	while(1)
	{
		ulong StarTime_swH=millis();
		ulong HoldTime_swH=HoldTime;
	if(0==((StarTime_swH+HoldTime_swH) % HoldTime))
		{
		return;
		}
	else
	{
		//do nothing
	}
	}

}
//Filter for averaging last 10 values recieved and return output values
void filter_avg(float* inputVal, uint8_t size, float* outputVal)
{

	 float sum=0.0;				//variable for sum


	for(int i=0;i<size;i++)
	{
			sum+=*(inputVal+i);
	}
	sum/=size;
	*(outputVal)=sum;
}
unsigned long millis(void)
{

 return HAL_GetTick();

}

void delay_us(unsigned long delay_us)
{
 __HAL_TIM_SET_COUNTER(&htim5,0);
// __HAL_TIM_SET_COUNTER(&htim6,0);
 while(__HAL_TIM_GET_COUNTER(&htim5)<delay_us);


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
				//sum2=(uint16_t) data8[3] | (uint16_t) data8[2]<< 8 ;
				(*temperature_val)=((sum>>3)/4.0);
			}


}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance==TIM3) //check if the interrupt comes from TIM2
        {
    //	counter_us++;
    	//counter_us2++;
        }
}



