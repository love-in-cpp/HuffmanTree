/*
 Filename: HTree.cpp
 Description: HTree类函数的实现
 Author: 剑断了
 Date: 2020/12/9
 Course:数据结构
*/
#include "HTree.h"
#include<iostream>
using namespace std;
/*
*HTree 友元函数
*完成从单结点（无双亲的结点）中返回最小的两个结点的下标
*@param data[], 树的结点数组
*@param n, 树的结点数组的长度
*@param &i1, 第一个下标最小的单结点
*@param &i2, 第二个下标最小的单结点
*@returns nothing
*/
void Select(Node data[], int n, int &i1, int &i2)
{
	
	int i = 0;//标记 i
	int min = 0;//记录最小权值
	
	for (i = 0; i < n; i++)//遍历全部结点，找出单节点
	{
		if (data[i].parent == -1)//如果此结点的父亲没有，那么把结点号赋值给 min，跳出循环
		{
			min = i;
			break;
		}
	}
	
	for (i = 0; i < n; i++)//继续遍历全部结点，找出权值最小的单节点
	{
		if (data[i].parent == -1)//如果此结点的父亲为空，则进入 if
		{
			if (data[i].weight < data[min].weight)//如果此结点的权值比 min 结点的权值小，那么更新 min 结点，否则就是最开始的 min
			{
				min = i;
			}
		}
	}

	i1 = min;//找到了最小权值的结点，i1指向

	for (i = 0; i < n; i++)//遍历全部结点
	{
		if (data[i].parent == -1 && i != i1)//找出下一个单节点，且没有被 i1指向，那么i 赋值给 min，跳出循环
		{
			min = i;
			break;
		}
	}
	
	for (i = 0; i < n; i++)//继续遍历全部结点，找到权值最小的那一个
	{
		if (data[i].parent == -1 && i != i1)
		{
			if (data[i].weight < data[min].weight)//如果此结点的权值比 min 结点的权值小，那么更新 min 结点，否则就是最开始的 min
			{
				min = i;
			}
		}
	}
	i2 = min;//i2指针指向第二个权值最小的叶子结点
}
/*
*HTree 构造函数
*完成动态数组堆内存的分配以及HTree方法的调用
*@param w[], 树的叶子结点数组w[n]d
*@param n, 树的叶子结点数组的长度
*@returns nothing
*/
HTree::HTree(int w[], int n)
{
	this->n = n;
	huffTree = new Node[2 * n - 1]();
	huffmanCode = new HuffmanCode[n]();//huffmanCode是二级指针，指向一片char*型数组,char*p1用来指向char型数组，数组存放n-start个二进制码
	//huffTree[2*n-1] = { 0 };
	Creat(w, n);
	EnCode();
	PrintHuffCode();
	DeCode();
}
/*
*HTree 创建哈夫曼树的方法
*完成哈夫曼树的构造和储存
*@param w[], 树的叶子结点数组w[n]d
*@param n, 树的叶子结点数组的长度
*@returns nothing
*/
void HTree::Creat(int w[], int n)
{
	int i, j, i1, i2;
	char a = 97;
	cout << "****************二叉树构造过程******************" << endl;
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

		Select(huffTree, j, i1, i2);//输入一个ElemType类型的数组，j控制新的组合数加入集合T，返回权值最小的两个下标，分别赋给i1,i2;
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
*HTree 打印哈夫曼树的方法
*完成哈夫曼树的控制台输出
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
*HTree 编码哈夫曼树的方法
*完成哈夫曼树的二进制编码
*@param nothing
*@returns nothing
*/
void HTree::EnCode()
{
	cout << "****************Encode******************" << endl;
	int i;//指示标记
	int start;//倒序编码标记
	int p;//指向当前结点的双亲结点
	int c;//遍历n个结点的标记
	//huffmanCode = new HuffmanCode[n];//huffmanCode是二级指针，指向一片char*型数组,char*p1用来指向char型数组，数组存放n-start个二进制码
	char* cd = new char[n];//指针cd指向char数组
	cd[n - 1] = '\0';//用来暂时存放二进制码的数组，给数组最后一个做标记  '\0'，倒序存放二进制数
	for (i = 0; i < n; i++)
	{//从第一个叶子结点开始，遍历所有叶子结点，求每个叶子结点的二进制编码
		start = n - 1;//start是数组cd的下标，当前下标指向cd的最后一个元素，即'\0'
		for (c = i, p = huffTree[i].parent; p != -1; c = p, p = huffTree[p].parent)//从叶子结点向上遍历，找到结点的双亲，再判断当前结点是双亲的左孩子还是右孩子
		{
			if (huffTree[p].lchild == c)
			{
				start--;//n-2 n-3...找到几次叶子结点的双亲就--几次，也就产生几次二进制数
				cd[start] = '0';//倒序存放
			}
			else
			{
				start--;
				cd[start] = '1';
			}
		}
		huffmanCode[i] = new char[n - start];//给一级指针即char*指针分配指向，指向n-start个char型数组的首地址
		strcpy(huffmanCode[i], &cd[start]);//从数组cd有效下标start开始，把内容复制给huffmanCode[i]
	}
	delete cd;
}
/*
*HTree 打印哈夫曼树编码的方法
*完成哈夫曼树编码的控制台输出
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
*HTree 解码哈夫曼树编码的方法
*完成哈夫曼树的二进制编码的解码
*@param nothing
*@returns nothing
*/
void HTree::DeCode()
{
	cout << "****************Decode******************" << endl;
	int start = 2 * n - 2;//从头结点往下遍历
	char* p;//工作指针
	int current = 0;//记录当前遍历到的叶子结点
	for (int i = 0; i < n; i++)//解码n个叶子结点
	{
		p = huffmanCode[i];//一级指针p，指向char型数组
		start = 2 * n - 2;//每完成一次解码就重置根节点位置
		for (int j = 0; p[j] != '\0'; j++)//编码不为'\0'则继续向下遍历
		{
			
			if (p[j] == '0')//二进制码为0
			{
				start = huffTree[start].lchild;//访问根节点的左孩子
				cout << p[j];//输出当前二进制码
			}
			if (p[j] == '1')
			{
				start = huffTree[start].rchild;//访问根节点的右孩子
				cout << p[j];
			}
		}
		current = start;//记录叶子结点
		cout <<':' <<huffTree[current].ch << endl;//输出叶子结点的符号，完成一次解码
	}

}