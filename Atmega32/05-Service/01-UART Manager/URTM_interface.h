/****************************************************************
 * Author  : Nada Mohamed
 * Data    : 11 Mar2020
 * Version : v01
 *****************************************************************/
#ifndef URTM_INTERFACE_H
#define URTM_INTERFACE_H


#define  URTM_SEND_SYNC   		1
#define  URTM_SEND_ASYNC        2
#define  URTM_REC_SYNC          3
#define  URTM_REC_ASYNC         4

/*
 * JobType :-
 *         URTM_SEND_SYNC
 *         URTM_SEND_ASYNC
 *         URTM_REC_SYNC
 *         URTM_REC_ASYNC
 */
typedef struct
{
	u8  JobType           ;
	u8* DataBuffer		  ; /* Data To send */
	u8  Length            ; /* Data Length */
	void(*CallBack)(void) ; /* Call back notification function in case Asynch*/
}URTM_JobRequest;

/****************************************************************
 * brief : This function put the job Request into the Queue
 * Param : Copy_JobInfo
 *             container that contain information about job
 * return: Std_ReturnType
 *            E_OK     -> Request is accepted
 *            E_NOT_OK -> Request is not accepted
 ****************************************************************/
Std_ReturnType URTM_u8PerformJobRequest (URTM_JobRequest Copy_JobInfo);

#endif
