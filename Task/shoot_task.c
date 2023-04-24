#include "main.h"
#include "shoot_task.h"
#include "can_receive.h"
#include "pid.h"
#include "remote_receive.h"

extern motor_measure_t motor_shoot[5];
extern pid_type_def pid_shoot[8];
extern RC_ctrl_t rc_ctrl;
extern float shoot3_pid;
moto_measure_t  moto_shoot[2];




void shoot_pid_init()
{	//摩擦轮
	PID_init(&pid_shoot[1],10,0,0,1000,5000);
	PID_init(&pid_shoot[2],10,0,0,1000,5000);
	//拨盘
	PID_init(&pid_shoot[3],6 , 0, 0, 1000,15000);
	PID_init(&pid_shoot[4],10 ,  0, 0,2000,15000);
}


uint8_t cnt =1;

void Motor_Angle_Cal(moto_measure_t *ptr)
{
	
	ptr->real_angle= motor_shoot[3].ecd/8192.0f*360.0f;
	float  res1, res2;
	
	if(cnt)
	{
		ptr->pos_old=ptr->real_angle;
		cnt=0;
	}	
	ptr->pos = ptr->real_angle ;
	ptr->angle_err=ptr->pos- ptr->pos_old;
	
	if(ptr->angle_err>0) 	
	{
		res1=ptr->angle_err-360;
		res2=ptr->angle_err;
	}
	else
	{
		res1=ptr->angle_err+360;
		res2=ptr->angle_err;
	}
	
	if(ABS(res1)<ABS(res2)) 
	{
		ptr->angle_err_err = res1;
	}
	else
	{
		ptr->angle_err_err = res2;
	}
	
	ptr->POS_ABS += ptr->angle_err_err;
	ptr->pos_old  = ptr->pos;

}











//void get_moto_measure(moto_measure_t *ptr, CAN_HandleTypeDef* hcan)
//{

//	ptr->last_angle = ptr->angle;
//	ptr->angle =motor_shoot[3].ecd;
//	
//	
//	if(ptr->angle - ptr->last_angle > 4096)
//		ptr->round_cnt --;
//	else if (ptr->angle - ptr->last_angle < -4096)
//		ptr->round_cnt ++;
//	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
//}

///*this function should be called after system+can init */
//void get_moto_offset(moto_measure_t *ptr, CAN_HandleTypeDef* hcan)
//{
//	ptr->angle =motor_shoot[3].ecd;
//	ptr->offset_angle = ptr->angle;
//}

///**
//*@bref 电机上电角度=0， 之后用这个函数更新3510电机的相对开机后（为0）的相对角度。
//	*/
//void get_total_angle(moto_measure_t *p){
//	
//	int res1, res2, delta;
//	if(p->angle < p->last_angle){			//可能的情况
//		res1 = p->angle + 8192 - p->last_angle;	//正转，delta=+
//		res2 = p->angle - p->last_angle;				//反转	delta=-
//	}else{	//angle > last
//		res1 = p->angle - 8192 - p->last_angle ;//反转	delta -
//		res2 = p->angle - p->last_angle;				//正转	delta +
//	}
//	//不管正反转，肯定是转的角度小的那个是真的
//	if(ABS(res1)<ABS(res2))
//		delta = res1;
//	else
//		delta = res2;

//	p->total_angle += delta;
//	p->last_angle = p->angle;
//}








int v;
void shoot_one(void)
{
	if(rc_ctrl.mouse.press_l==1)
	{
		v++;
		if(v==1)
		{
			moto_shoot[0].ref_pos+=1620;
		}

	}
		else 
	{
		pid_shoot[4].out=0;
		v=0;
	}
	
}

void shoot_long(void)
{		
	if(rc_ctrl.mouse.press_l==1)
	{
		moto_shoot[0].ref_pos+=10;
	}
	
	else {
		pid_shoot[4].out=0;
	}
}


int shoot_1=1;
void shoot_rc_pc(void)
{	
	static uint8_t press_flag=1;
	if (press_flag==1&&rc_ctrl.key.v & KEY_PRESSED_OFFSET_F)
		{	
			HAL_Delay(20);		
			if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_F)
			{	
				press_flag=0;
				if(shoot_1==0)
				{shoot_1=1;}
				else	
				{shoot_1=0;}
				moto_shoot[0].POS_ABS=0;
				moto_shoot[0].ref_pos=0;
			}
			
		}
		if(press_flag==0&&rc_ctrl.key.v==0)
		{
			press_flag=1;
		}
	
		if(shoot_1==1)
		{
			shoot_one();
		}
		else
		{
			shoot_long();
		}
}



void shoot_init(void)
{
	shoot_rc_pc();
	PID_calc(&pid_shoot[1],	motor_shoot[1].speed_rpm ,-1000);
	PID_calc(&pid_shoot[2], motor_shoot[2].speed_rpm , 1000);
	PID_calc(&pid_shoot[3], moto_shoot[0].POS_ABS,moto_shoot[0].ref_pos);
	PID_calc(&pid_shoot[4], motor_shoot[3].speed_rpm , pid_shoot[3].out);
}

void shoot_ctrl(void)
{
	shoot_init();
	Motor_Angle_Cal(&moto_shoot[0]);

	if(rc_ctrl.rc.s1==2||rc_ctrl.rc.s1==1)
	{
		CAN_cmd_shoot(pid_shoot[1].out,pid_shoot[2].out);
	}
	if(rc_ctrl.rc.s1==3)
	{
		CAN_cmd_shoot(0,0);
	}
	
}


