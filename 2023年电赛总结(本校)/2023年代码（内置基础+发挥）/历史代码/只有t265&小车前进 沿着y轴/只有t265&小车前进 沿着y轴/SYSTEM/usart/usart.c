#include "sys.h"
#include "usart.h"	 
#define sec_basis 0


u8 rx_buff[38]={0};
u8 rx_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx_num=0,command_text=0x00;

u8 rx_buff2[38]={0};
u8 rx_end_flag2=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx_star_flag2=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx_num2=0,command_text2=0x00;


u8 rx3_buff[38]={0};
u8 rx3_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx3_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx3_num=0,command_text3=0x00;

u8 first_frame_end=0x00,second_frame_end=0x00,find_pole_flag=0;







u8 res;
u8 row_cloumn_all=0;
u8 row_num=0;
u8 cloumn_num=0;



short  YAW=0,PITCH=0,ROLL=0;
u8   gy_5_flag=0;
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  










void uart4_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4, ENABLE);	//ʹ��UART4��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC ,ENABLE);//GPIOAʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
	
	//USART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PD.5
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOD.5
   
  //USART4_RX	  GPIOC.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PD6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOD.6  
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//Ҫʹ�ý�����ӳ��
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//Ҫʹ��PA15��PB3��PA2��PA3�Ķ˿���ϣ�Ҫ���в�����ӳ��

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(UART4, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���1 

}


void UART4_IRQHandler(void)
{
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET);//USART_IT_RXNE
	
	
	 res =USART_ReceiveData(UART4);	//��ȡ���յ�������
            

	 switch(rx_num)
	 {
		  case 0://freame star
		 {
			 if(0xaa==res)
			 {
				 rx_buff[0]=res;
				 rx_num=0x01;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
			 }
			 else
			 {
				 rx_buff[0]=0x00;
				 rx_buff[1]=0x00;
				 rx_buff[2]=0x00;
				 rx_buff[3]=0x00;
				 rx_buff[4]=0x00;
				 rx_buff[5]=0x00;
				 rx_buff[6]=0x00;
				 rx_buff[7]=0x00;
				
				 
				 rx_num=0x00;
				 rx_end_flag=0x00;
				 rx_star_flag=0x00;
			 }
			 
			 
			 break;
		 } 
		 case 1://YAWY hige 8 bit
		 {
			 
			 rx_buff[1]=res;
			 rx_num=0x02;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
				 
			 
			 
			 break;
		 }
		 case 2:////YAWY low 8 bit
		 {
			 rx_buff[2]=res;
			 rx_num=0x03;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
		 
		 case 3://PITCH hige 8 bit
		 {
			 
			 rx_buff[3]=res;
			 rx_num=0x04;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 
		 
			 break;      
						 
		  }
		  
		case 4://length
		 {
			 rx_buff[4]=res;
			 rx_num=0x05;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
		 
		  case 5://length
		 {
			 rx_buff[5]=res;
			 rx_num=0x06;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
		  case 6://length
		 {
			 rx_buff[6]=res;
			 rx_num=0x07;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
			
		 
		 
		 case 7://PITCH low 8 bit
		 {
			 if(res==0x55)
			 {
				  
				  rx_buff[7]=res;
				 
				 
				  YAW=(rx_buff[1]<<8|rx_buff[2]);//YAW��PITCH,ROLLΪ��ʵֵ��100��
				  PITCH=(rx_buff[3]<<8|rx_buff[4]);
				  ROLL=(rx_buff[5]<<8|rx_buff[6]);
				  rx_num=0x00;
				  rx_end_flag=0x01;
				  rx_star_flag=0x01;
//				  LED0=!LED0;
//				 
			 }
			 else
			{
				 rx_buff[0]=0x00;
				 rx_buff[1]=0x00;
				 rx_buff[2]=0x00;
				 rx_buff[3]=0x00;
				 rx_buff[4]=0x00;
				 rx_buff[5]=0x00;
				 rx_buff[6]=0x00;
				 rx_buff[7]=0x00;
				
				 
				 rx_num=0x00;
				 rx_end_flag=0x00;
				 rx_star_flag=0x00;
				 
			 }
			 
			 break;
		 }
		
		 

		 default:
		  {
			 rx_buff[0]=0x00;
			 rx_buff[1]=0x00;
			 rx_buff[2]=0x00;
			 rx_buff[3]=0x00;
			 rx_buff[4]=0x00;
			 rx_buff[5]=0x00;
			 rx_buff[6]=0x00;
			 rx_buff[7]=0x00;
			
			 
			 rx_num=0x00;
			 rx_end_flag=0x00;
			 rx_star_flag=0x00;
			  
			  break;
			  
		  }
	 }
		
		
}















void uart3_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
//	

//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
//	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     /*ʹ��SWD ����JTAG*/ 
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PA.12 �˿�����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		//fukong����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5

//	
//	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//Ҫʹ��PA15��PB3��PA2��PA3�Ķ˿���ϣ�Ҫ���в�����ӳ��




	     //GPIO_PartialRemap_USART3
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART2��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC ,ENABLE);//GPIOAʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
	
	//USART3_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PD.5
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOD.5
   
  //USART3_RX	  GPIOB.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PD6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOD.6  
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//Ҫʹ�ý�����ӳ��
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//Ҫʹ��PA15��PB3��PA2��PA3�Ķ˿���ϣ�Ҫ���в�����ӳ��

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART3, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���1 

}


void clear_tx3_buff(void)
{
	rx3_buff[0]=0x00;
	rx3_buff[1]=0x00;
	rx3_buff[2]=0x00;
	rx3_buff[3]=0x00;
	rx3_buff[4]=0x00;
	rx3_buff[5]=0x00;
	rx3_buff[6]=0x00;
	rx3_buff[7]=0x00;
	rx3_buff[8]=0x00;
	rx3_buff[9]=0x00;
	rx3_buff[10]=0x00;
	rx3_buff[10]=0x00;
	rx3_buff[11]=0x00;
	rx3_buff[12]=0x00;
	rx3_buff[13]=0x00;
	rx3_buff[14]=0x00;
	rx3_buff[15]=0x00;
	rx3_buff[16]=0x00;
	rx3_buff[17]=0x00;
	rx3_buff[18]=0x00;
	rx3_buff[19]=0x00;
	rx3_buff[20]=0x00;
	
	rx3_buff[21]=0x00;
	rx3_buff[22]=0x00;
	rx3_buff[23]=0x00;
	rx3_buff[24]=0x00;
	rx3_buff[25]=0x00;
	rx3_buff[26]=0x00;
	rx3_buff[27]=0x00;
	rx3_buff[28]=0x00;
	rx3_buff[29]=0x00;
	rx3_buff[30]=0x00;

	rx3_num=0x00;
	rx3_end_flag=0x00;
	rx3_star_flag=0x00;
	
}


void USART3_IRQHandler(void)
{
				uint8_t res2;
				if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
				{                
						res2 =USART_ReceiveData(USART3);	//��ȡ���յ�������
						switch(rx3_num)
             {
                  case 0://freame star
                 {
                     if(0xaa==res2)
                     {
                         rx3_buff[0]=res2;
                         rx3_num=0x01;
                         rx3_end_flag=0x00;
                         rx3_star_flag=0x01;
                     }
                     else
                     {
                         clear_tx3_buff();
                     }
                     
                     
                     break;
                 } 
                 case 1://freame star
                 {
                     if(0x29==res2)
                     {
                         rx3_buff[1]=res2;
                         rx3_num=0x02;
                         rx3_end_flag=0x00;
                         rx3_star_flag=0x01;
                     }
                     else
                     {
                        clear_tx3_buff();
                     }
                     
                     break;
                 }
								 
							 case 2://freame star
                 {
                     if(0X05==res2)
                     {
                         rx3_buff[2]=res2;
                         rx3_num=0x03;
                         rx3_end_flag=0x00;
                         rx3_star_flag=0x01;
                     }
                     else
                     {
                         clear_tx3_buff();
                     }
                     
                     break;
                 }
                 case 3:///*�����֣�0X35ŷ���� 0X34λ�� 0X33�ٶ�*/
                 {
                    if(res2==0x33 || res2==0x34|| res2==0x35)
										{
											 rx3_buff[3]=res2;
											 rx3_num=0x04;
											 rx3_end_flag=0x00;
											 rx3_star_flag=0x01;
										}
										else
										{
											clear_tx3_buff();
										}	
										
										 break;

										
                 }
                 
                 case 4://///*0X06*/����������Ϊ6���ֽڣ�2���ֽ��ٶȣ�2���ֽ�λ�ã�2���ֽڽǶ�
                 {
                     
									 rx3_buff[4]=res2;
									 rx3_num=0x05;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 5://commamd 1x.h
                 {
                     
									 rx3_buff[5]=res2;
									 rx3_num=0x06;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 6://commamd 1x.l
                 {
                     
									 rx3_buff[6]=res2;
									 rx3_num=0x07;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 7://y.h
                 {
                     
									 rx3_buff[7]=res2;
									 rx3_num=0x08;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 8://commamd 1 y.hl
                 {
                     
									 rx3_buff[8]=res2;
									 rx3_num=0x09;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 9://z.h
                 {
                     
									 rx3_buff[9]=res2;
									 rx3_num=0x0a;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 10://commamd 1 z.l
                 {
                     
									 rx3_buff[10]=res2;
									 rx3_num=0x0b;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								  case 11://yaw.h
								 {
									 
													 rx3_buff[11]=res2;
													 rx3_num=0x0c;
													 rx3_end_flag=0x00;
													 rx3_star_flag=0x01;
								   break;                   
								 }
												 case 12://commamd 1 yaw.l
								 {
									 
													 rx3_buff[12]=res2;
													 rx3_num=0x0d;
													 rx3_end_flag=0x00;
													 rx3_star_flag=0x01;
								   break;                   
								 }
								
				 
								case 13:///*֡β*/yaw.h
											 {
									 if(0x00==res2)
									 {
										 rx3_buff[13]=res2;
										 rx3_num=0x00;
										 rx3_star_flag=0x00;
										 command_text3=rx3_buff[2];
										 rx3_end_flag=0x01;
										 
									 }
									 else
									 {
											clear_tx3_buff();
												 
												 
									 }
													 break;
											 }
							 default:
								{
								clear_tx3_buff();
									
									break;
									
								}
								
				} 
						 
			}
}








////////////////////





////////////////////
////////
////////////////////
////////
////////////////
void uart2_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
//	

//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
//	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     /*ʹ��SWD ����JTAG*/ 
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PA.12 �˿�����
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		//fukong����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5

//	
//	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//Ҫʹ��PA15��PB3��PA2��PA3�Ķ˿���ϣ�Ҫ���в�����ӳ��




	     //GPIO_PartialRemap_USART3
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO ,ENABLE);//GPIOAʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
	
	//USART2_TX   GPIOD.5
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PD.5
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD.5
   
  //USART2_RX	  GPIOD.6��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PD6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOD.6  
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//Ҫʹ�ý�����ӳ��
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//Ҫʹ��PA15��PB3��PA2��PA3�Ķ˿���ϣ�Ҫ���в�����ӳ��

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���1 

}


void clc_first_frame2(void)
{
	rx_buff2[0]=0x00;
	rx_buff2[1]=0x00;
	rx_buff2[2]=0x00;
	rx_buff2[3]=0x00;
	rx_buff2[4]=0x00;
	rx_buff2[5]=0x00;
	rx_buff2[6]=0x00;
	rx_buff2[7]=0x00;
	rx_buff2[8]=0x00;
	rx_buff2[9]=0x00;
	rx_buff2[10]=0x00;
	rx_buff2[10]=0x00;
	rx_buff2[11]=0x00;
	rx_buff2[12]=0x00;
	rx_buff2[13]=0x00;
	rx_buff2[14]=0x00;
	rx_buff2[15]=0x00;
	rx_buff2[16]=0x00;
	rx_buff2[17]=0x00;
	rx_buff2[18]=0x00;
	rx_buff2[19]=0x00;
	rx_buff2[20]=0x00;
	
	rx_buff2[21]=0x00;
	rx_buff2[22]=0x00;
	rx_buff2[23]=0x00;
	rx_buff2[24]=0x00;
	rx_buff2[25]=0x00;
	rx_buff2[26]=0x00;
	rx_buff2[27]=0x00;
	rx_buff2[28]=0x00;
	rx_buff2[29]=0x00;
	rx_buff2[30]=0x00;

	rx_num2=0x00;
	rx_end_flag2=0x00;
	rx_star_flag2=0x00;
	
}







void USART2_IRQHandler(void)                	//����1�жϷ������
	{
	u8 com_data;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			com_data =USART_ReceiveData(USART2);	//��ȡ���յ�������
			
			switch(rx_num2)
             {
                  case 0://freame star
                 {
                     if(0xaa==com_data)
                     {
                         rx_buff2[0]=com_data;
                         rx_num2=0x01;
                         rx_end_flag2=0x00;
                         rx_star_flag2=0x01;
                     }
                     else
                     {
                         clc_first_frame2();
                     }
                     
                     
                     break;
                 } 
                 case 1://freame star
                 {
                     if(0x29==com_data)
                     {
                         rx_buff2[1]=com_data;
                         rx_num2=0x02;
                         rx_end_flag2=0x00;
                         rx_star_flag2=0x01;
                     }
                     else
                     {
                        clc_first_frame2();
                     }
                     
                     break;
                 }
								 
					case 2://freame star
                 {
                     if(0X05==com_data)
                     {
                         rx_buff2[2]=com_data;
                         rx_num2=0x03;
                         rx_end_flag2=0x00;
                         rx_star_flag2=0x01;
                     }
                     else
                     {
                         clc_first_frame2();
                     }
                     
                     break;
                 }
                 case 3:///*�����֣�0X35ŷ���� 0X34λ�� 0X33�ٶ�*/
                 {
                    if(com_data==0x33 || com_data==0x34|| com_data==0x35)
										{
											 rx_buff2[3]=com_data;
											 rx_num2=0x04;
											 rx_end_flag2=0x00;
											 rx_star_flag2=0x01;
										}
										else
										{
											clc_first_frame2();
										}	
										
										 break;

										
                 }
                 
                 case 4://///*0X06*/����������Ϊ6���ֽڣ�2���ֽ��ٶȣ�2���ֽ�λ�ã�2���ֽڽǶ�
                 {
                     
									 rx_buff2[4]=com_data;
									 rx_num2=0x05;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 5://commamd 1x.h
                 {
                     
									 rx_buff2[5]=com_data;
									 rx_num2=0x06;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 6://commamd 1x.l
                 {
                     
									 rx_buff2[6]=com_data;
									 rx_num2=0x07;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 7://y.h
                 {
                     
									 rx_buff2[7]=com_data;
									 rx_num2=0x08;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 8://commamd 1 y.hl
                 {
                     
									 rx_buff2[8]=com_data;
									 rx_num2=0x09;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 9://z.h
                 {
                     
									 rx_buff2[9]=com_data;
									 rx_num2=0x0a;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 10://commamd 1 z.l
                 {
                     
									 rx_buff2[10]=com_data;
									 rx_num2=0x0b;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								  case 11://yaw.h
								 {
									 
													 rx_buff2[11]=com_data;
													 rx_num2=0x0c;
													 rx_end_flag2=0x00;
													 rx_star_flag2=0x01;
								   break;                   
								 }
												 case 12://commamd 1 yaw.l
								 {
									 
													 rx_buff2[12]=com_data;
													 rx_num2=0x0d;
													 rx_end_flag2=0x00;
													 rx_star_flag2=0x01;
								   break;                   
								 }
								
				 
								case 13:///*֡β*/yaw.h
											 {
									 if(0x00==com_data)
									 {
										 rx_buff2[13]=com_data;
										 rx_num2=0x00;
										 rx_star_flag2=0x00;
										 command_text3=rx_buff2[2];
										 rx_end_flag2=0x01;
										 
									 }
									 else
									 {
											clc_first_frame2();
												 
												 
									 }
													 break;
											 }
							 default:
								{
								clc_first_frame2();
									
									break;
									
								}
								
				} 
						 
			}

            

//			switch(rx_num2)
//			{
//			  case 0://freame star "$"
//			 {
//				 if(0x24==com_data)
//				 {
//					 rx_buff2[0]=com_data;
//					 rx_num2=0x01;
//					 rx_end_flag2=0x00;
//					 rx_star_flag2=0x01;
//				 }
//				 else
//				 {
//					clc_first_frame2();
//				 }
//				 
//				 
//				 break;
//			 } 
//			 case 1://"K"
//			 {
//				 
//				 rx_buff2[1]=com_data;
//				 rx_num2=0x02;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//					 
//				 
//				 
//				 break;
//			 }
//			 case 2:////"T"
//			 {
//				 rx_buff2[2]=com_data;
//				 rx_num2=0x03;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			 
//			 case 3://"0"
//			 {
//				 
//				 rx_buff2[3]=com_data;
//				 rx_num2=0x04;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 
//			 
//				 break;      
//							 
//			  }
//			  
//				case 4://x1
//			 {
//				 rx_buff2[4]=com_data;
//				 rx_num2=0x05;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			 
//			  case 5:////x2
//			 {
//				 rx_buff2[5]=com_data;
//				 rx_num2=0x06;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 6:////x3
//			 {
//				 rx_buff2[6]=com_data;
//				 rx_num2=0x07;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }



//			 case 7:///x4
//			 {
//				 rx_buff2[7]=com_data;
//				 rx_num2=0x08;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 8:///y1
//			 {
//				 rx_buff2[8]=com_data;
//				 rx_num2=0x09;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }


//			   case 9://y2
//			 {
//				 rx_buff2[9]=com_data;
//				 rx_num2=10;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 10:///y3
//			 {
//				 rx_buff2[10]=com_data;
//				 rx_num2=11;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 11:///y4
//			 {
//				 rx_buff2[11]=com_data;
//				 rx_num2=12;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 12:///z1
//			 {
//				 rx_buff2[12]=com_data;
//				 rx_num2=13;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 13:///z2
//			 {
//				 rx_buff2[13]=com_data;
//				 rx_num2=14;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 14:///z3
//			 {
//				 rx_buff2[14]=com_data;
//				 rx_num2=15;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 15:///z4
//			 {
//				 rx_buff2[15]=com_data;
//				 rx_num2=16;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 16:///check sum1
//			 {
//				 rx_buff2[16]=com_data;
//				 rx_num2=17;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 17:///check sum2
//			 {
//				 rx_buff2[17]=com_data;
//				 rx_num2=18;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 18:///check sum3
//			 {
//				 rx_buff2[18]=com_data;
//				 rx_num2=19;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 19:///check sum4
//			 {
//				 rx_buff2[19]=com_data;
//				 rx_num2=20;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			 
//			  
//				
//			 
//			 
//			 case 20:////֡β
//			 {
//				 if(com_data==0xA)
//				 {
//					  
//					  rx_buff2[20]=com_data;
//					 
////					 check_sum=0;
////					 for(tempa=0;tempa<9;tempa++)
////					 {
////						 check_sum=check_sum+rx_buff2[tempa];
////					 }
//					 
//						rx_num2=0x00;
//						rx_end_flag2=0x01;
//						rx_star_flag=0x01;
//						first_frame_end=1;
//					
//	//				 
//				 }

//				 else
//				 {
//					 clc_first_frame2();
//					 
//				 }
//				 
//				 break;
//			 }
//			
//			 

//			 default:
//			  {
//				 clc_first_frame2();
//				  
//				  break;
//				  
//			  }
//		 }

///////////
		
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
	

















  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  
  
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void clc_first_frame(void)
{
	rx_buff[0]=0x00;
	rx_buff[1]=0x00;
	rx_buff[2]=0x00;
	rx_buff[3]=0x00;
	rx_buff[4]=0x00;
	rx_buff[5]=0x00;
	rx_buff[6]=0x00;
	rx_buff[7]=0x00;
	rx_buff[8]=0x00;
	rx_buff[9]=0x00;
	rx_buff[10]=0x00;
	rx_buff[10]=0x00;
	rx_buff[11]=0x00;
	rx_buff[12]=0x00;
	rx_buff[13]=0x00;
	rx_buff[14]=0x00;
	rx_buff[15]=0x00;
	rx_buff[16]=0x00;
	rx_buff[17]=0x00;
	rx_buff[18]=0x00;
	rx_buff[19]=0x00;
	rx_buff[20]=0x00;
	
	rx_buff[21]=0x00;
	rx_buff[22]=0x00;
	rx_buff[23]=0x00;
	rx_buff[24]=0x00;
	rx_buff[25]=0x00;
	rx_buff[26]=0x00;
	rx_buff[27]=0x00;
	rx_buff[28]=0x00;
	rx_buff[29]=0x00;
	rx_buff[30]=0x00;

	rx_num=0x00;
	rx_end_flag=0x00;
	rx_star_flag=0x00;
	first_frame_end=0;
	second_frame_end=0x00;
}

void clc_second_frame(void)
{
	rx_buff[sec_basis+0]=0x00;
	rx_buff[sec_basis+1]=0x00;
	rx_buff[sec_basis+2]=0x00;
	rx_buff[sec_basis+3]=0x00;
	rx_buff[sec_basis+4]=0x00;
	rx_buff[sec_basis+5]=0x00;
	rx_buff[sec_basis+6]=0x00;
	rx_buff[sec_basis+7]=0x00;
	rx_buff[sec_basis+8]=0x00;
	rx_buff[sec_basis+9]=0x00;
	rx_buff[sec_basis+10]=0x00;

	rx_num=0x00;
	rx_star_flag=0x00;
	second_frame_end=0x00;
}




void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 com_data;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			com_data =USART_ReceiveData(USART1);	//��ȡ���յ�������
            

			switch(rx_num)
			{
			  case 0://freame star "$"
			 {
				 if(0x24==com_data)
				 {
					 rx_buff[0]=com_data;
					 rx_num=0x01;
					 rx_end_flag=0x00;
					 rx_star_flag=0x01;
				 }
				 else
				 {
					clc_first_frame();
				 }
				 
				 
				 break;
			 } 
			 case 1://"K"
			 {
				 
				 rx_buff[1]=com_data;
				 rx_num=0x02;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
					 
				 
				 
				 break;
			 }
			 case 2:////"T"
			 {
				 rx_buff[2]=com_data;
				 rx_num=0x03;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			 case 3://"0"
			 {
				 
				 rx_buff[3]=com_data;
				 rx_num=0x04;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 
			 
				 break;      
							 
			  }
			  
				case 4://x1
			 {
				 rx_buff[4]=com_data;
				 rx_num=0x05;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			  case 5:////x2
			 {
				 rx_buff[5]=com_data;
				 rx_num=0x06;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 6:////x3
			 {
				 rx_buff[6]=com_data;
				 rx_num=0x07;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }



			 case 7:///x4
			 {
				 rx_buff[7]=com_data;
				 rx_num=0x08;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 8:///y1
			 {
				 rx_buff[8]=com_data;
				 rx_num=0x09;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }


			   case 9://y2
			 {
				 rx_buff[9]=com_data;
				 rx_num=10;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 10:///y3
			 {
				 rx_buff[10]=com_data;
				 rx_num=11;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 11:///y4
			 {
				 rx_buff[11]=com_data;
				 rx_num=12;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 12:///z1
			 {
				 rx_buff[12]=com_data;
				 rx_num=13;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 13:///z2
			 {
				 rx_buff[13]=com_data;
				 rx_num=14;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 14:///z3
			 {
				 rx_buff[14]=com_data;
				 rx_num=15;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 15:///z4
			 {
				 rx_buff[15]=com_data;
				 rx_num=16;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 16:///check sum1
			 {
				 rx_buff[16]=com_data;
				 rx_num=17;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 17:///check sum2
			 {
				 rx_buff[17]=com_data;
				 rx_num=18;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 18:///check sum3
			 {
				 rx_buff[18]=com_data;
				 rx_num=19;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 19:///check sum4
			 {
				 rx_buff[19]=com_data;
				 rx_num=20;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			  
				
			 
			 
			 case 20:////֡β
			 {
				 if(com_data==0xA)
				 {
					  
					  rx_buff[20]=com_data;
					 
//					 check_sum=0;
//					 for(tempa=0;tempa<9;tempa++)
//					 {
//						 check_sum=check_sum+rx_buff[tempa];
//					 }
					 
						rx_num=0x00;
						rx_end_flag=0x01;
						rx_star_flag=0x01;
						first_frame_end=1;
					
	//				 
				 }

				 else
				 {
					 clc_first_frame();
					 
				 }
				 
				 break;
			 }
			
			 

			 default:
			  {
				 clc_first_frame();
				  
				  break;
				  
			  }
		 }

/////////
		
		
		
		
		
		
		
		} 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
	





#endif	

