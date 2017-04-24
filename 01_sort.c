#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "macrofunctions.h"

int *arr_;
int arrBackup_[100];
int arrSize_;

void initArray()
{
	COPY_ARRAY(arr_, 1, arrBackup_, 1, arrSize_);
}

void showResult()
{
	int i;
	FOR(i, arrSize_) {
		PRTD(arr_[i]);
	}
	PRTLN;
}


/*


void selectionSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
}

void bubbleSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
}

void insertionSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
}

void countingSort(int *arr, int size, int maxK)
{
	PRT("%s: \n", __FUNCTION__);
	// maxK: max number of the dataset
	
}

void merge(int *arr, int head, int mid, int tail)
{

}

void mergeSort(int *arr, int head, int tail)
{

}

int partition(int *arr, int head, int tail)
{

}

void quickSort(int *arr, int head, int tail)
{

}

int quickSelection(int *arr, int size, int k)
{
	PRT("%s: \n", __FUNCTION__);
}


void heapify(int *arr, int root, int size)
{

}

void buildHeap(int *arr, int size)
{

}

void heapSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
}


*/


void selectionSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
	int i, j, maxIdx;
	FORDEC(i, size, 2) {
		maxIdx = 1;
		FORFROM(j, 2, i) {
			if (arr[j] > arr[maxIdx]) {
				maxIdx = j;
			}
		}
		SWAP(arr[maxIdx], arr[i]);
	}
}

void bubbleSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
	int i, j;
	FORDEC(i, size, 2) {
		FOR(j, i - 1) {
			if (arr[j] > arr[j + 1]) {
				SWAP(arr[j], arr[j + 1]);
			}
		}
	}
}

void insertionSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
	int i, j, newItem;
	FORFROM(i, 2, size) {
		newItem = arr[i];
		FORDEC(j, i - 1, 1) {
			if (arr[j] > newItem) {
				arr[j + 1] = arr[j];
			}
			else {
				arr[j + 1] = newItem;
				break;
			}
		}
	}
}

void countingSort(int *arr, int size, int maxK)
{
	PRT("%s: \n", __FUNCTION__);
	// maxK: max number of the dataset
	int i, cnt[1024];
	FILL_ARRAY(cnt, maxK, 0);
	FOR(i, size) {
		cnt[arr[i]]++;
	}
	FOR(i, maxK) {
		cnt[i] += cnt[i - 1];
	}

	int tmp[100];
	FOR(i, size) {
		tmp[cnt[arr[i]]--] = arr[i];
	}
	COPY_ARRAY(arr, 1, tmp, 1, size);
}

void merge(int *arr, int head, int mid, int tail)
{
	int i = head;
	int j = mid + 1;
	int tmp[100], t = 1;
	while (i <= mid && j <= tail) {
		tmp[t++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
	}
	while (i <= mid) {
		tmp[t++] = arr[i++];
	}
	while (j <= tail) {
		tmp[t++] = arr[j++];
	}
	COPY_ARRAY(arr, head, tmp, 1, tail - head + 1);
}

void mergeSort(int *arr, int head, int tail)
{
	if (head >= tail) {
		return;
	}
	int mid = (head + tail) / 2;
	mergeSort(arr, head, mid);
	mergeSort(arr, mid + 1, tail);
	merge(arr, head, mid, tail);
}

int partition(int *arr, int head, int tail)
{
	int pivot = arr[tail];
	int mid = head;
	int gt;
	FORFROM(gt, head, tail - 1){
		if (arr[gt] < pivot) {
			SWAP(arr[gt], arr[mid]);
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

int quickSelection(int *arr, int size, int k)
{
	PRT("%s: \n", __FUNCTION__);
	int head, tail, mid, gt, pivot;
	head = 1;
	tail = size;
	while (head < tail) {
		pivot = arr[tail];
		mid = head;
		FORFROM(gt, head, tail - 1){
			if (arr[gt] < pivot) {
				SWAP(arr[gt], arr[mid]);
				mid++;
			}
		}
		arr[tail] = arr[mid];
		arr[mid] = pivot;
		
		if (k == mid) {
			return arr[k];
		}
		else if (k < mid) {
			tail = mid - 1;
		}
		else if (k > mid) {
			head = mid + 1;
		}
	}
	if (head == tail && head == k) {
		return arr[k];
	}
	else {
		return -1;
	}
}


void heapify(int *arr, int root, int size)
{
	int lc, rc, child, parent = root;
	while (true) {
		lc = parent * 2;
		rc = lc + 1;
		if (rc <= size) {
			child = (arr[lc] >= arr[rc]) ? lc : rc;
		}
		else if (lc <= size) {
			child = lc;
		}
		else {
			break;
		}

		if (arr[child] > arr[parent]) {
			SWAP(arr[child], arr[parent]);
			parent = child;
		}
		else {
			break;
		}
	}
}

void buildHeap(int *arr, int size)
{
	int i;
	int internalNodeSize = size / 2;
	FORDEC(i, internalNodeSize, 1) {
		heapify(arr, i, size);
	}
}

void heapSort(int *arr, int size)
{
	PRT("%s: \n", __FUNCTION__);
	buildHeap(arr, size);
	int i = size;
	while (i > 1){
		SWAP(arr[1], arr[i]);
		heapify(arr, 1, --i);
	}
}

int main(void)
{
	FILE *fp = fopen("01_sort_input.txt", "r");

	int i;
	char buf1[1024], buf2[1024], *p;

	fgets(buf1, 1024, fp);
	strcpy(buf2, buf1);


	arrSize_ = 0;
	for (p = strtok(buf1, " "); p; p = strtok(NULL, " ")) {
		arrSize_++;
	}
	arr_ = (int*)malloc(sizeof(int) * (arrSize_ + 1));

	i = 1;
	arr_[0] = 0;
	for (p = strtok(buf2, " "); p; p = strtok(NULL, " ")) {
		arr_[i++] = atoi(p);
	}
	COPY_ARRAY(arrBackup_, 1, arr_, 1, arrSize_);

	PRT("data size: %d\n", arrSize_);
	FOR(i, arrSize_) {
		PRTD(arr_[i]);
	}
	PRTLN; PRTLN;

	selectionSort(arr_, arrSize_); showResult(); initArray();
	bubbleSort(arr_, arrSize_); showResult(); initArray();
	insertionSort(arr_, arrSize_); showResult(); initArray();
	countingSort(arr_, arrSize_, 100); showResult(); initArray();
	PRT("mergeSort:\n");
	mergeSort(arr_, 1, arrSize_); showResult(); initArray();
	PRT("quickSort:\n");
	quickSort(arr_, 1, arrSize_); showResult(); initArray();


	int k = 6;  // must test item 6 !!
	int kval = quickSelection(arr_, arrSize_, k);
	printf("%d-th value: %d\n", k, kval);
	showResult(); initArray();


	heapSort(arr_, arrSize_); showResult(); initArray();

	system("pause");
	return 0;
}

