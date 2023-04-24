#ifndef _VOFA_TASK_H
#define _VOFA_TASK_H
#include "main.h"

typedef uint8_t  u8;

typedef union 
{
    float c;
		float d;
    u8 b[4];
	
}vofa_date; 

void vofa_send(void);

#endif

