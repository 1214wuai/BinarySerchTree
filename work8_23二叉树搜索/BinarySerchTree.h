#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int BSTDataType;

typedef struct BSTreeNode
{
	struct BSTreeNode* _left;
	struct BSTreeNode* _right;
	BSTDataType _data;
}BSTreeNode;

int BSTreeInsert(BSTreeNode** tree, BSTDataType x);
int BSTreeRemove(BSTreeNode** tree, BSTDataType x);
BSTreeNode* BSTreeFind(BSTreeNode** tree, BSTDataType x);
void BSTreeInOrder(BSTreeNode* tree);
void TestBSTree();
//////////////////////////////////////////////////////////////ÏÂÃæµÝ¹é°æ±¾
int BSTreeInsertR(BSTreeNode** ppTree, BSTDataType x);
int BSTreeRemoveR(BSTreeNode** ppTree, BSTDataType x);
BSTreeNode* BSTreeFindR(BSTreeNode** ppTree, BSTDataType x);
void TestBSTreeR();