#pragma once

#define QUEUE_MAX_SIZE 100

typedef struct queue_t {
	int data[QUEUE_MAX_SIZE + 1];
	int front, rear;
	int maxSize;
} Queue;

void initQueue(Queue *q);
void enqueue(Queue *q, int v);
int  dequeue(Queue *q);
bool isEmptyQueue(Queue *q);
void displayQueue(Queue *q);

/*

void initQueue(Queue *q)
{

}

void enqueue(Queue *q, int v)
{

}

int  dequeue(Queue *q)
{

}

bool isEmptyQueue(Queue *q)
{

}

void displayQueue(Queue *q)
{

}

*/

void initQueue(Queue *q)
{
	q->front = q->rear = 0;
	q->maxSize = QUEUE_MAX_SIZE;
}

void enqueue(Queue *q, int v)
{
	if (q->rear == q->maxSize) {
		return; // overflow
	}

	if (q->front == q->rear) {
		q->front = 1;
		q->rear = 2;
		q->data[1] = v;
	}
	else {
		q->data[q->rear++] = v;
	}
}

int  dequeue(Queue *q)
{
	if (q->front == q->rear) {
		return -1; // empty queue
	}
	return q->data[q->front++];
}

bool isEmptyQueue(Queue *q)
{
	return (q->front == q->rear);
}

void displayQueue(Queue *q)
{
	printf("\nDisplay queue:\n");
	int i;
	for (i = q->front; i < q->rear; i++) {
		printf("%-3d", q->data[i]);
	}
	printf("\n");
}


/* Linked list
// Queue implementation start

 [1] [2] [3] [ ]
 array      : front = [1], rear = [ ]    front = rear -> empty
 linked list: front = [1], rear = [3]    front = rear -> 1 element is left
 
 
typedef struct node_t {
	int value;
	struct node_t *next;
} Node;

typedef struct queue_t {
	Node *front;
	Node *rear;
} Queue;

void initQueue    (Queue *q);
int  isEmptyQueue (Queue *q);
void enqueue      (Queue *q, int v);
int  dequeue      (Queue *q);
void displayQueue (Queue *q);

void initQueue(Queue *q)
{
	q->front = q->rear = NULL;
}

int isEmptyQueue(Queue *q)
{
	return (q->front == NULL);

}

void enqueue(Queue *q, int v)
{
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->value = v;
	newNode->next  = NULL;
	
	if (q->front == NULL) {
		q->front = newNode;
	}
	else {
		q->rear->next = newNode;
	}
	q->rear = newNode;
}

int  dequeue(Queue *q)
{
	if (q->front == NULL) {
		return -1; // empty queue;
	}
	
	Node *tmp = q->front;
	if (q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		q->front = q->front->next;
	}
	
	int v = tmp->value;
	free(tmp);
	return v;
}

void displayQueue(Queue *q) {
	Node *p = q->front;
	printf("\nDisplay queue:\n");
	for (p = q->front; p; p = p->next) {
		printf("%-3d", p->value);
	} 
}

*/