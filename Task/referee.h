#ifndef __REFEREE_H
#define __REFEREE_H
#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>


#define YES true
#define NO  false
#define JUDGE_BUFFER_LEN 128              //缓存区长度

#define JUDGE_FRAME_HEADER 0XA5           //帧头

#define    JUDGE_DATA_ERROR      0
#define    JUDGE_DATA_CORRECT    1     //裁判系统可以不可以用

#define shoot_speed_limit 20;

#define TRUE 1
#define FALSE 0

#define BLUE 0
#define RED 1

//长度根据协议定义,数据段长度为n需要根据帧头第二字节来获取
#define    LEN_HEADER    5        //帧头长
#define    LEN_CMDID     2        //命令码长度
#define    LEN_TAIL      2	      //帧尾CRC16

/* RFID卡类型 */
#define    CARD_ATTACK        ((uint8_t)0x00)
#define    CARD_PROTECT       ((uint8_t)0x01)
#define    CARD_BLOOD_RED     ((uint8_t)0x02)
#define    CARD_BLOOD_BLUE    ((uint8_t)0x03)
#define    CARD_HEAL_RED      ((uint8_t)0x04)
#define    CARD_HEAL_BLUE     ((uint8_t)0x05)
#define    CARD_COLD_RED      ((uint8_t)0x06)
#define    CARD_COLD_BLUE     ((uint8_t)0x07)
#define    CARD_FORT          ((uint8_t)0x08)


#define    LEN_HEADER    5        //帧头长
#define    LEN_CMDID     2        //命令码长度
#define    LEN_TAIL      2	      //帧尾CRC16

/*心跳*/
bool Judge_IF_Refer_Normal(void);
#define     IF_REFER_NORMAL      Judge_IF_Refer_Normal()


//通信协议格式
typedef enum  
{
	FRAME_HEADER         = 0,
	CMD_ID               = 5,
	DATA                 = 7,
	
}JudgeFrameOffset;

// frame_header 格式
typedef enum
{
	SOF          = 0,//起始位
	DATA_LENGTH  = 1,//帧内数据长度,根据这个来获取数据长度
	SEQ          = 3,//包序号
	CRC8         = 4 //CRC8	
}	FrameHeaderOffset;


typedef enum
{
	ID_game_state       = 0x0001,
	ID_game_result      = 0x0002,
	ID_game_robot_survivors       	= 0x0003,//比赛机器人存活数据
	ID_game_missile_state = 0x0004, //飞镖发射状态
	ID_game_buff         =0x0005,//buff
	
	ID_event_data  					= 0x0101,//场地事件数据 
	ID_supply_projectile_action   	= 0x0102,//场地补给站动作标识数据
	ID_supply_warm 	= 0x0104,//裁判系统警告数据
	ID_missile_shoot_time =0x0105  , //飞镖发射口倒计时
	
	ID_game_robot_state    			= 0x0201,//机器人状态数据
	ID_power_heat_data    			= 0x0202,//实时功率热量数据
	ID_game_robot_pos        		= 0x0203,//机器人位置数据
	ID_buff_musk					= 0x0204,//机器人增益数据
	ID_aerial_robot_energy			= 0x0205,//空中机器人能量状态数据
	ID_robot_hurt					= 0x0206,//伤害状态数据
	ID_shoot_data					= 0x0207,//实时射击数据
	ID_bullet_remaining             = 0x0208,//剩余发射数
	ID_rfid_status									= 0x0209,//机器人RFID状态，1Hz
	
	ID_dart_client_directive        = 0x020A,//飞镖机器人客户端指令书, 10Hz
  
	ID_robot_interactive_header_data			= 0x0301,//机器人交互数据，——发送方触发——发送 10Hz
	ID_controller_interactive_header_data = 0x0302,//自定义控制器交互数据接口，通过——客户端触发——发送 30Hz
	ID_map_interactive_header_data        = 0x0303,//客户端小地图交互数据，——触发发送——
	ID_keyboard_information               = 0x0304//键盘、鼠标信息，通过——图传串口——发送

}CmdID;

typedef enum
{
	/* Std */
	LEN_FRAME_HEAD 	                 = 5,	// 帧头长度
	LEN_CMD_ID 		                 = 2,	// 命令码长度
	LEN_FRAME_TAIL 	                 = 2,	// 帧尾CRC16
	/* Ext */  

	LEN_game_state       				= 11,	//0x0001
	LEN_game_result       				= 1,	//0x0002
	LEN_game_robot_survivors       		= 32,	//0x0003  比赛机器人血量数据
	LED_game_missile_state              = 3  , //0X0004飞镖发射状态
	LED_game_buff                       = 11 , //0X0005
	
	LEN_event_data  					= 4,	//0x0101  场地事件数据 
	LEN_supply_projectile_action        = 4,	//0x0102场地补给站动作标识数据
	LEN_supply_warm                     = 2, //裁判系统警告 0x0104
	LEN_missile_shoot_time              = 1  , //飞镖发射口倒计时
	
	LEN_game_robot_state    			= 27,	//0x0201机器人状态数据
	LEN_power_heat_data   				= 16,	//0x0202实时功率热量数据
	LEN_game_robot_pos        			= 16,	//0x0203机器人位置数据
	LEN_buff_musk        				=  1,	//0x0204机器人增益数据
	LEN_aerial_robot_energy        		=  1,	//0x0205空中机器人能量状态数据
	LEN_robot_hurt        				=  1,	//0x0206伤害状态数据
	LEN_shoot_data       				=  7,	//0x0207	实时射击数据
	LEN_bullet_remaining                = 6,//剩余发射数
  
	LEN_rfid_status					         = 4,
	LEN_dart_client_directive        = 12,//0x020A
	// 0x030x
	//LEN_robot_interactive_header_data      = n,
	//LEN_controller_interactive_header_data = n,
	LEN_map_interactive_headerdata           = 15,
	LEN_keyboard_information                 = 12,//0x0304

}JudgeDataLength;

/* 自定义帧头 */
typedef __packed struct
{
	uint8_t  SOF;
	uint16_t DataLength;
	uint8_t  Seq;
	uint8_t  CRC8;
	
} xFrameHeader;

/* ID: 0x0001  Byte:  11    比赛状态数据 */
typedef __packed struct 
{ 
	uint8_t game_type : 4;
	uint8_t game_progress : 4;
	uint16_t stage_remain_time;
  uint64_t SyncTimeStamp;
} ext_game_state_t; 

/* ID: 0x0002  Byte:  1    比赛结果数据 */
typedef __packed struct 
{ 
	uint8_t winner;
} ext_game_result_t; 

/* ID: 0x0003  Byte:  32    比赛机器人血量数据 */
typedef __packed struct 
{ 
	uint16_t red_1_robot_HP;   
	uint16_t red_2_robot_HP;  
	uint16_t red_3_robot_HP;  
	uint16_t red_4_robot_HP;  
	uint16_t red_5_robot_HP;  
	uint16_t red_6_robot_HP;  
	uint16_t red_7_robot_HP;  
	uint16_t red_outpost_HP; 
  uint16_t red_base_HP; 
	
	uint16_t blue_1_robot_HP;   
	uint16_t blue_2_robot_HP;   
	uint16_t blue_3_robot_HP;   
	uint16_t blue_4_robot_HP;   
	uint16_t blue_5_robot_HP;   
	uint16_t blue_6_robot_HP;   
	uint16_t blue_7_robot_HP; 

	uint16_t blue_outpost_HP; 
  uint16_t blue_base_HP;   
}  ext_game_robot_HP_t; 

/* ID: 0x0004  Byte:  3    飞镖发射状态 */
typedef __packed struct 
{  
	uint8_t dart_belong; 
	uint16_t stage_remaining_time; 
} ext_dart_status_t;

/* ID: 0x0005  Byte:  11    buff */
typedef __packed struct
{ 
	uint8_t F1_zone_status:1;  
	uint8_t F1_zone_buff_debuff_status:3;   
	
	uint8_t F2_zone_status:1;  
	uint8_t F2_zone_buff_debuff_status:3;   
	
	uint8_t F3_zone_status:1;  
	uint8_t F3_zone_buff_debuff_status:3;  
	
	uint8_t F4_zone_status:1;  
	uint8_t F4_zone_buff_debuff_status:3;  
	
	uint8_t F5_zone_status:1;  
	uint8_t F5_zone_buff_debuff_status:3;  
	
	uint8_t F6_zone_status:1;  
	uint8_t F6_zone_buff_debuff_status:3;  
  
  uint16_t red1_bullet_left;
  
  uint16_t red2_bullet_left;
  
  uint16_t blue1_bullet_left;
  
  uint16_t blue2_bullet_left;
  
} ext_ICRA_buff_debuff_zone_status_t; 

/* ID: 0x0101  Byte:  4    场地事件数据 */
typedef __packed struct 
{ 
	uint32_t event_type;
} ext_event_data_t; 


/* ID: 0x0102  Byte:  4    场地补给站动作标识数据 */
typedef __packed struct 
{ 
	uint8_t supply_projectile_id;
	uint8_t supply_robot_id;
	uint8_t supply_projectile_step;
  uint8_t supply_projectile_num;
} ext_supply_projectile_action_t; 

/* ID: 0x0104  Byte: 2   裁判系统警告信息 */
typedef __packed struct 
{ 
  uint8_t level; 
	uint8_t foul_robot_id;
}  ext_referee_warning_t;  

/* ID: 0x0105  Byte:1  飞镖发射口倒计时 */
typedef __packed struct 
{ 
	uint8_t dart_remaining_time; 
}  ext_dart_remaining_time_t; 

/* ID: 0X0201  Byte: 27    机器人状态数据 */
typedef __packed struct 
{ 
	uint8_t robot_id;   //机器人ID，可用来校验发送
	uint8_t robot_level;  //1一级，2二级，3三级
	uint16_t remain_HP;  //机器人剩余血量
	uint16_t max_HP; //机器人满血量

  uint16_t shooter1_17mm_cooling_rate;  //机器人 17mm 子弹热量冷却速度 单位 /s
  uint16_t shooter1_17mm_cooling_limit;   // 机器人 17mm 子弹热量上限  
  uint16_t shooter1_17mm_speed_limit;

  
  uint16_t shooter2_17mm_cooling_rate;
  uint16_t shooter2_17mm_cooling_limit;  
  uint16_t shooter2_17mm_speed_limit;

  
  uint16_t shooter_42mm_cooling_rate;
  uint16_t shooter_42mm_cooling_limit;
  uint16_t shooter_42mm_speed_limit;

  
	uint16_t max_chassis_power; 
	uint8_t mains_power_gimbal_output : 1;  
	uint8_t mains_power_chassis_output : 1;  
	uint8_t mains_power_shooter_output : 1; 
} ext_game_robot_state_t;   

/* ID: 0X0202  Byte: 16    实时功率热量数据 */
typedef __packed struct 
{ 
	uint16_t chassis_volt;   
	uint16_t chassis_current;    
	float chassis_power;   //瞬时功率 
	uint16_t chassis_power_buffer;//60焦耳缓冲能量
	uint16_t shooter_heat0;//17mm
	uint16_t shooter_heat1;  
	uint16_t mobile_shooter_heat2; 
} ext_power_heat_data_t; 

/* ID: 0x0203  Byte: 16    机器人位置数据 */
typedef __packed struct 
{   
	float x;   
	float y;   
	float z;   
	float yaw; 
} ext_game_robot_pos_t; 

/* ID: 0x0204  Byte:  1    机器人增益数据 */
typedef __packed struct 
{ 
	uint8_t power_rune_buff; 
} ext_buff_musk_t; 

/* ID: 0x0205  Byte:  1    空中机器人能量状态数据 */
typedef __packed struct 
{ 
  uint8_t attack_time;
} aerial_robot_energy_t; 

/* ID: 0x0206  Byte:  1    伤害状态数据 */
typedef __packed struct 
{ 
	uint8_t armor_id : 4; 
	uint8_t hurt_type : 4; 
} ext_robot_hurt_t; 

/* ID: 0x0207  Byte:  7    实时射击数据 */
typedef __packed struct 
{ 
	uint8_t bullet_type; 
  uint8_t shooter_id;  //发射机构是17还是42
	uint8_t bullet_freq;   
	float bullet_speed;  
} ext_shoot_data_t; 


/* ID: 0x0208  Byte:  6    子弹剩余数量 */
typedef __packed struct 
{ 
  uint16_t bullet_remaining_num_17mm;
  uint16_t bullet_remaining_num_42mm;
  uint16_t coin_remaining_num;//金币剩余
}  ext_bullet_remaining_t; 

/* ID: 0x0209  Byte:  4 	机器人RFID状态 */
typedef __packed struct
{
	uint32_t rfid_status;
} ext_rfid_status_t;

typedef __packed struct{
	uint8_t dart_launch_opening_status;//当前飞镖发射口的状态
	uint8_t dart_attack_target;        //飞镖的打击目标，默认为前哨站（1：前哨站，2：基地）
	uint16_t target_change_time;       //切换打击目标时的比赛剩余时间
	uint8_t first_dart_speed;          //检测到的第一枚飞镖速度，单位 0.1m/s/LSB
	uint8_t second_dart_speed;         //检测到的第二枚飞镖速度，单位 0.1m/s/LSB
	uint8_t third_dart_speed;          //检测到的第三枚飞镖速度，单位 0.1m/s/LSB
	uint8_t fourth_dart_speed;         //检测到的第四枚飞镖速度，单位 0.1m/s/LSB
	uint16_t last_dart_launch_time;    //最近一次的发射飞镖的比赛剩余时间，单位秒
	uint16_t operate_launch_cmd_time;  //最近一次操作手确定发射指令时的比赛剩余时间，单位秒
} ext_dart_client_cmd_t; //LEN_DART_CLIENT_DIRECTIVE  表3-19

/* 
	
	交互数据，包括一个统一的数据段头结构，
	包含了内容 ID，发送者以及接受者的 ID 和内容数据段，
	整个交互数据的包总共长最大为 128 个字节，
	减去 frame_header,cmd_id,frame_tail 以及数据段头结构的 6 个字节，
	故而发送的内容数据段最大为 113。
	整个交互数据 0x0301 的包上行频率为 10Hz。

	机器人 ID：
	1，英雄(红)；
	2，工程(红)；
	3/4/5，步兵(红)；
	6，空中(红)；
	7，哨兵(红)；
	11，英雄(蓝)；
	12，工程(蓝)；
	13/14/15，步兵(蓝)；
	16，空中(蓝)；
	17，哨兵(蓝)。 
	客户端 ID： 
	0x0101 为英雄操作手客户端( 红) ；
	0x0102 ，工程操作手客户端 ((红 )；
	0x0103/0x0104/0x0105，步兵操作手客户端(红)；
	0x0106，空中操作手客户端((红)； 
	0x0111，英雄操作手客户端(蓝)；
	0x0112，工程操作手客户端(蓝)；
	0x0113/0x0114/0x0115，操作手客户端步兵(蓝)；
	0x0116，空中操作手客户端(蓝)。 
*/

/* 交互数据接收信息：0x0301  */
typedef __packed struct 
{ 
	uint16_t data_cmd_id;    
	uint16_t send_ID;    
	uint16_t receiver_ID; 
} ext_student_interactive_header_data_t; 

enum judge_robot_ID{
	hero_red       = 1,
	engineer_red   = 2,
	infantry3_red  = 3,
	infantry4_red  = 4,
	infantry5_red  = 5,
	plane_red      = 6,
	
	hero_blue      = 101,
	engineer_blue  = 102,
	infantry3_blue = 103,
	infantry4_blue = 104,
	infantry5_blue = 105,
	plane_blue     = 106,
};
typedef struct{
	uint16_t teammate_hero;
	uint16_t teammate_engineer;
	uint16_t teammate_infantry3;
	uint16_t teammate_infantry4;
	uint16_t teammate_infantry5;
	uint16_t teammate_plane;
	uint16_t teammate_sentry;
	
	uint16_t client_hero;
	uint16_t client_engineer;
	uint16_t client_infantry3;
	uint16_t client_infantry4;
	uint16_t client_infantry5;
	uint16_t client_plane;
} ext_interact_id_t;



/* 
	学生机器人间通信 cmd_id 0x0301，内容 ID:0x0200~0x02FF
	交互数据 机器人间通信：0x0301。
	发送频率：上限 10Hz  

	字节偏移量 	大小 	说明 			备注 
	0 			2 		数据的内容 ID 	0x0200~0x02FF 
										可以在以上 ID 段选取，具体 ID 含义由参赛队自定义 
	
	2 			2 		发送者的 ID 	需要校验发送者的 ID 正确性， 
	
	4 			2 		接收者的 ID 	需要校验接收者的 ID 正确性，
										例如不能发送到敌对机器人的ID 
	
	6 			n 		数据段 			n 需要小于 113 

*/
typedef __packed struct 
{ 
	uint8_t data[113]; //数据段,n需要小于113
} robot_interactive_data_t;




/**
  * @brief  读取裁判数据,loop中循环调用此函数来读取数据
  * @param  缓存数据
  * @retval 是否对正误判断做处理
  * @attention  在此判断帧头和CRC校验,无误再写入数据
  */


typedef struct judge_info_struct {
	xFrameHeader							FrameHeader;				// 帧头信息
	
	ext_game_state_t 							GameState;				// 0x0001           比赛状态数据
	ext_game_result_t 							GameResult;				// 0x0002         比赛结果数据
	ext_game_robot_HP_t 						GameRobotHP;			// 0x0003         机器人血量数据
	ext_dart_status_t								GameRobotmissile;				// 0x0004         飞镖发射状态
	ext_ICRA_buff_debuff_zone_status_t	Game_ICRA_buff;      //                人工智能挑战赛加成与惩罚区状态
	
	ext_event_data_t								EventData;					// 0x0101         场地事件数据
	ext_supply_projectile_action_t	SupplyProjectileAction;		// 0x0102 补给站动作标识
	ext_referee_warning_t						RefereeWarning;		// 0x0104         裁判警告信息
	ext_dart_remaining_time_t				dart_remaining_time;// 0x0105         飞镖发射口倒计时
	
	ext_game_robot_state_t					GameRobotStat;	// 0x0201         比赛机器人状态
	ext_power_heat_data_t						PowerHeatData;		// 0x0202         实时功率热量数据
	ext_game_robot_pos_t						GameRobotPos;			// 0x0203         机器人位置
	ext_buff_musk_t											Buff;								// 0x0204     机器人增益
	aerial_robot_energy_t				AerialRobotEnergy;// 0x0205             空中机器人能量状态
	ext_robot_hurt_t								RobotHurt;					// 0x0206         伤害状态
	ext_shoot_data_t								ShootData;					// 0x0207         实时射击信息(射频  射速  子弹信息)
	ext_bullet_remaining_t					bullet_remaining;		// 0x0208	        子弹剩余发射数
	ext_rfid_status_t								rfid_status;				// 0x0209	        RFID信息
	ext_dart_client_cmd_t           dart_client;        // 0x020A         飞镖客户端
	
	ext_interact_id_t								ids;								//与本机交互的机器人id
	uint16_t                        self_client;        //本机客户端
	bool	 		IF_REF_ONL;

} Referee_info_t;



bool Judege_read_data(uint8_t *ReadFromUsart );







void GUSIUI(void);

#endif  
