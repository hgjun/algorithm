#include <stdio.h>
#include <stdlib.h>
#include "macroFunctions.h"

int f[101];

void fibonacci(int *arr, int n)
{
	if (n > 3) {
		int i;
		arr[1] = arr[2] = 1;
		FORFROM(i, 3, n) {
			arr[i] = arr[i - 2] + arr[i - 1];
		}
	}
}

int main(void)
{
	int i, n;
	n = 10;
	fibonacci(f, n);

	FOR(i, n) {
		PRTD(f[i]);
	}
	PRTLN;

	system("pause");
	return 0;
}
