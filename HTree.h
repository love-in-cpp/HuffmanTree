/*
 Filename: HTree.h
 Description: HTree�ຯ��������
 Author: ������
 Date: 2020/11/30
 Course:���ݽṹ
*/
#pragma once
#include "string.h"
typedef struct  {
	int weight;//Ȩֵ
	int parent, lchild, rchild;//�α�
	char ch;
}Node,*HuffmanTree;
/*
*typedef struct  {}Node,*HuffmanTree;
*��ͬ��:
*typedef struct Node;
*typedef struct Node* HuffmanTree;
*/

typedef char* HuffmanCode;//HuffmanCode=char* 

class HTree {
public:
	HTree(int w[], int n);//���캯��������w[n]�����������
	friend void Select(Node data[], int n, int& i1, int& i2);//��Ԫ����

private:
	int n;//Ҷ�ӽ����
	HuffmanTree huffTree;//��������ָ�룬ָ��2n-1���������
	HuffmanCode* huffmanCode;//����ָ��ָ�����������ռ�
	void Creat(int w[], int n);//������������
	void PrintHuffTree();//��ӡ��������
	void EnCode();//������������
	void PrintHuffCode();//��ӡ����������
	void DeCode();//����
};
