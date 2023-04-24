#include "vofa_task.h"
#include "CAN_receive.h"
#include "pid.h"

extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart5;

vofa_date vofa_date_t[8];
unsigned char tail[6] = {0x00, 0x00, 0x80, 0x7f, 0x0D, 0x0A}; 
unsigned char huan=0x0D; 
unsigned char huan1=0x0A; 

extern pid_type_def pid_shoot[5];
extern pid_type_def pid_gimbal[5];
extern float Eular[3];





void vofa_send(void)
{
	uint16_t i=0;

//	vofa_date_t[1].c=Eular[1];
//	vofa_date_t[2].c=Eular[2];
//	vofa_date_t[3].c=pid_gimbal[1].set;
//	vofa_date_t[4].c=pid_gimbal[2].set;
	vofa_date_t[1].c=1111;
	vofa_date_t[2].c=2222;
	for(i = 0; i<4; i++)	
	{
		HAL_UART_Transmit(&huart6,&vofa_date_t[1].b[i],1,100);
	}


	for(i = 0; i<4; i++)
	{
		HAL_UART_Transmit(&huart6,&vofa_date_t[2].b[i],1,100);
	}


//	for(i = 0; i<4; i++)
//	{
//		HAL_UART_Transmit(&huart6,&vofa_date_t[3].b[i],1,100);
//	}
//	
//	for(i = 0; i<4; i++)
//	{
//		HAL_UART_Transmit(&huart6,&vofa_date_t[4].b[i],1,100);
//	}
	
		HAL_UART_Transmit(&huart6,&tail[0],1,100);
		HAL_UART_Transmit(&huart6,&tail[1],1,100);
		HAL_UART_Transmit(&huart6,&tail[2],1,100);
		HAL_UART_Transmit(&huart6,&tail[3],1,100);
//		HAL_UART_Transmit(&huart6,&tail[4],1,100);
//		HAL_UART_Transmit(&huart6,&tail[5],1,100);

}

