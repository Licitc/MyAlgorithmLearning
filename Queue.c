#define  _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
	int* data;
	int head, tail;
	int length,cnt;
}Queue;

Queue* init(int n) {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = (int*)malloc(sizeof(int) * n);
	q->head = q->tail = q->cnt =0;
	q->length = n;
	return q;
}

int empty(Queue* q) {
	return q->cnt ==0;
}

int front(Queue* q) {
	//if (empty(q)) return 0;
	return q->data[q->head];
}

int push(Queue* q,int val) {
	if (q == NULL) return 0;
	if (q->cnt == q->length) return 0;
	q->data[q->tail++] = val;
	if (q->tail == q->length) q->tail -= q->length;
	q->cnt++;
	return 1;
}

int pop(Queue* q) {
	if (q == NULL) return 0;
	if (empty(q)) return 0;
	q->head++;
	if (q->head == q->length) q->head -= q->length;
	q->cnt--;
	return 1;
}

void output(Queue* q) {
	printf("Queue = [");
	for (int i = q->head, j = 0; j < q->cnt; j++) {
		int ind = (i + j) % q->length;
		printf(" %d", q->data[ind]);
	}
	printf("]\n");
	return;
}

void clear(Queue* q) {
	if (q == NULL) return;
	free(q->data);
	free(q);
	return;
}

#define MAX_OP  20

int main() {
	srand(time(0));
	Queue* q = init(MAX_OP);
	for (int i = 0; i < MAX_OP; i++) {
		int op = rand() % 2, val = rand() % 100;
		switch (op) {
			case 0: {
				printf("push %d to Queue = %d\n", val, push(q,val));	
			}break;
			case 1: {
				printf("pop %d from Queue = %d\n", front(q), pop(q));
			}break;
		}
		output(q);
	}
	printf("head: %d,tail: %d,count: %d", q->head, q->tail, q->cnt);
	for (int i = 0; i < MAX_OP; i++) {
		int val = rand() % 100;
		printf("push %d to Queue = %d\n", val, push(q, val));
	}
	output(q);
	return 0;
}