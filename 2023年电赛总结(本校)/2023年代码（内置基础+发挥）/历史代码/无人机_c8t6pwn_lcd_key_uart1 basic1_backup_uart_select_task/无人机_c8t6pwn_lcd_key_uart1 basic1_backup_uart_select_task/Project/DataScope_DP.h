

#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H
 
 
extern unsigned char DataScope_OutPut_Buffer[42];	   //待发送帧数据缓存区
extern unsigned char DataScope_OutPut_Buffer2[50];	   //待发送帧数据缓存区

void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // 写通道数据至 待发送帧数据缓存区
void DataScope_Get_Channel_Data2(float Data,unsigned char Channel);    // 写通道数据至 待发送帧数据缓存区
void DataScope_Get_Channel_Data3(float Data,unsigned char Channel);   // 发送帧数据生成函数 
 
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // 发送帧数据生成函数 
unsigned char DataScope_Data_Generate2(unsigned char Channel_Number);  // 发送帧数据生成函数 
unsigned char DataScope_Data_Generate3(unsigned char Channel_Number);  // 发送帧数据生成函数 




#endif 



