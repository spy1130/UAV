1���ṹ���������
1)�ṹ�����Ͷ���
	//structΪ�ؼ��֣�StuΪ�Զ����ʾ��
	//struct Stu���ǽṹ������
	//�ṹ���Ա�����ڶ�������ʱ��ֵ
	struct Stu
	{
		int age;
		char name[50];
		int scroe;
	}; //�����зֺ�

2)�ṹ������Ķ���ͳ�ʼ��
	//�ṹ�������ʼ������������ƣ�ֻ���ڶ���ʱ�����ܳ�ʼ��
	//����ṹ�����ʱ��������struct�ؼ���
	struct Stu obj = {18, "mike", 59};

3)�ṹ���Ա������ʹ��
a)�������ͨ�������������
	obj.age = 18;

b)�����ָ�������->
	(&obj)->age = 28;

2���ṹ��ָ�����
1)ָ�����ָ��ջ��
	struct Stu *p = NULL;
	struct Stu obj; //ջ���ṹ��
	p = &obj;		//ָ��ջ��
	p->age = 18;
	(*p).age = 18;
	
2)ָ�����ָ�����
	struct Stu *p = NULL;
	
	//ָ�����
	p = (struct Stu *)malloc(sizeof(struct Stu));
	p->age = 18;
	
	free(p);
	p = NULL;

3)const���ε�ָ�����
	//��const������*�����Ǳ���
	//�����*��˵���ṹ���Ա�������޸�
	//����Ǳ�����˵���ṹ��ָ������������޸�
	
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

3���ṹ������
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
		tmp[i].age = 18+i; //����
	}

4���ṹ��ͺ���
1)ͬ���ͽṹ�������ֵ
	struct Stu obj1 = {18, "lily", 99};
	struct Stu obj2;
	obj2 = obj1;
	
2)����ֵ����
	a)
	struct Stu p;
	//�ṹ�����������(ֵ����)���β��޸Ĳ���Ӱ�쵽ʵ��
	//�������fun()������p�ĳ�Ա����û�и�ֵ
	fun(p); 
	void fun(struct Stu p)
	{
		p.age = 18;
		strcpy(p.name, "mike");
		p.score = 59;
	}
	
	b)
	struct Stu s = {18, "mike", 59};
	fun(s); //ֵ����
	void fun(struct Stu s) //����ʱ����ʵ��s��Ա�����ݸ��β�s��ֵ
	{	//��Ȼ�ܴ�ӡ���ݣ����Ǵ�ӡ����Ϊfun�β�s��Ա����������
		printf("%d, %s, %d\n", s.age, s.name, s.score);
	}
	
3)������ַ����
	struct Stu p;
	fun(&p); //��ַ���ݣ��β��޸Ŀ��Լ��Ӱ�쵽ʵ��
	void fun(struct Stu *p)
	{
		p->age = 18;
		strcpy(p->name, "mike");
		p->score = 59;
	}

5���ṹ����һ��ָ��
	struct Stu
	{
		int age;
		char *name; //һ��ָ��
		int score;
	}; //�����зֺ�
	
1)ջ���ṹ��
	struct Stu s;
	s.age = 10;
	
	s.name = (char *)malloc( strlen("mike") + 1);
	strcpy(s.name, "mike");
	s.score = 59;
	
	free(s.name);

2)�����ṹ��
	struct Stu *p;
	p = (struct Stu *)malloc(sizeof(struct Stu));
	p->name = (char *)malloc( strlen("mike") + 1);
	p->age = 18;
	strcpy(p->name, "mike");
	p->score = 59;
	
	free(p->name);
	free(p);

6�������壨�����壩
	//ֻ��Ҫ�ѽṹ���struct��Ϊunion
	union Test
	{
		unsigned char a;
		unsigned short b;
		unsigned int c;
	};

	//union Test������
	//tmp�Ǳ�����
	union Test tmp;

	//1�������壬���г�Ա����һ���ڴ�ռ�
	//2�����г�Ա���׵�ַ��һ����
	printf("%p, %p, %p\n", &tmp.a, &tmp.b, &tmp.c);
	
	//3��������Ĵ�СΪ����Ա�Ĵ�С
	printf("sizeof(union Test) = %lu\n", sizeof(union Test) );

	//4���ı�һ����Ա����Ӱ�쵽����ĳ�Ա
	//����Ǹ�λ���ұ��ǵ�λ
	//��λ�Ÿߵ�ַ����λ�ŵ͵�ַ��С�ˣ�
	tmp.c = 0xaabbccdd;
	printf("c1 = %x\n", tmp.c); //aabbccdd
	printf("a = %x\n", tmp.a); //dd
	printf("b = %x\n", tmp.b); //ccdd
	
	tmp.a = 0x11;
	printf("c2 = %x\n", tmp.c); //aabbcc11
	
	tmp.b = 0x1234;
	printf("c3 = %x\n", tmp.c); //aabb1234
	
7��ö��
	//����ö������ enum{};
	//enum Color��ö������
	enum Color
	{
		//ö�ٳ�Ա��ö�ٳ���
		//a)�����Ա����ֵ����0����ԱֵΪ0����һ����Ա��ǰһ����1
		red, blue, green, black, white
	};
	
	//1������ֱ�Ӱ�ö�ٳ�����ֵ�����ͱ���
	int flag = red;
	
	//2������һ��ö�ٱ���������ö�ٳ�����ֵ
	enum Color tmp = red;
	
	//3������ֱ����һ��������ö�ٱ�����ֵ�����ǲ��Ƽ�
	//tmp = 100;
	
	printf("%d\n", tmp);

8��typedef��ʹ��
	//typedef�����þ��Ǹ�һ���Դ��ڵ�������һ������
	//typedef���ܴ���������
	typedef int int64; 
	int64 a; //int a

	//��struct Student���ͣ���һ��������Stu
	typedef struct Student
	{
		//�ṹ���Ա
		char name[50];
		int age;
		int score;
	}Stu; //�и��ֺ�

	//��struct Student���ͣ���һ��������S
	typedef struct Student S;

	struct Student obj; //������������struct�ؼ���
	Stu obj2;
	S tmp;
	
	
