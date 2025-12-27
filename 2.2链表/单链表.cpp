#include<iostream>
using namespace std;

typedef struct LNode		//和定义顺序表结构时不一样，这里struct后要声明类型别名LNode，否则在定义成员的LNode*时，编译器不知道struct LNode是什么。
{
	int data;
	struct LNode* next;		//指针类型为struct LNode—>这个名叫next的指针可以存放struct LNode类型变量的地址。
} LNode, * LinkList;		//typedef <数据类型> <别名> : struct LNode == LNode; LNode*和LinkList在编译器层面效果相同，只是使用不同的名称代表不同的意义。

bool InitList(LinkList &L)
{
	L = (LNode*) malloc(sizeof(LNode));
	if (L == NULL)		//给链表L分配内存失败
	{
		return false;
	}
	L->next = NULL;		//L是指针用L->;L是结构体变量用L.，L->next等价于(L*).next		！！这里设置头节点的next指针指向NULL！！，所以插入创建链表时，最后一个指针仍然指向NULL！！
	return true;
}

bool ListInsert(LinkList L, int location, int e)
{
	if (location < 1)		//location = 1,插在头节点后。
		return false;
	LNode* p;
	p = L;
	for (int i = 0; p!=NULL && i<location-1; i++)		//location减1，p移动到插入位置的前一个结点。因为单链表是单向的，所以循环到插入位置的前一个结点。
	{
		p = p->next;
	}
	if (p == NULL)		//链表没有设置表示长度成员，不然可以把这个判断和上面的合并。
		return false;

	LNode* s = (LNode*)malloc(sizeof(LNode));		
	s->next = p->next;		//p->next现在指向插入位置的结点，把这个结点后移。
	s->data = e;			//现在s->next和p都指向p->next。
	p->next = s;
	//InsertNextNode(p, e);		//需要InsertNextNode(LNode* p, int e)的函数声明。

	return true;
}

bool InsertNextNode(LNode* p, int e)		//这里可以用LNode * &p，不过如果有p = s这种情况，会修改p指针本身。 
{
	if (p == NULL)
		return false;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;	//内存分配失败
	s->next = p->next;
	s->data = e;
	p->next = s;		//形参p是传入指针的副本，但副本p和传入指针都指向同一个地址，所以这里p->next = s;可以修改传入指针的成员next。
	return true;
}

bool InsertPriorNode(LinkList L, LNode* p, int e)		//不用LinkList &L是因为函数内的(L = L->next;)会修改L的地址。
{
	if (p == NULL)
		return false;

	while (L->next != p)
		L = L->next;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;	//内存分配失败

	s->next = L->next;		//s->next = p;
	s->data = e;
	L->next = s;

}

bool InsertPriorNode2(LNode* p, int e)
{
	if (p == NULL)
		return false;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (s == NULL)
		return false;	//内存分配失败

	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;		//在p结点后插入一个结点s，但是交换了p和s结点的值。从表结构来看相当于在链表p结点的元素前插入了一个元素。

}

void printList(LinkList L)
{
	int i = 0;
	while(L->next != NULL)
	/*while (L != NULL)*/
	{
		L = L->next; 
		i++;
		printf("链表第%d个元素为：%d\n", i, L->data);
	}
	printf("链表共有%d个元素\n", i);

}

LNode* getLNode(LinkList L, int location)
{
	if (location  < 1)
	{
		printf("获取结点的位置应大于等于1");
		return NULL;
	}
	int i = 0;
	while (i < location)
	{
		if (L == NULL)
		{
			printf("获取结点失败。输入结点位置大于单链表长度，单链表长度为：%d", i - 1);
			return NULL;
		}
		L = L->next;
		i++;
	}

	return	L;
}

void LocateElem(LinkList L, int e)
{
	int i = 0;
	while (L != NULL)
	{
		if(L->data == e)
			printf("链表的第%d个结点的值等于%d\n", i, e);
		
		L = L->next;
		i++;
	}
}

bool ListDelete(LinkList L, int location, int& e)
{
	if (location < 1)
	{
		printf("获取结点的位置应大于等于1");
		return false;
	}

	LNode* p = L;		//创建指针指向已有结点。
	int i = 0;
	while (i < location-1 && p->next != NULL)		//循环location-1次使指针p指向删除结点的前一个结点。
	{
		p = p->next;		//指针p最终会指向删除结点的前一个结点或链表的最后一个结点
		i++;
	}
	if (p->next == NULL)
	{
		printf("获取结点失败。输入结点位置大于单链表长度，单链表长度为：%d\n", i);
		return false;
	}
	LNode* s = p->next;		//下一步修改连接后无法访问修改前p的下一个结点，这里创建一个结点s指向p原来的下一个结点。
	e = s->data;
	p->next = s->next;
	free(s);		//指针s在函数结束后会被销毁，但s指向的结点的内存不会自动释放。

	//e = p->next->data;
	//p->next = p->next->next;

	/*free(p);*/	//free(p)会释放链表的内存，导致访问错误。
	return true;
}

bool DeleteNode(LinkList L, LNode* a)
{
	if (a == NULL)
		return false;

	LNode* p = L;
	while (p->next != a && p->next != NULL)
	{
		p = p->next;		//最后a指针指向传入指针p的前一个结点或最后一个结点。
	}
	if(p->next == NULL)
	{
		printf("链表里没有与输入节点相同的结点。\n");
		return false;
	}

	p->next = a->next;
	free(a);
	return true;

}

bool DeleteNode2(LNode* p)
{
	if (p == NULL)
		return false;
	if (p->next == NULL)
	{
		printf("这是最后一个结点，目前无法删除它...\n");		//如果用free(p),p的前一个结点的next需要指向NULL,但无法做到。
		return false;
	}

	LNode* s = p->next;
	p->data = s->data;		//输入结点i复制i+1结点的值
	p->next = s->next;		//结点i链接结点i+2
	free(s);				//删除多余的i+1结点。（i+1结点什么也没做就被删了ToT）
	return true;
}

//void List_TailInsert(LinkList &L)		//传入的L只是指针变量，而给L分配内存改变了L的地址，所以需要用引用类型&L。
LinkList List_TailInsert(LinkList L)		//这里直接返回L，可以把返回的L赋值给原指针，所以不用引用类型。
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

	int e = 0;
	LNode* p, * s = L;

	printf("输入插入链表的值：（输入123456结束创建链表）\n");
	cin >> e;
	while (e != 123456)
	{
		p = (LNode*)malloc(sizeof(LNode));
		p->data = e;
		/*p->next = NULL;*/		//在循环内，下一句会让尾结点指向新结点，所以这里不用把尾结点指向NULL。
		s->next = p;		//将链表表尾结点连向新节点。
		s = p;		//s指向链表表尾结点。
		printf("输入插入链表的值：（输入123456结束创建链表）\n");
		cin >> e;
	}
	s->next = NULL;		//结束时将尾结点指向NULL。

	return L;
}

LinkList List_HeadInsert(LinkList L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

	int e = 0;
	LNode* p;

	printf("输入插入链表的值：（输入123456结束创建链表）\n");
	cin >> e;
	while (e != 123456)
	{
		p = (LNode*)malloc(sizeof(LNode));
		p->data = e;	
		p->next = L->next;
		L->next = p;
		printf("输入插入链表的值：（输入123456结束创建链表）\n");
		cin >> e;
	}		

	return L;
}

LinkList InverseList(LinkList L, LinkList L2)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;

	LNode* p;

	L2 = L2->next;		//L2指向头结点后一个结点
	while (L2 != NULL)
	{
		p = (LNode*)malloc(sizeof(LNode));
		p->data = L2->data;
		p->next = L->next;
		L->next = p;
		L2 = L2->next;
	}
	printf("Inverse Success!\n");

	return L;
}

int main()
{
	LinkList L1;		//根据LNode的结构定义，这里只是声明了一个LinkList类型的指针变量L1,没有分配内存，还没有头结点。
	if (InitList(L1))		//创建单链表头结点，头结点的next成员指向NULL,。
		printf("单链表创建成功\n");
	else
		printf("单链表创建失败\n");
	
	for (int i = 1; i <= 5; i++)		//插入5个元素
	{
		if(ListInsert(L1, i, i * 100))
			printf("插入成功\n");
		else
			printf("插入失败\n");
	}
	printList(L1);


	//if (ListInsert(L1, 10, -1))
	//	printf("插入成功\n");
	//else
	//	printf("插入失败\n");


	LNode* a = getLNode(L1, 3);

	LNode* b = getLNode(L1, 1);

	LNode* c = getLNode(L1, 5);

	LNode* d = getLNode(L1, 10);


	if (InsertNextNode(c, 2345))
		printf("插入成功\n");
	else
		printf("插入失败\n");

	if (InsertPriorNode(L1, b, 2345))
		printf("插入成功\n");
	else
		printf("插入失败\n");

	if (InsertPriorNode2(c, 2345))
		printf("插入成功\n");
	else
		printf("插入失败\n");

	printList(L1);


	//int deleteValue;
	//if(ListDelete(L1, 8, deleteValue))
	//	printf("删除成功, 删除的值为:%d\n", deleteValue);
	//else
	//	printf("删除失败\n");
	//printList(L1);

	
	//if(DeleteNode2(c))
	//	printf("删除成功\n");
	//else
	//	printf("删除失败\n");
	//printList(L1);


	//if (DeleteNode(L1, c))
	//	printf("删除成功\n");
	//else
	//	printf("删除失败\n");
	//printList(L1);


	//printList(L1);
	//for (int i = 1; i <= 5; i++)		//插入5个元素
	//{
	//	if (ListInsert(L1, i*2, 500))
	//		printf("插入成功\n");
	//	else
	//		printf("插入失败\n");
	//}
	//LocateElem(L1, 500);
	//printList(L1);
 
	//LinkList L2 = NULL;
	//L2 = List_TailInsert(L2);
	//printList(L2);


	//LinkList L3 = NULL;
	//L3 = List_HeadInsert(L3);
	//printList(L3);


	//LinkList L2 = NULL, L3 = NULL;
	//L2 = List_TailInsert(L2);
	//printList(L2);
	//L3 = InverseList(L3, L2);
	//printList(L3);

	//L2 = InverseList(L2, L2);
	//printList(L2);


	return 0;
}