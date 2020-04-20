/****************************************************************
 Author  : Nada Mohamed 
 Data    : 15 Apr 2020
 Version : v01 
 ****************************************************************/
#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

Std_ReturnType EEPROM_u8WriteData(u16 Copy_u16Address ,u8 Copy_u8Data);
Std_ReturnType EEPROM_u8ReadData(u16 Copy_u16Address ,u8* Copy_pu8Data);
#endif
