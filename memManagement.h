#include "linkedList.h"

struct MemoryManagement
{
	struct LinkedList* linkedList;//pointer list  with size
	size_t freeMem;
	size_t maxFreeMem;
	size_t usedMem;
	void* memStartAddress;
};

void* findFreeMem(struct MemoryManagement* ,size_t);
void printmem(struct MemoryManagement*);
