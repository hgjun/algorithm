#include <stdio.h>
#include <conio.h>
#include "macrofunctions.h"

typedef struct activity_t {
	int start;
	int finish;
} Activity;

typedef struct activitySelection_t {
	Activity act[100];
	int nActivities;

	Activity selection[100];
	int size;
} ActivitySelection;

ActivitySelection as;

int actPartition(Activity *arr, int head, int tail)
{
	Activity pivot = arr[tail];
	int mid = head;
	int gt;

	FORFROM(gt, head, (tail - 1)) {
		if (arr[gt].finish < pivot.finish) {
			SWAP(arr[mid].start, arr[gt].start);
			SWAP(arr[mid].finish, arr[gt].finish);
			mid++;
		}
	}
	arr[tail] = arr[mid];
	arr[mid] = pivot;
	return mid;
}

void actQuickSort(Activity *arr, int head, int tail)
{
	if (head >= tail) {
		return;
	}

	int mid = actPartition(arr, head, tail);
	actQuickSort(arr, head, mid - 1);
	actQuickSort(arr, mid + 1, tail);
}


int main(void)
{
	int i, j, k;
	freopen("09_greedyActivitySelection_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	scanf("%d", &as.nActivities);

	FOR(i, as.nActivities) {
		scanf("%d %d", &as.act[i].start, &as.act[i].finish);
	}

	actQuickSort(as.act, 1, as.nActivities);
	PRT("Sorted by finish time:\n");
	FOR(i, as.nActivities) {
		PRT("%d %d\n", as.act[i].start, as.act[i].finish);
	}

	as.size = 1;
	as.selection[1] = as.act[1];

	FORFROM(i, 2, as.nActivities) {
		if (as.act[i].start >= as.selection[as.size].finish) {
			as.size++;
			as.selection[as.size] = as.act[i];
		}
	}

	PRT("\n\nSelected activities:\n");
	FOR(i, as.size) {
		PRT("%d %d\n", as.selection[i].start, as.selection[i].finish);
	}
	_getch();
	return 0;
}

