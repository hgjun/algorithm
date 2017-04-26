#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macrofunctions.h"

// Sieve of Eratosthenes
bool num[101];
unsigned int primeNum[100];

int main()
{
	unsigned int size = 100;
	unsigned int i, j;

	FOR(i, size) {
		num[i] = true;
	}
	num[1] = false;

	unsigned int sqr_i = 4; // 2 * 2
	i = 2;
	while (sqr_i <= size) {
		if (num[i]) {
			for (j = sqr_i; j <= size; j += i) {
				num[j] = false;
			}
		}
		i++;
		sqr_i = i * i;
	}

	FOR(i, size) {
		PRTD(num[i]);
		if (i % 10 == 0) PRTLN;
	}
	PRTLN;

	FILL_ARRAY(primeNum, size, 0);
	j = 1;
	FOR(i, size) {
		if (num[i] == true) {
			primeNum[j++] = i;
		}
	}
	PRTLN;

	FOR(i, size) {
		if (primeNum[i] == 0) {
			break;
		}
		PRTD(primeNum[i]);
	}
	PRTLN;
	system("pause");
	return 0;
}

