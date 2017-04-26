#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

int main()
{
	int i, j;
	int m[12] = { 0, 1, 9, 2, 4, 5, 7, 3, 3, 4, 8, 9 };
	int r[12];
	FILL_ARRAY(r, 11, 0);

	int size = 0;

	PRT("Input:\n");
	FOR(i, 11) {
		PRTD(m[i]);
	}
	PRTLN; PRTLN;

	PRT("Longest increasing subsequence:\n");
	FOR(i, 11) {
		if (r[size] > m[i]) {
			while (r[size] > m[i]) {
				size--;
			}
		}


		if (r[size] < m[i]) {
			// skip r[size] == m[i]
			size++;
			r[size] = m[i];
		}
		FOR(j, size) {
			PRTD(r[j]);
		}
		PRTLN;
	}

	PRTLN;
	PRT("Result: size %d\n", size);
	FOR(i, size) {
		PRTD(r[i]);
	}
	PRTLN;
	_getch();
	return 0;
}
