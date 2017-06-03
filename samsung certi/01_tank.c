#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "_macrofunctions.h"

#define ROAD      0
#define TOMB      1
#define ENEMY     2
#define TANK      3

typedef struct tank_t{
	int map[10][10];
	int size;
	int nAttacks;
} Tank;
Tank t;

void shoot(int y, int x)
{
	int i, j;
	// Left
	j = x - 1;
	while (j >= 0){
		if (t.map[y][j] == TOMB || t.map[y][j] == TANK) {
			break;
		}
		else if (t.map[y][j] == ENEMY) {
			t.nAttacks++;
			t.map[y][j] = TOMB;
		}
		else {
			j--;
		}
	}
	//Right
	j = x + 1;
	while (j < t.size){
		if (t.map[y][j] == TOMB || t.map[y][j] == TANK) {
			break;
		}
		else if (t.map[y][j] == ENEMY) {
			t.nAttacks++;
			t.map[y][j] = TOMB;
		}
		else {
			j++;
		}
	}
	// Up
	i = y - 1;
	while (i >= 0){
		if (t.map[i][x] == TOMB || t.map[i][x] == TANK) {
			break;
		}
		else if (t.map[i][x] == ENEMY) {
			t.nAttacks++;
			t.map[i][x] = TOMB;
		}
		else {
			i--;
		}
	}
	// Down
	i = y + 1;
	while (i < t.size){
		if (t.map[i][x] == TOMB || t.map[i][x] == TANK) {
			break;
		}
		else if (t.map[i][x] == ENEMY) {
			t.nAttacks++;
			t.map[i][x] = TOMB;
		}
		else {
			i++;
		}
	}
}

int main()
{
	freopen("test.txt", "r", stdin);

	int loop, loopCnt;

	scanf("%d", &loopCnt);
	PRT("Loop Cnt: %d\n", loopCnt);
	FOR(loop, loopCnt) {
		scanf("%d", &t.size);
		PRT("Map size: %d\n", t.size);
		int i, j;
		char typeTbl[5] = "0BET";
		char type[10];

		for (i = 0; i < t.size; i++) {
			for (j = 0; j < t.size; j++) {
				scanf("%s", type);
				//PRT("%c", *strchr(typeTbl, type[0]));
				t.map[i][j] = strchr(typeTbl, type[0]) - &typeTbl[0];
			}
		}
		PRTLN; PRTLN; PRTLN;

		for (i = 0; i < t.size; i++) {
			for (j = 0; j < t.size; j++) {
				PRTD(t.map[i][j]);
			}
			PRTLN;
		}

		t.nAttacks = 0;
		for (i = 0; i < t.size; i++) {
			for (j = 0; j < t.size; j++) {
				if (t.map[i][j] == TANK) {
					shoot(i, j);
				}
			}
		}

		PRT("\nAttacks: %d\n", t.nAttacks);
		for (i = 0; i < t.size; i++) {
			for (j = 0; j < t.size; j++) {
				PRTD(t.map[i][j]);
			}
			PRTLN;
		}

	}
	
	_getch();
	return 0;

}

