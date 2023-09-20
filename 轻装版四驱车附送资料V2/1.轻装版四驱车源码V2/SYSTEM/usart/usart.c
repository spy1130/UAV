#include "usart.h"	  
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      

	while((USART2->SR&0X40)==0);
	USART2->DR = (u8) ch;      
  return ch;
}
#endif 
int Usart_Receive;

//////////////////////////////////////////////////////////////////
/**************************ʵ�ֺ���**********************************************
*��    ��:		usart1����һ���ֽ�
*********************************************************************************/
void usart2_send(u8 data)
{
	USART2->DR = data;
	while((USART2->SR&0x40)==0);	
}
void uart2_init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USARTʱ��
	//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.2
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.3  
   //USART ��ʼ������

	  //UsartNVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2 
}
/**************************************************************************
�������ܣ�����2�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void)
{	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
	{	       
		static u8 Flag_PID,i,j,Receive[50];
			static float Data;
  	  Usart_Receive=USART2->DR; 
			if(Usart_Receive>=0x41&&Usart_Receive<=0x48)  
			Flag_Direction=Usart_Receive-0x40;
			else 	  
			Flag_Direction=0;	
		//��������APP���Խ���ͨѶ
		if(Usart_Receive==0x7B) Flag_PID=1;   //APP����ָ����ʼλ
		if(Usart_Receive==0x7D) Flag_PID=2;   //APP����ָ��ֹͣλ

		 if(Flag_PID==1)  //�ɼ�����
		 {
			Receive[i]=Usart_Receive;
			i++;
		 }
		 if(Flag_PID==2)  //��������
		 {
			     if(Receive[3]==0x50) 	 PID_Send=1;
					 else  if(Receive[1]!=0x23) 
					 {								
						for(j=i;j>=4;j--)
						{
						  Data+=(Receive[j-1]-48)*pow(10,i-j);
						}
						switch(Receive[1])
						 {
							 case 0x30:  RC_Velocity=Data;break;
							 case 0x31:  Velocity_KP=Data;break;
							 case 0x32:  Velocity_KI=Data;break;
							 case 0x33:  break; //Ԥ��
							 case 0x34:  break; //Ԥ��
							 case 0x35:  break; //Ԥ��
							 case 0x36:  break; //Ԥ��
							 case 0x37:  break; //Ԥ��
							 case 0x38:  break; //Ԥ��
						 }
					 }				 
					 Flag_PID=0;//��ر�־λ����
					 i=0;
					 j=0;
					 Data=0;
					 memset(Receive, 0, sizeof(u8)*50);//��������
		 } 	 
   }
}



/**************************************************************************
�������ܣ�����ɨ��
**************************************************************************/
u8 click_RC (void)
{
			static u8 flag_key=1;//�������ɿ���־
	    u8 temp;
			if(flag_key&&Usart_Receive!=0x5A)
			{
			flag_key=0;
		  if(Usart_Receive>=0x01&&Usart_Receive<=0x08)temp=Usart_Receive;
		  else	if(Usart_Receive>=0x41&&Usart_Receive<=0x48)temp=Usart_Receive-0x40;	
		//	else 	temp=0;
			return temp;	// ��������
			}
			else if(Usart_Receive==0x5A)			flag_key=1;
			return 0;//�ް�������
}


/**************************************************************************
�������ܣ�ͨ�����ڰ�����Ĵ��������ͳ�ȥ
**************************************************************************/
void USART_TX(void)
{
        u8 Direction_A,Direction_B,Direction_C,Direction_D;//���ʹ������ݵ��ⲿ
	      u16 Temp_GZ;
	           if(Encoder_A>0) Direction_A=0;
        else if(Encoder_A<0) Direction_A=2;
	      else                 Direction_A=1;
		         if(Encoder_B>0) Direction_B=0;
        else if(Encoder_B<0) Direction_B=2;
	      else                 Direction_B=1;     
		         if(Encoder_C>0) Direction_C=0;
        else if(Encoder_C<0) Direction_C=2;
	      else                 Direction_C=1;
      	Temp_GZ=Gryo_Z+32768;//���ٶ����ݴ���
				
				usart3_send(0xff); //֡ͷ
				usart3_send(0xfe); //֡ͷ
				usart3_send(abs(Encoder_A));//A����ٶ�
				usart3_send(Direction_A);	//A�������
				usart3_send(abs(Encoder_B));	//B����ٶ�	
				usart3_send(Direction_B);	//B�������
				usart3_send(abs(Encoder_C));	//C����ٶ�	
				usart3_send(Direction_C);	//C�������
				usart3_send(abs(Encoder_D));	//C����ٶ�	
				usart3_send(Direction_D);	//C�������
				usart3_send(Temp_GZ>>8);	//���������ݸ�8λ	
				usart3_send(Temp_GZ&0x00ff);	//���������ݵ�8λ
}
