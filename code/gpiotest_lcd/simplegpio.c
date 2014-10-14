/*  This work is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * 
 *  Copyright(c) 2014 Hong Moon 	All Rights Reserved
 */

// description: a simple gpio control
// name: Hong Moon (hsm5xw@gmail.com)
// date: 2014-Sept

#include "simplegpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>


int gpio_export(unsigned int gpioPinNumber)
{
	int fd, len;
	char buf[MAX_BUF_LENGTH];

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if( fd < 0){
		perror("failed to open gpio_export \n");
		return fd;		
	}

	len = snprintf(buf, sizeof(buf), "%d", gpioPinNumber);
	write(fd, buf, len);
	close(fd);

	return 0;
}

int gpio_unexport(unsigned int gpioPinNumber)
{
	int fd, len;
	char buf[MAX_BUF_LENGTH];

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if( fd < 0){
		perror("failed to open gpio_unexport \n");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d", gpioPinNumber);
	write(fd, buf, len);
	close(fd);

	return 0;
}

int gpio_set_direction(unsigned int gpioPinNumber, PIN_DIRECTION out_flag)
{
	int fd;
	char buf[MAX_BUF_LENGTH];

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpioPinNumber);

	fd = open(buf, O_WRONLY);
	if( fd < 0){
		perror("failed to open gpio_set_direction \n");
		return fd;
	}

	if( out_flag == OUTPUT_PIN)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);

	close(fd);
	return 0;
}

int gpio_set_value(unsigned int gpioPinNumber, unsigned int value)
{
	int fd;
	char buf[MAX_BUF_LENGTH];

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpioPinNumber);

	fd = open(buf, O_WRONLY);
	if( fd < 0){
		perror("failed to open gpio_set_value \n");
		return fd;
	}

	if( value == 0 )
		write(fd, "0", 2);
	else
		write(fd, "1", 2);

	close(fd);
	return 0;
}

int gpio_get_value(unsigned int gpioPinNumber, unsigned int *value)
{
	int fd;
	char buf[MAX_BUF_LENGTH];
	char ch;

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpioPinNumber);

	fd = open(buf, O_RDONLY);
	if( fd < 0){
		perror("failed to open gpio_get_value \n");
		return fd;
	}

	read(fd, &ch, 1);

	if( ch != '0')
		*value = 1;
	else
		*value = 0;

	close(fd);
	return 0;
}

int gpio_fd_open(unsigned int gpioPinNumber)
{
	int fd;
	char buf[MAX_BUF_LENGTH];

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpioPinNumber);

	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if( fd < 0){
		perror("failed to open gpio_fd_open \n");
	}
	return fd;
}

int gpio_fd_close(int fd)
{
	return close(fd);
}





