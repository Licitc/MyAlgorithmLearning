#include<stdio.h>
#include<stdlib.h>	

typedef struct Node {
	int key;
	struct Node* lchild, * rchild;
}Node;

Node* getNewNode(int key) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->key = key;
	p->lchild = p->rchild = NULL;
	return p;
}

void clear(Node* node) {
	if (node == NULL)return;
	clear(node->lchild);
	clear(node->rchild);
	free(node);
	return;
}

//return tree's root that already changed
Node* insert(Node* root, int key) {
	if (root == NULL)return getNewNode(key);
	if (root->key == key)return root;
	if (root->key > key)root->lchild = insert(root->lchild, key);
	else root->rchild = insert(root->rchild, key);
	return root;
}

Node* predecessor(Node* root) {//zuozishudezuiyoujiedian
	Node* temp = root->lchild;
	while (temp->rchild)temp = temp->rchild;
	return temp;
}

Node* erase(Node* root, int key) {
	if (root == NULL)return root;
	if (root->key > key)root->lchild = erase(root->lchild, key);
	else if(root->key < key)root->rchild = erase(root->rchild, key);
	else {
		if (root->lchild == NULL || root->rchild == NULL) {//the root has one or zero child
			Node* temp = (root->lchild ? root->lchild : root->rchild);
			free(root);
			return temp;
		}else {//two child
			Node* temp = predecessor(root);
			root->key = temp->key;
			root->lchild = erase(root->lchild, temp->key);
		}
	}
	return root;
}

void __inorder(Node* root) {
	if (root == NULL)return;
	__inorder(root->lchild);
	printf("%d ", root->key);
	__inorder(root->rchild);
	return;
}

void inorder(Node* root){
	printf("in order :");
	__inorder(root);
	printf("\n");
	return;
}

int main() {
	int op, val;
	Node* root = NULL;
	while (~scanf_s("%d%d", &op, &val)) {
		switch (op)
		{
		case 1:root = insert(root, val); break;
		case 2:root = erase(root, val); break;
		default:
			break;
		}
		inorder(root);
	}
	clear(root);
	return 0;
}