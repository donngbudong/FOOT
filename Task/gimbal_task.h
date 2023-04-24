#ifndef GIMBAL_TASK_H
#define GIMBAL_TASK_H


void gimbal_pid_init(void);
void pitch_limit(float *a, float imu_MAX,float imu_MIX);
float yaw_limit(float *a);
void gimbal_rc_dbus(void);
void gimbal_rc_pc(void);
void yaw_pitch_gimbal(void);
void gimbal_ctrl(void);
void gimbal_pid(void);

#endif

