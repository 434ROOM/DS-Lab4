#include<iostream>
#include<string.h>
#define MAXSIZE 100
using namespace std;

typedef struct BiTNode
{//��������˫����洢��ʾ
	double data;          //���������
	bool ischaracter;      //�жϽ���Ƿ�Ϊ�ַ�
	struct BiTNode* lchild, * rchild;    //���Һ���ָ��
}BiTNode, * BiTree;

typedef struct
{//�ַ�ջ�Ĵ洢�ṹ
	char* base;     //ջ��ָ��
	char* top;       //ջ��ָ��
	int stacksize;   //ջ���õ��������
}SqStack1;

typedef struct
{//���ջ�Ĵ洢�ṹ
	BiTree* base;
	BiTree* top;
	int stacksize;
}SqStack2;

void InitStack1(SqStack1& s)
{//�ַ�ջ�ĳ�ʼ��
	s.base = new char[MAXSIZE];
	s.top = s.base;
	s.stacksize = MAXSIZE;
}

void InitStack2(SqStack2& s)
{//���ջ�ĳ�ʼ��
	s.base = new BiTree[MAXSIZE];
	s.top = s.base;
	s.stacksize = MAXSIZE;
}

void Push1(SqStack1& s, char ch)
{//�ַ���ջ����
	*(s.top++) = ch;
	return;
}

void Push2(SqStack2& s, BiTree t)
{//�����ջ����
	*(s.top++) = t;
	return;
}

void Pop1(SqStack1& s, char& ch)
{//�ַ���ջ����
	ch = *--s.top;
}

void Pop2(SqStack2& s, BiTree& t)
{//����ջ����
	t = *--s.top;
}

char GetTop(SqStack1 s)
{//ȡ�ַ�ջ��ջ��Ԫ��
	return *(s.top - 1);
}

bool EmptyStack(SqStack1 s)
{//ջ���пղ���
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
{//�Ƚ������a��b�����ȼ�
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
{//������ʽ��a op b����ֵ
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
{//�ж�ch�Ƿ�Ϊ+��-��*��/��(��)��= ������ַ������򷵻�true
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
	//�������������������ʽ��ֵ
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
	//���ݱ��ʽ����������

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
		SqStack1 optr;      //�����ջoptr
		SqStack2 expt;        //����ջexpt
		InitStack1(optr);     //��ʼ��ջ
		InitStack2(expt);     //��ʼ��ջ
		Push1(optr, '=');    //���������ջ�׷���һ��'='
		CreateBT(ch, t, optr, expt);       //����������
		double answer = InOrder(t);
		cout << answer << endl;
	}
	return 0;
}
