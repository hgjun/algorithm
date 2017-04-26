#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include "macrofunctions.h"


int columns_[100];

int matSize_;
int mat_[100][100];
int bestK_[100][100];

int main(void)
{
	freopen("05_matrixMultiplication_input.txt", "r", stdin);

	scanf("%d", &matSize_);

	int i, j, l, k;

	FORFROM(i, 0, matSize_) {
		scanf("%d", &columns_[i]);
	}

	// mat[i][j] = mat[i][k] + mat[k+1][j] + col[i-1] col[k] col[j], k = i ~ j - 1
	// mat[i][i] = 0;
	// i <= j
	// i = 1 ~ n - 1
	// l = 1 ~ n - 1
	// j = i + l
	FOR(i, matSize_) {
		FOR(j, matSize_) {
			if (i == j) {
				mat_[i][j] = 0;
			}
			else if (i < j) {
				mat_[i][j] = INT_MAX;
			}
			else {
				mat_[i][j] = -1;
			}
			bestK_[i][j] = 0;
		}
	}

	int tmpCost;
	FOR(l, matSize_ - 1) {
		FOR(i, matSize_ - l) {
			j = i + l;

			FORFROM(k, i, j - 1) {
				tmpCost = mat_[i][k] + mat_[k + 1][j] + columns_[i - 1] * columns_[k] * columns_[j];
				if (tmpCost < mat_[i][j]) {
					mat_[i][j] = tmpCost;
					bestK_[i][j] = k;
				}
			}
		}
	}

	FORFROM(i, 0, matSize_) {
		PRTD(columns_[i]);
	}
	PRTLN; PRTLN;
	FOR(i, matSize_) {
		FOR(j, matSize_) {
			printf("%-10d", mat_[i][j]);
		}
		PRTLN;
	}
	PRTLN; PRTLN;
	FOR(i, matSize_) {
		FOR(j, matSize_) {
			printf("%-10d", bestK_[i][j]);
		}
		PRTLN;
	}
	PRTLN;
	_getch();
	return 0;
}
