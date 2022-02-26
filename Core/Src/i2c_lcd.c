/**
  ******************************************************************************
  * @file    /src/i2c-lcd.c
  * @author  Miroslav Mitrovic
  * @brief   This file contains all the functions definitions for the i2c LCD functions.
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
/** @addtogroup I2C LCD
  * @{
  */


/* Includes ------------------------------------------------------------------*/
#include <i2c_lcd.h>
#include "main.h"
extern I2C_HandleTypeDef hi2c1;  	///< Global I2C hanlde-change your handler here accordingly

/* Defines ------------------------------------------------------------------*/
#define  SLAVE_ADDRESS_LCD 0x4EU 	///< I2C LCD address-change according to your I2C address

/* Functions ------------------------------------------------------------------*/
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd & 0xf0);
	data_l = ( (cmd << 4) & 0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

void lcd_clear_cmd(void)
{
	lcd_send_cmd (0x0);
	HAL_Delay(1);
	lcd_send_cmd (0x1);
	HAL_Delay(1);
}

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

void lcd_init_2 (void)
{
	uint8_t i=0;
	HAL_Delay(20);
	for(i=0;i<3;i++)//sending 3 times: select 4-bit mode
	{
		lcd_send_cmd(0x03);
		HAL_Delay(10);
	}
	//4
	lcd_send_cmd (0x02); //to set to 4-bit mode
	//5
	HAL_Delay(10);
	lcd_send_cmd (0x20);
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	//6
	HAL_Delay(10);
	lcd_send_cmd (0x00);
	lcd_send_cmd (0x80);
	//7
	HAL_Delay(10);
	lcd_send_cmd (0x00);
	lcd_send_cmd(0x10);
	//8
	HAL_Delay(10);
	lcd_send_cmd (0x00);
	lcd_send_cmd(0x40);
	HAL_Delay(10);
	lcd_send_cmd (0x00);
	lcd_send_cmd (LCD_TURN_ON);
	HAL_Delay(10);
}



void lcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(50);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(50);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(50);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(50);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(50);
	HAL_Delay(50);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(50);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
