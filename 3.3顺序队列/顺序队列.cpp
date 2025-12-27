#include<iostream>
using namespace std;

#define MaxSize 10
typedef struct
{
	int data[MaxSize];
	int front;
	int rear;
}sq_queue;

bool init_queue(sq_queue &Q)
{
	Q.front = 0;
	Q.rear = 0;
	printf("队列初始化成功\n");
	return true;
}

bool empty_queue(sq_queue Q)
{
	if (Q.front == Q.rear)
	{
		printf("队列为空\n");
		return true;
	}
	/*printf("队列不为空\n");*/
	return false;
}

bool full_queue(sq_queue Q)
{
	if ((Q.rear+1)%MaxSize == Q.front)		//%运算优先级高于+运算
	{
		printf("队列已满\n");
		return true;
	}
	/*printf("队列未满\n");  */
	return false;
}

bool enter_queue(sq_queue &Q, int e)
{
	if (full_queue(Q))
	{
		printf("%d进入队列失败\n", e);
		return false;
	}
	Q.data[Q.rear] = e;
	Q.rear = (Q.rear+1)%MaxSize;
	printf("%d进入队列成功\n", e);
	return true;
}

bool out_queue(sq_queue& Q, int& e)
{
	if (empty_queue(Q))
	{
		printf("出队列失败\n");
		return false;
	}
	e = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	printf("%d出队列成功\n", e);
	return true;
}

bool get_front(sq_queue Q, int& e)
{
	if (empty_queue(Q))
	{
		printf("查询失败\n");
		return false;
	}
	e = Q.data[Q.front];
	printf("队列第一个元素为：%d\n", e);
	return true;
}

void print_queue(sq_queue Q)
{
	if (empty_queue(Q))
	{
		printf("空队列\n");
		return;
	}
	int i = 0;

	/*while (!empty_queue(Q))*/
	while (Q.front != Q.rear)	
	{
		i++;
		printf("队列第%d个元素为：%d\n", i, Q.data[Q.front]);
		Q.front = (Q.front + 1) % MaxSize;
	}
	printf("队列共有%d个元素\n", i);
}

int main()
{
	sq_queue Q1;
	init_queue(Q1);

	//empty_queue(Q1) ;
	//full_queue(Q1);

	for (int i = 0; i < 12; i++)
	{
		enter_queue(Q1, i*10);
	}
	empty_queue(Q1);
	full_queue(Q1);
	print_queue(Q1);

	int rv;
	get_front(Q1, rv);

	out_queue(Q1, rv);		//7个
	out_queue(Q1, rv);
	out_queue(Q1, rv);
	out_queue(Q1, rv);
	out_queue(Q1, rv);
	out_queue(Q1, rv);
	out_queue(Q1, rv);

	print_queue(Q1);
	get_front(Q1, rv);

	for (int i = 0; i < 6; i++)
	{
		enter_queue(Q1, i * 100);
	}
	print_queue(Q1);

	for (int i = 0; i < 5; i++)
	{
		out_queue(Q1, rv);
	}
	print_queue(Q1);

	return 0;
}