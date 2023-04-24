#ifndef VISUAL_RECEIVE_TASK_H
#define VISUAL_RECEIVE_TASK_H
#include "main.h"

#define VISAUAL_DATE_LEN 6



typedef struct 
{
int16_t Pitch_High; 
int16_t Pitch_Low;
int16_t Yaw_High;
int16_t Yaw_Low ;
float Vision_Pitch;
float Vision_Yaw;
}Visual_date;

typedef uint8_t   u8;

typedef union 
{
    float date;
    u8 date_t[4];
	
}visual_send; 

void visual_date_t(uint8_t data);

void visual_date(uint8_t *data);
void visual_send_date(void);

#endif
