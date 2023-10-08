#include "Expansion_board_RXSD.h"
#include "info.h"
#include "Drv_Uart.h"

u8 DataReceive2[10];
void Expansion_board_RX(u8 data){
	static u8 rx_flag=0;
	static u8 data_length=0;
	switch(rx_flag){
		case 0:
		{
			data_length=0;
			if(data==0x66){
				rx_flag++;
			}
		
		}
		break;
		case 1:
		{
			if(data==0x98){
				rx_flag++;
			}
			else if(data==0x01){
				
			rx_flag=6;
			}
		}
		break;
		case 2:
		{
			DataReceive2[data_length++]=data;
			if(data_length==1){
				rx_flag++;
			}
		}
		break;
		case 3:
		{
			if(data==0xEE){
				if(DataReceive2[0] == 0x01){
					User.Flight.Page_OK_Flag=1;
				}
			}
			rx_flag=0;	
		}
		break;
		case 6:
		{
			DataReceive2[data_length++]=data;
			if(data_length==1){
				rx_flag++;
			}
		}
		break;
		case 7:
		{
			if(data==0xee){
				User.Flight.key=DataReceive2[0];
			}
			rx_flag=0;
		}
		break;
		default:break;
	}
}

static u8 Data_sd[15];
void Expansion_board_Laser(u8 data){
	Data_sd[0]=0x66;
	Data_sd[1]=0x01;
	Data_sd[2]=data;
	Data_sd[3]=0xee;
	DrvUart1SendBuf(Data_sd,4);
}
void Expansion_board_Page(u8 data){
	Data_sd[0]=0x66;
	Data_sd[1]=0x02;
	Data_sd[2]=data;
	Data_sd[3]=0xee;
	DrvUart1SendBuf(Data_sd,4);
}

void Expansion_board_Location(s16 x,s16 y){
	s16 temp=x;
	s16 temp2=y;
	Data_sd[0]=0x66;
	Data_sd[1]=0x03;
	Data_sd[2]=BYTE0(temp);
	Data_sd[3]=BYTE1(temp);
	Data_sd[4]=BYTE0(temp2);
	Data_sd[5]=BYTE1(temp2);
	Data_sd[6]=0xee;
	DrvUart1SendBuf(Data_sd,7);
}

void Expansion_board_LED(u8 data,u8 data2){
	Data_sd[0]=0x66;
	Data_sd[1]=0x01;
	Data_sd[2]=data;
	Data_sd[3]=data2;
	Data_sd[4]=0xee;
	DrvUart1SendBuf(Data_sd,5);
}

void Expansion_board_RT_Location(s16 x,s16 y){
	s16 temp=x;
	s16 temp2=y;
	Data_sd[0]=0x66;
	Data_sd[1]=0x05;
	Data_sd[2]=BYTE0(temp);
	Data_sd[3]=BYTE1(temp);
	Data_sd[4]=BYTE0(temp2);
	Data_sd[5]=BYTE1(temp2);
	Data_sd[6]=0xee;
	DrvUart1SendBuf(Data_sd,7);
}

