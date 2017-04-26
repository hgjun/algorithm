#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"

#define GRAPH_SIZE 100

typedef struct bipartiteU_t {
	// graph
	int vertexSize;
	int adjMat[GRAPH_SIZE][GRAPH_SIZE];

	// DFS
	int visited[GRAPH_SIZE];
	int match[GRAPH_SIZE];
} BipartiteU;

typedef struct bipartiteV_t {
	int vertexSize;
	int match[GRAPH_SIZE];
} BipartiteV;

BipartiteU bu;
BipartiteV bv;

bool isConnected(int u, int v);
void bipartiteInit(void);
void bipartiteDisplay(void);
int  bipartiteMatch(void);
bool bipartiteVisitDFS(int u);

/*

bool isConnected(int u, int v)
{
}
void bipartiteInit(void)
{
}
void bipartiteDisplay(void)
{
}
int bipartiteMatch (void)
{
}
bool bipartiteVisitDFS (int u)
{
}

*/

bool isConnected(int u, int v) {
	return (bu.adjMat[u][v] != 0);
}

void bipartiteInit(void)
{
	FILL_MATRIX(bu.adjMat, bu.vertexSize, bv.vertexSize, 0);
	FILL_ARRAY(bu.visited, bu.vertexSize, 0);
	FILL_ARRAY(bu.match, bu.vertexSize, 0);
	FILL_ARRAY(bv.match, bv.vertexSize, 0);
}

void bipartiteDisplay(void)
{
	int i, j;
	printf("Graph info.\n");

	printf("Vertex (Set A): %d\nVertex (Set B): %d\n\n", bu.vertexSize, bv.vertexSize);

	printf("\nAdjacency matrix\n    ");

	FOR(i, bv.vertexSize) {
		printf("%-3d", i);
	}
	printf("\n");
	FOR(i, bu.vertexSize) {
		printf("%-4d", i);
		FOR(j, bv.vertexSize) {
			printf("%-3d", bu.adjMat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int bipartiteMatch(void)
{
	int nMatches = 0;

	int u;
	FOR(u, bu.vertexSize) {
		FILL_ARRAY(bu.visited, bu.vertexSize, 0);

		if (bipartiteVisitDFS(u)) {
			nMatches++;
		}
	}
	return nMatches;
}

bool bipartiteVisitDFS(int u)
{
	if (bu.visited[u] != 0) {
		return false;
	}
	bu.visited[u] = 1;

	int v;
	FOR(v, bv.vertexSize) {
		if (isConnected(u, v) == false) {
			continue;
		}

		if (bv.match[v] == 0 || bipartiteVisitDFS(bv.match[v])) {
			bu.match[u] = v;
			bv.match[v] = u;
			return true;
		}
	}
	return false;
}

int main(void)
{
	int i, j;
	freopen("16_bipartiteBishop_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int size;
	scanf("%d", &size);

	int a[10][10];
	int b[10][10];

	FOR(i, size) {
		FOR(j, size) {
			scanf("%d", &a[i][j]);
			b[i][j] = a[i][j];
		}
	}

	int aSize = 0;
	int x, y;
	FOR(i, size) {
		FOR(j, size) {
			if (a[i][j] == -1) {
				aSize++;
				x = j; y = i;
				while (x >= 1 && y <= size && a[y][x] != 0) {
					a[y++][x--] = aSize;
				}
			}
		}
	}

	FOR(i, size) {
		FOR(j, size) {
			PRTD(a[i][j]);
		}
		PRTLN;
	}
	PRTLN;

	int bSize = 0;
	FOR(i, size) {
		FOR(j, size) {
			if (b[i][j] == -1) {
				bSize++;
				x = j; y = i;
				while (x <= size && y <= size && b[y][x] != 0) {
					b[y++][x++] = bSize;
				}
			}
		}
	}

	FOR(i, size) {
		FOR(j, size) {
			PRTD(b[i][j]);
		}
		PRTLN;
	}
	PRTLN;

	bipartiteInit();
	bu.vertexSize = aSize;
	bv.vertexSize = bSize;

	FOR(i, size){
		FOR(j, size) {
			if (a[i][j] == 0) continue;
			bu.adjMat[a[i][j]][b[i][j]] = 1;
		}
	}
	bipartiteDisplay();

	int nMatches = bipartiteMatch();
	printf("Number of matches: %d\n", nMatches);

	_getch();
	return 0;
}
