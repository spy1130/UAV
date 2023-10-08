#include "wwdg.h"
#include "led.h"

/*
窗口看门狗编程步骤：
1，开启时钟
2，设置分频系数
3，设置窗口值和计数值
4，清除中断标志位
5，开启窗口看门狗
6，编写中断函数
*/

//保存WWDG计数器的设置值,默认为最大. 
u8 WWDG_CNT=0x7f; 
//初始化窗口看门狗 	
//tr   :T[6:0],计数器值 
//wr   :W[6:0],窗口值 
//fprer:分频系数（WDGTB）,仅最低2位有效 
//Fwwdg=PCLK1/(4096*2^fprer). 

void WWDG_Init(u8 tr,u8 wr,u32 fprer)//100ms
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //   WWDG时钟使能

	WWDG_CNT=tr&WWDG_CNT;   //初始化WWDG_CNT.   
	WWDG_SetPrescaler(fprer);////设置IWDG预分频值

	WWDG_SetWindowValue(wr);//设置窗口值

	WWDG_Enable(WWDG_CNT);	 //使能看门狗 ,	设置 counter .                  

	WWDG_ClearFlag();//清除提前唤醒中断标志位 

	WWDG_NVIC_Init();//初始化窗口看门狗 NVIC

	WWDG_EnableIT(); //开启窗口看门狗中断
} 
//重设置WWDG计数器的值
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);//使能看门狗 ,	设置 counter .	 
}

//窗口看门狗中断服务程序
void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占2，子优先级3，组2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //抢占2，子优先级3，组2	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);//NVIC初始化
}


void WWDG_IRQHandler(void)
{

	WWDG_SetCounter(WWDG_CNT);	  //当禁掉此句后,窗口看门狗将产生复位

	WWDG_ClearFlag();	  //清除提前唤醒中断标志位

	led =!led;		 //LED状态翻转
}

