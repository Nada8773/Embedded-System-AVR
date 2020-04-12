/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 11 Mar2020
 * Version : v01
 *****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"

#include "URTM_interface.h"
#include "URTM_config.h"
#include "URTM_private.h"
#include "URTM_register.h"

/* Global Variable */
URTM_JobRequest URTM_QUEUE[URTM_u8_MAX_QUEUE_SIZE];
u8 URTM_QCurrent	 = 0 ;
u8 URTM_QNext    	 = 0 ;
u8 URTM_QAvailable   = URTM_u8_MAX_QUEUE_SIZE ;
u8 URTM_BusyFlag     = 0 ;
u8 URTM_NextByte     = 0 ;

/****************************************************************
 * brief : This function put the job Request into the Queue
 * Param : Copy_JobInfo
 *             container that contain information about job
 * return: Std_ReturnType
 *            E_OK     -> Request is accepted
 *            E_NOT_OK -> Request is not accepted
 ****************************************************************/
Std_ReturnType URTM_u8PerformJobRequest (URTM_JobRequest Copy_JobInfo)
{
	Std_ReturnType Local_u8Status=E_OK ;

	if(URTM_QAvailable > 0)
	{
		URTM_QAvailable--;
		/* Add the Job to the Queue*/
		URTM_QUEUE[URTM_QNext]= Copy_JobInfo;
		/* Increment the next */
		if(URTM_QNext == URTM_u8_MAX_QUEUE_SIZE-1)
		{
			URTM_QNext = 0;
		}
		else
		{
			URTM_QNext++;
		}
		voidExecute();
	}
	else
	{
		Local_u8Status = E_NOT_OK;
	}

	return Local_u8Status;
}

/****************************************************************
 * brief : private function to start the execute function
 * Param : void
 * return: void
 ****************************************************************/
static void voidExecute(void)
{
	if(URTM_BusyFlag == 0)
	{
		voidStart();
	}
	else
	{
		/* Do nothing */
	}
}

/****************************************************************
 * brief : private function for stating the execution
 * Param : void
 * return: void
 ****************************************************************/
static void voidStart(void)
{
	while(1)
	{
		if(URTM_QAvailable == URTM_u8_MAX_QUEUE_SIZE) /* Queue is Full */
		{
			/* Do nothing */
			URTM_BusyFlag=0;
			break;
		}
		else  /* Queue includes jobs */
		{
			URTM_BusyFlag=1;
			switch (URTM_QUEUE[URTM_QCurrent].JobType)
			{
			case  URTM_SEND_SYNC  : voidSendSych () ; break;
			case  URTM_REC_SYNC   : voidRecSych  () ; break;
			case  URTM_SEND_ASYNC : voidSendASych() ; break;
			case  URTM_REC_ASYNC  : voidRecASych () ; break;
			}
		}
	}
}

/****************************************************************
 * brief : private function to send data using uart Synchronous
 * Param : void
 * return: void
 ****************************************************************/
static void voidSendSych(void)
{
	u8 Local_u8Counter ;

	/* Start Job */
	for(Local_u8Counter=0;Local_u8Counter<URTM_QUEUE[URTM_QCurrent].Length;Local_u8Counter++)
	{
		UART_voidTransmitDataSynch(URTM_QUEUE[URTM_QCurrent].DataBuffer[Local_u8Counter]);
	}
	URTM_QAvailable++;

	if(URTM_QCurrent== URTM_u8_MAX_QUEUE_SIZE-1)
	{
		URTM_QCurrent=0;
	}
	else
	{
		URTM_QCurrent ++;
	}
}

/****************************************************************
 * brief : private function to recieve data using uart Synchronous
 * Param : void
 * return: void
 ****************************************************************/
static void voidRecSych(void)
{
	u8 Local_u8Counter;
	/* Start Job */
	for(Local_u8Counter=0;Local_u8Counter<URTM_QUEUE[URTM_QCurrent].Length;Local_u8Counter++)
	{
		UART_u8RecieveSynch(&(URTM_QUEUE[URTM_QCurrent].DataBuffer[Local_u8Counter]));
	}
	URTM_QAvailable++;

	if(URTM_QCurrent== URTM_u8_MAX_QUEUE_SIZE-1)
	{
		URTM_QCurrent=0;
	}
	else
	{
		URTM_QCurrent ++;
	}


}


/****************************************************************
 * brief : private function to send data using uart ASynchronous
 * Param : void
 * return: void
 ****************************************************************/
static void voidSendASych(void)
{
	URTM_NextByte =0;
	UART_voidTransmitDataAsynch(URTM_QUEUE[URTM_QCurrent].DataBuffer[URTM_NextByte], AsynchCallBack);
	URTM_NextByte++;
}
/****************************************************************
 * brief : private function to recieve data using uart ASynchronous
 * Param : void
 * return: void
 ****************************************************************/
static void voidRecASych(void)
{
	URTM_NextByte =0;
	UART_u8RecieveAsynch(&(URTM_QUEUE[URTM_QCurrent].DataBuffer[URTM_NextByte]), AsynchCallBack);
	URTM_NextByte++;
}
/****************************************************************
 * brief : private function using as call back function for Asynchronous
 * Param : void
 * return: void
 ****************************************************************/
static void  AsynchCallBack(void)
{
	if(URTM_NextByte < URTM_QUEUE[URTM_QCurrent].Length)
	{
		switch(URTM_QUEUE[URTM_QCurrent].JobType)
		{
		case  URTM_SEND_ASYNC:
			UART_voidTransmitDataAsynch(URTM_QUEUE[URTM_QCurrent].DataBuffer[URTM_NextByte], AsynchCallBack);
			break;
		case  URTM_REC_ASYNC:
			UART_u8RecieveAsynch(&(URTM_QUEUE[URTM_QCurrent].DataBuffer[URTM_NextByte]), AsynchCallBack);
			break;
		}
		URTM_NextByte++;
	}
	else
	{
		URTM_QUEUE[URTM_QCurrent].CallBack();
		URTM_QAvailable++;

		if(URTM_QCurrent== URTM_u8_MAX_QUEUE_SIZE-1)
		{
			URTM_QCurrent=0;
		}
		else
		{
			URTM_QCurrent ++;
		}
		URTM_BusyFlag=0 ;
	}

}


