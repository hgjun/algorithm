#pragma once

#include <stdio.h>
#include <limits.h>
#include "macrofunctions.h"
#include "graph.h"

typedef struct shortestPath_t {
	// Shortest path result
	Edge path[GRAPH_SIZE * GRAPH_SIZE + 1];
	int pathSize;

	// Shortest path computation
	int distance[GRAPH_SIZE];
	int parent[GRAPH_SIZE];

	// A start algo
	int estimatedDistance[GRAPH_SIZE];

} ShortestPath;

ShortestPath sp;

/*

void shortPathInit (void)
{
}
void shortPathDisplay (void)
{
}

*/


void shortPathInit(void)
{
	sp.pathSize = 0;
	FILL_ARRAY(sp.distance, g.vertexSize, INT_MAX);
	FILL_ARRAY(sp.parent, g.vertexSize, 0);
}

void shortPathDisplay(void)
{
	int i;
	// Print result
	printf("\nDistance:\n");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d ", sp.distance[i]);
	}
	printf("\n\nParent nodes:\n");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d ", sp.parent[i]);
	}
	printf("\n\nShortest path:\n");
	for (i = 1; i <= sp.pathSize; i++) {
		printf("[%d] %d %d %d\n", i, sp.path[i].u, sp.path[i].v, sp.path[i].w);
	}
}

