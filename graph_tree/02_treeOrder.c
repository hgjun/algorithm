#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "macrofunctions.h"
#include "stack.h"

char infix_[1024];
char postfix_[1024];

void changeData(char *infix, char *postfix);
bool isOperator(char c);
int  precedence(char op);
void initPostfix(void);

/*

void changeData(char *infix, char *postfix)
{
}
bool isOperator(char c)
{
}
int  precedence(char op)
{
}

*/

void changeData(char *infix, char *postfix)
{
	memset(postfix_, '\0', 1024);  //initPostfix
	Stack stk;
	stkInit(&stk);

	int nSteps = 0;

	printf("Step %d: Init\n", nSteps++);
	printf("infix: %s\n", infix_);
	printf("postfix: %s\n", postfix_);

	while (*infix) {
		printf("\nStep %d: ", nSteps++);

		if (*infix == '(') {
			printf("parenthesis '('\n");
			printf("prev stack: ");
			stkDisplayChar(&stk);

			stkPush(&stk, *infix++);

			printf("infix: %s\n", infix);
			printf("postfix: %s\n", postfix_);
			printf("push parenthesis '('\n");
			printf("after stack: ");
			stkDisplayChar(&stk);
		}
		else if (*infix == ')') {
			printf("parenthesis ')'\n");
			printf("prev stack: ");
			stkDisplayChar(&stk);
			printf("infix: %s\n", infix);
			printf("postfix: %s\n", postfix_);

			while (stkGetTop(&stk) != '(') {
				*postfix++ = stkPop(&stk);
				*postfix++ = ' ';
			}
			stkPop(&stk);
			infix++;

			printf("pop every op between '(' and ')'\n");
			printf("after postfix: %s\n", postfix_);
			printf("after stack: ");
			stkDisplayChar(&stk);
		}
		else if (isOperator(*infix)) {
			printf("Op %c\n", *infix);
			printf("prev stack: ");
			stkDisplayChar(&stk);

			// Example 1.
			// infix   str  = 1 + 2
			// postfix str  = 1
			// current char = + 
			// If stack is empty then write the number to the prefix str = 1 2

			// Example 2.
			// infix   str  = 1 + 2 * 3
			// postfix str  = 1 2 
			// current char = *
			// current stk  = +
			// If 'precedence of stacktop +' < 'current op *' then push current op *
			// result  stk  = + *

			// Example 3.
			// infix   str  = 2 * 4 + 1
			// postfix str  = 2 4
			// current char = +
			// current stk  = *
			// If 'precedence of stacktop *' >= 'current op +' then pop stack (finish prev calculation op)
			// result  stk  = +

			// Example 4.
			// infix   str  = 2 * ( 4 + 1 )
			// postfix str  = 2 4
			// current char = +
			// current stk  = * (
			// If 'precedence of stacktop (' < 'current op +' then push current op +
			// -> if 2 * 4 + 1 then  [ first * (pop  stack) then after + ]
			// -> if * ( + )   then  [ first + (push stack) then after * ], by "stacktop '(' "
			// result  stk  = + ( *
			char currentOp = *infix;

			while (!stkIsEmpty(&stk) && precedence(stkGetTop(&stk)) >= precedence(*infix)) {
				*postfix++ = stkPop(&stk);
				*postfix++ = ' ';
			}
			stkPush(&stk, *infix++);

			printf("infix: %s\n", infix);
			printf("postfix: %s\n", postfix_);
			printf("push current op: %c\n", currentOp);
			printf("after stack: ");
			stkDisplayChar(&stk);
		}
		else if (*infix >= '0' && *infix <= '9') {
			char tmp[1024];
			char *t = tmp;
			do {
				*t++ = *infix;
				*postfix++ = *infix++;
			} while (*infix >= '0' && *infix <= '9');
			*postfix++ = ' ';
			*t = '\0';

			printf("Number %d\n", atoi(tmp));
			printf("infix: %s\n", infix);
			printf("postfix: %s\n", postfix_);
		}
		else {
			printf("Else\n");
			infix++;
		}
	}

	printf("\nStep %d: pop stack\n", nSteps);
	printf("stack: ");
	stkDisplayChar(&stk);

	while (stkIsEmpty(&stk) == false) {
		*postfix++ = stkPop(&stk);
		*postfix++ = ' ';
	}
	*postfix--;
	*postfix = '\0';

	PRTLN;
	printf("infix  : %s\n", infix_);
	printf("postfix: %s\n", postfix_);
	PRTLN;
	printf("======================================\n");
	PRTLN;
}

bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int  precedence(char op)
{
	switch (op) {
	case '(':           return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	default:           return 3;
	}
}


int main()
{
	int i;
	FILE *fp = fopen("02_treeOrder_input.txt", "r");
	int nLoops;
	char tmp[1024];

	nLoops = atoi(fgets(tmp, 2014, fp));

	FOR(i, nLoops) {
		PRT("Loop: %d\n", i);
		fgets(infix_, 1024, fp);
		infix_[strlen(infix_) - 1] = '\0';
		changeData(infix_, postfix_);
		//PRT("%s\n", infix_);
	}

	fclose(fp);
	system("pause");
	return 0;
}
