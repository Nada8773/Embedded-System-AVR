/****************************************************************
 Author      : Nada Mohamed
 Data        : 20 Apr 2020
 Version     : v01
 Platform    : Atmega32
 File        : I2C_interface.h
 Description : interfaces header file for i2c
 ****************************************************************/

#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H


#define CPU_CLOCK_FREQUENCY         8000000U
#define CPU_SCL_FREQUENCY           400000U


/* Options :-
 *  I2C_PRESCALER_1
	I2C_PRESCALER_4
	I2C_PRESCALER_16
	I2C_PRESCALER_64
 */
#define I2C_PRESCALER    I2C_PRESCALER_1
#endif
