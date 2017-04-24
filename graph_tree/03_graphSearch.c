#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

int main(void)
{
	int i;
	freopen("03_graphSearch_input.txt", "r", stdin);
	//setbuf(stdout, NULL);
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

	PRT("\n----------------------------------------------------\n");
	PRT("Breadth first search");
	PRT("\n----------------------------------------------------\n");
	BFS(1);
	gsDisplay();

	PRT("\n----------------------------------------------------\n");
	PRT("Depth first search");
	PRT("\n----------------------------------------------------\n");
	DFS(1);
	gsDisplay();

	PRT("\n----------------------------------------------------\n");
	PRT("DFS: Tree edge, forward edge, back edge, and cross edge");
	PRT("\n----------------------------------------------------\n");
	freopen("03_graphSearch_input2.txt", "r", stdin);
	scanf("%d %d", &vertexSize, &edgeSize);

	graphInit(vertexSize);
	g.isDirectedGraph = true;  ////  DIRECTED GRAPH!!

	FOR(i, edgeSize) {
		scanf("%d %d", &u, &v);
		w = 1;
		graphAddEdge(u, v, w);
	}

	graphDisplay();
	DFS2(1);

	_getch();

	return 0;
}
