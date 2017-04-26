#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

int step[21];
int size = 20;

// 3 ways to move step
// step + 1, step + 2, step + 3

// Count possible ways to reach n-th step

int countStepR(int n) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	if (step[n] >= 0) return step[n];
	step[n] = countStepR(n - 1) + countStepR(n - 2) + countStepR(n - 3);
	return step[n];
}

int step2[21];

int countStep(int n) {
	step[0] = 1;
	step[1] = 1;
	step[2] = 2;

	int i;
	FORFROM(i, 3, n) {
		step[i] = step[i - 1] + step[i - 2] + step[i - 3];
	}
}


int main(void)
{
	int i;
	FILL_ARRAY(step, size, -1);

	countStepR(20);
	FORFROM(i, 0, size) {
		PRT("%-3d ", step[i]);
	}
	PRTLN;

	countStep(20);
	FORFROM(i, 0, size) {
		PRT("%-3d ", step[i]);
	}
	PRTLN;

	_getch();
	return 0;
}
