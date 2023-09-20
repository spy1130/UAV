#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "type_define.h"
#include "str_dispose.h"

#define alg_s (4)

u8 *ALG[alg_s] = {"add", "sub", "mux", "dive"};


BOOL Order_judge( u8 *data );

int Order_transition( u8 *data );

u32 Order_count( int way, u32 data_0, u32 data_1 );

/*********************************
 * ������: Counter_run
 * ����: ����������
 * �ӿ�: ��
 * ����: ��
**********************************/
void Counter_run( void )
    {
        u8 name[] = ""; //������
        u32 data_0,data_1; //����������
        printf("�����㷨�����ʽΪ(add 15 25):\n");
        
        do
        {
            
            scanf("%s %d %d", name, &data_0, &data_1);
            //printf("name = %s, data_0 = %d, data_1 = %d\n", name,data_0,data_1);

                if( Order_judge( name ) == False )
                    {
                        printf("�����������,��������!\n");
                    }
        }
        while( Order_judge( name ) == False);

        printf("%d %s %d = %d\n", data_0, name, data_1,
            Order_count( Order_transition( name ), data_0, data_1 ));

    }


/*********************************
 * ������: Order_judge
 * ����: �������㷨�����ж�
 * �ӿ�: *data
 * ����: BOOL
**********************************/
BOOL Order_judge( u8 *data )
    {
        #define Correct (0)
        BOOL bit = False;
        for( int x = 0; x < alg_s; x++)
            {
                if( strcmp_analyze( data, ALG[x]) == Correct )bit = True;
            }
        return bit;
    }

/*********************************
 * ������: Order_transition
 * ����: ����������ת����
 * �ӿ�: *data
 * ����: int
**********************************/
int Order_transition( u8 *data )
    {
        #define Correct (0)
        int bit = 0;
        for( int x = 0; x < alg_s; x++ )
            {
                if( strcmp_analyze( data, ALG[x]) == Correct ) 
                    {
                        bit = x;
                        break;
                    }
            }
        return bit;
    }

/*********************************
 * ������: Order_count
 * ����: ����
 * �ӿ�: way,data_0,data_1
 * ����: u32
**********************************/
u32 Order_count( int way, u32 data_0, u32 data_1 )
    {
        switch( way )
            {
                case 0:
                    {
                        return (data_0+data_1);
                    }
                case 1:
                    {
                        return (data_0-data_1);
                    }
                case 2:
                    {
                        return (data_0*data_1);
                    }
                case 3:
                    {
                        return (data_0/data_1);
                    }
            }
    }


int main( void )
    {
        printf("****************************************\n");
            Counter_run( );
            //printf("Strlen_output( u8 *data ) = %d", strcmp_analyze( "add", ALG[0]));
        printf("****************************************\n");
        system("pause");
        return 0;
    }