#include "memManagement.h"
#include <stdio.h>
#include <string.h>

void* findFreeMem(struct MemoryManagement* memManag, size_t size)
{
	int defragflg = 0;
	size_t notAppropriate;
	struct LinkedList* head;
	void* ptr, *preptr;
	size_t sizeBetweenSegs;
	struct LinkedList* prehead;

	start:
	notAppropriate = 0;
	if (memManag->freeMem == memManag->maxFreeMem){
		return memManag->memStartAddress;
	}

	head = memManag->listHead;
	ptr = head->segPtr;
	preptr = ptr;
	prehead = head;

	while(head->next != NULL){
		prehead = head;
		preptr = prehead->segPtr;
		head = head->next;
		ptr = head->segPtr;
		sizeBetweenSegs = (size_t)preptr - (size_t)ptr - head->segSize;
		if (sizeBetweenSegs >= size){
			return (void*)((char*)ptr + head->segSize);
		}
		notAppropriate += prehead->segSize + sizeBetweenSegs;
	}
	if (head != NULL){
		notAppropriate += head->segSize;
	}

	if ((int)(memManag->maxFreeMem - notAppropriate - size) < 0){
		if(defragflg == 0){
			defragflg = 1;
			defrag(memManag);
			goto start;
		}
		puts("big segmentation");
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
			for(int j = 0; j < sizeBetweenSegs; j++)
				printf("0");
			i += sizeBetweenSegs;
			printf("\n");
		}
		if (head != NULL){
			for(int j = 0; j < head->segSize; j++)
				printf("1");
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
	printf("\n");
}

void defrag(struct MemoryManagement* memManag)
{
	struct LinkedList* head = memManag->listTail;
	struct LinkedList* prehead = memManag->listTail;

	if (head == NULL)
		return;
	//shuffle first node to the left
	if ((char*)head->segPtr > (char*)memManag->memStartAddress){
		memmove(memManag->memStartAddress, head->segPtr, head->segSize);
		head->segPtr = memManag->memStartAddress;
	}

	while(head->prev != NULL){
		//copy data from next node to prev
		//first copying is from second to first
		prehead = head;
		head = head->prev;

		if ((int)((char*)prehead->segPtr + prehead->segSize < (char*)head->segPtr)){
			memmove((void*)((char*)prehead->segPtr + prehead->segSize), head->segPtr, head->segSize);
			head->segPtr = (void*)((char*)prehead->segPtr + prehead->segSize);
		}
	}
}

void memoryInit(struct MemoryManagement* memMan, int memorySize, void* memory)
{
	memMan->listHead = NULL;
	memMan->listTail = NULL;
	memMan->maxFreeMem = memorySize;
	memMan->freeMem  = memorySize;
	memMan->memStartAddress = memory;
}

void** my_malloc(struct MemoryManagement* memMan, size_t size)
{
	if (size == 0)
		return NULL;
	if(memMan->freeMem < size){
		puts("not enough memory");
		exit(1);
	}
	void* address;
	address = findFreeMem(memMan, size);
	void** ptrToAddress;
	ptrToAddress = push(&(memMan->listHead), &(memMan->listTail), address, size); //add ptr and size to memMan
	memMan->freeMem -= size;
	return ptrToAddress;
}

void my_free(struct MemoryManagement* memMan, void* ptr)
{
	size_t size;
	size = pop(&(memMan->listHead), &(memMan->listTail), ptr);
	memMan->freeMem += size;
}
