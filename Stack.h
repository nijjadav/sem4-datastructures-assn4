// Stack.h


#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DoublyLinkedList.h"

typedef struct stack {
	ListPtr	data;
} Stack, *StackPtr;


StackPtr createEmptyStack();

char * pop(StackPtr);
void push(StackPtr, const char * );
int isEmpty(StackPtr);

void printStack(StackPtr);

#endif // STACK_H
