#include "memManagement.h"
#include <stdio.h>

void* findFreeMem(struct MemoryManagement* memManag, size_t size)
{
	puts("start find");
	if (memManag->freeMem == memManag->maxFreeMem)
		return memManag->memStartAddress;

	struct LinkedList* head = memManag->linkedList;
	size_t notAppropriate = 0;
	void* ptr, *preptr;
	ptr = head->segPtr;
	preptr = ptr;
	size_t sizeBetweenSegs;
	struct LinkedList* prehead = head;

	while(head->next != NULL){
		prehead = head;
		preptr = prehead->segPtr;
		head = head->next;
		ptr = head->segPtr;
		puts("iteration");
		printf("------preHeadPtr---  %p\n",preptr);
		printf("------HeadPtr---  %p\n",ptr);
		printf("------headSize---  %zd\n",head->segSize);
		//ptr = head->segPtr;
		sizeBetweenSegs = (size_t)preptr - (size_t)ptr - head->segSize;
		printf("------size---betweenSegs  %zd\n",sizeBetweenSegs);
		//preptr = ptr;
		if (sizeBetweenSegs >= size){
			return (void*)((char*)ptr + head->segSize); //think a bit about size type conversion
		}
		notAppropriate += head->segSize + sizeBetweenSegs;
		//prehead = head;
		//head = head->next;
	}
	puts("bad iteration");
	if (notAppropriate > (memManag->freeMem - size)){
		puts("big segmentation");
		exit(1);
	}	
	return (void*)((char*)preptr + prehead->segSize);
}