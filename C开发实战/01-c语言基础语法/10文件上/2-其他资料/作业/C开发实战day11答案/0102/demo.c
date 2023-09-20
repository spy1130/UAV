Darren 09:17:06
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct STR_TIME
{
	int hour;
	int minute;
	int second;
}Time;


int main(int argc,char* argv[])
{
	/*
	Times times;
	
	time_t tmpcal_ptr;  
	struct tm *tmp_ptr = NULL;
	
	time(&tmpcal_ptr);
	tmp_ptr = localtime(&tmpcal_ptr);
	
	times.year=(1900+tmp_ptr->tm_year);
	times.month=(1+tmp_ptr->tm_mon);
	times.day=(tmp_ptr->tm_mday);
	*/
	Time times;
	time_t tmpcal_ptr;  
	struct tm *tmp_ptr = NULL;
	
	time(&tmpcal_ptr);
	tmp_ptr = localtime(&tmpcal_ptr);
	times.hour=(tmp_ptr->tm_hour);
	times.minute=(tmp_ptr->tm_min);
	times.second=(tmp_ptr->tm_sec);
	
	/*
	Time times;
	
	times.hour=10;
	times.minute=58;
	times.second=58;
	*/
	char ch[10];
	sprintf(ch,"%02d:%02d:%02d",times.hour,times.minute,times.second);
	while(1)
	{
		printf("%s\r",ch);
		//sleep(1);
		if(times.second>59)
		{
			
			times.minute=times.minute+times.second/59;
			
			if(times.minute>59)
			{
				times.hour=times.hour+times.minute%59;
			}
			if(times.minute==60)
			{
				times.minute=0;
			}
			times.second=times.second%59;
			if(times.second==59)
			{
				times.second=0;
			}
		}
		sleep(1);
		sprintf(ch,"%02d:%02d:%02d",times.hour,times.minute,times.second+=1);
		fflush(stdout);
		
	}
	
	return 0;
} 