#ifndef __pid_H
#define __pid_H

float PID_x(float target_value_x, float temp_val_x, float kp_x, float ki_x, float kd_x);
float PID_y(float target_value_y, float temp_val_y, float kp_y, float ki_y, float kd_y);

#endif
