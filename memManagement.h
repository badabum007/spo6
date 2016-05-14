#include "linkedList.h"

struct MemoryManagement
{
	struct LinkedList* listHead;
	struct LinkedList* listTail;
	size_t freeMem;
	size_t maxFreeMem;
	void* memStartAddress;
};

void* findFreeMem(struct MemoryManagement* ,size_t);
void printmem(struct MemoryManagement*);
void defrag(struct MemoryManagement*);
