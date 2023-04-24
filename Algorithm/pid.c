#include "pid.h"
#include "main.h"


#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

pid_type_def pid_chassis[8];
pid_type_def pid_gimbal[5];		
pid_type_def pid_shoot[8];
		
		
void PID_init(pid_type_def *pid,float KP,float KI,float KD, int max_out, int max_iout)
{

//    pid->mode = mode;
    pid->Kp = KP;
    pid->Ki = KI;
    pid->Kd = KD;
    pid->max_out = max_out;
    pid->max_iout = max_iout;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;
}


float PID_calc(pid_type_def *pid, float ref, float set)
{
//    if (pid == NULL)
//    {
//        return 0.0f;
//    }

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->set = set;
    pid->fdb = ref;
    pid->error[0] = set - ref;
//    if (pid->mode == PID_POSITION)
//    {
        pid->Pout = pid->Kp * pid->error[0];
        pid->Iout += pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        LimitMax(pid->Iout, pid->max_iout);
        pid->out = pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
//    }
//    else if (pid->mode == PID_DELTA)
//    {
//        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
//        pid->Iout = pid->Ki * pid->error[0];
//        pid->Dbuf[2] = pid->Dbuf[1];
//        pid->Dbuf[1] = pid->Dbuf[0];
//        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
//        pid->Dout = pid->Kd * pid->Dbuf[0];
//        pid->out += pid->Pout + pid->Iout + pid->Dout;
//        LimitMax(pid->out, pid->max_out);
//    }
    return pid->out;
}

