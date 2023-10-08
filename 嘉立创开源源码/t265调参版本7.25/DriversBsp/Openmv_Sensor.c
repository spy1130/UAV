#include "Openmv_Sensor.h"
#include "info.h"
#include "Drv_Uart.h"
u8 DataReceive3[10];

void Openmv_GetOneByte(u8 data){
	static u8 openmv_flag=0;
	static u8 openmv_data_length=0;
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
			DataReceive3[openmv_data_length++]=data;
			if(openmv_data_length==1){
				openmv_flag++;
			}
		}
		break;
		case 3:
		{
			if(data==0xe2){
				User.Flight.openmv_flag=DataReceive3[0];
			}
			openmv_flag=0;
		}
		break;
		default:break;
	}
}
u8 Data_sd2[4];
void Openmv_sd(u8 data){
	Data_sd2[0]=0x67;
	Data_sd2[1]=0x93;
	Data_sd2[2]=data;
	Data_sd2[3]=0xe2;
	DrvUart3SendBuf(Data_sd2,4);
}

