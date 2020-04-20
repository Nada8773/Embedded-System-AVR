/****************************************************************
 Author  : Nada Mohamed 
 Data    : 15 Apr 2020
 Version : v01 
 ****************************************************************/

#include "STD_TYPES.h"

#include "I2C_interface.h"

#include "EEPROM_config.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

/***************
 * EEPROM -> 8K
 ***************/

Std_ReturnType EEPROM_u8WriteData(u16 Copy_u16Address ,u8 Copy_u8Data)
{

	Std_ReturnType Local_u8ReturnState = E_OK ;

	/* Start Condition */
	I2C_errSendStartCondition();

	/* slave Address */
	I2C_errSendSlaveAddressWrite((EEPROM_FIXED_ADDRESS) | (EEPROM_A2_VALUE <<2 ) |((Copy_u16Address>>8)&3));

	/* Send Byte Address */
	I2C_errMasterSendData((u8)Copy_u16Address);

	/* Send data */
	I2C_errMasterSendData(Copy_u8Data);

	/* Stop Condition */
	I2C_voidSendStopCondition();


	return Local_u8ReturnState ;
}

Std_ReturnType EEPROM_u8ReadData(u16 Copy_u16Address ,u8* Copy_pu8Data)
{
	Std_ReturnType Local_u8ReturnState = E_OK ;

	/* Start Condition */
	I2C_errSendStartCondition();

	/* Send Slave Address with w */
	I2C_errSendSlaveAddressWrite((EEPROM_FIXED_ADDRESS) | (EEPROM_A2_VALUE <<2 ) |((Copy_u16Address>>8)&3));

	/* Send Byte Address */
	I2C_errMasterSendData((u8)Copy_u16Address);

	/* Repeated start condition */
	I2C_errSendStartCondition();

	/* Send Slave Address with R */
	I2C_errSendSlaveAddressRead((EEPROM_FIXED_ADDRESS) | (EEPROM_A2_VALUE <<2 ) |((Copy_u16Address>>8)&3));

	/* Send data */
	I2C_errMasterReceiveData(Copy_pu8Data);

	/* Stop Condition */
	I2C_voidSendStopCondition();

	return Local_u8ReturnState ;
}

