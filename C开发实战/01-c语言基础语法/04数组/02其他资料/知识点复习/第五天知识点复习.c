字符的输入
	char a;
	printf("请输入a：");
	//scanf("%c",  &a);
	a = getchar();//从键盘读取字符，放在a变量中
	printf("a = %c\n", a);
	
	//读取换行符，吃掉，不做处理
	//scanf("%c",  &a);
	getchar();

	char b;
	printf("请输入b：");
	//scanf("%c",  &b);
	b = getchar();
	printf("b = %c\n", b);
	
类型转换
1、隐式转换
	double a;
	int b = 1;
	//编译器自动转换，把b转换为double类型后，再给a赋值（隐式转换）
	a = b; 
	printf("%lf\n", b);
	
2、强制类型转换：  (类型)变量名
	int a = 10;
	//a只有在此语句执行时，才强制转换为double类型，其它地址还是为int类型
	printf("%lf\n", (double)a); 
	
	转换原则：占用内存字节数少(值域小)的类型，向占用内存字节数多(值域大)的类型转换，以保证精度不降低。

3、浮点型和整型打印问题
a)不要直接通过%d，打印一个浮点型变量，得不到想要的结果，要想得到结果，强制类型转换
	double a = 11.11;
	printf("%d\n", (int)a);

b)不要直接通过%f或%lf，打印一个整型变量，得不到想要的结果，要想得到结果，强制类型转换
	int a = 10;
	printf("%lf\n", (double)a);
	
运算符和表达式
1、相除得到小数问题
	a)两个整数相除，只是取整数，不会带小数
		int a = 1/2; //a = 0
	b)要想得到小数的结果，分子分母至少有一个是小数
		double a
		a = 1.0/2; //a = 0.5
		a = 1/(double)2;
		
2、前置++、后置++区别
	int b, c;
	b = 1;
	c = 0;
	c = b++; //后置++，先用后加
	printf("c = %d, b = %d\n", c, b); //c = 1, b = 2
	
	b = 1;
	c = 0;
	c = ++b;//前置++，先加后用
	printf("c1 = %d, b1 = %d\n", c, b);//c = 2, b = 2

	区别下面的情况：
	int b = 1;
	++b; //必须执行完此语句，才往后执行，所以b已经加1了，这里前置、后置都没区别
	int c = b;
	printf("c = %d\n", b);

3、条件真假问题
	a)0就是假
	b)非0就是真，通常以1表示
	
4、逻辑与、或的短路规则
	&&，左边为假，右边不执行
	||，左边为真，右边不执行
	
5、运算符优先级
	int c = 0;
	//&&优先级比 = 高
	//1、0 && c 结果为假，0
	//2、0 = 1(常量不能修改)
	0 && c = 1; //err
	
程序流程结构
C语言支持最基本的三种程序运行结构：顺序结构、选择结构、循环结构。

1、选择结构
1) if语句
	a) if
	//if是选择语句的关键字
	//()为条件，如果条件为真，执行{}，()后面是没有分号的
	//if语句下面最好写{}
	//if(-1) //条件为真
	if(0) //条件为假
	{
		printf("test\n");
	} //大括号后面没有分号
	
	//if后面没有写{}，只有第一个语句是属于if的
	if(0) //条件为假，不执行if语句
		printf("test1\n");
		printf("test2\n");
	
	//条件为假	
	if(0); //后面无条件执行
	{
		printf("22222222222222\n");
	}
	
	int a = 1;
	//条件为赋值语句，先赋值，然后判断a是0，还是非0，结果为非0，条件为真
	//建议if(3 == a)，常量放左边
	if( a = 3) 
	{
		printf("22222222222222\n");
	}
	
	b) if else
	int a = 1;
	int b = 2;
	if(a < b)
	{
		printf("最大值为: %d\n", b);
	}
	else //else后面不要接条件，else不是必须
	{
		printf("最大值为: %d\n", a);
	}
	
	c) if~else if~else
	int a = 10;
	
	if(a == 10)
	{
		printf("a == 10\n");
	}
	else if(a > 10)
	{
		printf("a > 10\n");
	}
	else if(a < 10)
	{
		printf("a < 10\n");
	}
	else
	{
		printf("这是不可能的\n");
	}

2) 三目运算符?:
	//三目运算符?:  ，就是简洁版的if else
	int a = 10;
	int b = 20;
	int c = 0;
	//1、判断a > b结果
	//2、如果为真，执行？后面
	//3、如果为假，执行：后面
	c = a > b ? a : b;
	printf("最大值为：%d\n", c);

3) switch语句
	int a;
	printf("请输入楼层：");
	scanf("%d", &a);
	
	switch(a) //后面没有分号，条件只能是整型或字符型
	{
	case 1:
		printf("按下的是1楼\n");
		break; //break的作用，跳出switch语句，最好加上
		
	case 2:
		printf("按下的是2楼\n");
		break;
		
	case 3:
		printf("按下的是3楼\n");
		break;
		
	default:
		printf("其它\n");
		break;
	}
	
2、循环结构
1) while语句
	int i = 0;
	int sum = 0;
	
	//1、判断i <= 100是否成立，如果为真，执行{}语句，如果为假，跳出循环
	//2、{}语句执行完一次后，再重复1的操作
	while(i <= 100)//没有分号
	{
		sum += i;
		i++;
	}//没有分号
	printf("sum = %d\n", sum);
	
2) do while语句
	int i = 0;
	int sum = 0;
	
	//while() 先判断再执行
	//do while(), 第一次无条件执行，以后和while()一样
	do
	{
		sum +=i;
		i++;
	}while(i <= 100); //有分号
	printf("sum = %d\n", sum);

3) for语句
	int i = 0;
	int sum = 0;
	//for()内部必须有2个分号";"
	//1、i = 0
	//2、判断 i <= 100
	//	如果条件为真，执行{}语句，如果条件为假，跳出for循环
	//3、执行完{}内容，再执行i++
	//4、重复2、3步骤
	for(i = 0; i <= 100; ++i) //后面没有分号
	{
		sum +=i;
	}
	printf("sum = %d\n", sum);

4) 死循环
	a)
	while(1)
	{
		
	}
	
	b)
	do
	{

	}while(1);
	
	c)
	for(;;)
	{
		
	}

5) 循环嵌套
任意循环都可以相互嵌套：
	while()
	{
		do
		{
			for()
			{
				
			}
			
		}while();
	}

6)跳转语句
break:
	a)跳出当前的switch语句
	b)跳出当前的循环语句，跳出整个循环

continue: 只能用于循环语句，跳出本次循环，下一次继续执行

goto: 不是循环语句的专属，无条件跳转，不建议使用

字符编码
Windows默认支持的中文编码为：GBK, ANSI, GB2312
Linux默认支持的中文编码为：UTF-8


