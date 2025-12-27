#include<iostream>
using namespace std;

//typedef struct link_node link_node;		//给struct link_node起别名为link_node。
//struct link_node
//{
//	int data;
//	link_node* next;
//};
//typedef link_node* link_queue;

typedef struct link_node		//和上面一段定义等价。
{
	int data;
	struct link_node* next;
}link_node;		

typedef struct
{
	link_node* front, * rear;
}link_queue;

bool init_queue(link_queue& Q)
{
	Q.front = Q.rear = (link_node*)malloc(sizeof(link_node));
	Q.front->next = NULL;		//Q.rear和Q.front是同一个位置，所以Q.rear->next也为NULL。
	printf("链式队列初始化成功\n");
	return true;
}

bool empty_queue(link_queue Q)
{
	if (Q.front == Q.rear)
	{
		printf("队列为空\n");
		return true;
	}
	/*printf("队列不为空\n");*/
	return false;
}

bool in_queue(link_queue& Q, int e)
{
	link_node* p = (link_node*)malloc(sizeof(link_node));
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;		//链接末尾结点和插入结点。
	Q.rear = p;		//移动rear指针到末尾结点。
	printf("%d插入成功\n", e);
	return true;
 }

bool out_queue(link_queue& Q, int& e)
{
	if (empty_queue(Q))
	{
		printf("删除失败，传入了空队列\n");
		return false;
	}
	if (Q.front->next == Q.rear)		//如果删除的是队列仅有的一个结点，需要把rear指向front，不然会free掉rear指的位置。
	{
		Q.rear = Q.front;
	}
	link_node* p = Q.front->next;		//Q.front是data未初始化的头结点
	/*e = Q.front->data;*/
	e = Q.front->next->data;
	Q.front->next = Q.front->next->next;
	free(p);		//p和Q.front是两个指针，而上面初始化时给Q.front->next赋值时也给Q.rear->next赋值了，是因为他们指向相同的地址，是给地址赋值了。

	printf("%d删除成功\n", e);
	return true;
}

bool print_queue(link_queue Q)
{
	if (empty_queue(Q))
	{
		printf("传入队列是空队列\n");
		return true;
	}
	int i = 0;
	while (Q.front != Q.rear)
	{
		i++;
		Q.front = Q.front->next;
		printf("队列的第%d个元素为：%d\n", i, Q.front->data);
	}
	printf("队列共有%d个元素。\n", i);
	return true;
}

int main()
{
	link_queue Q;
	init_queue(Q);

	empty_queue(Q);

	for (int i = 1; i <= 10; i++)
	{
		in_queue(Q, i*10);
	}
	print_queue(Q);

	int rv;
	for (int i = 0; i < 5; i++)
	{
		out_queue(Q, rv);
	}
	print_queue(Q);

	return 0;
}