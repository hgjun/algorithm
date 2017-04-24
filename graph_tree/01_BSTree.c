#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "macrofunctions.h"

// Input data 
int  arrSize_;
int *arr_;

typedef struct treeNode_t {
	int key;
	struct treeNode_t *lc, *rc;
} TreeNode;

TreeNode *root_;

void      bstSearch(int v);
void      bstAdd(int v);
void      bstDisplay(void);
void      bstTraverse(TreeNode *parent, TreeNode *t, int depth);
void      bstDel(int v);
TreeNode* bstDelNode(TreeNode *delItem);
int       bstGetHeight(TreeNode *t);

/*

void bstSearch(int v)
{
}
void bstAdd(int v)
{
}
void bstDel(int v)
{
}
TreeNode* bstDelNode(TreeNode *delItem)
{
}
void bstDisplay(void)
{
}
void bstTraverse(TreeNode *parent, TreeNode *t, int depth)
{
}
int bstGetHeight(TreeNode *node)
{
}

*/

void bstSearch(int v)
{
	if (root_ == NULL) {
		PRT("Search: empty tree\n");
		return;
	}

	TreeNode *parent = NULL, *t;
	for (t = root_; t != NULL;) {
		if (v < t->key) {
			parent = t;
			t = t->lc;
		}
		else if (v > t->key) {
			parent = t;
			t = t->rc;
		}
		else if (v == t->key) {
			PRT("Search %d: parent %d\n", v, parent->key);
			return;
		}
	}
	PRT("Search %d fail: not exist\n", v);
	return;
}

void bstAdd(int v)
{
	if (root_ == NULL) {
		root_ = (TreeNode*)malloc(sizeof(TreeNode));
		root_->key = v;
		root_->lc = root_->rc = NULL;
	}
	else {
		TreeNode *parent = NULL, *t;
		bool isLeft;
		for (t = root_; t != NULL;) {
			if (v < t->key) {
				parent = t;
				t = t->lc;
				isLeft = true;
			}
			else if (v > t->key) {
				parent = t;
				t = t->rc;
				isLeft = false;
			}
			else if (v == t->key) {
				PRT("Add %d fail: already exists\n", v);
				return;
			}
		}
		
		TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
		newNode->key = v;
		newNode->lc = newNode->rc = NULL;

		if (isLeft) {
			parent->lc = newNode;
		}
		else {
			parent->rc = newNode;
		}
	}
	
}

void bstDel(int v)
{
	if (root_ == NULL) {
		PRT("Delete: empty tree\n");
		return;
	}

	TreeNode *parent = NULL, *t;
	bool isLeft;
	for (t = root_; t != NULL;) {
		if (v < t->key) {
			parent = t;
			t = t->lc;
			isLeft = true;
		}
		else if (v > t->key) {
			parent = t;
			t = t->rc;
			isLeft = false;
		}
		else if (v == t->key) {
			PRT("Delete %d\n", v);
			if (isLeft) {
				parent->lc = bstDelNode(t);
			}
			else {
				parent->rc = bstDelNode(t);
			}
			bstDisplay();
			return;
		}
	}
	PRT("Delete %d fail: not exist\n", v);
	return;
}

TreeNode* bstDelNode(TreeNode *delItem)
{
	if (delItem->lc == NULL && delItem->rc == NULL) {
		free(delItem);
		return NULL;
	}
	else if (delItem->lc != NULL && delItem->rc == NULL) {
		TreeNode *t = delItem->lc;
		free(delItem);
		return t;
	}
	else if (delItem->lc == NULL && delItem->rc != NULL) {
		TreeNode *t = delItem->rc;
		free(delItem);
		return t;
	}
	else {
		TreeNode *parent = NULL;
		TreeNode *t = delItem->rc;
		while (t->lc != NULL) {
			parent = t;
			t = t->lc;
		}

		if (t == delItem->rc) {
			t->lc = delItem->lc;
		}
		else {
			parent->lc = t->rc;

			t->lc = delItem->lc;
			t->rc = delItem->rc;
		}
		free(delItem);
		return t;
	}
}

void bstDisplay(void)
{
	if (root_ == NULL) {
		PRT("Display: empty tree\n");
		return;
	}
	bstTraverse(NULL, root_, 0);
}

void bstTraverse(TreeNode *parent, TreeNode *t, int depth)
{
	if (t == NULL) {
		return;
	}

	bstTraverse(t, t->rc, depth + 1);
	if (t == root_) {
		PRT("%d\n", root_->key);
	}
	else {
		PRT("%*s(%d)-%d\n", depth * 7, "", parent->key, t->key);
	}
	bstTraverse(t, t->lc, depth + 1);
}

int bstGetHeight(TreeNode *node)
{
	if (node == NULL) {
		return -1;
	}
	return MAX(bstGetHeight(node->lc) + 1, bstGetHeight(node->lc) + 1);
}


// Tree order data
// assume: BST Size = 17
int bstSize_ = 17;
int preorder_[18];
int inorder_[18];
int postorder_[18];
int orderIdx_;

void      bstOrderTest(void);
void      bstPreorder(TreeNode *t);
void      bstInorder(TreeNode *t);
void      bstPostorder(TreeNode *t);
void      getPostorder(int *preorder, int *inorder, int size);
int*      getSubTree(int *node, int start, int end);

/*

void bstOrderTest(void)
{
}
void bstPreorder(TreeNode *t)
{
}
void bstInorder(TreeNode *t)
{
}
void bstPostorder(TreeNode *t)
{
}


int* getSubTree(int *node, int start, int end)
{
}
void getPostorder(int *preorder, int *inorder, int size)
{
}


*/

void bstOrderTest(void)
{
	int i;
	orderIdx_ = 1;
	PRT("Preorder:\n");
	bstPreorder(root_);
	PRTLN;
	FOR(i, bstSize_) {
		PRT("%-3d", preorder_[i]);
	}
	PRTLN;

	orderIdx_ = 1;
	PRT("Inorder:\n");
	bstInorder(root_);
	PRTLN;
	FOR(i, bstSize_) {
		PRT("%-3d", inorder_[i]);
	}
	PRTLN;

	orderIdx_ = 1;
	PRT("Postorder:\n");
	bstPostorder(root_);
	PRTLN;
	FOR(i, bstSize_) {
		PRT("%-3d", postorder_[i]);
	}
	PRTLN;

	getPostorder(preorder_, inorder_, bstSize_);
	PRTLN;
}

void bstPreorder(TreeNode *t)
{
	if (t == NULL) {
		return;
	}

	PRTD(t->key);
	preorder_[orderIdx_++] = t->key;
	bstPreorder(t->lc);
	bstPreorder(t->rc);
}

void bstInorder(TreeNode *t)
{
	if (t == NULL) {
		return;
	}

	bstInorder(t->lc);
	PRTD(t->key);
	inorder_[orderIdx_++] = t->key;
	bstInorder(t->rc);
}

void bstPostorder(TreeNode *t)
{
	if (t == NULL) {
		return;
	}

	bstPostorder(t->lc);
	bstPostorder(t->rc);
	PRTD(t->key);
	postorder_[orderIdx_++] = t->key;
}

int* getSubTree(int *node, int start, int end)
{
	int *tmp = (int*)malloc(sizeof(int)*(end - start + 2));
	COPY_ARRAY(tmp, 1, node, start, end);
	return tmp;
}

void getPostorder(int *preorder, int *inorder, int size)
{
	if (size == 0) {
		return;
	}
	int root = preorder[1];
	int i;
	int mid;
	FOR(i, size) {
		if (inorder[i] == root) {
			mid = i;
			break;
		}
	}
	getPostorder(getSubTree(preorder, 2, mid), getSubTree(inorder, 1, mid - 1), mid - 1);
	getPostorder(getSubTree(preorder, mid + 1, size), getSubTree(inorder, mid + 1, size),size - mid);
	PRTD(root);
}

int main()
{
	FILE *fp = fopen("02_BSTree_input.txt", "r");

	int  i;
	char buf1[1024], buf2[1024];
	char *p;

	fgets(buf1, 1024, fp);
	strcpy(buf2, buf1);
	arrSize_ = 0;
	for (p = strtok(buf1, " "); p; p = strtok(NULL, " ")) {
		arrSize_++;
	}
	arr_ = (int*)malloc(sizeof(int) * (arrSize_ + 1));
	for (i = 1, p = strtok(buf2, " "); p; i++, p = strtok(NULL, " ")) {
		arr_[i] = atoi(p);
	}

	fclose(fp);


	PRT("Size: %d\n", arrSize_);
	FOR(i, arrSize_) {
		PRTD(arr_[i]);
	}
	PRTLN; PRTLN;


	bstDisplay();  // empty tree check

	bstSearch(1);  // empty tree check

	bstDel(1);

	PRT("height: %d\n", bstGetHeight(root_));

	bstAdd(arr_[1]);
	PRT("height: %d\n", bstGetHeight(root_));

	bstAdd(arr_[2]);
	PRT("height: %d\n", bstGetHeight(root_));

	FORFROM(i, 3, arrSize_) {
		bstAdd(arr_[i]);
	}
	PRT("height: %d\n", bstGetHeight(root_));

	bstDisplay();

	bstSearch(11);
	bstSearch(30);

	

	//bstDel( 1 );  // not exist

	//bstDel( 3 );  // case 1

	//bstDel( 38 ); // case 2

	//bstDel( 60 ); // case 3

	//bstDel( 45 ); // case 4

	//bstDel( 15 ); // case 5

	//PRTLN;
	//bstAdd(25);
	//bstDisplay();
	//bstDel( 28 ); // case 6

	
	bstOrderTest();

	free(arr_);
	system("pause");
	return 0;
}
