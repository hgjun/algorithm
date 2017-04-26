#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "macrofunctions.h"

int main()
{
	int i, j;
	freopen("05_longestCommonSubsequence_input.txt", "r", stdin);

	char tmp[1024];

	char x[1024];
	int xLength, yLength;
	char y[1024];

	scanf("%s", tmp);
	xLength = strlen(tmp);
	strcpy(x, " ");
	strcat(x, tmp);
	PRT("%s %d\n", x, xLength);

	scanf("%s", tmp);
	yLength = strlen(tmp);
	strcpy(y, " ");
	strcat(y, tmp);
	PRT("%s %d\n", y, yLength);

	int cnt[100][100];
	FORFROM(i, 0, xLength) {
		cnt[i][0] = 0;
	}
	FORFROM(j, 0, yLength) {
		cnt[0][j] = 0;
	}
	// x == y
	// cnt[x][y] = cnt[x - 1][y - 1] + 1

	// x != y
	// cnt[x][y] = MAX( cnt[x - 1][y], cnt[x][y - 1] )
	FOR(i, xLength) {
		FOR(j, yLength) {
			if (x[i] == y[j]) {
				cnt[i][j] = cnt[i - 1][j - 1] + 1;
			}
			else {
				cnt[i][j] = MAX(cnt[i - 1][j], cnt[i][j - 1]);
			}
		}
	}

	FORFROM(i, 0, xLength) {
		FORFROM(j, 0, yLength) {
			PRT("%-3d", cnt[i][j]);
		}
		PRTLN;
	}
	_getch();
	return 0;
}
