#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <conio.h>

#include "macrofunctions.h"

// http://whocouldthat.be/visualizing-string-matching/
// http://m.blog.naver.com/choyi0521/80206821567

void buildPartialMatch(char *pattern, int len, int *pi)
{
	int prefixIdx, suffixIdx;
	FILL_ARRAY(pi, len, 0);
	prefixIdx = -1;
	suffixIdx = 0;
	pi[0] = -1;
	while (suffixIdx < len) {
		if (prefixIdx == -1 || pattern[prefixIdx] == pattern[suffixIdx]) {
			prefixIdx++;
			suffixIdx++;
			pi[suffixIdx] = prefixIdx;
		}
		else {
			prefixIdx = pi[prefixIdx];
		}
	}
}

void kmp(char *str, char *pattern, int *pi)
{
	int sIdx, pIdx;
	sIdx = pIdx = 0;
	int sLen = strlen(str);
	int pLen = strlen(pattern);
	int cnt = 0;
	//PRT("%s sLen %d\npLen %d\n", str, sLen, pLen);
	while (sIdx < sLen) {
		//PRT("%c %c %d\n", str[sIdx], pattern[pIdx], str[sIdx] == pattern[pIdx]);
		if (pIdx == -1 || str[sIdx] == pattern[pIdx]) {
			/*if (pIdx == -1) {
			PRT("init: sid%d pid%d\n", sIdx, pIdx);
			}
			else
			{
			PRT("same, sid%d (%c) pid%d (%c)\n", sIdx, str[sIdx], pIdx, pattern[pIdx]);
			}*/

			sIdx++;
			pIdx++;
			/*if (pIdx == -1) {
			PRT("initialize: sid%d pid%d\n", sIdx, pIdx);
			}
			else
			{
			PRT("same, next: sid%d (%c) pid%d (%c)\n", sIdx, str[sIdx], pIdx, pattern[pIdx]);
			}*/
		}
		else {
			//PRT("different: pid%d -> pi[%d]: %d\n", pIdx, pIdx, pi[pIdx]);
			pIdx = pi[pIdx];
		}
		//PRT("cnt: %d\n", cnt++);
		if (pIdx == pLen) {
			printf("%d ~ %d\n", sIdx - pLen, sIdx - 1);
			int i;
			FORFROM(i, sIdx - pLen, sIdx - 1)
			{
				PRT("%c ", str[i]);
			}PRTLN;
			PRT("pidx %d -> pi[%d]", pIdx, pIdx);
			pIdx = pi[pIdx];
			PRT(" = %d\n", pIdx);
		}
	}
}

int main()
{
	freopen("20_kmp.txt", "r", stdin);
	char pattern[1024];
	char str[1024];
	int pi[1024];

	scanf("%s", pattern);
	scanf("%s", str);

	int i;
	int len = strlen(pattern);

	FORFROM(i, 0, strlen(str) - 1) {
		PRT("%-3d", i);
	}PRTLN;
	FORFROM(i, 0, strlen(str) - 1) {
		PRT("%-3c", str[i]);
	}
	PRTLN; PRTLN;
	FORFROM(i, 0, len - 1) {
		PRT("%-3d", i);
	}PRTLN;
	FORFROM(i, 0, len - 1) {
		PRT("%-3c", pattern[i]);
	}
	PRTLN; PRTLN;


	buildPartialMatch(pattern, len, pi);
	FORFROM(i, 0, len) {
		PRTD(pi[i]);
	}
	PRTLN; PRTLN;

	kmp(str, pattern, pi);

	_getch();
	return 0;
}