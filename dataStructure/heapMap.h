#pragma once

#include <stdio.h>
#include "macrofunctions.h"

#define MAP_MAX_SIZE 100

typedef struct mapData_t{
	int key;
	int value;
} MapData;

typedef struct heapMap_t{
	MapData data[MAP_MAX_SIZE];
	int size;
} HeapMap;

void     hmapInit(HeapMap *hmap);
bool     hmapIsEmpty(HeapMap *hmap);
bool     hmapIsExist(HeapMap *hmap, int key);
void     hmapDisplay(HeapMap *hmap, int displaySize);
void     hmapAddNode(HeapMap *hmap, int key, int val);
void     hmapSetValue(HeapMap *hmap, int key, int val);
int      hmapGetValue(HeapMap *hmap, int key);
int      hmapExtractMinKey(HeapMap *hmap);
MapData  hmapExtractMinData(HeapMap *hmap);
void     hmapHeapify(MapData *arr, int root, int size);

/*

void hmapInit(HeapMap *hmap, int maxSize)
{
}
bool hmapIsEmpty(HeapMap *hmap)
{
}
bool hmapIsExist(HeapMap *hmap, int key)
{
}
void hmapDisplay(HeapMap *hmap, int displaySize)
{
}
void hmapAddNode(HeapMap *hmap, int key, int val)
{
}
void hmapSetValue(HeapMap *hmap, int key, int val)
{
}
int hmapGetValue(HeapMap *hmap, int key)
{
}
int hmapExtractMinKey(HeapMap *hmap)
{
}
MapData hmapExtractMinData(HeapMap *hmap)
{
}
void hmapHeapify(HeapMap *arr, int root, int size)
{
}

*/

void hmapInit(HeapMap *hmap)
{
	hmap->size = 0;
}

bool hmapIsEmpty(HeapMap *hmap)
{
	return (hmap->size == 0);
}

bool hmapIsExist(HeapMap *hmap, int key)
{
	for (int i = 1; i <= hmap->size; i++) {
		if (hmap->data[i].key == key) {
			return true;
		}
	}
	return false;
}

void hmapDisplay(HeapMap *hmap, int displaySize)
{
	int i;
	printf("\nDisplay heap map [size %d]: \nidx   ", hmap->size);
	for (i = 1; i <= hmap->size; i++) {
		printf("%-3d ", i);
	}
	printf("\nkey   ");
	for (i = 1; i <= displaySize; i++) {
		printf("%-3d ", hmap->data[i].key);
	}
	printf("\nvalue ");
	for (i = 1; i <= displaySize; i++) {
		printf("%-3d ", hmap->data[i].value);
	}
	printf("\n");
}

void hmapAddNode(HeapMap *hmap, int key, int val)
{
	if (hmap->size == MAP_MAX_SIZE - 1) return;
	hmap->size++;
	hmap->data[hmap->size].key = key;
	hmap->data[hmap->size].value = val;
}

void hmapSetValue(HeapMap *hmap, int key, int val)
{
	for (int i = 1; i <= hmap->size; i++) {
		if (hmap->data[i].key == key) {
			hmap->data[i].value = val;
		}
	}
}

int hmapGetValue(HeapMap *hmap, int key)
{
	for (int i = 1; i <= hmap->size; i++) {
		if (hmap->data[i].key == key) {
			return hmap->data[i].value;
		}
	}
	return -1;
}

int hmapExtractMinKey(HeapMap *hmap)
{
	int internalNodeSize = hmap->size / 2;
	for (int i = internalNodeSize; i >= 1; i--) {
		hmapHeapify(hmap->data, i, hmap->size);
	}

	SWAP(hmap->data[1].key, hmap->data[hmap->size].key);
	SWAP(hmap->data[1].value, hmap->data[hmap->size].value);
	return hmap->data[hmap->size--].key;
}

MapData hmapExtractMinData(HeapMap *hmap)
{
	int internalNodeSize = hmap->size / 2;
	for (int i = internalNodeSize; i >= 1; i--) {
		hmapHeapify(hmap->data, i, hmap->size);
	}

	MapData minData = hmap->data[1];
	SWAP(hmap->data[1].key, hmap->data[hmap->size].key);
	SWAP(hmap->data[1].value, hmap->data[hmap->size].value);
	hmap->size--;
	return minData;
}

void hmapHeapify(MapData *arr, int root, int size)
{
	int lc, rc, parent, child;
	parent = root;

	while (true) {
		lc = parent * 2;
		rc = lc + 1;
		if (rc <= size) {
			child = (arr[lc].value <= arr[rc].value) ? lc : rc;
		}
		else if (lc <= size) {
			child = lc;
		}
		else {
			break;
		}

		if (arr[child].value < arr[parent].value) {
			SWAP(arr[child].key, arr[parent].key);
			SWAP(arr[child].value, arr[parent].value);
			parent = child;
		}
		else {
			break;
		}
	}
}


/* Test code
int main()
{
	HeapMap m;
	hmapInit(&m);
	hmapAddNode(&m, 1, 999);
	hmapAddNode(&m, 2, 999);
	hmapAddNode(&m, 13, 999);
	hmapAddNode(&m, 14, 999);
	hmapAddNode(&m, 15, 999);
	hmapSetValue(&m, 2, 30);
	hmapSetValue(&m, 14, 20);
	hmapSetValue(&m, 15, 10);
	hmapDisplay(&m, 5);


	PRT("find 3 : %d\n", hmapGetValue(&m, 2));
	PRT("extrace min %d\n", hmapExtractMinKey(&m));
	hmapDisplay(&m, 5);
	PRT("extrace min %d\n", hmapExtractMinData(&m).key);
	hmapDisplay(&m, 5);
	system("pause");
	return 0;
}

Result:

Display heap map [size 5]:
idx   1   2   3   4   5
key   1   2   13  14  15
value 999 30  999 20  10
find 3 : 30
extrace min 15

Display heap map [size 4]:
idx   1   2   3   4
key   2   14  13  1   15
value 30  20  999 999 10
extrace min 14

Display heap map [size 3]:
idx   1   2   3
key   1   2   13  14  15
value 999 30  999 20  10
계속하려면 아무 키나 누르십시오 . . .

*/