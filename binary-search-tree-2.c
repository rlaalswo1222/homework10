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
	printf("[----- [김민재] [2021041070] -----]\n");
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
	*h = (Node*)malloc(sizeof(Node)); // 헤드노드 동적 할당
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
		recursiveInorder(ptr->left); // 왼쪽서브트리 먼저 순회
		printf(" [%d] ", ptr->key);// 현재 노드 출력
		recursiveInorder(ptr->right);  // 그 후 오른쪽서브트리 순회 
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;) // 스택이 공백 될때까지 반복
	{
		for(; node; node = node->left)  // 
			push(node); //스택에 삽입
		node = pop(); // 스택에서 값 가져옴

		if(!node) break;
		printf(" [%d] ", node->key); 

		node = node->right; // 오른쪽 자식노드로 이동
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

	for(;;) // 큐가 공백이 될때까지 반복
	{
		ptr = deQueue(); //큐에서 값 가져옴
		if(ptr) {
			printf(" [%d] ", ptr->key); //노드 출력

			if(ptr->left)
				enQueue(ptr->left); //왼쪽 자식노드가 존재하면 큐에 삽입
			if(ptr->right)
				enQueue(ptr->right); // 오른쪽 자식노드가 존재하면 큐에 삽입
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //삽입할 노드 생성
	newNode->key = key; // 노드의 데이터값을 입력값으로 지정
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { // 루트 노드가 없을 시
		head->left = newNode; // 삽입할 노드를 루트 노드로 지정
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // 현재노드로 활용 

	Node* parentNode = NULL; // 부모노드 = 현재노드의 이전노드로 활용
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
		if(ptr->key < key) // 만약 입력값이 현재 노드보다 크다면
			ptr = ptr->right; // 오른쪽 자식노드로 이동
		else // 아니라면
			ptr = ptr->left; // 왼쪽 자식노드로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  // 만약 부모노드의 값이 입력값보다 크다면
		parentNode->left = newNode; // 부모노드의 왼쪽 자식노드를 삽입할 노드로 지정
	else
		parentNode->right = newNode; // 부모노드의 오른쪽 자식노드를 삽입할 노드로 지정
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) { // 헤드노드가 없다면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {  // 루트노드가 없다면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; // 현재 노드로 활용



	Node* parent = NULL; //부모노드 
	Node* ptr = root; // 현재노드 

	while((ptr != NULL)&&(ptr->key != key)) { // 입력값과 현재 노드 값이 같거나, 모든 노드를 탐색할때까지 반복
		if(ptr->key != key) { // 입력값과 현재 노드 값과 다름

			parent = ptr;	/* save the parent */

			if(ptr->key > key) // 입력값이 현재 노드 값보다 작다면
				ptr = ptr->left; // 왼쪽 자식노드로 이동
			else
				ptr = ptr->right; //오른쪽 자식노드로 이동
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) // 노드가 비었다면
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //만약 리프노드라면
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) // 부모노드의 왼쪽 자식노드가 현재 노드라면
				parent->left = NULL;
			else // 오른쪽 자식노드라면
				parent->right = NULL;
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr); //현재노드 동적할당 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // 자식노드가 하나라면
	{
		Node* child;
		if (ptr->left != NULL) // 왼쪽 자식노드가 있다면
			child = ptr->left; // child에 자식노드를 담음
		else
			child = ptr->right; // "

		if(parent != NULL) // 부모노드가 없다면
		{
			if(parent->left == ptr) // 부모노드의 왼쪽 자식노드가 현재노드라면
				parent->left = child; // 부모노드의 왼쪽 자식노드를 현재노드의 자식노드로 설정
			else
				parent->right = child; // "
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; 
		}

		free(ptr); //현재노드 동적할당 해제
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
		parent = candidate; //후보 노드의 부모노드
		candidate = candidate->left; // 왼쪽 자식노드로 이동
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) // 후보노드의 부모노드의 오른쪽 자식노드가 후보노드라면
		parent->right = candidate->right; // 부모노드의 오른쪽 자식노드는 후보노드의 오른쪽 자식노드를 가리킴
	else
		parent->left = candidate->right; // 부모노드의 왼쪽 자식노드는 후보노드의 오른쪽 자식노드를 가리킴

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // 현재 노드값을 candidate의 값으로 지정

	free(candidate); // 해제
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left); //노드의 왼쪽,오른쪽 자식노드 해제
		freeNode(ptr->right);
		free(ptr); //자식노드 해제 후 해당노드 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //루트노드가 없다면
	{
		free(head); //헤드노드 해제
		return 1;
	}

	Node* p = head->left;

	freeNode(p); //헤드노드 제외 해제

	free(head); //헤드노드 해제
	return 1;
}



Node* pop() //스택에서 제거
{
	if (top < 0) return NULL; //비어있다면
	return stack[top--]; //스택에 있는 값을 가져온 후 top을 한칸 내림
}

void push(Node* aNode) //스택에 추가 
{
	stack[++top] = aNode;//스택의 top을 한칸 증가시킨 후 그 자리에 추가
}


void printStack() //스택 원소 출력
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue() // 큐에서 제거
{
	if (front == rear) { // 큐에서 제거
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front를 한칸 증가시켜 그 원소를 빼옴 
	return queue[front];

}

void enQueue(Node* aNode) // 큐에 추가
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;// 현재 rear에서 한칸 증가
		// 원형큐이기 때문에 큐 사이즈보다 크면 다시 처음부터 원소가 삽입되어야함. 그러므로 큐 사이즈로 나머지 연산
	if (front == rear) { // 큐가 꽉찼으면
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;//값추가 
}





