#include "chassis_task.h" 
#include "can_receive.h"
#include "remote_receive.h"

#include "pid.h"
#include "math.h"


/*----------------------------------结构体-----------------------------*/
extern pid_type_def pid_chassis[8];
extern motor_measure_t motor_chassis[5];
extern motor_measure_t motor_gimbal[3];
extern RC_ctrl_t rc_ctrl;
rc_3508 rc_3508_t;








float YAW_MotorAngle_Proc(int16_t Angle)
{
	if(YAW_ZERO_DEGREE - Angle>4096)
	{
		Angle+=8192;
	}
	else if(YAW_ZERO_DEGREE - Angle<-4096)
	{
		Angle-=8192;
	}
	
  return (float)Angle;
}


void xy_speed(int32_t *speed, float MAX,float MIX)
{
    if(*speed > MAX)
		{
        *speed = MAX;
		}
    if(*speed < MIX)
		{ *speed = MIX;}
}

void chassis_pid_init()
{
	PID_init(&pid_chassis[1],11,0,0,5000,5000);
	PID_init(&pid_chassis[2],11,0,0,5000,5000);
	PID_init(&pid_chassis[3],11,0,0,5000,5000);
	PID_init(&pid_chassis[4],11,0,0,5000,5000);
	
	PID_init(&pid_chassis[5],40,0,0,6000,5000);
	PID_init(&pid_chassis[6],350,0,0,8000,10000);
}




void chassis_to_common(void)
{	
	
	rc_3508_t.wz_set = 0;
	
	rc_3508_t.wheel_speed[0] =  rc_3508_t.vx_set - rc_3508_t.vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
	rc_3508_t.wheel_speed[1] = -rc_3508_t.vx_set - rc_3508_t.vy_set + (CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
	rc_3508_t.wheel_speed[2] = -rc_3508_t.vx_set + rc_3508_t.vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
	rc_3508_t.wheel_speed[3] =  rc_3508_t.vx_set + rc_3508_t.vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
}


float Yaw_Angle_t = 0;
void chassis_to_gyro(void)
{
	float sin_yaw_x = 0.0f;
	float cos_yaw_y = 0.0f;	
	float Yaw_Angle;
	
	Yaw_Angle=YAW_ZERO_DEGREE - motor_gimbal[1].ecd;
	if(Yaw_Angle < 0)
	{
		Yaw_Angle += 8192;
	}
	Yaw_Angle_t=Yaw_Angle*2*3.1415926f/8192;

	if(sin_yaw_x!=0||cos_yaw_y!=0)
	{
		rc_3508_t.wz_set = 8000;
	}
	else
	{
		rc_3508_t.wz_set = 5000;
	}

	sin_yaw_x=-cos(Yaw_Angle_t) * rc_3508_t.vx_set + sin(Yaw_Angle_t) * rc_3508_t.vy_set;
	cos_yaw_y=-sin(Yaw_Angle_t) * rc_3508_t.vx_set - cos(Yaw_Angle_t) * rc_3508_t.vy_set;
	rc_3508_t.wheel_speed[0] =  sin_yaw_x - cos_yaw_y + ( CHASSIS_WZ_SET_SCALE - 1.0f)* MOTOR_DISTANCE_TO_CENTER + rc_3508_t.wz_set;//4
	rc_3508_t.wheel_speed[1] = -sin_yaw_x - cos_yaw_y + ( CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER + rc_3508_t.wz_set;//3
	rc_3508_t.wheel_speed[2] = -sin_yaw_x + cos_yaw_y + (-CHASSIS_WZ_SET_SCALE - 1.0f)* MOTOR_DISTANCE_TO_CENTER + rc_3508_t.wz_set;//2
	rc_3508_t.wheel_speed[3] =  sin_yaw_x + cos_yaw_y + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER + rc_3508_t.wz_set;//1

}


//底盘跟随
int16_t yaw_angle_t;
void chassis_yaw(void)
{	
	yaw_angle_t=YAW_MotorAngle_Proc(motor_gimbal[1].ecd);

	PID_calc(&pid_chassis[5],yaw_angle_t,YAW_ZERO_DEGREE);
	PID_calc(&pid_chassis[6],motor_gimbal[1].speed_rpm,pid_chassis[5].out);
//	if(pid_chassis[5].error[0] > 4000||pid_chassis[5].error[0]<-4000)
//		{
//		rc_3508_t.wz_set = 0;
//		}
//	else 
//		{
		rc_3508_t.wz_set = -pid_chassis[6].out;
//		}
		
	rc_3508_t.wheel_speed[0] =  rc_3508_t.vx_set - rc_3508_t.vy_set + ( CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
	rc_3508_t.wheel_speed[1] = -rc_3508_t.vx_set - rc_3508_t.vy_set + ( CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
	rc_3508_t.wheel_speed[2] = -rc_3508_t.vx_set + rc_3508_t.vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;
	rc_3508_t.wheel_speed[3] =  rc_3508_t.vx_set + rc_3508_t.vy_set + (-CHASSIS_WZ_SET_SCALE - 1.0f) * MOTOR_DISTANCE_TO_CENTER * rc_3508_t.wz_set;

}

void chassis_rc_dbus(void)
{			
	rc_3508_t.vx_set = rc_ctrl.rc.ch3 * 5000/660;
	rc_3508_t.vy_set = rc_ctrl.rc.ch2 * 5000/660;
	
	if(rc_ctrl.rc.s1 == 1)
	{
		switch (rc_ctrl.rc.s2)
		{
		case 1:
					chassis_to_common();
					break;
		case 2:
					chassis_to_gyro();
					break;
		case 3:
					chassis_yaw();
					break;
		}
	}
	
}

//pc
int Z, X, C;//z:底盘跟随  x:普通模式 c:小陀螺
void chassis_rc_pc(void)
{
	xy_speed(&rc_3508_t.vx_set,4000,-4000);
	xy_speed(&rc_3508_t.vy_set,4000,-4000);

	if(rc_ctrl.key.v ==1){
		rc_3508_t.vx_set+=4;
	}
	
	else if(rc_ctrl.key.v ==2){
		rc_3508_t.vx_set-=4;
	}
	
	else if(rc_ctrl.key.v ==4){
		rc_3508_t.vy_set-=4;
	}
	
	else if(rc_ctrl.key.v==8){
		rc_3508_t.vy_set+=4;
	}
	
	else if(rc_ctrl.key.v==5){//左上
		rc_3508_t.vx_set+=4;
		rc_3508_t.vy_set-=4;
	}
		else if(rc_ctrl.key.v==6){//左下
		rc_3508_t.vx_set-=4;
		rc_3508_t.vy_set-=4;
	}
		else if(rc_ctrl.key.v==9){//右上
		rc_3508_t.vx_set+=4;
		rc_3508_t.vy_set+=4;
	}
		else if(rc_ctrl.key.v==10){//右下
		rc_3508_t.vx_set-=4;
		rc_3508_t.vy_set+=4;
	}
	else
	{
		rc_3508_t.vx_set = 0;
  	rc_3508_t.vy_set = 0;
	}
	
	
	if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_X)
	{
		Z = 0;
		X = 1;
		C = 0;
	}
	if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_Z)
	{
		Z = 1;
		X = 0;
		C = 0;
	}
	if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_C)
	{
		Z = 0;
		X = 0;
		C = 1;
	}

	
	if(X == 1)
	{
		chassis_to_common();
	}
	if(C == 1)
	{
		chassis_to_gyro();
	}
	
	if(Z == 1)
	{
		chassis_yaw();
	}
	
}


void chassis_ctrl(void)
{	
		
	PID_calc(&pid_chassis[1],motor_chassis[1].speed_rpm,rc_3508_t.wheel_speed[0]);
	PID_calc(&pid_chassis[2],motor_chassis[2].speed_rpm,rc_3508_t.wheel_speed[1]);
	PID_calc(&pid_chassis[3],motor_chassis[3].speed_rpm,rc_3508_t.wheel_speed[2]);
	PID_calc(&pid_chassis[4],motor_chassis[4].speed_rpm,rc_3508_t.wheel_speed[3]);
	if (rc_ctrl.rc.s1 == 1)
	{
		chassis_rc_dbus();
		CAN_cmd_chassis(pid_chassis[1].out,pid_chassis[2].out,pid_chassis[3].out,pid_chassis[4].out);
	}

	if (rc_ctrl.rc.s1 == 3)
	{
		CAN_cmd_chassis(0,0,0,0);
		
	}

	if(rc_ctrl.rc.s1==2)
	{
		chassis_rc_pc();
		CAN_cmd_chassis(pid_chassis[1].out,pid_chassis[2].out,pid_chassis[3].out,pid_chassis[4].out);
	}
	
}



