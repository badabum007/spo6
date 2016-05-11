#include "linkedList.h"

struct MemoryManagement
{
	struct LinkedList* linkedList;//pointer list  with size
	size_t freeMem;
	size_t maxFreeMem;
	void* memStartAddres;
	void* findFreeMem(size_t);
};