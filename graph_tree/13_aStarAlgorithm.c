#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "heapMap.h"
#include "shortestPath.h"

// A star algorithm (weighted dijkstra)


void aStarAlgorithm(int start, int target)
{
	FILL_ARRAY(sp.distance, g.vertexSize, INT_MAX);
	FILL_ARRAY(sp.parent, g.vertexSize, 0);
	sp.distance[start] = 0;

	HeapMap hmap;
	hmapInit(&hmap);

	int i;
	FOR(i, g.vertexSize) {
		hmapAddNode(&hmap, i, INT_MAX);
	}
	hmapSetValue(&hmap, start, sp.estimatedDistance[start]);

	int u, v;
	while (!hmapIsEmpty(&hmap)) {
		u = hmapExtractMinKey(&hmap);

		if (u == target) {
			printf("\nFind target node %d\n", target);
			break;
		}

		FOR(v, g.vertexSize) {
			if (!graphIsConnected(u, v) || !hmapIsExist(&hmap, v)) {
				continue;
			}
			if (sp.distance[u] + g.adjMat[u][v] < sp.distance[v]) {
				sp.distance[v] = sp.distance[u] + g.adjMat[u][v];
				sp.parent[v] = u;
				hmapSetValue(&hmap, v, sp.distance[v] + sp.estimatedDistance[v]);
			}
		}
	}

	for (v = target; v != start; v = sp.parent[v]) {
		u = sp.parent[v];
		sp.pathSize++;
		sp.path[sp.pathSize].u = u;
		sp.path[sp.pathSize].v = v;
		sp.path[sp.pathSize].w = g.adjMat[u][v];
	}
}

int main(void)
{
	int i;
	freopen("13_aStarAlgorithm_input.txt", "r", stdin);
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

	FOR(i, vertexSize) {
		scanf("%*s %*s %d", &sp.estimatedDistance[i]);
	}

	graphDisplay();

	printf("\nEstimated distance v(1-9) -> v4\n");
	FOR(i, vertexSize) {
		PRTD(sp.estimatedDistance[i]);
	}
	PRTLN;

	aStarAlgorithm(9, 4);
	shortPathDisplay();

	_getch();
	return 0;
}