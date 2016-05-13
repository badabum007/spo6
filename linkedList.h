#include <stdlib.h>

struct LinkedList {
	int segSize;
	void* segPtr;
	struct LinkedList* next;
};

void push(struct LinkedList**, void* addres, size_t size);
size_t pop(struct LinkedList**, void*); //delete node by ptr value