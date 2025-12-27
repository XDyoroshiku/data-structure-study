#include<iostream>
using namespace std;

#define MaxSize 200
typedef struct
{
	char data[MaxSize];
	int length;
}sq_string;

bool init_string(sq_string &S)
{
	S.length = 0;
	printf("串初始化成功\n");
	return true;
}

bool get_substring(sq_string& Sub, sq_string S, int position, int len)
{
	if ((position + len - 1) > S.length)
	{
		printf("取字串失败，取的位置超出了主串的范围\n");
		return false;
	}
	for (int i = 0; i < len; i++)
	{
		Sub.data[i] = S.data[position - 1 + i];
		Sub.length++;
	}
	printf("取子串成功\n");
	return true;
}

void print_string(sq_string S)
{
	int length = S.length;
	if (length == 0)
	{
		printf("串为空\n");
		return;
	}
	printf("串为：\n");
	for (int i = 0; i < length; i++)
	{
		printf("%c", S.data[i]);
	}
	printf("\n串的长度为：%d\n", length);
	printf("打印串完成\n");
}

bool value_string(sq_string& S)
{
	int length = S.length;
	char ch;
	printf("输入进入字符串的值：(输入回车结束输入)\n");
	for (int i = 0; i < MaxSize; i++)
	{
		ch = cin.get();
		/*scanf_s("%c", &ch, 1);*/		//" %c"会读取第一个不带空格的字符，"%c"读取输入缓冲区的下一个字符。
		if (ch == '\n')				//scanf_s会把输入的字符都存到输入缓冲区，然后每次读取一定数量的字符或字符串。例如%3s会读取3个字符。
		{							//scanf_s("%c", &ch, 1);把一个字符写入到ch。
			printf("输入结束\n");	
			break;
		}
		S.data[i] = ch;
		S.length++;
	}
	if (S.length == 0)
	{
		cout << "子串为空\n";
		return false;
	}
	return true;
}

bool compare_string(sq_string s1, sq_string s2)
{
	if (s1.length != s2.length)
	{
		printf("输入的两个字符串长度不等\n");
		return false;
	}
	for (int i = 0; i < s1.length; i++)
	{
		if (s1.data[i] != s2.data[i])
		{
			printf("两个字符串不相等\n");
			return false;
		}
	}
	printf("两个字符串相等\n");
	return true;
}

bool index(sq_string S, sq_string s)
{
	int position = 1;
	int m = S.length;
	int n = s.length;
	sq_string sub_string;
	init_string(sub_string);
	for (int i = 0; i < m - n + 1; i++)
	{
		if (get_substring(sub_string, S, position, n))
		{
			if (compare_string(sub_string, s))
			{
				printf("匹配成功，主串相匹配的字符串的首位置为：%d\n", position);
				position++;
			}
			else
			{
				position++;
			}
			init_string(sub_string);
		}
		else
		{
			printf("匹配失败，没有匹配的字串。\n");		//S里取字串时超出了范围，说明前面的字串都不匹配。
			return false;
		}
	}
	return true;
}

bool index2(sq_string S, sq_string s, int position)
{
	int m = S.length;
	int n = s.length;
	int i = position-1, j = 0;
	while (position < m - n + 2 && j < n)		//postion = m-n+1时，主串只剩最后一个字串。
	{
		if (S.data[i] == s.data[j])
		{
			i++;
			j++;
		}
		else
		{
			i = position;
			j = 0;
			position++;
		}
	}
	if (j == n)
	{
		printf("匹配成功，主串相匹配的字符串的首位置为：%d\n", position);
		return true;
	}
	else
	{
		printf("匹配失败，没有匹配的字串。\n");
		return false;
	}
	//if (i == m - n + 1)		//有问题。匹配成功时，i有可能等于m-n+1。
	//{
	//	printf("匹配失败，没有匹配的字串。\n");
	//	return false;
	//}
	//else
	//{
	//	printf("匹配成功，主串相匹配的字符串的首位置为：%d\n", position);
	//	return true;
	//}

}

bool my_create_next(sq_string s, int next[])		//数组作为函数参数时会退化为指针，所以不用引用变量也行。
{
	int length = s.length;
	next[0] = 0;

	int i = 1, j = 0;
	while (i < length)
	{
		if (s.data[i] == s.data[j])
		{
			if (i - 1 == j)
			{
				next[i] = next[i - 1];
				i++;
				j++;
			}
			else
			{
				j++;
				next[i] = j;
				i++;
			}
		}
		else
		{
			if (j == 0)
			{
				next[i] = 0;
				i++;
			}
			else
				/*j = next[j];*/
				j = next[j-1];		//把next【j-1】的值看作前缀相等的部分有几个字符。因为数组下标是从0开始，所以下一次循环比较j=next【j-1】刚好是比较相等前缀的下一个。
									//next【i】数组下标：0, 1, 2, 3, 4, 5, 6, 7
									//字串：             A, B, A, C, A, B, A, B
									//next【i】的值：    0, 0, 1, 0, 1, 2, 3, 2
									//第123个字符ABA和第567个字符ABA相等。这时j = 3, i = 7, next【j - 1】就是next【2】。next【2】 = 1, 也就是ABA的第一个和第三个相等。因为123个字符ABA等于567个字符ABA, 所以第1个字符A等于第3个字符A等于第7个字符A。然后进入下一个循环，第12个字符AB和第78个字符AB匹配。
		}
			
	}
	
	next[length] = -2;
	printf("创建next数组成功。\n");
	return true;
}

bool my_kmp(sq_string S, sq_string s, int position)		//并非kmp，只是优化了暴力算法，不匹配时i会回退到i+1;
{
	int next[MaxSize];
	my_create_next(s, next);

	int m = S.length, n = s.length;
	int i = position-1, j = 0;

	while (position < m - n + 2 && j < n)
	{
		printf("i=%d, j=%d, position=%d\n", i, j, position);
		if (S.data[i] == s.data[j])
		{
			i++;
			j++;
		}
		else
		{
			/*j = next[j - 1];*/
			j = next[j];	
			if (j == 0)
			{
				i = position;
				position++;
			}
		}
	}
	if (j == n)
	{
		printf("匹配成功，主串相匹配的字符串的首位置为：%d\n", position);
		return true;
	}
	else
	{
		printf("匹配失败，没有匹配的字串。\n");
		return false;
	}

	return true;
}

bool get_next(sq_string s, int next[])		//数组作为函数参数时会退化为指针，所以不用引用变量也行。
{
	if (s.length == 0)
	{
		cout << "创建next数组失败，传入了空字符串。\n";
		return false;
	}

	int length = s.length;
	next[0] = 0;

	int i = 1, j = 0;
	while (i < length)
	{
		if (s.data[i] == s.data[j])
		{
				j++;
				next[i] = j;
				i++;
		}
		else
		{
			if (j == 0)
			{
				next[i] = 0;
				i++;
			}
			else
				j = next[j - 1];		//把next【j-1】的值看作前缀相等的部分有几个字符。因为数组下标是从0开始，所以下一次循环比较j=next【j-1】刚好是比较相等前缀的下一个。
										//next【i】数组下标：0, 1, 2, 3, 4, 5, 6, 7
										//字串：             A, B, A, C, A, B, A, B
										//next【i】的值：    0, 0, 1, 0, 1, 2, 3, 2
										//第123个字符ABA和第567个字符ABA相等。这时j = 3, i = 7, next【j - 1】就是next【2】。next【2】 = 1, 也就是ABA的第一个和第三个相等。因为123个字符ABA等于567个字符ABA, 所以第1个字符A等于第3个字符A等于第7个字符A。然后进入下一个循环，第12个字符AB和第78个字符AB匹配。
		}

	}
	next[length] = -2;
	printf("创建next数组成功。\n");
	return true;
}

bool kmp(sq_string S, sq_string s, int position)
{
	int next[MaxSize];
	if (!get_next(s, next))
		return false;

	int m = S.length, n = s.length;
	int i = position - 1, j = 0;

	while (i < m && j < n)		//为什么不是i<m-n+1?因为在对比S的最后一个主串时，如果第一个字符相等，i++,应该继续对比，而这时i=m-n+1,循环结束。
	{
		printf("i=%d, j=%d, position=%d\n", i, j, position);
		if (S.data[i] == s.data[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0)
			{
				i++;
				position = i + 1;
			}
			else
			{
				j = next[j - 1];
				position = i - j + 1;		//i - j得出主串与子串匹配的第一个元素的数组下标，加1得到是第几个。
			}
		}
	}
	if (j == n)
	{
		printf("匹配成功，主串相匹配的字符串的首位置为：%d\n\n", position);
		return true;
	}
	else
	{
		printf("匹配失败，没有匹配的字串。\n\n");
		return false;
	}

	return true;
}

int main()
{
	sq_string a;
	init_string(a);
	value_string(a);
	print_string(a);

	//sq_string sub;
	//init_string(sub);
	//get_substring(sub, a, 5, 5);
	//print_string(sub);

	sq_string b;
	init_string(b);
	value_string(b);
	print_string(b); 

	//int postion = 1;
	//index(a, b);
	//index2(a, b, 1);
	//index2(a, b, 4);
	//index2(a, b, 9);

	int next[MaxSize];
	//my_create_next(b, next);
	if(get_next(b, next))
		for (int i = 0; next[i] != -2; i++)
			printf("data[%d] = %d\n", i, next[i]);

	//my_kmp(a, b, 1);
	//my_kmp(a, b, 3);
	//my_kmp(a, b, 5);
	//my_kmp(a, b, 6);

	kmp(a, b, 1);
	kmp(a, b, 3);
	kmp(a, b, 5);
	kmp(a, b, 6);

	return 0;
 }