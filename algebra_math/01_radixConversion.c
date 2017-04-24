#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "macrofunctions.h"

void radixConversion(unsigned int n, unsigned int radix)
{
	unsigned int i = 1;
	unsigned int res = 0;
	while (n) {
		res += i * (n % radix);
		i *= 10;
		printf("n = %d, radix %d = %d\n", n, radix, res);
		n /= radix;
	}
	printf("n = %d, radix %d = %d\n", n, radix, res);
}

int main(void)
{
	radixConversion(100, 2);
	system("pause");
	return 0;
}

