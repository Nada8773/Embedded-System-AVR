/****************************************************************
 Author      : Nada Mohamed
 Data        : 20 Apr 2020
 Version     : v01
 Platform    : Atmega32
 File        : I2C_program.c
 Description : program file for i2c Driver
 ****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_config.h"
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_register.h"

#define I2C_PRESCALER_MASK     (u8)0xfC


/**********************************************************
 * @brief  initialize the Master
 * @param  void
 * @return void
 ***********************************************************/
void I2C_voidMasterInit(void)
{

	/* SCL Frequency =  CPU Clock Frequency / (16 + 2(TWBR)*( 4^(TWPS)) */

	/* Prescaler */
	TWCR &= I2C_PRESCALER_MASK ;
	TWCR |= I2C_PRESCALER ;

	TWBR =  (( CPU_CLOCK_FREQUENCY / CPU_SCL_FREQUENCY ) - 16 ) /(4^(TWCR & 0x03));

	SET_BIT(TWCR,TWCR_TWEA) ;
	SET_BIT(TWCR,TWCR_TWEN) ;

}


/**********************************************************
 * @brief initialize the slave
 * @param u8 (Copy_u8SlaveAddress)
 *             Slave Address (7 Bits) max Range 127
 * @return Std_ReturnType
			  E_OK     : input argument is valid
			  E_NOT_OK : input argument is Not valid
 ***********************************************************/
Std_ReturnType I2C_errSlaveInit(u8 Copy_u8SlaveAddress)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;
	if(Copy_u8SlaveAddress > 127)
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		TWAR = Copy_u8SlaveAddress << 1 ;  /* Slave Address */
		SET_BIT(TWCR,TWCR_TWEA) ;          /* Enable Acknowledge Bit */
		SET_BIT(TWCR,TWCR_TWEN) ;         /* Enable TWI */
	}

	return Local_u8I2CStatus ;
}


/**********************************************************
 * @brief   master send start condition
 * @param   void
 * @return Std_ReturnType
			  E_OK     : if start send successful
			  E_NOT_OK : if start send failed
 ***********************************************************/
Std_ReturnType I2C_errSendStartCondition(void)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;

	SET_BIT(TWCR,TWCR_TWSTA) ; /* Start Condition Bit */
	SET_BIT(TWCR,TWCR_TWINT) ;  /* Clear Interrupt Flag */

	while(!GET_BIT(TWCR,TWCR_TWINT));

	if( (TWSR & I2C_STATUS_CODE_MASK) != I2C_MASTER_START_ACK)
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		/* Do nothing */
	}
	return Local_u8I2CStatus ;
}

/**********************************************************
 * @brief   master send Restart condition
 * @param   void
 * @return Std_ReturnType
			  E_OK     : if start send successful
			  E_NOT_OK : if start send failed
 ***********************************************************/
Std_ReturnType I2C_errSendReStartCondition(void)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;

	SET_BIT(TWCR,TWCR_TWSTA) ; /* Start Condition Bit */
	SET_BIT(TWCR,TWCR_TWINT) ;  /* Clear Interrupt Flag */

	while(!GET_BIT(TWCR,TWCR_TWINT));

	if( (TWSR & I2C_STATUS_CODE_MASK) != I2C_MASTER_RSTART_ACK)
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		/* Do nothing */
	}
	return Local_u8I2CStatus ;
}


/**********************************************************
 * @brief Master Send slave address + write operation
 * @param u8 (Copy_u8SlaveAddress)
 *             Slave Address (7 Bits) max Range 127
 * @return Std_ReturnType
			  E_OK     : Send successfully
			  E_NOT_OK : Send failed
 ***********************************************************/
Std_ReturnType I2C_errSendSlaveAddressWrite(u8 Copy_u8SlaveAddress)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;


	TWDR = Copy_u8SlaveAddress << 1 ;   /* Slave Address */
	CLR_BIT(TWDR,TWDR_TWDR0) ;          /* Write Operation */

	CLR_BIT(TWCR,TWCR_TWSTA) ; /* Start Condition Bit */
	SET_BIT(TWCR,TWCR_TWINT) ;  /* Clear Interrupt Flag */
	/*
	 * Immediately after the application has cleared TWINT, the TWI will
   initiate transmission of the address packet.
	 */

	while(!GET_BIT(TWCR,TWCR_TWINT));

	if( (TWSR & I2C_STATUS_CODE_MASK) != I2C_MASTER_SLA_W_ACK)
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		/* Do nothing */
	}
	return Local_u8I2CStatus ;
}

/**********************************************************
 * @brief Master Send slave address + Read Operation
 * @param u8 (Copy_u8SlaveAddress)
 *             Slave Address (7 Bits) max Range 127
 * @return Std_ReturnType
			  E_OK     : Send successfully
			  E_NOT_OK : Send failed
 ***********************************************************/
Std_ReturnType I2C_errSendSlaveAddressRead(u8 Copy_u8SlaveAddress)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;


	TWDR = Copy_u8SlaveAddress << 1 ;   /* Slave Address */
	SET_BIT(TWDR,TWDR_TWDR0) ;          /* Read Operation */

	CLR_BIT(TWCR,TWCR_TWSTA) ; /* Start Condition Bit */
	SET_BIT(TWCR,TWCR_TWINT) ;  /* Clear Interrupt Flag */
	/*
	 * Immediately after the application has cleared TWINT, the TWI will
   initiate transmission of the address packet.
	 */

	while(!GET_BIT(TWCR,TWCR_TWINT));

	if( (TWSR & I2C_STATUS_CODE_MASK) != I2C_MASTER_RECEIVER_SLA_R_ACK)
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		/* Do nothing */
	}
	return Local_u8I2CStatus ;
}

/**********************************************************
 * @brief Master Send Data to Slave
 * @param u8 (Copy_u8Data)
 *             Slave Address (8 Bits) max Range 255
 * @return Std_ReturnType
			  E_OK     : Send successfully
			  E_NOT_OK : Send failed
 ***********************************************************/
Std_ReturnType I2C_errMasterSendData(u8 Copy_u8Data)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;


	TWDR = Copy_u8Data ;   /* Slave Address */
	SET_BIT(TWDR,TWDR_TWDR0) ;          /* Read Operation */

	SET_BIT(TWCR,TWCR_TWINT) ;  /* Clear Interrupt Flag */
	/*
	 * Immediately after the application has cleared TWINT, the TWI will
	   initiate transmission of the address packet.
	 */

	while(!GET_BIT(TWCR,TWCR_TWINT));

	if( (TWSR & I2C_STATUS_CODE_MASK) != I2C_MASTER_DATA_ACK )
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		/* Do nothing */
	}
	return Local_u8I2CStatus ;

}

/**********************************************************
 * @brief Master Read Data from the slave
 * @param u8* (Copy_pu8Data)
 *             pointer contain the Reading Data from the slave
 * @return Std_ReturnType
			  E_OK     : Request successfully
			  E_NOT_OK : Request failed
 ***********************************************************/
Std_ReturnType I2C_errMasterReceiveData(u8 * Copy_pu8Data)
{
	Std_ReturnType Local_u8I2CStatus = E_OK ;


	SET_BIT(TWCR,TWCR_TWINT) ;  /* Clear Interrupt Flag */


	while(!GET_BIT(TWCR,TWCR_TWINT));

	if( (TWSR & I2C_STATUS_CODE_MASK) != I2C_MASTER_RECEIVER_DATA_ACK )
	{
		Local_u8I2CStatus = E_NOT_OK ;
	}
	else
	{
		*Copy_pu8Data = TWDR ;
	}
	return Local_u8I2CStatus ;

}

/**********************************************************
 * @brief  Master Send Stop Condition
 * @param  void
 * @return void
 ***********************************************************/
void I2C_voidSendStopCondition(void)
{
	//Stop Condition
	SET_BIT(TWCR,TWCR_TWSTO);

	//Clear Flag
	SET_BIT(TWCR,TWCR_TWINT);
}



