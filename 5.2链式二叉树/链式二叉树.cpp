#include<iostream>
using namespace std;

typedef struct tree_node
{
	char data;
	struct tree_node* left, * right;
	/*struct tree_node* parent;*/
}tree_node, * tree;

void init_tree(tree& t)
{
	t = (tree_node*)malloc(sizeof(tree_node));
	t->left = NULL;
	t->right = NULL;
	//t->parent = NULL;
}

tree_node* insert(tree_node* t, int lr, char e)
{
	//if (t == NULL);
	if (t == NULL)
	{
		printf("插入失败，传入了空树结点。\n");
		return NULL;
	}
	tree_node* p = (tree_node*)malloc(sizeof(tree_node));
	if (p == NULL)
		return NULL;
	p->data = e;
	p->left = NULL;
	p->right = NULL;

	if (lr == -1)
	{
		if (t->left == NULL)
		{
			t->left = p;
		}
		else
		{
			printf("插入失败，插入结点已有左叶子。\n");
		}
	}
	else if (lr == 1)
	{
		if (t->right == NULL)
		{
			t->right = p;
		}
		else
		{
			printf("插入失败，插入结点已有右叶子。\n");
		}
	}
	else
	{
		printf("插入失败，输入lr错误\n");
		return NULL;
	}

	return p;
}

void print_preorder(tree t)
{
	if (t != NULL)
	{
		printf("%c", t->data);
		print_preorder(t->left);
		print_preorder(t->right);
	}
}

void print_inorder(tree t)
{
	if (t != NULL)
	{
		print_inorder(t->left);
		printf("%c", t->data);
		print_inorder(t->right);
	}
}

void print_postorder(tree t)
{
	if (t != NULL)
	{
		print_postorder(t->left);
		print_postorder(t->right);
		printf("%c", t->data);
	}
}

static tree_node* temp = NULL;
static tree_node* pre = NULL;
void prenode_inorder(tree t, tree_node* p)
{
	if (t != NULL)
	{
		prenode_inorder(t->left, p);
		if (t == p)
		{
			pre = temp;
		}
		else
		{
			temp = t;
		}
		prenode_inorder(t->right, p);
	}
}


int main()
{
	tree A = NULL;
	init_tree(A);
	A->data = 'A';


	tree_node* B = (tree_node*)malloc(sizeof(tree_node));
	B->data = 'B';
	B->left = NULL;
	B->right = NULL;

	A->left = B;
	tree_node* C = insert(A, 1, 'C');

	tree_node* D = insert(B, -1, 'D');
	tree_node* E = insert(B, 1, 'E');
	tree_node* G = insert(D, 1, 'G');
	tree_node* F = insert(C, -1, 'F');


	print_preorder(A);
	cout << endl;
	print_inorder(A);
	cout << endl;
	print_postorder(A);
	cout << endl;

	prenode_inorder(A, D);
	if (pre == NULL)
		printf("结点没有前驱\n");
	else
		printf("前驱为：%c\n", pre->data);

	return 0;
}