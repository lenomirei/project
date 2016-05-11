#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<iostream>
#include<fstream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")



#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>  
#include<string>
#include<time.h>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<string>
#pragma comment (lib, "winmm.lib")


void ShowFileList(string filename,SOCKET sockConn)
{
	
	WIN32_FIND_DATAA p;
	HANDLE h = FindFirstFileA(filename.c_str(), &p);
	if (string(p.cFileName) != "." || string(p.cFileName) != "..")
	{
		send(sockConn, p.cFileName, 260, 0);
	}
	while (FindNextFileA(h, &p))
	{
		if (string(p.cFileName) != "." || string(p.cFileName) != "..")
		{
			cout << p.cFileName << endl;
			send(sockConn, p.cFileName, 260, 0);
		}
	}
	char end[260] = "transform end";
	send(sockConn, "transform end", 260, 0);
	/*for (int i = 0; i < filelist.size(); i++)
	{
		cout << filelist[i] << endl;
	}*/
}

void ShowLastFileList(string & filepath,SOCKET sockConn)
{
	string filepath2 = filepath;
	string tmp = "../";
	tmp += filepath2;
	filepath = tmp;
	ShowFileList(tmp, sockConn);
}


void ShowSelectFileList(string &filepath, SOCKET sockConn)
{
	char Path[260] = { 0 };
	recv(sockConn, Path, 260, 0);
	cout << "Path:" << Path << endl;
	string yourchoose(Path);
	yourchoose += '/';
	string filepath2 = filepath;
	yourchoose += filepath2;
	ShowFileList(yourchoose, sockConn);
}



string ExecuteCommand(SOCKET sockConn)
{
	string filepath = "";
	string FileName = "*.*";
	string FilePath = filepath + FileName;
	while (1)
	{
		char *command = new char(0);
		recv(sockConn, command, 1, 0);
		cout << "command" << command << endl;
		if (*command == '4')
		{
			char filename[260] = { 0 };
			recv(sockConn, filename, 260, 0);
			cout << "FilePath1:  " << FilePath << endl;
			FilePath.erase(FilePath.size() - 3, 3);
			cout<<"FilePath2:  " << FilePath << endl;
			FilePath += filename;
			break;
		}
		switch (*command)																  //首先发文件名
		{
		case '1':
			ShowFileList(FilePath, sockConn);
			break;
		case '2':
			ShowLastFileList(FilePath, sockConn);
			break;
		case '3':
			ShowSelectFileList(FilePath, sockConn);
			break;
		case '5':
			closesocket(sockConn);
			exit(0);
			break;
		}
	}
	return FilePath;
}





int main()
{
	WORD wVersionRequested;  //typedef unsigned short WORD
	WSADATA wsaData;   //用阿里存储系统传回的关于WinSocket的资料
	int err;  //用来判断启动函数是否正常

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);   //AF_INET tcpip的协议

	SOCKADDR_IN addrSrv;

	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8001);  //ftp server

								   //绑定自己的socket地址 到一个socket对象  等于说服务器和客户端都要进行该socket的 连接/绑定，且服务器影应该先绑定
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//设计监听该socket,该socket已经绑定了socket地址，所以凡是连接该socket的客户端都会被加入到队列中
	listen(sockSrv, 5);  //设置监听队列  使服务器socket处于监听状态

	SOCKADDR_IN addrClient;  //保存客户端的ip地址
	int len = sizeof(SOCKADDR);

	//监听循环
	while (1)
	{
		//这里可能进程会阻塞，等待唤醒
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);  //接受客户端连接
																		  //当收到一个请求时 发送给其文件


		//首先接收一个命令
		string FilePath=ExecuteCommand(sockConn);
		cout<<"return FilePath:  " << FilePath << endl;
	//	char filename[256] = { "test2.txt " };  //不超过255个字符

//		send(sockConn, filename, strlen(filename) + 1, 0);
		
		//send(sockConn, "hello", 6, 0);
		//Sleep(2000);
		FILE * fp;
		fp = fopen(FilePath.c_str(), "rb");
		if (!fp)
			return 0;


		//发送缓冲
		char sendBuf[512] = { 0 };  //一次512B 数据

									 //FILE * fp = fopen("F:\\1.pdf", "rb");
		int count = 0;
		

		while (1)
		{
			memset(sendBuf, 0, 512);
			int len = fread(sendBuf, 1, 512, fp);
			send(sockConn, sendBuf, len, 0);
		//	printf("sendBuf:%c\n",* sendBuf);
		//	printf("len:%d\n", len);
			count++;
			if (len<1)
				break;
		}
		//memset(sendBuf, 0, 1);
		//strcpy(sendBuf, "end");
		//send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		//printf("Finished!\n%d",count);
		closesocket(sockConn);
	}

	closesocket(sockSrv);
	WSACleanup();
	system("pause");
	return 0;
}
