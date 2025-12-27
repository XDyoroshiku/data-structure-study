#include<iostream>
using namespace std;

#define MaxSize 100
typedef struct tree_node
{
	int value;
	bool is_empty;
}tree_node;

void init_tree(tree_node t[])
{
	for (int i = 0; i < MaxSize; i++)
	{
		 t[i].is_empty = true;
	}
}

int main()
{
	tree_node t[MaxSize];
	init_tree(t);


	return 0;
}