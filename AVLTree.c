#include<stdio.h>
#include<stdlib.h>	

typedef struct Node {
	int key, h; // h:tree's height.
	struct Node* lchild, * rchild;
}Node;

Node _NIL, * NIL = &_NIL;

Node* getNewNode(int key) {
	Node* p = (Node*)malloc(sizeof(Node));
	p->key = key;
	p->lchild = p->rchild = NIL;
	p->h = 1;
	return p;
}

void clear(Node* root) {
	if (root == NIL)return;
	clear(root->lchild);
	clear(root->rchild);
	free(root);
	return;
}

void UpdateHeight(Node* root) {
	int h1 = root->lchild->h, h2 = root->rchild->h;
	root->h = (h1 > h2 ? h1 : h2) + 1;
	return;
}

Node* left_rotate(Node* root) {
	Node* temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	UpdateHeight(root);
	UpdateHeight(temp);
	return temp;
}

Node* right_rotate(Node* root) {
	Node* temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	UpdateHeight(root);
	UpdateHeight(temp);
	return temp;
}

Node* maintain(Node* root) {
	if (abs(root->lchild->h - root->rchild->h) <= 1)return root;
	if (root->lchild->h > root->rchild->h) {// L
		if (root->lchild->rchild->h > root->lchild->lchild->h) {// L+
			root->lchild = left_rotate(root->lchild);// LR
		}
		root = right_rotate(root);// LL 
	}
	else {
		if (root->rchild->lchild->h > root->rchild->rchild->h) {// L+
			root->rchild = right_rotate(root->rchild);// LR
		}
		root = left_rotate(root);// LL 
	}

}
//return tree's root that already changed
Node* insert(Node* root, int key) {
	if (root == NIL)return getNewNode(key);
	if (root->key == key)return root;
	if (root->key > key)root->lchild = insert(root->lchild, key);
	else root->rchild = insert(root->rchild, key);
	UpdateHeight(root);
	return root;
}

Node* predecessor(Node* root) {//zuozishudezuiyoujiedian
	Node* temp = root->lchild;
	while (temp->rchild != NIL)temp = temp->rchild;
	return temp;
}

Node* erase(Node* root, int key) {
	if (root == NIL)return root;
	if (root->key > key)root->lchild = erase(root->lchild, key);
	else if (root->key < key)root->rchild = erase(root->rchild, key);
	else {
		if (root->lchild == NIL || root->rchild == NIL) {//the root has one or zero child
			Node* temp = (root->lchild ==  NIL ? root->rchild : root->lchild);
			free(root);
			return temp;
		}
		else {//two child
			Node* temp = predecessor(root);
			root->key = temp->key;
			root->lchild = erase(root->lchild, temp->key);
		}
	}
	UpdateHeight(root);
	maintain(root);
	return root;
}

void inorder(Node* root) {
	if (root == NIL)return;
	inorder(root->lchild);
	printf("%d [%d, %d]\n", root->key,root->lchild->h,root->rchild->h);
	inorder(root->rchild);
	return;
}


int main() {
	int op, val;
	NIL->key = 0;
	NIL->h = 0;
	NIL->lchild = NIL->rchild = NIL;
	Node* root = NIL;
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