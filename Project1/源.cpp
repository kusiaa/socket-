#include<stdio.h>
#include<cstdio>
#include<cstdlib>
#include<stdlib.h>
#include<iostream>
#include<winsock.h>
#include <sstream>
using namespace std;
int main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

    #define MESSAGE_LEN 5000
	
	int clientSocket;

	struct sockaddr_in sad;
	int serveraddrLen = sizeof(sad);
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(12000);

	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	printf("请输入发送到服务端的内容 : ");
	
    char a[320];//用来存储输入的汉字
	char buf[16];//一个汉字占据16个二进制位
	char sou[320] = { 0 };//储存汉字转换后的二进制代码
	int i = 0; int d = 0;
	cin >> a;
    double result[3000] = { 0 };//储存调制后的码元

	while (*(a + i))
	{

		_itoa_s(0xff & a[i++], buf, 2);
		for (int z = 0; z < 8; z++)
		{
			sou[d] = buf[z];
			d++;

		}
	}
	/// 汉字转化为二进制码元，利用的是GB18030编码
	double number[1000] = { 0 }; double number1[1000] = { 0 };
	int flag = strlen(sou);
	if (flag % 16 == 0)
	{
		flag = flag / 16;
	}
	else flag = flag / 16 + 1;
	//计算汉字个数

	for (int i = 0; i < flag * 8*10; i++)
	{
		number[i] = 0.1 * i;
	}
	for (int i = 0; i < flag * 8* 10; i++)
	{
		number1[i] = 0.1 * i;
	}
	//储存时间值，这里的表示为一个码元周期为1，抽样周期为码元周期的十分之一
	double ji[2000] = { 0 };
	double ou[2000] = { 0 };
	double w = 2*3.14159;
	int j = 0; int k = 0; int g = 0;
	for (int i = 0; i < flag * 16; i++)
	{
		if (i % 2 == 0)
		{   
			while(1)
			{
				ji[j] = ((sou[i] - 48) * 2 - 1) * cos(w * number[j]);
				g++; j++;
				if (g == 10)
				{   g = 0;
					break;
					
				}
			}
		}
		if(i%2==1)
		{
			while (1)
			{
				ou[k] = ((sou[i] - 48) * 2 - 1) * sin(w * number1[k]);
				g++; k++;
				if (g == 10)
				{   g = 0;
					break;
					
				}
			}
			
		}
	}
	//这里起到的作用是将01码元转换成为1 -1码元的同时乘上载波进行调制，还将码元的数量扩大了十倍，并同时进行IQ分路

	

	for (int i = 0; i < flag * 16*5; i++)
	{
		result[i] = ji[i] - ou[i];
	}//将调制后的码元存放在result数组内
	
	for (int i = 0; i < flag * 8 * 10; i++)
	{
		cout << result[i] << endl;
	}
	stringstream ss; string s1; string s2;
	char de[4000] = { 0 };
	for (int i = 0; i < 8* flag*5; i++)
	{  
		ss << result[i];
		ss << 'A';

	}
	ss.clear();
	ss >> s1;
	stringstream ss1;
	for (int i = 8 * flag * 5; i < 8 * flag * 10; i++)
	{
		ss1<< result[i];
		ss1<< 'A';

	}
	 ss1 >> s2;
	 ss1.clear();
	 int m = s1.length();
	 int o=s2.length();
	 int h = 0;
	for(int i=0;i<m;i++)
	{
		de[h] = s1[i];
		h++;
      
	}
	for (int i = 0; i < o ; i++)
	{
		de[h] = s2[i];
		h++;
	}
	sendto(clientSocket, de, strlen(de), 0, (struct sockaddr*)&sad, sizeof(sad));
	closesocket(clientSocket); //关闭连接
	WSACleanup();   //清理网络环境
					
}

	
	






