#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

typedef struct ntFlow_t {
	// BFS
	int visited[GRAPH_SIZE];
	int parent[GRAPH_SIZE];

	// Network flow
	int flowMat[GRAPH_SIZE][GRAPH_SIZE];
	int maxFlow;
} NtFlow;

NtFlow nt;

void ntFlowInit(void);
void ntFlowInfo(void);
void fordFulkerson(int source, int sink);
void findMinCut(int source, int sink);

/*

void ntFlowInit(void)
{
}
void ntFlowInfo(void)
{
}
void fordFulkerson(int source, int sink)
{
}
void findMinCut(int source, int sink)
{
}

*/

void ntFlowInit(void)
{
	FILL_ARRAY(nt.visited, g.vertexSize, 0);
	FILL_ARRAY(nt.parent, g.vertexSize, 0);
	FILL_MATRIX(nt.flowMat, g.vertexSize, g.vertexSize, 0);
	nt.maxFlow = 0;
}

void ntFlowInfo(void)
{
	int i, j;
	printf("\n\n");
	printf("Max flow = %d\n", nt.maxFlow);

	for (i = 1; i <= g.vertexSize; i++) {
		for (j = 1; j <= g.vertexSize; j++) {
			printf("%-3d", nt.flowMat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void fordFulkerson(int source, int sink)
{
	ntFlowInit();


	Queue q;
	int   u, v;
	bool  isPathExists;
	int   residualCapacity;
	int   pathFlow;

	int loopCnt = 1;
	printf("Network flow\n");
	printf("Find augmenting path: source %d to sink %d\n\n", source, sink);

	while (true) {
		printf("[%d] ", loopCnt++);

		// init
		isPathExists = false;
		FILL_ARRAY(nt.visited, g.vertexSize, 0);
		FILL_ARRAY(nt.parent, g.vertexSize, 0);
		initQueue(&q);

		nt.visited[source] = 1;
		enqueue(&q, source);

		while (isEmptyQueue(&q) == false) {
			u = dequeue(&q);

			if (u == sink) {
				isPathExists = true;
				break;
			}

			FOR(v, g.vertexSize) {
				residualCapacity = g.adjMat[u][v] - nt.flowMat[u][v];
				if (graphIsConnected(u, v) == false || residualCapacity <= 0) {
					continue;
				}

				if (nt.visited[v] == 0) {
					nt.visited[v] = 1;
					nt.parent[v] = u;
					enqueue(&q, v);
				}
			}
		}
		PRTLN;
		if (isPathExists == false) {
			printf("do not exist remaining path\n");
			break;
		}

		// find pathFlow
		pathFlow = INT_MAX;
		for (v = sink; v != source; v = nt.parent[v]) {
			u = nt.parent[v];
			residualCapacity = g.adjMat[u][v] - nt.flowMat[u][v];
			pathFlow = MIN(pathFlow, residualCapacity);
		}

		// send pathFlow
		for (v = sink; v != source; v = nt.parent[v]) {
			printf("%-3d-> ", v);
			u = nt.parent[v];
			nt.flowMat[u][v] += pathFlow;
			nt.flowMat[v][u] -= pathFlow;
		}
		printf("%-3d ", source);

		nt.maxFlow += pathFlow;
		printf(" min. residual capacity of the path: %d \n\n", pathFlow);
	}

}

Graph rg;
void rgVisitDFS(int u)
{
	PRTD(u);
	gs.visited[u] = 1;
	int v;
	FOR(v, g.vertexSize) {
		if (rg.adjMat[u][v] == 0 || gs.visited[v] != 0) {
			continue;
		}
		gs.parent[v] = u;
		rgVisitDFS(v);
	}
}

void findMinCut(int source, int sink)
{
	int i, j;

	FILL_MATRIX(rg.adjMat, g.vertexSize, g.vertexSize, 0);

	FOR(i, g.vertexSize) {
		FOR(j, g.vertexSize) {
			if (nt.flowMat[i][j] > 0) {
				rg.adjMat[i][j] = g.adjMat[i][j] - nt.flowMat[i][j];
			}
		}
	}

	PRT("Redidual capacity graph:\n    ");
	FOR(i, g.vertexSize) {
		printf("%-3d", i);
	}
	PRTLN;
	FOR(i, g.vertexSize) {
		printf("%-4d", i);
		FOR(j, g.vertexSize) {
			printf("%-3d", rg.adjMat[i][j]);
		}
		PRTLN;
	}
	PRTLN;


	PRT("Redidual graph - DFS start:\n");
	FILL_ARRAY(gs.visited, g.vertexSize, 0);
	FILL_ARRAY(gs.parent, g.vertexSize, 0);
	rgVisitDFS(source);
	PRTLN; PRTLN;


	// Show min cut
	PRT("S: ");
	FOR(i, g.vertexSize) {
		if (gs.visited[i] == 1) {
			PRTD(i);
		}
	}

	PRTLN;
	PRT("T: ");
	FOR(i, g.vertexSize) {
		if (gs.visited[i] == 0) {
			PRTD(i);
		}
	}
	PRTLN; PRTLN;

	PRT("Min cut:\n");
	FOR(i, g.vertexSize) {
		FOR(j, g.vertexSize) {
			if (graphIsConnected(i, j) && gs.visited[i] && !gs.visited[j]) {
				PRT("u%d - v%d\n", i, j);
			}
		}
	}
	PRTLN;
}

int main(void)
{
	int i;
	freopen("14_networkFlows_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	// G(V, E): undirected graph
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

	fordFulkerson(6, 3);
	ntFlowInfo();
	findMinCut(6, 3);


	_getch();
	return 0;
}