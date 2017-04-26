#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

typedef struct item_t {
	int weight;
	int value;
	int isChosen;
} Item;

typedef struct knapsack_t {
	int itemSize;
	Item item[100];

	int knapsackSize;
	int mat[100][100];   // without repetition
	int arr[100];        // with repetition
	int parent[100];     // with repetition
	int chosenItem[100]; // with repetition
} Knapsack;
Knapsack k;

int knapsackWith()
{
	FILL_ARRAY(k.arr, k.knapsackSize, 0);
	FILL_ARRAY(k.parent, k.knapsackSize, 0);
	//k.arr[0] = 0;

	int i, c;
	FOR(c, k.knapsackSize) {
		FOR(i, k.itemSize) {
			if (k.item[i].weight > c) {
				continue;
			}
			int chosen = k.arr[c - k.item[i].weight] + k.item[i].value;
			if (chosen > k.arr[c]) {
				k.arr[c] = chosen;
				k.chosenItem[c] = i;
				k.parent[c] = c - k.item[i].weight;
			}

		}
	}
}

void setIsChosenWith(){
	int i = k.itemSize;
	int c = k.knapsackSize;

	while (i >= 1) {
		if (k.mat[i][c] == k.mat[i - 1][c]) {
			k.item[i].isChosen = 0;
		}
		else {
			k.item[i].isChosen = 1;
			c = c - k.item[i].weight;
		}
		i--;
	}
}


int knapsackWithout(int i, int c)
{
	if (k.mat[i][c] != -1) {
		return k.mat[i][c]; // memoization
	}

	if (i == 0 || c == 0) {
		k.mat[i][c] = 0;
	}
	else if (k.item[i].weight > c) {
		k.mat[i][c] = knapsackWithout(i - 1, c);
	}
	else {

		int discarded = knapsackWithout(i - 1, c);
		int chosen = knapsackWithout(i - 1, c - k.item[i].weight) + k.item[i].value;
		if (discarded <= chosen) {
			k.mat[i][c] = chosen;
		}
		else {
			k.mat[i][c] = discarded;
		}
	}
	return k.mat[i][c];
}

void setIsChosenWithout(){
	int i = k.itemSize;
	int c = k.knapsackSize;

	while (i >= 1) {
		if (k.mat[i][c] == k.mat[i - 1][c]) {
			k.item[i].isChosen = 0;
		}
		else {
			k.item[i].isChosen = 1;
			c = c - k.item[i].weight;
		}
		i--;
	}
}

void computeKnapsackWithout()
{

}
int main()
{
	int i, c;
	freopen("10_knapsack_input.txt", "r", stdin);

	scanf("%d %d", &k.itemSize, &k.knapsackSize);
	FILL_MATRIX(k.mat, k.itemSize, k.knapsackSize, -1);

	FOR(i, k.itemSize) {
		scanf("%d", &k.item[i].weight);
	}
	FOR(i, k.itemSize) {
		scanf("%d", &k.item[i].value);
	}

	PRT("0-1 Knapsack problem without repetition\n\n");
	knapsackWithout(k.itemSize, k.knapsackSize);
	setIsChosenWithout();
	PRT("Calculate K[i][c]: \n");
	FORFROM(c, 0, k.knapsackSize) {
		PRTD(c);
	} PRTLN;
	FORFROM(i, 0, k.itemSize) {
		FORFROM(c, 0, k.knapsackSize) {
			if (k.mat[i][c] == -1) {
				PRT("   ");
				continue;
			}
			PRTD(k.mat[i][c]);
		}
		PRTLN;
	}
	PRTLN;

	PRT("Chosen items: \nitem    ");
	FOR(i, k.itemSize) {
		PRTD(i);
	}
	PRT("\nweight  ");
	FOR(i, k.itemSize) {
		PRTD(k.item[i].weight);
	}
	PRT("\nvalue   ");
	FOR(i, k.itemSize) {
		PRTD(k.item[i].value);
	}
	PRT("\nchosen  ");
	FOR(i, k.itemSize) {
		if (k.item[i].isChosen == 1) {
			PRT("o  ");
		}
		else {
			PRT("x  ");
		}
		//PRTD(k.item[i].isChosen);
	}
	PRTLN;
	PRT("\n\n--------------------------------------------------\n\n");
	PRT("0-1 Knapsack problem without repetition\n");
	knapsackWith();
	setIsChosenWith();
	PRT("Calculate K[c]: \n");
	FORFROM(c, 0, k.knapsackSize) {
		PRTD(c);
	} PRTLN;
	FORFROM(c, 0, k.knapsackSize) {
		PRTD(k.arr[c]);
	} PRTLN;
	FORFROM(c, 0, k.knapsackSize) {
		PRTD(k.chosenItem[c]);
	} PRTLN;
	FORFROM(c, 0, k.knapsackSize) {
		PRTD(k.parent[c]);
	} PRTLN;

	PRT("Chosen items: \nitem    ");
	c = k.knapsackSize;
	while (1) {
		PRTD(k.chosenItem[c]);
		if (k.parent[c] == 0) {
			break;
		}
		c = k.parent[c];
	}
	PRT("\nvalue   ");
	c = k.knapsackSize;
	while (1) {
		PRTD(k.item[k.chosenItem[c]].value);
		if (k.parent[c] == 0) {
			break;
		}
		c = k.parent[c];
	}
	_getch();
	return 0;
}
