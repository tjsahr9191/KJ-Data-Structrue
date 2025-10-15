//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);
BSTNode* find_node(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root) {

	if (root == NULL) return;

	Stack stack1;
	stack1.top = NULL;

	Stack stack2;
	stack2.top = NULL;

	push(&stack1, root);
	while (!isEmpty(&stack1)) {
		if (peek(&stack1)->left == NULL && peek(&stack1)->right == NULL) {
			printf("%d ", pop(&stack1)->item);
			continue;
		}
		if (peek(&stack1) == peek(&stack2)) {
			printf("%d ", pop(&stack1)->item);
			pop(&stack2);
			continue;
		}

		push(&stack2, peek(&stack1));

		if (peek(&stack2)->right != NULL)
			push(&stack1, peek(&stack2)->right);
		if (peek(&stack2)->left != NULL)
			push(&stack1, peek(&stack2)->left);
	}
}
BSTNode* findMinValueNode(BSTNode* node)
{
	BSTNode* current = node;

	while (current && current->left != NULL) {
		current = current->left;
	}

	return current;
}

BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	if (root == NULL) return root;

	if (value < root->item) {
		root->left = removeNodeFromTree(root->left, value);
	}
	else if (value > root->item) {
		root->right = removeNodeFromTree(root->right, value);
	}
	else {
		if (root->left == NULL) {
			BSTNode *temp = root->right;
			free(root);
			return temp;
		}
		if (root->right == NULL) {
			BSTNode *temp = root->left;
			free(root);
			return temp;
		}

		BSTNode* temp = findMinValueNode(root->right);

		root->item = temp->item;

		root->right = removeNodeFromTree(root->right, temp->item);
	}

	return root;
}

BSTNode* find_node(BSTNode *root, int value) {
	if (root == NULL) return NULL;
	if (root->item == value) return root;

	BSTNode *left = find_node(root->left, value);
	if (left != NULL) return left;

	BSTNode *right = find_node(root->left, value);
	if (right != NULL) return right;

	return NULL;
}

BSTNode* removeNodeFromTree(BSTNode *root, int value) {



}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
