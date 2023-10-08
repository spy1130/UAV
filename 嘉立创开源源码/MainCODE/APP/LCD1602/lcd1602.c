/*
硬件连线：
	LCD   ： D0-D7     RS     RW     E      A      K/VSS  VDD  V0
	STM32 ： PA0-PA7   PB12   PB13   PB14   5V   GND    5v 电压调解端
	供地
*/

#include "lcd1602.h"
#include "delay.h"

void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA的时钟
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = LCD_PORT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//LCD D0-D7
	
	GPIO_ResetBits(GPIOA,LCD_PORT_PIN);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOA的时钟
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = LCD_RS_PIN|LCD_RW_PIN|LCD_EN_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//LCD RS RW EN
	
	GPIO_ResetBits(GPIOB,LCD_RS_PIN|LCD_RW_PIN|LCD_EN_PIN);
}

void LCD_Init(void)
{
	LCD_GPIO_Init();
	delay_ms(20);
	LCD_Write_Command(0x38);
	delay_ms(5);
	LCD_Write_Command(0x38);
	delay_ms(5);
	LCD_Write_Command(0x38);
	delay_ms(5);
	LCD_Write_Command(0x0c);
	LCD_Write_Command(0x01);
	LCD_Write_Command(0x06);
	delay_ms(20);
}

void LCD_Clear(void)
{
	LCD_Write_Command(0x01);
}

/*
RS: 高电平：表示写的是数据data（代表我们要想在屏幕显示的具体数据：'A'）   
	低电平：表示写的是命令command（操作LCD内部寄存器的值）
RW:低电平：表示向LCD写东西     高电平：表示从LCD读东西
E:Enable Signal
DB0-DB7:lcd的数据总线

	LCD     RS        RW      意思
			0          0       写命令
			0          1       读命令
			1          0       写数据
			1          1       读数据

*/

#define LCD_PORT GPIOA->ODR
void LCD_Write_Command(unsigned char com)
{
	//判断LCD是否处于繁忙，如果不是就向其写东西
	//delay_ms(10);
	LCD_Read_State();
	
	LCD_RS = 0;
	LCD_RW = 0;

	LCD_PORT = com;
	//GPIOA->ODR = com;
	
	LCD_EN = 0;
	delay_us(5);
	LCD_EN = 1;
	//延时tPW
	delay_us(10);
	LCD_EN = 0;
	
}
	
void LCD_Write_Data(unsigned char dat)
{
	//判断LCD是否处于繁忙，如果不是就向其写东西
	//delay_ms(10);
	
	LCD_Read_State();
	
	LCD_RS = 1;
	LCD_RW = 0;
	
	LCD_PORT = dat;
	
	LCD_EN = 0;
	delay_us(5);
	LCD_EN = 1;
	//延时tPW
	delay_us(10);
	LCD_EN = 0;	
}

/*
读数据：
D0-D7:
D7 == 1:LCD1602繁忙状态
返回值：0：不忙 1：繁忙
*/
void LCD_Read_State(void)//判忙函数
{
	unsigned char state = 0;
#if 0
	GPIO_InitTypeDef GPIO_InitStruct;
	
	LCD_PORT = 0xff;
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin   = LCD_PORT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//LCD D0-D7
	
	LCD_RS = 0;
	LCD_RW = 1;
	while(state != 0)
	{
		LCD_EN = 1;
		delay_us(10);
		state = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
		LCD_EN = 0;
	}	

	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = LCD_PORT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//LCD D0-D7
#else
	
#define DATAOUT(GPIOx,value) GPIO_Write(GPIOx,value)
	
	DATAOUT(GPIOA,0xff);
	LCD_RS = 0;
	LCD_RW = 1;
	do
	{
		LCD_EN = 1;
		delay_ms(5);	
		state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7);
		LCD_EN = 0;
	}while(state & 0x80);
#endif
	
}
	
void LCD_Set_Position(unsigned char x,unsigned char y)
{
	if(y == 0)//第一行开始
	{
		LCD_Write_Command(0x80+x);
	}
	else if(y == 1)
	{
		LCD_Write_Command(0xC0+x);
	}
	else;
}

void LCD_Display_Char(unsigned char dat,unsigned char x,unsigned char y)//'0'/:48
{
	LCD_Set_Position(x,y);
	LCD_Write_Data(dat);
}

void LCD_Display_String(unsigned char x,unsigned char y,unsigned char *str)
{
	int i = 0;
	LCD_Set_Position(x,y);
	
	while(str[i] != '\0')
	{
		LCD_Write_Data(str[i]);
		i++;
	}
}







