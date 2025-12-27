#include<iostream>
#include<stdlib.h>
using namespace std;


#define InitSize 5		//预定义宏定义，将InitSize替换为5，这样在顺序表初始化时可以灵活调整数据结构定义的长度
#define ListIncreament 5
typedef struct 
{
	int data[InitSize];		//data[]不用指针，SqList_static表示一个静态顺序表，L2.data[i]对应表中第i个位置的元素
	int MaxSize;
	int length;
}SqList_static;

void InitList_static(SqList_static& L)		//&L是引用传递，意味着对形参 L 的修改会反映到外部的实际变量
{
	L.MaxSize = InitSize;
	for (int i = 0; i < L.MaxSize; i++)		/*for (int i = 0; i < InitSize; i++)*/
	{
		L.data[i] = 0;		//将所有元素初始化为0
	}
	L.length = 0;		//顺序表当前长度为0
	printf("顺序表初始化成功\n");
} 

typedef struct
{
	int* data;
	int MaxSize;
	//int MaxSize = 10 -> error C5208: typedef 类不能使用未命名的类作为成员，不允许非静态数据成员作为成员初始值设定项;
	int length;	
}SqList_dynamic;

void InitList_dynamic(SqList_dynamic& L)
{
	L.MaxSize = InitSize;
	L.data = (int*)malloc(L.MaxSize * sizeof(int));
	for (int i = 0; i < L.MaxSize; i++)
	{
		L.data[i] = 0;		//将所有元素初始化为0
	}
	L.length = 0;		//顺序表当前长度为0
	printf("顺序表初始化成功\n");
}

void IncreaseList(SqList_dynamic& L, int IncreaseSize)
{
	L.MaxSize = L.MaxSize + IncreaseSize;

	int* newBase = (int*)realloc(L.data, (L.MaxSize) * sizeof(int));
	//int* p = L.data;
	//L.data = (int*)malloc((L.MaxSize) * sizeof(int));
	/// *for (int i = 0; i < L.MaxSize; i++)* /
	//for (int i = 0; i < L.length; i++)
	//{
	//	L.data[i] = p[i];		//p[i] 会自动转换为 *(p + i),即指针向后移动i个元素，每个元素大小为int 的 4 个字节。
	//}
	//free(p);

	if (newBase == NULL)
	{
		printf("内存分配扩展失败\n");
		return;
	}
	L.data = newBase;
	for (int i = L.length; i < L.MaxSize; i++)
	{
		L.data[i] = 0;		//初始化新增元素
	}
	

	printf("顺序表长度增加%d,新表最大容量为%d\n", IncreaseSize, L.MaxSize);
}


void printList(SqList_dynamic L)
{
	int ListLength = L.MaxSize;		//打印长度为MaxSize,方便查看表中实际值
	/*int ListLength = L.length;*/		
	
	if (ListLength == 0	|| L.data == nullptr)	//判断表长是否为0或malloc是否未分配
	{
		cout << "顺序表长为0，没有元素可打印" << endl;
	}
	else 
	{
		printf("顺序表当前长度:%d\n", L.length);
		/*printf("顺序表当前长度:%d\n", ListLength);*/
		for (int i = 0; i < ListLength; i++)
		{
			cout << "data[" << i << "] = " << L.data[i] << endl;
			/*printf("data[%d] = %d\n", i, L.data[i]);*/
		}
	}
}

void ListAlter(SqList_dynamic& L, int location, int e)
{
	int length = L.length;
	if (location < 1 || location > length)
	{
		printf("修改位置不合法，当前顺序表长度为%d，位置合法范围为[1, %d]\n", length, length);
	}
	else
	{
		L.data[location-1] = e;
		printf("修改成功\n");
	}
}

void ListInsert(SqList_dynamic& L, int location, int e)
{
	int length = L.length;
	if (location < 1 || location > length + 1)
	{
		printf("插入位置不合法，当前顺序表长度为%d，位置合法范围为[1, %d]\n", length, length+1);
	}

	else
	{
		if (length >= L.MaxSize)
		{
			IncreaseList (L, ListIncreament);
			printf("顺序表已动态扩容，新容量为%d\n", L.MaxSize);
		}
		/*for (int i = L.MaxSize; i > location; i--)*/
		for (int i = L.length; i >= location; i--)
		{
			L.data[i] = L.data[i - 1];
		}
		L.data[location - 1] = e;
		L.length++;
		printf("插入成功\n");
	}

}

int ListDelete(SqList_dynamic& L, int location, int &e)		//&e引用传递，保证将删除的值传回主函数
{
	int length = L.length;
	if (length == 0)
	{
		printf("顺序表已为空，无法删除\n");
		return 0;
	}
	if (location < 1 || location > length)
	{
		printf("删除位置不合法，当前顺序表长度为%d，位置合法范围为[1, %d]\n", length, length);
		return 0;
	}
	e = L.data[location-1];		//存储被删除值
	for (int i = location - 1; i < L.length - 1; i++)
	{
		L.data[i] = L.data[i + 1];
	}
	if (L.length > 0)		//L.data[length - 1]在length = 0时会越界。
	{
		L.data[length - 1] = 0;		//末尾元素重置为0
	}
	L.length--;
	printf("删除成功，删除的是第%d个元素，值为%d\n", location, e);
	return 1;
}

int GetElem(SqList_dynamic L, int location, int &e)
{
	int length = L.length;
	if (location < 1 || location > L.length)
	{
		printf("查找位置不合法，当前顺序表长度为%d，位置合法范围为[1, %d]\n", length, length);
		return 0;
	}
	e = L.data[location - 1];
	return 1;
}

int locateELem(SqList_dynamic L, int e)
{
	int length = L.length;
	int num = 0;
	for (int i = 0; i < length; i++)
	{
		//if (L.data[i] == e);		多写;表示一个空语句，条件成立后，执行一个空语句，而非return语句
		if (L.data[i] == e)
		{
			printf("顺序表中第%d个元素的值 = %d\n", i+1, e);
			num++;
		}
	}
	return num;
	
}

int main()
{
	/*SqList_static L1;*/
	SqList_dynamic L2;
	InitList_dynamic(L2);

	for (int i = 1; i < L2.MaxSize; i++)		//向顺序表中插入(顺序表容量-1)个元素
	{
		ListInsert(L2, i, i);
	}
	

	bool loop = true;		//true和1效果一样
	while (loop)
	{
		printf("\n请选择顺序表操作:\n 0.打印顺序表\n 1.顺序表容量增加5\n 2.向顺序表指定位置插入值\n 3.修改顺序表指定值\n 4.删除顺序表中指定位置的元素\n 5.按位查找顺序表中指定位置的值\n 6.按值查找顺序表中指定的值\n 7.结束程序\n");
		int operation;
		/*scanf("%d", &operation);*/
		cin >> operation;
		switch (operation)
		{
			case 0:
			{
				printList(L2);
				break;
			}
			case 1:
			{
				IncreaseList(L2, 5);
				break;
			}
			case 2:
			{
				printf("请输入要插入顺序表的位置和值:\n");
				int location, e;
				/*scanf("%d", &location);	*/	//&location是获取location变量的地址，scanf会将输入值写入到该地址指向的内存
				cin >> location;
				/*scanf("%d", &e);*/
				cin >> e;
				ListInsert(L2, location, e);
				break;
			}
			case 3:
			{
				printf("请输入要修改顺序表的位置和值:\n");
				int location, e;
				cin >> location;
				cin >> e;
				ListAlter(L2, location, e);
				break;
			}
			case 4:
			{
				printf("请输入要删除顺序表中元素的位置:\n");
				int location, deleteValue;
				cin >> location;
				int status = ListDelete(L2, location, deleteValue);
				if(status)
				{
					printf("成功获取被删除顺序表中元素，值为:%d\n", deleteValue);
				}
				else
				{
					printf("删除失败\n");
				}
				break;
			}
			case 5:
			{
				printf("请选择按位查找顺序表中元素的位置:\n");		//按位查找获取值
				int location, getValue;
				cin >> location;
				int status = GetElem(L2, location, getValue);
				if (status)
				{
					printf("查找成功，顺序表中第%d个元素的值为:%d\n", location, getValue);
				}
				else
				{
					printf("查找失败\n");
				}
				break;
			}
			case 6:
			{
				printf("请选择按值查找顺序表中元素的值:\n");
				int searchValue;
				cin >> searchValue;
				int matchNum = locateELem(L2, searchValue);
				if (matchNum)
				{
					printf("该顺序表中一共有%d个与%d匹配的值\n", matchNum, searchValue);
				}
				else
				{
					printf("该顺序表中没有与%d匹配的元素\n", searchValue);
				}
				break;
			}
			case 7:
			{
				loop = false;
				free(L2.data);		//malloc申请的内存需要手动free
				break;
			}

			default:
			{
				printf("输入错误，请输入0到7之间的整数");
				break;
			}
		}
	}
	
	
	return 0;
}