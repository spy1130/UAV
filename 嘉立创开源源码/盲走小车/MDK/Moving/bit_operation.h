#ifndef __bit_operation_H
#define __bit_operation_H	
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr  0x4001080C
#define GPIOB_ODR_Addr  0x40010C0C
#define GPIOC_ODR_Addr  0x4001100C

#define GPIOA_IDR_Addr  0x40010808 
#define GPIOB_IDR_Addr  0x40010C08
#define GPIOC_IDR_Addr  0x40011008

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
//void WFI_SET(void)
//{
//	__ASM volatile("wfi");		  
//}
////关闭所有中断
//void INTX_DISABLE(void)
//{		  
//	__ASM volatile("cpsid i");
//}
////开启所有中断
//void INTX_ENABLE(void)
//{
//	__ASM volatile("cpsie i");		  
//}
////设置栈顶地址
////addr:栈顶地址
//__asm void MSR_MSP(u32 addr) 
//{
//    MSR MSP, r0		//set Main Stack value
//    BX r14
//}

#endif

