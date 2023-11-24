#include<iostream>
#define MAXSIZE 100
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

void GetLongest(BiTree T, int& longest)
{
	//二叉树最长路径的求解

	if (T == NULL)
	{
		longest = 0;
		return;
	}
	int l1 = 0, l2 = 0;
	
	GetLongest(T->lchild, l1);
	GetLongest(T->rchild, l2);

	if (l1 > l2)
	{
		longest = l1 + 1;
	}
	else
	{
		longest = l2 + 1;
	}
	return;
}

bool isfind = false;
void GetPath(BiTree T, BiTree path[], int& deep, int longest) {
	if (deep==0)
	{
		isfind = false;
	}
	if (T == NULL || deep == longest) {
		return;
	}

	path[deep + 1] = T;
	deep++;

	if (T->lchild == NULL && T->rchild == NULL && deep == longest) {
		isfind = true;
		return;
	}

	if (!isfind)
	{
		GetPath(T->lchild, path, deep, longest);
	}
	if (!isfind)
	{
		GetPath(T->rchild, path, deep, longest);
	}
	
	if (!isfind)
	{
		deep--;
	}
}


void LongestPath(BiTree T, BiTree l[], int& longest)
{
	//二叉树最长路径的求解
	GetLongest(T, longest);
	int deep = 0;
	GetPath(T, l, deep, longest);
}







int main()
{
	char S[100];
	while (cin >> S && S[0] != '0')
	{
		int i = -1;
		BiTree T;
		BiTree l[MAXSIZE];
		int longest = 0;
		CreateBiTree(T, S, ++i);
		LongestPath(T, l, longest);
		cout << longest << endl;
		for (int k = 1; k <= longest; k++)
			cout << l[k]->data;
		cout << endl;
	}
	return 0;
}

