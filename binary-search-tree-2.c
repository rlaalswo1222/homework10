/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE	20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE	20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[----- [�����] [2021041070] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // ����� ���� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left); // ���ʼ���Ʈ�� ���� ��ȸ
		printf(" [%d] ", ptr->key);// ���� ��� ���
		recursiveInorder(ptr->right);  // �� �� �����ʼ���Ʈ�� ��ȸ 
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;) // ������ ���� �ɶ����� �ݺ�
	{
		for(; node; node = node->left)  // 
			push(node); //���ÿ� ����
		node = pop(); // ���ÿ��� �� ������

		if(!node) break;
		printf(" [%d] ", node->key); 

		node = node->right; // ������ �ڽĳ��� �̵�
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); // iterative Inorder(Node* node)

	for(;;) // ť�� ������ �ɶ����� �ݺ�
	{
		ptr = deQueue(); //ť���� �� ������
		if(ptr) {
			printf(" [%d] ", ptr->key); //��� ���

			if(ptr->left)
				enQueue(ptr->left); //���� �ڽĳ�尡 �����ϸ� ť�� ����
			if(ptr->right)
				enQueue(ptr->right); // ������ �ڽĳ�尡 �����ϸ� ť�� ����
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //������ ��� ����
	newNode->key = key; // ����� �����Ͱ��� �Է°����� ����
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { // ��Ʈ ��尡 ���� ��
		head->left = newNode; // ������ ��带 ��Ʈ ���� ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // ������� Ȱ�� 

	Node* parentNode = NULL; // �θ��� = �������� �������� Ȱ��
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ���� �Է°��� ���� ��庸�� ũ�ٸ�
			ptr = ptr->right; // ������ �ڽĳ��� �̵�
		else // �ƴ϶��
			ptr = ptr->left; // ���� �ڽĳ��� �̵�
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  // ���� �θ����� ���� �Է°����� ũ�ٸ�
		parentNode->left = newNode; // �θ����� ���� �ڽĳ�带 ������ ���� ����
	else
		parentNode->right = newNode; // �θ����� ������ �ڽĳ�带 ������ ���� ����
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) { // ����尡 ���ٸ�
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {  // ��Ʈ��尡 ���ٸ�
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; // ���� ���� Ȱ��



	Node* parent = NULL; //�θ��� 
	Node* ptr = root; // ������ 

	while((ptr != NULL)&&(ptr->key != key)) { // �Է°��� ���� ��� ���� ���ų�, ��� ��带 Ž���Ҷ����� �ݺ�
		if(ptr->key != key) { // �Է°��� ���� ��� ���� �ٸ�

			parent = ptr;	/* save the parent */

			if(ptr->key > key) // �Է°��� ���� ��� ������ �۴ٸ�
				ptr = ptr->left; // ���� �ڽĳ��� �̵�
			else
				ptr = ptr->right; //������ �ڽĳ��� �̵�
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) // ��尡 ����ٸ�
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //���� ���������
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) // �θ����� ���� �ڽĳ�尡 ���� �����
				parent->left = NULL;
			else // ������ �ڽĳ����
				parent->right = NULL;
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr); //������ �����Ҵ� ����
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // �ڽĳ�尡 �ϳ����
	{
		Node* child;
		if (ptr->left != NULL) // ���� �ڽĳ�尡 �ִٸ�
			child = ptr->left; // child�� �ڽĳ�带 ����
		else
			child = ptr->right; // "

		if(parent != NULL) // �θ��尡 ���ٸ�
		{
			if(parent->left == ptr) // �θ����� ���� �ڽĳ�尡 ��������
				parent->left = child; // �θ����� ���� �ڽĳ�带 �������� �ڽĳ��� ����
			else
				parent->right = child; // "
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; 
		}

		free(ptr); //������ �����Ҵ� ����
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right; 

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) 
	{
		parent = candidate; //�ĺ� ����� �θ���
		candidate = candidate->left; // ���� �ڽĳ��� �̵�
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) // �ĺ������ �θ����� ������ �ڽĳ�尡 �ĺ������
		parent->right = candidate->right; // �θ����� ������ �ڽĳ��� �ĺ������ ������ �ڽĳ�带 ����Ŵ
	else
		parent->left = candidate->right; // �θ����� ���� �ڽĳ��� �ĺ������ ������ �ڽĳ�带 ����Ŵ

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // ���� ��尪�� candidate�� ������ ����

	free(candidate); // ����
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //����� ����,������ �ڽĳ�� ����
		freeNode(ptr->right);
		free(ptr); //�ڽĳ�� ���� �� �ش��� ����
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //��Ʈ��尡 ���ٸ�
	{
		free(head); //����� ����
		return 1;
	}

	Node* p = head->left;

	freeNode(p); //����� ���� ����

	free(head); //����� ����
	return 1;
}



Node* pop() //���ÿ��� ����
{
	if (top < 0) return NULL; //����ִٸ�
	return stack[top--]; //���ÿ� �ִ� ���� ������ �� top�� ��ĭ ����
}

void push(Node* aNode) //���ÿ� �߰� 
{
	stack[++top] = aNode;//������ top�� ��ĭ ������Ų �� �� �ڸ��� �߰�
}


void printStack() //���� ���� ���
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() // ť���� ����
{
	if (front == rear) { // ť���� ����
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front�� ��ĭ �������� �� ���Ҹ� ���� 
	return queue[front];

}

void enQueue(Node* aNode) // ť�� �߰�
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;// ���� rear���� ��ĭ ����
		// ����ť�̱� ������ ť ������� ũ�� �ٽ� ó������ ���Ұ� ���ԵǾ����. �׷��Ƿ� ť ������� ������ ����
	if (front == rear) { // ť�� ��á����
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;//���߰� 
}





