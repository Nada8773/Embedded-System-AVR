/****************************************************************
 Author      : Nada Mohamed
 Data        : 20 Apr 2020
 Version     : v01
 Platform    : Atmega32
 File        : main
 Description :   write data  in EEPROM and  then read it
 	 	 	 	 and display it in LCD
 ****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "string.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "I2C_interface.h"

#include "EEPROM_interface.h"
#include "CLCD_interface.h"



/*
 * Description :-
 * write data  in EEPROM and  then read it
 * and display it in LCD
 */
int main(void)
{
	u8 Data;
	u8 Buffer[10];
	PortInitialize();
	I2C_voidMasterInit();

    CLCD_voidInitialize();
    EEPROM_u8WriteData(10,142);
    _delay_ms(10);
    EEPROM_u8ReadData(10 ,&Data);
	CLCD_voidWriteString(itoa(Data,Buffer,10));
	while(1);

	return 0;

}
