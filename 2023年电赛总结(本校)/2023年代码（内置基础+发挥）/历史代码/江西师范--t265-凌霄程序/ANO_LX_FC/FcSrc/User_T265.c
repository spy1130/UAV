/*==========================================================================
 * ����    ��T265���ݴ���
 * ����ʱ�䣺2023��3��23��
 * ����		 ��	LHB
===========================================================================*/


#include "Drv_Uart.h"
#include "uart.h"
#include "hw_ints.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "Ano_DT_LX.h"
#include "Drv_UbloxGPS.h"
#include "Drv_AnoOf.h"
#include "User_T265.h"

/*T265�ṹ�壬Ϊȫ�ֱ���*/
T265_Data t265={0};
/*�������ݻ���*/
uint8_t t265_buf[20];
/*�����������ݻ���*/
uint8_t t265_send[30];

/**************************************************************************
�������ܣ�T265���ݽ���
��ڲ���������BIT
����  ֵ����
��    �ߣ�LHB
**************************************************************************/
void t265_data_get(uint8_t data)
{
    
    static uint8_t rec_sta = 0;

	t265_buf[rec_sta] = data;
    
	if(rec_sta==0)
	{
		if(data==0Xaa)/*֡ͷ0Xaa*/
		{
			rec_sta++;
		}
		else
		{
			rec_sta=0;
		}
	}
	else if(rec_sta==1)
	{
		if(data==0X29)/*֡ͷ0X29*/
		{
			rec_sta++;
		}	
		else
		{
			rec_sta=0;
		}		
	}
	else if(rec_sta==2)/*ƫ����������־λ*/
	{
		if(data==0X05)/*֡ͷ0X05*/
		{
			rec_sta++;
		}
		else
		{
			rec_sta=0;
		}		
	}
	else if(rec_sta==3)
	{
		/*�����֣�0X35ŷ���� 0X34λ�� 0X33�ٶ�*/
		if(data==0x33 || data==0x34|| data==0x35)
		{
			rec_sta++;
		}
		else
		{
			rec_sta=0;
		}	
	}
	else if(rec_sta==4)/*0X06*/
	{
			rec_sta++;
	}
    else if(rec_sta==5)
	{
			rec_sta++;		
	}
	else if(rec_sta==6)
	{
			rec_sta++;		
	}
	else if(rec_sta==7)
	{
			rec_sta++;		
	}
	else if(rec_sta==8)
	{
			rec_sta++;		
	}
	else if(rec_sta==9)
	{
			rec_sta++;		
	}
	else if(rec_sta==10)
	{
			rec_sta++;		
	}
	else if(rec_sta==11)/*֡β*/
	{
        if( data == 0X00 )/*��ȷ��λ�ý��յ�֡β����ʼ����*/
        {           
						t265_data_analysis();
            rec_sta=0;
        }
				else
				{
					rec_sta=0;
				}		
	}
	else
	{
		rec_sta=0;
	}
}

/**************************************************************************
�������ܣ�T265���ݽ���
��ڲ�����
����  ֵ��
��    �ߣ�LHB
**************************************************************************/
void t265_data_analysis(void)
{		

//    int16_t sum=0;	
				/*���������������ϵ*/
    if(t265_buf[3]==0x35)/*����ŷ����*/
    {
			
      t265.pitch=(int16_t)((t265_buf[5]<<8)|t265_buf[6]);
			t265.roll= (int16_t)((t265_buf[7]<<8)|t265_buf[8]);
			t265.yaw=  (int16_t)((t265_buf[9]<<8)|t265_buf[10]);

			t265.pi_f=(int16_t)(t265.pitch);
			
			t265.ro_f=(int16_t)(t265.roll);
			
			t265.ya_f=(int16_t)(t265.yaw);

			
    }else if(t265_buf[3]==0x34)/*����λ��*/
    {
			
			t265.pos_x=(int16_t)((t265_buf[5]<<8)|t265_buf[6]);
			
			t265.pos_y=(int16_t)((t265_buf[7]<<8)|t265_buf[8]);
			
			t265.pos_z=(int16_t)((t265_buf[9]<<8)|t265_buf[10]);
			

			t265.pos_y_f=-(int16_t)(1*(float)t265.pos_x);
			t265.pos_z_f=(int16_t)(1*(float)t265.pos_y);
			t265.pos_x_f=-(int16_t)(1*(float)t265.pos_z);

    }else if(t265_buf[3]==0x33)/*�����ٶ�*/
    {
			t265.v_x=(int16_t)((t265_buf[5]<<8)|t265_buf[6]);
			t265.v_y=(int16_t)((t265_buf[7]<<8)|t265_buf[8]);
			t265.v_z=(int16_t)((t265_buf[9]<<8)|t265_buf[10]);

			t265.v_x_f=(int16_t)(1.5*(t265.v_x));
				
			t265.v_y_f=(int16_t)(1.5*(t265.v_y));
			t265.v_z_f=(int16_t)(1.5*(t265.v_z));
    }

}




