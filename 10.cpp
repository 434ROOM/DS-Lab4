#include<iostream>
#include <string.h>
using namespace std;
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

void CreateBiTree(BiTree& T, char S[], int& i)
{////先序建立二叉树
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

int Depth(BiTree T)
{//二叉树高度的计算
	if (T == NULL)
	{
		return 0;
	}
	int l = Depth(T->lchild);
	int r = Depth(T->rchild);
	int deep;
	if (l>r)
	{
		deep = l + 1;
	}
	else
	{
		deep = r + 1;
	}
	return deep;
}

