/*
 Filename: HMain.cpp
 Description: ��������ʵ�ֵĺ������
 Author: ������
 Date: 2020/11/30
 Course:���ݽṹ
*/
#include<iostream>
#include"HTree.h"
using namespace std;
const int passageMaxSize = 1000;//����������󳤶�
int main() {
//#if(0)
	int count = 97;//97��ASCII���a������char c=count; �����c ��ô��õ��ַ�'a',count++���Եõ�bcd...�Դ�����
	double length = 0;//ͳ���������ݵĳ��ȣ��������˶��ٸ�Сд��ĸ
	char character[26];//���ڴ��26��Сд��ĸ
	char passage[passageMaxSize];//��������ȣ�Ĭ��Ϊ1000
	/*
	*��character[26]����ÿ��Ԫ�ظ�ֵ(a, b, c, d, e, f...)
	*/
	for (int i = 0; i < 26; i++) 
	{
		character[i] = count;
		count++;
	}
	count = 97;
	/*
	*�Ӽ��̽����ַ���Ϣ�����õ����˷�Сд��ĸ��Ϣ���ֳ�
	*/
	cout << "������һ��СдӢ������(����ո�����)����#�Ž���:";
	for (int i = 0;  i < 1000; i++) 
	{
		cin >> passage[i];
		if (passage[i] == '#')
			break;
		if(passage[i]>=97&&passage[i]<=122)
		length++;
	}
	cout << "length:" << length << endl;
	/*
	*�õ�ÿ����ĸ���ֵ�Ƶ����Ƶ��
	*/
	double p[26] = {0};
	int pcount[26] = {0};//��ĸ�����³��ֵ�Ƶ����Ҫ��ÿ��Ԫ�س�ʼ��Ϊ0
	for (int i = 0; i < 26; i++) 
	{//������ĸ�����ÿ����ĸ�ĸ���
		for (int j = 0; j < length; j++) 
		{//��������
			if (passage[j] == count)
				pcount[i]++;//��ĸ���ֵĴ�������
		}
		count++;
		if(length!=0)
		p[i] = pcount[i] / length;//�õ�����
	}
	/*
	*����������ֶε�һ��ͳ�� ��Ƶ�ʺ͸���
	*/
	for (int i = 0; i < 26; i++) 
	{
		cout << character[i]<<":"<<pcount[i] << " ";
	}
	cout << endl;
	cout << fixed;
	cout.precision(4);
	for (int i = 0; i < 26; i++) 
	{
		cout << character[i] << ":" << p[i] << " ";
	}
	cout << endl;
	/*
	*��ÿ����ĸ���ֵ�Ƶ����Ϊ��ʼ���ݽ���������
	*/
	cout << "**********���������������***************" << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << pcount[i] << " ";
	}
	cout << endl;
	HTree h(pcount, 26);
//#endif
	/*int pcount[7] = { 2,3,5,7,8,9,11 };
	cout << "************************" << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << pcount[i] << " ";
	}
	cout << endl;
	cout << "************************" << endl;
	HTree test(pcount, 7);
	*/
	
	return 0;
}