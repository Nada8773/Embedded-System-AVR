/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 3 Mar2020
 * Version : v01
 *****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_register.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


#define ISR_RXC    13  /*Rx Complete*/
#define ISR_UDRE   14  /*USART Data Register Empty*/
#define ISR_TXC    15  /*USART, Tx Complete*/

/* pointer to function */
static void (*EndOfTransmitCB)(void) = NULL;
static void (*EndOfRecCB)(void)      = NULL ;
static void (*EndOfRec2CB)(u8)       = NULL ;

/* Global Variable */
static u8   UART_u8gTransmit ;
static u8 * UART_pu8gRecieve = NULL;
static u8 g_u8RecieveAsynch2Flag =0;

const u8 BaudRateValue[3][3]=
{
		/* 4800     ,  9600   , 115200 */
		{    0x67   ,  0x33   ,   0x03   },  /* Clock System 0 = 8MHz */
		{    154    ,  77     ,   6      }, /* Clock System 1 = 12MHz */
		{    0xcf   ,  0x67   ,  0x08    } /* Clock System 2 = 16MHz */
};

/******************************************************************
 * @brief initialize uart
 * @Param  void
 * @return void
 *****************************************************************/
void UART_voidInitialize(void)
{
	/* U2X=0 */
	CLR_BIT(UCSRA,1);

	/* Disable all interrupt */
	/*Enable RX & TX */
	/* 8 Character Bit */
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

	/* Asynchronous Mode
	 *  Character size = 8 bit
	 */
	UCSRC = ((1<<7) | (UART_u8_PARITY << UCSRC_UPM0) | (UART_u8_STOP_BITS << UCSRC_USBS) | (3<<UCSRC_UCSZ0));

	/* ASSIGN Baud Rate */
	UBRRL=BaudRateValue[UART_u8_SYS_FREQ ][UART_u8_BAUDRATE];
}

/******************************************************************
 * @brief Transmit data using uart synchronous
 * @Param Copy_u8Data :-
 *                    Data to transmit
 * @return Std_ReturnType :-
 *                    E_OK     -> data transmit successfully
 *                    E_NOT_OK -> data transmit Fail
 *****************************************************************/
Std_ReturnType UART_voidTransmitDataSynch (u8 Copy_u8Data)
{
	u32 Local_u32TimeOut=0;
	Std_ReturnType Local_u8Status=E_OK ;

	/* sand data on UDR */
	UDR_T = Copy_u8Data;

	while ( (GET_BIT(UCSRA,UCSRA_UDRE) == 0) && Local_u32TimeOut < UART_u32_TIME_OUT)
	{
		Local_u32TimeOut++;
	}
	/* TimeOUT happened */
	if(Local_u32TimeOut >= UART_u32_TIME_OUT)
	{
		Local_u8Status = E_NOT_OK ;
	}
	else
	{
		CLR_BIT(UCSRA,6);
	}
	return Local_u8Status;
}

/******************************************************************
 * @brief Receive data using uart synchronous
 * @Param Copy_u8Data :-
 *                    Data to receive
 * @return Std_ReturnType :-
 *                    E_OK     -> data receive successfully
 *                    E_NOT_OK -> data transmit Fail
 *****************************************************************/
Std_ReturnType UART_u8RecieveSynch(u8* Copy_pu8Data )
{
	u32 Local_u32TimeOut=0;
	Std_ReturnType Local_u8Status=E_OK ;

	while ((GET_BIT(UCSRA,UCSRA_RXC) == 0)  && Local_u32TimeOut < UART_u32_TIME_OUT)
	{
		Local_u32TimeOut++;
	}
	/* TimeOUT happened */
	if(Local_u32TimeOut >= UART_u32_TIME_OUT)
	{
		Local_u8Status = E_NOT_OK ;
	}
	else
	{
		*Copy_pu8Data = UDR_R;
	}
	return Local_u8Status;
}

/******************************************************************
 * @brief Transmit data using uart Asynchronous
 * @Param Copy_u8Data :-
 *                    Data to transmit
 *        Copy_ptr    :-
 *                    Pointer to function used for call back
 * @return Std_ReturnType :-
 *                    E_OK     -> input argument is valid
 *                    E_NOT_OK -> input argument isnot valid
 *****************************************************************/
Std_ReturnType UART_voidTransmitDataAsynch (u8 Copy_u8Data, void(*Copy_ptr)(void))
{
	Std_ReturnType Local_u8Status = E_OK ;

	if((Copy_ptr == NULL)||(Copy_u8Data == NULL))
	{
		Local_u8Status = E_NOT_OK ;
	}

	else
	{
		/* Set recieved data  */
		UDR_T = Copy_u8Data;

		/* Enable TX interrupt */
		SET_BIT(UCSRB,UCSRB_TXCIE);

		/*save the callback address */
		EndOfTransmitCB = Copy_ptr;

	}
	return Local_u8Status ;
}


/******************************************************************
 * @brief Recieve data using uart Asynchronous
 * @Param Copy_u8Data :-
 *                    pointer to the recieved data
 *        Copy_ptr    :-
 *                    pointer to function used as call back function
 *
 * @return Std_ReturnType :-
 *                    E_OK     -> input argument is valid
 *                    E_NOT_OK -> input argument isnot valid
 *****************************************************************/
Std_ReturnType UART_u8RecieveAsynch(u8* Copy_pu8Data, void(*Copy_ptr)(void))
{
	Std_ReturnType Local_u8Status = E_OK ;

	g_u8RecieveAsynch2Flag = 0;

	if((Copy_ptr == NULL)||(Copy_pu8Data == NULL))
	{
		Local_u8Status = E_NOT_OK ;
	}
	else
	{
		if(GET_BIT(UCSRA,UCSRA_RXC) == 1)
		{
           *Copy_pu8Data = UDR_R;
			Copy_ptr();
		}
		else
		{

			SET_BIT(UCSRB,UCSRB_RXCIE);
			UART_pu8gRecieve = Copy_pu8Data;
			EndOfRecCB = Copy_ptr;
		}

	}
	return Local_u8Status;

}


/******************************************************************
 * @brief Recieve data using uart Asynchronous
 * @Param
 *        Copy_ptr    :-
 *                    pointer to function used as call back function
 *
 * @return Std_ReturnType :-
 *                    E_OK     -> input argument is valid
 *                    E_NOT_OK -> input argument isnot valid
 *****************************************************************/

Std_ReturnType UART_u8RecieveAsynch2(void(*Copy_ptr)(u8))
{
	Std_ReturnType Local_u8Status = E_OK ;

	g_u8RecieveAsynch2Flag = 1;
	if(Copy_ptr == NULL)
	{
		Local_u8Status = E_NOT_OK ;
	}
	else
	{
		if(GET_BIT(UCSRA,UCSRA_RXC) == 1)
		{
			Copy_ptr(UDR_R);

		}
		else
		{
			// Enable Receive interrupt
			SET_BIT(UCSRB,UCSRB_RXCIE);
			EndOfRecCB=Copy_ptr;
		}
	}
	return Local_u8Status;
}

/******************************************* Interrupt ****************************/

#define ISR(NO)                           void __vector_##NO(void) __attribute__((signal));   \
		                                  void __vector_##NO(void)
/* Transmit Complete */
ISR(ISR_TXC)
{
	/* Disable interrupt */
	CLR_BIT(UCSRB,UCSRB_TXCIE);

	/* Call back Function */
	EndOfTransmitCB();

}

/* Recieve complete */
ISR(ISR_RX)
{
	/* Disable interrupt */
	CLR_BIT(UCSRB,UCSRB_RXCIE);

	if(g_u8RecieveAsynch2Flag ==1 )
	{
	/* Call back Function */
	EndOfRec2CB(UDR_R);
	}
	else
	{
		EndOfRecCB();
	}

}


