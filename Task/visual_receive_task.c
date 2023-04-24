#include "main.h"
#include "visual_receive_task.h"

float  Vision_Coff=0.1;
extern UART_HandleTypeDef huart4;
extern float Eular[3];

uint8_t  Visual_Buffer[VISAUAL_DATE_LEN];
Visual_date From_Vision_Data;

void visual_date(uint8_t *data)
{
	 if(*data==0x80 && (*(data+5))==0x7F)
 {
  From_Vision_Data.Pitch_High = *(data+1);
  From_Vision_Data.Pitch_Low = *(data+2);
  From_Vision_Data.Yaw_High = *(data+3);
  From_Vision_Data.Yaw_Low = *(data+4);
	From_Vision_Data.Vision_Pitch = ((float)(int16_t)(From_Vision_Data.Pitch_High<<8|From_Vision_Data.Pitch_Low)*90/32767)*Vision_Coff;
  From_Vision_Data.Vision_Yaw = ((float)(int16_t)(From_Vision_Data.Yaw_High<<8|From_Vision_Data.Yaw_Low)*90/32767)*Vision_Coff;
 }
}

void visual_date_t(uint8_t data)
{
	 if(data==0x80 && (data+5)==0x7F)
 {
  From_Vision_Data.Pitch_High = (data+1);
  From_Vision_Data.Pitch_Low = (data+2);
  From_Vision_Data.Yaw_High = (data+3);
  From_Vision_Data.Yaw_Low = (data+4);
	From_Vision_Data.Vision_Pitch = ((float)(int16_t)(From_Vision_Data.Pitch_High<<8|From_Vision_Data.Pitch_Low)*90/32767)*Vision_Coff;
  From_Vision_Data.Vision_Yaw = ((float)(int16_t)(From_Vision_Data.Yaw_High<<8|From_Vision_Data.Yaw_Low)*90/32767)*Vision_Coff;
 }
}
visual_send send[8];

void visual_send_date(void)
{
	uint16_t i=0;

//	send[1].date=Eular[1];
//	send[2].date=Eular[2];
	send[1].date=0;
	send[2].date=2222;
	for(i = 0; i<4; i++)
	{
		HAL_UART_Transmit(&huart4,&send[1].date_t[i],1,100);
	}
	
	for(i = 0; i<4; i++)
	{
		HAL_UART_Transmit(&huart4,&send[2].date_t[i],1,100);
	}
	
//		HAL_UART_Transmit(&huart4,&tail[0],1,100);
//		HAL_UART_Transmit(&huart4,&tail[1],1,100);
//		HAL_UART_Transmit(&huart4,&tail[2],1,100);
//		HAL_UART_Transmit(&huart4,&tail[3],1,100);
}
