#include<iostream>
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

void AllPath(BiTree T, char path[], int pathlen)
{//������Ҷ�ӽ�㵽������·�������
	if (T == NULL)
	{
		return;
	}
	path[pathlen] = T->data;
	pathlen++;
	if (T->lchild == NULL && T->rchild == NULL)
	{
		for (int i = pathlen - 1; i >= 0; i--)
		{
			cout << path[i];
		}
		cout << endl;
	}
	else
	{
		AllPath(T->lchild, path, pathlen);
		AllPath(T->rchild, path, pathlen);
	}
}
