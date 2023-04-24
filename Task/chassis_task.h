#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H
#include "stm32f4xx.h"                  


#define Motor_180         4096
#define Motor_360         8192

#define CHASSIS_WZ_SET_SCALE  0.1f
#define MOTOR_DISTANCE_TO_CENTER 0.2f
#define PI 3.1415926
#define YAW_ZERO_DEGREE  7563//  7563

typedef struct
{
	int16_t wheel_speed[4];
	int32_t vx_set; 
	int32_t vy_set;
	int16_t wz_set;
	int16_t q;
}rc_3508;


float YAW_MotorAngle_Proc(int16_t Angle);

void chassis_pid_init(void);

void chassis_to_common(void);
void chassis_to_gyro(void);
void chassis_yaw(void);

void chassis_rc_dbus(void);
void chassis_rc_pc(void);
void chassis_ctrl(void);

#endif	
	
	

