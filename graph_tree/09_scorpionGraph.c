#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"
#include "graphSearch.h"

typedef struct degree_t {
	int degree;
	int adjacent[GRAPH_SIZE];
} Degree;

Degree d[GRAPH_SIZE];

void initDegree(void);
void displayDegree(void);

/*
void initDegree(void)
{
}
void displayDegree(void)
{
}
*/

void initDegree(void)
{
	int i;
	FOR(i, g.vertexSize) {
		d[i].degree = 0;
	}
}

void displayDegree(void);

void displayDegree(void)
{
	int i, j;
	PRT("degree:\n");

	FOR(i, g.vertexSize) {
		PRT("[%d] degree %d: ", i, d[i].degree);
		FOR(j, d[i].degree) {
			PRT("%-3d", d[i].adjacent[j]);
		}
		PRTLN;
	}
	PRTLN;
}

bool isTail(int v)
{
	return (d[v].degree == 2);
}

bool hasSting(int v)
{
	int sibling1 = d[v].adjacent[1];
	int sibling2 = d[v].adjacent[2];
	return (d[sibling1].degree == 1 || d[sibling2].degree == 1);
}

bool hasBody(int v)
{
	int sibling1 = d[v].adjacent[1];
	int sibling2 = d[v].adjacent[2];

	// legs - body - tail
	// adjcent numbers of body:
	// legs# + tail# = ( |V| - 3 ) + 1 = |V| - 2
	int bound = g.vertexSize - 2;

	return (d[sibling1].degree == bound || d[sibling2].degree == bound);
}

void checkScorpionGraph()
{
	displayDegree();
	// feet - body - tail - sting

	int i;
	FOR(i, g.vertexSize) {
		// find tail
		if (isTail(i) == false) {
			continue;
		}

		// find sting
		if (hasSting(i) == false) {
			continue;
		}

		// find body
		if (hasBody(i)) {
			printf("This one is a scorpion graph.\n");
			return;
		}
	}

	printf("This one is not a scorpion graph. \n");
}

int main(void)
{
	int i;
	freopen("09_scorpionGraph_input.txt", "r", stdin);
	//setbuf(stdout, NULL);
	int vertexSize, edgeSize;
	scanf("%d %d", &vertexSize, &edgeSize);

	Graph g;
	graphInit(vertexSize);
	g.isDirectedGraph = false;

	initDegree();

	int u, v, w;
	FOR(i, edgeSize) {
		scanf("%d %d", &u, &v);
		w = 1;

		graphAddEdge(u, v, w);
		d[u].degree++;
		d[u].adjacent[d[u].degree] = v;

		d[v].degree++;
		d[v].adjacent[d[v].degree] = u;
	}

	graphDisplay();

	checkScorpionGraph();

	_getch();
	return 0;
}