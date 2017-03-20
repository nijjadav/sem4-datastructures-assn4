// Assignment 4
// David Nijjar

// Reads in a mathematical expression written in polish notation (aka prefix notation)
// (where the operator comes before its two operands), and prints out the value it would have if it would be evaluated.

// This assignment developed practice with linked lists, stacks, trees, and
// illustrates using a stack to evaluate an expression written in reverse polish (aka postfix) notation.

// assumption: each line of the file has a maximum of 9 characters, not including the newline.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Tree.h"

void testDoublyLinkedList();
void testDoublyLinkedList2();
void testStack();
void testTree();

TreeNodePtr buildExpressionTree(char expression[][10], int * indexOfNextItemToRead, int numItems);
int isOperator(const char *);

double evaluateExpressionInPrefixNotation(ListPtr);


int main(int argc, char *argv[]) {
	
	//testDoublyLinkedList();
	//testStack();
	//testDoublyLinkedList2();
	//testTree();
	
	
	//-- read in lines from a file, transfering them into a list
	// assumption: each line is no more than 9 characters long, not including the newline
	
	ListPtr listOfLinesInFile = createEmptyList();
	
	FILE * in = fopen("mathExpression.txt", "r");
	
	char inputLine[50];
	char * returnedValue = fgets(inputLine, sizeof inputLine, in);  // will be NULL when EOF is reached
	
	while(returnedValue != NULL) {
		
		// strip off newline character, if it is there.
		// (it might not be there if this is the last line read in the file)
		if (inputLine[strlen(inputLine) - 1] == 10)
			inputLine[strlen(inputLine) - 1]= '\0';
		
		//printf("Line was: %s\n", inputLine);
		
		// put the value read into the list
		addAfterLast(listOfLinesInFile, createListNode(inputLine));
		
		returnedValue = fgets(inputLine, sizeof inputLine, in);
	}
	
	printf("The list of lines read in is: ");
	printList(listOfLinesInFile);
	printf("\n\n");
	
	// convert the list into an array of strings, just because it makes
	// the buildExpresionTree() function much easier to write.
	int numItems = getLengthOfList(listOfLinesInFile);
	char arrayOfItems [numItems][10];
	
	ListNodePtr currentNodePtr = listOfLinesInFile->first;
	
	for (int i = 0; i < numItems; i++) {
		strcpy(arrayOfItems[i], currentNodePtr->data);
		currentNodePtr = currentNodePtr->next;
	}
	
	/*
	for (int i = 0; i < numItems; i++) {
		printf("%s\n", arrayOfItems[i]);
	}
	*/
	
	int indexOfNextItemToRead = 0;
	TreeNodePtr expressionTree = buildExpressionTree(arrayOfItems, &indexOfNextItemToRead, numItems);
	
	// if the expression tree is bad, abort program
	if (expressionTree == NULL) {
		printf("Expression in file is bad!");
		return 1;
	}
	
	printf("The expression tree built is as follows:\n");
	printTree(expressionTree);
	printf("\n\n");
	
	// generate a reverse-polish expression from this tree.
	// (yes, it's silly to do this when we could jsut evaluate the expressionTree recursively, but the assignment
	// wants me to demonstrate evaluating a reverse-polish expression using a stack)
	ListPtr expressionInPrefixNotation = createListFromPostOrderTraversal(expressionTree);
	
	printf("The prefix notation list is: \n");
	printList(expressionInPrefixNotation);
	printf("\n\n");
	
	// evaluate this expression
	double expressionEvaluated = evaluateExpressionInPrefixNotation(expressionInPrefixNotation);
	
	printf("The expression evaluated is %f\n", expressionEvaluated);
	
	return 0;
}


double evaluateExpressionInPrefixNotation(ListPtr expressionInPrefixNotation) {
	StackPtr myStackPtr = createEmptyStack();
	
	ListNodePtr currentListNode = expressionInPrefixNotation->first;
	
	while(currentListNode != NULL) {
		char item[10];
		strcpy(item, currentListNode->data);
		
		//printf("evalauting item %s\n", item);
		
		if (isOperator(item) == 1) {
			
			
			
			double operand2, operand1;
			
			char * operand2AsString = pop(myStackPtr);
			char * operand1AsString = pop(myStackPtr);
			
			sscanf(operand2AsString, "%lf", &operand2);
			sscanf(operand1AsString, "%lf", &operand1);
						
			//printf("   operand2 is %s and as a double is %lf\n", operand2AsString, operand2);
			//printf("   operand1 is %s and as a double is %lf\n", operand1AsString, operand1);
						
			double calculation;

			if (strcmp(item, "+") == 0) {
				calculation = operand1 + operand2;
			}
			else if (strcmp(item, "-") == 0) {
				calculation = operand1 - operand2;
			}
			else if (strcmp(item, "/") == 0) {
				calculation = operand1 / operand2;
			}
			else if (strcmp(item, "*") == 0) {
				calculation = operand1 * operand2;
			}
			
			char calculationAsString[10];
			sprintf(calculationAsString, "%.6g", calculation);
			push(myStackPtr, calculationAsString);
			
			//printf("   calcuation is %lf\n", calculation);
		}
		else
			push(myStackPtr, item);
		
		
		currentListNode = currentListNode->next;
	}
	
	double toReturn;
	sscanf(pop(myStackPtr), "%lf", &toReturn);
				
	return toReturn;
}

// build an expression tree, from an array that holds an expression in polish notation
// the (*indexOfNextItemToRead) is the index to to the next item in the array to read (ie it has not yet been read).
// when this function returns, and (say) it has read 4 items, it will update (*indexOfNextItemToRead) accordingly
// so that future calls to this same function will read the next unread item correctly.
//
// returns NULL if an error happened (eg if the List is not a properly built expression tree)
// note: the array is allowed to have extraneous garbage data items following the items that make up a valid expression tree.

TreeNodePtr buildExpressionTree(char expression[][10], int * indexOfNextItemToRead, int numItems) {
	
		
	// error case: if we have reached the end of the list, this is an error; it menas that
	// there were operators earlier expecting operands to follow, but we have run out of items
	int indexOfLastItem = numItems - 1;
	if ( (*indexOfNextItemToRead) > indexOfLastItem ) {
		return NULL;
	}
	
	// read the next item, and then update the pointer to point to the next item
	char * item = expression[(*indexOfNextItemToRead)];
	(*indexOfNextItemToRead)++;
	
	
	// -- base case: the root of this expression tree is a number.
	if (!isOperator(item)) {
		return createTreeNode(item);
	}
	
	// -- recursive case: the item read is an operator. then, we expect two more expressionTrees to follow the operator
	else {
		TreeNodePtr theOperator;           // "operator" might be a reserved word..?
		TreeNodePtr leftChild;
		TreeNodePtr rightChild;
		
		theOperator = createTreeNode(item);
		
		leftChild = buildExpressionTree(expression, indexOfNextItemToRead, numItems);
		
		// check for error
		if (leftChild == NULL) {
			return NULL;
		}
		
		rightChild = buildExpressionTree(expression, indexOfNextItemToRead, numItems);
		// check for error
		if (rightChild == NULL) {
			return NULL;
		}
		
		// build tree
		theOperator->leftChild = leftChild;
		theOperator->rightChild = rightChild;
		
		// return the tree
		return theOperator;
	}
}

// returns 1 if the character is a valid operator
int isOperator(const char * stringToCheck) {
	
	if (strcmp(stringToCheck, "+") == 0)
		return 1;
	if (strcmp(stringToCheck, "-") == 0)
		return 1;
	if (strcmp(stringToCheck, "*") == 0)
		return 1;
	if (strcmp(stringToCheck, "/") == 0)
		return 1;
	
	return 0;
}




// ---- test functions ---------------------------------------------------------------

void testTree() {
	TreeNodePtr myRootNode = createTreeNode("/");
	
	TreeNodePtr aLeftSubTree = createTreeNode("+");
	aLeftSubTree->leftChild = createTreeNode("3");
	aLeftSubTree->rightChild = createTreeNode("4");
	
	myRootNode->leftChild = aLeftSubTree;
	
	//TreeNodePtr aRightSubTree = createTreeNode("-")->leftChild = (createTreeNode("*") -> leftChild = (createTreeNode("9")));
	//     ^okay, this chaining isn't very readable. nor can i get it to make work!
    
 	TreeNodePtr aRightSubTree = createTreeNode("-");
 	
	aRightSubTree->leftChild = createTreeNode("*");
 	aRightSubTree->leftChild->leftChild = createTreeNode("9");
 	aRightSubTree->leftChild->rightChild = createTreeNode("8");
 	
	aRightSubTree->rightChild = createTreeNode("10");
 	
 	myRootNode->rightChild = aRightSubTree;
	
	printTree(myRootNode);

}

void testDoublyLinkedList2() {
	ListPtr myList = createEmptyList();
	addAfterLast(myList, createListNode("A"));
	addAfterLast(myList, createListNode("B"));
	
	removeLast(myList);
	removeLast(myList);
	
	printf("Length is: %d\n", getLengthOfList(myList));
}

void testDoublyLinkedList() {
	ListNodePtr myListNode = createListNode("10");
	printf("myListNode contains %s\n", myListNode->data);
	
	ListPtr myList = createEmptyList();
	addAfterLast(myList, myListNode);
	
	addAfterLast(myList, createListNode("30"));
	addAfterLast(myList, createListNode("40"));
	
	printList(myList);
	printf("\n");
	
	ListNodePtr removedListNode = removeLast(myList);
	printf("removedListNode contains %s\n", removedListNode->data);
	
	printList(myList);
	printf("\n");
	printf("Length of List is: %d\n", getLengthOfList(myList));
}



void testStack() {
	StackPtr myStack = createEmptyStack();
	printf("is myStack empty? answer is: %d\n", isEmpty(myStack));
	
	printf("Pushing on A..\n");
	push(myStack, "A");
	printf("is myStack empty? answer is: %d\n", isEmpty(myStack));
	printStack(myStack);
	printf("\n");
	
	printf("Pushing onB..\n");
	push(myStack, "B");
	printStack(myStack);
	printf("\n");
	
	printf("Popping off B..\n");
	printf("popped value is: %s\n", pop(myStack));
	printf("is myStack empty? answer is: %d\n", isEmpty(myStack));
	printStack(myStack);
	printf("\n\n");
	
	printf("Popping off A..\n");
	printf("popped value is: %s\n", pop(myStack));
	printf("is myStack empty? answer is: %d\n", isEmpty(myStack));
	printStack(myStack);
	printf("\n\n");
	
}
