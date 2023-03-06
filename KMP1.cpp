#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int BF(char S[], char T[]) {
	int i = 0, j = 0;
	while (S[i] != '\0' && T[j] != '\0') {
		if (S[i] == T[j]) {
			i++; 
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}	
	}
	if (T[j] == '\0') return (i - j);
	else return -1;
}


void getNext(char* T, int* next,int length) {
	int j = -1;  //jÇ°×º
	int	i = 0;  //iºó×º
	next[0] = -1;
	while (i < length) {
		if (j == -1 || T[i] == T[j]) {
			i++;
			j++;
			next[i] = j;
		}
		else j = next[j];
	}
}

int KMP(char S[], char T[]) {
	int i = 0, j = 0;
	int length = sizeof(T);
	int* next = (int*)malloc(sizeof(char) * length);

	int lenS = strlen(S);
	int lenT = strlen(T);
	getNext(S, next, length);
	while (i < lenS && j < lenT){
		if (j == -1 || S[i] == T[j]){
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j == lenT)
		return (i - j);
	else
		return -1;
}

int main(void) {
	// ind:       0123456789
	char src[] = "abaabaabbab";
	char pat[] = "bba";

	printf("ind = %d\n",  BF(src, pat)); // 7
	printf("ind = %d\n", KMP(src, pat)); // 7

	return 0;
}