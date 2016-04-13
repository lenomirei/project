#include<stdio.h>
void menu()
{
	printf("1.日历显示->\n");
	printf("2.日历查询->\n");
	printf("3.修改日期->\n");
	printf("4.日期备忘录->\n");
	printf("5.退出\n");
}
void menu1()
{
	printf("显示日期时间\n");
	printf("显示本月日历表\n");
	printf("返回主菜单\n");
}
void menu2()
{
	printf("显示当前日期\n");
	printf("查询N天后日期\n");
	printf("查询N天前日期\n");
	printf("查看距离某日期的天数\n");
	printf("返回主菜单\n");
}
void week()
{
	printf("  SUN  MON  TUES  WED THUR  FRI  SAT  \n");
}
void creation()
{
	printf("\n");
				printf("按下PageDown可以看下一个月的日历         ");
				printf("按下PageUp可以看上一个月的日历\n");
				printf("上键昨天       ");
				printf("下键明天\n");
				printf("按下其他键退出\n");
}