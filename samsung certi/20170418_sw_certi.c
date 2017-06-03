#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <conio.h>
#include <time.h>
#include <limits.h>

#include "_macrofunctions.h"
int partition(int *arr, int head, int tail)
{
	int pivot = arr[tail];
	int mid = head;
	int gt;

	FORFROM(gt, head, (tail - 1)) {
		if (arr[gt] < pivot) {
			SWAP(arr[mid], arr[gt]);
			mid++;
		}
	}
	arr[tail] = arr[mid];
	arr[mid] = pivot;
	return mid;
}

void quickSort(int *arr, int head, int tail)
{
	if (head >= tail) {
		return;
	}

	int mid = partition(arr, head, tail);
	quickSort(arr, head, mid - 1);
	quickSort(arr, mid + 1, tail);
}

int road[1000];

int err[100];
int errCount;
int coverSize;

typedef struct group_t {
	int computed;
	int begin;
	int end;
	int prev;
	int next;
} Group;
Group group[1000];
int groupCount;

int main(void)
{
	int i, j;
	int result;
	
	freopen("22_roadCover.txt", "r", stdin);
	int test, testCount;
	scanf("%d", &testCount);
	
	FOR(test, testCount) {
		scanf("%d %d", &errCount, &coverSize);

		PRT("test#%d: errCount %d  coverSize %d\n", test, errCount, coverSize);
		FOR(i, errCount) {
			scanf("%d", &err[i]);
		}
		quickSort(err, 1, errCount);

		FILL_ARRAY(road, err[errCount] + coverSize - 1, 0);
		FOR(i, errCount) {
			road[err[i]] = 1;
		}
		FOR(i, err[errCount] + coverSize - 1) {
			PRTD(i);
		}PRTLN;
		FOR(i, err[errCount] + coverSize - 1) {
			PRTD(road[i]);
		}PRTLN;

		groupCount = 0;
		for (i = 0; i <= err[errCount];) {
			if (road[i] == 0) {  // case 1
				i++;
			}
			else if (road[i] == 1 && road[i + coverSize - 1] == 0) { // case 2			
				groupCount++;
				group[groupCount].begin = group[groupCount].end = i;
				group[groupCount].computed = 0;
				group[groupCount].prev = (groupCount > 1) ? groupCount - 1 : 1;
				group[groupCount].next = groupCount + 1;

				i++;
			}
			else {  // case 3			
				groupCount++;
				group[groupCount].begin = i;
				group[groupCount].end = i + coverSize - 1;
				group[groupCount].computed = 1;
				group[groupCount].prev = (groupCount > 1) ? groupCount - 1 : 1;
				group[groupCount].next = groupCount + 1;

				i += coverSize;
			}
		}
		group[groupCount + 1].next = -1;  // last dummy node to notify end



		for (i = 1; -1 != group[i].next; i = group[i].next) {
			if (group[i].computed == 1) {
				PRT("group %d computed \n", i);
				continue;
			}
			PRT("group %d check \n", i);
			if (i == 1 || group[group[i].prev].end < group[i].begin - coverSize) {
				group[i].computed = 1;
				group[i].end = group[i].end + coverSize - 1;
			}
			else if (group[group[i].prev].end >= group[i].begin) {
				PRT("included\n");
				group[i].computed = 1;
				group[group[i].prev].next = group[i].next;
			}
			else if (group[group[i].prev].end >= group[i].begin - coverSize && group[group[i].next].computed == 1) {
				int leftInterval = group[i].begin - group[group[i].prev].end + 1;
				int rightInterval = group[group[i].next].begin - 1 - group[i].begin;
				if (leftInterval < rightInterval) {
					group[i].computed = 1;
					group[group[i].prev].end = group[i].end;
					group[group[i].prev].next = group[i].next;
				}
				else {
					group[i].computed = 1;
					group[i].end = group[group[i].next].end;
					group[i].next = group[group[i].next].next;
				}
			}
			else if (group[group[i].prev].end >= group[i].begin - coverSize && group[group[i].next].computed == 0) {
				if (group[group[i].next].begin >= group[i].begin + coverSize * 2 - 1) {
					PRT("a\n");
					group[i].computed = 1;
					group[group[i].prev].end = group[group[i].next].end;
					group[group[i].prev].next = group[group[i].next].next;
				}
				else {
					int leftLength = group[i].begin - group[group[i].prev].begin + 1;
					int rightLegnth = group[group[i].next].begin - group[i].begin + 1;
					if (group[group[i].next].next == -1) {
						rightLegnth = 10000;
					}
					if (leftLength < rightLegnth) {
						PRT("b1\n");
						group[i].computed = 1;
						group[group[i].prev].end = group[i].end;
						group[group[i].prev].next = group[i].next;
					}
					else {
						PRT("b2  %d  %d\n", leftLength, rightLegnth);
						if (group[group[i].prev].end >= group[group[i].next].end - coverSize + 1){
							group[i].computed = 1;
							group[group[i].next].computed = 1;
							group[group[i].prev].end = group[group[i].next].end;
							group[group[i].prev].next = group[group[i].next].next;
						}
						else {
							group[i].computed = 1;
							group[i].end = group[i].end + coverSize - 1;
						}

					}
				}
			}
			//if (i == 5) break;
		}

		int coverLength = 0;
		for (i = 1; group[i].next != -1; i = group[i].next) {
			PRT("group%d: begin %d  end %d \n", i, group[i].begin, group[i].end);
			coverLength += group[i].end - group[i].begin + 1;
		}
		PRT("Result %d\n", coverLength); 
		PRTLN; PRTLN;
	}
	
	
	_getch();
	return 0;
}