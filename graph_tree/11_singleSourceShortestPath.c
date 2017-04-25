#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "heapMap.h"
#include "shortestPath.h"

void bellmanFord(int start);
void dijkstra(int start);

/*

void bellmanFord(int start)
{
}

void dijkstra(int start)
{
}

*/

void bellmanFord(int start)
{
	int i, loop;
	shortPathInit();
	sp.distance[start] = 0;
	
	int u, v, w;
	FOR(loop, g.vertexSize - 1) {
		FOR(i, g.edgeSize) {
			u = g.edge[i].u;
			v = g.edge[i].v;
			w = g.edge[i].w;
			if (sp.distance[u] == INT_MAX) {
				continue;
			}
			if (sp.distance[u] + g.adjMat[u][v] < sp.distance[v]) {
				sp.distance[v] = sp.distance[u] + g.adjMat[u][v];
				sp.parent[v] = u;
			}
		}
	}

	FOR(i, g.edgeSize) {
		u = g.edge[i].u;
		v = g.edge[i].v;
		w = g.edge[i].w;
		if (sp.distance[u] == INT_MAX) {
			continue;
		}
		if (sp.distance[u] + g.adjMat[u][v] < sp.distance[v]) {
			printf("\nGraph contains negative weight cycle.\n");
			break;
		}
	}

	i = 1;
	FOR(v, g.vertexSize) {
		u = sp.parent[v];
		if (u == 0) {
			continue;
		}
		sp.path[i].u = u;
		sp.path[i].v = v;
		sp.path[i].w = g.adjMat[u][v];
		i++;
	}
	sp.pathSize = i - 1;
}

void dijkstra(int start)
{
	shortPathInit();
	sp.distance[start] = 0;

	int i;
	HeapMap hmap;
	hmapInit(&hmap);
	FOR(i, g.vertexSize) {
		hmapAddNode(&hmap, i, sp.distance[i]);
	}

	int u, v;
	while (!hmapIsEmpty(&hmap)) {
		u = hmapExtractMinKey(&hmap);
		FOR(v, g.vertexSize) {
			if (!graphIsConnected(u, v) || !hmapIsExist(&hmap, v)) {
				continue;
			}
			if (sp.distance[u] + g.adjMat[u][v] < sp.distance[v]) {
				sp.distance[v] = sp.distance[u] + g.adjMat[u][v];
				sp.parent[v] = u;
				hmapSetValue(&hmap, v, sp.distance[v]);
			}
		}
	}

	i = 1;
	FOR(v, g.vertexSize) {
		u = sp.parent[v];
		if (u == 0) {
			continue;
		}
		sp.path[i].u = u;
		sp.path[i].v = v;
		sp.path[i].w = g.adjMat[u][v];
		i++;
	}
	sp.pathSize = i - 1;
}

int main()
{
	int i;
	int u, v, w;
	int vertexSize, edgeSize;
	
	PRT("\n----------------------------------------------------\n");
	PRT("ShortestPath: BellmanFord");
	PRT("\n----------------------------------------------------\n");

	freopen("11_shortestPath_BellmanFord_input1.txt", "r", stdin);
	scanf("%d %d", &vertexSize, &edgeSize);
	// G(V, E): directed, weighted graph
	// minus edge value can be exist
	graphInit(vertexSize);
	g.isDirectedGraph = true;

	FOR(i, edgeSize) {
		scanf("%d %d %d", &u, &v, &w);
		graphAddEdge(u, v, w);
	}
	graphDisplay();
	bellmanFord(1);
	shortPathDisplay();

	PRT("\n----------------------------------------------------\n");
	PRT("ShortestPath: Dijkstra");
	PRT("\n----------------------------------------------------\n");
	freopen("11_shortestPath_Dijkstra_input1.txt", "r", stdin);
	scanf("%d %d", &vertexSize, &edgeSize);
	// G(V, E): directed, weighted graph
	graphInit(vertexSize);
	g.isDirectedGraph = true;

	FOR(i, edgeSize) {
		scanf("%d %d %d", &u, &v, &w);
		graphAddEdge(u, v, w);
	}
	graphDisplay();
	dijkstra(1);
	shortPathDisplay();

	_getch();
	return 0;
}