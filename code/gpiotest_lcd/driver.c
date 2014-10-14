/* This work is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * 
 * Copyright(c) 2014 Hong Moon 	All Rights Reserved
 */

// description: a testing and driver program for 16x2 character LCD (with HD44780 LCD controller) with 4 bit mode
// name: 	Hong Moon (hsm5xw@gmail.com)
// date: 	2014-September

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "simplegpio.h"
#include "mylcd.h"

// ******************************** TEST CASES *************************************************

void test1()
{
	// Test 1
	lcd_print("A mid summer night's dream", LCD_FIRST_LINE);
}

void test2()
{
	// Test 2
	lcd_print("HSM5XW", LCD_FIRST_LINE);
	lcd_setLinePosition(2);
	lcd_print("AABB", LCD_SECOND_LINE);
}

void test3()
{
	// Test 3
  	lcd_print("ABCDEFGHIJKLMNOPQRSTUVWXYZ AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ", LCD_FIRST_LINE);
}

void test4()
{
	// Test 4
	lcd_print("ABCDE", 3);
}

void test5()
{
	// Test 5
	lcd_print( NULL, LCD_FIRST_LINE );
}

void test6()
{
	// Test 6
	lcd_setPosition( LCD_SECOND_LINE, 2);
}

void test7()
{
	// Test 7
	lcd_print_WithPosition("ABCD", LCD_SECOND_LINE, 3);
}

void test8()
{
	// Test 8
	lcd_print_WithPosition("ABCDEFGHIJKLMNOPQRSTUVWXYZ AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ", LCD_SECOND_LINE, 3);
}

void test9()
{
	// Test 9
	lcd_print_WithPosition("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LCD_FIRST_LINE, 3);
}


// ************************************* END OF TEST CASES *************************************

int main(void)
{
	lcd_pin_setup_All();
	printf("Set up pins for LCD \n");

	lcd_initialize();
	printf("Initialize LCD \n");

	test2(); 	// select the test case here
	printf("LCD program complete \n");

	return 0;
}
