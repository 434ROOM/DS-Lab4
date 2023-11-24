#include<iostream>
#include<string.h>
using namespace std;

typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

void CreateBiTree(BiTree& T, char S[], int& i)
{////������������
	if (S[i] == '0')
	{
		T = NULL;
		i++;
	}
	else
	{
		T = new BiTNode;
		T->data = S[i];
		i++;
		CreateBiTree(T->lchild, S, i);
		CreateBiTree(T->rchild, S, i);
	}
}

void Count(BiTree T, int& a, int& b, int& c)
{
	//��������������ͳ��
	//a,b,c�ֱ�Ϊ�������Ķ�Ϊ0��1��2�Ľ�����
	if (T == NULL)
	{
		return;
	}
	if (T->lchild == NULL && T->rchild == NULL)
	{
		a++;
	}
	else if (T->lchild != NULL && T->rchild != NULL)
	{
		c++;
	}
	else
	{
		b++;
	}
	Count(T->lchild, a, b, c);
	Count(T->rchild, a, b, c);
}