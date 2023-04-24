#include "remote_receive.h"
#include "main.h"
#include "Game_Start.h"

extern IWDG_HandleTypeDef hiwdg;
uint32_t  dbus_imu_off_line_time = 0;

RC_ctrl_t rc_ctrl;

void sbus_to_rc(volatile const uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl)
{
    if (sbus_buf == NULL || rc_ctrl == NULL)
    {
        return;
    }

		rc_ctrl->rc.ch0 = (sbus_buf[0] | (sbus_buf[1] << 8)) & 0x07ff;        //!< Channel 0
    rc_ctrl->rc.ch1 = ((sbus_buf[1] >> 3) | (sbus_buf[2] << 5)) & 0x07ff; //!< Channel 1
    rc_ctrl->rc.ch2 = ((sbus_buf[2] >> 6) | (sbus_buf[3] << 2) |          //!< Channel 2
	(sbus_buf[4] << 10)) &0x07ff;
    rc_ctrl->rc.ch3 = ((sbus_buf[4] >> 1) | (sbus_buf[5] << 7)) & 0x07ff; //!< Channel 3
    rc_ctrl->rc.s1 = ((sbus_buf[5] >> 4) & 0x0003);                  //!< Switch left
    rc_ctrl->rc.s2 = ((sbus_buf[5] >> 4) & 0x000C) >> 2;                       //!< Switch right
    rc_ctrl->mouse.x = sbus_buf[6] | (sbus_buf[7] << 8);                    //!< Mouse X axis
    rc_ctrl->mouse.y = sbus_buf[8] | (sbus_buf[9] << 8);                    //!< Mouse Y axis
    rc_ctrl->mouse.z = sbus_buf[10] | (sbus_buf[11] << 8);                  //!< Mouse Z axis
    rc_ctrl->mouse.press_l = sbus_buf[12];                                  //!< Mouse Left Is Press 
    rc_ctrl->mouse.press_r = sbus_buf[13];                                  //!< Mouse Right Is Press
    rc_ctrl->key.v = sbus_buf[14] | (sbus_buf[15] << 8);                    //!< KeyBoard value
//    rc_ctrl.rc.ch[4] = sbus_buf[16] | (sbus_buf[17] << 8);                 //NULL

    rc_ctrl->rc.ch0 -= 1024;
    rc_ctrl->rc.ch1 -= 1024;
    rc_ctrl->rc.ch2 -= 1024;
    rc_ctrl->rc.ch3 -= 1024;
		
	if(rc_ctrl->rc.ch0 <= 5 && rc_ctrl->rc.ch0 >= -5)
		rc_ctrl->rc.ch0 = 0;
  if(rc_ctrl->rc.ch1 <= 5 && rc_ctrl->rc.ch1 >= -5)
    rc_ctrl->rc.ch1 = 0;
  if(rc_ctrl->rc.ch2 <= 5 && rc_ctrl->rc.ch2>= -5)
    rc_ctrl->rc.ch2 = 0;
  if(rc_ctrl->rc.ch3 <= 5 && rc_ctrl->rc.ch3 >= -5)
    rc_ctrl->rc.ch3 = 0;
	
	if(rc_ctrl->mouse.x <= 5 && rc_ctrl->mouse.x >= -5)
		rc_ctrl->mouse.x = 0;
  if(rc_ctrl->mouse.y <= 10 && rc_ctrl->mouse.y >= -10)
    rc_ctrl->mouse.y = 0;

}



extern Sys_Init_t System;//系统状态

/*mode切换*/
void Rc_mode_ctrl(void)
{
	
	
	
}

//
void RC_Ctrl(void)
{
	/*遥控器自检*/
	RC_State_Report();
	if(System.RC_state==RC_NORMAL)
	{
		Rc_mode_ctrl();
	}
	
}

/*遥控器数据状态上报*/
void RC_State_Report(void)
{
 	System.RC_state = RC_Check();
}


/*遥控器总自检*/
RC_State_t RC_Check(void)
{
  static RC_State_t res;
  res = RC_NORMAL;
  if(IF_RC_LOST)
    res = RC_LOST;
  if(IF_RC_DATAERR)
    res = RC_DATEERR;
  return res;
}


/*遥控器数据自检*/
bool Judge_RC_DataErr(void)
{
  static bool res ;
  res = false;
  if( ((RC_S1 != 1)&&(RC_S1 != 2)&&(RC_S1 != 3)) || ((RC_S2 != 1)&&(RC_S2 != 2)&&(RC_S2 != 3)) )
    res = true;
  else if(abs(RC_CH0)>660 ||
          abs(RC_CH1)>660 || 
          abs(RC_CH2)>660 ||
          abs(RC_CH3)>660)
    res = true;
	return res;
}


/*遥控器连接自检*/
extern uint32_t  Remote_time;
bool Judge_RC_Lost(void)
{
  static bool res ;
  res = false;
  if(HAL_GetTick() >= Remote_time)
    res = true;
  return res;
}


/*遥控器自我保护*/
void RC_Protect(void)
{
  RC_CH0 = RC_CH_VALUE_OFFSET;
  RC_CH1 = RC_CH_VALUE_OFFSET;
  RC_CH2 = RC_CH_VALUE_OFFSET;
  RC_CH3 = RC_CH_VALUE_OFFSET;
  RC_S1 = RC_SW_MID;
  RC_S2 = RC_SW_MID;	
  MOUSE_X_MOVE_SPEED = 0;
  MOUSE_Y_MOVE_SPEED = 0;
  MOUSE_Z_MOVE_SPEED = 0;
  MOUSE_LEFT = 0;
  MOUSE_RIGH = 0;
}

