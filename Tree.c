// Tree.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Tree.h"
#include "DoublyLinkedList.h"

TreeNodePtr createTreeNode(const char * content) {
	TreeNodePtr toReturn = (TreeNodePtr) malloc(sizeof(TreeNode));
	strcpy(toReturn->data, content);
	toReturn->leftChild = NULL;
	toReturn->rightChild = NULL;
	
	return toReturn;
}

void printTree(TreeNodePtr treeNodePtr) {
	printf("\n");
	printTreeRecursiveFunction(treeNodePtr, 0);
}

// a root node has depth of zero
// this function uses depth to pretty print the tree
void printTreeRecursiveFunction(TreeNodePtr treeNodePtr, int depth) {
	// print this node
	for (int i = 1; i <= depth; i++) {
		printf("  ");
	}
	printf("%s\n", treeNodePtr->data);
	
	// print the left child tree (if it exists)
	if (treeNodePtr->leftChild != NULL)
		printTreeRecursiveFunction(treeNodePtr->leftChild, depth+1);
	
	// print the right child tree (if it exists)
	if (treeNodePtr->rightChild != NULL)
		printTreeRecursiveFunction(treeNodePtr->rightChild, depth+1);
}


ListPtr createListFromPostOrderTraversal(TreeNodePtr treeNodePtr) {
	ListPtr toReturn = createEmptyList();
	
	createListFromPostOrderTraversalRecursiveFunction(treeNodePtr, toReturn);
}

// when a node is visitted, it will be added to the end of the passed-in list
void createListFromPostOrderTraversalRecursiveFunction(TreeNodePtr treeNodePtr, ListPtr listToAddToPtr) {

	// -- base case: this tree is NULL
	if (treeNodePtr == NULL)
		return;
	
	// -- recursive case
	
	// visit nodes in left child tree
	createListFromPostOrderTraversalRecursiveFunction(treeNodePtr->leftChild, listToAddToPtr);
	
	// visit nodes in right child tree
	createListFromPostOrderTraversalRecursiveFunction(treeNodePtr->rightChild, listToAddToPtr);
	
	// visit this node
	addAfterLast(listToAddToPtr, createListNode(treeNodePtr->data));
}






/*
int isLeaf(TreeNodePtr treeNodePtr) {
	if ((treeNodePtr->leftChild == NULL) && (treeNodePtr->rightChild == NULL))
		return 1;
	else
		return 0;
}
*/

/*
// the child you add is allowed to be NULL
void setAsLeftChild(TreeNodePtr treeNodePtr, TreeNodePtr toAddAsChildTreeNodePtr) {
	treeNodePtr->leftChild = toAddAsChildTreeNodePtr;
}

void setAsRightChild(TreeNodePtr treeNodePtr, TreeNodePtr toAddAsChildTreeNodePtr) {
	treeNodePtr->rightChild = toAddAsChildTreeNodePtr;
}
*/


/*
ListPtr createListFromPostOrderTraversal(TreeNodePtr treeNodePtr) {
	
	// base case -- this tree is empty.
	if (treeNodePtr == NULL)
		return createEmptyList();
		
	// make a list from the left child tree
	ListPtr leftChildList = createListFromPostOrderTraversal(treeNodePtr);
	
	// make a list from the right child tree
	ListPtr rightChildList = createListFromPostOrderTraversal
	
	// make a list from this node
	ListPtr thisNodeList = createEmptyList();
	addToEnd(thisNodeList, createNode(treeNodePtr->data));
}
*/


/*
// the workToDoAtVisit function pointer takes in a TreeNodePtr argument, from which you can access the data or check to see
// what children it has
void visitNodesPostOrder(TreeNodePtr treeNodePtr, void (*workToDoAtVisit)(TreeNodePtr)) {
	// base case: this node is NULL
	// (happens when the left child or right child is empty)
	if (treeNodePtr == NULL)
		return;
	
	// visit all the nodes in the left child
	visitNodesPostOrder(treeNodePtr->leftChild, workToDoAtVisit);
	
	// visit all the nodes in the right child
	visitNodesPostOrder(treeNodePtr->rightChild, workToDoAtVisit);
	
	// visit this node
	(*workToDoAtVisit) (treeNodePtr);
}
*/


