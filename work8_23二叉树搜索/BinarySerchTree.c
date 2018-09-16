#include"BinarySerchTree.h"
BSTreeNode* BuyBSTNode(BSTDataType x)
{
	BSTreeNode *newNode = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	newNode->_data = x;
	newNode->_left = NULL;
	newNode->_right = NULL;
	return newNode;
}
int BSTreeInsert(BSTreeNode** tree, BSTDataType x)
{
	BSTreeNode *root = *tree;
	BSTreeNode *cur, *parent;

	if (root == NULL)
	{
		*tree = BuyBSTNode( x);
		return 1;
	}
	cur = root;
	parent = cur;
	while (cur)
	{
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		else
			return 0;
	}
	if (parent->_data < x)
	{
		parent->_right = BuyBSTNode(x);
	}
	else
	{
		parent->_left = BuyBSTNode(x);
	}
	return 1;
}
int BSTreeRemove(BSTreeNode** tree, BSTDataType x)
{
	BSTreeNode *root = *tree;
	BSTreeNode *cur, *parent,*replace;
	if (root == NULL)
		return 0;
	cur = *tree;
	parent = cur;
	while (cur)
	{
		if (cur->_data > x)
		{
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_data < x)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_data == x)
		{
			//parent = cur;
			if (cur->_left == NULL && cur->_right == NULL)//叶子，左右孩子都为空
			{
				if (parent->_left == cur)
				{
					parent->_left = NULL;
					break;
				}
				else
				{
					parent->_right = NULL;
					break;
				}
			}
			else if (cur->_left == NULL && cur->_right != NULL)//cur只有左为空
			{
				if (parent == cur)
				{
					BSTreeNode **del = &cur;
					cur = cur->_right;
					parent = cur;
					del = NULL;
					break;
				}
				else if (parent->_left == cur)
				{
					parent->_left = cur->_right;
					cur->_right = NULL;
					break;
				}
				else
				{
					parent->_right = cur->_right;
					cur->_right = NULL;
					break;
				}
			}
			else if (cur->_left != NULL && cur->_right == NULL)//cur只有右为空
			{
				if (parent == cur)
				{
					cur = cur->_left;
					parent = cur;
					break;
				}
				else if (parent->_left == cur)
				{
					parent->_left = cur->_left;
					cur->_left = NULL;
					break;
				}
				else
				{
					parent->_right = cur->_left;
					cur->_left = NULL;
					break;
				}
			}
			else//cur左右均不为空
			{
				parent = cur;
				replace = cur->_right;
				while (replace->_left)
				{
					parent = replace;
					replace = replace->_left;
					
				}
				BSTDataType tmp = cur->_data;
				cur->_data = replace->_data;
				replace->_data = tmp;
				//return (BSTreeRemove(tree, replace->_data));//交换数字之后，不能构成搜索树
				///////////////////////////////////////
				if (replace->_left == NULL && replace->_right == NULL)
				{
					if (parent->_left == replace)
						parent->_left = NULL;
					else
						parent->_right = NULL;
				}
				else
				{
					if (parent->_left == replace)
					{
						parent->_left = replace->_right;
						replace->_right = NULL;
						break;
					}
					else
					{
						parent->_right = replace->_right;
						replace->_right = NULL;
						break;
					}
					/*parent->_right = replace->_right;
					replace->_right = NULL;
					break;*/
				}
			}
		}
		else
			return 0;
	}
	//free(cur);
	return 1;
}
BSTreeNode* BSTreeFind(BSTreeNode** tree, BSTDataType x)
{
	BSTreeNode *cur = *tree;
	while (cur)
	{
		if (cur->_data < x)
		{
			cur = cur->_right;
		}
		else if (cur->_data > x)
		{
			cur = cur->_left;
		}
		else
		{
			return cur;
		}
	}
	return NULL;
}
//void BSTreeInOrder(BSTreeNode** ppTree)
//{
//	if (*ppTree == NULL)
//	{
//		return;
//	}
//
//	BSTreeInOrder(&(*ppTree)->_left);
//	printf("%d ", (*ppTree)->_data);
//	BSTreeInOrder(&(*ppTree)->_right);
//}
void BSTreeInOrder(BSTreeNode* tree)
{
	if (tree == NULL)
		return;
	BSTreeInOrder(tree->_left);
	printf("%d ", tree->_data);
	BSTreeInOrder(tree->_right);
}
void TestBSTree()
{
	int i = 0;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	BSTreeNode* tree = NULL;
	for (i = 0; i < sizeof(a) / sizeof(BSTDataType); i++)
	{
		BSTreeInsert(&tree, a[i]);
	}
	//////////////////////////////////////删除叶子
	

	BSTreeRemove(&tree, 0);
	BSTreeRemove(&tree, 1);

	BSTreeRemove(&tree, 2);
	BSTreeRemove(&tree, 3);

	BSTreeRemove(&tree, 4);
	/*BSTreeRemove(&tree, 6);
	BSTreeRemove(&tree, 9);*/
	/////////////////////////////////////删除只有一边是空
	/*BSTreeRemove(&tree, 8);*/
	/////////////////////////////////////删除两边都不为空
	//BSTreeRemove(&tree, 7);
	BSTreeRemove(&tree, 5);

	BSTreeInOrder(tree);
	system("pause");
}
int BSTreeInsertR(BSTreeNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		*ppTree = BuyBSTNode(x);
		return 1;
	}

	if ((*ppTree)->_data> x)
		return BSTreeInsertR(&(*ppTree)->_left, x);
	else if ((*ppTree)->_data < x)
		return BSTreeInsertR(&(*ppTree)->_right, x);
	else
		return 0;
}
//
int BSTreeRemoveR(BSTreeNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		return -1;
	}

	if ((*ppTree)->_data < x)
	{
		return BSTreeRemoveR(&((*ppTree)->_right), x);
	}
	else if ((*ppTree)->_data > x)
	{
		return BSTreeRemoveR(&((*ppTree)->_left), x);
	}
	else
	{
		BSTreeNode* del = *ppTree;
		if ((*ppTree)->_left == NULL)
		{
			*ppTree = (*ppTree)->_right;
			free(del);
		}
		else if ((*ppTree)->_right == NULL)
		{
			*ppTree = (*ppTree)->_left;
			free(del);
		}
		else
		{
			BSTreeNode* replace = (*ppTree)->_right;
			while (replace->_left)
			{
				replace = replace->_left;
			}
			(*ppTree)->_data = replace->_data;
			return BSTreeRemoveR(&(*ppTree)->_right, replace->_data);
		}
	}

	return 1;
}
//
BSTreeNode* BSTreeFindR(BSTreeNode** ppTree, BSTDataType x)
{
	if (*ppTree == NULL)
	{
		return NULL;
	}

	if ((*ppTree)->_data > x)
	{
		return BSTreeFindR(&((*ppTree)->_left), x);
	}
	else if ((*ppTree)->_data < x)
	{
		return BSTreeFindR(&((*ppTree)->_right), x);
	}
	else
	{
		return *ppTree;
	}
}

void TestBSTreeR()
{
	int i = 0;
	BSTreeNode* pTree = NULL;
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	for (; i < sizeof(a)/sizeof(int); ++i)
	{	
		BSTreeInsertR(&pTree, a[i]);
	}

	BSTreeRemoveR(&pTree, 0);
	BSTreeRemoveR(&pTree, 1);
	BSTreeRemoveR(&pTree, 2);
	BSTreeRemoveR(&pTree, 3);
	BSTreeRemoveR(&pTree, 4);
	BSTreeRemoveR(&pTree, 5);
	BSTreeRemoveR(&pTree, 6);
	BSTreeRemoveR(&pTree, 7);
	BSTreeRemoveR(&pTree, 8);
	BSTreeRemoveR(&pTree, 9);
	BSTreeRemoveR(&pTree, 10);

	BSTreeInsertR(&pTree, a[2]);

	BSTreeInOrder(pTree);
	printf("\n");
	system("pause");
}
