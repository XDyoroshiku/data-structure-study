#include<iostream>
using namespace std;

typedef struct
{
	int* data;
	int length;
}ss_table;

void init_ss_table(ss_table &s)
{
	s.length = 0;
	s.data = (int*)malloc(sizeof(int));
}

int sq_search(ss_table s, int e)
{
	s.data[0] = e;
	int i;
	for (i = s.length; s.data[i] != e; i--);		//data[0]存的是要查找的元素，所以从data[i]而不是data[i-1]开始反向找
	return i;
}

void sq_insert(ss_table &s, int e)
{
	s.data[s.length] = e;
	s.length++;
}

void print_ss_table(ss_table s)
{
	for (int i = 0; i < 11; i++)
	{
		printf("%d, ", s.data[i]);
	}
	printf("\n顺序表的长度为：%d\n", s.length);
	printf("顺序表打印完成\n");
}

int binary_search(ss_table s, int e)
{
	int low = 0, high = s.length - 1;
	int mid;

	while (low <= high)
	{
		mid = (low + high) / 2;		//整数除法会直接舍弃小数部分。
		if (s.data[mid] == e)
		{
			return mid + 1;		//mid是数组下标
		}
		else if (s.data[mid] < e)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;		
		}
	}
	return -1;
}

int main()
{
	ss_table s;
	init_ss_table(s);

	sq_insert(s, 7);
	sq_insert(s, 10);
	sq_insert(s, 13);
	sq_insert(s, 16);
	sq_insert(s, 19);
	sq_insert(s, 29);
	sq_insert(s, 32);
	sq_insert(s, 33);
	sq_insert(s, 37);
	sq_insert(s, 41);
	sq_insert(s, 43);

	print_ss_table(s);

	/*printf("i == %d\n", sq_search(s, 52));*/		//顺序查找


	printf("%d\n", binary_search(s, 13));

	return 0;
}