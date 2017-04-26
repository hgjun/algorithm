#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

void findPath(int start, int target);  // DFS
bool backTracking(int u, int target);  // visitDFS
void showInfo(int start, int target);

/*

void findPath(int start, int target)
{
}
bool backTracking(int u, int target)
{
}
void showInfo(int start, int target)
{
}

*/

void findPath(int start, int target)
{
	FILL_ARRAY(gs.parent, g.vertexSize, 0);
	FILL_ARRAY(gs.visited, g.vertexSize, 0);

	if (backTracking(start, target)) {
		PRT("\nFind path\n");
		showInfo(start, target);
	}
	else {
		PRT("\nNo path\n");
	}
}

bool backTracking(int u, int target)
{
	PRTD(u);
	gs.visited[u] = 1;
	if (u == target) {
		return true;
	}
	int v;
	FORDEC(v, g.vertexSize, 1) {
		if (graphIsConnected(u, v) && gs.visited[v] == 0) {
			gs.parent[v] = u;
			if (backTracking(v, target)) {
				return true;
			}
		}
	}
	return false;
}

void showInfo(int start, int target)
{
	int i;
	printf("\nVisited:\n");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d", gs.visited[i]);
	}
	printf("\nParents:\n");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d", gs.parent[i]);
	}
	PRTLN; PRTLN;

	int u, v;
	for (v = target; v != start; v = gs.parent[v]) {
		u = gs.parent[v];
		PRT("u%d v%d\n", u, v);
	}
	PRTLN;
}

int main(void)
{
	int i;
	freopen("03_stateSpaceTree_Maze_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	// G(V, E): undirected graph
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

	findPath(12, 13);


	_getch();
	return 0;
}

