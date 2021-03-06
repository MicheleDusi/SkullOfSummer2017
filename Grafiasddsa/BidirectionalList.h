#ifndef BIDIRECTIONALLIST_H_
#define BIDIRECTIONALLIST_H_

#include <stdbool.h>

#ifndef SIZE_OPERATIONS
#	define SIZE_OPERATIONS
#	define INT_SWAP(a, b) a = a + b; b = a - b; a = a - b
#	define EMPTY_SIZE 0
#endif

#ifndef STRING_FORMATTING
#	define STRING_FORMATTING
	const char* STRING_TITLE = "LISTA [size: %d]\n";
#endif

typedef struct blinked_list_node {
	void* data;
	struct blinked_list_node* next;
	struct blinked_list_node* prev;
} blinked_list_node;

typedef struct blinked_list {
	int size;
	blinked_list_node* head;
	blinked_list_node* tail;	
} blinked_list;

// Initializing List
blinked_list* bl_initList(); // OK

// Size
int bl_getListSize(blinked_list* l); // OK

// Cancelling List
void bl_deleteList(blinked_list* l); // OK
void bl_purgeList(blinked_list* l); // OK

// Inserting Elements
void bl_insertFirstElement(blinked_list* l, void* new_element_data); // OK
void bl_insertLastElement(blinked_list* l, void* new_element_data); // OK
void bl_insertElementAtPosition(blinked_list* l, void* new_element_data, int pos); // OK
void bl_insertAllElementsLast(blinked_list* l, blinked_list* elements); // OK

// Deleting Elements
void bl_deleteFirstElement(blinked_list* l); // OK
void bl_deleteLastElement(blinked_list* l); // OK
void bl_deleteElementAtPosition(blinked_list* l, int pos); // OK
void bh_deleteElementByContent(binaryheap* h, void* element_to_delete); /// TODO
void bl_deleteElementsByCondition(blinked_list* l, bool (*condition)(void*)); // OK
void bl_deleteSubList(blinked_list* l, int start_pos, int end_pos); // OK // NEW

// Purging Elements
void bl_purgeFirstElement(blinked_list* l); // OK
void bl_purgeLastElement(blinked_list* l); // OK
void bl_purgeElementAtPosition(blinked_list* l, int pos); // OK
void bl_purgeElementsByCondition(blinked_list* l, bool (*condition)(void*)); // OK
void bl_purgeSubList(blinked_list* l, int start_pos, int end_pos); // OK // NEW

// Getting Elements
void* bl_getFirstElement(blinked_list* l); // OK
void* bl_getLastElement(blinked_list* l); // OK
void* bl_getElementAtPosition(blinked_list* l, int pos); // OK
blinked_list* bl_getElementsByCondition(blinked_list* l, bool (*condition)(void*)); // OK 
blinked_list* bl_getSubList(blinked_list* l, int start_pos, int end_pos); // OK

// Extracting Elements
void* bl_extractFirstElement(blinked_list* l); // OK
void* bl_extractLastElement(blinked_list* l); // OK
void* bl_extractElementAtPosition(blinked_list* l, int pos); // OK
blinked_list* bl_extractElementsByCondition(blinked_list* l, bool (*condition)(void*)); // OK
blinked_list* bl_extractSubList(blinked_list* l, int start_pos, int end_pos); // OK // NEW

// Searching Elements
bool bl_containsElement(blinked_list* l, void* element_content); // OK
bool bl_containsElementByCondition(blinked_list* l, bool (*condition)(void*)); // OK
int bl_countElementsByCondition(blinked_list* l, bool (*condition)(void*)); // OK 
int bl_getPositionOfElement(blinked_list* l, void* element_content); // OK

// Cloning List
blinked_list* bl_cloneOrderedList(blinked_list* l, void* (*clone)(void*)); // OK
blinked_list* bl_cloneSubList(blinked_list* l, int start_pos, int end_pos, void* (*clone)(void*)); // OK
blinked_list* bl_concatenateTwoLists(blinked_list* l1, blinked_list* l2, void* (*clone)(void*)); // OK

// Managing and Modifying List
void bl_swapTwoElements(blinked_list* l, int pos1, int pos2); // OK
void bl_reverseList(blinked_list* l); // OK // NEW
void bl_shiftListBy(blinked_list* l, int shift); // OK // NEW

// Generic Operations On Elements
void bl_iterateOnElements(blinked_list* l, void (*procedure)(void*)); // OK // NEW
void bl_mapElements(blinked_list* l, void* (*unaryMap)(void*)); // OK // NEW
void* bl_cumulateElements(blinked_list* l, void* (*binaryOperation)(void*, void*)); // OK // NEW
void* bl_getMinimumElement(blinked_list* l, int (*compare)(void*, void*)); // OK /// Refactored position
void* bl_getMaximumElement(blinked_list* l, int (*compare)(void*, void*)); // OK /// Refactored position

// Sorting List
void bl_sortByOrder(blinked_list* l, int (*compare)(void*, void*)); // OK

// Visualizing List
char* bl_listToString(blinked_list* l, char* (*toStringFunction)(void*)); // OK

#endif
