#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

int main(void)
{
	int i, j, k;
	freopen("08_joinedLis_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int loop, loopCnt;
	scanf("%d", &loopCnt);

	int a[101], b[101], c[201];
	int aSize, bSize, cSize;

	FOR(loop, loopCnt) {
		scanf("%d %d", &aSize, &bSize);

		FOR(i, aSize) {
			scanf("%d", &a[i]);
		}
		FOR(i, bSize) {
			scanf("%d", &b[i]);
		}

		i = j = k = 1;
		while (i <= aSize && j <= bSize) {
			if (a[i] == b[j]) {
				i++;
				continue;
			}
			c[k++] = (a[i] < b[j]) ? a[i++] : b[j++];
		}
		while (i <= aSize) {
			c[k++] = a[i++];
		}
		while (j <= bSize) {
			c[k++] = b[j++];
		}
		cSize = k - 1;

		PRT("Set A size %d: ", aSize);
		FOR(i, aSize) {
			PRT("%-3d", a[i]);
		}
		PRT("\nSet B size %d: ", bSize);
		FOR(i, bSize) {
			PRT("%-3d", b[i]);
		}
		PRTLN;
		PRT("Joined longest increasing subsequence: size %d\n", cSize);
		FOR(i, cSize) {
			PRT("%-3d", c[i]);
		}
		PRTLN; PRTLN; PRTLN;
	}

	_getch();
	return 0;
}

