#ifndef __myiap_H
#define __myiap_H
#include "stm32f10x.h"

typedef  void (*iapfun)(void);				//定义一个函数类型的参数.

#define FLASH_APP1_ADDR		0x08010000  	//第一个应用程序起始地址(存放在FLASH)
											//保留0X08000000~0X0800FFFF的空间为IAP使用

void iap_load_app(uint32_t appxaddr);			//执行flash里面的app程序
void iap_load_appsram(uint32_t appxaddr);		//执行sram里面的app程序
void iap_download_appbin(uint32_t appxaddr,uint8_t *appbuf,uint32_t applen);	//在指定地址开始,写入bin
#endif



