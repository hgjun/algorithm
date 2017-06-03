#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

#define MAX_VERTEX 201
#define TRUE       1
#define FALSE      0

#define UNVISITED 0
#define SET_A 1
#define SET_B 2

// Bipartite match
int set[MAX_VERTEX];

int main(void)
{
	freopen("input_sample.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int T;
	int test_case;
	scanf("%d", &T);

	int i;
	int u, v;
	int result;
	int vertexSize, edgeSize;
	for (test_case = 1; test_case <= T; test_case++) {
		scanf("%d %d", &vertexSize, &edgeSize);

		FILL_ARRAY(set, vertexSize, UNVISITED);
		result = TRUE;
		for (i = 1; i <= edgeSize; i++) {
			scanf("%d %d", &u, &v);
			if (set[u] == UNVISITED && set[v] == UNVISITED) {
				set[u] = SET_A;
				set[v] = SET_B;
			}
			else if (set[u] == UNVISITED && set[v] != UNVISITED) {
				set[u] = (set[v] == SET_A) ? SET_B : SET_A;
			}
			else if (set[u] != UNVISITED && set[v] == UNVISITED) {
				set[v] = (set[u] == SET_A) ? SET_B : SET_A;
			}
			else if (set[u] == set[v]) {
				// edge e(u, v) and Set[u] == Set[v] => Not a bipartite graph
				result = FALSE;
			}
		}

		printf("Case #%d\n%d\n", test_case, result);
	}

	_getch();
	return 0;
}