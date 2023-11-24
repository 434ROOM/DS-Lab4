#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

typedef struct BiTNode
{
    char data;
    struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

BiTree CreateBiTree(int& pos, char* str)
{// ������������
	if (str[pos] == '0')
	{
		pos++;
		return NULL;
	}
	else
	{
		BiTree T = new BiTNode;
		T->data = str[pos];
		pos++;
		T->lchild = CreateBiTree(pos, str);
		T->rchild = CreateBiTree(pos, str);
		return T;
	}
}


int Width(BiTree T)
{// �������T�����
    if (!T)
    {
        return 0;
    }

    int maxWidth = 0;
    queue<BiTNode*> q;
    q.push(T);

    while (!q.empty()) {
        int levelSize = q.size(); // ��ǰ��Ľڵ���
        maxWidth = max(maxWidth, levelSize);

        // ����ǰ��Ľڵ����γ��ӣ�������һ��ڵ����
        for (int i = 0; i < levelSize; ++i) {
            BiTNode* node = q.front();
            q.pop();

            if (node->lchild) {
                q.push(node->lchild);
            }
            if (node->rchild) {
                q.push(node->rchild);
            }
        }
    }

    return maxWidth;
}