#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"

typedef struct findCutBridge_t {
	// DFS
	int visited[GRAPH_SIZE];
	int parent[GRAPH_SIZE];
	int timeStamp[GRAPH_SIZE];
	int time;

	// Find cut vertices, and bridges
	int minReachTime[GRAPH_SIZE];

	// Find cut vertices
	bool isCutVertex[GRAPH_SIZE];

	// Find bridges
	Edge bridge[GRAPH_SIZE];
	int nBridges;
} FindCutBridge;

FindCutBridge f;

void findCutVertex(int start);
void visitFindCutVertex(int u, bool isRoot);

void findCutVertex(int start)
{
	PRT("Find cut vertices start:\n");
	FILL_ARRAY(f.visited, g.vertexSize, 0);
	FILL_ARRAY(f.parent, g.vertexSize, 0);
	FILL_ARRAY(f.isCutVertex, g.vertexSize, 0);

	f.time = 1;
	visitFindCutVertex(start, true);

	int i;
	FOR(i, g.vertexSize) {
		if (f.visited[i] == 0) {
			visitFindCutVertex(i, false);
		}
	}
	PRTLN; PRTLN;
	PRT("Node:                ");
	FOR(i, g.vertexSize) {
		PRTD(i);
	}
	PRTLN;
	PRT("TimeStamp:           ");
	FOR(i, g.vertexSize) {
		PRTD(f.timeStamp[i]);
	}
	PRTLN;
	PRT("Parents:             ");
	FOR(i, g.vertexSize) {
		PRTD(f.parent[i]);
	}
	PRTLN;
	PRT("Reachable min time:  ");
	FOR(i, g.vertexSize) {
		PRTD(f.minReachTime[i]);
	}
	PRTLN; PRTLN;

	printf("Cut vertices:\n", i);
	FOR(i, g.vertexSize) {
		printf("%-3d", i);
	}
	printf("\n");
	FOR(i, g.vertexSize) {
		printf("%-3d", f.isCutVertex[i]);

	}
	printf("\n\n");
}

void visitFindCutVertex(int u, bool isRoot)
{
	PRTD(u);
	f.visited[u] = 1;
	f.timeStamp[u] = f.time++;
	f.minReachTime[u] = f.timeStamp[u];

	int v;
	int rootChildren = 0;
	FOR(v, g.vertexSize) {
		if (!graphIsConnected(u, v)) {
			continue;
		}
		if (f.visited[v] == 0) {
			rootChildren++;
			f.parent[v] = u;
			visitFindCutVertex(v, false); // calculate minReachTime[v]
			f.minReachTime[u] = MIN(f.minReachTime[u], f.minReachTime[v]);

			if (!isRoot &&  f.minReachTime[v] >= f.timeStamp[u]) {
				f.isCutVertex[u] = true;
			}
		}
		else {
			// compare to timeStamp[v] : already visited node  f.visited[v] == 1 
			f.minReachTime[u] = MIN(f.minReachTime[u], f.timeStamp[v]);
		}
	}

	if (isRoot) {
		f.isCutVertex[u] = (rootChildren >= 2);
	}
}

/* Recursive version
int  visitFindCutVertexReturnVal(int u, bool isRoot)
{
	PRTD(u);
	f.visited[u] = 1;
	f.timeStamp[u] = f.time++;
	f.reachableMinTime[u] = f.timeStamp[u];

	int v;
	int rootChildren = 0;
	int subTree;
	FOR(v, g.vertexSize) {
		if (!graphIsConnected(u, v)) {
			continue;
		}
		if (f.visited[v] == 0) {
			rootChildren++;
			f.parent[v] = u;
			subTree = visitFindCutVertexReturnVal(v, false);

			if (!isRoot && subTree >= f.timeStamp[u]) {
				f.isCutVertex[u] = true;
			}
			f.reachableMinTime[u] = MIN(f.reachableMinTime[u], subTree);

		}
		else {
			f.reachableMinTime[u] = MIN(f.reachableMinTime[u], f.timeStamp[v]);
		}
	}

	if (isRoot) {
		f.isCutVertex[u] = (rootChildren >= 2);
	}
	return f.reachableMinTime[u];
}
*/


void findBridge(int start);
void visitFindBridge(int u, int v);

void findBridge(int start)
{
	PRT("Find bridge start:\n");
	FILL_ARRAY(f.visited, g.vertexSize, 0);
	FILL_ARRAY(f.parent, g.vertexSize, 0);
	f.nBridges = 0;

	f.time = 1;
	visitFindBridge(start, start);

	int i;
	FOR(i, g.vertexSize) {
		if (f.visited[i] == 0) {
			visitFindBridge(i, i);
		}
	}
	PRTLN; PRTLN;

	PRT("Node:                ");
	FOR(i, g.vertexSize) {
		PRTD(i);
	}
	PRTLN;
	PRT("TimeStamp:           ");
	FOR(i, g.vertexSize) {
		PRTD(f.timeStamp[i]);
	}
	PRTLN;
	PRT("Parents:             ");
	FOR(i, g.vertexSize) {
		PRTD(f.parent[i]);
	}
	PRTLN;
	PRT("Reachable min time:  ");
	FOR(i, g.vertexSize) {
		PRTD(f.minReachTime[i]);
	}
	PRTLN; PRTLN;
	PRT("Number of bridges: %d\n", f.nBridges);
	FOR(i, f.nBridges) {
		PRT("u%d v%d\n", f.bridge[i].u, f.bridge[i].v);
	}
	PRTLN; PRTLN;
}

void  visitFindBridge(int u, int v)
{
	PRTD(v);
	f.visited[v] = 1;
	f.timeStamp[v] = f.time++;
	f.minReachTime[v] = f.timeStamp[v];

	int w;
	FOR(w, g.vertexSize) {
		if (!graphIsConnected(v, w)) {
			continue;
		}
		if (f.visited[w] == 0) {
			f.parent[w] = v;
			visitFindBridge(v, w);
			f.minReachTime[v] = MIN(f.minReachTime[v], f.minReachTime[w]);

			if (f.minReachTime[w] == f.timeStamp[w]) {
				//PRT("BRIDGE v%d t%d time%d  w%d\n", v, f.reachableMinTime[w], f.timeStamp[w], w);
				f.nBridges++;
				f.bridge[f.nBridges].u = v;
				f.bridge[f.nBridges].v = w;
			}
		}
		else {
			// Do not consider edge u-v
			// Check if any v-w  can reach u  without edge u-v
			// different point from find cut vertices
			if (w != u) {
				f.minReachTime[v] = MIN(f.minReachTime[v], f.timeStamp[w]);
			}
		}
	}
}

int main(void)
{
	int i;
	int vertexSize, edgeSize;

	freopen("06_dfs_findCut_findBridge_input.txt", "r", stdin);
	scanf("%d %d", &vertexSize, &edgeSize);
	graphInit(vertexSize);
	g.isDirectedGraph = false;////  UNDIRECTED GRAPH!!

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d", &u, &v);
		w = 1;
		graphAddEdge(u, v, w);
	}
	graphDisplay();


	PRT("\n----------------------------------------------------\n");
	PRT("Find cut vertices");
	PRT("\n----------------------------------------------------\n");
	findCutVertex(1);

	PRT("\n----------------------------------------------------\n");
	PRT("Find Bridges");
	PRT("\n----------------------------------------------------\n");
	findBridge(1);

	_getch();
	return 0;
}