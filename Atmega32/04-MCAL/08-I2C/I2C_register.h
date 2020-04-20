/****************************************************************
 Author      : Nada Mohamed
 Data        : 20 Apr 2020
 Version     : v01
 Platform    : Atmega32
 File        : I2C_interface.h
 Description : interfaces header file for i2c
 ****************************************************************/

#ifndef I2C_REGISTER_H
#define I2C_REGISTER_H


#define TWDR         *((volatile u8*)0x23)
#define TWAR         *((volatile u8*)0x22)
#define TWSR         *((volatile u8*)0x21)
#define TWBR         *((volatile u8*)0x20)
#define TWCR         *((volatile u8*)0x56)


#endif
