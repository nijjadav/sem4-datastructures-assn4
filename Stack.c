// Stack.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Stack.h"

StackPtr createEmptyStack() {
	StackPtr toReturn = (StackPtr) malloc(sizeof(Stack));
	toReturn->data = createEmptyList();
	
	return toReturn;
}

int isEmpty(StackPtr stackPtr) {
	if (stackPtr->data->first == NULL)
		return 1;
	else
		return 0;
}


char * pop(StackPtr stackPtr) {
	// return NULL if the list is empty
	if (isEmpty(stackPtr))
		return NULL;
	
	ListNodePtr poppedNodePtr = removeLast(stackPtr->data);
	char * toReturn = poppedNodePtr->data;
	
	return toReturn;
}


void push(StackPtr stackPtr, const char * toPush) {
	addAfterLast(stackPtr->data, createListNode(toPush));
}


void printStack(StackPtr stackPtr) {
	printf("(bottom to top) ");
	printList(stackPtr->data);
}
