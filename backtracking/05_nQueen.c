#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macrofunctions.h"

int size_;
int cnt;

typedef struct row_t{
	int col;
} Row;

Row row[100];

bool isValid(int row);
void backTracking(int row);

bool isValid(int k)
{
	int i;
	int width, height;
	bool isDiagonal = false;

	FOR(i, (k - 1)) {
		if (row[i].col == row[k].col) return false; // same column

		height = k - i;
		width = (row[k].col - row[i].col > 0) ? row[k].col - row[i].col : row[i].col - row[k].col;
		isDiagonal = (height == width);
		if (isDiagonal) return false;
	}
	return true;
}

void backTracking(int k)
{
	if (size_ + 1 == k) {
		int i;
		FOR(i, size_) {
			PRTD(row[i].col);
		}
		PRTLN;
		cnt++;
		return;
	}

	int i;
	FOR(i, size_) {
		row[k].col = i;

		if (isValid(k)) {
			backTracking(k + 1);
		}
	}
}

int main()
{
	size_ = 4;
	cnt = 0;
	backTracking(1);
	PRT("\nTotal cnt %d\n", cnt);
	system("pause");
	return 0;
}