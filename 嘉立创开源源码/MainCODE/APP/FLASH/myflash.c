#include "myflash.h"
#include "usart.h"


/*
	写数据步骤：
		1，解锁
		2，擦除（扇区擦除与全部擦除）
		3，写数据
		4，上锁
*/
void myflash_STD_test(void)
{
	uint32_t *p;
	
	//步骤1，解锁
	FLASH_Unlock();
	
	//步骤2，擦除
	//擦除第5页
	FLASH_ErasePage(0x08000000+2048*1);
	
	FLASH_ProgramWord(0x08000000+2048*1,0x01234567);
	
	FLASH_Lock();
	
	printf("\r\n已经向内部FLASH写入完成");
	
	p = (uint32_t *)(0x08000000+2048*1);
	
	printf("\r\n读取内部FLASH该地址存储的内容为：0x%x",*p);
}

void myflash_REG_test(void)
{
	
}




