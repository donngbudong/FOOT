#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H
#include "stm32f4xx.h"                  // Device header
#include "stdio.h"


//#define CHASSIS_CAN hcan1
//#define GIMBAL_CAN hcan2
//#define SHOOT_CAN hcan2


//电机的类型和约定的id枚举类型。通过修改这里的值对应更改电机
typedef enum
{
    CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x201,
    CAN_3508_M2_ID = 0x202,
    CAN_3508_M3_ID = 0x203,
    CAN_3508_M4_ID = 0x204,

    CAN_YAW_MOTOR_ID = 0x205,
    CAN_PIT_MOTOR_ID = 0x206,//can2
    CAN_TRIGGER_DRIVER_ID = 0x207,
    CAN_GIMBAL_ALL_ID = 0x1FF,

    CAN_SHOOT_ALL_ID=0X200,
    CAN_SHOOT_3508_ID_1=0X201,
    CAN_SHOOT_3508_ID_2=0X202,
    
} can_id;

// 电机数据结构体。
typedef struct
{
    uint16_t chi_voltage;
    int16_t power;
    int16_t rong_voltage;
    uint8_t state;
}super_capacitor_t;

/*超级电容数据结构体*/
typedef struct
{
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint8_t temperate;
    int16_t last_ecd;
} motor_measure_t;
void get_motor_measure(motor_measure_t *ptr, uint8_t *data); 
void capacitance_date(super_capacitor_t *ptr, uint8_t *data);                                

void CAN_cmd_capacitance(int16_t size);
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
void CAN_cmd_gimbal_yaw( int16_t yaw);
void CAN_cmd_gimbal_pitch(int16_t pitch,int16_t driver);
void CAN_cmd_shoot( int16_t shoot1,int16_t shoot2);


#endif

