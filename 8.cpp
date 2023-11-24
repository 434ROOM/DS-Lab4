#include<iostream>
#include<string.h>
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

void PreOrderTraverse(BiTree T)
{//二叉树的先序遍历
	if (T != NULL) {
		// 先访问根节点
		cout << T->data;

		// 递归遍历左子树
		PreOrderTraverse(T->lchild);

		// 递归遍历右子树
		PreOrderTraverse(T->rchild);
	}
}


void InOrderTraverse(BiTree T) {
// 中序遍历
	if (T != NULL) {
		// 递归遍历左子树
		InOrderTraverse(T->lchild);

		// 访问根节点
		cout << T->data;

		// 递归遍历右子树
		InOrderTraverse(T->rchild);
	}
}


void PostOrderTraverse(BiTree T) {
// 后序遍历
	if (T != NULL) {
		// 递归遍历左子树
		PostOrderTraverse(T->lchild);

		// 递归遍历右子树
		PostOrderTraverse(T->rchild);

		// 访问根节点
		// 这里可以进行对根节点的操作，比如输出节点值
		cout << T->data;
	}
}
