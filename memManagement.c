#include "memManagement.h"
#include <stdio.h>

void* findFreeMem(struct MemoryManagement* memManag, size_t size)
{
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
		exit(1);
	}
	return (void*)((char*)memManag->listHead->segPtr + memManag->listHead->segSize);
}

void printmem(struct MemoryManagement* memManag)
{
	struct LinkedList* head = memManag->listHead;
	struct LinkedList* prehead = memManag->listHead;
	size_t sizeBetweenSegs;
	void* ptr, *preptr;
	int i = 0;
	/*printf("%p\n", head->segPtr);
	exit(1);*/
	int freeMemAfterLastSeg = (int)(memManag->maxFreeMem - ((char*)head->segPtr
	 - (char*)memManag->memStartAddress) - head->segSize);
	if (freeMemAfterLastSeg > 0){
		/*puts("ORLY");
		exit(1);*/
		for ( ; i < freeMemAfterLastSeg;){
			printf("0");
			i++;
		}
		//printf("\n");
		//puts("ORLY");
	}
	for ( ; i < memManag->maxFreeMem;){
		if (head == NULL){
			break;
		}
		ptr = head->segPtr;
		preptr = prehead->segPtr;
		if (head != prehead){
			sizeBetweenSegs = (size_t)preptr - (size_t)ptr ;
			printf("%zd\n", sizeBetweenSegs);
			for(int j = 0; j < sizeBetweenSegs - head->segSize; j++)
				printf("0");
			i += sizeBetweenSegs - head->segSize;
		}
		if (head != NULL){
			for(int j = 0; j < head->segSize; j++)
				printf("1");
			printf("\n");
			i += head->segSize;
		}
		prehead = head;
		head = head->next;
	}

	if (i < memManag->maxFreeMem){
		while (i < memManag->maxFreeMem){
			printf("0");
			i++;
		}
		printf("\n");
	}
}
