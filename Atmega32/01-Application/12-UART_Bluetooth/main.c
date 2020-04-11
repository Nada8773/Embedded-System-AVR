
 /****************************************************************
 * Author 	: Nada Mohamed
 * Data    	: 11 Apr 2020
 * Version 	: v01
 * Description 	: Using Bluetooth HC05 to recieve signal from mobile 
                  Application and transmit it to the microcontroller 
 *****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "UART_interface.h"

static 	u8  Data_R[1] ;
void Recieve_CallBack(void)
{
	if(Data_R[0] == 'F')
	{
		SetPinVal('B',0,1); // set pin on
	}
}

/*
void Recieve_CallBack2(u8 Data_Rec)
{
	if(Data_Rec == 'F')
	{
		SetPinVal('B',0,1); // set pin on
	}
}*/

int main()
{
	/********** Asynchronous Test ***************/
	SetPinDir('B',0,1);
	SetPinVal('B',0,0); // set pin on
	UART_voidInitialize();
	while(1)
	{
		UART_u8RecieveAsynch(Data_R,Recieve_CallBack);
	    //UART_u8RecieveAsynch2(Recieve_CallBack2);
	}


	/********** Synchronous Test ****************/
	/*
	u8  Data_R[1] ;
	SetPinDir('B',0,1);
	SetPinVal('B',0,0); // set pin on
	UART_voidInitialize();

   while(1)
   {
		UART_u8RecieveSynch(Data_R);

		if(Data_R[0] == 'F')
		{
			SetPinVal('B',0,1); // set pin on
		}

   }
   */
	return 0;
}
