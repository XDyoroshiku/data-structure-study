#include <iostream>
using namespace std;

#define MaxSize 10
typedef struct
{
	int data[MaxSize];
	int top;
}SqStack;

void InitStack(SqStack &S)
{
	S.top = -1;
	printf("栈初始化成功\n");
}

bool emptyStack(SqStack S)
{
	if (S.top == -1)
		return true;
	return false;
}

bool fullStack(SqStack S)
{
	if (S.top == MaxSize - 1)
		return true;
	return false;
}

bool push(SqStack &S, int x)		//S是整个结构体而不是指针，所以要用引用类型。
{
	if (fullStack(S))
	{
		printf("推入失败。栈已满，无法进栈。\n");
		return false;
	}
	/*++S.top;*/
	S.top = S.top + 1;
	S.data[S.top] = x;
	printf("推入栈成功\n");
	return true;
}

bool pop(SqStack &S, int &x)
{
	if (emptyStack(S))
	{
		printf("弹出失败。栈已空，无法弹出。\n");
		return false;
	}
	x = S.data[S.top];
	--S.top;
	printf("%d弹出栈成功。\n", x);
	return true;
}

bool getTop(SqStack S, int& x)
{
	if (emptyStack(S))
	{
		printf("弹出失败。栈已空，无法弹出。\n");
		return false;
	}
	x = S.data[S.top];
	return true;
}

void printStack(SqStack S)
{
	if (emptyStack(S))
	{
		printf("传入了空栈\n");
		return;
	}
	printf("栈的结构为：\n\n");
	int i = 0;
	while (!emptyStack(S))
	{
		printf("|%d|\n", S.data[S.top]);
		i++;
		S.top--;
	}
	printf("▔▔▔\n栈共有%d个元素\n", i);

}

void locateElem(SqStack S, int e)
{
	if (emptyStack(S))
	{
		printf("传入了空栈\n");
		return;
	}
	int i = 0, num = 0;
	while (!emptyStack(S))
	{
		if (S.data[S.top] == e)
		{
			printf("栈的第%d个元素=%d\n", S.top+1, e);
			num++;
		}
		i++;
		S.top--;
	}
	if (num == 0)
	{
		printf("栈中没有值等于%d的元素\n", e);
	}
	printf("栈中有%d个元素和%d相等\n", num, e);

}


//void printStack(SqStack S)
//{
//	for(int i = 0) 
//}

int main()
{
	SqStack S1;
	InitStack(S1);
	
	int rv;
	pop(S1, rv);

	for (int i = 0; i < MaxSize + 2; i++)
	{
		cout << i;
		push(S1, i);
	}
	printStack(S1);

	pop(S1, rv);
	pop(S1, rv);
	printStack(S1);

	pop(S1, rv);
	pop(S1, rv);
	push(S1, 1);
	push(S1, 1);
	push(S1, 1);
	push(S1, 2);
	push(S1, 2);
	printStack(S1);

	locateElem(S1, 5);
	locateElem(S1, 1);
	locateElem(S1, 2);

	return 0;
}