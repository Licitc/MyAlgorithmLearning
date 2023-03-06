#define  _CRT_SECURE_NO_WARNINGS 1
#define MAX_OP 20

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {
	int* data;
	int top, size;
}Stack;

Stack* init(int n) {
	Stack* p = (Stack*)malloc(sizeof(Stack));
	Stack* t = (int*)malloc(sizeof(int)*n);
	if (t == NULL) return;
	p->data = t;
	p->top = -1;
	p->size = n;
	return p;
}

int empty(Stack* p) {
	if (p == NULL) return 0;
	return p->top == -1;
}

int top(Stack* p) {
	if (p == NULL) return 0;
	if (empty(p)) return 0;
	return p->data[p->top];
}

int push(Stack* p ,int val) {
	if (p == NULL) return 0;
	if(p->top + 1 == p->size)return 0;
	p->top += 1;
	p->data[p->top] = val;
	return 1;
}

int pop(Stack* p) {
	if (p == NULL) return 0;
	if (empty(p)) return 0;
	p->top -= 1;
	return 1;
}

void clear(Stack* p) {
	if (p == NULL) return ;
	free(p->data);
	free(p);
	return;
}

void output(Stack* s) {
	printf("stack {%d] = [", s->top + 1);
	for (int i = s->top; i >= 0; i--) {
		printf("%d ", s->data[i]);
	}
	printf("]\n");
	return;
}

int main() {
	srand(time(0));
	Stack* s = init(MAX_OP);
	for (int i = 0; i < MAX_OP; i++) {
		int op = rand() % 2, val = rand() % 100;
		switch (op)
		{
			case 0: {
				printf("push %d to Stack = %d\n",val,push(s,val));
			}break;
			case 1: {
				printf("pop %d from Stack = %d\n", top(s), pop(s));
                //due to IDE ,printf() implement sequence is from head to tail
				//the result will have first front but second pop err phenomenon
			}break;
			default:
				break;
		}
		output(s);
	}
	return 0;
}