#include <stdio.h>
#include <conio.h>

long long int getGcd(long long int a, long long int b)
{
	long long int c = a % b;
	while (c) {
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}

char mean[16];
long long int num[6 + 1];
long long int sum, n;
long long int gcd, a, b;
int n1, n2, n3;

int main()
{
	freopen("sample.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int t, tv = 0;
	int i, j;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", mean);
		a = 0;
		for (i = 0; mean[i]; i++)
		{
			if (mean[i] == '.')break;
			a = (a * 10) + (mean[i] - '0');
		}
		b = 1;
		for (j = i + 1; mean[j]; j++)
		{
			a = (a * 10) + (mean[j] - '0');
			b *= 10;
		}
		gcd = getGcd(a, b);
		sum = a / gcd;
		n = b / gcd;

		for (i = 1; i <= 6; i++) {
			num[i] = 0;
		}

		// n = n1 + n2 + n3
		n1 = (sum - n) / 5;
		i = (sum - n) % 5;
		n2 = (i != 0) ? 1 : 0;
		n3 = n - n1 - n2;

		num[6] = n1;
		num[i + 1] = n2;
		num[1] = n3;

		printf("#testcase%d: %s\n%lld %lld %lld %lld %lld %lld\n", ++tv, mean, num[1], num[2], num[3], num[4], num[5], num[6]);
	}
	_getch();
	return 0;
}