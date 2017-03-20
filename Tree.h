// Tree.h


#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DoublyLinkedList.h"

typedef struct treeNode {
	char data[10];
	struct treeNode * leftChild;
	struct treeNode * rightChild;
} TreeNode, *TreeNodePtr;


TreeNodePtr createTreeNode(const char *);

void printTree(TreeNodePtr);

ListPtr createListFromPostOrderTraversal(TreeNodePtr);


// void visitNodesPostOrder(TreeNodePtr treeNodePtr, void (*workToDoAtVisit)(TreeNodePtr));

// int isLeaf(TreeNodePtr);
//void setAsLeftChild(TreeNodePtr, TreeNodePtr);  // right, i don't need these, b/c struct members are public.. . i'm too much in Java mindset.
//void setAsRightChild(TreeNodePtr, TreeNodePtr);



#endif // TREE_H
