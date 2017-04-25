#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "heapMap.h"

// Kruskal's
typedef struct rankNode_t {
	int name;
	int rank;
	struct rankNode_t *parent;
} RankNode;

// MST result data: Kruskal, Prim
typedef struct mst_t {
	Edge path[GRAPH_SIZE];
	int pathSize;

	// Kruskal's
	RankNode node[GRAPH_SIZE];
	Edge sortedEdge[GRAPH_SIZE * GRAPH_SIZE + 1];

	// Prim's
	int parent[GRAPH_SIZE];
} Mst;

Mst mst;

void      mstKruskals(void);
void      qSortEdge(Edge *edge, int head, int tail);
int       qSortEdgePartition(Edge *edge, int head, int tail);
bool      unionSet(RankNode *u, RankNode *v);
RankNode* findSet(RankNode *u);

void mstPrims(int start);

/*


void mstKruskals(void)
{
}
void qSortEdge(Edge *arr, int head, int tail)
{
}
int qSortEdgePartition(Edge *arr, int head, int tail)
{
}
bool unionSet(RankNode *u, RankNode *v)
{
}
RankNode* findSet(RankNode *u)
{
}
void mstPrims(int start)
{
}


*/


void mstKruskals(void)
{
	int i;

	// Sort edges
	COPY_ARRAY(mst.sortedEdge, 1, g.edge, 1, g.edgeSize);
	qSortEdge(mst.sortedEdge, 1, g.edgeSize);
	PRT("Sorted edge:\n");
	FOR(i, g.edgeSize) {
		PRT("%d %d %d\n", mst.sortedEdge[i].u, mst.sortedEdge[i].v, mst.sortedEdge[i].w);
	}

	// Make set
	FOR(i, g.vertexSize) {
		mst.node[i].name = i;
		mst.node[i].rank = 0;
		mst.node[i].parent = &mst.node[i];
	}

	// Union set
	mst.pathSize = 0;
	RankNode *u, *v;
	FOR(i, g.edgeSize) {
		u = &mst.node[mst.sortedEdge[i].u];
		v = &mst.node[mst.sortedEdge[i].v];
		if (unionSet(u, v)) {
			mst.pathSize++;
			mst.path[mst.pathSize].u = mst.sortedEdge[i].u;
			mst.path[mst.pathSize].v = mst.sortedEdge[i].v;
			mst.path[mst.pathSize].w = mst.sortedEdge[i].w;
		}
	}

	PRT("\nNode Parent Rank\n");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%d %d %d\n", mst.node[i].name, mst.node[i].parent->name, mst.node[i].rank);
	}

	printf("\n");
	printf("\nKruskal's MST result\n");
	for (i = 1; i <= mst.pathSize; i++) {
		printf("[%d] u%d v%d weight %d\n", i, mst.path[i].u, mst.path[i].v, mst.path[i].w);
	}
}

void qSortEdge(Edge *arr, int head, int tail)
{
	if (head >= tail) {
		return;
	}
	int mid = qSortEdgePartition(arr, head, tail);
	qSortEdge(arr, head, mid - 1);
	qSortEdge(arr, mid + 1, tail);
}

int qSortEdgePartition(Edge *arr, int head, int tail)
{
	Edge pivot = arr[tail];
	int mid = head;
	int gt;
	FORFROM(gt, head, (tail - 1)) {
		if (arr[gt].w < pivot.w) {
			SWAP(arr[gt].u, arr[mid].u);
			SWAP(arr[gt].v, arr[mid].v);
			SWAP(arr[gt].w, arr[mid].w);
			mid++;
		}
	}
	arr[tail] = arr[mid];
	arr[mid] = pivot;
	return mid;
}

bool unionSet(RankNode *u, RankNode *v)
{
	RankNode *root_u = findSet(u);
	RankNode *root_v = findSet(v);

	if (root_u == root_v) {
		return false;
	}

	if (root_u->rank > root_v->rank) {
		root_v->parent = root_u;
	}
	else {
		root_u->parent = root_v;
		if (root_u->rank == root_v->rank) {
			root_v->rank++;
		}
	}
	return true;
}

RankNode* findSet(RankNode *u)
{
	RankNode *t;
	for (t = u; t != t->parent; t = t->parent);
	return t;
}

void mstPrims(int start)
{
	FILL_ARRAY(mst.parent, g.vertexSize, 0);
	HeapMap hmap;
	hmapInit(&hmap);

	int i;
	FOR(i, g.vertexSize) {
		hmapAddNode(&hmap, i, INT_MAX);
	}
	hmapSetValue(&hmap, start, 0);

	int u, v;
	while (!hmapIsEmpty(&hmap)) {
		printf("\n\nloop %d\n", g.vertexSize - hmap.size + 1);

		u = hmapExtractMinKey(&hmap);
		printf("\nExtract min key %d", u);
		hmapDisplay(&hmap, g.vertexSize);

		FOR(v, g.vertexSize) {
			if (!graphIsConnected(u, v) || !hmapIsExist(&hmap, v)) {
				continue;
			}
			if (g.adjMat[u][v] < hmapGetValue(&hmap, v)) {
				mst.parent[v] = u;
				hmapSetValue(&hmap, v, g.adjMat[u][v]);
			}
		}

		printf("\nafter update min cost path");
		hmapDisplay(&hmap, g.vertexSize);
	}

	i = 1;
	FOR(v, g.vertexSize) {
		u = mst.parent[v];
		if (u == 0) {
			continue;
		}
		mst.path[i].u = u;
		mst.path[i].v = v;
		mst.path[i].w = g.adjMat[u][v];
		i++;
	}
	mst.pathSize = i - 1;

	printf("\n\nParents: ");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d", mst.parent[i]);
	}
	printf("\nNodes  : ");
	for (i = 1; i <= g.vertexSize; i++) {
		printf("%-3d", i);
	}
	printf("\n\nPrim's MST result\n");
	for (i = 1; i <= mst.pathSize; i++) {
		printf("[%d] %d %d %d\n", i, mst.path[i].u, mst.path[i].v, mst.path[i].w);
	}
}

int main()
{
	int i;
	freopen("10_minimumSpanningTree_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	// G(V, E): connected, undirected, weighted graph
	int vertexSize, edgeSize;

	scanf("%d %d", &vertexSize, &edgeSize);
	graphInit(vertexSize);
	g.isDirectedGraph = false;

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d %d", &u, &v, &w);
		graphAddEdge(u, v, w);
	}

	graphDisplay();
	mstKruskals();
	mstPrims(1);
	_getch();
	return 0;
}