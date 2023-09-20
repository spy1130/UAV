#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct Time
{//表示时间的数据类型

	int hour;
	int minute;
	int second;
}Time;
	


int main()
{
	Time m_date;

	m_date.hour = 10;
	m_date.minute = 00;
	m_date.second = 00;

	printf("当前时间为：\n");
	
	while(1)
	{
		sleep(1);
		m_date.second++;
		if(m_date.second >= 60)
		{
			m_date.second = 0;
			
			m_date.minute++;
			if(m_date.minute >= 60)
			{
				m_date.minute = 0;
				
				m_date.hour++;
				if(m_date.hour >= 24)
				{
					m_date.hour = 0;
				}
			}
		}
		printf("\r%02d:%02d:%02d",m_date.hour,m_date.minute,m_date.second);
		fflush(stdout);
	}
}