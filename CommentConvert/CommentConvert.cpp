#include<stdio.h>

#define UL unsigned long

//定义状态
typedef enum
{
	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	STR_COMMENT_STATE,
	END_STATE
}STATE_ENUM;
STATE_ENUM Last_State=NO_COMMENT_STATE;
//定义状态机
typedef struct STATE_MACHINE
{
	FILE *inputfile;
	FILE *outputfile;
	STATE_ENUM ulstate;
}STATE_MACHINE;

///////////////////////////////////////////////////
STATE_MACHINE  g_state = {0};
void EventPro(char ch);
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
void EventProAtStr(char ch);
//////////////////////////////////////////////////

int CommentConvert(FILE *inputfile, FILE *outputfile)
{
	if(inputfile==NULL || outputfile==NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}

	////////////////////////////////////////////////
	//
	g_state.inputfile = inputfile;
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;
	
	char ch;
	while(g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		EventPro(ch);
	}
	return 0;
}

void EventPro(char ch)
{
	switch(g_state.ulstate)
	{
	case NO_COMMENT_STATE:
		EventProAtNo(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp(ch);
		break;
	case STR_COMMENT_STATE:
		EventProAtStr(ch);
		break;
	case END_STATE:
		break;
	default:
		break;
	}
}

void EventProAtNo(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		g_state.ulstate=END_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/') //C++
		{
			fputc(ch,g_state.outputfile);
			fputc('*',g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;//进入C++状态
		}
		else if(nextch == '*') // C
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;//进入C状态
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);//只是一个单纯的符号
		}
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=STR_COMMENT_STATE;
		Last_State=NO_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void EventProAtC(char ch)
{
	char nextch;
	switch (ch)
	{
	case EOF:
		g_state.ulstate=END_STATE;
		break;
	case '*' :
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;//C状态结束
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);//不需要更改状态
		}
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);//不可以改变状态
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);//单纯的一个符号不改变状态
		}
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=STR_COMMENT_STATE;
		Last_State=C_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void EventProAtCpp(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else if(nextch == '*')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);//就算这有C的也不改变状态
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '\n':
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		fputc(ch,g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=STR_COMMENT_STATE;
		Last_State=CPP_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void EventProAtStr(char ch)
{
	char nextch;
	switch (ch)
	{
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=Last_State;
		break;
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate=END_STATE;
		break;
	case '\n':
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate=NO_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void eventpro(char ch);
void eventproAtNo(char ch);
void eventproAtC(char ch);
void eventproAtCpp(char ch);
void eventproAtStr(char ch);
//////////////////////////////////////////////////

int ConvertCtoCpp(FILE *inputfile, FILE *outputfile)
{
	if(inputfile==NULL || outputfile==NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}

	////////////////////////////////////////////////
	//
	g_state.inputfile = inputfile;
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;
	
	char ch;
	while(g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		eventpro(ch);
	}
	return 0;
}

void eventpro(char ch)
{
	switch(g_state.ulstate)
	{
	case NO_COMMENT_STATE:
		eventproAtNo(ch);
		break;
	case C_COMMENT_STATE:
		eventproAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		eventproAtCpp(ch);
		break;
	case STR_COMMENT_STATE:
		eventproAtStr(ch);
		break;
	case END_STATE:
		break;
	default:
		break;
	}
}

void eventproAtNo(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		g_state.ulstate=END_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/') //C++
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;//进入C++状态
		}
		else if(nextch == '*') // C
		{
			fputc('/',g_state.outputfile);
			fputc('/',g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;//进入C状态
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);//只是一个单纯的符号
		}
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=STR_COMMENT_STATE;
		Last_State=NO_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void eventproAtC(char ch)
{
	char nextch;
	switch (ch)
	{
	case EOF:
		g_state.ulstate=END_STATE;
		break;
	case '*' :
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;//C状态结束
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);//不需要更改状态
		}
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);//不可以改变状态
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);//单纯的一个符号不改变状态
		}
		break;
	case '\n':
		fputc(ch,g_state.outputfile);
		fputc('/',g_state.outputfile);
		fputc('/',g_state.outputfile);
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=STR_COMMENT_STATE;
		Last_State=C_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void eventproAtCpp(char ch)
{
	char nextch;
	switch(ch)
	{
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else if(nextch == '*')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);//就算这有C的也不改变状态
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '\n':
		fputc(ch,g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
		}
		else
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
		}
		break;
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=STR_COMMENT_STATE;
		Last_State=CPP_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void eventproAtStr(char ch)
{
	char nextch;
	switch (ch)
	{
	case '"':
		fputc('"',g_state.outputfile);
		g_state.ulstate=Last_State;
		break;
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate=END_STATE;
		break;
	case '\n':
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate=NO_COMMENT_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}

