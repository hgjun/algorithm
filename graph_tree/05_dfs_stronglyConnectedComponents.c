#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

typedef struct scc_t {
	int transposedAdjMat[GRAPH_SIZE][GRAPH_SIZE];
	int group[GRAPH_SIZE][GRAPH_SIZE];
	int groupSize;
	int elemSize;

	int visited[GRAPH_SIZE];
} SCC;

SCC scc;

void sccInit(void);
bool sccIsConnected(int u, int v);

void stronglyConnectedComponents(int start);
void sccDFS(void);
void sccVisitDFS(int u);

/*

void sccInit()
{
}
bool sccIsConnected(int u, int v)
{
}
void stronglyConnectedComponents(int start)
{
}
void sccDFS(void)
{
}
void sccVisitDFS(int u)
{
}

*/


void sccInit()
{
	int i, j;
	FOR(i, g.vertexSize) {
		scc.visited[i] = 0;

		FOR(j, g.vertexSize) {
			scc.transposedAdjMat[i][j] = g.adjMat[j][i];
			scc.group[i][j] = 0;
		}
	}

}

bool sccIsConnected(int u, int v)
{
	return (scc.transposedAdjMat[u][v] != 0);
}

void stronglyConnectedComponents(int start)
{
	int i, j;
	int vSize = g.vertexSize;

	sccInit();
	printf("\n\nTransposed adjacency matrix: \n");
	FOR(i, vSize) {
		FOR(j, vSize) {
			PRTD(scc.transposedAdjMat[i][j]);
		}
		PRTLN;
	}
	PRTLN;

	// compute topological sort
	DFS(start);

	PRT("Topological sort result:\n");
	FOR(i, g.vertexSize) {
		PRT("%-3d", gs.topoSort[i]);
	}
	PRTLN; PRTLN;

	PRT("Time stamp:\n");
	FOR(i, g.vertexSize) {
		PRT("%-3d", i);
	}
	PRTLN;
	FOR(i, g.vertexSize) {
		PRT("%-3d", gs.timeStamp[i]);
	}
	PRTLN; PRTLN;

	printf("Scc DFS start:\n");
	sccDFS();

	printf("\n\nStrongly connected components: \n");
	FOR(i, scc.groupSize) {
		FOR(j, vSize) {
			if (scc.group[i][j] == 0) {
				break;
			}
			PRTD(scc.group[i][j]);
		}
		PRTLN;
	}
	PRTLN; PRTLN;
}

void sccDFS(void)
{
	int i, v;
	scc.groupSize = 0;

	FOR(i, g.vertexSize) {
		v = gs.topoSort[i];
		if (scc.visited[v] == 0) {
			scc.groupSize++;
			scc.elemSize = 1;
			sccVisitDFS(v);
		}
	}
}

void sccVisitDFS(int u)
{
	PRTD(u);
	scc.visited[u] = 1;
	scc.group[scc.groupSize][scc.elemSize++] = u;

	int i, v;
	FOR(i, g.vertexSize) {
		v = gs.topoSort[i];
		if (sccIsConnected(u, v) && scc.visited[v] == 0) {
			sccVisitDFS(v);
		}
	}
}

int main(void)
{
	int i;
	freopen("05_dfs_stronglyConnectedComponents_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int vertexSize, edgeSize;
	scanf("%d %d", &vertexSize, &edgeSize);

	graphInit(vertexSize);
	g.isDirectedGraph = true;

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d", &u, &v);
		w = 1;
		graphAddEdge(u, v, w);
	}

	graphDisplay();
	stronglyConnectedComponents(1);

	_getch();
	return 0;
}
