#ifndef __SHOOT_TASK_H
#define __SHOOT_TASK_H
#include "stm32f4xx.h"



#define ECD_FULL_ROUND 8192
typedef uint8_t 	u8;
typedef uint16_t 	u16;
typedef uint32_t 	u32;

enum Trigger_Mode{
    Trigger_ModeStop,         //停止发射
    Trigger_Mode_ShootOne,    //单发
    Trigger_Mode_ShootMulti,  //连发
    Trigger_Mode_StuckSolve,  //解决卡弹问题
};


//拨盘ecd圈数监控
struct driver_ecd{
	uint8_t cnt;
	
};


/*接收到的云台电机的参数结构体*/
typedef struct{
	uint16_t   real_angle;
	uint16_t   pos_old;
	uint16_t   pos;
	float  			angle_err;				
	float  		angle_err_err;
  int32_t  POS_ABS;
	int32_t  angle_pos;
	int32_t   ref_pos;

}moto_measure_t;


//#define FILTER_BUF_LEN		5

///*接收到的云台电机的参数结构体*/
//typedef struct{
//	int16_t	 	speed_rpm;
//    float  	real_current;
//    int16_t  	given_current;
//    uint8_t  	hall;
//	uint16_t 	angle;				//abs angle range:[0,8191]
//	uint16_t 	last_angle;	//abs angle range:[0,8191]
//	uint16_t	offset_angle;
//	int32_t		round_cnt;
//	int32_t		total_angle;
//	u8			buf_idx;
//	u16			angle_buf[FILTER_BUF_LEN];
//	u16			fited_angle;
//	u32			msg_cnt;
//}moto_measure_t;







void driver_limit(uint16_t *a,uint16_t *MAX);

void shoot_pid_init(void);

void Motor_Angle_Cal(moto_measure_t *ptr);
void shoot_one(void);
void shoot_long(void);
void shoot_rc_pc(void);



void shoot_init(void);
void shoot_ctrl(void);



#endif


