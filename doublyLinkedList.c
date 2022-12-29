#include <stdio.h>
#include <stdlib.h>
#include "doublyLinkedList.h"

int main()
{
	// Create pointer to the doubly Linked List Head	
	struct DoublyLinkedNode *doublyLinkedListHead = NULL;
	
	// Add three nodes to the beginning of the doubly linked list
	printf("Add three nodes to the beginning of list and print from the head\n");
	insertNodeToBeggingOfList(15, &doublyLinkedListHead);
	insertNodeToBeggingOfList(10, &doublyLinkedListHead);
	insertNodeToBeggingOfList(5, &doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Print list from the tail
	printf("\nPrint list starting from the tail\n");
	printListFromTail(doublyLinkedListHead);
	printf("\n");
	
	// Add three nodes to the end of the doubly linked list and print
	printf("\nAdd three nodes to the end of the doubly linked list and print\n");
	insertNodeToEndOfList(25, &doublyLinkedListHead);
	insertNodeToEndOfList(30, &doublyLinkedListHead);
	insertNodeToEndOfList(35, &doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Try to add node 11 right after node 9 (node 9 is not in the list)
	printf("\nTrying to add node 11 right after node 9 (node 9 not in list) and print list\n");
	insertAfterSelectedNode(11, 9, doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Add node 11 right after node 10 and print list
	printf("\nAdd node 11 right after node 10 and print list\n");
	insertAfterSelectedNode(11, 10, doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Print list from the tail
	printf("\nPrint list starting from the tail\n");
	printListFromTail(doublyLinkedListHead);
	printf("\n");
	
	// Delete head node and print list
	printf("\nDelete head node and print list\n");
	deleteHead(&doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Print list from the tail
	printf("\nPrint list starting from the tail\n");
	printListFromTail(doublyLinkedListHead);
	printf("\n");
	
	// Delete tail node and print
	printf("\nDelete tail node and print list\n");
	deleteTail(&doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Delete node 20 from the list and print
	printf("\nDelete node 20 (node 20 not in list) and print list\n");
	deleteSelectedNode(20, &doublyLinkedListHead);
	printListFromHead(doublyLinkedListHead);
	printf("\n");
	
	// Print number of nodes in List
	printf("\nNumber of nodes in List: %d\n", getNumberOfNodesInList(doublyLinkedListHead));
	printf("\n");	
	
	// Delete all the nodes in the List
	printf("Delete all nodes in the list\n");
	deleteList(&doublyLinkedListHead);	
	
	// Print number of node in List
	printf("\nNumber of nodes in list: %d\n", getNumberOfNodesInList(doublyLinkedListHead));
	
	// Show total amount of error during all operations on list
	printf("\nTotal amount of errors detected during list operations - (DLL Error): %d\n", DLL_Error);
	
	return 0;
}
