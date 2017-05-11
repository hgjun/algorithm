#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "macrofunctions.h"

void palindrome(char *str, int begin, int end)
{
	//int mid = begin + (end - begin + 1) / 2;
	int mid = (begin + end + 1) / 2;
	int i = begin, j = end;

	while (i < mid) {
		if (str[i] == str[j]) {
			i++;
			j--;
		}
		else {
			break;
		}
	}
	int k;
	FORFROM(k, begin, end) {
		PRT("%c", str[k]);
	}
	if (i == mid) {
		PRT("\nPalindrome\n");
	}
	else {
		PRT("\nNot alindrome\n");
	}
}
int main(void)
{
	palindrome("abba", 0, 3);
	palindrome("abcba", 0, 4);
	palindrome("abaccaba", 0, 7);
	palindrome("abaccaba", 2, 5);
	palindrome("abacecaba", 2, 6);
	palindrome("abacecaba", 2, 5);
	system("pause");
	return 0;
}

