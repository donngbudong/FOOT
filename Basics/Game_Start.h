#ifndef __GAME_START_H
#define __GAME_START_H


#define abs(x) ((x)>0? (x):(-(x)))       //����ֵ�궨��


/* ң����״̬ö�� */
typedef enum 
{
	RC_DATEERR		= 0,   //ң�����ݴ���ģʽ
	RC_NORMAL		= 1,   //ϵͳ����ģʽ
	RC_LOST			= 2,   //ң��ʧ��ģʽ
}RC_State_t;






/* ״̬�ṹ�� */
typedef struct 
{
	RC_State_t RC_state;
	
}Sys_Init_t;

#endif

