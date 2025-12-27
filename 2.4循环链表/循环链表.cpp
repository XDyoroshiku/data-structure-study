#include<iostream>
using namespace std;

typedef struct LNode		
{
	int data;
	struct LNode* next;	
} LNode, * LinkList;		

typedef struct DNode
{
	int data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

bool InitList(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)		
	{
		printf("内存分配失败\n");
		return false;
	}
	L->data = 0;
	L->next = L;		
	return true;
}

bool InitDList(DLinkList& L)
{
	L = (DLinkList)malloc(sizeof(DNode));
	if (L == NULL)
	{
		printf("内存分配失败\n");
		return false;
	}
	L->data = 0;
	L->prior = L;
	L->next = L;
	printf("双链表初始化成功\n");
	return true;
}

bool IsTail(LinkList L, LNode* p)
{
	if(p->next == L)
		return true;
	return false;
}

bool IsTail(DLinkList L, DNode *p)		//函数重载
{
	if (p->next == L)
		return true;
	return false;
}

bool IsHead(LinkList L, LNode* p)
{
	if (p == L)
		return true;
	return false;
}

bool IsHead(DLinkList L, DNode* p)
{
	if (p == L)
		return true;
	return false;
}

bool InsertNextNode(LNode *p, int e)
{
	if (p == NULL)
	{
		printf("插入失败，传入了空结点\n");
		return false;
	}

	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;	//内存分配失败
	s->next = p->next;
	s->data = e;
	p->next = s;		//形参p是传入指针的副本，但副本p和传入指针都指向同一个地址，所以这里p->next = s;可以修改传入指针的成员next。
	printf("插入成功\n");
	return true;
}

bool InsertNextNode(DNode* p, int e)
{
	if (p == NULL)
	{
		printf("插入失败，传入了空结点\n");
		return false;
	}

	DNode* s = (DNode*)malloc(sizeof(DNode));
	if (s == NULL)
		return false;	//内存分配失败
	s->next = p->next;
	s->prior = p;
	s->data = e;

	p->next->prior = s;
	p->next = s;		//形参p是传入指针的副本，但副本p和传入指针都指向同一个地址，所以这里p->next = s;可以修改传入指针的成员next。
	printf("插入成功\n");
	return true;
}

void printList(LinkList L)
{
	if (L == NULL)
	{
		printf("打印循环单链表失败，传入了空指针\n");
		return;
	}
	LNode *p = L;
	int i = 0;
	while (!IsTail(L, p))
	{
		i++;
		p = p->next;		//打印指针指向的下一个结点的值，到尾结点时就打印了包括尾结点的所有结点元素。
		printf("循环单链表的第%d个结点为：%d\n", i, p->data);
	}
	printf("循环单链表共有%d个结点。\n", i);
}

void printList(DLinkList L)
{
	if (L == NULL)
	{
		printf("打印循环双链表失败，传入了空指针\n");
		return;
	}
	DNode* p = L;
	int i = 0;
	while (!IsTail(L, p))
	{
		i++;
		p = p->next;		//打印指针指向的下一个结点的值，到尾结点时就打印了包括尾结点的所有结点元素。
		printf("循环双链表的第%d个结点为：%d\n", i, p->data);
	}
	printf("循环双链表共有%d个结点。\n", i);
}

LNode * getPriorLNode(LinkList L, int location)
{
	if (L == NULL)
	{
		printf("获取结点失败。获取循环单链表结点失败，传入了空指针\n");
		return NULL;
	}
	if (location < 1)
	{
		printf("获取结点失败。获取结点位置应大于等于1\n");
		return NULL;
	}
	int i = 0;
	LNode* p = L;
	while (i < location-1 && !IsTail(L, p))		//location-1获取前一个结点
	{
		i++;
		p = p->next;
	}
	//if (i = location - 1)		。。。。。。
	if (i == location - 1)		//i=location-1说明获取位置结点的前一个结点是尾结点，不加这个判断不能获取到尾结点。
	{
		return p;
	}
	if (IsTail(L, p))
	{
		printf("获取结点失败。获取结点位置超出了链表，链表长度为：%d\n", i);
		return NULL;
	}
	return p;
}

DNode * getPriorDNode(DLinkList L, int location)
{
	if (L == NULL)
	{
		printf("获取结点失败。获取循环单链表结点失败，传入了空指针\n");
		return NULL;
	}
	if (location < 1)
	{
		printf("获取结点失败。获取结点位置应大于等于1\n");
		return NULL;
	}
	int i = 0;
	DNode* p = L;
	while (i < location-1 && !IsTail(L, p))
	{
		i++;
		p = p->next;
	}
	if (i == location - 1)		//i=location-1说明获取位置结点的前一个结点是尾结点，不加这个判断不能获取到尾结点。
	{
		return p;
	}
	if (IsTail(L, p))
	{
		printf("获取结点失败。获取结点位置超出了链表，链表长度为：%d\n", i);
		return NULL;
	}
	return p;
}

LNode* getLNode(LinkList L, int location)
{
	if (L == NULL)
	{
		printf("获取结点失败。获取循环单链表结点失败，传入了空指针\n");
		return NULL;
	}
	if (location < 1)
	{
		printf("获取结点失败。获取结点位置应大于等于1\n");
		return NULL;
	}
	int i = 0;
	LNode* p = L;
	while (i < location && !IsTail(L, p))		
	{
		i++;
		p = p->next;
	}

	if (i == location)		//i=location说明获取位置结点是尾结点，不加这个判断不能获取到尾结点。
	{
		return p;
	}
	if (IsTail(L, p))
	{
		printf("获取结点失败。获取结点位置超出了链表，链表长度为：%d\n", i);
		return NULL;
	}
	return p;
}

DNode* getDNode(DLinkList L, int location)
{
	if (L == NULL)
	{
		printf("获取结点失败。获取循环单链表结点失败，传入了空指针\n");
		return NULL;
	}
	if (location < 1)
	{
		printf("获取结点失败。获取结点位置应大于等于1\n");
		return NULL;
	}
	int i = 0;
	DNode* p = L;
	while (i < location && !IsTail(L, p))
	{
		i++;
		p = p->next;
	}

	if (i == location)		//i=location说明获取位置结点是尾结点，不加这个判断不能获取到尾结点。
	{
		return p;
	}
	if (IsTail(L, p))
	{
		printf("获取结点失败。获取结点位置超出了链表，链表长度为：%d\n", i);
		return NULL;
	}
	return p;
}


bool InsertByLocation(LinkList L, int location, int e)
{
	/*printf("进入InsertByLocation(LinkList L, int location, int e)函数\n");*/

	if (L == NULL)
	{
		printf("插入失败。传入了空指针\n");
		return false;
	}

	/*printf("location的值为：%d\n", location);*/

	LNode *p = getPriorLNode(L, location);

	//LNode* p = getLNode(L, location);		//！！！这里的方法是找到插入位置的结点，通过循环链表一圈得到前驱结点。但是这个方法不能在链表尾结点后插入结点，因为想要在尾结点后插入，需要getNode()得到尾结点后的结点，但这个结点不存在。这个方法需要写其他判断，不想写了。
	//if (p == NULL)
	//	return false;		//否则会把空指针传给s，while语句无限循环。
	//LNode* s = p;
	//while (p->next != s)		//location大于等于1，p不会是空链表的头结点，不会无限循环
	//{
	//	p = p->next;		//最后得到p的前一个结点。
	//}

	if(!InsertNextNode(p, e))
	{
		printf("输入位置插入结点失败\n");
		return false;
	}
	return true;
}

bool InsertByLocation(DLinkList L, int location, int e)
{
	if (L == NULL)
	{
		printf("插入失败。传入了空指针\n");
		return false;
	}
	DNode* p = getPriorDNode(L, location);

	//DNode* p = getDNode(L, location);
	//if (p == NULL)
	//	return false;		//p可能得到空指针。
	//p = p->prior;		//p指向前一个结点。

	if (!InsertNextNode(p, e))
	{
		printf("输入位置插入结点失败\n");
		return false;
	}
	return true;
}

bool DeleteByLocation(LinkList L, int location)
{
	if (L == NULL)
	{
		printf("删除失败。传入了空指针\n");
		return false;
	}
	if (IsTail(L, L))
	{
		printf("删除失败。传入了只有头结点的链表\n");		//如果输入了只有头结点的链表，location又超过1，会删除循环链表的头结点。
		return false;
	}
	if (location < 1)
	{
		printf("删除结点失败。删除结点位置应大于等于1\n");
		return false;
	}
	int i = 0;
	LNode* p = L;
	while (i < location-1 && !IsTail(L, p))
	{
		i++;
		p = p->next;		//找到删除结点的前一个结点。
	}
	LNode* s = p->next;
	p->next = p->next->next;
	free(s);
	if (location = i)
	{
		printf("删除成功\n");
		return true;
	}
	if (IsTail(L, p))	//删除结点的前一个结点如果是尾结点，说明这个结点不存在
	{
		printf("删除结点失败。删除结点位置应超出链表，链表长度为：%d\n", i+1);		//因为
		return false;
	}
	printf("删除成功\n");
}

bool DeleteByLocation(DLinkList L, int location)
{
	if (L == NULL)
	{
		printf("删除失败。传入了空指针\n");
		return false;
	}
	if (IsTail(L, L))
	{
		printf("删除失败。传入了只有头结点的链表\n");		//如果输入了只有头结点的链表，location又超过1，会删除循环链表的头结点。
		return false;
	}
	if (location < 1)
	{
		printf("删除结点失败。删除结点位置应大于等于1\n");
		return false;
	}
	int i = 0;
	DNode* p = L;
	while (i < location - 1 && !IsTail(L, p))
	{
		i++;
		p = p->next;		//找到删除结点的前一个结点。
	}
	DNode* s = p->next;
	p->next->next->prior = p;
	p->next = p->next->next;
	free(s);
	if (location = i)
	{
		printf("删除成功\n");
		return true;
	}
	if (IsTail(L, p))	//删除结点的前一个结点如果是尾结点，说明这个结点不存在
	{
		printf("删除结点失败。删除结点位置应超出链表，链表长度为：%d\n", i);
		return false;
	}
	printf("删除成功\n");
}

int main()
{
	LinkList L1;
	InitList(L1);

	DLinkList L2;
	InitDList(L2);

	LinkList L3;
	InitList(L3);

	InsertNextNode(L1, 100);
	InsertNextNode(L1, 200);

	printList(L1);
	//for (int i = 0; i < 10; i++)
	//{
	//	printf("%d\n", L1->data);
	//	L1 = L1->next;
	//}

	InsertByLocation(L1, 0, 600);
	printList(L1);
	InsertByLocation(L1, 500, 700);
	printList(L1);
	InsertByLocation(L1, 1, 800);
	printList(L1);
	InsertByLocation(L1, 3, 900);
	printList(L1);
	InsertByLocation(L1, 5, 1000);
	printList(L1);

	DeleteByLocation(L1, 1);
	printList(L1);
	DeleteByLocation(L1, 3);
	printList(L1);
	/*DeleteByLocation(L1, 4);*/
	DeleteByLocation(L1, 3);
	printList(L1);

	//记得free链表

	InsertNextNode(L2, 10);
	InsertNextNode(L2->prior, 20);

	InsertByLocation(L2, 0, 60);
	printList(L2);
	InsertByLocation(L2, 500, 70);
	printList(L2);
	InsertByLocation(L2, 1, 80);
	printList(L2);
	InsertByLocation(L2, 3, 90);
	printList(L2);
	InsertByLocation(L2, 5, 100);
	printList(L2);
	DeleteByLocation(L2, 1);
	printList(L2);
	DeleteByLocation(L2, 3);
	printList(L2);
	/*DeleteByLocation(L1, 4);*/
	DeleteByLocation(L2, 3);
	printList(L2);

	DeleteByLocation(L3, 1);

	//记得free链表

	return 0;
}