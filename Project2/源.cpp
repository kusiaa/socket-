#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<WinSock2.h>
#include <sstream>
using namespace std;
char bit4ToHex(string s);
int count(char a, char b, char c, char d);
void hanzi(int a);
char sou[320] = { 0 };
void trans(double a[], double b[],int c);
int main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);
	int serverSocket;
	struct sockaddr_in sad;
    #define MESSAGE_LEN 4000
	char message[MESSAGE_LEN] = { 0 };
	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(&sad, 0, sizeof(sad));
	sad.sin_family = AF_INET;
	sad.sin_addr.s_addr = inet_addr("127.0.0.1");
	sad.sin_port = htons(12000);
	bind(serverSocket, (struct sockaddr*)&sad, sizeof(sad));
	printf("等待客户端连接\n");
	struct sockaddr_in cad;
	memset(&cad, 0, sizeof(cad));
	int clientAddrLen = sizeof(struct sockaddr);
	int ret = recvfrom(serverSocket, message, MESSAGE_LEN, 0, (struct sockaddr*)&cad, &clientAddrLen);
	int l = strlen(message);//接收另一个主机发来的字符
	int flag = 0; int number = 0;
	stringstream ss; double end[1000] = { 0 }; int count = 0;
	for (int i = 0; i < l; i++)
	{
		if (message[i] == 'A')
		{
			number = i;
			for (int j = flag; j < number; j++)
			{
				ss.clear();
				ss << message[j];
			}
			ss >> end[count++];
			flag = i + 1;
		}
	}
	ss.clear();
	//将收到的字符串转换成double数组
	double time[1000] = { 0 };
	for (int i = 0; i < count; i++)
	 {
		 time[i] = 0.1 * i;
	 }
	//储存解调信号的时间值
	double solution1[1000] = { 0 };
	double solution2[1000] = { 0 };
	//储存处理过后的IQ两路信号
	for (int i = 0; i < count; i++)
	{
		solution1[i] = end[i] * cos(2*3.14159 * time[i]);
	}
	for (int i = 0; i < count; i++)
	{
		solution2[i] = end[i] * sin(2*3.14159 * time[i])*(-1);
	}
	for (int i = 0; i < count; i++)
	{
		cout << solution1[i] << endl;
	}
	//解调IQ两路信号
	double cat1[200] = { 0 };
	double cat2[200] = { 0 };
	trans(solution1,cat1, count);
	trans(solution2, cat2,count);
	double cat3[400] = { 0 }; int v = 0;
	for (int i = 0; i < count / 10; i++)
	{
		cat3[v++] = cat1[i];
		cat3[v++] = cat2[i];
	}
	string tt;
	for (int i = 0; i < count / 5; i++)
	{
		ss << cat3[i];
	}
	ss >> tt;
	for (int i = 0; i < count / 5; i++)
	{
		sou[i] = tt[i];
	}
	int h;
	h = strlen(sou);
	
	if (h % 16 == 0)
	{
		h = h / 16;
	}
	else h = h / 16 + 1;
	cout << "收到的消息为：";
	for (int i = 0; i < h; i++)
	{
		hanzi(i);		
	}
	
}
void hanzi(int a)
{
	char sou1[16] = { 0 };
	for (int g = 0; g < 16; g++)
	{
		sou1[g] = sou[g + a * 16];
	}
	string s1, s2, s3, s4;
	char shuzhu1[5] = { 0 };
	char shuzhu2[5] = { 0 };
	char shuzhu3[5] = { 0 };
	char shuzhu4[5] = { 0 };
	for (int k = 0; k < 16; k++)
	{
		if (k < 4 && k >= 0)
		{
			shuzhu1[k] = sou1[k];
		}
		if (k < 8 && k >= 4)
		{
			shuzhu2[k - 4] = sou1[k];
		}
		if (k < 12 && k >= 8)
		{
			shuzhu3[k - 8] = sou1[k];
		}
		if (k < 16 && k >= 12)
		{
			shuzhu4[k - 12] = sou1[k];
		}
	}
	s1 = shuzhu1; s2 = shuzhu2; s3 = shuzhu3; s4 = shuzhu4;
	char q = bit4ToHex(s1);
	char w = bit4ToHex(s2);
	char e = bit4ToHex(s3);
	char r = bit4ToHex(s4);
	//char x1[5] = { e,r,q,w ,0};
	int x1 = 0;
	x1 = count(q, w, e, r);
	int* x2 = &x1;
	printf("%s", (char*)x2);
}

int count(char a, char b, char c, char d)
{
	if (a > 57)
	{
		a = a - 55;
	}
	else
	{
		a = a - 48
			;
	}
	if (b > 57)
	{
		b = b - 55;
	}
	else
	{
		b = b - 48
			;
	}
	if (c > 57)
	{
		c = c - 55;
	}
	else
	{
		c = c - 48
			;
	}
	if (d > 57)
	{
		d = d - 55;
	}
	else
	{
		d = d - 48
			;
	}
	int number = c * 16 * 16 * 16 + d * 16 * 16 + a * 16 + b;
	return number;
}
char bit4ToHex(string s)
{
	if (s.size() != 4)
	{
		return ' ';
	}
	if (s.find_first_not_of("01") != string::npos)
	{
		return ' ';
	}
	int t = (s[0] * 1 - 48) * 8 + (s[1] * 1 - 48) * 4 + (s[2] * 1 - 48) * 2 + (s[3] * 1 - 48) * 1;
	char ch = ' ';
	switch (t) {
	case 10:
		ch = 'A';
		break;
	case 11:
		ch = 'B';
		break;
	case 12:
		ch = 'C';
		break;
	case 13:
		ch = 'D';
		break;
	case 14:
		ch = 'E';
		break;
	case 15:
		ch = 'F';
		break;
	default:
		ch = char(t + 48);
	}

	return ch;
}
void trans(double a[],double b[], int c)
{
	c = c / 10; 
	int j = 0;
	
	for (int i = 0; i < c; i++)
	{
		b[i] = a[j] + a[j + 1] + a[j + 2] + a[j + 3] + a[j + 4] + a[j + 5] + a[j + 6] + a[j + 7] + a[j + 8] + a[j + 9];
		j = j + 10; 
		if (b[i] > 1)
			b[i] = 1;
		else b[i] = 0;
	}	
}








