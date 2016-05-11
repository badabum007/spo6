#include "memManagement.h"

void* findFreeMem(size_t size)
{
	if (freeMem == maxFreeMem)
		return memStartAddres;
	struct Linkedlist* head = linkedlist;
	size_t currSize = 0, notAppropriate = 0;
	void* ptr, *preptr;
	ptr = head->segPtr;
	preptr = ptr;
	size_t sizeBetweenSegs;
	struct Linkedlist* prehead = head;

	//TODO add adding to linkedList according to ptr value
	while(head->next != NULL){
		ptr = head->segPtr;
		sizeBetweenSegs = ptr - preptr;
		preptr = ptr;
		if (sizeBetweenSegs >= size){
			return ptr + (void*)head->size; //think a bit about size type conversion
		}
		notAppropriate += head->size + sizeBetweenSegs;
		prehead = head;
		head = head->next;
	}
	if (notAppropriate >= (freeMem - size)){
		puts("big segmentation");
		exit(1);
	}	
	return ptr + (void*)prehead->size;
}