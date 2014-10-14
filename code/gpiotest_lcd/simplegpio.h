/*  This work is licensed under a Creative Commons Attribution-Noncommercial-NoDerivative 4.0 International License.
 *
 *  Copyright(c) 2014 Hong Moon 	All Rights Reserved 
 */

// description: a simple gpio control
// name: Hong Moon (hsm5xw@gmail.com)
// date: 2014-Sept

#ifndef SIMPLEGPIO_H_
#define SIMPLEGPIO_H_

#define MAX_BUF_LENGTH 50

typedef enum pin_dir
{
	INPUT_PIN  = 0,
	OUTPUT_PIN = 1
} PIN_DIRECTION;


// ********** Function Prototypes **********

int gpio_export(unsigned int gpioPinNumber);
int gpio_unexport(unsigned int gpioPinNumber);
int gpio_set_direction(unsigned int gpioPinNumber, PIN_DIRECTION out_flag);
int gpio_set_value(unsigned int gpioPinNumber, unsigned int value);
int gpio_get_value(unsigned int gpioPinNumber, unsigned int *value);
int gpio_fd_open(unsigned int gpioPinNumber);
int gpio_fd_close(int fd);

#endif
