//T265ͷ�ļ���
#include "SysConfig.h"
typedef struct
{
	//
	u8 of_t265_update_cnt;  //T265�ٶȵ����ݸ��¼�����
	u8 alt_t265_update_cnt; //�߶����ݸ��¼�����
	u8 pos_t265_update_cnt;
	//
	u8 t265_link_sta; //����״̬��0��δ���ӡ�1�������ӡ�
	u8 t265_work_sta; //����״̬��0���쳣��1������
	//
	u8 t265_of_quality;
	//t65���ٶ���Ϣ����λcm
	s16 speed_x_cms;
	s16 speed_y_cms;
	s16 speed_z_cms;
	
	/*
	s16 of2_dx_fix;
	s16 of2_dy_fix;
	s16 intergral_x;
	s16 intergral_y;
	*/
	//�߶���Ϣ����λcm��������ʱע�⴦��
	//��̼���Ϣ
	s16 pose_x_cm;
	s16 pose_y_cm;
	s16 pose_z_cm;
	
	//
	float quaternion[4];
	//
	s16 t265_acc_data_x;
	s16 t265_acc_data_y;
	s16 t265_acc_data_z;
	s16 t265_gyr_data_x;
	s16 t265_gyr_data_y;
	s16 t265_gyr_data_z;

}T265_info;

typedef union
{
	float Data[6];
	u8 byet[24];
}float_u8;

typedef union
{
	float Data[1];
	u8 byet[4];
}float2_u8;


typedef union
{
	s16 Data[2];
	u8 byet[4];
}s16_u8;

extern T265_info T265;
void T265_GetOneByte(uint8_t data);
void T265_Restart(u8 data);
void T265_text(s16 x,s16 y);
