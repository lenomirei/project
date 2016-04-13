#ifndef _CDATETIME_H
#define _CDATETIME_H

#include"stdafx.h"

typedef struct CDateTime
{
	int m_year;
	int m_month;
	int m_mday;
	int m_hour;
	int m_minute;
	int m_second;
	int m_wday;
	int m_yday;
}CDateTime;

#define SUN 0
#define MON 1
#define TUES 2
#define WED 3
#define TURS 4
#define FRI 5
#define SAT 6


/////////////////////////////////////////
void InitDateTime(CDateTime *dt);
void GetNowDateTime(CDateTime *dt);
void ShowDateTime(CDateTime *dt);
void ShowNowTime(CDateTime *dt);
void ShowCalender(CDateTime *dt);
void GetNDateTime(CDateTime *ndt,int n);
void GetNqDateTime(CDateTime *ndt,int n);
void GetLength();
bool IsBig(CDateTime ndt,CDateTime dt);
void ShowAnyCalender(CDateTime *dt,char ch);
void ShowNewCalender(CDateTime *dt,char ch);
void ShowNewCalender(CDateTime *dt,char ch);
int GetMonth(int year,int month);
bool IsLeapYear(int year);
int GetYDay(CDateTime *dt);
void CreateTXT(CDateTime *ndt);

#endif

