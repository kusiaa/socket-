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

	printf("�����뷢�͵�����˵����� : ");
	
    char a[320];//�����洢����ĺ���
	char buf[16];//һ������ռ��16��������λ
	char sou[320] = { 0 };//���溺��ת����Ķ����ƴ���
	int i = 0; int d = 0;
	cin >> a;
    double result[3000] = { 0 };//������ƺ����Ԫ

	while (*(a + i))
	{

		_itoa_s(0xff & a[i++], buf, 2);
		for (int z = 0; z < 8; z++)
		{
			sou[d] = buf[z];
			d++;

		}
	}
	/// ����ת��Ϊ��������Ԫ�����õ���GB18030����
	double number[1000] = { 0 }; double number1[1000] = { 0 };
	int flag = strlen(sou);
	if (flag % 16 == 0)
	{
		flag = flag / 16;
	}
	else flag = flag / 16 + 1;
	//���㺺�ָ���

	for (int i = 0; i < flag * 8*10; i++)
	{
		number[i] = 0.1 * i;
	}
	for (int i = 0; i < flag * 8* 10; i++)
	{
		number1[i] = 0.1 * i;
	}
	//����ʱ��ֵ������ı�ʾΪһ����Ԫ����Ϊ1����������Ϊ��Ԫ���ڵ�ʮ��֮һ
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
	//�����𵽵������ǽ�01��Ԫת����Ϊ1 -1��Ԫ��ͬʱ�����ز����е��ƣ�������Ԫ������������ʮ������ͬʱ����IQ��·

	

	for (int i = 0; i < flag * 16*5; i++)
	{
		result[i] = ji[i] - ou[i];
	}//�����ƺ����Ԫ�����result������
	
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
	closesocket(clientSocket); //�ر�����
	WSACleanup();   //�������绷��
					
}

	
	






