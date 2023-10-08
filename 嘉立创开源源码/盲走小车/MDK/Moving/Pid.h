#ifndef _PID_H
#define _PID_H

#include "sys.h"
#include "usart.h"

//���˫�ջ�����
typedef struct
{
    float                kp;         //P
    float                ki;         //I
    float                kd;         //D
    float                imax;       //�����޷�

    float                out_p;  //KP���
    float                out_i;  //KI���
    float                out_d;  //KD���
    float                out;    //pid���

    float                integrator; //< ����ֵ
    float                last_error; //< �ϴ����
    float                last_derivative;//< �ϴ���������ϴ����֮��
    uint32_t             last_t;     //< �ϴ�ʱ��
}pid_param_t;


void PidInit(pid_param_t * pid);//pid��ʼ��
float constrain_float(float amt, float low, float high);//�޷�
float PidLocCtrl(pid_param_t * pid, float error);//pidλ��ʽ���������
float PidIncCtrl(pid_param_t * pid, float error);//pid����ʽ���������
#endif
