#pragma once

#include "stdio.h"
#include "stdbool.h"
#include "macrofunctions.h"
#include "queue.h"

#define GRAPH_SIZE 100

typedef struct edge_t {
	int u, v; // vertex u and v
	int w; // link weight between u and v
} Edge;

typedef struct graph_t {
	bool isDirectedGraph;
	int vertexSize;
	int edgeSize;

	int adjMat[GRAPH_SIZE][GRAPH_SIZE];
	Edge edge[GRAPH_SIZE + GRAPH_SIZE + 1];
} Graph;

Graph g;

void graphInit(int vSize);
void graphAddEdge(int u, int v, int w);
bool graphIsConnected(int u, int v);
void graphDisplay();

void graphInit(int vSize)
{
	g.vertexSize = vSize;
	g.edgeSize = 0;
	FILL_MATRIX(g.adjMat, vSize, vSize, 0);
}

void graphAddEdge(int u, int v, int w)
{
	g.edgeSize++;
	Edge *e = &g.edge[g.edgeSize];
	e->u = u;
	e->v = v;
	e->w = w;

	g.adjMat[u][v] = w;
	if (g.isDirectedGraph == false) {
		g.adjMat[v][u] = w;
	}
}

bool graphIsConnected(int u, int v)
{
	return (g.adjMat[u][v] != 0);
}

void graphDisplay(void)
{
	int i, j;
	PRT("\n----------------------------------------------------\n");
	PRT("Input graph data");
	PRT("\n----------------------------------------------------\n");
	if (g.isDirectedGraph) {
		printf("Directed graph\n");
	}
	else {
		printf("Undirected graph\n");
	}
	printf("Vertex: %d\nEdge  : %d\n\n", g.vertexSize, g.edgeSize);
	for (i = 1; i <= g.edgeSize; i++) {
		printf("[%d] u%d v%d weight: %d\n", i, g.edge[i].u, g.edge[i].v, g.edge[i].w);
	}

	printf("\nAdjacency matrix\n    ");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d", i);
	}
	printf("\n");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-4d", i);
		for (j = 1; j <= g.vertexSize; j++) {
			printf("%-3d", g.adjMat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
