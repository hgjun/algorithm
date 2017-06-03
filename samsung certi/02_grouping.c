#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "_macrofunctions.h"

typedef struct group_t{
	int map[11][11];
	int size;
	int groupSize[101];
	int nGroups;
	int nodeSize;
} Group;
Group t;

typedef struct node_t{
	int value;
	int size;
	struct node_t *parent;
} Node;

Node node[101];

void unionSet(Node *u, Node *v);
Node* findSet(Node *u);

void unionSet(Node *u, Node *v)
{
	Node *ru = findSet(u);
	Node *rv = findSet(v);

	if (ru == rv) { // same group
		return;
	}
	t.nGroups--;
	if (ru->size > rv->size) {
		rv->parent = ru;
		ru->size += rv->size;
	}
	else {
		ru->parent = rv;
		rv->size += ru->size;
	}
}

Node* findSet(Node *u)
{
	Node *t;
	for (t = u; t != t->parent; t = t->parent);
	return t;
}

int main()
{
	freopen("test.txt", "r", stdin);

	int loop, loopCnt;

	scanf("%d", &loopCnt);
	PRT("Loop Cnt: %d\n", loopCnt);
	FOR(loop, loopCnt) {
		scanf("%d", &t.size);
		PRT("Map size: %d\n", t.size);
		

		int i, j;
		t.nodeSize = 0;
		Node *n;
		// MAKE SET
		t.nGroups = 0;
		FOR(i, t.size) {
			FOR(j, t.size) {				
				// nodeSize = size x size;
				t.nodeSize++;

				// init groupSize = 0
				t.groupSize[t.nodeSize] = 0;

				n = &node[t.nodeSize];

				// node name: 1 - nodeSize
				t.map[i][j] = t.nodeSize;				
				scanf("%d", &n->value);
				if (n->value == 1) {
					t.nGroups++;
				}
				n->parent = n;
				n->size = 1;
			}
		}
		
		Node *right, *down;
		FOR(i, t.size) {
			FOR(j, t.size) {
				n = &node[t.map[i][j]];

				if (n->value == 0){
					continue;
				}

				right = (j < t.size) ? &node[t.map[i][j+1]] : NULL;
				down = (i < t.size) ? &node[t.map[i+1][j]] : NULL;

				// check right
				if (right && right->value) {
					unionSet(n, right);
				}

				if (down && down->value) {
					unionSet(n, down);
				}
			}
		}
		PRT("\nGroup size: %d\n", t.nGroups);
		
		FOR(i, t.nodeSize) {
			if (node[i].value ==1 && node[i].parent == &node[i]) {
				PRTD(node[i].size);
			}
		}

		PRTLN; PRTLN; PRTLN;
		FOR(i, t.size) {
			FOR(j, t.size) {
				PRTD(t.map[i][j]);
			}
			PRTLN;
		}
		PRTLN; PRTLN; PRTLN;
		int k = 1;
		FOR(i, t.size) {
			FOR(j, t.size) {
				PRTD(node[k++].value);
			}
			PRTLN;
		}
	}
	
	_getch();
	return 0;

}

