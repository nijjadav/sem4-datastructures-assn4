// DoublyLinkedList.c
// the value stored for each node is a char[10]

#include "DoublyLinkedList.h"


/* behaviour available just by using the ListPtr struct, is geting the first node, and getting the last node */



int getLengthOfList(ListPtr listPtr) {
	
	int runningCount = 0;
	ListNodePtr currentNodePtr = listPtr->first;
		
	while (currentNodePtr != NULL) {
		currentNodePtr = currentNodePtr->next;
		runningCount++;
	}
	
	return runningCount;
}


/* create a new list node containing a short string for the data */
ListNodePtr createListNode(const char * content) {
	ListNodePtr new = (ListNodePtr) malloc(sizeof(ListNode));
	strcpy(new->data, content);
	new->next = NULL;
	new->previous = NULL;
	
	return new;

}

/* creates an empty list (which is just a struct -- ie not a pointer to dynamically allocated memory) */
ListPtr createEmptyList() {
	ListPtr toReturn = (ListPtr) malloc(sizeof(List));
	
	toReturn->first = NULL;
	toReturn->last = NULL;
	
	return toReturn;
}

/* add a node (not part of any list -- ie with NULL links) to the end of the list */
void addAfterLast(ListPtr listPtr, ListNodePtr node) {

	/* special case: List is empty - first and last are NULL */
	if (listPtr->last == NULL) {
		listPtr->first = node;
		listPtr->last = node;
	}
	else {
		node->previous = listPtr->last;
		listPtr->last->next = node;
		listPtr->last = node;
		
	}
	
}

/* Remove the last node from the list, and return it. */
ListNodePtr removeLast(ListPtr listPtr) {
	
	ListNodePtr toReturn;
	
	/* special case if list is empty - return NULL */
	if (listPtr->first == NULL)
		return NULL;
	
	else {
		toReturn = listPtr->last;
		
		listPtr->last = listPtr->last->previous;
		if (listPtr->last != NULL)               // happens if we just removed the last node
			listPtr->last->next = NULL;
		
		toReturn->previous = NULL;
		toReturn->next = NULL;
		
		if (listPtr->last == NULL)
			listPtr->first = NULL;
			
		return toReturn;
	}
}

// add a list to the end of list
// note: it may be dangerous to modify listToAddPtr; that is, to remove the last Node from the list
void addListToEnd(ListPtr listPtr, ListPtr listToAddPtr) {
	
	if (listPtr == NULL)
		return;
		
	//-- if the list to add is empty..
	if ((listToAddPtr == NULL) || (listToAddPtr->first == NULL))
		return;
	//-- if the list to add to is empty
	else if (listPtr->first == NULL) {
		listPtr->first = listToAddPtr->first;
		listPtr->last = listToAddPtr->last;
	}
	//-- if both lists are not empty
	else {
		listPtr->last->next = listToAddPtr->first;
		listToAddPtr->first->previous = listPtr->last;
		
		listPtr->last = listToAddPtr->last;
		listToAddPtr->first = listPtr->first;
	}
}


void printList(ListPtr listPtr) {
	printf("[");
	
	ListNodePtr currentNodePtr = listPtr->first;
	
	while(currentNodePtr != NULL) {
		printf("%s", currentNodePtr->data);
		if (listPtr->last != currentNodePtr) {
			printf(", ");
		}
		currentNodePtr = currentNodePtr->next;
	}
	
	printf("]");
}


