#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <conio.h>

#include "_macrofunctions.h"


bool isSubstring(char *s1, char *s2, int s2begin, int s2len)
{
	/*
	PRT("%s %d \n%s %d\n", s1, strlen(s1), s2, strlen(s2));
	if (strcmp(s2, "COMPUTER") == 0) {
	PRT("\ncomputer %s\n", s1);
	}*/
	int i, j, size;
	int length1 = strlen(s1);
	int length2 = s2len;
	bool isSubstr;

	size = length1 - length2;
	for (i = 0; i <= size; i++) {
		isSubstr = true;
		for (j = 0; j < length2; j++) {
			if (s1[i + j] != s2[s2begin + j]) {
				//PRT("%c = %c?\n", s1[i + j], s2[j]);
				isSubstr = false;
				break;
			}
			else {
				//PRT("%c = %c!\n", s1[i + j], s2[j]);
			}
		}
		if (isSubstr) {
			return true;
		}
	}
	return false;
}

/*
old version

bool isSubstring(char *s1, char *s2)
{
	int i, j, size;
	int length1 = strlen(s1);
	int length2 = strlen(s2);
	bool isSubstr;
	if (length2 == 1) {
		return false;
	}

	size = length1 - length2;
	for (i = 0; i <= size; i++) {
		isSubstr = true;
		for (j = 0; j < length2; j++) {
			if (s1[i + j] != s2[j]) {
				//PRT("%c = %c?\n", s1[i + j], s2[j]);
				isSubstr = false;
				break;
			}
			else {
				//PRT("%c = %c!\n", s1[i + j], s2[j]);
			}
		}
		if (isSubstr) {
			return true;
		}
	}
	return false;
}


void substring(char *s1, char *s2, int begin, int size)
{
	char *p = &s1[begin];
	int i = 1;
	while (i <= size){
		*s2++ = *p++;
		i++;
	}
	*s2 = '\0';
}
*/

int main(void)
{
	/*if (isSubstring("ILOVECOMPUTER", "COMPUTER"))
	{
		PRT("SUBSTRING\n");
	}
	else {
		PRT("NOT\n");
	}*/
	
	freopen("test.txt", "r", stdin);
	int i, j, k, count;
	int loop, loopCnt;
	int check[101][101];
	/*
	chkstr = SAQTEST
	chk[6][6]
	[1][1] SAQTEST
	[2][1] SAQTES  [2][2] AQTEST
	[3][1] SAQTE   [3][2] AQTES  [3][3] QTEST
	[4][1] SAQT    [4][2] AQTE   [4][3] QTES  [4][4] TEST
	[5][1] SAQ     [5][2] AQT    [5][3] QTE   [5][4] TES  [5][5] EST
	[6][1] SA      [6][2] AQ     [6][3] QT    [6][4] TE   [6][5] ES  [6][6] ST
	*/

	char basestr[100], baselen;
	char chkstr[100], chklen;
	char tmp[100];

	scanf("%d", &loopCnt);
	scanf("%s", basestr);
	baselen = strlen(basestr);
	PRT("Base string: %s\n", basestr);

	FOR(loop, loopCnt) {
		PRT("#%d\n", loop);
		
		scanf("%s", chkstr);
		chklen = strlen(chkstr);
		PRT("Check string: %s\n", chkstr);
		FILL_MATRIX(check, chklen-1, chklen-1, 0);

		FOR(i, (chklen - 1)) {
			FOR(j, i) {
				//substring(chkstr, tmp, j - 1, chklen - i + 1); old version
				if (check[i][j] == 0) {
					//check[i][j] = isSubstring(basestr, tmp); old version
					check[i][j] = isSubstring(basestr, chkstr, j - 1, chklen - i + 1);
				}

				if (check[i][j] == 1 || check[i][j] == 2) {
					check[i + 1][j] = check[i + 1][j + 1] = 2;
				}
			}
		}

		count = 0;
		FOR(i, (chklen - 1)) {
			FOR(j, i) {
				if (check[i][j] == 1) {
					count++;
					substring(chkstr, tmp, j - 1, chklen - i + 1);
					PRT("substr: %s\n", tmp);
				}
			}
		}
		PRT("Substring count: %d\n", count);
	}
	_getch();
	return 0;
}
