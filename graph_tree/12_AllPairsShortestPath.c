#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"

typedef struct floydWarshall_t {
	int distance[GRAPH_SIZE][GRAPH_SIZE];
	int parent[GRAPH_SIZE][GRAPH_SIZE];
	int child[GRAPH_SIZE][GRAPH_SIZE];
} FloydWarshall;

FloydWarshall sp;

void floydWarshall();
void showPathInfo();
void showPathTraverse(int start, int end);

void floydWarshall()
{
	int i, j, k;
	FOR(i, g.vertexSize) {
		FOR(j, g.vertexSize) {
			sp.distance[i][j] = INT_MAX;
			sp.parent[i][j] = 0;
			sp.child[i][j] = 0;

			if (i == j) {
				sp.distance[i][j] = 0;
			}
			else if (g.adjMat[i][j] != 0) {
				sp.distance[i][j] = g.adjMat[i][j];
				sp.parent[i][j] = i;
				sp.child[i][j] = j;
			}
		}
	}

	FOR(k, g.vertexSize) {
		FOR(i, g.vertexSize) {
			if (sp.distance[i][k] == INT_MAX) {
				continue;
			}
			FOR(j, g.vertexSize) {
				if (sp.distance[k][j] == INT_MAX || i == j) {
					continue;
				}

				if (sp.distance[i][k] + sp.distance[k][j] < sp.distance[i][j]) {
					sp.distance[i][j] = sp.distance[i][k] + sp.distance[k][j];
					sp.parent[i][j] = sp.parent[k][j];
					sp.child[i][j] = sp.child[i][k];
				}
			}
		}
	}
}

void showPathInfo()
{
	int i, j;
	printf("\nDistance matrix:\n");
	for (i = 1; i <= g.vertexSize; i++) {
		for (j = 1; j <= g.vertexSize; j++) {
			printf("%-3d", sp.distance[i][j]);
		}
		printf("\n");
	}
	printf("\nparent\n");
	for (i = 1; i <= g.vertexSize; i++) {
		for (j = 1; j <= g.vertexSize; j++) {
			printf("%-3d ", sp.parent[i][j]);
		}
		printf("\n");
	}
	printf("\nchild\n");
	for (i = 1; i <= g.vertexSize; i++) {
		for (j = 1; j <= g.vertexSize; j++) {
			printf("%-3d", sp.child[i][j]);
		}
		printf("\n");
	}
}

void showPathTraverse(int start, int end)
{
	if (sp.distance[start][end] == INT_MAX) {
		return;
	}

	int k;
	printf("\nPath traverse %d -> %d\n", start, end);
	for (k = end; k != start; k = sp.parent[start][k]) {
		printf("%-3d", k);
	}
	printf("%-3d\n", start);

	printf("\nPath traverse %d -> %d\n", start, end);
	for (k = start; k != end; k = sp.child[k][end]) {
		printf("%-3d", k);
	}
	printf("%-3d\n", end);
}

int main(void)
{
	int i;
	freopen("12_shortestPath_FloydWarshall_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	// G(V, E): directed, weighted graph
	int vertexSize, edgeSize;

	scanf("%d %d", &vertexSize, &edgeSize);
	graphInit(vertexSize);
	g.isDirectedGraph = true;

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d %d", &u, &v, &w);
		graphAddEdge(u, v, w);
	}
	graphDisplay();

	floydWarshall();
	showPathInfo();
	showPathTraverse(1, 2);

	_getch();
	return 0;
}
