#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

Graph eg;
int circuit[GRAPH_SIZE];
int circuitSize;

bool eulerIsConnected(int u, int v){
	return (eg.adjMat[u][v] != 0);
}

void eulerCircuit(int start);
void visitEulerCircuit(int u);

void eulerCircuit(int start){
	int i, j;
	FOR(i, g.vertexSize) {
		FOR(j, g.vertexSize) {
			eg.adjMat[i][j] = g.adjMat[i][j];
		}
	}
	circuitSize = 1;
	visitEulerCircuit(start);
	PRTLN; PRTLN;
	FORDEC(i, circuitSize, 1) {
		PRTD(circuit[i]);
	}
	PRTLN;
}

void visitEulerCircuit(int u)
{
	PRTD(u);
	int v;
	FOR(v, g.vertexSize) {
		if (eulerIsConnected(u, v)) {
			eg.adjMat[u][v] = eg.adjMat[v][u] = 0;
			visitEulerCircuit(v);
		}
	}

	circuit[circuitSize++] = u;
}

int main(void)
{
	int i;
	freopen("08_dfs_eulerianPath_input.txt", "r", stdin);
	//setbuf(stdout, NULL);
	int vertexSize, edgeSize;
	scanf("%d %d", &vertexSize, &edgeSize);

	Graph g;
	graphInit(vertexSize);
	g.isDirectedGraph = false;

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d", &u, &v);
		w = 1;

		graphAddEdge(u, v, w);
	}

	graphDisplay();


	BFS(1);
	gsDisplay();
	DFS(1);
	gsDisplay();
	eulerCircuit(1);

	_getch();
	return 0;
}
