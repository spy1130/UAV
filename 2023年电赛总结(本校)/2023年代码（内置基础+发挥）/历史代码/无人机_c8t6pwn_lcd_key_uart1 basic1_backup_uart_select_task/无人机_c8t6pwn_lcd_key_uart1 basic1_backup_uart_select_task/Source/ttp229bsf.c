#include "ttp229bsf.h"
#include "UART.h"
#include "uart_LCD.h"

extern u8 flag;
extern u8 scale;//扫描图像放大比例系数
extern u8 color_wall;
extern u8 stay;

u16 keysta[16] = {
	0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
	0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
};

void TTP229_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//使能 GPIO 端口B时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置引脚为上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIOB 端口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置输出速率为 50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置引脚为推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIOB 端口
}

u16 TTP229_Readkey(void)
{
	u32 mask;
	u16 keynum;
	
	keynum = 0;
	TTP229_SCL=1;
	for(mask=1; mask<=0x00008000; mask<<=1)
	{
		TTP229_SCL=0;
		TTP229_SCL=1;
		if(TTP229_SDO == 0)
			keynum &= ~mask;
		else
			keynum |= mask;
	}
	
	return keynum;
}

void keyplay(u8 keycode)
{
	if(keycode == 0)//按键1雷达开始扫描
	{
		stay = 1;
		UART1_Send(0x62);
	}
	else if(keycode == 1)//按键2雷达停止扫描
	{
		stay = 0;
		UART1_Send(0x65);
	}
	else if(keycode == 2)//按键3清屏
	{
		USART_Cmd(USART1,DISABLE);   //使能USART2
		Show_Init();
		flag = 0;
		USART_Cmd(USART1,ENABLE);    //使能USART2
	}
	else if(keycode == 3)//按键4缩小图像比例
	{
		if(scale < 30)
			scale++;
		USART_Cmd(USART1,DISABLE);  //使能USART2
		Show_Init();
		flag = 0;
		USART_Cmd(USART1,ENABLE);   //使能USART2
	}
	else if(keycode == 4)//按键5增大图像比例
	{
		if(scale > 1)
			scale--;
		USART_Cmd(USART1,DISABLE);  //使能USART2
		Show_Init();
		flag = 0;
		USART_Cmd(USART1,ENABLE);   //使能USART2
	}
}

void keyaction(void)
{
	u8 i;
	u16 keybuff;
	static u16 backup[16] = {
	0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
	0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000
	};
	
	keybuff = TTP229_Readkey();
	for(i=0; i<16; i++)
	{
		if((keybuff & keysta[i]) != backup[i])
		{
			if(backup[i] != 0)
				keyplay(i);
			backup[i] = (keybuff & keysta[i]);
		}
	}
}









