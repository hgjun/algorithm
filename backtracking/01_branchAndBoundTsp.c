#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "heapMap.h"

typedef struct tsp_t {
	int start;
	int visited[GRAPH_SIZE];

	int cost[GRAPH_SIZE];
	int path[GRAPH_SIZE];
	int pathSize;

	int minTotalCost;
	int minPath[GRAPH_SIZE];
} Tsp;

Tsp tsp;

void tspDisplay(void);

void tspDisplay()
{
	int i;
	printf("\n\nMin cost: %d\n", tsp.minTotalCost);
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%d -> ", tsp.minPath[i]);
	}
	printf("%d\n", tsp.start);
}

void normalTsp(void);
void normalTspVisit(int u);

void branchAndBound(void);
void branchAndBoundVisit(int u);
int  getLowerBound(int candidateNode);


/*

void normalTsp(void)
{
}
void normalTspVisit(int u)
{
}
void branchAndBound()
{
}
void branchAndBoundVisit(int u)
{
}
int  getLowerBound(int candidateNode)
{
}

*/


void normalTsp(void)
{
	int i;
	FILL_ARRAY(tsp.visited, g.vertexSize, 0);
	tsp.pathSize = 1;
	tsp.path[1] = 1;
	tsp.start = 1;
	tsp.cost[1] = 0;
	tsp.visited[1] = 1;
	tsp.minTotalCost = INT_MAX;

	printf("TSP start:\n%d\n", tsp.start);
	FORFROM(i, 2, g.vertexSize) {
		if (tsp.visited[i] == 0) {
			normalTspVisit(i);
		}
	}

	tspDisplay();
}

void normalTspVisit(int u)
{
	int prev_u = tsp.path[tsp.pathSize];
	tsp.pathSize++;

	tsp.visited[u] = 1;
	tsp.path[tsp.pathSize] = u;
	tsp.cost[tsp.pathSize] = g.adjMat[prev_u][u];

	int v;
	FOR(v, tsp.pathSize) {
		PRTD(tsp.path[v]);
	}
	PRTLN;

	bool isLeafNode = (tsp.pathSize == g.vertexSize - 1);

	if (isLeafNode == false) {

		FORFROM(v, 2, g.vertexSize) {
			if (tsp.visited[v] == 0) {
				normalTspVisit(v);
			}
		}
	}
	else {
		int sum = 0;
		int unVisited;
		FOR(v, g.vertexSize) {
			if (tsp.visited[v] == 0) {
				unVisited = v;
			}
		}

		FOR(v, tsp.pathSize) {
			sum += tsp.cost[v];
		}
		sum += g.adjMat[u][unVisited] + g.adjMat[unVisited][tsp.start];

		if (sum < tsp.minTotalCost) {
			tsp.minTotalCost = sum;
			COPY_ARRAY(tsp.minPath, 1, tsp.path, 1, tsp.pathSize);
			tsp.minPath[tsp.pathSize + 1] = unVisited;
		}

		printf("cost: ");
		for (v = 1; v <= tsp.pathSize; v++) {
			printf("%2d + ", tsp.cost[v]);
		}
		printf("(%d->%d)%2d + (%d->%d)%2d", u, unVisited, g.adjMat[u][unVisited], unVisited, tsp.start, g.adjMat[unVisited][tsp.start]);
		printf(" = %d\n", sum);
	}

	tsp.visited[u] = 0;
	tsp.pathSize--;
}

void branchAndBound()
{
	int v;
	FILL_ARRAY(tsp.visited, g.vertexSize, 0);
	tsp.start = 1;
	tsp.pathSize = 1;
	tsp.path[1] = 1;
	tsp.cost[1] = 0;
	tsp.visited[1] = 1;
	tsp.minTotalCost = INT_MAX;

	printf("Branch and Bound TSP start:\n%d\n", tsp.start);
	HeapMap hmap;
	hmapInit(&hmap);
	int lBound;
	FORFROM(v, 2, g.vertexSize) {
		lBound = getLowerBound(v);
		printf("lowerbound with %d: %d\n", v, lBound);
		hmapAddNode(&hmap, v, lBound);
	}

	MapData minNode;
	while (!hmapIsEmpty(&hmap)) {
		minNode = hmapExtractMinData(&hmap);
		if (minNode.value < tsp.minTotalCost) {
			branchAndBoundVisit(minNode.key);
		}
		else {
			// greator than lower bound, skip traversing subtree
			printf("%d %d\n", tsp.start, minNode.key);
			printf("Prunning node %d: cost%d > sumMinCost%d\n", minNode.key, minNode.value, tsp.minTotalCost);
		}
	}

	tspDisplay();
}


void branchAndBoundVisit(int u)
{
	int prev_u = tsp.path[tsp.pathSize];
	tsp.pathSize++;

	tsp.visited[u] = 1;
	tsp.path[tsp.pathSize] = u;
	tsp.cost[tsp.pathSize] = g.adjMat[prev_u][u];

	int v;
	FOR(v, tsp.pathSize) {
		PRTD(tsp.path[v]);
	}
	PRTLN;

	bool isLeafNode = (tsp.pathSize == g.vertexSize - 1);

	if (isLeafNode == false) {
		HeapMap hmap;
		hmapInit(&hmap);
		int lBound;
		FORFROM(v, 2, g.vertexSize) {
			if (tsp.visited[v] == 0) {
				lBound = getLowerBound(v);
				printf("lowerbound with %d: %d\n", v, lBound);
				hmapAddNode(&hmap, v, lBound);
			}
		}

		MapData minNode;
		while (hmapIsEmpty(&hmap) == false) {
			minNode = hmapExtractMinData(&hmap);
			if (minNode.value < tsp.minTotalCost) {
				branchAndBoundVisit(minNode.key);
			}
			else {
				// greator than lower bound, skip traversing subtree
				printf("%d %d\n", tsp.start, minNode.key);
				printf("Prunning node %d: cost%d > sumMinCost%d\n", minNode.key, minNode.value, tsp.minTotalCost);
			}
		}
	}
	else {
		int sum = 0;
		int unVisited;
		FOR(v, g.vertexSize) {
			if (tsp.visited[v] == 0) {
				unVisited = v;
			}
		}

		FOR(v, tsp.pathSize) {
			sum += tsp.cost[v];
		}
		sum += g.adjMat[u][unVisited] + g.adjMat[unVisited][tsp.start];

		if (sum < tsp.minTotalCost) {
			tsp.minTotalCost = sum;
			FOR(v, tsp.pathSize) {
				tsp.minPath[v] = tsp.path[v];
			}
			tsp.minPath[v] = unVisited;
		}

		printf("cost: ");
		for (v = 1; v <= tsp.pathSize; v++) {
			printf("%2d + ", tsp.cost[v]);
		}
		printf("(%d->%d)%2d + (%d->%d)%2d", u, unVisited, g.adjMat[u][unVisited], unVisited, tsp.start, g.adjMat[unVisited][tsp.start]);
		printf(" = %d\n", sum);
	}

	tsp.visited[u] = 0;
	tsp.pathSize--;
}


int  getLowerBound(int candidateNode)
{
	int i, j;
	int lBound = 0;

	FOR(i, tsp.pathSize) {
		lBound += tsp.cost[i];
	}

	int lastPath = tsp.path[tsp.pathSize];
	lBound += g.adjMat[lastPath][candidateNode];

	int minTmp;
	FOR(i, g.vertexSize) {
		if (tsp.visited[i] == 1) {
			continue;
		}

		minTmp = INT_MAX;
		if (i != candidateNode) {
			minTmp = g.adjMat[i][tsp.start];
		}

		FOR(j, g.vertexSize) {
			if (tsp.visited[j] == 1 || i == j || j == candidateNode) {
				continue;
			}

			minTmp = MIN(minTmp, g.adjMat[i][j]);
		}
		lBound += minTmp;
	}
	return lBound;
}

int main(void)
{
	int i, j;
	freopen("01_branchAndBoundTsp_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	// G(V, E): directed, weighted graph
	int vertexSize;
	scanf("%d", &vertexSize);
	graphInit(vertexSize);
	g.isDirectedGraph = true;

	//nEdges_ = nVertices_ * nVertices_ - nVertices_;
	int w;
	FOR(i, vertexSize) {
		FOR(j, vertexSize) {
			scanf("%d", &w);
			graphAddEdge(i, j, w);
		}
	}
	graphDisplay();

	normalTsp();
	PRT("\n\n\n-------------------------------------\n");
	branchAndBound();

	_getch();
	return 0;
}