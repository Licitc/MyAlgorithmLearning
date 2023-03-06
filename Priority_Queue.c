#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct priority{
	 int* data;
	 int cnt, size;
}priority_queue;

priority_queue* init(int n) {
	priority_queue* q = (priority_queue*)malloc(sizeof(priority_queue));
	q->data = (int*)malloc(sizeof(int) * (n+1));
	q->cnt = 0;
	q->size = n;
	return q;
}

void clear(priority_queue* q) {
	if (q == NULL)return;
	free(q->data);
	free(q);
	return;
}
void swap(int *a,int *b){
	int temp = *a;
	*a = *b, *b = temp;
}

int empty(priority_queue* q) {
	if (q == NULL)return 0;
	return q->cnt == 0;
}

int top(priority_queue* q) {
	return q->data[1];
}

void push(priority_queue* q,int val) {
	if (q->cnt == q->size)return;
	q->cnt += 1;
	q->data[q->cnt] = val;
	int ind = q->cnt;
	while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
		swap(&q->data[ind], &q->data[ind >> 1]);
		ind >>= 1;
	}
	return;
}

int pop(priority_queue* q) {
	if(empty(q)) return 0;
	q->data[1] = q->data[q->cnt--];
	int ind = 1;
	while ((ind << 1) <= q->cnt) {
		int temp = ind,l = ind << 1,r = ind << 1 | 1;
		if (q->data[l] > q->data[temp])temp = l;
		if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
		if (temp == ind)break;
		swap(&q->data[ind], &q->data[temp]);
		ind = temp;
	}
	return 1;
}

int main() {
	srand(time(0));
	#define MAX_OP 20
	priority_queue* q = init(MAX_OP);
	for (int i = 0; i < MAX_OP; i++) {
		int val = rand() % 100;
		push(q,val);
		printf("insert %d to q\n", val);
	}
	for (int i = 0; i < MAX_OP; i++) {
		printf("%d ", top(q));
		pop(q);
	}
	return 0;
}