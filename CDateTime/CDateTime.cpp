#include"CDateTime.h"

//////////////////////////
#define TRUE 1
#define FALSE 0
#define SIZE 100


////////////////////////////
char weekday[7][5]={"SUN","MON","TUES","WED","TURS","FRI","SAT"};

int GetYDay(CDateTime *dt)
{
	int result=0;
	for(int i=1;i<dt->m_month;i++)
	{
		result+=GetMonth(dt->m_year,i);
	}
	result+=dt->m_mday;
	return result;
}
void InitDateTime(CDateTime *dt)
{
	dt->m_year = 1;
	dt->m_month = 1;
	dt->m_mday = 1;
	dt->m_hour = 1;
	dt->m_minute = 1;
	dt->m_second = 1;
	dt->m_wday = 1;
	dt->m_yday = 1;
}
bool IsLeapYear(int year)
{
	if((year%4 == 0 && year%100!=0) || (year%400==0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int GetMonth(int year,int month)
{
	int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(IsLeapYear(year) && month==2)
	{
		return 29;
	}
	else
	{
		return mon[month];
	}
}


void ShowDateTime(CDateTime *dt)
{
	printf("%d年%d月%d日\n",dt->m_year,dt->m_month,dt->m_mday);
	printf("%d时%d分%d秒\n",dt->m_hour,dt->m_minute,dt->m_second);
}
void GetNowDateTime(CDateTime *dt)
{
	time_t te;
	time(&te);
	tm *ptm = localtime(&te);
	dt->m_year = ptm->tm_year+1900;
	dt->m_month = ptm->tm_mon+1;
	dt->m_mday = ptm->tm_mday;
	dt->m_hour = ptm->tm_hour;
	dt->m_minute = ptm->tm_min;
	dt->m_second = ptm->tm_sec;
	dt->m_wday=ptm->tm_wday;
	dt->m_yday=ptm->tm_yday;
}
void GetNDateTime(CDateTime *ndt,int n)
{
	char *temp;
	if(n < GetMonth(ndt->m_year,ndt->m_month-1)-ndt->m_mday)//-1是当前月的下标，不加不减是当前月的下标
	{
		ndt->m_mday+=n;
		ndt->m_wday=(ndt->m_wday+n)%7;
	}
	else if(n < 365-GetYDay(ndt))
	{
		ndt->m_wday=(ndt->m_wday+n)%7;
		n=n-(GetMonth(ndt->m_year,ndt->m_month-1)-ndt->m_mday)-1;
		ndt->m_month++;
		ndt->m_mday=1;
		while(n>GetMonth(ndt->m_year,ndt->m_month-1))
		{
			n=n-GetMonth(ndt->m_year,ndt->m_month-1);
			ndt->m_month++;
		}
		ndt->m_mday+=n;	
	}
	else
	{
		ndt->m_wday=(ndt->m_wday+n)%7;
		n=n-(365-GetYDay(ndt))-1;
		ndt->m_year++;
		ndt->m_month=1;
		ndt->m_mday=1;
	/*	if(n>(month[ndt->m_month-1]-ndt->m_mday))
		{
			n=n-(month[ndt->m_month-1]-ndt->m_mday);
			ndt->m_month++;
		}*/
		while(n>GetMonth(ndt->m_year,ndt->m_month-1))
		{
			n=n-GetMonth(ndt->m_year,ndt->m_month-1);
			ndt->m_month++;
			if(ndt->m_month>12)
			{
				ndt->m_month=1;
				ndt->m_year++;
			}
		}
		ndt->m_mday+=n;
	}
	temp=weekday[ndt->m_wday];
	printf("%d年%d月%d日%s\n",ndt->m_year,ndt->m_month,ndt->m_mday,temp);
}
void GetNqDateTime(CDateTime *ndt,int n)
{
	char *temp;
	
	if(n < ndt->m_mday)
	{
		ndt->m_mday-=n;
		if(ndt->m_wday-n%7>=0)
		{
			ndt->m_wday=ndt->m_wday-n%7;
		}
		else
		{
			ndt->m_wday=7-abs(ndt->m_wday-n%7);
		}
		
	}
	else if(n < GetYDay(ndt))
	{
		if(ndt->m_wday-n%7>=0)
		{
			ndt->m_wday=ndt->m_wday-n%7;
		}
		else
		{
			ndt->m_wday=7-abs(ndt->m_wday-n%7);
		}
		n=n-ndt->m_mday;
		ndt->m_month--;
		ndt->m_mday=GetMonth(ndt->m_year,ndt->m_month-1);//-1是当前月的下标，-2是上个月的下标
		while(n>GetMonth(ndt->m_year,ndt->m_month-1))
		{
			
			n=n-GetMonth(ndt->m_year,ndt->m_month-1);
			ndt->m_month--;
		}
		ndt->m_mday-=n;
	}
	else
	{
		if(ndt->m_wday-n%7>=0)
		{
			ndt->m_wday=ndt->m_wday-n%7;
		}
		else
		{
			ndt->m_wday=7-abs(ndt->m_wday-n%7);
		};//这条语句需要重新用蔡勒公式给出
		n=n-GetYDay(ndt);
		ndt->m_year--;
		ndt->m_month=12;
		ndt->m_mday=31;
		/*while(n>365)
		{
			n-=365;
			ndt->m_year--;
		}
		while(n>month[ndt->m_month-1])
		{
			
			n=n-month[ndt->m_month-1];
			ndt->m_month++;
		}*/
		while(n>GetMonth(ndt->m_year,ndt->m_month-1))
		{
			n=n-GetMonth(ndt->m_year,ndt->m_month-1);
			ndt->m_month--;
			if(ndt->m_month<=0)
			{
				ndt->m_month=12;
				ndt->m_year--;
			}
		}
		ndt->m_mday-=n;
	}
	temp=weekday[ndt->m_wday];
	printf("%d年%d月%d日%s\n",ndt->m_year,ndt->m_month,ndt->m_mday,temp);
}
void ShowNowTime(CDateTime *dt)
{
	char ch='c';
	while(ch!=27)
	{
		printf("请输入‘ESC’退出\n");
		GetNowDateTime(dt);
		ShowDateTime(dt);
		Sleep(1000);
		if(_kbhit())
		{
			ch=_getch();
		}
		system("CLS");
	}
}
void ShowCalender(CDateTime *dt)
{
	int distance,weekday1;
	
	distance=dt->m_mday-1;
	if(dt->m_wday-distance%7>=0)
	{
		weekday1=dt->m_wday-distance%7;//这句话需要进行修改加强健壮性可能会出现负值
	}
	else
	{
		weekday1=7-abs(dt->m_wday-distance%7);
	}
	for(int j=0;j<5*weekday1;++j)
	{
		printf(" ");
	}
	for(int i=1;i<=GetMonth(dt->m_year,dt->m_month-1);++i)
	{
		printf("%5d",i);
		if((i-(6-weekday1+1))%7==0)
		{
			printf("\n");
		}
	}
	printf("\n");
}//这个函数需要进行参数改写
void ShowAnyCalender(CDateTime *dt,char ch)
{//主要目标找出改约第一号距离当天的日子，然后计算可能的星期，再进行循环输出
	GetNqDateTime(dt,GetMonth(dt->m_year,dt->m_month-1));
	
}//这个函数需要改写
void ShowNewCalender(CDateTime *dt,char ch)
{
	GetNDateTime(dt,GetMonth(dt->m_year,dt->m_month-1));
}
bool IsBig(CDateTime ndt,CDateTime dt)
{
	if(dt.m_year>ndt.m_year)
	{
		return true;
	}
	else if(dt.m_year<ndt.m_year)
	{
		return false;
	}
	else
	{
		if(dt.m_month>ndt.m_month)
		{
			return true;
		}
		else if(dt.m_month<ndt.m_month)
		{
			return false;
		}
		else
		{
			if(dt.m_mday>ndt.m_mday)
			{
				return true;
			}
			else if(dt.m_mday<ndt.m_mday)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}
void GetLength()
{	
	int result=0;
	CDateTime dt;
	InitDateTime(&dt);
	CDateTime ndt;
	InitDateTime(&ndt);
	GetNowDateTime(&ndt);
	printf("请输入一个日期");
	scanf("%d%d%d",&dt.m_year,&dt.m_month,&dt.m_mday);
	if(IsBig(ndt,dt))
	{
		
		if(ndt.m_year == dt.m_year)
		{
			for(int i=ndt.m_month;i<dt.m_month-1;i++)
			{
				result+=GetMonth(dt.m_year,i);
			}
		}
		else
		{
			for(int i=0;i<dt.m_month-1;i++)
			{
				result+=GetMonth(dt.m_year,i);
			}
			for(int i=ndt.m_month;i<12;i++)
			{
				result+=GetMonth(dt.m_year,i);
			}
			for(int i=ndt.m_year+1;i<dt.m_year;i++)
			{
				result+=365;
			}
		}
		if(ndt.m_month==dt.m_month)
		{
			result+=(dt.m_mday-ndt.m_mday);
		}
		else
		{
			result+=dt.m_mday;
			result=result+GetMonth(ndt.m_year,ndt.m_month-1)-ndt.m_mday;
		}
	}
	else
	{
		if(dt.m_year == ndt.m_year)
		{
			for(int i=dt.m_month;i<ndt.m_month-1;i++)
			{
				result+=GetMonth(dt.m_year,i);
			}
		}
		else
		{
			for(int i=0;i<ndt.m_month-1;i++)
			{
				result+=GetMonth(dt.m_year,i);
			}
			for(int i=dt.m_month;i<12;i++)
			{
				result+=GetMonth(dt.m_year,i);
			}
			for(int i=dt.m_year+1;i<ndt.m_year;i++)
			{
				result+=365;
			}
		}
		if(dt.m_month==ndt.m_month)
		{
			result+=(ndt.m_mday-dt.m_mday);
		}
		else
		{
			result+=ndt.m_mday;
			result=result+GetMonth(dt.m_year,dt.m_month-1)-dt.m_mday;
		}
	}
	printf("%d\n",result);
}


void CreateTXT(CDateTime *ndt)
{
	char temp[SIZE];
	char *address;
	address=(char *)malloc(strlen(temp)+1+16);
	printf("请输入您要保存的路径：");
	scanf("%s",temp);
	sprintf(address,"%s/%d_%d_%d.txt",temp,ndt->m_year,ndt->m_month,ndt->m_mday);
	FILE *fp;
	fp=fopen(address,"w");
	if(NULL==fp)
	{
		printf("error:can't open file");
	}

}