/*
 Filename: HTree.h
 Description: HTree类函数的声明
 Author: 剑断了
 Date: 2020/11/30
 Course:数据结构
*/
#pragma once
#include "string.h"
typedef struct  {
	int weight;//权值
	int parent, lchild, rchild;//游标
	char ch;
}Node,*HuffmanTree;
/*
*typedef struct  {}Node,*HuffmanTree;
*等同于:
*typedef struct Node;
*typedef struct Node* HuffmanTree;
*/

typedef char* HuffmanCode;//HuffmanCode=char* 

class HTree {
public:
	HTree(int w[], int n);//构造函数，传递w[n]构造哈夫曼树
	friend void Select(Node data[], int n, int& i1, int& i2);//友元函数

private:
	int n;//叶子结点数
	HuffmanTree huffTree;//哈夫曼树指针，指向2n-1个结点数组
	HuffmanCode* huffmanCode;//二级指针指向哈夫曼编码空间
	void Creat(int w[], int n);//创建哈夫曼树
	void PrintHuffTree();//打印哈夫曼树
	void EnCode();//创建哈夫曼码
	void PrintHuffCode();//打印哈夫曼编码
	void DeCode();//解码
};
