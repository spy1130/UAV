

#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
 
 
extern unsigned char DataScope_OutPut_Buffer[42];	   //������֡���ݻ�����
extern unsigned char DataScope_OutPut_Buffer2[50];	   //������֡���ݻ�����

void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // дͨ�������� ������֡���ݻ�����
void DataScope_Get_Channel_Data2(float Data,unsigned char Channel);    // дͨ�������� ������֡���ݻ�����
void DataScope_Get_Channel_Data3(float Data,unsigned char Channel);   // ����֡�������ɺ��� 
 
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // ����֡�������ɺ��� 
unsigned char DataScope_Data_Generate2(unsigned char Channel_Number);  // ����֡�������ɺ��� 
unsigned char DataScope_Data_Generate3(unsigned char Channel_Number);  // ����֡�������ɺ��� 




#endif 



