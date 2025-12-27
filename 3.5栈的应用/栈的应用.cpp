#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct link_node
{
	char data;
	struct link_node* next;
}link_node, *link_stack;

typedef struct link_node_num
{
	int data;
	struct link_node_num* next;
}*link_stack_num;

bool init_stack(link_stack& S)
{
	S = (link_node*)malloc(sizeof(link_node));
	if (S == NULL)
	{
		printf("内存分配失败\n");
		return false;
	}
	S->next = NULL;	
	printf("链栈初始化成功\n");
	return true;
}

bool init_stack_num(link_stack_num& S)
{
	S = (link_node_num*)malloc(sizeof(link_node_num));
	if (S == NULL)
	{
		printf("内存分配失败\n");
		return false;
	}
	S->next = NULL;
	printf("链栈初始化成功\n");
	return true;
}

bool empty_stack(link_stack S)
{
	if (S->next == NULL)
	{
		/*printf("栈为空\n");*/
		return true;
	}
	return false;
}

bool empty_stack(link_stack_num S)
{
	if (S->next == NULL)
	{
		/*printf("栈为空\n");*/
		return true;
	}
	return false;
}

bool in_stack(link_stack S, char str)
{
	link_node* p = (link_node*)malloc(sizeof(link_node));
	p->data = str;
	p->next = S->next;
	S->next = p;		
	printf("%c插入成功\n", str);
	return true;
}

bool in_stack_num(link_stack_num S, int num)
{
	link_node_num* p = (link_node_num*)malloc(sizeof(link_node_num));
	p->data = num;
	p->next = S->next;
	S->next = p;
	printf("%d插入成功\n", num);
	return true;
}

bool out_stack(link_stack S, char& str)
{
	if (empty_stack(S))
	{
		printf("删除失败，传入了空栈\n");
		return false;
	}
	link_node* p = S->next;		//Q.front是data未初始化的头结点
	str = p->data;
	S->next = S->next->next;
	free(p);		//p和Q.front是两个指针，而上面初始化时给Q.front->next赋值时也给Q.rear->next赋值了，是因为他们指向相同的地址，是给地址赋值了。

	printf("%c删除成功\n", str);
	return true;
}

bool out_stack_num(link_stack_num S, int &num)
{
	if (empty_stack(S))
	{
		printf("删除失败，传入了空栈\n");
		return false;
	}
	link_node_num* p = S->next;	
	num = p->data;
	S->next = S->next->next;
	free(p);		

	printf("%d删除成功\n", num);
	return true;
}

char get_top(link_stack S)
{
	if (empty_stack(S))
	{
		printf("获取失败，传入了空栈\n");
		return false;
	}
	return S->next->data;
}

bool print_stack(link_stack S)
{
	if (empty_stack(S))
	{
		printf("传入了空栈\n");
		return false;
	}
	int i = 0;
	while (!empty_stack(S))
	{
		i++;
		S = S->next;
		printf("栈的第%d个元素为：%c\n", i, S->data);
	}
	printf("队列共有%d个元素。\n", i);
	return true;
}

bool destroy_stack(link_stack& S)
{
	char rv;
	while (!empty_stack(S))
		out_stack(S, rv);
	free(S);
	S = NULL;		//避免悬空指针。
	printf("栈销毁成功\n");
	return true;
}

bool destroy_stack(link_stack_num &S)
{
	int rv;
	while (!empty_stack(S))
		out_stack_num(S, rv);
	free(S);
	S = NULL;		//避免悬空指针。
	printf("栈销毁成功\n");
	return true;
}

bool check_bracket(char str[])		//括号匹配
{
	link_stack S;
	init_stack(S);
	for (int i = 0; str[i] != '\0'; i++)
	{
		char c = str[i];
		if (c == '(' || c == '[' || c == '{')
			in_stack(S, str[i]);
		else
		{
			if (c == ')' || c == ']' || c == '}')
			{
				if (empty_stack(S))
				{
					printf("匹配失败,存在多余右括号\n");
					destroy_stack(S);
					return false;		//存在多余的右括号。
				}
				char rv;
				char bracket = S->next->data;		//empty_stack判断后,S->next->data不会访问空指针。
				if ((c == ')' && bracket == '(') ||
					(c == ']' && bracket == '[') ||
					(c == '}' && bracket == '{'))
					out_stack(S, rv);
				else
				{
					destroy_stack(S);
					printf("匹配失败,括号不匹配\n");
					return false;
				}
			}
			
		}
		/*print_stack(S);*/
	}
	if (!empty_stack(S))		//存在多余左括号。
	{
		destroy_stack(S);
		printf("匹配失败,存在多余左括号\n");
		return false;
	}
	destroy_stack(S);
	printf("匹配成功\n");
	return true;
}

bool precede(char a, char b)		//判断a的优先级是否大于或等于b的优先级。
{
	if (a == '(')
		return false;
	if (a == '*' || a == '/')
		return true;
	else
	{
		if (b == '+' || b == '-')
			return true;
		return false;
	}
}

bool is_operator(char o)
{
	if (o == '+' || o == '-' || o == '*' || o == '/')
		return true;
	return false;
}

int calculate(int num1, int num2, char op)
{
	switch (op)
	{
		case '+':
		{
			num1 = num1 + num2;
			break;
		}
		case '-':
		{
			num1 = num1 - num2;
			break;
		}
		case '*':
		{
			num1 = num1 * num2;
			break;
		}
		case '/':
		{
			num1 = num1 / num2;
			break;
		}
	}
	return num1;
}



int infix_expression(char str[])		//输入字符串类型的计算表达式，计算结果
{
	link_stack symbol, charnum;
	init_stack(symbol);			//存放运算符。
	init_stack(charnum);		//存放字符类型的数据，准备把字符串数据转化为int类型。
	link_stack_num num_stack;		//存放转换成int类型的数据。
	init_stack_num(num_stack);

	int digit = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		char c = str[i];
		if (c == '(')
		{
			in_stack(symbol, c);
		}
		else
		{
			if (is_operator(c) || c == ')')
			{
				if (!empty_stack(charnum))
				{
					int num = 0;
					char rv;
					for (int i = 1; i <= digit; i++)		//数据输入完毕，合并数据。
					{
						int n = 1;
						for (int j = 1; j < i; j++)		//i是弹出栈的数据的位数。比如i=2，弹出数据十位数。
						{
							n = n * 10;
						}
						out_stack(charnum, rv);
						num = num + n * (rv - '0');		//计算机里存的'1'是ASCII编码值，为49减去0的ASCII编码值'0'，得到1。
					}
					in_stack_num(num_stack, num);
					digit = 0;		//合并数据后初始化digit。
				}
				if (is_operator(c))
				{
					if (empty_stack(symbol))
						in_stack(symbol, str[i]);
					else
					{
						if (precede(get_top(symbol), str[i]))		//栈里的运算符优先级大于等于扫描到的运算符。
						{
							char op;
							int num1, num2;
							out_stack(symbol, op);
							out_stack_num(num_stack, num2);
							out_stack_num(num_stack, num1);
							num1 = calculate(num1, num2, op);
							in_stack_num(num_stack, num1);
						}
						else
						{
							in_stack(symbol, str[i]);
						}
					}
				}
				else
				{		//处理")"
					char op;
					int num1, num2;
					out_stack(symbol, op);
					out_stack_num(num_stack, num2);
					out_stack_num(num_stack, num1);
					num1 = calculate(num1, num2, op);

					in_stack_num(num_stack, num1);
					out_stack(symbol, op);		//弹出'('。
				}
			}
			else
			{		//扫描到数据
				in_stack(charnum, str[i]);
				digit++;
				if (str[i + 1] == '\0')		//处理最后输入的数字而没有把这个数字转换为int类型就结束循环的情况。
				{
					int num = 0;
					char rv;
					for (int i = 1; i <= digit; i++)		//数据输入完毕，合并数据。
					{
						int n = 1;
						for (int j = 1; j < i; j++)		//i是弹出栈的数据的位数。比如i=2，弹出数据十位数。
						{
							n = n * 10;
						}
						out_stack(charnum, rv);
						num = num + n * (rv - '0');		//计算机里存的'1'是ASCII编码值，为49减去0的ASCII编码值'0'，得到1。
					}
					in_stack_num(num_stack, num);
					digit = 0;		//合并数据后初始化digit。
				}
			}


		}

	}
	char op;
	int num1, num2;
	out_stack(symbol, op);
	out_stack_num(num_stack, num2);
	out_stack_num(num_stack, num1);
	int result = calculate(num1, num2, op);
	destroy_stack(symbol);
	destroy_stack(charnum);
	destroy_stack(num_stack);
	return result;

}

int main()
{
	//char s1[20] = "(())";
	//char s2[20] = "{[()]}";
	//char s3[20] = "{[()][(])}";
	//char s4[20] = "(((])))";
	//char s5[20] = "w";
	//char s6[50] = "haha(wow)[???!...(whatevet)]{}";
	//char s7[20] = "({[]}";
	//
	//check_bracket(s7);

	char s21[50] = "1+1";
	char s22[50] = "123+87";
	char s23[50] = "8*(3+1)";
	char s24[50] = "8*((3+1)+1)";
	char s25[50] = "((15/(7-(1+1)))*3)-(2+(1+1))";

	char s26[50];
	cin >> s26;

	printf("计算结果为：%d\n", infix_expression(s26));

	return 0;
}