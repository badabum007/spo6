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
		notAppropriate += prehead->segSize + sizeBetweenSegs;
		//prehead = head;
		//head = head->next;
	}
	if (head != NULL)
		notAppropriate += head->segSize;
	printf("notAppropriate %d\n", notAppropriate);
	//printf("%zd\n", memManag->maxFreeMem - notAppropriate - size);
	puts("bad iteration");
	if ((int)(memManag->maxFreeMem - notAppropriate - size) < 0){
		//printf("notAppropriate %d\n", notAppropriate);
		puts("big segmentation");
		exit(1);
	}	
	return (void*)((char*)memManag->linkedList->segPtr + memManag->linkedList->segSize);
}

void printmem(struct MemoryManagement* memManag)
{
	struct LinkedList* head = memManag->linkedList;
	struct LinkedList* prehead = memManag->linkedList;
	size_t sizeBetweenSegs;
	void* ptr, *preptr;
	for (int i = 0; i < memManag->maxFreeMem; i++){
		ptr = head->segPtr;
		preptr = prehead->segPtr;
		if (head != prehead){
			sizeBetweenSegs = (size_t)preptr - (size_t)ptr - head->segSize;
			for(int j = 0; j < sizeBetweenSegs; j++)
				printf("0");
			//printf("\n");
		}
		if (head != NULL){
			for(int j = 0; j < head->segSize; j++)
				printf("1");
			printf("\n");
		}
		prehead = head;
		head = head->next;
	}
}
