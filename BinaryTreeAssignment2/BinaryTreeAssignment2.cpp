/*******************************************************************************************
* File Name          : BinartTreeAssignment.c
* Description        : Prog8130 - Assignment 2: Binary Tree without recursion
*					   This program uses binary tree to hold and print a list of words
*					   organized randomly. Each word can consist of maximum 30 characters.
*
* Author:            :  Sinan KARACA - 8743013
* Date:              :  03.10.2021
********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// The correct sorted order using a binary tree is:
//      anykt
//      hkgth
//      hngrr
//      klunp
//      owrke
//      pvdat
//      qewar
//      reykn
//      tsifu
//      ubpoq
//      vsjkb
//      weydj

// data to be stored in tree.  In this case there is just a character string but this could have contained more

// replace inputData used for test put it in here and is created from Prog8130AssignDataCreator.exe 
const char* inputData[12] = {
		{ "hngrr"},
		{ "klunp"},
		{ "owrke"},
		{ "reykn"},
		{ "hkgth"},
		{ "weydj"},
		{ "anykt"},
		{ "vsjkb"},
		{ "qewar"},
		{ "tsifu"},
		{ "ubpoq"},
		{ "pvdat"}
};


// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
struct nodeData {
	char name[30];				// character string of the data being stored in the node
	struct nodeData* left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
	struct nodeData* right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
};


// structure defining a binary tree stack. It can be considered as linked list
struct nodeStack {
	struct nodeData* s;
	struct nodeStack* next;
};

// FUNCTION      : newNode
// DESCRIPTION   : Function used to create new node in the binary tree
// PARAMETERS    : const char data
// RETURNS       : nodeData structure

struct nodeData* newNode(const char *data)
{
	struct nodeData* nodeData = (struct nodeData*) malloc(sizeof(struct nodeData));
	strcpy_s(nodeData->name, data);
	nodeData->left = NULL;
	nodeData->right = NULL;

	return(nodeData);
}



// FUNCTION      : clear()
// DESCRIPTION   : Function used for clearing scanf buffer
// PARAMETERS    : NONE
// RETURNS       : NONE

void clear(void) {
	int c;
	while ((c = getchar() != '\n' && c != EOF));
}



// FUNCTION      : addToBinaryTree
//
// DESCRIPTION   :
//   This function will store the data in newNode into a binary tree according to alphabetical order
//
// PARAMETERS    :
//   newString - the string that is to be stored in the binary tree in alphabetical order
//
// RETURNS       :
//   Nothing
struct nodeData* addToBinaryTree(nodeData* rootHead, const char* newString) {
	// add code to put items into binary tree in alphabetical order here
	// consider using strcmp library function to decide if a name is greater or less than
	int compResult;

	// Create new tree if it is NULL
	if (rootHead == NULL) {
		return newNode(newString);
	}

	compResult = strcmp(rootHead->name, newString);

	if (compResult >= 0) {
		rootHead->left = addToBinaryTree(rootHead->left, newString);
	}
	else {
		rootHead->right = addToBinaryTree(rootHead->right, newString);
	}

	return rootHead;

}



// FUNCTION      : printBinaryTree
//
// DESCRIPTION   :
//   This function will print the entire binary tree out.  You can choose to print
//   it using recursion but more marks will be awarded if you do it non recursively.
//
// PARAMETERS    :
//				   struc nodeData (used to access the head of the tree.
//  
//
// RETURNS       :
//   Nothing
void printBinaryTree(struct nodeData *rootHead) {
	
	struct nodeData* current = rootHead; // store current node
	struct nodeStack* stack = NULL; // create a NULL node to start binary tree

	// Controlling while loop 
	int i = 0;
	// Counting the number of items inside the binary tree
	int count = 1;

	while (i == 0) {

		if (current != NULL) {

			// new item for stack
			struct nodeStack* newItem = (struct nodeStack*)malloc(sizeof(struct nodeStack));
			
			//If current node is not Null, send it to head of the stack
			newItem->s = current;

			newItem->next = stack;

			stack = newItem;
			// make the current Node, left of it
			current = current->left;

		}
		else {
			if (stack != NULL) {

				//create tempStack struct to delete it from stack
				struct nodeStack* tempStack;

				tempStack = stack;

				current = stack->s;

				stack = stack->next;

				// Delete the correspounding Node and print it
				free(tempStack);

				printf("%d : %s\n", count, current->name);
				count++;

				current = current->right;

			}
			else {
				//Exit from the while loop
				i = 1;
			}

		}

	}
	
}

struct nodeData* rootHead = NULL;	// head of the binary tree

int main() {
	int i;
	char opt[20];

	// put all the data into the binary tree
	for (i = 0; i < 12; i++)
		rootHead = addToBinaryTree(rootHead, inputData[i]);

	while (1) {
		printf("\n *****************************************\n");
		printf("\n *  Binart Tree operations:              *\n");
		printf("\n *  1. Print the Binary Tree             *\n");
		printf("\n *  2. Add an element to the Binary Tree *\n");
		printf("\n *  3. Quit						       *\n");
		printf("\n *****************************************\n");
		printf("\n Choose an option [1-3] :				    \n");

		scanf_s("%20s", &opt, 20);

		if (strcmp(opt, "1") == 0) {
			// print the entire tree.  It should come out in alphabetical order because of the way it was stored in the tree
			printBinaryTree(rootHead);
		}
		else if (strcmp(opt, "2") == 0) {
			scanf_s("%20s", &opt, 20);
			rootHead = addToBinaryTree(rootHead, opt);
		}
		else if (strcmp(opt, "3") == 0) {
			return 0;
		}
		

	}
	return 0;
}

