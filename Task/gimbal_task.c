#include "gimbal_task.h"
#include "can_receive.h"
#include "remote_receive.h"
#include "pid.h"
#include "visual_receive_task.h"
#include "imu_data_decode.h"


#define Remote_dB 0.00000001f
#define PC_dB 		0.000000001f

extern int16_t Gyo[3];
extern float Eular[3];
extern RC_ctrl_t rc_ctrl; 
extern Visual_date From_Vision_Data;

extern motor_measure_t motor_gimbal[3];
extern pid_type_def pid_shoot[5];
extern pid_type_def pid_gimbal[5];

float shoot3_pid;

void gimbal_pid_init()
{
	PID_init(&pid_gimbal[1],12 ,0  ,0,20000,15000);
	PID_init(&pid_gimbal[2],300,0.1,0,20000,15000);
	PID_init(&pid_gimbal[3],15 ,0  ,0,20000,15000);
	PID_init(&pid_gimbal[4],105,0  ,0,20000,15000);
}


void pitch_limit(float *a, float imu_MAX,float imu_MIX)
{
    if(*a > imu_MAX)
        *a = imu_MAX;
		
    if(*a < imu_MIX)
        *a = imu_MIX;
}

float yaw_limit(float *a)
{
	if(*a-Eular[2] >180)    
	{
		*a =*a-360;        
	}
	else if(*a-Eular[2] <-180)
	{
		*a =*a+ 360;
	}
		return *a;
}


float x= 0;
float z=0;

void gimbal_rc_dbus(void)
{
	x=x+RC_CH0*Remote_dB;
	z=z+RC_CH1*Remote_dB;
}


void gimbal_rc_pc(void)
{
	x=x+RC_CH0*PC_dB;
	z=z+RC_CH1*PC_dB;
}


void yaw_pitch_gimbal(void)
{
	yaw_limit(&x);
	PID_calc(&pid_gimbal[1],Eular[2],x);
	PID_calc(&pid_gimbal[2],Gyo[2]/10,pid_gimbal[1].out);

	//Pitch
	pitch_limit(&z,18,-30);//(18,-38)
	PID_calc(&pid_gimbal[3],Eular[1],z);
	PID_calc(&pid_gimbal[4],Gyo[0]/10,pid_gimbal[3].out);
}


void visual_giambal(void)
{		
  //Yaw	
	float visual_x=x+From_Vision_Data.Vision_Pitch;
	yaw_limit(&visual_x);	
	PID_calc(&pid_gimbal[1],Eular[2],visual_x);
	PID_calc(&pid_gimbal[2],Gyo[2]/10,pid_gimbal[1].out);

	//Pitch
	float visual_y=x+From_Vision_Data.Vision_Yaw;
	pitch_limit(&visual_y,30,-18);
	PID_calc(&pid_gimbal[3],Eular[1],visual_y);
	PID_calc(&pid_gimbal[4],Gyo[0]/10,pid_gimbal[3].out);
}


	

extern uint32_t imu_off_line_time;

void gimbal_ctrl(void)
{


	yaw_pitch_gimbal();
	if (rc_ctrl.rc.s1==1)
	{	
		gimbal_rc_dbus();
		CAN_cmd_gimbal_pitch(pid_gimbal[4].out,pid_shoot[4].out);
		CAN_cmd_gimbal_yaw(pid_gimbal[2].out);
	}
	
	if (rc_ctrl.rc.s1==3)
	{	
			CAN_cmd_gimbal_pitch(0,0);
			CAN_cmd_gimbal_yaw(0);
	}
	
	if (rc_ctrl.rc.s1==2)
	{	
		gimbal_rc_pc();
		CAN_cmd_gimbal_pitch(pid_gimbal[4].out,pid_shoot[4].out);
		CAN_cmd_gimbal_yaw(pid_gimbal[2].out);
	}

}








//void gimbal_pid(void)
//{
//	if(rc_ctrl.rc.s2==1)
//	{	//Yaw
//		PID_calc(&pid_gimbal[1],Eular[2],160);
//		PID_calc(&pid_gimbal[2],Gyo[2]/10,pid_gimbal[1].out);
//		//Pitch
//		PID_calc(&pid_gimbal[3],Eular[1],25);
//		PID_calc(&pid_gimbal[4],Gyo[0]/10,pid_gimbal[3].out);

//	}
//	
//		else if(rc_ctrl.rc.s2==3)
//	{
//		PID_calc(&pid_gimbal[1],Eular[2],140);
//		PID_calc(&pid_gimbal[2],Gyo[2]/10,pid_gimbal[1].out);
//		
//		PID_calc(&pid_gimbal[3],Eular[1],5);
//		PID_calc(&pid_gimbal[4],Gyo[0]/10,pid_gimbal[3].out);
//	}
//	
//		else if(rc_ctrl.rc.s2==2)
//	{
//		PID_calc(&pid_gimbal[1],Eular[2],120);
//		PID_calc(&pid_gimbal[2],Gyo[2]/10,pid_gimbal[1].out);
//		
//		PID_calc(&pid_gimbal[3],Eular[1],-15);
//		PID_calc(&pid_gimbal[4],Gyo[0]/10,pid_gimbal[3].out);
//	}

//}



