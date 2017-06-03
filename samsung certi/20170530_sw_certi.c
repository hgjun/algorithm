#include <stdio.h>

#define PRT  printf
#define MAX(x, y)         ((x) >= (y) ? (x) : (y))
#define FILL_ARRAY(arr, size, v) 		do { int i_; for (i_ = size; i_ >= 0; i_--) arr[i_] = (v); } while (0)

typedef struct box_t {
	int x, y, z;
} Box;
Box b[21];

int N;
int visited[21];

int compute(int prevL1, int prevL2)
{
	int maxVal = 0;
	int L1, L2, v;

	for (int i = 1; i <= N; i++) {
		int tmp;
		int maxTmp = 0;

		if (visited[i] == 1) {
			continue;
		}
		visited[i] = 1;

		if (b[i].x >= b[i].y) {
			L1 = b[i].x; L2 = b[i].y;
		}
		else {
			L1 = b[i].y; L2 = b[i].x;
		}
		v = b[i].z;
		tmp = 0;
		if (L1 <= prevL1 && L2 <= prevL2) {
			tmp = v + compute(L1, L2);
		}
		maxTmp = MAX(maxTmp, tmp);

		if (b[i].x >= b[i].z) {
			L1 = b[i].x; L2 = b[i].z;
		}
		else {
			L1 = b[i].z; L2 = b[i].x;
		}
		v = b[i].y;
		tmp = 0;
		if (L1 <= prevL1 && L2 <= prevL2) {
			tmp = v + compute(L1, L2);
		}
		maxTmp = MAX(maxTmp, tmp);

		if (b[i].y >= b[i].z) {
			L1 = b[i].y; L2 = b[i].z;
		}
		else {
			L1 = b[i].z; L2 = b[i].y;
		}
		v = b[i].x;
		tmp = 0;
		if (L1 <= prevL1 && L2 <= prevL2) {
			tmp = v + compute(L1, L2);
		}
		maxTmp = MAX(maxTmp, tmp);

		maxVal = MAX(maxVal, maxTmp);
		visited[i] = 0;
	}

	return maxVal;
}

int main(void)
{
	int answer;

	freopen("06_boxTower.txt", "r", stdin);
	int test, testCount;
	scanf("%d", &testCount);
	
	for (test = 1; test <= testCount; test++) {
		scanf("%d", &N);
		FILL_ARRAY(visited, 20, 0);

		for (int i = 1; i <= N; i++) {
			scanf("%d %d %d", &b[i].x, &b[i].y, &b[i].z);
		}

		answer = compute(10000, 10000);
		printf("#%d %d\n", test, answer);
	}

	_getch();
	return 0;
}