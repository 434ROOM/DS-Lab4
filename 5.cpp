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
{// 先序建立二叉树
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
{// 求二叉树T最大宽度
    if (!T)
    {
        return 0;
    }

    int maxWidth = 0;
    queue<BiTNode*> q;
    q.push(T);

    while (!q.empty()) {
        int levelSize = q.size(); // 当前层的节点数
        maxWidth = max(maxWidth, levelSize);

        // 将当前层的节点依次出队，并将下一层节点入队
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