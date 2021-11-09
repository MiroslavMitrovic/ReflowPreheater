/*
 * functions.h
 *
 *  Created on: May 16, 2020
 *      Author: miki
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_
//#include "functions.h"
#include "variables.h"
#include "main.h"
#include "eeprom.h"
//#include "glcd.h"
//#include "../../LCD/fonts/font5x7.h"
#include  <stdint.h>
#include <stdbool.h>



unsigned long millis(void);
void delay_ms(unsigned long);
void delay_us(unsigned long);
int PID_control(int, float, float ,float, volatile float*);
void kontrola_grejac(volatile uint32_t);
double* DHT12_ocitavanje(int);
void getTimeDate_DS3231(int);
void setTime_DS3231(int,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
uint8_t dectohex(int val);
int hextodec(uint8_t val);
int find_I2C_deviceAddress(void);
void lcd_init (void);
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_put_cur(int row, int col);
void lcd_clear (void);
void setpointChange(void);
void stepperMotorControlFD(int);
void show_time(void);
void show_date(void);
void show_date_and_time(void);
void show_tempAndHumidity(void);
void show_lowHumWarning(void);
void start_menu_1(void);
void start_menu_2(void);
void start_menu_3(void);
bool debouncingFunct(unsigned long debounceVal);
void switchHold(unsigned long holdTime);
void incub_menu_1(uint8_t days, uint8_t hours, uint8_t minutes);
void incub_menu_2(uint8_t days, uint8_t hours, uint8_t minutes);
void filter_avg(float* inputVal, uint8_t size, float* outputVal);
void readTemperatureData(volatile float* temperature);


/*Struct za setpointe */
typedef  struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t	year;
} TIME;





extern volatile uint32_t *p_counter_us;
#endif /* INC_FUNCTIONS_H_ */
