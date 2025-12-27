#include<iostream>
using namespace std;


typedef struct thread_tree_node
{
	char data;
	struct thread_tree_node* left, * right;
	int ltag, rtag;
}thread_tree_node, * thread_tree;

void init_tree(thread_tree& t)
{
	t = (thread_tree_node*)malloc(sizeof(thread_tree_node));
	t->left = NULL;
	t->right = NULL;
	t->ltag = 0;
	t->rtag = 0;
}

thread_tree_node* insert(thread_tree_node* t, int lr, char e)
{
	//if (t == NULL);
	if (t == NULL)
	{
		printf("插入失败，传入了空树结点。\n");
		return NULL;
	}
	thread_tree_node* p = (thread_tree_node*)malloc(sizeof(thread_tree_node));
	if (p == NULL)
		return NULL;
	p->data = e;
	p->left = NULL;
	p->right = NULL;
	t->ltag = 0;
	t->rtag = 0;

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

void pre_thread(thread_tree t, thread_tree_node*& pre)
{
	if (t != NULL)
	{
		if (t->left == NULL)
		{
			t->left = pre;
			t->ltag = 1;
		}
		if (pre != NULL && pre->right == NULL)
		{
			pre->right = t;
			pre->rtag = 1;
		}	
		pre = t;

		if (t->ltag == 0)		//对于只有右子树的非根结点，在前序化它本身时，会把它的left指向它的前驱。在前序化本身完成后会前序化它的左孩子（应该为空），但这时它的left指向它的前驱，进入了死循环。
			pre_thread(t->left, pre);
		if (t->rtag == 0)		//对于只有左子树的节点，在前序化它的左孩子时，会把左孩子的父节点也就是该结点的right指向它的左孩子。在前序化完它的左子树后，会前序化它的右子树（应该为空）但这时right指向了它的左孩子，进入了死循环。
			pre_thread(t->right, pre);
	}							//“先序线索化”时要检查时ltag, rtag时因为先序遍历是先修改结点，再递归左右孩子。而修改结点左空指针时会影响t->left；而在遍历完根结点后会先遍历它的左子树，再遍历它的右子树，而在修改结点的左孩子的右空指针后会影响t->right。两个修改可能会导致在遍历时进入死循环。
								//因为先序线索化的“根，左，右”顺序，导致它在线索化某个节点时可能会修改它的左空指针，导致访问这个结点的左孩子时访问到自己的前驱。（前驱在访问左孩子时回到该结点）
															    //在线索化某节点的左孩子时可能会修改该结点的右空指针，导致访问完这个结点的左子树后访问它的右孩子时又访问到了这个结点的左孩子。
								//总的来说，线索化“根”时，影响了访问左孩子；线索化“左孩子”时，影响了访问右孩子。
										
								
								//“中序线索化”。中序遍历的顺序是“左，根，右”。在线索化左孩子时，影响的是左孩子的左空指针和左孩子的左孩子的右空指针，不会影响到根结点；在线索化根结点时，影响的是它本身的左空指针和左孩子的右空指针，不会影响到该节点的右指针。不会在遍历该节点的右指针时出问题。

								//“后序线索化”。后序遍历的顺序时“左，右，根”。在线索化左孩子时，影响的是左孩子的左空指针和左孩子的左/右孩子的右空指针，不会影响该结点的右孩子；在线索化右孩子时，影响的是右孩子的左空指针和左孩子的右空指针，不会影响到该结点。不会在遍历该节点的右指针时出问题。
}

void make_pre_thread(thread_tree t)
{
	thread_tree_node* pre = NULL;
	pre_thread(t, pre);
	if (pre->right == NULL)	//pre指向最后一个结点。在先序中指向最后一个结点（右子树），在中序中指向最大的结点（最右）。
	{
		pre->rtag = 1;		//二叉树的所有空指针都被线索化，tag=1说明被线索化了。tag=0说明结点的左右指针没被线索化，在线索化之前它就有左或右孩子。
	}						//在“先序和中序线索化”时，设置最后结点的rtag==1，不影响遍历结果，但设置后表示空指针被线索化。
}							//对于“后序线索化”。如果最后一个结点（根节点）有右子树，那么不需要设置；如果根节点没有右子树，那么设置这个rtag==1也不影响遍历结果。
							//总的来说，三种顺序的线索化设置最后一个结点的rtag==1与否不影响实际的遍历结果，只是为了二叉树定义的统一。（所有空指针都被线索化）


void in_thread(thread_tree t, thread_tree_node* &pre)
{
	if (t != NULL)
	{
		in_thread(t->left, pre);

		if (t->left == NULL)
		{
			t->left = pre;
			t->ltag = 1;
		}
		if (pre != NULL && pre->right == NULL)
		{
			pre->right = t;
			pre->rtag = 1;
		}
		pre = t;
		
		in_thread(t->right, pre);
	}
}

void make_in_thread(thread_tree t)
{
	thread_tree_node* pre = NULL;
	in_thread(t, pre);
	if (pre->right == NULL)
		pre->rtag = 1;		//作用在前序线索化的注释里说明
}


void post_thread(thread_tree t, thread_tree_node*& pre)
{
	if (t != NULL)
	{
		post_thread(t->left, pre);

		post_thread(t->right, pre);

		if (t->left == NULL)
		{
			t->left = pre;
			t->ltag = 1;
		}
		if (pre != NULL && pre->right == NULL)
		{
			pre->right = t;
			pre->rtag = 1;
		}
		pre = t;
	}
}
void make_post_thread(thread_tree t)
{
	thread_tree_node* pre = NULL;
	post_thread(t, pre);
	if( pre->right == NULL)
		pre->rtag = 1;		//作用在前序线索化的注释里说明
}

void print_preorder(thread_tree t)		//二叉线索树前序打印（结点有左孩子的情况找不到该节点的前驱。因为left指针已经指向它的左孩子，所以在前序线索化时left指针不会指向该结点的前驱）
{
	while (t != NULL)
	{
		printf("%c", t->data);
		if (t->ltag == 0 && t->left != NULL)
			t = t->left;
		else
		{
			t = t->right;
		}
	}
	printf("\n二叉线索树前序打印完成。\n");
}

void print_inorder(thread_tree t)		//二叉线索树中序打印
{
	while (t->ltag == 0 && t->left != NULL)
	{
		t = t->left;
	}
	while (t != NULL)
	{
		printf("%c", t->data);
		if (t->rtag == 1)
		{
			t = t->right;
		}
		else
		{
			//if (t->right != NULL)		//在线索化后，t->right==NULL说明t是中序遍历最后一个结点。
			if (t->rtag == 0)
			{
				t = t->right;
				while (t->ltag == 0 && t->left != NULL)		//如果有左子树，那么此时t不是最小的。没有则说明此时t是最小的。
				{
					t = t->left;
				}
			}
			else
			{
				t = t->right;
			}
		}
	}
	printf("\n二叉线索树中序打印完成。\n");
}


typedef struct LinkNode
{
	char data;
	struct LinkNode* next;
}*LinkStack;

bool InitLinkStack(LinkStack& S)
{
	S = (LinkStack)malloc(sizeof(LinkNode));
	if (S == NULL)
	{
		printf("内存分配失败\n");
		return false;
	}
	S->data = 0;
	S->next = NULL;
	/*printf("链栈初始化成功\n");*/
	return true;
}

bool emptyStack(LinkStack S)
{
	if (S->next == NULL)
		return true;
	return false;
}

bool push(LinkStack S, char e)
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
	/*printf("%c插入成功\n", e);*/
	return true;
}

void printStack(LinkStack S)
{
	if (emptyStack(S))
	{
		printf("传入了空栈\n");
		return;
	}
	int i = 0;
	while (!emptyStack(S))		//正常来说判断条件应该是S->next != NULL
	{
		i++;
		S = S->next;
		printf("%c", S->data);
	}
}

void print_postorder(thread_tree t)		//二叉线索树后序打印（从后往前逆序打印，因为可能找不到后继结点。——结点有右孩子时，它的右指针被占用，不会被后序线索化）
{
	LinkStack S = NULL;
	InitLinkStack(S);
	while (t != NULL)
	{
		/*printf("%c", t->data);*/		//逆序打印
		push(S, t->data);				//传入栈，再正序打印。
		if (t->rtag == 0)
			t = t->right;
		else
		{
				t = t->left;
		}
	}
	printStack(S);
	printf("\n二叉线索树后序打印完成。\n");
}

int main()
{
	thread_tree A = NULL;
	init_tree(A);
	A->data = 'A';

	thread_tree_node* B = insert(A, -1, 'B');
	thread_tree_node* C = insert(A, 1, 'C');
	thread_tree_node* D = insert(B, -1, 'D');
	thread_tree_node* E = insert(B, 1, 'E');
	thread_tree_node* G = insert(D, 1, 'G');
	thread_tree_node* F = insert(C, -1, 'F');
	
	//make_pre_thread(A);
	//print_preorder(A);

	//make_in_thread(A);
	//print_inorder(A);

	make_post_thread(A);
	print_postorder(A);


	return 0;
}