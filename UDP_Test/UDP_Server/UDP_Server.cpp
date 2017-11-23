// UDP_Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>  
#include <WINSOCK2.H>  
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
#pragma comment(lib,"WS2_32.lib")  
#define  BUF_SIZE 4096

struct Scan
{
	float ranges[720];
	float angle_min;
	float angle_max;
	float range_min;
	float range_max;
	float angle_increment;

};

struct Data
{
	float x;
	float y;
	float data[2];
}; 
int GetServerAddr(char * addrname)
{
	printf("please input server addr:");
	scanf("%s", addrname);
	return 1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsd;
	SOCKET  s;
	int     nRet;

	// ��ʼ���׽��ֶ�̬��  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed !/n");
		return 1;
	}

	// �����׽���  
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET)
	{
		printf("socket() failed ,Error Code:%d/n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	SOCKET      socketSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	SOCKADDR_IN addrClient;
	char        buf[BUF_SIZE];
	int         len = sizeof(SOCKADDR);

	// ���÷�������ַ  
	ZeroMemory(buf, BUF_SIZE);
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5000);

	// ���׽���  
	nRet = bind(socketSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("bind failed !/n");
		closesocket(s);
		WSACleanup();
		return -1;
	}
	//Data data;
	//data.data[0] = 0;
	//data.data[1] = 0;
	Scan data;
	while (1)
	{
		//data.ranges.clear();
		//data.ranges.resize(720);
		// �ӿͻ��˽�������  
		nRet = recvfrom(socketSrv, buf, BUF_SIZE, 0, (SOCKADDR*)&addrClient, &len);
		if (SOCKET_ERROR == nRet)
		{
			printf("recvfrom failed !/n");
			closesocket(s);
			WSACleanup();
			return -1;
		}
		memcpy(&data, buf, sizeof(data) + 1);
		// ��ӡ���Կͻ��˷�����������  
		//printf("Recv From Client:%s", buf);
		//cout << endl;
		// ��ͻ��˷�������  
		//sendto(socketSrv, "UDP Hello World !", sizeof("UDP Hello World !"), 0, (SOCKADDR*)&addrClient, len);
		//cout <<"Data 1:"<<data.x<<", Data 2: "<<data.y<< endl;
		cout << "range:" << data.ranges[720] << endl;
	}

	closesocket(s);
	WSACleanup();
	int i;
	cin >> i;
	return 0;
}

