#include "T265_Sensor.h"
#include "Info.h"
#include "Ano_Math.h"
#include "LX_FC_EXT_Sensor.h"
#include "ANO_DT_LX.h"
#include "Drv_Uart.h"
/*******************************************************
	函数名：T265_GetOneByte
	输  入:
	输  出:
	功能说明：T265信息接收解包

********************************************************/
extern _fc_ext_sensor_st ext_sens;
T265_info T265;
float_u8 float_get;
float2_u8 float2_get;
s16_u8 s16_get;
u8 DataSend[100];
u8 DataReceive[60];
static float T265_data_old[6];
#define T265_Dis 20.0f;
void T265_GetOneByte(u8 data)
{
	static u8 camera_ok=0;
	static u8 my_flag = 0;
	static u8 _datalen = 0;		//数据长度


	//	格式: 帧头 0xAA 0xFF 
//		    pose_x_cm
//				pose_y_cm
//				pose_z_cm
//				speed_x_cms
//				speed_y_cms
//				speed_z_cms
//				帧尾 0xEA
	switch (my_flag)
	{
		case 0:
		{
			_datalen = 0;
			if(data == 0xAA){
				my_flag++;
			}
			else if(data == 0xAB){
				my_flag=20;
			}
		}
		break;
		case 1:
		{
			if(data == 0xFF){
				my_flag++;
			}
		}
		break;
		case 2:
		{	
			DataReceive[_datalen++] = data;
			if(_datalen == 24){
				my_flag++;
			}
		}
		break;
		case 3:
		{
			if(data == 0xEA )
			{
				for(u8 i = 0;i < 24;i++)
					float_get.byet[i] = DataReceive[i];
				
				for(u8 i = 0;i < 6;i++)
					if(ABS(float_get.Data[i] - T265_data_old[i]) > 0.2f)
						float_get.Data[i] = T265_data_old[i];
					/*
					T265.pose_x_cm=float_get.Data[0]*100;
					T265.pose_y_cm=float_get.Data[1]*100;
					T265.pose_z_cm=float_get.Data[2]*100;
					T265.speed_x_cms=-float_get.Data[3]*100;
					T265.speed_y_cms=float_get.Data[4]*100;
					T265.speed_z_cms=float_get.Data[5]*100;
					*/
				S_LPF_1(0.5f,-float_get.Data[1] * 100,T265.pose_x_cm); //x,y取反
				S_LPF_1(0.5f,float_get.Data[0] * 100,T265.pose_y_cm); //加入滤波
				S_LPF_1(0.5f,float_get.Data[2] * 100,T265.pose_z_cm);
				S_LPF_1(0.5f,float_get.Data[4] * 100,T265.speed_x_cms);
				S_LPF_1(0.5f,-float_get.Data[3] * 100,T265.speed_y_cms);
				S_LPF_1(0.5f,float_get.Data[5] * 100,T265.speed_z_cms);
				
//		x正为-y，y变成-x
//				ext_sens.gen_pos.st_data.ulhca_pos_cm[0]=(s32)T265.pose_x_cm;
//		  	ext_sens.gen_pos.st_data.ulhca_pos_cm[1]=(s32)T265.pose_y_cm;
//				ext_sens.gen_pos.st_data.ulhca_pos_cm[2]=(s32)T265.pose_z_cm;
//				dt.fun[0x32].WTS = 1;
			for(u8 i = 0;i < 6;i++){
				T265_data_old[i] = float_get.Data[i];
			}
					
				
//				T265.t265_work_sta = 1;
					
				User.Flight.T265_Flag=1;
			
			}
			my_flag = 0;
		}
		break;
		case 20:
			{
			if(data == 0xFB)
				my_flag++;
			}
		break;
		case 21:
			{	
				DataReceive[_datalen++] = data;
				if(_datalen == 4)
					my_flag++;
			}
		break;
			case 22:
		{
			if(data == 0xEB )
			{
		//		for(u8 i = 0;i < 6;i++){
		//			if(i<=4){
		//				float2_get.byet[i] = DataReceive[i];//-------------------------------需要根据具体数据再修改一下，int？
		//			}
		//			else{
				
				s16_get.byet[0]	=	DataReceive[0];
				s16_get.byet[1]	=	DataReceive[1];		//先x再y
				s16_get.byet[2]	=	DataReceive[2];
				s16_get.byet[3]	=	DataReceive[3];
				if(s16_get.Data[0]==6000 ){
					User.Flight.Camera_error++;
					if(User.Flight.Camera_error>5){
					User.Flight.Success_Find=0;
					}
		
				}
				else{
					camera_ok++;
					if(camera_ok>5){
						camera_ok=6;
					}
			
					User.Flight.Success_Find=1;
	//				}
		//		}
				/*
				for(u8 i = 0;i < 2;i++)
					if(ABS(float_get.Data[i] - T265_data_old[i]) > 0.2f)
						float_get.Data[i] = T265_data_old[i];
				*/
			//	User.Flight.Pole_Dis=float2_get.Data[0];
				
				if((ABS(s16_get.Data[1] - User.Flight.FireCenter[1]) > 140 && User.Flight.Camera_Flag == 1) ||(ABS(s16_get.Data[0] - User.Flight.FireCenter[0]) > 140 && User.Flight.Camera_Flag == 1)){
					User.Flight.FireCenter[0]=User.Flight.Last_FireCenter[0];
					User.Flight.FireCenter[1]=User.Flight.Last_FireCenter[1];
				}
				else{
					User.Flight.Last_FireCenter[0] = User.Flight.FireCenter[0];
					User.Flight.Last_FireCenter[1] = User.Flight.FireCenter[1];
					User.Flight.FireCenter[0] = s16_get.Data[0];
					User.Flight.FireCenter[1] = s16_get.Data[1];
				}
				
			}
				
			
				
				User.Flight.Camera_Flag=1;
			}
			my_flag = 0;
		}
		break;
		default:break;
	}
}

void T265_Restart(u8 data){
	u8 Data_sd5[4];
	Data_sd5[0]=0xBB;
	Data_sd5[1]=0xFF;
	Data_sd5[2]=data;
	Data_sd5[3]=0xEB;
	DrvUart2SendBuf(Data_sd5,4);
}


void T265_text(s16 x,s16 y){
	u8 Data_sd5[7];
	
	Data_sd5[0]=0xCC;
	Data_sd5[1]=0xFF;
	Data_sd5[2]=BYTE0(x);
	Data_sd5[3]=BYTE1(x);
	Data_sd5[4]=BYTE0(y);
	Data_sd5[5]=BYTE1(y);
	Data_sd5[6]=0xEC;
	DrvUart2SendBuf(Data_sd5,7);
}

