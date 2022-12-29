/* doublyLinkedList.h */
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

/* A node of our Doubly Linked List */
struct DoublyLinkedNode {
	int data;
	struct DoublyLinkedNode *nextNode;	
	struct DoublyLinkedNode *previousNode;	
};

/* Doubly Linked List Error
 * A Global variable that is set if there is an error in one of the Doubly Linked List routines. 
 * A value of 0 signifies no error present, or that the error was reset, a value of 1 
 * signifies an error present. */
int DLL_Error = 0;

/* Need forward reference, this is used for one of the other methods */
int insertNodeToEndOfList(int, struct DoublyLinkedNode **);

/* This function creates a new DoublyLinkedNode on the heap and returns
 * a pointer to this struct. */
struct DoublyLinkedNode *createDoublyLinkedHead(int data) {
	struct DoublyLinkedNode *newNode = malloc(sizeof(struct DoublyLinkedNode));
	
	/* Check for errors allocating memory for new node */
	if(newNode == NULL) {
		DLL_Error = 1;
		return NULL;
	}
	
	newNode->data = data;
	newNode->nextNode = NULL;
	newNode->previousNode = NULL;
	
	return newNode;
} 

/* This function creates a doubly linked list from the input array
 * numberOfElements contains the amount of elements in the inputArray */
struct DoublyLinkedNode *createDoublyLinkedListFromArray(int *inputArray, int numberOfElements)
{
	/* We cannot create a list from a NULL array */
	if(inputArray == NULL)	{
		DLL_Error = 1;
		return NULL;
	} 
	
	/* If we are to create a doublyLinkedList from the array, the amount of elements in the 
	 * array needs to be positive */
	if(numberOfElements <= 0) {
		DLL_Error = 1;
		return NULL;
	}
	
	/* Create new list starting at the head */
	struct DoublyLinkedNode *newList = createDoublyLinkedHead(inputArray[0]);
	
	/* Check for any errors creating new head */
	if(newList == NULL) {
		DLL_Error = 1;
		return NULL;
	}	
	
	/* Add remaining members of Array to Linked List
	 * exit if any errors during insertion */
	for(int i = 1; i < numberOfElements; i++)
	{
		if(insertNodeToEndOfList(inputArray[i], &newList) == -1) {
			//insertNodeToEndOfList(inputArray[i], &newList);
			DLL_Error = 1;
			return NULL;
		}
	}
	
	return newList;
}

/* Retrieve the head node of the doubly linked list
 * Parameter *nodePtr is a pointer to any node in the list */
struct DoublyLinkedNode *getNodeHead(struct DoublyLinkedNode *nodePtr) {
	
	/* If incoming node pointer is NULL, this is an error, return NULL */
	if(nodePtr == NULL) {
		DLL_Error = 1;		
		return NULL;
	}		
	
	/* Search the list until we find the node whose previous node is NULL
	 * This is the head node */
	while(nodePtr->previousNode != NULL) {
		nodePtr = nodePtr->previousNode;
	}
	
	return nodePtr;
}

/* Retrieve the tail node of the doubly linked list
 * Parameter *nodePtr is a pointer to any node in the list */
struct DoublyLinkedNode *getNodeTail(struct DoublyLinkedNode *nodePtr) {
	
	/* If incoming node pointer is NULL, this is an error, return NULL */
	if(nodePtr == NULL) {	
		DLL_Error = 1;	
		return NULL;
	}		
	
	/* Search the list until we find the node whose next node is NULL
	 * This is the tail node */
	while(nodePtr->nextNode != NULL) {
		nodePtr = nodePtr->nextNode;
	}
	
	return nodePtr;
}

/* Retrieve the next node of the doubly linked list
 * Parameter *nodePtr is a pointer to any node in the list 
 * A returned NULL is valid if the next node is the tail and points to NULL
 * Check DLL_Error to see if returned NULL is an error */
struct DoublyLinkedNode *getNodeNext(struct DoublyLinkedNode *nodePtr) {
	
	/* If incoming node pointer is NULL, this is an error, return NULL */
	if(nodePtr == NULL) {	
		DLL_Error = 1;	
		return NULL;
	}		
	
	return nodePtr->nextNode;
}

/* Retrieve the previous node of the doubly linked list
 * Parameter *nodePtr is a pointer to any node in the list 
 * A returned NULL is valid if the previous node is the head and points to NULL
 * Check DLL_Error to see if returned NULL is an error */
struct DoublyLinkedNode *getNodePrevious(struct DoublyLinkedNode *nodePtr) {
	
	/* If incoming node pointer is NULL, this is an error, return NULL */
	if(nodePtr == NULL) {	
		DLL_Error = 1;	
		return NULL;
	}		
	
	return nodePtr->previousNode;
}

/* Returns the number of nodes in the list
 * Parameter *nodePtr is a pointer to any node in the list
 * A returned value of -1 signifies an error */
int getNumberOfNodesInList(struct DoublyLinkedNode *nodePtr) {
	
	/* An Empty list has zero nodes
	 * We do not set DLL_Error = 1 since
	 * A nodePtr that points to NULL is allowed and 
	 * has zero nodes and we return zero */
	if(nodePtr == NULL) {
		return 0;
	}
			
	/* Get the head of the list in order to start counting nodes
	 * There might be a more efficient routine but this gets the job done */
	struct DoublyLinkedNode *currentNode = getNodeHead(nodePtr);	
	/* Check to make sure that we have a valid Node */
	if(currentNode == NULL) {
		DLL_Error = 1;
		return -1;
	}
	
	/* Start counting nodes */
	int numberOfNodes = 0;
	while(currentNode != NULL) {
		numberOfNodes++;
		currentNode = currentNode->nextNode;
	}
	
	return numberOfNodes;
}

/* Inserts a node to the beginning of the list. This is one of the few functions
 * where we need a pointer to a pointer **headPtr, we need this because we will
 * be inserting a new node to the beginning of the list, making it in essence
 * the new head, we then update this pointer to point to the new head. We only do this
 * becuase traditionally linked lists have been accessed through a pointer to
 * the head of the list. Implementation can be changed for other scenarios. */
int insertNodeToBeggingOfList(int nodeData, struct DoublyLinkedNode **headPtr) {	
	
	/* If the headPtr is null, we assume this was done on purpose and that we
	 * are creating a node for a new list. We create a new node and make it the head */
	if(headPtr == NULL || (*headPtr) == NULL) {
		struct DoublyLinkedNode *newHead = malloc(sizeof(struct DoublyLinkedNode));
		newHead->data = nodeData;
		newHead->previousNode = NULL;
		newHead->nextNode = NULL;
		*headPtr = newHead;			
		return 1;
	}
	
	/* Check to see if the supplied pointer points to the head node.
	 * The previous node of the head will always point to NULL
	 * Even though we can find the head of the list with a regular pointer, we need the 
	 * actual address of the head pointer supplied to us as a parameter
	 * in the function since we will be updating this pointer */
	if((*headPtr)->previousNode != NULL) {
		DLL_Error = 1;		
		return -1;
	}	
	
	/* Create node and make/change associations */
      	struct DoublyLinkedNode **oldHead = headPtr;
	struct DoublyLinkedNode *newHead = malloc(sizeof(struct DoublyLinkedNode));
	newHead->data = nodeData;
	newHead->nextNode = *oldHead;	
	/* Previous node on the head always points to NULL */	
	newHead->previousNode = NULL; 	
	(*oldHead)->previousNode = newHead;
	/* The old head now becomes the new head */
	*oldHead = newHead;
	return 1;	
}

/* Inserts a node to the end of the list. **nodePtr is a double pointer to any node in the list */
int insertNodeToEndOfList(int nodeData, struct DoublyLinkedNode **nodePtr) {
	
	/* This pointer cannot be NULL. */
	if(nodePtr == NULL)
	{
		DLL_Error = 1;
		return -1;
	}
	
	/* If the *nodePtr is null, we assume this was done on purpose and that we
	 * are createing a node for a new list. We create a new node and make it the head */
	if(*nodePtr == NULL) {
		struct DoublyLinkedNode *newHead = malloc(sizeof(struct DoublyLinkedNode));
		newHead->data = nodeData;
		newHead->previousNode = NULL;
		newHead->nextNode = NULL;
		*nodePtr = newHead;		
		return 1;
	}
	
	/* Get the tail node */
	struct DoublyLinkedNode *oldTail = getNodeTail(*nodePtr);
	/* Check to see if we got an error finding the tail node */
	if(DLL_Error == 1)
		return -1;
	
	/* We now create the new tail node and add this node to the
	 * end of the list */		
	struct DoublyLinkedNode *newTail = malloc(sizeof(struct DoublyLinkedNode));
	newTail->data = nodeData;
	newTail->nextNode = NULL;
	newTail->previousNode = oldTail;	
	/* The old tail now points to the new tail */
	oldTail->nextNode = newTail;
	return 1;
}

/* This function returns a pointer to the node in the linked list from that supplied data
 * Returns NULL if no node is found, or if an error was present, check for DLL_Error */
struct DoublyLinkedNode *getNodeFromData(int searchData, struct DoublyLinkedNode *nodePtr) {
	
	/* We cannot search a list that is NULL */
	if(nodePtr == NULL) {		
		DLL_Error = 1;
		return NULL;
	}
	
	/* We need to start searching for our Node from the beginning of the list */
	struct DoublyLinkedNode *currentNode = getNodeHead(nodePtr);
	
	/* Check for any errors from getNodeTail() */
	if(currentNode == NULL) {		
		DLL_Error = 1;		
		return NULL;
	}	
	
	while(currentNode != NULL) {	
	
		/* We found the node with the data that we were looking for
		 * No need to keep on searching */	
		if(currentNode->data == searchData) {			
			break;
		}
		
		/* We've reached the end of the list without finding our selected node
		 * We can exit this method, no need to keep on looking */
		if(currentNode->nextNode == NULL) {				
			return NULL;
		}
			
		/* Keep on searching */
		currentNode = currentNode->nextNode;
	};	
	
	return currentNode;		
}

/* Inserts a node into the list after a selected node. */
int insertAfterSelectedNode(int dataToInsert, int afterNodeData, struct DoublyLinkedNode *nodePtr)
{	
	/* Pointer cannot be NULL */
	if(nodePtr == NULL) {
		DLL_Error = 1;
		return -1;
	}
	
	/* Search for the specified node */
	struct DoublyLinkedNode *insertAfterNode = getNodeFromData(afterNodeData, nodePtr);
	
	/* The node that we want to insert afterwards does not exist.
	 * This is not an error, the node simply does not exist */
	if(insertAfterNode == NULL) {
		return -1;
	}		
	
	/* Create node to insert and change all associations needed to properly insert node into list */
	struct DoublyLinkedNode *nodeToInsert = malloc(sizeof(struct DoublyLinkedNode));
	nodeToInsert->data = dataToInsert;
	nodeToInsert->nextNode = insertAfterNode->nextNode;
	nodeToInsert->previousNode = insertAfterNode;	
	insertAfterNode->nextNode->previousNode = nodeToInsert;
	insertAfterNode->nextNode = nodeToInsert;	
	return 1;
}

/* Deletes the first node of the list, the head node. 
 * We need the pointer to the head since we will be updating
 * the head address */
int deleteHead(struct DoublyLinkedNode **headPtr) {
	
	/* Unable to delete a the node head if the pointer does not point to anything */
	if(headPtr == NULL || (*headPtr) == NULL) {
		DLL_Error = 1;
		return -1;
	}
	
	/* Check to see if the supplied pointer points to the head of the list, we can 
	 * The previous node of the HEAD will always point to NULL */
	if((*headPtr)->previousNode != NULL) {
		DLL_Error = 1;
		return -1;		
	}
	
	/* If there is only one node in the list, the head == tail
	 * Special case of deleting */
	if(getNumberOfNodesInList(*headPtr) == 1)
	{
		free(*headPtr);
		*headPtr = NULL;
		return 1;
	}
	
	/* We now change all the associations of the head and free the space */
	struct DoublyLinkedNode **oldHeadPtr = headPtr;
	struct DoublyLinkedNode *newHeadPtr = (*oldHeadPtr)->nextNode;	
	newHeadPtr->previousNode = NULL;
	free(*oldHeadPtr);
	*oldHeadPtr = newHeadPtr;
	return 1;
}

/* Delete all the nodes from the list. nodePtr can store the address of any node. 
 * We need a double pointer to update the address of this node to NULL since
 * the list is deleted. We need to avoid "access after free" errors. */
int deleteList(struct DoublyLinkedNode **nodePtr) {	
	/* Pointer cannot be NULL. Pointer needs to point to any node in the list */
	if(nodePtr == NULL || *nodePtr == NULL) {
		DLL_Error = 1;
		return -1;
	}	
	
	/* We start deleting the list from the head, we first must
	 * get the head node */
	struct DoublyLinkedNode *nodeToDelete = getNodeHead(*nodePtr);
		
	/* Check to see if there was an error while trying to find the head node */
	if(nodeToDelete == NULL) {
		DLL_Error = 1;
		return -1;
	}	
	
	/* Loop through all the nodes and delete (free)*/
	struct DoublyLinkedNode *nextNode;
	while(nodeToDelete != NULL) {
		nextNode = nodeToDelete->nextNode;
		free(nodeToDelete);
		nodeToDelete = nextNode;	
	}	
	
	/* After freeing the memory, we need to make sure the original pointer now points to NULL 
	 * in order to avoid "access after free" errors. */
	*nodePtr = NULL;
	return 1;
}

/* Deletes the last node of the list, the tail. We need a pointer to the
 * head in case the tail and the head are the same (1 element list). We then
 * need to update the head pointer. */
int deleteTail(struct DoublyLinkedNode **headPtr) {
	
	/* Pointer cannot be NULL */
	if(headPtr == NULL || (*headPtr) == NULL) {
		DLL_Error = 1;
		return -1;
	}
	
	/* Check to see if the supplied pointer points to the head of the list. 
	 * The previous node of the HEAD will always point to NULL */
	if((*headPtr)->previousNode != NULL) {
		DLL_Error = 1;
		return -1;
	}	
	
	/* Find the tail node and check for errors */
	struct DoublyLinkedNode *tailToDelete = getNodeTail(*headPtr);
	if(tailToDelete == NULL) {
		DLL_Error = 1;
		return -1;
	}
		
	/* If there is only one node in the list, the head == tail
	 * Special case of deleting */
	if(getNumberOfNodesInList(*headPtr) == 1) {
		free(tailToDelete);
		*headPtr = NULL;
		return 1;
	}	
	
	tailToDelete->previousNode->nextNode = NULL; 
	free(tailToDelete);
	return 1;
}

/* Deletes the selected Node. We need the **headPtr in case the node that we
 * want to delete is the head, then we update the head pointer to point
 * to the new new head after deletion */
int deleteSelectedNode(int nodeData, struct DoublyLinkedNode **headPtr) {
	
	/* Pointer cannot be NULL */
	if(headPtr == NULL || (*headPtr) == NULL) {		
		DLL_Error = 1;
		return -1;
	}
	
	/* Check to see if the supplied pointer points to the head of the list. 
	 * The previous node of the HEAD will always point to NULL */
	if((*headPtr)->previousNode != NULL) {		
		DLL_Error = 1;
		return -1;
	}	
	
	/* Search for the specified node to delete */
	struct DoublyLinkedNode *nodeToDelete = getNodeFromData(nodeData, *headPtr);
	
	/* The node that we want to delete does not exist.
	 * No error is present, the node simply does not exist */
	if(nodeToDelete == NULL) {		
		return -1;
	}
	
	/* Check to see if the node that we are deleting is the head */
	if(nodeToDelete == *headPtr) {		
		int result = deleteHead(headPtr);
		/* returns 1 on success and -1 on error */
		return result;
	}
	
	/* Check to see if the node that we are deleting is the tail */
	if(nodeToDelete == getNodeTail(*headPtr)) {		
		int result = deleteTail(headPtr);
		/* returns 1 on success and -1 on error */
		return result;
	}
	
	/* If node is not the head or tail node,
	 * Change all the associations and delete Node */
	nodeToDelete->previousNode->nextNode = nodeToDelete->nextNode;
	nodeToDelete->nextNode->previousNode = nodeToDelete->previousNode;
	free(nodeToDelete);
	return 1;
}

/* Prints the entire list starting from the head node */
int printListFromHead(struct DoublyLinkedNode *listNode) {		
	/* If the input is NULL, we assume that the list is empty */
	if(listNode == NULL) {
		printf("[]");
		return 1;
	}
	
	/* Retrieve node head */
	struct DoublyLinkedNode *nodeHead = getNodeHead(listNode);
	
	/* Check for any errors retrieving head node */
	if(nodeHead == NULL) {
		DLL_Error = 1;	
		return -1;
	}		
	
	/* Print the data of the nodes */
	struct DoublyLinkedNode *currentNode = nodeHead;
	while(currentNode != NULL) {
		printf("%d ", currentNode->data);
		currentNode = currentNode->nextNode;
	};
	
	return 1;
}

/* Prints the entire list starting from the tail node */
int printListFromTail(struct DoublyLinkedNode *listNode)
{
	if(listNode == NULL) {
		printf("[]");
		return 1;
	}
	
	/* Retrieve node head */
	struct DoublyLinkedNode *nodeTail = getNodeTail(listNode);
	
	/* Check for any errors retrieving head node */
	if(nodeTail == NULL) {
		DLL_Error = 1;	
		return -1;
	}	
	
	/* Print the list starting from the tail going back to the head */
	struct DoublyLinkedNode *currentNode = nodeTail;
	while(currentNode != NULL) {
		printf("%d ", currentNode->data);					
		currentNode = currentNode->previousNode;
	};
	
	return 1;
}

#endif
