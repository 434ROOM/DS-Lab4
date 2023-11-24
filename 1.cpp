#include<iostream>
#include<string.h>
#pragma warning(disable:4996)
#define MAXSIZE 100
using namespace std;

typedef struct
{//��������������ʽ
	int weight;               //����Ȩֵ
	int parent, lchild, rchild;  //����˫�ס����ӡ��Һ��ӵ��±�
}HTNode, * HuffmanTree;       //��̬��������洢��������

typedef char** HuffmanCode;   //������������

int Search(char a[], char ch)
{//�����������ַ�ch���ڵ�λ�ã����������±꣬���򷵻�-1
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == ch)
			return i;
	}
	return -1;
}

void Sort(char a[], int b[], int len)
{//��ASCII��ð������
	int i, j, temp;
	char ch;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				ch = a[j];
				a[j] = a[j + 1];
				a[j + 1] = ch;
				temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
			}
		}
	}
}

void Select_min(HuffmanTree HT, int n, int& s1, int& s2)
{// ��HT[k](1��k��i-1����ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ�㣬������������HT�е����s1��s2
	int i, j;
	int min1 = 10000, min2 = 10000;
	for (i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < min1)
		{
			min1 = HT[i].weight;
			s1 = i;
		}
	}
	for (j = 1; j <= n; j++)
	{
		if (HT[j].parent == 0 && HT[j].weight < min2 && j != s1)
		{
			min2 = HT[j].weight;
			s2 = j;
		}
	}
}

int m;
void CreateHuffmanTree(HuffmanTree& HT, int n, int b[])
{//�����������HT
	m = 2 * n - 1;   //���������Ľ����
	HT = new HTNode[m + 1];   //0�ŵ�Ԫδ��
	int i;
	for (i = 1; i <= n; i++)   //��ʼ��ǰn�����
	{
		HT[i].weight = b[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)   //��ʼ����m-n�����
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	int s1, s2;
	for (i = n + 1; i <= m; i++)   //������������ĺ�m-n�����
	{
		Select_min(HT, i - 1, s1, s2);   //��HT[k](1��k��i-1����ѡ��������˫����Ϊ0��Ȩֵ��С�Ľ�㣬������������HT�е����s1��s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n)
{//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ����HC��
	int i, j, start, c, f;
	char* cd;
	HC = new char* [n + 1];   //����n���ַ������ͷָ������
	cd = new char[n];         //���������Ĺ����ռ�
	cd[n - 1] = '\0';         //���������
	for (i = 1; i <= n; i++)  //����ַ������������
	{
		start = n - 1;        //���������λ��
		c = i;                //��Ҷ�ӵ������������
		f = HT[i].parent;     //fָ��˫��
		while (f != 0)        //˫�״���
		{
			start--;          //���������λ�õݼ�
			if (HT[f].lchild == c)
				cd[start] = '0';  //���֧��0
			else
				cd[start] = '1';  //�ҷ�֧��1
			c = f;             //�ƶ�����ָ�뵽˫��
			f = HT[f].parent;  //�ƶ�˫��ָ�뵽˫�׵�˫��
		}
		HC[i] = new char[n - start];  //Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);  //��cd���Ʊ��뵽HC
	}
	delete[] cd;   //�ͷŹ����ռ�
}

void CharFrequency(char ch[], char a[], int b[], int& j)
{//ͳ�ƴ�Ƶ
	j = 0;
	int i, k;
	for (i = 0; ch[i] != '\0'; i++)
	{
		k = Search(a, ch[i]);
		if (k == -1)
		{
			a[j] = ch[i];
			b[j] = 1;
			j++;
		}
		else
			b[k]++;
	}
}

void PrintHT(HuffmanTree HT)
{//������������Ĵ洢�ṹ����̬
	for (int i = 1; i <= m; i++)
	{
		cout << i << " "
			<< HT[i].weight << " "
			<< HT[i].parent << " "
			<< HT[i].lchild << " " 
			<< HT[i].rchild << endl;
	}
}

void PrintHC(HuffmanCode HC, char a[], int j)
{//���ÿ���ַ��Ĺ���������
	for (int i = 1; i <= j; i++)
	{
		cout << a[i - 1] << ":";
		for (int k = 0; HC[i][k] != '\0'; k++)
		{
			cout << HC[i][k];
		}
		if (i != j)
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}
}




int main()
{
	char ch[MAXSIZE];
	int i, j;
	while (cin >> ch)
	{
		if (ch[0] == '0') break;
		HuffmanTree HT;
		char a[MAXSIZE] = { '\0' };
		int b[MAXSIZE] = { 0 };
		j = 0;      //jͳ�Ʋ�ͬ�ַ�������
		CharFrequency(ch, a, b, j);   //ͳ�ƴ�Ƶ
		Sort(a, b, j);     //��ASCII��ð������
		for (i = 0; a[i] != '\0'; i++)   //���ͳ�Ƴ������ַ��ͳ���Ƶ��
		{
			if (a[i + 1] != '\0')
				cout << a[i] << ":" << b[i] << " ";
			else
				cout << a[i] << ":" << b[i] << endl;
		}
		//�����������
		CreateHuffmanTree(HT, i, b);    //�����������HT
		PrintHT(HT);      //������������Ĵ洢�ṹ����̬
		//����������
		HuffmanCode HC;    //�����HC
		CreateHuffmanCode(HT, HC, j);
		PrintHC(HC, a, j);    //���ÿ���ַ��Ĺ���������
		int k;
		for (i = 0; ch[i] != '\0'; i++)    //����������ַ���
		{
			for (k = 0; k < j; k++)
			{
				if (ch[i] == a[k])
					cout << HC[k + 1];
			}
		}
		cout << endl;
		cout << ch << endl;//����������ַ�������������ַ�����ͬ��
	}
	return 0;
}
