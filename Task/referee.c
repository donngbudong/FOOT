#include "referee.h"
#include "crc.h"
#include "stdio.h"
#include <string.h>

uint8_t  Judge_Buffer[ JUDGE_BUFFER_LEN ];

Referee_info_t 	REF = {
 	.IF_REF_ONL = NO,
};

bool Judge_Data_TF = FALSE;

bool Judege_read_data(uint8_t *ReadFromUsart )
{
	bool retval_tf = FALSE;//数据正确与否标志,每次调用读取裁判系统数据函数都先默认为错误
	
	uint16_t judge_length;//统计一帧数据长度 
	
	int CmdID = 0;//数据命令码解析	
//	
//	if(ReadFromUsart == NULL)
//	{
//		return -1;
//	}
	
	memcpy(&REF.FrameHeader,ReadFromUsart,LEN_HEADER);   //储存帧头数据
	
	if(ReadFromUsart[SOF] == JUDGE_FRAME_HEADER)                   //判断帧头是否为0xa5
	{
		if(Verify_CRC8_Check_Sum( ReadFromUsart, LEN_HEADER ) == TRUE)  //帧头CRC校验
		{
			judge_length = ReadFromUsart[DATA_LENGTH] + LEN_HEADER + LEN_CMDID + LEN_TAIL;	//统计一帧数据长度,用于CR16校验
			
			if(Verify_CRC16_Check_Sum(ReadFromUsart,judge_length) == TRUE)//帧尾CRC16校验
			{
//				retval_tf = TRUE;//数据可用
				
				CmdID = (ReadFromUsart[6] << 8 | ReadFromUsart[5]);//解析数据命令码,将数据拷贝到相应结构体中(注意拷贝数据的长度)
				
				switch(CmdID)
				{
					case ID_game_state:     //0x0001
							 memcpy(&REF.GameState, (ReadFromUsart + DATA), LEN_game_state);
							 break;
					
					case ID_game_result:    //0x0002
							 memcpy(&REF.GameResult, (ReadFromUsart + DATA), LEN_game_result);
							 break;
					
					case ID_game_robot_survivors:    //0x0003
							 memcpy(&REF.GameRobotHP, (ReadFromUsart + DATA), LEN_game_robot_survivors);
							 break;
					
					case ID_game_missile_state:    //0x0004
							 memcpy(&REF.GameRobotmissile, (ReadFromUsart + DATA), LED_game_missile_state);
							 break;
					
					case ID_game_buff:    //0x0005
							 memcpy(&REF.Game_ICRA_buff, (ReadFromUsart + DATA), LED_game_buff);
							 break;
					
					case ID_event_data:    //0x0101
							 memcpy(&REF.EventData, (ReadFromUsart + DATA), LEN_event_data);
							 break;
					
					case ID_supply_projectile_action:    //0x0102
							 memcpy(&REF.SupplyProjectileAction, (ReadFromUsart + DATA), LEN_supply_projectile_action);
							 break;
					
					case ID_supply_warm:    //0x0104
							 memcpy(&REF.RefereeWarning, (ReadFromUsart + DATA), LEN_supply_warm);
							 break;
					
					case ID_missile_shoot_time:    //0x0105
							 memcpy(&REF.dart_remaining_time, (ReadFromUsart + DATA), LEN_missile_shoot_time);
							 break;
					
					case ID_game_robot_state:    //0x0201
//               Determine_ID();
///*1*/          Referee_Update(GameRobotStat_ID);
							 memcpy(&REF.GameRobotStat, (ReadFromUsart + DATA), LEN_game_robot_state);
							 break;
				
					case ID_power_heat_data:    //0x0202
///*2*/          Referee_Update(PowerHeatData_ID);
							 memcpy(&REF.PowerHeatData, (ReadFromUsart + DATA), LEN_power_heat_data);
							 break;
					
					case ID_game_robot_pos:    //0x0203
							 memcpy(&REF.GameRobotPos, (ReadFromUsart + DATA), LEN_game_robot_pos);
							 break;
					
					case ID_buff_musk:    //0x0204
							 memcpy(&REF.Buff, (ReadFromUsart + DATA), LEN_buff_musk);
							 break;
					
					case ID_aerial_robot_energy:    //0x0205
							 memcpy(&REF.AerialRobotEnergy, (ReadFromUsart + DATA), LEN_aerial_robot_energy);
							 break;
					
					case ID_robot_hurt:      			//0x0206
							memcpy(&REF.RobotHurt, (ReadFromUsart + DATA), LEN_robot_hurt);
//							if(REF.RobotHurt.hurt_type == 0)//非装甲板离线造成伤害
//							{	
//								Hurt_Data_Update = TRUE;
//							}//装甲数据每更新一次则判定为受到一次伤害
							break;
					case ID_shoot_data:      			//0x0207
///*3*/          Referee_Update(ShootSpeed_ID);
							 memcpy(&REF.ShootData, (ReadFromUsart + DATA), LEN_shoot_data);
					     break;	
					
					case ID_bullet_remaining:    //0x0208
							 memcpy(&REF.bullet_remaining, (ReadFromUsart + DATA), LEN_bullet_remaining);
							 break;
          
					case ID_rfid_status: 
               memcpy(&REF.rfid_status, (ReadFromUsart+DATA), LEN_rfid_status);
               break;
              
					case ID_dart_client_directive:
               memcpy(&REF.dart_client,(ReadFromUsart+DATA),LEN_dart_client_directive);
               break;
					
				}
					
			}
		}
		//首地址加帧长度,指向CRC16下一字节,用来判断是否为0xA5,用来判断一个数据包是否有多帧数据
		if(*(ReadFromUsart + sizeof(xFrameHeader) + LEN_CMDID + REF.FrameHeader.DataLength + LEN_TAIL) == 0xA5)
		{
			//如果一个数据包出现了多帧数据,则再次读取
			Judege_read_data(ReadFromUsart + sizeof(xFrameHeader) + LEN_CMDID + REF.FrameHeader.DataLength + LEN_TAIL);
		}
	}
	if (retval_tf == TRUE)
	{
		Judge_Data_TF = TRUE;//辅助函数用
	}
	else		//只要CRC16校验不通过就为FALSE
	{
		Judge_Data_TF = FALSE;//辅助函数用
	}	
	return retval_tf;
	
}









