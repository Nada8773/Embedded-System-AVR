/****************************************************************
 Author      : Nada Mohamed
 Data        : 20 Apr 2020
 Version     : v01
 Platform    : Atmega32
 File        : I2C_interface.h
 Description : interfaces header file for i2c
 ****************************************************************/
#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H



#define I2C_PRESCALER_1      (u8)0x00
#define I2C_PRESCALER_4      (u8)0x01
#define I2C_PRESCALER_16     (u8)0x02
#define I2C_PRESCALER_64     (u8)0x03

/**********************************************************
 * @brief  initialize the Master
 * @param  void
 * @return void
 ***********************************************************/
void I2C_voidMasterInit(void);

/**********************************************************
 * @brief initialize the slave
 * @param u8 (Copy_u8SlaveAddress)
 *             Slave Address (7 Bits) max Range 127
 * @return Std_ReturnType
			  E_OK     : input argument is valid
			  E_NOT_OK : input argument is Not valid
 ***********************************************************/
Std_ReturnType I2C_errSlaveInit(u8 Copy_u8SlaveAddress);

/**********************************************************
 * @brief   master send start condition
 * @param   void
 * @return Std_ReturnType
			  E_OK     : if start send successful
			  E_NOT_OK : if start send failed
 ***********************************************************/
Std_ReturnType I2C_errSendStartCondition(void);

/**********************************************************
 * @brief   master send Restart condition
 * @param   void
 * @return Std_ReturnType
			  E_OK     : if start send successful
			  E_NOT_OK : if start send failed
 ***********************************************************/
Std_ReturnType I2C_errSendReStartCondition(void);

/**********************************************************
 * @brief Master Send slave address + write operation
 * @param u8 (Copy_u8SlaveAddress)
 *             Slave Address (7 Bits) max Range 127
 * @return Std_ReturnType
			  E_OK     : Send successfully
			  E_NOT_OK : Send failed
 ***********************************************************/
Std_ReturnType I2C_errSendSlaveAddressWrite(u8 Copy_u8SlaveAddress);

/**********************************************************
 * @brief Master Send slave address + Read Operation
 * @param u8 (Copy_u8SlaveAddress)
 *             Slave Address (7 Bits) max Range 127
 * @return Std_ReturnType
			  E_OK     : Send successfully
			  E_NOT_OK : Send failed
 ***********************************************************/
Std_ReturnType I2C_errSendSlaveAddressRead(u8 Copy_u8SlaveAddress);

/**********************************************************
 * @brief Master Send Data to Slave
 * @param u8 (Copy_u8Data)
 *             Slave Address (8 Bits) max Range 255
 * @return Std_ReturnType
			  E_OK     : Send successfully
			  E_NOT_OK : Send failed
 ***********************************************************/
Std_ReturnType I2C_errMasterSendData(u8 Copy_u8Data);

/**********************************************************
 * @brief Master Read Data from the slave
 * @param u8* (Copy_pu8Data)
 *             pointer contain the Reading Data from the slave
 * @return Std_ReturnType
			  E_OK     : Request successfully
			  E_NOT_OK : Request failed
 ***********************************************************/
Std_ReturnType I2C_errMasterReceiveData(u8 * Copy_pu8Data);


/**********************************************************
 * @brief  Master Send Stop Condition
 * @param  void
 * @return void
 ***********************************************************/
void I2C_voidSendStopCondition(void);
#endif
