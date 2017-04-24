#pragma once

#include <stdio.h>
#include "graph.h"

typedef struct graphSearch_t {
	// BFS, DFS
	int visited[GRAPH_SIZE];
	int parent[GRAPH_SIZE];

	// DFS
	int timeStamp[GRAPH_SIZE];
	int time;

	// DFS2
	Edge treeEdge[GRAPH_SIZE + GRAPH_SIZE + 1];
	int treeEdgeSize;
	Edge forwardEdge[GRAPH_SIZE + GRAPH_SIZE + 1];
	int forwardEdgeSize;
	Edge backEdge[GRAPH_SIZE + GRAPH_SIZE + 1];
	int backEdgeSize;
	Edge crossEdge[GRAPH_SIZE + GRAPH_SIZE + 1];
	int crossEdgeSize;

	// Topological sort
	int topoSort[GRAPH_SIZE];
	int topoIdx;
} GraphSearch;

GraphSearch gs;

void gsDisplay(void);

void BFS(int start);

void DFS(int start);
void visitDFS(int u);

void DFS2(int start);
void visitDFS2(int u);
void addTreeEdge(int u, int v);
void addForwardEdge(int u, int v);
void addBackEdge(int u, int v);
void addCrossEdge(int u, int v);

void gsDisplay()
{
	int u, v;
	int bound = g.vertexSize;

	PRT("Traversed edges: \n");
	FOR(v, bound) {
		u = gs.parent[v];
		if (u == 0) {
			continue;
		}

		PRT("u%d v%d\n", u, v);
	}
	PRTLN;
}

void BFS(int start)
{
	FILL_ARRAY(gs.visited, g.vertexSize, 0);
	FILL_ARRAY(gs.parent, g.vertexSize, 0);
	gs.visited[start] = 1;

	Queue q;
	initQueue(&q);
	enqueue(&q, start);

	PRT("BFS start:\n");
	int u, v;
	while (!isEmptyQueue(&q)) {
		u = dequeue(&q);
		PRTD(u);

		FOR(v, g.vertexSize) {
			if (graphIsConnected(u, v) && gs.visited[v] == 0) {
				gs.visited[v] = 1;
				gs.parent[v] = u;
				enqueue(&q, v);
			}
		}
	}
	PRTLN; PRTLN;
}

void DFS(int start)
{
	PRT("DFS start:\n");
	FILL_ARRAY(gs.visited, g.vertexSize, 0);
	FILL_ARRAY(gs.parent, g.vertexSize, 0);
	
	gs.topoIdx = g.vertexSize;
	gs.time = 1;
	visitDFS(start);

	int v;
	FOR(v, g.vertexSize) {
		if (gs.visited[v] == 0) {
			visitDFS(v);
		}
	}
	PRTLN; PRTLN;
}

void visitDFS(int u)
{
	PRTD(u);
	gs.visited[u] = 1;
	gs.timeStamp[u] = gs.time++;

	int v;
	FOR(v, g.vertexSize) {
		if (graphIsConnected(u, v) && gs.visited[v] == 0) {
			gs.parent[v] = u;
			visitDFS(v);
		}

	}
	gs.visited[u] = 2;
	gs.timeStamp[u] = gs.time++;
	gs.topoSort[gs.topoIdx--] = u;
}

void DFS2(int start)
{
	PRT("DFS (detailed version) start:\n");
	FILL_ARRAY(gs.visited, g.vertexSize, 0);
	FILL_ARRAY(gs.parent, g.vertexSize, 0);

	gs.treeEdgeSize = 0;
	gs.forwardEdgeSize = 0;
	gs.backEdgeSize = 0;
	gs.crossEdgeSize = 0;

	gs.time = 1;
	visitDFS2(start);

	int v;
	FOR(v, g.vertexSize) {
		if (gs.visited[v] == 0) {
			visitDFS2(v);
		}
	}
	PRTLN; PRTLN;

	gsDisplay();

	int i;
	PRT("Tree edges: %d\n", gs.treeEdgeSize);
	FOR(i, gs.treeEdgeSize) {
		PRT("u%d v%d weight%d\n", gs.treeEdge[i].u, gs.treeEdge[i].v, gs.treeEdge[i].w);
	}
	PRTLN; PRTLN;

	PRT("Forward edges: %d\n", gs.forwardEdgeSize);
	FOR(i, gs.forwardEdgeSize) {
		PRT("u%d v%d weight%d\n", gs.forwardEdge[i].u, gs.forwardEdge[i].v, gs.forwardEdge[i].w);
	}
	PRTLN;

	PRT("Back edges: %d\n", gs.backEdgeSize);
	FOR(i, gs.backEdgeSize) {
		PRT("u%d v%d weight%d\n", gs.backEdge[i].u, gs.backEdge[i].v, gs.backEdge[i].w);
	}
	PRTLN;

	PRT("Cross edges: %d\n", gs.crossEdgeSize);
	FOR(i, gs.crossEdgeSize) {
		PRT("u%d v%d weight%d\n", gs.crossEdge[i].u, gs.crossEdge[i].v, gs.crossEdge[i].w);
	}
	PRTLN;
}

void visitDFS2(int u)
{
	PRTD(u);
	gs.visited[u] = 1;
	gs.timeStamp[u] = gs.time++;

	int v;
	FOR(v, g.vertexSize) {
		if (!graphIsConnected(u, v)) {
			continue;
		}

		if (gs.visited[v] == 0) {
			addTreeEdge(u, v);
			gs.parent[v] = u;
			visitDFS2(v);
		}
		else if (gs.timeStamp[u] < gs.timeStamp[v]) {
			addForwardEdge(u, v);
		}
		else if (gs.visited[v] == 1 && gs.timeStamp[u] > gs.timeStamp[v]) {
			addBackEdge(u, v);
		}
		else if (gs.visited[v] == 2) {
			addCrossEdge(u, v);
		}
	}
	gs.visited[u] = 2;
}

void addTreeEdge(int u, int v)
{

	gs.treeEdgeSize++;
	Edge *e = &gs.treeEdge[gs.treeEdgeSize];
	e->u = u; e->v = v; e->w = g.adjMat[u][v];
}

void addForwardEdge(int u, int v)
{
	gs.forwardEdgeSize++;
	Edge *e = &gs.forwardEdge[gs.forwardEdgeSize];
	e->u = u; e->v = v; e->w = g.adjMat[u][v];
}

void addBackEdge(int u, int v)
{
	gs.backEdgeSize++;
	Edge *e = &gs.backEdge[gs.backEdgeSize];
	e->u = u; e->v = v; e->w = g.adjMat[u][v];
}

void addCrossEdge(int u, int v)
{
	gs.crossEdgeSize++;
	Edge *e = &gs.crossEdge[gs.crossEdgeSize];
	e->u = u; e->v = v; e->w = g.adjMat[u][v];
}
