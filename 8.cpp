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

void PreOrderTraverse(BiTree T)
{//���������������
	if (T != NULL) {
		// �ȷ��ʸ��ڵ�
		cout << T->data;

		// �ݹ����������
		PreOrderTraverse(T->lchild);

		// �ݹ����������
		PreOrderTraverse(T->rchild);
	}
}


void InOrderTraverse(BiTree T) {
// �������
	if (T != NULL) {
		// �ݹ����������
		InOrderTraverse(T->lchild);

		// ���ʸ��ڵ�
		cout << T->data;

		// �ݹ����������
		InOrderTraverse(T->rchild);
	}
}


void PostOrderTraverse(BiTree T) {
// �������
	if (T != NULL) {
		// �ݹ����������
		PostOrderTraverse(T->lchild);

		// �ݹ����������
		PostOrderTraverse(T->rchild);

		// ���ʸ��ڵ�
		// ������Խ��жԸ��ڵ�Ĳ�������������ڵ�ֵ
		cout << T->data;
	}
}
