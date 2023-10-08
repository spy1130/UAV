#include "Keyboard.h"
#include "LX_DT.h"

void Matrix_ssKey_Pin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

u8 Matrix_Key_Scan(void)
{
	u8 temp = 0;
	static u8 key_val = 0;
	
	//delay_ms(30); 
	GPIO_ResetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);			//拉低行线
	//delay_us(10);
	//temp =(GPIO_ReadInputData(GPIOB) >> 8)&0xff;	

	//第一行
	GPIO_Write(GPIOB,0);
	delay_ms(5);
	GPIO_Write(GPIOB,(uint16_t)(0xFE << 8)); 
	
	if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
	{
			delay_ms(5);//消抖

			if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
			{
					temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFE);		//对列进行扫描
					switch(temp)
					{
							case 0xEE:  key_val = 1;   break;
							case 0xDE:  key_val = 2;   break;
							case 0xBE:  key_val = 3;   break;
							case 0x7E:  key_val = 4;   break;
							default:    key_val = 31;   break;
					}
			}
	}
	
	//第二行
	GPIO_Write(GPIOB,0);
	delay_ms(5);
	GPIO_Write(GPIOB,(uint16_t)(0xFD << 8));
	
	if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0)!= 0XF0)
	{
			delay_ms(5);

			if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
			{
					temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFD);
					switch(temp)
					{
							case 0xED:  key_val = 5;   break;
							case 0xDD:  key_val = 6;   break;
							case 0xBD:  key_val = 7;   break;
							case 0x7D:  key_val = 8;   break;
							default:    key_val = 31;   break;
					}
			}
	}
	
	//第三行
	GPIO_Write(GPIOB,0);
	delay_ms(5);
	GPIO_Write(GPIOB,(uint16_t)(0xFB << 8));
	
	if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
	{
			delay_ms(5);

			if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
			{
					temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XFB);
					switch(temp)
					{
							case 0xEB:  key_val = 9;   break;
							case 0xDB:  key_val = 10;   break;
							case 0xBB:  key_val = 11;   break;
							case 0x7B:  key_val = 12;   break;
							default:    key_val = 31;   break;
					}
			}
	}
	
	//第四行
	GPIO_Write(GPIOB,0);
	delay_ms(5);
	GPIO_Write(GPIOB,(uint16_t)(0xF7 << 8));
	
	if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) !=0XF0)
	{
			delay_ms(5);

			if(((GPIO_ReadInputData(GPIOB) >> 8) & 0XF0) != 0XF0)
			{
					temp=((GPIO_ReadInputData(GPIOB) >> 8) & 0XF7);
					switch(temp)
					{
							case 0xE7:  key_val = 13;   break;
							case 0xD7:  key_val = 14;   break;
							case 0xB7:  key_val = 15;   break;
							case 0x77:  key_val = 16;   break;
							default:    key_val = 31;   break;
					}
			}
		}
		
	
	return key_val - 1;
 
}

void KeyBoardSend(u8 key)
{
	static u8 lastval = 30;
	
	if(lastval != key)
	{
		u8 send_buffer[10];
		lastval = key;
		u8 count = 0;
		send_buffer[count ++] = 0x66;
		send_buffer[count ++] = 0x98;
		send_buffer[count ++] = lastval;

		send_buffer[count ++] = 0xEE;
	
		for(int i = 0;i < count;i ++)
		{
			USART_SendData(USART1,send_buffer[i]);
			delay_us(60);
		}
	}
}
