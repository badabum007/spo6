#include "linkedList.h"

struct MemoryManagement
{
	struct LinkedList* listHead;//pointer list  with size
	struct LinkedList* listTail;//pointer list  with size
	size_t freeMem;
	size_t maxFreeMem;
	void* memStartAddress;
};

void* findFreeMem(struct MemoryManagement* ,size_t);
void printmem(struct MemoryManagement*);
