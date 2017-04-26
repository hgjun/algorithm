#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "macrofunctions.h"
#include "graph.h"

int  color_[GRAPH_SIZE];

void mColoring(int maxM);
int  getValidColor(int node, int maxM);

/*
void mColoring      (int maxM)
{
}
int  getValidColor  (int node, int maxM)
{
}
*/

void mColoring(int maxM)
{
	if (g.vertexSize < maxM) {
		printf("\n\n%d coloring success\n", maxM);
		return;
	}
	else if (maxM < 1) {
		printf("\n\nFailed: %d colors are not enough.\n", maxM);
		return;
	}

	FILL_ARRAY(color_, g.vertexSize, 0);
	color_[1] = 1;

	int i;
	FORFROM(i, 2, g.vertexSize) {
		color_[i] = getValidColor(i, maxM);
	}

	bool isSuccess = true;
	for (i = 1; i <= g.vertexSize; i++) {
		printf("Sector%2d - color %d\n", i, color_[i]);
		if (color_[i] == 0) {
			isSuccess = false;
		}
	}

	if (isSuccess) {
		printf("\n\n%d coloring success\n", maxM);
	}
	else {
		printf("\n\nFailed: %d colors are not enough.\n", maxM);
	}
}
/*
int getValidColor(int node, int maxK)
{
int v     = 1;
int color = 1;

while (v < node) {
// edge(u, v) == 0 then pass
if (graphIsConnected(v, node) == false) {
v++;
}
// edge(u, v) == 1 and different color then pass
else if (color_[v] != color) {
v++;
}
// edge(u, v) == 1 and same color then increase color, and refresh check
else {
v = 1;
color++;
}
}

if (color <= maxK) {
return color;
}
else {
return 0;
}
}
*/

int getValidColor(int node, int maxM)
{
	int v;
	int color = 1;
	while (color <= maxM) {
		FOR(v, (node - 1)) {
			if (graphIsConnected(v, node) && color_[v] == color) {
				color++;
				break;
			}
		}
		if (v == node && color <= maxM) {
			return color;
		}
	}
	return 0;
}

int main(void)
{
	int i;
	freopen("04_stateSpaceTree_mColoring_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	// G(V, E): undirected graph
	int vertexSize, edgeSize;
	scanf("%d %d", &vertexSize, &edgeSize);

	graphInit(vertexSize);
	g.isDirectedGraph = false;

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d", &u, &v);
		w = 1;
		graphAddEdge(u, v, w);
	}
	graphDisplay();

	mColoring(3);

	getch();
	return 0;
}
