/**
  ******************************************************************************
  * @file    /inc/i2c-lcd.h
  * @author  Miroslav Mitrovic
  * @brief   This file contains all the functions prototypes for the i2c LCD functions.
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
  @subpage I2C_LCD
*/



/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#define LCD_BACKLIGHT          0x08
#define LCD_NOBACKLIGHT        0x00
#define LCD_FIRST_ROW          0x80
#define LCD_SECOND_ROW         0xC0
#define LCD_THIRD_ROW          0x94
#define LCD_FOURTH_ROW         0xD4
#define LCD_CLEAR              0x01
#define LCD_RETURN_HOME        0x02
#define LCD_ENTRY_MODE_SET     0x04
#define LCD_CURSOR_OFF         0x0C
#define LCD_UNDERLINE_ON       0x0E
#define LCD_BLINK_CURSOR_ON    0x0F
#define LCD_MOVE_CURSOR_LEFT   0x10
#define LCD_MOVE_CURSOR_RIGHT  0x14
#define LCD_TURN_ON            0x0C
#define LCD_TURN_OFF           0x08
#define LCD_SHIFT_LEFT         0x18
#define LCD_SHIFT_RIGHT        0x1E

/* Function Prototypes ------------------------------------------------------------------*/

/** @brief Initialization of 1602 LCD display \n
 *  This Function initialize 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			none
 *  @param[out] 		none
 *  @return 			none
 */
void lcd_init_2 (void);
/** @brief Initialization of 1602 LCD display \n
 *  This Function initialize 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			none
 *  @param[out] 		none
 *  @return 			none
 */
void lcd_init (void);   // initialize lcd
/** @brief Send command to 1602 LCD display \n
 *  This Function Sends command to 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			cmd command to be sent
 *  @param[out] 		none
 *  @return 			none
 */
void lcd_send_cmd (char cmd);
/** @brief Send data to 1602 LCD display \n
 *  This Function sends data to 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			data data to be sent
 *  @param[out] 		none
 *  @return 			none
 */
void lcd_send_data (char data);
/** @brief Send string to 1602 LCD display \n
 *  This Function sends string to 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			str pointer to the string that is sent
 *  @param[out] 		none
 *  @return 			none
 */
void lcd_send_string (char *str);
/** @brief Put Cursor at commanded position on 1602 LCD display \n
 *  This Function puts cursor at commanded position of 1602 display in 4BIT mode via I2C bus.
 *	Possible inputs on 1602(16x2) LCD are : row(0-1); col(0-15).
 *
 *  @param[in] 			row row where the cursor will be placed
 *  @param[in]	 		col column where the cursor will be placed
 *  @param[out]	 		none
 *  @return 			none
 */
void lcd_put_cur(int row, int col);
/** @brief Clear the screen of 1602 LCD display \n
 *  This Function puts cursor at commanded position of 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			none
 *  @param[out]	 		none
 *  @return 			none
 */
void lcd_clear (void);
/** @brief Clear the screen of 1602 LCD display \n
 *  This Function puts cursor at commanded position of 1602 display in 4BIT mode via I2C bus.
 *
 *
 *  @param[in] 			none
 *  @param[out]	 		none
 *  @return 			none
 */
void lcd_clear_cmd (void);
