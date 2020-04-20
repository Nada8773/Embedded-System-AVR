/****************************************************************
 Author      : Nada Mohamed
 Data        : 20 Apr 2020
 Version     : v01
 Platform    : Atmega32
 File        : I2C_interface.h
 Description : interfaces header file for i2c
 ****************************************************************/

#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

/* TWCR PINS */

#define TWCR_TWINT               7U
#define TWCR_TWEA                6
#define TWCR_TWSTA               5U
#define TWCR_TWSTO               4U
#define TWCR_TWWC                3U
#define TWCR_TWEN                2U
#define TWCR_TWIE                0U


/* TWSR PINS */
#define TWSR_TWPS1               1
#define TWSR_TWPS0               0


/* TWDR PINS */
#define TWDR_TWDR0               0

#define I2C_STATUS_CODE_MASK   0xF8
/* Status Codes */
/* Master Transmit */

#define I2C_MASTER_START_ACK                0x08
#define I2C_MASTER_RSTART_ACK               0x10
#define I2C_MASTER_SLA_W_ACK                0x18
#define I2C_MASTER_DATA_ACK                 0x28



/* Master Receiver */

#define I2C_MASTER_RECEIVER_START_ACK          0x08
#define I2C_MASTER_RECEIVER_RSTART_ACK         0x10
#define I2C_MASTER_RECEIVER_SLA_R_ACK          0x40
#define I2C_MASTER_RECEIVER_DATA_ACK           0x50






#endif
