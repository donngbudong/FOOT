#include "system.h"
#include "remote_receive.h"
#include "Game_Start.h"

uint32_t Imu_time = 0;//������
uint32_t Remote_time = 0;//ң����
uint32_t Refer_time = 0;//����ϵͳ

extern Sys_Init_t System;//ϵͳ״̬




////ģ�鳬ʱ���Ӽ�ʱ��ʼ��
//void Time_Init(void)
//{
//	Imu_time=HAL_GetTick();
//  Remote_time = HAL_GetTick();
//  Refer_time = HAL_GetTick();
//  CAN1_time = HAL_GetTick();
//  CAN2_time = HAL_GetTick();
//}



/* ϵͳ״̬������ */
void system_state_Ctrl(void)
{
  RC_Ctrl();
  switch (System.RC_state)
  {
    case RC_NORMAL:
//      System_Normal_process();
      break;    
		
    case RC_DATEERR:
			RC_Protect();
			break;
    
    case RC_LOST :
			RC_Protect();
      break;
  }      
}

//int w;
//void imu_state_ctrl(void)
//{
//	if(Imu_time<HAL_GetTick())
//	{
//		w++;
//	}
//}
//	
