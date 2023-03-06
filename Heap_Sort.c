#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b, * b = temp;
}

void downUpdate(int* arr,int n, int ind) {
	while ((ind << 1) <= n) {//while the heap has its childs
		int temp = ind, l = ind << 1, r = ind << 1 | 1;
		if (arr[l] > arr[temp])temp = l;
		if (r <= n && arr[r] > arr[temp])temp = r;
		if (temp == ind)break;
		swap(&arr[temp], &arr[ind]);
		ind = temp;
	}
	return;
}

void heap_sort(int *arr ,int n) {
	arr -= 1;//the array is start in 1 position
	for (int i = n >> 2; i >= 1; --i) {
		downUpdate(arr, n, i);
	}
	for (int i = n; i > 1; --i) {
		swap(&arr[1], &arr[i]);
		downUpdate(arr, i - 1, 1);
	}
	return;
}

void output(int* arr, int n) {
	printf("arr[%d] = [",n);
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");
	return;
}

int main() {
	srand((unsigned)time(0));
	#define MAX_OP 20
	int* arr = (int*)malloc(sizeof(int) * MAX_OP);
	assert(arr);
	for (int i = 0; i < MAX_OP; i++) {
		arr[i] = rand() % 100;
	}
	output(arr, MAX_OP);
	heap_sort(arr, MAX_OP);
	output(arr, MAX_OP);
	return 0;
}