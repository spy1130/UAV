1、结构体基本操作
1)结构体类型定义
	//struct为关键字，Stu为自定义标示符
	//struct Stu才是结构体类型
	//结构体成员不能在定义类型时赋值
	struct Stu
	{
		int age;
		char name[50];
		int scroe;
	}; //后面有分号

2)结构体变量的定义和初始化
	//结构体变量初始化和数组很类似，只有在定义时，才能初始化
	//定义结构体变量时，别忘了struct关键字
	struct Stu obj = {18, "mike", 59};

3)结构体成员变量的使用
a)如果是普通变量，点运算符
	obj.age = 18;

b)如果是指针变量，->
	(&obj)->age = 28;

2、结构体指针变量
1)指针变量指向栈区
	struct Stu *p = NULL;
	struct Stu obj; //栈区结构体
	p = &obj;		//指向栈区
	p->age = 18;
	(*p).age = 18;
	
2)指针变量指向堆区
	struct Stu *p = NULL;
	
	//指向堆区
	p = (struct Stu *)malloc(sizeof(struct Stu));
	p->age = 18;
	
	free(p);
	p = NULL;

3)const修饰的指针变量
	//看const修饰是*，还是变量
	//如果是*，说明结构体成员不允许修改
	//如果是变量，说明结构体指针变量不允许修改
	
	//a)
	const struct Stu *p;
	struct Stu const*p;
	p = NULL; //ok
	//p->age = 18; //err
	
	//b)
	struct Stu * const p;
	//p = NULL; //err
	p->age = 18; //ok
	
	//c)
	const struct Stu * const p;
	//p = NULL; //err
	//p->age = 18;//err

3、结构体数组
	struct Stu obj[3] = { 
		{18, "lily", 99}, 
		{22, "lucy", -80}, 
		{33, "mike", 59} 
	};
	
	struct Stu obj2[3] = { 18, "lily", 99, 22, "lucy", -80, 33, "mike", 59 };
	
	struct Stu tmp[3];
	int i = 0;
	
	for(i = 0; i < 3; i++)
	{
		(tmp+i)->age = 18+i;
		( *(tmp+i) ).age = 18+i;
		tmp[i].age = 18+i; //常用
	}

4、结构体和函数
1)同类型结构体变量赋值
	struct Stu obj1 = {18, "lily", 99};
	struct Stu obj2;
	obj2 = obj1;
	
2)函数值传递
	a)
	struct Stu p;
	//结构体变量本身传递(值传递)，形参修改不会影响到实参
	//调用完毕fun()函数，p的成员还是没有赋值
	fun(p); 
	void fun(struct Stu p)
	{
		p.age = 18;
		strcpy(p.name, "mike");
		p.score = 59;
	}
	
	b)
	struct Stu s = {18, "mike", 59};
	fun(s); //值传递
	void fun(struct Stu s) //传参时，把实参s成员的内容给形参s赋值
	{	//虽然能打印内容，但是打印内容为fun形参s成员变量的内容
		printf("%d, %s, %d\n", s.age, s.name, s.score);
	}
	
3)函数地址传递
	struct Stu p;
	fun(&p); //地址传递，形参修改可以间接影响到实参
	void fun(struct Stu *p)
	{
		p->age = 18;
		strcpy(p->name, "mike");
		p->score = 59;
	}

5、结构体套一级指针
	struct Stu
	{
		int age;
		char *name; //一级指针
		int score;
	}; //后面有分号
	
1)栈区结构体
	struct Stu s;
	s.age = 10;
	
	s.name = (char *)malloc( strlen("mike") + 1);
	strcpy(s.name, "mike");
	s.score = 59;
	
	free(s.name);

2)堆区结构体
	struct Stu *p;
	p = (struct Stu *)malloc(sizeof(struct Stu));
	p->name = (char *)malloc( strlen("mike") + 1);
	p->age = 18;
	strcpy(p->name, "mike");
	p->score = 59;
	
	free(p->name);
	free(p);

6、共用体（联合体）
	//只需要把结构体的struct改为union
	union Test
	{
		unsigned char a;
		unsigned short b;
		unsigned int c;
	};

	//union Test类型名
	//tmp是变量名
	union Test tmp;

	//1、共用体，所有成员共用一段内存空间
	//2、所有成员的首地址是一样的
	printf("%p, %p, %p\n", &tmp.a, &tmp.b, &tmp.c);
	
	//3、共用体的大小为最大成员的大小
	printf("sizeof(union Test) = %lu\n", sizeof(union Test) );

	//4、改变一个成员，会影响到另外的成员
	//左边是高位，右边是低位
	//高位放高地址，低位放低地址（小端）
	tmp.c = 0xaabbccdd;
	printf("c1 = %x\n", tmp.c); //aabbccdd
	printf("a = %x\n", tmp.a); //dd
	printf("b = %x\n", tmp.b); //ccdd
	
	tmp.a = 0x11;
	printf("c2 = %x\n", tmp.c); //aabbcc11
	
	tmp.b = 0x1234;
	printf("c3 = %x\n", tmp.c); //aabb1234
	
7、枚举
	//定义枚举类型 enum{};
	//enum Color叫枚举类型
	enum Color
	{
		//枚举成员，枚举常量
		//a)如果成员不赋值，第0个成员值为0，后一个成员比前一个大1
		red, blue, green, black, white
	};
	
	//1、可以直接把枚举常量赋值给整型变量
	int flag = red;
	
	//2、定义一个枚举变量，再用枚举常量赋值
	enum Color tmp = red;
	
	//3、可以直接用一个常量给枚举变量赋值，但是不推荐
	//tmp = 100;
	
	printf("%d\n", tmp);

8、typedef的使用
	//typedef的作用就是给一个以存在的类型起一个别名
	//typedef不能创造新类型
	typedef int int64; 
	int64 a; //int a

	//把struct Student类型，起一个别名叫Stu
	typedef struct Student
	{
		//结构体成员
		char name[50];
		int age;
		int score;
	}Stu; //有个分号

	//把struct Student类型，起一个别名叫S
	typedef struct Student S;

	struct Student obj; //定义变量必须加struct关键字
	Stu obj2;
	S tmp;
	
	
