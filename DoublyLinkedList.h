// DoublyLinkedList.h
// the value stored for each node is a char[10]

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct listNode {
	char data[10];
	struct listNode* next;
	struct listNode* previous;
} ListNode, *ListNodePtr;

typedef struct {
	ListNodePtr first;
	ListNodePtr last;
} List, *ListPtr;


ListNodePtr createListNode(const char * content);
ListPtr createEmptyList();

void addAfterLast(ListPtr, ListNodePtr);
ListNodePtr removeLast(ListPtr);

int getLengthOfList(ListPtr);

void printList(ListPtr);

//void addToTop(ListPtr, NodePtr);
//void addToBottom(ListPtr,NodePtr);
//void addAfter(NodePtr, NodePtr);
//NodePtr removeAfter(NodePtr);
//void addToSortedAscendingPosition(ListPtr list, NodePtr node);

#endif   // DOUBLYLINKEDLIST_H
