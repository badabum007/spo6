#include "memManagement.h"
#include <stdio.h>

void* findFreeMem(struct MemoryManagement* memManag, size_t size)
{
	if (memManag->freeMem == memManag->maxFreeMem)
		return memManag->memStartAddress;
	struct LinkedList* head = memManag->linkedList;
	size_t notAppropriate = 0;
	void* ptr, *preptr;
	ptr = head->segPtr;
	preptr = ptr;
	size_t sizeBetweenSegs;
	struct LinkedList* prehead = head;

	//TODO add adding to linkedList according to ptr value
	while(head->next != NULL){
		ptr = head->segPtr;
		sizeBetweenSegs = (size_t)ptr - (size_t)preptr;
		preptr = ptr;
		if (sizeBetweenSegs >= size){
			return (void*)((char*)ptr + head->segSize); //think a bit about size type conversion
		}
		notAppropriate += head->segSize + sizeBetweenSegs;
		prehead = head;
		head = head->next;
	}
	if (notAppropriate >= (memManag->freeMem - size)){
		puts("big segmentation");
		exit(1);
	}	
	return (void*)((char*)ptr + prehead->segSize);
}