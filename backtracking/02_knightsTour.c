#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macrofunctions.h"

// Backtracking: the knight's tour problem

#define N 8
#define MAX_SIZE 100

typedef struct knightMove_t {
	int x, y;
} KnightMove;

typedef struct knightTour_t {
	KnightMove mov[8 + 1];
	int movSize;

	int board[MAX_SIZE][MAX_SIZE];
	int size; // board size
	int nMoves;
	int maxMove;
} KnightTour;

KnightTour kt;

void displaySolution()
{
	int i, j;
	FOR(i, kt.size) {
		FOR(j, kt.size) {
			PRTD(kt.board[i][j]);
		}
		PRTLN;
	}
}

void setKnightMovement()
{
	kt.movSize = 8;
	int xMov[9] = { 0, 2, 1, -1, -2, -2, -1, 1, 2 };
	int yMov[9] = { 0, 1, 2, 2, 1, -1, -2, -2, -1 };
	int i;
	FOR(i, 8) {
		kt.mov[i].x = xMov[i];
		kt.mov[i].y = yMov[i];
	}
}

bool isValidMove(int x, int y)
{

	return (x >= 1 && x <= kt.size && y >= 1 && y <= kt.size && kt.board[x][y] == -1);
}

int solveKnightTour(int x, int y)
{
	if (kt.nMoves > kt.maxMove) {
		return true;
	}

	int i;
	int nextX, nextY;
	FOR(i, 8) {
		nextX = x + kt.mov[i].x;
		nextY = y + kt.mov[i].y;

		if (isValidMove(nextX, nextY)) {
			kt.board[nextX][nextY] = kt.nMoves++;
			if (solveKnightTour(nextX, nextY)) {
				return true;
			}
			else {
				// rollback for backtraking
				kt.board[nextX][nextY] = -1;
				kt.nMoves--;
			}
		}
	}
	return false;
}


int main(void)
{
	// Init
	setKnightMovement();
	kt.size = 8;
	kt.maxMove = 8 * 8;

	FILL_MATRIX(kt.board, kt.size, kt.size, -1);
	kt.nMoves = 1;
	kt.board[1][1] = kt.nMoves++;

	if (solveKnightTour(1, 1) == false) {
		PRT("Solution does not exist.\n");
	}
	else {
		displaySolution();
	}

	system("pause");
	return 0;
}