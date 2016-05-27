//客户端

#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<windows.h>
#include<locale.h>
using namespace std;

bool Judge(char *buf, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		if (buf[i] != 0)
		{
			return false;
		}
	}
	return true;
}

#pragma comment(lib, "ws2_32.lib")
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

	SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);   //AF_INET tcpip的协议
															 //初始化连接
	SOCKADDR_IN addrSrv;  //服务器的地址
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.74.129");
	addrSrv.sin_family = AF_INET;  //使用的是TCP/IP 
	addrSrv.sin_port = htons(8001);  //转为网络序  设置端口号

								   //连接到服务器 使用SOCKET对象连接服务器,送入服务器的地址信息  强转
	if (connect(socketClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) < 0)  //协议参数  套接字参数 
	{
		printf("connction faild!");
		closesocket(socketClient);
		return 0;
	}

	//如果连接到了  那就先传出命令字符串再去接收命令执行结果集
	char recvBuf[512] = { 0 };
	char sendBuf[512] = { 0 };
	
//	FILE* fp = fopen("resultfile.txt", "w");//真的有必要再写入一个文件里面么？
//	if (!fp)
//		return 0;


	//写入文件
	while (1)
	{
		//输入并传输命令
		cin >> sendBuf;
		send(socketClient, sendBuf, 512, 0);
		//cout << "已经传输了命令，等待接受结果集" << endl;
		memset(sendBuf, 0, 512);

		while (1)
		{
			//接收结果集
			int len = recv(socketClient, recvBuf, 512, 0);
		//	cout << "接受结果集" << endl;
			//fwrite(recvBuf, 1, len, fp);
			cout << recvBuf << endl;
		//	cout << "len:" << len << endl;
		//	cout << "打印结果集" << endl;
			//printf("%s\n", recvBuf);
			
			if (Judge(recvBuf,512))
			{
		//		cout << "我要退出接受结果集的循环了" << endl;
				break;
			}
			memset(recvBuf, 0, 512);
	//		cout << "清空缓冲区" << endl;
		}

	}






	//char recvBuf[50] = {0};

	//int size = 10;
	//int i = 0;
	//while (i<100)
	//{
	//	//recv(socketClient, recvBuf, 50, 0);  //socket对象已经接收到数据，现在开始次on个缓存区中取数据
	//    //printf("%s\n", recvBuf);
	//	send(socketClient, "123456789" , 50, 0);
	//	//Sleep(100);
	//}

	closesocket(socketClient);  //关闭socket连接

	WSACleanup();

	printf("Client exit!");
	system("pause");
	return 0;

}