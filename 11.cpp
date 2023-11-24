#include<iostream>
#include<string.h>
#define MAXSIZE 100
using namespace std;

typedef struct BiTNode
{//二叉树的双链表存储表示
	double data;          //结点数据域
	bool ischaracter;      //判断结点是否为字符
	struct BiTNode* lchild, * rchild;    //左右孩子指针
}BiTNode, * BiTree;

typedef struct
{//字符栈的存储结构
	char* base;     //栈底指针
	char* top;       //栈顶指针
	int stacksize;   //栈可用的最大容量
}SqStack1;

typedef struct
{//结点栈的存储结构
	BiTree* base;
	BiTree* top;
	int stacksize;
}SqStack2;

void InitStack1(SqStack1& s)
{//字符栈的初始化
	s.base = new char[MAXSIZE];
	s.top = s.base;
	s.stacksize = MAXSIZE;
}

void InitStack2(SqStack2& s)
{//结点栈的初始化
	s.base = new BiTree[MAXSIZE];
	s.top = s.base;
	s.stacksize = MAXSIZE;
}

void Push1(SqStack1& s, char ch)
{//字符入栈操作
	*(s.top++) = ch;
	return;
}

void Push2(SqStack2& s, BiTree t)
{//结点入栈操作
	*(s.top++) = t;
	return;
}

void Pop1(SqStack1& s, char& ch)
{//字符出栈操作
	ch = *--s.top;
}

void Pop2(SqStack2& s, BiTree& t)
{//结点出栈操作
	t = *--s.top;
}

char GetTop(SqStack1 s)
{//取字符栈的栈顶元素
	return *(s.top - 1);
}

bool EmptyStack(SqStack1 s)
{//栈的判空操作
	if (s.base==s.top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char Precede(char a, char b)
{//比较运算符a和b的优先级
	switch (a)
	{
	case '+':
		if (b == '+' || b == '-' || b == ')' || b == '=')
			return '>';
		else
			return '<';
		break;
	case '-':
		if (b == '+' || b == '-' || b == ')' || b == '=')
			return '>';
		else
			return '<';
		break;
	case '*':
		if (b == '(')
			return '<';
		else
			return '>';
		break;
	case '/':
		if (b == '(')
			return '<';
		else
			return '>';
		break;
	case '(':
		if (b == ')')
			return '=';
		else
			return '<';
		break;
	case ')':
		return '>';
		break;
	case '=':
		if (b == '=')
			return '=';
		else
			return '<';
		break;
	default:
		break;
	}
}

double Calculate(double a, char op, double b)
{//计算表达式“a op b”的值
	switch (op)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return a / b;
		break;
	default:
		break;
	}
}

bool IsCharacter(char ch)
{//判断ch是否为+、-、*、/、(、)、= 这类的字符，是则返回true
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '=')
	{
		return true;
	}
	else
	{
		return false;
	}
}

double InOrder(BiTree T)
{
	//中序遍历二叉树并求表达式的值
	if (T == NULL)
	{
		return 0;
	}
	if (!T->lchild && !T->rchild)
		return T->data;
	else
	{
		double num1 = 0, num2 = 0;
		num1 = InOrder(T->lchild);
		num2 = InOrder(T->rchild);
		return Calculate(num1, T->data, num2);
	}
}

void CreateBT(char ch[], BiTree& t, SqStack1 optr, SqStack2 expt) {
	//根据表达式创建二叉树

	int len = strlen(ch);
	int i = 0;
	while(i < len)
	{
		char c = ch[i];
		if (!IsCharacter(c))
		{
			BiTree T = new BiTNode;
			T->data = ch[i] - '0';
			T->ischaracter = false;
			T->lchild = NULL;
			T->rchild = NULL;
			Push2(expt, T);
			i++;
		}
		else
		{
			char op;
			switch (Precede(GetTop(optr), c))
			{
			case '<':
				Push1(optr, ch[i++]);
				break;
			case '=':
				Pop1(optr, op);
				i++;
				break;
			case '>':
				GetTop(optr);
				Pop1(optr, op);
				BiTree rc;
				Pop2(expt, rc);
				BiTree lc;
				Pop2(expt, lc);
				BiTree temp = new BiTNode;
				temp->data = op;
				temp->ischaracter = true;
				temp->lchild = lc;
				temp->rchild = rc;
				Push2(expt, temp);
				break;
			}

		}
	}
	Pop2(expt, t);
}



int main()
{
	char ch[MAXSIZE];
	while (cin >> ch)
	{
		if (ch[0] == '=') break;
		BiTree t;
		SqStack1 optr;      //运算符栈optr
		SqStack2 expt;        //数字栈expt
		InitStack1(optr);     //初始化栈
		InitStack2(expt);     //初始化栈
		Push1(optr, '=');    //先在运算符栈底放入一个'='
		CreateBT(ch, t, optr, expt);       //创建二叉树
		double answer = InOrder(t);
		cout << answer << endl;
	}
	return 0;
}
