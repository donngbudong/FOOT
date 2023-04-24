#ifndef __REMOTE_RECEIVE_H
#define __REMOTE_RECEIVE_H
#include "main.h"
#include "stdbool.h"
#include "Game_Start.h"






typedef struct
{
	struct
	{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;
		int16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;
	
	struct
	{
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t press_l;
    uint8_t press_r;
	}mouse;
	struct
	{
		uint16_t v;
	}key;
	
}RC_ctrl_t;
extern RC_ctrl_t rc_ctrl;


/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)-660 )
#define RC_CH_VALUE_OFFSET ((uint16_t)0)
#define RC_CH_VALUE_MAX ((uint16_t)660)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
#define RC_SW_ERR ((uint16_t)4)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W            ((uint16_t)1 << 0)
#define KEY_PRESSED_OFFSET_S            ((uint16_t)1 << 1)
#define KEY_PRESSED_OFFSET_A            ((uint16_t)1 << 2)
#define KEY_PRESSED_OFFSET_D            ((uint16_t)1 << 3)
#define KEY_PRESSED_OFFSET_SHIFT        ((uint16_t)1 << 4)
#define KEY_PRESSED_OFFSET_CTRL         ((uint16_t)1 << 5)
#define KEY_PRESSED_OFFSET_Q            ((uint16_t)1 << 6)
#define KEY_PRESSED_OFFSET_E            ((uint16_t)1 << 7)
#define KEY_PRESSED_OFFSET_R            ((uint16_t)1 << 8)
#define KEY_PRESSED_OFFSET_F            ((uint16_t)1 << 9)
#define KEY_PRESSED_OFFSET_G            ((uint16_t)1 << 10)
#define KEY_PRESSED_OFFSET_Z            ((uint16_t)1 << 11)
#define KEY_PRESSED_OFFSET_X            ((uint16_t)1 << 12)
#define KEY_PRESSED_OFFSET_C            ((uint16_t)1 << 13)
#define KEY_PRESSED_OFFSET_V            ((uint16_t)1 << 14)
#define KEY_PRESSED_OFFSET_B            ((uint16_t)1 << 15)

/*遥控器数据*/
#define			RC_CH0              	rc_ctrl.rc.ch0
#define			RC_CH1              	rc_ctrl.rc.ch1
#define			RC_CH2              	rc_ctrl.rc.ch2
#define			RC_CH3              	rc_ctrl.rc.ch3
#define			RC_S1               	rc_ctrl.rc.s1      
#define 		RC_S2              		rc_ctrl.rc.s2
#define 		RC_SW               	rc_ctrl.rc.sw

/*鼠标三轴的移动速度*/
#define			MOUSE_X_MOVE_SPEED    (rc_ctrl.mouse.x)
#define			MOUSE_Y_MOVE_SPEED    (rc_ctrl.mouse.y)
#define			MOUSE_Z_MOVE_SPEED    (rc_ctrl.mouse.z)

/* 检测鼠标按键状态 */
#define			MOUSE_LEFT    				(rc_ctrl.mouse.press_l )
#define			MOUSE_RIGH   					(rc_ctrl.mouse.press_r )


void sbus_to_rc(volatile const uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl);
void DBUS_RC(uint8_t *sbus_buf);
void remote_control_init(void);
void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);


void RC_Ctrl(void);
void RC_State_Report(void);
RC_State_t RC_Check(void);
bool Judge_RC_Lost(void);
bool Judge_RC_DataErr(void);
void RC_Protect(void);


#define    IF_RC_DATAERR   Judge_RC_DataErr()
#define    IF_RC_LOST      Judge_RC_Lost()


#endif

