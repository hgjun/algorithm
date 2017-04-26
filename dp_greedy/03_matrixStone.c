#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

typedef struct matrixStone_t {
	int rows;
	int cols;
	int types;

	int mat[100][100]; // rows x cols
	int maxScore[100][100]; // rows x types
} MatrixStone;

MatrixStone m;

int getScore(int type, int col);
int getMaxPrevScore(int currentType, int j);

int getScore(int type, int col)
{
	// (type, col) validation check is omitted
	if (type == 4) {
		return m.mat[1][col] + m.mat[3][col];
	}
	else {
		return m.mat[type][col];
	}
}

int getMaxPrevScore(int currentType, int j)
{
	// current pattern type: computable previous pattern types
	// type 1              : type 2, 3
	// type 2              : type 1, 3, 4
	// type 3              : type 1, 2
	// type 4              : type 2
	int score = 0;
	int prevCol = j - 1;

	switch (currentType) {
	case 1:
		score = MAX(m.maxScore[2][prevCol], m.maxScore[3][prevCol]);
		break;
	case 2:
		score = MAX(m.maxScore[1][prevCol], m.maxScore[3][prevCol]);
		score = MAX(score, m.maxScore[4][prevCol]);
		break;
	case 3:
		score = MAX(m.maxScore[1][prevCol], m.maxScore[2][prevCol]);
		break;
	case 4:
		score = m.maxScore[2][prevCol];
		break;
	}
	return score;
}

int main(void)
{
	freopen("03_matrixStone_input.txt", "r", stdin);

	scanf("%d %d", &m.rows, &m.cols);

	int i, t;
	FOR(t, m.rows) {
		FOR(i, m.cols) {
			scanf("%d", &m.mat[t][i]);
		}
	}

	m.types = 4;
	m.maxScore[1][1] = m.mat[1][1];
	m.maxScore[2][1] = m.mat[2][1];
	m.maxScore[3][1] = m.mat[3][1];
	m.maxScore[4][1] = m.mat[1][1] + m.mat[3][1];

	FOR(i, m.cols) {
		FOR(t, m.types) {
			m.maxScore[t][i] = getMaxPrevScore(t, i) + getScore(t, i);
		}
	}

	FOR(t, m.rows) {
		FOR(i, m.cols) {
			printf("%-4d", m.mat[t][i]);
		}
		PRTLN;
	}
	PRTLN;

	FOR(t, m.types) {
		FOR(i, m.cols) {
			printf("%-4d", m.maxScore[t][i]);
		}
		PRTLN;
	}
	PRTLN;
	PRTLN;

	_getch();
	return 0;
}
