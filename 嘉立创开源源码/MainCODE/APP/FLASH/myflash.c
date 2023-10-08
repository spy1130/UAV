#include "myflash.h"
#include "usart.h"


/*
	д���ݲ��裺
		1������
		2������������������ȫ��������
		3��д����
		4������
*/
void myflash_STD_test(void)
{
	uint32_t *p;
	
	//����1������
	FLASH_Unlock();
	
	//����2������
	//������5ҳ
	FLASH_ErasePage(0x08000000+2048*1);
	
	FLASH_ProgramWord(0x08000000+2048*1,0x01234567);
	
	FLASH_Lock();
	
	printf("\r\n�Ѿ����ڲ�FLASHд�����");
	
	p = (uint32_t *)(0x08000000+2048*1);
	
	printf("\r\n��ȡ�ڲ�FLASH�õ�ַ�洢������Ϊ��0x%x",*p);
}

void myflash_REG_test(void)
{
	
}




