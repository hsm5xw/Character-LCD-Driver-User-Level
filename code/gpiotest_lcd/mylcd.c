/*  This work is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 *
 *  Copyright(c) 2014 Hong Moon 	All Rights Reserved
 */

/* description: a user level Linux driver to control a 16x2 character LCD (with HD44780 LCD controller) with 4 bit mode.
  		The LCD is interfaced with a micro-controller using GPIO pins.

   name:	Hong Moon (hsm5xw@gmail.com)
   date:	2014-Sept
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "mylcd.h"
#include "simplegpio.h"

/*
 * description:		 Set up a pin for LCD.
 * 
 * @param pin_number	 pin number to be set up. 	
*/
void lcd_pin_setup(unsigned int pin_number)
{
	PIN_DIRECTION gpio_direction = OUTPUT_PIN;

	gpio_export(pin_number);			 // set GPIO pin export
	gpio_set_direction(pin_number, gpio_direction);  // set GPIO pin direction
	gpio_set_value(pin_number, 0);			 // set GPIO pin value
}

/*
 * description: Set up all pins needed for LCD
 * 
*/
void lcd_pin_setup_All()
{
	lcd_pin_setup(LCD_RS_PIN_NUMBER);
	lcd_pin_setup(LCD_E_PIN_NUMBER);

	lcd_pin_setup(LCD_DB4_PIN_NUMBER);
	lcd_pin_setup(LCD_DB5_PIN_NUMBER);
	lcd_pin_setup(LCD_DB6_PIN_NUMBER);
	lcd_pin_setup(LCD_DB7_PIN_NUMBER);
}

/*
 * description:		 send a 4-bit command to the HD44780 LCD controller.
 *
 * @param command	 command to be sent to the LCD controller. Only the upper 4 bits of this command is used.
*/
void lcd_instruction(char command)
{
	unsigned int db7_data = 0;
	unsigned int db6_data = 0;
	unsigned int db5_data = 0;
	unsigned int db4_data = 0;

	usleep(2000);	// added delay instead of busy checking

	// Upper 4 bit data (DB7 to DB4)
	db7_data = ( (command)&(0x1 << 7) ) >> (7) ;
	db6_data = ( (command)&(0x1 << 6) ) >> (6) ;
	db5_data = ( (command)&(0x1 << 5) ) >> (5) ;
	db4_data = ( (command)&(0x1 << 4) ) >> (4) ;

	gpio_set_value(LCD_DB7_PIN_NUMBER, db7_data);
	gpio_set_value(LCD_DB6_PIN_NUMBER, db6_data);
	gpio_set_value(LCD_DB5_PIN_NUMBER, db5_data);
	gpio_set_value(LCD_DB4_PIN_NUMBER, db4_data);

	// Set to command mode
	gpio_set_value(LCD_RS_PIN_NUMBER, RS_COMMAND_MODE);
	usleep(5);

	// Simulate falling edge triggered clock
	gpio_set_value(LCD_E_PIN_NUMBER, 1);
	usleep(5);
	gpio_set_value(LCD_E_PIN_NUMBER, 0);
}

/*
 * description:		send a 1-byte ASCII character data to the HD44780 LCD controller.
 * @param data		a 1-byte data to be sent to the LCD controller. Both the upper 4 bits and the lower 4 bits are used.
*/
void lcd_data(char data)
{
	unsigned int db7_data = 0;
	unsigned int db6_data = 0;
	unsigned int db5_data = 0;
	unsigned int db4_data = 0;

	// Part 1.  Upper 4 bit data (from bit 7 to bit 4)
	usleep(2000); 	// added delay instead of busy checking

	db7_data = ( (data)&(0x1 << 7) ) >> (7) ;
	db6_data = ( (data)&(0x1 << 6) ) >> (6) ;
	db5_data = ( (data)&(0x1 << 5) ) >> (5) ;
	db4_data = ( (data)&(0x1 << 4) ) >> (4) ;

	gpio_set_value(LCD_DB7_PIN_NUMBER, db7_data);
	gpio_set_value(LCD_DB6_PIN_NUMBER, db6_data);
	gpio_set_value(LCD_DB5_PIN_NUMBER, db5_data);
	gpio_set_value(LCD_DB4_PIN_NUMBER, db4_data);

	// Part 1. Set to data mode
	gpio_set_value(LCD_RS_PIN_NUMBER, RS_DATA_MODE);
	usleep(5);

	// Part 1. Simulate falling edge triggered clock
	gpio_set_value(LCD_E_PIN_NUMBER, 1);
	usleep(5);
	gpio_set_value(LCD_E_PIN_NUMBER, 0);	


	// Part 2. Lower 4 bit data (from bit 3 to bit 0)
	usleep(2000);	// added delay instead of busy checking

	db7_data = ( (data)&(0x1 << 3) ) >> (3) ;
	db6_data = ( (data)&(0x1 << 2) ) >> (2) ;
	db5_data = ( (data)&(0x1 << 1) ) >> (1) ;
	db4_data = ( (data)&(0x1)      )        ;

	gpio_set_value(LCD_DB7_PIN_NUMBER, db7_data);
	gpio_set_value(LCD_DB6_PIN_NUMBER, db6_data);
	gpio_set_value(LCD_DB5_PIN_NUMBER, db5_data);
	gpio_set_value(LCD_DB4_PIN_NUMBER, db4_data);

	// Part 2. Set to data mode
	gpio_set_value(LCD_RS_PIN_NUMBER, RS_DATA_MODE);
        usleep(5);

	// Part 2. Simulate falling edge triggered clock
	gpio_set_value(LCD_E_PIN_NUMBER, 1);
	usleep(5);
	gpio_set_value(LCD_E_PIN_NUMBER, 0);	
}


/*
 * description: 	initialize the LCD in 4 bit mode as described on the HD44780 LCD controller document.
*/

void lcd_initialize()
{
	usleep(50*1000);		// wait for more than 40 ms once the power is on

	lcd_instruction(0x30);		// Instruction 0011b (Function set)
	usleep(5*1000);			// wait for more than 4.1 ms

	lcd_instruction(0x30);		// Instruction 0011b (Function set)
	usleep(200);			// wait for more than 100 us

	lcd_instruction(0x30);		// Instruction 0011b (Function set)
	usleep(200);			// wait for more than 100 us

	lcd_instruction(0x20);		/* Instruction 0010b (Function set)
					   Set interface to be 4 bits long
					*/
	usleep(200);			// wait for more than 100 us

	lcd_instruction(0x20);		// Instruction 0010b (Function set)
	lcd_instruction(0x80);		/* Instruction NF**b
					   Set N = 1, or 2-line display
					   Set F = 0, or 5x8 dot character font
					 */
	usleep(50*1000);

					/* Display off */
	lcd_instruction(0x00);		// Instruction 0000b
	lcd_instruction(0x80);		// Instruction 1000b
	usleep(200);

					/* Display clear */
	lcd_instruction(0x00);		// Instruction 0000b
	lcd_instruction(0x10);		// Instruction 0001b
	usleep(200);

					/* Entry mode set */
	lcd_instruction(0x00);		// Instruction 0000b
	lcd_instruction(0x60);		/* Instruction 01(I/D)Sb -> 0110b
					   Set I/D = 1, or increment or decrement DDRAM address by 1
					   Set S = 0, or no display shift
					*/
	usleep(200);

	/* Initialization Complete, but set up default LCD setting here */

					/* Display On/off Control */
	lcd_instruction(0x00);		// Instruction 0000b
	lcd_instruction(0xF0);		/* Instruction 1DCBb  
					   Set D= 1, or Display on
					   Set C= 1, or Cursor on
					   Set B= 1, or Blinking on
					*/
	usleep(200);
}


/*
 * description: 	print a string data on the LCD
 * 			(If the line number is 1 and the string is too long to be fit in the first line, the LCD
 * 			will continue to print the string on the second line)
 *
 * @param lineNumber	the line number of the LCD where the string is be printed. It should be either 1 or 2.
 * 			Otherwise, it is readjusted to 1.
 *
 * detail:		I implemented the code to only allow a certain number of characters to be written on the LCD.
 * 			As each character is written, the DDRAM address in the LCD controller is incrmented.
 * 			When the string is too long to be fit in the LCD, the DDRAM can be set back to 0 and the existing
 * 			data on the LCD are overwritten by the new data. This causes the LCD to be very unstable and also
 * 			lose data.		
*/

void lcd_print(char * msg, unsigned int lineNumber)
{
	unsigned int counter = 0;
	unsigned int lineNum = lineNumber;

	if(msg == NULL){
		printf("ERR: Empty data for lcd_print \n");
		return;
	}
	if( (lineNum != 1) && (lineNum != 2) ) { 
		printf("ERR: Invalid line number readjusted to 1 \n");
		lineNum = 1;
	}

	if( lineNum == 1 )
	{
		lcd_setLinePosition( LCD_FIRST_LINE );

		while( *(msg) != '\0' )
		{
			if(counter >=  NUM_CHARS_PER_LINE )
			{
				lineNum = 2;	// continue writing on the next line if the string is too long
				counter = 0;
				break;		
			}

			lcd_data(*msg);
			msg++;
			counter++;
		}
	}

	if( lineNum == 2)
	{
		lcd_setLinePosition( LCD_SECOND_LINE);
		
		while( *(msg) != '\0' )
		{
			if(counter >=  NUM_CHARS_PER_LINE )
			{
				 break;
			}

			lcd_data(*msg);
			msg++;
			counter++;
		}
	}
}

/*
 * description: 	print a string data on the specified position of the LCD
 * 			(If the line number is 1 and the string is too long to be fit in the first line, the LCD
 * 			 will continue to print the string on the second line)
 *
 * @param lineNumber 	the line number of the LCD where the string is printed. It should be either 1 or 2.
 * 			Otherwise, it is readjusted to 1.
 *
 * @param nthCharacter  the nth character of the line where the string is printed.
 * 			It starts from 0, which indicates the beginning of the line specified.
*/

void lcd_print_WithPosition(char * msg, unsigned int lineNumber, unsigned int nthCharacter)
{
	unsigned int counter = nthCharacter;
	unsigned int lineNum = lineNumber;
	unsigned int nthChar = nthCharacter;

	if( msg == NULL ){
		printf("ERR: Empty data for lcd_print_WithPosition \n");
		return;
	}

	if( (lineNum != 1) && (lineNum != 2)  ){
		printf("ERR: Invalid line number input readjusted to 1 \n");
		lineNum = 1;
	}

	if( lineNum == 1 )
	{
		lcd_setPosition( LCD_FIRST_LINE, nthChar );
		
		while( *(msg) != '\0' )
		{
			if( counter >= NUM_CHARS_PER_LINE )
			{
				lineNum = 2;  // continue writing on the next line if the string is too long
				counter = 0;
				nthChar = 0;
				break;
			}
			lcd_data(*msg);
			msg++;
			counter++;
		}
	}

	if( lineNum == 2)
	{	
		lcd_setPosition( LCD_SECOND_LINE, nthChar );

		while( *(msg) != '\0' )
		{
			if( counter >= NUM_CHARS_PER_LINE )
			{
				break;
			}	
			lcd_data(*msg);
			msg++;
			counter++;
		}
	}

}


/*
 * description:	set the cursor to the beginning of the line specified.
 * @param line  line number should be either 1 or 2.	
*/
void lcd_setLinePosition(unsigned int line)
{
	if(line == 1){
		lcd_instruction(0x80);	// set position to LCD line 1
		lcd_instruction(0x00);
	}
	else if(line == 2){
		lcd_instruction(0xC0);
		lcd_instruction(0x00);
	}
	else{
		printf("ERR: Invalid line number. Select either 1 or 2 \n");
	}
}

/*
 * description:  	 set the cursor to the nth character of the line specified.
 * @param line 		 the line number should be either 1 or 2. 
 * @param nthCharacter	 n'th character where the cursor should start on the line specified.
 * 			 It starts from 0, which indicates the beginning of the line.
*/
void lcd_setPosition(unsigned int line, unsigned int nthCharacter)
{
	char command;

	if(line == 1){
		command = 0x80 + (char) nthCharacter;
		
		lcd_instruction(  command & 0xF0 ); 	  // upper 4 bits of command
		lcd_instruction( (command & 0x0F) << 4 ); // lower 4 bits of command 
	}
	else if(line == 2){
		command = 0xC0 + (char) nthCharacter;

		lcd_instruction(  command & 0xF0 ); 	  // upper 4 bits of command
		lcd_instruction( (command & 0x0F) << 4 ); // lower 4 bits of command
	}
	else{
		printf("ERR: Invalid line number. Select either 1 or 2 \n");
	}	
}
