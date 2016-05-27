#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> //inet_ntoa()函数的头文件
#include <string>
#include <unistd.h>
#include <iostream>
using namespace std;



bool Judge(char *buf,size_t size)
{
	for(int i =0;i<size;++i)
	{
		if(buf[i]!=0)
		{
			return false;
		}
	}
	return true;
}


#define portnumber 8001 //定义端口号：（0-1024为保留端口号，最好不要用）

int main(int argc, char *argv[])
{
	int sockfd, new_fd;
	struct sockaddr_in server_addr; //描述服务器地址
	struct sockaddr_in client_addr; //描述客户端地址
	socklen_t sin_size;
	char hello[] = "Hello! Are You Fine?\n";


	/* 服务器端开始建立sockfd描述符 */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{
		fprintf(stderr, "Socket error:%s\n\a", strerror(errno));
		exit(1);
	}

	/* 服务器端填充 sockaddr结构 */
	bzero(&server_addr, sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family = AF_INET; // Internet
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // (将本机器上的long数据转化为网络上的long数据)和任何主机通信 //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	server_addr.sin_addr.s_addr=inet_addr("192.168.74.128"); //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port = htons(portnumber); // (将本机器上的short数据转化为网络上的short数据)端口号

											
	if (bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
		exit(1);
	}  /* 捆绑sockfd描述符到IP地址 */

	/* 设置允许连接的最大客户端数 */
	if (listen(sockfd, 5) == -1)
	{
		fprintf(stderr, "Listen error:%s\n\a", strerror(errno));
		exit(1);
	}


	/* 服务器阻塞,直到客户程序建立连接 */
	sin_size = sizeof(struct sockaddr_in);
	new_fd = accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size);
	cout<<"连接成功等待输入并接收命令字符串"<<endl;
	if (new_fd == -1)
	{
		fprintf(stderr, "Accept error:%s\n\a", strerror(errno));
		exit(1);
	}
	char recvbuf[512] = { 0 };
	char sendbuf[512] = { 0 };
	while (1)
	{
		//等待接受字符串，也就是等待命令的输入
		cout<<"等待接收命令字符串"<<endl;
		int len = recv(new_fd, recvbuf,  512, 0);
		string tmp(recvbuf);
		cout<<"接受字符串，等待书写结果集："<<recvbuf<<endl;

		//执行传输过来的字符串并且解析成命令行命令并执行制作成结果集文件等待传输
		//核心就是popen函数
		FILE   *stream;  
   		FILE    *wstream;
   		char   buf[1024]; 
     
    		memset( buf, '\0', sizeof(buf) );//初始化buf,以免后面写如乱码到文件中
    		stream = popen( tmp.c_str(), "r" ); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
    		wstream = fopen( "result.txt", "w+"); //新建一个可写的文件

    		fread( buf, sizeof(char), sizeof(buf),  stream);  //将刚刚FILE* stream的数据流读取到buf中
    		fwrite( buf, 1, sizeof(buf), wstream );//将buf中的数据写到FILE    *wstream对应的流中，也是写到文件中
    
    		pclose( stream );  
    		fclose( wstream );
		cout<<"结果集书写完毕"<<endl;
		system("iconv result.txt -f UTF-8 -t GBK -o resultfile.txt ");



		FILE *fp;
		fp=fopen("resultfile.txt","r");
		int count=0;
		//传输结果集文件
		while (1)
		{
			//fseek(fp,0,SEEK_SET);
			//memset(sendbuf, 0, 512);//这句话是否有必要还有待考究
			int len = fread(sendbuf, 1, 512,fp );
			send(new_fd, sendbuf, len, 0);
			//cout<<"传输中"<<count<<endl;
			cout<<sendbuf<<endl;
			count++;
			cout<<"count:"<<count<<endl;
			//	printf("sendBuf:%c\n",* sendBuf);
			//	printf("len:%d\n", len);
			if (Judge(sendbuf,512))
			{
				cout<<"退出"<<endl;
				//send(new_fd,sendbuf,len,0);//发送全空字符串？！
				break;
			}
			memset(sendbuf, 0, 512);
		}

		//接收什么样的字符串才结束这个程序？
		//if ()
		//	break;

		cout<<"结果集传输完毕"<<endl;
		memset(recvbuf, 0, 512);
	}
	cout<<"传输完毕"<<endl;
	/* 结束通讯 */
	close(new_fd);
	close(sockfd);
	exit(0);
}
