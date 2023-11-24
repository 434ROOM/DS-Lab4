#include<iostream>
#include<string.h>
#pragma warning(disable:4996)
#define MAXSIZE 100
using namespace std;

typedef struct
{//哈夫曼树结点的形式
	int weight;               //结点的权值
	int parent, lchild, rchild;  //结点的双亲、左孩子、右孩子的下标
}HTNode, * HuffmanTree;       //动态分配数组存储哈夫曼树

typedef char** HuffmanCode;   //定义编码表类型

int Search(char a[], char ch)
{//查找数组中字符ch所在的位置，返回数组下标，否则返回-1
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == ch)
			return i;
	}
	return -1;
}

void Sort(char a[], int b[], int len)
{//按ASCII码冒泡排序
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
{// 在HT[k](1≤k≤i-1）中选择两个其双亲域为0且权值最小的结点，并返回它们在HT中的序号s1和s2
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
{//构造哈夫曼树HT
	m = 2 * n - 1;   //哈夫曼树的结点数
	HT = new HTNode[m + 1];   //0号单元未用
	int i;
	for (i = 1; i <= n; i++)   //初始化前n个结点
	{
		HT[i].weight = b[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)   //初始化后m-n个结点
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	int s1, s2;
	for (i = n + 1; i <= m; i++)   //构造哈夫曼树的后m-n个结点
	{
		Select_min(HT, i - 1, s1, s2);   //在HT[k](1≤k≤i-1）中选择两个其双亲域为0且权值最小的结点，并返回它们在HT中的序号s1和s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n)
{//从叶子到根逆向求每个字符的哈夫曼编码，存储在编码表HC中
	int i, j, start, c, f;
	char* cd;
	HC = new char* [n + 1];   //分配n个字符编码的头指针向量
	cd = new char[n];         //分配求编码的工作空间
	cd[n - 1] = '\0';         //编码结束符
	for (i = 1; i <= n; i++)  //逐个字符求哈夫曼编码
	{
		start = n - 1;        //编码结束符位置
		c = i;                //从叶子到根逆向求编码
		f = HT[i].parent;     //f指向双亲
		while (f != 0)        //双亲存在
		{
			start--;          //编码结束符位置递减
			if (HT[f].lchild == c)
				cd[start] = '0';  //左分支标0
			else
				cd[start] = '1';  //右分支标1
			c = f;             //移动编码指针到双亲
			f = HT[f].parent;  //移动双亲指针到双亲的双亲
		}
		HC[i] = new char[n - start];  //为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);  //从cd复制编码到HC
	}
	delete[] cd;   //释放工作空间
}

void CharFrequency(char ch[], char a[], int b[], int& j)
{//统计词频
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
{//输出哈夫曼树的存储结构的终态
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
{//输出每个字符的哈夫曼编码
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
		j = 0;      //j统计不同字符的数量
		CharFrequency(ch, a, b, j);   //统计词频
		Sort(a, b, j);     //按ASCII码冒泡排序
		for (i = 0; a[i] != '\0'; i++)   //输出统计出来的字符和出现频率
		{
			if (a[i + 1] != '\0')
				cout << a[i] << ":" << b[i] << " ";
			else
				cout << a[i] << ":" << b[i] << endl;
		}
		//构造哈夫曼树
		CreateHuffmanTree(HT, i, b);    //构造哈夫曼树HT
		PrintHT(HT);      //输出哈夫曼树的存储结构的终态
		//哈夫曼编码
		HuffmanCode HC;    //编码表HC
		CreateHuffmanCode(HT, HC, j);
		PrintHC(HC, a, j);    //输出每个字符的哈夫曼编码
		int k;
		for (i = 0; ch[i] != '\0'; i++)    //输出编码后的字符串
		{
			for (k = 0; k < j; k++)
			{
				if (ch[i] == a[k])
					cout << HC[k + 1];
			}
		}
		cout << endl;
		cout << ch << endl;//输出解码后的字符串（与输入的字符串相同）
	}
	return 0;
}
