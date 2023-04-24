#include "main.h"
#include "bsp_usart.h"
#include "referee_UI.h"
#include "string.h"
#define PI 3.1415936
#include "math.h"
#include "pid.h"
#include "shoot_task.h"
#include "CAN_receive.h"

extern motor_measure_t motor_shoot[5];
extern int shoot_1;

Graph_Data G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11;
String_Data CH_SHOOT;
String_Data CH_TOP;
char shoot_arr[5]="shoot";
char top_arr[4]="top";
void GUSIUI(void)
{
		memset(&G1,0,sizeof(G1));//中心垂线
		memset(&G2,0,sizeof(G2));//上击打线
		memset(&G3,0,sizeof(G3));//中心水平线
		memset(&G4,0,sizeof(G4));//枪管轴心线
		memset(&G5,0,sizeof(G5));//下击打线
		memset(&G6,0,sizeof(G6));//远距离击打线
		memset(&G7,0,sizeof(G7));//摩擦轮状态
		memset(&CH_SHOOT,0,sizeof(CH_SHOOT));//摩擦轮标识
		memset(&CH_TOP,0,sizeof(CH_TOP));//mode

//		memset(&G8,0,sizeof(G8));//前装甲板状态
//		memset(&G9,0,sizeof(G9));//左装甲板状态
//		memset(&G10,0,sizeof(G10));//右装甲板状态
//		memset(&G11,0,sizeof(G11));//后装甲板状态
//		memset(&CH_FLRB,0,sizeof(CH_FLRB));//装甲板标识

		Line_Draw(&G1,"091",UI_Graph_ADD,9,UI_Color_Purplish_red,1,960,330,960,620);
		Line_Draw(&G2,"092",UI_Graph_ADD,9,UI_Color_Purplish_red,1,880,580,1040,580);
		Line_Draw(&G3,"093",UI_Graph_ADD,9,UI_Color_Purplish_red,1,800,540,1120,540);
		Line_Draw(&G4,"094",UI_Graph_ADD,9,UI_Color_Purplish_red,1,880,500,1040,500);
		Line_Draw(&G5,"095",UI_Graph_ADD,9,UI_Color_Purplish_red,1,900,420,1020,420);
		Line_Draw(&G6,"096",UI_Graph_ADD,9,UI_Color_Purplish_red,1,920,370,1000,370);
		Circle_Draw(&G7,"097",UI_Graph_ADD,9,UI_Color_Black,15,230,770,15);
		Char_Draw(&CH_SHOOT,"087",UI_Graph_ADD,8 ,UI_Color_Yellow,24,5,4,80,780,&shoot_arr[0]);
		Char_Draw(&CH_TOP,"086",UI_Graph_ADD,8 ,UI_Color_Yellow,24,5,4,50 	,780,&top_arr[0]);

		UI_ReFresh(7,G1,G2,G3,G4,G5,G6,G7); 
		Char_ReFresh(CH_SHOOT);
		Char_ReFresh(CH_TOP);

		
		

//  while(1)
//	{
//				//发射模式
//		if(shoot_1==1)
//		Circle_Draw(&G7,"097",UI_Graph_Change,9,UI_Color_Green,15,230,770,15);
//		else Circle_Draw(&G7,"097",UI_Graph_Change,9,UI_Color_Purplish_red,15,230,770,15);
//		UI_ReFresh(1,G7); 
//		HAL_Delay(100);
//	}		
}



