#include "main.h"
#include "can_receive.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;


static CAN_TxHeaderTypeDef  gimbal_tx_message;
static uint8_t              gimbal_can_send_data[8];

static CAN_TxHeaderTypeDef  shoot_tx_message;
static uint8_t              shoot_can_send_data[8];

static CAN_TxHeaderTypeDef  chassis_tx_message;
static uint8_t              chassis_can_send_data[8];

static CAN_TxHeaderTypeDef  capacitance_tx_message;
static uint8_t              capacitance_can_send_data[8];

void get_motor_measure(motor_measure_t *ptr, uint8_t *data)                                    
{                                                                   
		(ptr)->last_ecd = (ptr)->ecd;                                   
		(ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);            
		(ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);      
		(ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]);  
		(ptr)->temperate = (data)[6];                                   
}

void capacitance_date(super_capacitor_t *ptr, uint8_t *data)                                    
{                                                                   
		(ptr)->chi_voltage = (uint16_t)((data)[0] << 8 | (data)[1]);            
		(ptr)->power = (uint16_t)((data)[2] << 8 | (data)[3]);      
		(ptr)->rong_voltage = (uint16_t)((data)[4] << 8 | (data)[5]);  
		(ptr)->state = (data)[6];                                   
}

super_capacitor_t super_capacitor[1];
motor_measure_t motor_chassis[5];
motor_measure_t motor_gimbal[3];
motor_measure_t motor_shoot[4];

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
	if(hcan->Instance==CAN1)
	{
	
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data);

    switch (rx_header.StdId)
    {
        case CAN_3508_M1_ID:
					get_motor_measure(&motor_chassis[1], rx_data);
					break;

        case CAN_3508_M2_ID:
					get_motor_measure(&motor_chassis[2], rx_data);
					break;

        case CAN_3508_M3_ID:
					get_motor_measure(&motor_chassis[3], rx_data);
					break;

        case CAN_3508_M4_ID:
					get_motor_measure(&motor_chassis[4], rx_data);
					break;
				
				case CAN_YAW_MOTOR_ID:
					get_motor_measure(&motor_gimbal[1], rx_data);
					break;
				
				case 0X666:
					capacitance_date(&super_capacitor[0],rx_data);
					break;
		}
	}
	if(hcan->Instance==CAN2)
	{
	
    HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &rx_header, rx_data);

    switch (rx_header.StdId)
    {
        case CAN_PIT_MOTOR_ID:
					get_motor_measure(&motor_gimbal[2], rx_data);
					break;

        case CAN_SHOOT_3508_ID_1:
					get_motor_measure(&motor_shoot[1], rx_data);
					break;

        case CAN_SHOOT_3508_ID_2:
					get_motor_measure(&motor_shoot[2], rx_data);
					break;

        case CAN_TRIGGER_DRIVER_ID:
					get_motor_measure(&motor_shoot[3], rx_data);
					break;
		}
  }
}



void CAN_cmd_capacitance(int16_t size)
{
	uint32_t send_mail_box;
	capacitance_tx_message.StdId = 0x333;
	capacitance_tx_message.IDE = CAN_ID_STD;
	capacitance_tx_message.RTR = CAN_RTR_DATA;
	capacitance_tx_message.DLC = 0x08;
	
	capacitance_can_send_data[0]=size>>8;
	capacitance_can_send_data[1]=size;
	
	HAL_CAN_AddTxMessage(&hcan1, &capacitance_tx_message, capacitance_can_send_data, &send_mail_box);
}

void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
	uint32_t send_mail_box;
	chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID;
	chassis_tx_message.IDE = CAN_ID_STD;
	chassis_tx_message.RTR = CAN_RTR_DATA;
	chassis_tx_message.DLC = 0x08;
	
	chassis_can_send_data[0] = motor1 >> 8;
	chassis_can_send_data[1] = motor1;
	chassis_can_send_data[2] = motor2 >> 8;
	chassis_can_send_data[3] = motor2;
	chassis_can_send_data[4] = motor3 >> 8;
	chassis_can_send_data[5] = motor3;
	chassis_can_send_data[6] = motor4 >> 8;
	chassis_can_send_data[7] = motor4;

	HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}


void CAN_cmd_gimbal_yaw( int16_t yaw)
{
    uint32_t send_mail_box;
    gimbal_tx_message.StdId = CAN_GIMBAL_ALL_ID;
    gimbal_tx_message.IDE = CAN_ID_STD;
    gimbal_tx_message.RTR = CAN_RTR_DATA;
    gimbal_tx_message.DLC = 0x08;
    
    gimbal_can_send_data[0] = yaw >> 8;
    gimbal_can_send_data[1] = yaw;

    HAL_CAN_AddTxMessage(&hcan1, &gimbal_tx_message, gimbal_can_send_data, &send_mail_box);
}


void CAN_cmd_gimbal_pitch(int16_t pitch,int16_t driver)
{
    uint32_t send_mail_box;
    gimbal_tx_message.StdId = CAN_GIMBAL_ALL_ID;
    gimbal_tx_message.IDE = CAN_ID_STD;
    gimbal_tx_message.RTR = CAN_RTR_DATA;
    gimbal_tx_message.DLC = 0x08;
    
    gimbal_can_send_data[2] = pitch >> 8;
    gimbal_can_send_data[3] = pitch;
		gimbal_can_send_data[4] = driver >> 8;
		gimbal_can_send_data[5] = driver;

    HAL_CAN_AddTxMessage(&hcan2, &gimbal_tx_message, gimbal_can_send_data, &send_mail_box);
}


void CAN_cmd_shoot( int16_t shoot1,int16_t shoot2)
{
    uint32_t send_mail_box;
    shoot_tx_message.StdId = CAN_SHOOT_ALL_ID;
    shoot_tx_message.IDE = CAN_ID_STD;
    shoot_tx_message.RTR = CAN_RTR_DATA;
    shoot_tx_message.DLC = 0x08;
    
   	shoot_can_send_data[0] = shoot1 >> 8;
    shoot_can_send_data[1] = shoot1;
		shoot_can_send_data[2] = shoot2 >> 8;
    shoot_can_send_data[3] = shoot2;

    HAL_CAN_AddTxMessage(&hcan2, &shoot_tx_message, shoot_can_send_data, &send_mail_box);
}




