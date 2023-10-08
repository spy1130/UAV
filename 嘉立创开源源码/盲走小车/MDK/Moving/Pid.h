#ifndef _PID_H
#define _PID_H

#include "sys.h"
#include "usart.h"

//电机双闭环控制
typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //积分限幅

    float                out_p;  //KP输出
    float                out_i;  //KI输出
    float                out_d;  //KD输出
    float                out;    //pid输出

    float                integrator; //< 积分值
    float                last_error; //< 上次误差
    float                last_derivative;//< 上次误差与上上次误差之差
    uint32_t             last_t;     //< 上次时间
}pid_param_t;


void PidInit(pid_param_t * pid);//pid初始化
float constrain_float(float amt, float low, float high);//限幅
float PidLocCtrl(pid_param_t * pid, float error);//pid位置式控制器输出
float PidIncCtrl(pid_param_t * pid, float error);//pid增量式控制器输出
#endif
