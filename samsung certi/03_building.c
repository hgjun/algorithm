#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "_macrofunctions.h"

typedef struct building_t {
	int rows[15];
	int cols[15];
	int map[15][15];
	int size;
	int threshold;
	int totalH;
	int thresholdCnt;
} Building;

Building t;


bool isInside(i, j)
{
	if (j > 1 && t.map[i][j - 1] == 0) return false;
	if (j < t.size && t.map[i][j + 1] == 0) return false;
	if (i > 1 && t.map[i - 1][j] == 0) return false;
	if (i < t.size && t.map[i + 1][j] == 0) return false;
	return true;
}

int main()
{
	freopen("test.txt", "r", stdin);

	int loop, loopCnt;
	char x[2];

	scanf("%d", &loopCnt);
	PRT("Loop Cnt: %d\n", loopCnt);

	FOR(loop, loopCnt) {
		scanf("%d %d", &t.size, &t.threshold);
	
		PRT("Map size: %d\n", t.size);

		int i, j;

		FILL_ARRAY(t.rows, t.size, 0);
		FILL_ARRAY(t.cols, t.size, 0);
		FOR(i, t.size) {
			FOR(j, t.size) {				
				scanf("%s", x);
				if (x[0] == 'P') {
					t.map[i][j] = 0;
				}
				else if (x[0] == 'B') {
					t.map[i][j] = 1;
					t.rows[i]++;
					t.cols[j]++;
				}
			}
		}
		
		PRTLN; PRTLN; PRTLN;
		FOR(i, t.size) {
			FOR(j, t.size) {
				PRTD(t.map[i][j]);
			}
			PRTLN;
		} PRTLN;
		FOR(i, t.size) {
			PRTD(t.rows[i]);
		} PRTLN;
		FOR(i, t.size) {
			PRTD(t.cols[i]);
		}
		PRTLN; PRTLN;

		t.thresholdCnt = 0;
		t.totalH = 0;
		FOR(i, t.size) {
			FOR(j, t.size) {
				if (t.map[i][j] == 0) {
					continue;
				}

				if (isInside(i, j)) {
					t.map[i][j] = t.rows[i] + t.cols[j] - 1;
				}

				t.totalH += t.map[i][j];
				t.thresholdCnt += (t.map[i][j] >= t.threshold) ? 1 : 0;
			}
		}

		PRTLN; PRTLN; PRTLN;
		FOR(i, t.size) {
			FOR(j, t.size) {
				PRTD(t.map[i][j]);
			}
			PRTLN;
		} 
		PRTLN; PRTLN;
		PRT("Total: %d\n", t.totalH);
		PRT("Threshold Cnt: %d\n", t.thresholdCnt);
		PRTLN;
	}
	
	_getch();
	return 0;

}

