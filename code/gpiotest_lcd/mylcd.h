/*  This work is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * 
 *  Copyright(c) 2014 Hong Moon 	All Rights Reserved
 */

/* description: a user level Linux driver to control a 16x2 character LCD (with HD44780 LCD Controller) with 4 bit mode.
		The LCD is interfaced with a micro-controller using GPIO pins.
		See below "LCD Pin Configuration" to see GPIO pin connections

   name:	Hong Moon (hsm5xw@gmail.com)
   date:	2014-Sept
*/

#ifndef MYLCD_H_
#define MYLCD_H_

// ******** LCD Pin Configuration ****************

#define LCD_RS_PIN_NUMBER	67  // LCD_RS: P8_8  (GPIO pin 67)
#define LCD_E_PIN_NUMBER	68  // LCD_E:  P8_10 (GPIO pin 68)

#define LCD_DB4_PIN_NUMBER	65  // LCD_DB4: P8_18 (GPIO pin 65)
#define LCD_DB5_PIN_NUMBER	46  // LCD_DB5: P8_16 (GPIO pin 46)
#define LCD_DB6_PIN_NUMBER	26  // LCD_DB6: P8_14 (GPIO pin 26)
#define LCD_DB7_PIN_NUMBER	44  // LCD_DB7: P8_12 (GPIO pin 44)


// ******** Other Constants **********************

#define RS_COMMAND_MODE		0   // command mode to select Insruction register with RS signal
#define RS_DATA_MODE		1   // data mode to select Data register with RS signal

#define LCD_FIRST_LINE		1
#define LCD_SECOND_LINE		2

#define NUM_CHARS_PER_LINE      16  // the number of characters per line


// ********* Function Prototypes *****************

void lcd_pin_setup(unsigned int pin_number);
void lcd_pin_setup_All();
void lcd_instruction(char command);
void lcd_data(char data);

void lcd_initilize();
void lcd_print(char * msg, unsigned int lineNumber);
void lcd_print_WithPosition(char * msg, unsigned int lineNumber, unsigned int nthCharacter);

void lcd_setLinePosition(unsigned int line);
void lcd_setPosition(unsigned int line, unsigned int nthCharacter);

#endif
