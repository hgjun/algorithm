#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STK_MAX_SIZE 100


typedef struct stack_t {
	int data[STK_MAX_SIZE + 1];
	int top;
	int maxSize;
} Stack;

void stkInit(Stack *stk);
void stkPush(Stack *stk, int v);
int  stkPop(Stack *stk);
int  stkGetTop(Stack *stk);
bool stkIsEmpty(Stack *stk);
void stkDisplay(Stack *stk);
void stkDisplayChar(Stack *stk);

/*

void stkInit(Stack *stk)
{

}

void stkPush(Stack *stk, int v)
{

}

int stkPop(Stack *stk)
{

}

int stkGetTop(Stack *stk)
{

}

bool stkIsEmpty(Stack *stk)
{

}

void stkDisplay(Stack *stk)
{

}

void stkDisplayChar(Stack *stk)
{

}

*/


void stkInit(Stack *stk)
{
	stk->top = 0;
	stk->maxSize = STK_MAX_SIZE;
}

void stkPush(Stack *stk, int v)
{
	if (stk->top == stk->maxSize) {
		printf("Push fail: stack overflow\n");
		return;
	}
	stk->data[++stk->top] = v;
}

int stkPop(Stack *stk)
{
	if (stk->top == 0) {
		printf("Pop fail: stack underflow\n\n");
		return -1;
	}
	return stk->data[stk->top--];
}

int stkGetTop(Stack *stk)
{
	if (stk->top == 0) {
		printf("Get top fail: empty stack\n\n");
		return -1;
	}
	return stk->data[stk->top];
}

bool stkIsEmpty(Stack *stk)
{
	return (stk->top == 0);
}

void stkDisplay(Stack *stk)
{
	printf("Stack display\n");
	int i;
	for (i = 1; i <= stk->top; i++) {
		printf("%3d", stk->data[i]);
	}
	printf("\n\n");
}

void stkDisplayChar(Stack *stk)
{
	printf("Stack display\n");
	int i;
	for (i = 1; i <= stk->top; i++) {
		printf("%3c", stk->data[i]);
	}
	printf("\n\n");
}

/* TEST CODE

int main(void)
{
	Stack stk;
	stkInit(&stk);

	if (stkIsEmpty(&stk)) {
		printf("Empty stack\n");
	}
	else {
		printf("Not empty stack\n");
	}
	stkPop(&stk);
	stkGetTop(&stk);
	stkDisplay(&stk);

	stkPush(&stk, 1);
	stkPush(&stk, 2);
	stkPush(&stk, 3);
	stkPush(&stk, 4);
	stkDisplay(&stk);

	printf("Pop %d\n", stkPop(&stk));
	stkDisplay(&stk);

	printf("Get top %d\n", stkGetTop(&stk));
	stkDisplay(&stk);

	if (stkIsEmpty(&stk)) {
		printf("Empty stack\n");
	}
	else {
		printf("Not empty stack\n");
	}
	system("pause");
	return 0;
}

Empty stack
Pop fail: stack underflow

Get top fail: empty stack

Stack display


Stack display
1  2  3  4

Pop 4
Stack display
1  2  3

Get top 3
Stack display
1  2  3

Not empty stack
계속하려면 아무 키나 누르십시오 . . .
*/

#endif