#include "BlueEye.h"
#include "info.h"
#include "Drv_Uart.h"
u8 DataReceive3;

void BlueEye_GetOneByte(u8 data){
	static u8 openmv_flag=0;//懒得改变量名字了
	switch(openmv_flag){
		case 0:
		{
			if(data==0x67){
				openmv_flag++;
			}
		}
		break;
		case 1:
		{
			if(data==0x94){
				openmv_flag++;
			}
		}
		break;
		case 2:
		{
			DataReceive3=data;
			openmv_flag++;
		}
		break;
		case 3:
		{
			if(data==0xe2){
				User.Flight.key=DataReceive3;
			}
			openmv_flag=0;
		}
		break;
		default:break;
	}
}
u8 Data_sd2[15];
void Openmv_sd(s16 x,s16 y){
	Data_sd2[0]=0x67;
	Data_sd2[1]=0x93;
	static u8 once=1;
	static u16 dly_ms=980;
	static s16 PIC_Location_x;
	static s16 PIC_Location_y;
	static s16 RT_Location_x;
	static s16 RT_Location_y;
	static s16 Fire_Location_x;
	static s16 Fire_Location_y;
	PIC_Location_x=x;
	PIC_Location_y=y;
	dly_ms+=20;
	if(dly_ms==1000){
		RT_Location_x=x;
		RT_Location_y=y;
	}
	if(User.Flight.Send_Fire_Location == 1 && once == 1 ){
		Fire_Location_x=x;
		Fire_Location_y=y;
		once=0;
	}
	s16 temp_y=PIC_Location_y;
	Data_sd2[2]=BYTE0(PIC_Location_x);
	Data_sd2[3]=BYTE1(PIC_Location_x);
	Data_sd2[4]=BYTE0(temp_y);
	Data_sd2[5]=BYTE1(temp_y);
	Data_sd2[6]=BYTE0(RT_Location_x);
	Data_sd2[7]=BYTE1(RT_Location_x);
	temp_y=RT_Location_y;
	Data_sd2[8]=BYTE0(temp_y);
	Data_sd2[9]=BYTE1(temp_y);
	Data_sd2[10]=BYTE0(Fire_Location_x);
	Data_sd2[11]=BYTE1(Fire_Location_x);
	temp_y=Fire_Location_y;
	Data_sd2[12]=BYTE0(temp_y);
	Data_sd2[13]=BYTE1(temp_y);
	Data_sd2[14]=0xe2;
	DrvUart3SendBuf(Data_sd2,15);
}

