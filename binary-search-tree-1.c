/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;             // 노드의 키 값
    struct node *left;   // 왼쪽 자식 노드의 포인터
    struct node *right;  // 오른쪽 자식 노드의 포인터
} Node;


int initializeBST(Node** h); /*이진 탐색 트리의 노드를 초기화하는 함수*/

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [김예진]  [2022041035] -----]\n");

	char command; // 입력받은 명령어를 저장하는 변수
	int key; // 입력받은 키 값을 저장하는 변수
	Node* head = NULL; 
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* 트리가 비어 있지 않으면 트리에서 할당된 모든 노드를 제거 */
	if (*h != NULL)
		freeBST(*h);

	/* 헤드 노드 생성*/
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* 루트 노드 */
	(*h)->right = *h; /* 헤드 노드의 right 포인터를 자기 자신을 가리키도록 설정 */
	(*h)->key = -9999; /* 헤드 노드의 key 값을 임의로 설정 */
	return 1;
}


void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);  // 왼쪽 서브트리를 중위 순회로 방문
		printf(" [%d] ", ptr->key);  // 현재 노드를 출력
		inorderTraversal(ptr->right);  // 오른쪽 서브트리를 중위 순회로 방문
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);  // 현재 노드를 출력
		preorderTraversal(ptr->left);  // 왼쪽 서브트리를 전위 순회로 방문
		preorderTraversal(ptr->right);  // 오른쪽 서브트리를 전위 순회로 방문
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);  // 왼쪽 서브트리를 후위 순회로 방문
		postorderTraversal(ptr->right);  // 오른쪽 서브트리를 후위 순회로 방문
		printf(" [%d] ", ptr->key);  // 현재 노드를 출력
	}
}


int insert(Node* head, int key)
{
	// 새로운 노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		// 트리가 비어있을 경우 새로운 노드를 루트로 설정
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
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
		if(ptr->key < key)
			ptr = ptr->right; // 오른쪽 서브트리로 이동
		else
			ptr = ptr->left; // 왼쪽 서브트리로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode; // 왼쪽 자식으로 연결
	else
		parentNode->right = newNode; // 오른쪽 자식으로 연결

	return 1;
}


int deleteLeafNode(Node* head, int key)
{
	// 헤드 노드가 NULL인 경우 삭제할 노드가 없음을 출력하고 -1을 반환
	if (head == NULL) {
		printf("\n 삭제할 노드가 없습니다!!\n");
		return -1;
	}

	// 헤드 노드의 왼쪽 자식이 NULL인 경우 삭제할 노드가 없음을 출력하고 -1을 반환
	if (head->left == NULL) {
		printf("\n 삭제할 노드가 없습니다!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	// ptr이 NULL이 아닐 때까지 반복
	while(ptr != NULL) {

		// ptr의 키가 삭제할 키와 일치하는 경우
		if(ptr->key == key) {
			// ptr이 리프 노드인 경우
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				// ptr을 해제
				free(ptr);
			}
			else {
				// 노드가 리프 노드가 아닌 경우 해당 메시지를 출력
				printf("노드 [%d]는 리프 노드가 아닙니다\n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// 삭제할 키에 해당하는 노드를 찾을 수 없는 경우 해당 메시지를 출력
	printf("키 [%d]에 해당하는 노드를 찾을 수 없습니다\n ", key);

	return 1;
}



Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // 포인터가 NULL인 경우
		return NULL; // NULL을 반환

	if(ptr->key < key) // 현재 노드의 키 값이 찾는 키 값보다 작은 경우
		ptr = searchRecursive(ptr->right, key); // 오른쪽 서브트리에서 재귀적으로 검색 수행
	else if(ptr->key > key) // 현재 노드의 키 값이 찾는 키 값보다 큰 경우
		ptr = searchRecursive(ptr->left, key); // 왼쪽 서브트리에서 재귀적으로 검색 수행

	/* if ptr->key == key */
	return ptr; // 찾은 노드 포인터 반환
}

Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left; // 포인터를 헤드의 왼쪽 자식으로 초기화

	while(ptr != NULL) // 포인터가 NULL이 아닐 때까지 반복
	{
		if(ptr->key == key) // 현재 노드의 키 값이 찾는 키 값과 같은 경우
			return ptr; // 해당 노드 포인터 반환

		if(ptr->key < key) // 현재 노드의 키 값이 찾는 키 값보다 작은 경우
			ptr = ptr->right; // 오른쪽 자식으로 이동
		else
			ptr = ptr->left; // 현재 노드의 키 값이 찾는 키 값보다 큰 경우, 왼쪽 자식으로 이동
	}

	return NULL; // 찾는 키 값에 해당하는 노드를 찾지 못한 경우 NULL 반환
}

void freeNode(Node* ptr)
{
	if(ptr) { // 포인터가 NULL이 아닌 경우
		freeNode(ptr->left); // 왼쪽 서브트리 해제
		freeNode(ptr->right); // 오른쪽 서브트리 해제
		free(ptr); // 현재 노드 해제
	}
}

int freeBST(Node* head)
{
	if(head->left == head) // 헤드의 왼쪽 자식이 헤드 자신인 경우 (트리가 비어있는 경우)
	{
		free(head); // 헤드 노드 해제
		return 1; // 성공적으로 해제되었음을 나타내는 값 반환
	}

	Node* p = head->left; // 포인터를 헤드의 왼쪽 자식으로 초기화

	freeNode(p); // 트리의 모든 노드 해제

	free(head); // 헤드 노드 해제
	return 1; // 성공적으로 해제되었음을 나타내는 값 반환
}




