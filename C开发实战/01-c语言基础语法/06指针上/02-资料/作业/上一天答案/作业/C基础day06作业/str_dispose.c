#include "type_define.h"

int str_add( u8 *str_0 );

/*********************************
 * 函数名: Strlen_output
 * 功能: 字符串长度输出
 * 接口: *data
 * 返回: u16
**********************************/
u16 Strlen_output( u8 *data )
    {
        u16 len = 0;
        while(*data != '\0')
            {
                data++;
                len++;
            }
        return len;
    }

/*********************************
 * 函数名: strcmp_analyze
 * 功能: 判断字符串是否相等
 * 接口: *str_0,*str_1
 * 返回: int
**********************************/
int strcmp_analyze( u8 *str_0, u8 *str_1 )
    {
        #define Erro_greater (1)
        #define Correct  (0)
        #define Erro_less (-1)
        int str_a=0, str_b=0;
        /* 将字符串的每个字符相加为整数 */
            str_a = str_add( str_0 );
            str_b = str_add( str_1 );

        /* 判断相加后的整数 */
            if( str_a == str_b ) return Correct;
            else if( str_a < str_b ) return Erro_less;
            else if( str_a > str_b ) return Erro_greater;
    }

/*********************************
 * 函数名: str_add
 * 功能: 字符串-每个字符相加后的整数
 * 接口: *str_0
 * 返回: int
**********************************/
int str_add( u8 *str_0 )
    {
        int str_a=0;
            while(*str_0 != '\0') 
                {
                    str_a += (int)*str_0;
                    str_0++;
                }   
        return str_a;   
    }