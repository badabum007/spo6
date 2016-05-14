#include "memManagement.h"
#include <stdio.h>
#include <string.h>

void* findFreeMem(struct MemoryManagement* memManag, size_t size)
{
	//start:
	puts("start find");
	size_t notAppropriate = 0;
	if (memManag->freeMem == memManag->maxFreeMem){
		return memManag->memStartAddress;
	}

	struct LinkedList* head = memManag->listHead;
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
	if (head != NULL){
		notAppropriate += head->segSize;
	}
	printf("notAppropriate %d\n", notAppropriate);
	//printf("%zd\n", memManag->maxFreeMem - notAppropriate - size);
	puts("bad iteration");
	if ((int)(memManag->maxFreeMem - notAppropriate - size) < 0){
		//printf("notAppropriate %d\n", notAppropriate);
		puts("big segmentation");
		//defrag();
		//goto start:
		exit(1);
	}
	return (void*)((char*)memManag->listHead->segPtr + memManag->listHead->segSize);
}

void printmem(struct MemoryManagement* memManag)
{
	struct LinkedList* head = memManag->listTail;
	struct LinkedList* prehead = memManag->listTail;
	size_t sizeBetweenSegs;
	void* ptr, *preptr;
	int i = 0;
	/*printf("%p\n", head->segPtr);
	exit(1);*/

	int freeMemAfterLastSeg = (int)((char*)head->segPtr
		- (char*)memManag->memStartAddress);
	if (freeMemAfterLastSeg > 0){
		for ( ; i < freeMemAfterLastSeg;){
			printf("0");
			i++;
		}
		printf("\n");
	}
	for ( ; i < memManag->maxFreeMem;){
		if (head == NULL){
			break;
		}
		ptr = head->segPtr;
		preptr = prehead->segPtr;
		if (head != prehead){
			sizeBetweenSegs = (size_t)ptr - (size_t)preptr - prehead->segSize;
			//printf("%zd\n", sizeBetweenSegs);
			for(int j = 0; j < sizeBetweenSegs; j++)
				printf("0");
			i += sizeBetweenSegs;
			printf("\n");
		}
		if (head != NULL){
			for(int j = 0; j < head->segSize; j++)
				printf("1");
			//printf("\n");
			i += head->segSize;
		}
		prehead = head;
		head = head->prev;
	}
	printf("\n");

	if (i < memManag->maxFreeMem){
		while (i < memManag->maxFreeMem){
			printf("0");
			i++;
		}
		printf("\n");
	}
}

void defrag(struct MemoryManagement* memManag){
	//pointer to pointer??
	struct LinkedList* head = memManag->listTail;
	struct LinkedList* prehead = memManag->listTail;

	if (head == NULL)
		return;
	//shuffle first node to the left
	if ((char*)head->segPtr > (char*)memManag->memStartAddress){
		memmove(memManag->memStartAddress, head->segPtr, head->segSize);
		head->segPtr = memManag->memStartAddress;
	}

	printf("\n");
	printmem(memManag);

	while(head->prev != NULL){
		//copy data from next node to prev
		//first copying is from second to first
		prehead = head;
		head = head->prev;

		if ((int)((char*)prehead->segPtr + prehead->segSize < (char*)head->segPtr)){
			memmove((void*)((char*)prehead->segPtr + prehead->segSize), head->segPtr, head->segSize);
			head->segPtr = (void*)((char*)prehead->segPtr + prehead->segSize);
			printf("\n");
			printmem(memManag);
		}
	}
}
