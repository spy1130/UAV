#include <string.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "wit_c_sdk.h"
#include "UART1.h"
#include "UART2.h"
#include "delay.h"
#include "oled.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x.h"
#include "Oled.h"
#include "usart.h"
#include "pwm.h"
#include "Keyboard.h"
#include "Timer.h"
#include "LX_DT.h"
#include "moto.h"
#include "Pid.h"
#include "Math.h"

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80
static volatile char s_cDataUpdate = 0, s_cCmd = 0xff;
const uint32_t c_uiBaud[10] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
static void CmdProcess(void);
static void AutoScanSensor(void);
static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void Delayms(uint16_t ucMs);
extern u8 Nano_send_buffer[50];
extern S16_Byte FirePosition;
extern pid_param_t TurnControl;
//u8 Turn_Flag = 0;
u8 MissionFlag = 0;
	s16 angle = 0;
	s16 counttime = 0;
u8 MissionQuality = 0;
float fAcc[3], fGyro[3], fAngle[3];
u8 CurrLevel;
int main(void)
{
	
	int i;
	u8 stop=0;
	u8 back=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	SysTick_Init();
	Usart1Init(115200);
	Usart2Init(9600);
	uart3_init(115200);
	WitInit(WIT_PROTOCOL_NORMAL, 0x50);
	WitSerialWriteRegister(SensorUartSend);
	WitRegisterCallBack(SensorDataUpdata);
	WitDelayMsRegister(Delayms);
	OLED_Init();
	InitDirection();
	PWM_Int(1999,719);
	Timer1_Init(499,14399);//10ms
	PidInit(&TurnControl);
	Matrix_ssKey_Pin_Init();
	//OLED_Clear();
	u8 string[10] = {0};

	u8 stopFlag = 0;
	u8 backFlag  = 0 ;

	AutoScanSensor();
	
	while (1)
	{
		//angle = atan2((double)(185-135),(double)(45-25))/3.14159265*180.0;
		CurrLevel = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12);
		CmdProcess();
		stop = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
		back = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
		DataSend(CurrLevel);

		
		
//		OLED_Refresh();
		//delay_us(100);
		
	//	for(i=0;i<15;i++){
	//		USART_SendData(USART3,Nano_send_buffer[i]);
	//		delay_us(1000);
	//	}
		if(s_cDataUpdate)
		{
			for(i = 0; i < 3; i++)
			{
				fAcc[i] = sReg[AX+i] / 32768.0f * 16.0f;
				fGyro[i] = sReg[GX+i] / 32768.0f * 2000.0f;
				fAngle[i] = sReg[Roll+i] / 32768.0f * 180.0f;
			}
			if(s_cDataUpdate & ACC_UPDATE)
			{
				//printf("acc:%.3f %.3f %.3f\r\n", fAcc[0], fAcc[1], fAcc[2]);
				s_cDataUpdate &= ~ACC_UPDATE;
			}
			if(s_cDataUpdate & GYRO_UPDATE)
			{
				//printf("gyro:%.3f %.3f %.3f\r\n", fGyro[0], fGyro[1], fGyro[2]);
				s_cDataUpdate &= ~GYRO_UPDATE;
			}
			if(s_cDataUpdate & ANGLE_UPDATE)
			{
				//printf("angle:%.3f %.3f %.3f\r\n", fAngle[0], fAngle[1], fAngle[2]);
				s_cDataUpdate &= ~ANGLE_UPDATE;
			}
			if(s_cDataUpdate & MAG_UPDATE)
			{
				//printf("mag:%d %d %d\r\n", sReg[HX], sReg[HY], sReg[HZ]);
				s_cDataUpdate &= ~MAG_UPDATE;
			}
		}
	//	sprintf((char *)string,"Z:%.2f  QLY:%d",fAngle[2],MissionQuality);//0300
		
		sprintf((char *)string,"Z:%.2f  CUT:%d",fAngle[2],counttime);//0300
		OLED_ShowString(0,0,string,16);
		sprintf((char *)string,"%d  Angle%d",CurrLevel,angle);//0300
		OLED_ShowString(0,16,string,16);
		OLED_Refresh();
		
		

//	
		if(stop == 0 && stopFlag == 0)
		{
			MissionFlag = 200;
			stopFlag = 1;
		}
		if(back == 0 && backFlag == 0)
		{
			MissionFlag = 250;
			backFlag = 1;
		}
		
	}
}

void CopeCmdData(unsigned char ucData)
{
	static unsigned char s_ucData[50], s_ucRxCnt = 0;
	
	s_ucData[s_ucRxCnt++] = ucData;
	if(s_ucRxCnt<3)return;										//Less than three data returned
	if(s_ucRxCnt >= 50) s_ucRxCnt = 0;
	if(s_ucRxCnt >= 3)
	{
		if((s_ucData[1] == '\r') && (s_ucData[2] == '\n'))
		{
			s_cCmd = s_ucData[0];
			memset(s_ucData,0,50);//
			s_ucRxCnt = 0;
		}
		else 
		{
			s_ucData[0] = s_ucData[1];
			s_ucData[1] = s_ucData[2];
			s_ucRxCnt = 2;
			
		}
	}

}
static void ShowHelp(void)
{
//	printf("\r\n************************	 WIT_SDK_DEMO	************************");
//	printf("\r\n************************          HELP           ************************\r\n");
//	printf("UART SEND:a\\r\\n   Acceleration calibration.\r\n");
//	printf("UART SEND:m\\r\\n   Magnetic field calibration,After calibration send:   e\\r\\n   to indicate the end\r\n");
//	printf("UART SEND:U\\r\\n   Bandwidth increase.\r\n");
//	printf("UART SEND:u\\r\\n   Bandwidth reduction.\r\n");
//	printf("UART SEND:B\\r\\n   Baud rate increased to 115200.\r\n");
//	printf("UART SEND:b\\r\\n   Baud rate reduction to 9600.\r\n");
//	printf("UART SEND:R\\r\\n   The return rate increases to 10Hz.\r\n");
//	printf("UART SEND:r\\r\\n   The return rate reduction to 1Hz.\r\n");
//	printf("UART SEND:C\\r\\n   Basic return content: acceleration, angular velocity, angle, magnetic field.\r\n");
//	printf("UART SEND:c\\r\\n   Return content: acceleration.\r\n");
//	printf("UART SEND:h\\r\\n   help.\r\n");
//	printf("******************************************************************************\r\n");
}

static void CmdProcess(void)
{
	switch(s_cCmd)
	{
		case 'a':	
			if(WitStartAccCali() != WIT_HAL_OK) 
				//printf("\r\nSet AccCali Error\r\n");
			break;
		case 'm':	
			if(WitStartMagCali() != WIT_HAL_OK) 
				//printf("\r\nSet MagCali Error\r\n");
			break;
		case 'e':	
			if(WitStopMagCali() != WIT_HAL_OK)
				//printf("\r\nSet MagCali Error\r\n");
			break;
		case 'u':	
			if(WitSetBandwidth(BANDWIDTH_5HZ) != WIT_HAL_OK) 
				//printf("\r\nSet Bandwidth Error\r\n");
			break;
		case 'U':	
			if(WitSetBandwidth(BANDWIDTH_256HZ) != WIT_HAL_OK) 
				//printf("\r\nSet Bandwidth Error\r\n");
			break;
		case 'B':	
			if(WitSetUartBaud(WIT_BAUD_115200) != WIT_HAL_OK) ;
				//printf("\r\nSet Baud Error\r\n");
			else 
				Usart2Init(c_uiBaud[WIT_BAUD_115200]);											
			break;
		case 'b':	
			if(WitSetUartBaud(WIT_BAUD_9600) != WIT_HAL_OK);
				//printf("\r\nSet Baud Error\r\n");
			else 
				Usart2Init(c_uiBaud[WIT_BAUD_9600]);												
			break;
		case 'R':	
			if(WitSetOutputRate(RRATE_10HZ) != WIT_HAL_OK) 
				//printf("\r\nSet Rate Error\r\n");
			break;
		case 'r':	
			if(WitSetOutputRate(RRATE_1HZ) != WIT_HAL_OK) 
				//printf("\r\nSet Rate Error\r\n");
			break;
		case 'C':	
			if(WitSetContent(RSW_ACC|RSW_GYRO|RSW_ANGLE|RSW_MAG) != WIT_HAL_OK) 
				//printf("\r\nSet RSW Error\r\n");
			break;
		case 'c':	
			if(WitSetContent(RSW_ACC) != WIT_HAL_OK) 
				//printf("\r\nSet RSW Error\r\n");
			break;
		case 'h':
			//ShowHelp();
			break;
	}
	s_cCmd = 0xff;
}

static void SensorUartSend(uint8_t *p_data, uint32_t uiSize)
{
	Uart2Send(p_data, uiSize);
}

static void Delayms(uint16_t ucMs)
{
	delay_ms(ucMs);
}

static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
	int i;
    for(i = 0; i < uiRegNum; i++)
    {
        switch(uiReg)
        {
//            case AX:
//            case AY:
            case AZ:
				s_cDataUpdate |= ACC_UPDATE;
            break;
//            case GX:
//            case GY:
            case GZ:
				s_cDataUpdate |= GYRO_UPDATE;
            break;
//            case HX:
//            case HY:
            case HZ:
				s_cDataUpdate |= MAG_UPDATE;
            break;
//            case Roll:
//            case Pitch:
            case Yaw:
				s_cDataUpdate |= ANGLE_UPDATE;
            break;
            default:
				s_cDataUpdate |= READ_UPDATE;
			break;
        }
		uiReg++;
    }
}

static void AutoScanSensor(void)
{
	int i, iRetry;
	
	for(i = 1; i < 10; i++)
	{
		Usart2Init(c_uiBaud[i]);
		iRetry = 2;
		do
		{
			s_cDataUpdate = 0;
			WitReadReg(AX, 3);
			delay_ms(100);
			if(s_cDataUpdate != 0)
			{
				//printf("%d baud find sensor\r\n\r\n", c_uiBaud[i]);
				//ShowHelp();
				return ;
			}
			iRetry--;
		}while(iRetry);		
	}
	//printf("can not find sensor\r\n");
	//printf("please check your connection\r\n");
}

