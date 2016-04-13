#include<stdio.h>

/****************************************
 * Function name:  main
 * Argument     :  void
 * Destribute   :  
 * Return value :
 * when   why   what    who
 * 
 ****************************************/

extern int ConvertCtoCpp(FILE *, FILE *);
extern int CommentConvert(FILE *, FILE *);

int main()
{
	char Input[20];
	char Output[20];
	printf("请输入输入文件的路径");
	scanf("%s",Input);
	printf("请输入输出文件的路径");
	scanf("%s",Output);
	int select;
	FILE *fpIn;
	FILE *fpOut;
	fpIn = fopen(Input,"r");
	if(NULL == fpIn)
	{
		printf("Error: Open input.c file fail!\n");
		return -1;
	}
	fpOut = fopen(Output,"w");
	if(NULL == fpOut)
	{
		printf("Error: Open output.c file fail!\n");
		return -1;
	}
	printf("请输入您想完成的操作\n");
	printf("1.C  to Cpp\n");
	printf("2.Cpp  to  C\n");
	scanf("%d",&select);
	switch(select)
	{
	case 1:
		ConvertCtoCpp(fpIn,fpOut);//
		break;
	case 2:
		CommentConvert(fpIn,fpOut);
		break;
	default :
		break;
	}
	fclose(fpIn);
	fclose(fpOut);
	return 0;
}