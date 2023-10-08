#ifndef __myiap_H
#define __myiap_H
#include "stm32f10x.h"

typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.

#define FLASH_APP1_ADDR		0x08010000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
											//����0X08000000~0X0800FFFF�Ŀռ�ΪIAPʹ��

void iap_load_app(uint32_t appxaddr);			//ִ��flash�����app����
void iap_load_appsram(uint32_t appxaddr);		//ִ��sram�����app����
void iap_download_appbin(uint32_t appxaddr,uint8_t *appbuf,uint32_t applen);	//��ָ����ַ��ʼ,д��bin
#endif



