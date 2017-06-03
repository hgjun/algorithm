#include <stdio.h>

#define FOR(i, n)                        for (i = 1; i <= (n); i++)
#define FORFROM(i, m, n)                 for (i = (m); i <= (n); i++)
#define FORDEC(i, m, n)                  for (i = (m); i >= (n); i--)
#define FILL_ARRAY(arr, size, v)         do {int _i; for(_i = (size); _i >= 0; _i--) arr[_i] = (v);} while(0)

typedef struct item_t {
	int weight;
	int value;
	int isChosen;
} Item;

typedef struct knapsack_t {
	int itemSize;
	Item item[5001];

	int knapsackSize;
	int arr[10001];        // with repetition
	int parent[10001];     // with repetition
	int chosenItem[10001]; // with repetition
} Knapsack;
Knapsack k;


int knapsackWith()
{
	FILL_ARRAY(k.arr, k.knapsackSize, 0);
	FILL_ARRAY(k.parent, k.knapsackSize, 0);
	//k.arr[0] = 0;

	int i, c;
	FOR(c, k.knapsackSize) {
		FOR(i, k.itemSize) {
			if (k.item[i].weight > c) {
				continue;
			}
			int chosen = k.arr[c - k.item[i].weight] + k.item[i].value;
			if (chosen > k.arr[c]) {
				k.arr[c] = chosen;
				k.chosenItem[c] = i;
				k.parent[c] = c - k.item[i].weight;
			}

		}
	}
}

int main()
{
	freopen("classSchedule.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T;
	int test_case;
	int i, j, num;
	int res = 0;

	scanf("%d", &T);
	for (test_case = 1; test_case <= T; test_case++) {
		scanf("%d %d", &k.itemSize, &k.knapsackSize);

		FOR(i, k.itemSize) {
			scanf("%d", &k.item[i].weight);
			k.item[i].value = k.item[i].weight;
		}

		knapsackWith();

		printf("Case #%d\n%d\n", test_case, k.arr[k.knapsackSize]);
	}
	
	_getch();
	return 0;
}

