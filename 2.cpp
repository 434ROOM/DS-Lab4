#include<iostream>
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

int Compare(BiTree T1, BiTree T2)
{//判断两棵二叉树是否相等，不相等返回0，相等返回1
	if (T1 == NULL && T2 == NULL)
	{
		return 1;
	}
	else if (T1 == NULL || T2 == NULL)
	{
		return 0;
	}
	else if (T1->data != T2->data)
	{
		return 0;
	}
	else
	{
		return Compare(T1->lchild, T2->lchild) & Compare(T1->rchild, T2->rchild);
	}
}


int main()
{
	char S1[100], S2[100];
	while (cin >> S1 && S1[0] != '0')
	{
		cin >> S2;
		int i = -1, j = -1;
		BiTree T1, T2;
		CreateBiTree(T1, S1, ++i);
		CreateBiTree(T2, S2, ++j);
		if (!Compare(T1, T2))
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
	}
	return 0;
}
