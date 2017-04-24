#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

void topologicalSort(int start)
{
	DFS(start);

	PRT("Topological sort result:\n");
	int i;
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
	PRT("Inverse order of timestamp = topo sort\n");
	PRTLN; PRTLN;
}

int main(void)
{
	int i;
	freopen("04_dfs_topologicalSort_input.txt", "r", stdin);
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
	topologicalSort(5);

	_getch();

	return 0;
}
