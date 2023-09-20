1.设置光标的位置
typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD;
COORD coord;
coor.X = 20;
coor.Y = 10;
设置:
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

//隐藏控制台光标
	CONSOLE_CURSOR_INFO  cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	
	
//判断是否按下按键
#include <conio.h>
   char  key;
	while (_kbhit()) //判断是否按下按键,按下不等于0 
	{
		key = _getch();
	}
	
	
	
	
	
	