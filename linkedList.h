#include <stdlib.h>

struct LinkedList {
	int segSize;
	void* segPtr;
	struct LinkedList* next;
	struct LinkedList* prev;
};

void* push(struct LinkedList** head, struct LinkedList** tail, void* addres, size_t size);
size_t pop(struct LinkedList**, struct LinkedList** maintail, void*); //delete node by ptr value
void show(struct LinkedList* mainhead);