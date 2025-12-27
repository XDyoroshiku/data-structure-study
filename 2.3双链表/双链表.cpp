#include<iostream>
using namespace std;

typedef struct DNode
{
	int data;
	struct DNode* prior, * next;
}DNode, *DLinkList;

bool InitDList(DLinkList& L)
{
	L = (DLinkList)malloc(sizeof(DNode));
	if (L == NULL)
	{
		printf("内存分配失败\n");
		return false;
	}
	L->prior = NULL;
	L->next = NULL;
	printf("双链表初始化成功\n");
	return true;
}

bool InsertNextNode(DNode* p, DNode* s)		//s结点插入p结点后
{
	if (s == NULL)
	{
		printf("不能将空指针插入双链表\n");
		return false;
	}


	s->prior = p;
	s->next = p->next;

	if(p->next != NULL)
		p->next->prior = s;

	p->next = s;
	
	printf("插入成功\n");
	return true;
}

bool InsertByLocation(DLinkList L, int location, int e)
{
	if (location < 1)
	{
		printf("插入位置应大于等于1\n");
		return false;
	}
	int i = 0;
	while (i < location-1 && L != NULL)
	{
		L = L->next;
		i++;
	}
	if (L == NULL)
	{
		printf("插入位置超出双链表，双链表长度为：%d\n", i-1);
		return false;
	}
	DNode* s = (DNode*)malloc(sizeof(DNode));
	s->data = e;
	InsertNextNode(L, s);
	return true;
}


void printList(DLinkList L)
{
	if (L == NULL)
	{
		printf("打印双链表失败，传入了空指针\n");
		return;
	}
	int i = 0;
	L = L->next;
	while (L != NULL)
	{
		i++;
		printf("双链表第%d个结点的值为：%d\n", i, L->data);
		L = L->next;
		
	}
	printf("双链表的长度为：%d\n", i);
}

bool DeleteDNode(DNode* p)
{
	if (p == NULL)
	{
		printf("删除节点为空指针\n");
		return false;
	}
	p->prior->next = p->next;
	if (p->next != NULL)
		p->next->prior = p->prior;
	free(p);
	printf("删除成功\n");
	return true;
}

bool DeleteByLocation(DLinkList L, int location)
{
	if (location < 1)
	{
		printf("删除位置应大于等于1\n");
		return false;
	}
	int i = 0;
	while (i < location && L != NULL)
	{
		L = L->next;
		i++;
	}
	if (L == NULL)
	{
		printf("删除位置超出双链表，双链表长度为：%d\n", i - 1);
		return false;
	}
	DeleteDNode(L);
	return true;
}

int main()
{
	DLinkList L1;
	InitDList(L1);

	printList(L1);

	DNode* Node1 = (DNode *)malloc(sizeof(DNode));
	Node1->data = 100;

	DNode* Node2 = (DNode*)malloc(sizeof(DNode));
	Node2->data = 200;

	InsertNextNode(L1, Node1);
	InsertNextNode(Node1, Node2);

	printList(L1);

	InsertByLocation(L1, 3, 300);
	InsertByLocation(L1, 1, 400);
	InsertByLocation(L1, 8, 500);
	InsertByLocation(L1, 4, 600);
	printList(L1);

	//DeleteDNode(Node1);
	//printList(L1);

	DeleteByLocation(L1, 5);
	printList(L1);
	
	while (L1->next != NULL)
	{
		DeleteByLocation(L1, 1);
	}
	free(L1);
	L1 = NULL;

	return 0;
}