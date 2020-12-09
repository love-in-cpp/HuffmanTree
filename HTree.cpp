/*
 Filename: HTree.cpp
 Description: HTree�ຯ����ʵ��
 Author: ������
 Date: 2020/12/9
 Course:���ݽṹ
*/
#include "HTree.h"
#include<iostream>
using namespace std;
/*
*HTree ��Ԫ����
*��ɴӵ���㣨��˫�׵Ľ�㣩�з�����С�����������±�
*@param data[], ���Ľ������
*@param n, ���Ľ������ĳ���
*@param &i1, ��һ���±���С�ĵ����
*@param &i2, �ڶ����±���С�ĵ����
*@returns nothing
*/
void Select(Node data[], int n, int &i1, int &i2)
{
	
	int i = 0;//��� i
	int min = 0;//��¼��СȨֵ
	
	for (i = 0; i < n; i++)//����ȫ����㣬�ҳ����ڵ�
	{
		if (data[i].parent == -1)//����˽��ĸ���û�У���ô�ѽ��Ÿ�ֵ�� min������ѭ��
		{
			min = i;
			break;
		}
	}
	
	for (i = 0; i < n; i++)//��������ȫ����㣬�ҳ�Ȩֵ��С�ĵ��ڵ�
	{
		if (data[i].parent == -1)//����˽��ĸ���Ϊ�գ������ if
		{
			if (data[i].weight < data[min].weight)//����˽���Ȩֵ�� min ����ȨֵС����ô���� min ��㣬��������ʼ�� min
			{
				min = i;
			}
		}
	}

	i1 = min;//�ҵ�����СȨֵ�Ľ�㣬i1ָ��

	for (i = 0; i < n; i++)//����ȫ�����
	{
		if (data[i].parent == -1 && i != i1)//�ҳ���һ�����ڵ㣬��û�б� i1ָ����ôi ��ֵ�� min������ѭ��
		{
			min = i;
			break;
		}
	}
	
	for (i = 0; i < n; i++)//��������ȫ����㣬�ҵ�Ȩֵ��С����һ��
	{
		if (data[i].parent == -1 && i != i1)
		{
			if (data[i].weight < data[min].weight)//����˽���Ȩֵ�� min ����ȨֵС����ô���� min ��㣬��������ʼ�� min
			{
				min = i;
			}
		}
	}
	i2 = min;//i2ָ��ָ��ڶ���Ȩֵ��С��Ҷ�ӽ��
}
/*
*HTree ���캯��
*��ɶ�̬������ڴ�ķ����Լ�HTree�����ĵ���
*@param w[], ����Ҷ�ӽ������w[n]d
*@param n, ����Ҷ�ӽ������ĳ���
*@returns nothing
*/
HTree::HTree(int w[], int n)
{
	this->n = n;
	huffTree = new Node[2 * n - 1]();
	huffmanCode = new HuffmanCode[n]();//huffmanCode�Ƕ���ָ�룬ָ��һƬchar*������,char*p1����ָ��char�����飬������n-start����������
	//huffTree[2*n-1] = { 0 };
	Creat(w, n);
	EnCode();
	PrintHuffCode();
	DeCode();
}
/*
*HTree �������������ķ���
*��ɹ��������Ĺ���ʹ���
*@param w[], ����Ҷ�ӽ������w[n]d
*@param n, ����Ҷ�ӽ������ĳ���
*@returns nothing
*/
void HTree::Creat(int w[], int n)
{
	int i, j, i1, i2;
	char a = 97;
	cout << "****************�������������******************" << endl;
	for (i = 0; i < 2 * n - 1; i++)
	{
		huffTree[i].parent = -1;
		huffTree[i].lchild = huffTree[i].rchild = -1;
	}
	for (i = 0; i < n; i++, a++)
	{
		huffTree[i].weight = w[i];
		huffTree[i].ch = a;
	}
	for (j = n; j < 2 * n - 1; j++)
	{

		Select(huffTree, j, i1, i2);//����һ��ElemType���͵����飬j�����µ���������뼯��T������Ȩֵ��С�������±꣬�ֱ𸳸�i1,i2;
		huffTree[j].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[j].lchild = i1;
		huffTree[j].rchild = i2;
		huffTree[i1].parent = huffTree[i2].parent = j;
		/*printf("%d (%d, %d)\n", huffTree[j].weight,
			huffTree[i1].weight, huffTree[i2].weight);*/
		cout << huffTree[j].weight << '(' << huffTree[i1].weight << ',' << huffTree[i2].weight << ')' << endl;
	}
	cout << endl;
}
/*
*HTree ��ӡ���������ķ���
*��ɹ��������Ŀ���̨���
*@param nothing
*@returns nothing
*/
void HTree::PrintHuffTree()
{
	for (int i = n; i < 2 * n - 1; i++)
	{
		cout << huffTree[i].weight << '(' << huffTree[huffTree->lchild].weight << ',' << huffTree[huffTree->rchild].weight << ')' << endl;
	}
}
/*
*HTree ������������ķ���
*��ɹ��������Ķ����Ʊ���
*@param nothing
*@returns nothing
*/
void HTree::EnCode()
{
	cout << "****************Encode******************" << endl;
	int i;//ָʾ���
	int start;//���������
	int p;//ָ��ǰ����˫�׽��
	int c;//����n�����ı��
	//huffmanCode = new HuffmanCode[n];//huffmanCode�Ƕ���ָ�룬ָ��һƬchar*������,char*p1����ָ��char�����飬������n-start����������
	char* cd = new char[n];//ָ��cdָ��char����
	cd[n - 1] = '\0';//������ʱ��Ŷ�����������飬���������һ�������  '\0'�������Ŷ�������
	for (i = 0; i < n; i++)
	{//�ӵ�һ��Ҷ�ӽ�㿪ʼ����������Ҷ�ӽ�㣬��ÿ��Ҷ�ӽ��Ķ����Ʊ���
		start = n - 1;//start������cd���±꣬��ǰ�±�ָ��cd�����һ��Ԫ�أ���'\0'
		for (c = i, p = huffTree[i].parent; p != -1; c = p, p = huffTree[p].parent)//��Ҷ�ӽ�����ϱ������ҵ�����˫�ף����жϵ�ǰ�����˫�׵����ӻ����Һ���
		{
			if (huffTree[p].lchild == c)
			{
				start--;//n-2 n-3...�ҵ�����Ҷ�ӽ���˫�׾�--���Σ�Ҳ�Ͳ������ζ�������
				cd[start] = '0';//������
			}
			else
			{
				start--;
				cd[start] = '1';
			}
		}
		huffmanCode[i] = new char[n - start];//��һ��ָ�뼴char*ָ�����ָ��ָ��n-start��char��������׵�ַ
		strcpy(huffmanCode[i], &cd[start]);//������cd��Ч�±�start��ʼ�������ݸ��Ƹ�huffmanCode[i]
	}
	delete cd;
}
/*
*HTree ��ӡ������������ķ���
*��ɹ�����������Ŀ���̨���
*@param nothing
*@returns nothing
*/
void HTree::PrintHuffCode()
{

	for (int i = 0; i < n; i++)
	{
		cout << huffTree[i].ch << ':' << huffmanCode[i] << endl;
	}
}
/*
*HTree ���������������ķ���
*��ɹ��������Ķ����Ʊ���Ľ���
*@param nothing
*@returns nothing
*/
void HTree::DeCode()
{
	cout << "****************Decode******************" << endl;
	int start = 2 * n - 2;//��ͷ������±���
	char* p;//����ָ��
	int current = 0;//��¼��ǰ��������Ҷ�ӽ��
	for (int i = 0; i < n; i++)//����n��Ҷ�ӽ��
	{
		p = huffmanCode[i];//һ��ָ��p��ָ��char������
		start = 2 * n - 2;//ÿ���һ�ν�������ø��ڵ�λ��
		for (int j = 0; p[j] != '\0'; j++)//���벻Ϊ'\0'��������±���
		{
			
			if (p[j] == '0')//��������Ϊ0
			{
				start = huffTree[start].lchild;//���ʸ��ڵ������
				cout << p[j];//�����ǰ��������
			}
			if (p[j] == '1')
			{
				start = huffTree[start].rchild;//���ʸ��ڵ���Һ���
				cout << p[j];
			}
		}
		current = start;//��¼Ҷ�ӽ��
		cout <<':' <<huffTree[current].ch << endl;//���Ҷ�ӽ��ķ��ţ����һ�ν���
	}

}