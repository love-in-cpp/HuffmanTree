/*
 Filename: HMain.cpp
 Description: 哈夫曼树实现的函数入口
 Author: 剑断了
 Date: 2020/11/30
 Course:数据结构
*/
#include<iostream>
#include"HTree.h"
using namespace std;
const int passageMaxSize = 1000;//控制文章最大长度
int main() {
//#if(0)
	int count = 97;//97是ASCII码的a，例如char c=count; 再输出c 那么会得到字符'a',count++可以得到bcd...以此类推
	double length = 0;//统计输入数据的长度，即输入了多少个小写字母
	char character[26];//用于存放26个小写字母
	char passage[passageMaxSize];//文章最长长度，默认为1000
	/*
	*给character[26]数组每个元素赋值(a, b, c, d, e, f...)
	*/
	for (int i = 0; i < 26; i++) 
	{
		character[i] = count;
		count++;
	}
	count = 97;
	/*
	*从键盘接收字符信息，并得到过滤非小写字母信息的字长
	*/
	cout << "请输入一段小写英文序列(允许空格缩进)并以#号结束:";
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
	*得到每个字母出现的频数和频率
	*/
	double p[26] = {0};
	int pcount[26] = {0};//字母在文章出现的频数，要给每个元素初始化为0
	for (int i = 0; i < 26; i++) 
	{//遍历字母，求出每个字母的概率
		for (int j = 0; j < length; j++) 
		{//遍历文章
			if (passage[j] == count)
				pcount[i]++;//字母出现的次数自增
		}
		count++;
		if(length!=0)
		p[i] = pcount[i] / length;//得到概率
	}
	/*
	*输出对输入字段的一阶统计 即频率和概率
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
	*将每个字母出现的频数作为初始数据建立二叉树
	*/
	cout << "**********传入二叉树的序列***************" << endl;
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