#include<stdio.h>
#include"CDateTime.h"
#include"menu.h"

////////////////////////////////////////
#define UP 72
#define DOWN 80
#define PAGEUP 73
#define PAGEDOWN 81
#define S 115

////////////////////////////////////////
CDateTime nowtime;
int main()
{
	InitDateTime(&nowtime);
	GetNowDateTime(&nowtime);
	while(1)
	{
		system("CLS");
		menu();
		int select;
		scanf("%d",&select);
		switch(select)
		{
		case 1:
			system("CLS");
			menu1();
			int se1;
			scanf("%d",&se1);
			switch(se1)
			{
			case 1:
				system("CLS");
				CDateTime ndt;
				InitDateTime(&ndt);
				ShowNowTime(&ndt);
				break;
			case 2:
				system("CLS");
				week();
				ShowCalender(&nowtime);
				system("pause");
				break;
			case 0:
				break;
			default:
				break;
			}
			break;
		case 2:
			system("CLS");
			menu2();
			int se2;
			scanf("%d",&se2);
			switch(se2)
			{
			case 1:
				system("CLS");
				CDateTime dt;
				InitDateTime(&dt);
				ShowNowTime(&dt);
				break;
			case 2:
				int n;
				printf("请输入天数：");
				scanf("%d",&n);
				CDateTime ndt;
				InitDateTime(&ndt);
				GetNowDateTime(&ndt);
				GetNDateTime(&ndt,n);

				system("pause");
				break;
			case 3:
				int n1;
				printf("请输入天数：");
				scanf("%d",&n1);
				CDateTime now;
				InitDateTime(&now);
				GetNowDateTime(&now);
				GetNqDateTime(&now,n1);
				system("pause");
				break;
			case 4:
				system("CLS");
				GetLength();
				system("pause");
				break;
			case 5:
				system("CLS");
				break;
			default:
				break;
			}
			break;
		case 3:
			system("CLS");
			//更改while循环的位置，使得可以不断输出刷新的日期节点
			
			CDateTime dt;
			InitDateTime(&dt);
			GetNowDateTime(&dt);
			while(1)
			{
				system("CLS");
				int ch=0;
				printf("今天是%d年%d月%d日星期%d\n",dt.m_year,dt.m_month,dt.m_mday,dt.m_wday+1);
				week();
				ShowCalender(&dt);
				creation();
				ch=_getch();
				ch=_getch();
				switch(ch)
				{
				case PAGEUP:

					ShowAnyCalender(&dt,ch);
					//				week();
					//				ShowCalender(&dt);
					system("CLS");
					break;
				case PAGEDOWN:
					ShowNewCalender(&dt,ch);
					//				week();
					//				ShowCalender(&dt);
					system("CLS");
					break;
				case UP:
					printf("按下的是上键\n");
					GetNDateTime(&dt,1);
					break;
				case DOWN:
					printf("按下的是下键\n");
					GetNqDateTime(&dt,1);
					break;
				case S:
					break;
				default:
					break;
				}

			}
			system("pause");

			break;
		case 4:
			CreateTXT(&nowtime);
			break;
		case 5:
			return 0;
			break;
		default:
			break;
		}
		
	}
}