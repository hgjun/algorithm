#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "macrofunctions.h"
#include "graph.h"

typedef struct minDominatingSet_t {
	// DFS
	int visited[GRAPH_SIZE];
	int parent[GRAPH_SIZE];

	// Min dominating set
	int dominating[GRAPH_SIZE];
	int dominatedBy[GRAPH_SIZE];
	int size;
} MinDominatingSet;

MinDominatingSet m;

void minDominatingSet();
void visitMinDominatingSet(int u);

/*

void minDominatingSet()
{
}
void visitMinDominatingSet(int u)
{
}


*/

void minDominatingSet()
{
	// NP problem
	// but solvable if unrooted tree
	// D: dominating set
	// if v = leaf node  then v != D
	// if any children(v) is not dominated then v = D, else v != D

	FILL_ARRAY(m.visited, g.vertexSize, 0);
	FILL_ARRAY(m.parent, g.vertexSize, 0);
	FILL_ARRAY(m.dominating, g.vertexSize, 0);
	FILL_ARRAY(m.dominatedBy, g.vertexSize, 0);

	m.size = 0;
	int i;

	PRT("DFS visit:\n");
	FOR(i, g.vertexSize) {
		if (m.visited[i] == 0) {
			visitMinDominatingSet(i);
		}
	}

	PRTLN; PRTLN;
	PRT("Min dominating set size: %d\n\n", m.size);
	PRT("dominating: \n");
	FOR(i, g.vertexSize) {
		PRTD(i);
	}PRTLN;

	FOR(i, g.vertexSize) {
		PRTD(m.dominating[i]);
	}PRTLN; PRTLN;

	PRT("dominated by: \n");
	FOR(i, g.vertexSize) {
		PRTD(i);
	}PRTLN;

	FOR(i, g.vertexSize) {
		PRTD(m.dominatedBy[i]);
	}
	PRTLN; PRTLN;
}

void visitMinDominatingSet(int u)
{
	PRTD(u);
	m.visited[u] = 1;
	bool isLeafNode = true;
	int v;
	FOR(v, g.vertexSize) {
		if (graphIsConnected(u, v) && m.visited[v] == 0){
			isLeafNode = false;
			m.parent[v] = u;
			visitMinDominatingSet(v);
		}
	}

	if (isLeafNode == false) {
		FOR(v, g.vertexSize) {
			// set u as a dominating node if any child node is not yet dominated
			if (u == m.parent[v] && m.dominatedBy[v] == 0) {
				if (m.dominating[u] == 0) {
					m.dominating[u] = 1;
					m.dominatedBy[u] = u;
					m.size++;
				}
				m.dominatedBy[v] = u;
			}
		}
	}
	else if (isLeafNode && m.parent[u] == 0) {
		// leaf node and root node (isolated node)
		m.size++;
		m.dominating[u] = 1;
		m.dominatedBy[u] = u;
	}
}

int main(void)
{
	int i, j;
	freopen("07_dfs_minDominatingSet_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

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
	minDominatingSet();

	_getch();
	return 0;
}