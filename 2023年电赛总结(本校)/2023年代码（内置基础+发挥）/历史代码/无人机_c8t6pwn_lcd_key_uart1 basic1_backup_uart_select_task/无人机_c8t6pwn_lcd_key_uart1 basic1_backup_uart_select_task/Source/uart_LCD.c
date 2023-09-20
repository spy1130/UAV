#include "uart_LCD.h"
#include "UART.h"
#include "delay.h"

extern u8 color_xy;
extern u8 color_wall;

u8 str_1[]={"DS16(0,0,'1:开始,2:停止,3:清屏',15);\r\n"};
u8 str_2[]={"DS16(0,17,'4:缩小,5:放大',15);\r\n"};

void LED_PS(u16 x, u16 y, u16 c)//画点
{
	u8 str_ps[18];
	
	str_ps[0] = 'P';
	str_ps[1] = 'S';
	str_ps[2] = '(';
	str_ps[3] = x/100%10 + '0';
	str_ps[4] = x/10%10 + '0';
	str_ps[5] = x%10 + '0';
	str_ps[6] = ',';
	str_ps[7] = y/100%10 + '0';
	str_ps[8] = y/10%10 + '0';
	str_ps[9] = y%10 + '0';
	str_ps[10] = ',';
	str_ps[11] = c/100%10 + '0';
	str_ps[12] = c/10%10 + '0';
	str_ps[13] = c%10 + '0';
	str_ps[14] = ')';
	str_ps[15] = ';';
	str_ps[16] = 0x0D;
	str_ps[17] = '\0';
	
	UART2_SendStr(str_ps);
}

void LED_PL(u16 x1, u16 y1, u16 x2, u16 y2, u16 c)//画线PL(x1,y1,x2,y2,c);
{
	u8 str_pl[26];
	
	str_pl[0] = 'P';
	str_pl[1] = 'L';
	str_pl[2] = '(';
	str_pl[3] = x1/100%10 + '0';
	str_pl[4] = x1/10%10 + '0';
	str_pl[5] = x1%10 + '0';
	str_pl[6] = ',';
	str_pl[7] = y1/100%10 + '0';
	str_pl[8] = y1/10%10 + '0';
	str_pl[9] = y1%10 + '0';
	str_pl[10] = ',';
	str_pl[11] = x2/100%10 + '0';
	str_pl[12] = x2/10%10 + '0';
	str_pl[13] = x2%10 + '0';
	str_pl[14] = ',';
	str_pl[15] = y2/100%10 + '0';
	str_pl[16] = y2/10%10 + '0';
	str_pl[17] = y2%10 + '0';
	str_pl[18] = ',';
	str_pl[19] = c/100%10 + '0';
	str_pl[20] = c/10%10 + '0';
	str_pl[21] = c%10 + '0';
	str_pl[22] = ')';
	str_pl[23] = ';';
	str_pl[24] = 0x0D;
	str_pl[25] = '\0';
	
	UART2_SendStr(str_pl);
}
//16*16数字显示
void LCD_DS16(u16 x, u16 y, u32 num, u16 c)
{
	u8 str_ds1[14];
	u8 str_ds2[10];
	u8 str_ds3[8];//发送格式DS32(9,13,'123456',1);
	s8 i;
	u32 num_size;
	
	num_size = num;
	for(i=0; i<=8; i++)
	{
		if(num_size == 0)
			break;
		num_size = num_size/10;
	}
	str_ds2[i+1] = '\0';
	for(; i>=0; i--)
	{
		str_ds2[i] = num%10+'0';
		num = num/10;
	}
	str_ds1[0] = 'D';
	str_ds1[1] = 'S';
	str_ds1[2] = '1';
	str_ds1[3] = '6';
	str_ds1[4] = '(';
	str_ds1[5] = x/100%10 + '0';
	str_ds1[6] = x/10%10 + '0';
	str_ds1[7] = x%10 + '0';
	str_ds1[8] = ',';
	str_ds1[9] = y/100%10 + '0';
	str_ds1[10] = y/10%10 + '0';
	str_ds1[11] = y%10 + '0';
	str_ds1[12] = ',';
	str_ds1[13] = 0x27;//'
	str_ds1[13] = '\0';//'
	
	str_ds3[0] = 0x27;
	str_ds3[1] = c/100%10 + '0';
	str_ds3[2] = c/10%10 + '0';
	str_ds3[3] = c%10 + '0';
	str_ds3[4] = ')';
	str_ds3[5] = ';';
	str_ds3[6] = 0x0D;
	str_ds3[7] = '\0';
	
	UART2_SendStr(str_ds1);
	UART2_SendStr(str_ds2);
	UART2_SendStr(str_ds3);
}

//32*32数字显示
void LCD_DS32(u16 x, u16 y, u32 num, u16 c)
{
	u8 str_ds1[14];
	u8 str_ds2[10];
	u8 str_ds3[8];//发送格式DS32(9,13,'123456',1);
	s8 i;
	u32 num_size;
	
	num_size = num;
	for(i=0; i<=8; i++)
	{
		if(num_size == 0)
			break;
		num_size = num_size/10;
	}
	str_ds2[i+1] = '\0';
	for(; i>=0; i--)
	{
		str_ds2[i] = num%10+'0';
		num = num/10;
	}
	str_ds1[0] = 'D';
	str_ds1[1] = 'S';
	str_ds1[2] = '3';
	str_ds1[3] = '2';
	str_ds1[4] = '(';
	str_ds1[5] = x/100%10 + '0';
	str_ds1[6] = x/10%10 + '0';
	str_ds1[7] = x%10 + '0';
	str_ds1[8] = ',';
	str_ds1[9] = y/100%10 + '0';
	str_ds1[10] = y/10%10 + '0';
	str_ds1[11] = y%10 + '0';
	str_ds1[12] = ',';
	str_ds1[13] = 0x27;//'
	str_ds1[13] = '\0';//'
	
	str_ds3[0] = 0x27;
	str_ds3[1] = c/100%10 + '0';
	str_ds3[2] = c/10%10 + '0';
	str_ds3[3] = c%10 + '0';
	str_ds3[4] = ')';
	str_ds3[5] = ';';
	str_ds3[6] = 0x0D;
	str_ds3[7] = '\0';
	
	UART2_SendStr(str_ds1);
	UART2_SendStr(str_ds2);
	UART2_SendStr(str_ds3);
}

void LED_Init(u16 c)//清屏，c为背景色
{
	u8 str_init[15];
	
	str_init[0] = 'D';
	str_init[1] = 'R';
	str_init[2] = '3';
	str_init[3] = ';';
	str_init[4] = 'C';
	str_init[5] = 'L';
	str_init[6] = 'S';
	str_init[7] = '(';
	str_init[8] = c/100%10+'0';
	str_init[9] = c/10%10+'0';
	str_init[10] = c%10+'0';
	str_init[11] = ')';
	str_init[12] = ';';		//DR2;CLS(0);
	str_init[13] = 0x0D;
	str_init[14] = '\0';
	
	UART2_SendStr(str_init);
}

void Show_Init(void)
{
	LED_Init(color_wall); //清屏，c为背景色
	delay_ms(200);
	LED_Init(color_wall); //清屏，c为背景色
	delay_ms(200);
	UART2_SendStr(str_1);
	delay_ms(3);
	UART2_SendStr(str_2);
	LED_PL(120, 0, 120, 319, color_xy); //画线
	delay_ms(3);
	LED_PL(0, 160, 239, 160, color_xy); //画线
}







