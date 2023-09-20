#include  "oled.h" 
#include  "codetab.h" //专用字模数组存放头文件
#include  "delay.h"
// ------------------------------------------------------------
// IO口软件模拟I2C通信
// SCL接PB^15
// SDA接PB^9
// ------------------------------------------------------------
void OLED_GPIO_Init(void)  
{
	
    GPIO_InitTypeDef GPIO_InitStructure;
	
//    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//上拉
//		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	
	
	
	
	
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 
 GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1);						 //PB.5 输出高

	
}

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{   
	 OLED_SDA = high;
	 delay_us(1);
   OLED_SCL = high;
   delay_us(1);
   OLED_SDA = low;
	 delay_us(1);
   OLED_SCL = low;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{ 
	 OLED_SDA = low;
	 delay_us(1);
   OLED_SCL = low;
   delay_us(1);
   OLED_SDA = high;
	 delay_us(1);
   OLED_SCL = high;
}

/**********************************************
// 通过I2C总线写一个字节
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
  for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			OLED_SDA=high;
		else
			OLED_SDA=low;
		    delay_us(1);
		OLED_SCL=high;
        delay_us(1);  //必须有保持SCL脉冲的延时
		OLED_SCL=low;
		    delay_us(1);
		IIC_Byte<<=1;
	}
    //原程序这里有一个拉高SDA，根据OLED的DATASHEET，此句必须去掉。
	OLED_SCL=1;
    delay_us(1);
	OLED_SCL=0;
}

/*********************OLED写数据*********************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}
/*********************OLED写命令**********************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);          //Slave address,SA0=0
	Write_IIC_Byte(0x00);			     //write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}
/*********************OLED 设置坐标*******************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
   OLED_Fill(0x00);
}
//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
	OLED_WrCmd(0X8D);  //设置电荷泵
	OLED_WrCmd(0X14);  //开启电荷泵
	OLED_WrCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	OLED_WrCmd(0X8D);  //设置电荷泵
	OLED_WrCmd(0X10);  //关闭电荷泵
	OLED_WrCmd(0XAE);  //OLED休眠
}
/*********************OLED初始化************************************/
void OLED_Init(void)
{
	OLED_GPIO_Init();
	delay_ms(100);//初始化之前的延时很重要！
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
} 
/*功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7*/
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[],unsigned char against)
{
	unsigned char c=0,i=0,j=0;
	unsigned char Temp;
		if(!against)Temp = 0x00;
	else Temp = 0xFF;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]^Temp);
		x+=6;
		j++;
	}
}
/*功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7*/
void OLED_P8x16Str(unsigned char x,unsigned  char y,unsigned char ch[],unsigned char against)
{
	unsigned char c=0,i=0,j=0;
	unsigned char Temp;
	  if(!against)Temp = 0x00;
	else Temp = 0xFF;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
	 OLED_WrDat(F8X16[c*16+i]^Temp);
	 OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
	 OLED_WrDat(F8X16[c*16+i+8]^Temp);
		x+=8;
		j++;
	}
}
/*功能描述：显示 6*8 点阵 显示的坐标（x,y），y为页范围0～7*/
void OLED_Show6x8(unsigned char x,unsigned char y,unsigned int N,unsigned char against)
{
	unsigned char i = 0;
	unsigned int  adder = 6*N;
	unsigned char Temp;
		if(!against)Temp = 0x00;
	else Temp = 0xFF;
  if(x>126)
     x=0,y++;
	OLED_Set_Pos(x,y);
  for(i=0;i < 6;i++)OLED_WrDat(My6x8[adder++]^Temp);
}
/*功能描述：显示 8*16 点阵 显示的坐标（x,y），y为页范围0～7*/
void OLED_Show8x16(unsigned char x,unsigned char y,unsigned int N,unsigned char against)
{
	unsigned char i = 0;
	unsigned int  adder = 16*N;
	unsigned char Temp;
		if(!against)Temp = 0x00;
	else Temp = 0xFF;
  if(x>120)
     x=0,y++;
	OLED_Set_Pos(x,y);
	 for(i=0;i < 8;i++)
	OLED_WrDat(My8x16[adder++]^Temp);
	OLED_Set_Pos(x,y+1);
	 for(i=0;i < 8;i++)
	OLED_WrDat(My8x16[adder++]^Temp);			
}
/*功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7*/
void OLED_Show16x16(unsigned char x,unsigned char y,unsigned int N,unsigned char against)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	unsigned char Temp;
		if(!against)Temp = 0x00;
	else Temp = 0xFF;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]^Temp);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]^Temp);
		adder += 1;
	}   	
}
/*功能描述：显示6x8或者8x16的 u16（无符号16位数据）(TextSize：0-> 6x8 ,1-> 8x16)，显示的坐标（x,y），y为页范围0～7*/
void Oled_Printf_U16(unsigned char x,unsigned char y,unsigned int num,unsigned char TextSize)
{
	unsigned char temp[6],i;
	temp[5] = '\0';
	temp[4] = (unsigned char)(num%10+'0');num/=10;
	temp[3] = (unsigned char)(num%10+'0');num/=10;
	temp[2] = (unsigned char)(num%10+'0');num/=10;
	temp[1] = (unsigned char)(num%10+'0');num/=10;
	temp[0] = (unsigned char)(num%10+'0');
	for(i=0;i<4;i++)
	{
		if(temp[i]=='0')
			temp[i]=' ';
		else
			break;
	}
	switch(TextSize)
	{
		case 0:
			OLED_P6x8Str(x,y,temp,0);
			break;
		case 1:
			OLED_P8x16Str(x,y,temp,0);
			break;
		default:
			break;
	}
}
/*功能描述：显示6x8或者8x16的 float 数据，显示的坐标（x,y），y为页范围0～7*/
void Oled_Printf_Float(unsigned char x,unsigned char y,float num,unsigned char TextSize)
{
	unsigned char i;
	unsigned char result[7];
	unsigned char  tempH;
	unsigned char tempL;
	result[6]='\0';
	result[3] = '.';
	if(num < 0)
	{
    num = -num;
		result[0] = '-';
	}
	else
		result[0] = '+';
	tempH = (unsigned int)num;
	tempL = (unsigned char)((num - tempH)*100);
  for(i=0;i<4;i++)
	{
		switch(i)
		{
			/*显示整数部分*/
			case 0:result[2] = tempH%10 + '0';tempH/=10;break;
			case 1:result[1] = tempH + '0';break;
			/*显示小数部分*/
			case 2:result[5] = tempL%10 + '0';tempL/=10;break;
			case 3:result[4] = tempL + '0';break;
		 default:break;
		}
	}	
	 for(i=1;i<2;i++)
	{
		if(result[i]=='0')
			result[i]=' ';
		else
			break;
	}
	switch(TextSize)
 {
	case 0:
		OLED_P6x8Str(x,y,result,0);break;
	case 1:
		OLED_P8x16Str(x,y,result,0);break;
	default:break;
	}
}

