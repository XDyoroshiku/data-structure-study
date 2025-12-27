#include<iostream>
using namespace std;

#define MaxSize 10
typedef struct
{
	int data;
	int next;
}SLinkList[MaxSize];

typedef struct
{
	int data;
	int next;
}Node;

int main()
{
	printf("Node的大小为：%d\n", sizeof(Node));
	printf("SLinkList的大小为：%d\n", sizeof(SLinkList));
	return 0;
}