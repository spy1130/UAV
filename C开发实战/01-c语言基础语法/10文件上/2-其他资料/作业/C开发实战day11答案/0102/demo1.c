1111 09:17:01
void main12() 
{
	//2、利用sleep函数(Linux平台)结合结构体，编写一个模拟时钟
	struct  Time T;
	int flag = 0;
	//获取时间
	time_t timep;
	char s[30];
	time(&timep);
	strcpy(s, ctime(&timep));
	//printf("%s", s);
	//Wed Mar 28 11:15 : 06 2018

	//组包
	/*char ch[100];
	int ma = 1011;
	int len=sprintf(ch, "%d:", ma);*/
	//printf("%s   len=%d\n", ch, len);

	//拆包
	int a=0,b=0,c=0;
	char * buff111 = s;
	sscanf(buff111,"%*11c%02d:%02d : %02d",&T.hour,&T.minute,&T.second);
	//printf("%d:%d:%d\n", T.hour, T.minute, T.second);
	while (1)
	{
		
		T.second = (T.second += 1) == 60 ? 0 : T.second;//拿到秒直接加一。。。。。。。。。。比正常的快一秒.....
		if (T.second==0) {//T.second==0  加1分钟
			flag++;//
			//printf("T.second==0====%\n", flag);
			T.minute = (T.minute += 1) == 60 ? 0 : T.minute;
		}
		if (flag !=0&& T.minute==0) {// 两个条件同时满足 才能加小时
			flag = 0;
			T.hour = (T.hour += 1) == 12 ? 0 : T.hour;
		}
		printf("%02d:%02d:%02d\r", T.hour, T.minute, T.second);
		_sleep(1000);
	
	}

}
