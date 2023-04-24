#ifndef __GAME_START_H
#define __GAME_START_H


#define abs(x) ((x)>0? (x):(-(x)))       //绝对值宏定义


/* 遥控器状态枚举 */
typedef enum 
{
	RC_DATEERR		= 0,   //遥控数据错误模式
	RC_NORMAL		= 1,   //系统正常模式
	RC_LOST			= 2,   //遥控失联模式
}RC_State_t;






/* 状态结构体 */
typedef struct 
{
	RC_State_t RC_state;
	
}Sys_Init_t;

#endif

