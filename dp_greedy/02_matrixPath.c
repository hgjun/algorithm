#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "macrofunctions.h"

int nRows_;
int nCols_;

int mat_[100][100];
int cost_[100][100];

int main(void)
{
	freopen("02_matrixPath_input.txt", "r", stdin);

	scanf("%d %d", &nRows_, &nCols_);

	int i, j;
	FOR(i, nRows_) {
		FOR(j, nCols_) {
			scanf("%d", &mat_[i][j]);
			cost_[i][j] = 0;
		}
	}

	cost_[1][1] = mat_[1][1];
	FORFROM(i, 2, nRows_) {
		cost_[i][1] = cost_[i - 1][1] + mat_[i][1];
	}
	FORFROM(j, 2, nRows_) {
		cost_[1][j] = cost_[1][j - 1] + mat_[1][j];
	}
	FORFROM(i, 2, nRows_) {
		FORFROM(j, 2, nCols_) {
			cost_[i][j] = MAX(cost_[i - 1][j], cost_[i][j - 1]) + mat_[i][j];
		}
	}

	FOR(i, nRows_) {
		FOR(j, nCols_) {
			PRTD(mat_[i][j]);
		}
		PRTLN;
	}
	PRTLN; PRTLN;

	FOR(i, nRows_) {
		FOR(j, nCols_) {
			PRTD(cost_[i][j]);
		}
		PRTLN;
	}
	PRTLN;

	_getch();
	return 0;
}
