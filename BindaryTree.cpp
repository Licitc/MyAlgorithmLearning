#define  _CRT_SECURE_NO_WARNINGS 1
// MY LEARNING PROCESSING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//define  bindarytree node
typedef struct Node {
	int val;
	struct Node* lchild, * rchild;//two branches
}Node;

//define  bindarytree
typedef struct Tree {
	Node* root;
	int n;
}Tree;

Node* getNewNode(int val) {
	Node *p = (Node*)malloc(sizeof(Node));
	assert(p != NULL);
	p->val = val;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}

Tree* getNewaTree() {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	assert(tree != NULL);
	tree->n = 0;
	tree->root = NULL;
	return tree;
}

// root: the branch |val: just for compare if it is bigger or not  |  ret: a flag of insert succeed or fail
// this is a splay function
Node* insertNode(Node* root, int val,int *ret) {
	if (root == NULL) {//the node will first join this implementation
		*ret = 1;//insert succeed
		return getNewNode(val);//this can implement assignment operation
	}
	if (root->val == val) return root;
	if (root->val > val) root->lchild = insertNode(root->lchild,val,ret);
	else root->rchild = insertNode(root->rchild,val,ret);
	return root;
}

void insert(Tree* tree, int val) {
	int flag = 0;
	tree->root = insertNode(tree->root, val, &flag);
	tree->n += flag;
	return ;
}

void clearNode(Node* node) {
	if (node == NULL) return;
	clearNode(node->lchild);
	clearNode(node->rchild);
	free(node);
	return ;
}

void clearTree(Tree* tree) {
	clearNode(tree->root);
	free(tree);
	return ;
}

void outputNode(Node* root) {
	if (root == NULL) return;
	printf("%d", root->val);
	if (root->lchild == NULL && root->rchild == NULL) return;
	printf("(");
	outputNode(root->lchild);
	printf(",");
	outputNode(root->rchild);
	printf(")");
	return ;
}

void outputTree(Tree* tree) {
	printf("tree(%d) = ", tree->n);
	outputNode(tree->root);
	printf("\n");
	return;
}

//____ The following are sorted functions______HEN NIU BI DE DIGUI HANSHU ZHANSHI_____
void preorderNode(Node *node) {
	if (node == NULL) return;
	printf(" %d", node->val);
	preorderNode(node->lchild); 
	preorderNode(node->rchild);
	return;
}
void preorder(Tree *tree) {
	printf("preorder:");
	preorderNode(tree->root);
	printf("\n");
	return;
}

void inorderNode(Node* node) {
	if (node == NULL) return;
	inorderNode(node->lchild);
	printf(" %d", node->val);
	inorderNode(node->rchild);
	return;
}
void inorder(Tree* tree) {
	printf("inorder:");
	inorderNode(tree->root);
	printf("\n");
	return;
}

void postorderNode(Node* node) {
	if (node == NULL) return;
	postorderNode(node->lchild);
	postorderNode(node->rchild);
	printf(" %d", node->val);
	return;
}
void postorder(Tree* tree) {
	printf("postorder:");
	postorderNode(tree->root);
	printf("\n");
	return;
}
int main() {
	srand((unsigned int)time(0));
	Tree *tree = getNewaTree();
	for (int i = 0; i < 10; i++) {
		int val = rand() % 100;
		insert(tree, val);
		outputTree(tree);
	}
	//output bindarytree by different sequence
	preorder(tree);
	inorder(tree);// this will output a  increasing-ordered sequence
	postorder(tree);
	clearTree(tree);
	return 0;
}
