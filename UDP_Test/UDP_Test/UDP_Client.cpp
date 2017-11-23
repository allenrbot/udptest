// UDP_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>  
#include <WINSOCK2.H>  
#include <iostream>
#include <vector>

using namespace std;
#pragma comment(lib,"WS2_32.lib")  
#define BUF_SIZE    64 
struct Data
{
	float x;
	float y;
	float data[2];
};
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsd;
	SOCKET  s;

	// 初始化套接字动态库  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed !/n");
		return 1;
	}

	// 创建套接字  
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET)
	{
		printf("socket() failed, Error Code:%d/n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	char        buf[BUF_SIZE];  // 接受数据  
	SOCKADDR_IN servAddr;       // 服务器套接字地址  
	SOCKET      sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	int         nRet;

	ZeroMemory(buf, BUF_SIZE);
	//strcpy(buf, "UDP Hello World !");

	// 设置服务器地址  
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(8888);
	int nServAddLen = sizeof(servAddr);
	Data data;
	data.data[0] = 0;
	data.data[1] = 1;

	data.x = 0.5;
	data.y = 0.6;
	char *pPack = (char *)&data;
	while (1)
	{
		
		//cin >> buf;
		// 向服务器发送数据  
		//cout << data.data[1] << endl;
		if (sendto(sockClient, (char*)&data, sizeof(Data) + 1, 0, (sockaddr *)&servAddr, nServAddLen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed:%d/n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return 1;
		}
		Sleep(1000);
		cout << "Send data!" << endl;
		/*
		nRet = recvfrom(sockClient, buf, BUF_SIZE, 0, (sockaddr *)&servAddr, &nServAddLen);
		if (SOCKET_ERROR == nRet)
		{
			printf("recvfrom failed !/n");
			closesocket(s);
			WSACleanup();
			return -1;
		}
		
		// 打印来自服务端发送来的数据  
		printf("Recv From Server:%s/n", buf);
		cout << endl;
		*/
	}

	closesocket(s);
	WSACleanup();

	int i;
	cin >>i ;
	return 0;
}

