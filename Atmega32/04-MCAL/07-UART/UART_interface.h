/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 9 Mar2020
 * Version : v01
 *****************************************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

/******************************************************************
 * @brief initialize uart
 * @Param  void
 * @return void
 *****************************************************************/
void UART_voidInitialize(void);

/*****************************************************************
 * @brief Transmit data using uart synchronous
 * @Param Copy_u8Data :-
 *                    Data to transmit
 * @return Std_ReturnType :-
 *                    E_OK     -> data transmit successfully
 *                    E_NOT_OK -> data transmit Fail
 ****************************************************************/
Std_ReturnType UART_voidTransmitDataSynch (u8 Copy_u8Data);

/******************************************************************
 * @brief Receive data using uart synchronous
 * @Param Copy_u8Data :-
 *                    Data to receive
 * @return Std_ReturnType :-
 *                    E_OK     -> data receive successfully
 *                    E_NOT_OK -> data transmit Fail
 *****************************************************************/
Std_ReturnType UART_u8RecieveSynch(u8* Copy_u8Data);

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
Std_ReturnType UART_voidTransmitDataAsynch (u8 Copy_u8Data, void(*Copy_ptr)(void));

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
Std_ReturnType UART_u8RecieveAsynch(u8* Copy_pu8Data, void(*Copy_ptr)(void));

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
Std_ReturnType UART_u8RecieveAsynch2(void(*Copy_ptr)(u8));

#endif
