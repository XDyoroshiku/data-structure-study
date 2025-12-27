#include <iostream>
using namespace std;

typedef struct LinkNode
{
	int data;
	struct LinkNode* next;
}*LinkStack;

bool InitLinkStack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(LinkNode));
	if (S == NULL)
	{
		printf("内存分配失败\n");
		return false;
	}
	S->data = 0;
	S->next = NULL;
	printf("链栈初始化成功\n");
	return true;
}

bool emptyStack(LinkStack S)
{
	if (S->next == NULL)
		return true;
	return false;
}

//链栈似乎不会满。

bool push(LinkStack S, int e)
{
	if (S == NULL)
	{
		printf("传入了空指针\n");
		return false;
	}
	LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = e;
	p->next = S->next;
	S->next = p;
	printf("%d插入成功\n", e);
	return true;
}

bool pop(LinkStack S, int &e)
{
	if (S == NULL)
	{
		printf("传入了空指针\n");
		return false;
	}
	if (emptyStack(S))
	{
		printf("传入了空栈，无法弹出\n");
	}
	LinkNode* p = S->next;
	e = p->data;
	S->next = S->next->next;
	free(p);
	printf("%d弹出成功\n", e);
	return true;
}
void printStack(LinkStack S)
{
	if (emptyStack(S))
	{
		printf("传入了空栈\n");
		return;
	}
	printf("栈的结构为：\n\n");
	int i = 0;
	while (!emptyStack(S))		//正常来说判断条件应该是S->next != NULL
	{
		i++;
		S = S->next;
		printf("|%d|\n", S->data);
	}
	printf("▔▔▔▔▔\n栈共有%d个元素\n", i);
}

bool getTop(LinkStack S, int& e)
{
	if (emptyStack(S))
	{
		printf("传入了空栈\n");
		return false;
	}
	//while (!emptyStack(S))		//！！加上后是求栈底元素
	//{
	//	S = S->next;
	//}
	e = S->next->data;
	printf("栈顶元素为：%d\n", e);
	return true;
}

int main()
{
	LinkStack S1;
	InitLinkStack(S1);

	for (int i = 0; i < 10; i++)
	{
		push(S1, i*100);
	}
	printStack(S1);

	int rv;
	pop(S1, rv);
	pop(S1, rv);
	pop(S1, rv);
	printStack(S1);

	getTop(S1, rv);

	return 0;
}